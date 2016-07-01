
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

#include <uhf.h>

/* ---------- ---------- */

/* ---------- helper function ---------- */

/* TODO: fill the string */
const char *radio_cmd_to_string(uint16_t command)
{
	switch (command) {
	  case SET_VERSION:
		  return "";
	  case GET_VERSION:
		  return "";
	  case SET_TRANS_POWER:
		  return "";
	  case GET_TRANS_POWER:
		  return "";
	  case SET_FHSS_ENABLE:
		  return "";
	  case GET_FHSS_ENABLE:
		  return "";
	  case SET_TRANS_FREQ_RANGE:
		  return "";
	  case GET_TRANS_FREQ_RANGE:
		  return "";
	  case SET_REVER_CHAN_RATE:
		  return "";
	  case GET_REVER_CHAN_RATE:
		  return "";
	  case SET_REVER_CODE_MODE:
		  return "";
	  case GET_REVER_CODE_MODE:
		  return "";
	  case SET_ANTENNA_ATTR:
		  return "";
	  case GET_ANTENNA_ATTR:
		  return "";
	  case SET_ANTENNA_GAIN:
		  return "";
	  case GET_ANTENNA_GAIN:
		  return "";
	  case SET_CARR_ENABLE:
		  return "";
	  case GET_CARR_ENABLE:
		  return "";
	  case SET_FPGA_THRESH:
		  return "";
	  case GET_FPGA_THRESH:
		  return "";
	  case SET_ANTI_COLL_PROTO:
		  return "";
	  case GET_ANTI_COLL_PROTO:
		  return "";
	  case SET_Q_VALUE:
		  return "";
	  case GET_Q_VALUE:
		  return "";
	  case SET_MODUL_MODE:
		  return "";
	  case GET_MODUL_MODE:
		  return "";
	  case SET_TC_VALUE:
		  return "";
	  case GET_TC_VALUE:
		  return "";
	  case SET_SJC_VALUE:
		  return "";
	  case GET_SJC_VALUE:
		  return "";
	  case SIGNAL_CHECK:
		  return "";
	  case START_CONTI_CHECK:
		  return "";
	  case STOP_CONTI_CHECK:
		  return "";
	  case SET_WRITE_TAG:
		  return "";
	  case GET_RADIO_PARAM:
		  return "";
	  case SET_DIG_ATTEN:
		  return "";
	  case GET_DIG_ATTEN:
		  return "";
	  case SET_PA_ENABLE:
		  return "";
	  case GET_PA_ENABLE:
		  return "";
	  case START_RADIO_WORK:
		  return "";
	  case STOP_RADIO_WORK:
		  return "";
	  case REBOOT_RADIO_MODULE:
		  return "";
	  case REQ_RADIO_UPGRADE:
		  return "";
	  case MID_UPGRADE_PACK:
		  return "";
	  case LAST_UPGRADE_PACK:
		  return "";
	  default:
		  return "";
	}

	return "";
}

/* Initialize UART driver */
int init_uart(char *dev)
{
	int fd;
	struct termios ti;

	printf("Init the uart port %s\n", dev);

	fd = open(dev, O_RDWR | O_NOCTTY);
	if (fd < 0) {
		perror("Can't open serial port");
		return -FAILED;
	}

	tcflush(fd, TCIOFLUSH);

	if (tcgetattr(fd, &ti) < 0) {
		perror("Can't get port settings");
		goto fail;
	}

	cfmakeraw(&ti);				// make new setting

	/* setup speed */
	cfsetispeed(&ti, B115200);
	cfsetospeed(&ti, B115200);

	ti.c_cflag |= CLOCAL;
	ti.c_cflag &= ~CRTSCTS;		// have no flow control

	/* data size is 8bit */
	ti.c_cflag &= ~CSIZE;
	ti.c_cflag |= CS8;

	/* no checking bit */
	ti.c_cflag &= ~PARENB;		// Clear parity enable
	ti.c_iflag &= ~INPCK;		// Enable parity checking
	ti.c_iflag &= ~(ICRNL | IGNCR);
	ti.c_lflag &= ~(ICANON);

	/* 1bit stopbits */
	ti.c_cflag &= ~CSTOPB;

	ti.c_cc[VTIME] = 50;		// 5 seconds for transfer timeout
	ti.c_cc[VMIN] = 0;

	/* Update the options and do it NOW */
	tcflush(fd, TCIFLUSH);
	if (tcsetattr(fd, TCSANOW, &ti) != 0) {
		perror("Setup serial failed");
		goto fail;
	}

	printf("uart setup complete\n");

	return fd;

  fail:
	close(fd);
	return -FAILED;
}

