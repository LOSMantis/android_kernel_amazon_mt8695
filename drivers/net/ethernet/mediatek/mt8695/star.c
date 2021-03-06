/* Mediatek STAR MAC network driver.
 *
 * Copyright (c) 2016-2017 Mediatek Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#include <linux/clk.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/mii.h>
#include <linux/ethtool.h>
#include <linux/of_net.h>
#include <linux/pm_runtime.h>

#include "star.h"
#include "star_procfs.h"

#define STAR_DRV_NAME	"star-eth"
#define STAR_DRV_VERSION "version-1.0"
#define ETH_WOL_NAME "WOL"

int star_dbg_level;

static void star_finish_xmit(struct net_device *dev);

static struct sk_buff *get_skb(struct net_device *ndev)
{
	unsigned char *tail;
	u32 offset;
	struct sk_buff *skb;

	skb = dev_alloc_skb(ndev->mtu + ETH_EXTRA_PKT_LEN);
	if (!skb)
		return NULL;

	/* Shift to 16 byte alignment */
	/* while  call dev_alloc_skb(), the pointer of
	 * skb->tail & skb->data is the same
	 */
	tail = skb_tail_pointer(skb);
	if (((uintptr_t)tail) & (ETH_SKB_ALIGNMENT - 1)) {
		offset = ((uintptr_t)tail) & (ETH_SKB_ALIGNMENT - 1);
		skb_reserve(skb, ETH_SKB_ALIGNMENT - offset);
	}

	/* Reserve 2 bytes for zero copy */
	/* Reserving 2 bytes makes the skb->data points to
	 * a 16-byte aligned address after eth_type_trans is called.
	 * Since eth_type_trans will extracts the pointer (ETH_LEN)
	 * 14 bytes. With this 2 bytes reserved, the skb->data
	 * can be 16-byte aligned before passing to upper layer.
	 */
	skb_reserve(skb, 2);

	return skb;
}

/* pre-allocate Rx buffer */
static int alloc_rx_skbs(star_dev *star_dev)
{
	int retval;
	star_private *star_prv = star_dev->star_prv;

	do {
		u32 dmaBuf;
		struct sk_buff *skb = get_skb(star_prv->dev);

		if (!skb) {
			STAR_MSG(STAR_ERR, "Error! No momory for rx sk_buff\n");
			return -ENOMEM;
		}

		/* Note:
		* We pass to dma addr with skb->tail-2 (4N aligned),
		* Because Star Ethernet buffer must 16 byte align
		* But the RX_OFFSET_2B_DIS has to be set to 0, making
		* DMA to write tail (4N+2) addr.
		*/
		dmaBuf = dma_map_single(star_dev->dev,
					skb_tail_pointer(skb) - 2,
					skb_tailroom(skb),
					DMA_FROM_DEVICE);
		if (dma_mapping_error(star_dev->dev, dmaBuf)) {
			STAR_MSG(STAR_ERR, "dma_mapping_error error\n");
			return -ENOMEM;
		}

		retval = star_dma_rx_set(star_dev, dmaBuf,
					 skb_tailroom(skb), (uintptr_t)skb);
		STAR_MSG(STAR_VERB, "rx descriptor idx(%d) for skb(%p)\n",
			 retval, skb);
		if (retval < 0) {
			dma_unmap_single(star_dev->dev, dmaBuf,
					 skb_tailroom(skb), DMA_FROM_DEVICE);
					 dev_kfree_skb(skb);
		}
	} while (retval >= 0);

	return 0;
}

/* Free Tx descriptor and skbs not xmited */
static void free_tx_skbs(star_dev *star_dev)
{
	int retval;
	uintptr_t extBuf;
	u32 ctrl_len, len, dmaBuf;

	do {
		retval = star_dma_tx_get(star_dev,
					 (u32 *)&dmaBuf, &ctrl_len, &extBuf);
		if (retval >= 0 && extBuf != 0) {
			len = star_dma_tx_length(ctrl_len);
			dma_unmap_single(star_dev->dev, dmaBuf,
					 len, DMA_TO_DEVICE);
			STAR_MSG(STAR_DBG,
				 "get tx desc index(%d) for skb(0x%lx)\n",
				 retval, extBuf);
			dev_kfree_skb((struct sk_buff *)extBuf);
		}
	} while (retval >= 0);
}

static void free_rx_skbs(star_dev *star_dev)
{
	int retval;
	uintptr_t  extBuf;
	u32 dmaBuf;

	/* Free Rx descriptor */
	do {
		retval = star_dma_rx_get(star_dev,
					 (u32 *)&dmaBuf, NULL, &extBuf);
		if (retval >= 0 && extBuf != 0) {
			dma_unmap_single(star_dev->dev, dmaBuf,
					 skb_tailroom((struct sk_buff *)
						      extBuf),
						      DMA_FROM_DEVICE);
			STAR_MSG(STAR_DBG,
				 "get tx desc index(%d) for skb(0x%lx)\n",
				 retval, extBuf);
			dev_kfree_skb((struct sk_buff *)extBuf);
		}
	} while (retval >= 0);
}

