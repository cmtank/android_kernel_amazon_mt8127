#include <linux/kernel.h>
#include <linux/string.h>

#include <mach/mtk_rtc.h>
#include <mach/wd_api.h>
extern void wdt_arch_reset(char);


/* this function uses RTC to save state
   Also uses WDT register to save the same state
   This is for projects that does not have RTC
*/
void arch_reset(char mode, const char *cmd)
{
	char reboot = 0;
	int res = 0;
	struct wd_api *wd_api = NULL;

	res = get_wd_api(&wd_api);
	pr_notice("arch_reset: cmd = %s\n", cmd ? : "NULL");
	if (res)
		pr_err("arch_reset, get wd api error %d\n", res);

	if (cmd && !strcmp(cmd, "charger")) {
		/* do nothing */
	} else if (cmd && !strcmp(cmd, "recovery")) {
		rtc_mark_recovery();
		if (!res)
			wd_api->wd_set_persist_data_bit(WD_BOOTMODE_RECOVERY);
	} else if (cmd && !strcmp(cmd, "bootloader")) {
		rtc_mark_fast();
		if (!res)
			wd_api->wd_set_persist_data_bit(WD_BOOTMODE_FASTBOOT);
	} else if (cmd && !strcmp(cmd, "rpmbp")) {
		rtc_mark_rpmbp();
		if (!res)
			wd_api->wd_set_persist_data_bit(WD_BOOTMODE_RPMB_PROGRAM);
	}
#ifdef CONFIG_MTK_KERNEL_POWER_OFF_CHARGING
	else if (cmd && !strcmp(cmd, "kpoc")) {
		rtc_mark_kpoc();
	} else if (cmd && !strcmp(cmd, "enter_kpoc")) {
		rtc_mark_enter_kpoc();
	}
#endif
	else {
		if (rtc_enter_kpoc_detected())
			reboot = 0;
		else
			reboot = 1;
	}

	if (!res)
		wd_api->wd_sw_reset(reboot);
}
