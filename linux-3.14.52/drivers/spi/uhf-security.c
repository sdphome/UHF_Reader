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
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/gpio.h>
#include <linux/workqueue.h>
#include <linux/semaphore.h>
#include <asm/cache.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <linux/fs.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/errno.h>
#include <linux/spi/uhf-security.h>


struct uhf_security *__uhf = NULL;

static int device_open(struct inode *inode,struct file *filp)
{
    struct uhf_security *uhf = __uhf;
    if (0 == uhf->open_idx) {
        /* power on / reset */
        printk(KERN_ALERT "unf security : open\n");
        uhf->open_idx = 1;
    } else {
        printk(KERN_ALERT "unf security : has opened\n");
    }

    return 0;
}

static int device_release(struct inode *inode,struct file *filp)
{
    struct uhf_security *uhf = __uhf;

    uhf->open_idx = 0;

    return 0;
}

ssize_t device_read (struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    return 0;
}

ssize_t device_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    return 0;
}

static void uhf_security_work_func(struct work_struct *work)
{
    printk(KERN_ALERT "%s\n", __func__);
}

static irqreturn_t uhf_security_handler(int irq, void *handle)
{
    printk(KERN_ALERT "got a interupt!!\n");
    return IRQ_HANDLED;
}

static inline void uhf_security_reset(int reset)
{
    gpio_set_value(reset, GPIOF_INIT_HIGH);
    msleep(1);
    gpio_set_value(reset, GPIOF_INIT_LOW);
    msleep(3);
    gpio_set_value(reset, GPIOF_INIT_HIGH);
    printk(KERN_ALERT "reset security module\n");
}

static inline int uhf_security_get_status(int status)
{
    int value;

    value = gpio_get_value(status);
    if (value == 0)
        return OK;
    else
        return BUSY;
}

static ssize_t uhf_security_sys_show(struct device *dev,
            struct device_attribute *attr, char *buf)
{
    return 0;
}

static ssize_t uhf_security_sys_store(struct device *dev,
            struct device_attribute *attr, const char *buf, size_t size)
{
    int ret;
    struct uhf_security *uhf = __uhf;

    if (strstr(buf,"status") != NULL) {
        ret = uhf_security_get_status(uhf->status);
        printk(KERN_ALERT "uhf security module status is %s.\n", ret == OK ? "OK" : "BUSY");
    } else if (strstr(buf,"reset") != NULL) {
        uhf_security_reset(uhf->reset);
    }

    return size;
}

static DEVICE_ATTR(uhf_security_sys, 0664, uhf_security_sys_show, uhf_security_sys_store);

static int uhf_security_init_gpio(struct uhf_security *uhf)
{
    int ret;
    /*
     * reset    gpio1-14  SD2_DATA1
     * status   gpio1-15  SD2_DATA0
     */
    ret = devm_gpio_request_one(&uhf->spi->dev, uhf->reset,
                                GPIOF_OUT_INIT_HIGH, "uhf-reset");

    ret += devm_gpio_request_one(&uhf->spi->dev, uhf->status,
                                GPIOF_IN, "uhf-status");

    return ret;
}

static int uhf_security_parse_dt(struct spi_device *spi, struct uhf_security *uhf)
{
    struct device_node *np = spi->dev.of_node;

    uhf->reset = of_get_named_gpio(np, "reset-gpio", 0);
    if (!gpio_is_valid(uhf->reset)) {
        dev_err(&spi->dev, "no reset gpio setting in dts\n");
        return -EINVAL;
    }

    uhf->status = of_get_named_gpio(np, "status-gpio", 0);
    if (!gpio_is_valid(uhf->status)) {
        dev_err(&spi->dev, "no reset gpio setting in dts\n");
        return -EINVAL;
    }

    printk(KERN_ALERT "@%s: reset = %d, status=%d\n", __func__, uhf->reset, uhf->status);

    return 0;
}

/******File operations define******/
struct file_operations uhf_fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

