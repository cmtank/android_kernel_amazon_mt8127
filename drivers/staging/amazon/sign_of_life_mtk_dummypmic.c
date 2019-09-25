/*
 * sign_of_life_mtk.c
 *
 * MTK platform implementation
 *
 * Copyright (C) Amazon Technologies Inc. All rights reserved.
 * Yang Liu (yangliu@lab126.com)
 * TODO: Add additional contributor's names.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/vmalloc.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/sign_of_life.h>
#include <mach/mtk_rtc.h>
#include <mach/mt_typedefs.h>
#include <mach/mt_pmic_wrap.h>

#ifdef CONFIG_MTK_PMIC_DUMMY /* No PMIC, need to use WDT instead of RTC */

#include <mach/wd_api.h>


static u32 wd_read() {
	int res = 0, val = 0;
	struct wd_api *wd_api = NULL;

	res = get_wd_api(&wd_api);
	if (!res && wd_api)
		val = wd_api->wd_get_persist_data();
	else
		printk(KERN_ERR"Failed to get wd api\n");

	return val;
}

static void wd_write(u32 data) {
	int res = 0;
	struct wd_api *wd_api = NULL;

	res = get_wd_api(&wd_api);
	if (!res && wd_api)
		wd_api->wd_set_persist_data(data);
	else
		printk(KERN_ERR"Failed to get wd api\n");

	return;
}

static void wd_set_bit(u32 data) {
	int res = 0;
	struct wd_api *wd_api = NULL;

	res = get_wd_api(&wd_api);
	if (!res && wd_api)
		wd_api->wd_set_persist_data_bit(data);
	else
		printk(KERN_ERR"Failed to get wd api\n");

	return;
}


static int (mtk_read_boot_reason)(life_cycle_boot_reason *boot_reason)
{
	u32 wd_breason;

	wd_breason = wd_read();
	printk(KERN_ERR"%s: boot_reason is 0x%x\n", __func__, (u32)(wd_breason));

	if (wd_breason & (1<<WD_SOL_WARM_BOOT_KERNEL_PANIC))
		*boot_reason = WARMBOOT_BY_KERNEL_PANIC;
	else if (wd_breason & (1<<WD_SOL_WARM_BOOT_KERNEL_WDOG))
		*boot_reason = WARMBOOT_BY_KERNEL_WATCHDOG;
	else if (wd_breason & (1<<WD_SOL_WARM_BOOT_HW_WDOG))
		*boot_reason = WARMBOOT_BY_HW_WATCHDOG;
	else if (wd_breason & (1<<WD_SOL_WARM_BOOT_SW))
		*boot_reason = WARMBOOT_BY_SW;
	else if (wd_breason & (1<<WD_SOL_COLD_BOOT_USB))
		*boot_reason = COLDBOOT_BY_USB;
	else if (wd_breason & (1<<WD_SOL_COLD_BOOT_POWER_KEY))
		*boot_reason = COLDBOOT_BY_POWER_KEY;
	else if (wd_breason & (1<<WD_SOL_COLD_BOOT_POWER_SUPPLY))
		*boot_reason = COLDBOOT_BY_POWER_SUPPLY;
	else {
		printk(KERN_ERR"Failed to read boot reason\n");
		return -1;
	}

	return 0;
}

static int (mtk_write_boot_reason)(life_cycle_boot_reason boot_reason)
{
	u32 wd_breason;

	wd_breason = wd_read();
	printk(KERN_ERR"%s: current 0x%x boot_reason 0x%x\n", __func__, wd_breason, boot_reason);

	if (boot_reason == WARMBOOT_BY_KERNEL_PANIC)
		wd_breason = WD_SOL_WARM_BOOT_KERNEL_PANIC;
	else if (boot_reason == WARMBOOT_BY_KERNEL_WATCHDOG)
		wd_breason = WD_SOL_WARM_BOOT_KERNEL_WDOG;
	else if (boot_reason == WARMBOOT_BY_HW_WATCHDOG)
		wd_breason = WD_SOL_WARM_BOOT_HW_WDOG;
	else if (boot_reason == WARMBOOT_BY_SW)
		wd_breason = WD_SOL_WARM_BOOT_SW;
	else if (boot_reason == COLDBOOT_BY_USB)
		wd_breason = WD_SOL_COLD_BOOT_USB;
	else if (boot_reason == COLDBOOT_BY_POWER_KEY)
		wd_breason = WD_SOL_COLD_BOOT_POWER_KEY;
	else if (boot_reason == COLDBOOT_BY_POWER_SUPPLY)
		wd_breason = WD_SOL_COLD_BOOT_POWER_SUPPLY;
	else {
		printk(KERN_ERR"Failed to write boot reason\n");
		return -1;
	}

	wd_set_bit(wd_breason);

	return 0;
}

