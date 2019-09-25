// ---------------------------------------------------------------------------
#ifndef     HDMITX_H
#define     HDMITX_H

/*#define HDMI_DRV "/dev/hdmitx"*/

/* taken from hdmitable.h --- start */
typedef  enum
{
    HDMI_VIDEO_720x480p_60Hz=0,  // 0
    HDMI_VIDEO_720x576p_50Hz,    // 1
    HDMI_VIDEO_1280x720p_60Hz,   // 2
    HDMI_VIDEO_1280x720p_50Hz,   // 3
    HDMI_VIDEO_1920x1080i_60Hz,  // 4
    HDMI_VIDEO_1920x1080i_50Hz,  // 5
    HDMI_VIDEO_1920x1080p_30Hz,  // 6
    HDMI_VIDEO_1920x1080p_25Hz,  // 7
    HDMI_VIDEO_1920x1080p_24Hz,  // 8
    HDMI_VIDEO_1920x1080p_23Hz,  // 9
    HDMI_VIDEO_1920x1080p_29Hz,  // a
    HDMI_VIDEO_1920x1080p_60Hz,  // b
    HDMI_VIDEO_1920x1080p_50Hz,  // c

    HDMI_VIDEO_1280x720p3d_60Hz,   // d
    HDMI_VIDEO_1280x720p3d_50Hz,   // e
    HDMI_VIDEO_1920x1080i3d_60Hz,  // f
    HDMI_VIDEO_1920x1080i3d_50Hz,  // 10
    HDMI_VIDEO_1920x1080p3d_24Hz,  // 11
    HDMI_VIDEO_1920x1080p3d_23Hz,  // 12

    HDMI_VIDEO_RESOLUTION_NUM
}   HDMI_VIDEO_RESOLUTION;

typedef enum
{
  HDMI_DEEP_COLOR_AUTO=0,
  HDMI_NO_DEEP_COLOR,
  HDMI_DEEP_COLOR_10_BIT,
  HDMI_DEEP_COLOR_12_BIT,
  HDMI_DEEP_COLOR_16_BIT
} HDMI_DEEP_COLOR_T;

typedef  enum
{
  SV_I2S = 0,
  SV_SPDIF

} HDMI_AUDIO_INPUT_TYPE_T;

typedef enum// new add 2007/9/12
{
  FS_16K= 0x00,
  FS_22K,
  FS_24K,
  FS_32K,
  FS_44K,
  FS_48K,
  FS_64K,
  FS_88K,
  FS_96K,
  FS_176K,
  FS_192K,
  FS512_44K,//for DSD
  FS_768K,
  FS128_44k,
  FS_128K,
  FS_UNKOWN,
  FS_48K_MAX_CH
} AUDIO_SAMPLING_T;

typedef enum
{
  IEC_48K = 0,
  IEC_96K,
  IEC_192K,
  IEC_768K,
  IEC_44K,
  IEC_88K,
  IEC_176K,
  IEC_705K,
  IEC_16K,
  IEC_22K,
  IEC_24K,
  IEC_32K,


} IEC_FRAME_RATE_T;

typedef enum
{
  HDMI_FS_32K = 0,
  HDMI_FS_44K,
  HDMI_FS_48K,
  HDMI_FS_88K,
  HDMI_FS_96K,
  HDMI_FS_176K,
  HDMI_FS_192K

} HDMI_AUDIO_SAMPLING_T;

typedef enum
{
  PCM_16BIT=0,
  PCM_20BIT,
  PCM_24BIT

} PCM_BIT_SIZE_T;

typedef  enum
{
   HDMI_RGB = 0,
   HDMI_RGB_FULL,
   HDMI_YCBCR_444,
   HDMI_YCBCR_422,
   HDMI_XV_YCC,
   HDMI_YCBCR_444_FULL,
   HDMI_YCBCR_422_FULL

} HDMI_OUT_COLOR_SPACE_T;

typedef  enum
{
  HDMI_RJT_24BIT= 0,
  HDMI_RJT_16BIT,
  HDMI_LJT_24BIT,
  HDMI_LJT_16BIT,
  HDMI_I2S_24BIT,
  HDMI_I2S_16BIT
} HDMI_AUDIO_I2S_FMT_T;

typedef enum
{
    AUD_INPUT_1_0= 0,
    AUD_INPUT_1_1,
    AUD_INPUT_2_0,
    AUD_INPUT_2_1,
    AUD_INPUT_3_0, //C,L,R
    AUD_INPUT_3_1, //C,L,R
    AUD_INPUT_4_0, //L,R,RR,RL
    AUD_INPUT_4_1, //L,R,RR,RL
    AUD_INPUT_5_0,
    AUD_INPUT_5_1,
    AUD_INPUT_6_0,
    AUD_INPUT_6_1,
    AUD_INPUT_7_0,
    AUD_INPUT_7_1,
    AUD_INPUT_3_0_LRS, //LRS
    AUD_INPUT_3_1_LRS, //LRS
    AUD_INPUT_4_0_CLRS,//C,L,R,S
    AUD_INPUT_4_1_CLRS,//C,L,R,S
    //new layout added for DTS
    AUD_INPUT_6_1_Cs,
    AUD_INPUT_6_1_Ch,
    AUD_INPUT_6_1_Oh,
    AUD_INPUT_6_1_Chr,
    AUD_INPUT_7_1_Lh_Rh,
    AUD_INPUT_7_1_Lsr_Rsr,
    AUD_INPUT_7_1_Lc_Rc,
    AUD_INPUT_7_1_Lw_Rw,
    AUD_INPUT_7_1_Lsd_Rsd,
    AUD_INPUT_7_1_Lss_Rss,
    AUD_INPUT_7_1_Lhs_Rhs,
    AUD_INPUT_7_1_Cs_Ch,
    AUD_INPUT_7_1_Cs_Oh,
    AUD_INPUT_7_1_Cs_Chr,
    AUD_INPUT_7_1_Ch_Oh,
    AUD_INPUT_7_1_Ch_Chr,
    AUD_INPUT_7_1_Oh_Chr,
    AUD_INPUT_7_1_Lss_Rss_Lsr_Rsr,
    AUD_INPUT_6_0_Cs,
    AUD_INPUT_6_0_Ch,
    AUD_INPUT_6_0_Oh,
    AUD_INPUT_6_0_Chr,
    AUD_INPUT_7_0_Lh_Rh,
    AUD_INPUT_7_0_Lsr_Rsr,
    AUD_INPUT_7_0_Lc_Rc,
    AUD_INPUT_7_0_Lw_Rw,
    AUD_INPUT_7_0_Lsd_Rsd,
    AUD_INPUT_7_0_Lss_Rss,
    AUD_INPUT_7_0_Lhs_Rhs,
    AUD_INPUT_7_0_Cs_Ch,
    AUD_INPUT_7_0_Cs_Oh,
    AUD_INPUT_7_0_Cs_Chr,
    AUD_INPUT_7_0_Ch_Oh,
    AUD_INPUT_7_0_Ch_Chr,
    AUD_INPUT_7_0_Oh_Chr,
    AUD_INPUT_7_0_Lss_Rss_Lsr_Rsr,
    AUD_INPUT_8_0_Lh_Rh_Cs,
    AUD_INPUT_UNKNOWN = 0xFF

} AUD_CH_NUM_T;
typedef enum
{
    MCLK_128FS,
    MCLK_192FS,
    MCLK_256FS,
    MCLK_384FS,
    MCLK_512FS,
    MCLK_768FS,
    MCLK_1152FS,
}   SAMPLE_FREQUENCY_T;

