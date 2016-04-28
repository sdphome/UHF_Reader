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
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <sys/socket.h>
//#include <security.h>
#include <uhf.h>

/* FIXME: undef it */
//#define TEST
#define DEBUG

static inline int security_open(char *dev)
{
	return open(dev, O_RDWR);
}

static inline void security_close(int fd)
{
	close(fd);
}

uint8_t security_crc(security_pack_hdr * hdr, uint8_t * buf)
{
	int i = 0;
	uint8_t crc = 0;
	uint8_t *tmp = (uint8_t *) hdr;

	for (i = 1; i < SECURITY_PACK_HDR_SIZE; i++) {
		crc ^= *(tmp + i);
	}

	for (i = 0; i < hdr->len - 1; i++) {
		crc ^= *(buf + i);
	}

	return crc;
}

void security_print_result(security_package_t * result)
{
#ifdef DEBUG
	int i;
	printf("===============SECURITY================\n");
	printf("hdr:%x, type:%x, version:%x, cmd:%x, len:%x, crc:%x\n", result->hdr.hdr,
		   result->hdr.type, result->hdr.version, result->hdr.cmd, result->hdr.len, result->crc);
	printf("payload: ");
	for (i = 0; i < result->hdr.len - 1; i++) {
		printf("%3x", *(result->payload + i));
	}
	printf("\n===============SECURITY================\n");
#endif
}

void inline lock_security(pthread_mutex_t * lock)
{
	pthread_mutex_lock(lock);
}

void inline unlock_security(pthread_mutex_t * lock)
{
	pthread_mutex_unlock(lock);
}

int inline security_reset(int fd)
{
	return ioctl(fd, US_IOC_RESET, NULL);
}

int inline security_get_status(int fd)
{
	int status = OK;

	status = ioctl(fd, US_IOC_GET_STATUS, NULL);

	return status;
}

int inline security_reset_radio(int fd)
{
	return ioctl(fd, US_IOC_RESET_RADIO, NULL);
}

int inline security_get_radio_status(int fd)
{
	int status = OK;

	status = ioctl(fd, US_IOC_GET_RADIO_STATUS, NULL);

	return status;
}

const char *security_upload_err_to_str(uint8_t errno)
{
	switch (errno) {
	  case NO_ERROR:
		  return "success.\n";
	  case TID_DECIP_FAILED:
		  return "tid verify failed, got tid'\n";
	  case READ_PART_FAILED:
		  return "tid is right, but read user part data failed.\n";
	  case WRONG_CHECK:
		  return "security receive error check framw from radio module.\n";
	  case USER_PART_FAILED:
		  return "read user part verify failed, return data directly\n";
	  default:
		  return "unknow error.\n";
	}
}

const char *security_errno_to_str(uint8_t errno)
{
	switch (errno) {
	  case NO_ERROR:
		  return "success.\n";
	  case UNKNOWN_TYPE:
		  return "unknown frame type.\n";
	  case DATA_ERROR:
		  return "frame payload error.\n";
	  case PACK_ILLE:
		  return "illegal frame.\n";
	  case CRC_FAILED:
		  return "crc verify failed.\n";
	  case PROGRAM_MISSING:
		  return "security module user program failed.\n";
	  case VERIFY_ENCR_FAILED:
		  return "security module user program sign the check failed.\n";
	  default:
		  return "unknown error.\n";
	}
}

int security_wait_result(security_info_t * info, uint8_t type, uint8_t cmd,
						 security_package_t * result)
{
	int ret = NO_ERROR;
	int resultReceived = 0;
	struct timeval now;
	struct timespec outtime;

	memset(result, 0, sizeof(security_package_t));

	gettimeofday(&now, NULL);
	outtime.tv_sec = now.tv_sec + SECURITY_TIMEOUT;
	outtime.tv_nsec = now.tv_usec * 1000;
#ifdef DEBUG
	printf("%s: +\n", __func__);
#endif
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
				if (result_list->result.hdr.cmd == cmd && result_list->result.hdr.type == type) {
#else
				/* Check if got a error frame */
				if (result_list->result.hdr.type == ERROR_TYPE) {
					printf("%s: Got a error frame, errno=%d.\n", __func__,
						   result_list->result.hdr.cmd);
					return result_list->result.hdr.cmd;
				}

				if (result_list->result.hdr.cmd == cmd && result_list->result.hdr.type == type + 1) {
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
					result_list_prev = result_list;
					result_list = result_list->next;
				}
			}
		}
	}
#ifdef DEBUG
	printf("%s: -\n", __func__);
#endif
	return ret;
}

