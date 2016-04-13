
/***************************************************************************
*
*   Author: Shao Depeng <dp.shao@gmail.com>
*   Copyright 2016 Golden Sky Technology CO.,LTD
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
****************************************************************************/
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
//#include <upper.h>
//#include <security.h>
//#include <radio.h>
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
	const LLRP_tSTypeDescriptor *pResponseType;
	LLRP_tSConnection *pConn = info->pConn;
	const LLRP_tSTypeDescriptor *pErrorMsgType;
	LLRP_tSErrorDetails *pError = &pConn->Recv.ErrorDetails;
	llrp_u32_t ResponseMessageID = pSendMessage->MessageID + 1;

	if (0 > pConn->fd) {
		LLRP_Error_resultCodeAndWhatStr(pError, LLRP_RC_MiscError, "not connected");
		return NULL;
	}

	pResponseType = pSendMessage->elementHdr.pType->pResponseType;
	pErrorMsgType = LLRP_TypeRegistry_lookupMessage(pConn->pTypeRegistry, 303u);

	gettimeofday(&now, NULL);
	outtime.tv_sec = now.tv_sec + UPPER_TIMEOUT;
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
			if (NULL != pResponseType) {
				if (pResponse->elementHdr.pType != pResponseType &&
					pResponse->elementHdr.pType != pErrorMsgType) {
					pPrev = pResponse;
					continue;
				}
			}

			if (pResponse->MessageID != ResponseMessageID) {
				pPrev = pResponse;
				continue;
			}

			responseReceived = 1;
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

	if (pConn == NULL) {
		printf("%s: pConn is null.\n", __func__);
		return -1;
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
	pSendMsg->DeviceSN = 0x1234;
	pSendMsg->Version = 1;
	//pSendMsg->MessageID = info->next_msg_id ++;

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

static int upper_check_llrp_status(LLRP_tSStatus * pLLRPStatus, char *pWhatStr)
{
	if (NULL == pLLRPStatus) {
		printf("ERROR: %s missing LLRP status\n", pWhatStr);
		return -FAILED;
	}

	if (pLLRPStatus->eStatusCode != LLRP_StatusCode_M_Success) {
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

	LLRP_ConnectionAttemptEvent_setConnectionStatus(pCAE, LLRP_ConnectionStatus_Success);
	LLRP_DeviceEventNotification_setConnectionAttemptEvent(pThis, pCAE);

	lock_upper(&info->lock);

	if (LLRP_RC_OK != upper_send_message(info, &pThis->hdr)) {
		ret = -FAILED;
	}

	unlock_upper(&info->lock);

	LLRP_DeviceEventNotification_destruct(pThis);

	info->status = 1;
	return ret;
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

static LLRP_tSStatus * upper_setup_status(LLRP_tEStatusCode status)
{
	LLRP_tSStatus *pStatus;
	llrp_utf8v_t description;

	memset(&description, 0, sizeof(llrp_utf8v_t));
	pStatus = LLRP_Status_construct();

	LLRP_Status_setStatusCode(pStatus, status);
	LLRP_Status_setErrorDescription(pStatus, description);

	return pStatus;
}

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

	/* don't have ack */
	lock_upper(&info->lock);
	upper_send_message(info, &pEA->hdr);
	unlock_upper(&info->lock);

out:
	if (pEA != NULL) LLRP_ErrorAck_destruct(pEA);
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
	if (pDis != NULL) LLRP_Disconnect_destruct(pDis);
	if (pAck != NULL) LLRP_DisconnectAck_destruct(pAck);

	return ret;
}

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

	lock_upper(&info->disconnect_lock);
	pthread_cond_broadcast(&info->disconnect_cond);
	unlock_upper(&info->disconnect_lock);

out:
	if (pDis != NULL) LLRP_Disconnect_destruct(pDis);
	if (pAck != NULL) LLRP_DisconnectAck_destruct(pAck);

	return ret;
}

static int upper_request_Keepalive(upper_info_t * info)
{
	int ret = NO_ERROR;
	LLRP_tSKeepalive *pKA = NULL;
	LLRP_tSKeepaliveAck *pAck = NULL;

	pKA = LLRP_Keepalive_construct();
	pKA->hdr.MessageID = info->next_msg_id++;

	lock_upper(&info->lock);
	ret = upper_send_message(info, &pKA->hdr);

	if (ret == NO_ERROR)
		pAck = (LLRP_tSKeepaliveAck *) upper_wait_response(info, &pKA->hdr);

	unlock_upper(&info->lock);

	LLRP_Keepalive_destruct(pKA);
	if (pAck != NULL)
		LLRP_Element_destruct(&pAck->hdr.elementHdr);

	return ret;
}

int upper_request_TagSelectAccessReport(upper_info_t * info, llrp_u64_t tid,
										llrp_u8_t anten_no, llrp_u64_t timestamp)
{
	LLRP_tSTagSelectAccessReport *pTSAR;
	LLRP_tSTagReportData *pTRD;
	llrp_u8v_t Tid;

	if (info == NULL) {
		printf("info is null.\n");
		return 0;
	} else
		printf("info ptr = %p.\n", info);

	if (info->status != 1) {
		printf("%s: upper hasn't ready.\n", __func__);
		return 0;
	}
	pTSAR = LLRP_TagSelectAccessReport_construct();
	pTRD = LLRP_TagReportData_construct();

	pTSAR->hdr.MessageID = info->next_msg_id++;

	Tid.nValue = 8;
	Tid.pValue = (llrp_u8_t *) malloc(Tid.nValue);
	//upper_hton_64(Tid.pValue, tid);
	memcpy(Tid.pValue, &tid, 8);

	LLRP_TagReportData_setTID(pTRD, Tid);
	LLRP_TagSelectAccessReport_addTagReportData(pTSAR, pTRD);

	lock_upper(&info->lock);

	upper_send_message(info, &pTSAR->hdr);

	unlock_upper(&info->lock);
	LLRP_TagSelectAccessReport_destruct(pTSAR);
	return 0;
}

// 600
static int upper_process_DeviceBinding(upper_info_t * info, LLRP_tSDeviceBinding * pDB)
{
	return 0;
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
	Error.nValue = 0;
	LLRP_Status_setStatusCode(pStatus, LLRP_StatusCode_M_Success);
	LLRP_Status_setErrorDescription(pStatus, Error);
	LLRP_DeviceCertificateConfigAck_setStatus(pDCC_Ack, pStatus);
	pDCC_Ack->hdr.MessageID = pDCC->hdr.MessageID;
	pDCC_Ack->hdr.Version = pDCC->hdr.Version;

	lock_upper(&info->lock);

	ret = upper_send_message(info, &pDCC_Ack->hdr);

	unlock_upper(&info->lock);

	pCer = LLRP_DeviceCertificateConfig_getCertificateData(pDCC);
	pUser = LLRP_DeviceCertificateConfig_getUserData(pDCC);

	ret += upper_write_to_file(info->active_cer_path, &pCer);
	ret += upper_write_to_file(info->user_info_path, &pUser);

	LLRP_DeviceCertificateConfigAck_destruct(pDCC_Ack);
	LLRP_DeviceCertificateConfig_destruct(pDCC);

	return ret;
}

// 662
static int upper_process_SetDeviceConfig(upper_info_t * info, LLRP_tSSetDeviceConfig *pThis)
{
	int ret = NO_ERROR;
	LLRP_tSSetDeviceConfigAck *pSDC_Ack = NULL;
	LLRP_tSStatus *pStatus;
	LLRP_tEStatusCode status = LLRP_StatusCode_M_Success;

	if (pThis->pCommunicationConfiguration != NULL) {
		LLRP_tSCommunicationConfiguration * pCC = NULL;
		LLRP_tSCommLinkConfiguration *pCLC = NULL;
		LLRP_tSNTPConfiguration * pNTPC = NULL;

		pCC = LLRP_SetDeviceConfig_getCommunicationConfiguration(pThis);

		for (pCLC = LLRP_CommunicationConfiguration_beginCommLinkConfiguration(pCC);
			 pCLC != NULL; 
			 pCLC = LLRP_CommunicationConfiguration_nextCommLinkConfiguration(pCLC)) {
			/* Just support TCP now */
			if (LLRP_CommLinkConfiguration_getLinkType(pCLC) == LLRP_LinkType_TCP) {
				LLRP_tSKeepaliveSpec * pKS = NULL;
				LLRP_tSTcpLinkConfiguration * pTLC = NULL;
				pKS = LLRP_CommLinkConfiguration_getKeepaliveSpec(pCLC);
				if (LLRP_KeepaliveSpec_getKeepaliveTrigger(pKS))
					info->heartbeats_periodic = LLRP_KeepaliveSpec_getPeriodicTriggerValue(pKS);
				else
					info->heartbeats_periodic = 0;

				pTLC = LLRP_CommLinkConfiguration_getTcpLinkConfiguration(pCLC);
				if (pTLC != NULL) {
					/* Just support Server mode now */
					if (LLRP_TcpLinkConfiguration_getCommMode(pTLC) == LLRP_CommMode_ServerMode) {
						LLRP_tSServerModeConfiguration * pSMC = NULL;
						pSMC = LLRP_TcpLinkConfiguration_getServerModeConfiguration(pTLC);
						if (pSMC != NULL)
							info->port = LLRP_ServerModeConfiguration_getPort(pSMC);
					}
				}
				break;
			}

			pNTPC = LLRP_CommunicationConfiguration_getNTPConfiguration(pCC);
			if (pNTPC != NULL) {
				/* TODO: setup ntp */
			}
		}
	}

	pSDC_Ack = LLRP_SetDeviceConfigAck_construct();
	pStatus = upper_setup_status(status);
	if (pSDC_Ack == NULL || pStatus == NULL)
		goto out;

	LLRP_SetDeviceConfigAck_setStatus(pSDC_Ack, pStatus);

out:
	LLRP_SetDeviceConfig_destruct(pThis);
	LLRP_SetDeviceConfigAck_destruct(pSDC_Ack);

	return ret;
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
			break;
	  case 402:				//DeleteSelectSpec
			break;
	  case 404:				//StartSelectSpec
			break;
	  case 406:				//StopSelectSpec
			break;
	  case 408:				//EnableSelectSpec
			break;
	  case 410:				//DisableSelectSpecAck
			break;
	  case 412:				//GetSelectSpec
			break;
	  case 450:				//AddAccessSpec
			break;
	  case 452:				//DeleteAccessSpec
			break;
	  case 454:				//EnableAccessSpec
			break;
	  case 456:				//DisableAccessSpec
			break;
	  case 458:				//GetAccessSpec
			break;
	  case 600:				//DeviceBinding
			upper_process_DeviceBinding(info, (LLRP_tSDeviceBinding *) pRequest);
			break;
	  case 602:				//DeviceCertificateConfig
			upper_process_DeviceCertificateConfig(info, (LLRP_tSDeviceCertificateConfig *) pRequest);
			break;
	  case 620:				//UploadTagLog
			break;
	  case 622:				//ClearLog
			break;
	  case 640:				//UploadDeviceLog
			break;
	  case 642:				//ClearDeviceLog
			break;
	  case 660:				//GetDeviceConfig
			break;
	  case 662:				//SetDeviceConfig
			break;
	  case 700:				//GetVersion
			break;
	  case 702:				//SetVersion
			break;
	  case 704:				//ActiveVersion
			break;
	  case 706:				//UnAciveVersion
			break;
	  case 760:				//ResetDevice
			break;
	  default:
		  printf("hasn't support this type.\n");
		  break;
	}

	printf("%s: type = %d -\n", __func__, type);
}

