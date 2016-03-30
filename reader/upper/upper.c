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

#include "upper.h"

void upper_print_XML_message(LLRP_tSMessage *pMessage)
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

int upper_send_message(upper_info_t *info, LLRP_tSMessage *pSendMsg)
{
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

        return -FAILED;
    }

	return NO_ERROR;
}

int upper_send_connected_notification(upper_info_t *info)
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

int main(int argc, char** argv)
{
	test_upper();
	return 0;
}