void security_signal_result(security_info_t * info, security_package_t * result)
{
	lock_security(&info->lock);

	security_result_list_t *curr_result =
		(security_result_list_t *) malloc(sizeof(security_result_list_t));
	if (curr_result == NULL) {
		printf("ERROR: malloc for security result failed, Result will not be sent\n");
		goto malloc_failed;
	}

	curr_result->result = *result;
	curr_result->next = NULL;

	if (info->result_list == NULL)
		info->result_list = curr_result;
	else {
		security_result_list_t *result_list = info->result_list;
		while (result_list->next != NULL)
			result_list = result_list->next;
		result_list->next = curr_result;
	}

  malloc_failed:
	pthread_cond_broadcast(&info->cond);
	unlock_security(&info->lock);
}

void security_signal_upload(security_info_t * info, security_package_t * upload)
{
	lock_security(&info->upload_lock);

	security_result_list_t *curr_upload =
		(security_result_list_t *) malloc(sizeof(security_result_list_t));
	if (curr_upload == NULL) {
		printf("ERROR: malloc for security result failed, Result will not be sent\n");
		goto malloc_failed;
	}

	curr_upload->result = *upload;
	curr_upload->next = NULL;

	if (info->upload_list == NULL)
		info->upload_list = curr_upload;
	else {
		security_result_list_t *upload_list = info->upload_list;
		while (upload_list->next != NULL)
			upload_list = upload_list->next;
		upload_list->next = curr_upload;
	}

  malloc_failed:
	pthread_cond_broadcast(&info->upload_cond);
	unlock_security(&info->upload_lock);
}

int security_write(security_info_t * info, uint8_t type, uint8_t cmd, uint16_t len,
				   uint8_t * payload)
{
	int nwt;
	int ret = NO_ERROR;
	uint8_t *buf = info->wbuf;
	security_pack_hdr hdr;

	//printf("%s: +++++++\n", __func__);

	hdr.hdr = PACK_SEND_HDR;
	hdr.type = type;
	hdr.version = SECURITY_VERSION_1;	/* TODO: Attention the version */
	hdr.len = len;
	hdr.cmd = cmd;

	memcpy(buf, (uint8_t *) & hdr, SECURITY_PACK_HDR_SIZE);
	buf += SECURITY_PACK_HDR_SIZE;
	if (payload != NULL && len > 1) {
		memcpy(buf, payload, len - 1);
		buf += (len - 1);
	}

	*buf = security_crc(&hdr, payload);

#ifdef DEBUG
	int i = 0;
	printf("before security_write:");
	for (i = 0; i < SECURITY_PACK_HDR_SIZE + len; i++) {
		if (!(i%16))
			printf("\n");
		printf("%4x", *(info->wbuf + i));
	}
	printf("\n");
#endif
	nwt = write(info->fd, info->wbuf, SECURITY_PACK_HDR_SIZE + len);
#ifdef DEBUG
	printf("security write finish\n");
#endif
	if (nwt < 0) {
		printf("%s:write failed, ret = %d\n", __func__, nwt);
		ret = nwt;
	}

/*
	else if (nwt != SECURITY_PACK_HDR_SIZE + len) {
		printf("write failed, nwt=%d, total_len=%d\n", nwt, SECURITY_PACK_HDR_SIZE + len);
		ret = -FAILED;
	}
*/

//	printf("%s: ret = %d.\n", __func__, ret);
	return ret;
}

int security_set_rtc(security_info_t * info)
{
	int ret = NO_ERROR;
	security_package_t result;
	timestamp_v2_param time_ms;
	struct timeval now;
	time_t rawtime;
	struct tm *timeinfo;

	memset(&result, 0, sizeof(security_package_t));

	time(&rawtime);
	printf("%s: %x\n", __func__, (unsigned int)rawtime);
	timeinfo = localtime(&rawtime);
	printf("The current date/time is: %s\n", asctime(timeinfo));

	gettimeofday(&now, NULL);
	printf("%s: now.tv_sec=%x\n", __func__, (uint32_t) now.tv_sec);
	time_ms.time = ((uint64_t) now.tv_sec) * 1000 + ((uint64_t) now.tv_usec) / 1000;

	lock_security(&info->lock);

	ret =
		security_write(info, SETUP_TYPE, SETUP_RTC, TIMESTAMP_V2_PARAM_SIZE + 1,
					   (uint8_t *) & time_ms.time);
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

	if (result.payload != NULL) {
		ret = *result.payload;
		if (ret != NO_ERROR) {
			printf("%s: setup rtc failed\n", __func__);
			ret = -ret;
		}

		free(result.payload);
		result.payload = NULL;
	}

	printf("%s: end.\n", __func__);

	return ret;
}

uint64_t security_get_rtc(security_info_t * info)
{
	int ret = NO_ERROR;
	security_package_t result;
	timestamp_v2_param time;
	time_t lt;

	memset(&result, 0, sizeof(security_package_t));

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

	/* FIXME: May need check version */

	if (result.payload == NULL) {
		return -FAILED;
	}

	memcpy(&time, result.payload, TIMESTAMP_V2_PARAM_SIZE);

	if (result.payload != NULL) {
		free(result.payload);
		result.payload = NULL;
	}

	lt = (time_t) (time.time / 1000);

	printf("%s: time is %s\n", __func__, asctime(localtime(&lt)));

	return time.time;
}