static const unsigned char HDMI_VIDEO_ID_CODE[HDMI_VIDEO_RESOLUTION_NUM]=
{2, 17,  4, 19, 5, 20, 34,33,32, 32, 34, 16,31};//, , 480P,576P, ,, , ,720P60,720P50,1080I60,1080I50,,,1080P30,1080P25, , , 1080P24, 1080P23.97, 1080P29.97, 1080p60,1080p50

static const unsigned char POSDIV[3][4]=
{
  {0x3, 0x3, 0x3, 0x2},	   // 27Mhz
  {0x2, 0x1, 0x1, 0x1},	   //74Mhz
  {0x1, 0x0, 0x0, 0x0}	   //148Mhz
};

static const unsigned char FBKSEL[3][4]=
{
  {0x1, 0x1, 0x1, 0x1},	   // 27Mhz
  {0x1, 0x0, 0x1, 0x1},	   //74Mhz
  {0x1, 0x0, 0x1, 0x1}	   //148Mhz
};

static const unsigned char FBKDIV[3][4]=
{
  {19, 24, 29, 19},	   // 27Mhz
  {19, 24, 14, 19},	   //74Mhz
  {19, 24, 14, 19}	   //148Mhz
};

static const unsigned char DIVEN[3][4]=
{
  {0x2, 0x1, 0x1, 0x2},	   // 27Mhz
  {0x2, 0x2, 0x2, 0x2},	   //74Mhz
  {0x2, 0x2, 0x2, 0x2}	   //148Mhz
};

static const unsigned char HTPLLBP[3][4]=
{
  {0xc, 0xc, 0x8, 0xc},	   // 27Mhz
  {0xc, 0xf, 0xf, 0xc},	   //74Mhz
  {0xc, 0xf, 0xf, 0xc}	   //148Mhz
};

static const unsigned char HTPLLBC[3][4]=
{
  {0x2, 0x3, 0x3, 0x2},	   // 27Mhz
  {0x2, 0x3, 0x3, 0x2},	   //74Mhz
  {0x2, 0x3, 0x3, 0x2}	   //148Mhz
};

static const unsigned char HTPLLBR[3][4]=
{
  {0x1, 0x1, 0x0, 0x1},	   // 27Mhz
  {0x1, 0x2, 0x2, 0x1},	   //74Mhz
  {0x1, 0x2, 0x2, 0x1}	   //148Mhz
};

#define NCTS_BYTES          0x07
static const unsigned char HDMI_NCTS[7][7][NCTS_BYTES]=
{
  {{0x00, 0x00, 0x69, 0x78, 0x00, 0x10, 0x00}, //32K, 480i/576i/480p@27MHz/576p@27MHz
   {0x00, 0x00, 0xd2, 0xf0, 0x00, 0x10, 0x00}, //32K, 480p@54MHz/576p@54MHz
   {0x00, 0x03, 0x37, 0xf9, 0x00, 0x2d, 0x80}, //32K, 720p@60/1080i@60
   {0x00, 0x01, 0x22, 0x0a, 0x00, 0x10, 0x00}, //32K, 720p@50/1080i@50
   {0x00, 0x06, 0x6f, 0xf3, 0x00, 0x2d, 0x80}, //32K, 1080p@60
   {0x00, 0x02, 0x44, 0x14, 0x00, 0x10, 0x00},  //32K, 1080p@50
   {0x00, 0x01, 0xA5, 0xe0, 0x00, 0x10, 0x00} //32K, 480p@108MHz/576p@108MHz
  },
  {{0x00, 0x00, 0x75, 0x30, 0x00, 0x18, 0x80}, //44K, 480i/576i/480p@27MHz/576p@27MHz
   {0x00, 0x00, 0xea, 0x60, 0x00, 0x18, 0x80}, //44K, 480p@54MHz/576p@54MHz
   {0x00, 0x03, 0x93, 0x87, 0x00, 0x45, 0xac}, //44K, 720p@60/1080i@60
   {0x00, 0x01, 0x42, 0x44, 0x00, 0x18, 0x80}, //44K, 720p@50/1080i@50
   {0x00, 0x03, 0x93, 0x87, 0x00, 0x22, 0xd6}, //44K, 1080p@60
   {0x00, 0x02, 0x84, 0x88, 0x00, 0x18, 0x80},  //44K, 1080p@50
   {0x00, 0x01, 0xd4, 0xc0, 0x00, 0x18, 0x80}  //44K, 480p@108MHz/576p@108MHz
  },
  {{0x00, 0x00, 0x69, 0x78, 0x00, 0x18, 0x00}, //48K, 480i/576i/480p@27MHz/576p@27MHz
   {0x00, 0x00, 0xd2, 0xf0, 0x00, 0x18, 0x00}, //48K, 480p@54MHz/576p@54MHz
   {0x00, 0x02, 0x25, 0x51, 0x00, 0x2d, 0x80}, //48K, 720p@60/1080i@60
   {0x00, 0x01, 0x22, 0x0a, 0x00, 0x18, 0x00}, //48K, 720p@50/1080i@50
   {0x00, 0x02, 0x25, 0x51, 0x00, 0x16, 0xc0}, //48K, 1080p@60
   {0x00, 0x02, 0x44, 0x14, 0x00, 0x18, 0x00},  //48K, 1080p@50
   {0x00, 0x01, 0xA5, 0xe0, 0x00, 0x18, 0x00} //48K, 108p@54MHz/576p@108MHz
  },
  {{0x00, 0x00, 0x75, 0x30, 0x00, 0x31, 0x00},//88K 480i/576i/480p@27MHz/576p@27MHz
   {0x00, 0x00, 0xea, 0x60, 0x00, 0x31, 0x00},//88K 480p@54MHz/576p@54MHz
   {0x00, 0x03, 0x93, 0x87, 0x00, 0x8b, 0x58},//88K, 720p@60/1080i@60
   {0x00, 0x01, 0x42, 0x44, 0x00, 0x31, 0x00},//88K, 720p@50/1080i@50
   {0x00, 0x03, 0x93, 0x87, 0x00, 0x45, 0xac}, //88K, 1080p@60
   {0x00, 0x02, 0x84, 0x88, 0x00, 0x31, 0x00},  //88K, 1080p@50
   {0x00, 0x01, 0xd4, 0xc0, 0x00, 0x31, 0x00}//88K 480p@108MHz/576p@108MHz
  },
  {{0x00, 0x00, 0x69, 0x78, 0x00, 0x30, 0x00},//96K, 480i/576i/480p@27MHz/576p@27MHz
   {0x00, 0x00, 0xd2, 0xf0, 0x00, 0x30, 0x00},//96K, 480p@54MHz/576p@54MHz
   {0x00, 0x02, 0x25, 0x51, 0x00, 0x5b, 0x00},//96K, 720p@60/1080i@60
   {0x00, 0x01, 0x22, 0x0a, 0x00, 0x30, 0x00},//96K, 720p@50/1080i@50
   {0x00, 0x02, 0x25, 0x51, 0x00, 0x2d, 0x80}, //96K, 1080p@60
   {0x00, 0x02, 0x44, 0x14, 0x00, 0x30, 0x00},  //96K, 1080p@50
   {0x00, 0x01, 0xA5, 0xe0, 0x00, 0x30, 0x00}//96K, 480p@108MHz/576p@108MHz
  },
  {{0x00, 0x00, 0x75, 0x30, 0x00, 0x62, 0x00},//176K, 480i/576i/480p@27MHz/576p@27MHz
   {0x00, 0x00, 0xea, 0x60, 0x00, 0x62, 0x00},//176K, 480p@54MHz/576p@54MHz
   {0x00, 0x03, 0x93, 0x87, 0x01, 0x16, 0xb0},//176K, 720p@60/1080i@60
   {0x00, 0x01, 0x42, 0x44, 0x00, 0x62, 0x00},//176K, 720p@50/1080i@50
   {0x00, 0x03, 0x93, 0x87, 0x00, 0x8b, 0x58}, //176K, 1080p@60
   {0x00, 0x02, 0x84, 0x88, 0x00, 0x62, 0x00},  //176K, 1080p@50
   {0x00, 0x01, 0xd4, 0xc0, 0x00, 0x62, 0x00}//176K, 480p@54MHz/576p@54MHz
  },
  {{0x00, 0x00, 0x69, 0x78, 0x00, 0x60, 0x00},//192K, 480i/576i/480p@27MHz/576p@27MHz
   {0x00, 0x00, 0xd2, 0xf0, 0x00, 0x60, 0x00},//192K, 480p@54MHz/576p@54MHz
   {0x00, 0x02, 0x25, 0x51, 0x00, 0xb6, 0x00},//192K, 720p@60/1080i@60
   {0x00, 0x01, 0x22, 0x0a, 0x00, 0x60, 0x00},//192K, 720p@50/1080i@50
   {0x00, 0x02, 0x25, 0x51, 0x00, 0x5b, 0x00}, //192K, 1080p@60
   {0x00, 0x02, 0x44, 0x14, 0x00, 0x60, 0x00},  //192K, 1080p@50
   {0x00, 0x01, 0xA5, 0xe0, 0x00, 0x60, 0x00}//192K, 480p@108MHz/576p@108MHz
  }
};

