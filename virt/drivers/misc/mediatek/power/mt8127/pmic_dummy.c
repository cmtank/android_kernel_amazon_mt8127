
#include <generated/autoconf.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/kthread.h>
#include <linux/wakelock.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/aee.h>
#include <linux/xlog.h>
#include <linux/proc_fs.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/writeback.h>

#include <asm/uaccess.h>

#include <mach/pmic_mt6397_sw.h>
#include <mach/upmu_common.h>
#include <mach/upmu_hw.h>
#include <mach/mt_pm_ldo.h>
//#include <mach/mt6320_pmic_feature_api.h>
#include <mach/eint.h>
#include <mach/mt_pmic_wrap.h>
#include <mach/mt_gpio.h>
#include <mach/mtk_rtc.h>
#include <mach/mt_spm_mtcmos.h>
#include <mach/charging.h>

#include <mach/mt_clkmgr.h>

#define GPIO_SRCLKENA_PIN         (GPIO12 | 0x80000000)

//==============================================================================
// PMIC lock/unlock APIs
//==============================================================================
void pmic_lock(void)
{

}

void pmic_unlock(void)
{

}

//==============================================================================
// PMIC read/write APIs
//==============================================================================
S32 pwrap_read(U32 adr, U32 *rdata)
{
	return 0;
}
EXPORT_SYMBOL(pwrap_read);

S32 pwrap_write(U32 adr, U32 wdata)
{
	return 0;
}
EXPORT_SYMBOL(pwrap_write);


kal_uint32 upmu_get_reg_value(kal_uint32 reg)
{
    return 0;
}

void upmu_set_reg_value(kal_uint32 reg, kal_uint32 reg_val)
{

}

//==============================================================================
// PMIC-AUXADC 
//==============================================================================

int PMIC_IMM_GetOneChannelValue(int dwChannel, int deCount, int trimd)
{
    return 0;
    
}


void upmu_interrupt_chrdet_int_en(kal_uint32 val)
{
    xlog_printk(ANDROID_LOG_INFO, "Power/PMIC", "[upmu_interrupt_chrdet_int_en] val=%d.\r\n", val);
    upmu_set_rg_int_en_chrdet(val);
}
EXPORT_SYMBOL(upmu_interrupt_chrdet_int_en);

//==============================================================================
// PMIC Interrupt service
//==============================================================================


void mt6397_pmic_eint_irq(void)
{

}

void PMIC_EINT_SETTING(void)
{

}

void PMIC_DUMP_ALL_Register(void)
{

}

U32 pmic_read_interface (U32 RegNum, U32 *val, U32 MASK, U32 SHIFT)
{
    return 0;
}

U32 pmic_config_interface (U32 RegNum, U32 val, U32 MASK, U32 SHIFT)
{
    U32 return_value = 0;
    return return_value;
}


U32 pmic_read_interface_nolock (U32 RegNum, U32 *val, U32 MASK, U32 SHIFT)
{
    return 0;
}

U32 pmic_config_interface_nolock (U32 RegNum, U32 val, U32 MASK, U32 SHIFT)
{
    return 0;
}

void ldo_service_test(void)
{

}


int pmic_get_gpu_status_bit_info(void)
{
    return 1;
}
EXPORT_SYMBOL(pmic_get_gpu_status_bit_info);

int get_spm_gpu_status(void)
{
    return 0;
}

void pmic_gpu_power_enable(int power_en)
{
    
}
EXPORT_SYMBOL(pmic_gpu_power_enable);



static int pmic_mt6397_probe(struct platform_device *dev)
{
    return 0;
}

static int pmic_mt6397_remove(struct platform_device *dev)
{
    xlog_printk(ANDROID_LOG_INFO, "Power/PMIC", "******** MT6397 pmic driver remove!! ********\n" );

    return 0;
}

static void pmic_mt6397_shutdown(struct platform_device *dev)
{

}

