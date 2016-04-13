
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
#ifndef __UPPER_H
#define __UPPER_H
#include <stdint.h>
#include "../utils/llrp/ltkc.h"

#define UPPER_TIMEOUT				5

#define UPPER_DEFAULT_HEARTBEATS_PERIODIC	1000

int upper_main(int argc, char **argv);

typedef struct upper_info {
	int sock;
	int status;
	int verbose;
	char active_cer_path[48];
	char user_info_path[48];

	uint64_t next_msg_id;
	uint64_t serial;
	uint32_t heartbeats_periodic;;

	uint64_t ntp_left_sec;

	pthread_t read_thread;
	pthread_mutex_t lock;
	pthread_cond_t cond;

	pthread_t request_thread;
	pthread_mutex_t req_lock;
	pthread_cond_t req_cond;

	pthread_mutex_t disconnect_lock;
	pthread_cond_t disconnect_cond;

	LLRP_tSMessage *request_list;
	LLRP_tSMessage *response_list;

	LLRP_tSTypeRegistry *pTypeRegistry;
	LLRP_tSConnection *pConn;

	uint16_t port;

	void *uhf;
} upper_info_t;

void stop_upper(upper_info_t * info);
int start_upper(upper_info_t * info);
int alloc_upper(upper_info_t ** info);
void release_upper(upper_info_t ** info);

int upper_request_TagSelectAccessReport(upper_info_t * info, llrp_u64_t tid,
										llrp_u8_t anten_no, llrp_u64_t timestamp);
int upper_send_heartbeat(upper_info_t * info);
#endif