/////////////////////////////////////////////////////////////
typedef struct _AUDIO_DEC_OUTPUT_CHANNEL_T
{
  unsigned short FL: 1; //bit0
  unsigned short FR: 1; //bit1
  unsigned short LFE: 1; //bit2
  unsigned short FC: 1; //bit3
  unsigned short RL: 1; //bit4
  unsigned short RR: 1; //bit5
  unsigned short RC: 1; //bit6
  unsigned short FLC: 1; //bit7
  unsigned short FRC: 1; //bit8
  unsigned short RRC: 1; //bit9
  unsigned short RLC: 1; //bit10

} HDMI_AUDIO_DEC_OUTPUT_CHANNEL_T;

typedef union _AUDIO_DEC_OUTPUT_CHANNEL_UNION_T
{
  HDMI_AUDIO_DEC_OUTPUT_CHANNEL_T bit;//HDMI_AUDIO_DEC_OUTPUT_CHANNEL_T
  unsigned short word;

} AUDIO_DEC_OUTPUT_CHANNEL_UNION_T;

//////////////////////////////////////////////////////////
typedef   struct _HDMI_AV_INFO_T
{
    HDMI_VIDEO_RESOLUTION e_resolution;
    unsigned char fgHdmiOutEnable;
    unsigned char u2VerFreq;
    unsigned char b_hotplug_state;
    HDMI_OUT_COLOR_SPACE_T e_video_color_space;
    HDMI_DEEP_COLOR_T e_deep_color_bit;
    unsigned char ui1_aud_out_ch_number;
    HDMI_AUDIO_SAMPLING_T e_hdmi_fs;
    unsigned char bhdmiRChstatus[6];
    unsigned char bhdmiLChstatus[6];
    unsigned char bMuteHdmiAudio;
    unsigned char u1HdmiI2sMclk;
	unsigned char u1hdcponoff;
	unsigned char u1audiosoft;
	unsigned char fgHdmiTmdsEnable;
	AUDIO_DEC_OUTPUT_CHANNEL_UNION_T ui2_aud_out_ch;

	unsigned char	e_hdmi_aud_in;
	unsigned char	e_iec_frame;
	unsigned char	e_aud_code;
	unsigned char	u1Aud_Input_Chan_Cnt;
	unsigned char	e_I2sFmt;
}   HDMI_AV_INFO_T;

///////////////////////////////////////////////////////////

/* taken from hdmitable.h --- end */

/* taken from hdmiedid.h -- start */
typedef enum
{
  AVD_BITS_NONE=0,
  AVD_LPCM=1,
  AVD_AC3,
  AVD_MPEG1_AUD,
  AVD_MP3,
  AVD_MPEG2_AUD,
  AVD_AAC,
  AVD_DTS,
  AVD_ATRAC,
  AVD_DSD,
  AVD_DOLBY_PLUS,
  AVD_DTS_HD,
  AVD_MAT_MLP,
  AVD_DST,
  AVD_DOLBY_ATMOS,
  AVD_WMA,
  AVD_CDDA,
  AVD_SACD_PCM,
  AVD_HDCD =0xfe,
  AVD_BITS_OTHERS=0xff
} AUDIO_BITSTREAM_TYPE_T;

typedef enum
{
  EXTERNAL_EDID=0,
  INTERNAL_EDID,
  NO_EDID
} GET_EDID_T;
#define SINK_480P      (1<< 0)
#define SINK_720P60    (1<< 1)
#define SINK_1080I60   (1<< 2)
#define SINK_1080P60   (1<< 3)
#define SINK_480P_1440 (1<< 4)
#define SINK_480P_2880 (1<< 5)
#define SINK_480I      (1<< 6)//actuall 480Ix1440
#define SINK_480I_1440 (1<< 7)//actuall 480Ix2880
#define SINK_480I_2880 (1<< 8)//No this type for 861D
#define SINK_1080P30   (1<< 9)
#define SINK_576P      (1<< 10)
#define SINK_720P50    (1<< 11)
#define SINK_1080I50   (1<< 12)
#define SINK_1080P50   (1<< 13)
#define SINK_576P_1440 (1<< 14)
#define SINK_576P_2880 (1<< 15)
#define SINK_576I      (1<< 16)
#define SINK_576I_1440 (1<< 17)
#define SINK_576I_2880 (1<< 18)
#define SINK_1080P25   (1<< 19)
#define SINK_1080P24   (1<< 20)
#define SINK_1080P23976   (1<< 21)
#define SINK_1080P2997   (1<< 22)

//This HDMI_SINK_VIDEO_COLORIMETRY_T will define what kind of YCBCR
//can be supported by sink.
//And each bit also defines the colorimetry data block of EDID.
#define SINK_YCBCR_444 (1<<0)
#define SINK_YCBCR_422 (1<<1)
#define SINK_XV_YCC709 (1<<2)
#define SINK_XV_YCC601 (1<<3)
#define SINK_METADATA0 (1<<4)
#define SINK_METADATA1 (1<<5)
#define SINK_METADATA2 (1<<6)
#define SINK_RGB       (1<<7)


