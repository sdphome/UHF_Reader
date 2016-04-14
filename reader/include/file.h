#ifndef __FILE_H
#define __FILE_H

#include <stdint.h>

int file_get_size(const char *path, unsigned long *size);
int file_read_data(uint8_t * buf, FILE * fp, unsigned long size);
int file_write_data(uint8_t * buf, FILE * fp, unsigned long size);

#endif
