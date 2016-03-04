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

static LIST_HEAD(device_list);
static DEFINE_MUTEX(device_list_lock);

static unsigned bufsiz = 4096;

/*-------------------------------------------------------------------------*/

static int uhf_security_init_gpio(struct uhf_security *uhf)
{
    int ret;
    /*
     * status   gpio3-21  J4-10
     * reset    gpio3-22  J4-12
     */
    ret = devm_gpio_request_one(&uhf->spi->dev, uhf->reset,
                                GPIOF_OUT_INIT_HIGH, "uhf-reset");

    ret += devm_gpio_request_one(&uhf->spi->dev, uhf->status,
                                GPIOF_IN, "uhf-status");

    return ret;
}

static inline void uhf_security_enable_irq(struct uhf_security *uhf)
{
    if (!uhf->irq_enabled) {
        enable_irq(uhf->irq);
        uhf->irq_enabled = true;
    } else {
        printk(KERN_ALERT "%s: irq has been enabled\n", __func__);
    }
}

static inline void uhf_security_disable_irq(struct uhf_security *uhf)
{
    if (uhf->irq_enabled) {
        disable_irq(uhf->irq);
        uhf->irq_enabled = false;
    } else {
        printk(KERN_ALERT "%s: irq has been enabled\n", __func__);
    }
}

/*
 * We can't use the standard synchronous wrappers for file I/O; we
 * need to protect against async removal of the underlying spi_device.
 */
static void uhf_security_complete(void *arg)
{
    complete(arg);
}

static ssize_t uhf_security_sync(struct uhf_security *uhf, struct spi_message *message)
{
    DECLARE_COMPLETION_ONSTACK(done);
    int status;

    message->complete = uhf_security_complete;
    message->context = &done;

    spin_lock_irq(&uhf->lock);
    if (uhf->spi == NULL)
        status = -ESHUTDOWN;
    else
        status = spi_async(uhf->spi, message);
    spin_unlock_irq(&uhf->lock);

    if (status == 0) {
        wait_for_completion(&done);
        status = message->status;
        if (status == 0)
            status = message->actual_length;
    }

    return status;
}

static inline ssize_t uhf_security_sync_write(struct uhf_security *uhf, size_t len)
{
    struct spi_transfer t = {
            .tx_buf     = uhf->buffer,
            .len        = len,
    };
    struct spi_message  m;

    spi_message_init(&m);
    spi_message_add_tail(&t, &m);
    return uhf_security_sync(uhf, &m);
}

static inline ssize_t uhf_security_sync_read(struct uhf_security *uhf, size_t len)
{
    struct spi_transfer t = {
            .tx_buf     = uhf->buffer,
            .len        = len,
    };
    struct spi_message  m;

    spi_message_init(&m);
    spi_message_add_tail(&t, &m);
    return uhf_security_sync(uhf, &m);
}

/*-------------------------------------------------------------------------*/

static int uhf_security_open(struct inode *inode,struct file *filp)
{
    int status = -ENXIO;
    struct uhf_security *uhf = NULL;

    mutex_lock(&device_list_lock);

    list_for_each_entry(uhf, &device_list, device_entry) {
        if (uhf->devt == inode->i_rdev) {
            status = 0;
            break;
        }
    }

    if (status == 0) {
        if (!uhf->buffer) {
            uhf->buffer = kmalloc(bufsiz, GFP_KERNEL);
            if (!uhf->buffer) {
                printk(KERN_ERR "%s: open/ENOMEM\n", __func__);
                status = -ENOMEM;
            }
        }

        if (status == 0) {
            uhf->users ++;
            filp->private_data = uhf;
            nonseekable_open(inode, filp);
        }
    } else
        printk(KERN_ALERT "%s: nothing for minor %d\n", __func__, iminor(inode));

    mutex_unlock(&device_list_lock);

    return status;
}

static int uhf_security_release(struct inode *inode,struct file *filp)
{
    int status = 0;
    struct uhf_security *uhf = NULL;

    mutex_lock(&device_list_lock);
    uhf = filp->private_data;

    filp->private_data = NULL;

    /* last close? */
    uhf->users--;
    if (!uhf->users) {
        int dofree;
        kfree(uhf->buffer);
        uhf->buffer = NULL;

        /* ... after we unbound from the underlying device? */
        spin_lock_irq(&uhf->lock);
        dofree = (uhf->spi == NULL);
        spin_unlock_irq(&uhf->lock);

        if (dofree)
            kfree(uhf);
    }
    mutex_unlock(&device_list_lock);

    return status;
}

ssize_t uhf_security_read (struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    ssize_t ret = 0;
    struct uhf_security *uhf = NULL;

    /* chipselect only toggles at start or end of operation */
    if (count > bufsiz)
        return -EMSGSIZE;

    uhf = filp->private_data;

    mutex_lock(&uhf->buf_lock);
    ret = uhf_security_sync_read(uhf, count);
    if (ret > 0) {
        unsigned long missing;

        missing = copy_to_user(buf, uhf->buffer, ret);
        if (missing == ret)
            ret = -EFAULT;
        else
            ret = ret - missing;
    }
    mutex_unlock(&uhf->buf_lock);

    return ret;
}

