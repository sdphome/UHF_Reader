
/*
 *   Author: Shao Depeng <dp.shao@gmail.com>
 *   Copyright 2016 Golden Sky Technology CO.,LTD
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <ltkc.h>
#include <xml.h>
#include <uhf.h>

static void upper_print_XML_message(LLRP_tSMessage * pMessage)
{
	char aBuf[100 * 1024];

	/*
	 * Convert the message to an XML string.
	 * This fills the buffer with either the XML string
	 * or an error message. The return value could
	 * be checked.
	 */
	LLRP_toXMLString(&pMessage->elementHdr, aBuf, sizeof aBuf);

	/*
	 * Print the XML Text to the standard output.
	 */
	printf("%s", aBuf);
}

static void upper_show_report_speed(upper_info_t * info)
{
	double speed;
	int64_t diff = 0;
	int64_t curr;
	struct timeval now;

	gettimeofday(&now, NULL);
	curr = ((uint64_t) now.tv_sec) * 1000 + ((uint64_t) now.tv_usec) / 1000;

	diff = curr - info->last_report_time;
	if (diff <= 0)
		printf("%s: timestamp disorder.\n", __func__);

	info->tid_count++;

	if (diff > 1000) {
		speed = (((double)(info->tid_count - info->last_tid_count)) *
				 (double)(1000)) / (double)diff;
		printf("%s:tid_diff=%lld, time_diff=%lld, speed is %.4f TIDs/sec.\n",
			   __func__, info->tid_count - info->last_tid_count, diff, speed);
		info->last_tid_count = info->tid_count;
		info->last_report_time = curr;
	}
}

static void inline lock_upper(pthread_mutex_t * lock)
{
	pthread_mutex_lock(lock);
}

static void inline unlock_upper(pthread_mutex_t * lock)
{
	pthread_mutex_unlock(lock);
}

static void upper_signal_response(upper_info_t * info, LLRP_tSMessage * pResponse)
{
	LLRP_tSMessage **ppResponseTail;

	lock_upper(&info->lock);

	ppResponseTail = &info->response_list;
	while (*ppResponseTail != NULL) {
		ppResponseTail = &(*ppResponseTail)->pQueueNext;
	}

	pResponse->pQueueNext = NULL;
	*ppResponseTail = pResponse;

	pthread_cond_broadcast(&info->cond);
	unlock_upper(&info->lock);
}

static void upper_signal_request(upper_info_t * info, LLRP_tSMessage * pRequest)
{
	LLRP_tSMessage **ppRequestTail;

	lock_upper(&info->req_lock);

	ppRequestTail = &info->request_list;
	while (*ppRequestTail != NULL) {
		ppRequestTail = &(*ppRequestTail)->pQueueNext;
	}

	pRequest->pQueueNext = NULL;
	*ppRequestTail = pRequest;

	pthread_cond_broadcast(&info->req_cond);
	unlock_upper(&info->req_lock);
}

static LLRP_tSMessage *upper_wait_response(upper_info_t * info, LLRP_tSMessage * pSendMessage)
{
	int responseReceived = 0;
	struct timeval now;
	struct timespec outtime;
	LLRP_tResultCode lrc;
	LLRP_tSMessage *pResponse;
	LLRP_tSMessage *pPrev;
	LLRP_tSConnection *pConn = info->pConn;
	const LLRP_tSTypeDescriptor *pErrorMsgType;
	LLRP_tSErrorDetails *pError = &pConn->Recv.ErrorDetails;
	llrp_u32_t ResponseMessageID = pSendMessage->MessageID;
	//const LLRP_tSTypeDescriptor *pResponseType = pSendMessage->elementHdr.pType->pResponseType;
	const LLRP_tSTypeDescriptor *pSendType = pSendMessage->elementHdr.pType;

	if (0 > pConn->fd) {
		LLRP_Error_resultCodeAndWhatStr(pError, LLRP_RC_MiscError, "not connected");
		return NULL;
	}

	pErrorMsgType = LLRP_TypeRegistry_lookupMessage(pConn->pTypeRegistry, 303u);

	gettimeofday(&now, NULL);
	outtime.tv_sec = now.tv_sec + info->pXmlConfig->config.upper.timeout;
	outtime.tv_nsec = now.tv_usec * 1000;

	while (!responseReceived) {
		lrc = pthread_cond_timedwait(&info->cond, &info->lock, &outtime);
		if (lrc == ETIMEDOUT) {
			LLRP_Error_resultCodeAndWhatStr(pError, LLRP_RC_RecvTimeout, "wait ack timeout");
			return NULL;
		}

		pPrev = info->response_list;
		pResponse = info->response_list;
		for (; pResponse != NULL; pResponse = pResponse->pQueueNext) {
			if (pResponse->elementHdr.pType == pErrorMsgType) {
				responseReceived = 1;
				break;
			}

			if (strncmp
				(pSendType->pName, pResponse->elementHdr.pType->pName, strlen(pSendType->pName))) {
				pPrev = pResponse;
				continue;
			}

			if (pResponse->MessageID == ResponseMessageID) {
				responseReceived = 1;
				break;
			}

			/*
			 * the xml doesn't contains ack type now which get from tmri,  so can't use
			 * this method to check response.
			 */

/*
			if (pResponseType != pResponse->elementHdr.pType) {
				pPrev = pResponse;
				continue;
			}
*/
			pPrev = pResponse;
			break;
		}
	}

	if (NULL != pResponse && responseReceived) {
		if (pPrev == pResponse)
			info->response_list = info->response_list->pQueueNext;
		else
			pPrev->pQueueNext = pResponse->pQueueNext;
		pResponse->pQueueNext = NULL;
		return pResponse;
	}

	return NULL;
}

static int upper_send_message(upper_info_t * info, LLRP_tSMessage * pSendMsg)
{
	int ret = NO_ERROR;
	LLRP_tSConnection *pConn = info->pConn;

	if (pConn == NULL || pSendMsg == NULL) {
		printf("%s: pConn(%p) or pSendMsg(%p) is null.\n", __func__, pConn, pSendMsg);
		return -FAILED;
	}

	if (info->status < UPPER_CONNECTED) {
		printf("%s: now status is %d.\n", __func__, info->status);
		return -FAILED;
	}
	/*
	 * Print the XML text for the outbound message if
	 * verbosity is 1 or higher.
	 */
	if (info->verbose > 0) {
		printf("\n===================================\n");
		printf("INFO: Sending:\n");
		upper_print_XML_message(pSendMsg);
	}
	pSendMsg->DeviceSN = info->serial;
	pSendMsg->Version = 1;

	/*
	 * If LLRP_Conn_sendMessage() returns other than LLRP_RC_OK
	 * then there was an error. In that case we try to print
	 * the error details.
	 */
	if (LLRP_RC_OK != LLRP_Conn_sendMessage(pConn, pSendMsg)) {
		const LLRP_tSErrorDetails *pError = LLRP_Conn_getSendError(pConn);

		printf("ERROR: %s sendMessage failed, %s\n",
			   pSendMsg->elementHdr.pType->pName,
			   pError->pWhatStr ? pError->pWhatStr : "no reason given");

		if (pError->pRefType != NULL) {
			printf("ERROR: ... reference type %s\n", pError->pRefType->pName);
		}

		if (pError->pRefField != NULL) {
			printf("ERROR: ... reference field %s\n", pError->pRefField->pName);
		}

		ret = -FAILED;
	}

	return ret;
}

/*
static void upper_hton_64(uint8_t * buf, llrp_u64_t value)
{
	int i = 0;

	if (buf == NULL)
		return;

	buf[i++] = value >> 56u;
	buf[i++] = value >> 48u;
	buf[i++] = value >> 40u;
	buf[i++] = value >> 32u;
	buf[i++] = value >> 24u;
	buf[i++] = value >> 16u;
	buf[i++] = value >> 8u;
	buf[i++] = value >> 0u;
}
*/

/*
static int upper_check_llrp_status(LLRP_tSStatus * pLLRPStatus, char *pWhatStr)
{
	if (NULL == pLLRPStatus) {
		printf("ERROR: %s missing LLRP status\n", pWhatStr);
		return -FAILED;
	}

	if (pLLRPStatus->eStatusCode != 0) {
		if (pLLRPStatus->ErrorDescription.nValue == 0) {
			printf("ERROR: %s failed, no error description given\n", pWhatStr);
		} else {
			printf("ERROR: %s failed, %.*s\n",
				   pWhatStr,
				   pLLRPStatus->ErrorDescription.nValue, pLLRPStatus->ErrorDescription.pValue);
		}
	}

	return -pLLRPStatus->eStatusCode;
}
*/
int upper_notify_connected_event(upper_info_t * info)
{
	int ret = NO_ERROR;
	struct timeval now;
	LLRP_tSDeviceEventNotification *pThis;
	LLRP_tSUTCTimestamp *pTimestamp;
	LLRP_tSConnectionAttemptEvent *pCAE;

	pThis = LLRP_DeviceEventNotification_construct();
	pTimestamp = LLRP_UTCTimestamp_construct();
	pCAE = LLRP_ConnectionAttemptEvent_construct();

	pThis->hdr.MessageID = info->next_msg_id++;
	gettimeofday(&now, NULL);
	LLRP_UTCTimestamp_setMicroseconds(pTimestamp,
									  (((uint64_t) now.tv_sec) * 1000 +
									   ((uint64_t) now.tv_usec) / 1000));
	LLRP_DeviceEventNotification_setUTCTimestamp(pThis, pTimestamp);

	LLRP_ConnectionAttemptEvent_setConnectionStatus(pCAE,
													LLRP_ConnectionAttemptEventStatusType_Success);
	LLRP_DeviceEventNotification_setConnectionAttemptEvent(pThis, pCAE);

	lock_upper(&info->lock);

	if (LLRP_RC_OK != upper_send_message(info, &pThis->hdr)) {
		ret = -FAILED;
	}

	unlock_upper(&info->lock);

	LLRP_DeviceEventNotification_destruct(pThis);

	info->status = UPPER_READY;
	return ret;
}

