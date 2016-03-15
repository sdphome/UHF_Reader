#ifndef __SECURITY_H
#define __SECURITY_H

#include <stdint.h>

#define SECURITY_DEV        "/dev/uhf-security"

#define false							0
#define true							1

#define SECURITY_MTU					1500
#define SECURITY_TIMEOUT				2

/* ---------- Response Result ---------- */
#define NO_ERROR						0
#define FAILED							1

#define PACK_SEND_HDR					0xAA
#define PACK_RECV_HDR					0xAB

#define SECURITY_VERSION				0x1

/* -------- Security Frame Type -------- */
#define SETUP_TYPE						0x1
#define SETUP_ACK_TYPE					0x2
#define AUTH_TYPE						0x3
#define AUTH_ACK_TYPE					0x4
#define UPLOAD_INFO_TYPE				0x5
#define DATA_FORWA_TYPE					0x6
#define DATA_FORWA_ACK_TYPE				0x7
#define ERROR_TYPE						0x8

/* ---------- Security Cmd ---------- */
// SETUP_TYPE & SETUP_ACK_TYPE
#define SETUP_RTC						0x1
#define GET_RTC							0x2
#define SETUP_PARAM						0x3
#define GET_PARAM						0x4
#define GET_PERMI						0x5
#define SETUP_MODE						0x6

// SETUP_PARAM & GET_PARAM type
#define FIRMWARE_VERSION				0x0
#define SECURITY_SERIAL					0x1
#define REPEAT_READ						0x2
#define WORK_MODE						0x3
#define KEY_VERSION						0x4
#define FILTR_INTERV					0x5

// AUTH_TYPE & AUTH_ACK_TYPE
#define REQ_RAND_NUM					0x1
#define SEND_RAND_NUM					0x2
#define USER_INFO						0x3
#define SEND_AUTH						0x4
#define SEND_CERT						0x5

// SEND_RAND_NUM errno
#define AUTH_PASS						0x0
#define SIGN_FAILED						0x1
#define RAND_NUM_FAILED					0x2
#define SECU_HASNT_ACTIVE				0x3
#define SECU_HAS_ACTIVE_OTHER			0x4
#define SERIAL_FAILED					0xA

// SEND_AUTH errno
#define ACTIVE_SUCC						0x0
#define DECIP_FAILED					0x1
#define VERIFY_SIGN_FAILED				0x2
#define SERIAL_NOT_MATCH				0x3


//UPLOAD_INFO_TYPE
#define REPORT_TID						0x1
#define REPORT_PART						0x2

// UPLOAD_INFO errno
#define TID_DECIP_FAILED				0x1
#define READ_PART_FAILED				0x2
#define WRONG_CHECK						0x3
#define USER_PART_FAILED				0x4

// DATA_FORWA_TYPE & DATA_FORWA_ACK_TYPE
#define UPGRADE_ENCR_MODULE				0x1
#define UPLOAD_FIRMWARE					0x2


typedef struct {
	uint64_t time;
} __attribute__ ((packed)) timestamp_param;
#define TIMESTAMP_PARAM_SIZE			8

typedef struct {
	uint16_t type;
	uint8_t flag;
} __attribute__ ((packed)) repeat_read_param;
#define REPEAT_READ_PARAM_SIZE			3

typedef struct {
	uint16_t type;
	uint32_t interval;
} __attribute__ ((packed)) filtr_interv_param;
#define FILTR_INTERV_PARAM_SIZE			6


/* ---------- message related ---------- */

typedef struct {
	uint8_t hdr;
	uint8_t type:4;
	uint8_t version:4;
	uint16_t len;
	uint8_t cmd;
} __attribute__ ((packed)) security_pack_hdr;
#define SECURITY_PACK_HDR_SIZE			5

typedef struct {
	security_pack_hdr hdr;
	uint8_t *payload;
	uint8_t crc;
} __attribute__ ((packed)) security_package_t;

typedef struct security_result_list {
	security_package_t result;
	struct security_result_list *next;
} security_result_list_t;

typedef struct security_info {
	int fd;
	int status;
	pthread_t read_thread;

	pthread_mutex_t lock;
	pthread_cond_t cond;

	security_result_list_t *result_list;

	uint8_t rbuf[SECURITY_MTU];
	uint8_t wbuf[SECURITY_MTU];
} security_info_t;

#endif
