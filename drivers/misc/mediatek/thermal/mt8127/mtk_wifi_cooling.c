/*
 * Copyright (C) 2015 Lab126, Inc.  All rights reserved.
 * Author: Akwasi Boateng <boatenga@lab126.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/kobject.h>
#include <linux/err.h>
#include <thermal_core.h>

#include "mach/mtk_thermal_monitor.h"
#include "linux/platform_data/mtk_thermal.h"

#define MAX_LEVEL	2
#define MIN_LEVEL	0
#define MAX_STATE	6

int wifi_enable_throttle(int state)
{
	pr_debug("%s, state=%d\n", __func__, state); // wifi team can do wifi throttling here
	return 0;
}

static int mtk_wifi_cooling_get_max_state(struct thermal_cooling_device *cdev, unsigned long *state)
{
	struct mtk_cooler_platform_data *pdata = cdev->devdata;
	*state = pdata->max_state;
	return 0;
}

static int mtk_wifi_cooling_get_cur_state(struct thermal_cooling_device *cdev, unsigned long *state)
{
	struct mtk_cooler_platform_data *pdata = cdev->devdata;
	*state = pdata->state;
	return 0;
}

static int mtk_wifi_cooling_set_cur_state(struct thermal_cooling_device *cdev, unsigned long state)
{
	struct mtk_cooler_platform_data *pdata = cdev->devdata;
	wifi_enable_throttle(state);
	pr_info("%s thermal limit set state = %ld\n", __func__, state);
	pdata->state = state;
	return 0;
}
static ssize_t levels_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct thermal_cooling_device *cdev = container_of(dev, struct thermal_cooling_device, device);
	struct mtk_cooler_platform_data *pdata = cdev->devdata;
	struct thermal_instance *instance;
	int offset = 0;

	if (!pdata)
		return -EINVAL;

	list_for_each_entry(instance, &cdev->thermal_instances, cdev_node) {
		offset += sprintf(buf + offset, "%d %d\n", instance->trip, pdata->levels[instance->trip]);
	}
	return offset;
}

static ssize_t levels_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int level, state;
	struct thermal_cooling_device *cdev = container_of(dev, struct thermal_cooling_device, device);
	struct mtk_cooler_platform_data *pdata = cdev->devdata;

	if (!pdata)
		return -EINVAL;
	if (sscanf(buf, "%d %d\n", &state, &level) != 2)
		return -EINVAL;
	if (state > MAX_STATE || state < 0)
		return -EINVAL;
	if (level < MIN_LEVEL || level > MAX_LEVEL)
		return -EINVAL;

	pdata->levels[state] = level;
	return count;
}

static DEVICE_ATTR(levels, S_IRUGO | S_IWUSR, levels_show, levels_store);

static struct thermal_cooling_device_ops mtk_wifi_cooling_ops = {
	.get_max_state = mtk_wifi_cooling_get_max_state,
	.get_cur_state = mtk_wifi_cooling_get_cur_state,
	.set_cur_state = mtk_wifi_cooling_set_cur_state,
};

static int mtk_wifi_cooling_probe(struct platform_device *pdev)
{
	struct mtk_cooler_platform_data *pdata = dev_get_platdata(&pdev->dev);

	if (!pdata)
		return -EINVAL;

	pdata->cdev = thermal_cooling_device_register(pdata->type, pdata, &mtk_wifi_cooling_ops);

	if (IS_ERR(pdata->cdev)) {
		dev_err(&pdev->dev, "Failed to register wifi cooling device\n");
		return PTR_ERR(pdata->cdev);
	}

	platform_set_drvdata(pdev, pdata->cdev);
	device_create_file(&pdata->cdev->device, &dev_attr_levels);
	dev_info(&pdev->dev, "Cooling device registered: %s\n",	pdata->cdev->type);

	return 0;
}

static int mtk_wifi_cooling_remove(struct platform_device *pdev)
{
	struct thermal_cooling_device *cdev = platform_get_drvdata(pdev);

	thermal_cooling_device_unregister(cdev);

	return 0;
}

static struct platform_driver mtk_wifi_cooling_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "mtk-wifi-cooling",
	},
	.probe = mtk_wifi_cooling_probe,
	.remove = mtk_wifi_cooling_remove,
};

static struct mtk_cooler_platform_data mtk_wifi_cooling_pdata = {
	.type = "wifi",
	.state = 0,
	.max_state = MAX_STATE,
};

static struct platform_device mtk_wifi_cooling_device = {
	.name = "mtk-wifi-cooling",
	.id = -1,
	.dev = {
		.platform_data = &mtk_wifi_cooling_pdata,
	},
};

static int __init mtk_wifi_cooling_init(void)
{
	int ret;
	ret = platform_driver_register(&mtk_wifi_cooling_driver);
	if (ret) {
		pr_err("Unable to register wifi cooling driver (%d)\n", ret);
		return ret;
	}
	ret = platform_device_register(&mtk_wifi_cooling_device);
	if (ret) {
		pr_err("Unable to register wifi cooling device (%d)\n", ret);
		return ret;
	}
	return 0;
}

static void __exit mtk_wifi_cooling_exit(void)
{
	platform_driver_unregister(&mtk_wifi_cooling_driver);
	platform_device_unregister(&mtk_wifi_cooling_device);
}

module_init(mtk_wifi_cooling_init);
module_exit(mtk_wifi_cooling_exit);
