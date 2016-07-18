
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
#ifndef __UHF_H
#define __UHF_H

#include "upper.h"
#include "radio.h"
#include "security.h"
#include "file.h"
#include "sql.h"
#include "xml.h"

#define false			0
#define true			1

#define NO_ERROR		0
#define FAILED			1

typedef struct uhf_info {
	int status;
	int sec_auth_status;
	uint64_t serial;

	pthread_t heartbeat_thread;

	upper_info_t *upper;
	security_info_t *security;
	radio_info_t *radio;

	struct xmlConfigInfo xmlConfig;
} uhf_info_t;

#endif
