#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>
#include <errno.h>

#include "radio.h"

/* ---------- ---------- */

radio_result_list g_result_list = NULL;

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
    tcflush(fd,TCIFLUSH);
    if (tcsetattr(fd,TCSANOW,&options) != 0) {
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

void signal_result(radio_info_t *radio_info, radio_result_t *result)
{
    pthread_mutex_lock(&radio_info->s_lock);

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
    pthread_cond_broadcast(&radio_info->s_cond);
    pthread_mutex_unlock(&radio_info->s_lock);
}

int start_radio(radio_info_t *radio_info)
{
    int ret;

    radio_info->fd = init_uart(RADIO_PORT);
    if (radio_info->fd < 0) {
        printf("Init uart failed.\n");
        return -FAILED;
    }
    /* TODO: create pthread */
    pthread_create();
}

void stop_radio(radio_info_t *radio_info)
{
    close_uart(radio_info->fd);
}

int init_radio(radio_info_t *radio_info)
{
    int ret;

    radio_info = (radio_info_t *)malloc(sizeof(radio_info_t));
    if (radio_info == NULL) {
        printf("Alloc memory for radio info failed.\n");
        return -FAILED;
    }

    radio_info->fd = -1;
    radio_info->result_list = NULL;

    return NO_ERROR;
}

void release_radio(radio_info_t *radio_info)
{
    free(radio_info);
}
