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

static LLRP_tSMessage *upper_wait_response(upper_info_t *info, LLRP_tSMessage *pSendMessage)
{
	int responseReceived = 0;
	struct timeval now;
	struct timespec outtime;
	LLRP_tResultCode lrc;
	LLRP_tSMessage *pMessage;
	LLRP_tSMessage **ppMessage;
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

		for (ppMessage = &pConn->pInputQueue; NULL != (pMessage = *ppMessage);
			ppMessage = &pMessage->pQueueNext) {
			if(NULL != pResponseType) {
				if(pMessage->elementHdr.pType != pResponseType &&
					pMessage->elementHdr.pType != pErrorMsgType) {
					continue;
				}
			}

			if(0 != ResponseMessageID) {
				if(pMessage->MessageID != ResponseMessageID)
					continue;
			}

			responseReceived = 1;
			break;
		}

		if(NULL != pMessage && responseReceived) {
			*ppMessage = pMessage->pQueueNext;
			pMessage->pQueueNext = NULL;
			return pMessage;
		}
	}

	return NULL;
}

static int upper_send_message(upper_info_t *info, LLRP_tSMessage *pSendMsg)
{
	int ret = NO_ERROR;
	LLRP_tSConnection *pConn = info->pConn;

	lock_upper(&info->wlock);

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

	unlock_upper(&info->wlock);

	return ret;
}

int upper_notify_connected_event(upper_info_t *info)
{
	int ret = NO_ERROR;
	LLRP_tSDeviceEventNotification *pThis;

	pThis = LLRP_DeviceEventNotification_construct();

	if(LLRP_RC_OK != upper_send_message(info, &pThis->hdr)) {
		ret = -FAILED;
	}

	LLRP_DeviceEventNotification_destruct(pThis);

	return ret;
}

void *upper_process_loop(void *data)
{

}

void *upper_read_loop(void *data)
{
	fd_set fds;
	int maxfdp;
	int ret = NO_ERROR;
	upper_info_t *info = (upper_info_t *)data;
	LLRP_tSConnection *pConn = info->pConn;
	LLRP_tSMessage *pMessage = NULL;

	while (true) {
		FD_ZERO(&fds);
		FD_SET(pConn->fd, &fds);

		maxfdp = pConn->fd + 1;

		ret = select(maxfdp, &fds, NULL, NULL, NULL);
		if (ret <= 0) {
			printf("%s: select failed, ret=%d.\n", __func__, ret);
			return NULL;
		} else if (FD_ISSET(pConn->fd, &fds)) {
			pMessage = LLRP_Conn_recvMessage(pConn, -1);
			if (pMessage == NULL) {
				LLRP_tSErrorDetails *pError = &pConn->Recv.ErrorDetails;
				printf("%s: error code:%d, error message:%s.\n",
						__func__, pError->eResultCode, pError->pWhatStr);
				continue;
			}


		}

	}

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

	printf("Start upper module, ret=%d\n", ret);

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

	(*info)->sock = -1;

    pthread_mutex_init(&(*info)->lock, NULL);
    pthread_mutex_init(&(*info)->wlock, NULL);
    pthread_cond_init(&(*info)->cond, NULL);

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
    pthread_mutex_destroy(&info->wlock);
    pthread_cond_destroy(&info->cond);

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

    ret = upper_send_connected_notification(info);
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
