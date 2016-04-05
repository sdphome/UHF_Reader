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
#include <ltkc.h>
#include <upper.h>

static void upper_print_XML_message(LLRP_tSMessage *pMessage)
{
    char aBuf[100*1024];

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

static void inline lock_upper(pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
}

static void inline unlock_upper(pthread_mutex_t *lock)
{
	pthread_mutex_unlock(lock);
}

static void upper_signal_response(upper_info_t *info, LLRP_tSMessage *pResponse)
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

static void upper_signal_request(upper_info_t *info, LLRP_tSMessage *pRequest)
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

static LLRP_tSMessage *upper_wait_response(upper_info_t *info, LLRP_tSMessage *pSendMessage)
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

	if(0 > pConn->fd) {
		LLRP_Error_resultCodeAndWhatStr(pError,
				LLRP_RC_MiscError, "not connected");
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
			LLRP_Error_resultCodeAndWhatStr(pError,
					LLRP_RC_RecvTimeout, "wait ack timeout");
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

			if(pResponse->MessageID != ResponseMessageID) {
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

static int upper_send_message(upper_info_t *info, LLRP_tSMessage *pSendMsg)
{
	int ret = NO_ERROR;
	LLRP_tSConnection *pConn = info->pConn;

    /*
     * Print the XML text for the outbound message if
     * verbosity is 1 or higher.
     */
	if (info->verbose > 0) {
		printf("\n===================================\n");
		printf("INFO: Sending:\n");
		upper_print_XML_message(pSendMsg);
	}

    /*
     * If LLRP_Conn_sendMessage() returns other than LLRP_RC_OK
     * then there was an error. In that case we try to print
     * the error details.
     */
    if(LLRP_RC_OK != LLRP_Conn_sendMessage(pConn, pSendMsg)) {
        const LLRP_tSErrorDetails *pError = LLRP_Conn_getSendError(pConn);

        printf("ERROR: %s sendMessage failed, %s\n",
            pSendMsg->elementHdr.pType->pName,
            pError->pWhatStr ? pError->pWhatStr : "no reason given");

        if(pError->pRefType != NULL) {
            printf("ERROR: ... reference type %s\n",
                pError->pRefType->pName);
        }

        if(pError->pRefField != NULL) {
            printf("ERROR: ... reference field %s\n",
                pError->pRefField->pName);
        }

        ret = -FAILED;
    }

	return ret;
}

static int upper_check_llrp_status(LLRP_tSStatus *pLLRPStatus, char *pWhatStr)
{
	if(NULL == pLLRPStatus) {
		printf("ERROR: %s missing LLRP status\n", pWhatStr);
		return -FAILED;
	}

	if (pLLRPStatus->eStatusCode != LLRP_StatusCode_M_Success) {
		if (pLLRPStatus->ErrorDescription.nValue == 0) {
			printf("ERROR: %s failed, no error description given\n", pWhatStr);
		} else {
			printf("ERROR: %s failed, %.*s\n",
					pWhatStr,
					pLLRPStatus->ErrorDescription.nValue,
					pLLRPStatus->ErrorDescription.pValue);
		}
	}

	return -pLLRPStatus->eStatusCode;
}

int upper_notify_connected_event(upper_info_t *info)
{
	int ret = NO_ERROR;
	struct timeval now;
	LLRP_tSDeviceEventNotification *pThis;
	LLRP_tSUTCTimestamp *pTimestamp;

	pThis = LLRP_DeviceEventNotification_construct();
	pTimestamp = LLRP_UTCTimestamp_construct();

	gettimeofday(&now, NULL);
	LLRP_UTCTimestamp_setMicroseconds(pTimestamp,
		(((uint64_t)now.tv_sec) * 1000 + ((uint64_t)now.tv_usec) / 1000));
	LLRP_DeviceEventNotification_setUTCTimestamp(pThis, pTimestamp);

	lock_upper(&info->lock);

	if(LLRP_RC_OK != upper_send_message(info, &pThis->hdr)) {
		ret = -FAILED;
	}

	unlock_upper(&info->lock);

	LLRP_UTCTimestamp_destruct(pTimestamp);
	LLRP_DeviceEventNotification_destruct(pThis);

	return ret;
}

static void upper_process_request(upper_info_t *info, LLRP_tSMessage *pRequest)
{
    printf("%s: id[%d] %s +\n", __func__, pRequest->MessageID, pRequest->elementHdr.pType->pName);
    printf("%s: id[%d] %s -\n", __func__, pRequest->MessageID, pRequest->elementHdr.pType->pName);
}

static void *upper_request_loop(void *data)
{
    upper_info_t *info = (upper_info_t *)data;
	LLRP_tSMessage *pRequest;

    while (true) {
        lock_upper(&info->req_lock);
        pthread_cond_wait(&info->req_cond, &info->req_lock);

        if (info->request_list == NULL) {
            unlock_upper(&info->req_lock);
            continue;
        }

        pRequest = &info->request_list;
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
	upper_info_t *info = (upper_info_t *)data;
	LLRP_tSConnection *pConn = info->pConn;
	LLRP_tSMessage *pMessage = NULL;
	LLRP_tSErrorDetails *pError = &pConn->Recv.ErrorDetails;

	while (true) {
        /* Need enqueue pMessage into queue */
		pMessage = LLRP_Conn_recvMessage(pConn, 1000);
		if (pMessage == NULL) {
			if (pError->eResultCode == LLRP_RC_RecvIOError) {
				printf("%s: error code:%d, error message:%s.\n",
					__func__, pError->eResultCode, pError->pWhatStr);
				break;
			} else
				continue;
		}

        if (strstr(pMessage->elementHdr.pType->pName, "Ack") != NULL) {
            upper_signal_response(info, pMessage);
        }
    }

	/* TODO: signal or release resource? */

	return NULL;
}

void stop_upper(upper_info_t *info)
{
	LLRP_Conn_closeConnectionToUpper(info->pConn);
	close(info->sock);
}

int start_upper(upper_info_t *info)
{
	int ret = NO_ERROR;
	pthread_attr_t attr;

	info->sock = LLRP_Conn_startServerForUpper(info->pConn);
	if (info->sock < 0) {
		printf("%s: start server failed.\n", __func__);
		return info->sock;
	}

	pthread_attr_init (&attr);
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

	printf("Start upper module, ret=%d\n", ret);

    if (ret < 0)
        stop_upper(info);

	return ret;
}

int alloc_upper(upper_info_t **info)
{
	int ret = NO_ERROR;

	*info = (upper_info_t *)malloc(sizeof(upper_info_t));
	if (*info == NULL) {
		printf("%s: Alloc memory for upper info failed. errno=%d.\n", __func__, errno);
		return -ENOMEM;
	}

    memset(*info, 0, sizeof(upper_info_t));
	(*info)->sock = -1;

    pthread_mutex_init(&(*info)->lock, NULL);
    pthread_cond_init(&(*info)->cond, NULL);
    pthread_mutex_init(&(*info)->req_lock, NULL);
    pthread_cond_init(&(*info)->req_cond, NULL);

    (*info)->pTypeRegistry = LLRP_getTheTypeRegistry();
    if((*info)->pTypeRegistry == NULL) {
        printf("%s: ERROR: getTheTypeRegistry failed\n", __func__);
		free(*info);
        return -FAILED;
    }

	(*info)->pConn = LLRP_Conn_construct((*info)->pTypeRegistry, 32u*1024u);
	if ((*info)->pConn == NULL) {
		printf("%s: ERROR: LLRP_Conn_construct failed.\n", __func__);
		LLRP_TypeRegistry_destruct((*info)->pTypeRegistry);
		free(*info);
		return -FAILED;
	}

	return ret;
}

void release_upper(upper_info_t *info)
{
	if (info == NULL) {
		printf("%s: failed, info ptr is null.\n", __func__);
		return;
	}

    pthread_mutex_destroy(&info->lock);
    pthread_cond_destroy(&info->cond);
    pthread_mutex_destroy(&info->req_lock);
    pthread_cond_destroy(&info->req_cond);

	LLRP_TypeRegistry_destruct(info->pTypeRegistry);
	LLRP_Conn_destruct(info->pConn);

	free(info);
	info = NULL;
}

void test_upper()
{
	int ret = NO_ERROR;
	upper_info_t *info;

	ret = alloc_upper(&info);
	if (ret != NO_ERROR)
		return;

	ret = start_upper(info);
	if (ret != NO_ERROR) {
		release_upper(info);
		return;
	}

    ret = upper_notify_connected_event(info);
    if (ret != NO_ERROR) {
        printf("%s: send device event notification failed.\n", __func__);
		goto failed;
    }

failed:
	stop_upper(info);
	release_upper(info);
}

int upper_main(int argc, char** argv)
{
	test_upper();
	return 0;
}