//HDMI_SINK_VCDB_T Each bit defines the VIDEO Capability Data Block of EDID.
#define SINK_CE_ALWAYS_OVERSCANNED                  (1<<0)
#define SINK_CE_ALWAYS_UNDERSCANNED                 (1<<1)
#define SINK_CE_BOTH_OVER_AND_UNDER_SCAN            (1<<2)
#define SINK_IT_ALWAYS_OVERSCANNED                  (1<<3)
#define SINK_IT_ALWAYS_UNDERSCANNED                 (1<<4)
#define SINK_IT_BOTH_OVER_AND_UNDER_SCAN            (1<<5)
#define SINK_PT_ALWAYS_OVERSCANNED                  (1<<6)
#define SINK_PT_ALWAYS_UNDERSCANNED                 (1<<7)
#define SINK_PT_BOTH_OVER_AND_UNDER_SCAN            (1<<8)
#define SINK_RGB_SELECTABLE                         (1<<9)


//HDMI_SINK_AUDIO_DECODER_T define what kind of audio decoder
//can be supported by sink.
#define   HDMI_SINK_AUDIO_DEC_LPCM        (1<<0)
#define   HDMI_SINK_AUDIO_DEC_AC3         (1<<1)
#define   HDMI_SINK_AUDIO_DEC_MPEG1       (1<<2)
#define   HDMI_SINK_AUDIO_DEC_MP3         (1<<3)
#define   HDMI_SINK_AUDIO_DEC_MPEG2       (1<<4)
#define   HDMI_SINK_AUDIO_DEC_AAC         (1<<5)
#define   HDMI_SINK_AUDIO_DEC_DTS         (1<<6)
#define   HDMI_SINK_AUDIO_DEC_ATRAC       (1<<7)
#define   HDMI_SINK_AUDIO_DEC_DSD         (1<<8)
#define   HDMI_SINK_AUDIO_DEC_DOLBY_PLUS   (1<<9)
#define   HDMI_SINK_AUDIO_DEC_DTS_HD      (1<<10)
#define   HDMI_SINK_AUDIO_DEC_MAT_MLP     (1<<11)
#define   HDMI_SINK_AUDIO_DEC_DST         (1<<12)
#define   HDMI_SINK_AUDIO_DEC_ATMOS       (1<<13)
#define   HDMI_SINK_AUDIO_DEC_WMA         (1<<14)


//Sink audio channel ability for a fixed Fs
#define SINK_AUDIO_2CH   (1<<0)
#define SINK_AUDIO_3CH   (1<<1)
#define SINK_AUDIO_4CH   (1<<2)
#define SINK_AUDIO_5CH   (1<<3)
#define SINK_AUDIO_6CH   (1<<4)
#define SINK_AUDIO_7CH   (1<<5)
#define SINK_AUDIO_8CH   (1<<6)

//Sink supported sampling rate for a fixed channel number
#define SINK_AUDIO_32k (1<<0)
#define SINK_AUDIO_44k (1<<1)
#define SINK_AUDIO_48k (1<<2)
#define SINK_AUDIO_88k (1<<3)
#define SINK_AUDIO_96k (1<<4)
#define SINK_AUDIO_176k (1<<5)
#define SINK_AUDIO_192k (1<<6)

//The following definition is for Sink speaker allocation data block .
#define SINK_AUDIO_FL_FR   (1<<0)
#define SINK_AUDIO_LFE     (1<<1)
#define SINK_AUDIO_FC      (1<<2)
#define SINK_AUDIO_RL_RR   (1<<3)
#define SINK_AUDIO_RC      (1<<4)
#define SINK_AUDIO_FLC_FRC (1<<5)
#define SINK_AUDIO_RLC_RRC (1<<6)

//The following definition is
//For EDID Audio Support, //HDMI_EDID_CHKSUM_AND_AUDIO_SUP_T
#define SINK_BASIC_AUDIO_NO_SUP    (1<<0)
#define SINK_SAD_NO_EXIST          (1<<1)//short audio descriptor
#define SINK_BASE_BLK_CHKSUM_ERR   (1<<2)
#define SINK_EXT_BLK_CHKSUM_ERR    (1<<3)


//The following definition is for the output channel of
//audio decoder AUDIO_DEC_OUTPUT_CHANNEL_T
#define AUDIO_DEC_FL   (1<<0)
#define AUDIO_DEC_FR   (1<<1)
#define AUDIO_DEC_LFE  (1<<2)
#define AUDIO_DEC_FC   (1<<3)
#define AUDIO_DEC_RL   (1<<4)
#define AUDIO_DEC_RR   (1<<5)
#define AUDIO_DEC_RC   (1<<6)
#define AUDIO_DEC_FLC  (1<<7)
#define AUDIO_DEC_FRC  (1<<8)

// (5) Define the EDID relative information
// (5.1) Define one EDID block length
#define EDID_BLOCK_LEN      128
// (5.2) Define EDID header length
#define EDID_HEADER_LEN     8
// (5.3) Define the address for EDID info. (ref. EDID Recommended Practive for EIA/CEA-861)
// Base Block 0
#define EDID_ADDR_HEADER                      0x00
#define EDID_ADDR_VERSION                     0x12
#define EDID_ADDR_REVISION                    0x13
#define EDID_IMAGE_HORIZONTAL_SIZE            0x15
#define EDID_IMAGE_VERTICAL_SIZE              0x16
#define EDID_ADDR_FEATURE_SUPPORT             0x18
#define EDID_ADDR_TIMING_DSPR_1               0x36
#define EDID_ADDR_TIMING_DSPR_2               0x48
#define EDID_ADDR_MONITOR_DSPR_1              0x5A
#define EDID_ADDR_MONITOR_DSPR_2              0x6C
#define EDID_ADDR_EXT_BLOCK_FLAG              0x7E
#define EDID_ADDR_EXTEND_BYTE3                0x03 //EDID address: 0x83
                                                   //for ID receiver if RGB, YCbCr 4:2:2 or 4:4:4
// Extension Block 1:
#define EXTEDID_ADDR_TAG                      0x00
#define EXTEDID_ADDR_REVISION                 0x01
#define EXTEDID_ADDR_OFST_TIME_DSPR           0x02

// (5.4) Define the ID for descriptor block type
// Notice: reference Table 11 ~ 14 of "EDID Recommended Practive for EIA/CEA-861"
#define DETAIL_TIMING_DESCRIPTOR              -1
#define UNKNOWN_DESCRIPTOR                    -255
#define MONITOR_NAME_DESCRIPTOR               0xFC
#define MONITOR_RANGE_LIMITS_DESCRIPTOR       0xFD


// (5.5) Define the offset address of info. within detail timing descriptor block
#define OFST_PXL_CLK_LO       0
#define OFST_PXL_CLK_HI       1
#define OFST_H_ACTIVE_LO      2
#define OFST_H_BLANKING_LO    3
#define OFST_H_ACT_BLA_HI     4
#define OFST_V_ACTIVE_LO      5
#define OFST_V_BLANKING_LO    6
#define OFST_V_ACTIVE_HI      7
#define OFST_FLAGS            17

// (5.6) Define the ID for EDID extension type
#define LCD_TIMING                  0x1
#define CEA_TIMING_EXTENSION        0x01
#define EDID_20_EXTENSION           0x20
#define COLOR_INFO_TYPE0            0x30
#define DVI_FEATURE_DATA            0x40
#define TOUCH_SCREEN_MAP            0x50
#define BLOCK_MAP                   0xF0
#define EXTENSION_DEFINITION        0xFF

