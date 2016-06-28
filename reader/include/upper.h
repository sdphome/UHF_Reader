
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
#ifndef __UPPER_H
#define __UPPER_H
#include <stdint.h>
#include "../utils/llrp/ltkc.h"

#define UPPER_TIMEOUT				5

#define UPPER_DEFAULT_HEARTBEATS_PERIODIC	1000

#define UPPER_STOP			0x00
#define UPPER_DISCONNECTED	0x01
#define UPPER_CONNECTED		0x02
#define UPPER_READY			0x03

#define DB_PATH	"/uhf/uhf.db"

typedef struct data_param {
#define TYPE_CID	0x8801
#define TYPE_FPDH	0x8802
#define TYPE_SYXZ	0x8803
#define TYPE_CCRQ	0x8804
#define TYPE_CLLX	0x8805
#define TYPE_PL		0x8806
#define TYPE_GL		0x8807
#define TYPE_HPZL	0x8808
#define TYPE_HPHMXH	0x8809
#define TYPE_JYYXQ	0x880A
#define TYPE_QZBFQ	0x880B
#define TYPE_CSYS	0x880C
#define TYPE_ZKZL	0x880D
	uint16_t type_code;
	uint16_t len;
	uint8_t payload[0];
} data_param_t;

typedef struct select_report_spec {
	uint8_t SelectReportTrigger;
	uint16_t NValue;
#define	ENABLE_SELECT_SPEC_ID		0x8000
#define ENABLE_SPEC_INDEX			0x4000
#define ENABLE_RF_SPEC_ID			0x2000
#define ENABLE_ANTENNAL_ID			0x1000
#define ENABLE_PEAK_RSSI			0x0800
#define ENABLE_FST					0x0400
#define ENABLE_LST					0x0200
#define ENABLE_TSC					0x0100
#define ENABLE_ACCESS_SPEC_ID		0x0080
	uint16_t mask;
} select_report_spec_t;

/*
typedef struct select_spec {
	uint32_t SelectSpecID;
	uint8_t Priority;
	uint8_t CurrentState;
	uint8_t Persistence;
	select_spec_start_trigger_t SelectStart;
	select_spec_start_trigger_t SelectStop;
} select_spec_t;
*/

typedef struct tag_info {
	uint64_t TID;
	uint32_t SelectSpecID;
	uint16_t SpecIndex;
	uint16_t RfSpecID;
	uint8_t AntennalID;
	uint64_t FirstSeenTimestampUTC;
	uint64_t LastSeenTimestampUTC;
	uint16_t TagSeenCount;
	uint32_t AccessSpecID;
	llrp_u8v_t PartData;
	uint8_t FirstTime;
} tag_info_t;

typedef struct tag_list {
	tag_info_t tag;
	struct tag_list *next;
} tag_list_t;

typedef struct upper_info {
	int sock;
	int status;
	int verbose;
	int db_valid;
	char active_cer_path[48];
	char user_info_path[48];

	uint64_t next_msg_id;
	uint64_t serial;
	uint32_t heartbeats_periodic;

	uint64_t ntp_left_sec;
	uint16_t port;

	select_report_spec_t tag_spec;
	tag_list_t *tag_list;

	pthread_t read_thread;
	pthread_mutex_t lock;
	pthread_cond_t cond;

	pthread_t request_thread;
	pthread_mutex_t req_lock;
	pthread_cond_t req_cond;

	pthread_t upload_thread;
	pthread_mutex_t upload_lock;
	pthread_cond_t upload_cond;

	pthread_mutex_t disconnect_lock;
	pthread_cond_t disconnect_cond;

	LLRP_tSMessage *request_list;
	LLRP_tSMessage *response_list;

	LLRP_tSTypeRegistry *pTypeRegistry;
	LLRP_tSConnection *pConn;

	uint64_t last_report_time;
	uint64_t tid_count;
	uint64_t last_tid_count;

	void *uhf;
} upper_info_t;

void stop_upper(upper_info_t * info);
int start_upper(upper_info_t * info);
int alloc_upper(upper_info_t ** info);
void release_upper(upper_info_t ** info);

void upper_signal_upload(upper_info_t * info);
int upper_request_TagSelectAccessReport(upper_info_t * info, llrp_u64_t tid,
										llrp_u8_t anten_no, llrp_u64_t timestamp, void *part_data);

int upper_send_heartbeat(upper_info_t * info);

#endif
