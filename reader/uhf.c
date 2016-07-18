
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <execinfo.h>
#include <ltkc.h>
#include <uhf.h>

//#define TEST

uhf_info_t *g_uhf = NULL;

static int uhf_init_security(uhf_info_t * p_uhf)
{
	int ret = NO_ERROR;
	security_info_t *security = p_uhf->security;
	uint64_t sec_rand = 0;

	security->uhf = (void *)p_uhf;
	security->pXmlConfig = &p_uhf->xmlConfig;
	security->serial = p_uhf->serial;

	sec_rand = security_request_rand_num(security);

	ret = security_send_auth_data(security, sec_rand);
	p_uhf->sec_auth_status = ret;

	ret = security_set_rtc(security);
	/* default work mode: part0, full partion */
	ret += security_set_work_mode_helper(security, 0, 2);

	printf("%s: security_send_auth_data ret = %d.\n", __func__, p_uhf->sec_auth_status);

	return ret;
}

static int uhf_init_radio(uhf_info_t * p_uhf)
{
	int ret = NO_ERROR;
	radio_info_t *radio = p_uhf->radio;

	radio->uhf = (void *)p_uhf;
	radio->pXmlConfig = &p_uhf->xmlConfig;
	radio->heartbeats_periodic = p_uhf->xmlConfig.config.radio.heart_peri;

	printf("%s: stop continue check.\n", __func__);
	ret = radio_stop_conti_check(radio);

	return ret;
}

static void uhf_init_upper(uhf_info_t * p_uhf)
{
	upper_info_t *upper = p_uhf->upper;

	upper->uhf = (void *)p_uhf;
	upper->pXmlConfig = &p_uhf->xmlConfig;
	upper->serial = p_uhf->serial;
	upper->heartbeats_periodic = p_uhf->xmlConfig.config.upper.heart_peri;
	sql_create_tag_table(p_uhf->xmlConfig.config.upper.db_path);

	upper->report_spec = &p_uhf->xmlConfig.config.upper.report_spec;
	upper->select_spec = &p_uhf->xmlConfig.config.upper.select_spec;

	upper_check_local_spec(upper);
}

int uhf_get_uuid(uhf_info_t * info)
{
	uint8_t userid[8] = { 0x30, 0x33, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31 };	// "03000001"
	FILE *fp = NULL;
	int ret = NO_ERROR;
	unsigned long size = -1;

	ret = file_get_size(info->xmlConfig.config.uuid_path, &size);
	if (ret == NO_ERROR && size == 9) {
		fp = fopen(info->xmlConfig.config.uuid_path, "r");
		if (fp != NULL) {
			file_read_data(userid, fp, 8);
			printf("%s: userid = %llx.\n", __func__, *(uint64_t *) userid);
			fclose(fp);
		}
	}

	memcpy(&info->serial, userid, 8);

	return ret;
}

void *uhf_heartbeat_loop(void *data)
{
	uhf_info_t *p_uhf = (uhf_info_t *) data;
	radio_info_t *radio = p_uhf->radio;
	upper_info_t *upper = p_uhf->upper;
	uint32_t count = 1;
	uint32_t radio_per_seconds, upper_per_seconds, base;

	while (true) {

		radio_per_seconds = radio->heartbeats_periodic / 1000;
		upper_per_seconds = upper->heartbeats_periodic / 1000;
		if (upper_per_seconds != 0)
			base = radio_per_seconds * upper_per_seconds;
		else
			base = radio_per_seconds;

		if (count % radio_per_seconds == 0) {
			radio_send_heartbeat(radio);
		}

		if (upper_per_seconds && count % upper_per_seconds == 0) {
			upper_send_heartbeat(upper);
		}

		if (count % 5 == 0)
			upper_signal_upload(upper);

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

	printf("[UHF] %s Enter\n", __func__);

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

static void uhf_print_trace(int signum)
{
	void *array[10];
	size_t size;
	char **strings;
	size_t i;
	FILE *fp;
	uhf_config_t *uhf_cfg = &g_uhf->xmlConfig.config;

	signal(signum, SIG_DFL);
	size = backtrace(array, 10);
	strings = (char **)backtrace_symbols(array, size);

	fp = fopen(uhf_cfg->uhf_trace_path, "w");

	fprintf(stderr, "uhf received SIGSEGV! Stack trace:\n");
	for (i = 0; i < size; i++) {
		fprintf(stderr, "%d %s \n", i, strings[i]);
		file_write_data((uint8_t *) strings[i], fp, strlen(strings[i]));
		file_write_data((uint8_t *) "\n", fp, 1);
	}

	free(strings);
	fclose(fp);
	system("reboot");
	exit(1);
}

#ifndef TEST
int main(int argc, char **argv)
{
	int ret = NO_ERROR;
	uhf_info_t *p_uhf;
	struct xmlConfigInfo *pXmlConfig = NULL;

	signal(SIGSEGV, uhf_print_trace);
	signal(SIGABRT, uhf_print_trace);

	/* TODO: setup rtc */
	system("ntpd");

	p_uhf = (uhf_info_t *) malloc(sizeof(uhf_info_t));
	if (p_uhf == NULL)
		return -ENOMEM;

	g_uhf = p_uhf;
	memset(p_uhf, 0, sizeof(uhf_info_t));

	signal(SIGINT, uhf_stop);
	signal(SIGSTOP, uhf_stop);

	pXmlConfig = &p_uhf->xmlConfig;

	ret = xml_parse_config(pXmlConfig);
	if (ret) {
		printf("xml parse config failed.");
		goto failed;
	}

	uhf_get_uuid(p_uhf);

	ret = alloc_radio(&p_uhf->radio);
	ret += alloc_security(&p_uhf->security);
	ret += alloc_upper(&p_uhf->upper);
	if (ret != NO_ERROR)
		goto alloc_failed;

	ret = start_security(p_uhf->security);
	if (ret != NO_ERROR)
		goto start_failed;

	ret = uhf_init_security(p_uhf);

/*  TODO: check the return
	if (ret != NO_ERROR)
		goto start_failed;
*/

	uhf_init_upper(p_uhf);

	ret = start_radio(p_uhf->radio);
	if (ret != NO_ERROR)
		goto start_failed;

	uhf_init_radio(p_uhf);

	uhf_create_heartbeat_thread(p_uhf);

	printf("Let's start the upper loop............\n");

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
  failed:
	free(p_uhf);
	system("reboot");
	return ret;
}
#else							// TEST
int main(int argc, char **argv)
{
	int ret = NO_ERROR;
	uhf_info_t *p_uhf;

	/* TODO: setup rtc */
	//system("ntpd");

	signal(SIGSEGV, uhf_print_trace);
	signal(SIGABRT, uhf_print_trace);

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

	//radio_main(p_uhf->radio);

	ret = uhf_init_security(p_uhf);
	if (ret != NO_ERROR)
		goto start_failed;

	security_upgrade_firmware(p_uhf->security, p_uhf.xmlConfig.config.security.fw_path);
	sleep(30);

	security_reset(p_uhf->security->fd);
	security_get_status(p_uhf->security->fd);
	security_get_status(p_uhf->security->fd);
	sleep(6);

	ret = uhf_init_security(p_uhf);
	if (ret != NO_ERROR)
		goto start_failed;

//  security_main(p_uhf->security);

	printf("Will return.\n");

	return 0;

  start_failed:
  alloc_failed:

	return ret;
}
#endif