static int (mtk_read_shutdown_reason)(life_cycle_shutdown_reason *shutdown_reason)
{
	u32 wd_shutdown_reason;

	wd_shutdown_reason = wd_read();
	printk(KERN_ERR"%s: shutdown reason is 0x%x\n", __func__, wd_shutdown_reason);

	if (wd_shutdown_reason & (1<<WD_SOL_SHUTDOWN_LONG_PWR_KEY_PRESS))
		*shutdown_reason = SHUTDOWN_BY_LONG_PWR_KEY_PRESS;
	else if (wd_shutdown_reason & (1<<WD_SOL_SHUTDOWN_SW))
		*shutdown_reason = SHUTDOWN_BY_SW;
	else if (wd_shutdown_reason & (1<<WD_SOL_SHUTDOWN_PWR_KEY))
		*shutdown_reason = SHUTDOWN_BY_PWR_KEY;
	else if (wd_shutdown_reason & (1<<WD_SOL_SHUTDOWN_SUDDEN_PWR_LOSS))
		*shutdown_reason = SHUTDOWN_BY_SUDDEN_POWER_LOSS;
	else if (wd_shutdown_reason & (1<<WD_SOL_SHUTDOWN_UKNOWN))
		*shutdown_reason = SHUTDOWN_BY_UNKNOWN_REASONS;
	else {
		printk(KERN_ERR"Failed to read shutdown reason\n");
		return -1;
	}

	return 0;
}

static int (mtk_write_shutdown_reason)(life_cycle_shutdown_reason shutdown_reason)
{
	u32 wd_shutdown_reason;

	wd_shutdown_reason = wd_read();
	printk(KERN_ERR"%s: shutdown_reason 0x%x\n", __func__, wd_shutdown_reason);

	if (shutdown_reason == SHUTDOWN_BY_LONG_PWR_KEY_PRESS)
		wd_shutdown_reason = WD_SOL_SHUTDOWN_LONG_PWR_KEY_PRESS;
	else if (shutdown_reason == SHUTDOWN_BY_SW)
		wd_shutdown_reason = WD_SOL_SHUTDOWN_SW;
	else if (shutdown_reason == SHUTDOWN_BY_PWR_KEY)
		wd_shutdown_reason = WD_SOL_SHUTDOWN_PWR_KEY;
	else if (shutdown_reason == SHUTDOWN_BY_SUDDEN_POWER_LOSS)
		wd_shutdown_reason = WD_SOL_SHUTDOWN_SUDDEN_PWR_LOSS;
	else if (shutdown_reason == SHUTDOWN_BY_UNKNOWN_REASONS)
		wd_shutdown_reason = WD_SOL_SHUTDOWN_UKNOWN;
	else {
		printk(KERN_ERR"Failed to write shutdown reason\n");
		return -1;
	}

	wd_set_bit(wd_shutdown_reason);

	return 0;
}

static int (mtk_read_thermal_shutdown_reason)(life_cycle_thermal_shutdown_reason *thermal_shutdown_reason)
{
	u32 wd_thermal_shutdown_reason;

	wd_thermal_shutdown_reason = wd_read();
	printk(KERN_ERR"%s: thermal shutdown reason 0x%x\n", __func__, wd_thermal_shutdown_reason);

	if (wd_thermal_shutdown_reason & (1<<WD_SOL_THERMAL_SHUTDOWN_BATTERY))
		*thermal_shutdown_reason = THERMAL_SHUTDOWN_REASON_BATTERY;
	else if (wd_thermal_shutdown_reason & (1<<WD_SOL_THERMAL_SHUTDOWN_PMIC))
		*thermal_shutdown_reason = THERMAL_SHUTDOWN_REASON_PMIC;
	else if (wd_thermal_shutdown_reason & (1<<WD_SOL_THERMAL_SHUTDOWN_SOC))
		*thermal_shutdown_reason = THERMAL_SHUTDOWN_REASON_SOC;
	else if (wd_thermal_shutdown_reason & (1<<WD_SOL_THERMAL_SHUTDOWN_MODEM))
		*thermal_shutdown_reason = THERMAL_SHUTDOWN_REASON_MODEM;
	else if (wd_thermal_shutdown_reason & (1<<WD_SOL_THERMAL_SHUTDOWN_WIFI))
		*thermal_shutdown_reason = THERMAL_SHUTDOWN_REASON_WIFI;
	else if (wd_thermal_shutdown_reason & (1<<WD_SOL_THERMAL_SHUTDOWN_PCB))
		*thermal_shutdown_reason = THERMAL_SHUTDOWN_REASON_PCB;
	else {
		printk(KERN_ERR"Failed to read thermal shutdown reason\n");
		return -1;
	}

	return 0;
}