int upper_send_heartbeat(upper_info_t * info)
{
	return upper_request_Keepalive(info);
}

static void *upper_request_loop(void *data)
{
	upper_info_t *info = (upper_info_t *) data;
	LLRP_tSMessage *pRequest;

	while (true) {
		lock_upper(&info->req_lock);
		pthread_cond_wait(&info->req_cond, &info->req_lock);

		if (info->status == 0) {
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
				printf("%s: error code:%d, error message:%s.\n",
					   __func__, pError->eResultCode, pError->pWhatStr);
				break;
			} else {
				continue;
			}
		}

		printf("%s: pType->pName=%s\n", __func__, pMessage->elementHdr.pType->pName);
		upper_print_XML_message(pMessage);

		if (strstr(pMessage->elementHdr.pType->pName, "Ack") != NULL) {
			upper_signal_response(info, pMessage);
		} else {
			upper_signal_request(info, pMessage);
		}
	}

	//info->status = 0;
	lock_upper(&info->disconnect_lock);
	pthread_cond_broadcast(&info->disconnect_cond);
	unlock_upper(&info->disconnect_lock);

	printf("%s: exit\n", __func__);

	return NULL;
}

void stop_upper(upper_info_t * info)
{
	void *ret;
	if (info == NULL)
		return;

	pthread_cancel(info->read_thread);
	pthread_cancel(info->request_thread);
	pthread_join(info->read_thread, &ret);
	pthread_join(info->request_thread, &ret);

	LLRP_Conn_closeConnectionToUpper(info->pConn);
	close(info->sock);
}