static int pmic_mt6397_suspend(struct platform_device *dev, pm_message_t state)
{
	xlog_printk(ANDROID_LOG_INFO, "Power/PMIC", "[pmic_mt6397_suspend]\n");
	mt_set_gpio_out(GPIO_SRCLKENA_PIN, GPIO_OUT_ZERO);
    return 0;
}

static int pmic_mt6397_resume(struct platform_device *dev)
{
	xlog_printk(ANDROID_LOG_INFO, "Power/PMIC", "[pmic_mt6397_resume]\n");
	mt_set_gpio_out(GPIO_SRCLKENA_PIN, GPIO_OUT_ONE);
    return 0;
}

struct platform_device pmic_mt6397_device = {
    .name   = "pmic_mt6397",
    .id        = -1,
};

static struct platform_driver pmic_mt6397_driver = {
    .probe        = pmic_mt6397_probe,
    .remove        = pmic_mt6397_remove,
    .shutdown    = pmic_mt6397_shutdown,
    .suspend    = pmic_mt6397_suspend,
    .resume        = pmic_mt6397_resume,
    .driver     = {
        .name = "pmic_mt6397",
    },
};

//==============================================================================
// PMIC6397 mudule init/exit
//==============================================================================
static int __init pmic_mt6397_init(void)
{
	int ret,res;
	

	printk("pmic pmic_mt6397_init\n");

	//close pmic clock, which will not use in box platform
	res = enable_clock(MT_CG_INFRA_PMICSPI_SHARE, "PMICSPI_SHARE");
	res = enable_clock(MT_CG_INFRA_PMICWRAP, "PMICWRAP");
	res = enable_clock(MT_CG_TOPCK_PMICSPI, "PMICSPI");
	res = disable_clock(MT_CG_INFRA_PMICSPI_SHARE, "PMICSPI_SHARE");
	res = disable_clock(MT_CG_INFRA_PMICWRAP, "PMICWRAP");
	res = disable_clock(MT_CG_TOPCK_PMICSPI, "PMICSPI");

	    // PMIC device driver register
    ret = platform_device_register(&pmic_mt6397_device);
    if (ret) {
        return ret;
    }
    ret = platform_driver_register(&pmic_mt6397_driver);
    if (ret) {

        return ret;
    }
    return 0;
}

static void __exit pmic_mt6397_exit (void)
{

}

fs_initcall(pmic_mt6397_init);
module_exit(pmic_mt6397_exit);

MODULE_AUTHOR("Tank Hung");
MODULE_DESCRIPTION("MT6397 PMIC Device Driver");
MODULE_LICENSE("GPL");




#include <linux/kernel.h>
#include <linux/xlog.h>
#include <linux/module.h>

#include <mach/pmic_mt6320_sw.h>
#include <mach/upmu_common.h>
#include <mach/upmu_hw.h>

kal_uint32 upmu_get_fchrkey_deb(void)
{
	return 0;
}

kal_uint32 upmu_get_rgs_chr_ldo_det(void)
{
	return 0;
}

U32 upmu_get_rgs_vcdt_hv_det(void)
{
  return 0;
}

U32 upmu_get_rgs_chrdet(void)
{
  return 0;
}

void upmu_set_rg_chr_en(U32 val)
{

}

void upmu_set_rg_csdac_en(U32 val)
{

}

void upmu_set_rg_vcdt_hv_en(U32 val)
{

}

void upmu_set_rg_vcdt_hv_vth(U32 val)
{

}

void upmu_set_rg_cs_en(U32 val)
{

}

void upmu_set_rg_vbat_cv_en(U32 val)
{

}

void upmu_set_rg_vbat_cv_vth(U32 val)
{

}

void upmu_set_rg_cs_vth(U32 val)
{

}

void upmu_set_rg_vbat_ov_vth(U32 val)
{

}

void upmu_set_rg_vbat_ov_en(U32 val)
{

}


U32 upmu_get_rgs_baton_undet(void)
{
  return 0;
}

void upmu_set_baton_tdet_en(U32 val)
{

}

void upmu_set_rg_baton_ht_en(U32 val)
{

}

void upmu_set_rg_baton_en(U32 val)
{

}

void upmu_set_rg_chrwdt_wr(U32 val)
{

}

