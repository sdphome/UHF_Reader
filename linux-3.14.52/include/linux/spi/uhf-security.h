/*
 * UHF security module driver
 *
 * Author: Shao Depeng <dp.shao@gmail.com>
 * Copyright 2016 Golden Sky Technology CO.,LTD
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

#ifndef __LINUX_SPI_UHF_SECURITY_H__
#define __LINUX_SPI_UHF_SECURITY_H__

/* security module status */
#define OK 0
#define BUSY 1

#define UHF_SECURITY_NAME    "uhf_security"

#define UHF_SECURITY_SPI_MAX_SPEED_HZ 15000000

/*
 * This supports access to SPI devices using normal userspace I/O calls.
 * Note that while traditional UNIX/POSIX I/O semantics are half duplex,
 * and often mask message boundaries, full SPI support requires full duplex
 * transfers.  There are several kinds of internal message boundaries to
 * handle chipselect management and other protocol options.
 *
 * SPI has a character major number assigned.  We allocate minor numbers
 * dynamically using a bitmask.  You must use hotplug tools, such as udev
 * (or mdev with busybox) to create and destroy the /dev/spidevB.C device
 * nodes, since there is no fixed association of minor numbers with any
 * particular SPI bus or device.
 */
#define UHF_SPI_MAJOR   153 /* assigned */
#define UHF_SPI_MINORS  32  /* ... up to 256 */

#define UHF_SPI_MTU		1500

static DECLARE_BITMAP(minors, UHF_SPI_MINORS);

#define US_IOC_MAGIC			'u'
#define US_IOC_RESET			_IO(US_IOC_MAGIC, 1)
#define US_IOC_GET_STATUS		_IO(US_IOC_MAGIC, 2)
#define US_IOC_RESET_RADIO		_IO(US_IOC_MAGIC, 3)

/*-------------------------------------------------------------------------*/

struct uhf_security_data {
	uint16_t len;
	uint8_t data[UHF_SPI_MTU];
} __packed;
#define UHF_CACHE_NUM	1000
#define UHF_CACHE_SIZE	(sizeof(struct uhf_security_data) * UHF_CACHE_NUM)

struct uhf_security_cache {
	volatile unsigned long recv_buf;
	volatile unsigned long recv_head;
	volatile unsigned long recv_tail;

	wait_queue_head_t inq;
};

struct uhf_security {
    struct spi_device *spi;
    struct list_head device_entry;

    struct class *class;
    dev_t devt;
    struct device *dev;

    spinlock_t lock;
    struct mutex buf_lock;
    struct semaphore sem;

    struct work_struct recv_work;
    struct workqueue_struct *recv_queue;

    bool irq_enabled;

    int irq;
    int reset;
    int status;
	int radio_reset;

	struct uhf_security_cache *cache;

    int users;
};



#endif /* __LINUX_SPI_UHF_SECURITY_H__ */