static int receive_one_packet(star_dev *star_dev, bool napi)
{
	int retval;
	uintptr_t extBuf;
	u32 ctrl_len, len, dmaBuf;
	struct sk_buff *curr_skb, *new_skb;
	star_private *star_prv = star_dev->star_prv;
	struct net_device *ndev = star_prv->dev;

	retval = star_dma_rx_get(star_dev, &dmaBuf, &ctrl_len, &extBuf);
	/*no any skb to receive*/
	if (retval < 0)
		return retval;

	curr_skb = (struct sk_buff *)extBuf;
	dma_unmap_single(star_dev->dev, dmaBuf,
			 skb_tailroom(curr_skb), DMA_FROM_DEVICE);
	STAR_MSG(STAR_VERB, "%s(%s):rx des %d for skb(0x%lx)/length(%d)\n",
		 __func__, ndev->name, retval, extBuf,
		 star_dma_rx_length(ctrl_len));

	if (star_dma_rx_valid(ctrl_len)) {
		len = star_dma_rx_length(ctrl_len);
		new_skb = get_skb(ndev);
		if (new_skb) {
			skb_put(curr_skb, len);
			curr_skb->ip_summed = CHECKSUM_NONE;
			curr_skb->protocol = eth_type_trans(curr_skb, ndev);
			curr_skb->dev = ndev;

			/* send the packet up protocol stack */
			(napi ? netif_receive_skb : netif_rx)(curr_skb);
			/* set the time of the last receive */
			ndev->last_rx = jiffies;
			star_dev->stats.rx_packets++;
			star_dev->stats.rx_bytes += len;
		} else {
			star_dev->stats.rx_dropped++;
			new_skb = curr_skb;
		}
	} else {
		/* Error packet */
		new_skb = curr_skb;
		star_dev->stats.rx_errors++;
		star_dev->stats.rx_crc_errors += star_dma_rx_crc_err(ctrl_len);
	}

	dmaBuf = dma_map_single(star_dev->dev,
				skb_tail_pointer(new_skb) - 2,
				skb_tailroom(new_skb),
				DMA_FROM_DEVICE);
	star_dma_rx_set(star_dev, dmaBuf,
			skb_tailroom(new_skb), (uintptr_t)new_skb);

	return retval;
}

static int star_poll(struct napi_struct *napi, int budget)
{
	int retval, npackets;
	star_private *star_prv = container_of(napi, star_private, napi);
	star_dev *star_dev = &star_prv->star_dev;

	for (npackets = 0; npackets < budget; npackets++) {
		retval = receive_one_packet(star_dev, true);
		if (retval < 0)
			break;
	}

	star_dma_rx_resume(star_dev);

	if (npackets < budget) {
		local_irq_disable();
		napi_complete(napi);
		star_intr_rx_enable(star_dev);
		local_irq_enable();
	}

	return npackets;
}

/* star tx use tasklet */
static void star_dsr(unsigned long data)
{
	star_private *star_prv;
	star_dev *star_dev;
	struct net_device *ndev = (struct net_device *)data;

	STAR_MSG(STAR_VERB, "%s(%s)\n", __func__, ndev->name);

	star_prv = netdev_priv(ndev);
	star_dev = &star_prv->star_dev;

	if (star_prv->tsk_tx) {
		star_prv->tsk_tx = false;
		star_finish_xmit(ndev);
	}
}