llrp_u32_t inline upper_conv_type32(llrp_u32_t value)
{
	return (((value) & 0xff) << 24) + (((value >> 8) & 0xff) << 16) +
		(((value >> 16) & 0xff) << 8) + (((value >> 24) & 0xff));
}

static int upper_write_to_file(char *path, llrp_u8v_t * data)
{
	int ret;
	FILE *fp;

	if (path == NULL) {
		printf("path is null.\n");
		return -FAILED;
	}

	remove(path);

	fp = fopen(path, "w");
	if (fp == NULL) {
		printf("%s: create file error.\n", __func__);
		return -FAILED;
	}

	ret = file_write_data(data->pValue, fp, data->nValue);
	if (ret != NO_ERROR) {
		printf("%s: write failed, nValue=%d.\n", __func__, data->nValue);
	}

	fclose(fp);
	return ret;
}

static LLRP_tSStatus *upper_setup_status(llrp_u32_t status, char *str)
{
	LLRP_tSStatus *pStatus;
	llrp_utf8v_t description;

	memset(&description, 0, sizeof(llrp_utf8v_t));
	pStatus = LLRP_Status_construct();

	if (str != NULL) {
		description.nValue = strlen(str);
		if (description.nValue > 0)
			description.pValue = malloc(description.nValue);
		if (description.pValue != NULL)
			memcpy(description.pValue, str, description.nValue);
	}
	LLRP_Status_setStatusCode(pStatus, status);
	LLRP_Status_setErrorDescription(pStatus, description);

	return pStatus;
}

void upper_trans_ip(uint8_t * ip_s, uint32_t ip_i)
{
	uint8_t each, tmp;
	int i = 0;
	int j = 0;
	int is_zero = 1;

	if (ip_i == 0) {
		ip_s[0] = '\0';
		return;
	}

	for (i = 0; i < 4; i++) {
		each = ip_i >> (8 * i);
		tmp = each / 100;
		if (tmp) {
			ip_s[j++] = tmp + '0';
			is_zero = 0;
		}

		tmp = (each % 100) / 10;
		if (!is_zero || tmp) {
			ip_s[j++] = tmp + '0';
		}

		tmp = each % 10;
		ip_s[j++] = tmp + '0';
		ip_s[j++] = '.';
		is_zero = 1;
	}

	ip_s[j - 1] = '\0';
}

/*
static void upper_request_ErrorAck(upper_info_t * info, LLRP_tEStatusCode status)
{
	LLRP_tSErrorAck *pEA;
	LLRP_tSStatus *pStatus;

	pEA = LLRP_ErrorAck_construct();
	pStatus = upper_setup_status(status);
	if (pEA == NULL || pStatus == NULL)
		goto out;

	pEA->hdr.MessageID = info->next_msg_id++;

	LLRP_ErrorAck_setStatus(pEA, pStatus);

	lock_upper(&info->lock);
	upper_send_message(info, &pEA->hdr);
	unlock_upper(&info->lock);

  out:
	if (pEA != NULL)
		LLRP_ErrorAck_destruct(pEA);
}

static int upper_request_Disconnect(upper_info_t * info)
{
	int ret = NO_ERROR;
	LLRP_tSDisconnect *pDis = NULL;
	LLRP_tSDisconnectAck *pAck = NULL;

	pDis = LLRP_Disconnect_construct();
	if (pDis == NULL)
		goto out;
	pDis->hdr.MessageID = info->next_msg_id++;

	lock_upper(&info->lock);
	ret = upper_send_message(info, &pDis->hdr);

	if (ret == NO_ERROR)
		pAck = (LLRP_tSDisconnectAck *) upper_wait_response(info, &pDis->hdr);

	unlock_upper(&info->lock);

	lock_upper(&info->disconnect_lock);
	pthread_cond_broadcast(&info->disconnect_cond);
	unlock_upper(&info->disconnect_lock);

  out:
	if (pDis != NULL)
		LLRP_Disconnect_destruct(pDis);
	if (pAck != NULL)
		LLRP_DisconnectAck_destruct(pAck);

	return ret;
}
*/

static int upper_request_Keepalive(upper_info_t * info)
{
	int ret = NO_ERROR;
	LLRP_tSKeepalive *pKA = NULL;
	LLRP_tSKeepaliveAck *pAck = NULL;

	if (info->status != UPPER_READY)
		return -FAILED;

	pKA = LLRP_Keepalive_construct();
	pKA->hdr.MessageID = info->next_msg_id++;

	lock_upper(&info->lock);
	ret = upper_send_message(info, &pKA->hdr);

	if (ret == NO_ERROR) {
		pAck = (LLRP_tSKeepaliveAck *) upper_wait_response(info, &pKA->hdr);
	}
	unlock_upper(&info->lock);

	LLRP_Keepalive_destruct(pKA);
	if (pAck != NULL) {
		LLRP_Element_destruct(&pAck->hdr.elementHdr);
	}

	return ret;
}

int upper_request_TagSelectAccessReport(upper_info_t * info, llrp_u64_t tid,
										llrp_u8_t anten_no, llrp_u64_t timestamp, void *part_data)
{
	int ret = NO_ERROR;
	tag_list_t *curr_list;
	tag_list_t *tag_list = NULL;
	tag_list_t *tag_list_prev = NULL;
	int new_tag = true;
	int need_notify = true;		/* TODO: re-check this condition */

	if (info == NULL) {
		printf("info is null.\n");
		return 0;
	}

	lock_upper(&info->upload_lock);

	upper_show_report_speed(info);

	if (info->status < UPPER_CONNECTED) {
		printf("%s: upper hasn't ready, status = %d, store tag info into db.\n", __func__,
			   info->status);
		tag_info_t tag;
		tag.TID = tid;
		tag.SelectSpecID = info->select_spec->SelectSpecID;
		tag.RfSpecID = info->select_spec->RfSpec.RfSpecId;
		tag.AntennalID = anten_no;
		tag.FirstSeenTimestampUTC = timestamp;
		tag.LastSeenTimestampUTC = timestamp;
		tag.AccessSpecID = 1;	/* FIXME */
		tag.TagSeenCount = 1;
		info->db_valid = true;
		sql_insert_tag_info(info->pXmlConfig->config.upper.db_path, &tag);
		goto out;
	}

	tag_list = info->tag_list;
	tag_list_prev = info->tag_list;

	while (tag_list != NULL) {
		tag_list_prev = tag_list;
		if (tag_list->tag.TID == tid) {
			new_tag = false;
			tag_list->tag.TagSeenCount += 1;
			tag_list->tag.LastSeenTimestampUTC = timestamp;
			/* if this tag first time have part data, then report it */
			if (tag_list->tag.PartData.nValue == 0 && part_data != NULL) {
				tag_list->tag.PartData = *(llrp_u8v_t *) part_data;
				tag_list->tag.FirstTime = true;
			} else {
				tag_list->tag.FirstTime = false;
				free(((llrp_u8v_t *) part_data)->pValue);
			}
			break;
		}
		tag_list = tag_list->next;
	}

	if (new_tag) {
		curr_list = (tag_list_t *) malloc(sizeof(tag_list_t));
		memset(curr_list, 0, sizeof(tag_list_t));
		if (curr_list == NULL)
			goto out;
		memset(curr_list, 0, sizeof(tag_list_t));
		curr_list->tag.TID = tid;
		curr_list->tag.SelectSpecID = info->select_spec->SelectSpecID;
		curr_list->tag.SpecIndex = 0;
		curr_list->tag.RfSpecID = info->select_spec->RfSpec.RfSpecId;
		curr_list->tag.AntennalID = anten_no;
		curr_list->tag.FirstSeenTimestampUTC = timestamp;
		curr_list->tag.LastSeenTimestampUTC = timestamp;
		curr_list->tag.AccessSpecID = 1;
		curr_list->tag.TagSeenCount = 1;
		curr_list->tag.FirstTime = true;
		if (part_data != NULL) {
			curr_list->tag.PartData = *(llrp_u8v_t *) part_data;
		}

		if (tag_list_prev == NULL)
			info->tag_list = curr_list;
		else
			tag_list_prev->next = curr_list;
		curr_list->next = NULL;
	}

	if (need_notify) {
		pthread_cond_broadcast(&info->upload_cond);
	}

  out:
	unlock_upper(&info->upload_lock);

	return ret;
}

