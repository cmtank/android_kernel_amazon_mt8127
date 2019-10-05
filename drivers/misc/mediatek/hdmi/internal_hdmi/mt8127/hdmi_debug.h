#ifndef _MT_HDMI_DEBUG_H_
#define _MT_HDMI_DEBUG_H_

#ifdef CONFIG_MTK_INTERNAL_HDMI_SUPPORT

extern unsigned char _bHdcpOff;
extern size_t hdmi_powerenable;
extern size_t hdmidrv_log_on;
extern HDMI_AV_INFO_T _stAvdAVInfo;
extern  HDMI_SINK_AV_CAP_T _HdmiSinkAvCap;
extern unsigned char cDstStr[50];
extern const unsigned char _cFsStr[][7];
extern unsigned char hdmi_plug_test_mode;
/* unsigned int hdmi_plug_out_delay; */
/* unsigned int hdmi_plug_in_delay; */
extern unsigned char is_user_mute_hdmi;
extern unsigned char is_user_mute_hdmi_audio;
extern CEC_LA_ADDRESS _rCECLaAddr;


extern void hdmi_force_plug_out(void);
extern void hdmi_force_plug_in(void);
extern unsigned char hdmi_hdcp_for_avmute;
extern void mt_hdmi_show_info(char *pbuf);
extern void mt_hdmi_debug_write(const char *pbuf);
extern void hdmi_force_plug_out(void);
extern void hdmi_force_plug_in(void);
extern unsigned char hdmi_hdcp_for_avmute;
extern void hdmi_read(unsigned int u2Reg, unsigned int *p4Data);
extern void HDMI_EnableIrq(void);
extern void HDMI_DisableIrq(void);
#endif
#endif
