/*
 * UHF security module driver
 *
 * Author: Shao Depeng <dp.shao@gmail.com>
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

#define UHF_SECURITY_SPI_MAX_SPEED_HZ 15000000

struct uhf_security {
    struct spi_device *spi;

    struct class *uhf_class;
    struct cdev cdev;
    int major;
    int minor;
    struct device *dev;

    spinlock_t lock;
    struct semaphore sem;

    struct delayed_work uhf_work;
    struct workqueue_struct *uhf_queue;

    int irq;
    int reset;
    int status;

    int open_idx;
};

#endif /* __LINUX_SPI_UHF_SECURITY_H__ */
