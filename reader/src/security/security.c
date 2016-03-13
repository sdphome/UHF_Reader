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

int open_us(char *dev)
{
    int fd;

    fd = open(dev, O_RDWR);
    if (fd < 0) {
        
    }
}
