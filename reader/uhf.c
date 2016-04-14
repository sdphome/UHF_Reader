
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
#include <sys/types.h>
#include <sys/wait.h>
#include <ltkc.h>
#include <uhf.h>

//#define TEST

uhf_info_t * g_uhf = NULL;

static int uhf_init_security(uhf_info_t * p_uhf)
{
	int ret = NO_ERROR;
	security_info_t *security = p_uhf->security;
	//uint64_t sec_rand;

	security->uhf = (void *)p_uhf;

	//ret = security_set_rtc(security);

	//sec_rand = security_request_rand_num(security);

	//ret = security_send_auth_data(security, sec_rand);

	return ret;
}

static int uhf_init_radio(uhf_info_t * p_uhf)
{
	int ret = NO_ERROR;
	radio_info_t *radio = p_uhf->radio;

	radio->uhf = (void *)p_uhf;

#ifndef TEST
	printf("%s: start continue check.\n", __func__);
	ret = radio_set_conti_check(radio);
#endif

	return ret;
}

static void uhf_init_upper(uhf_info_t * p_uhf)
{
	upper_info_t *upper = p_uhf->upper;

	upper->uhf = (void *)p_uhf;

	/* setup default select report spec */
	upper->tag_spec.SelectReportTrigger = 1;
	upper->tag_spec.NValue = 400;
	upper->tag_spec.mask |= ENABLE_SELECT_SPEC_ID;
	upper->tag_spec.mask |= ENABLE_RF_SPEC_ID;
	upper->tag_spec.mask |= ENABLE_ANTENNAL_ID;
	upper->tag_spec.mask |= ENABLE_FST;
	upper->tag_spec.mask |= ENABLE_LST;
	upper->tag_spec.mask |= ENABLE_TSC;
}

void *uhf_heartbeat_loop(void *data)
{
	uhf_info_t *p_uhf = (uhf_info_t *) data;
	radio_info_t *radio = p_uhf->radio;
	upper_info_t *upper = p_uhf->upper;
	uint32_t count = 1;
	uint32_t radio_per_seconds, upper_per_seconds, base;

	while (true) {
		printf("%s: radio_per_seconds=%d, upper_per_seconds=%d.\n",
				__func__, radio->heartbeats_periodic, upper->heartbeats_periodic);
		radio_per_seconds = radio->heartbeats_periodic / 1000;
		upper_per_seconds = upper->heartbeats_periodic / 1000;
		if (upper_per_seconds != 0)
			base = radio_per_seconds * upper_per_seconds;
		else
			base = radio_per_seconds;

		if (count % radio_per_seconds == 0) {
			printf("%s: radio send heartbeat.\n", __func__);
			radio_send_heartbeat(radio);
		}

		if (upper_per_seconds && count % upper_per_seconds == 0) {
			printf("%s: upper set heartbeat.\n", __func__);
			upper_send_heartbeat(upper);
		}

		if (count++ == base)
			count = 1;

		sleep(1);
	}

	return NULL;
}

static int uhf_create_heartbeat_thread(uhf_info_t * p_uhf)
{
	int ret = NO_ERROR;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	ret = pthread_create(&p_uhf->heartbeat_thread, &attr, uhf_heartbeat_loop, (void *)p_uhf);
	if (ret < 0) {
		printf("%s: failed, ret = %d.\n", __func__, ret);
	}

	return ret;
}

void uhf_stop(int signo)
{
	void *ret;
	radio_info_t *radio = g_uhf->radio;
	security_info_t *security = g_uhf->security;
	upper_info_t *upper = g_uhf->upper;

	pthread_cancel(g_uhf->heartbeat_thread);
	pthread_join(g_uhf->heartbeat_thread, &ret);

	stop_radio(radio);
	stop_security(security);
	stop_upper(upper);

	release_radio(&radio);
	release_security(&security);
	release_upper(&upper);

	free(g_uhf);
	g_uhf = NULL;

	printf("Will stop this process.\n");
	_exit(0);
}

#ifndef TEST
int main(int argc, char **argv)
{
	int ret = NO_ERROR;
	uhf_info_t *p_uhf;

	/* TODO: setup rtc */
	system("ntpd");

	p_uhf = (uhf_info_t *) malloc(sizeof(uhf_info_t));
	if (p_uhf == NULL)
		return -ENOMEM;

	g_uhf = p_uhf;
	memset(p_uhf, 0, sizeof(uhf_info_t));

	signal(SIGINT, uhf_stop);
	signal(SIGSTOP, uhf_stop);

	ret = alloc_radio(&p_uhf->radio);
	ret += alloc_security(&p_uhf->security);
	ret += alloc_upper(&p_uhf->upper);
	if (ret != NO_ERROR)
		goto alloc_failed;

	ret = start_security(p_uhf->security);
	if (ret != NO_ERROR)
		goto start_failed;

	ret = uhf_init_security(p_uhf);
	if (ret != NO_ERROR)
		goto start_failed;
	p_uhf->upper->uhf = (void *)p_uhf;

	security_main(p_uhf->security);

	uhf_init_upper(p_uhf);

	ret = start_radio(p_uhf->radio);
	if (ret != NO_ERROR)
		goto start_failed;

	uhf_init_radio(p_uhf);

	uhf_create_heartbeat_thread(p_uhf);

	printf("Let's start the upper loop\n");

	ret = start_upper(p_uhf->upper);
	if (ret != NO_ERROR)
		goto start_failed;

	return 0;

  start_failed:
	stop_radio(p_uhf->radio);
	stop_security(p_uhf->security);
	stop_upper(p_uhf->upper);
  alloc_failed:
	release_upper(&p_uhf->upper);
	release_security(&p_uhf->security);
	release_radio(&p_uhf->radio);

	/* TODO: reboot */
	return ret;
}
#else
int main(int argc, char **argv)
{
	int ret = NO_ERROR;
	uhf_info_t *p_uhf;

	/* TODO: setup rtc */
	system("ntpd");

	p_uhf = (uhf_info_t *) malloc(sizeof(uhf_info_t));
	if (p_uhf == NULL)
		return -ENOMEM;

	memset(p_uhf, 0, sizeof(uhf_info_t));
	g_uhf = p_uhf;

	signal(SIGINT, uhf_stop);
	signal(SIGSTOP, uhf_stop);

	ret = alloc_radio(&p_uhf->radio);
	ret += alloc_security(&p_uhf->security);
	if (ret != NO_ERROR)
		goto alloc_failed;

	ret = start_security(p_uhf->security);
	if (ret != NO_ERROR)
		goto start_failed;

	ret = start_radio(p_uhf->radio);
	if (ret != NO_ERROR)
		goto start_failed;

	uhf_init_radio(p_uhf);

	radio_get_version(p_uhf->radio);

	radio_update_firmware(p_uhf->radio);
	sleep(3);

	security_reset_radio(p_uhf->security->fd);
	sleep(3);
	radio_get_version(p_uhf->radio);

	return 0;

  start_failed:
	stop_radio(p_uhf->radio);
  alloc_failed:
	release_radio(&p_uhf->radio);

	return ret;
}
#endif
