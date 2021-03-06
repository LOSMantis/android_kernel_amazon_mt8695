/*
 * Copyright (C) 2015 MediaTek Inc.
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/io.h>
#include <emi.h>

DEFINE_SEMAPHORE(emi_bwl_sem);

void __iomem *EMI_BASE;
void __iomem *EMI_CHA_BASE;
void __iomem *EMI_CHB_BASE;

static const struct of_device_id emi_bwl_of_match[] = {
	{ .compatible = "mediatek,mt2701-emi", },
	{ .compatible = "mediatek,mt8127-emi", },
	{ .compatible = "mediatek,mt7623-emi", },
	{ .compatible = "mediatek,mt8695-emi", },
	{}
};

/* define EMI bandwiwth limiter control table */
static struct emi_bwl_ctrl ctrl_tbl[NR_CON_SCE];

/* current concurrency scenario */
static int cur_con_sce = 0x0FFFFFFF;

#ifdef CONFIG_MTK_EMI_7622
/****************** For 7622 ******************/
/* define concurrency scenario strings */
static const char * const con_sce_str[] = {
#define X_CON_SCE(con_sce, arba, arbb, arbc, arbd, arbe) (#con_sce),
#include "con_sce_ddr3_16.h"
#undef X_CON_SCE
};

static const unsigned int emi_arba_ddr3_16_val[] = {
#define X_CON_SCE(con_sce, arba, arbb, arbc, arbd, arbe, arbf) arba,
#include "con_sce_ddr3_7622.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbb_ddr3_16_val[] = {
#define X_CON_SCE(con_sce, arba, arbb, arbc, arbd, arbe, arbf) arbb,
#include "con_sce_ddr3_7622.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbc_ddr3_16_val[] = {
#define X_CON_SCE(con_sce, arba, arbb, arbc, arbd, arbe, arbf) arbc,
#include "con_sce_ddr3_7622.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbd_ddr3_16_val[] = {
#define X_CON_SCE(con_sce, arba, arbb, arbc, arbd, arbe, arbf) arbd,
#include "con_sce_ddr3_7622.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbe_ddr3_16_val[] = {
#define X_CON_SCE(con_sce, arba, arbb, arbc, arbd, arbe, arbf) arbe,
#include "con_sce_ddr3_7622.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbf_ddr3_16_val[] = {
#define X_CON_SCE(con_sce, arba, arbb, arbc, arbd, arbe, arbf) arbf,
#include "con_sce_ddr3_7622.h"
#undef X_CON_SCE
};
#endif

#ifdef CONFIG_MTK_EMI_8695
/****************** For 8695 ******************/
/* define concurrency scenario strings */
static const char * const con_sce_str[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) (#con_sce),
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_mdct_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) mdct,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_iocl_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) iocl,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_iocl_2nd_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) iocl_2nd,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_iocm_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) iocm,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_iocm_2nd_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) iocm_2nd,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbc_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) arbc,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbd_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) arbd,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbf_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) arbf,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbg_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) arbg,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_arbh_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) arbh,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_slct_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) slct,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_shfo_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) shfo,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_slva_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) slva,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_testb_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) testb,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_cha_slct_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) cha_slct,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};

static const unsigned int emi_chb_slct_lpddr4_16_val[] = {
#define X_CON_SCE(con_sce, mdct, iocl, iocl_2nd, iocm, iocm_2nd, arbc, arbd, arbf, arbg, arbh, slct, \
	shfo, slva, testb, cha_slct, chb_slct) chb_slct,
#include "con_sce_lpddr4_8695.h"
#undef X_CON_SCE
};
#endif

/*
 * mtk_mem_bw_ctrl: set EMI bandwidth limiter for memory bandwidth control
 * @sce: concurrency scenario ID
 * @op: either ENABLE_CON_SCE or DISABLE_CON_SCE
 * Return 0 for success; return negative values for failure.
 */
