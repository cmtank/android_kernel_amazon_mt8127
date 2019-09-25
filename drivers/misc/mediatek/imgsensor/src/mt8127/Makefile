#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
#
# Makefile for misc devices that really don't fit anywhere else.

include $(srctree)/drivers/misc/mediatek/Makefile.custom

obj-y				+= kd_sensorlist.o
ifeq ($(ARCH_MTK_PROJECT), tb27A1910)
obj-y				+= gc0312yuv_Sensor.o
else
  ifeq ($(ARCH_MTK_PROJECT), abc123)
  obj-y				+= gc0312yuv_Sensor.o
  obj-y				+= hi704yuv_Sensor.o
  else
    ifeq ($(ARCH_MTK_PROJECT), tank)
        obj-y				+= gc0312yuv_Sensor.o
        obj-y				+= hi704yuv_Sensor.o
    else
        ifeq ($(ARCH_MTK_PROJECT), tb27A1912)
            obj-y                         += gc0312yuv_Sensor.o
         else
            ifeq ($(ARCH_MTK_PROJECT), abc123_proto)
                obj-y                         += gc0312yuv_Sensor.o
            else
                obj-y				+= ov2659yuv_Sensor.o
         endif
     endif
  endif
endif
endif

# $(CONFIG_MTK_PLATFORM)
$(warning "xilog project is:$(ARCH_MTK_PROJECT)")
ifeq ($(ARCH_MTK_PROJECT), tb8127p4)
	obj-y				+= ov5647_Sensor_p4.o
else
  	ifeq ($(ARCH_MTK_PROJECT), tb8127p4_25)
		obj-y				+= ov5647_Sensor_p4_25.o
	else
		ifeq ($(ARCH_MTK_PROJECT), tb8127p1_25)
			obj-y				+= ov5647_Sensor_p1_25.o
		else
 			ifeq ($(ARCH_MTK_PROJECT), tb27A1910)
				obj-y				+= gc2355mipiraw_Sensor.o
			else
  			    ifeq ($(ARCH_MTK_PROJECT), abc123)
	  			    obj-y				+= gc2355mipiraw_Sensor.o
	  			    obj-y				+= gc2356mipiraw_Sensor.o
		  	    else
  			        ifeq ($(ARCH_MTK_PROJECT), tank)
	  			        obj-y				+= gc2355mipiraw_Sensor.o
	  			        obj-y				+= gc2356mipiraw_Sensor.o
                    else
                        ifeq ($(ARCH_MTK_PROJECT), tb27A1912)
                            obj-y                           += gc2355mipiraw_Sensor.o
                        else
                            ifeq ($(ARCH_MTK_PROJECT), abc123_proto)
                                obj-y                           += gc2355mipiraw_Sensor.o
                            else
				                obj-y				+= ov5647_Sensor.o
			                endif
                        endif
                    endif
                endif
		    endif
	    endif
    endif
endif

