#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <uhf.h>

unsigned long file_get_size(const char *path)
{
	unsigned long filesize = -1;
	struct stat statbuff;

	if (stat(path, &statbuff) > 0) {
		filesize = statbuff.st_size;
	}

	return filesize;
}

int file_read_data(uint8_t *buf, FILE *fp, unsigned long size)
{
	int ret = NO_ERROR;
	unsigned long nrd = 0;

	nrd = fread(buf, size, 1, fp);

	if (nrd != size)
		ret = -FAILED;

	return ret;
}

int file_write_data(uint8_t *buf, FILE *fp, unsigned long size)
{
	int ret = NO_ERROR;
	unsigned long nwr = 0;

	nwr = fwrite(buf, size, 1, fp);

	if (nwr != size)
		ret = -FAILED;

	return ret;
}
