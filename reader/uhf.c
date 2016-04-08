/***************************************************************************
*
*   Author: Shao Depeng <dp.shao@gmail.com>
*   Copyright 2016 Golden Sky Technology CO.,LTD
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <ltkc.h>
#include <uhf.h>

#define TEST

static int uhf_init_security(uhf_info_t *p_uhf)
{
	int ret = NO_ERROR;
	security_info_t *security = p_uhf->security;
	uint64_t sec_rand;

	security->uhf = (void *)p_uhf;

	ret = security_set_rtc(security);

	sec_rand = security_request_rand_num(security);

	ret = security_send_auth_data(security, sec_rand);

	return ret;
}

static int uhf_init_radio(uhf_info_t *p_uhf)
{
	int ret = NO_ERROR;
	radio_info_t *radio = p_uhf->radio;

	radio->uhf = (void *)p_uhf;
	return 0;
}

int main(int argc, char** argv)
{
#ifndef TEST
	int ret = NO_ERROR;
	uhf_info_t *p_uhf;

	/* TODO: setup rtc */

	p_uhf = (uhf_info_t *)malloc(sizeof(uhf_info_t));
	if (p_uhf == NULL)
		return -ENOMEM;

	ret = alloc_radio(&p_uhf->radio);
	ret += alloc_security(&p_uhf->security);
	ret += alloc_upper(&p_uhf->upper);
	if (ret != NO_ERROR)
		goto alloc_failed;

	ret = start_radio(p_uhf->radio);
	if (ret != NO_ERROR)
		goto start_failed;

	uhf_init_radio(p_uhf);

	ret = start_security(p_uhf->security);
	if (ret != NO_ERROR)
		goto start_failed;

	uhf_init_security(p_uhf);

	p_uhf->upper->uhf = (void *)p_uhf;
	ret = start_upper(p_uhf->upper);
	if (ret != NO_ERROR)
		goto start_failed;

start_failed:
	stop_radio(p_uhf->radio);
	stop_security(p_uhf->security);
	stop_upper(p_uhf->upper);
alloc_failed:
	release_upper(p_uhf->upper);
	release_security(p_uhf->security);
	release_radio(p_uhf->radio);

	/* TODO: reboot */
	return ret;
#else
	upper_main(0, NULL);
	return 0;
#endif
}