ssize_t uhf_security_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    ssize_t ret = 0;
    unsigned long missing;
    struct uhf_security *uhf = NULL;

    /* chipselect only toggles at start or end of operation */
    if (count > bufsiz)
        return -EMSGSIZE;

    uhf = filp->private_data;

    mutex_lock(&uhf->buf_lock);
    missing = copy_from_user(uhf->buffer, buf, count);
    if (missing == 0)
        ret = uhf_security_sync_write(uhf, count);
    else
        ret = -EFAULT;
    mutex_unlock(&uhf->buf_lock);

    return ret;
}

static long uhf_security_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    return 0;
}

#ifdef CONFIG_COMPAT
static long uhf_security_compat_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    return uhf_security_ioctl(filp, cmd, (unsigned long)compat_ptr(arg));
}
#else
#define uhf_security_compat_ioctl NULL
#endif /* CONFIG_COMPAT */

struct file_operations uhf_fops = {
    .owner =    THIS_MODULE,
    .read = uhf_security_read,
    .write = uhf_security_write,
    .unlocked_ioctl = uhf_security_ioctl,
    .compat_ioctl = uhf_security_compat_ioctl,
    .open = uhf_security_open,
    .release = uhf_security_release,
    .llseek = no_llseek,
};

/*-------------------------------------------------------------------------*/

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

static int uhf_security_probe(struct spi_device *spi)
{
    int ret = 0;
    struct uhf_security *uhf = NULL;
    unsigned long minor;

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
    mutex_init(&uhf->buf_lock);

    INIT_LIST_HEAD(&uhf->device_entry);

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

    /*
     * If we can allocate a minor number, hook up this device.
     * Reusing minors is fine so long as udev or mdev is working.
     */

    ret = register_chrdev(UHF_SPI_MAJOR, "spi", &uhf_fops);
    if (ret < 0) {
        printk(KERN_ALERT "%s: register chardev failed.\n", __func__);
        return -ENOMEM;
    }

    /* create class and device for udev information. */
    uhf->class = class_create(THIS_MODULE, "uhf_security");
    if (IS_ERR(uhf->class)) {
        printk(KERN_ERR "failed to create uhf class\n");
        goto class_fail;
    }

    mutex_lock(&device_list_lock);
    minor = find_first_zero_bit(minors, UHF_SPI_MINORS);
    if (minor < UHF_SPI_MINORS) {
        uhf->devt = MKDEV(UHF_SPI_MAJOR, minor);
        uhf->dev = device_create(uhf->class, &spi->dev, uhf->devt,
                    uhf, "uhf_security");
        ret = PTR_ERR_OR_ZERO(uhf->dev);
    } else {
        printk(KERN_ALERT "%s: no minor number available!\n", __func__);
        ret = -ENODEV;
        goto device_fail;
    }

    if (ret == 0) {
        set_bit(minor, minors);
        list_add(&uhf->device_entry, &device_list);
    }
    mutex_unlock(&device_list_lock);

    uhf->spi = spi;
    uhf->irq = spi->irq;
    spi_set_drvdata(spi, uhf);

    ret = uhf_security_init_gpio(uhf);

    ret += device_create_file(uhf->dev, &dev_attr_uhf_security_sys);
    if (ret) {
        printk(KERN_ALERT "%s: create sys file failed.\n", __func__);
        goto sys_fail;
    }

    /* Initializes uhf security INT irq. */
    ret = devm_request_threaded_irq(&spi->dev, uhf->irq, NULL, uhf_security_handler,
                                IRQF_TRIGGER_FALLING | IRQF_ONESHOT, "uhf_irq", uhf);
    if (ret) {
        printk(KERN_ERR "failed to request irq_handler, ret=%d\n", ret);
        goto irq_fail;
    }

    uhf->irq_enabled = true;

    INIT_DELAYED_WORK(&uhf->uhf_work, uhf_security_work_func);
    uhf->uhf_queue = create_workqueue("uhf_wq");
    if (!uhf->uhf_queue){
        printk(KERN_ERR"create singlethread workqueue ERROR\n");
        ret = -ENOMEM;
        goto queue_fail;
    }

    return ret;

queue_fail:
    uhf_security_disable_irq(uhf);
irq_fail:
    device_remove_file(uhf->dev, &dev_attr_uhf_security_sys);
sys_fail:
    device_destroy(uhf->class, uhf->devt);
device_fail:
    class_destroy(uhf->class);
class_fail:
    unregister_chrdev(UHF_SPI_MAJOR, UHF_SECURITY_NAME);
    return ret;
}

static int uhf_security_remove(struct spi_device *spi)
{
    struct uhf_security *uhf = spi_get_drvdata(spi);

    /* make sure ops on existing fds can abort cleanly */
    spin_lock_irq(&uhf->lock);
    uhf->spi = NULL;
    spin_unlock_irq(&uhf->lock);

    uhf_security_disable_irq(uhf);

    /* prevent new opens */
    mutex_lock(&device_list_lock);
    list_del(&uhf->device_entry);

    device_destroy(uhf->class, uhf->devt);
    class_destroy(uhf->class);
    unregister_chrdev(UHF_SPI_MAJOR, UHF_SECURITY_NAME);
    clear_bit(MINOR(uhf->devt), minors);
    mutex_unlock(&device_list_lock);

    if (uhf->users == 0)
        kfree(uhf);


    if (uhf->uhf_queue)
        destroy_workqueue(uhf->uhf_queue);

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
        .name   = UHF_SECURITY_NAME,
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