// (5.7) Define EDID VSDB header length
#define EDID_VSDB_LEN               0x03
typedef enum
{
  HDMI_SINK_NO_DEEP_COLOR=0,
  HDMI_SINK_DEEP_COLOR_10_BIT=(1<<0),
  HDMI_SINK_DEEP_COLOR_12_BIT=(1<<1),
  HDMI_SINK_DEEP_COLOR_16_BIT=(1<<2)
} HDMI_SINK_DEEP_COLOR_T;

typedef   struct _HDMI_SINK_AV_CAP_T
{
  unsigned int ui4_sink_cea_ntsc_resolution;//use HDMI_SINK_VIDEO_RES_T
  unsigned int ui4_sink_cea_pal_resolution;//use HDMI_SINK_VIDEO_RES_T
  unsigned int ui4_sink_dtd_ntsc_resolution;//use HDMI_SINK_VIDEO_RES_T
  unsigned int ui4_sink_dtd_pal_resolution;//use HDMI_SINK_VIDEO_RES_T
  unsigned int ui4_sink_1st_dtd_ntsc_resolution;//use HDMI_SINK_VIDEO_RES_T
  unsigned int ui4_sink_1st_dtd_pal_resolution;//use HDMI_SINK_VIDEO_RES_T
  unsigned int ui4_sink_native_ntsc_resolution;//use HDMI_SINK_VIDEO_RES_T
  unsigned int ui4_sink_native_pal_resolution;//use HDMI_SINK_VIDEO_RES_T
  unsigned short ui2_sink_colorimetry;//use HDMI_SINK_VIDEO_COLORIMETRY_T
  unsigned short ui2_sink_vcdb_data; //use HDMI_SINK_VCDB_T
  unsigned short ui2_sink_aud_dec;//HDMI_SINK_AUDIO_DECODER_T
  unsigned char ui1_sink_dsd_ch_num;
  unsigned char ui1_sink_pcm_ch_sampling[7];//n: channel number index, value: each bit means sampling rate for this channel number (SINK_AUDIO_32k..)
  unsigned char ui1_sink_pcm_bit_size[7];////n: channel number index, value: each bit means bit size for this channel number
  unsigned char ui1_sink_dst_ch_sampling[7];//n: channel number index, value: each bit means sampling rate for this channel number (SINK_AUDIO_32k..)
  unsigned char ui1_sink_dsd_ch_sampling[7];//n: channel number index, value: each bit means sampling rate for this channel number (SINK_AUDIO_32k..)
  unsigned char ui1_sink_ac3_ch_sampling[7]; /* n: channel number index, value: each bit means sampling rate for this channel number (SINK_AUDIO_32k..) */
  unsigned char ui1_sink_ec3_ch_sampling[7]; /* n: channel number index, value: each bit means sampling rate for this channel number (SINK_AUDIO_32k..) */
  unsigned short ui1_sink_max_tmds_clock;
  unsigned char ui1_sink_spk_allocation;
  unsigned char ui1_sink_content_cnc;
  unsigned char ui1_sink_p_latency_present;
  unsigned char ui1_sink_i_latency_present;
  unsigned char ui1_sink_p_audio_latency;
  unsigned char ui1_sink_p_video_latency;
  unsigned char ui1_sink_i_audio_latency;
  unsigned char ui1_sink_i_video_latency;
  unsigned char e_sink_rgb_color_bit;
  unsigned char e_sink_ycbcr_color_bit;
  unsigned char u1_sink_support_ai; //kenny add 2010/4/25
  unsigned char u1_sink_max_tmds; //kenny add 2010/4/25
  unsigned short ui2_edid_chksum_and_audio_sup;//HDMI_EDID_CHKSUM_AND_AUDIO_SUP_T
  unsigned short ui2_sink_cec_address;
  unsigned char   b_sink_edid_ready;
  unsigned char   b_sink_support_hdmi_mode;
  unsigned char ui1_ExtEdid_Revision;
  unsigned char ui1_Edid_Version;
  unsigned char ui1_Edid_Revision;
  unsigned char ui1_sink_support_ai;
  unsigned char ui1_Display_Horizontal_Size;
  unsigned char ui1_Display_Vertical_Size;
  unsigned char   b_sink_hdmi_video_present;
  unsigned char  ui1_CNC;
  unsigned char   b_sink_3D_present;
  unsigned int ui4_sink_cea_3D_resolution;
}   HDMI_SINK_AV_CAP_T;

typedef   struct  _HDMI_EDID_INFO_T
{
  unsigned int ui4_ntsc_resolution;//use EDID_VIDEO_RES_T, there are many resolution
  unsigned int ui4_pal_resolution;// use EDID_VIDEO_RES_T
  unsigned int ui4_sink_native_ntsc_resolution;//use EDID_VIDEO_RES_T, only one NTSC resolution, Zero means none native NTSC resolution is avaiable
  unsigned int ui4_sink_native_pal_resolution; //use EDID_VIDEO_RES_T, only one resolution, Zero means none native PAL resolution is avaiable
  unsigned int ui4_sink_cea_ntsc_resolution;//use EDID_VIDEO_RES_T
  unsigned int ui4_sink_cea_pal_resolution;//use EDID_VIDEO_RES_T
  unsigned int ui4_sink_dtd_ntsc_resolution;//use EDID_VIDEO_RES_T
  unsigned int ui4_sink_dtd_pal_resolution;//use EDID_VIDEO_RES_T
  unsigned int ui4_sink_1st_dtd_ntsc_resolution;//use EDID_VIDEO_RES_T
  unsigned int ui4_sink_1st_dtd_pal_resolution;//use EDID_VIDEO_RES_T
  unsigned short ui2_sink_colorimetry;//use EDID_VIDEO_COLORIMETRY_T
  unsigned char ui1_sink_rgb_color_bit;//color bit for RGB
  unsigned char ui1_sink_ycbcr_color_bit; // color bit for YCbCr
  unsigned short ui2_sink_aud_dec;// use EDID_AUDIO_DECODER_T
  unsigned char ui1_sink_is_plug_in;//1: Plug in 0:Plug Out
  unsigned int ui4_hdmi_pcm_ch_type;//use EDID_A_FMT_CH_TYPE
  unsigned int ui4_hdmi_pcm_ch3ch4ch5ch7_type;//use EDID_A_FMT_CH_TYPE1
  unsigned int ui4_hdmi_ac3_ch_type; /* use AVD_AC3_CH_TYPE */
  unsigned int ui4_hdmi_ac3_ch3ch4ch5ch7_type; /* use AVD_AC3_CH_TYPE1 */
  unsigned int ui4_hdmi_ec3_ch_type; /* AVD_DOLBY_PLUS_CH_TYPE */
  unsigned int ui4_hdmi_ec3_ch3ch4ch5ch7_type; /* AVD_DOLBY_PLUS_CH_TYPE1 */
  unsigned int ui4_dac_pcm_ch_type;//use EDID_A_FMT_CH_TYPE
  unsigned char ui1_sink_i_latency_present;
  unsigned char ui1_sink_p_audio_latency;
  unsigned char ui1_sink_p_video_latency;
  unsigned char ui1_sink_i_audio_latency;
  unsigned char ui1_sink_i_video_latency;
  unsigned char ui1ExtEdid_Revision;
  unsigned char ui1Edid_Version;
  unsigned char ui1Edid_Revision;
  unsigned char ui1_Display_Horizontal_Size;
  unsigned char ui1_Display_Vertical_Size;
  unsigned int ui4_ID_Serial_Number;
  unsigned int ui4_sink_cea_3D_resolution;
  unsigned char ui1_sink_support_ai;//0: not support AI, 1:support AI
  unsigned short ui2_sink_cec_address;
  unsigned short ui1_sink_max_tmds_clock;
  unsigned short ui2_sink_3D_structure;
  unsigned int ui4_sink_cea_FP_SUP_3D_resolution;
  unsigned int ui4_sink_cea_TOB_SUP_3D_resolution;
  unsigned int ui4_sink_cea_SBS_SUP_3D_resolution;
  unsigned short ui2_sink_ID_manufacturer_name;//(08H~09H)
  unsigned short ui2_sink_ID_product_code;           //(0aH~0bH)
  unsigned int ui4_sink_ID_serial_number;         //(0cH~0fH)
  unsigned char  ui1_sink_week_of_manufacture;   //(10H)
  unsigned char  ui1_sink_year_of_manufacture;   //(11H)  base on year 1990
  unsigned char ui1rawdata_edid[256];
}   HDMI_EDID_INFO_T;