static irqreturn_t star_isr(int irq, void *dev_id)
{
	u32 intrStatus;
	u32 intr_clr_msk = 0xffffffff;
	star_private *star_prv;
	star_dev *star_dev;
	struct net_device *dev = (struct net_device *)dev_id;

	intr_clr_msk &= ~STAR_INT_STA_RXC;

	if (!dev) {
		STAR_MSG(STAR_ERR, "star_isr - unknown device\n");
		return IRQ_NONE;
	}

	STAR_MSG(STAR_VERB, "star_isr(%s)\n", dev->name);

	star_prv = netdev_priv(dev);
	star_dev = &star_prv->star_dev;

	star_intr_disable(star_dev);
	intrStatus = star_intr_status(star_dev);
	star_intr_clear(star_dev, intrStatus & intr_clr_msk);

	do {
		STAR_MSG(STAR_VERB,
			 "star_isr:interrupt status(0x%08x)\n", intrStatus);
		if (intrStatus & STAR_INT_STA_RXC) {
			STAR_MSG(STAR_VERB, "rx complete\n");
			/* Disable rx interrupts */
			star_intr_rx_disable(star_dev);
			/* Clear rx interrupt */
			star_intr_clear(star_dev, STAR_INT_STA_RXC);
			napi_schedule(&star_prv->napi);
		}

		if (intrStatus & STAR_INT_STA_RXQF)
			STAR_MSG(STAR_VERB, "rx queue full\n");

		if (intrStatus & STAR_INT_STA_RXFIFOFULL)
			STAR_MSG(STAR_WARN, "rx fifo full\n");

		if (intrStatus & STAR_INT_STA_TXC) {
			STAR_MSG(STAR_VERB, " tx complete\n");
			star_prv->tsk_tx = true;
		}

		if (intrStatus & STAR_INT_STA_TXQE)
			STAR_MSG(STAR_VERB, "tx queue empty\n");

		if (intrStatus & STAR_INT_STA_RX_PCODE)
			STAR_MSG(STAR_DBG, "Rx PCODE\n");

		if (intrStatus & STAR_INT_STA_MAGICPKT)
			STAR_MSG(STAR_WARN, "magic packet received\n");

		if (intrStatus & STAR_INT_STA_MIBCNTHALF) {
			STAR_MSG(STAR_VERB, " mib counter reach 2G\n");
			star_mib_init(star_dev);
		}

		if (intrStatus & STAR_INT_STA_PORTCHANGE) {
			STAR_MSG(STAR_DBG, "port status change\n");
			star_link_status_change(star_dev);
		}

		/* read interrupt requests came during interrupt handling */
		intrStatus = star_intr_status(star_dev);
		star_intr_clear(star_dev, intrStatus & intr_clr_msk);
	} while ((intrStatus & intr_clr_msk) != 0);

	star_intr_enable(star_dev);
	if (star_prv->tsk_tx)
		tasklet_schedule(&star_prv->dsr);

	STAR_MSG(STAR_VERB, "star_isr return\n");

	return IRQ_HANDLED;
}

#ifdef CONFIG_STAR_USE_RMII_MODE
static irqreturn_t star_eint_isr(int irq, void *dev_id)
{
	STAR_MSG(STAR_DBG, "enter star_eint_isr\n");

	return IRQ_HANDLED;
}
#endif

#ifdef CONFIG_NET_POLL_CONTROLLER
static void star_netpoll(struct net_device *dev)
{
	star_private *tp = netdev_priv(dev);
	star_dev *pdev = tp->mii.dev;

	disable_irq(pdev->irq);
	star_isr(pdev->irq, dev);
	enable_irq(pdev->irq);
}
#endif

static int star_mac_enable(struct net_device *ndev)
{
	int intrStatus;
	star_private *star_prv = netdev_priv(ndev);
	star_dev *star_dev = &star_prv->star_dev;

	STAR_MSG(STAR_DBG, "%s(%s)\n", __func__, ndev->name);

	/* Start RX FIFO receive */
	star_nic_pdset(star_dev, false);

	star_intr_disable(star_dev);
	star_dma_tx_stop(star_dev);
	star_dma_rx_stop(star_dev);

	netif_carrier_off(ndev);

	star_mac_init(star_dev, ndev->dev_addr);

	star_dma_init(star_dev,
		      star_prv->desc_vir_addr, star_prv->desc_dma_addr);

	/*Enable PHY auto-polling*/
	star_phyctrl_init(star_dev, 1, star_prv->phy_addr);

	if (alloc_rx_skbs(star_dev)) {
		STAR_MSG(STAR_ERR, "rx bufs init fail\n");
		return -ENOMEM;
	}

	STAR_MSG(STAR_DBG, "request interrupt vector=%d\n", ndev->irq);
	if (request_irq(ndev->irq, star_isr, IRQF_TRIGGER_NONE,
			ndev->name, ndev) != 0) {
		STAR_MSG(STAR_ERR, "interrupt %d request fail\n", ndev->irq);
		return -ENODEV;
	}

#ifdef CONFIG_STAR_USE_RMII_MODE
	STAR_MSG(STAR_DBG, "request eint_irq vector=%d\n", star_prv->eint_irq);
	if (request_irq(star_prv->eint_irq, star_eint_isr,
			IRQ_TYPE_EDGE_FALLING, ndev->name, ndev) != 0) {
		STAR_MSG(STAR_ERR,
			 "eint_irq %d request fail\n", star_prv->eint_irq);
		return -ENODEV;
	}
#endif

	napi_enable(&star_prv->napi);

	intrStatus = star_intr_status(star_dev);
	star_intr_clear(star_dev, intrStatus);
	star_intr_enable(star_dev);

	if (star_dev->phy_ops->init)
		star_dev->phy_ops->init(star_dev);

	dma_tx_start_and_reset_tx_desc(star_dev);
	dma_rx_start_and_reset_rx_desc(star_dev);

	star_link_status_change(star_dev);
	netif_start_queue(ndev);

	return 0;
}