// 600
static int upper_request_DeviceBinding(upper_info_t * info, uint8_t * binding, uint16_t len)
{
	int ret = NO_ERROR;
	LLRP_tSDeviceBinding *pDB = NULL;
	LLRP_tSDeviceBindingAck *pAck = NULL;
	LLRP_tSDeviceBindingResultNotification *pDBRN = NULL;
	llrp_u8v_t binding_data;

	if (info->status != UPPER_READY)
		goto out;

	pDB = LLRP_DeviceBinding_construct();
	if (pDB == NULL)
		goto out;

	pDB->hdr.MessageID = info->next_msg_id++;
	LLRP_DeviceBinding_setBindingType(pDB, *binding - 7);

	binding_data.nValue = len;
	binding_data.pValue = (llrp_u8_t *) malloc(len);
	if (binding_data.pValue == NULL)
		goto out;

	memcpy(binding_data.pValue, binding + 1, len);

	LLRP_DeviceBinding_setBindingData(pDB, binding_data);

	lock_upper(&info->lock);
	ret = upper_send_message(info, &pDB->hdr);
	printf("%s: ret = %d.\n", __func__, ret);

	if (ret == NO_ERROR) {
		pAck = (LLRP_tSDeviceBindingAck *) upper_wait_response(info, &pDB->hdr);
		ret = -FAILED;
	}

	unlock_upper(&info->lock);

	if (pAck != NULL) {
		llrp_u8v_t binding_result;
		LLRP_tSStatus *pStatus;

		binding_result = LLRP_DeviceBindingAck_getBindingResultData(pAck);
		pStatus = LLRP_DeviceBindingAck_getStatus(pAck);

		if (LLRP_Status_getStatusCode(pStatus) == 0) {
			ret = security_send_active_auth(((uhf_info_t *) (info->uhf))->security,
											binding_result.pValue, binding_result.nValue);
		} else {
			ret = FAILED;
		}

		pDBRN = LLRP_DeviceBindingResultNotification_construct();
		if (pDBRN == NULL)
			goto out;

		if (ret == NO_ERROR)
			pStatus = upper_setup_status(0, NULL);	//"BINDING SUCCESS!");
		else
			pStatus = upper_setup_status(0, NULL);	//"BINDING FAILED!");

		LLRP_DeviceBindingResultNotification_setStatus(pDBRN, pStatus);

		lock_upper(&info->lock);
		ret = upper_send_message(info, &pDBRN->hdr);
		unlock_upper(&info->lock);
	}

  out:
	printf("###############################################\n");
	printf("%s: the active result is %s.\n", __func__, ret ? "FAIL" : "SUCC");
	printf("###############################################\n");

	if (pDB != NULL) {
		LLRP_DeviceBinding_destruct(pDB);
	}

	if (pAck != NULL)
		LLRP_DeviceBindingAck_destruct(pAck);

	if (pDBRN != NULL)
		LLRP_DeviceBindingResultNotification_destruct(pDBRN);

	return ret;
}

// 303
static int upper_process_Disconnect(upper_info_t * info, LLRP_tSDisconnect * pDis)
{
	int ret = NO_ERROR;
	LLRP_tSDisconnectAck *pAck = NULL;

	pAck = LLRP_DisconnectAck_construct();
	if (pAck == NULL)
		goto out;

	pAck->hdr.MessageID = pDis->hdr.MessageID;

	lock_upper(&info->lock);
	ret = upper_send_message(info, &pAck->hdr);
	unlock_upper(&info->lock);

  out:
	if (pDis != NULL)
		LLRP_Disconnect_destruct(pDis);
	if (pAck != NULL)
		LLRP_DisconnectAck_destruct(pAck);

	return ret;
}

// 400
static int upper_process_AddSelectSpec(upper_info_t * info, LLRP_tSAddSelectSpec * pASS)
{
	int ret = NO_ERROR;
	char status[64] = { 0 };
	LLRP_tSAddSelectSpecAck *pASS_Ack = NULL;
	LLRP_tSSelectSpec *pSS = NULL;
	LLRP_tSSelectReportSpec *pSRS = NULL;
	LLRP_tSSelectSpecStartTrigger *pSSST = NULL;
	LLRP_tSAntennaSpec *pAS = NULL;
	LLRP_tSRfSpec *pRS = NULL;
	LLRP_tSMemoryBank *pMB = NULL;

	if (pASS == NULL)
		goto out;

	pSS = LLRP_AddSelectSpec_getSelectSpec(pASS);
	if (pSS == NULL) {
		ret = -1;
		goto ack;
	}

	/* process select spec start trigger */
	if (info->select_spec != NULL) {
		if (info->select_spec->SelectSpecID == LLRP_SelectSpec_getSelectSpecID(pSS) ||
			info->select_spec->Priority < LLRP_SelectSpec_getPriority(pSS)) {
			printf("this spec has exist, old SelectSpecID = %u, new SelectSpecID=%u,"
				   "old Priority = %u, new Priority = %u.\n", info->select_spec->SelectSpecID,
				   LLRP_SelectSpec_getSelectSpecID(pSS), info->select_spec->Priority,
				   LLRP_SelectSpec_getPriority(pSS));
			ret = -2;
			strncpy(status, "this spec has exist.", 64);
			goto ack;
		}
	}

/*
	else {
		info->select_spec = (select_spec_t *) malloc(sizeof(select_spec_t));
		if (info->select_spec == NULL) {
			printf("malloc for select_spec failed.\n");
			ret = -3;
			strncpy(status, "malloc memory for select spec failed.", 64);
			goto ack;
		}
		memset(info->select_spec, 0, sizeof(select_spec_t));
	}
*/
	info->select_spec->SelectSpecID = LLRP_SelectSpec_getSelectSpecID(pSS);
	info->select_spec->Priority = LLRP_SelectSpec_getPriority(pSS);
	info->select_spec->CurrentState = LLRP_SelectSpec_getCurrentState(pSS);
	info->select_spec->Persistence = LLRP_SelectSpec_getPersistence(pSS);
	pSSST = LLRP_SelectSpec_getSelectSpecStartTrigger(pSS);
	info->select_spec->SelectSpecStart.type =
		LLRP_SelectSpecStartTrigger_getSelectSpecStartTriggerType(pSSST);

	/* Just process one spec */
	pAS = (LLRP_tSAntennaSpec *) LLRP_SelectSpec_beginSpecParameter(pSS);
	pRS = LLRP_AntennaSpec_beginRfSpec(pAS);
	info->select_spec->RfSpec.RfSpecId = LLRP_RfSpec_getRfSpecID(pRS);
	info->select_spec->RfSpec.SelectType = LLRP_RfSpec_getSelectType(pRS);
	pMB = LLRP_RfSpec_getMemoryBank(pRS);
	if (pMB != NULL) {
		info->select_spec->RfSpec.MemoryBankId = LLRP_MemoryBank_getMemoryBankID(pMB);
		info->select_spec->RfSpec.BankType = LLRP_MemoryBank_getBankType(pMB);
	} else {
		info->select_spec->RfSpec.MemoryBankId = LLRP_HbSpecMemoryBankIDType_User_0;
		info->select_spec->RfSpec.BankType = LLRP_HbBankType_Full;
	}

	if (info->select_spec->SelectSpecStart.type == LLRP_SelectSpecStartTriggerType_Periodic) {
		LLRP_tSPeriodicTrigger *pPT = NULL;

		pPT = LLRP_SelectSpecStartTrigger_getPeriodicTrigger(pSSST);
		info->select_spec->SelectSpecStart.offset = LLRP_PeriodicTrigger_getOffset(pPT);
		info->select_spec->SelectSpecStart.period = LLRP_PeriodicTrigger_getPeriod(pPT);
		/* TODO: TBD */
	} else if (info->select_spec->SelectSpecStart.type == LLRP_SelectSpecStartTriggerType_Immediate) {
		rf_spec_t *rf_spec = &info->select_spec->RfSpec;
		/* setup security work mode */
		security_set_work_mode_helper(((uhf_info_t *) (info->uhf))->security, rf_spec->MemoryBankId,
									  rf_spec->BankType);

		/* start radio continue check */
		radio_start_conti_check(((uhf_info_t *) (info->uhf))->radio);
	}

	/* process report spec */
	pSRS = LLRP_SelectSpec_getSelectReportSpec(pSS);
	if (pSRS != NULL) {
		info->report_spec->SelectReportTrigger = LLRP_SelectReportSpec_getSelectReportTrigger(pSRS);
		info->report_spec->NValue = LLRP_SelectReportSpec_getNValue(pSRS);
		info->report_spec->mask = 0;
		if (LLRP_SelectReportSpec_getEnableSelectSpecID(pSRS)) {
			info->report_spec->mask |= ENABLE_SELECT_SPEC_ID;
		}
		if (LLRP_SelectReportSpec_getEnableSpecIndex(pSRS)) {
			info->report_spec->mask |= ENABLE_SPEC_INDEX;
		}
		if (LLRP_SelectReportSpec_getEnableRfSpecID(pSRS)) {
			info->report_spec->mask |= ENABLE_RF_SPEC_ID;
		}
		if (LLRP_SelectReportSpec_getEnableAntennaID(pSRS)) {
			info->report_spec->mask |= ENABLE_ANTENNAL_ID;
		}
		if (LLRP_SelectReportSpec_getEnablePeakRSSI(pSRS)) {
			info->report_spec->mask |= ENABLE_PEAK_RSSI;
		}
		if (LLRP_SelectReportSpec_getEnableFirstSeenTimestamp(pSRS)) {
			info->report_spec->mask |= ENABLE_FST;
		}
		if (LLRP_SelectReportSpec_getEnableLastSeenTimestamp(pSRS)) {
			info->report_spec->mask |= ENABLE_LST;
		}
		if (LLRP_SelectReportSpec_getEnableTagSeenCount(pSRS)) {
			info->report_spec->mask |= ENABLE_TSC;
		}
		if (LLRP_SelectReportSpec_getEnableAccessSpecID(pSRS)) {
			info->report_spec->mask |= ENABLE_ACCESS_SPEC_ID;
		}
	}

  ack:

	pASS_Ack = LLRP_AddSelectSpecAck_construct();
	if (pASS_Ack != NULL) {
		LLRP_tSStatus *pStatus = NULL;

		pStatus = upper_setup_status(-ret, status);
		LLRP_AddSelectSpecAck_setStatus(pASS_Ack, pStatus);
	}

	lock_upper(&info->lock);
	ret = upper_send_message(info, &pASS_Ack->hdr);
	unlock_upper(&info->lock);

	/* save the config into xml file */
	xml_save_config(info->pXmlConfig);

  out:
	if (pASS != NULL)
		LLRP_AddSelectSpec_destruct(pASS);
	if (pASS_Ack != NULL)
		LLRP_AddSelectSpecAck_destruct(pASS_Ack);

	return ret;
}