extern void hdmi_checkedid(unsigned char i1noedid);
extern unsigned char hdmi_fgreadedid(unsigned char i1noedid);
extern void vShowEdidInformation(void);
extern void vShowEdidRawData(void);
extern void vClearEdidInfo(void);
extern void hdmi_AppGetEdidInfo(HDMI_EDID_INFO_T *pv_get_info);
extern unsigned char vCheckPcmBitSize(unsigned char ui1ChNumInx);

extern unsigned char hdmi_check_edid_header(void);
/* taken from hdmiedid.h -- end */

/* taken from old hdmitx.h -- start */
typedef enum
{
    HDMI_STATUS_OK = 0,
    HDMI_STATUS_NOT_IMPLEMENTED,
    HDMI_STATUS_ALREADY_SET,
    HDMI_STATUS_ERROR,
} HDMI_STATUS;

typedef enum
{
    SMART_BOOK_DISCONNECTED = 0,
    SMART_BOOK_CONNECTED,
} SMART_BOOK_STATE;

typedef enum
{
    HDMI_POWER_STATE_OFF = 0,
    HDMI_POWER_STATE_ON,
    HDMI_POWER_STATE_STANDBY,
} HDMI_POWER_STATE;

typedef struct
{

} HDMI_CAPABILITY;


typedef enum
{
    HDMI_TO_TV = 0x0,
    HDMI_TO_SMB,
} hdmi_device_type;

typedef enum
{
    HDMI_IS_DISCONNECTED = 0,
    HDMI_IS_CONNECTED = 1,
    HDMI_IS_RES_CHG = 0x11,
} hdmi_connect_status;

#define MAKE_MTK_HDMI_FORMAT_ID(id, bpp)  (((id) << 8) | (bpp))
typedef enum
{
    MTK_HDMI_FORMAT_UNKNOWN = 0,

    MTK_HDMI_FORMAT_RGB565   = MAKE_MTK_HDMI_FORMAT_ID(1, 2),
    MTK_HDMI_FORMAT_RGB888   = MAKE_MTK_HDMI_FORMAT_ID(2, 3),
    MTK_HDMI_FORMAT_BGR888   = MAKE_MTK_HDMI_FORMAT_ID(3, 3),
    MTK_HDMI_FORMAT_ARGB8888 = MAKE_MTK_HDMI_FORMAT_ID(4, 4),
    MTK_HDMI_FORMAT_ABGR8888 = MAKE_MTK_HDMI_FORMAT_ID(5, 4),
    MTK_HDMI_FORMAT_YUV422   = MAKE_MTK_HDMI_FORMAT_ID(6, 2),
    MTK_HDMI_FORMAT_XRGB8888 = MAKE_MTK_HDMI_FORMAT_ID(7, 4),
    MTK_HDMI_FORMAT_XBGR8888 = MAKE_MTK_HDMI_FORMAT_ID(8, 4),
    MTK_HDMI_FORMAT_BPP_MASK = 0xFF,
} MTK_HDMI_FORMAT;

typedef struct
{
    bool is_audio_enabled;
    bool is_video_enabled;
} hdmi_device_status;

typedef struct
{
    void *src_base_addr;
    void *src_phy_addr;
    int src_fmt;
    unsigned int  src_pitch;
    unsigned int  src_offset_x, src_offset_y;
    unsigned int  src_width, src_height;

    int next_buff_idx;
    int identity;
    int connected_type;
    unsigned int security;
#if defined(MTK_OVERLAY_ENGINE_SUPPORT)
    int fenceFd;
#endif
} hdmi_video_buffer_info;


typedef struct
{
    //  Input
    int ion_fd;
    // Output
    unsigned int index; //fence count
    int fence_fd;   //fence fd
} hdmi_buffer_info;

#define MTK_HDMI_NO_FENCE_FD        ((int)(-1)) //((int)(~0U>>1))
#define MTK_HDMI_NO_ION_FD        ((int)(-1))   //((int)(~0U>>1))
#define HDCPKEY_LENGTH_DRM 512

typedef struct
{
    unsigned int u4Addr;
    unsigned int u4Data;
} hdmi_device_write;

typedef struct
{
    unsigned int u4Data1;
    unsigned int u4Data2;
} hdmi_para_setting;

typedef struct
{
    unsigned char u1Hdcpkey[287];
} hdmi_hdcp_key;

typedef struct
{
    unsigned char u1Hdcpkey[HDCPKEY_LENGTH_DRM];
} hdmi_hdcp_drmkey;

typedef struct
{
    unsigned char u1sendsltdata[15];
} send_slt_data;