static int uhf_security_probe(struct spi_device *spi)
{
    int ret = 0;
    struct uhf_security *uhf = NULL;
    dev_t devid = MKDEV(0, 0);

    printk(KERN_ALERT "Enter %s\n", __func__);

    uhf = devm_kzalloc(&spi->dev, sizeof(struct uhf_security), GFP_KERNEL);
    if (uhf == NULL) {
        dev_err(&spi->dev, "no memory\n");
        return -ENOMEM;
    }

    spi->mode = SPI_MODE_0;
    spi->bits_per_word = 8;
    if (!spi->max_speed_hz)
        spi->max_speed_hz = UHF_SECURITY_SPI_MAX_SPEED_HZ;

    ret = spi_setup(spi);
    if (ret < 0) {
        dev_err(&spi->dev, "setup spi failed\n");
        return ret;
    }

    spin_lock_init(&uhf->lock);
    sema_init(&uhf->sem, 1);

    uhf->spi = spi;
    uhf->irq = spi->irq;
    spi_set_drvdata(spi, uhf);

    if (spi->irq <= 0) {
        dev_err(&spi->dev, "no irq\n");
        return -ENODEV;
    }

    printk(KERN_ALERT "irq no:%d\n", spi->irq);

    ret = uhf_security_parse_dt(spi, uhf);
    if (ret < 0) {
        dev_err(&spi->dev, "parse dts failed\n");
        return -ENODEV;
    }

    /* Initializes a character device. */
    uhf->minor = 0;
    alloc_chrdev_region(&devid, 0, 1, "uhf_security");
    uhf->major = MAJOR(devid);

    cdev_init(&uhf->cdev, &uhf_fops);
    uhf->cdev.owner = THIS_MODULE;

    ret = cdev_add(&uhf->cdev, MKDEV(uhf->major, 0), 1);
    if (ret) {
        printk(KERN_ERR "register character device error");
        goto err1;
    }

    /* create class and device for udev information. */
    uhf->uhf_class = class_create(THIS_MODULE, "uhf_security");
    if (IS_ERR(uhf->uhf_class)) {
        printk(KERN_ERR "failed to create uhf class\n");
        goto err2;
    }

    /*
     * register device in sysfs, and this will cause udev to
     * create corresponding device node.
     */
    uhf->dev = device_create(uhf->uhf_class, NULL,
        MKDEV(uhf->major, uhf->minor), NULL, "uhf_security");
    if (IS_ERR(uhf->dev)) {
        printk(KERN_ERR "failed to create class device\n");
        goto err3;
    }

    ret = uhf_security_init_gpio(uhf);

    ret += device_create_file(uhf->dev, &dev_attr_uhf_security_sys);
    if (ret)
        goto err3;

    /* Initializes uhf security INT irq. */
    ret = devm_request_threaded_irq(&spi->dev, uhf->irq, NULL, uhf_security_handler,
                                IRQF_TRIGGER_FALLING | IRQF_ONESHOT, "uhf_irq", (void *)uhf);
    if (ret) {
        printk(KERN_ERR "failed to request irq_handler, ret=%d\n", ret);
        goto err3;
    } else
        enable_irq(uhf->irq); /* FIXME : need disable_irq */

    INIT_DELAYED_WORK(&uhf->uhf_work, uhf_security_work_func);
    uhf->uhf_queue = create_workqueue("uhf_wq");
    if (!uhf->uhf_queue){
        printk(KERN_ERR"create singlethread workqueue ERROR\n");
        ret = -ENOMEM;
        goto err3;
    }

    __uhf = uhf;

    goto success;

err3:
    printk(KERN_ALERT "device_destroy\n");
    device_destroy(uhf->uhf_class, MKDEV(uhf->major, uhf->minor));
err2:
    printk(KERN_ALERT "class_destroy\n");
    class_destroy(uhf->uhf_class);
err1:
    printk(KERN_ALERT "cdev_del\n");
    cdev_del(&uhf->cdev);
success:
    return ret;
}

static int uhf_security_remove(struct spi_device *spi)
{
    struct uhf_security *uhf = spi_get_drvdata(spi);

    device_destroy(uhf->uhf_class, MKDEV(uhf->major, uhf->minor));
    class_destroy(uhf->uhf_class);
    cdev_del(&uhf->cdev);

    if (uhf->uhf_queue)
        destroy_workqueue(uhf->uhf_queue);

    kfree(uhf); 

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
    .remove = uhf_security_remove,
};

module_spi_driver(uhf_security_driver);


MODULE_AUTHOR("Shao Depeng <dp.shao@gmail.com>");
MODULE_DESCRIPTION("UHF security module driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:uhf_security");