// 402
static int upper_process_DeleteSelectSpec(upper_info_t * info, LLRP_tSDeleteSelectSpec * pDSS)
{
	int ret = NO_ERROR;
	LLRP_tSDeleteSelectSpecAck *pDSS_Ack = NULL;
	LLRP_tSStatus *pStatus = NULL;

	if (pDSS == NULL)
		goto out;

	if (info->select_spec != NULL) {
		if (info->select_spec->SelectSpecID == LLRP_DeleteSelectSpec_getSelectSpecID(pDSS)) {
			/* FIXME : setup as default spec */
			info->select_spec->SelectSpecID = 234;
			info->select_spec->Priority = 7;
		}
	}

	/* save the config into xml file */
	xml_save_config(info->pXmlConfig);

	pDSS_Ack = LLRP_DeleteSelectSpecAck_construct();
	if (pDSS_Ack == NULL)
		goto out;

	pStatus = upper_setup_status(0, NULL);
	LLRP_DeleteSelectSpecAck_setStatus(pDSS_Ack, pStatus);

	lock_upper(&info->lock);
	ret = upper_send_message(info, &pDSS_Ack->hdr);
	unlock_upper(&info->lock);

  out:
	if (pDSS != NULL)
		LLRP_DeleteSelectSpec_destruct(pDSS);
	if (pDSS_Ack != NULL)
		LLRP_DeleteSelectSpecAck_destruct(pDSS_Ack);

	return ret;
}

// 404
static int upper_process_StartSelectSpec(upper_info_t * info, LLRP_tSStartSelectSpec * pSSS)
{
	int ret = NO_ERROR;
	LLRP_tSStartSelectSpecAck *pSSS_Ack = NULL;

	if (pSSS == NULL)
		goto out;

//  ack:
	pSSS_Ack = LLRP_StartSelectSpecAck_construct();

  out:
	if (pSSS != NULL)
		LLRP_StartSelectSpec_destruct(pSSS);
	if (pSSS_Ack != NULL)
		LLRP_StartSelectSpecAck_destruct(pSSS_Ack);

	return ret;
}

// 406
static int upper_process_StopSelectSpec(upper_info_t * info, LLRP_tSStopSelectSpec * pSSS)
{
	int ret = NO_ERROR;
	LLRP_tSStopSelectSpecAck *pSSS_Ack = NULL;

	if (pSSS == NULL)
		goto out;

  out:
	if (pSSS != NULL)
		LLRP_StopSelectSpec_destruct(pSSS);
	if (pSSS_Ack != NULL)
		LLRP_StopSelectSpecAck_destruct(pSSS_Ack);

	return ret;
}

// 408
static int upper_process_EnableSelectSpec(upper_info_t * info, LLRP_tSEnableSelectSpec * pESS)
{
	int ret = NO_ERROR;
	LLRP_tSEnableSelectSpecAck *pESS_Ack = NULL;

	if (pESS == NULL)
		goto out;

  out:
	if (pESS != NULL)
		LLRP_EnableSelectSpec_destruct(pESS);
	if (pESS_Ack != NULL)
		LLRP_EnableSelectSpecAck_destruct(pESS_Ack);

	return ret;
}

// 410
static int upper_process_DisableSelectSpec(upper_info_t * info, LLRP_tSDisableSelectSpec * pDSS)
{
	int ret = NO_ERROR;
	LLRP_tSDisableSelectSpecAck *pDSS_Ack = NULL;

	if (pDSS == NULL)
		goto out;

  out:
	if (pDSS != NULL)
		LLRP_DisableSelectSpec_destruct(pDSS);
	if (pDSS_Ack != NULL)
		LLRP_DisableSelectSpecAck_destruct(pDSS_Ack);

	return ret;
}

// 450
static int upper_process_AddAccessSpec(upper_info_t * info, LLRP_tSAddAccessSpec * pAAS)
{
	int ret = NO_ERROR;
	LLRP_tSAddAccessSpecAck *pAAS_Ack = NULL;
	LLRP_tSAccessSpec *pAS = NULL;

	if (pAAS == NULL)
		goto out;

	pAS = LLRP_AddAccessSpec_getAccessSpec(pAAS);
	if (pAS == NULL)
		goto out;

  out:
	if (pAAS != NULL)
		LLRP_AddAccessSpec_destruct(pAAS);
	if (pAAS_Ack != NULL)
		LLRP_AddAccessSpecAck_destruct(pAAS_Ack);

	return ret;
}

// 452
static int upper_process_DeleteAccessSpec(upper_info_t * info, LLRP_tSDeleteAccessSpec * pDAS)
{
	int ret = NO_ERROR;
	LLRP_tSDeleteAccessSpecAck *pDAS_Ack = NULL;

	if (pDAS == NULL)
		goto out;

  out:
	if (pDAS != NULL)
		LLRP_DeleteAccessSpec_destruct(pDAS);
	if (pDAS_Ack != NULL)
		LLRP_DeleteAccessSpecAck_destruct(pDAS_Ack);

	return ret;
}

// 454
static int upper_process_EnableAccessSpec(upper_info_t * info, LLRP_tSEnableAccessSpec * pEAS)
{
	int ret = NO_ERROR;
	LLRP_tSEnableAccessSpecAck *pEAS_Ack = NULL;

	if (pEAS == NULL)
		goto out;

  out:
	if (pEAS != NULL)
		LLRP_EnableAccessSpec_destruct(pEAS);
	if (pEAS_Ack != NULL)
		LLRP_EnableAccessSpecAck_destruct(pEAS_Ack);

	return ret;
}

// 456
static int upper_process_DisableAccessSpec(upper_info_t * info, LLRP_tSDisableAccessSpec * pDAS)
{
	int ret = NO_ERROR;
	LLRP_tSDisableAccessSpecAck *pDAS_Ack = NULL;

	if (pDAS == NULL)
		goto out;

  out:
	if (pDAS != NULL)
		LLRP_DisableAccessSpec_destruct(pDAS);
	if (pDAS_Ack != NULL)
		LLRP_DisableAccessSpecAck_destruct(pDAS_Ack);

	return ret;
}

// 602
static int upper_process_DeviceCertificateConfig(upper_info_t * info,
												 LLRP_tSDeviceCertificateConfig * pDCC)
{
	int ret = NO_ERROR;
	LLRP_tSDeviceCertificateConfigAck *pDCC_Ack;
	LLRP_tSStatus *pStatus;
	llrp_utf8v_t Error;
	llrp_u8v_t pCer;
	llrp_u8v_t pUser;

	pDCC_Ack = LLRP_DeviceCertificateConfigAck_construct();
	pStatus = LLRP_Status_construct();
	memset(&Error, 0, sizeof(llrp_utf8v_t));
	LLRP_Status_setStatusCode(pStatus, 0);
	LLRP_Status_setErrorDescription(pStatus, Error);
	LLRP_DeviceCertificateConfigAck_setStatus(pDCC_Ack, pStatus);
	pDCC_Ack->hdr.MessageID = pDCC->hdr.MessageID;
	pDCC_Ack->hdr.Version = pDCC->hdr.Version;

	lock_upper(&info->lock);

	ret = upper_send_message(info, &pDCC_Ack->hdr);

	unlock_upper(&info->lock);

	pCer = LLRP_DeviceCertificateConfig_getCertificateData(pDCC);
	pUser = LLRP_DeviceCertificateConfig_getUserData(pDCC);

	ret += upper_write_to_file(info->pXmlConfig->config.active_cert_path, &pCer);
	ret += upper_write_to_file(info->pXmlConfig->config.user_info_path, &pUser);

	if (ret == NO_ERROR) {
		security_package_t result;
		active_req_param *active_req;

		ret = security_send_cert(((uhf_info_t *) (info->uhf))->security, pCer.pValue, pCer.nValue);

		ret = security_send_user_info(((uhf_info_t *) (info->uhf))->security, &result);
		if (ret == NO_ERROR && result.payload != NULL) {
			active_req = (active_req_param *) result.payload;
			printf("active flag=%d, len=%x, mode=%d, serial=%llx.\n", active_req->active_flag,
				   active_req->len, active_req->mode, active_req->serial);
			upper_request_DeviceBinding(info, result.payload, result.hdr.len - 2);
			free(result.payload);
			result.payload = NULL;
		} else {
			printf("security_send_user_info return %d.\n", ret);
			ret = -FAILED;
		}
	}

	LLRP_DeviceCertificateConfig_destruct(pDCC);
	LLRP_DeviceCertificateConfigAck_destruct(pDCC_Ack);

	return ret;
}

// 620
static int upper_process_UploadTagLog(upper_info_t * info, LLRP_tSUploadTagLog * pThis)
{
	int ret = NO_ERROR;
	LLRP_tSUploadTagLogAck *pUTL_Ack = NULL;
	LLRP_tSStatus *pStatus = NULL;
	llrp_u32_t status = 0;

	/* TODO: upload tag log */

	pUTL_Ack = LLRP_UploadTagLogAck_construct();
	pStatus = upper_setup_status(status, NULL);
	if (pUTL_Ack == NULL || pStatus == NULL)
		goto out;

	LLRP_UploadTagLogAck_setStatus(pUTL_Ack, pStatus);

  out:
	if (pThis != NULL)
		LLRP_UploadTagLog_destruct(pThis);
	if (pUTL_Ack == NULL)
		LLRP_UploadTagLogAck_destruct(pUTL_Ack);
	return ret;
}

