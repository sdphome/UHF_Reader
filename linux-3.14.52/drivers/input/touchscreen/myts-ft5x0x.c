/*
 * MYZR Technology Co.,Ltd
 * http://www.myzr.com.cn
 * Tang Bin <tangb@myzr.com.cn>
 */

#define DEBUG

#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/of_gpio.h>
#include <linux/input/mt.h>
#include <linux/input/myts-ft5x0x.h>

#define TOUCH_EVENT_DOWN		0x00
#define TOUCH_EVENT_UP			0x01
#define TOUCH_EVENT_ON			0x02
#define TOUCH_EVENT_RESERVED	0x03

#define MAX_SUPPORT_POINTS		5
#define MYTS_NAME_LEN			16
#define MYTS_DATA_LEN			33

#define SCREEN_MAX_X			1024
#define SCREEN_MAX_Y			600

#define EVT_TYPE	0
#define EVENT_X		1
#define EVENT_Y		2

struct myts_ft5x0x_ts_data {
	struct i2c_client *client;
	struct input_dev *input;
	struct mutex mutex;
	u16 num_x;
	u16 num_y;

	int reset_pin;
	int irq_pin;
	int wake_pin;
	int version;

	bool factory_mode;

	char name[MYTS_NAME_LEN];
	u8 buffer[MYTS_DATA_LEN];
	u8 unused[3];
	int abs_data[3][MAX_SUPPORT_POINTS];
};

static int myts_ft5x0x_readwrite(struct i2c_client *client,
				   u16 wr_len, u8 *wr_buf,
				   u16 rd_len, u8 *rd_buf)
{
	struct i2c_msg wrmsg[2];
	int i = 0;
	int ret;

	if (wr_len) {
		wrmsg[i].addr  = client->addr;
		wrmsg[i].flags = 0;
		wrmsg[i].len = wr_len;
		wrmsg[i].buf = wr_buf;
		i++;
	}
	if (rd_len) {
		wrmsg[i].addr  = client->addr;
		wrmsg[i].flags = I2C_M_RD;
		wrmsg[i].len = rd_len;
		wrmsg[i].buf = rd_buf;
		i++;
	}

	ret = i2c_transfer(client->adapter, wrmsg, i);
	if (ret < 0)
		return ret;
	if (ret != i)
		return -EIO;

	return 0;
}

static irqreturn_t myts_ft5x0x_isr(int irq, void *dev_id)
{
	struct myts_ft5x0x_ts_data *tsdata = dev_id;
	struct device *dev = &tsdata->client->dev;
	struct input_dev *ts_input = tsdata->input;
	int *ptr_type = tsdata->abs_data[0];
	int *ptr_x = tsdata->abs_data[1];
	int *ptr_y = tsdata->abs_data[2];
	u8 *ts_buf = tsdata->buffer;

	int offset, tplen, i, id, error;

	memset(ts_buf, 0, sizeof(ts_buf));
	ts_buf[0] = 0;
	error = myts_ft5x0x_readwrite(tsdata->client,
			1, ts_buf, MYTS_DATA_LEN, ts_buf);
	if (error) {
		dev_err_ratelimited(dev, "Unable to fetch data, error: %d\n",
				    error);
		goto out;
	}
	
	offset = 3;
	tplen = 6;
	memset(tsdata->abs_data, 0, sizeof(tsdata->abs_data));
	for (i = 0; i < MAX_SUPPORT_POINTS; i++) {
		u8 *buf = &ts_buf[i * tplen + offset];
		bool down;

		ptr_type[i] = buf[0] >> 6;
		if (ptr_type[i] == TOUCH_EVENT_RESERVED)
			continue;

		ptr_x[i] = ((buf[0] << 8) | buf[1]) & 0x0fff;
		ptr_y[i] = ((buf[2] << 8) | buf[3]) & 0x0fff;
		id = (buf[2] >> 4) & 0x0f;
		down = (ptr_type[i] != TOUCH_EVENT_UP);

		input_mt_slot(ts_input, id);
		input_mt_report_slot_state(ts_input, MT_TOOL_FINGER, down);

		if (!down)
			continue;

		input_report_abs(ts_input, ABS_MT_POSITION_X, ptr_x[i]);
		input_report_abs(ts_input, ABS_MT_POSITION_Y, ptr_y[i]);
	}

	dev_dbg(dev, "%d:%d,%d %d:%d,%d %d:%d,%d %d:%d,%d %d:%d,%d\n",
			ptr_type[0], ptr_x[0], ptr_y[0],
			ptr_type[1], ptr_x[1], ptr_y[1],
			ptr_type[2], ptr_x[2], ptr_y[2],
			ptr_type[3], ptr_x[3], ptr_y[3],
			ptr_type[4], ptr_x[4], ptr_y[4]);

	input_mt_report_pointer_emulation(ts_input, true);
	input_sync(ts_input);

out:
	return IRQ_HANDLED;
}