typedef   struct  _HDMI_EDID_T
{
    unsigned int ui4_ntsc_resolution;//use EDID_VIDEO_RES_T, there are many resolution
    unsigned int ui4_pal_resolution;// use EDID_VIDEO_RES_T
    unsigned int ui4_sink_native_ntsc_resolution;//use EDID_VIDEO_RES_T, only one NTSC resolution, Zero means none native NTSC resolution is avaiable
    unsigned int ui4_sink_native_pal_resolution; //use EDID_VIDEO_RES_T, only one resolution, Zero means none native PAL resolution is avaiable
    unsigned int ui4_sink_cea_ntsc_resolution;//use EDID_VIDEO_RES_T
    unsigned int ui4_sink_cea_pal_resolution;//use EDID_VIDEO_RES_T
    unsigned int ui4_sink_dtd_ntsc_resolution;//use EDID_VIDEO_RES_T
    unsigned int ui4_sink_dtd_pal_resolution;//use EDID_VIDEO_RES_T
    unsigned int ui4_sink_1st_dtd_ntsc_resolution;//use EDID_VIDEO_RES_T
    unsigned int ui4_sink_1st_dtd_pal_resolution;//use EDID_VIDEO_RES_T
    unsigned short ui2_sink_colorimetry;//use EDID_VIDEO_COLORIMETRY_T
    unsigned char ui1_sink_rgb_color_bit;//color bit for RGB
    unsigned char ui1_sink_ycbcr_color_bit; // color bit for YCbCr
    unsigned short ui2_sink_aud_dec;// use EDID_AUDIO_DECODER_T
    unsigned char ui1_sink_is_plug_in;//1: Plug in 0:Plug Out
    unsigned int ui4_hdmi_pcm_ch_type;//use EDID_A_FMT_CH_TYPE
    unsigned int ui4_hdmi_pcm_ch3ch4ch5ch7_type;//use EDID_A_FMT_CH_TYPE1
    unsigned int ui4_hdmi_ac3_ch_type; /* use AVD_AC3_CH_TYPE */
    unsigned int ui4_hdmi_ac3_ch3ch4ch5ch7_type; /* use AVD_AC3_CH_TYPE1 */
    unsigned int ui4_hdmi_ec3_ch_type; /* AVD_DOLBY_PLUS_CH_TYPE */
    unsigned int ui4_hdmi_ec3_ch3ch4ch5ch7_type; /* AVD_DOLBY_PLUS_CH_TYPE1 */
    unsigned int ui4_dac_pcm_ch_type;//use EDID_A_FMT_CH_TYPE
    unsigned char ui1_sink_i_latency_present;
    unsigned char ui1_sink_p_audio_latency;
    unsigned char ui1_sink_p_video_latency;
    unsigned char ui1_sink_i_audio_latency;
    unsigned char ui1_sink_i_video_latency;
    unsigned char ui1ExtEdid_Revision;
    unsigned char ui1Edid_Version;
    unsigned char ui1Edid_Revision;
    unsigned char ui1_Display_Horizontal_Size;
    unsigned char ui1_Display_Vertical_Size;
    unsigned int ui4_ID_Serial_Number;
    unsigned int ui4_sink_cea_3D_resolution;
    unsigned char ui1_sink_support_ai;//0: not support AI, 1:support AI
    unsigned short ui2_sink_cec_address;
    unsigned short ui1_sink_max_tmds_clock;
    unsigned short ui2_sink_3D_structure;
    unsigned int ui4_sink_cea_FP_SUP_3D_resolution;
    unsigned int ui4_sink_cea_TOB_SUP_3D_resolution;
    unsigned int ui4_sink_cea_SBS_SUP_3D_resolution;
    unsigned short ui2_sink_ID_manufacturer_name;//(08H~09H)
    unsigned short ui2_sink_ID_product_code;           //(0aH~0bH)
    unsigned int ui4_sink_ID_serial_number;         //(0cH~0fH)
    unsigned char  ui1_sink_week_of_manufacture;   //(10H)
    unsigned char  ui1_sink_year_of_manufacture;   //(11H)  base on year 1990
    unsigned char ui1rawdata_edid[256];
}   HDMI_EDID_T;

typedef   struct
{
    unsigned int ui4_sink_FP_SUP_3D_resolution;
    unsigned int ui4_sink_TOB_SUP_3D_resolution;
    unsigned int ui4_sink_SBS_SUP_3D_resolution;
}   MHL_3D_SUPP_T;

typedef struct
{
    unsigned char       ui1_la_num;
    unsigned char     e_la[3];
    unsigned short     ui2_pa;
    unsigned short    h_cecm_svc;
} CEC_DRV_ADDR_CFG;

typedef struct
{
    unsigned char destination : 4;
    unsigned char initiator   : 4;
} CEC_HEADER_BLOCK_IO;

typedef struct
{
    CEC_HEADER_BLOCK_IO header;
    unsigned char opcode;
    unsigned char operand[15];
} CEC_FRAME_BLOCK_IO;

typedef struct
{
    unsigned char size;
    unsigned char sendidx;
    unsigned char reTXcnt;
    void *txtag;
    CEC_FRAME_BLOCK_IO blocks;
} CEC_FRAME_DESCRIPTION_IO;

typedef struct _CEC_FRAME_INFO
{
    unsigned char       ui1_init_addr;
    unsigned char       ui1_dest_addr;
    unsigned short      ui2_opcode;
    unsigned char       aui1_operand[14];
    unsigned int      z_operand_size;
}   CEC_FRAME_INFO;

typedef struct _CEC_SEND_MSG
{
       void*         pv_tag;
    CEC_FRAME_INFO      t_frame_info;
    unsigned char       b_enqueue_ok;
} CEC_SEND_MSG;

/* ACK condition */
typedef enum
{
    APK_CEC_ACK_COND_OK = 0,
    APK_CEC_ACK_COND_NO_RESPONSE,
}   APK_CEC_ACK_COND;

/* ACK info */
typedef struct _APK_CEC_ACK_INFO
{
    void*               pv_tag;
    APK_CEC_ACK_COND      e_ack_cond;
}   APK_CEC_ACK_INFO;

typedef struct
{
    unsigned char       ui1_la;
    unsigned short     ui2_pa;
}   CEC_ADDRESS_IO;

typedef struct
{
    unsigned char   u1Size;
    unsigned char   au1Data[14];
}   CEC_GETSLT_DATA;

typedef struct
{
    unsigned int    u1adress;
    unsigned int    pu1Data;
}   READ_REG_VALUE;


typedef struct
{
	unsigned int	cmd;
	unsigned int	result;
}	CEC_USR_CMD_T;


typedef struct
{
    unsigned char   e_hdmi_aud_in;
    unsigned char   e_iec_frame;
    unsigned char   e_hdmi_fs;
    unsigned char   e_aud_code;
    unsigned char   u1Aud_Input_Chan_Cnt;
    unsigned char   e_I2sFmt;
    unsigned char   u1HdmiI2sMclk;
    unsigned char   bhdmi_LCh_status[5];
    unsigned char   bhdmi_RCh_status[5];
}   HDMITX_AUDIO_PARA;

typedef struct
{
    unsigned char current_level;
    unsigned char max_level;
} HDCP_LEVEL;

#define HDMI_IOW(num, dtype)     _IOW('H', num, dtype)
#define HDMI_IOR(num, dtype)     _IOR('H', num, dtype)
#define HDMI_IOWR(num, dtype)    _IOWR('H', num, dtype)
#define HDMI_IO(num)             _IO('H', num)

#define MTK_HDMI_AUDIO_VIDEO_ENABLE             HDMI_IO(1)
#define MTK_HDMI_AUDIO_ENABLE                   HDMI_IO(2)
#define MTK_HDMI_VIDEO_ENABLE                   HDMI_IO(3)
#define MTK_HDMI_GET_CAPABILITY                 HDMI_IOWR(4, HDMI_CAPABILITY)
#define MTK_HDMI_GET_DEVICE_STATUS              HDMI_IOWR(5, hdmi_device_status)
#define MTK_HDMI_VIDEO_CONFIG                   HDMI_IOWR(6, int)
#define MTK_HDMI_AUDIO_CONFIG                   HDMI_IOWR(7, int)
#define MTK_HDMI_FORCE_FULLSCREEN_ON            HDMI_IOWR(8, int)
#define MTK_HDMI_FORCE_FULLSCREEN_OFF           HDMI_IOWR(9, int)
#define MTK_HDMI_IPO_POWEROFF                   HDMI_IOWR(10, int)
#define MTK_HDMI_IPO_POWERON                    HDMI_IOWR(11, int)
#define MTK_HDMI_POWER_ENABLE                   HDMI_IOW(12, int)
#define MTK_HDMI_PORTRAIT_ENABLE                HDMI_IOW(13, int)
#define MTK_HDMI_FORCE_OPEN                     HDMI_IOWR(14, int)
#define MTK_HDMI_FORCE_CLOSE                    HDMI_IOWR(15, int)
#define MTK_HDMI_IS_FORCE_AWAKE                 HDMI_IOWR(16, int)