// 622
static int upper_process_ClearTagLog(upper_info_t * info, LLRP_tSClearTagLog * pThis)
{
	int ret = NO_ERROR;
	LLRP_tSClearTagLogAck *pCTL_Ack = NULL;
	LLRP_tSStatus *pStatus = NULL;
	llrp_u32_t status = 0;

	/* TODO: clear tag log */

	pCTL_Ack = LLRP_ClearTagLogAck_construct();
	pStatus = upper_setup_status(status, NULL);
	if (pCTL_Ack == NULL || pStatus == NULL)
		goto out;

	LLRP_ClearTagLogAck_setStatus(pCTL_Ack, pStatus);

  out:
	if (pThis != NULL)
		LLRP_ClearTagLog_destruct(pThis);
	if (pCTL_Ack != NULL)
		LLRP_ClearTagLogAck_destruct(pCTL_Ack);

	return ret;

}

// 640
static int upper_process_UploadDeviceLog(upper_info_t * info, LLRP_tSUploadDeviceLog * pThis)
{
	int ret = NO_ERROR;
	LLRP_tSUploadDeviceLogAck *pUDL_Ack = NULL;
	LLRP_tSStatus *pStatus = NULL;
	llrp_u32_t status = 0;

	/* TODO: upload device log */

	pUDL_Ack = LLRP_UploadDeviceLogAck_construct();
	pStatus = upper_setup_status(status, NULL);
	if (pUDL_Ack == NULL || pStatus == NULL)
		goto out;

	LLRP_UploadDeviceLogAck_setStatus(pUDL_Ack, pStatus);

  out:
	if (pThis != NULL)
		LLRP_UploadDeviceLog_destruct(pThis);
	if (pUDL_Ack == NULL)
		LLRP_UploadDeviceLogAck_destruct(pUDL_Ack);

	return ret;
}

// 642
static int upper_process_ClearDeviceLog(upper_info_t * info, LLRP_tSClearDeviceLog * pThis)
{
	int ret = NO_ERROR;
	LLRP_tSClearDeviceLogAck *pCDL_Ack = NULL;
	LLRP_tSStatus *pStatus = NULL;
	llrp_u32_t status = 0;

	/* TODO: clear device log */

	pCDL_Ack = LLRP_ClearDeviceLogAck_construct();
	pStatus = upper_setup_status(status, NULL);
	if (pCDL_Ack == NULL || pStatus == NULL)
		goto out;

	LLRP_ClearDeviceLogAck_setStatus(pCDL_Ack, pStatus);

  out:
	if (pThis != NULL)
		LLRP_ClearDeviceLog_destruct(pThis);
	if (pCDL_Ack != NULL)
		LLRP_ClearDeviceLogAck_destruct(pCDL_Ack);

	return ret;
}

// 662
static int upper_process_SetDeviceConfig(upper_info_t * info, LLRP_tSSetDeviceConfig * pThis)
{
	int ret = NO_ERROR;
	LLRP_tSSetDeviceConfigAck *pSDC_Ack = NULL;
	LLRP_tSStatus *pStatus;
	llrp_u32_t status = 0;

	// Identification Parameter
	if (pThis->pIdentification != NULL) {
		LLRP_tSIdentification *pID = NULL;

		pID = LLRP_SetDeviceConfig_getIdentification(pThis);

		printf("%s: DeviceName: %s.\n", __func__, pID->DeviceName.pValue);
	}
	// CommunicationConfiguration Parameter
	if (pThis->pCommunicationConfiguration != NULL) {
		LLRP_tSCommunicationConfiguration *pCC = NULL;
		LLRP_tSCommLinkConfiguration *pCLC = NULL;
		LLRP_tSNTPConfiguration *pNTPC = NULL;
		LLRP_tSParameter *pEC = NULL;

		pCC = LLRP_SetDeviceConfig_getCommunicationConfiguration(pThis);

		for (pCLC = LLRP_CommunicationConfiguration_beginCommLinkConfiguration(pCC);
			 pCLC != NULL; pCLC = LLRP_CommunicationConfiguration_nextCommLinkConfiguration(pCLC)) {
			/* Just support TCP now */
			if (LLRP_CommLinkConfiguration_getLinkType(pCLC) == LLRP_CommLinkType_Tcp) {
				LLRP_tSKeepaliveSpec *pKS = NULL;
				LLRP_tSTcpLinkConfiguration *pTLC = NULL;
				pKS = LLRP_CommLinkConfiguration_getKeepaliveSpec(pCLC);
				if (LLRP_KeepaliveSpec_getKeepaliveTriggerType(pKS))
					info->heartbeats_periodic = LLRP_KeepaliveSpec_getPeriodicTriggerValue(pKS);
				else
					info->heartbeats_periodic = 0;

				pTLC = LLRP_CommLinkConfiguration_getTcpLinkConfiguration(pCLC);
				if (pTLC != NULL) {
					/* Just support Server mode now */
					if (LLRP_TcpLinkConfiguration_getCommMode(pTLC) == LLRP_TcpLinkCommMode_Server) {
						LLRP_tSServerModeConfiguration *pSMC = NULL;
						pSMC = LLRP_TcpLinkConfiguration_getServerModeConfiguration(pTLC);
						if (pSMC != NULL)
							info->port = LLRP_ServerModeConfiguration_getPort(pSMC);
					}
				}
				break;
			}
		}

		/* just process one vaild ip setting */
		pEC = LLRP_CommunicationConfiguration_beginEthernetConfiguration(pCC);
		if (pEC != NULL) {
			const LLRP_tSTypeDescriptor *pType;
			pType = pEC->elementHdr.pType;
			if (&LLRP_tdEthernetIpv4Configuration == pType) {
				LLRP_tSEthernetIpv4Configuration *pEIV4C = NULL;
				printf("Setup ipv4---------------\n");
				pEIV4C = (LLRP_tSEthernetIpv4Configuration *) pEC;
				if (!LLRP_EthernetIpv4Configuration_getIsDHCP(pEIV4C)) {
					char cmd[128];
					uint8_t ip[16];
					uint8_t mask[16];
					uint8_t gate[16];
					uint8_t dns[16];

					upper_trans_ip(ip,
								   upper_conv_type32(LLRP_EthernetIpv4Configuration_getIPAddress
													 (pEIV4C)));
					upper_trans_ip(mask,
								   upper_conv_type32(LLRP_EthernetIpv4Configuration_getIPMask
													 (pEIV4C)));
					upper_trans_ip(gate,
								   upper_conv_type32(LLRP_EthernetIpv4Configuration_getGateWayAddr
													 (pEIV4C)));
					upper_trans_ip(dns, LLRP_EthernetIpv4Configuration_getDNSAddr(pEIV4C));

					memset(cmd, 0, 128);
					sprintf(cmd, "setup_ip.sh static %s %s %s %s", ip, mask, gate, dns);
					system(cmd);
				} else {
					char cmd[32];

					memset(cmd, 0, sizeof(cmd));
					sprintf(cmd, "setup_ip.sh auto");
					system(cmd);
				}
				/*TODO: may need reboot or wait request reset */
			}
		}

		pNTPC = LLRP_CommunicationConfiguration_getNTPConfiguration(pCC);
		if (pNTPC != NULL) {
			LLRP_tSIPAddress *pIPA = NULL;

			info->ntp_left_sec = LLRP_NTPConfiguration_getNtpPeriodicTime(pNTPC) * 3600;
			system("mv /etc/ntp.conf /etc/ntp.conf.bak");
			for (pIPA = LLRP_NTPConfiguration_beginIPAddress(pNTPC);
				 pIPA != NULL; pIPA = LLRP_NTPConfiguration_nextIPAddress(pIPA)) {
				/* just support ipv4 now */
				if (LLRP_IPAddress_getVersion(pIPA) == LLRP_IPAddressVersion_Ipv4) {
					FILE *fp = NULL;
					uint8_t ip[16];

					upper_trans_ip(ip, upper_conv_type32(*((llrp_u32_t *)
														   (LLRP_IPAddress_getAddress
															(pIPA)).pValue)));

					fp = fopen("/etc/ntp.conf", "a+");
					if (fp == NULL) {
						system("mv /etc/ntp.conf.bak /etc/ntp.conf");
						break;
					}
					printf("%s: setup ntp, ip = %s.\n", __func__, ip);
					file_write_data((uint8_t *) "\n", fp, 1);
					file_write_data((uint8_t *) "server ", fp, 7);
					file_write_data(ip, fp, strlen((char *)ip));
					file_write_data((uint8_t *) "\n", fp, 1);
					fclose(fp);
				}
			}
			system("ntpd");
		}
	}

	pSDC_Ack = LLRP_SetDeviceConfigAck_construct();
	pStatus = upper_setup_status(status, NULL);
	if (pSDC_Ack == NULL || pStatus == NULL)
		goto out;

	LLRP_SetDeviceConfigAck_setStatus(pSDC_Ack, pStatus);

  out:
	lock_upper(&info->upload_lock);
	upper_send_message(info, &pSDC_Ack->hdr);
	unlock_upper(&info->upload_lock);

	if (pThis != NULL)
		LLRP_SetDeviceConfig_destruct(pThis);

	if (pSDC_Ack != NULL)
		LLRP_SetDeviceConfigAck_destruct(pSDC_Ack);

	return ret;
}