void close_uart(int fd)
{
	close(fd);
	fd = -1;
}

void inline lock_radio(pthread_mutex_t * lock)
{
	pthread_mutex_lock(lock);
}

void inline unlock_radio(pthread_mutex_t * lock)
{
	pthread_mutex_unlock(lock);
}

int radio_wait_result(radio_info_t * radio_info, uint8_t cmd, radio_result_t * result)
{
	int ret = NO_ERROR;
	int resultReceived = 0;
	struct timeval now;
	struct timespec outtime;

	while (!resultReceived) {
		gettimeofday(&now, NULL);
		outtime.tv_sec = now.tv_sec + RADIO_TIMEOUT;
		outtime.tv_nsec = now.tv_usec * 1000;
		ret = pthread_cond_timedwait(&radio_info->c_cond, &radio_info->c_lock, &outtime);
		if (ret == ETIMEDOUT) {
			//printf("%s: timeout for cmd %x\n", __func__, cmd);
			return ret;
		} else
			ret = NO_ERROR;
		if (radio_info->result_list != NULL) {
			radio_result_list_t *result_list = radio_info->result_list;
			radio_result_list_t *result_list_prev = radio_info->result_list;
			while (result_list != NULL) {
				if (result_list->result.hdr.cmd == cmd) {
					resultReceived = 1;
					*result = result_list->result;
					//radio_print_result(*result);
					result_list_prev->next = result_list->next;
					if (result_list == radio_info->result_list) {
						radio_info->result_list = result_list->next;
					}
					free(result_list);
					result_list = NULL;
					break;
				} else {
					/* TODO: maybe need to precess this event */
					result_list_prev = result_list;
					result_list = result_list->next;
				}
			}
		}
	}

	return ret;
}

void radio_signal_result(radio_info_t * radio_info, radio_result_t * result)
{
	lock_radio(&radio_info->c_lock);

	radio_result_list_t *curr_result = (radio_result_list_t *) malloc(sizeof(radio_result_list_t));
	if (curr_result == NULL) {
		printf("ERROR: malloc for radio result failed, Result will not be sent\n");
		goto malloc_failed;
	}
	curr_result->result = *result;
	curr_result->next = NULL;

	if (radio_info->result_list == NULL)
		radio_info->result_list = curr_result;
	else {
		radio_result_list_t *result_list = radio_info->result_list;
		while (result_list->next != NULL)
			result_list = result_list->next;
		result_list->next = curr_result;
	}

  malloc_failed:
	pthread_cond_broadcast(&radio_info->c_cond);
	unlock_radio(&radio_info->c_lock);
}

uint16_t inline conv_type16(uint16_t value)
{
	return (value >> 8) | ((value << 8) & 0xFF00);
}

/*
uint32_t inline conv_type32(uint32_t value)
{
	uint32_t ret = 0;
	uint8_t tmp = 0;
	int i;

	for (i = 0; i < 4; i++) {
		tmp = value >> i * 8;
		ret = ret | ((uint32_t)tmp << ((4 - i) * 8));
	}
	return ret;
}
*/

uint16_t calc_crc16(radio_pack_hdr * hdr, uint8_t * payload)
{
	uint16_t len = conv_type16(hdr->len);
	uint8_t *p = (uint8_t *) malloc(RADIO_PACK_HDR_SIZE + len);
	uint8_t *p_t = p;
	uint16_t shift, data, val;
	int i;

	memcpy(p, hdr, RADIO_PACK_HDR_SIZE);
	if (payload != NULL)
		memcpy(p + RADIO_PACK_HDR_SIZE, payload, len);

	shift = 0xFFFF;

	for (i = 0; i < (RADIO_PACK_HDR_SIZE + len) * 8; i++) {
		if ((i % 8) == 0)
			data = (*p++) << 8;
		val = shift ^ data;
		shift = shift << 1;
		data = data << 1;
		if (val & 0x8000)
			shift = shift ^ 0x1021;
	}

	free(p_t);
	p_t = NULL;
	return (uint16_t) (~shift);
}

