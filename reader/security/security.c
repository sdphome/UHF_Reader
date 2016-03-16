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
#include "../utils/sm2.hpp"

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

	memset(result, 0, sizeof(security_package_t));

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
#ifdef TEST
                if (result_list->result.hdr.cmd == cmd &&
						result_list->result.hdr.type == type + 1) {
#else
				if (result_list->result.hdr.cmd == cmd &&
						result_list->result.hdr.type == type) {
#endif
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

	return ret;
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
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, SETUP_TYPE, SETUP_RTC, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	ret = *result.payload;
	if (ret == FAILED) {
		printf("%s: setup rtc failed\n", __func__);
		ret = -ret;
	}

	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

	return ret;
}

uint64_t security_get_rtc(security_info_t *info)
{
	int ret = NO_ERROR;
	security_package_t result;
	timestamp_param time;

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, GET_RTC, NO_PARAM_SIZE, NULL);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, SETUP_TYPE, GET_RTC, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	memcpy(&time, result.payload, TIMESTAMP_PARAM_SIZE);
	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

	return time.time;
}

int security_set_params(security_info_t *info, uint8_t *param)
{
	int ret = NO_ERROR;
	security_package_t result;
	uint16_t len;

	if (*(uint16_t *)param == REPEAT_READ) {
		len = REPEAT_READ_PARAM_SIZE + 1;
	} else if (*(uint16_t *)param == FILTR_INTERV) {
		len = FILTR_INTERV_PARAM_SIZE + 1;
	} else {
		printf("%s: can't get this param, type=%d.\n", __func__, *(uint16_t *)param);
		return -FAILED;
	}

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, SETUP_PARAM, len, param);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, SETUP_TYPE, SETUP_PARAM, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	ret = *result.payload;
	if (ret == FAILED) {
		printf("%s: setup rtc failed\n", __func__);
		ret = -ret;
	}

	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

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

uint8_t* security_get_params(security_info_t *info, uint16_t type)
{
	int ret = NO_ERROR;
	get_params_param param;
	security_package_t result;

	param.type = type;

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, GET_PARAM, GET_PARAMS_PARAM_SIZE + 1, (uint8_t *)&param);
	if (ret != NO_ERROR) {
		printf("%s: write failed, ret = %d\n", __func__, ret);
		unlock_security(&info->lock);
		return NULL;
	}

	ret = security_wait_result(info, SETUP_TYPE, GET_PARAM, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return NULL;
	}

	return (uint8_t *)result.payload;
}

int security_get_firmware_version(security_info_t *info, firmware_version_param *param)
{
	int ret = NO_ERROR;
	uint8_t *payload = NULL;

	payload = security_get_params(info, FIRMWARE_VERSION);
	if (payload == NULL) {
		printf("%s: get version failed.\n", __func__);
		return -FAILED;
	}

	memcpy(param, payload, FIRMWARE_VERSION_PARAM_SIZE);

	free(payload);

	return ret;
}

int security_get_serial_number(security_info_t *info, serial_num_param *param)
{
	int ret = NO_ERROR;
	uint8_t *payload = NULL;

	payload = security_get_params(info, SECURITY_SERIAL);
	if (payload == NULL) {
		printf("%s: get serial number failed.\n", __func__);
		return -FAILED;
	}

	memcpy(param, payload, SERIAL_NUM_PARAM_SIZE);

	free(payload);

	return ret;
}

int security_get_repeat_read_flag(security_info_t *info, repeat_read_param *param)
{
	int ret = NO_ERROR;
	uint8_t *payload = NULL;

	payload = security_get_params(info, REPEAT_READ);
	if (payload == NULL) {
		printf("%s: get repeat read flag failed.\n", __func__);
		return -FAILED;
	}

	memcpy(param, payload, REPEAT_READ_PARAM_SIZE);

	free(payload);

	return ret;
}

work_mode_param* security_get_work_mode(security_info_t *info)
{
	uint8_t num = 0;
	uint8_t *payload = NULL;
	work_mode_param *param;

	payload = security_get_params(info, REPEAT_READ);
	if (payload == NULL) {
		printf("%s: get work mode information failed.\n", __func__);
		return NULL;
	}

	num = *payload;
	/* Need free in main thread */
	param = (work_mode_param *)malloc(WORK_MODE_PARAM_SIZE + PART_INFO_PARAM_SIZE * num);
	if (param == NULL) {
		printf("%s: malloc memory failed.\n", __func__);
		free(payload);
		return NULL;
	}

	/* FIXME: maybe also can resurn payload derectly */
	memcpy(param, payload, WORK_MODE_PARAM_SIZE + PART_INFO_PARAM_SIZE * num);
	free(payload);

	return param;
}

int security_get_key_version(security_info_t *info, security_package_t *result)
{
	int ret = NO_ERROR;
	get_params_param param;

	param.type = KEY_VERSION;

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, GET_PARAM, GET_PARAMS_PARAM_SIZE + 1, (uint8_t *)&param);
	if (ret != NO_ERROR) {
		printf("%s: write failed, ret = %d\n", __func__, ret);
		unlock_security(&info->lock);
		return -FAILED;
	}

	ret = security_wait_result(info, SETUP_TYPE, GET_PARAM, result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return -FAILED;
	}

	return ret;
}

int security_get_filtr_interv(security_info_t *info, repeat_read_param *param)
{
	int ret = NO_ERROR;
	uint8_t *payload = NULL;

	payload = security_get_params(info, FILTR_INTERV);
	if (payload == NULL) {
		printf("%s: get param failed.\n", __func__);
		return -FAILED;
	}

	memcpy(param, payload, FILTR_INTERV_PARAM_SIZE);

	free(payload);

	return ret;
}