static void star_mac_disable(struct net_device *ndev)
{
	int intrStatus;
	star_private *star_prv = netdev_priv(ndev);
	star_dev *star_dev = &star_prv->star_dev;

	STAR_MSG(STAR_DBG, "%s(%s)\n", __func__, ndev->name);

	netif_stop_queue(ndev);

	napi_disable(&star_prv->napi);

	star_intr_disable(star_dev);
	star_dma_tx_stop(star_dev);
	star_dma_rx_stop(star_dev);
	intrStatus = star_intr_status(star_dev);
	star_intr_clear(star_dev, intrStatus);

	free_irq(ndev->irq, ndev);
#ifdef CONFIG_STAR_USE_RMII_MODE
	free_irq(star_prv->eint_irq, ndev);
#endif

	/* Free Tx descriptor */
	free_tx_skbs(star_dev);

	/* Free Rx descriptor */
	free_rx_skbs(star_dev);
}

static int star_open(struct net_device *ndev)
{
	int ret;
	star_private *star_prv = netdev_priv(ndev);

	STAR_MSG(STAR_DBG, "star_open(%s)\n", ndev->name);

	if (star_prv->opened) {
		STAR_MSG(STAR_DBG, "%s(%s) is already open\n",
			 __func__, ndev->name);
		return 0;
	}

	ret = star_mac_enable(ndev);
	if (ret) {
		STAR_MSG(STAR_DBG, "star_mac_enable(%s) fail\n", ndev->name);
		return ret;
	}

	star_prv->opened = true;

	return 0;
}

static int star_stop(struct net_device *ndev)
{
	star_private *star_prv = netdev_priv(ndev);

	STAR_MSG(STAR_DBG, "enter %s\n", __func__);
	if (!star_prv->opened) {
		STAR_MSG(STAR_DBG, "%s(%s) is already close\n", __func__,
			 ndev->name);
		return 0;
	}

	star_mac_disable(ndev);
	star_prv->opened = false;

	return 0;
}

static int star_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	u32 dmaBuf;
	unsigned long flags;
	star_private *star_prv;
	star_dev *star_dev;

	star_prv = netdev_priv(ndev);
	star_dev = &star_prv->star_dev;

	/* If frame size > Max frame size, drop this packet */
	if (skb->len > ETH_MAX_FRAME_SIZE) {
		STAR_MSG(STAR_WARN, "%s:Tx frame len is oversized(%d bytes)\n",
			 ndev->name, skb->len);
		dev_kfree_skb(skb);
		star_dev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}

	dmaBuf = dma_map_single(star_dev->dev,
				skb->data, skb_headlen(skb), DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(star_dev->dev, dmaBuf))) {
		STAR_MSG(STAR_ERR, "%s,dma_mapping_error error\n", __func__);
		return -ENOMEM;
	}

	spin_lock_irqsave(&star_prv->lock, flags);
	star_dma_tx_set(star_dev, dmaBuf, skb->len, (uintptr_t)skb);
	/* Tx descriptor ring full */
	if (star_dev->tx_num == star_dev->tx_ring_size)
		netif_stop_queue(ndev);
	spin_unlock_irqrestore(&star_prv->lock, flags);
	star_dma_tx_resume(star_dev);
	ndev->trans_start = jiffies;

	return NETDEV_TX_OK;
}

static void star_finish_xmit(struct net_device *ndev)
{
	int retval, wake = 0;
	star_private *star_prv;
	star_dev *star_dev;

	star_prv = netdev_priv(ndev);
	star_dev = &star_prv->star_dev;

	do {
		uintptr_t extBuf;
		u32 ctrl_len;
		u32 len;
		u32 dmaBuf;
		unsigned long flags;

		spin_lock_irqsave(&star_prv->lock, flags);
		retval = star_dma_tx_get(star_dev, (u32 *)&dmaBuf,
					 &ctrl_len, &extBuf);
		spin_unlock_irqrestore(&star_prv->lock, flags);

		if (retval >= 0 && extBuf != 0) {
			len = star_dma_tx_length(ctrl_len);
			dma_unmap_single(star_dev->dev,
					 dmaBuf, len, DMA_TO_DEVICE);
			STAR_MSG(STAR_VERB,
				 "%s get tx desc(%d) for skb(0x%lx), len(%08x)\n",
				 __func__, retval, extBuf, len);

			dev_kfree_skb_irq((struct sk_buff *)extBuf);

			star_dev->stats.tx_bytes += len;
			star_dev->stats.tx_packets++;
			wake = 1;
		}
	} while (retval >= 0);

	if (wake)
		netif_wake_queue(ndev);
}

static struct net_device_stats *star_get_stats(struct net_device *ndev)
{
	star_private *star_prv;
	star_dev *star_dev;

	STAR_MSG(STAR_VERB, "enter %s\n", __func__);

	star_prv = netdev_priv(ndev);
	star_dev = &star_prv->star_dev;

	return &star_dev->stats;
}

#define STAR_HTABLE_SIZE 512
#define STAR_HTABLE_SIZE_LIMIT (STAR_HTABLE_SIZE >> 1)

