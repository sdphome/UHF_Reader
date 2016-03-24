#ifndef __SECURITY_H
#define __SECURITY_H

#include <stdint.h>

#define SECURITY_DEV        "/dev/uhf-security"

#define false							0
#define true							1

#define SECURITY_MTU					1500
#define SECURITY_TIMEOUT				2

#define US_IOC_MAGIC            		'u'
#define US_IOC_RESET            		_IO(US_IOC_MAGIC, 1)
#define US_IOC_GET_STATUS       		_IO(US_IOC_MAGIC, 2)
#define US_IOC_RESET_RADIO      		_IO(US_IOC_MAGIC, 3)

/* security module status */
#define OK 								0
#define BUSY							1

/* ---------- Response Result ---------- */
#define NO_ERROR						0
#define FAILED							1


#define PACK_SEND_HDR					0xAA
#define PACK_RECV_HDR					0xAB

#define SECURITY_VERSION_1				0x1
#define SECURITY_VERSION_2				0x2

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
#define IDEN_AUTH						0x2
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

// ERROR_TYPE
#define UNKNOWN_TYPE					0xB
#define DATA_ERROR						0xC
#define PACK_ILLE						0xD
#define CRC_FAILED						0xE
#define PROGRAM_MISSING					0x60
#define VERIFY_ENCR_FAILED				0x61

#define NO_PARAM_SIZE					1

typedef struct {
	uint32_t time;
} __attribute__ ((packed)) timestamp_v1_param;
#define TIMESTAMP_V1_PARAM_SIZE			4

typedef struct {
	uint64_t time;
} __attribute__ ((packed)) timestamp_v2_param;
#define TIMESTAMP_V2_PARAM_SIZE			8

typedef struct {
	uint16_t type;
} __attribute__ ((packed)) get_params_param;
#define GET_PARAMS_PARAM_SIZE			2

typedef struct {
	uint16_t type;
	uint16_t hw_ver;
	uint16_t ctrl_boot_ver;
	uint16_t encry_boot_ver;
	uint16_t ctrl_ver;
	uint16_t encry1_ver;
	uint16_t encry2_ver;
} __attribute__ ((packed)) firmware_version_param;
#define FIRMWARE_VERSION_PARAM_SIZE		14

typedef struct {
	uint16_t type;
	uint64_t serial_num;
} __attribute__ ((packed)) serial_num_param;
#define SERIAL_NUM_PARAM_SIZE			10

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

typedef struct {
	uint8_t part_num;
	uint8_t part_indi;
	uint8_t ciphertext:4;
	uint8_t high_speed:4;
	uint16_t read_index;
	uint16_t read_len;
} __attribute__ ((packed)) part_info_param;
#define PART_INFO_PARAM_SIZE			7

typedef struct {
	uint8_t num;
	uint8_t data[0];
} __attribute__ ((packed)) work_mode_param;
#define WORK_MODE_PARAM_SIZE			1

typedef struct {
	uint8_t part[12];
} __attribute__ ((packed)) perm_table_param;
#define PERM_TABLE_PARAM_SIZE			12

typedef struct {
	uint64_t sec_rand;
} __attribute__ ((packed)) rand_num_param;
#define RAND_NUM_PARAM_SIZE				8

typedef struct {
	uint8_t boot_version;
	uint8_t firmware_version;
	uint32_t file_size;
	uint32_t firmware_size;
	uint16_t block_size;
	uint8_t cmd;
	uint8_t reserve[19];
	uint8_t block[0];
} __attribute__ ((packed)) firmware_data;
#define FIRMWARE_DATA_HDR_SIZE			32


//7.6.1
typedef struct {
	uint64_t host_rand;
	uint64_t sec_rand;
	uint64_t serial;
	uint64_t reserve;
	uint8_t sign[64];
	uint8_t x509[0];
} __attribute__ ((packed)) auth_data_param;
#define AUTH_DATA_PARAM_SIZE			96

// 7.6.2
typedef struct {
	uint8_t province[10];
	uint8_t city[10];
	uint8_t longitude[6];
	uint8_t use[20];
	uint8_t model[8];
	uint8_t company[40];
	uint8_t contact[10];
	uint8_t tele1[5];
	uint8_t tele2[5];
	uint8_t email[30];
	uint8_t reg_data[5];
	uint8_t remark[75];
} __attribute__ ((packed)) user_info_param;
#define USER_INFO_PARAM_SIZE			224

