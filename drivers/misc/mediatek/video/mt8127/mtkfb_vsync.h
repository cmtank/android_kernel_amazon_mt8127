#ifndef __MTKFB_VSYNC_H__
#define __MTKFB_VSYNC_H__


#define MTKFB_VSYNC_DEVNAME "mtkfb_vsync"

#define MTKFB_VSYNC_IOCTL_MAGIC      'V'

typedef enum {
	MTKFB_VSYNC_SOURCE_LCM = 0,
	MTKFB_VSYNC_SOURCE_HDMI = 1,
} vsync_src;

typedef struct vsync_config {
	unsigned long long vsync_ticks;
}vsync_config_t;
#define MTKFB_VSYNC_IOCTL     _IOWR(MTKFB_VSYNC_IOCTL_MAGIC, 1, vsync_config_t)

#endif //MTKFB_VSYNC_H