// 702
static void upper_process_SetVersion(upper_info_t * info, LLRP_tSSetVersion * pThis)
{
	char cmd[128];
	char *local_file = NULL;
	uint8_t server_type = 0;
	unsigned long filesize = 0;
	LLRP_tSStatus *pStatus = NULL;
	LLRP_tSSetVersionAck *pAck = NULL;
	LLRP_tSVersionDownload *pVD = NULL;
	/* FIXME: it should be other status */
	llrp_u32_t status = 5555;

	memset(cmd, 0, 100);

	if (pThis->eVerType == LLRP_VersionType_Device_Boot) {
		local_file = "boot.bin";
	} else if (pThis->eVerType == LLRP_VersionType_Device_Sys) {
		local_file = "system.bin";
	} else if (pThis->eVerType == LLRP_VersionType_Device_Sys) {
		local_file = "security.bin";
	} else if (pThis->eVerType == LLRP_VersionType_Security_Chip_Sys) {
		local_file = "sec_chip.bin";
	} else if (pThis->eVerType == LLRP_VersionType_Security_Module_Pwd) {
		local_file = "radio.bin";
	} else {
		goto out;
	}

	pVD = LLRP_SetVersion_getVersionDownload(pThis);
	if (pVD == NULL) {
		goto out;
	}

	server_type = LLRP_VersionDownload_getServerType(pVD);
	if (server_type != LLRP_VersionDownloadServerType_Ftp
		|| server_type != LLRP_VersionDownloadServerType_Tftp) {
		goto out;
	} else {
		uint8_t ip[16];
		LLRP_tSIPAddress *pIP;

		pIP = LLRP_VersionDownload_getIPAddress(pVD);

		upper_trans_ip(ip, *(pIP->Address.pValue));

		if (server_type == LLRP_VersionDownloadServerType_Ftp)
			sprintf(cmd, "ftpget -u %s -p %s %s %s %s", pVD->UserName.pValue,
					pVD->UserPass.pValue, ip, local_file, pVD->VersionPath.pValue);
		else
			sprintf(cmd, "tftp -l %s -r %s -g %s", local_file, pVD->VersionPath.pValue, ip);

		printf("%s: cmd is %s.\n", __func__, cmd);
		system(cmd);
	}

	if (file_get_size(local_file, &filesize) == NO_ERROR && filesize > 0)
		status = 0;

  out:
	pStatus = upper_setup_status(status, NULL);
	pAck = LLRP_SetVersionAck_construct();
	LLRP_SetVersionAck_setStatus(pAck, pStatus);

	lock_upper(&info->lock);
	upper_send_message(info, &pAck->hdr);
	unlock_upper(&info->lock);

	LLRP_SetVersionAck_destruct(pAck);
	LLRP_SetVersion_destruct(pThis);
}

// 704
static void upper_process_ActiveVersion(upper_info_t * info, LLRP_tSActiveVersion * pThis)
{
	int ret;
	LLRP_tEVersionType type;
	char *message = NULL;
	LLRP_tSActiveVersionAck *pAck = NULL;
	LLRP_tSStatus *pStatus = NULL;

	type = LLRP_ActiveVersion_getVerType(pThis);

	/* TODO: */
	switch (type) {
	  case LLRP_VersionType_Device_Boot:
		  break;
	  case LLRP_VersionType_Device_Sys:
		  break;
	  case LLRP_VersionType_Security_Module_Sys:
		  break;
	  case LLRP_VersionType_Security_Chip_Sys:
		  ret = security_upgrade_firmware(((uhf_info_t *) (info->uhf))->security,
										  info->pXmlConfig->config.security.fw_path);
		  if (ret == -ENOENT)
			  message = "No such file";
		  else if (ret == -FAILED)
			  message = "Upgrade failed";
		  else
			  message = "Unknow error";
		  break;
	  case LLRP_VersionType_Security_Module_Pwd:
		  ret = radio_update_firmware(((uhf_info_t *) (info->uhf))->radio);
		  break;
	  default:
		  ret = -FAILED;
		  message = "No such version type";
		  printf("%s: error version type : %d.\n", __func__, type);
	}

	pAck = LLRP_ActiveVersionAck_construct();
	if (pAck == NULL)
		goto out;

	pStatus = upper_setup_status(-ret, message);
	if (pStatus == NULL)
		goto out;

	LLRP_ActiveVersionAck_setStatus(pAck, pStatus);

	lock_upper(&info->upload_lock);
	upper_send_message(info, &pAck->hdr);
	unlock_upper(&info->upload_lock);

  out:
	if (pThis != NULL)
		LLRP_ActiveVersion_destruct(pThis);

	if (pAck != NULL)
		LLRP_ActiveVersionAck_destruct(pAck);
}

// 760
static void upper_process_ResetDevice(upper_info_t * info)
{
	/* May need reconnect after reboot */
	//upper_request_Disconnect(info);
	sync();
	system("reboot");
}

static void upper_process_request(upper_info_t * info, LLRP_tSMessage * pRequest)
{
	uint16_t type;

	type = pRequest->elementHdr.pType->TypeNum;

	printf("%s: id[%d] type[%d] %s +\n", __func__, pRequest->MessageID, type,
		   pRequest->elementHdr.pType->pName);

	switch (type) {
	  case 303:				//Disconnect
		  upper_process_Disconnect(info, (LLRP_tSDisconnect *) pRequest);
		  break;
	  case 350:				//GetDeviceCapabilities
		  break;
	  case 400:				//AddSelectSpec
		  upper_process_AddSelectSpec(info, (LLRP_tSAddSelectSpec *) pRequest);
		  break;
	  case 402:				//DeleteSelectSpec
		  upper_process_DeleteSelectSpec(info, (LLRP_tSDeleteSelectSpec *) pRequest);
		  break;
	  case 404:				//StartSelectSpec
		  upper_process_StartSelectSpec(info, (LLRP_tSStartSelectSpec *) pRequest);
		  break;
	  case 406:				//StopSelectSpec
		  upper_process_StopSelectSpec(info, (LLRP_tSStopSelectSpec *) pRequest);
		  break;
	  case 408:				//EnableSelectSpec
		  upper_process_EnableSelectSpec(info, (LLRP_tSEnableSelectSpec *) pRequest);
		  break;
	  case 410:				//DisableSelectSpecAck
		  upper_process_DisableSelectSpec(info, (LLRP_tSDisableSelectSpec *) pRequest);
		  break;
	  case 412:				//GetSelectSpec
		  break;
	  case 450:				//AddAccessSpec
		  upper_process_AddAccessSpec(info, (LLRP_tSAddAccessSpec *) pRequest);
		  break;
	  case 452:				//DeleteAccessSpec
		  upper_process_DeleteAccessSpec(info, (LLRP_tSDeleteAccessSpec *) pRequest);
		  break;
	  case 454:				//EnableAccessSpec
		  upper_process_EnableAccessSpec(info, (LLRP_tSEnableAccessSpec *) pRequest);
		  break;
	  case 456:				//DisableAccessSpec
		  upper_process_DisableAccessSpec(info, (LLRP_tSDisableAccessSpec *) pRequest);
		  break;
	  case 458:				//GetAccessSpec
		  break;
	  case 600:				//DeviceBinding
		  break;
	  case 602:				//DeviceCertificateConfig
		  upper_process_DeviceCertificateConfig(info, (LLRP_tSDeviceCertificateConfig *) pRequest);
		  break;
	  case 620:				//UploadTagLog
		  upper_process_UploadTagLog(info, (LLRP_tSUploadTagLog *) pRequest);
		  break;
	  case 622:				//ClearTagLog
		  upper_process_ClearTagLog(info, (LLRP_tSClearTagLog *) pRequest);
		  break;
	  case 640:				//UploadDeviceLog
		  upper_process_UploadDeviceLog(info, (LLRP_tSUploadDeviceLog *) pRequest);
		  break;
	  case 642:				//ClearDeviceLog
		  upper_process_ClearDeviceLog(info, (LLRP_tSClearDeviceLog *) pRequest);
		  break;
	  case 660:				//GetDeviceConfig
		  break;
	  case 662:				//SetDeviceConfig
		  upper_process_SetDeviceConfig(info, (LLRP_tSSetDeviceConfig *) pRequest);
		  break;
	  case 700:				//GetVersion
		  break;
	  case 702:				//SetVersion
		  upper_process_SetVersion(info, (LLRP_tSSetVersion *) pRequest);
		  break;
	  case 704:				//ActiveVersion
		  upper_process_ActiveVersion(info, (LLRP_tSActiveVersion *) pRequest);
		  break;
	  case 706:				//UnAciveVersion
		  break;
	  case 760:				//ResetDevice
		  upper_process_ResetDevice(info);
		  break;
	  default:
		  printf("%s: hasn't support this type.\n", __func__);
		  LLRP_Element_finalDestruct((LLRP_tSElement *) pRequest);
		  break;
	}

	printf("%s: type = %d -\n", __func__, type);
}

void upper_check_local_spec(upper_info_t * info)
{

}

int upper_send_heartbeat(upper_info_t * info)
{
	return upper_request_Keepalive(info);
}