int start_upper(upper_info_t * info)
{
	int ret = NO_ERROR;
	pthread_attr_t attr;
	void *status;

	while (true) {
		//if (info->pConn == NULL)
		//  printf("%s: pConn is null.\n", __func__);
		info->sock = LLRP_Conn_startServerForUpper(info->pConn);
		if (info->sock < 0) {
			printf("%s: start server failed, error:%s.\n", __func__, info->pConn->pConnectErrorStr);
			return info->sock;
		}

		pthread_attr_init(&attr);
		//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

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

		ret = upper_notify_connected_event(info);
		if (ret < 0)
			goto retry;

		info->status = 1;
		printf("Start upper module, ret=%d\n", ret);

		lock_upper(&info->disconnect_lock);
		pthread_cond_wait(&info->disconnect_cond, &info->disconnect_lock);
		unlock_upper(&info->disconnect_lock);
	  retry:
		info->status = 0;

		lock_upper(&info->req_lock);
		pthread_cond_broadcast(&info->req_cond);
		unlock_upper(&info->req_lock);

		pthread_join(info->read_thread, &status);
		pthread_join(info->request_thread, &status);
		stop_upper(info);
		sleep(2);				/* workaround to release the link */
	}

	if (ret < 0)
		stop_upper(info);

	return ret;
}

