ccflags-y += -I$(srctree)/drivers/misc/mediatek/mdp/imgresz
ccflags-y += -I$(srctree)/drivers/misc/mediatek/mdp/cli
ccflags-y += -I$(srctree)/drivers/misc/mediatek/mdp/nr
ccflags-y += -I$(srctree)/drivers/misc/mediatek/sync
ccflags-y += -I$(srctree)/include/trustzone
ccflags-y += -I$(srctree)/drivers/staging/android
ccflags-y += -I$(srctree)/drivers/staging/android/ion
ccflags-y += -I$(srctree)/drivers/staging/android/mtk_ion
ccflags-y += -I$(srctree)/drivers/misc/mediatek/video/mt8695/dispsys
ccflags-y += -I$(srctree)/drivers/misc/mediatek/mmp
ccflags-y += -I$(srctree)/drivers/misc/mediatek/hdmi/hdmitx/mt8695/inc/

obj-y += mdp_driver.o
obj-y += mdp_core.o
obj-y += mdp_fence.o
obj-y += mdp_imgresz.o
obj-y += mdp_nr.o
obj-y += mdp_rot.o
obj-y += mdp_buffer.o
obj-y += mdp_proc_print.o
obj-$(CONFIG_MTK_CLI_DEBUG_SUPPORT) += mdp_cli.o