static int myts_ft5x0x_reset(struct i2c_client *client,
			struct myts_ft5x0x_ts_data *tsdata)
{
	int error;

	if (gpio_is_valid(tsdata->wake_pin)) {
		error = devm_gpio_request_one(&client->dev,
					tsdata->wake_pin, GPIOF_OUT_INIT_LOW,
					"myts-ft5x0x wake");
		if (error) {
			dev_err(&client->dev,
				"Failed to request GPIO %d as wake pin, error %d\n",
				tsdata->wake_pin, error);
			return error;
		}

		msleep(5);
		gpio_set_value(tsdata->wake_pin, 1);
	}
	if (gpio_is_valid(tsdata->reset_pin)) {
		error = devm_gpio_request_one(&client->dev,
					tsdata->reset_pin, GPIOF_OUT_INIT_LOW,
					"myts-ft5x0x reset");
		if (error) {
			dev_err(&client->dev,
				"Failed to request GPIO %d as reset pin, error %d\n",
				tsdata->reset_pin, error);
			return error;
		}

		msleep(5);
		gpio_set_value(tsdata->reset_pin, 1);
		msleep(300);
	}

	return 0;
}

static int myts_ft5x0x_identify(struct i2c_client *client,
					struct myts_ft5x0x_ts_data *tsdata)
{
	int error;
	u8 ret;
	
	tsdata->num_x = SCREEN_MAX_X;
	tsdata->num_y = SCREEN_MAX_Y;
	strlcpy(tsdata->name, "myts-ft5x0x", 12);
	error = myts_ft5x0x_readwrite(client, 1, "\xA6", 1, &ret);
	if (error)
		return error;
	tsdata->version = ret;

	return 0;
}

#ifdef CONFIG_OF
static int myts_ft5x0x_probe_dt(struct device *dev,
				struct myts_ft5x0x_ts_data *tsdata)
{
	struct device_node *np = dev->of_node;

	tsdata->irq_pin = -EINVAL;
	tsdata->reset_pin = of_get_named_gpio(np, "reset-gpios", 0);
	tsdata->wake_pin = of_get_named_gpio(np, "wake-gpios", 0);

	return 0;
}
#else
static inline int myts_ft5x0x_probe_dt(struct device *dev,
					struct myts_ft5x0x_ts_data *tsdata)
{
	return -ENODEV;
}
#endif

