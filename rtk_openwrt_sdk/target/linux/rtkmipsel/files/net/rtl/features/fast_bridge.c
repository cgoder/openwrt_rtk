/*
* Copyright c                  Realtek Semiconductor Corporation, 2010 
* All rights reserved.
* 
* Program : fast path for bridge(l2 switch)
*/
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0)
#include <linux/config.h>
#include <linux/autoconf.h>
#endif
#include <linux/module.h>
#include <linux/kernel.h>
#include <net/rtl/rtl_types.h>
#include <linux/netlink.h>
#include <linux/list.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <net/rtl/features/fast_bridge.h>
//#include <bsp/bspchip.h>

#if 0
/*******************************************************/
/* MUST keep exactly the same as user/rtk_cmd/rtk_cmd.h */
#define	NL_DATA_SEND_MAX_LEN	64
struct nl_data_info_kernel
{
	int		len;
	char		data[NL_DATA_SEND_MAX_LEN];
};
/*******************************************************/
#endif
__DRAM_FWD	rtl_fb_para		fb_paras;
__DRAM_FWD	rtl_fb_head		fb_head;
static struct sock *nl_sk;

static inline int rtl_fb_hash(const uint8 *mac);
static inline rtl_fb_entry* rtl_fb_entry_get(const uint8 *mac);
static void rtl_fb_entry_put(rtl_fb_entry *entry);
__MIPS16 __IRAM_FWD  static rtl_fb_entry* rtl_fb_entry_find(const uint8 *mac);
static inline void rtl_fb_entry_init(rtl_fb_entry *entry);
static inline rtl_fb_entry*	rtl_fb_alloc_entry(void);
static inline void	rtl_fb_alloc_free(rtl_fb_entry* entry);

static inline void rtl_fb_protect_on(unsigned long flags)
{
	local_irq_save(flags);
}

static inline void rtl_fb_protect_off(unsigned long flags)
{
	local_irq_restore(flags);
}

static inline int rtl_fb_hash(const uint8 *mac)
{
	return (mac[3]^mac[5]) & (RTL_FB_HASH_SIZE - 1);
}

static inline void rtl_fb_update_entry(rtl_fb_entry *entry, struct sk_buff *pskb, struct net_device *dev)
{
	if (entry->dev_matchKey != (void*)dev) {
		entry->dev_matchKey = (void*)dev;
		#if !defined(CONFIG_DEFAULTS_KERNEL_2_6) || defined(CONFIG_COMPAT_NET_DEV_OPS)
		entry->ndo_start_xmit = dev->hard_start_xmit;
		#else
		entry->ndo_start_xmit = dev->netdev_ops->ndo_start_xmit;
		#endif
	}
	entry->last_used = jiffies;
}

__IRAM_FWD int32 rtl_fb_process_in_nic(struct sk_buff *pskb, struct net_device *dev)
{
	rtl_fb_entry	*entry;
	unsigned long	flags;

	/* check source mac */
	if (fb_paras.enable_fb_fwd!=TRUE)
		return RTL_FB_RETURN_FAILED;

	rtl_fb_protect_on(flags);	
	entry = rtl_fb_entry_find(&pskb->data[ETHER_ADDR_LEN]);
	if ((entry==NULL)) {
		/* src mac learn */
		entry = rtl_fb_entry_get(&pskb->data[ETHER_ADDR_LEN]);
		if (entry) {
			rtl_fb_update_entry(entry, pskb, dev);
		}
	} else {
		/* update info */
		rtl_fb_update_entry(entry, pskb, dev);
	}

	/* get dstination mac */
	entry = rtl_fb_entry_find(pskb->data);


	if (entry&&(entry->dev_matchKey!=(void*)dev)) {
		pskb->dev = (struct net_device*)(entry->dev_matchKey);
		entry->ndo_start_xmit(pskb, pskb->dev);

		rtl_fb_protect_off(flags);
		return RTL_FB_RETURN_SUCCESS;
	} else {
		rtl_fb_protect_off(flags);
		return RTL_FB_RETURN_FAILED;
	}
}

static inline rtl_fb_entry* rtl_fb_entry_get(const uint8 *mac)
{
	int	hidx;
	rtl_fb_entry	*entry;

	if (!hlist_empty(&fb_head.free_list))	{
		hidx = rtl_fb_hash(mac);
		entry = (rtl_fb_entry*)fb_head.free_list.first;
		memcpy(entry->mac_addr, mac, ETHER_ADDR_LEN);
		hlist_del(&entry->hlist);
		hlist_add_head(&entry->hlist, &fb_head.in_used_list[hidx]);
		fb_head.used_cnt++;
	} else {
		entry==NULL;
	}

	return entry;
}

static void rtl_fb_entry_put(rtl_fb_entry *entry)
{
	unsigned long	flags;
	
	rtl_fb_protect_on(flags);
	hlist_del_init(&entry->hlist);
	hlist_add_head(&entry->hlist, &fb_head.free_list);
	entry->dev_matchKey = NULL;
	entry->ndo_start_xmit = NULL;
	entry->last_used = 0;
	memset(entry->mac_addr, 0, ETHER_ADDR_LEN);
	fb_head.used_cnt--;
	rtl_fb_protect_off(flags);
}

