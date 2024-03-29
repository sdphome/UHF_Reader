
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
#ifndef __XML_H
#define __XML_H

#include <libxml/parser.h>

#define NAME_SIZE_MAX			512
#define MAX_KEY_VALUE_PAIRS 	20
#define MAX_KEY_SIZE			32

#define BUFF_SIZE_255			255

#define CONFIG_XML_PATH			"/uhf/"
#define CONFIG_XML				"uhf.xml"

#if !defined RETURN_ON_FAILED
#define RETURN_ON_FAILED(expr)                         \
    if ((expr) == FAILED) {                            \
        printf("failed evaluated expression is FALSE.\n"); \
        return FAILED;                                 \
     }
#endif

#if !defined RETURN_ON_NULL
#define RETURN_ON_NULL(expr)                           \
    if ((expr) == NULL) {                              \
        printf("failed NULL pointer detected " #expr); \
        return FAILED;                                  \
     }
#endif

#if !defined RETURN_FAILED_IF
#define RETURN_FAILED_IF(_cond, args...)                \
    if ((_cond)) {                                     \
        printf(" failed evaluated expression is FALSE: " #_cond " : " args); \
        return FAILED;                                           \
    }
#endif

enum xmlValueType {
	XML_VALUE_STRING,
	XML_VALUE_INT8,
	XML_VALUE_UINT8,
	XML_VALUE_INT16,
	XML_VALUE_UINT16,
	XML_VALUE_UINT64,
	XML_VALUE_INT32,
	XML_VALUE_UINT32,
	XML_VALUE_FLOAT,
	XML_VALUE_MAX
};

struct xmlKeyValuePair {
	void *value;
	char key[MAX_KEY_SIZE];
	xmlElementType nodeType;
	enum xmlValueType value_type;
};

typedef struct {
	uint8_t log_level;
	char dev_link[NAME_SIZE_MAX];
	char fw_path[NAME_SIZE_MAX];
	uint8_t timeout;
	uint32_t heart_peri;
} radio_config_t;

typedef struct {
	uint8_t log_level;
	char dev_link[NAME_SIZE_MAX];
	char fw_path[NAME_SIZE_MAX];
	char auth_x509_path[NAME_SIZE_MAX];
	uint8_t timeout;
} security_config_t;

typedef struct select_report_spec {
	uint8_t SelectReportTrigger;
	uint16_t NValue;
#define ENABLE_SELECT_SPEC_ID       0x8000
#define ENABLE_SPEC_INDEX           0x4000
#define ENABLE_RF_SPEC_ID           0x2000
#define ENABLE_ANTENNAL_ID          0x1000
#define ENABLE_PEAK_RSSI            0x0800
#define ENABLE_FST                  0x0400
#define ENABLE_LST                  0x0200
#define ENABLE_TSC                  0x0100
#define ENABLE_ACCESS_SPEC_ID       0x0080
	uint16_t mask;
} select_report_spec_t;

typedef struct select_spec_start_trigger {
	uint8_t type;
	uint32_t offset;
	uint32_t period;
} select_spec_start_trigger_t;

typedef struct rf_spec {
	uint8_t RfSpecId;
	uint8_t SelectType;
	uint8_t MemoryBankId;
	uint8_t BankType;
} rf_spec_t;

typedef struct antenna_configuration {
	uint8_t AntennaID;
	uint16_t TransmitPowerIndex;
	uint16_t FrequencyIndex;
	uint16_t ForDataRateIndex;
	uint16_t RevDataRateIndex;
	uint16_t ForModulationIndex;
	uint16_t RevDataEncodingIndex;
} antenna_configuration_t;

typedef struct select_spec {
	uint32_t SelectSpecID;
	uint8_t Priority;
	uint8_t CurrentState;
	uint8_t Persistence;
	select_spec_start_trigger_t SelectSpecStart;
	rf_spec_t RfSpec;
	antenna_configuration_t AntennaConfiguration;
} select_spec_t;

typedef struct {
	uint8_t log_level;
	char db_path[NAME_SIZE_MAX];
	uint8_t timeout;
	uint32_t heart_peri;
	select_spec_t select_spec;
	select_report_spec_t report_spec;
} upper_config_t;

typedef struct {
	char active_cert_path[NAME_SIZE_MAX];
	char user_info_path[NAME_SIZE_MAX];
	char bind_accept_path[NAME_SIZE_MAX];
	char uuid_path[NAME_SIZE_MAX];
	char uhf_trace_path[NAME_SIZE_MAX];

	radio_config_t radio;
	security_config_t security;
	upper_config_t upper;
} uhf_config_t;

struct xmlConfigInfo {
	xmlDocPtr docPtr;
	xmlNodePtr nodePtr;
	uhf_config_t config;
};

int xml_save_config(struct xmlConfigInfo *pXmlConfig);
int xml_parse_config(struct xmlConfigInfo *pXmlConfig);

#endif