#define MTK_HDMI_ENTER_VIDEO_MODE               HDMI_IO(17)
#define MTK_HDMI_LEAVE_VIDEO_MODE               HDMI_IO(18)
#define MTK_HDMI_REGISTER_VIDEO_BUFFER          HDMI_IOW(19, hdmi_video_buffer_info)
#define MTK_HDMI_POST_VIDEO_BUFFER              HDMI_IOW(20,  hdmi_video_buffer_info)
#define MTK_HDMI_AUDIO_SETTING                  HDMI_IOWR(21, HDMITX_AUDIO_PARA)


#define MTK_HDMI_FACTORY_MODE_ENABLE            HDMI_IOW(30, int)
#define MTK_HDMI_FACTORY_GET_STATUS             HDMI_IOWR(31, int)
#define MTK_HDMI_FACTORY_DPI_TEST               HDMI_IOWR(32, int)

#define MTK_HDMI_USBOTG_STATUS                  HDMI_IOWR(33, int)
#define MTK_HDMI_GET_DRM_ENABLE                 HDMI_IOWR(34, int)

#define MTK_HDMI_GET_DEV_INFO                   HDMI_IOWR(35, mtk_dispif_info_t)
#define MTK_HDMI_PREPARE_BUFFER                 HDMI_IOW(36, hdmi_buffer_info)
#define MTK_HDMI_SCREEN_CAPTURE                 HDMI_IOW(37, unsigned long)
#define MTK_HDMI_COLOR_RANGE_SETTING            HDMI_IOW(38, int)

#define MTK_HDMI_WRITE_DEV                      HDMI_IOWR(52, hdmi_device_write)
#define MTK_HDMI_READ_DEV                       HDMI_IOWR(53, unsigned int)
#define MTK_HDMI_ENABLE_LOG                     HDMI_IOWR(54, unsigned int)
#define MTK_HDMI_CHECK_EDID                     HDMI_IOWR(55, unsigned int)
#define MTK_HDMI_INFOFRAME_SETTING              HDMI_IOWR(56, hdmi_para_setting)
#define MTK_HDMI_COLOR_DEEP                     HDMI_IOWR(57, hdmi_para_setting)
#define MTK_HDMI_ENABLE_HDCP                    HDMI_IOWR(58, unsigned int)
#define MTK_HDMI_STATUS                         HDMI_IOWR(59, unsigned int)
#define MTK_HDMI_HDCP_KEY                       HDMI_IOWR(60, hdmi_hdcp_key)
#define MTK_HDMI_GET_EDID                       HDMI_IOWR(61, HDMI_EDID_T)
#define MTK_HDMI_SETLA                          HDMI_IOWR(62, CEC_DRV_ADDR_CFG)
#define MTK_HDMI_GET_CECCMD                     HDMI_IOWR(63, CEC_FRAME_DESCRIPTION_IO)
#define MTK_HDMI_SET_CECCMD                     HDMI_IOWR(64, CEC_SEND_MSG)
#define MTK_HDMI_CEC_ENABLE                     HDMI_IOWR(65, unsigned int)
#define MTK_HDMI_GET_CECADDR                    HDMI_IOWR(66, CEC_ADDRESS_IO)
#define MTK_HDMI_CECRX_MODE                     HDMI_IOWR(67, unsigned int)
#define MTK_HDMI_SENDSLTDATA                    HDMI_IOWR(68, send_slt_data)
#define MTK_HDMI_GET_SLTDATA                    HDMI_IOWR(69, CEC_GETSLT_DATA)
#define MTK_HDMI_VIDEO_MUTE                     HDMI_IOWR(70, int)

#define MTK_HDMI_READ                           HDMI_IOWR(81, unsigned int)
#define MTK_HDMI_WRITE                          HDMI_IOWR(82, unsigned int)
#define MTK_HDMI_CMD                            HDMI_IOWR(83, unsigned int)
#define MTK_HDMI_DUMP                           HDMI_IOWR(84, unsigned int)
#define MTK_HDMI_DUMP6397                       HDMI_IOWR(85, unsigned int)
#define MTK_HDMI_DUMP6397_W                     HDMI_IOWR(86, unsigned int)
#define MTK_HDMI_CBUS_STATUS                    HDMI_IOWR(87, unsigned int)
#define MTK_HDMI_CONNECT_STATUS                 HDMI_IOWR(88, unsigned int)
#define MTK_HDMI_DUMP6397_R                     HDMI_IOWR(89, unsigned int)
#define MTK_MHL_GET_DCAP                        HDMI_IOWR(90, unsigned int)
#define MTK_MHL_GET_3DINFO                      HDMI_IOWR(91, unsigned int)
#define MTK_HDMI_HDCP                           HDMI_IOWR(92, unsigned int)
#define MTK_HDMI_GET_CECSTS                     HDMI_IOWR(93, APK_CEC_ACK_INFO)
#define MTK_HDMI_CEC_USR_CMD                    HDMI_IOWR(94, CEC_USR_CMD_T)
#define MTK_HDMI_AUDIO_CH_SETTING               HDMI_IOWR(95, HDMITX_AUDIO_PARA)
#define MTK_HDMI_HDCP_LEVEL                     HDMI_IOWR(96, unsigned int)
#define MTK_HDMI_HDCP_STATUS                    HDMI_IOWR(97, unsigned int)
#define MTK_HDMI_HDCP_REPEATER_MODE             HDMI_IOWR(98, unsigned int)
#define MTK_HDMI_HDCP_AUTH_STATUS               HDMI_IOWR(99, unsigned int)
#define MTK_HDMI_HPD_ONOFF                      HDMI_IOWR(100, unsigned int)

#define IS_INTERLACE_OUTPUT(res) (((res) == HDMI_VIDEO_1920x1080i_60Hz) || ((res) == HDMI_VIDEO_1920x1080i_50Hz))

long hdmi_handle_cmd(unsigned int cmd, unsigned long arg);

#if defined(MTK_ALPS_BOX_SUPPORT) || defined(MTK_AOSP_TVSTICK_SUPPORT)
HDMI_VIDEO_RESOLUTION hdmi_get_resolution(void);
#endif
void set_rdma_address_config_ex(unsigned long va, unsigned long mva);
void disp_ovl_engine_565_to_888(void *src_va, void *dst_va);
void hdmi_set_hdmi_res(HDMI_VIDEO_RESOLUTION res);
unsigned int hdmi_get_width(HDMI_VIDEO_RESOLUTION r);
unsigned int hdmi_get_height(HDMI_VIDEO_RESOLUTION r);
void hdmi_disp_dump_output_buffer(void);
int hdmi_rdma_address_config(bool enable, hdmi_video_buffer_info buffer_info);
void set_rdma_full2limit_enable(unsigned int enable);
/* taken from old hdmitx.h -- end */

#endif