__MIPS16 __IRAM_FWD static rtl_fb_entry* rtl_fb_entry_find(const uint8 *mac)
{
	int				hidx;
	rtl_fb_entry		*entry;
    #if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
	struct hlist_node	*pos;
	#endif

	if (fb_head.used_cnt==0)
		return NULL;

	hidx = rtl_fb_hash(mac);
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	hlist_for_each_entry_rcu(entry, &fb_head.in_used_list[hidx], hlist) 
	#else
	hlist_for_each_entry_rcu(entry, pos, &fb_head.in_used_list[hidx], hlist) 
	#endif
	{
		if (!compare_ether_addr(entry->mac_addr, mac)) {
			entry->last_used = jiffies;
			return entry;
		}
	}

	return NULL;
}

unsigned long rtl_fb_get_entry_lastused(const uint8 *mac)
{
	int				hidx;
	rtl_fb_entry		*entry;
    #if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
	struct hlist_node	*pos;
	#endif

	if (fb_head.used_cnt==0)
		return 0;

	hidx = rtl_fb_hash(mac);
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	hlist_for_each_entry_rcu(entry, &fb_head.in_used_list[hidx], hlist) 
	#else
	hlist_for_each_entry_rcu(entry, pos, &fb_head.in_used_list[hidx], hlist) 
	#endif
	{
		if (!compare_ether_addr(entry->mac_addr, mac)) {
			return entry->last_used;
		}
	}

	return 0;
}

void rtl_fb_del_entry(const uint8 *mac)
{
	rtl_fb_entry		*entry;

	entry = rtl_fb_entry_find(mac);
	if (entry)
		rtl_fb_entry_put(entry);
}

void rtl_fb_flush(void)
{
	int	i;
	struct hlist_node *entry;

	if (fb_head.used_cnt==0)
		return;

	for (i=0;i<RTL_FB_HASH_SIZE;i++) {
		while(!hlist_empty(&fb_head.in_used_list[i])) {
			entry = fb_head.in_used_list[i].first;
			rtl_fb_entry_put((rtl_fb_entry*)entry);
		}
		if (fb_head.used_cnt==0)
			break;
	}
}

void rtl_fb_flush_by_dev(void* dev_key)
{
	int	i;
	struct hlist_node *pos;
	rtl_fb_entry *entry;

	if (fb_head.used_cnt==0)
		return;

	for (i=0;i<RTL_FB_HASH_SIZE;i++) {
		hlist_for_each(pos, &fb_head.in_used_list[i]) {
			entry = (rtl_fb_entry*)pos;
			if (entry->dev_matchKey==dev_key) {
				rtl_fb_entry_put(entry);
			}
		}
		if (fb_head.used_cnt==0)
			break;
	}
}

static inline void rtl_fb_entry_init(rtl_fb_entry *entry)
{
	INIT_HLIST_NODE(&entry->hlist);
	entry->dev_matchKey = NULL;
	entry->ndo_start_xmit = NULL;
	entry->last_used = 0;
	memset(entry->mac_addr, 0, ETHER_ADDR_LEN);
}

static inline rtl_fb_entry*	rtl_fb_alloc_entry(void)
{
	rtl_fb_entry*		entry;

	entry = (rtl_fb_entry*)kmalloc(sizeof(rtl_fb_entry), GFP_KERNEL);

	if (entry!=NULL) {
		rtl_fb_entry_init(entry);
	}

	return entry;
}

static inline void	rtl_fb_alloc_free(rtl_fb_entry* entry)
{
	kfree(entry);
}

static void rtl_fb_copy_to_user(rtl_fb_nl_entry *data, int cnt)
{
	int	i, len;
	struct hlist_node 		*pos;
	rtl_fb_entry			*entry;

	if (fb_head.used_cnt==0)
		return;

	len = 0;
	for (i=0;i<RTL_FB_HASH_SIZE;i++) {
		hlist_for_each(pos, &fb_head.in_used_list[i]) {
			entry = (rtl_fb_entry*)pos;
			copy_to_user((void*)data->mac_addr, (void*)entry->mac_addr, ETHER_ADDR_LEN);
			copy_to_user((void*)data->name, (void*)(((struct net_device*)(entry->dev_matchKey))->name), IFNAMSIZ);
			data->last_used = (jiffies-entry->last_used)/HZ;
			data++;
			len++;
			
			if (len==cnt)
				return;
		}
	}
}