static void star_set_multicast_list(struct net_device *ndev)
{
	unsigned long flags;
	star_private *star_prv;
	star_dev *star_dev;

	STAR_MSG(STAR_VERB, "enter %s\n", __func__);

	star_prv = netdev_priv(ndev);
	star_dev = &star_prv->star_dev;

	spin_lock_irqsave(&star_prv->lock, flags);

	if (ndev->flags & IFF_PROMISC) {
		STAR_MSG(STAR_WARN, "%s: Promiscuous mode enabled.\n",
			 ndev->name);
		star_arl_promisc_enable(star_dev);
	} else if ((netdev_mc_count(ndev) > STAR_HTABLE_SIZE_LIMIT) ||
				(ndev->flags & IFF_ALLMULTI)) {
		u32 hashIdx;

		for (hashIdx = 0; hashIdx < STAR_HTABLE_SIZE; hashIdx++)
			star_set_hashbit(star_dev, hashIdx, 1);
	} else {
		struct netdev_hw_addr *ha;

		netdev_for_each_mc_addr(ha, ndev) {
			u32 hashAddr;

			hashAddr = (u32)(((ha->addr[0] & 0x1) << 8)
				   + (u32)(ha->addr[5]));
			star_set_hashbit(star_dev, hashAddr, 1);
		}
	}

	spin_unlock_irqrestore(&star_prv->lock, flags);
}

static int star_ioctl(struct net_device *dev, struct ifreq *req, int cmd)
{
	star_private *star_prv = netdev_priv(dev);
	unsigned long flags;
	int rc = 0;

	if (!netif_running(dev))
		return -EINVAL;

	spin_lock_irqsave(&star_prv->lock, flags);
	rc = generic_mii_ioctl(&star_prv->mii, if_mii(req), cmd, NULL);
	spin_unlock_irqrestore(&star_prv->lock, flags);

	return rc;
}

static void star_tx_timeout(struct net_device *ndev)
{
	bool state;
	int ret;

	STAR_MSG(STAR_ERR, "%s tx timeout\n", __func__);
	STAR_MSG(STAR_DBG, "request interrupt vector=%d\n", ndev->irq);
	ret = irq_get_irqchip_state(ndev->irq, IRQCHIP_STATE_MASKED, &state);
	STAR_MSG(STAR_DBG, "irq mask status(ret=%d)=0x%x\n", ret, state);
	ret = irq_get_irqchip_state(ndev->irq, IRQCHIP_STATE_PENDING, &state);
	STAR_MSG(STAR_DBG, "irq pending status(ret=%d)=0x%x\n", ret, state);
	ret = irq_get_irqchip_state(ndev->irq, IRQCHIP_STATE_ACTIVE, &state);
	STAR_MSG(STAR_DBG, "irq active status(ret=%d)=0x%x\n", ret, state);
}

static int mdcmdio_read(struct net_device *dev, int phy_id, int location)
{
	star_private *star_prv;
	star_dev *star_dev;

	star_prv = netdev_priv(dev);
	star_dev = &star_prv->star_dev;

	return star_mdc_mdio_read(star_dev, phy_id, location);
}

static void mdcmdio_write(struct net_device *dev, int phy_id,
			  int location, int val)
{
	star_private *star_prv;
	star_dev *star_dev;

	star_prv = netdev_priv(dev);
	star_dev = &star_prv->star_dev;
	star_mdc_mdio_write(star_dev, phy_id, location, val);
}

const struct net_device_ops star_netdev_ops = {
	.ndo_open = star_open,
	.ndo_stop = star_stop,
	.ndo_start_xmit = star_start_xmit,
	.ndo_get_stats = star_get_stats,
	.ndo_set_rx_mode = star_set_multicast_list,
	.ndo_do_ioctl = star_ioctl,
	.ndo_tx_timeout	= star_tx_timeout,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller = star_netpoll,
#endif
	.ndo_change_mtu	= eth_change_mtu,
	.ndo_set_mac_address = eth_mac_addr,
	.ndo_validate_addr = eth_validate_addr,
};

static int starmac_get_settings(struct net_device *ndev,
				struct ethtool_cmd *cmd)
{
	int ret;
	unsigned long flags;
	star_private *star_prv = netdev_priv(ndev);

	spin_lock_irqsave(&star_prv->lock, flags);
	ret = mii_ethtool_gset(&star_prv->mii, cmd);
	spin_unlock_irqrestore(&star_prv->lock, flags);

	return ret;
}

static int starmac_set_settings(struct net_device *ndev,
				struct ethtool_cmd *cmd)
{
	int ret;
	unsigned long flags;
	star_private *star_prv = netdev_priv(ndev);

	spin_lock_irqsave(&star_prv->lock, flags);
	ret = mii_ethtool_sset(&star_prv->mii, cmd);
	spin_unlock_irqrestore(&star_prv->lock, flags);

	return ret;
}

static int starmac_nway_reset(struct net_device *ndev)
{
	int ret;
	unsigned long flags;
	star_private *star_prv = netdev_priv(ndev);

	spin_lock_irqsave(&star_prv->lock, flags);
	ret = mii_nway_restart(&star_prv->mii);
	spin_unlock_irqrestore(&star_prv->lock, flags);

	return ret;
}

