#ifndef CONFIG_MTK_PMIC_DUMMY
	#ifdef MTK_PMIC_MT6397
	#include "upmu_common_mt6397.c"
	#else
	#include "upmu_common_mt6323.c"
	#endif
#endif