void *upper_upload_loop(void *data)
{
	upper_info_t *info = (upper_info_t *) data;
	LLRP_tSTagSelectAccessReport *pTSAR;
	llrp_u64_t curr_timestamp;
	int found = false;
	struct timeval now;

	while (true) {
		lock_upper(&info->upload_lock);
		pthread_cond_wait(&info->upload_cond, &info->upload_lock);

		if (info->status <= UPPER_DISCONNECTED) {
			unlock_upper(&info->upload_lock);
			return NULL;
		}

		if (info->db_valid == true) {
			sql_get_tag_info(info->pXmlConfig->config.upper.db_path, &info->tag_list);
			info->db_valid = false;
		}

		gettimeofday(&now, NULL);
		curr_timestamp = ((uint64_t) now.tv_sec) * 1000 + ((uint64_t) now.tv_usec) / 1000;

		if (info->tag_list != NULL) {
			tag_list_t *tag_list = info->tag_list;
			tag_list_t *tag_list_prev = info->tag_list->next;

			pTSAR = LLRP_TagSelectAccessReport_construct();
			if (pTSAR == NULL)
				continue;
			pTSAR->hdr.MessageID = info->next_msg_id++;

			while (tag_list != NULL) {
				tag_info_t *tag_info = &tag_list->tag;
				/* FIXME: maybe other condiction */
				if (curr_timestamp - tag_info->LastSeenTimestampUTC > 5000 ||
					tag_info->TagSeenCount >= info->report_spec->NValue ||
					tag_info->FirstTime == true) {
					LLRP_tSTagReportData *pTRD = NULL;
					llrp_u8v_t Tid;

					found = true;
					tag_info->TagSeenCount = 0;

					pTRD = LLRP_TagReportData_construct();
					Tid.nValue = 8;
					Tid.pValue = (llrp_u8_t *) malloc(Tid.nValue);
					memcpy(Tid.pValue, &tag_info->TID, 8);

					LLRP_TagReportData_setTID(pTRD, Tid);

					if (info->report_spec->mask | ENABLE_SELECT_SPEC_ID) {
						LLRP_tSSelectSpecID *pSSID = NULL;
						pSSID = LLRP_SelectSpecID_construct();
						LLRP_SelectSpecID_setSelectSpecID(pSSID, tag_info->SelectSpecID);
						LLRP_TagReportData_setSelectSpecID(pTRD, pSSID);
					}

					if (info->report_spec->mask | ENABLE_SPEC_INDEX) {
						LLRP_tSSpecIndex *pSI = NULL;
						pSI = LLRP_SpecIndex_construct();
						LLRP_SpecIndex_setSpecIndex(pSI, tag_info->SpecIndex);
						LLRP_TagReportData_setSpecIndex(pTRD, pSI);
					}

					if (info->report_spec->mask | ENABLE_RF_SPEC_ID) {
						LLRP_tSRfSpecID *pRSID = NULL;
						pRSID = LLRP_RfSpecID_construct();
						LLRP_RfSpecID_setRfSpecID(pRSID, tag_info->RfSpecID);
						LLRP_TagReportData_setRfSpecID(pTRD, pRSID);
					}

					if (info->report_spec->mask | ENABLE_ANTENNAL_ID) {
						LLRP_tSAntennaID *pAID = NULL;
						pAID = LLRP_AntennaID_construct();
						LLRP_AntennaID_setAntennaID(pAID, tag_info->AntennalID);
						LLRP_TagReportData_setAntennaID(pTRD, pAID);
					}

					if (info->report_spec->mask | ENABLE_FST) {
						LLRP_tSFirstSeenTimestampUTC *pFST = NULL;
						pFST = LLRP_FirstSeenTimestampUTC_construct();
						LLRP_FirstSeenTimestampUTC_setMicroseconds(pFST,
																   tag_info->FirstSeenTimestampUTC);
						LLRP_TagReportData_setFirstSeenTimestampUTC(pTRD, pFST);
					}

					if (info->report_spec->mask | ENABLE_LST) {
						LLRP_tSLastSeenTimestampUTC *pLST = NULL;
						pLST = LLRP_LastSeenTimestampUTC_construct();
						LLRP_LastSeenTimestampUTC_setMicroseconds(pLST,
																  tag_info->LastSeenTimestampUTC);
						LLRP_TagReportData_setLastSeenTimestampUTC(pTRD, pLST);
					}

					if (info->report_spec->mask | ENABLE_TSC) {
						LLRP_tSTagSeenCount *pTSC = NULL;
						pTSC = LLRP_TagSeenCount_construct();
						LLRP_TagSeenCount_setTagCount(pTSC, tag_info->TagSeenCount);
						LLRP_TagReportData_setTagSeenCount(pTRD, pTSC);
					}

					if (tag_info->PartData.nValue) {
						LLRP_tSCustomizedSelectSpecResult *pCSSR = NULL;
						LLRP_tSReadDataInfo *pRDI = NULL;
						data_param_t *data = NULL;
						llrp_u8v_t tmp;
						uint16_t pos = 0;

						pCSSR = LLRP_CustomizedSelectSpecResult_construct();
						LLRP_CustomizedSelectSpecResult_setResult(pCSSR, 0);

						pRDI = LLRP_ReadDataInfo_construct();

						tag_info->PartData.nValue -= 5;
						for (; tag_info->PartData.nValue - pos >= 4; pos += (data->len + 4)) {
							memset(&tmp, 0, sizeof(llrp_u8v_t));
							data = (data_param_t *) (tag_info->PartData.pValue + pos);
							tmp.nValue = data->len;
							tmp.pValue = malloc(tmp.nValue);
							memcpy(tmp.pValue, data->payload, tmp.nValue);

							if (tag_info->PartData.nValue < pos + data->len)
								break;

							switch (data->type_code) {
							  case TYPE_CID:
								  {
									  LLRP_tSCID *pCID = NULL;

									  pCID = LLRP_CID_construct();
									  LLRP_CID_setCIDData(pCID, tmp);
									  LLRP_ReadDataInfo_setCID(pRDI, pCID);
									  break;
								  }
							  case TYPE_FPDH:
								  {
									  LLRP_tSFPDH *pFPDH = NULL;

									  pFPDH = LLRP_FPDH_construct();
									  LLRP_FPDH_setFPDHData(pFPDH, tmp);
									  LLRP_ReadDataInfo_setFPDH(pRDI, pFPDH);
									  break;
								  }
							  case TYPE_SYXZ:
								  {
									  LLRP_tSSYXZ *pSYXZ = NULL;

									  pSYXZ = LLRP_SYXZ_construct();
									  LLRP_SYXZ_setSYXZData(pSYXZ, tmp);
									  LLRP_ReadDataInfo_setSYXZ(pRDI, pSYXZ);
									  break;
								  }
							  case TYPE_CCRQ:
								  {
									  LLRP_tSCCRQ *pCCRQ = NULL;

									  pCCRQ = LLRP_CCRQ_construct();
									  LLRP_CCRQ_setCCRQData(pCCRQ, tmp);
									  LLRP_ReadDataInfo_setCCRQ(pRDI, pCCRQ);
									  break;
								  }
							  case TYPE_CLLX:
								  {
									  LLRP_tSCLLX *pCLLX = NULL;

									  pCLLX = LLRP_CLLX_construct();
									  LLRP_CLLX_setCLLXData(pCLLX, tmp);
									  LLRP_ReadDataInfo_setCLLX(pRDI, pCLLX);
									  break;
								  }
							  case TYPE_PL:
								  {
									  LLRP_tSPL *pPL = NULL;

									  pPL = LLRP_PL_construct();
									  LLRP_PL_setPLData(pPL, tmp);
									  LLRP_ReadDataInfo_setPL(pRDI, pPL);
									  break;
								  }
							  case TYPE_GL:
								  {
									  LLRP_tSGL *pGL = NULL;

									  pGL = LLRP_GL_construct();
									  LLRP_GL_setGLData(pGL, tmp);
									  LLRP_ReadDataInfo_setGL(pRDI, pGL);
									  break;
								  }
							  case TYPE_HPZL:
								  {
									  LLRP_tSHPZL *pHPZL = NULL;

									  pHPZL = LLRP_HPZL_construct();
									  LLRP_HPZL_setHPZLData(pHPZL, tmp);
									  LLRP_ReadDataInfo_setHPZL(pRDI, pHPZL);
									  break;
								  }
							  case TYPE_HPHMXH:
								  {
									  LLRP_tSHPHMXH *pHPHMXH = NULL;

									  pHPHMXH = LLRP_HPHMXH_construct();
									  LLRP_HPHMXH_setHPHMXHData(pHPHMXH, tmp);
									  LLRP_ReadDataInfo_setHPHMXH(pRDI, pHPHMXH);
									  break;
								  }
							  case TYPE_JYYXQ:
								  {
									  LLRP_tSJYYXQ *pJYYXQ = NULL;

									  pJYYXQ = LLRP_JYYXQ_construct();
									  LLRP_JYYXQ_setJYYXQData(pJYYXQ, tmp);
									  LLRP_ReadDataInfo_setJYYXQ(pRDI, pJYYXQ);
									  break;
								  }
							  case TYPE_QZBFQ:
								  {
									  LLRP_tSQZBFQ *pQZBFQ = NULL;

									  pQZBFQ = LLRP_QZBFQ_construct();
									  LLRP_QZBFQ_setQZBFQData(pQZBFQ, tmp);
									  LLRP_ReadDataInfo_setQZBFQ(pRDI, pQZBFQ);
									  break;
								  }
							  case TYPE_CSYS:
								  {
									  LLRP_tSCSYS *pCSYS = NULL;

									  pCSYS = LLRP_CSYS_construct();
									  LLRP_CSYS_setCSYSData(pCSYS, tmp);
									  LLRP_ReadDataInfo_setCSYS(pRDI, pCSYS);
									  break;
								  }
							  case TYPE_ZKZL:
								  {
									  LLRP_tSZKZL *pZKZL = NULL;

									  pZKZL = LLRP_ZKZL_construct();
									  LLRP_ZKZL_setZKZLData(pZKZL, tmp);
									  LLRP_ReadDataInfo_setZKZL(pRDI, pZKZL);
									  break;
								  }
							  default:
								  printf("%s: has no this data type %u.\n", __func__,
										 data->type_code);
								  break;
							}
						}
						LLRP_CustomizedSelectSpecResult_setReadDataInfo(pCSSR, pRDI);
						LLRP_TagReportData_setSelectSpecResult(pTRD, (LLRP_tSParameter *) pCSSR);
						free(tag_info->PartData.pValue);
					}

					LLRP_TagSelectAccessReport_addTagReportData(pTSAR, pTRD);
				}
				//printf("curr_timestamp=%lld, LastSeenTimestampUTC=%lld., count=%u\n", curr_timestamp,
				//                                  tag_info->LastSeenTimestampUTC, tag_info->TagSeenCount);
				/* FIXME: maybe other time */
				if (curr_timestamp - tag_info->LastSeenTimestampUTC > 5000) {
					if (info->tag_list == tag_list) {
						info->tag_list = tag_list->next;
						tag_list_prev = info->tag_list;
						free(tag_list);
						tag_list = info->tag_list;
					} else {
						tag_list = tag_list->next;
						free(tag_list_prev->next);
						tag_list_prev->next = tag_list;
					}
				} else {
					tag_list_prev = tag_list;
					tag_list = tag_list->next;
				}
			}

			if (found) {
				lock_upper(&info->lock);
				upper_send_message(info, &pTSAR->hdr);
				unlock_upper(&info->lock);
				found = false;
			}

			LLRP_TagSelectAccessReport_destruct(pTSAR);
			pTSAR = NULL;
		}

		unlock_upper(&info->upload_lock);
	}
}

