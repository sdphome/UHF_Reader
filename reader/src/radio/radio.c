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

#include "radio.h"

/* ---------- ---------- */

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

    cfmakeraw(&ti);  // make new setting

    /* setup speed */
    cfsetispeed(&ti, B115200);
    cfsetospeed(&ti, B115200);

    ti.c_cflag |= CLOCAL;
    ti.c_cflag &= ~CRTSCTS; // have no flow control

    /* data size is 8bit */
    ti.c_cflag &= ~CSIZE;
    ti.c_cflag |= CS8;

    /* no checking bit */
    ti.c_cflag &= ~PARENB; // Clear parity enable
    ti.c_iflag &= ~INPCK; // Enable parity checking
    ti.c_iflag &= ~(ICRNL|IGNCR);
    ti.c_lflag &= ~(ICANON );

    /* 1bit stopbits */
    ti.c_cflag &= ~CSTOPB;

    ti.c_cc[VTIME] = 50; // 5 seconds for transfer timeout
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

void inline lock_radio(pthread_mutex_t *lock)
{
    pthread_mutex_lock(lock);
}

void inline unlock_radio(pthread_mutex_t *lock)
{
    pthread_mutex_unlock(lock);
}

void radio_wait_result(radio_info_t *radio_info, uint8_t cmd, radio_result_t *result)
{
    int resultReceived = 0;

    while  (!resultReceived) {
        /* FIXME: It may need a timeout */
        pthread_cond_wait(&radio_info->c_cond, &radio_info->c_lock);
        if (radio_info->result_list != NULL) {
            radio_result_list_t *result_list = radio_info->result_list;
            radio_result_list_t *result_list_prev = radio_info->result_list;
            while (result_list != NULL) {
                if (result_list->result.hdr.cmd == cmd) {
                    resultReceived = 1;
                    *result = result_list->result;
                    radio_print_result(*result);
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
}

void radio_signal_result(radio_info_t *radio_info, radio_result_t *result)
{
    lock_radio(&radio_info->c_lock);

    radio_result_list_t *curr_result = (radio_result_list_t *)malloc(sizeof(radio_result_list_t));
    if (curr_result == NULL) {
        printf("ERROR: malloc for radio result failed, Result will not be sent\n");
        goto malloc_failed;
    }
    curr_result->result = *result;
    curr_result->next = NULL;

    if (radio_info->result_list == NULL) radio_info->result_list = curr_result;
    else {
        radio_result_list_t *result_list = radio_info->result_list;
        while (result_list != NULL) result_list = result_list->next;
        result_list->next = curr_result;
    }

malloc_failed:
    pthread_cond_broadcast(&radio_info->c_cond);
    unlock_radio(&radio_info->c_lock);
}

uint16_t calc_crc16(radio_pack_hdr *hdr, uint8_t *payload)
{
    uint16_t crc16;
    uint8_t temp;
    uint8_t *th= (uint8_t *)hdr;
    int i, j;

    for (i = 0; i < RADIO_PACK_HDR_SIZE; i ++) {
        crc16 ^= th[i];
        for (j = 0; j < 8; j ++) {
            temp = crc16 & 0x0001;
            crc16 = crc16 >> 1;
            if (temp) crc16 ^= 0xA001;
        }
    }

    for (i = 0; i < hdr->len; i ++) {
        crc16 ^= payload[i];
        for (j = 0; j < 8; j ++) {
            temp = crc16 & 0x0001;
            crc16 = crc16 >> 1;
            if (temp) crc16 ^= 0xA001;
        }
    }

    return crc16;
}

int radio_read(int fd, radio_result_t *rsp)
{
    int nrd;
    int ret = NO_ERROR;

    /* read package header */
    nrd = read(fd, &rsp->hdr, RADIO_PACK_HDR_SIZE);
/*    if (nrd != RADIO_PACK_HDR_SIZE || rsp->hdr.hdr != PACK_HDR
        || rsp->hdr.type != RESPONSE_TYPE) {
        printf("ERROR: Read package failed, read number = %d.
                SOF:%x, TYPE:%x, cmd:%x, len:%d\n", ret, rsp->hdr.header,
                rsp->hdr.type, rsp->hdr.cmd, rsp->hdr.len);
        ret = -FAILED;
    } else {
*/
        rsp->payload = (uint8_t *)malloc(rsp->hdr.len);
        if (rsp->payload == NULL) {
            printf("Error: Malloc memory for payload failed\n.");
        } else {
            /* FIXME: maybe need a while for payload */
            nrd = read(fd, rsp->payload, rsp->hdr.len);
            nrd += read(fd, &rsp->end, RADIO_PACK_END_SIZE);
/*
            if (nrd != rsp->hdr.len + RADIO_PACK_END_SIZE || rsp->end.end != PACK_END
                || rsp->end.crc16 != calc_crc16(&rsp->hdr, rsp->payload)) {
                printf("read data/end package failed.\n");
                ret = -FAILED;
            }
*/
        }
/*
    }
*/

    return ret;
}

int radio_write(int fd, uint8_t cmd, uint16_t len, uint8_t *payload)
{
    int nwt;
    int ret = NO_ERROR;
    radio_pack_hdr hdr;
    radio_pack_end end;

    printf("radio_write +\n");

    hdr.hdr = PACK_HDR;
    hdr.type = REQUEST_TYPE;
    hdr.cmd = cmd;
    hdr.len = len;
    nwt = write(fd, &hdr, RADIO_PACK_HDR_SIZE);
    if (payload != NULL && len != 0)
        nwt += write(fd, payload, len);

    end.crc16 = calc_crc16(&hdr, payload);
    end.end = PACK_END;
    nwt += write(fd, &end, RADIO_PACK_END_SIZE);

    if (nwt != RADIO_PACK_HDR_SIZE + len + RADIO_PACK_END_SIZE) {
        printf("write failed.\n");
        ret = -FAILED;
    }

    printf("radio_write -\n");
    return ret;
}

void *radio_reader_loop(void *data)
{
    radio_info_t *radio_info = (radio_info_t *)data;
    fd_set fds;
    radio_result_t rsp;
    int maxfdp;
    int ret;

    printf("Enter radio_reader_loop...\n");

    while(true) {
        FD_ZERO(&fds);
        FD_SET(radio_info->fd, &fds);

        maxfdp = radio_info->fd + 1;

        memset(&rsp, 0, sizeof(radio_result_t));
        /* TODO: error process */
        ret = select(maxfdp, &fds, NULL, NULL, NULL);
        if (ret <= 0) {
            printf("radio_reader_loop: select error, ret = %d\n", ret);
        } else if (FD_ISSET(radio_info->fd, &fds)) {
            ret = radio_read(radio_info->fd, &rsp);
            if (ret != NO_ERROR) {
                printf("read failed\n");
                free(rsp.payload);
                rsp.payload = NULL;
            } else {
                radio_signal_result(radio_info, &rsp);
            }
/* The payload free by main thread
            if (rsp.payload != NULL) {
                free(rsp.payload);
                rsp.payload = NULL;
            }
*/
        }
    }
}

int radio_set_version(radio_info_t *radio_info)
{
    int ret = NO_ERROR;
    int fd = radio_info->fd;
    version_param version;
    radio_result_t result;

    printf("Enter radio_set_version\n");

    version.hw_version[0] = 0x12;
    version.hw_version[1] = 0x34;
    version.hw_version[2] = 0x56;
    version.sw_version[0] = 0x23;
    version.sw_version[1] = 0x45;
    version.sw_version[2] = 0x67;

    lock_radio(&radio_info->c_lock);

    ret = radio_write(fd, SET_VERSION, VERSION_PARAM_SIZE, (char *)&version);
    if (ret != NO_ERROR) {
        printf("Set version failed!\n");
        return -FAILED;
    }

    radio_wait_result(radio_info, SET_VERSION, &result);

    radio_print_result(result);
    free(result.payload);
    result.payload = NULL;

    unlock_radio(&radio_info->c_lock);

    printf("Exit radio_set_version\n");

    return ret;
}
/*
int radio_(radio_info_t *radio_info)
{
	int ret = NO_ERROR;
    int fd = radio_info->fd;
    radio_result_t result;

	printf("%s +\n", __func__);

	lock_radio(&radio_info->c_lock);

	ret = radio_write(fd, , _PARAM_SIZE, (char *)&);
    if (ret != NO_ERROR) {
        printf("%s write failed!\n", __func__);
        return -FAILED;
    }

    radio_wait_result(radio_info, , &result);

    radio_print_result(result);
    free(result.payload);
    result.payload = NULL;

    unlock_radio(&radio_info->c_lock);

	printf("%s -\n", __func__);
	return ret;
}

*/


int radio_set_fhss(radio_info_t *radio_info, uint8_t enable)
{
	int ret = NO_ERROR;
    int fd = radio_info->fd;
    radio_result_t result;
	fhss_enable_param fhss;

	printf("%s +\n", __func__);

	fhss.enable = enable;

	lock_radio(&radio_info->c_lock);

	ret = radio_write(fd, SET_FHSS_ENABLE, FHSS_ENABLE_PARAM_SIZE, (char *)&fhss);
    if (ret != NO_ERROR) {
        printf("set fhss failed!\n");
        return -FAILED;
    }

    radio_wait_result(radio_info, SET_FHSS_ENABLE, &result);

    radio_print_result(result);
    free(result.payload);
    result.payload = NULL;

    unlock_radio(&radio_info->c_lock);

	printf("%s -\n", __func__);
	return ret;
}

int radio_set_antenna_attr(radio_info_t *radio_info, uint8_t attr)
{
	int ret = NO_ERROR;
    int fd = radio_info->fd;
    radio_result_t result;
	antenna_attr_param antenna_attr;

	printf("%s +\n", __func__);

	antenna_attr.attribute = attr;

	lock_radio(&radio_info->c_lock);

	ret = radio_write(fd, SET_ANTENNA_ATTR, ANTENNA_ATTR_PARAM_SIZE, (char *)&antenna_attr);
    if (ret != NO_ERROR) {
        printf("%s write failed!\n", __func__);
        return -FAILED;
    }

    radio_wait_result(radio_info, SET_ANTENNA_ATTR, &result);

    radio_print_result(result);
    free(result.payload);
    result.payload = NULL;

    unlock_radio(&radio_info->c_lock);

	printf("%s -\n", __func__);
	return ret;
}

int radio_set_dig_atten(radio_info_t *radio_info, uint8_t attenuation)
{
	int ret = NO_ERROR;
    int fd = radio_info->fd;
    radio_result_t result;
	dig_atten_param dig_atten;

	printf("%s +\n", __func__);

	dig_atten.attenuation = attenuation;

	lock_radio(&radio_info->c_lock);

	ret = radio_write(fd, SET_DIG_ATTEN, DIG_ATTEN_PARAM_SIZE, (char *)&dig_atten);
    if (ret != NO_ERROR) {
        printf("%s write failed!\n", __func__);
        return -FAILED;
    }

    radio_wait_result(radio_info, SET_DIG_ATTEN, &result);

    radio_print_result(result);
    free(result.payload);
    result.payload = NULL;

    unlock_radio(&radio_info->c_lock);

	printf("%s -\n", __func__);
	return ret;
}

int radio_set_carr(radio_info_t *radio_info, uint8_t enable)
{
	int ret = NO_ERROR;
    int fd = radio_info->fd;
    radio_result_t result;
	carr_enable_param carr_enable;

	printf("%s +\n", __func__);

	carr_enable.enable = enable;
	lock_radio(&radio_info->c_lock);

	ret = radio_write(fd, SET_CARR_ENABLE, CARR_ENABLE_PARAM_SIZE, (char *)&carr_enable);
    if (ret != NO_ERROR) {
        printf("%s write failed!\n", __func__);
        return -FAILED;
    }

    radio_wait_result(radio_info, SET_CARR_ENABLE, &result);

    radio_print_result(result);
    free(result.payload);
    result.payload = NULL;

    unlock_radio(&radio_info->c_lock);

	printf("%s -\n", __func__);
	return ret;
}


int start_radio(radio_info_t *radio_info)
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
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    ret = pthread_create(&radio_info->read_thread, &attr, radio_reader_loop, (void *)radio_info);
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

void stop_radio(radio_info_t *radio_info)
{
    close_uart(radio_info->fd);
}

int alloc_radio(radio_info_t **radio_info)
{
    int ret;

    *radio_info = (radio_info_t *)malloc(sizeof(radio_info_t));
    if (radio_info == NULL) {
        printf("Alloc memory for radio info failed., errno=%d\n", errno);
        return -FAILED;
    }

    (*radio_info)->fd = -1;
    (*radio_info)->result_list = NULL;

    pthread_mutex_init(&(*radio_info)->c_lock, NULL);
    pthread_cond_init(&(*radio_info)->c_cond, NULL);

    return NO_ERROR;
}

void release_radio(radio_info_t *radio_info)
{
    pthread_mutex_destroy(&radio_info->c_lock);
    pthread_cond_destroy(&radio_info->c_cond);

    free(radio_info);
    radio_info = NULL;
}

void radio_print_result(radio_result_t result)
{
    int i;
    printf("===============================\n");
    printf("hdr:%x, type:%x, cmd:%x, len:%x\n", result.hdr.hdr, result.hdr.type, result.hdr.cmd, result.hdr.len);
    printf("payload: ");
    for (i = 0; i < result.hdr.len; i ++) {
        printf("%4x", result.payload[i]);
    }
    printf("\ncrc16:%x, end:%x\n", result.end.crc16, result.end.end);
    printf("===============================\n");
}

int test_radio()
{
    int ret;
    radio_info_t *pr = NULL;

    ret = alloc_radio(&pr);
    if (ret != NO_ERROR)
        return -FAILED;

    ret = start_radio(pr);

	/* set version */
    radio_set_version(pr);

	/* disable fhss */
	radio_set_fhss(pr, false);

	/* enable no.4 antenna */
	radio_set_antenna_attr(pr, NO_TO_ATTR(4));

	radio_set_dig_atten(pr, 0x3C);

	/* disable carrier wave */
	radio_set_carr(pr, false);

test_fail:
    stop_radio(pr);
    release_radio(pr);
}

int main(int argc, char** argv)
{
    test_radio();
}