int alloc_upper(upper_info_t ** info)
{
	int ret = NO_ERROR;

	*info = (upper_info_t *) malloc(sizeof(upper_info_t));
	if (*info == NULL) {
		printf("%s: Alloc memory for upper info failed. errno=%d.\n", __func__, errno);
		return -ENOMEM;
	}

	memset(*info, 0, sizeof(upper_info_t));
	(*info)->sock = -1;
	(*info)->status = 0;

	pthread_mutex_init(&(*info)->lock, NULL);
	pthread_cond_init(&(*info)->cond, NULL);
	pthread_mutex_init(&(*info)->req_lock, NULL);
	pthread_cond_init(&(*info)->req_cond, NULL);

	(*info)->pTypeRegistry = LLRP_getTheTypeRegistry();
	if ((*info)->pTypeRegistry == NULL) {
		printf("%s: ERROR: getTheTypeRegistry failed\n", __func__);
		free(*info);
		return -FAILED;
	}

	(*info)->verbose = 1;
	(*info)->next_msg_id = 1;
	(*info)->heartbeats_periodic = UPPER_DEFAULT_HEARTBEATS_PERIODIC;

	memcpy((*info)->active_cer_path, ACTIVE_CER_PATH, sizeof(ACTIVE_CER_PATH));
	memcpy((*info)->user_info_path, USER_INFO_PATH, sizeof(USER_INFO_PATH));

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

	LLRP_TypeRegistry_destruct((*info)->pTypeRegistry);
	LLRP_Conn_destruct((*info)->pConn);

	free(*info);
	*info = NULL;
}

void test_upper()
{
	int ret = NO_ERROR;
	upper_info_t *info;
	void *status;

	ret = alloc_upper(&info);
	if (ret != NO_ERROR)
		return;

	ret = start_upper(info);
	if (ret != NO_ERROR) {
		release_upper(&info);
		return;
	}

	ret = upper_notify_connected_event(info);
	if (ret != NO_ERROR) {
		printf("%s: send device event notification failed.\n", __func__);
		goto failed;
	}

	printf("%s: wait ###################\n", __func__);

	pthread_join(info->read_thread, &status);
	printf("%s: wait 1 ####################\n", __func__);
	pthread_join(info->request_thread, &status);
	printf("%s: wait 2\n", __func__);

  failed:
	printf("%s: end\n", __func__);
	stop_upper(info);
	release_upper(&info);
}

int upper_main(int argc, char **argv)
{
	test_upper();
	return 0;
}
