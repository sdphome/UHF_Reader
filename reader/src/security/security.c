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

    ret = pthread_create(&radio_info->read_thread, &attr, radio_reader_loop, (void *)radio_info);
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
