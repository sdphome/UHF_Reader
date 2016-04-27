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
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <uhf.h>

int file_get_size(const char *path, unsigned long *filesize)
{
	FILE *fp;

	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("can't open %s.\n", path);
		return -FAILED;
	}

	fseek(fp, 0L, SEEK_END);
	*filesize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	fclose(fp);

	return NO_ERROR;
}

int file_read_data(uint8_t * buf, FILE * fp, unsigned long size)
{
	int ret = NO_ERROR;
	unsigned long nrd = 0;

	if (fp == NULL || size == 0)
		return -FAILED;

	nrd = fread(buf, size, 1, fp);

	if (nrd < 0) {
		printf("%s: nrd=%ld, size=%ld.\n", __func__, nrd, size);
		ret = -FAILED;
	}

	return ret;
}

int file_write_data(uint8_t * buf, FILE * fp, unsigned long size)
{
	int ret = NO_ERROR;
	unsigned long nwr = 0;

	if (fp == NULL || size == 0)
		return -FAILED;

	nwr = fwrite(buf, size, 1, fp);

	if (nwr < 0)
		ret = -FAILED;

	return ret;
}
