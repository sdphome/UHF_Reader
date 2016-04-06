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

#define NO_ERROR			0
#define FAILED				1

#define false				0
#define true				1

#define UPPER_TIMEOUT		3

int upper_main(int argc, char** argv);

typedef struct upper_info {
	int sock;
	int status;
	int verbose;

	uint64_t next_msg_id;
	uint64_t serial;

	pthread_t read_thread;
	pthread_mutex_t lock;
	pthread_cond_t cond;

	pthread_t request_thread;
	pthread_mutex_t req_lock;
	pthread_cond_t req_cond;

    LLRP_tSMessage *request_list;
    LLRP_tSMessage *response_list;

	LLRP_tSTypeRegistry *pTypeRegistry;
	LLRP_tSConnection *pConn;

	void *uhf;
} upper_info_t;


#endif
