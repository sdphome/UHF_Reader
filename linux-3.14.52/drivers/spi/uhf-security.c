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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/spi/uhf-security.h>

static int uhf_security_probe(struct spi_device *spi)
{
    printk(KERN_ALERT "Enter %s\n", __func__);
    return 0;
}

static int uhf_security_remove(struct spi_device *spi)
{
    printk(KERN_ALERT "Enter %s\n", __func__);
    return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id uhf_security_of_match[] = {
    { .compatible = "jzt,uhf_security" },
    { /* sentinel */ }
};
#endif

static struct spi_driver uhf_security_driver = {
    .driver = {
        .owner  = THIS_MODULE,
        .name   = "uhf_security",
        .of_match_table = of_match_ptr(uhf_security_of_match),
    },
    .probe = uhf_security_probe,
    .remove= uhf_security_remove,
};

module_spi_driver(uhf_security_driver);


MODULE_AUTHOR("Shao Depeng <dp.shao@gmail.com>");
MODULE_DESCRIPTION("UHF security module driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:uhf_security");
