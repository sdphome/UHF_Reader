#ifndef __RADIO_H
#define __RADIO_H

#include <linux/types.h>

#define RADIO_PORT      "/dev/ttymxc1"

/* ---------- Response Result ---------- */
#define SUCCESS                         0
#define FAILED                          1

/* ---------- Package Fixed Value ---------- */
#define PACK_HDR                        0xFA
#define PACK_END                        0xFB
#define REQUEST_TYPE                    0x0000
#define RESPONSE_TYPE                   0x0001


/* ---------- RADIO Commands ---------- */

#define SET_VERSION                     0x0001
#define GET_VERSION                     0x0002
typedef struct {
    uint8_t hw_version[3];
    uint8_t sw_version[3];
} __attribute__ ((packed)) version_param;
#define VERSION_PARAM_SIZE              6

#define SET_TRANS_POWER                 0x0003
#define GET_TRANS_POWER                 0x0004
typedef struct {
    uint8_t power;
} __attribute__ ((packed)) trans_power_param;
#define TRANS_POWER_PARAM_SIZE          1

#define SET_FHSS_ENABLE                 0x0005
#define GET_FHSS_ENABLE                 0x0006
typedef struct {
    uint8_t enable;
} __attribute__ ((packed)) fhss_enable_param;
#define FHSS_ENABLE_PARAM_SIZE          1

#define SET_TRANS_FREQ_RANGE            0x0007
#define GET_TRANS_FREQ_RANGE            0x0008
typedef struct {
    uint8_t start_freq;
    uint8_t stop_freq;
} __attribute__ ((packed)) trans_freq_range_param;
#define TRANS_FREQ_RANGE_PARAM_SIZE     2

#define SET_REVER_CHAN_RATE             0x0009
#define GET_REVER_CHAN_RATE             0x000A
typedef struct {
    uint8_t rate;
} __attribute__ ((packed)) rever_chan_rate_param;
#define REVER_CHAN_RATE_PARAM_SIZE      1

#define SET_REVER_CODE_MODE             0x000B
#define GET_REVER_CODE_MODE             0x000C
typedef struct {
    uint8_t mode;
} __attribute__ ((packed)) rever_code_mode_param;
#define REVER_CODE_MODE_PARAM_SIZE      1

#define SET_ANTENNA_ATTR                0x000D
#define GET_ANTENNA_ATTR                0x000E
typedef struct {
    uint8_t attribute;
} __attribute__ ((packed)) antenna_attr_param;
#define ANTENNA_ATTR_PARAM_SIZE         1

#define SET_ANTENNA_GAIN                0x000F
#define GET_ANTENNA_GAIN                0x0010
typedef struct {
    uint8_t gain;
} __attribute__ ((packed)) antenna_gain_param;
#define ANTENNA_GAIN_PARAM_SIZE         1

#define SET_CARR_ENABLE                 0x0011
#define GET_CARR_ENABLE                 0x0012
typedef struct {
    uint8_t enable;
} __attribute__ ((packed)) carr_enable_param;
#define CARR_ENABLE_PARAM_SIZE          1

#define SET_FPGA_THRESH                 0x0013
#define GET_FPGA_THRESH                 0x0014
typedef struct {
    uint8_t thresh[3];
}__attribute__ ((packed)) fpga_thresh_param;
#define FPGA_THRESH_PARAM_SIZE          3

#define SET_ANTI_COLL_PROTO             0x0015
#define GET_ANTI_COLL_PROTO             0x0016
typedef struct {
    uint8_t protocol;
}__attribute__ ((packed)) anti_coll_proto_param;
#define ANTI_COLL_PROTO_PARAM_SIZE      1

#define SET_Q_VALUE                     0x0017
#define GET_Q_VALUE                     0x0018
typedef struct {
    uint8_t value;
}__attribute__ ((packed)) q_value_param;
#define Q_VALUE_PARAM_SIZE              1

#define SET_MODUL_MODE                  0x0019
#define GET_MODUL_MODE                  0x001A
typedef struct {
    uint8_t mode;
}__attribute__ ((packed)) modul_mode_param;
#define MODUL_MODE_PARAM_SIZE           1

#define SET_TC_VALUE                    0x001B
#define GET_TC_VALUE                    0x001C
typedef struct {
    uint8_t tc;
}__attribute__ ((packed)) tc_value_param;
#define TC_VALUE_PARAM_SIZE             1

#define SET_SJC_VALUE                   0x001D
#define GET_SJC_VALUE                   0x001E
typedef struct {
    uint8_t sjc;
}__attribute__ ((packed)) sjc_value_param;
#define SJC_VALUE_PARAM_SIZE            1

/* start/stop check has no data */
#define SIGNAL_CHECK                    0x001F
#define START_CONTI_CHECK               0x0020
#define STOP_CONTI_CHECK                0x0021