uint16_t calc_crc16_1(uint8_t * p, int len)
{
	uint16_t shift, data, val;
	int i;

	shift = 0xFFFF;

	for (i = 0; i < (len - 3) * 8; i++) {
		if ((i % 8) == 0)
			data = (*p++) << 8;
		val = shift ^ data;
		shift = shift << 1;
		data = data << 1;
		if (val & 0x8000)
			shift = shift ^ 0x1021;
	}

	return (uint16_t) (~shift);
}

int radio_read(radio_info_t * radio_info, radio_result_t * rsp)
{
	int nrd;
	int ret = -FAILED;
	int fd = radio_info->fd;
	uint8_t *data = radio_info->data;
	uint8_t *temp;
	uint16_t len = 0;
	uint16_t type = 0;
	//int i = 0;

	//printf("%s: +\n", __func__);

	nrd = read(fd, data, RADIO_MTU);
	temp = data;

/*
	for (i = 0; i < nrd; i++) {
		printf("%4x", data[i]);
	}
	printf("\n");
*/
	if (nrd >= RADIO_PACK_HDR_SIZE + RADIO_PACK_END_SIZE) {
		memcpy(&rsp->hdr, temp, RADIO_PACK_HDR_SIZE);
		len = conv_type16(rsp->hdr.len);
		//printf("rsp->hdr.len=%x, len=%x.\n", rsp->hdr.len, len);
		type = conv_type16(rsp->hdr.type);
		if (nrd == len + RADIO_PACK_HDR_SIZE + RADIO_PACK_END_SIZE) {
			temp += RADIO_PACK_HDR_SIZE;
			rsp->payload = NULL;
			if (len != 0) {
				rsp->payload = (uint8_t *) malloc(len);	/* free in main thread */
				memcpy(rsp->payload, temp, len);
				temp += len;
			}
			memcpy(&rsp->end, temp, RADIO_PACK_END_SIZE);

			//radio_print_result(*rsp);

			rsp->end.crc16 = conv_type16(rsp->end.crc16);

			if (rsp->end.crc16 != calc_crc16_1(data, nrd)) {
				printf("%s: crc by read:%x, crc by calc:%x\n", __func__,
					   rsp->end.crc16, calc_crc16_1(data, nrd));
				if (rsp->hdr.len != 0) {
					free(rsp->payload);
					rsp->payload = NULL;
				}
			} else {
				rsp->hdr.len = len;
				rsp->hdr.type = type;
				ret = NO_ERROR;
			}
		} else {
			printf("%s: oops, nrd=%d, payload len=%d.\n", __func__, nrd, rsp->hdr.len);
			free(rsp->payload);
			rsp->payload = NULL;
		}
	} else {
		printf("%s: read data is too few, nrd=%d, data[0]:%x.\n", __func__, nrd, *data);
	}

	//printf("%s: -, nrd=%d\n", __func__, nrd);
	return ret;
}

int radio_write(radio_info_t * radio_info, uint8_t cmd, uint16_t len, uint8_t * payload)
{
	//int i;
	int nwt;
	int ret = NO_ERROR;
	radio_pack_hdr hdr;
	radio_pack_end end;
	uint8_t *data = radio_info->data;
	uint16_t total_len = RADIO_PACK_HDR_SIZE + RADIO_PACK_END_SIZE + len;

	//printf("radio_write +\n");

	if (total_len > RADIO_MTU) {
		printf("%s: payload is too long.\n", __func__);
		return -FAILED;
	}

	if (radio_info->flashing == true)
		if (cmd != REQ_RADIO_UPGRADE && cmd != MID_UPGRADE_PACK && cmd != LAST_UPGRADE_PACK) {
			printf("%s: can't send cmd 0x%x, radio is flashing...\n", __func__, cmd);
			return -FAILED;
		}

	hdr.hdr = PACK_HDR;
	hdr.type = REQUEST_TYPE;
	hdr.cmd = cmd;
	hdr.len = conv_type16(len);

	end.crc16 = calc_crc16(&hdr, payload);
	end.crc16 = conv_type16(end.crc16);
	//printf("%s : crc16 = %x\n", __func__, end.crc16);
	end.end = PACK_END;

	memcpy(data, (uint8_t *) & hdr, RADIO_PACK_HDR_SIZE);
	data += RADIO_PACK_HDR_SIZE;
	if (payload != NULL && len != 0) {
		memcpy(data, payload, len);
		data = data + len;
	}
	memcpy(data, &end, RADIO_PACK_END_SIZE);

/*
	printf("Before send: ");
	for (i = 0; i < total_len; i++)
		printf("%4x", *(radio_info->data + i));
	printf("\n");
*/
	nwt = write(radio_info->fd, radio_info->data, total_len);

	if (nwt < 0) {
		printf("write failed\n");
		ret = nwt;
	} else if (nwt != total_len) {
		printf("write failed, nwt=%d, total_len=%d\n", nwt, total_len);
		ret = -FAILED;
	}
//  printf("nwt=%d\n", nwt);
//  printf("radio_write -\n");
	return ret;
}

