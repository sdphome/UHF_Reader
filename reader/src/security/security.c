#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/select.h>
#include <errno.h>
#include <pthread.h>

#include "security.h"

static inline int security_open(char *dev)
{
	return open(dev, O_RDWR);
}

static inline void security_close(int fd)
{
	close(fd);
}

uint8_t security_crc(security_pack_hdr *hdr, uint8_t *buf)
{
	int i = 0;
	uint8_t crc = 0;
	uint8_t *tmp = (uint8_t *)hdr;

	for (i = 0; i < SECURITY_PACK_HDR_SIZE; i++) {
		crc ^= *(tmp + i);
	}

	for (i = 0; i < hdr->len -1; i ++) {
		crc ^= *(buf + i);
	}

	return crc;
}

void security_print_result(security_package_t *result)
{
	int i;
	printf("===============SECURITY================\n");
	printf("hdr:%x, type:%x, version:%x, cmd:%x, len:%x, crc:%x\n", result->hdr.hdr,
			result->hdr.type, result->hdr.version, result->hdr.cmd, result->hdr.len, result->crc);
	printf("payload: ");
	for (i = 0; i < result->hdr.len; i ++) {
		printf("%3x", result->payload[i]);
	}
	printf("\n===============SECURITY================\n");
}

void inline lock_security(pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
}

void inline unlock_security(pthread_mutex_t *lock)
{
	pthread_mutex_unlock(lock);
}

int security_wait_result(security_info_t *info, uint8_t type, uint8_t cmd, security_package_t *result)
{
	int ret = NO_ERROR;
	int resultReceived = 0;
	struct timeval now;
	struct timespec outtime;

	gettimeofday(&now, NULL);
	outtime.tv_sec = now.tv_sec + SECURITY_TIMEOUT;
	outtime.tv_nsec = now.tv_usec * 1000;

	while (!resultReceived) {
		ret = pthread_cond_timedwait(&info->cond, &info->lock, &outtime);
		if (ret == ETIMEDOUT) {
			printf("%s: timeout for type=%d, cmd %d\n", __func__, type, cmd);
			return ret;
		}

        if (info->result_list != NULL) {
            security_result_list_t *result_list = info->result_list;
            security_result_list_t *result_list_prev = info->result_list;
            while (result_list != NULL) {
                if (result_list->result.hdr.cmd == cmd &&
						result_list->result.hdr.type == type) {
                    resultReceived = 1;
                    *result = result_list->result;
                    security_print_result(result);
                    result_list_prev->next = result_list->next;
                    if (result_list == info->result_list) {
						info->result_list = result_list->next;
                    }
                    free(result_list);
                    result_list = NULL;
                    break;
                } else {
                    /* TODO: maybe need to precess this event */
					/* TODO: for security, need add new list to process it in other thread */
                    result_list_prev = result_list;
                    result_list = result_list->next;
                }
            }
        }
	}
}

void security_signal_result(security_info_t *info, security_package_t *result)
{
	lock_security(&info->lock);

	security_result_list_t *curr_result = (security_result_list_t *)malloc(sizeof(security_result_list_t));
	if (curr_result == NULL) {
		printf("ERROR: malloc for security result failed, Result will not be sent\n");
		goto malloc_failed;
	}

	curr_result->result = *result;
	curr_result->next = NULL;

	if (info->result_list == NULL) info->result_list = curr_result;
	else {
		/* TODO:Need check the message type to distinguish which list this result to add */
		security_result_list_t *result_list = info->result_list;
		while (result_list != NULL) result_list = result_list->next;
		result_list->next = curr_result;
	}

malloc_failed:
	pthread_cond_broadcast(&info->cond);
	unlock_security(&info->lock);
}

void *security_read_loop(void *data)
{
	int ret;
	int nrd;
	security_info_t *info = (security_info_t *)data;
	int fd = info->fd;
	security_package_t result;
	uint8_t *buf = NULL;

	while(true) {
		buf = info->rbuf;
		memset(&result, 0, sizeof(security_package_t));
		nrd = read(fd, buf, SECURITY_MTU);
		if (nrd < 6) {
			printf("%s: the data is too few. ignore it.\n", __func__);
			continue;
		}

		memcpy(&result.hdr, buf, SECURITY_PACK_HDR_SIZE);
		if (nrd != result.hdr.len + SECURITY_PACK_HDR_SIZE) {
			printf("%s: oops, nrd=%d, hdr.len=%d.\n", nrd, result.hdr.len);
			continue;
		}

		buf += SECURITY_PACK_HDR_SIZE * sizeof(buf);
		if (result.hdr.len > 1) {
			result.payload = (uint8_t *)malloc(result.hdr.len - 1);
			if (result.payload == NULL) {
				printf("%s: can't alloc memory for payload.\n", __func__);
				continue;
			}
			memcpy(result.payload, buf, result.hdr.len - 1);
			buf += result.hdr.len - 1;
		}
		result.crc = *buf;

		/* check if crc match */
		if (result.crc != security_crc(&result.hdr, result.payload)) {
			printf("%s: crc isn't right, read crc=%d, calc crc=%d.\n", __func__,
							result.crc, security_crc(&result.hdr, result.payload));
			continue;
		}

		security_signal_result(info, &result);
	}
}

