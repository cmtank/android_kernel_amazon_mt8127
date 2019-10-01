/*
 * SYSFS infrastructure specific to Lab126 product
 */
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/sysfs.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <asm/setup.h>


#define MAXBUF 16
static char usb_charge_type[MAXBUF];

static struct kobject *lab126_kobj;

static void __init usb_charge_type_setup(char * str)
{
	snprintf(usb_charge_type, MAXBUF, "%s\n", str);

	return;
}

__setup("usb_charge_type=", usb_charge_type_setup);

static ssize_t
usb_charge_type_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	sprintf(buf, "%s", usb_charge_type);

	return strlen(usb_charge_type);
}

static DEVICE_ATTR(usb_charge_type, 0444, usb_charge_type_show, NULL);


static struct attribute *lab126_attrs[] = {
	&dev_attr_usb_charge_type.attr,
	NULL,
};

static struct attribute_group lab126_attr_group = {
	.attrs = lab126_attrs,
};

static int __init lab126_sysfs_init(void)
{
	lab126_kobj = kobject_create_and_add("lab126", NULL);
	if (!lab126_kobj)
		return -ENOMEM;
	return sysfs_create_group(lab126_kobj, &lab126_attr_group);
}

static void __exit lab126_sysfs_exit(void)
{
	sysfs_remove_group(lab126_kobj, &lab126_attr_group);
}

module_init(lab126_sysfs_init);
module_exit(lab126_sysfs_exit);