void *radio_read_loop(void *data)
{
	radio_info_t *radio_info = (radio_info_t *) data;
	fd_set fds;
	radio_result_t rsp;
	int maxfdp;
	int ret;

	printf("Enter radio_read_loop...\n");

	while (true) {
		FD_ZERO(&fds);
		FD_SET(radio_info->fd, &fds);

		maxfdp = radio_info->fd + 1;

		memset(&rsp, 0, sizeof(radio_result_t));
		/* TODO: error process */
		ret = select(maxfdp, &fds, NULL, NULL, NULL);
		if (ret <= 0) {
			printf("radio_reader_loop: select error, ret = %d\n", ret);
			return NULL;
		} else if (FD_ISSET(radio_info->fd, &fds)) {
			ret = radio_read(radio_info, &rsp);
			if (ret != NO_ERROR) {
				printf("read failed\n");
				if (rsp.payload != NULL) {
					free(rsp.payload);
					rsp.payload = NULL;
				}
			} else {
				radio_signal_result(radio_info, &rsp);
			}
		}
	}
}

int radio_set_version(radio_info_t * radio_info)
{
	int ret = NO_ERROR;
	version_param version;
	radio_result_t result;

	printf("Enter radio_set_version\n");

	memset(&result, 0, sizeof(radio_result_t));

	version.hw_version[0] = 0x12;
	version.hw_version[1] = 0x00;
	version.hw_version[2] = 0x56;
	version.sw_version[0] = 0x00;
	version.sw_version[1] = 0x45;
	version.sw_version[2] = 0x67;

	lock_radio(&radio_info->c_lock);

	ret = radio_write(radio_info, SET_VERSION, VERSION_PARAM_SIZE, (uint8_t *) & version);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("Set version failed!\n");
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, SET_VERSION, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload != NULL) {
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	}

	printf("Exit radio_set_version\n");

	return ret;
}

int radio_get_version(radio_info_t * radio_info)
{
	int ret = NO_ERROR;
	//version_param version;
	radio_result_t result;
	uint8_t dummy = 0;

	printf("%s: Enter\n", __func__);

	memset(&result, 0, sizeof(radio_result_t));

	lock_radio(&radio_info->c_lock);

	ret = radio_write(radio_info, GET_VERSION, 1, &dummy);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("Set version failed!\n");
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, GET_VERSION, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload != NULL) {
		/* TODO: save this version */
		free(result.payload);
		result.payload = NULL;
	}

	printf("%s: Exit\n", __func__);

	return ret;
}