static u32 starmac_get_link(struct net_device *ndev)
{
	u32 ret;
	unsigned long flags;
	star_private *star_prv = netdev_priv(ndev);

	spin_lock_irqsave(&star_prv->lock, flags);
	ret = mii_link_ok(&star_prv->mii);
	spin_unlock_irqrestore(&star_prv->lock, flags);
	STAR_MSG(STAR_DBG, "ETHTOOL_TEST is called\n");

	return ret;
}

static int starmac_check_if_running(struct net_device *dev)
{
	if (!netif_running(dev))
		return -EINVAL;

	return 0;
}

static void starmac_get_drvinfo(struct net_device *dev,
				struct ethtool_drvinfo *info)
{
	strlcpy(info->driver, STAR_DRV_NAME, sizeof(info->driver));
	strlcpy(info->version, STAR_DRV_VERSION, sizeof(info->version));
}

static struct ethtool_ops starmac_ethtool_ops = {
	.begin = starmac_check_if_running,
	.get_drvinfo = starmac_get_drvinfo,
	.get_settings = starmac_get_settings,
	.set_settings = starmac_set_settings,
	.nway_reset = starmac_nway_reset,
	.get_link = starmac_get_link,
};

int star_get_wol_flag(star_private *star_prv)
{
	return star_prv->support_wol;
}

void star_set_wol_flag(star_private *star_prv, bool flag)
{
	star_prv->support_wol = flag;
}

static int  star_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct net_device *netdev = platform_get_drvdata(pdev);
	star_private *star_prv = netdev_priv(netdev);
	star_dev *star_dev = &star_prv->star_dev;

	STAR_MSG(STAR_DBG, "entered %s, line(%d)\n", __func__, __LINE__);

	if (star_prv->opened) {
		if (star_prv->wol == WOL_NONE) {
			STAR_MSG(STAR_DBG, "Not support wol.\n");
			star_mac_disable(netdev);
			clk_disable_unprepare(star_prv->axi_dram);
			clk_disable_unprepare(star_prv->apb_reg);
			clk_disable_unprepare(star_prv->ext_125m_clk);
		} else if (star_prv->wol == MAC_WOL) {
			STAR_MSG(STAR_DBG, "support mac wol.\n");
			star_config_wol(star_dev, true);
		} else if (star_prv->wol == PHY_WOL) {
			STAR_MSG(STAR_DBG, "support phy wol.\n");
			star_mac_disable(netdev);
			if (star_dev->phy_ops->wol_enable)
				star_dev->phy_ops->wol_enable(netdev);
			enable_irq_wake(star_prv->eint_irq);
		}
	}

	return 0;
}

static int star_resume(struct platform_device *pdev)
{
	struct net_device *netdev = platform_get_drvdata(pdev);
	star_private *star_prv = netdev_priv(netdev);
	star_dev *star_dev = &star_prv->star_dev;
	int ret;

	STAR_MSG(STAR_DBG, "entered %s(%s)\n", __func__, netdev->name);

	if (star_prv->opened) {
		if (star_prv->wol == WOL_NONE) {
			STAR_MSG(STAR_DBG, "Not support wol.\n");

			ret = clk_prepare_enable(star_prv->axi_dram);
			if (ret < 0)
				STAR_MSG(STAR_ERR, "failed to enable axi_dram (%d)\n", ret);

			ret = clk_prepare_enable(star_prv->apb_reg);
			if (ret < 0)
				STAR_MSG(STAR_ERR, "failed to enable apb_reg (%d)\n", ret);

			ret = clk_prepare_enable(star_prv->ext_125m_clk);
			if (ret < 0)
				STAR_MSG(STAR_ERR, "failed to enable ext_125m_clk (%d)\n", ret);

			star_hw_init(star_dev);
			star_mac_enable(netdev);
		} else if (star_prv->wol == MAC_WOL) {
			STAR_MSG(STAR_DBG, "support mac wol.\n");
			star_config_wol(star_dev, false);
		} else if (star_prv->wol == PHY_WOL) {
			STAR_MSG(STAR_DBG, "support phy wol.\n");
			if (star_dev->phy_ops->wol_disable)
				star_dev->phy_ops->wol_disable(netdev);
			disable_irq_wake(star_prv->eint_irq);
			star_hw_init(star_dev);
			star_mac_enable(netdev);
		}
	}

	return 0;
}

static int star_probe(struct platform_device *pdev)
{
	int ret = 0;
	star_private *star_prv;
	star_dev *star_dev;
	struct net_device *netdev;
	struct device_node *np = pdev->dev.of_node;
	const char *mac_addr;

	star_set_dbg_level(STAR_WARN);
	STAR_MSG(STAR_DBG, "%s entered\n", __func__);

	pm_runtime_enable(&pdev->dev);

	/* Need to enable MTCMOS */
	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0)
		goto clean_runtime_disabled_ret;

	netdev = alloc_etherdev(sizeof(star_private));
	if (!netdev)
		return -ENOMEM;

	pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	star_prv = netdev_priv(netdev);
	memset(star_prv, 0, sizeof(star_private));
	star_prv->dev = netdev;
	/* defalt close eth */
	star_prv->opened = false;