static void rtl_fb_netlink_receive (struct sk_buff *puskb)
{
	int		pid, i;
	rtl_fb_entry*		entry;
	fb_cmd_info_s		fb_info;
	fb_cmd_info_s		tx_info;


	pid = rtk_nlrecvmsg(puskb, sizeof(fb_cmd_info_s), &fb_info);	

//	printk("len[%d] rx[0x%p] action[%d]\n", fb_info.len, fb_info, fb_info?fb_info.action:-99);

	switch (fb_info.action)
	{
		case 	FB_CMD_SET_FWD:
		{
			tx_info.action = FB_CMD_SET_FWD;
			fb_paras.enable_fb_fwd = fb_info.info.data.enable_fb_fwd;
			rtl_fb_flush();
			break;
		}
		case 	FB_CMD_SET_FILTER:
		{
			tx_info.action = FB_CMD_SET_FILTER;
			fb_paras.enable_fb_filter = fb_info.info.data.enable_fb_filter;
			break;
		}
		case 	FB_CMD_SET_ENTRY_NUM:
		{
			tx_info.action = FB_CMD_SET_ENTRY_NUM;
			
			if ( fb_head.used_cnt>fb_info.info.data.entry_num ) {
				for (i=fb_info.info.data.entry_num;i<fb_head.used_cnt;i++) {
					entry = (rtl_fb_entry*)fb_head.free_list.first;
					hlist_del(&entry->hlist);
					rtl_fb_alloc_free(entry);
				}
				fb_info.info.data.entry_num = fb_head.used_cnt;
			} else if (fb_info.info.data.entry_num>fb_paras.entry_num) {
				for(i=fb_paras.entry_num;i<fb_info.info.data.entry_num;i++) {
					entry = rtl_fb_alloc_entry();
					if (entry==NULL) {
						fb_info.info.data.entry_num = i;
						break;
					}
					hlist_add_head(&entry->hlist, &fb_head.free_list);
				}
			}

			fb_paras.entry_num = fb_info.info.data.entry_num;
			tx_info.info.data.entry_num = fb_info.info.data.entry_num;
			break;
		}
		case	FB_CMD_GET_STATUS:
		{
			tx_info.action = FB_CMD_GET_STATUS;

			tx_info.info.data.enable_fb_filter = fb_paras.enable_fb_filter;
			tx_info.info.data.enable_fb_fwd = fb_paras.enable_fb_fwd;
			tx_info.info.data.entry_num = fb_paras.entry_num;
			tx_info.info.in_used = fb_head.used_cnt;
			break;
		}
		case	FB_CMD_GET_USED_NUM:
		{
			tx_info.action = FB_CMD_GET_USED_NUM;
			tx_info.info.in_used= fb_head.used_cnt;
			break;
		}
		case	FB_CMD_DUMP_ENTRYS:
		{
			tx_info.action = FB_CMD_DUMP_ENTRYS;
			rtl_fb_copy_to_user((rtl_fb_nl_entry*)fb_info.info.entry, fb_info.info.in_used);
			tx_info.info.entry = fb_info.info.entry;
			tx_info.info.in_used = fb_info.info.in_used;
			break;
		}
		default:		break;
	}

      	rtk_nlsendmsg(pid, nl_sk, sizeof(fb_cmd_info_s), &tx_info);
  	return;
}

static inline int rtl_fb_netlink_init(void) {
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	struct netlink_kernel_cfg cfg = {
		.groups		= 0,
		.input		= rtl_fb_netlink_receive,
		.cb_mutex	= NULL,
	};
	 nl_sk = netlink_kernel_create(&init_net, NETLINK_RTK_FB, &cfg);
	 #else
  	 nl_sk = netlink_kernel_create(&init_net, NETLINK_RTK_FB, 0, rtl_fb_netlink_receive, NULL, THIS_MODULE);
	#endif
	
  	if (!nl_sk) {
    		printk(KERN_ERR "RTK fast bridge can NOT create netlink socket.\n");
  	}
  	return 0;
}

static int __init rtl_fb_init(void)
{
	int		i;
	rtl_fb_entry*	entry;
	
	/* set default value */
	fb_paras.entry_num = RTL_FB_ENTRY_NUM;
	fb_paras.enable_fb_filter = FALSE;
	fb_paras.enable_fb_fwd = TRUE;

	/* init head */
	fb_head.used_cnt = 0;
	for (i=0;i<RTL_FB_HASH_SIZE;i++)
		INIT_HLIST_HEAD(&fb_head.in_used_list[i]);
	INIT_HLIST_HEAD(&fb_head.free_list);
	for(i=0;i<RTL_FB_ENTRY_NUM;i++) {
		entry = rtl_fb_alloc_entry();
		if (entry==NULL) {
			fb_paras.entry_num = i;
			break;
		}
		hlist_add_head(&entry->hlist, &fb_head.free_list);
	}

	/* init netlink */
	rtl_fb_netlink_init();
	
	return SUCCESS;
}

static void __exit rtl_fb_exit(void)
{
	struct hlist_node *pos;

	/* set default value */
	fb_paras.entry_num = 0;
	fb_paras.enable_fb_filter = FALSE;
	fb_paras.enable_fb_fwd = TRUE;

	rtl_fb_flush();
	
 	hlist_for_each(pos, &fb_head.free_list) {
		rtl_fb_alloc_free((rtl_fb_entry*)pos);
	}
}

module_init(rtl_fb_init);
module_exit(rtl_fb_exit);