static int myts_ft5x0x_probe(struct i2c_client *client,
					 const struct i2c_device_id *id)
{
	const struct myts_ft5x0x_platform_data *pdata =
						dev_get_platdata(&client->dev);
	struct myts_ft5x0x_ts_data *tsdata;
	struct input_dev *input;
	int error;

	dev_dbg(&client->dev, "probing for myzr ft5x0x module\n");

	tsdata = devm_kzalloc(&client->dev, sizeof(*tsdata), GFP_KERNEL);
	if (!tsdata) {
		dev_err(&client->dev, "failed to allocate driver data.\n");
		return -ENOMEM;
	}

	if (!pdata) {
		error = myts_ft5x0x_probe_dt(&client->dev, tsdata);
		if (error) {
			dev_err(&client->dev,
				"DT probe failed and no platform data present\n");
			return error;
		}
	} else {
		tsdata->reset_pin = pdata->reset_pin;
		tsdata->irq_pin = pdata->irq_pin;
		tsdata->wake_pin = -EINVAL;
	}

	error = myts_ft5x0x_reset(client, tsdata);
	if (error)
		return error;

	if (gpio_is_valid(tsdata->irq_pin)) {
		error = devm_gpio_request_one(&client->dev, tsdata->irq_pin,
					GPIOF_IN, "myts-ft5x0x irq");
		if (error) {
			dev_err(&client->dev,
				"Failed to request GPIO %d, error %d\n",
				tsdata->irq_pin, error);
			return error;
		}
	}

	input = devm_input_allocate_device(&client->dev);
	if (!input) {
		dev_err(&client->dev, "failed to allocate input device.\n");
		return -ENOMEM;
	}

	mutex_init(&tsdata->mutex);
	tsdata->client = client;
	tsdata->input = input;
	tsdata->factory_mode = false;

	error = myts_ft5x0x_identify(client, tsdata);
	if (error) {
		dev_err(&client->dev, "touchscreen probe failed\n");
		return error;
	}

	dev_dbg(&client->dev,
		"Model: %s, Rev.%d, %dx%d sensors\n",
		tsdata->name, tsdata->version, tsdata->num_x, tsdata->num_y);

	input->name = tsdata->name;
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;

	__set_bit(EV_SYN, input->evbit);
	__set_bit(EV_KEY, input->evbit);
	__set_bit(EV_ABS, input->evbit);
	__set_bit(BTN_TOUCH, input->keybit);
	input_set_abs_params(input, ABS_X, 0, tsdata->num_x, 0, 0);
	input_set_abs_params(input, ABS_Y, 0, tsdata->num_y, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_X,
			     0, tsdata->num_x, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y,
			     0, tsdata->num_y, 0, 0);
	error = input_mt_init_slots(input, MAX_SUPPORT_POINTS, 0);
	if (error) {
		dev_err(&client->dev, "Unable to init MT slots.\n");
		return error;
	}

	input_set_drvdata(input, tsdata);
	i2c_set_clientdata(client, tsdata);

	error = devm_request_threaded_irq(&client->dev, client->irq, NULL,
					myts_ft5x0x_isr,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					client->name, tsdata);
	if (error) {
		dev_err(&client->dev, "Unable to request touchscreen IRQ.\n");
		return error;
	}

	error = input_register_device(input);
	if (error)
		return error;

	device_init_wakeup(&client->dev, 1);

	dev_dbg(&client->dev,
		"MYZR FT5X0X initialized: IRQ %d, WAKE pin %d, Reset pin %d.\n",
		client->irq, tsdata->wake_pin, tsdata->reset_pin);

	return 0;
}

static int myts_ft5x0x_remove(struct i2c_client *client)
{
	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int myts_ft5x0x_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);

	if (device_may_wakeup(dev))
		enable_irq_wake(client->irq);

	return 0;
}

static int myts_ft5x0x_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);

	if (device_may_wakeup(dev))
		disable_irq_wake(client->irq);

	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(myts_ft5x0x_pm_ops,
			 myts_ft5x0x_suspend, myts_ft5x0x_resume);

static const struct i2c_device_id myts_ft5x0x_id[] = {
	{ "myts-ft5316", 0, },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(i2c, myts_ft5x0x_id);

#ifdef CONFIG_OF
static const struct of_device_id myts_ft5x0x_of_match[] = {
	{ .compatible = "myzr,myts-ft5316", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, myts_ft5x0x_of_match);
#endif

static struct i2c_driver myts_ft5x0x_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "myts_ft5x0x",
		.of_match_table = of_match_ptr(myts_ft5x0x_of_match),
		.pm = &myts_ft5x0x_pm_ops,
	},
	.id_table = myts_ft5x0x_id,
	.probe    = myts_ft5x0x_probe,
	.remove   = myts_ft5x0x_remove,
};

module_i2c_driver(myts_ft5x0x_driver);

MODULE_AUTHOR("Tang Bin <tangb@myzr.com.cn>");
MODULE_DESCRIPTION("MYZR FT5X0X Touchscreen Module Driver");
MODULE_LICENSE("GPL");
