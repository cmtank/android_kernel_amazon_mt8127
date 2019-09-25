/*****************************************************************************
* Copyright 2011 Broadcom Corporation.  All rights reserved.
*
* Unless you and Broadcom execute a separate written software license
* agreement governing use of this software, this software is licensed to you
* under the terms of the GNU General Public License version 2, available at
* http://www.broadcom.com/licenses/GPLv2.php (the "GPL").
*
* Notwithstanding the above, under no circumstances may you combine this
* software in any way with any other Broadcom software provided under a
* license other than the GPL, without Broadcom's express prior written
* consent.
*****************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <asm/mach-types.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/setup.h>
#include <linux/if.h>
#include <linux/skbuff.h>
#include <linux/wlan_plat.h>
#include <linux/pm_runtime.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/fixed.h>
#include <asm/mach/mmc.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/random.h>
#include <linux/jiffies.h>

#include <mach/mt_gpio.h>

#ifdef CONFIG_IDME
#include <linux/of.h>
#include <linux/ctype.h>
#endif


/* ???
#ifdef CONFIG_BRCM_UNIFIED_DHD_SUPPORT

#define GPIO_WLAN_PMENA		104
#define GPIO_WLAN_IRQ		2

#define ATAG_MAC	0x57464d41
*/
#define CONFIG_BROADCOM_WIFI_RESERVED_MEM /* moved from defconfig file to reduce config items */

#ifdef CONFIG_BROADCOM_WIFI_RESERVED_MEM

#define WLAN_STATIC_SCAN_BUF0		5
#define WLAN_STATIC_SCAN_BUF1		6
#define PREALLOC_WLAN_SEC_NUM		4
#define PREALLOC_WLAN_BUF_NUM		160
#define PREALLOC_WLAN_SECTION_HEADER	24

#define WLAN_SECTION_SIZE_0	(PREALLOC_WLAN_BUF_NUM * 128)
#define WLAN_SECTION_SIZE_1	(PREALLOC_WLAN_BUF_NUM * 128)
#define WLAN_SECTION_SIZE_2	(PREALLOC_WLAN_BUF_NUM * 512)
#define WLAN_SECTION_SIZE_3	(PREALLOC_WLAN_BUF_NUM * 1024)

#define DHD_SKB_HDRSIZE			336
#define DHD_SKB_1PAGE_BUFSIZE	((PAGE_SIZE*1)-DHD_SKB_HDRSIZE)
#define DHD_SKB_2PAGE_BUFSIZE	((PAGE_SIZE*2)-DHD_SKB_HDRSIZE)
#define DHD_SKB_4PAGE_BUFSIZE	((PAGE_SIZE*4)-DHD_SKB_HDRSIZE)

#define WLAN_SKB_BUF_NUM	17

static struct sk_buff *wlan_static_skb[WLAN_SKB_BUF_NUM];

struct wlan_mem_prealloc {
	void *mem_ptr;
	unsigned long size;
};

static struct wlan_mem_prealloc wlan_mem_array[PREALLOC_WLAN_SEC_NUM] = {
	{NULL, (WLAN_SECTION_SIZE_0 + PREALLOC_WLAN_SECTION_HEADER)},
	{NULL, (WLAN_SECTION_SIZE_1 + PREALLOC_WLAN_SECTION_HEADER)},
	{NULL, (WLAN_SECTION_SIZE_2 + PREALLOC_WLAN_SECTION_HEADER)},
	{NULL, (WLAN_SECTION_SIZE_3 + PREALLOC_WLAN_SECTION_HEADER)}
};

void *wlan_static_scan_buf0;
void *wlan_static_scan_buf1;


/* What's in dhd.h:
   enum dhd_prealloc_index {
	DHD_PREALLOC_PROT = 0,
	DHD_PREALLOC_RXBUF,
	DHD_PREALLOC_DATABUF,
	DHD_PREALLOC_OSL_BUF,
#if defined(STATIC_WL_PRIV_STRUCT)
	DHD_PREALLOC_WIPHY_ESCAN0 = 5,
#endif
	DHD_PREALLOC_DHD_INFO = 7,
	DHD_PREALLOC_DHD_WLFC_INFO = 8,
	DHD_PREALLOC_IF_FLOW_LKUP = 9,
	DHD_PREALLOC_FLOWRING = 10,
	DHD_PREALLOC_PKTID_MAP = 11
}*/

