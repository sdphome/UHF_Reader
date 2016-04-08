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
#ifndef __UHF_H
#define __UHF_H

#include "upper.h"
#include "radio.h"
#include "security.h"


#define ACTIVE_CER_PATH     "/home/root/active.cer"
#define USER_INFO_PATH      "/home/root/user_info"

typedef struct uhf_info {
	int status;

	pthread_t heartbeat_thread;

	upper_info_t *upper;
	security_info_t *security;
	radio_info_t *radio;
} uhf_info_t;

#endif