/* len include cmd, so len = payload_size + 1 */
int security_write(security_info_t *info, uint8_t type, uint8_t cmd, uint16_t len, uint8_t *payload)
{
	int nwt;
	int ret = NO_ERROR;
	uint8_t *buf = info->wbuf;
	security_pack_hdr hdr;

	hdr.hdr = PACK_SEND_HDR;
	hdr.type = type;
	hdr.version = SECURITY_VERSION;
	hdr.len = len;
	hdr.cmd = cmd;

	memcpy(buf, (uint8_t *)&hdr, SECURITY_PACK_HDR_SIZE);
	buf += SECURITY_PACK_HDR_SIZE * sizeof(buf);
	if (payload != NULL && len > 1) {
		memcpy(buf, payload, len - 1);
		buf += (len - 1) * sizeof(buf);
	}

	*buf = security_crc(&hdr, payload);

	nwt = write(info->fd, info->wbuf, SECURITY_PACK_HDR_SIZE + len);

	if (nwt < 0) {
		printf("write failed, ret = %d\n", nwt);
		ret = nwt;
	} else if (nwt != SECURITY_PACK_HDR_SIZE + len) {
		printf("write failed, nwt=%d, total_len=%d\n", nwt, SECURITY_PACK_HDR_SIZE + len);
		ret = -FAILED;
	}

	return ret;
}

int security_set_rtc(security_info_t *info)
{
	int ret = NO_ERROR;
	security_package_t result;
	timestamp_param time;
	struct timeval now;

	gettimeofday(&now, NULL);
	time.time = ((uint64_t)now.tv_sec) * 1000 + ((uint64_t)now.tv_usec) / 1000;

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, SETUP_RTC, TIMESTAMP_PARAM_SIZE + 1, (uint8_t *)&time);
	if (ret != NO_ERROR) {
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return ret;
	}

	security_wait_result(info, SETUP_TYPE, SETUP_RTC, &result);

	ret = *result.payload;
	if (ret == FAILED) {
		printf("%s: setup rtc failed\n", __func__);
		ret = -ret;
	}

	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

	unlock_security(&info->lock);

	return ret;
}

uint64_t security_get_rtc(security_info_t *info)
{
	int ret = NO_ERROR;
	security_package_t result;
	timestamp_param time;

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, GET_RTC, 1, NULL);
	if (ret != NO_ERROR) {
		printf("%s: write failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	security_wait_result(info, SETUP_TYPE, GET_RTC, &result);

	memcpy(&time, result.payload, TIMESTAMP_PARAM_SIZE);
	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

	unlock_security(&info->lock);

	return time.time;
}

int security_set_params(security_info_t *info, uint8_t *param)
{
	int ret = NO_ERROR;
	security_package_t result;
	uint16_t len;

	lock_security(&info->lock);

	if (*(uint16_t *)param == REPEAT_READ) {
		len = REPEAT_READ_PARAM_SIZE + 1;
	} else if (*(uint16_t *)param == FILTR_INTERV) {
		len = FILTR_INTERV_PARAM_SIZE + 1;
	}

	ret = security_write(info, SETUP_TYPE, SETUP_PARAM, len, param);
	if (ret != NO_ERROR) {
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return ret;
	}

	security_wait_result(info, SETUP_TYPE, SETUP_PARAM, &result);

	ret = *result.payload;
	if (ret == FAILED) {
		printf("%s: setup rtc failed\n", __func__);
		ret = -ret;
	}

	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

	unlock_security(&info->lock);

	return ret;
}

int security_set_repeat_read(security_info_t *info, uint8_t repeat)
{
	repeat_read_param param;

	param.type = REPEAT_READ;
	param.flag = repeat;

	return security_set_params(info, (uint8_t *)&param);
}

int security_set_filtr_interv(security_info_t *info, uint32_t interval)
{
	filtr_interv_param param;

	param.type = FILTR_INTERV;
	param.interval = interval;

	return security_set_params(info, (uint8_t *)&param);
}

int start_security(security_info_t *security_info)
{
	int ret;
	pthread_attr_t attr;

	assert(security_info != NULL);

	security_info->fd = security_open(SECURITY_DEV);
	if (security_info->fd < 0) {
		printf("%s: open security device node failed.\n", __func__);
		return -FAILED;
	}

	pthread_attr_init (&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	ret = pthread_create(&security_info->read_thread, &attr, security_read_loop, (void *)security_info);
	if (ret < 0) {
		printf("create security thread failed.\n");
		goto create_thread_failed;
	}

	printf("Start security successfully...\n");

	return NO_ERROR;

create_thread_failed:
	security_close(security_info->fd);
	return -FAILED;
}

void stop_security(security_info_t *security_info)
{
	close(security_info->fd);
}

int alloc_security(security_info_t **security_info)
{
	int ret;

	*security_info = (security_info_t *)malloc(sizeof(security_info));
	if (*security_info == NULL) {
		printf("Alloc memory for security info failed., errno=%d\n", errno);
		return -ENOMEM;
	}

	(*security_info)->fd = -1;
	(*security_info)->result_list = NULL;

	pthread_mutex_init(&(*security_info)->lock, NULL);
	pthread_cond_init(&(*security_info)->cond, NULL);

	return NO_ERROR;
}

void release_security(security_info_t *security_info)
{
	pthread_mutex_destroy(&security_info->lock);
	pthread_cond_destroy(&security_info->cond);

	/* free all pending api result here */
	if (security_info->result_list != NULL) {
		security_result_list_t *result_list = security_info->result_list;
		security_result_list_t *result_list_next;
		while (result_list != NULL) {
			result_list_next = result_list->next;
			free(result_list);
			result_list = result_list_next;
		}
	}

	free(security_info);
	security_info = NULL;
}

void test_security()
{
	int ret = NO_ERROR;
	security_info_t *pr = NULL;

	ret = alloc_security(&pr);
	if (ret != NO_ERROR)
		return;

	ret = start_security(pr);

test_fail:
	stop_security(pr);
	release_security(pr);
}

int main(int argc, char** argv)
{
	test_security();
	return 0;
}