int radio_update_firmware(radio_info_t * info)
{
	int ret = NO_ERROR;
	radio_result_t result;
	uint8_t *buf;
	uint8_t *temp;
	uint16_t num_block;
	uint16_t block_size;
	uint32_t file_size_read;
	uint8_t status = 0;
	unsigned long file_size = 0;
	FILE *fp = NULL;
	int i;
	uint16_t flag;

	memset(&result, 0, sizeof(radio_result_t));

	ret = file_get_size(RADIO_FW_DEFAULT_PATH, &file_size);
	if (file_size <= 0) {
		printf("%s: can't get %s size, ret = %d.\n", __func__, RADIO_FW_DEFAULT_PATH, ret);
		return -FAILED;
	}

	printf("%s: file size = %ld.\n", __func__, file_size);

	buf = (uint8_t *) malloc(file_size);
	if (buf == NULL)
		return -ENOMEM;

	fp = fopen(RADIO_FW_DEFAULT_PATH, "r");
	fseek(fp, 0L, SEEK_SET);
	ret = file_read_data(buf, fp, file_size);
	if (ret != NO_ERROR) {
		printf("%s: read firmware failed.\n", __func__);
		free(buf);
		fclose(fp);
		return ret;
	}
	fclose(fp);

	file_size_read = *(uint32_t *) (buf + 1);
	block_size = *(uint16_t *) (buf + 9);

	if (file_size_read != (uint32_t) file_size) {
		printf("%s: size not match, read: %x, size:%x.\n", __func__, file_size_read,
			   (uint32_t) file_size);
		free(buf);
		return -FAILED;
	}

	flag = file_size_read % block_size;

	if (flag)
		num_block = file_size_read / block_size + 1;
	else {
		num_block = file_size_read / block_size;
		flag = block_size;
	}

	security_reset_radio(((uhf_info_t *) (info->uhf))->radio->fd);
	//sleep(1);
	while (security_get_radio_status(((uhf_info_t *) (info->uhf))->radio->fd)) ;

	lock_radio(&info->c_lock);

	info->flashing = true;

	printf("%s: num_block = %u.\n", __func__, num_block);
	/* 1.request upgrade */
	ret = radio_write(info, REQ_RADIO_UPGRADE, 0, NULL);
	if (ret != NO_ERROR) {
		printf("request radio upgrade failed.\n");
		goto out;
	}

	ret = radio_wait_result(info, REQ_RADIO_UPGRADE, &result);
	if (ret == NO_ERROR && result.payload != NULL) {
		status = *result.payload;
		free(result.payload);
	} else {
		printf("REQ_RADIO_UPGRADE result payload is null.\n");
		status = FAILED;
		//goto out;
	}

	if (status != NO_ERROR) {
		printf("REQ_RADIO_UPGRADE result is %x.\n", status);
//      goto out;
	}

	temp = buf;

	/* 2. begin upgrade */
	for (i = 0; i < num_block - 1; i++) {
		printf("%s: loop %d ...\n", __func__, i);
		ret = radio_write(info, MID_UPGRADE_PACK, block_size, temp);
		if (ret != NO_ERROR)
			goto out;

		memset(&result, 0, sizeof(radio_result_t));
		ret = radio_wait_result(info, MID_UPGRADE_PACK, &result);
		if (ret == NO_ERROR && result.payload != NULL) {
			status = *result.payload;
			free(result.payload);
		} else {
			printf("MID_UPGRADE_PACK result payload is null");
			//goto out;
		}

		temp = temp + block_size;
	}

	memset(&result, 0, sizeof(radio_result_t));

	/* 3. last package */
	ret = radio_write(info, LAST_UPGRADE_PACK, flag, temp);
	if (ret != NO_ERROR)
		goto out;

	ret = radio_wait_result(info, LAST_UPGRADE_PACK, &result);
	if (ret == NO_ERROR && result.payload != NULL) {
		ret = *result.payload;
		free(result.payload);
	}

  out:
	info->flashing = false;
	free(buf);
	unlock_radio(&info->c_lock);
	return ret;
}

int radio_set_fhss(radio_info_t * radio_info, uint8_t enable)
{
	int ret = NO_ERROR;
	radio_result_t result;
	fhss_enable_param fhss;

	printf("%s +\n", __func__);

	fhss.enable = enable;

	memset(&result, 0, sizeof(radio_result_t));

	lock_radio(&radio_info->c_lock);

	ret = radio_write(radio_info, SET_FHSS_ENABLE, FHSS_ENABLE_PARAM_SIZE, (uint8_t *) & fhss);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("set fhss failed!\n");
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, SET_FHSS_ENABLE, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload) {
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	}

	printf("%s -\n", __func__);
	return ret;
}