static void *tank_wifi_mem_prealloc(int section, unsigned long size)
{
	if (section == PREALLOC_WLAN_SEC_NUM) /* 4 */
		return wlan_static_skb;
	if (section == WLAN_STATIC_SCAN_BUF0) /* 5, DHD_PREALLOC_WIPHY_ESCAN0 */
		return wlan_static_scan_buf0;
	if (section == WLAN_STATIC_SCAN_BUF1) /* 6 */
		return wlan_static_scan_buf1;
	if ((section < 0) || (section > PREALLOC_WLAN_SEC_NUM))
		return NULL;

	if (wlan_mem_array[section].size < size) /* 0 to 4 */
		return NULL;

	return wlan_mem_array[section].mem_ptr;
}

int __init tank_init_wifi_mem(void)
{
	int i;
	int j;

	for (i = 0; i < 8; i++) {
		wlan_static_skb[i] = dev_alloc_skb(DHD_SKB_1PAGE_BUFSIZE);
		if (!wlan_static_skb[i])
			goto err_skb_alloc;
	}

	for (; i < 16; i++) {
		wlan_static_skb[i] = dev_alloc_skb(DHD_SKB_2PAGE_BUFSIZE);
		if (!wlan_static_skb[i])
			goto err_skb_alloc;
	}

	wlan_static_skb[i] = dev_alloc_skb(DHD_SKB_4PAGE_BUFSIZE);
	if (!wlan_static_skb[i])
		goto err_skb_alloc;

	for (i = 0; i < PREALLOC_WLAN_SEC_NUM; i++) {
		wlan_mem_array[i].mem_ptr =
		    kmalloc(wlan_mem_array[i].size, GFP_KERNEL);

		if (!wlan_mem_array[i].mem_ptr)
			goto err_mem_alloc;
	}
	wlan_static_scan_buf0 = kmalloc(65536, GFP_KERNEL);
	if (!wlan_static_scan_buf0)
		goto err_mem_alloc;
	wlan_static_scan_buf1 = kmalloc(65536, GFP_KERNEL);
	if (!wlan_static_scan_buf1)
		goto err_mem_alloc;

	printk(KERN_ERR "%s: WIFI MEM Allocated\n", __func__);
	return 0;

err_mem_alloc:
	pr_err("Failed to mem_alloc for WLAN\n");
	for (j = 0; j < i; j++)
		kfree(wlan_mem_array[j].mem_ptr);

	i = WLAN_SKB_BUF_NUM;

err_skb_alloc:
	pr_err("Failed to skb_alloc for WLAN\n");
	for (j = 0; j < i; j++)
		dev_kfree_skb(wlan_static_skb[j]);

	return -ENOMEM;
}
#endif /* CONFIG_BROADCOM_WIFI_RESERVED_MEM */

int
tank_wifi_status_register(void (*callback) (int card_present, void *dev_id),
			   void *dev_id);

EXPORT_SYMBOL(tank_wifi_status_register);

static int tank_wifi_cd = 0;	/* WIFI virtual 'card detect' status */
static void (*wifi_status_cb) (int card_present, void *dev_id);
static void *wifi_status_cb_devid;

int
tank_wifi_status_register(void (*callback) (int card_present, void *dev_id),
			   void *dev_id)
{
	printk(KERN_ERR " %s ENTRY\n", __func__);

	if (wifi_status_cb) {
		printk(KERN_ERR "%s wifi_status_cb set\n", __func__);
		return -EAGAIN;
	}
	wifi_status_cb = callback;
	wifi_status_cb_devid = dev_id;
	return 0;
}

static unsigned int tank_wifi_status(struct device *dev)
{
	return tank_wifi_cd;
}

struct mmc_platform_data tank_wifi_data = {
	.ocr_mask = MMC_VDD_165_195 | MMC_VDD_20_21,
	.built_in = 1,
	.status = tank_wifi_status,
	.card_present = 0,
	.register_status_notify = tank_wifi_status_register,
};

static int tank_wifi_set_carddetect(int val)
{
	pr_debug("%s: %d\n", __func__, val);
	printk(KERN_ERR "%s: ENTRY val=%d\n", __func__, val);
	tank_wifi_cd = val;

	if (wifi_status_cb) {
		printk(KERN_ERR "%s: CALLBACK NOT NULL\n", __func__);
		wifi_status_cb(val, wifi_status_cb_devid);
		printk(KERN_ERR "%s: CALLBACK COMPLETE\n", __func__);
	} else
		pr_warning("%s: Nobody to notify\n", __func__);

	return 0;
}

