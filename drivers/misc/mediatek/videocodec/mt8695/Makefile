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

vcodec_kernel_driver-objs :=        \
    videocodec_kernel_driver.o      \
    common/val/src/val.o			\
    common/drv/src/drv_base.o \
    venc_kernel_driver.o


ifeq ($(CONFIG_MTK_SEC_VIDEO_PATH_SUPPORT),y)
  ccflags-y += -DCONFIG_MTK_SEC_VIDEO_PATH_SUPPORT
endif
ccflags-y += -DCONFIG_MTK_VIDEO_HEVC_SUPPORT

obj-$(CONFIG_MTK_VIDEOCODEC_DRIVER) += vcodec_kernel_driver.o


ccflags-y += \
    -I$(srctree)/drivers/misc/mediatek/videocodec/$(CONFIG_MTK_PLATFORM)/common/drv/inc		\
    -I$(srctree)/drivers/misc/mediatek/videocodec/include   \
    -I$(srctree)/drivers/misc/mediatek/videocodec/include/kernel   \
    -I$(srctree)/drivers/misc/mediatek/include/mt-plat   \
    -I$(srctree)/drivers/iommu   \
    -I$(srctree)/include/soc/mediatek   \
    -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include/mach