// 7.6.3
typedef struct {
#define TO_BE_ACTIVED					0x8
#define RE_ACTIVE						0x9
	uint8_t active_flag;
	uint16_t len;
	uint8_t mode;
	uint64_t serial;
	uint8_t reserve[5];
	uint8_t forward[424];
	uint8_t x509[0];
} __attribute__ ((packed)) active_req_param;
#define ACTIVE_REQ_PARAM_SIZE			441

//7.6.4
typedef struct {
	uint16_t len;
	uint8_t mode;
	uint64_t serial;
	uint8_t reserve[5];
	uint8_t forward[200];
} __attribute__ ((packed)) active_auth_param;
#define ACTIVE_AUTH_PARAM_SIZE			216

// 7.6.5
typedef struct {
#define GRADE_ZERO						0
#define GRADE_ONE						1
	uint8_t curr_grade;
#define TWO_GRADE						1
#define THREE_GRADE						2
	uint8_t total_grade;
	uint8_t x509[0];
} __attribute__ ((packed)) cert_chain_param;
#define CERT_CHAIN_PARAM_SIZE			2

typedef struct {
	uint8_t errno;
	uint64_t tid;
	uint8_t ante_no;
	uint64_t time;  /* FIXME: make sure which version */
} __attribute__ ((packed)) tid_upload_param;
#define TID_UPLOAD_PARAM_SIZE			17

typedef struct {
	uint8_t errno;
	uint8_t part_no:4;
	uint8_t flag:2;
	uint8_t ante_no:2;
	uint64_t time;
	uint8_t tid_en[16];
} __attribute__ ((packed)) tid_upload_err1_param;
#define TID_UPLOAD_ERR1_PARAM_SIZE		25

typedef struct {
	uint8_t errno;
	uint8_t ante_no;
	uint64_t time;
} __attribute__ ((packed)) tid_upload_err3_param;
#define TID_UPLOAD_ERR3_PARAM_SIZE		8

typedef struct {
	uint8_t errno;
	uint64_t tid;
	uint8_t part_no:4;
	uint8_t flag:2;
	uint8_t ante_no:2;
	uint64_t time;
	uint8_t data[0];
} __attribute__ ((packed)) part_data_upload_param;
#define PART_DATA_UPLOAD_PARAM_SIZE		18

typedef struct {
	uint8_t errno;
	uint8_t part_no:4;
	uint8_t flag:2;
	uint8_t ante_no:2;
	uint64_t time;
	uint8_t tid_en[16];
} __attribute__ ((packed)) part_data_upload_err1_param;
#define PART_DATA_UPLOAD_ERR1_PARAM_SIZE     26

typedef struct {
	uint8_t errno;
	uint64_t tid;
	uint8_t part_no:4;
	uint8_t flag:2;
	uint8_t ante_no:2;
	uint64_t time;
} __attribute__ ((packed)) part_data_upload_err2_param;
#define PART_DATA_UPLOAD_ERR2_PARAM_SIZE     18

typedef struct {
	uint8_t errno;
	uint8_t ante_no;
	uint64_t time;
} __attribute__ ((packed)) part_data_upload_err3_param;
#define PART_DATA_UPLOAD_ERR3_PARAM_SIZE     10

typedef struct {
	uint8_t errno;
	uint64_t tid;
	uint8_t part_no:4;
	uint8_t flag:2;
	uint8_t ante_no:2;
	uint64_t time;
	uint8_t data[0];
} __attribute__ ((packed)) part_data_upload_err4_param;
#define PART_DATA_UPLOAD_ERR4_PARAM_SIZE     18

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

	pthread_t upload_thread;
	pthread_mutex_t upload_lock;
	pthread_cond_t upload_cond;

	security_result_list_t *result_list;
	security_result_list_t *upload_list;

	uint8_t rbuf[SECURITY_MTU];
	uint8_t wbuf[SECURITY_MTU];

	/* security module info */
	uint8_t version;
	uint64_t serial;
	char x509_path[20];
	uint8_t pub_key[64];
	uint8_t priv_key[32];
} security_info_t;

#endif