void upmu_set_rg_chrwdt_en(U32 val)
{

}

void upmu_set_rg_chrwdt_td(U32 val)
{

}

void upmu_set_rg_chrwdt_flag_wr(U32 val)
{

}

void upmu_set_rg_chrwdt_int_en(U32 val)
{

}

void upmu_set_rg_usbdl_set(U32 val)
{

}

void upmu_set_rg_usbdl_rst(U32 val)
{

}

void upmu_set_rg_bc11_rst(U32 val)
{

}

void upmu_set_rg_bc11_bb_ctrl(U32 val)
{

}

void upmu_set_rg_csdac_stp_dec(U32 val)
{

}


void upmu_set_rg_csdac_stp_inc(U32 val)
{

}


void upmu_set_rg_csdac_stp(U32 val)
{

}

void upmu_set_rg_csdac_dly(U32 val)
{

}

void upmu_set_rg_low_ich_db(U32 val)
{

}

void upmu_set_rg_ulc_det_en(U32 val)
{

}

void upmu_set_rg_hwcv_en(U32 val)
{

}

void upmu_set_rg_csdac_mode(U32 val)
{

}

void upmu_set_rg_vcdt_mode(U32 val)
{

}

U32 upmu_get_cid(void)
{
  return 0;
}

void upmu_set_rg_clksq_en_aud(kal_uint32 val)
{
	
}

void upmu_set_rg_bst_drv_1m_ck_pdn(U32 val)
{

}

void upmu_set_rg_fgadc_ana_ck_pdn(U32 val)
{

}

void upmu_set_rg_fgadc_ck_pdn(U32 val)
{

}

void upmu_set_rg_drv_32k_ck_pdn(U32 val)
{

}

void upmu_set_rg_pwrkey_rst_td(U32 val)
{

}

void upmu_set_rg_pwrkey_rst_en(U32 val)
{

}

void upmu_set_rg_homekey_rst_en(U32 val)
{

}

void upmu_set_rg_clksq_en(U32 val)
{

}

U32 upmu_get_pwrkey_deb(void)
{
  return 0;
}

U32 upmu_get_homekey_deb(void)
{
  return 0;
}

void upmu_set_rg_homekey_puen(U32 val)
{

}

void upmu_set_rg_int_en_chrdet(U32 val)
{

}

void upmu_set_vgpu_vosel_trans_en(U32 val)
{

}

void upmu_set_rg_vibr_sw_mode(U32 val)
{

}

void upmu_set_rg_vibr_fr_ori(U32 val)
{

}

void upmu_set_rg_vibr_en(U32 val)
{

}

void upmu_set_rg_vibr_vosel(U32 val)
{

}

void upmu_set_rg_vibr_pwdb(U32 val)
{

}

void upmu_set_isink_dim0_duty(U32 val)
{

}

void upmu_set_isink_dim0_fsel(U32 val)
{

}

void upmu_set_isink_dim1_duty(U32 val)
{

}

void upmu_set_isink_dim1_fsel(U32 val)
{

}

void upmu_set_isink_rsv2_isink0(U32 val)
{

}

void upmu_set_isink_rsv2_isink1(U32 val)
{

}


void upmu_set_isink_rsv2_isink2(U32 val)
{

}

void upmu_set_isink_dim2_duty(U32 val)
{

}

void upmu_set_isink_dim2_fsel(U32 val)
{

}

void upmu_set_isinks_ch2_en(U32 val)
{

}

void upmu_set_isinks_ch1_en(U32 val)
{

}

void upmu_set_isinks_ch0_en(U32 val)
{

}

void upmu_set_isinks_ch0_step(U32 val)
{

}

void upmu_set_isinks_ch0_mode(U32 val)
{

}

void upmu_set_isinks_ch1_step(U32 val)
{

}

void upmu_set_isinks_ch1_mode(U32 val)
{

}

void upmu_set_isinks_ch2_step(U32 val)
{

}

void upmu_set_isinks_ch2_mode(U32 val)
{

}

void upmu_set_isinks_breath0_trf_sel(U32 val)
{

}