int radio_set_antenna_attr(radio_info_t * radio_info, uint8_t attr)
{
	int ret = NO_ERROR;
	radio_result_t result;
	antenna_attr_param antenna_attr;

	printf("%s +\n", __func__);

	memset(&result, 0, sizeof(radio_result_t));

	antenna_attr.attribute = attr;

	lock_radio(&radio_info->c_lock);

	ret =
		radio_write(radio_info, SET_ANTENNA_ATTR, ANTENNA_ATTR_PARAM_SIZE,
					(uint8_t *) & antenna_attr);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("%s write failed!\n", __func__);
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, SET_ANTENNA_ATTR, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload != NULL) {
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	}

	printf("%s -\n", __func__);
	return ret;
}

int radio_start_conti_check(radio_info_t * radio_info)
{
	int ret = NO_ERROR;
	radio_result_t result;
	uint8_t dummy = 0;

	printf("%s +\n", __func__);

	memset(&result, 0, sizeof(radio_result_t));

	lock_radio(&radio_info->c_lock);

	ret = radio_write(radio_info, START_CONTI_CHECK, 1, (uint8_t *) & dummy);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("%s write failed!\n", __func__);
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, START_CONTI_CHECK, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload != NULL) {
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	}

	printf("%s -\n", __func__);
	return ret;
}

int radio_stop_conti_check(radio_info_t * radio_info)
{
	int ret = NO_ERROR;
	radio_result_t result;
	uint8_t dummy = 0;

	printf("%s +\n", __func__);

	memset(&result, 0, sizeof(radio_result_t));

	lock_radio(&radio_info->c_lock);

	ret = radio_write(radio_info, STOP_CONTI_CHECK, 1, (uint8_t *) & dummy);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("%s write failed!\n", __func__);
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, STOP_CONTI_CHECK, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload != NULL) {
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	}

	printf("%s -\n", __func__);
	return ret;
}

int radio_set_dig_atten(radio_info_t * radio_info, uint8_t attenuation)
{
	int ret = NO_ERROR;
	radio_result_t result;
	dig_atten_param dig_atten;

	printf("%s +\n", __func__);

	dig_atten.attenuation = attenuation;

	memset(&result, 0, sizeof(radio_result_t));

	lock_radio(&radio_info->c_lock);

	ret = radio_write(radio_info, SET_DIG_ATTEN, DIG_ATTEN_PARAM_SIZE, (uint8_t *) & dig_atten);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("%s write failed!\n", __func__);
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, SET_DIG_ATTEN, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload != NULL) {
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	}

	printf("%s -\n", __func__);
	return ret;
}

int radio_set_carr(radio_info_t * radio_info, uint8_t enable)
{
	int ret = NO_ERROR;
	radio_result_t result;
	carr_enable_param carr_enable;

	printf("%s +\n", __func__);

	carr_enable.enable = enable;
	lock_radio(&radio_info->c_lock);

	memset(&result, 0, sizeof(radio_result_t));

	ret =
		radio_write(radio_info, SET_CARR_ENABLE, CARR_ENABLE_PARAM_SIZE, (uint8_t *) & carr_enable);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("%s write failed!\n", __func__);
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, SET_CARR_ENABLE, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload != NULL) {
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	}

	printf("%s -\n", __func__);
	return ret;
}

int radio_get_status(radio_info_t * radio_info)
{
	int ret = NO_ERROR;
	radio_result_t result;
	uint8_t dummy = 0;

	memset(&result, 0, sizeof(radio_result_t));

	lock_radio(&radio_info->c_lock);

	ret = radio_write(radio_info, GET_RADIO_STATUS, 1, (uint8_t *) & dummy);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("%s write failed!\n", __func__);
		return -FAILED;
	}

	ret = radio_wait_result(radio_info, GET_RADIO_STATUS, &result);

	unlock_radio(&radio_info->c_lock);

	if (result.payload != NULL) {
		ret = *result.payload;
		free(result.payload);
		result.payload = NULL;
	}

	return ret;
}

int radio_send_heartbeat(radio_info_t * info)
{
	return radio_get_status(info);
}

int start_radio(radio_info_t * radio_info)
{
	int ret;
	pthread_attr_t attr;

	assert(radio_info != NULL);

	radio_info->fd = init_uart(RADIO_PORT);
	if (radio_info->fd < 0) {
		printf("Init uart failed.\n");
		return -FAILED;
	}

	printf("fd = %d.\n", radio_info->fd);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	ret = pthread_create(&radio_info->read_thread, &attr, radio_read_loop, (void *)radio_info);
	if (ret < 0) {
		printf("create reader thread failed.\n");
		goto create_thread_failed;
	}

	printf("Start radio successfully...\n");

	return NO_ERROR;

  create_thread_failed:
	close_uart(radio_info->fd);
	return -FAILED;
}