static int tank_wifi_power_state;
static int power_gpio_num = 27;
static int power_gpio_active_level = -1;
#define DT_WIFI_PATH	"/wifi/power"

static int tank_wifi_power(int onoff)
{
	printk(KERN_ERR "%s ENTRY onoff=%d\n", __func__, onoff);

	if (power_gpio_num != -1) {
		mt_set_gpio_mode(power_gpio_num, GPIO_MODE_00);
		mt_set_gpio_dir(power_gpio_num, GPIO_DIR_OUT);

		/* wifi_power_gpio_value can be 0 or 1 only */
		if (onoff) {
			mt_set_gpio_out(power_gpio_num, GPIO_OUT_ONE);
		} else {
			mt_set_gpio_out(power_gpio_num, GPIO_OUT_ZERO);
		}
	}
	tank_wifi_power_state = onoff;

	return 0;
}

static int tank_wifi_reset_state;

static int tank_wifi_reset(int on)
{
	pr_debug("%s: do nothing\n", __func__);
	printk(KERN_ERR " %s INSIDE tank_wifi_reset\n", __func__);
	tank_wifi_reset_state = on;
	return 0;
}

static unsigned char tank_mac_addr[IFHWADDRLEN] = { 0, 0x90, 0x4c, 0, 0, 0 };

static int __init tank_mac_addr_setup(char *str)
{
	char macstr[IFHWADDRLEN * 3];
	char *macptr = macstr;
	char *token;
	int i = 0;

	if (!str)
		return 0;
	pr_debug("wlan MAC = %s\n", str);
	if (strlen(str) >= sizeof(macstr))
		return 0;
	strcpy(macstr, str);

	while ((token = strsep(&macptr, ":")) != NULL) {
		unsigned long val;
		int res;

		if (i >= IFHWADDRLEN)
			break;
		res = strict_strtoul(token, 0x10, &val);
		if (res < 0)
			return 0;
		tank_mac_addr[i++] = (u8)val;
	}

	return 1;
}

__setup("androidboot.macaddr=", tank_mac_addr_setup);


#ifdef CONFIG_IDME
static int hexval(char c)
{
        if (c >= '0' && c <= '9')
                return c - '0';
        else if (c >= 'a' && c <= 'f')
                return c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
                return c - 'A' + 10;
        return 0;
}

#define IDME_MACADDR "/proc/idme/mac_addr"

static int idme_get_mac_addr(unsigned char *mac_addr)
{
	unsigned char buf[IFHWADDRLEN* 2 + 1] = {""}, str[3] = {""};
	int i, mac[IFHWADDRLEN];
	mm_segment_t fs;
	struct file *f;
	size_t len;

	f = filp_open(IDME_MACADDR, O_RDONLY, 0);
	if (IS_ERR(f)) {
		printk(KERN_ERR "(IDME) cannot read /proc/idme/mac_addr\n");
		return -1;
	}

	fs = get_fs();
	set_fs(get_ds());
	f->f_op->read(f, buf, IFHWADDRLEN * 2, &f->f_pos);
	set_fs(fs);

	if (strlen(buf) != IFHWADDRLEN * 2)
		goto bailout;

	for (i = 0; i < IFHWADDRLEN; i++) {
		str[0] = buf[i * 2];
		str[1] = buf[i * 2 + 1];
		if (!isxdigit(str[0]) || !isxdigit(str[1]))
			goto bailout;
		len = sscanf(str, "%02x", &mac[i]);
		if (len != 1)
			goto bailout;
	}
	for (i = 0; i < IFHWADDRLEN; i++)
		mac_addr[i] = (unsigned char)mac[i];

	return 0;
bailout:
	printk(KERN_ERR "(IDME) wrong mac_addr '%s', expected format 112233445566\n", buf);
	return -1;
}
#endif

/*
 * tank_wifi_get_mac_addr() - return the WiFi MAC address.
 *
 * This function is called by the WiFi driver during initialization.
 * The returned address is used to create the WiFi interface.
 * The MAC address is returned in a 6-byte buffer pointed to by buf.
 * Non-zero return code is treated as error and the content of the
 * buffer is ignored.
 *
 * It currently returns a randomized address.  Platform should
 * re-implement this function to specific platform requirements.
 * For example, this function can read the MAC address from persistent
 * storage and return that in the buffer.
 */
