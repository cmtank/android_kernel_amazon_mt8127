
#include <asm/io.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/xlog.h>

#include <asm/uaccess.h>
    
#include <mach/mt_typedefs.h>
#include <mach/mt_pm_ldo.h>

/****************************************************************
 * FUNCTION DEFINATIONS
 *******************************************************************/

bool hwPowerOn(MT65XX_POWER powerId, MT65XX_POWER_VOLTAGE powerVolt, char *mode_name)
{
    return 1;
}
EXPORT_SYMBOL(hwPowerOn);

bool hwPowerDown(MT65XX_POWER powerId, char *mode_name)
{
	return 1;
}
EXPORT_SYMBOL(hwPowerDown);
