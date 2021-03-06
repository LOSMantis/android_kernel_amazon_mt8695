/*
 * Copyright (C) 2017 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#ifndef __PINCTRL_MTK_MT8695_H
#define __PINCTRL_MTK_MT8695_H
#include <linux/pinctrl/pinctrl.h>
#include <pinctrl-mtk-common.h>
static const struct mtk_desc_pin mtk_pins_mt8695[] = {
	MTK_PIN(
		PINCTRL_PIN(0, "NFI_ALE"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 1),
		MTK_FUNCTION(0, "GPIO0"),
		MTK_FUNCTION(4, "TSCLK"),
		MTK_FUNCTION(5, "PWM0"),
		MTK_FUNCTION(6, "NALE")
	),
	MTK_PIN(
		PINCTRL_PIN(1, "NFI_DAT0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 2),
		MTK_FUNCTION(0, "GPIO1"),
		MTK_FUNCTION(4, "TSDATA0"),
		MTK_FUNCTION(5, "PWM1"),
		MTK_FUNCTION(6, "NAND_ND0")
	),
	MTK_PIN(
		PINCTRL_PIN(2, "NFI_DAT1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 3),
		MTK_FUNCTION(0, "GPIO2"),
		MTK_FUNCTION(4, "TSDATA1"),
		MTK_FUNCTION(5, "PWM2"),
		MTK_FUNCTION(6, "NAND_ND1")
	),
	MTK_PIN(
		PINCTRL_PIN(3, "NFI_DAT2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 4),
		MTK_FUNCTION(0, "GPIO3"),
		MTK_FUNCTION(4, "TSDATA2"),
		MTK_FUNCTION(5, "PWM3"),
		MTK_FUNCTION(6, "NAND_ND2")
	),
	MTK_PIN(
		PINCTRL_PIN(4, "NFI_DAT3"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 5),
		MTK_FUNCTION(0, "GPIO4"),
		MTK_FUNCTION(4, "TSDATA3"),
		MTK_FUNCTION(5, "PWM4"),
		MTK_FUNCTION(6, "NAND_ND3")
	),
	MTK_PIN(
		PINCTRL_PIN(5, "NFI_DAT4"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 6),
		MTK_FUNCTION(0, "GPIO5"),
		MTK_FUNCTION(4, "TSDATA4"),
		MTK_FUNCTION(5, "PWM5"),
		MTK_FUNCTION(6, "NAND_ND4")
	),
	MTK_PIN(
		PINCTRL_PIN(6, "NFI_DAT5"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 7),
		MTK_FUNCTION(0, "GPIO6"),
		MTK_FUNCTION(4, "TSDATA5"),
		MTK_FUNCTION(5, "PWM0"),
		MTK_FUNCTION(6, "NAND_ND5")
	),
	MTK_PIN(
		PINCTRL_PIN(7, "NFI_DAT6"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 8),
		MTK_FUNCTION(0, "GPIO7"),
		MTK_FUNCTION(4, "TSDATA6"),
		MTK_FUNCTION(5, "PWM1"),
		MTK_FUNCTION(6, "NAND_ND6")
	),
	MTK_PIN(
		PINCTRL_PIN(8, "NFI_DAT7"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 9),
		MTK_FUNCTION(0, "GPIO8"),
		MTK_FUNCTION(4, "TSDATA7"),
		MTK_FUNCTION(5, "PWM2"),
		MTK_FUNCTION(6, "NAND_ND7")
	),
	MTK_PIN(
		PINCTRL_PIN(9, "NFI_WEB"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 10),
		MTK_FUNCTION(0, "GPIO9"),
		MTK_FUNCTION(4, "TSSYNC"),
		MTK_FUNCTION(5, "PWM3"),
		MTK_FUNCTION(6, "NWEB"),
		MTK_FUNCTION(7, "NOR_SPI_CS")
	),
	MTK_PIN(
		PINCTRL_PIN(10, "NFI_REB"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 11),
		MTK_FUNCTION(0, "GPIO10"),
		MTK_FUNCTION(4, "TSVAL"),
		MTK_FUNCTION(5, "PWM4"),
		MTK_FUNCTION(6, "NREB"),
		MTK_FUNCTION(7, "NOR_SPI_IO0")
	),
	MTK_PIN(
		PINCTRL_PIN(11, "NFI_RB"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 12),
		MTK_FUNCTION(0, "GPIO11"),
		MTK_FUNCTION(4, "SDA2"),
		MTK_FUNCTION(5, "SPI_CS_0"),
		MTK_FUNCTION(6, "NRB"),
		MTK_FUNCTION(7, "NOR_SPI_CK")
	),
	MTK_PIN(
		PINCTRL_PIN(12, "NFI_CLE"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 13),
		MTK_FUNCTION(0, "GPIO12"),
		MTK_FUNCTION(2, "AMUTE"),
		MTK_FUNCTION(3, "IR_IN"),
		MTK_FUNCTION(4, "SCL2"),
		MTK_FUNCTION(5, "SPI_MI_0"),
		MTK_FUNCTION(6, "NCLE"),
		MTK_FUNCTION(7, "NOR_SPI_IO1")
	),
	MTK_PIN(
		PINCTRL_PIN(13, "NFI_CE1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 14),
		MTK_FUNCTION(0, "GPIO13"),
		MTK_FUNCTION(1, "URXD1"),
		MTK_FUNCTION(2, "AMUTE1"),
		MTK_FUNCTION(3, "IDDIG_A"),
		MTK_FUNCTION(4, "SDA1"),
		MTK_FUNCTION(5, "SPI_CK_0"),
		MTK_FUNCTION(6, "NCEB1"),
		MTK_FUNCTION(7, "NOR_SPI_IO2")
	),
	MTK_PIN(
		PINCTRL_PIN(14, "NFI_CE0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 15),
		MTK_FUNCTION(0, "GPIO14"),
		MTK_FUNCTION(1, "UTXD1"),
		MTK_FUNCTION(2, "PWM4"),
		MTK_FUNCTION(3, "DRV_VBUS_A"),
		MTK_FUNCTION(4, "SCL1"),
		MTK_FUNCTION(5, "SPI_MO_0"),
		MTK_FUNCTION(6, "NCEB0"),
		MTK_FUNCTION(7, "NOR_SPI_IO3")
	),
	MTK_PIN(
		PINCTRL_PIN(15, "USB_DP_P0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 16),
		MTK_FUNCTION(0, "GPIO15"),
		MTK_FUNCTION(1, "URXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(16, "USB_DM_P0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 17),
		MTK_FUNCTION(0, "GPIO16"),
		MTK_FUNCTION(1, "UTXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(17, "USB_DP_P1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 18),
		MTK_FUNCTION(0, "GPIO17"),
		MTK_FUNCTION(1, "URXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(18, "USB_DM_P1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 19),
		MTK_FUNCTION(0, "GPIO18"),
		MTK_FUNCTION(1, "UTXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(19, "USB_ID"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 20),
		MTK_FUNCTION(0, "GPIO19"),
		MTK_FUNCTION(1, "IDDIG_A"),
		MTK_FUNCTION(2, "MSDC1_PSW"),
		MTK_FUNCTION(3, "URXD2"),
		MTK_FUNCTION(4, "SDA3"),
		MTK_FUNCTION(5, "IR_IN"),
		MTK_FUNCTION(6, "SRCCLKENA0")
	),
	MTK_PIN(
		PINCTRL_PIN(20, "USB_DRV"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 21),
		MTK_FUNCTION(0, "GPIO20"),
		MTK_FUNCTION(1, "DRV_VBUS_A"),
		MTK_FUNCTION(2, "MSDC1_DET"),
		MTK_FUNCTION(3, "UTXD2"),
		MTK_FUNCTION(4, "SCL3"),
		MTK_FUNCTION(5, "WATCHDOG"),
		MTK_FUNCTION(6, "SRCCLKENA1")
	),
	MTK_PIN(
		PINCTRL_PIN(21, "EINT0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 28),
		MTK_FUNCTION(0, "GPIO21"),
		MTK_FUNCTION(1, "EINT0"),
		MTK_FUNCTION(2, "URXD0"),
		MTK_FUNCTION(3, "PCM1_DO"),
		MTK_FUNCTION(4, "USB0_FT_SDA"),
		MTK_FUNCTION(5, "PWM0"),
		MTK_FUNCTION(6, "URXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(22, "EINT1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 29),
		MTK_FUNCTION(0, "GPIO22"),
		MTK_FUNCTION(1, "EINT1"),
		MTK_FUNCTION(2, "UTXD0"),
		MTK_FUNCTION(3, "PCM1_CLK"),
		MTK_FUNCTION(4, "USB0_FT_SCL"),
		MTK_FUNCTION(5, "PWM1"),
		MTK_FUNCTION(6, "UTXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(23, "EINT2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 30),
		MTK_FUNCTION(0, "GPIO23"),
		MTK_FUNCTION(1, "EINT2"),
		MTK_FUNCTION(2, "URTS0"),
		MTK_FUNCTION(3, "PCM1_DI"),
		MTK_FUNCTION(4, "USB1_FT_SCL"),
		MTK_FUNCTION(5, "PWM2"),
		MTK_FUNCTION(6, "URXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(24, "EINT3"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 31),
		MTK_FUNCTION(0, "GPIO24"),
		MTK_FUNCTION(1, "EINT3"),
		MTK_FUNCTION(2, "UCTS0"),
		MTK_FUNCTION(3, "PCM1_SYNC"),
		MTK_FUNCTION(4, "USB1_FT_SDA"),
		MTK_FUNCTION(5, "PWM3"),
		MTK_FUNCTION(6, "UTXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(25, "GPIO25"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 32),
		MTK_FUNCTION(0, "GPIO25"),
		MTK_FUNCTION(1, "JTRST_B_ICE"),
		MTK_FUNCTION(2, "SRCCLKENA0"),
		MTK_FUNCTION(3, "WATCHDOG"),
		MTK_FUNCTION(4, "IR_IN"),
		MTK_FUNCTION(5, "PWM4"),
		MTK_FUNCTION(6, "AMUTE")
	),
	MTK_PIN(
		PINCTRL_PIN(26, "GPIO26"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 33),
		MTK_FUNCTION(0, "GPIO26"),
		MTK_FUNCTION(1, "MSDC2_PSW"),
		MTK_FUNCTION(2, "URXD1"),
		MTK_FUNCTION(3, "URXD2"),
		MTK_FUNCTION(4, "AMUTE"),
		MTK_FUNCTION(5, "PWM0"),
		MTK_FUNCTION(6, "SRCCLKENA0")
	),
	MTK_PIN(
		PINCTRL_PIN(27, "GPIO27"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 34),
		MTK_FUNCTION(0, "GPIO27"),
		MTK_FUNCTION(1, "MSDC2_DET"),
		MTK_FUNCTION(2, "UTXD1"),
		MTK_FUNCTION(3, "UTXD2"),
		MTK_FUNCTION(4, "AMUTE1"),
		MTK_FUNCTION(5, "PWM1"),
		MTK_FUNCTION(6, "SRCCLKENA1")
	),
	MTK_PIN(
		PINCTRL_PIN(28, "MSDC2_CLK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 35),
		MTK_FUNCTION(0, "GPIO28"),
		MTK_FUNCTION(1, "MSDC2_CLK")
	),
	MTK_PIN(
		PINCTRL_PIN(29, "MSDC2_DSL"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 36),
		MTK_FUNCTION(0, "GPIO29"),
		MTK_FUNCTION(1, "MSDC2_DSL")
	),
	MTK_PIN(
		PINCTRL_PIN(30, "MSDC2_DATA3"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 37),
		MTK_FUNCTION(0, "GPIO30"),
		MTK_FUNCTION(1, "MSDC2_DAT3")
	),
	MTK_PIN(
		PINCTRL_PIN(31, "MSDC2_DATA2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 38),
		MTK_FUNCTION(0, "GPIO31"),
		MTK_FUNCTION(1, "MSDC2_DAT2")
	),
	MTK_PIN(
		PINCTRL_PIN(32, "MSDC2_DATA1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 39),
		MTK_FUNCTION(0, "GPIO32"),
		MTK_FUNCTION(1, "MSDC2_DAT1")
	),
	MTK_PIN(
		PINCTRL_PIN(33, "MSDC2_DATA0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 40),
		MTK_FUNCTION(0, "GPIO33"),
		MTK_FUNCTION(1, "MSDC2_DAT0")
	),
	MTK_PIN(
		PINCTRL_PIN(34, "MSDC2_CMD"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 41),
		MTK_FUNCTION(0, "GPIO34"),
		MTK_FUNCTION(1, "MSDC2_CMD")
	),
	MTK_PIN(
		PINCTRL_PIN(35, "EMMC_DSL"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 42),
		MTK_FUNCTION(0, "GPIO35"),
		MTK_FUNCTION(1, "MSDC0_DSL")
	),
	MTK_PIN(
		PINCTRL_PIN(36, "EMMC_CLK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 43),
		MTK_FUNCTION(0, "GPIO36"),
		MTK_FUNCTION(1, "MSDC0_CLK")
	),
	MTK_PIN(
		PINCTRL_PIN(37, "EMMC_DAT7"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 44),
		MTK_FUNCTION(0, "GPIO37"),
		MTK_FUNCTION(1, "MSDC0_DAT7"),
		MTK_FUNCTION(3, "SPI_CS_0")
	),
	MTK_PIN(
		PINCTRL_PIN(38, "EMMC_DAT6"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 45),
		MTK_FUNCTION(0, "GPIO38"),
		MTK_FUNCTION(1, "MSDC0_DAT6"),
		MTK_FUNCTION(3, "SPI_MI_0")
	),
	MTK_PIN(
		PINCTRL_PIN(39, "EMMC_DAT5"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 46),
		MTK_FUNCTION(0, "GPIO39"),
		MTK_FUNCTION(1, "MSDC0_DAT5"),
		MTK_FUNCTION(3, "SPI_CK_0")
	),
	MTK_PIN(
		PINCTRL_PIN(40, "EMMC_DAT4"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 47),
		MTK_FUNCTION(0, "GPIO40"),
		MTK_FUNCTION(1, "MSDC0_DAT4"),
		MTK_FUNCTION(3, "SPI_MO_0")
	),
	MTK_PIN(
		PINCTRL_PIN(41, "EMMC_DAT3"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 48),
		MTK_FUNCTION(0, "GPIO41"),
		MTK_FUNCTION(1, "MSDC0_DAT3"),
		MTK_FUNCTION(3, "URXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(42, "EMMC_DAT2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 49),
		MTK_FUNCTION(0, "GPIO42"),
		MTK_FUNCTION(1, "MSDC0_DAT2"),
		MTK_FUNCTION(3, "UTXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(43, "EMMC_DAT1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 50),
		MTK_FUNCTION(0, "GPIO43"),
		MTK_FUNCTION(1, "MSDC0_DAT1"),
		MTK_FUNCTION(3, "URXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(44, "EMMC_DAT0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 51),
		MTK_FUNCTION(0, "GPIO44"),
		MTK_FUNCTION(1, "MSDC0_DAT0"),
		MTK_FUNCTION(3, "UTXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(45, "EMMC_CMD"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 52),
		MTK_FUNCTION(0, "GPIO45"),
		MTK_FUNCTION(1, "MSDC0_CMD"),
		MTK_FUNCTION(3, "SDA2")
	),
	MTK_PIN(
		PINCTRL_PIN(46, "EMMC_RSTB"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 53),
		MTK_FUNCTION(0, "GPIO46"),
		MTK_FUNCTION(1, "MSDC0_RSTB"),
		MTK_FUNCTION(3, "SCL2")
	),
	MTK_PIN(
		PINCTRL_PIN(47, "JTDO_ICE"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 54),
		MTK_FUNCTION(0, "GPIO47"),
		MTK_FUNCTION(1, "JTDO_ICE")
	),
	MTK_PIN(
		PINCTRL_PIN(48, "JTCK_ICE"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 55),
		MTK_FUNCTION(0, "GPIO48"),
		MTK_FUNCTION(1, "JTCK_ICE")
	),
	MTK_PIN(
		PINCTRL_PIN(49, "JTDI_ICE"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 56),
		MTK_FUNCTION(0, "GPIO49"),
		MTK_FUNCTION(1, "JTDI_ICE")
	),
	MTK_PIN(
		PINCTRL_PIN(50, "JTMS_ICE"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 57),
		MTK_FUNCTION(0, "GPIO50"),
		MTK_FUNCTION(1, "JTMS_ICE")
	),
	MTK_PIN(
		PINCTRL_PIN(51, "IR"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 58),
		MTK_FUNCTION(0, "GPIO51"),
		MTK_FUNCTION(1, "IR_IN"),
		MTK_FUNCTION(4, "SRCCLKENA0"),
		MTK_FUNCTION(5, "WATCHDOG"),
		MTK_FUNCTION(6, "PWM5")
	),
	MTK_PIN(
		PINCTRL_PIN(52, "GPIO52"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 59),
		MTK_FUNCTION(0, "GPIO52"),
		MTK_FUNCTION(1, "KROW1"),
		MTK_FUNCTION(2, "SPI_CS_1"),
		MTK_FUNCTION(3, "URXD1"),
		MTK_FUNCTION(4, "SDA3"),
		MTK_FUNCTION(5, "URXD0"),
		MTK_FUNCTION(6, "SRCCLKENA0")
	),
	MTK_PIN(
		PINCTRL_PIN(53, "GPIO53"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 60),
		MTK_FUNCTION(0, "GPIO53"),
		MTK_FUNCTION(1, "KROW0"),
		MTK_FUNCTION(2, "SPI_MI_1"),
		MTK_FUNCTION(3, "UTXD1"),
		MTK_FUNCTION(4, "SCL3"),
		MTK_FUNCTION(5, "UTXD0"),
		MTK_FUNCTION(6, "SRCCLKENA1")
	),
	MTK_PIN(
		PINCTRL_PIN(54, "WATCHDOG"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 61),
		MTK_FUNCTION(0, "GPIO54"),
		MTK_FUNCTION(1, "KCOL1"),
		MTK_FUNCTION(2, "SPI_CK_1"),
		MTK_FUNCTION(3, "WATCHDOG"),
		MTK_FUNCTION(4, "URXD2"),
		MTK_FUNCTION(5, "URTS0"),
		MTK_FUNCTION(6, "SDA1")
	),
	MTK_PIN(
		PINCTRL_PIN(55, "GPIO55"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 62),
		MTK_FUNCTION(0, "GPIO55"),
		MTK_FUNCTION(1, "KCOL0"),
		MTK_FUNCTION(2, "SPI_MO_1"),
		MTK_FUNCTION(3, "AMUTE1"),
		MTK_FUNCTION(4, "UTXD2"),
		MTK_FUNCTION(5, "UCTS0"),
		MTK_FUNCTION(6, "SCL1")
	),
	MTK_PIN(
		PINCTRL_PIN(56, "SDA1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 63),
		MTK_FUNCTION(0, "GPIO56"),
		MTK_FUNCTION(1, "SDA2"),
		MTK_FUNCTION(2, "PWM4"),
		MTK_FUNCTION(3, "SDA1"),
		MTK_FUNCTION(4, "URXD1"),
		MTK_FUNCTION(5, "KROW1"),
		MTK_FUNCTION(6, "SRCCLKENA0")
	),
	MTK_PIN(
		PINCTRL_PIN(57, "SCL1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 64),
		MTK_FUNCTION(0, "GPIO57"),
		MTK_FUNCTION(1, "SCL2"),
		MTK_FUNCTION(2, "PWM5"),
		MTK_FUNCTION(3, "SCL1"),
		MTK_FUNCTION(4, "UTXD1"),
		MTK_FUNCTION(5, "KROW0"),
		MTK_FUNCTION(6, "SRCCLKENA1")
	),
	MTK_PIN(
		PINCTRL_PIN(58, "URXD1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 65),
		MTK_FUNCTION(0, "GPIO58"),
		MTK_FUNCTION(1, "MSDC1_PSW"),
		MTK_FUNCTION(2, "URXD2"),
		MTK_FUNCTION(3, "URXD1"),
		MTK_FUNCTION(4, "KCOL1"),
		MTK_FUNCTION(5, "PWM4"),
		MTK_FUNCTION(6, "SDA2")
	),
	MTK_PIN(
		PINCTRL_PIN(59, "UTXD1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 66),
		MTK_FUNCTION(0, "GPIO59"),
		MTK_FUNCTION(1, "MSDC1_DET"),
		MTK_FUNCTION(2, "UTXD2"),
		MTK_FUNCTION(3, "UTXD1"),
		MTK_FUNCTION(4, "KCOL0"),
		MTK_FUNCTION(5, "PWM5"),
		MTK_FUNCTION(6, "SCL2")
	),
	MTK_PIN(
		PINCTRL_PIN(60, "NOR_CS"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 67),
		MTK_FUNCTION(0, "GPIO60"),
		MTK_FUNCTION(1, "NOR_SPI_CS"),
		MTK_FUNCTION(2, "SPI_CS_0"),
		MTK_FUNCTION(3, "MSDC1_PSW"),
		MTK_FUNCTION(4, "URXD1"),
		MTK_FUNCTION(5, "SDA2")
	),
	MTK_PIN(
		PINCTRL_PIN(61, "NOR_IO0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 68),
		MTK_FUNCTION(0, "GPIO61"),
		MTK_FUNCTION(1, "NOR_SPI_IO0"),
		MTK_FUNCTION(2, "SPI_MI_0"),
		MTK_FUNCTION(3, "MSDC1_DET"),
		MTK_FUNCTION(4, "UTXD1"),
		MTK_FUNCTION(5, "SCL2")
	),
	MTK_PIN(
		PINCTRL_PIN(62, "NOR_CK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 69),
		MTK_FUNCTION(0, "GPIO62"),
		MTK_FUNCTION(1, "NOR_SPI_CK"),
		MTK_FUNCTION(2, "SPI_CK_0"),
		MTK_FUNCTION(3, "IR_IN"),
		MTK_FUNCTION(4, "URXD2"),
		MTK_FUNCTION(5, "SDA1")
	),
	MTK_PIN(
		PINCTRL_PIN(63, "NOR_IO1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 70),
		MTK_FUNCTION(0, "GPIO63"),
		MTK_FUNCTION(1, "NOR_SPI_IO1"),
		MTK_FUNCTION(2, "SPI_MO_0"),
		MTK_FUNCTION(3, "PWM3"),
		MTK_FUNCTION(4, "UTXD2"),
		MTK_FUNCTION(5, "SCL1")
	),
	MTK_PIN(
		PINCTRL_PIN(64, "NOR_IO2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 71),
		MTK_FUNCTION(0, "GPIO64"),
		MTK_FUNCTION(1, "NOR_SPI_IO2"),
		MTK_FUNCTION(2, "SDA_EPM"),
		MTK_FUNCTION(3, "PWM4"),
		MTK_FUNCTION(4, "URXD1"),
		MTK_FUNCTION(5, "URXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(65, "NOR_IO3"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 72),
		MTK_FUNCTION(0, "GPIO65"),
		MTK_FUNCTION(1, "NOR_SPI_IO3"),
		MTK_FUNCTION(2, "SCL_EPM"),
		MTK_FUNCTION(3, "PWM5"),
		MTK_FUNCTION(4, "UTXD1"),
		MTK_FUNCTION(5, "UTXD2"),
		MTK_FUNCTION(6, "IR_IN")
	),
	MTK_PIN(
		PINCTRL_PIN(66, "MSDC1_CLK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 73),
		MTK_FUNCTION(0, "GPIO66"),
		MTK_FUNCTION(1, "MSDC1_CLK"),
		MTK_FUNCTION(2, "EJ_TCK"),
		MTK_FUNCTION(4, "PWM0")
	),
	MTK_PIN(
		PINCTRL_PIN(67, "MSDC1_DATA3"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 74),
		MTK_FUNCTION(0, "GPIO67"),
		MTK_FUNCTION(1, "MSDC1_DAT3"),
		MTK_FUNCTION(4, "PWM1")
	),
	MTK_PIN(
		PINCTRL_PIN(68, "MSDC1_DATA1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 75),
		MTK_FUNCTION(0, "GPIO68"),
		MTK_FUNCTION(1, "MSDC1_DAT1"),
		MTK_FUNCTION(2, "EJ_TDO"),
		MTK_FUNCTION(4, "PWM2")
	),
	MTK_PIN(
		PINCTRL_PIN(69, "MSDC1_DATA2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 76),
		MTK_FUNCTION(0, "GPIO69"),
		MTK_FUNCTION(1, "MSDC1_DAT2"),
		MTK_FUNCTION(2, "EJ_NTRST"),
		MTK_FUNCTION(4, "PWM3")
	),
	MTK_PIN(
		PINCTRL_PIN(70, "MSDC1_DATA0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 77),
		MTK_FUNCTION(0, "GPIO70"),
		MTK_FUNCTION(1, "MSDC1_DAT0"),
		MTK_FUNCTION(2, "EJ_TDI"),
		MTK_FUNCTION(4, "PWM4")
	),
	MTK_PIN(
		PINCTRL_PIN(71, "MSDC1_CMD"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 78),
		MTK_FUNCTION(0, "GPIO71"),
		MTK_FUNCTION(1, "MSDC1_CMD"),
		MTK_FUNCTION(2, "EJ_TMS"),
		MTK_FUNCTION(4, "PWM5")
	),
	MTK_PIN(
		PINCTRL_PIN(72, "HDMITX20_CEC"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 79),
		MTK_FUNCTION(0, "GPIO72"),
		MTK_FUNCTION(1, "HDMITX20_CEC"),
		MTK_FUNCTION(2, "SDA1"),
		MTK_FUNCTION(3, "SDA2"),
		MTK_FUNCTION(4, "SDA3")
	),
	MTK_PIN(
		PINCTRL_PIN(73, "HDMITX20_HTPLG"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 80),
		MTK_FUNCTION(0, "GPIO73"),
		MTK_FUNCTION(1, "HDMITX20_HTPLG"),
		MTK_FUNCTION(2, "SCL1"),
		MTK_FUNCTION(3, "SCL2"),
		MTK_FUNCTION(4, "SCL3")
	),
	MTK_PIN(
		PINCTRL_PIN(74, "HDMITX20_HDMISCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 81),
		MTK_FUNCTION(0, "GPIO74"),
		MTK_FUNCTION(1, "SCL_HDMI"),
		MTK_FUNCTION(2, "URXD2"),
		MTK_FUNCTION(3, "SDA2"),
		MTK_FUNCTION(4, "URXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(75, "HDMITX20_HDMISD"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 82),
		MTK_FUNCTION(0, "GPIO75"),
		MTK_FUNCTION(1, "SDA_HDMI"),
		MTK_FUNCTION(2, "UTXD2"),
		MTK_FUNCTION(3, "SCL2"),
		MTK_FUNCTION(4, "UTXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(76, "SDA2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 83),
		MTK_FUNCTION(0, "GPIO76"),
		MTK_FUNCTION(1, "SDA1"),
		MTK_FUNCTION(2, "SDA2"),
		MTK_FUNCTION(3, "SDA_EPM"),
		MTK_FUNCTION(4, "SDA3"),
		MTK_FUNCTION(5, "PWM4"),
		MTK_FUNCTION(6, "AMUTE")
	),
	MTK_PIN(
		PINCTRL_PIN(77, "SCL2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 84),
		MTK_FUNCTION(0, "GPIO77"),
		MTK_FUNCTION(1, "SCL1"),
		MTK_FUNCTION(2, "SCL2"),
		MTK_FUNCTION(3, "SCL_EPM"),
		MTK_FUNCTION(4, "SCL3"),
		MTK_FUNCTION(5, "PWM5"),
		MTK_FUNCTION(6, "AMUTE1")
	),
	MTK_PIN(
		PINCTRL_PIN(78, "GPIO78"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 85),
		MTK_FUNCTION(0, "GPIO78"),
		MTK_FUNCTION(1, "JTDO_ICE"),
		MTK_FUNCTION(2, "KCOL1"),
		MTK_FUNCTION(4, "SDA1"),
		MTK_FUNCTION(5, "AMUTE")
	),
	MTK_PIN(
		PINCTRL_PIN(79, "GPIO79"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 86),
		MTK_FUNCTION(0, "GPIO79"),
		MTK_FUNCTION(1, "JTDI_ICE"),
		MTK_FUNCTION(2, "KCOL0"),
		MTK_FUNCTION(4, "SCL1"),
		MTK_FUNCTION(5, "AMUTE1")
	),
	MTK_PIN(
		PINCTRL_PIN(80, "GPIO80"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 87),
		MTK_FUNCTION(0, "GPIO80"),
		MTK_FUNCTION(1, "JTMS_ICE"),
		MTK_FUNCTION(2, "URXD1"),
		MTK_FUNCTION(4, "SRCCLKENA0"),
		MTK_FUNCTION(5, "KROW1")
	),
	MTK_PIN(
		PINCTRL_PIN(81, "GPIO81"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 88),
		MTK_FUNCTION(0, "GPIO81"),
		MTK_FUNCTION(1, "JTCK_ICE"),
		MTK_FUNCTION(2, "UTXD1"),
		MTK_FUNCTION(4, "SRCCLKENA1"),
		MTK_FUNCTION(5, "KROW0")
	),
	MTK_PIN(
		PINCTRL_PIN(82, "SPDIF"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 89),
		MTK_FUNCTION(0, "GPIO82"),
		MTK_FUNCTION(1, "SPDIF_OUT"),
		MTK_FUNCTION(2, "I2SO2_DO"),
		MTK_FUNCTION(3, "SDA1"),
		MTK_FUNCTION(4, "I2SO5_DO"),
		MTK_FUNCTION(5, "PWM1")
	),
	MTK_PIN(
		PINCTRL_PIN(83, "SPDIF_IN"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 90),
		MTK_FUNCTION(0, "GPIO83"),
		MTK_FUNCTION(1, "SPDIF_IN"),
		MTK_FUNCTION(2, "I2SO3_DO"),
		MTK_FUNCTION(3, "SCL1"),
		MTK_FUNCTION(4, "I2SO5_DO"),
		MTK_FUNCTION(5, "PWM2"),
		MTK_FUNCTION(6, "AMUTE")
	),
	MTK_PIN(
		PINCTRL_PIN(84, "I2SI0_DATA"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 91),
		MTK_FUNCTION(0, "GPIO84"),
		MTK_FUNCTION(1, "I2SI0_DI"),
		MTK_FUNCTION(2, "I2SI1_DI"),
		MTK_FUNCTION(3, "URXD2"),
		MTK_FUNCTION(4, "TDMIN_DI"),
		MTK_FUNCTION(5, "I2SO2_DO")
	),
	MTK_PIN(
		PINCTRL_PIN(85, "I2SI0_LRCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 92),
		MTK_FUNCTION(0, "GPIO85"),
		MTK_FUNCTION(1, "I2SI0_WS"),
		MTK_FUNCTION(2, "I2SI1_WS"),
		MTK_FUNCTION(3, "UTXD2"),
		MTK_FUNCTION(4, "TDMIN_BCK"),
		MTK_FUNCTION(5, "I2SO3_DO"),
		MTK_FUNCTION(6, "I2SIS0_BCK")
	),
	MTK_PIN(
		PINCTRL_PIN(86, "I2SI0_BCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 93),
		MTK_FUNCTION(0, "GPIO86"),
		MTK_FUNCTION(1, "I2SI0_BCK"),
		MTK_FUNCTION(2, "I2SI1_BCK"),
		MTK_FUNCTION(3, "SCL2"),
		MTK_FUNCTION(4, "TDMIN_LRCK"),
		MTK_FUNCTION(5, "I2SO4_DO"),
		MTK_FUNCTION(6, "I2SIS0_WS")
	),
	MTK_PIN(
		PINCTRL_PIN(87, "I2SI0_MCLK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 94),
		MTK_FUNCTION(0, "GPIO87"),
		MTK_FUNCTION(1, "I2SI0_MCK"),
		MTK_FUNCTION(2, "I2SI1_MCK"),
		MTK_FUNCTION(3, "SDA2"),
		MTK_FUNCTION(4, "TDMIN_MCLK"),
		MTK_FUNCTION(5, "I2SO5_DO"),
		MTK_FUNCTION(6, "I2SIS0_MCK")
	),
	MTK_PIN(
		PINCTRL_PIN(88, "I2SI1_DATA"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 95),
		MTK_FUNCTION(0, "GPIO88"),
		MTK_FUNCTION(1, "I2SI1_DI"),
		MTK_FUNCTION(2, "I2SI0_DI"),
		MTK_FUNCTION(3, "AMUTE1"),
		MTK_FUNCTION(4, "I2SOS_DO"),
		MTK_FUNCTION(5, "USB0_FT_SDA"),
		MTK_FUNCTION(6, "SRCCLKENA1")
	),
	MTK_PIN(
		PINCTRL_PIN(89, "I2SI1_BCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 96),
		MTK_FUNCTION(0, "GPIO89"),
		MTK_FUNCTION(1, "I2SI1_BCK"),
		MTK_FUNCTION(2, "I2SI0_BCK"),
		MTK_FUNCTION(3, "I2SO2_DO"),
		MTK_FUNCTION(4, "I2SOS_BCK"),
		MTK_FUNCTION(5, "USB0_FT_SCL"),
		MTK_FUNCTION(6, "I2SIS1_BCK")
	),
	MTK_PIN(
		PINCTRL_PIN(90, "I2SI1_LRCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 97),
		MTK_FUNCTION(0, "GPIO90"),
		MTK_FUNCTION(1, "I2SI1_WS"),
		MTK_FUNCTION(2, "I2SI0_WS"),
		MTK_FUNCTION(3, "I2SO3_DO"),
		MTK_FUNCTION(4, "I2SOS_WS"),
		MTK_FUNCTION(5, "USB1_FT_SCL"),
		MTK_FUNCTION(6, "I2SIS1_WS")
	),
	MTK_PIN(
		PINCTRL_PIN(91, "I2SI1_MCLK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 98),
		MTK_FUNCTION(0, "GPIO91"),
		MTK_FUNCTION(1, "I2SI1_MCK"),
		MTK_FUNCTION(2, "I2SI0_MCK"),
		MTK_FUNCTION(3, "I2SO4_DO"),
		MTK_FUNCTION(4, "I2SOS_MCK"),
		MTK_FUNCTION(5, "USB1_FT_SDA"),
		MTK_FUNCTION(6, "I2SIS1_MCK")
	),
	MTK_PIN(
		PINCTRL_PIN(92, "GPIO92"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 99),
		MTK_FUNCTION(0, "GPIO92"),
		MTK_FUNCTION(1, "PCM1_DO"),
		MTK_FUNCTION(2, "I2SO0_DO"),
		MTK_FUNCTION(3, "I2SI2_DI"),
		MTK_FUNCTION(4, "I2SI0_DI"),
		MTK_FUNCTION(5, "I2SO2_DO"),
		MTK_FUNCTION(6, "SRCCLKENA0")
	),
	MTK_PIN(
		PINCTRL_PIN(93, "GPIO93"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 100),
		MTK_FUNCTION(0, "GPIO93"),
		MTK_FUNCTION(1, "PCM1_CLK"),
		MTK_FUNCTION(2, "I2SO0_MCK"),
		MTK_FUNCTION(3, "I2SI3_DI"),
		MTK_FUNCTION(4, "I2SI0_MCK"),
		MTK_FUNCTION(5, "I2SO3_DO"),
		MTK_FUNCTION(6, "I2SIS0_BCK")
	),
	MTK_PIN(
		PINCTRL_PIN(94, "GPIO94"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 101),
		MTK_FUNCTION(0, "GPIO94"),
		MTK_FUNCTION(1, "PCM1_DI"),
		MTK_FUNCTION(2, "I2SO0_BCK"),
		MTK_FUNCTION(3, "I2SI2_DI"),
		MTK_FUNCTION(4, "I2SI0_BCK"),
		MTK_FUNCTION(5, "I2SO4_DO"),
		MTK_FUNCTION(6, "I2SIS0_WS")
	),
	MTK_PIN(
		PINCTRL_PIN(95, "GPIO95"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 102),
		MTK_FUNCTION(0, "GPIO95"),
		MTK_FUNCTION(1, "PCM1_SYNC"),
		MTK_FUNCTION(2, "I2SO0_WS"),
		MTK_FUNCTION(3, "I2SI3_DI"),
		MTK_FUNCTION(4, "I2SI0_WS"),
		MTK_FUNCTION(5, "I2SO5_DO"),
		MTK_FUNCTION(6, "I2SIS0_MCK")
	),
	MTK_PIN(
		PINCTRL_PIN(96, "SPI1_CSN"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 103),
		MTK_FUNCTION(0, "GPIO96"),
		MTK_FUNCTION(1, "SPI_CS_1"),
		MTK_FUNCTION(2, "NOR_SPI_CS"),
		MTK_FUNCTION(3, "SPI_CS_0"),
		MTK_FUNCTION(4, "TDMIN_DI"),
		MTK_FUNCTION(5, "I2SOS_DO"),
		MTK_FUNCTION(6, "I2SI1_DI")
	),
	MTK_PIN(
		PINCTRL_PIN(97, "SPI1_SI"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 104),
		MTK_FUNCTION(0, "GPIO97"),
		MTK_FUNCTION(1, "SPI_MI_1"),
		MTK_FUNCTION(2, "NOR_SPI_IO0"),
		MTK_FUNCTION(3, "SPI_MI_0"),
		MTK_FUNCTION(4, "TDMIN_BCK"),
		MTK_FUNCTION(5, "I2SOS_BCK"),
		MTK_FUNCTION(6, "I2SIS1_BCK")
	),
	MTK_PIN(
		PINCTRL_PIN(98, "SPI1_CK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 105),
		MTK_FUNCTION(0, "GPIO98"),
		MTK_FUNCTION(1, "SPI_CK_1"),
		MTK_FUNCTION(2, "NOR_SPI_CK"),
		MTK_FUNCTION(3, "SPI_CK_0"),
		MTK_FUNCTION(4, "TDMIN_LRCK"),
		MTK_FUNCTION(5, "I2SOS_WS"),
		MTK_FUNCTION(6, "I2SIS1_WS")
	),
	MTK_PIN(
		PINCTRL_PIN(99, "SPI1_SO"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 106),
		MTK_FUNCTION(0, "GPIO99"),
		MTK_FUNCTION(1, "SPI_MO_1"),
		MTK_FUNCTION(2, "NOR_SPI_IO1"),
		MTK_FUNCTION(3, "SPI_MO_0"),
		MTK_FUNCTION(4, "TDMIN_MCLK"),
		MTK_FUNCTION(5, "I2SOS_MCK"),
		MTK_FUNCTION(6, "I2SIS1_MCK")
	),
	MTK_PIN(
		PINCTRL_PIN(100, "I2SO0_BCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 107),
		MTK_FUNCTION(0, "GPIO100"),
		MTK_FUNCTION(1, "I2SO0_BCK"),
		MTK_FUNCTION(2, "I2SO1_BCK"),
		MTK_FUNCTION(3, "PCM1_CLK"),
		MTK_FUNCTION(4, "I2SI0_BCK"),
		MTK_FUNCTION(5, "PWM3"),
		MTK_FUNCTION(6, "I2SI2_DI")
	),
	MTK_PIN(
		PINCTRL_PIN(101, "I2SO0_LRCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 108),
		MTK_FUNCTION(0, "GPIO101"),
		MTK_FUNCTION(1, "I2SO0_WS"),
		MTK_FUNCTION(2, "I2SO1_WS"),
		MTK_FUNCTION(3, "PCM1_SYNC"),
		MTK_FUNCTION(4, "I2SI0_WS"),
		MTK_FUNCTION(5, "PWM4"),
		MTK_FUNCTION(6, "I2SI3_DI")
	),
	MTK_PIN(
		PINCTRL_PIN(102, "I2SO0_MCLK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 109),
		MTK_FUNCTION(0, "GPIO102"),
		MTK_FUNCTION(1, "I2SO0_MCK"),
		MTK_FUNCTION(2, "I2SO1_MCK"),
		MTK_FUNCTION(3, "PCM1_DO"),
		MTK_FUNCTION(4, "I2SI0_MCK"),
		MTK_FUNCTION(5, "PWM5"),
		MTK_FUNCTION(6, "I2SI2_DI")
	),
	MTK_PIN(
		PINCTRL_PIN(103, "I2SO0_DATA0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 110),
		MTK_FUNCTION(0, "GPIO103"),
		MTK_FUNCTION(1, "I2SO0_DO"),
		MTK_FUNCTION(2, "AMUTE"),
		MTK_FUNCTION(3, "PCM1_DI"),
		MTK_FUNCTION(4, "I2SI0_DI"),
		MTK_FUNCTION(5, "SDA3"),
		MTK_FUNCTION(6, "I2SI3_DI")
	),
	MTK_PIN(
		PINCTRL_PIN(104, "I2SO0_DATA1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 111),
		MTK_FUNCTION(0, "GPIO104"),
		MTK_FUNCTION(1, "I2SO1_DO"),
		MTK_FUNCTION(2, "AMUTE1"),
		MTK_FUNCTION(3, "IR_IN"),
		MTK_FUNCTION(4, "I2SI1_DI"),
		MTK_FUNCTION(5, "SCL3"),
		MTK_FUNCTION(6, "SRCCLKENA1")
	),
	MTK_PIN(
		PINCTRL_PIN(105, "I2SO1_MCLK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 112),
		MTK_FUNCTION(0, "GPIO105"),
		MTK_FUNCTION(1, "I2SO1_MCK"),
		MTK_FUNCTION(2, "I2SO0_MCK"),
		MTK_FUNCTION(3, "I2SI0_MCK"),
		MTK_FUNCTION(4, "TDMIN_MCLK"),
		MTK_FUNCTION(5, "I2SO2_DO"),
		MTK_FUNCTION(6, "AMUTE1")
	),
	MTK_PIN(
		PINCTRL_PIN(106, "I2SO1_DATA"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 113),
		MTK_FUNCTION(0, "GPIO106"),
		MTK_FUNCTION(1, "I2SO1_DO"),
		MTK_FUNCTION(2, "I2SO0_DO"),
		MTK_FUNCTION(3, "I2SI0_DI"),
		MTK_FUNCTION(4, "TDMIN_DI"),
		MTK_FUNCTION(5, "I2SO3_DO"),
		MTK_FUNCTION(6, "I2SOS_DO")
	),
	MTK_PIN(
		PINCTRL_PIN(107, "I2SO1_BCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 114),
		MTK_FUNCTION(0, "GPIO107"),
		MTK_FUNCTION(1, "I2SO1_BCK"),
		MTK_FUNCTION(2, "I2SO0_BCK"),
		MTK_FUNCTION(3, "I2SI0_BCK"),
		MTK_FUNCTION(4, "TDMIN_BCK"),
		MTK_FUNCTION(5, "I2SO4_DO"),
		MTK_FUNCTION(6, "I2SOS_BCK")
	),
	MTK_PIN(
		PINCTRL_PIN(108, "I2SO1_LRCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 115),
		MTK_FUNCTION(0, "GPIO108"),
		MTK_FUNCTION(1, "I2SO1_WS"),
		MTK_FUNCTION(2, "I2SO0_WS"),
		MTK_FUNCTION(3, "I2SI0_WS"),
		MTK_FUNCTION(4, "TDMIN_LRCK"),
		MTK_FUNCTION(5, "I2SO5_DO"),
		MTK_FUNCTION(6, "I2SOS_WS")
	),
	MTK_PIN(
		PINCTRL_PIN(109, "DMIC1_SCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 116),
		MTK_FUNCTION(0, "GPIO109"),
		MTK_FUNCTION(1, "DMIC1_SCK"),
		MTK_FUNCTION(2, "DMIC0_SCK"),
		MTK_FUNCTION(3, "TDMIN_DI"),
		MTK_FUNCTION(4, "I2SO0_DO"),
		MTK_FUNCTION(5, "I2SI0_DI"),
		MTK_FUNCTION(6, "AMUTE")
	),
	MTK_PIN(
		PINCTRL_PIN(110, "DMIC1_DAT"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 117),
		MTK_FUNCTION(0, "GPIO110"),
		MTK_FUNCTION(1, "DMIC1_DAT"),
		MTK_FUNCTION(2, "DMIC0_DAT"),
		MTK_FUNCTION(3, "TDMIN_BCK"),
		MTK_FUNCTION(4, "I2SO0_BCK"),
		MTK_FUNCTION(5, "I2SI0_WS"),
		MTK_FUNCTION(6, "AMUTE1")
	),
	MTK_PIN(
		PINCTRL_PIN(111, "DMIC0_SCK"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 118),
		MTK_FUNCTION(0, "GPIO111"),
		MTK_FUNCTION(1, "DMIC0_SCK"),
		MTK_FUNCTION(2, "DMIC0_DAT_R"),
		MTK_FUNCTION(3, "TDMIN_LRCK"),
		MTK_FUNCTION(4, "I2SO0_WS"),
		MTK_FUNCTION(5, "I2SI0_MCK"),
		MTK_FUNCTION(6, "SDA2")
	),
	MTK_PIN(
		PINCTRL_PIN(112, "DMIC0_DAT"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 119),
		MTK_FUNCTION(0, "GPIO112"),
		MTK_FUNCTION(1, "DMIC0_DAT"),
		MTK_FUNCTION(2, "AMUTE"),
		MTK_FUNCTION(3, "TDMIN_MCLK"),
		MTK_FUNCTION(4, "I2SO0_MCK"),
		MTK_FUNCTION(5, "I2SI0_BCK"),
		MTK_FUNCTION(6, "SCL2")
	),
	MTK_PIN(
		PINCTRL_PIN(113, "URXD0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 120),
		MTK_FUNCTION(0, "GPIO113"),
		MTK_FUNCTION(1, "URXD1"),
		MTK_FUNCTION(2, "URXD0"),
		MTK_FUNCTION(3, "SDA1"),
		MTK_FUNCTION(4, "AMUTE"),
		MTK_FUNCTION(5, "SPI_CS_0"),
		MTK_FUNCTION(6, "SPI_CS_1")
	),
	MTK_PIN(
		PINCTRL_PIN(114, "UTXD0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 121),
		MTK_FUNCTION(0, "GPIO114"),
		MTK_FUNCTION(1, "UTXD1"),
		MTK_FUNCTION(2, "UTXD0"),
		MTK_FUNCTION(3, "SCL1"),
		MTK_FUNCTION(4, "AMUTE1"),
		MTK_FUNCTION(5, "SPI_MI_0"),
		MTK_FUNCTION(6, "SPI_MI_1")
	),
	MTK_PIN(
		PINCTRL_PIN(115, "URXD2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 122),
		MTK_FUNCTION(0, "GPIO115"),
		MTK_FUNCTION(1, "URXD2"),
		MTK_FUNCTION(2, "URTS0"),
		MTK_FUNCTION(3, "SDA2"),
		MTK_FUNCTION(4, "AMUTE"),
		MTK_FUNCTION(5, "SPI_CK_0"),
		MTK_FUNCTION(6, "SPI_CK_1")
	),
	MTK_PIN(
		PINCTRL_PIN(116, "UTXD2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 123),
		MTK_FUNCTION(0, "GPIO116"),
		MTK_FUNCTION(1, "UTXD2"),
		MTK_FUNCTION(2, "UCTS0"),
		MTK_FUNCTION(3, "SCL2"),
		MTK_FUNCTION(4, "AMUTE1"),
		MTK_FUNCTION(5, "SPI_MO_0"),
		MTK_FUNCTION(6, "SPI_MO_1")
	),
	MTK_PIN(
		PINCTRL_PIN(117, "SDA_EPM"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 124),
		MTK_FUNCTION(0, "GPIO117"),
		MTK_FUNCTION(1, "SDA_EPM"),
		MTK_FUNCTION(2, "SDA1")
	),
	MTK_PIN(
		PINCTRL_PIN(118, "SCL_EPM"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 125),
		MTK_FUNCTION(0, "GPIO118"),
		MTK_FUNCTION(1, "SCL_EPM"),
		MTK_FUNCTION(2, "SCL1")
	),
	MTK_PIN(
		PINCTRL_PIN(119, "WP_EPM"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 126),
		MTK_FUNCTION(0, "GPIO119"),
		MTK_FUNCTION(1, "WP_EPM"),
		MTK_FUNCTION(2, "AMUTE1")
	),
	MTK_PIN(
		PINCTRL_PIN(120, "GBE_TXD3"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 127),
		MTK_FUNCTION(0, "GPIO120"),
		MTK_FUNCTION(1, "GBE_TXD3"),
		MTK_FUNCTION(5, "TSCLK"),
		MTK_FUNCTION(6, "SDA1")
	),
	MTK_PIN(
		PINCTRL_PIN(121, "GBE_TXD2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 128),
		MTK_FUNCTION(0, "GPIO121"),
		MTK_FUNCTION(1, "GBE_TXD2"),
		MTK_FUNCTION(5, "TSSYNC"),
		MTK_FUNCTION(6, "SCL1")
	),
	MTK_PIN(
		PINCTRL_PIN(122, "GBE_TXD1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 129),
		MTK_FUNCTION(0, "GPIO122"),
		MTK_FUNCTION(1, "GBE_TXD1"),
		MTK_FUNCTION(5, "TSVAL"),
		MTK_FUNCTION(6, "URXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(123, "GBE_TXD0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 130),
		MTK_FUNCTION(0, "GPIO123"),
		MTK_FUNCTION(1, "GBE_TXD0"),
		MTK_FUNCTION(5, "TSDATA0"),
		MTK_FUNCTION(6, "UTXD1")
	),
	MTK_PIN(
		PINCTRL_PIN(124, "GBE_TXC"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 131),
		MTK_FUNCTION(0, "GPIO124"),
		MTK_FUNCTION(1, "GBE_TXC"),
		MTK_FUNCTION(5, "TSDATA1")
	),
	MTK_PIN(
		PINCTRL_PIN(125, "GBE_TXEN"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 132),
		MTK_FUNCTION(0, "GPIO125"),
		MTK_FUNCTION(1, "GBE_TXEN"),
		MTK_FUNCTION(5, "TSDATA2")
	),
	MTK_PIN(
		PINCTRL_PIN(126, "GBE_RXD3"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 133),
		MTK_FUNCTION(0, "GPIO126"),
		MTK_FUNCTION(1, "GBE_RXD3"),
		MTK_FUNCTION(5, "TSDATA3"),
		MTK_FUNCTION(6, "SDA2")
	),
	MTK_PIN(
		PINCTRL_PIN(127, "GBE_RXD2"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 134),
		MTK_FUNCTION(0, "GPIO127"),
		MTK_FUNCTION(1, "GBE_RXD2"),
		MTK_FUNCTION(5, "TSDATA4"),
		MTK_FUNCTION(6, "SCL2")
	),
	MTK_PIN(
		PINCTRL_PIN(128, "GBE_RXD1"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 135),
		MTK_FUNCTION(0, "GPIO128"),
		MTK_FUNCTION(1, "GBE_RXD1"),
		MTK_FUNCTION(5, "TSDATA5"),
		MTK_FUNCTION(6, "URXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(129, "GBE_RXD0"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 136),
		MTK_FUNCTION(0, "GPIO129"),
		MTK_FUNCTION(1, "GBE_RXD0"),
		MTK_FUNCTION(5, "TSDATA6"),
		MTK_FUNCTION(6, "UTXD2")
	),
	MTK_PIN(
		PINCTRL_PIN(130, "GBE_RXDV"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 137),
		MTK_FUNCTION(0, "GPIO130"),
		MTK_FUNCTION(1, "GBE_RXDV"),
		MTK_FUNCTION(5, "TSDATA7")
	),
	MTK_PIN(
		PINCTRL_PIN(131, "GBE_RXER"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 138),
		MTK_FUNCTION(0, "GPIO131"),
		MTK_FUNCTION(1, "GBE_RXER"),
		MTK_FUNCTION(6, "AMUTE")
	),
	MTK_PIN(
		PINCTRL_PIN(132, "GBE_RXC"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 139),
		MTK_FUNCTION(0, "GPIO132"),
		MTK_FUNCTION(1, "GBE_RXC")
	),
	MTK_PIN(
		PINCTRL_PIN(133, "GBE_MDC"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 141),
		MTK_FUNCTION(0, "GPIO133"),
		MTK_FUNCTION(1, "GBE_MDC")
	),
	MTK_PIN(
		PINCTRL_PIN(134, "GBE_MDIO"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 142),
		MTK_FUNCTION(0, "GPIO134"),
		MTK_FUNCTION(1, "GBE_MDIO")
	),
	MTK_PIN(
		PINCTRL_PIN(135, "GBE_TXER"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 143),
		MTK_FUNCTION(0, "GPIO135"),
		MTK_FUNCTION(1, "GBE_TXER"),
		MTK_FUNCTION(3, "PWM3"),
		MTK_FUNCTION(5, "URXD2"),
		MTK_FUNCTION(6, "I2SOS_DO"),
		MTK_FUNCTION(7, "SDA3")
	),
	MTK_PIN(
		PINCTRL_PIN(136, "GBE_INTR"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 144),
		MTK_FUNCTION(0, "GPIO136"),
		MTK_FUNCTION(1, "GBE_INTR"),
		MTK_FUNCTION(2, "GBE_CRS"),
		MTK_FUNCTION(3, "PWM4"),
		MTK_FUNCTION(6, "I2SOS_WS"),
		MTK_FUNCTION(7, "SDA3")
	),
	MTK_PIN(
		PINCTRL_PIN(137, "GBE_COL"),
		NULL, "mt8695",
		MTK_EINT_FUNCTION(0, 145),
		MTK_FUNCTION(0, "GPIO137"),
		MTK_FUNCTION(1, "GBE_COL"),
		MTK_FUNCTION(2, "AMUTE1"),
		MTK_FUNCTION(3, "PWM5"),
		MTK_FUNCTION(5, "UTXD2"),
		MTK_FUNCTION(6, "I2SOS_BCK"),
		MTK_FUNCTION(7, "SCL3")
	),
};

#endif /* __PINCTRL_MTK_MT8695_H */