#define SET_WRITE_TAG                   0x0022
/* the data of write tag cmd variable */
typedef struct {
    uint8_t len;
    uint8_t *tag;
}__attribute__ ((packed)) write_tag_param;

#define GET_RADIO_PARAM                 0x0023
typedef struct {
    uint8_t *param;
}__attribute__ ((packed)) radio_rsp_param;

#define SET_DIG_ATTEN                   0x0024
#define GET_DIG_ATTEN                   0x0025
typedef struct {
    uint8_t attenuation;
}__attribute__ ((packed)) dig_atten_param;
#define DIG_ATTEN_PARAM_SIZE            1

#define SET_PA_ENABLE                   0x0026
#define GET_PA_ENABLE                   0x0027
typedef struct {
    uint8_t enable;
}__attribute__ ((packed)) pa_enable_param;
#define PA_ENABLE_PARAM_SIZE            1

/* start/stop check has no data */
#define START_RADIO_WORK                0x00F0
#define STOP_RADIO_WORK                 0x00F1
#define REBOOT_RADIO_MODULE             0x00F2

/* module upgrade cmd has no data */
#define REQ_RADIO_UPGRADE               0x00F3
#define MID_UPGRADE_PACK                0x00F4
#define LAST_UPGRADE_PACK               0x00F5
#define EVT_UPGRADE_SUCC                0x00F6
#define EVT_UPGRADE_FAIL                0x00F7

#define GET_RADIO_STATUS                0x00FC

/* ---------- Genaral Package ---------- */

typedef struct {
    uint8_t hdr;
    uint16_t type;
    uint8_t cmd;
    uint16_t len;
} __attribute__ ((packed)) radio_pack_hdr;
#define RADIO_PACK_HDR_SIZE             6

typedef struct {
    uint16_t crc16;
    uint8_t end;
} __attribute__ ((packed)) radio_pack_end;
#define RADIO_PACK_END_SIZE              3


/* ---------- message related ---------- */
typedef struct {
    uint8_t status;
    radio_pack_hdr hdr;
    uint8_t *payload;
    radio_pack_end end;
} radio_result_t;

typedef struct {
    radio_result_t result;
    struct api_result_list *next;
} radio_result_list_t;


typedef struct {
    int fd;
    int status;
    pthread_mutex_t c_lock;
    pthread_cond_t c_cond;
    pthread_t read_thread;
    radio_result_list_t *result_list;
} radio_info_t;

/* ---------- helper function ---------- */
/* TODO: fill the string */
const char *radio_cmd_to_string(uint16_t command)
{
    switch (command) {
	case SET_VERSION: return "";
	case GET_VERSION: return "";
	case SET_TRANS_POWER: return "";
	case GET_TRANS_POWER: return "";
	case SET_FHSS_ENABLE: return "";
	case GET_FHSS_ENABLE: return "";
	case SET_TRANS_FREQ_RANGE: return "";
	case GET_TRANS_FREQ_RANGE: return "";
	case SET_REVER_CHAN_RATE: return "";
	case GET_REVER_CHAN_RATE: return "";
	case SET_REVER_CODE_MODE: return "";
	case GET_REVER_CODE_MODE: return "";
	case SET_ANTENNA_ATTR: return "";
	case GET_ANTENNA_ATTR: return "";
	case SET_ANTENNA_GAIN: return "";
	case GET_ANTENNA_GAIN: return "";
	case SET_CARR_ENABLE: return "";
	case GET_CARR_ENABLE: return "";
	case SET_FPGA_THRESH: return "";
	case GET_FPGA_THRESH: return "";
	case SET_ANTI_COLL_PROTO: return "";
	case GET_ANTI_COLL_PROTO: return "";
	case SET_Q_VALUE: return "";
	case GET_Q_VALUE: return "";
	case SET_MODUL_MODE: return "";
	case GET_MODUL_MODE: return "";
	case SET_TC_VALUE: return "";
	case GET_TC_VALUE: return "";
	case SET_SJC_VALUE: return "";
	case GET_SJC_VALUE: return "";
	case SIGNAL_CHECK: return "";
	case START_CONTI_CHECK: return "";
	case STOP_CONTI_CHECK: return "";
	case SET_WRITE_TAG: return "";
	case GET_RADIO_PARAM: return "";
	case SET_DIG_ATTEN: return "";
	case GET_DIG_ATTEN: return "";
	case SET_PA_ENABLE: return "";
	case GET_PA_ENABLE: return "";
	case START_RADIO_WORK: return "";
	case STOP_RADIO_WORK: return "";
	case REBOOT_RADIO_MODULE: return "";
	case REQ_RADIO_UPGRADE: return "";
	case MID_UPGRADE_PACK: return "";
	case LAST_UPGRADE_PACK: return "";
	case EVT_UPGRADE_SUCC: return "";
	case EVT_UPGRADE_FAIL: return "";
	case GET_RADIO_STATUS: return "";
	default: return "<unknown request>";
    }
}

#endif /* __RADIO_H */
