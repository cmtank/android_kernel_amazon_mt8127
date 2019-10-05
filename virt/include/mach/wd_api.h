#ifndef _MT_WD_API_H_
#define _MT_WD_API_H_
/* WD MODE MARK BIT */
#define MTK_WDT_REQ_DEBUG_EN_MARK		(0x80000)
#define MTK_WDT_REQ_SPM_THERMAL_MARK		(0x0001)
#define MTK_WDT_REQ_SPM_SCPSYS_MARK		(0x0002)
#define MTK_WDT_REQ_THERMAL_MARK		(1<<18)

typedef enum ext_wdt_mode {
	WDT_IRQ_ONLY_MODE,
	WDT_HW_REBOOT_ONLY_MODE,
	WDT_DUAL_MODE,
} WD_MODE;

typedef enum wk_wdt_en {
	WK_WDT_DIS,
	WK_WDT_EN,
} WD_CTL;


typedef enum wd_restart_type {
	WD_TYPE_NORMAL,
	WD_TYPE_NOLOCK,
} WD_RES_TYPE;

typedef enum wk_req_en {
	WD_REQ_DIS,
	WD_REQ_EN,
} WD_REQ_CTL;

typedef enum wk_req_mode {
	WD_REQ_IRQ_MODE,
	WD_REQ_RST_MODE,
} WD_REQ_MODE;

/* used to store persist data in wdt, each one is one bit */
typedef enum wd_persist_data {
	WD_BOOTMODE_FASTBOOT,      /* 0 */
	WD_BOOTMODE_RPMB_PROGRAM,  /* 1 */
	WD_BOOTMODE_RECOVERY,      /* 2 */

	/* Sign of Life flags, taken from life_cycle_reasons_mtk.c */

	WD_SOL_WARM_BOOT_KERNEL_PANIC, /* 3 */
	WD_SOL_WARM_BOOT_KERNEL_WDOG, 
	WD_SOL_WARM_BOOT_HW_WDOG, 
	WD_SOL_WARM_BOOT_SW, 
	WD_SOL_COLD_BOOT_USB, 
	WD_SOL_COLD_BOOT_POWER_KEY, 
	WD_SOL_COLD_BOOT_POWER_SUPPLY, 

	WD_SOL_SHUTDOWN_LONG_PWR_KEY_PRESS, /* 10 */
	WD_SOL_SHUTDOWN_SW, 
	WD_SOL_SHUTDOWN_PWR_KEY, 
	WD_SOL_SHUTDOWN_SUDDEN_PWR_LOSS, 
	WD_SOL_SHUTDOWN_UKNOWN, 

	WD_SOL_THERMAL_SHUTDOWN_BATTERY, /* 15 */
	WD_SOL_THERMAL_SHUTDOWN_PMIC, 
	WD_SOL_THERMAL_SHUTDOWN_SOC, 
	WD_SOL_THERMAL_SHUTDOWN_MODEM, 
	WD_SOL_THERMAL_SHUTDOWN_WIFI, 
	WD_SOL_THERMAL_SHUTDOWN_PCB, 

	WD_SOL_SPECIAL_MODE_LOW_BATTERY, /* 21 */
	WD_SOL_SPECIAL_MODE_WARM_BOOT_USB_CONNECTED, 
	WD_SOL_SPECIAL_MODE_OTA, 
	WD_SOL_SPECIAL_MODE_FACTORY_RESET, 

} WD_PERSIST_DATA;

#define WD_BOOTMODE_MASK           ((1<<WD_BOOTMODE_FASTBOOT) | (1<<WD_BOOTMODE_RPMB_PROGRAM) | (1<<WD_BOOTMODE_RECOVERY))
#define WD_SOL_BOOT_REASON_MASK    ((1<<WD_SOL_WARM_BOOT_KERNEL_PANIC) | (1<<WD_SOL_WARM_BOOT_KERNEL_WDOG) | \
									(1<<WD_SOL_WARM_BOOT_HW_WDOG) | (1<<WD_SOL_WARM_BOOT_SW) | \
									(1<<WD_SOL_COLD_BOOT_USB) | (1<<WD_SOL_COLD_BOOT_POWER_KEY) | \
									(1<<WD_SOL_COLD_BOOT_POWER_SUPPLY))
#define WD_SOL_SHUTDOWN_MASK       ((1<<WD_SOL_SHUTDOWN_LONG_PWR_KEY_PRESS) | (1<<WD_SOL_SHUTDOWN_SW) | \
									(1<<WD_SOL_SHUTDOWN_PWR_KEY) | (1<<WD_SOL_SHUTDOWN_SUDDEN_PWR_LOSS) | \
									(1<<WD_SOL_SHUTDOWN_UKNOWN))
#define WD_SOL_THERMAL_SHUTDOWN_MASK   ((1<<WD_SOL_THERMAL_SHUTDOWN_BATTERY) | (1<<WD_SOL_THERMAL_SHUTDOWN_PMIC) | \
										(1<<WD_SOL_THERMAL_SHUTDOWN_SOC) | (1<<WD_SOL_THERMAL_SHUTDOWN_MODEM) | \
										(1<<WD_SOL_THERMAL_SHUTDOWN_WIFI) | (1<<WD_SOL_THERMAL_SHUTDOWN_PCB))
#define WD_SOL_SPECIAL_MODE_MASK   ((1<<WD_SOL_SPECIAL_MODE_LOW_BATTERY) | (1<<WD_SOL_SPECIAL_MODE_WARM_BOOT_USB_CONNECTED) | \
									(1<<WD_SOL_SPECIAL_MODE_OTA) | (1<<WD_SOL_SPECIAL_MODE_FACTORY_RESET))

struct wd_api {
	long ready;
	int (*wd_restart) (enum wd_restart_type type);
	int (*wd_cpu_hot_plug_on_notify) (int);
	int (*wd_cpu_hot_plug_off_notify) (int);
	int (*wd_sw_reset) (int);
	int (*wd_config) (enum ext_wdt_mode, int timeout_val);
	int (*wd_disable_ext) (void);
	int (*wd_disable_local) (void);
	int (*wd_disable_all) (void);
	int (*wd_set_mode) (enum ext_wdt_mode);
	int (*wd_aee_confirm_hwreboot) (void);
	void (*wd_suspend_notify) (void);
	void (*wd_resume_notify) (void);
	unsigned int (*wd_get_check_bit) (void);
	unsigned int (*wd_get_kick_bit) (void);
	int (*wd_spmwdt_mode_config) (WD_REQ_CTL en, WD_REQ_MODE mode);
	int (*wd_thermal_mode_config) (WD_REQ_CTL en, WD_REQ_MODE mode);
	int (*wd_dram_reserved_mode) (bool enabled);
	int (*wd_thermal_direct_mode_config) (WD_REQ_CTL en, WD_REQ_MODE mode);
	int (*wd_set_persist_data) (int persistdata);
	int (*wd_set_persist_data_bit) (WD_PERSIST_DATA persistdata);
	int (*wd_get_persist_data) ();
};

int wd_api_init(void);
int get_wd_api(struct wd_api **obj);
#endif				/* _MT_WD_API_H_ */