void upmu_set_isinks_breath0_ton_sel(U32 val)
{

}

void upmu_set_isinks_breath0_toff_sel(U32 val)
{

}

void upmu_set_isinks_breath1_trf_sel(U32 val)
{

}

void upmu_set_isinks_breath1_ton_sel(U32 val)
{

}

void upmu_set_isinks_breath1_toff_sel(U32 val)
{

}

void upmu_set_isinks_breath2_trf_sel(U32 val)
{

}

void upmu_set_isinks_breath2_ton_sel(U32 val)
{

}


void upmu_set_isinks_breath2_toff_sel(U32 val)
{

}

U32 upmu_get_fg_car_35_32(void)
{
  return 0;
}


U32 upmu_get_fg_car_31_16(void)
{
  return 0;
}

U32 upmu_get_fg_car_15_00(void)
{
  return 0;
}

U32 upmu_get_fg_nter_29_16(void)
{
  return 0;
}

U32 upmu_get_fg_nter_15_00(void)
{
  return 0;
}

U32 upmu_get_fg_current_out(void)
{
  return 0;
}

void upmu_set_rg_fchr_pu_en(kal_uint32 val)
{

}

void upmu_set_rg_isink0_ck_pdn(kal_uint32 val)
{

}

void upmu_set_isink_ch0_mode(kal_uint32 val)
{

}

void upmu_set_isink_ch0_en(kal_uint32 val)
{
  
}

void upmu_set_isink_ch1_en(kal_uint32 val)
{
  
}

void upmu_set_isink_ch2_en(kal_uint32 val)
{
  
}

void upmu_set_isink_ch3_en(kal_uint32 val)
{
  
}

void upmu_set_isink_chop0_en(kal_uint32 val)
{
  
}

void upmu_set_isink_chop1_en(kal_uint32 val)
{
 
}

void upmu_set_isink_chop2_en(kal_uint32 val)
{
  
}

void upmu_set_isink_chop3_en(kal_uint32 val)
{
  
}

void upmu_set_rg_isink0_ck_sel(kal_uint32 val)
{
  
}

void upmu_set_rg_isink1_ck_sel(kal_uint32 val)
{
  
}

void upmu_set_rg_isink2_ck_sel(kal_uint32 val)
{
 
}

void upmu_set_rg_isink3_ck_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_ch0_step(kal_uint32 val)
{
  
}

void upmu_set_isink_breath0_toff_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_breath0_ton_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_breath0_trf_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_ch1_mode(kal_uint32 val)
{
  
}

void upmu_set_isink1_rsv1(kal_uint32 val)
{
  
}

void upmu_set_isink1_rsv0(kal_uint32 val)
{
  
}

void upmu_set_isink_sfstr1_en(kal_uint32 val)
{
  
}

void upmu_set_isink_sfstr1_tc(kal_uint32 val)
{
  
}

void upmu_set_isink_ch1_step(kal_uint32 val)
{
  
}

void upmu_set_isink_breath1_toff_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_breath1_ton_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_breath1_trf_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_ch2_mode(kal_uint32 val)
{
  
}

void upmu_set_isink2_rsv1(kal_uint32 val)
{
  
}


void upmu_set_isink2_rsv0(kal_uint32 val)
{
  
}


void upmu_set_isink_sfstr2_en(kal_uint32 val)
{
  
}

void upmu_set_isink_sfstr2_tc(kal_uint32 val)
{
  
}

void upmu_set_isink_ch2_step(kal_uint32 val)
{
  
}

void upmu_set_isink_breath2_toff_sel(kal_uint32 val)
{
}

void upmu_set_isink_breath2_ton_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_breath2_trf_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_ch3_mode(kal_uint32 val)
{
  
}

void upmu_set_isink3_rsv1(kal_uint32 val)
{
  
}

void upmu_set_isink_dim3_duty(kal_uint32 val)
{
}

void upmu_set_isink3_rsv0(kal_uint32 val)
{
}

void upmu_set_isink_dim3_fsel(kal_uint32 val)
{
  
}