void stop_radio(radio_info_t * radio_info)
{
	void *ret;
	if (radio_info == NULL)
		return;

	pthread_cancel(radio_info->read_thread);
	pthread_join(radio_info->read_thread, &ret);
	close_uart(radio_info->fd);
}

int alloc_radio(radio_info_t ** radio_info)
{
	*radio_info = (radio_info_t *) malloc(sizeof(radio_info_t));
	if (radio_info == NULL) {
		printf("Alloc memory for radio info failed., errno=%d\n", errno);
		return -FAILED;
	}

	(*radio_info)->fd = -1;
	(*radio_info)->result_list = NULL;
	(*radio_info)->heartbeats_periodic = RADIO_DEFAULT_HEARTBEATS_PERIODIC;
	(*radio_info)->flashing = false;

	pthread_mutex_init(&(*radio_info)->c_lock, NULL);
	pthread_cond_init(&(*radio_info)->c_cond, NULL);

	return NO_ERROR;
}

void release_radio(radio_info_t ** radio_info)
{
	radio_info_t *info;
	if (radio_info == NULL || *radio_info == NULL)
		return;

	info = *radio_info;

	pthread_mutex_destroy(&info->c_lock);
	pthread_cond_destroy(&info->c_cond);

	/* free all pending api result here */
	if (info->result_list != NULL) {
		radio_result_list_t *result_list = info->result_list;
		radio_result_list_t *result_list_next;
		while (result_list != NULL) {
			result_list_next = result_list->next;
			free(result_list);
			result_list = result_list_next;
		}
	}

	free(info);
	info = NULL;
}

void radio_print_result(radio_result_t result)
{
	int i;
	uint16_t len = conv_type16(result.hdr.len);
	printf("\n===============================\n");
	printf("hdr:%x, type:%x, cmd:%x, len:%x\n", result.hdr.hdr, result.hdr.type, result.hdr.cmd,
		   result.hdr.len);
	printf("payload: ");
	for (i = 0; i < len; i++) {
		printf("%4x", result.payload[i]);
	}
	printf("\ncrc16:%x, end:%x\n", result.end.crc16, result.end.end);
	printf("\n===============================\n");
}

int radio_write_test(radio_info_t * radio_info)
{
	int ret = NO_ERROR;
	//uint8_t buf[4];
	radio_result_t result;

	printf("Enter %s\n", __func__);

/*
	buf[0] = 0xCC;
	buf[1] = 0xDD;
	buf[2] = 0xEE;
	buf[3] = 0xAC;
*/
	lock_radio(&radio_info->c_lock);

	ret = radio_write(radio_info, 0, 0, NULL);
	if (ret != NO_ERROR) {
		unlock_radio(&radio_info->c_lock);
		printf("write test cmd failed!\n");
		return -FAILED;
	}

	radio_wait_result(radio_info, 0, &result);

	//radio_print_result(result);
	free(result.payload);
	result.payload = NULL;

	unlock_radio(&radio_info->c_lock);

	printf("Exit %s\n", __func__);

	return ret;
}

int test_radio(radio_info_t * pr)
{
	int ret;
//    radio_info_t *pr = NULL;

	//  ret = alloc_radio(&pr);
	//if (ret != NO_ERROR)
	//    return -FAILED;

	//ret = start_radio(pr);
	//if (ret < 0) {
	//  goto test_fail;
	//}

	ret = radio_write_test(pr);

	ret = radio_get_status(pr);
	/* set version */
	//radio_set_version(pr);

	/* disable fhss */
	//radio_set_fhss(pr, false);

//  ret = radio_set_conti_check(pr);
	/* enable no.4 antenna */
	//radio_set_antenna_attr(pr, NO_TO_ATTR(4));

	//radio_set_dig_atten(pr, 0x3C);

	/* disable carrier wave */
	//radio_set_carr(pr, false);
	return ret;
//  test_fail:
//  stop_radio(pr);
//  release_radio(&pr);
//  return ret;
}

int radio_main(radio_info_t * info)
{
	test_radio(info);
	return 0;
}