static int (mtk_write_thermal_shutdown_reason)(life_cycle_thermal_shutdown_reason thermal_shutdown_reason)
{
	u32 wd_thermal_shutdown_reason;

	wd_thermal_shutdown_reason = wd_read();
	printk(KERN_ERR "%s: shutdown_reason 0x%0x\n", __func__, wd_thermal_shutdown_reason);


	if (thermal_shutdown_reason == THERMAL_SHUTDOWN_REASON_BATTERY)
		wd_thermal_shutdown_reason = WD_SOL_THERMAL_SHUTDOWN_BATTERY;
	else if (thermal_shutdown_reason == THERMAL_SHUTDOWN_REASON_PMIC)
		wd_thermal_shutdown_reason = WD_SOL_THERMAL_SHUTDOWN_PMIC;
	else if (thermal_shutdown_reason == THERMAL_SHUTDOWN_REASON_SOC)
		wd_thermal_shutdown_reason = WD_SOL_THERMAL_SHUTDOWN_SOC;
	else if (thermal_shutdown_reason == THERMAL_SHUTDOWN_REASON_MODEM)
		wd_thermal_shutdown_reason = WD_SOL_THERMAL_SHUTDOWN_MODEM;
	else if (thermal_shutdown_reason == THERMAL_SHUTDOWN_REASON_WIFI)
		wd_thermal_shutdown_reason = WD_SOL_THERMAL_SHUTDOWN_WIFI;
	else if (thermal_shutdown_reason == THERMAL_SHUTDOWN_REASON_PCB)
		wd_thermal_shutdown_reason = WD_SOL_THERMAL_SHUTDOWN_PCB;
	else {
		printk(KERN_ERR"Failed to write thermal shutdown reason\n");
		return -1;
	}

	wd_set_bit(wd_thermal_shutdown_reason);

	return 0;
}

static int (mtk_read_special_mode)(life_cycle_special_mode *special_mode)
{
	u32 wd_smode;

	wd_smode = wd_read();
	printk(KERN_ERR"%s: special mode is 0x%x\n", __func__, wd_smode);

	if (wd_smode & (1<<WD_SOL_SPECIAL_MODE_LOW_BATTERY))
		*special_mode = LIFE_CYCLE_SMODE_LOW_BATTERY;
	else if (wd_smode & (1<<WD_SOL_SPECIAL_MODE_WARM_BOOT_USB_CONNECTED))
		*special_mode = LIFE_CYCLE_SMODE_WARM_BOOT_USB_CONNECTED;
	else if (wd_smode & (1<<WD_SOL_SPECIAL_MODE_OTA))
		*special_mode = LIFE_CYCLE_SMODE_OTA;
	else if (wd_smode & (1<<WD_SOL_SPECIAL_MODE_FACTORY_RESET))
		*special_mode = LIFE_CYCLE_SMODE_FACTORY_RESET;
	else {
		printk(KERN_ERR"Failed to read special mode\n");
		return -1;
	}
	return 0;
}

static int (mtk_write_special_mode)(life_cycle_special_mode special_mode)
{
	u32 wd_smode;

	wd_smode = wd_read();
	printk(KERN_ERR"%s: special_mode 0x%x\n", __func__, wd_smode);

	if (special_mode == LIFE_CYCLE_SMODE_LOW_BATTERY)
		wd_smode = WD_SOL_SPECIAL_MODE_LOW_BATTERY;
	else if (special_mode == LIFE_CYCLE_SMODE_WARM_BOOT_USB_CONNECTED)
		wd_smode = WD_SOL_SPECIAL_MODE_WARM_BOOT_USB_CONNECTED;
	else if (special_mode == LIFE_CYCLE_SMODE_OTA)
		wd_smode = WD_SOL_SPECIAL_MODE_OTA;
	else if (special_mode == LIFE_CYCLE_SMODE_FACTORY_RESET)
		wd_smode = WD_SOL_SPECIAL_MODE_FACTORY_RESET;
	else {
		printk(KERN_ERR"Failed to write special mode\n");
		return -1;
	}

	wd_set_bit(wd_smode);

	return 0;
}

int mtk_lcr_reset(void)
{
	u32 data;

	/* clean up all SoL flags */
	/* might need to add lock */
	data = wd_read();
	data &= ~(WD_SOL_BOOT_REASON_MASK | WD_SOL_SHUTDOWN_MASK);
	data &= ~(WD_SOL_THERMAL_SHUTDOWN_MASK | WD_SOL_SPECIAL_MODE_MASK);
	wd_write(data);

	return 0;
}

int life_cycle_platform_init(sign_of_life_ops *sol_ops)
{
	printk(KERN_ERR "%s: Support MTK platform with dummy pmic\n", __func__);
	sol_ops->read_boot_reason = mtk_read_boot_reason;
	sol_ops->write_boot_reason = mtk_write_boot_reason;
	sol_ops->read_shutdown_reason = mtk_read_shutdown_reason;
	sol_ops->write_shutdown_reason = mtk_write_shutdown_reason;
	sol_ops->read_thermal_shutdown_reason = mtk_read_thermal_shutdown_reason;
	sol_ops->write_thermal_shutdown_reason = mtk_write_thermal_shutdown_reason;
	sol_ops->read_special_mode = mtk_read_special_mode;
	sol_ops->write_special_mode = mtk_write_special_mode;
	sol_ops->lcr_reset = mtk_lcr_reset;

	return 0;
}

#endif //CONFIG_MTK_PMIC_DUMMY