void upmu_set_isink_sfstr3_en(kal_uint32 val)
{
  
}

void upmu_set_isink_sfstr3_tc(kal_uint32 val)
{
  
}

void upmu_set_isink_ch3_step(kal_uint32 val)
{
  
}

void upmu_set_isink_breath3_toff_sel(kal_uint32 val)
{
  
}

void upmu_set_isink_breath3_ton_sel(kal_uint32 val)
{
}

void upmu_set_isink_breath3_trf_sel(kal_uint32 val)
{
}

void upmu_set_rg_isinks_rsv(kal_uint32 val)
{
}

void upmu_set_rg_isink3_double_en(kal_uint32 val)
{

}

void upmu_set_rg_isink2_double_en(kal_uint32 val)
{
}

void upmu_set_rg_isink1_double_en(kal_uint32 val)
{

}

void upmu_set_rg_isink0_double_en(kal_uint32 val)
{
}

void upmu_set_rg_isink3_ck_pdn(kal_uint32 val)
{
}

void upmu_set_rg_isink2_ck_pdn(kal_uint32 val)
{
}

void upmu_set_rg_isink1_ck_pdn(kal_uint32 val)
{
}

void upmu_set_rg_drv_2m_ck_pdn(kal_uint32 val)
{
}

void upmu_set_isink_sfstr0_en(kal_uint32 val)
{
}

void upmu_set_isink_phase_dly_tc(kal_uint32 val)
{
}

void upmu_set_isink_phase0_dly_en(kal_uint32 val)
{
}

void upmu_set_isink_phase1_dly_en(kal_uint32 val)
{
}

void upmu_set_isink_phase2_dly_en(kal_uint32 val)
{
}

void upmu_set_isink_phase3_dly_en(kal_uint32 val)
{
}

void dct_pmic_VIBR_enable(kal_bool dctEnable)
{
}

void upmu_set_vcn_1v8_lp_mode_set(kal_uint32 val)
{
}

void upmu_set_vcn28_on_ctrl(kal_uint32 val)
{
}

void upmu_set_vcn33_on_ctrl_bt(kal_uint32 val)
{
}

kal_uint32 upmu_get_rg_adc_out_wakeup_pchr(void)
{
	return 0;
}

void upmu_set_rg_bc11_bias_en(kal_uint32 val)
{
}


void upmu_set_rg_bc11_vsrc_en(kal_uint32 val)
{
}

void upmu_set_rg_bc11_vref_vth(kal_uint32 val)
{
}

void upmu_set_rg_bc11_cmp_en(kal_uint32 val)
{
}

void upmu_set_rg_bc11_ipu_en(kal_uint32 val)
{
}

void upmu_set_rg_bc11_ipd_en(kal_uint32 val)
{
}

void upmu_set_rg_pchr_flag_en(kal_uint32 val)
{
}

void upmu_set_vcn33_on_ctrl_wifi(kal_uint32 val)
{
}

kal_uint32 upmu_get_rgs_bc11_cmp_out(void)
{
	return 0;
}
void upmu_set_rg_vcn33_vosel(kal_uint32 val)
{
}
//export some api for WMT use
EXPORT_SYMBOL(upmu_set_vcn33_on_ctrl_bt);
EXPORT_SYMBOL(upmu_set_vcn28_on_ctrl);
EXPORT_SYMBOL(upmu_set_vcn_1v8_lp_mode_set);
EXPORT_SYMBOL(upmu_set_vcn33_on_ctrl_wifi);
EXPORT_SYMBOL(upmu_set_rg_vcn33_vosel);

void upmu_set_rg_vgp1_vosel(kal_uint32 val)
{
}

void upmu_set_rg_vgp1_en(kal_uint32 val)
{
}

void upmu_set_rg_vgp2_vosel(kal_uint32 val)
{
}

void upmu_set_rg_vgp2_en(kal_uint32 val)
{
}

void upmu_set_rg_vgp3_vosel(kal_uint32 val)
{
}

void upmu_set_rg_vgp3_en(kal_uint32 val)
{
}