#ifdef ETH_SUPPORT_WOL
	STAR_MSG(STAR_ERR, "%s() support WOL\n", __func__);
	star_prv->support_wol = true;
#endif
	star_dev = &star_prv->star_dev;
	star_dev->dev = &pdev->dev;

	star_prv->axi_dram = devm_clk_get(&pdev->dev, "axi_dram");
	if (IS_ERR(star_prv->axi_dram)) {
		ret = PTR_ERR(star_prv->axi_dram);
		dev_err(&pdev->dev, "failed to get peri_axi_clk: %d\n", ret);
	}

	star_prv->apb_reg = devm_clk_get(&pdev->dev, "apb_reg");
	if (IS_ERR(star_prv->apb_reg)) {
		ret = PTR_ERR(star_prv->apb_reg);
		dev_err(&pdev->dev, "failed to get peri_apb_clk: %d\n", ret);
	}

	star_prv->ext_125m_clk = devm_clk_get(&pdev->dev, "mac_ext");
	if (IS_ERR(star_prv->ext_125m_clk)) {
		ret = PTR_ERR(star_prv->ext_125m_clk);
		dev_err(&pdev->dev, "failed to get ext_125m_clk: %d\n", ret);
	}

	ret = clk_prepare_enable(star_prv->axi_dram);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable axi_dram (%d)\n", ret);
		goto err_free_netdev;
	}

	ret = clk_prepare_enable(star_prv->apb_reg);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable apb_reg (%d)\n", ret);
		goto clean_axi;
	}

	ret = clk_prepare_enable(star_prv->ext_125m_clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable ext_125m_clk (%d)\n", ret);
		goto clean_apb;
	}

	star_dev->base = of_iomap(np, 0);
	if (!star_dev->base) {
		STAR_MSG(STAR_ERR, "fail to ioremap eth!\n");
		ret = -ENOMEM;
		goto clean_125m;
	}
	STAR_MSG(STAR_DBG, "BASE: mac(0x%p)\n", star_dev->base);

#ifdef CONFIG_STAR_USE_RMII_MODE
	star_dev->pericfg_base = of_iomap(np, 1);
	if (!star_dev->pericfg_base) {
		STAR_MSG(STAR_ERR, "fail to ioremap pericfg_base!\n");
		ret = -ENOMEM;
		goto clean_125m;
	}

	STAR_MSG(STAR_DBG, "BASE: clk(0x%p)\n", star_dev->pericfg_base);

	star_switch_to_rmii_mode(star_dev);
#endif

	switch (of_get_phy_mode(np)) {
	case PHY_INTERFACE_MODE_MII:
		star_set_reg(star_dev->base + 0x344, 0x0);
		break;
	case PHY_INTERFACE_MODE_RMII:
		star_set_reg(star_dev->base + 0x344, 0x4);
		break;
	case PHY_INTERFACE_MODE_RGMII:
		star_set_reg(star_dev->base + 0x344, 0x2);
		star_set_bit(star_dev->base + 0x4, 1 << 17);
		star_set_reg(star_dev->base + 0x58, 0x212f);
		break;
	default:
		STAR_MSG(STAR_ERR, "phy interface not support\n");
		break;
	}

	tasklet_init(&star_prv->dsr, star_dsr, (unsigned long)netdev);

    /* Init system locks */
	spin_lock_init(&star_prv->lock);

	star_prv->desc_vir_addr =
		(uintptr_t)dma_alloc_coherent(star_dev->dev,
					      TX_DESC_TOTAL_SIZE +
					      RX_DESC_TOTAL_SIZE,
					      &star_prv->desc_dma_addr,
					      GFP_KERNEL | GFP_DMA);
	if (!star_prv->desc_vir_addr) {
		STAR_MSG(STAR_ERR, "fail to dma_alloc_coherent!!\n");
		ret = -ENOMEM;
		goto alloc_desc_fail;
	}

	star_dev->star_prv = star_prv;

	STAR_MSG(STAR_ERR, "Ethernet disable powerdown!\n");
	star_nic_pdset(star_dev, false);

	star_hw_init(star_dev);

	/* Get PHY ID */
	star_prv->phy_addr = star_detect_phyid(star_dev);
	if (star_prv->phy_addr == 32) {
		STAR_MSG(STAR_ERR, "can't detect phy_addr,default to %d\n",
			 star_prv->phy_addr);
		ret = -ENODEV;
		goto phy_detect_fail;
	} else {
		STAR_MSG(STAR_DBG, "PHY addr = 0x%04x\n", star_prv->phy_addr);
	}

	star_prv->mii.phy_id = star_prv->phy_addr;
	star_prv->mii.dev = netdev;
	star_prv->mii.mdio_read = mdcmdio_read;
	star_prv->mii.mdio_write = mdcmdio_write;
	star_prv->mii.phy_id_mask = 0x1f;
	star_prv->mii.reg_num_mask = 0x1f;

	/* Set MAC address */
	mac_addr = of_get_mac_address(np);
	if (mac_addr)
		ether_addr_copy(netdev->dev_addr, mac_addr);

	STAR_MSG(STAR_DBG, "default netdev->dev_addr(%pM).\n", netdev->dev_addr);
	/* If the mac address is invalid, use random mac address  */
	if (!is_valid_ether_addr(netdev->dev_addr)) {
		random_ether_addr(netdev->dev_addr);
		STAR_MSG(STAR_DBG, "generated random MAC address %pM\n",
			 netdev->dev_addr);
		netdev->addr_assign_type = NET_ADDR_RANDOM;
	}

	netdev->irq = platform_get_irq(pdev, 0);
	if (netdev->irq < 0) {
		STAR_MSG(STAR_ERR, "no IRQ resource found\n");
		goto phy_detect_fail;
	}
	STAR_MSG(STAR_ERR, "eth irq (%d)\n", netdev->irq);