static int tank_wifi_get_mac_addr(unsigned char *buf)
{
#ifndef CONFIG_IDME
	uint rand_mac;

	if ((tank_mac_addr[4] == 0) && (tank_mac_addr[5] == 0)) {
		srandom32((uint) jiffies);
		rand_mac = random32();
		tank_mac_addr[3] = (unsigned char)rand_mac;
		tank_mac_addr[4] = (unsigned char)(rand_mac >> 8);
		tank_mac_addr[5] = (unsigned char)(rand_mac >> 16);
	}
	memcpy(buf, tank_mac_addr, IFHWADDRLEN);
#else
	idme_get_mac_addr(buf);
	#if 0 // commented out because we don't have device tree */
	struct device_node *ap;
	int len = 0;
	int idx;
	const char *idme_mac;

	if (!buf)
		return -EFAULT;

	/* Get IDME mac address */
	ap = of_find_node_by_path(IDME_MACADDR);
	if (!ap) {
		pr_err("%s: Unable to get of node: %s\n", __func__, IDME_MACADDR);
		return -EINVAL;
        }

	idme_mac = of_get_property(ap, "value", &len);
	if (!idme_mac || (len < IFHWADDRLEN*2)) {
		pr_err("%s:%s invalid length %d\n", __func__, IDME_MACADDR, len);
		return -EINVAL;
        }

	pr_info("%s:%s value:%s\n", __func__, IDME_MACADDR, idme_mac);
	/* Convert IDME mac address */
	for (idx = 0; idx < IFHWADDRLEN; idx++) {
		tank_mac_addr[idx]  = hexval(idme_mac[idx*2])<<4;
		tank_mac_addr[idx] += hexval(idme_mac[idx*2+1]);
        }
	memcpy(buf, tank_mac_addr, IFHWADDRLEN);
	#endif
#endif
	printk(KERN_ERR " %s: mac address %02x:%02x:%02x:%02x:%02x:%02x\n", __func__,
	       buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

	return 0;
}


/* Customized Locale table : OPTIONAL feature */
#define WLC_CNTRY_BUF_SZ	4
typedef struct cntry_locales_custom {
	char iso_abbrev[WLC_CNTRY_BUF_SZ];
	char custom_locale[WLC_CNTRY_BUF_SZ];
	int custom_locale_rev;
} cntry_locales_custom_t;

static cntry_locales_custom_t tank_wifi_translate_custom_table[] = {
/* Table should be filled out based on custom platform regulatory requirement */
	{"", "XY", 12},		/* universal */
	{"E0", "E0", 25},
	{"EU", "E0", 25},
	{"US", "US", 174},
	{"JP", "JP", 72},
	{"KR", "KR", 4},
	{"BN", "BN", 4},
	{"CA", "CA", 2},
	{"MX", "MX", 20},
	{"MA", "MA", 7},
	{"RU", "RU", 50},
	{"TW", "TW", 1},
	{"AE", "AE", 6},
	{"UA", "UA", 13},
	{"KW", "KW", 5},
	{"AU", "AU", 6},
	{"NZ", "NZ", 4},
	{"SG", "SG", 12},
	{"BD", "BD", 2},
	{"HK", "HK", 2},
	{"IN", "IN", 3},
	{"MY", "MY", 3},
	{"NP", "NP", 3},
	{"CN", "CN", 38},
	{"EG", "EG", 13},
	{"IL", "IL", 7},
	{"PH", "PH", 5},
	{"ZA", "ZA", 6},
	{"ID", "ID", 5},
	{"PK", "PK", 2},
	{"VN", "VN", 4},
	{"LK", "LK", 2},
	{"SA", "SA", 5},
	{"TH", "TH", 5},
	{"MV", "MV", 3},
	{"AR", "AR", 21},
	{"BR", "BR", 17},
	{"CR", "CR", 17},
	{"CL", "CL", 7},
	{"CO", "CO", 17},
	{"EC", "EC", 18},
	{"PY", "PY", 2},
	{"PE", "PE", 20},
	{"PR", "PR", 20},
	{"PA", "PA", 17},
	{"VE", "VE", 3},
	{"AT", "AT", 4},
	{"BE", "BE", 4},
	{"BG", "BG", 4},
	{"HR", "HR", 4},
	{"CY", "CY", 4},
	{"CZ", "CZ", 4},
	{"DK", "DK", 4},
	{"EE", "EE", 4},
	{"FI", "FI", 4},
	{"FR", "FR", 5},
	{"DE", "DE", 7},
	{"GR", "GR", 4},
	{"HU", "HU", 4},
	{"IS", "IS", 4},
	{"IE", "IE", 5},
	{"IT", "IT", 4},
	{"LV", "LV", 4},
	{"LI", "LI", 4},
	{"LT", "LT", 4},
	{"LU", "LU", 4},
	{"MT", "MT", 4},
	{"NL", "NL", 4},
	{"NO", "NO", 4},
	{"PL", "PL", 4},
	{"PT", "PT", 4},
	{"RO", "RO", 4},
	{"SK", "SK", 4},
	{"SI", "SI", 4},
	{"ES", "ES", 4},
	{"SE", "SE", 4},
	{"CH", "CH", 4},
	{"GB", "GB", 6},
	{"TR", "TR", 7},
	{"BY", "BY", 3},
	{"AS", "AS", 0},
	{"BM", "BM", 0},
	{"SV", "SV", 17},
	{"GU", "GU", 12},
	{"MP", "MP", 0},
	{"PG", "PG", 2},
	{"UM", "UM", 0},
	{"VI", "VI", 13},
	{"ZM", "ZM", 2},
	{"UY", "UY", 6},
	{"NF", "NF", 1},
	{"AG", "AG", 2},
	{"LB", "LB", 5},
	{"TT", "TT", 3},
	{"KH", "KH", 2},
	{"GD", "GD", 2},
	{"JO", "JO", 3},
	{"BT", "BT", 0},
	{"MO", "MO", 2},
	{"MN", "MN", 3},
	{"MM", "MM", 0},
	{"LA", "LA", 2},
	{"AZ", "AZ", 2},
	{"KZ", "KZ", 0},
	{"BO", "BO", 0},
	{"HN", "HN", 0},
	{"JM", "JM", 0},
	{"NI", "NI", 2},
	{"DO", "DO", 0},
	{"GT", "GT", 0},
	{"AF", "AF", 0},
	{"RS", "RS", 2}
 };

static void *tank_wifi_get_country_code(char *ccode)
{
	int size = ARRAY_SIZE(tank_wifi_translate_custom_table);
	int i;

	if (!ccode)
		return NULL;

	for (i = 0; i < size; i++)
		if (strcmp
		    (ccode,
		     tank_wifi_translate_custom_table[i].iso_abbrev) == 0)
			return &tank_wifi_translate_custom_table[i];
	return &tank_wifi_translate_custom_table[0];
}

static struct resource tank_wifi_resources[] = {
	[0] = {
	       .name = "bcmdhd_wlan_irq",
	       .start = -1,
	       .end = -1,
	       .flags = IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE
	       /* IORESOURCE_IRQ_HIGHLEVEL */  | IORESOURCE_IRQ_SHAREABLE,
	       },
};

static struct wifi_platform_data tank_wifi_control = {
	.set_power = tank_wifi_power,
	.set_reset = tank_wifi_reset,
	.set_carddetect = tank_wifi_set_carddetect,
#ifdef CONFIG_BROADCOM_WIFI_RESERVED_MEM
	.mem_prealloc = tank_wifi_mem_prealloc,
#endif
	.get_mac_addr = tank_wifi_get_mac_addr,
	.get_country_code = tank_wifi_get_country_code,
};

static struct platform_device tank_wifi_device = {
	.name = "bcmdhd_wlan",
	.id = -1,
	.resource = tank_wifi_resources,
	.num_resources = ARRAY_SIZE(tank_wifi_resources),
	.dev = {
		.platform_data = &tank_wifi_control,
		},
};

static void __init tank_wlan_gpio(void)
{
}

int __init tank_wlan_init(void)
{
	pr_debug("%s: start\n", __func__);
	printk(KERN_ERR " %s Calling gpio init\n", __func__);
	tank_wlan_gpio();
	/* explicitly power on */
	printk(KERN_ERR " %s Calling wifi power\n", __func__);
	tank_wifi_power(0);
	printk(KERN_ERR " %s Calling mem init\n", __func__);
#ifdef CONFIG_BROADCOM_WIFI_RESERVED_MEM
	tank_init_wifi_mem();
#endif

	return platform_device_register(&tank_wifi_device);

}