int mtk_mem_bw_ctrl(int sce, int op)
{
	int i, highest;

	if (sce >= NR_CON_SCE)
		return -1;

	if (op != ENABLE_CON_SCE && op != DISABLE_CON_SCE)
		return -1;

	if (in_interrupt())
		return -1;

	down(&emi_bwl_sem);

	if (op == ENABLE_CON_SCE) {
		ctrl_tbl[sce].ref_cnt++;
	} else if (op == DISABLE_CON_SCE) {
		if (ctrl_tbl[sce].ref_cnt != 0)
			ctrl_tbl[sce].ref_cnt--;
	}

  /* find the scenario with the highest priority */
	highest = -1;
	for (i = 0; i < NR_CON_SCE; i++) {
		if (ctrl_tbl[i].ref_cnt != 0) {
			highest = i;
			break;
		}
	}

	if (highest == -1)
		highest = CON_SCE_NORMAL;

  /* set new EMI bandwidth limiter value */
#ifdef CONFIG_MTK_EMI_8695
	if (highest != cur_con_sce) {
		writel(emi_mdct_lpddr4_16_val[highest], EMI_MDCT);
		if (highest == CON_SCE_VP) {
			writel(emi_iocl_lpddr4_16_val[highest], EMI_IOCL);
			writel(emi_iocl_2nd_lpddr4_16_val[highest], EMI_IOCL_2ND);
		} else {
			writel(emi_iocl_2nd_lpddr4_16_val[highest], EMI_IOCL_2ND);
			writel(emi_iocl_lpddr4_16_val[highest], EMI_IOCL);
		}
		writel(emi_iocm_lpddr4_16_val[highest], EMI_IOCM);
		writel(emi_iocm_2nd_lpddr4_16_val[highest], EMI_IOCM_2ND);
		writel(emi_arbc_lpddr4_16_val[highest], EMI_ARBC);
		writel(emi_arbd_lpddr4_16_val[highest], EMI_ARBD);
		writel(emi_arbf_lpddr4_16_val[highest], EMI_ARBF);
		writel(emi_arbg_lpddr4_16_val[highest], EMI_ARBG);
		writel(emi_arbh_lpddr4_16_val[highest], EMI_ARBH);
		writel(emi_slct_lpddr4_16_val[highest], EMI_SLCT);
		writel(emi_shfo_lpddr4_16_val[highest], EMI_SHF0);
		writel(emi_slva_lpddr4_16_val[highest], EMI_SLVA);
		writel(emi_testb_lpddr4_16_val[highest], EMI_TESTB);
		writel(emi_cha_slct_lpddr4_16_val[highest], EMI_CHA_SLCT);
		writel(emi_chb_slct_lpddr4_16_val[highest], EMI_CHB_SLCT);
		cur_con_sce = highest;
	}
#else
	if (highest != cur_con_sce) {
		writel(emi_arba_ddr3_16_val[highest], EMI_ARBA);
		writel(emi_arbb_ddr3_16_val[highest], EMI_ARBB);
		writel(emi_arbc_ddr3_16_val[highest], EMI_ARBC);
		writel(emi_arbd_ddr3_16_val[highest], EMI_ARBD);
		writel(emi_arbe_ddr3_16_val[highest], EMI_ARBE);
#ifdef CONFIG_MTK_EMI_7622
		writel(emi_arbf_ddr3_16_val[highest], EMI_ARBF);
#endif
		cur_con_sce = highest;
	}
#endif
	up(&emi_bwl_sem);

	return 0;
}


/*
 * con_sce_show: sysfs con_sce file show function.
 * @driver:
 * @buf:
 * Return the number of read bytes.
 */
static ssize_t con_sce_show(struct device_driver *driver, char *buf)
{
	if (cur_con_sce >= NR_CON_SCE)
		sprintf(buf, "none\n");
	else
		sprintf(buf, "%s\n", con_sce_str[cur_con_sce]);

	return strlen(buf);
}

/*
 * con_sce_store: sysfs con_sce file store function.
 * @driver:
 * @buf:
 * @count:
 * Return the number of write bytes.
 */
static ssize_t con_sce_store(struct device_driver *driver, const char *buf, size_t count)
{
	int i;

	for (i = 0; i < NR_CON_SCE; i++) {
		if (!strncmp(buf, con_sce_str[i], strlen(con_sce_str[i]))) {
			if (!strncmp(buf + strlen(con_sce_str[i]) + 1, EN_CON_SCE_STR, strlen(EN_CON_SCE_STR))) {
				mtk_mem_bw_ctrl(i, ENABLE_CON_SCE);
				pr_info("concurrency scenario %s ON\n", con_sce_str[i]);
				break;
			} else if (!strncmp(buf + strlen(con_sce_str[i]) + 1,
						DIS_CON_SCE_STR, strlen(DIS_CON_SCE_STR))) {
				mtk_mem_bw_ctrl(i, DISABLE_CON_SCE);
				pr_info("concurrency scenario %s OFF\n", con_sce_str[i]);
				break;
			}
		}
	}

	return count;
}

DRIVER_ATTR(concurrency_scenario, 0644, con_sce_show, con_sce_store);

static int emi_bwl_probe(struct platform_device *dev)
{
	EMI_BASE = of_iomap(dev->dev.of_node, 0);
	EMI_CHA_BASE = of_iomap(dev->dev.of_node, 1);
	EMI_CHB_BASE = of_iomap(dev->dev.of_node, 2);

	return 0;
}

static struct platform_driver emi_bwl_driver = {
	.probe = emi_bwl_probe,
	.driver = {
		.name = "mem_bw_ctrl",
		.of_match_table = emi_bwl_of_match,
	},
};

/*
 * emi_bwl_mod_init: module init function.
 */
static int __init emi_bwl_mod_init(void)
{
	int ret;

	/*register emi bwl*/
	ret = platform_driver_register(&emi_bwl_driver);
	if (ret)
		pr_err("fail to register EMI_BW_LIMITER driver\n");

	ret = driver_create_file(&emi_bwl_driver.driver, &driver_attr_concurrency_scenario);
	if (ret)
		pr_err("fail to create EMI_BW_LIMITER sysfs file\n");

	mtk_mem_bw_ctrl(CON_SCE_NORMAL, ENABLE_CON_SCE);

	return 0;
}

/*
 * emi_bwl_mod_exit: module exit function.
 */
static void __exit emi_bwl_mod_exit(void)
{
}

module_init(emi_bwl_mod_init);
module_exit(emi_bwl_mod_exit);