static int security_set_params(security_info_t * info, uint8_t * param)
{
	int ret = NO_ERROR;
	security_package_t result;
	uint16_t len;

	memset(&result, 0, sizeof(security_package_t));

	if (*(uint16_t *) param == REPEAT_READ) {
		len = REPEAT_READ_PARAM_SIZE + 1;
	} else if (*(uint16_t *) param == FILTR_INTERV) {
		len = FILTR_INTERV_PARAM_SIZE + 1;
	} else {
		printf("%s: can't get this param, type=%d.\n", __func__, *(uint16_t *) param);
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

	if (result.payload != NULL) {
		ret = *result.payload;
		if (ret == FAILED) {
			printf("%s: setup param failed\n", __func__);
			ret = -ret;
		}

		free(result.payload);
		result.payload = NULL;
	} else {
		printf("%s: can't get the params.\n", __func__);
		ret = -FAILED;
	}

	return ret;
}

int security_set_repeat_read(security_info_t * info, uint8_t repeat)
{
	repeat_read_param param;

	param.type = REPEAT_READ;
	param.flag = repeat;

	return security_set_params(info, (uint8_t *) & param);
}

int security_set_filtr_interv(security_info_t * info, uint32_t interval)
{
	filtr_interv_param param;

	param.type = FILTR_INTERV;
	param.interval = interval;

	return security_set_params(info, (uint8_t *) & param);
}

static uint8_t *security_get_params(security_info_t * info, uint16_t type)
{
	int ret = NO_ERROR;
	get_params_param param;
	security_package_t result;

	memset(&result, 0, sizeof(security_package_t));

	param.type = type;

	lock_security(&info->lock);

	ret =
		security_write(info, SETUP_TYPE, GET_PARAM, GET_PARAMS_PARAM_SIZE + 1, (uint8_t *) & param);
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

	return (uint8_t *) result.payload;
}

int security_get_firmware_version(security_info_t * info, firmware_version_param * param)
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

int security_get_serial_number(security_info_t * info, serial_num_param * param)
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

int security_get_repeat_read_flag(security_info_t * info, repeat_read_param * param)
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

work_mode_param *security_get_work_mode(security_info_t * info)
{
	uint8_t num = 0;
	uint8_t *payload = NULL;
	work_mode_param *param;

	payload = security_get_params(info, WORK_MODE);
	if (payload == NULL) {
		printf("%s: get work mode information failed.\n", __func__);
		return NULL;
	}

	num = *(payload + 1);
	/* Need free in main thread */
	param = (work_mode_param *) malloc(WORK_MODE_PARAM_SIZE + PART_INFO_PARAM_SIZE * num);
	if (param == NULL) {
		printf("%s: malloc memory failed.\n", __func__);
		free(payload);
		return NULL;
	}

	/* FIXME: maybe also can resurn payload derectly */
	memcpy(param, payload + 1, WORK_MODE_PARAM_SIZE + PART_INFO_PARAM_SIZE * num);
	free(payload);

	return param;
}

int security_get_key_version(security_info_t * info, security_package_t * result)
{
	int ret = NO_ERROR;
	get_params_param param;

	param.type = KEY_VERSION;

	lock_security(&info->lock);

	ret =
		security_write(info, SETUP_TYPE, GET_PARAM, GET_PARAMS_PARAM_SIZE + 1, (uint8_t *) & param);
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

int security_get_filtr_interv(security_info_t * info, filtr_interv_param * param)
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

int security_get_perm(security_info_t * info, perm_table_param * param)
{
	int ret = NO_ERROR;
	security_package_t result;

	if (param == NULL) {
		printf("%s: get permission failed.\n", __func__);
		return -FAILED;
	}

	memset(&result, 0, sizeof(security_package_t));

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

int security_set_work_mode(security_info_t * info, work_mode_param * param)
{
	int ret = NO_ERROR;
	security_package_t result;

	if (param == NULL) {
		printf("%s: param is null.\n", __func__);
		return -FAILED;
	}

	memset(&result, 0, sizeof(security_package_t));

	lock_security(&info->lock);

	ret = security_write(info, SETUP_TYPE, SETUP_MODE,
						 PART_INFO_PARAM_SIZE * param->num + 2, (uint8_t *) param);
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

	if (result.payload != NULL) {
		if (*result.payload)
			ret = -FAILED;

		free(result.payload);
		result.payload = NULL;
	}
	return ret;
}

uint64_t security_request_rand_num(security_info_t * info)
{
	int ret = NO_ERROR;
	security_package_t result;
	uint64_t sec_rand;

	memset(&result, 0, sizeof(security_package_t));

	lock_security(&info->lock);

	ret = security_write(info, AUTH_TYPE, REQ_RAND_NUM, NO_PARAM_SIZE, NULL);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d.\n", __func__, ret);
		return NO_ERROR;
	}

	ret = security_wait_result(info, AUTH_TYPE, REQ_RAND_NUM, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	if (result.payload != NULL) {
		sec_rand = *(uint64_t *) result.payload;
		free(result.payload);
		result.payload = NULL;
		return sec_rand;
	} else
		return NO_ERROR;
}

static void security_reverse_32(uint8_t * buf)
{
	int i;
	uint8_t temp;

	for (i = 0; i < 16; i ++) {
		temp = buf[i];
		buf[i] = buf[31 - i];
		buf[31 - i] = temp;
	}
}

static int security_digi_sign(security_info_t * info, auth_data_param * param)
{
	int ret = NO_ERROR;
	uint8_t message[32] = { 0 };
	int rlen, slen;

	memcpy(message, (uint8_t *) & param->host_rand, 8);
	memcpy(message + 8, (uint8_t *) & param->sec_rand, 8);
	memcpy(message + 16, (uint8_t *) & param->serial, 8);
	memcpy(message + 24, (uint8_t *) & param->reserve, 8);

	security_reverse_32(message);
	sm2_sign(message, 32, param->sign, &rlen, param->sign + 32, &slen);

	security_reverse_32(param->sign);
	security_reverse_32(param->sign + 32);

	return ret;
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
int security_send_auth_data(security_info_t * info, uint64_t sec_rand)
{
	int ret = NO_ERROR;
	unsigned long size = -1;
	auth_data_param *param = NULL;
	security_package_t result;
	FILE *fp = NULL;

	memset(&result, 0, sizeof(security_package_t));

	ret = file_get_size(SECURITY_AUTH_X509_PATH, &size);
	if (ret < 0 || size > SECURITY_MTU - AUTH_DATA_PARAM_SIZE - SECURITY_PACK_HDR_SIZE) {
		printf("%s: x509 size error, size = %ld.\n", __func__, size);
		return -FAILED;
	}

	param = (auth_data_param *) malloc(AUTH_DATA_PARAM_SIZE + size);

	/* 1. generate random number */
	srand((unsigned)time(NULL));
	*(uint64_t *) param->host_rand = (uint64_t) rand() << 32 | (uint64_t) rand();

	/* 2. fill data */
	memcpy(param->sec_rand, &sec_rand, RAND_NUM_PARAM_SIZE);
	param->serial = info->serial;
	param->reserve = 0;

	fp = fopen(SECURITY_AUTH_X509_PATH, "r");
	if (fp == NULL) {
		printf("read data. fp is null.\n");
		return -FAILED;
	}
	ret = file_read_data(param->x509, fp, size);
	if (ret != NO_ERROR) {
		printf("%s: read x509 failed.\n", __func__);
		fclose(fp);
		free(param);
		return ret;
	}
	fclose(fp);

	/* 3. digital signature */
	/* CARE: May need use big endian data */
	ret = security_digi_sign(info, param);
	if (ret != NO_ERROR) {
		free(param);
		printf("%s: sign failed\n", __func__);
		return ret;
	}

	lock_security(&info->lock);

	ret =
		security_write(info, AUTH_TYPE, IDEN_AUTH, AUTH_DATA_PARAM_SIZE + size + 1,
					   (uint8_t *) param);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		free(param);
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, AUTH_TYPE, IDEN_AUTH, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		free(param);
		return ret;
	}

	if (result.payload != NULL) {
		/* upper level check the result */
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	} else
		ret = -FAILED;

	return ret;
}

int security_send_user_info(security_info_t * info, security_package_t * result)
{
	int ret = NO_ERROR;
	unsigned long size = -1;
	FILE * fp = NULL;
	user_info_param user_info;

	printf("Enter %s.\n", __func__);

	memset(result, 0, sizeof(security_package_t));
	memset(&user_info, 0, USER_INFO_PARAM_SIZE);
	/* TODO: fill user_info */
	ret = file_get_size(USER_INFO_PATH, &size);
	if (ret != NO_ERROR || size != USER_INFO_PARAM_SIZE) {
		printf("%s: %s size is %ld, ret = %d.\n", __func__, USER_INFO_PATH, size, ret);
		ret = -FAILED;
		return ret;
	}

	fp = fopen(USER_INFO_PATH, "r");
	if (fp == NULL) {
		printf("open %s fp is null.\n", USER_INFO_PATH);
		return -FAILED;
	}
	ret = file_read_data((uint8_t *) &user_info, fp, size);
	if (ret != NO_ERROR) {
		printf("%s: read x509 failed.\n", __func__);
		fclose(fp);
		return ret;
	}
	fclose(fp);

	lock_security(&info->lock);

	ret =
		security_write(info, AUTH_TYPE, USER_INFO, USER_INFO_PARAM_SIZE + 1,
					   (uint8_t *) & user_info);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return ret;
	}

	ret = security_wait_result(info, AUTH_TYPE, USER_INFO, result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return ret;
	}

	printf("Exit %s.\n", __func__);
	/* Need send the data to upper computer */
	return ret;
}

/**
 * ret
 * 0 : active success
 * 1 : deciphering failed
 * 2 : verify failed
 * 3 : serial not unanimous
 */
int security_send_active_auth(security_info_t * info, uint8_t * active, uint16_t len)
{
	int ret = NO_ERROR;
	security_package_t result;

	if (active == NULL || len != 216) {
		printf("%s: active = 0x%p, len = %d.\n", __func__, active, len);
		return -FAILED;
	}

	memset(&result, 0, sizeof(security_package_t));

	lock_security(&info->lock);

	ret = security_write(info, AUTH_TYPE, SEND_AUTH, len + 1, active);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return -FAILED;
	}

	ret = security_wait_result(info, AUTH_TYPE, SEND_AUTH, &result);

	unlock_security(&info->lock);

	if (ret != NO_ERROR || result.payload == NULL) {
		printf("%s: wait result failed, ret = %d.\n", __func__, ret);
		return -FAILED;
	}

	ret = *result.payload;
	free(result.payload);

	return ret;
}

int security_send_cert(security_info_t * info, uint8_t * cert, uint16_t len)
{
	int ret = NO_ERROR;
	security_package_t result;

	printf("Enter %s.\n", __func__);

	printf("cert len = %u.\n", len);

	if (cert == NULL || len < 512) {
		printf("%s: cert is %p, len = %u.\n", __func__, cert, len);
		return -FAILED;
	}

	memset(&result, 0, sizeof(security_package_t));

	lock_security(&info->lock);

	ret = security_write(info, AUTH_TYPE, SEND_CERT, len + 1, cert);
	if (ret != NO_ERROR) {
		unlock_security(&info->lock);
		printf("%s: write failed, ret = %d\n", __func__, ret);
		return -FAILED;
	}

	ret = security_wait_result(info, AUTH_TYPE, SEND_CERT, &result);

	unlock_security(&info->lock);

	if (result.payload != NULL) {
		ret = *result.payload;
	}

	printf("Exit %s.\n", __func__);
	return ret;
}

int security_upgrade_firmware(security_info_t * info, char *file)
{
	int ret = NO_ERROR;
	unsigned long file_size;
	uint8_t *buf;
	uint8_t *temp;
	uint16_t num_block;
	security_package_t result;
	firmware_data *data;
	FILE *fp;
	int i, flag;

	if (file == NULL) {
		printf("%s: file is null.\n", __func__);
		return -FAILED;
	}

	security_reset(info->fd);
	//sleep(1);
	while (security_get_status(info->fd));

	memset(&result, 0, sizeof(security_package_t));

	ret = file_get_size(file, &file_size);
	if (ret < 0) {
		printf("%s: get file size failed, ret=%d.\n", __func__, ret);
		return -FAILED;
	}

	buf = (uint8_t *) malloc(file_size);
	if (buf == NULL)
		return -ENOMEM;

	fp = fopen(file, "r");
	ret = file_read_data(buf, fp, file_size);
	if (ret != NO_ERROR) {
		printf("%s: read firmware failed.\n", __func__);
		free(buf);
		fclose(fp);
		buf = NULL;
		return ret;
	}
	fclose(fp);

	data = (firmware_data *) buf;

	if (data->file_size != data->firmware_size + FIRMWARE_DATA_HDR_SIZE) {
		printf("%s: firmware size verify failed.\n", __func__);
		free(buf);
		buf = NULL;
		return -FAILED;
	}

	temp = buf + FIRMWARE_DATA_HDR_SIZE;

	flag = data->firmware_size % data->block_size;
	if (flag)
		num_block = data->firmware_size / data->block_size + 1;
	else
		num_block = data->firmware_size / data->block_size;

	for (i = 0; i < num_block; i++) {
		lock_security(&info->lock);

		if (flag && i == num_block - 1)
			//data->block_size = data->firmware_size - i * data->block_size;
			data->block_size = flag;

		ret = security_write(info, DATA_FORWA_TYPE, data->cmd, data->block_size + 1, temp);
		if (ret != NO_ERROR) {
			unlock_security(&info->lock);
			free(buf);
			buf = NULL;
			printf("%s: write failed, ret = %d\n", __func__, ret);
			return -FAILED;
		}

		memset(&result, 0, sizeof(security_package_t));
		ret = security_wait_result(info, DATA_FORWA_TYPE, data->cmd, &result);

		unlock_security(&info->lock);

		if (ret != NO_ERROR || result.payload == NULL) {
			printf("%s: wait result failed, ret = %d.\n", __func__, ret);
			free(buf);
			buf = NULL;
			return -FAILED;
		}

		temp = temp + data->block_size;

		ret = *result.payload;
		if (ret != NO_ERROR)
			i = num_block;
		free(result.payload);
		result.payload = NULL;
	}

	free(buf);

	printf("%s: Upgrade firmware successful.\n", __func__);

	return ret;
}

static void security_upload_part(security_info_t * info, security_package_t * upload)
{
	uint8_t err_type;

	err_type = *upload->payload;

	switch (err_type) {
	  case NO_ERROR:{

/*
			if (upload->hdr.version == SECURITY_VERSION_1) {
				tid_upload_v1_param *param;
				param = (tid_upload_v1_param *)upload->payload;
				upper_request_TagSelectAccessReport(((uhf_info_t *)(info->uhf))->upper,
							param->tid, param->ante_no, param->time);
			} else {
*/
			  part_data_upload_v2_param *param;
			  param = (part_data_upload_v2_param *) upload->payload;
			  if (info->uhf != NULL && ((uhf_info_t *) (info->uhf))->upper != NULL) {
				  upper_request_TagSelectAccessReport(((uhf_info_t *) (info->uhf))->upper,
													  param->tid, param->ante_no, param->time);
			  }

/*
			}
*/
			free(upload->payload);
			upload->payload = NULL;
			break;
		  }
	  case TID_DECIP_FAILED:
		  break;
	  case WRONG_CHECK:
		  break;
	  default:
		  printf("%s: unknown error type %d.\n", __func__, err_type);
		  break;
	}
}

static void security_upload_tid(security_info_t * info, security_package_t * upload)
{
	uint8_t err_type;

	err_type = *upload->payload;

//	printf("%s: error_type = 0x%x.\n", __func__, err_type);
	switch (err_type) {
	  case NO_ERROR:{

/*
			if (upload->hdr.version == SECURITY_VERSION_1) {
				tid_upload_v1_param *param;
				param = (tid_upload_v1_param *)upload->payload;
				upper_request_TagSelectAccessReport(((uhf_info_t *)(info->uhf))->upper,
							param->tid, param->ante_no, param->time);
			} else {
*/
			tid_upload_v2_param *param;
			param = (tid_upload_v2_param *) upload->payload;
			if (info->uhf != NULL && ((uhf_info_t *) (info->uhf))->upper != NULL)
				upper_request_TagSelectAccessReport(((uhf_info_t *) (info->uhf))->upper,
											  param->tid, param->ante_no, param->time);

/*
			}
*/
			free(upload->payload);
			upload->payload = NULL;
			break;
		  }
	  case TID_DECIP_FAILED:
		  break;
	  case WRONG_CHECK:
		  break;
	  default:
		  printf("%s: unknown error type %d.\n", __func__, err_type);
		  break;
	}
}

void *security_upload_loop(void *data)
{
	int upload_received = false;
	security_info_t *info = (security_info_t *) data;
	security_package_t upload;

	while (true) {
		lock_security(&info->upload_lock);
		pthread_cond_wait(&info->upload_cond, &info->upload_lock);

		if (info->upload_list != NULL) {
			security_result_list_t *upload_list = info->upload_list;
			security_result_list_t *upload_list_prev = info->upload_list;
			while (upload_list != NULL) {
				upload_received = false;
				if (upload_list->result.hdr.type == UPLOAD_INFO_TYPE) {
					upload = upload_list->result;	/* Got the upload info */
					security_print_result(&upload);
					upload_received = true;
				}
				upload_list_prev->next = upload_list->next;	/* cross upload_list */
				if (upload_list == info->upload_list) {	/* list head, move list head to next */
					info->upload_list = upload_list->next;
				}
				if (upload_received == true) {
					/* TODO: we can process the upload now, TBD */
					if (upload.hdr.type == UPLOAD_INFO_TYPE) {
						if (upload.hdr.cmd == REPORT_TID) {
							security_upload_tid(info, &upload);
						} else if (upload.hdr.cmd == REPORT_PART) {
							security_upload_part(info, &upload);
							//printf("%s: Got REPORT_PART cmd.\n", __func__);
						}
					} else if (upload.hdr.type == DATA_FORWA_TYPE) {
						//printf("%s: Got DATA_FORWA_TYPE.\n", __func__);
					}
				}

				free(upload.payload);
				upload.payload = NULL;
				free(upload_list);
				upload_list = NULL;
			}
		}
		unlock_security(&info->upload_lock);
	}
}

void *security_read_loop(void *data)
{
	int nrd;
	security_info_t *info = (security_info_t *) data;
	int fd = info->fd;
	security_package_t result;
	uint8_t *buf = NULL;

	while (true) {
		buf = info->rbuf;
		memset(&result, 0, sizeof(security_package_t));
		memset(buf, 0, SECURITY_MTU);

		nrd = read(fd, buf, SECURITY_MTU);
		if (nrd < 6) {
			printf("%s: the data is too few. ignore it.\n", __func__);
			continue;
		}
#ifdef DEBUG
	{
		int i = 0;
		printf("%s: nrd = %d\n", __func__, nrd);
		for (i = 0; i < nrd; i ++) {
			printf("%4x", *(buf + i));
		}
		printf("\n");
	}
#endif

		memcpy(&result.hdr, buf, SECURITY_PACK_HDR_SIZE);
		if (nrd != result.hdr.len + SECURITY_PACK_HDR_SIZE) {
			printf
				("%s: oops, nrd=%d, hdr.hdr=%x, hdr.type=%x, hdr.version=%x, hdr.len=%x, hdr.cmd=%x.\n",
				 __func__, nrd, result.hdr.hdr, result.hdr.type, result.hdr.version, result.hdr.len,
				 result.hdr.cmd);
			continue;
		}

		buf += SECURITY_PACK_HDR_SIZE;
		if (result.hdr.len > 1) {
			result.payload = (uint8_t *) malloc(result.hdr.len - 1);
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

		if (result.hdr.type == ERROR_TYPE) {
			printf("%s: Occur a error, errno = %x\n", __func__, result.hdr.cmd);
		}

		/* TODO: check UPLOAD_INFO_TYPE, need add the result in a new list
		   DATA_FORWARD also need */

		if (result.hdr.type == UPLOAD_INFO_TYPE || result.hdr.type == DATA_FORWA_TYPE)
			security_signal_upload(info, &result);
		else
			security_signal_result(info, &result);
	}
}

int start_security(security_info_t * info)
{
	int ret;
	pthread_attr_t attr;

	assert(info != NULL);

	info->fd = security_open((char *)SECURITY_DEV);
	if (info->fd < 0) {
		printf("%s: open security device node failed.\n", __func__);
		return -FAILED;
	}

	security_get_status(info->fd);

	security_reset(info->fd);
	security_get_status(info->fd);
	security_get_status(info->fd);
	sleep(6);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	ret = pthread_create(&info->read_thread, &attr, security_read_loop, (void *)info);
	if (ret < 0) {
		printf("create security thread failed.\n");
		goto create_thread_failed;
	}

	ret = pthread_create(&info->upload_thread, &attr, security_upload_loop, (void *)info);
	if (ret < 0) {
		printf("create security thread failed.\n");
		goto create_thread_failed;
	}

/*
	security_reset(info->fd);
	security_get_status(info->fd);
	security_reset_radio(info->fd);
	security_get_status(info->fd);
	sleep(6);
*/
	/* FIXME : sequential */
	/* wait for ready */
#if 0
#ifndef TEST
	while (security_get_status(info->fd) == BUSY) {
		printf("%s: wait security module get ready.\n", __func__);
		sleep(1);
	}
#endif
#endif
	printf("Start security successfully...\n");

	return NO_ERROR;

  create_thread_failed:
	security_close(info->fd);
	return -FAILED;
}

void stop_security(security_info_t * info)
{
	void *ret;
	if (info == NULL)
		return;

	pthread_cancel(info->read_thread);
	pthread_join(info->read_thread, &ret);
	close(info->fd);
}

int alloc_security(security_info_t ** security_info)
{
	uint8_t userid[8] = {0x30, 0x33, 0x30,  0x30,  0x30,  0x30,  0x30,  0x31}; // "03000001"
	FILE * fp = NULL;
	int ret = NO_ERROR;
	unsigned long size = -1;

	*security_info = (security_info_t *) malloc(sizeof(security_info_t));
	if (*security_info == NULL) {
		printf("Alloc memory for security info failed., errno=%d\n", errno);
		return -ENOMEM;
	}

	(*security_info)->fd = -1;
	(*security_info)->result_list = NULL;
	(*security_info)->upload_list = NULL;

	ret = file_get_size(UUID_PATH, &size);
	if (ret == NO_ERROR && size == 9) {
		fp = fopen(UUID_PATH, "r");
		if (fp != NULL) {
			file_read_data(userid, fp, 8);
			printf("%s: userid = %llx.\n", __func__, *(uint64_t *)userid);
			fclose(fp);
		}
	}

	memcpy(&(*security_info)->serial, userid, 8);

	memcpy((*security_info)->auth_x509_path, SECURITY_AUTH_X509_PATH, sizeof(SECURITY_AUTH_X509_PATH));

	pthread_mutex_init(&(*security_info)->lock, NULL);
	pthread_cond_init(&(*security_info)->cond, NULL);
	pthread_mutex_init(&(*security_info)->upload_lock, NULL);
	pthread_cond_init(&(*security_info)->upload_cond, NULL);

	return NO_ERROR;
}

void release_security(security_info_t ** security_info)
{
	security_info_t *info;
	//pthread_join(upload_thread, NULL);
	//pthread_join(read_thread, NULL);

	if (security_info == NULL || *security_info == NULL)
		return;

	info = *security_info;

	pthread_mutex_destroy(&info->lock);
	pthread_cond_destroy(&info->cond);
	pthread_mutex_destroy(&info->upload_lock);
	pthread_cond_destroy(&info->upload_cond);

	/* free all pending result here */
	if (info->result_list != NULL) {
		security_result_list_t *result_list = info->result_list;
		security_result_list_t *result_list_next;
		while (result_list != NULL) {
			result_list_next = result_list->next;
			free(result_list->result.payload);
			free(result_list);
			result_list = result_list_next;
		}
	}

	free(info);
	info = NULL;
}

void test_security(security_info_t * pr)
{

/*
	int ret = NO_ERROR;
	security_info_t *pr = NULL;
	firmware_version_param param;
	serial_num_param ser_num;
	repeat_read_param re_re;
	filtr_interv_param fi_in;
	part_info_param part_ino;
	uint64_t sec_rand;
	perm_table_param perm_table;
	work_mode_param *work_mode = NULL;
*/
	work_mode_param *setup_work_mode = NULL;

	//ret = alloc_security(&pr);
	//if (ret != NO_ERROR)
	//  return;

	//ret = start_security(pr);
#if 0
	printf("****************set_rtc*********************************\n");
	security_set_rtc(pr);
	printf("*****************get_rtc********************************\n");
	security_get_rtc(pr);
	printf("************************get_firmware_version*************************\n");

	ret = security_get_firmware_version(pr, &param);
	if (ret == NO_ERROR)
		printf
			("get_firmware_version: type=%x, hw_ver=%x, ctrl_boot_ver=%x, encry_boot_ver=%x, ctrl_ver=%x, encry1_ver=%x, encry2_ver=%x.\n",
			 param.type, param.hw_ver, param.ctrl_boot_ver, param.encry_boot_ver, param.ctrl_ver,
			 param.encry1_ver, param.encry2_ver);

	printf("*********************get_serial_number****************************\n");
	ret = security_get_serial_number(pr, &ser_num);
	if (ret == NO_ERROR)
		printf("get_serial_number: type=%x, ser_num=%lx.\n", ser_num.type,
			   (unsigned long)ser_num.serial_num);
	printf("********************get_repeat_read_flag*****************************\n");

	ret = security_get_repeat_read_flag(pr, &re_re);
	if (ret == NO_ERROR)
		printf("get_repeat_read_flag: type=%x, flag=%x.\n", re_re.type, re_re.flag);
#endif
	printf("***********************set_work_mode**************************\n");
	part_info_param part1;
	part_info_param part2;
	memset(&part1, 0, PART_INFO_PARAM_SIZE);
	memset(&part2, 0, PART_INFO_PARAM_SIZE);
	part1.part_no = 0;
	part1.part_indi = 1;
	part1.ciphertext = 1;
	part1.high_speed = 0;
	part1.read_index = 0;
	part1.read_len = 122;
	part2.part_no = 2;
	part2.part_indi = 2;
	part2.ciphertext = 0;
	part2.high_speed = 1;
	part2.read_index = 0;
	part2.read_len = 234;
#if 0
	setup_work_mode = (work_mode_param *) malloc(2 + 2 * 7);
	setup_work_mode->num = 2;
	memcpy(setup_work_mode->data, (void *)&part1, 7);
	memcpy(setup_work_mode->data + 7, (void *)&part2, 7);
#else
	setup_work_mode = (work_mode_param *) malloc(1);
	setup_work_mode->num = 0;
#endif
	security_set_work_mode(pr, setup_work_mode);
	free(setup_work_mode);
#if 0
	printf("*********************get_work_mode****************************\n");
	work_mode = security_get_work_mode(pr);
	if (work_mode != NULL) {
		printf("get_work_mode: num=%x\n", work_mode->num);
		free(work_mode);
	}
	printf("*********************get_filtr_interv****************************\n");

	ret = security_get_filtr_interv(pr, &fi_in);
	if (ret == NO_ERROR) {
		printf("get_filtr_interv: type=%x, interval=%d.\n", fi_in.type, fi_in.interval);
	}

	printf("*********************set_repeat_read****************************\n");
	ret = security_set_repeat_read(pr, 0);
	if (ret == NO_ERROR)
		printf("set_repeat_read success\n");
	else
		printf("set_repeat_read failed\n");

	printf("*********************set_filtr_interv****************************\n");

	ret = security_set_filtr_interv(pr, 2000);

	printf("*********************get_filtr_interv again****************************\n");

	ret = security_get_filtr_interv(pr, &fi_in);
	if (ret == NO_ERROR) {
		printf("get_filtr_interv again: type=%x, interval=%d.\n", fi_in.type, fi_in.interval);
	}

	printf("********************get rand num*****************************\n");
	sec_rand = security_request_rand_num(pr);
	if (ret == NO_ERROR) {
		printf("get_rand_num: %llx\n", sec_rand);

		for (i = 0; i < 8; i++)
			printf("%4x", *((uint8_t *) & sec_rand + i));

		printf("\n");
	}
#endif
	printf("********************END*****************************\n");
}

int security_main(security_info_t * info)
{
	printf("Enter security_main.\n");
	test_security(info);
	printf("Exit security_main.\n");
	return 0;
}