static void *upper_request_loop(void *data)
{
	upper_info_t *info = (upper_info_t *) data;
	LLRP_tSMessage *pRequest;

	while (true) {
		lock_upper(&info->req_lock);
		pthread_cond_wait(&info->req_cond, &info->req_lock);

		if (info->status <= UPPER_DISCONNECTED) {
			unlock_upper(&info->req_lock);
			return NULL;
		}

		if (info->request_list == NULL) {
			unlock_upper(&info->req_lock);
			continue;
		}

		pRequest = info->request_list;
		while (pRequest != NULL) {
			info->request_list = info->request_list->pQueueNext;
			pRequest->pQueueNext = NULL;
			upper_process_request(info, pRequest);
			pRequest = info->request_list;
		}
		unlock_upper(&info->req_lock);
	}
	return NULL;
}

void *upper_read_loop(void *data)
{
	upper_info_t *info = (upper_info_t *) data;
	LLRP_tSConnection *pConn = info->pConn;
	LLRP_tSMessage *pMessage = NULL;
	LLRP_tSErrorDetails *pError = &pConn->Recv.ErrorDetails;

	while (true) {
		/* Need enqueue pMessage into queue */
		pMessage = LLRP_Conn_recvMessage(pConn, 10000);
		if (pMessage == NULL) {
			if (pError->eResultCode == LLRP_RC_RecvIOError ||
				pError->eResultCode == LLRP_RC_RecvEOF) {
				info->status = UPPER_DISCONNECTED;
				printf("%s: error code:%d, error message:%s.\n",
					   __func__, pError->eResultCode, pError->pWhatStr);
				break;
			} else {
				printf("%s: error code:%d, error message:%s.\n",
					   __func__, pError->eResultCode, pError->pWhatStr);
				continue;
			}
		}

		/*
		 * Print the XML text for the outbound message if
		 * verbosity is 1 or higher.
		 */
		if (info->verbose > 0) {
			printf("\n===================================\n");
			printf("INFO: Recving:\n");
			upper_print_XML_message(pMessage);
		}

		if (strstr(pMessage->elementHdr.pType->pName, "Ack") != NULL) {
			upper_signal_response(info, pMessage);
		} else {
			upper_signal_request(info, pMessage);
		}
	}

	//info->status = UPPER_STOP;
	lock_upper(&info->disconnect_lock);
	pthread_cond_broadcast(&info->disconnect_cond);
	unlock_upper(&info->disconnect_lock);

	printf("%s: exit\n", __func__);

	return NULL;
}

void upper_signal_upload(upper_info_t * info)
{
	if (info->status == UPPER_READY) {
		lock_upper(&info->upload_lock);
		pthread_cond_broadcast(&info->upload_cond);
		unlock_upper(&info->upload_lock);
	}
}

void stop_upper(upper_info_t * info)
{
	if (info == NULL)
		return;

	info->status = UPPER_STOP;

	lock_upper(&info->disconnect_lock);
	pthread_cond_wait(&info->disconnect_cond, &info->disconnect_lock);
	unlock_upper(&info->disconnect_lock);

	if (info->sock > 0)
		close(info->sock);
	LLRP_Conn_closeConnectionToUpper(info->pConn);
}

int start_upper(upper_info_t * info)
{
	int ret = NO_ERROR;
	pthread_attr_t attr;

	while (true) {
		printf("[UPPER] Start the server.....\n");
		info->sock = LLRP_Conn_startServerForUpper(info->pConn);
		if (info->sock < 0) {
			printf("%s: start server failed, error:%s, ret = %d.\n", __func__,
				   info->pConn->pConnectErrorStr, info->sock);
			goto retry;
		}

		info->status = UPPER_CONNECTED;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		ret = pthread_create(&info->read_thread, &attr, upper_read_loop, (void *)info);
		if (ret < 0) {
			printf("%s: create read thread failed.\n", __func__);
			stop_upper(info);
			ret = -FAILED;
		}

		ret = pthread_create(&info->request_thread, &attr, upper_request_loop, (void *)info);
		if (ret < 0) {
			printf("%s: create request thread failed.\n", __func__);
			stop_upper(info);
			ret = -FAILED;
		}

		ret = pthread_create(&info->upload_thread, &attr, upper_upload_loop, (void *)info);
		if (ret < 0) {
			printf("%s: create request thread failed.\n", __func__);
			stop_upper(info);
			ret = -FAILED;
		}

		ret = upper_notify_connected_event(info);
		if (ret < 0)
			goto retry;

		info->retry = 0;
		info->status = UPPER_READY;
		printf("Start upper module, ret=%d\n", ret);

		upper_signal_upload(info);

		lock_upper(&info->disconnect_lock);
		pthread_cond_wait(&info->disconnect_cond, &info->disconnect_lock);
		unlock_upper(&info->disconnect_lock);
	  retry:
		info->status = UPPER_STOP;

		if (info->retry++ == 5)
			break;

		/* TODO: check if thread alive */
		lock_upper(&info->req_lock);
		pthread_cond_broadcast(&info->req_cond);
		unlock_upper(&info->req_lock);

		lock_upper(&info->upload_lock);
		pthread_cond_broadcast(&info->upload_cond);
		unlock_upper(&info->upload_lock);

		if (info->sock > 0) {
			shutdown(info->sock, SHUT_RDWR);
			close(info->sock);
			info->sock = -1;
			shutdown(info->pConn->fd, SHUT_RDWR);
			close(info->pConn->fd);
			info->pConn->fd = -1;
		}

		sleep(2);				/* workaround to release the link */
	}

	if (ret < 0)
		stop_upper(info);

	return ret;
}

int alloc_upper(upper_info_t ** info, struct xmlConfigInfo *pXmlConfig)
{
	int ret = NO_ERROR;

	*info = (upper_info_t *) malloc(sizeof(upper_info_t));
	if (*info == NULL) {
		printf("%s: Alloc memory for upper info failed. errno=%d.\n", __func__, errno);
		return -ENOMEM;
	}

	memset(*info, 0, sizeof(upper_info_t));
	(*info)->sock = -1;
	(*info)->status = UPPER_STOP;
	(*info)->pXmlConfig = pXmlConfig;

	pthread_mutex_init(&(*info)->lock, NULL);
	pthread_cond_init(&(*info)->cond, NULL);
	pthread_mutex_init(&(*info)->req_lock, NULL);
	pthread_cond_init(&(*info)->req_cond, NULL);
	pthread_mutex_init(&(*info)->upload_lock, NULL);
	pthread_cond_init(&(*info)->upload_cond, NULL);

	(*info)->pTypeRegistry = LLRP_getTheTypeRegistry();
	if ((*info)->pTypeRegistry == NULL) {
		printf("%s: ERROR: getTheTypeRegistry failed\n", __func__);
		free(*info);
		return -FAILED;
	}

	(*info)->verbose = 1;
	(*info)->next_msg_id = 1;
	(*info)->tag_list = NULL;

	(*info)->pConn = LLRP_Conn_construct((*info)->pTypeRegistry, 32u * 1024u);
	if ((*info)->pConn == NULL) {
		printf("%s: ERROR: LLRP_Conn_construct failed.\n", __func__);
		LLRP_TypeRegistry_destruct((*info)->pTypeRegistry);
		free(*info);
		return -FAILED;
	}

	return ret;
}

void release_upper(upper_info_t ** info)
{
	if (info == NULL || *info == NULL) {
		printf("%s: failed, info ptr is null.\n", __func__);
		return;
	}

	pthread_mutex_destroy(&(*info)->lock);
	pthread_cond_destroy(&(*info)->cond);
	pthread_mutex_destroy(&(*info)->req_lock);
	pthread_cond_destroy(&(*info)->req_cond);
	pthread_mutex_destroy(&(*info)->upload_lock);
	pthread_cond_destroy(&(*info)->upload_cond);

	LLRP_TypeRegistry_destruct((*info)->pTypeRegistry);
	LLRP_Conn_destruct((*info)->pConn);

	free(*info);
	*info = NULL;
}