int security_get_perm(security_info_t *info, perm_table_param *param)
{
	int ret = NO_ERROR;
	security_package_t result;

	if (param == NULL) {
		printf("%s: get permission failed.\n", __func__);
		return -FAILED;
	}

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, GET_PERMI, NO_PARAM_SIZE, NULL);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, SETUP_TYPE, GET_RTC, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	memcpy(param, result.payload, PERM_TABLE_PARAM_SIZE);
	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

	return ret;
}

int security_set_work_mode(security_info_t *info, work_mode_param *param)
{
	int ret = NO_ERROR;
	security_package_t result;

	if (param == NULL) {
		printf("%s: param is null.\n", __func__);
		return -FAILED;
	}

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, SETUP_MODE,
					PART_INFO_PARAM_SIZE * param->num + 2, (uint8_t *)param);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, SETUP_TYPE, SETUP_MODE, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	if (*result.payload)
		ret = -FAILED;

	free(result.payload);
	result.payload = NULL;

	return ret;
}

int security_request_rand_num(security_info_t *info, rand_num_param *param)
{
	int ret = NO_ERROR;
	security_package_t result;

	if (param == NULL) {
		printf("%s: param is null.\n", __func__);
		return -FAILED;
	}

	lock_security(&info->lock);

	ret = security_write(info, AUTH_TYPE, REQ_RAND_NUM, NO_PARAM_SIZE, NULL);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, AUTH_TYPE, REQ_RAND_NUM, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	if (result.payload != NULL) {
		memcpy(param, result.payload, RAND_NUM_PARAM_SIZE);
		free(result.payload);
		result.payload = NULL;
	} else
		ret = -FAILED;

	return ret;
}

unsigned long security_get_file_size(const char *path)
{
	unsigned long size = -1;
	FILE *fp;

	fp = fopen(path, "r");
	if(fp == NULL)
		return size;

	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fclose(fp);

	return size;
}

int security_read_x509(uint8_t *x509, char *path, unsigned long size)
{
	unsigned long nrd;
	FILE *fp = fopen(path, "r");

	rewind(fp);
	nrd = fread(x509, 1, size, fp);

	if (nrd == size)
		return NO_ERROR;
	else
		return -FAILED;
}

int security_digi_sign(security_info_t *info, auth_data_param *param)
{
	int ret = NO_ERROR;
	uint8_t hash[32] = {0};
	uint8_t message[32] = {0};
	int rlen, slen;

	memcpy(message, (uint8_t *)&param->host_rand, 8);
	memcpy(message + 8, (uint8_t *)&param->sec_rand, 8);
	memcpy(message + 16, (uint8_t *)&param->serial, 8);
	memcpy(message + 24, (uint8_t *)&param->reserve, 8);

	ret = sm3_e((uint8_t *)&info->serial, 8, info->pub_key, 32,
		info->pub_key + 32, 32, message, 32, hash);
	if (ret != NO_ERROR)
		return ret;

	sm2_sign(hash, 32, info->priv_key, 32, param->sign, &rlen, param->sign + 32, &slen);
}


/**
 * ret
 * 0 : auth pass
 * 1 : verify sign failed
 * 2 : verify rand number faild
 * 3 : the module hasn't actived
 * 4 : security module has actived by other reader
 * A : reader serial number failed
*/
int security_send_auth_data(security_info_t *info, rand_num_param *rand_param)
{
	int ret = NO_ERROR;
	uint64_t rand_num = 0;
	unsigned long size = -1;
	auth_data_param *param = NULL;
	security_package_t result;

	size = security_get_file_size(info->x509_path);
	if (size < 0 || size > SECURITY_MTU - AUTH_DATA_PARAM_SIZE - SECURITY_PACK_HDR_SIZE) {
		printf("%s: x509 size error, size = %ld.\n", size);
		return -FAILED;
	}

	param = (auth_data_param *)malloc(AUTH_DATA_PARAM_SIZE + size);

	/* 1. generate random number */
	srand((unsigned)time(NULL));
	param->host_rand = (uint64_t)rand() << 32 | (uint64_t)rand();

	/* 2. fill data */
	param->sec_rand = rand_param->sec_rand;
	param->serial = info->serial;
	param->reserve = 0;
	ret = security_read_x509(param->x509, info->x509_path, size);
	if (ret != NO_ERROR) {
		printf("%s: read x509 failed.\n", __func__);
		free(param);
		return ret;
	}

	/* 3. digital signature */
	/* CARE: Need use big endian data */
	ret = security_digi_sign(info, param);
	if (ret != NO_ERROR) {
		free(param);
		printf("%s: sign failed\n", __func__);
		return ret;
	}

	lock_security(&info->lock);

	ret = security_write(info, AUTH_TYPE, IDEN_AUTH, AUTH_DATA_PARAM_SIZE + size + 1, (uint8_t *)param);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		free(param);
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, SETUP_TYPE, SETUP_RTC, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		free(param);
		return ret;
	}

	/* upper level check the result */
	ret = *result.payload;

	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

	return ret;
}

uint8_t *security_send_user_info(security_info_t *security_info)
{
	int ret = NO_ERROR;
	user_info_param user_info;
	security_package_t result;

	memset(&user_info, 0, USER_INFO_PARAM_SIZE);
	/* TODO: fill user_info */

	lock_security(&info->lock);

	ret = security_write(info, AUTH_TYPE, USER_INFO, USER_INFO_PARAM_SIZE + 1, (uint8_t *)&user_info);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return NULL;
	}

	ret = security_wait_result(info, SETUP_TYPE, SETUP_RTC, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return NULL;
	}

	return result->payload;
}

int start_security(security_info_t *security_info)
{
	int ret;
	pthread_attr_t attr;

	assert(security_info != NULL);

	security_info->fd = security_open((char *)SECURITY_DEV);
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