#ifdef CONFIG_STAR_USE_RMII_MODE
	star_prv->eint_pin = of_get_named_gpio(np, "eth-gpios", 0);
	if (star_prv->eint_pin < 0)
		STAR_MSG(STAR_DBG, "not find eth-gpio\n");
	star_prv->eint_irq = gpio_to_irq(star_prv->eint_pin);
#endif
	star_prv->wol = WOL_NONE;
	star_prv->wol_flag = false;

	netdev->base_addr = (unsigned long)star_dev->base;
	netdev->netdev_ops = &star_netdev_ops;

	STAR_MSG(STAR_DBG, "EthTool installed\n");
	netdev->ethtool_ops = &starmac_ethtool_ops;

	netif_napi_add(netdev, &star_prv->napi, star_poll, STAR_NAPI_WEIGHT);

	ret = register_netdev(netdev);
	if (ret)
		goto phy_detect_fail;

	platform_set_drvdata(pdev, netdev);

	ret = star_init_procfs();
	if (ret)
		STAR_MSG(STAR_WARN, "star_init_procfs fail\n");

	STAR_MSG(STAR_DBG, "star_probe success.\n");

	return 0;

phy_detect_fail:
	dma_free_coherent(star_dev->dev,
			  TX_DESC_TOTAL_SIZE + RX_DESC_TOTAL_SIZE,
			  (void *)star_prv->desc_vir_addr,
			  star_prv->desc_dma_addr);

alloc_desc_fail:
	free_netdev(netdev);

clean_125m:
	clk_disable_unprepare(star_prv->ext_125m_clk);

clean_apb:
	clk_disable_unprepare(star_prv->apb_reg);

clean_axi:
	clk_disable_unprepare(star_prv->axi_dram);

err_free_netdev:
	unregister_netdev(netdev);
	STAR_MSG(STAR_ERR, "Star MAC init fail\n");

clean_runtime_disabled_ret:
	pm_runtime_disable(&pdev->dev);
	return ret;
}

static int star_remove(struct platform_device *pdev)
{
	struct net_device *netdev = platform_get_drvdata(pdev);
	star_private *star_prv = netdev_priv(netdev);
	star_dev *star_dev = &star_prv->star_dev;

	star_exit_procfs();

	unregister_netdev(netdev);

	dma_free_coherent(star_dev->dev,
			  TX_DESC_TOTAL_SIZE + RX_DESC_TOTAL_SIZE,
			  (void *)star_prv->desc_vir_addr,
			  star_prv->desc_dma_addr);

	free_netdev(netdev);

	return 0;
}

static const struct of_device_id star_of_match[] = {
	{ .compatible = "mediatek,mt8695-ethernet", },
	{},
};

static struct platform_device *star_pdev;

static struct platform_driver star_pdrv = {
	.driver = {
		.name = STAR_DRV_NAME,
		.owner = THIS_MODULE,
		.of_match_table = star_of_match,
	},
	.probe = star_probe,
	.suspend = star_suspend,
	.resume = star_resume,
	.remove = star_remove,
};

static int __init star_init(void)
{
	int err;

	STAR_MSG(STAR_DBG, "enter %s\n", __func__);

	err = platform_driver_register(&star_pdrv);
	if (err)
		return err;

	STAR_MSG(STAR_DBG, "%s success.\n", __func__);
	return 0;
}

static void __exit star_exit(void)
{
	platform_device_unregister(star_pdev);
	platform_driver_unregister(&star_pdrv);
	STAR_MSG(STAR_DBG, "%s ...\n", __func__);
}

module_init(star_init);
module_exit(star_exit);

MODULE_AUTHOR("Leilk Liu <leilk.liu@mediatek.com>");
MODULE_DESCRIPTION("Mediatek STAR Network Driver");
MODULE_LICENSE("GPL");

