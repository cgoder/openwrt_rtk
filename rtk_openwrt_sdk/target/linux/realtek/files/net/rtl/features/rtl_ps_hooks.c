#include <linux/types.h>
#include <linux/netfilter.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/moduleparam.h>
#include <linux/notifier.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/inetdevice.h>

#include <net/ip_fib.h>
#include <net/netfilter/nf_nat.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
#include <net/netfilter/nf_nat.h>
#else
#include <net/netfilter/nf_nat_protocol.h>
#endif

#include <net/ip_vs.h>
#include <linux/ip_vs.h>

#if defined (CONFIG_BRIDGE) || defined (CONFIG_RTL_IGMP_SNOOPING)
#include <bridge/br_private.h>
#endif

#include <net/rtl/rtl_types.h>
#include <net/rtl/fastpath/fastpath_core.h>
#include <net/rtl/features/rtl_features.h>
#include <net/rtl/features/rtl_ps_hooks.h>

#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
#include <net/rtl/rtl865x_ppp.h>
#include <net/rtl/rtl865x_route_api.h>
#include <net/rtl/rtl865x_arp_api.h>
#endif

#if defined(CONFIG_IPV6) && defined(CONFIG_RTL_8198C)
#include <net/rtl/rtl8198c_route_ipv6_api.h>
#include <net/rtl/rtl8198c_arp_ipv6_api.h>
#include <net/ip6_fib.h>
#endif

#ifdef CONFIG_RTL_LAYERED_DRIVER_L2
#include <net/rtl/rtl865x_fdb_api.h>
#endif

#if defined(CONFIG_RTL_HW_QOS_SUPPORT) && defined(CONFIG_RTL_HARDWARE_NAT)
#include <net/rtl/rtl865x_netif.h>
#include <net/rtl/rtl865x_outputQueue.h>
#endif

#if defined (CONFIG_RTL865X_LANPORT_RESTRICTION)
#include <net/rtl/features/lan_restrict.h>
#endif

#ifdef CONFIG_RTL_HARDWARE_NAT
//#define CONFIG_HARDWARE_NAT_DEBUG
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
#include <net/rtl/rtl865x_ppp.h>
#include <net/rtl/rtl865x_route_api.h>
#endif
//unsigned int ldst, lmask, wdst, wmask;
extern int gHwNatEnabled;
#endif
#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
#include <linux/ppp_channel.h>
#endif

#ifdef CONFIG_RTL_HARDWARE_NAT
/*2007-12-19*/
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
#include <net/rtl/rtl865x_ip_api.h>
#endif
#ifdef CONFIG_RTL_LAYERED_DRIVER_L4
#include <net/rtl/rtl865x_nat.h>
#endif
extern char masq_if[];
extern unsigned int hw_napt_ip;
#endif

#if defined  (CONFIG_RTL_QOS_SYNC_SUPPORT)
#include <linux/types.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <net/net_namespace.h>
#include <net/sock.h>
#include <net/netlink.h>
//#include <net/pkt_sched.h>
#include <net/act_api.h>
#include <net/rtl/rtl865x_netif.h>
#include <net/rtl/rtl865x_outputQueue.h>
#include <net/rtl/features/rtl_sched_hooks.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#endif
#if defined (CONFIG_RTL_HW_QOS_SUPPORT)
int rtl_qos_initHook(void);
int rtl_qos_cleanupHook(void);

#endif

#if defined(CONFIG_RTL_IGMP_SNOOPING) || defined(CONFIG_RTL_HARDWARE_NAT)
#include <net/rtl/rtl_nic.h>
#endif
#if defined (CONFIG_RTL_IGMP_SNOOPING)
/*include*/
#include <net/rtl/rtl865x_igmpsnooping.h>
#include <linux/igmp.h>
#include <net/rtl/features/rtl_igmp_ps_hook.h>
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
#include <net/rtl/rtl865x_multicast.h>
#endif
#if defined (CONFIG_RTL_MLD_SNOOPING)
#include <net/mld.h>
#endif
#endif

/*global*/
#if defined (CONFIG_RTL_IGMP_SNOOPING)
int  igmpsnoopenabled = 1;
extern uint32 nicIgmpModuleIndex;

struct net_bridge *bridge0=NULL;
unsigned int br0SwFwdPortMask=0xFFFFFFFF;
unsigned int brIgmpModuleIndex=0xFFFFFFFF;
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
struct net_bridge *bridge1=NULL;
unsigned int brIgmpModuleIndex_2=0xFFFFFFFF;
unsigned int br1SwFwdPortMask=0xFFFFFFFF;
#endif
#if defined (CONFIG_RTL_MLD_SNOOPING)
extern int mldSnoopEnabled;
#endif

#if defined (CONFIG_RTL_HW_MCAST_WIFI)
int hwwifiEnable = 0;
#endif

#if defined (CONFIG_SWCONFIG)
extern int swconfig_vlan_enable;
#endif


#if defined(CONFIG_PROC_FS)
#if defined(CONFIG_RTL_PROC_NEW)
extern struct proc_dir_entry proc_root;
#else
struct proc_dir_entry *procIgmpSnoop=NULL;
struct proc_dir_entry *procIgmpDb=NULL;
#if defined (CONFIG_RTL_QUERIER_SELECTION)
struct proc_dir_entry *procIgmpQuery=NULL;
#endif
struct proc_dir_entry *procIgmpProxy = NULL;
struct proc_dir_entry *procMCastFastFwd=NULL;
#if defined (CONFIG_RTL_MLD_SNOOPING)
struct proc_dir_entry *procMldVersion=NULL;
#endif
#endif
#endif

#if defined (CONFIG_RTL_QUERIER_SELECTION)
struct querierInfo querierInfoList[MAX_QUERIER_RECORD];
#endif
int IGMPProxyOpened = 0;
int IGMPPRoxyFastLeave = 1;
static unsigned int mCastQueryTimerCnt=0;
int igmpQueryEnabled=1;
int igmpVersion=2;
#if defined(CONFIG_RTL_MLD_SNOOPING)
int mldQueryEnabled=1;	
int mldVersion=1;
#endif

int ipMulticastFastFwd=1;
int needCheckMfc=1;

unsigned int maxUnknownMcastPPS=1500;
unsigned int chkUnknownMcastEnable=1;
struct rtl865x_unKnownMCastRecord unKnownMCastRecord[MAX_UNKNOWN_MULTICAST_NUM];

extern struct rtl865x_ReservedMCastRecord reservedMCastRecord[MAX_RESERVED_MULTICAST_NUM];

/*igmpv3 general query*/
static unsigned char igmpV3QueryBuf[64]={	0x01,0x00,0x5e,0x00,0x00,0x01,		/*destination mac*/
									0x00,0x00,0x00,0x00,0x00,0x00,		/*offset:6*/
									0x08,0x00,						/*offset:12*/
									0x46,0x00,0x00,0x24,				/*offset:14*/
									0x00,0x00,0x40,0x00,				/*offset:18*/
									0x01,0x02,0x00,0x00,				/*offset:22*/
									0x00,0x00,0x00,0x00,				/*offset:26,source ip*/
									0xe0,0x00,0x00,0x01,				/*offset:30,destination ip*/
									0x94,0x04,0x00,0x00,				/*offset:34,router alert option*/
									0x11,0x01,0x00,0x00,				/*offset:38*/
									0x00,0x00,0x00,0x00,				/*offset:42,queried multicast ip address*/
									0x0a,0x3c,0x00,0x00,				/*offset:46*/
									0x00,0x00,0x00,0x00,				/*offset:50*/
									0x00,0x00,0x00,0x00,				/*offset:54*/
									0x00,0x00,0x00,0x00,				/*offset:58*/
									0x00,0x00							/*offset:62*/
									
								};			

/*igmpv2 general query*/
static unsigned char igmpV2QueryBuf[64]={	0x01,0x00,0x5e,0x00,0x00,0x01,		/*destination mac*/
									0x00,0x00,0x00,0x00,0x00,0x00,		/*offset:6*/
									0x08,0x00,						/*offset:12*/
									0x45,0x00,0x00,0x1c,				/*offset:14*/
									0x00,0x00,0x40,0x00,				/*offset:18*/
									0x01,0x02,0x00,0x00,				/*offset:22*/
									0x00,0x00,0x00,0x00,				/*offset:26*/
									0xe0,0x00,0x00,0x01,				/*offset:30*/
									0x11,0x01,0x0c,0xfa,				/*offset:34*/
									0x00,0x00,0x00,0x00,				/*offset:38*/
									0x00,0x00,0x00,0x00,				/*offset:42*/
									0x00,0x00,0x00,0x00,				/*offset:46*/
									0x00,0x00,0x00,0x00,				/*offset:50*/
									0x00,0x00,0x00,0x00,				/*offset:54*/
									0x00,0x00,0x00,0x00,				/*offset:58*/
									0x00,0x00							/*offset:62*/
									
								};			

#if defined(CONFIG_RTL_MLD_SNOOPING)
static unsigned char mldQueryBuf[90]={	0x33,0x33,0x00,0x00,0x00,0x01,		/*destination mac*/
									0x00,0x00,0x00,0x00,0x00,0x00,		/*source mac*/	/*offset:6*/
									0x86,0xdd,						/*ether type*/	/*offset:12*/
									0x60,0x00,0x00,0x00,				/*version(1 byte)-traffic cliass(1 byte)- flow label(2 bytes)*/	/*offset:14*/
									0x00,0x20,0x00,0x01,				/*payload length(2 bytes)-next header(1 byte)-hop limit(value:1 1byte)*//*offset:18*/
									0xfe,0x80,0x00,0x00,				/*source address*/	/*offset:22*/
									0x00,0x00,0x00,0x00,				/*be zero*/	/*offset:26*/
									0x00,0x00,0x00,					/*upper 3 bytes mac address |0x02*/ /*offset:30*/
									0xff,0xfe,						/*fixed*/
									0x00,0x00,0x00,					/*lowert 3 bytes mac address*/	 /*offset:35*/
									0xff,0x02,0x00,0x00,				/*destination address is fixed as FF02::1*/	/*offset:38*/
									0x00,0x00,0x00,0x00,			
									0x00,0x00,0x00,0x00,			
									0x00,0x00,0x00,0x01,			
									0x3a,0x00,						/*icmp type(1 byte)-length(1 byte)*/	 /*offset:54*/
									0x05,0x02,0x00,0x00,				/*router alert option*/
									0x01,0x00,						/*padN*/
									0x82,0x00,						/*type(query:0x82)-code(0)*/	/*offset:62*/
									0x00,0x00,						/*checksum*/	/*offset:64*/
									0x00,0x0a,						/*maximum reponse code*/
									0x00,0x00,						/*reserved*/
									0x00,0x00,0x00,0x00,				/*multicast address,fixed as 0*/
									0x00,0x00,0x00,0x00,			
									0x00,0x00,0x00,0x00,			
									0x00,0x00,0x00,0x00,
									0x0a,0x3c,0x00,0x00
								};	

static unsigned char ipv6PseudoHdrBuf[40]=	{	
									0xfe,0x80,0x00,0x00,				/*source address*/
									0x00,0x00,0x00,0x00,			
									0x00,0x00,0x00,0xff,			
									0xfe,0x00,0x00,0x00,			 	
									0xff,0x02,0x00,0x00,				/*destination address*/
									0x00,0x00,0x00,0x00,		
									0x00,0x00,0x00,0x00,			
									0x00,0x00,0x00,0x01,				
									0x00,0x00,0x00,0x18,				/*upper layer packet length*/
									0x00,0x00,0x00,0x3a					/*zero padding(3 bytes)-next header(1 byte)*/
									};		

#endif
#endif


#if defined(CONFIG_RTL_SPEED_MONITOR)
#include <net/rtl/features/rtl_dev_stats.h>
void (*build_con_dev_stats_hook)(struct nf_conn *ct, struct sk_buff *skb);
void (*dec_con_dev_ref_hook)(struct nf_conn *ct);
void (*update_dev_stats_hook)(struct nf_conn *ct,struct sk_buff *skb,enum packet_dir packet_dir_t);
EXPORT_SYMBOL(build_con_dev_stats_hook);
EXPORT_SYMBOL(dec_con_dev_ref_hook);
EXPORT_SYMBOL(update_dev_stats_hook);
EXPORT_SYMBOL(rtl_build_con_dev_stats_hook);
EXPORT_SYMBOL(rtl_dec_con_dev_ref_hook);
EXPORT_SYMBOL(rtl_update_dev_stats_hook);
void rtl_build_con_dev_stats_hook(struct nf_conn *ct, struct sk_buff *skb)
{
    if(build_con_dev_stats_hook)
        build_con_dev_stats_hook(ct,skb);
    else
        return;
}
void rtl_dec_con_dev_ref_hook(struct nf_conn *ct)
{
    if(dec_con_dev_ref_hook)
        dec_con_dev_ref_hook(ct);
    else
        return;
}
void rtl_update_dev_stats_hook(struct nf_conn *ct,struct sk_buff *skb,enum packet_dir packet_dir_t)
{
    if(update_dev_stats_hook)
        update_dev_stats_hook(ct,skb,packet_dir_t);
    else
        return;
}
#endif

#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) && defined(CONFIG_FAST_PATH_MODULE)
enum LR_RESULT (*FastPath_hook5)( ipaddr_t ip, ether_addr_t* mac, enum ARP_FLAGS flags )=NULL;
enum LR_RESULT (*FastPath_hook7)( ipaddr_t ip )=NULL;
enum LR_RESULT (*FastPath_hook8)( ipaddr_t ip, ether_addr_t* mac, enum ARP_FLAGS flags )=NULL;
EXPORT_SYMBOL(FastPath_hook8);
EXPORT_SYMBOL(FastPath_hook7);
EXPORT_SYMBOL(FastPath_hook5);
#endif
#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
int fast_nat_fw = 0;
int fast_l2tp_fw = 0;
int fast_pptp_fw = 0;
int fast_pppoe_fw = 0;
int fast_gre_fw = 0;
uint32 state;
EXPORT_SYMBOL(fast_pptp_fw);
EXPORT_SYMBOL(fast_l2tp_fw);
EXPORT_SYMBOL(fast_nat_fw);
EXPORT_SYMBOL(fast_pppoe_fw);
EXPORT_SYMBOL(state);

void (*event_ppp_dev_down_fphook)(const char *name) = NULL;
void (*set_l2tp_device_fphook)(char *ppp_device) = NULL;
void (*set_pptp_device_fphook)(char *ppp_device) = NULL;
unsigned long (*get_fast_l2tp_lastxmit_fphook)(void) = NULL;
unsigned long (*get_fastpptp_lastxmit_fphook)(void) = NULL;
int (*is_l2tp_device_fphook)(char *ppp_device) = NULL;	// sync from voip customer for multiple ppp
int (*check_for_fast_l2tp_to_wan_fphook)(void *skb) = NULL;
int (*fast_l2tp_to_wan_fphook)(void *skb) = NULL;
int (*rtl_fpTimer_update_fphook)(void *ct) = NULL;
int32 (*rtl_br_fdb_time_update_fphook)(void *br_dummy, void *fdb_dummy, const unsigned char *addr) = NULL;
int32 (*rtl_fp_dev_hard_start_xmit_check_fphook)(struct sk_buff *skb, struct net_device *dev, struct netdev_queue *txq) = NULL;
int32 (*rtl_fp_dev_queue_xmit_check_fphook)(struct sk_buff *skb, struct net_device *dev) = NULL;

void (*ppp_channel_pppoe_fphook)(struct ppp_channel *chan) = NULL;
int (*clear_pppoe_info_fphook)(char *ppp_dev, char *wan_dev, unsigned short sid,
								unsigned int our_ip,unsigned int	peer_ip,
								unsigned char * our_mac, unsigned char *peer_mac) = NULL;
int (*set_pppoe_info_fphook)(char *ppp_dev, char *wan_dev, unsigned short sid,
							unsigned int our_ip,unsigned int	peer_ip,
							unsigned char * our_mac, unsigned char *peer_mac) = NULL;
unsigned long (*get_pppoe_last_rx_tx_fphook)(char * ppp_dev,char * wan_dev,unsigned short sid,
									unsigned int our_ip,unsigned int peer_ip,
									unsigned char * our_mac,unsigned char * peer_mac,
									unsigned long * last_rx,unsigned long * last_tx) = NULL;

EXPORT_SYMBOL(event_ppp_dev_down_fphook);
EXPORT_SYMBOL(set_l2tp_device_fphook);
EXPORT_SYMBOL(set_pptp_device_fphook);
EXPORT_SYMBOL(get_fast_l2tp_lastxmit_fphook);
EXPORT_SYMBOL(get_fastpptp_lastxmit_fphook);
EXPORT_SYMBOL(is_l2tp_device_fphook);
EXPORT_SYMBOL(check_for_fast_l2tp_to_wan_fphook);
EXPORT_SYMBOL(fast_l2tp_to_wan_fphook);
EXPORT_SYMBOL(rtl_fpTimer_update_fphook);
EXPORT_SYMBOL(rtl_br_fdb_time_update_fphook);
EXPORT_SYMBOL(rtl_fp_dev_hard_start_xmit_check_fphook);
EXPORT_SYMBOL(rtl_fp_dev_queue_xmit_check_fphook);
EXPORT_SYMBOL(ppp_channel_pppoe_fphook);
EXPORT_SYMBOL(clear_pppoe_info_fphook);
EXPORT_SYMBOL(set_pppoe_info_fphook);
EXPORT_SYMBOL(get_pppoe_last_rx_tx_fphook);

EXPORT_SYMBOL(__br_fdb_get);
#endif
DEFINE_SPINLOCK(nf_conntrack_lock);
EXPORT_SYMBOL(nf_conntrack_lock);
EXPORT_SYMBOL(proc_root);

int32 rtl_nf_conntrack_in_hooks(rtl_nf_conntrack_inso_s *info)
{
#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	#if !defined(IMPROVE_QOS)
			rtl_fpAddConnCache(info->ct, info->skb);
	#elif defined(CONFIG_RTL_ROUTER_FAST_PATH)
			if(routerTypeFlag == 1)
				rtl_fpAddConnCache(info->ct, info->skb);
	#endif
#endif
#ifdef CONFIG_RTL_FAST_IPV6
	if(fast_ipv6_fw)
		rtl_AddV6ConnCache(info->ct,info->skb);
#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nf_conntrack_in_hooks);

int32 rtl_nf_conntrack_death_by_timeout_hooks(rtl_nf_conntrack_inso_s *info)
{
	int	ret;

	ret = RTL_PS_HOOKS_CONTINUE;
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
	if (rtl_connCache_timer_update(info->ct)==SUCCESS) {
		ret = RTL_PS_HOOKS_RETURN;
	}
	#endif

	#ifdef CONFIG_RTL_FAST_IPV6
	if(fast_ipv6_fw && rtl_V6_connCache_timer_update(info->ct) ==SUCCESS)
	{
		ret = RTL_PS_HOOKS_RETURN;
	}
	#endif	
	return ret;
}
EXPORT_SYMBOL(rtl_nf_conntrack_death_by_timeout_hooks);

int32 rtl_nf_conntrack_destroy_hooks(rtl_nf_conntrack_inso_s *info)
{
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	spin_lock_bh(&nf_conntrack_lock);
#endif
	rtl_delConnCache(info->ct);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	spin_unlock_bh(&nf_conntrack_lock);
#endif
	#endif

	#ifdef CONFIG_RTL_FAST_IPV6
	if(fast_ipv6_fw)
		rtl_DelV6ConnCache(info->ct); 
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nf_conntrack_destroy_hooks);

int32 rtl_nf_conntrack_confirm_hooks(rtl_nf_conntrack_inso_s *info)
{
	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	rtl_connGC_addList((void*)info->skb, (void*)info->ct);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nf_conntrack_confirm_hooks);

int32 rtl_nf_init_conntrack_hooks(rtl_nf_conntrack_inso_s *info)
{

	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	INIT_LIST_HEAD(&info->ct->state_tuple);
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nf_init_conntrack_hooks);


int32 rtl_nf_conntrack_init_hooks(void)
{
	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	rtl_nf_conn_GC_init();
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nf_conntrack_init_hooks);

int32 rtl_tcp_packet_hooks(rtl_nf_conntrack_inso_s *info)
{
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	if (info->new_state==TCP_CONNTRACK_LAST_ACK) {
		rtl865x_handle_nat(info->ct, 0, NULL);
	}
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_tcp_packet_hooks);

int32 rtl_nf_nat_packet_hooks(rtl_nf_conntrack_inso_s *info)
{
	#if (defined(IMPROVE_QOS) && defined(CONFIG_RTL_IPTABLES_FAST_PATH)) || defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_addConnCache(info->ct, info->skb);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nf_nat_packet_hooks);

#ifdef CONFIG_RTL_WLAN_DOS_FILTER
#define RTL_WLAN_NAME "wlan"
#define TCP_SYN 2
#define _MAX_SYN_THRESHOLD 		400
#define _WLAN_BLOCK_TIME			20	// unit: seconds

int wlan_syn_cnt=0;
int wlan_block=0, wlan_block_count=0;
unsigned int dbg_wlan_dos_block_pkt_num=0;
unsigned char block_source_mac[6];
int wlan_dos_filter_enabled = 1;

extern unsigned int _br0_ip;

#ifdef CONFIG_RTL8192CD
extern int issue_disassoc_from_kernel(void *priv, unsigned char *mac);
#endif

static struct timer_list wlan_dos_timer;
static void wlan_dos_timer_fn(unsigned long arg)
{	
	wlan_syn_cnt = 0;

	if(wlan_block_count >=_WLAN_BLOCK_TIME) {		
		wlan_block=0;
		wlan_block_count=0;
	}
	if(wlan_block == 1)
		wlan_block_count++;
	
      	mod_timer(&wlan_dos_timer, jiffies + HZ);
}

#endif

int32 rtl_nat_init_hooks(void)
{
#ifdef CONFIG_RTL_819X_SWCORE
	rtl_nat_init();
#endif
	#if 0//defined(CONFIG_NET_SCHED)
	rtl_qos_init();
	#endif
	#if defined (CONFIG_RTL_HW_QOS_SUPPORT)
	rtl_qos_initHook( );
	#endif
#ifdef CONFIG_RTL_WLAN_DOS_FILTER
      init_timer(&wlan_dos_timer);
      wlan_dos_timer.expires  = jiffies + HZ;
      wlan_dos_timer.data     = 0L;
      wlan_dos_timer.function = wlan_dos_timer_fn;
      mod_timer(&wlan_dos_timer, jiffies + HZ);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nat_init_hooks);

int32 rtl_nat_cleanup_hooks(void)
{
	#if 0//defined(CONFIG_NET_SCHED)
	rtl_qos_cleanup();
	#endif
	
#if defined (CONFIG_RTL_HW_QOS_SUPPORT)
	rtl_qos_cleanupHook( );
#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nat_cleanup_hooks);

int32 rtl_fn_hash_insert_hooks(struct fib_table *tb, struct fib_config *cfg, struct fib_info *fi)
{
#if defined( CONFIG_RTL_IPTABLES_FAST_PATH)
	#if defined(CONFIG_FAST_PATH_MODULE)
	if(FastPath_hook3!=NULL)
	{
		FastPath_hook3(cfg->fc_dst? cfg->fc_dst: 0, inet_make_mask(cfg->fc_dst_len),cfg->fc_gw ? cfg->fc_gw : 0, (uint8 *)fi->fib_dev->name, RT_NONE);
	}
	#else
	rtk_addRoute(cfg->fc_dst? cfg->fc_dst: 0, inet_make_mask(cfg->fc_dst_len),cfg->fc_gw ? cfg->fc_gw : 0, (uint8 *)fi->fib_dev->name, RT_NONE);
	#endif
#endif


	#if defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_fn_insert(tb, cfg, fi);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_fn_hash_insert_hooks);

int32 rtl_fn_hash_delete_hooks(struct fib_table *tb, struct fib_config *cfg)
{
	#if defined(CONFIG_RTK_IPTABLES_FAST_PATH)
	#ifdef CONFIG_FAST_PATH_MODULE
	if(FastPath_hook1!=NULL)
	{
		FastPath_hook1(cfg->fc_dst? cfg->fc_dst : 0, inet_make_mask(cfg->fc_dst_len));
	}
	#else
	rtk_delRoute(cfg->fc_dst? cfg->fc_dst : 0, inet_make_mask(cfg->fc_dst_len));
	#endif
	#endif

	#if defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_fn_delete(tb, cfg);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_fn_hash_delete_hooks);


int32 rtl_fn_flush_list_hooks(int	 fz_order, int idx, u32 tb_id, u32 fn_key)
{
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_fn_flush(fz_order, idx, tb_id, fn_key);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_fn_flush_list_hooks);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
int32 rtl_fib_flush_list_hooks(u32 tb_id, u32 fn_key, u32 ip_mask)
{
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_fib_flush(tb_id, fn_key, ip_mask);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_fib_flush_list_hooks);
#endif

int32 rtl_fn_hash_replace_hooks(struct fib_table *tb, struct fib_config *cfg, struct fib_info *fi)
{
#if defined( CONFIG_RTL_IPTABLES_FAST_PATH)
	#if defined(CONFIG_FAST_PATH_MODULE)
	if(FastPath_hook2!=NULL)
	{
		FastPath_hook2(cfg->fc_dst? cfg->fc_dst: 0, inet_make_mask(cfg->fc_dst_len),cfg->fc_gw ? cfg->fc_gw : 0, (uint8 *)fi->fib_dev->name, RT_NONE);
	}
	#else
	rtk_modifyRoute(cfg->fc_dst? cfg->fc_dst: 0, inet_make_mask(cfg->fc_dst_len),cfg->fc_gw ? cfg->fc_gw : 0, (uint8 *)fi->fib_dev->name, RT_NONE);
	#endif
#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_fn_hash_replace_hooks);

#if defined(CONFIG_IPV6) && defined(CONFIG_RTL_8198C)
int32 rtl8198c_fib6_add_hooks(struct rt6_info *rt)
{
	rtl8198c_ipv6_router_add(rt);

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl8198c_fib6_add_hooks);

int32 rtl8198c_fib6_del_hooks(struct rt6_info *rt)
{
	rtl8198c_ipv6_router_del(rt);

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl8198c_fib6_del_hooks);
#endif


int32 rtl_dev_queue_xmit_hooks(struct sk_buff *skb, struct net_device *dev)
{
	#if defined( CONFIG_RTL_IPTABLES_FAST_PATH)
	//rtl_fp_dev_queue_xmit_check(skb, dev);
	if(rtl_fp_dev_queue_xmit_check_fphook)
		rtl_fp_dev_queue_xmit_check_fphook(skb, dev);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_dev_queue_xmit_hooks);

int32 rtl_dev_hard_start_xmit_hooks(struct sk_buff *skb, struct net_device *dev, struct netdev_queue *txq)
{
	#if defined( CONFIG_RTL_IPTABLES_FAST_PATH)
	//rtl_fp_dev_hard_start_xmit_check(skb, dev, txq);
	if(rtl_fp_dev_hard_start_xmit_check_fphook)
		rtl_fp_dev_hard_start_xmit_check_fphook(skb, dev, txq);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_dev_hard_start_xmit_hooks);

#ifdef CONFIG_RTL_WLAN_DOS_FILTER

static int  filter_dos_wlan(struct sk_buff *skb)
{
	struct iphdr *iph;
	struct tcphdr *tcph;	
	unsigned char *tflag;		
	int ret=NF_ACCEPT;
	
	iph=ip_hdr(skb);
	tcph=(void *) iph + iph->ihl*4;
	tflag=(void *) tcph + 13;

     	//wlan_dev=__dev_get_by_name(&init_net,RTL_PS_WLAN0_DEV_NAME);	// wlan0
     	//wlan_dev=__dev_get_by_name(&init_net,RTL_PS_LAN_P0_DEV_NAME);	// eth0

	//if(skb->dev && (skb->dev == wlan_dev))

	if ((skb->dev) &&	(!strncmp(skb->dev->name, RTL_WLAN_NAME, 4)))	// wlan0, wlan1, wlan0-va0, ... and so on
	{
		if ((iph->protocol==IPPROTO_TCP) && ((*tflag & 0x3f)==TCP_SYN) && (iph->daddr == _br0_ip))		// xdos.exe 192.168.1.254 0-65535
		{	
			//if(wlan_block==1 && attack_daddr2==iph->daddr) {
			if ((wlan_block==1) && (memcmp(block_source_mac, &(skb->mac_header[6]), 6) == 0)) {
				dbg_wlan_dos_block_pkt_num++;
				ret = NF_DROP;
			}
			else {
	      			wlan_syn_cnt++;
			
				if(wlan_syn_cnt > _MAX_SYN_THRESHOLD)
				{
					//attack_daddr2=iph->daddr;
					wlan_block=1;

#ifdef CONFIG_RTL8192CD
					issue_disassoc_from_kernel((void *) skb->dev->priv, &(skb->mac_header[6]));
#endif
					memcpy(block_source_mac, &(skb->mac_header[6]), 6);
				}
			}
		}
			
	}

	return (ret);
}

int filter_dos_wlan_enter(struct sk_buff **pskb)
{
	int ret;
	struct sk_buff *skb;

	skb=*pskb;
	skb->transport_header=skb->data;
	skb->network_header = skb->data;

	ret = filter_dos_wlan((void*)skb);
	if (ret == NF_DROP) {
		kfree_skb(skb);
		ret = NET_RX_DROP;
	}
	else {
		ret = NET_RX_SUCCESS;
	}

	return ret;
}
#endif

int32 rtl_netif_receive_skb_hooks(struct sk_buff **pskb)
{
	int	ret;

	#if defined(CONFIG_RTL_FAST_BRIDGE)
	if(skb->dev->br_port && (rtl_fast_br_forwarding(*pskb)==RTL_FAST_BR_SUCCESS)) {
		ret = RTL_PS_HOOKS_RETURN;
	} else
	#endif

	#ifdef CONFIG_RTL_WLAN_DOS_FILTER
	if (wlan_dos_filter_enabled && filter_dos_wlan_enter(pskb)== NET_RX_DROP) {
		ret = RTL_PS_HOOKS_RETURN;
	} else
	#endif
	
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	//if (FastPath_Enter(pskb)== NET_RX_DROP)
	if (fast_path_hook(pskb)== NET_RX_DROP) {
		ret = RTL_PS_HOOKS_RETURN;
	} else
	#endif
	{
		ret = RTL_PS_HOOKS_CONTINUE;
	}

	return ret;
}
EXPORT_SYMBOL(rtl_netif_receive_skb_hooks);

int32 rtl_br_dev_queue_push_xmit_before_xmit_hooks(struct sk_buff *skb)
{
	#if defined(CONFIG_RTL_FAST_BRIDGE)
	rtl_fb_add_br_entry(skb);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_br_dev_queue_push_xmit_before_xmit_hooks);


int32 rtl_neigh_forced_gc_hooks(struct neigh_table *tbl, struct neighbour *n)
{
	#if (defined(CONFIG_RTL_HARDWARE_NAT)&&defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L3)) ||(defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C))
	syn_asic_arp(n,  0);
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_forced_gc_hooks);

int32 rtl_neigh_flush_dev_hooks(struct neigh_table *tbl, struct net_device *dev, struct neighbour *n)
{
	#if (defined(CONFIG_RTL_HARDWARE_NAT) && defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L3)) || defined(CONFIG_RTL_IPTABLES_FAST_PATH)  ||(defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C))
	if (n->nud_state & NUD_VALID) {
	#if (defined(CONFIG_RTL_HARDWARE_NAT)&&defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L3)) ||(defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C))
	syn_asic_arp(n,  0);
	#endif

	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
		#ifdef CONFIG_FAST_PATH_MODULE
		if(FastPath_hook7!=NULL) {
			FastPath_hook7(*(u32*)n->primary_key);
		}
		#else
		rtk_delArp(*(u32*)n->primary_key);
		#endif
	#endif
	}
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_flush_dev_hooks);

int32 rtl_neigh_destroy_hooks(struct neighbour *n)
{
	#if (defined(CONFIG_RTL_HARDWARE_NAT)&&defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L3)) ||(defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C))
	syn_asic_arp(n,  0);
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_destroy_hooks);

int32 rtl_neigh_connect_hooks(struct neighbour *neigh)
{
	#if (defined(CONFIG_RTL_HARDWARE_NAT)&&defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L3)) ||(defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C))
	if (neigh->nud_state & NUD_REACHABLE) {
		syn_asic_arp(neigh,  1);
	}
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_connect_hooks);

int32 rtl_neigh_update_hooks(struct neighbour *neigh, const u8 *lladdr, uint8 old)
{
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	if (old & NUD_VALID) {
		#ifdef CONFIG_FAST_PATH_MODULE
		if(FastPath_hook8!=NULL) {
			FastPath_hook8(*(u32*)neigh->primary_key, (ether_addr_t*)lladdr, ARP_NONE);
		}
		#else
		rtk_modifyArp(*(u32*)neigh->primary_key, (ether_addr_t*)lladdr, ARP_NONE);
		#endif
	}
	#endif

	#if (defined(CONFIG_RTL_HARDWARE_NAT)&&defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L3)) ||(defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C))
	syn_asic_arp(neigh,  1);
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_update_hooks);

int32 rtl_neigh_update_post_hooks(struct neighbour *neigh, const u8 *lladdr, uint8 old)
{
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	if ((neigh->nud_state & NUD_VALID) && !(old & NUD_VALID)) {
		#if	defined(CONFIG_FAST_PATH_MODULE)
		if(FastPath_hook5!=NULL)
		{
			FastPath_hook5(*(u32*)neigh->primary_key, (ether_addr_t*)neigh->ha, ARP_NONE);
		}
		#else
		rtk_addArp(*(u32*)neigh->primary_key, (ether_addr_t*)neigh->ha, ARP_NONE);
		#endif
	} else if ((old & NUD_VALID) && !(neigh->nud_state & NUD_VALID)) {
		#if	defined(CONFIG_FAST_PATH_MODULE)
		if(FastPath_hook7!=NULL)
		{
			FastPath_hook7(*(u32*)neigh->primary_key);
		}
		#else
		rtk_delArp(*(u32*)neigh->primary_key);
		#endif
	}
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_update_post_hooks);

static __inline__ int neigh_max_probes(struct neighbour *n)
{
	struct neigh_parms *p = n->parms;
	return (n->nud_state & NUD_PROBE ?
		p->ucast_probes :
		p->ucast_probes + p->app_probes + p->mcast_probes);
}

int32  rtl_neigh_periodic_timer_hooks(struct neighbour *n,  unsigned int  refresh)
{
	int	ret;
	#if defined(RTL_REFRESH_HW_L2_ENTRY_DECIDE_BY_HW_NAT)
	int 	tval = 0;
	#endif

	if (!(n->nud_state & NUD_VALID))
		return RTL_PS_HOOKS_CONTINUE;

	ret = RTL_PS_HOOKS_CONTINUE;
	#if defined(CONFIG_IPV6) && defined(ONFIG_RTL_8198C)
	if (n->tbl && (n->tbl->family==AF_INET6) && (n->tbl->key_len==sizeof(inv6_addr_t))) 
	{
		if (rtl8198c_ipv6ArpSync(*((inv6_addr_t *)n->primary_key), refresh) >0) {
			n->used = jiffies;
			n->dead=0;
			ret = RTL_PS_HOOKS_BREAK;
		}
	} 
	else if (n->tbl && (n->tbl->family==AF_INET) && (n->tbl->key_len==4))
	#endif
	{
		#if defined(CONFIG_RTL_HARDWARE_NAT) && defined(CONFIG_RTL_LAYERED_DRIVER)  && defined(CONFIG_RTL_LAYERED_DRIVER_L3)
		#if defined(RTL_REFRESH_HW_L2_ENTRY_DECIDE_BY_HW_NAT)
		if (rtl865x_check_hw_nat_by_ip(htonl(*((u32 *)n->primary_key)))== SUCCESS)
			tval = rtl865x_arpSync(htonl(*((u32 *)n->primary_key)), 1);
		else
			tval = rtl865x_arpSync(htonl(*((u32 *)n->primary_key)), refresh);
			
		if (tval > 0)
		#else
		if (rtl865x_arpSync(htonl(*((u32 *)n->primary_key)), refresh)>0) 
		#endif
		{
			n->used = jiffies;
			n->dead=0;
			ret = RTL_PS_HOOKS_BREAK;
		}
		else
		#endif

		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
		{
			#ifdef CONFIG_FAST_PATH_MODULE
			if(FastPath_hook7!=NULL)
			{
				FastPath_hook7(*(u32*)n->primary_key);
			}
			#else
			rtk_delArp(*(u32*)n->primary_key);
			#endif
		}
        #else
        return ret;
		#endif
	}

	return ret;
}
EXPORT_SYMBOL(rtl_neigh_periodic_timer_hooks);

int32 rtl_neigh_timer_handler_pre_update_hooks(struct neighbour *neigh, unsigned state)
{
	#if (defined(CONFIG_RTL_HARDWARE_NAT)&&defined(CONFIG_RTL_LAYERED_DRIVER)&&defined(CONFIG_RTL_LAYERED_DRIVER_L3)) ||(defined(CONFIG_IPV6)&&defined(ONFIG_RTL_8198C))
	int32	tval;
	#endif

	if (state & NUD_REACHABLE) {
		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
		if (neigh->nud_state & NUD_VALID) {
			#ifdef CONFIG_FAST_PATH_MODULE
			if(FastPath_hook7!=NULL)
			{
				FastPath_hook7(*(u32*)neigh->primary_key);
			}
			#else
			rtk_delArp(*(u32*)neigh->primary_key);
			#endif
		}
		#endif

		#if defined(CONFIG_IPV6) && defined(ONFIG_RTL_8198C)
		if (neigh->tbl && (neigh->tbl->family==AF_INET6) && (neigh->tbl->key_len==sizeof(inv6_addr_t))) 
		{
			tval = rtl8198c_ipv6ArpSync(*((inv6_addr_t *)neigh->primary_key), 0);
			if (tval > 0)
				neigh->confirmed = jiffies;
		} 
		else if (neigh->tbl && (neigh->tbl->family==AF_INET) && (neigh->tbl->key_len==4))
		#endif
		{
			#if defined(CONFIG_RTL_HARDWARE_NAT) && defined(CONFIG_RTL_LAYERED_DRIVER)  && defined(CONFIG_RTL_LAYERED_DRIVER_L3)
			#if defined(RTL_REFRESH_HW_L2_ENTRY_DECIDE_BY_HW_NAT)
			if (rtl865x_check_hw_nat_by_ip(htonl(*((u32 *)neigh->primary_key)))== SUCCESS)
				tval = rtl865x_arpSync(htonl(*((u32 *)neigh->primary_key)), 1);
			else
			#endif
				tval = rtl865x_arpSync(htonl(*((u32 *)neigh->primary_key)), 0);
			if (tval > 0)
				neigh->confirmed = jiffies;
			
			#if 0
			printk("%s:%d: ip:%u.%u.%u.%u, mac:%x:%x:%x:%x:%x:%x, tval is %d\n",
			__FUNCTION__,__LINE__,NIPQUAD(htonl(*((u32 *)neigh->primary_key))), neigh->ha[0], neigh->ha[1],
			neigh->ha[2], neigh->ha[3], neigh->ha[4], neigh->ha[5],tval);
			#endif
			#endif
		}

	} else if (state & NUD_DELAY) {
		#if defined(CONFIG_IPV6) && defined(ONFIG_RTL_8198C)
		if (neigh->tbl && (neigh->tbl->family==AF_INET6) && (neigh->tbl->key_len==sizeof(inv6_addr_t))) 
		{
			tval = rtl8198c_ipv6ArpSync(*((inv6_addr_t *)neigh->primary_key), 0);
			if (tval > 0)
				neigh->confirmed = jiffies;
		} 
		else if (neigh->tbl && (neigh->tbl->family==AF_INET) && (neigh->tbl->key_len==4))
		#endif
		{
			#if defined(CONFIG_RTL_HARDWARE_NAT) && defined(CONFIG_RTL_LAYERED_DRIVER)  && defined(CONFIG_RTL_LAYERED_DRIVER_L3)
			#if defined(RTL_REFRESH_HW_L2_ENTRY_DECIDE_BY_HW_NAT)
			if (rtl865x_check_hw_nat_by_ip(htonl(*((u32 *)neigh->primary_key)))== SUCCESS)
				tval = rtl865x_arpSync(htonl(*((u32 *)neigh->primary_key)), 1);
			else
			#endif
				tval = rtl865x_arpSync(htonl(*((u32 *)neigh->primary_key)), 0);
			if (tval > 0)
				neigh->confirmed = jiffies;
			
			#if 0
			printk("%s:%d: ip:%u.%u.%u.%u, mac:%x:%x:%x:%x:%x:%x, tval is %d",
			__FUNCTION__,__LINE__,NIPQUAD(htonl(*((u32 *)neigh->primary_key))), neigh->ha[0], neigh->ha[1],
			neigh->ha[2], neigh->ha[3], neigh->ha[4], neigh->ha[5],tval);
			#endif
			#endif
		}
	}

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_timer_handler_pre_update_hooks);

int32 rtl_neigh_timer_handler_during_update_hooks(struct neighbour *neigh, unsigned state)
{
	#if (defined(CONFIG_RTL_HARDWARE_NAT)&&defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L3)) ||(defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C))
	if ((neigh->nud_state & (NUD_INCOMPLETE | NUD_PROBE)) &&
	    atomic_read(&neigh->probes) >= neigh_max_probes(neigh)) {
		if (neigh->nud_state & NUD_VALID) {
			/*delete asic arp entry*/
			syn_asic_arp(neigh, 0);
			#if 0
			printk("%s:%d: ip:%u.%u.%u.%u, mac:%x:%x:%x:%x:%x:%x\n",
			__FUNCTION__,__LINE__,NIPQUAD(htonl(*((u32 *)neigh->primary_key))), neigh->ha[0], neigh->ha[1],
			neigh->ha[2], neigh->ha[3], neigh->ha[4],neigh->ha[5]);
			#endif
		}
	}
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_timer_handler_during_update_hooks);

int32 rtl_neigh_timer_handler_post_update_hooks(struct neighbour *neigh, unsigned state)
{
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	if ((neigh->nud_state & NUD_VALID) && !(state & NUD_VALID)) {
		#ifdef CONFIG_FAST_PATH_MODULE
		if(FastPath_hook5!=NULL)
		{
			FastPath_hook5(*(u32*)neigh->primary_key, (ether_addr_t*)neigh->ha, ARP_NONE);
		}
		#else
		rtk_addArp(*(u32*)neigh->primary_key, (ether_addr_t*)neigh->ha, ARP_NONE);
		#endif
	} else if ((state & NUD_VALID) && !(neigh->nud_state & NUD_VALID)) {
		#ifdef CONFIG_FAST_PATH_MODULE
		if(FastPath_hook7!=NULL)
		{
			FastPath_hook7(*(u32*)neigh->primary_key);
		}
		#else
		rtk_delArp(*(u32*)neigh->primary_key);
		#endif
	}
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_timer_handler_post_update_hooks);

int32 rtl___neigh_event_send_pre_hooks(struct neighbour *neigh, struct sk_buff *skb)
{
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	if (!(neigh->nud_state & (NUD_STALE | NUD_INCOMPLETE))) {
		if (neigh->nud_state & NUD_VALID) {
			#if	defined(CONFIG_FAST_PATH_MODULE)
			if(FastPath_hook7!=NULL) {
				FastPath_hook7(*(u32*)neigh->primary_key);
			}
			#else
			rtk_delArp(*(u32*)neigh->primary_key);
			#endif
		}
	}
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl___neigh_event_send_pre_hooks);

int32 rtl___neigh_event_send_post_hooks(struct neighbour *neigh, struct sk_buff *skb)
{
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl___neigh_event_send_post_hooks);

int32 rtl_neigh_init_hooks(void)
{
	#if defined(CONFIG_RTL_MULTIPLE_WAN)
	rtl_set_callback_for_ps_arp(rtl_get_ps_arp_mapping);
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_neigh_init_hooks);

#if defined(CONFIG_BRIDGE)
extern int32 rtl_br_fdb_time_update_hook(void *br_dummy, void *fdb_dummy, const unsigned char *addr);
int32 rtl___br_fdb_get_timeout_hooks(struct net_bridge *br, struct net_bridge_fdb_entry *fdb, const unsigned char *addr)
{
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_FASTBRIDGE)
	//if (rtl_br_fdb_time_update((void*)br, (void*)fdb, addr)==FAILED)
	if (rtl_br_fdb_time_update_hook((void*)br, (void*)fdb, addr)==FAILED) {
		return RTL_PS_HOOKS_BREAK;
	}
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl___br_fdb_get_timeout_hooks);
#endif

int32 rtl_masq_device_event_hooks(struct notifier_block *this, struct net_device *dev,  unsigned long event)
{
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	if (dev!=NULL && dev->ip_ptr!=NULL)
		rtl_update_ip_tables(dev->name, event, (struct in_ifaddr *)(((struct in_device *)(dev->ip_ptr))->ifa_list));
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_masq_device_event_hooks);


 int32 rtl_masq_inet_event_hooks(struct notifier_block *this, unsigned long event, void *ptr)
 {
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	struct in_ifaddr *ina;

	ina = (struct in_ifaddr*)ptr;

	#ifdef CONFIG_HARDWARE_NAT_DEBUG
	/*2007-12-19*/
	printk("%s:%d\n",__FUNCTION__,__LINE__);
	printk("ptr->ifa_dev->dev->name is %s\n", ina->ifa_dev->dev->name);
	#endif

	rtl_update_ip_tables(ina->ifa_dev->dev->name, event, ina);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
 }
EXPORT_SYMBOL(rtl_masq_inet_event_hooks);


int32 rtl_translate_table_hooks(const char *name,
		unsigned int valid_hooks,
		struct xt_table_info *newinfo,
		void *entry0,
		unsigned int size,
		unsigned int number,
		const unsigned int *hook_entries,
		const unsigned int *underflows)
{
#if defined(CONFIG_RTL_HARDWARE_NAT)
	//hyking:check masquerade and add ip
	if(strcmp(name,"nat") == 0)
	{
		rtl_flush_extern_ip();
		rtl_init_masq_info();
		rtl_check_for_extern_ip(name,valid_hooks,newinfo,entry0,size,number,hook_entries,underflows);
	}
#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_translate_table_hooks);

int32 rtl_ip_tables_init_hooks(void)
{
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_init_masq_info();
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_ip_tables_init_hooks);


int32 rtl_ip_vs_conn_expire_hooks1(struct ip_vs_conn *cp)
{
	int32	ret;

	ret = RTL_PS_HOOKS_CONTINUE;
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	if (FAILED==rtl_ip_vs_conn_expire_check(cp)) {
		ret = RTL_PS_HOOKS_RETURN;
	}
	#endif

	return ret;
}

int32 rtl_ip_vs_conn_expire_hooks2(struct ip_vs_conn *cp)
{
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_ip_vs_conn_expire_check_delete(cp);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}

#if defined(CONFIG_IP_VS_PROTO_TCP)
int32 rtl_tcp_state_transition_hooks(struct ip_vs_conn *cp, int direction, const struct sk_buff *skb, struct ip_vs_protocol *pp)
{
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_tcp_state_transition_check(cp, direction, skb, pp);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_tcp_state_transition_hooks);
#endif

#if defined(CONFIG_IP_VS_PROTO_UDP)
int32 rtl_udp_state_transition_hooks(struct ip_vs_conn *cp, int direction, const struct sk_buff *skb, struct ip_vs_protocol *pp)
{
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	rtl_udp_state_transition_check(cp, direction, skb, pp);
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_udp_state_transition_hooks);
#endif

#ifdef CONFIG_PROC_FS
int rtl_ct_seq_show_hooks(struct seq_file *s, struct nf_conn *ct)
{
	//hyking add for hw use
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	struct nf_conn_nat *nat;
	char *state[2]={"Hardware","software"};

	nat = nfct_nat(ct);
	if (nat == NULL) {
	  if (seq_printf(s,"[%s] ", state[1]) != 0)
	   return RTL_PS_HOOKS_BREAK;
	
	  return RTL_PS_HOOKS_CONTINUE;
	 }
	if(seq_printf(s,"[%s] ",nat->hw_acc?state[0]:state[1]) != 0)
		return RTL_PS_HOOKS_BREAK;
	#endif
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_ct_seq_show_hooks);
#endif

#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
//When do garbage collection and dst cache overflow, should not do garbage collection for rtl_gc_overflow_timout(default 3s)
//Note: rtl_gc_overflow_timout can be modified by user via /proc/gc_overflow_timout
unsigned long rtl_gc_overflow_timout=3*HZ;
static unsigned long rtl_gc_overflow_timeout=0;
#endif

//Before do garbage collection, do rtl_dst_alloc_gc_pre_check_hooks
int32 rtl_dst_alloc_gc_pre_check_hooks(struct dst_ops * ops)
{
#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	if((rtl_gc_overflow_timeout > 0)&& time_after_eq(rtl_gc_overflow_timeout, jiffies)){
		return RTL_PS_HOOKS_RETURN;
	}
#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_dst_alloc_gc_pre_check_hooks);

//After do garbage collection and dst cache overflow, do rtl_dst_alloc_gc_post_check1_hooks
int32 rtl_dst_alloc_gc_post_check1_hooks(struct dst_ops * ops)
{
#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	rtl_gc_overflow_timeout=jiffies+rtl_gc_overflow_timout;
#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_dst_alloc_gc_post_check1_hooks);

//After [do garbage collection and dst cache not overflow] and dst alloc success, do rtl_dst_alloc_gc_post_check2_hooks
int32 rtl_dst_alloc_gc_post_check2_hooks(struct dst_ops * ops, struct dst_entry * dst)
{
#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	rtl_gc_overflow_timeout=0;
#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_dst_alloc_gc_post_check2_hooks);

#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
// hooks in clean_from_lists at rtl_nf_connGC.c
int32 clean_from_lists_hooks(struct nf_conn *ct, struct net *net)
{
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
		rtl_delConnCache(ct);
	#endif
	#ifdef CONFIG_RTL_FAST_IPV6
	if(fast_ipv6_fw)
		rtl_DelV6ConnCache(ct); 
	#endif

	return RTL_PS_HOOKS_CONTINUE;
}

// hooks in __nf_ct_refresh_acct_proto at rtl_nf_connGC.c
int32 __nf_ct_refresh_acct_proto_hooks(struct nf_conn *ct,
					enum ip_conntrack_info ctinfo,
					const struct sk_buff *skb,
					int do_acct,
					int *event)
{
#ifdef CONFIG_IP_NF_CT_ACCT
	if (do_acct) {
		ct->counters[CTINFO2DIR(ctinfo)].packets++;
		ct->counters[CTINFO2DIR(ctinfo)].bytes +=
						ntohs(skb->nh.iph->tot_len);
		if ((ct->counters[CTINFO2DIR(ctinfo)].packets & 0x80000000)
		    || (ct->counters[CTINFO2DIR(ctinfo)].bytes & 0x80000000))
			*event |= IPCT_COUNTER_FILLING;
	}
#endif

	return RTL_PS_HOOKS_CONTINUE;
}

// hooks1 in __drop_one_conntrack_process at rtl_nf_connGC.c
int32 __drop_one_conntrack_process_hooks1(struct nf_conn* ct, int dropPrioIdx, int factor, int checkFlags, int tcpUdpState)
{
#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
	if (checkFlags==TRUE && drop_priority[dropPrioIdx].state==tcpUdpState) {
		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
		if (FAILED==rtl_fpTimer_update((void*)ct)) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			spin_unlock_bh(&nf_conntrack_lock);
#else
			read_unlock_bh(&nf_conntrack_lock);
#endif
			rtl_death_action((void*)ct);
			return RTL_PS_HOOKS_RETURN;
		}
		#endif

		#if defined(CONFIG_RTL_HARDWARE_NAT)
		if (FAILED==rtl_hwnat_timer_update(ct)) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			spin_unlock_bh(&nf_conntrack_lock);
#else
			read_unlock_bh(&nf_conntrack_lock);
#endif
			rtl_death_action((void*)ct);
			return RTL_PS_HOOKS_RETURN;
		}
		#endif
	}

#if (HZ==100)
	if (((ct->timeout.expires - jiffies) >> (factor+7))<=drop_priority[dropPrioIdx].threshold)
#elif (HZ==1000)
	if (((ct->timeout.expires - jiffies) >> (factor+10))<=drop_priority[dropPrioIdx].threshold)
#else
	#error "Please Check the HZ defination."
#endif
	{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		spin_unlock_bh(&nf_conntrack_lock);
#else
		read_unlock_bh(&nf_conntrack_lock);
#endif
		rtl_death_action((void*)ct);
		return RTL_PS_HOOKS_RETURN;
	}

	return RTL_PS_HOOKS_CONTINUE;
#else
	return RTL_PS_HOOKS_BREAK;
#endif
}

// hooks2 in __drop_one_conntrack_process at rtl_nf_connGC.c
int32 __drop_one_conntrack_process_hooks2(struct nf_conn* ct, int dropPrioIdx, int factor, int checkFlags, int tcpUdpState)
{
#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
	add_timer(&ct->timeout);
#endif

	return RTL_PS_HOOKS_CONTINUE;
}

// hooks in rtl_nf_conn_GC_init at rtl_nf_connGC.c
int32 rtl_nf_conn_GC_init_hooks(void)
{
#if defined(CONFIG_PROC_FS)
	gc_overflow_timout_proc_init();
#endif

	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_nf_conn_GC_init_hooks);
#endif


#if defined(CONFIG_BRIDGE)
int32 rtl_fdb_create_hooks(struct net_bridge_fdb_entry *fdb,const unsigned char *addr)
{
#if defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L2)
	#if defined (CONFIG_RTL865X_LANPORT_RESTRICTION)
		if (fdb->is_static == 0)
		{
			rtl865x_addAuthFDBEntry_hooks(addr);
		}

	#else
	//fdb->ageing_timer = 300*HZ;
		rtl865x_addFDBEntry(addr);
	#endif
#endif

return RTL_PS_HOOKS_CONTINUE;

}
EXPORT_SYMBOL(rtl_fdb_create_hooks);
int32 rtl_fdb_delete_hooks(struct net_bridge_fdb_entry *f)
{

#if defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L2) //&& defined(CONFIG_RTL865X_SYNC_L2)
	#if defined (CONFIG_RTL865X_LANPORT_RESTRICTION)
	rtl865x_delAuthLanFDBEntry(RTL865x_L2_TYPEII, f->addr.addr);
	#else
	rtl865x_delLanFDBEntry(RTL865x_L2_TYPEII, f->addr.addr);
	#endif	/*	defined (CONFIG_RTL865X_LANPORT_RESTRICTION)		*/
#endif	/*	defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L2) && defined(CONFIG_RTL865X_SYNC_L2)		*/

#if defined(CONFIG_RTL_FASTBRIDGE)
	rtl_fb_del_entry(f->addr.addr);
#endif	/*	defined(CONFIG_RTL_FASTBRIDGE)	*/
	return RTL_PS_HOOKS_CONTINUE;
}
EXPORT_SYMBOL(rtl_fdb_delete_hooks);


int32 rtl_br_fdb_cleanup_hooks(struct net_bridge *br, struct net_bridge_fdb_entry *f, unsigned long delay)
{
	#if defined(CONFIG_RTL_FASTBRIDGE)
	unsigned long	fb_aging;
	#endif
	#if defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L2) && defined(CONFIG_RTL865X_SYNC_L2)
	int32 port_num;
	unsigned long hw_aging = 0;
	#endif
	int ret;

	/*printk("timelist as follow:(s)jiffies:%ld,f->ageing_timer:%ld,delay:%ld",jiffies/HZ,f->ageing_timer/HZ,delay/HZ);*/
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	if (time_after(f->updated, jiffies))
	{
		printk("\nf->ageing_timer AFTER jiffies:addr is :%x,%x,%x,%x,%x,%x\n",f->addr.addr[0],f->addr.addr[1],f->addr.addr[2],f->addr.addr[3],f->addr.addr[4],f->addr.addr[5]);
#if defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L2) && defined(CONFIG_RTL865X_SYNC_L2)
		printk("time list:jiffies:%ld,hw_aging:%ld,f->ageing_timer:%ld\n",jiffies/HZ,hw_aging/HZ,f->updated/HZ );
#else
		printk("time list:jiffies:%ld,f->ageing_timer:%ld\n",jiffies/HZ,f->updated/HZ );
#endif
		return RTL_PS_HOOKS_BREAK;
	}
	#else
	if (time_after(f->ageing_timer, jiffies))
	{
		DEBUG_PRINT("\nf->ageing_timer AFTER jiffies:addr is :%x,%x,%x,%x,%x,%x\n",f->addr.addr[0],f->addr.addr[1],f->addr.addr[2],f->addr.addr[3],f->addr.addr[4],f->addr.addr[5]);
		DEBUG_PRINT("time list:jiffies:%ld,hw_aging:%ld,f->ageing_timer:%ld\n",jiffies/HZ,hw_aging/HZ,f->ageing_timer/HZ );
		return RTL_PS_HOOKS_BREAK;
	}
	#endif

	#if defined(CONFIG_RTL_LAYERED_DRIVER) && defined(CONFIG_RTL_LAYERED_DRIVER_L2) && defined(CONFIG_RTL865X_SYNC_L2)
		port_num= -100;
		ret = rtl865x_arrangeFdbEntry(f->addr.addr, &port_num);

		switch (ret) {
			case RTL865X_FDBENTRY_450SEC:
				hw_aging = jiffies;
				break;
			case RTL865X_FDBENTRY_300SEC:
				hw_aging = jiffies -150*HZ;
				break;
			case RTL865X_FDBENTRY_150SEC:
				hw_aging = jiffies -300*HZ;
				break;
			case RTL865X_FDBENTRY_TIMEOUT:
			case FAILED:
			default:
				hw_aging =jiffies -450*HZ;
				break;
		}

		ret = 0;
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		if(time_before_eq(f->updated,  hw_aging))
		{
			/*fresh f->ageing_timer*/
			f->updated= hw_aging;
		}
		#else
		if(time_before_eq(f->ageing_timer,  hw_aging))
		{
			/*fresh f->ageing_timer*/
			f->ageing_timer = hw_aging;
		}
		#endif
	#endif

	#if defined(CONFIG_RTL_FASTBRIDGE)
		fb_aging = rtl_fb_get_entry_lastused(f->addr.addr);
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		if(time_before_eq(f->updated,  fb_aging))
		{
			f->updated = fb_aging;
		}
		#else
		if(time_before_eq(f->ageing_timer,  fb_aging))
		{
			f->ageing_timer = fb_aging;
		}
		#endif
	#endif

	if (ret==0) {
		return RTL_PS_HOOKS_CONTINUE;
	} else {
		return RTL_PS_HOOKS_BREAK;
	}
}
EXPORT_SYMBOL(rtl_br_fdb_cleanup_hooks);


#endif	/*	defined(CONFIG_BRIDGE)	*/


#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
void event_ppp_dev_down_hook(const char *name)
{
   if(event_ppp_dev_down_fphook)
		event_ppp_dev_down_fphook(name);
}
EXPORT_SYMBOL(event_ppp_dev_down_hook);

void set_l2tp_device_hook(char *name)
{
   if(set_l2tp_device_fphook)
		set_l2tp_device_fphook(name);
}
EXPORT_SYMBOL(set_l2tp_device_hook);

void set_pptp_device_hook(char *name)
{
   if(set_pptp_device_fphook)
		set_pptp_device_fphook(name);
}
EXPORT_SYMBOL(set_pptp_device_hook);

unsigned long get_fast_l2tp_lastxmit_hook(void)
{
   if(get_fast_l2tp_lastxmit_fphook)
		return get_fast_l2tp_lastxmit_fphook();
   else
		return 0;
}
EXPORT_SYMBOL(get_fast_l2tp_lastxmit_hook);
unsigned long get_fastpptp_lastxmit_hook(void)
{
   if(get_fastpptp_lastxmit_fphook)
		return get_fastpptp_lastxmit_fphook();
   else
		return 0;
}
EXPORT_SYMBOL(get_fastpptp_lastxmit_hook);

int is_l2tp_device_hook(char *ppp_device)	// sync from voip customer for multiple ppp
{
   if(is_l2tp_device_fphook)
		return is_l2tp_device_fphook(ppp_device);
   else
		return 0;
}
EXPORT_SYMBOL(is_l2tp_device_hook);

int check_for_fast_l2tp_to_wan_hook(void *skb)
{
   if(check_for_fast_l2tp_to_wan_fphook)
		return check_for_fast_l2tp_to_wan_fphook(skb);
   else
		return 0;
}
EXPORT_SYMBOL(check_for_fast_l2tp_to_wan_hook);

int fast_l2tp_to_wan_hook(void *skb)
{
   if(fast_l2tp_to_wan_fphook)
		return fast_l2tp_to_wan_fphook(skb);
   else
		return 0;
}
EXPORT_SYMBOL(fast_l2tp_to_wan_hook);

int rtl_fpTimer_update_hook(void *ct)
{
   if(rtl_fpTimer_update_fphook)
		return rtl_fpTimer_update_fphook(ct);
   else
		return -1;
}
EXPORT_SYMBOL(rtl_fpTimer_update_hook);

int32 rtl_br_fdb_time_update_hook(void *br_dummy, void *fdb_dummy, const unsigned char *addr)
{
   if(rtl_br_fdb_time_update_fphook)
		return rtl_br_fdb_time_update_fphook(br_dummy,fdb_dummy,addr);
   else
		return -1;
}
EXPORT_SYMBOL(rtl_br_fdb_time_update_hook);

void ppp_channel_pppoe_hook(struct ppp_channel *chan)
{
    if(ppp_channel_pppoe_fphook)
		return ppp_channel_pppoe_fphook(chan);
	else
		return;
}
EXPORT_SYMBOL(ppp_channel_pppoe_hook);
int clear_pppoe_info_hook(char *ppp_dev, char *wan_dev, unsigned short sid,
								unsigned int our_ip,unsigned int	peer_ip,
								unsigned char * our_mac, unsigned char *peer_mac)
{
   if(clear_pppoe_info_fphook)
		return clear_pppoe_info_fphook(ppp_dev,wan_dev,sid,our_ip,peer_ip,our_mac,peer_mac);
   else
		return 0;
}
EXPORT_SYMBOL(clear_pppoe_info_hook);

int set_pppoe_info_hook(char *ppp_dev, char *wan_dev, unsigned short sid,
							unsigned int our_ip,unsigned int	peer_ip,
							unsigned char * our_mac, unsigned char *peer_mac)
{
   if(set_pppoe_info_fphook)
		return set_pppoe_info_fphook(ppp_dev,wan_dev,sid,our_ip,peer_ip,our_mac,peer_mac);
   else
		return 0;
}
EXPORT_SYMBOL(set_pppoe_info_hook);


int get_pppoe_last_rx_tx_hook(char * ppp_dev,char * wan_dev,unsigned short sid,
									unsigned int our_ip,unsigned int peer_ip,
									unsigned char * our_mac,unsigned char * peer_mac,
									unsigned long * last_rx,unsigned long * last_tx)
{
   if(get_pppoe_last_rx_tx_fphook)
		return get_pppoe_last_rx_tx_fphook(ppp_dev,wan_dev,sid,our_ip,peer_ip,our_mac,peer_mac,last_rx,last_tx);
   else
		return 0;
}
EXPORT_SYMBOL(get_pppoe_last_rx_tx_hook);
#endif

#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static inline struct nf_tcp_net *tcp_pernet(struct net *net)
{
	return &net->ct.nf_ct_proto.tcp;
}
static unsigned int *tcp_get_timeouts(struct net *net)
{
	return tcp_pernet(net)->timeouts;
}
//static unsigned int *tcp_get_timeouts(struct net *net);
int	tcp_get_timeouts_by_state(u_int8_t state,void *ct_or_cp,int is_ct)
{
    struct net *net = NULL;
	unsigned int *tcp_timeouts_run = NULL;
    if(is_ct){
        struct nf_conn *ct = (struct nf_conn *)ct_or_cp;
        net = nf_ct_net(ct);
    }
	else{
        struct ip_vs_conn *cp = (struct ip_vs_conn *)ct_or_cp;
		net = ip_vs_conn_net(cp);
    }
	tcp_timeouts_run = tcp_get_timeouts(net);
    //net_warn_ratelimited("--%s--%d-- state = %d,  tcp_timeouts_run[%s] = %d\n",__FUNCTION__,__LINE__,state,tcp_conntrack_names[state],tcp_timeouts_run[state]);
	return tcp_timeouts_run[state];
}
#else
int	tcp_get_timeouts_by_state(u_int8_t	state)
{
	return tcp_timeouts[state];
}
#endif
EXPORT_SYMBOL(tcp_get_timeouts_by_state);
#endif

#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#include <net/ip_vs.h>
static inline struct nf_udp_net *udp_pernet(struct net *net)
{
	return &net->ct.nf_ct_proto.udp;
}
static unsigned int *udp_get_timeouts(struct net *net)
{
	return udp_pernet(net)->timeouts;
}
unsigned int	udp_get_timeouts_by_state(enum udp_conntrack state,void *ct_or_cp,int is_ct)
{
    struct net *net = NULL;
	unsigned int *udp_timeouts_run = NULL;
    if(is_ct){
        struct nf_conn *ct = (struct nf_conn *)ct_or_cp;
        net = nf_ct_net(ct);
    }
	else{
        struct ip_vs_conn *cp = (struct ip_vs_conn *)ct_or_cp;
		net = ip_vs_conn_net(cp);
    }
	udp_timeouts_run = udp_get_timeouts(net);
    //net_warn_ratelimited("--%s--%d-- udp_timeouts_run[%d] = %d\n",__FUNCTION__,__LINE__,state,udp_timeouts_run[state]);
	return udp_timeouts_run[state];
}
#else
unsigned int	udp_get_timeouts_by_state(enum udp_conntrack state)
{
	return udp_timeouts[state];
}
#endif
EXPORT_SYMBOL(udp_get_timeouts_by_state);
#endif

#ifdef CONFIG_RTL_PPPOE_DIRECT_REPLY
int magicNum=-1;
EXPORT_SYMBOL(magicNum);
//void (*tx_pppoe_request_hook)(struct sk_buff *skb) = NULL;
void clear_magicNum(struct sk_buff *pskb)
{
	//panic_printk("%s:%d\n",__FUNCTION__,__LINE__);
	magicNum = -1;
}
EXPORT_SYMBOL(clear_magicNum);

void extract_magicNum(struct sk_buff *skb)
{
	unsigned char *mac_hdr = skb->data;
	//int i;
	int payloadLen=0;
	unsigned char type;
	unsigned char len;
	unsigned char *ptr;
	
	/*
	if( (*(unsigned short *)(&mac_hdr[12])==0x8864) \
		&&(*(unsigned short *)(&mac_hdr[20])==0xc021))
	{
		panic_printk("skb->dev is %s\n",skb->dev->name);
		for(i=0;i<32;i++)
		{
				panic_printk("0x%x\t",mac_hdr[i]);
				if(i%8==7)
				{
					panic_printk("\n");
				}
		}

	}	
	*/
	//panic_printk("%s:%d,magicNum is 0x%x\n",__FUNCTION__,__LINE__,magicNum);
	if(skb->dev==NULL)
	{
		return ;
	}
	
	if(strncmp(skb->dev->name, "ppp" ,3)==0)
	{
		return;
	}
	
	if((mac_hdr[12]!=0x88) || (mac_hdr[13]!=0x64))
	{
		return;
	}
	
	
	if((mac_hdr[20]!=0xc0) || (mac_hdr[21]!=0x21))
	{
		return;
	}

	/*lcp configuration request*/
	if(mac_hdr[22]==0x01)
	{
	
		payloadLen=(mac_hdr[24]<<8)+mac_hdr[25];	
		payloadLen=payloadLen-4;
		ptr=(mac_hdr+26);

		while(payloadLen>0)
		{
			/*parse tlv option*/
			type=*ptr;
			len=*(ptr+1);
			
			//panic_printk("%s:%d,type is %d\n",__FUNCTION__,__LINE__,type);
			if(type==0x05) /*magic number option*/
			{
				memcpy(&magicNum, ptr+2 , 4);
				//panic_printk("%s:%d,magicNum is 0x%x\n",__FUNCTION__,__LINE__,magicNum);
				break;
			}

			if(len>payloadLen)
			{
				break;
			}
			ptr=ptr+len;
			payloadLen=payloadLen-len;
			
		}
	}
	else if(mac_hdr[22]==0x09) /*lcp echo request*/
	{
		ptr=(mac_hdr+26);
		memcpy(&magicNum, ptr , 4);
		//panic_printk("%s:%d,magic number is 0x%x\n",__FUNCTION__,__LINE__,magicNum);
	}
	return;

}
EXPORT_SYMBOL(extract_magicNum);
#endif

#if defined (CONFIG_RTL_HW_QOS_SUPPORT)
//#define CONFIG_RTL_HW_QOS_SUPPORT_DEBUG 1
#if defined(CONFIG_RTL_HARDWARE_NAT)
extern int32 rtl8651_setAsicOperationLayer(uint32 layer) ;
#endif
int hwQosEnabled=1;
int qosEnabled =1;
int hwQosFlag=0;
int inhandle=0;
#define RTL_HWQOS_FILTER_FLAG		0x1
#define RTL_HWQOS_NOQUEUE_FLAG		0x2
#define RTL_HWQOS_QUEUE_FLAG		0x4
#define RTL_HWQOS_SCH_FLAG			0x8
#define RTL_HWQOS_IPTABLES_FLAG		0x10
#define RTL_HWQOS_FLAG_MASK		0x1F
#define RTL_HWQOS_TCFLAG_MASK		0xF
#define RTL_HWQOS_QUEUEFLAG_MASK		0xE
static void rtl_qosTimerInit(void);
static void rtl_update_hooktime(struct xt_table * table);
static void rtl_qosTimerDestroy(void);

int rtl_hwQosHwNatProcess(struct net_device *dev, int flag)
{
	int ret=0;
	#if defined ( CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
	printk("***************************hwQosFlag:%x,flag:%x,[%s]:[%d].\n",hwQosFlag,flag,__FUNCTION__,__LINE__);
	#endif
	if(flag ==0)
	{
		if((hwQosEnabled==0)||(qosEnabled==0))
		{
			rtl865x_HwQosProcess(dev, 0);
		}
		else if (hwQosEnabled)
		{
			if(hwQosFlag&RTL_HWQOS_FLAG_MASK)
			{
				if(!(hwQosFlag&RTL_HWQOS_NOQUEUE_FLAG))
				{
					//disable hw nat
				#if defined(CONFIG_RTL_HARDWARE_NAT)
					gHwNatEnabled = 0;
					rtl865x_nat_reinit();
				#endif
				}
				rtl865x_HwQosProcess(dev, 0);
			}
		}
		
	}
	else if(flag ==1)
	{
		//enable
		rtl865x_HwQosProcess(dev, 1);
	#if defined(CONFIG_RTL_HARDWARE_NAT)	
		gHwNatEnabled = 1;
	#endif
	}
	else if(flag ==2)
	{
		//reinit hw qos
		rtl865x_HwQosProcess(dev, 1);
#if defined(CONFIG_RTL_HARDWARE_NAT)
		//reinit hw nat
		gHwNatEnabled = 0;
		rtl865x_nat_reinit();
#if !defined(CONFIG_RTK_VLAN_SUPPORT)
		rtl8651_setAsicOperationLayer(4);
#endif	
		gHwNatEnabled = 1;
#endif	
		
	}
	return ret;
}

/********************
	queue sync  hook
********************/

static u32
sm2m(u64 sm)
{
	u64 m;

	m = (sm * PSCHED_TICKS_PER_SEC) >> SM_SHIFT;
	return (u32)m;
}

/* convert dx (psched us) into d (us) */
static u32
dx2d(u64 dx)
{
	u64 d;

	d = dx * USEC_PER_SEC;
	do_div(d, PSCHED_TICKS_PER_SEC);
	return (u32)d;
}


int rtl_getSchNum(char* s)
{
	int type =0;
	if(!strcmp(s,"htb")) type=RTL_HTB_TYPE;
	if(!strcmp(s,"hfsc")) type=RTL_HFSC_TYPE;
	#if 0
	if(!strcmp(s,"cbq")) type=RTL_CBQ_TYPE;
	if(!strcmp(s,"tbf")) type=RTL_TBF_TYPE;
	if(!strcmp(s,"sfq")) type=RTL_SFQ_TYPE;
	if(!strcmp(s,"drr")) type=RTL_DRR_TYPE;
	if(!strcmp(s,"dsmark")) type=RTL_DSMARK_TYPE;
	#endif
	return type;
}

static int rtl_getClassPara(unsigned long cl1,struct Qdisc * sch,struct rtl_class_para * rtl_class_para)
{

	struct Qdisc_ops	*ops=NULL;
	char	id[IFNAMSIZ];
	int ret=0;
	int type;
	
	ops =sch->ops;
	if(ops==NULL)
	{
		ret=-EINVAL;
		goto out;
	}
	memcpy(id,ops->id,IFNAMSIZ);
	type=rtl_getSchNum(id);
	hwQosFlag&=(~RTL_HWQOS_SCH_FLAG)&RTL_HWQOS_FLAG_MASK;
	if((type!=RTL_HTB_TYPE)&&(type!=RTL_HFSC_TYPE))
	{
		//rtl hw qos support htb /hfsc
		hwQosFlag|=RTL_HWQOS_SCH_FLAG;
	}
	switch(type)
	{
		#if defined (CONFIG_NET_SCH_HTB)
		case RTL_HTB_TYPE:
			if(cl1&&rtl_class_para)
			{
				struct htb_class  * cl=  (struct htb_class  *)cl1;
				memset(rtl_class_para,0,sizeof(struct rtl_class_para));
				memcpy(&(rtl_class_para->common),&(cl->common),sizeof(struct Qdisc_class_common));
				rtl_class_para->type=RTL_HTB_TYPE;
				rtl_class_para->cl=cl1;
				rtl_class_para->prio=cl->prio;
				rtl_class_para->level=cl->level;
				rtl_class_para->maxlevel=TC_HTB_MAXDEPTH-1;
				{
					memcpy(&(rtl_class_para->ceil),&(cl->ceil),sizeof(struct psched_ratecfg));
					rtl_class_para->max_bw =cl->ceil.rate_bps>>3;
				}
				
				#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
				printk("rtl_class_para:%x,%x,[%s]:[%d].\n",cl->common.classid,cl->level,__FUNCTION__,__LINE__);
				#endif
				memcpy(&(rtl_class_para->rate),&(cl->rate),sizeof(struct psched_ratecfg));
				rtl_class_para->min_bw =cl->rate.rate_bps>>3;
				
				if(cl->parent)
					rtl_class_para->parent =(void*)(cl->parent);
				else
					rtl_class_para->parent =NULL;
				ret=1;
				
			}
			break;
		#endif
		#if defined (CONFIG_NET_SCH_HFSC)
		case RTL_HFSC_TYPE:
			if(cl1&&rtl_class_para)
			{
				struct hfsc_class  * cl=  (struct hfsc_class  *)cl1;
				struct hfsc_class  *parentcl=NULL;
				struct tc_service_curve tsc_rsc,tsc_fsc,tsc_usc;
				struct internal_sc *sc;
				
				memset(&tsc_rsc,0,sizeof(struct tc_service_curve));
				memset(&tsc_fsc,0,sizeof(struct tc_service_curve));
				memset(&tsc_usc,0,sizeof(struct tc_service_curve));
				
				memcpy(&(rtl_class_para->common),&(cl->cl_common),sizeof(struct Qdisc_class_common));
				rtl_class_para->type=RTL_HFSC_TYPE;
				rtl_class_para->cl_flags =cl->cl_flags;				
				rtl_class_para->cl=cl1;
				if((cl->cl_flags &( HFSC_USC|HFSC_FSC|HFSC_RSC))==0) 
				{
					rtl_class_para->min_bw =(1024)>>3; //min: 1kbps
					rtl_class_para->max_bw =(FULL_SPEED)>>3; //max: full speed
				}
				else
				{
					if(cl->cl_flags & HFSC_RSC)
					{
						sc=&(cl->cl_rsc);
						tsc_rsc.m1 = sm2m(sc->sm1);
						tsc_rsc.d  = dx2d(sc->dx);
						tsc_rsc.m2 = sm2m(sc->sm2);
					}
					if (cl->cl_flags & HFSC_FSC)
					{
						sc=&(cl->cl_fsc);
						tsc_fsc.m1 = sm2m(sc->sm1);
						tsc_fsc.d  = dx2d(sc->dx);
						tsc_fsc.m2 = sm2m(sc->sm2);
					}
					if (cl->cl_flags & HFSC_USC) 
			 		{
			 			sc=&(cl->cl_usc);
						tsc_usc.m1 = sm2m(sc->sm1);
						tsc_usc.d  = dx2d(sc->dx);
						tsc_usc.m2 = sm2m(sc->sm2);	
					}
					rtl_class_para->min_bw =tsc_fsc.m2;
					rtl_class_para->max_bw =tsc_usc.m2;
				}
				
				rtl_class_para->level=cl->level;
				rtl_class_para->maxlevel=0xff;
				if(cl->cl_parent){
					rtl_class_para->parent =(void *)(cl->cl_parent);
					parentcl =cl->cl_parent;
					
				#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
					printk("cl:%p,parent:%p,id:%x,level:%d,[%s]:[%d].\n",cl,cl->cl_parent ,cl->cl_parent->cl_common.classid,cl->cl_parent->level,__FUNCTION__,__LINE__);	
				#endif
				}	
				else{
				#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
					printk("----not have parent %p![%s]:[%d].\n",cl,__FUNCTION__,__LINE__);
				#endif
					rtl_class_para->parent =NULL;
				}	
				ret=1;
			}
			break;
			#endif
		default:
			#if defined (CONFIG_NET_SCH_HTB)
			//default htb
			if(cl1&&rtl_class_para)
			{
				struct htb_class  * cl=  (struct rtl_htb_class  *)cl1;
				
				memset(rtl_class_para,0,sizeof(struct rtl_class_para));
				memcpy(&(rtl_class_para->common),&(cl->common),sizeof(struct Qdisc_class_common));
				rtl_class_para->type=RTL_HTB_TYPE;
				rtl_class_para->cl=cl1;
				rtl_class_para->prio=cl->prio;
				rtl_class_para->level=cl->level;
				rtl_class_para->maxlevel=TC_HTB_MAXDEPTH-1;
				
				memcpy(&(rtl_class_para->ceil),&(cl->ceil),sizeof(struct psched_ratecfg));
				rtl_class_para->max_bw =cl->ceil.rate_bps>>3;
		
				memcpy(&(rtl_class_para->rate),&(cl->rate),sizeof(struct psched_ratecfg));
				rtl_class_para->min_bw =cl->rate.rate_bps>>3;
				
				if(cl->parent)
					rtl_class_para->parent =(void*)(cl->parent);
				else
					rtl_class_para->parent =NULL;
				ret=1;
				
				#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
				printk("ret:%d,rtl_class_para:%x,[%s]:[%d].\n",ret,cl->common.classid,__FUNCTION__,__LINE__);
				#endif
			}
			#endif	
			break;
				
	}

out:
	return ret;
}

int rtl_getdefClassId(struct Qdisc * sch)
{
	int classId=0;
	void *	defQ=NULL;
	struct Qdisc_ops	*ops=NULL;
	char			id[IFNAMSIZ];
	int defcls=0;
	int type;
	
	if(sch==NULL)
		goto out;
	defQ = qdisc_priv(sch);

	ops =sch->ops;
	if(ops==NULL)
	{
		goto out;
	}
	memcpy(id,ops->id,IFNAMSIZ);
	hwQosFlag&=(~RTL_HWQOS_SCH_FLAG)&RTL_HWQOS_FLAG_MASK;
	type=rtl_getSchNum(id);
	
	if((type!=RTL_HTB_TYPE)&&(type!=RTL_HFSC_TYPE))
	{
		//rtl hw qos support htb /hfsc
		hwQosFlag |=RTL_HWQOS_SCH_FLAG;
	}

	switch(type)
	{
		#if defined (CONFIG_NET_SCH_HTB)
		case RTL_HTB_TYPE:
			if(defQ)
			{
				struct htb_sched *dfltQ =NULL;
				dfltQ=(struct htb_sched *)defQ;
				defcls =dfltQ->defcls;
				classId=TC_H_MAKE(sch->handle,defcls);
				
			
			}
			break;	
		#endif	
		#if defined (CONFIG_NET_SCH_HFSC)
		case RTL_HFSC_TYPE:
			if(defQ)
			{
				struct hfsc_sched *dfltQ =NULL;
				dfltQ =(struct hfsc_sched *)defQ;
				defcls =dfltQ->defcls;
				classId=TC_H_MAKE(sch->handle,defcls);
			}
			break;	
		#endif	
		default:
			break;
	}
out:
	
	return classId;
}
int rtl_get_hfsc_class_leafbw(struct Qdisc *sch,struct hfsc_class *parent)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl;
	unsigned int i;
	struct tc_service_curve tsc_rsc,tsc_fsc,tsc_usc;
	struct internal_sc *sc;
	unsigned int max_bw=0;
	#if 0
	if(parent ==NULL)
		return 0;
	#endif
	for (i = 0; i < q->clhash.hashsize; i++) {
		hlist_for_each_entry(cl, &q->clhash.hash[i],
				     cl_common.hnode) {
				 
			if((cl->cl_parent==parent)&&(parent !=NULL))
			{
				memset(&tsc_rsc,0,sizeof(struct tc_service_curve));
				memset(&tsc_fsc,0,sizeof(struct tc_service_curve));
				memset(&tsc_usc,0,sizeof(struct tc_service_curve));
				if(cl->cl_flags & HFSC_RSC)
				{
					sc=&(cl->cl_rsc);
					tsc_rsc.m1 = sm2m(sc->sm1);
					tsc_rsc.d  = dx2d(sc->dx);
					tsc_rsc.m2 = sm2m(sc->sm2);
				}
				if (cl->cl_flags & HFSC_FSC)
				{
					sc=&(cl->cl_fsc);
					tsc_fsc.m1 = sm2m(sc->sm1);
					tsc_fsc.d  = dx2d(sc->dx);
					tsc_fsc.m2 = sm2m(sc->sm2);
				}
				if (cl->cl_flags & HFSC_USC) 
		 		{
		 			sc=&(cl->cl_usc);
					tsc_usc.m1 = sm2m(sc->sm1);
					tsc_usc.d  = dx2d(sc->dx);
					tsc_usc.m2 = sm2m(sc->sm2);	
				}
				
				max_bw +=tsc_usc.m2;
				
			}
			
		
		}
	}
	return max_bw;
}

static int rtl_syncHwQueue(struct net_device *dev)
{
	/*	Qdisc exist	*/
	struct Qdisc	*q;
	u32			queueNum;
	u32			topClassNum;
	u32			idx;
	u32 maxlevel=0;

	void *  cl=NULL;
	struct rtl_class_para rtl_class_para;
	struct rtl_class_para rtl_class_paraHandle[ TC_HTB_MAXDEPTH-1];

	rtl865x_qos_t		queueInfo[RTL8651_OUTPUTQUEUE_SIZE];

	u32				defClassId;
	u32 tmpBandwidth1, tmpBandwidth2;
	int				i;
	struct Qdisc		*sch=NULL;
	struct Qdisc_ops	*ops=NULL;
	struct Qdisc_class_ops	*cl_ops=NULL;
	
	int ret=0;
	
	memset(queueInfo, 0, RTL8651_OUTPUTQUEUE_SIZE*sizeof(rtl865x_qos_t));
	queueNum = topClassNum = 0;
	sch=netdev_get_tx_queue(dev, 0)->qdisc_sleeping;
	
	hwQosFlag&=(~RTL_HWQOS_QUEUEFLAG_MASK)&RTL_HWQOS_FLAG_MASK;
	defClassId=rtl_getdefClassId(sch);
#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
	printk("dev:%s,defClassId:%x,dev->num_tx_queues:%d .[%s]:[%d].\n",dev->name,defClassId,dev->num_tx_queues,__FUNCTION__,__LINE__);
#endif
	for (i = 0; i < dev->num_tx_queues; i++)
	{
		struct netdev_queue *txq = netdev_get_tx_queue(dev, i);
		struct Qdisc *txq_root = txq->qdisc_sleeping;
		spin_lock_bh(qdisc_lock(txq_root));
		list_for_each_entry(q, &txq_root->list, list)
		{
			if(q&&q->ops&&(strcmp(q->ops->id,"ingress")==0))
			{
				inhandle =q->handle;
				//printk("qid:%s,inhandle:%x,[%s]:[%d].\n",q->ops->id,inhandle,__FUNCTION__,__LINE__);
			}
			if (q&&q->parent)
			{
				sch=NULL;
				sch=netdev_get_tx_queue(dev, 0)->qdisc_sleeping;
				if(sch==NULL)
				{
					spin_unlock_bh(qdisc_lock(txq_root));
					return -EINVAL;
				}	
				
				ops =sch->ops;
				if(ops==NULL)
				{
					spin_unlock_bh(qdisc_lock(txq_root));
					return -EINVAL;
				}
				
				cl_ops=ops->cl_ops;
				if(cl_ops==NULL)
				{
					spin_unlock_bh(qdisc_lock(txq_root));
					return -EINVAL;
				}
				if(!cl_ops->get)
				{
					spin_unlock_bh(qdisc_lock(txq_root));
					return -EINVAL;
				}	
				memset(&rtl_class_para,0,sizeof(struct rtl_class_para));
				cl=NULL;
				cl =cl_ops->get(sch,q->parent);	
				if(!cl)
				{
					spin_unlock_bh(qdisc_lock(txq_root));
					return -EINVAL;
				}
				
				ret=rtl_getClassPara(cl,sch,&rtl_class_para);
				#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
				printk("[%d][%d],parent:%x,handle:%x,flags:%x,[%s]:[%d].\n",i,queueNum,q->parent,q->handle,q->flags,__FUNCTION__,__LINE__);
				#endif
				if(ret==-EINVAL)
				{
					spin_unlock_bh(qdisc_lock(txq_root));
					return -EINVAL;
				}
				{
					
					#if defined (CONFIG_RTL_HW_QOS_SP_PRIO)	
					queueInfo[queueNum].prio= rtl_class_para.prio;	
					#endif
					
					//byte->bps
					queueInfo[queueNum].bandwidth =rtl_class_para.min_bw<<3;
					queueInfo[queueNum].ceil = rtl_class_para.max_bw<<3;
					queueInfo[queueNum].handle = queueInfo[queueNum].queueId =rtl_class_para.common.classid;
					memcpy(queueInfo[queueNum].ifname, dev->name, sizeof(dev->name));
					#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
					printk("queueInfo[%d]:prio:%d,bw:%d,ceil:%d,handle:%x,dev:%s,[%s]:[%d].\n",queueNum,queueInfo[queueNum].prio,
						queueInfo[queueNum].bandwidth,queueInfo[queueNum].ceil,queueInfo[queueNum].handle,queueInfo[queueNum].ifname,__FUNCTION__,__LINE__);				
					#endif
					if (rtl_class_para.common.classid==defClassId)
						queueInfo[queueNum].flags |= QOS_DEF_QUEUE;
					else
						queueInfo[queueNum].flags &= (~QOS_DEF_QUEUE);

					if (queueInfo[queueNum].bandwidth==queueInfo[queueNum].ceil)
					{
						/*	Consider ceil==rate as as STR	*/
						queueInfo[queueNum].flags = (queueInfo[queueNum].flags & (~QOS_TYPE_MASK)) | QOS_TYPE_STR | QOS_VALID_MASK;
					}
					else
					{
						/*	Otherwise, set all queue as WFQ	*/
						queueInfo[queueNum].flags = (queueInfo[queueNum].flags & (~QOS_TYPE_MASK)) | QOS_TYPE_WFQ | QOS_VALID_MASK;
					}
				
					maxlevel =rtl_class_para.maxlevel;
					while(cl&&(rtl_class_para.level!=maxlevel)&&(rtl_class_para.parent !=NULL))
					{
						memset(&rtl_class_para,0,sizeof(struct rtl_class_para));
						rtl_class_para.parent=NULL;
						rtl_getClassPara(cl,sch,&rtl_class_para);
						if((rtl_class_para.parent ==NULL)||(rtl_class_para.level==maxlevel))
							break;
						cl = rtl_class_para.parent;
						
						#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
						printk("[%x],classinfo:id:%x,pri:%x,minbw:%d,maxbw:%d,level:%x,[%s]:[%d].\n",i,rtl_class_para.common.classid,rtl_class_para.prio,rtl_class_para.min_bw,rtl_class_para.max_bw,rtl_class_para.level,__FUNCTION__,__LINE__);
						#endif
					}
					
					if (cl&&( rtl_class_para.parent==NULL))
					{
						int	newRoot;
						newRoot = 1;
						
						#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
						printk("[%x],topClassNum:%d,classinfo:id:%x,pri:%x,minbw:%d,maxbw:%d,level:%x,,[%s]:[%d].\n",i,topClassNum,rtl_class_para.common.classid,rtl_class_para.prio,rtl_class_para.min_bw,rtl_class_para.max_bw,rtl_class_para.level,__FUNCTION__,__LINE__);
						#endif
						for(idx=0;idx<topClassNum;idx++)
						{
							if (rtl_class_paraHandle[idx].common.classid==rtl_class_para.common.classid)
							{
								
								#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
								printk("[%x],topClassNum:%d,classinfo:id:%x,pri:%x,minbw:%d,maxbw:%d,level:%x,,[%s]:[%d].\n",i,topClassNum,rtl_class_para.common.classid,rtl_class_para.prio,rtl_class_para.min_bw,rtl_class_para.max_bw,rtl_class_para.level,__FUNCTION__,__LINE__);
								#endif	
								newRoot = 0;
								break;
							}
						}

						if (newRoot)
						{

							memcpy(&rtl_class_paraHandle[topClassNum],&rtl_class_para,sizeof(struct rtl_class_para));
							
							#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
							printk("----[%x],topClassNum:%d,rootclassinfo:id:%x,pri:%x,minbw:%d,maxbw:%d,level:%x,[%s]:[%d].\n",i,topClassNum,rtl_class_para.common.classid,rtl_class_para.prio,rtl_class_para.min_bw,rtl_class_para.max_bw,rtl_class_para.level,__FUNCTION__,__LINE__);
							#endif	
							topClassNum++;
						}
					}
				}
				queueNum++;
			}
		}
		spin_unlock_bh(qdisc_lock(txq_root));
	}
	
#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
	printk("------dump queue info:topClassNum:%d[%s]:[%d]\n",topClassNum,__FUNCTION__,__LINE__);
	for(i=0;i<queueNum;i++)
	{
		printk("[%d]:queueinfo:flag:%x,pri%d,bw:%d,ceil:%d,handle:%x,dev:%s\n",i,queueInfo[i].flags,queueInfo[i].prio,
		queueInfo[i].bandwidth ,queueInfo[i].ceil,queueInfo[i].handle ,queueInfo[i].ifname);
	}
#endif	
	if(((queueNum>RTL_MAX_HWQUEUE_NUM)||(queueNum==0))||(topClassNum == 0))
	{
#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
		printk("-----close qos!queueNum:%d,topClassNum%d[%s]:[%d].\n",queueNum,topClassNum,__FUNCTION__,__LINE__);
#endif
		rtl865x_qosFlushBandwidth(dev->name);
		rtl865x_closeQos(dev->name);
		if((queueNum==0)||(topClassNum == 0))
			hwQosFlag|=RTL_HWQOS_NOQUEUE_FLAG;
		else
			hwQosFlag|=RTL_HWQOS_QUEUE_FLAG;

	}
	else
	{
		int32		i;
		int32		portBandwidth, tmpPortBandwidth;
		int32		totalRnum;
		int32		totalGbandwidth, totalRbandwidth, calcRbandwidth;
	#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
		printk("-----process qos![%s]:[%d].\n",__FUNCTION__,__LINE__);
	#endif
		portBandwidth = 0;
		int leafBandwidth=0;
		for(idx=0;idx<topClassNum;idx++)
		{
			{
				leafBandwidth =0;	
				
#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
				printk("----[%x],topClassNum:%d,type:%x,clflags:%x,rootclassinfo:id:%x,[%s]:[%d].\n",idx, topClassNum,
				rtl_class_paraHandle[idx].type,rtl_class_paraHandle[idx].cl_flags,rtl_class_paraHandle[idx].common.classid,__FUNCTION__,__LINE__);
#endif	
				if((rtl_class_paraHandle[idx].type==RTL_HFSC_TYPE)
				&&((rtl_class_paraHandle[idx].cl_flags &( HFSC_USC|HFSC_FSC|HFSC_RSC))==0))
				{
					leafBandwidth=rtl_get_hfsc_class_leafbw(sch,rtl_class_paraHandle[idx].cl);
 					portBandwidth+=(leafBandwidth<<3);
					
 				}
				else
					portBandwidth += (rtl_class_paraHandle[idx].max_bw<<3); //byte->bps
				
			}
		}

		/*	Do port bandwidth adjust here		*/
		tmpPortBandwidth = portBandwidth + (BANDWIDTH_GAP_FOR_PORT);
#if 0
		tmpPortBandwidth = portBandwidth<<3;
		tmpPortBandwidth += tmpPortBandwidth>>3;
		tmpPortBandwidth -= tmpPortBandwidth>>5;
		if (tmpPortBandwidth>0x200000)
			tmpPortBandwidth = ((tmpPortBandwidth/1000)<<10);
		else
			tmpPortBandwidth = ((tmpPortBandwidth<<10)/1000);
#endif

		/////////////////////////////////////////////////////////////////////////////
		//Patch for qos: to improve no-match rule throughput especially for low speed(~500kbps)
		//tmpPortBandwidth+=192000;	//Added 192kbps
		/////////////////////////////////////////////////////////////////////////////
		
		#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
		printk("dev:%s, bw:%d,[%s]:[%d].\n",dev->name,tmpPortBandwidth,__FUNCTION__,__LINE__);
		#endif
		if(portBandwidth<=FULL_SPEED)
			rtl865x_qosSetBandwidth(dev->name, tmpPortBandwidth);

		totalGbandwidth = totalRbandwidth = totalRnum = 0;

		/*	Check for G type queue's total bandwidth	*/
		for(i=0; i<queueNum; i++)
		{
			if((queueInfo[i].ceil==portBandwidth)
				&& queueInfo[i].bandwidth<queueInfo[i].ceil)	/* change bandwidth granulity from bps(bit/sec) to Bps(byte/sec) */
			{
				/*totalGbandwidth += ((queueInfo[i].bandwidth<<3)/1000)<<7;*/
				totalGbandwidth += ((queueInfo[i].bandwidth));
			}
			else if ((queueInfo[i].ceil<portBandwidth)
				)
			{
				/*totalRbandwidth += ((queueInfo[i].ceil<<3)/1000)<<7;*/
				totalRbandwidth += ((queueInfo[i].ceil));
				totalRnum++;

				tmpBandwidth1=queueInfo[i].ceil;
				tmpBandwidth2=(tmpBandwidth1>>13)<<13;
				if(tmpBandwidth1-tmpBandwidth2>(EGRESS_BANDWIDTH_GRANULARITY>>1))	// 4KByte which is 32kbit
				{
					queueInfo[i].bandwidth=((queueInfo[i].bandwidth>>13)+1)<<13;
					queueInfo[i].ceil=((queueInfo[i].ceil>>13)+1)<<13;
				}
				else
				{
					queueInfo[i].bandwidth=(queueInfo[i].bandwidth>>13)<<13;
					queueInfo[i].ceil=(queueInfo[i].ceil>>13)<<13;
				}
				
				if(queueInfo[i].bandwidth<EGRESS_BANDWIDTH_GRANULARITY)	/* 8K bytes == 64K bits	*/
					queueInfo[i].bandwidth=EGRESS_BANDWIDTH_GRANULARITY;
				
				if(queueInfo[i].ceil<EGRESS_BANDWIDTH_GRANULARITY)	/* 8K bytes == 64K bits	*/
					queueInfo[i].ceil=EGRESS_BANDWIDTH_GRANULARITY;
			}
			/*
			else
			{
				printk("Set output queue error: Queue bandwidth[%d]bps > Port bandwidth[%d]bps\n", 
					queueInfo[i].ceil, portBandwidth);
			}
			*/
		}

		if ( totalRbandwidth!=0 && ((totalGbandwidth+totalRbandwidth)>portBandwidth))
		{
			/*	Should reduce the R type bandwidth	*/
			calcRbandwidth = portBandwidth - totalGbandwidth;

#if 0
			for(i=0; i<queueNum; i++)
			{
				if (queueInfo[i].bandwidth==queueInfo[i].ceil)
				{
					queueInfo[i].ceil = queueInfo[i].bandwidth 
						= queueInfo[i].bandwidth - (totalRbandwidth-calcRbandwidth)/totalRnum;
				}
			}
#endif
		}

		for(i=0; i<queueNum; i++)
		{
			if (queueInfo[i].bandwidth!=queueInfo[i].ceil)
			{
				/*	Do queue bandwidth adjust here		*/
				queueInfo[i].ceil += queueInfo[i].ceil>>3;
				#if 0
				if (queueInfo[i].ceil>0x200000)
					queueInfo[i].ceil = ((queueInfo[i].ceil/1000)<<10);
				else
					queueInfo[i].ceil = ((queueInfo[i].ceil<<10)/1000);
				#endif
				if (queueInfo[i].ceil>FULL_SPEED)
					queueInfo[i].ceil = FULL_SPEED;
			}
			else
			{
				/*	str	*/
				#if 0
				if (queueInfo[i].ceil>1000000)
					queueInfo[i].ceil = queueInfo[i].bandwidth = (queueInfo[i].ceil/1000000)<<20;
				else if (queueInfo[i].ceil>1000)
					queueInfo[i].ceil = queueInfo[i].bandwidth = (queueInfo[i].ceil/1000)<<10;
				#endif
				if (queueInfo[i].ceil>FULL_SPEED)
					queueInfo[i].ceil = queueInfo[i].bandwidth = FULL_SPEED;
			}
		}
		
		#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
		printk("------process qos!dump queue info:[%s]:[%d]\n",__FUNCTION__,__LINE__);
		for(i=0;i<queueNum;i++)
		{
			printk("[%d]:queueinfo:flag:%x,pri%d,bw:%d,ceil:%d,handle:%x,dev:%s\n",i,queueInfo[i].flags,queueInfo[i].prio,
			queueInfo[i].bandwidth ,queueInfo[i].ceil,queueInfo[i].handle ,queueInfo[i].ifname);
		}
		#endif
		ret=rtl865x_qosProcessQueue(dev->name, queueInfo);
		#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
		printk("------ret:%d,dev:%s,[%s]:[%d]\n",ret,dev->name,__FUNCTION__,__LINE__);
		#endif
	}
	
	return 0;
}

 int tc_sync_hardware(struct net_device *dev)
{
	struct Qdisc_class_ops *cops;
	int ret =0;
		
	if((hwQosEnabled==0)||(qosEnabled==0))
		return ret;
	
	if (dev==NULL||netdev_get_tx_queue(dev,0)->qdisc_sleeping==NULL
		||netdev_get_tx_queue(dev,0)->qdisc_sleeping->ops==NULL)
		return -EINVAL;

	cops = netdev_get_tx_queue(dev,0)->qdisc_sleeping->ops->cl_ops;

	if (cops )
	{		
		ret =rtl_syncHwQueue(dev);
	}
	else
	{
		rtl865x_qosFlushBandwidth(dev->name);
		ret=rtl865x_closeQos(dev->name);
	}

	return ret;
}

int rtl_hwQosSyncQueueHook(struct net_device *dev)
{
	int ret=0;
	
	rtl865x_qosFlushBandwidth(dev->name);
	rtl865x_closeQos(dev->name);
	if((hwQosEnabled==0)||(qosEnabled==0))
		return ret;
	else
	{
		ret=tc_sync_hardware(dev);
	}	

	return ret;
}

/********************
	filter sync hook
********************/
int rtl_hwQos_mark_classidMapHook(struct net_device *dev,struct tcf_proto *tp)
{
	struct fw_head *head;
	struct fw_filter *f;
	int h=0;
	int mark;
	int handle;
	int mask=0xFFFF;
	if (tp)
	{
		#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
		printk("tpinfo:%s,%x,%x,[%s]:[%d].\n",tp->ops->kind,tp->classid,tp->prio,__FUNCTION__,__LINE__);
		#endif
		head = (struct fw_head*)(tp->root);
		if (head != NULL) {
			mask=head->mask;
			for (h = 0; h < HTSIZE; h++) {
		
				for (f = head->ht[h]; f; f = f->next)
				{
				 	mark =f->id;
					handle=f->res.classid;
					#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
					printk("mark:%x/%x,handle:%x,[%s]:[%d].\n",mark,mask,handle,__FUNCTION__,__LINE__);
					#endif
					rtl_qosSetPriorityByMark(dev->name, mark, handle, mask,TRUE);
				}
			}
		} 
	
	}
	return 0;
}

int rtl_hwQosSyncFilterHook(struct net_device *dev, unsigned int parent)
{

	int ret =0;
	int swQosFlag=0;
	u32 id;
	int h=0,t=0;
	struct tcf_result *res;
	struct Qdisc  *q;
	unsigned long cl=0;
	struct tcf_proto  **chain;
	struct tcf_proto *tp;
	struct netdev_queue *dev_queue;
	struct Qdisc_class_ops *cops;
	
	if (dev == NULL){
		ret= -ENODEV;
		goto out;
	}
	if((hwQosEnabled==0)||(qosEnabled==0))
	{
		//swQosFlag=1;
		goto out;
	}
	if(strncmp(dev->name,"ifb",3)==0)
	{
		goto out;
	}
	
#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
	printk("dev->name:%s,%x[%s]:[%d]\n",dev->name,parent,__FUNCTION__,__LINE__);
#endif
	hwQosFlag=hwQosFlag &(~RTL_HWQOS_FILTER_FLAG)&RTL_HWQOS_FLAG_MASK;
	
	dev_queue = netdev_get_tx_queue(dev, 0);
	if(!parent){
		q = dev_queue->qdisc_sleeping;
		parent = q->handle;
	}
	else
	{
		q = qdisc_lookup(dev, TC_H_MAJ(parent));	
	}
	if (q == NULL){
		ret= -EINVAL;
		goto out;
	}	
	/* Is it classful? */
	if ((cops = q->ops->cl_ops) == NULL){
		ret= -EINVAL;
		goto out;
	}
	/* Do we search for filter, attached to class? */
	if (TC_H_MIN(parent)) {
		cl = cops->get(q, parent);
		if (cl == 0){
			ret=-ENOENT;
			goto out;
		}
	}
	/* And the last stroke */
	chain = cops->tcf_chain(q, cl);
	if (chain == NULL)
	{
		ret=-EINVAL;
		goto out;
	}

#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
	printk("dev->name:%s,%x[%s]:[%d]\n",dev->name,parent,__FUNCTION__,__LINE__);
#endif	
	rtl_qosSetPriorityByMark(dev->name, 0, 0,0,RTL_MARK2PRIO_FLUSH_FLAG);
	for (tp=*chain, t=0; tp; tp = tp->next, t++)
	{
		if (tp)
		{
			if(tp->ops&&strcmp(tp->ops->kind,"fw"))
			{
				//not fw filter disable hw qos 
				#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
				printk("dev:%s,[%d],tp->ops->kind:%s,parent:%x,inhandle:%x, [%s]:[%d].\n",dev->name,t,tp->ops->kind,parent,inhandle,__FUNCTION__,__LINE__);
				#endif
				if((inhandle&&parent!=inhandle)||inhandle==0)
				{
					hwQosFlag |=RTL_HWQOS_FILTER_FLAG;
					continue;
				}
			}
			else
			{
				#if defined (CONFIG_NET_CLS_FW)
				rtl_hwQos_mark_classidMapHook(dev,tp);
				#endif
			}
		}
		else
		{
			printk("==========NULL!t:%d [%s]:[%d].\n",t,__FUNCTION__,__LINE__);
			break;
		}
	}
out:		
	
#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
	printk("ret:%d,%x[%s]:[%d]\n",ret,parent,__FUNCTION__,__LINE__);
#endif
	return ret; 
}

int rtl_hwQosSyncTcHook(struct net_device *dev, struct Qdisc  *q,unsigned int parent)
{

	int ret =0;
	int swQosFlag=0;
	u32 id;
	int h=0,t=0;
	struct tcf_result *res;
	unsigned long cl=0;
	struct tcf_proto  **chain;
	struct tcf_proto *tp;
	struct netdev_queue *dev_queue;
	struct Qdisc_class_ops *cops;
	
	if (dev == NULL){
		ret= -ENODEV;
		goto out;
	}
	if((hwQosEnabled==0)||(qosEnabled==0))
	{
		//swQosFlag=1;
		goto out;
	}
	if(strncmp(dev->name,"ifb",3)==0)
	{
		goto out;
	}
	if(q&&(q->ops))
	{
		inhandle=0;
		if(strcmp(q->ops->id,"ingress")==0){
			inhandle =q->handle;
			#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
			printk("----------qid:%s,inhandle:%x,[%s]:[%d].\n",q->ops->id,inhandle,__FUNCTION__,__LINE__);
			#endif
			goto out;
		}
	}
	if(inhandle&&(parent==inhandle))
	{
		goto out;
	}
	
	hwQosFlag=hwQosFlag &(~RTL_HWQOS_TCFLAG_MASK)&RTL_HWQOS_FLAG_MASK;
	rtl_hwQosHwNatProcess(dev, 2);
	dev_queue = netdev_get_tx_queue(dev, 0);
	#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
	printk("--------dev->name:%s,parent:%x,[%s]:[%d]\n",dev->name,parent,__FUNCTION__,__LINE__);
	#endif
	ret =rtl_hwQosSyncQueueHook(dev);
	if(ret<0)
	{
		goto out;
	}

	rtl_hwQosSyncFilterHook(dev, parent);
	
	rtl_hwQosHwNatProcess(dev, 0);
out:	
	
	#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
	printk("ret:%d,%x[%s]:[%d]\n",ret,parent,__FUNCTION__,__LINE__);
	#endif
	return ret;	
}


/*******************
	iptables hook
*******************/

#if 1//defined (CONFIG_IP_NF_IPTABLES)
#define RTL_QOS_IPTABLES_CHAINNAME		"qos"
#define RTL_QOS_IPTABLES_CHAINNUM		10
#define RTL_QOS_MAX_IGNORE_MATCH_NUM	16
#define RTL_QOS_IPTABLES_IGNORE_ADD		0x1
#define RTL_QOS_IPTABLES_IGNORE_DEL		0x2
#define RTL_QOS_IPTABLES_IGNORE_FLUSH		0x3
#define RTL_QOS_IPTABLES_IGNORE_SHOW		0x4

struct rtl_ignore_mach
{
	unsigned char matchinfo[16];
	unsigned char vaild;
};
struct rtl_ignore_mach ignore_info[RTL_QOS_MAX_IGNORE_MATCH_NUM];
int rtl_ProcessHwQosIptablesIgnoreInfo(unsigned char *matchinfo, int flag)
{
	int i=0;
	int ret=0;
	
	if(flag==RTL_QOS_IPTABLES_IGNORE_FLUSH)
	{
		for(i=0;i<RTL_QOS_MAX_IGNORE_MATCH_NUM;i++)
		{
			memset(&(ignore_info[i]),0,sizeof(struct rtl_ignore_mach));
		}
		ret=1;
	}
	else if(flag==RTL_QOS_IPTABLES_IGNORE_SHOW)
	{
		for(i=0;i<RTL_QOS_MAX_IGNORE_MATCH_NUM;i++)
		{
			if(ignore_info[i].vaild)
			{
				printk("[%d] matchinfo:%s\n",i,ignore_info[i].matchinfo);
			}
		}
		ret=1;
	}
	if(matchinfo)
	{
		
		if(flag==RTL_QOS_IPTABLES_IGNORE_ADD){
			for(i=0;i<RTL_QOS_MAX_IGNORE_MATCH_NUM;i++)
			{
				if(ignore_info[i].vaild==0)
				{
					strcpy(ignore_info[i].matchinfo,matchinfo);
					ignore_info[i].vaild =1;
					ret =1;
					break;
				}
			}
		}
		else if(flag==RTL_QOS_IPTABLES_IGNORE_DEL)
		{
			
			for(i=0;i<RTL_QOS_MAX_IGNORE_MATCH_NUM;i++)
			{
				if((ignore_info[i].vaild)&&(strcmp(ignore_info[i].matchinfo,matchinfo)==0))
				{
					ignore_info[i].vaild=0;
					memset(&(ignore_info[i]),0,sizeof(struct rtl_ignore_mach));
					ret =1;
					break;
				}
			}
		}
			
		
	}
	return ret;
}
int rtl_HwQosIptablesIgnoreInfoInit(void)
{
	unsigned char matchInfo1[16];
	unsigned char *matchInfo=matchInfo1;
	int ret=0;
	rtl_ProcessHwQosIptablesIgnoreInfo(NULL, RTL_QOS_IPTABLES_IGNORE_FLUSH);
	
	rtl_ProcessHwQosIptablesIgnoreInfo("udp", RTL_QOS_IPTABLES_IGNORE_ADD);
	rtl_ProcessHwQosIptablesIgnoreInfo("tcp", RTL_QOS_IPTABLES_IGNORE_ADD);
	rtl_ProcessHwQosIptablesIgnoreInfo("multiport", RTL_QOS_IPTABLES_IGNORE_ADD);
	rtl_ProcessHwQosIptablesIgnoreInfo("mark", RTL_QOS_IPTABLES_IGNORE_ADD);
	rtl_ProcessHwQosIptablesIgnoreInfo("comment", RTL_QOS_IPTABLES_IGNORE_ADD);
	rtl_ProcessHwQosIptablesIgnoreInfo("length", RTL_QOS_IPTABLES_IGNORE_ADD);
	
	return ret;
}

int rtl_process_iptablesMatchInfo(struct xt_match *match)
{
	int ret=1;
	int i=0;
	
	if (match)
	{
		for(i=0;i<RTL_QOS_MAX_IGNORE_MATCH_NUM;i++)
		{
			if((ignore_info[i].vaild)&&(strcmp(ignore_info[i].matchinfo,match->name)==0))
			{
				ret=0;
				break;
			}
		}
	}
	return ret;
}
int rtl_hwQosIptables_Hook(struct xt_table * table)
{
	 if((table==NULL)||strcmp(table->name,"mangle"))
		return 0;
	 
	rtl_update_hooktime(table);
	return 1;
}
int  rtl_hwQosIptables_HookProcess(struct xt_table * table)	
{
	int total_size=0;
	int cpu;
	int ret=0;
	int qosFlag =0;
	void * table_base;
	int swQosFlag=0;
	int index=0;
	int i;
	
	 if((table==NULL)||strcmp(table->name,"mangle")||(hwQosEnabled==0))
		return 0;
	if (!IS_ERR_OR_NULL(table)) {
		const struct xt_table_info *private = table->private;
		
		{
		unsigned int off, num;
		const struct ipt_entry *e,*e_qos=NULL;		
		struct ipt_entry *e_jump[RTL_QOS_IPTABLES_CHAINNUM]={0};
		const struct xt_entry_target *t_jump=NULL;
		int rulenum = 0;
		const void *loc_cpu_entry;
		u8 flags;
		
		/* choose the copy that is on our node/cpu, ...
		 * This choice is lazy (because current thread is
		 * allowed to migrate to another cpu)
		 */
		 if(private==NULL)
			return 0;
		
		loc_cpu_entry = private->entries[raw_smp_processor_id()];

		table_base =loc_cpu_entry;
		total_size=private->size;
		#if 0//defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
		printk("t->private->number = %u, tablebase:%p,total_size:%d\n", private->number,loc_cpu_entry,total_size);
		#endif
		/* ... then go back and fix counters and names */
		//for (off = 0, num = 0; off < total_size; off += e->next_offset, num++)
		xt_entry_foreach(e, loc_cpu_entry, total_size)
		{
			unsigned int qos_num=0;
			const struct xt_entry_match *m_qos=NULL;
			const struct xt_entry_target *t=NULL,*t_qos=NULL;
			int v=0;
			rulenum++;
			//e = (struct ipt_entry *)(loc_cpu_entry + off);
			
			//printk("[%d],e:%p, [%s]:[%d].\n",rulenum,e,__FUNCTION__,__LINE__);
			flags = e->ip.flags & IPT_F_MASK;
			t = ipt_get_target(e);
		
			if(t==NULL){
				continue;
			}
			if(!t->u.kernel.target){
				continue;
			}	
		
			if (strcmp(t->u.user.name, XT_STANDARD_TARGET) == 0)
			{
				v = ((struct xt_standard_target *)t)->verdict;
				if(v == XT_RETURN)
				{
					qosFlag=0;
				}
				else
				{
					e_jump[index]=(struct ipt_entry *)(table_base + v);
					if(e_jump[index]&&(e_jump[index]<loc_cpu_entry+total_size))
					{
						if(index<RTL_QOS_IPTABLES_CHAINNUM)
							index++;
					}
				
				}
			}
		#if 1
			//if (strcmp(t->u.kernel.target->name, XT_ERROR_TARGET) == 0)
			{

				if(strncmp(t->data, RTL_QOS_IPTABLES_CHAINNAME,3) == 0)
				{
					#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
					printk("[%d],e:%p, data:%s,[%s]:[%d].\n",rulenum,e,t->data,__FUNCTION__,__LINE__);
					#endif
					for(i=0;i<index;i++)
					{
						if(( (struct ipt_entry *)((void *)e + e->next_offset))==e_jump[i])
						{
							qosFlag=1;
							#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
							printk("----------qosFlag is set![%d],e:%p, data:%s,[%s]:[%d].\n",rulenum,e,t->data,__FUNCTION__,__LINE__);
							#endif
							break;
							
						}
					}
					
				}
			}
		#endif
			if(qosFlag)
			{
			
				e_qos = (struct ipt_entry *)((void *)e + e->next_offset);
				while(e_qos&&(e_qos<loc_cpu_entry+total_size))
				{
					qos_num++;
					t_qos = ipt_get_target(e_qos);

				#if 0//defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
					printk("[%d][%d],e:%p, t:%s,data:%s ,flag:%x,%s,match: proto:%d,outif:%s[%s]:[%d].\n",rulenum,qos_num,e_qos,t_qos->u.user.name
					,t_qos->data,flags,t_qos->u.kernel.target->name,e_qos->ip.proto,e_qos->ip.outiface,__FUNCTION__,__LINE__);
				#endif
					//IP_NF_ASSERT(t_qos->u.kernel.target);
					if (strcmp(t_qos->u.user.name, XT_STANDARD_TARGET) == 0)
					{
						v = ((struct xt_standard_target *)t_qos)->verdict;
						if(v == XT_RETURN)
						{
							qosFlag=0;
							#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
							printk("[%d][%d],[%s]:[%d]",rulenum,qos_num,__FUNCTION__,__LINE__);
							#endif
							break;
						}
					}
					xt_ematch_foreach(m_qos, e_qos) {
						if(m_qos->u.kernel.match){
							swQosFlag=rtl_process_iptablesMatchInfo(m_qos->u.kernel.match);
							if(swQosFlag)
							{
								ret=1;
								#if defined (CONFIG_RTL_HW_QOS_SUPPORT_DEBUG)
								printk("[%d][%d]swQosFlag:%d,match info:%s,[%s]:[%d]\n",rulenum,qos_num,swQosFlag,m_qos->u.kernel.match->name,__FUNCTION__,__LINE__);
								#endif
								hwQosFlag |=RTL_HWQOS_IPTABLES_FLAG;
								goto out;
							}
						}
					}
				
					e_qos = (struct ipt_entry *)((void *)e_qos + e_qos->next_offset);
				}
			}
				
			
		}

		}
		
	out:	
		rtl_hwQosHwNatProcess(NULL, 0);	
	}
	
	return swQosFlag;	
}

EXPORT_SYMBOL(rtl_hwQosIptables_Hook);

#endif
/*******************
	init hook
*******************/

#if defined(CONFIG_PROC_FS)

static struct proc_dir_entry *proc_rtl_qos=NULL;

static int rtl_qos_proc_read(struct seq_file *s, void *v)
{
	seq_printf(s, "Qos:%d\n",qosEnabled);
	seq_printf(s, "hwQos:%d\n\n",hwQosEnabled);

	return 0;
}

static int32 rtl_qos_proc_write(struct file *file, const char *buffer,
		      unsigned long len, void *data)

{
	char tmpBuf[32];
	char		*strptr;
	char 		*cmd_addr;
	char 		*tmp;
	int value=0;
	int qosOld,hwQosOld;
	if(len>32)
	{
		goto errout;
	}

	if (buffer && !copy_from_user(tmpBuf, buffer, len)) {
		tmpBuf[len-1] = '\0';
		strptr=tmpBuf;
		cmd_addr = strsep(&strptr," ");
		if (cmd_addr==NULL)
		{
			goto errout;
		}

		if(strncmp(cmd_addr, "qos",3) == 0)
		{
			cmd_addr = strsep(&strptr," ");
			if (cmd_addr==NULL)
			{
				goto errout;
			}
			value = simple_strtol(cmd_addr, NULL, 0);
			if(value)
				qosEnabled =1;
			else
				qosEnabled =0;

		}
		else if(strncmp(cmd_addr, "hwqos",5) == 0)
		{
			cmd_addr = strsep(&strptr," ");
			if (cmd_addr==NULL)
			{
				goto errout;
			}
			value = simple_strtol(cmd_addr, NULL, 0);
			if(value)
				hwQosEnabled =1;
			else
				hwQosEnabled =0;

		}
		else if(strncmp(cmd_addr, "hwflag",6) == 0)
		{
			cmd_addr = strsep(&strptr," ");
			if (cmd_addr==NULL)
			{
				goto errout;
			}
			value = simple_strtol(cmd_addr, NULL, 0);
			if(value)
				hwQosFlag=value;
			else
				hwQosFlag =0;

		}
		
		else if(strncmp(cmd_addr, "iptables",8) == 0)
		{
			cmd_addr = strsep(&strptr," ");
			if (cmd_addr==NULL)
			{
				goto errout;
			}
			//printk("cmd_addr:%s,[%s]:[%d]\n",cmd_addr,__FUNCTION__,__LINE__);
			if(strncmp(cmd_addr, "add",3) == 0)
			{
				cmd_addr = strsep(&strptr," ");
				if (cmd_addr==NULL)
				{
					goto errout;
				}
				rtl_ProcessHwQosIptablesIgnoreInfo(cmd_addr,RTL_QOS_IPTABLES_IGNORE_ADD);
				
			}
			else if(strncmp(cmd_addr, "del",3) == 0)
			{
				cmd_addr = strsep(&strptr," ");
				if (cmd_addr==NULL)
				{
					goto errout;
				}
				rtl_ProcessHwQosIptablesIgnoreInfo(cmd_addr,RTL_QOS_IPTABLES_IGNORE_DEL);
				
			}
			else if(strncmp(cmd_addr, "flush",3) == 0)
			{
				rtl_ProcessHwQosIptablesIgnoreInfo(NULL,RTL_QOS_IPTABLES_IGNORE_FLUSH);
			}
			else if(strncmp(cmd_addr, "show",3) == 0)
			{
				rtl_ProcessHwQosIptablesIgnoreInfo(NULL,RTL_QOS_IPTABLES_IGNORE_SHOW);
			}
			
		}
	
		
		if((hwQosEnabled==0)||(qosEnabled==0))
		{
			rtl_hwQosHwNatProcess(NULL, 0);
		}
		

	}
	else
	{
errout:
			printk("error input\n");
	}
	return len;
}

int rtl_qos_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, rtl_qos_proc_read, NULL));
}
static ssize_t rtl_qos_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	    return rtl_qos_proc_write(file, userbuf,count, off);
}

static const struct file_operations rtl_qos_fops = {
	.owner = THIS_MODULE,
	.open = rtl_qos_single_open,
	.write = rtl_qos_single_write,
	.read  = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

#endif

int rtl_qos_initHook(void)
{
	#if defined(CONFIG_PROC_FS)
	proc_rtl_qos = proc_create_data("rtl_qos", 0, &proc_root,&rtl_qos_fops, NULL);
	#endif
	rtl_qosTimerInit();
	rtl_HwQosIptablesIgnoreInfoInit();
	return 0;
}

int rtl_qos_cleanupHook(void)
{
	
#if defined(CONFIG_PROC_FS)
	if(proc_rtl_qos)
		remove_proc_entry("rtl_qos", proc_rtl_qos);
			
#endif		
	rtl_qosTimerDestroy();
	rtl_ProcessHwQosIptablesIgnoreInfo(NULL, RTL_QOS_IPTABLES_IGNORE_FLUSH);
	return 0;
}

static void rtl_update_hooktime(struct xt_table * table)
{
	iptables_hook_info.table=table;
	iptables_hook_info.last_hook_time =jiffies;
	return ;
}
static void rtl_qosTimerMod(void)
{
	mod_timer(&rtlQosTimer, jiffies + HZ);
	return ;
}
static void rtl_qosTimerDestroy(void)
{
	del_timer(&rtlQosTimer);
	return ;
}
extern void rtl_watchdog_stop(void);
extern void rtl_watchdog_resume(void);

static void rtl_hwQosSyncCallback(void)
{
	int i=0;
	unsigned long current_time =jiffies;
	if(iptables_hook_info.last_hook_time&&(time_before_eq((iptables_hook_info.last_hook_time+RTL_DELAY_PROCESS_TIME*HZ),  current_time)))
	{
		//printk("----iptables hook porocess last_hook_time:%llu,jiffies:%llu\n",iptables_hook_info.last_hook_time,current_time);
		iptables_hook_info.last_hook_time=0;	
		rtl_watchdog_stop();
		rtl_hwQosIptables_HookProcess( iptables_hook_info.table);
		rtl_watchdog_resume();
	}
	
#if defined (CONFIG_RTL_QOS_SYNC_SUPPORT)
	for (i=0;i<RTL_MAX_QOSCONFIG_DEV_NUM;i++)
	{
		if(qosConf[i].valid&&qosConf[i].enable)
		{
			if(qosConf[i].last_hook_time&&(time_before_eq(qosConf[i].last_hook_time+RTL_DELAY_PROCESS_TIME*HZ,  current_time)))
			{
				//printk("[%d],dev:%s,last_hook_time:%llu,jiffies:%llu.\n",i,qosConf[i].dev->name,qosConf[i].last_hook_time,current_time);
				rtl_watchdog_stop();
				qosConf[i].last_hook_time=0;
				rtl_hwQosSyncTcHook(qosConf[i].dev, NULL,0);
				rtl_watchdog_resume();
			}
		}
	}
#endif
	
	rtl_qosTimerMod();
	return;
}


static void rtl_qosTimerInit(void)
{
	init_timer(&rtlQosTimer);
	rtlQosTimer.data=rtlQosTimer.expires;
	rtlQosTimer.expires=jiffies+HZ;
	rtlQosTimer.function=(void*)rtl_hwQosSyncCallback;
	add_timer(&rtlQosTimer);
	return ;
}


#endif
#if defined(CONFIG_RTL_QOS_SYNC_SUPPORT)
void rtl_set_dev_qos_config(struct net_device *dev,int enable)
{
	int i=0;
	int index =-1;
	int find =0;
	int enabedCnt=0;

	for (i=0;i<RTL_MAX_QOSCONFIG_DEV_NUM;i++)
	{
		if((qosConf[i].valid==0)&&(index==-1))
		{
			index =i;
		}
		if(qosConf[i].valid  )
		{
			if(qosConf[i].dev==dev){
				qosConf[i].enable =enable;
				qosConf[i].last_hook_time =jiffies;
				//printk("rtl_set_dev_qos_config 1 dev:%s,last_hook_time:%lu\n",qosConf[i].dev->name,qosConf[i].last_hook_time);
				find =1;
			}
			
			if(qosConf[i].enable){
				enabedCnt ++;
			}	
		}
	}

	if((index !=-1)&&(find==0))
	{
		qosConf[index].valid=1;
		qosConf[index].enable =enable;
		qosConf[index].dev =dev;
		qosConf[index].last_hook_time =jiffies;
		//printk("rtl_set_dev_qos_config 2 dev:%s,last_hook_time:%lu\n",qosConf[index].dev->name,qosConf[index].last_hook_time);
		if((qosConf[index].enable)&&(qosConf[index].valid))
		{
			enabedCnt ++;
		}	
		
	}
	if(enabedCnt)
		gQosEnabled =1;
	else
		gQosEnabled =0;
	
	return ;
}

void rtl_clear_dev_qos_config(void)
{
	memset(qosConf,0,RTL_MAX_QOSCONFIG_DEV_NUM*sizeof(struct qos_conf));
	return;
}

void rtl_dump_dev_qos_config(void)
{
	int i=0;
	for (i=0;i<RTL_MAX_QOSCONFIG_DEV_NUM;i++)
	{
		
		if(qosConf[i].valid  )
		{
			printk("[%d] dev:%s enable:%d\n",i,qosConf[i].dev->name,qosConf[i].enable);
		}
	}
	return;
}

int rtl_QosSyncTcHook(struct net_device *dev, struct Qdisc  *q,unsigned int parent,int process)
{

	int ret =0;
	int swQosFlag=0;
	u32 id;
	int h=0,t=0;
	struct tcf_result *res;
	unsigned long cl=0;
	struct tcf_proto  **chain;
	struct tcf_proto *tp;
	struct netdev_queue *dev_queue;
	struct Qdisc_class_ops *cops;
	
	if (dev == NULL){
		ret= -ENODEV;
		return ret;
	}
	
	//to do: sync ifb for  ingress qos 
	if(strncmp(dev->name,"ifb",3)==0)
	{
		return ret;
	}
	
#if !defined (CONFIG_RTL_HW_QOS_SUPPORT)	
	if(process&RTL_QOS_QUEUE_HOOK)
#endif		
	{
		if(dev->num_tx_queues)
		{
			struct netdev_queue *txq = netdev_get_tx_queue(dev, 0);
			struct Qdisc *q, *sub_q;
			int qosEnable=0;
			q =txq->qdisc;
			if (q&&(q->enqueue)){
			   struct Qdisc *txq_root = txq->qdisc_sleeping;
			   spin_lock_bh(qdisc_lock(txq_root));
				list_for_each_entry(sub_q, &txq_root->list, list)
				{
					if(sub_q->parent)
						qosEnable=1;
				}
				spin_unlock_bh(qdisc_lock(txq_root));
                
				rtl_set_dev_qos_config(dev,qosEnable);
			}
			else
			{
				rtl_set_dev_qos_config(dev,0);
			}
		}
		else
		{
			rtl_set_dev_qos_config(dev,0);
		}
	}

	return ret;	
}	
#endif
#if defined (CONFIG_RTL_HARDWARE_NAT)
extern int rtl_del_ps_drv_netif_mapping(struct net_device *dev);
extern int32 rtl865x_addPpp(uint8 *ifname, ether_addr_t *mac, uint32 sessionId, int32 type);
extern int rtl_add_ps_drv_netif_mapping(struct net_device *dev, const char *name);
extern int32 rtl865x_delPppbyIfName(char *name);
#if ! defined (CONFIG_RTL_HW_QOS_SUPPORT)

extern int32 rtl865x_detachMasterNetif(char *slave);
extern int32 rtl865x_attachMasterNetif(char *slave, char *master);
extern int  rtl865x_add_pattern_acl_for_contentFilter(rtl865x_AclRule_t *rule,char *netifName);
extern int  rtl865x_del_pattern_acl_for_contentFilter(rtl865x_AclRule_t *rule,char *netifName);
#endif
extern ps_drv_netif_mapping_t * rtl_get_ps_drv_netif_mapping_by_psdev(struct net_device *dev);
EXPORT_SYMBOL(rtl_del_ps_drv_netif_mapping);
EXPORT_SYMBOL(rtl865x_addPpp);
EXPORT_SYMBOL(rtl_add_ps_drv_netif_mapping);
EXPORT_SYMBOL(rtl865x_delPppbyIfName);
EXPORT_SYMBOL(rtl865x_detachMasterNetif);
EXPORT_SYMBOL(rtl865x_attachMasterNetif);
EXPORT_SYMBOL(rtl865x_add_pattern_acl_for_contentFilter);
EXPORT_SYMBOL(rtl865x_del_pattern_acl_for_contentFilter);
EXPORT_SYMBOL(rtl_get_ps_drv_netif_mapping_by_psdev);
#endif

#if defined (CONFIG_RTL_IGMP_SNOOPING)

/*querier select*/
#if defined (CONFIG_RTL_QUERIER_SELECTION)

int br_initQuerierInfo(void)
{
	memset(querierInfoList, 0, sizeof(querierInfoList));
	return 0;
}

int br_updateQuerierInfo(unsigned int version, unsigned char *devName, unsigned int* querierIp)
{
	int i;
	unsigned long oldestJiffies;
	unsigned long oldestIdx=0;
	
	if(querierIp==NULL)
	{
		return -1;	
	}
	
	if((version!=4) && (version!=6))
	{
		return -1;	
	}
	
	/*find matched one*/
	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if((querierInfoList[i].version==version))
		{
			if( (version==4) && (querierInfoList[i].querierIp[0]==querierIp[0]))
			{
				strcpy(querierInfoList[i].devName,devName);
				querierInfoList[i].lastJiffies=jiffies;
				return 0;
	
			}

			if((version ==6) && (memcmp(querierInfoList[i].querierIp, querierIp, 16) ==0)) 
			{
				strcpy(querierInfoList[i].devName,devName);
				querierInfoList[i].lastJiffies=jiffies;
				return 0;
			}
		}
	
	}
	
	/*no matched one, find an empty one*/
	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if(querierInfoList[i].version==0)
		{
			querierInfoList[i].version=version;
			if(version==4)
			{
				querierInfoList[i].querierIp[0]=querierIp[0];
			}
			else if (version ==6)
			{
				memcpy(querierInfoList[i].querierIp, querierIp, 16);
			}
			strcpy(querierInfoList[i].devName,devName);
			querierInfoList[i].lastJiffies=jiffies;
			
			return 0;
		}
	}
	
	/*all entries are used, find oldest one*/
	oldestJiffies=querierInfoList[0].lastJiffies;
	oldestIdx=0;
	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if(time_before((unsigned long)(querierInfoList[i].lastJiffies),oldestJiffies))
		{
			oldestJiffies=querierInfoList[i].lastJiffies;
			oldestIdx=i;
		}
	}
	
	querierInfoList[oldestIdx].version=version;
	if(version==4)
	{
		querierInfoList[oldestIdx].querierIp[0]=querierIp[0];
	}
	else if (version ==6)
	{
		memcpy(querierInfoList[oldestIdx].querierIp, querierIp, 16);
	}
	
	strcpy(querierInfoList[oldestIdx].devName,devName);
	querierInfoList[oldestIdx].lastJiffies=jiffies;
	
	return 0;

	
}

int check_igmpQueryExist(struct iphdr * iph)
{

	if(iph==NULL)
	{
		return 0;
	}

	if(*(unsigned char *)((unsigned char*)iph+((iph->ihl)<<2))==0x11)
	{
		return 1;
	}
	
	return 0;
}



int check_mldQueryExist(struct ipv6hdr* ipv6h)
{

	unsigned char *ptr=NULL;
	unsigned char *startPtr=NULL;
	unsigned char *lastPtr=NULL;
	unsigned char nextHeader=0;
	unsigned short extensionHdrLen=0;

	unsigned char  optionDataLen=0;
	unsigned char  optionType=0;
	unsigned int ipv6RAO=0;

	if(ipv6h==NULL)
	{
		return 0;
	}

	if(ipv6h->version!=6)
	{
		return 0;
	}

	startPtr= (unsigned char *)ipv6h;
	lastPtr=startPtr+sizeof(struct ipv6hdr)+(ipv6h->payload_len);
	nextHeader= ipv6h ->nexthdr;
	ptr=startPtr+sizeof(struct ipv6hdr);

	while(ptr<lastPtr)
	{
		switch(nextHeader)
		{
			case HOP_BY_HOP_OPTIONS_HEADER:
				/*parse hop-by-hop option*/
				nextHeader=ptr[0];
				extensionHdrLen=((uint16)(ptr[1])+1)*8;
				ptr=ptr+2;

				while(ptr<(startPtr+extensionHdrLen+sizeof(struct ipv6hdr)))
				{
					optionType=ptr[0];
					/*pad1 option*/
					if(optionType==0)
					{
						ptr=ptr+1;
						continue;
					}

					/*padN option*/
					if(optionType==1)
					{
						optionDataLen=ptr[1];
						ptr=ptr+optionDataLen+2;
						continue;
					}

					/*router altert option*/
					if(ntohl(*(uint32 *)(ptr))==IPV6_ROUTER_ALTER_OPTION)
					{
						ipv6RAO=IPV6_ROUTER_ALTER_OPTION;
						ptr=ptr+4;
						continue;
					}

					/*other TLV option*/
					if((optionType!=0) && (optionType!=1))
					{
						optionDataLen=ptr[1];
						ptr=ptr+optionDataLen+2;
						continue;
					}


				}

				break;

			case ROUTING_HEADER:
				nextHeader=ptr[0];
				extensionHdrLen=((uint16)(ptr[1])+1)*8;
                            ptr=ptr+extensionHdrLen;
				break;

			case FRAGMENT_HEADER:
				nextHeader=ptr[0];
				ptr=ptr+8;
				break;

			case DESTINATION_OPTION_HEADER:
				nextHeader=ptr[0];
				extensionHdrLen=((uint16)(ptr[1])+1)*8;
				ptr=ptr+extensionHdrLen;
				break;

			case ICMP_PROTOCOL:
				nextHeader=NO_NEXT_HEADER;
				if(ptr[0]==MLD_QUERY)
				{
					return 1;

				}
				break;

			default:
				/*not ipv6 multicast protocol*/
				return 0;
		}

	}
	return 0;
}

int br_querierSelection(struct net_bridge *br,unsigned int ipVer)	
{
	int i;
	int ret=1;
	struct net_device* brDev = NULL;
	struct in_device *in_dev;	
	struct net_device *landev;
	struct in_ifaddr *ifap = NULL;
	unsigned int brIpAddr=0;
	#if defined(CONFIG_RTL_MLD_SNOOPING)
	unsigned char brIpv6Addr[16]={	0xfe,0x80,0x00,0x00,				/*source address*/
									0x00,0x00,0x00,0x00,				/*be zero*/	
									0x00,0x00,0x00,					/*upper 3 bytes mac address |0x02*/ 
									0xff,0xfe,						/*fixed*/
									0x00,0x00,0x00					/*lowert 3 bytes mac address*/	};
	#endif

	
	if(br==NULL)
	{
		return 1;
	}
	
	brDev = br->dev;

	if(ipVer==4)
	{
		/*get bridge ip address*/
		if ((landev = __dev_get_by_name(&init_net, RTL_PS_BR0_DEV_NAME)) != NULL){
			in_dev=(struct in_device *)(landev->ip_ptr);
			if (in_dev != NULL) {
				for (ifap=in_dev->ifa_list; ifap != NULL; ifap=ifap->ifa_next) {
					if (strcmp(RTL_PS_BR0_DEV_NAME, ifap->ifa_label) == 0)
					{
							memcpy(&brIpAddr,&ifap->ifa_address,4);
					}
				}
				
			}
		}

		for(i=0; i<MAX_QUERIER_RECORD; i++)
		{
			if(	(querierInfoList[i].version==4)&&
				time_after((unsigned long)(querierInfoList[i].lastJiffies+QUERIER_EXPIRED_TIME*HZ), jiffies)&&
				(querierInfoList[i].querierIp[0] < brIpAddr))
			{
				ret=0;
			}
		}
		
	}
	#if defined(CONFIG_RTL_MLD_SNOOPING) 
	else if (ipVer==6)
	{
	
		memcpy(&brIpv6Addr[8],brDev->dev_addr,3);		/*generate br link-local ipv6 address*/
		brIpv6Addr[8]=brIpv6Addr[8]|0x02;		
		memcpy(&brIpv6Addr[13],&brDev->dev_addr[3],3);	
		#if 0
		printk("br0 ipv6 address is:\n");

		{
			int j;
			for(j=0; j<16; j++)	
			{
				printk("%x",brIpv6Addr[j]);
				if((j!=0) &&(j%4==0))
				{
					printk("-");
				}
			}
			printk("\n");
		}
		#endif
		
		for(i=0; i<MAX_QUERIER_RECORD; i++)
		{
			if(	(querierInfoList[i].version==6)&&
				time_after((unsigned long)(querierInfoList[i].lastJiffies+QUERIER_EXPIRED_TIME*HZ),jiffies))
			{
				if(memcmp(querierInfoList[i].querierIp, brIpv6Addr, 16)<0)
				{
					ret=0;
				}
			}
		}
		
		
	}
	#endif
	
	return ret;
}

#endif

/*proc for debug*/
#if defined (CONFIG_PROC_FS)
#ifdef CONFIG_RTL_PROC_NEW
static int br_igmpSnoopRead(struct seq_file *s, void *v)
{
    int i,j,k;
#if defined (CONFIG_RTL8196C_REVISION_B) || defined (CONFIG_RTL8198_REVISION_B) || defined(CONFIG_RTL_819XD) || defined(CONFIG_RTL_8196E) ||defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
    unsigned int currHashMethod;
#endif
#endif
    int cnt;

    seq_printf(s, "igmpsnoopenabled:%c\n\n",igmpsnoopenabled + '0');
	seq_printf(s, "igmpVersion: %c\n\n", igmpVersion + '0');	

#if defined (CONFIG_RTL_HW_MCAST_WIFI)
	seq_printf(s, "hwwifiEnable:%d\n\n",hwwifiEnable);
#endif
	seq_printf(s, "Block Info :%d,%d\n\n", chkUnknownMcastEnable, maxUnknownMcastPPS);
	cnt = 0;
	seq_printf(s,  "Reserved multicast address:\n");
	for(i=0; i<MAX_RESERVED_MULTICAST_NUM; i++)
	{
		if(reservedMCastRecord[i].valid==1)
		{

			cnt++;
			seq_printf(s, "    [%d] Group address:%d.%d.%d.%d\n",cnt,
			reservedMCastRecord[i].groupAddr>>24, (reservedMCastRecord[i].groupAddr&0x00ff0000)>>16,
			(reservedMCastRecord[i].groupAddr&0x0000ff00)>>8, (reservedMCastRecord[i].groupAddr&0xff));
		}
	}
	if(cnt==0)
		seq_printf(s, "NULL\n");
	seq_printf(s, "\n");

#if defined (CONFIG_RTL8196C_REVISION_B) || defined (CONFIG_RTL8198_REVISION_B) || defined(CONFIG_RTL_819XD) || defined(CONFIG_RTL_8196E)  ||defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
    rtl865x_getMCastHashMethod(&currHashMethod);
    if((currHashMethod==0) || (currHashMethod==1))
    {
        seq_printf(s,"hash method:sip&dip \n\n");
    }
    else if (currHashMethod==2)
    {
        seq_printf(s,"hash method:sip[6:0] \n\n");
    }
    else if (currHashMethod==3)
    {
        seq_printf(s,"hash method:dip[6:0] \n\n");
    }
#endif
#endif

	seq_printf(s,"bridge multicast fdb:\n");
	for (i = 0; i < BR_HASH_SIZE; i++) {
		struct net_bridge_fdb_entry *f;
		struct hlist_node *n; //, *h;

		j=0;
		hlist_for_each_entry_safe(f, n, &bridge0->hash[i], hlist) {
			if(MULTICAST_MAC(f->addr.addr) )
			{
				seq_printf(s,"[%d][%d]mCastMac:0x%x:%x:%x:%x:%x:%x,use_count is %lu,ageing_timer is %lu\n",
				i,j,f->addr.addr[0],f->addr.addr[1],f->addr.addr[2],f->addr.addr[3],f->addr.addr[4],f->addr.addr[5],f->used,(jiffies<f->updated) ?0:(jiffies-f->updated));
				for(k=0;k<FDB_IGMP_EXT_NUM;k++)
				{
					if(f->igmp_fdb_arr[k].valid)
					{
						seq_printf(s,"\t<%d>clientMac:0x%x:%x:%x:%x:%x:%x,ageing_time:%lu\n",
						k,f->igmp_fdb_arr[k].SrcMac[0],f->igmp_fdb_arr[k].SrcMac[1],f->igmp_fdb_arr[k].SrcMac[2],f->igmp_fdb_arr[k].SrcMac[3],f->igmp_fdb_arr[k].SrcMac[4],f->igmp_fdb_arr[k].SrcMac[5],(jiffies<f->igmp_fdb_arr[k].ageing_time) ?0:(jiffies-f->igmp_fdb_arr[k].ageing_time));
					}
				}

				j++;
				seq_printf(s,"--------------------------------------------\n");
			}

		}

	}
	return 0;
}
#else
static int br_igmpSnoopRead(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{
    int i,j,k;
#if defined (CONFIG_RTL8196C_REVISION_B) || defined (CONFIG_RTL8198_REVISION_B) || defined(CONFIG_RTL_819XD) || defined(CONFIG_RTL_8196E) ||defined(CONFIG_RTL_8198C)||defined(CONFIG_RTL_8197F)
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
    unsigned int currHashMethod;
#endif
#endif
#if defined(CONFIG_RTL_QUERIER_SELECTION)
	unsigned long elapseJiffies;
#endif
    int cnt = 0;
    int len;
	
    len = sprintf(page, "igmpsnoopenabled:%c\n\n", igmpsnoopenabled + '0');
	len += sprintf(page+len, "igmpVersion: %c\n\n", igmpVersion + '0');
	
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
	len += sprintf(page+len, "hwwifiEnable:%d\n\n", hwwifiEnable);
#endif

	len += sprintf(page+len, "Block Info :%d,%d\n\n", chkUnknownMcastEnable, maxUnknownMcastPPS);
	cnt = 0;
	len += sprintf(page+len, "Reserved multicast address:\n");
	for(i=0; i<MAX_RESERVED_MULTICAST_NUM; i++)
	{
		if(reservedMCastRecord[i].valid==1)
		{

			cnt++;
			len += sprintf(page+len, "    [%d] Group address:%d.%d.%d.%d\n",cnt,
			reservedMCastRecord[i].groupAddr>>24, (reservedMCastRecord[i].groupAddr&0x00ff0000)>>16,
			(reservedMCastRecord[i].groupAddr&0x0000ff00)>>8, (reservedMCastRecord[i].groupAddr&0xff));
		}
	}
	if(cnt==0)
		len += sprintf(page+len, "NULL\n");
	len += sprintf(page+len, "\n");	

#if defined (CONFIG_RTL8196C_REVISION_B) || defined (CONFIG_RTL8198_REVISION_B) || defined(CONFIG_RTL_819XD) || defined(CONFIG_RTL_8196E)  ||defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
    rtl865x_getMCastHashMethod(&currHashMethod);
    if((currHashMethod==0) || (currHashMethod==1))
    {
        len += sprintf(page+len, "hash method:sip&dip\n\n");
    }
    else if (currHashMethod==2)
    {
        len += sprintf(page+len, "hash method:sip[6:0]\n\n");
    }
    else if (currHashMethod==3)
    {
        len += sprintf(page+len, "hash method:dip[6:0]\n\n");
    }
#endif
#endif

    len += sprintf(page+len, "bridge multicast fdb:\n");
    for (i = 0; i < BR_HASH_SIZE; i++) {
        struct net_bridge_fdb_entry *f;
        struct hlist_node *n; //, *h;

        j=0;
        hlist_for_each_entry_safe(f, n, &bridge0->hash[i], hlist) {
            if(MULTICAST_MAC(f->addr.addr) )
            {
                len += sprintf(page+len,"[%d][%d]mCastMac:0x%x:%x:%x:%x:%x:%x,use_count is %lu,ageing_timer is %lu\n",
                    i,j,f->addr.addr[0],f->addr.addr[1],f->addr.addr[2],f->addr.addr[3],f->addr.addr[4],f->addr.addr[5],f->used,(jiffies<f->updated) ?0:(jiffies-f->updated));
                for(k=0;k<FDB_IGMP_EXT_NUM;k++)
                {
                    if(f->igmp_fdb_arr[k].valid)
                    {
                        len += sprintf(page+len,"\t<%d>clientMac:0x%x:%x:%x:%x:%x:%x,ageing_time:%lu\n",
                            k,f->igmp_fdb_arr[k].SrcMac[0],f->igmp_fdb_arr[k].SrcMac[1],f->igmp_fdb_arr[k].SrcMac[2],f->igmp_fdb_arr[k].SrcMac[3],f->igmp_fdb_arr[k].SrcMac[4],f->igmp_fdb_arr[k].SrcMac[5],(jiffies<f->igmp_fdb_arr[k].ageing_time) ?0:(jiffies-f->igmp_fdb_arr[k].ageing_time));
                    }
                    j++;
                    len += sprintf(page+len,"--------------------------------------------\n");
                }

            }
        }
    }
	
	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
}
#endif
static int br_igmpSnoopWrite(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
    //unsigned char br_tmp;
    char        tmpbuf[512];
    char        *strptr = NULL;
    char        *tokptr = NULL;
#if defined (CONFIG_RTL8196C_REVISION_B) || defined (CONFIG_RTL8198_REVISION_B) || defined(CONFIG_RTL_819XD) || defined(CONFIG_RTL_8196E) ||defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
    unsigned int newHashMethod=0;
#endif
	uint32  ipAddr[4];
	uint32 groupAddr;
	int flag;
	int cnt;
	int fastLeave=0;
	int ageTime=0;

    if (count < 2)
	    return -EFAULT;

    if (buffer && !copy_from_user(&tmpbuf, buffer, count)) {
        tmpbuf[count] = '\0';
        strptr = tmpbuf;

		tokptr = strsep(&strptr," ");

        if (tokptr != NULL)
        {
	        if(!memcmp(tokptr,"enable",6))
			{
				tokptr = strsep(&strptr," ");
				if (tokptr==NULL)
				{
					return -EFAULT;
				}
				igmpsnoopenabled = simple_strtol(tokptr, NULL, 0);
			}
			else if(!memcmp(tokptr, "igmpVersion", 11))
			{
				tokptr = strsep(&strptr, " ");
				if(tokptr==NULL)
				{	
					return -EFAULT;
				}
				igmpVersion = simple_strtol(tokptr, NULL, 0);
				if(igmpVersion>=3)
				{
					igmpVersion=3;
				}
				else
				{
					igmpVersion=2;
				}
			}
			else if(!memcmp(tokptr, "fastleave", 9))
			{
				tokptr = strsep(&strptr," ");
				if (tokptr==NULL)
				{
					return -EFAULT;
				}

				fastLeave = simple_strtol(tokptr, NULL, 0);

				if(fastLeave)
				{
					fastLeave=1;
				}

				tokptr = strsep(&strptr," ");
				if (tokptr==NULL)
				{
					return -EFAULT;
				}

				ageTime = simple_strtol(tokptr, NULL, 0);
				rtl_configMulticastSnoopingFastLeave(fastLeave,ageTime);
			}
			else if(!memcmp(tokptr,"block",5))
            {
            	tokptr = strsep(&strptr," ");
              	if (tokptr==NULL)
              	{
               		return -EFAULT;
        		}
 
               	chkUnknownMcastEnable = simple_strtol(tokptr, NULL, 0);
 
              	if(chkUnknownMcastEnable)
               	{
                    chkUnknownMcastEnable=1;
                }
 
             	tokptr = strsep(&strptr," ");
                if (tokptr==NULL)
             	{
                 	return -EFAULT;
                }
 
                maxUnknownMcastPPS = simple_strtol(tokptr, NULL, 0);
         	}
		#if defined (CONFIG_RTL_HW_MCAST_WIFI)
			else if(!memcmp(tokptr,"hwWifi",6))
			{
				tokptr = strsep(&strptr," ");
				if (tokptr==NULL)
				{
					return -EFAULT;
				}
              	hwwifiEnable = simple_strtol(tokptr, NULL, 0);
			}
		#endif
			else if(!memcmp(tokptr, "reserve", 7))
			{

				tokptr = strsep(&strptr," ");
				if (tokptr==NULL)
				{
					return -EFAULT;
				}
				if(	(!memcmp(tokptr, "add", 3))
				|| (!memcmp(tokptr, "Add", 3))
				||(!memcmp(tokptr, "ADD", 3)))
				{
					flag = 1;
				}
				else if((!memcmp(tokptr, "del", 3))
				|| (!memcmp(tokptr, "Del", 3))
				||(!memcmp(tokptr, "DEL", 3)))
				{
					flag = 0;
				}

				tokptr = strsep(&strptr," ");
				if (tokptr==NULL)
				{
					return -EFAULT;
				}
				cnt = sscanf(tokptr, "%d.%d.%d.%d", &ipAddr[0], &ipAddr[1], &ipAddr[2], &ipAddr[3]);

				groupAddr=(ipAddr[0]<<24)|(ipAddr[1]<<16)|(ipAddr[2]<<8)|(ipAddr[3]);
				rtl_add_ReservedMCastAddr(groupAddr,flag);
			}
#if defined (CONFIG_RTL8196C_REVISION_B) || defined (CONFIG_RTL8198_REVISION_B) || defined(CONFIG_RTL_819XD) || defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
			else if(!memcmp(tokptr, "hash", 4))
			{
				tokptr = strsep(&strptr," ");
				if (tokptr!=NULL )
				{
					newHashMethod = simple_strtol(tokptr, NULL, 0);
					if(newHashMethod >3)
					{
						return -1;
					}

					rtl865x_setMCastHashMethod(newHashMethod);

				}
			}
#endif
#endif
			else
			{
				igmpsnoopenabled = simple_strtol(tokptr, NULL, 0);
			}
			if(igmpsnoopenabled)
			{
				igmpsnoopenabled=1;
			}
			else
			{
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
				rtl865x_reinitMulticast();
#endif
				rtl_flushAllIgmpRecord(FLUSH_IGMP_RECORD);
			}
			#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
			rtl_processAclForIgmpSnooping(igmpsnoopenabled);
			#endif
		}
	    return count;
      }
      return -EFAULT;
}

#ifdef CONFIG_RTL_PROC_NEW
int rlx_br_igmpsnoop_single_open(struct inode *inode, struct file *file)
{
	return(single_open(file, br_igmpSnoopRead,NULL));
}
static ssize_t rlx_br_igmpsnoop_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return br_igmpSnoopWrite(file, userbuf,count, off);
}
struct file_operations rlx_br_igmpsnoop_proc_fops= {
        .open           = rlx_br_igmpsnoop_single_open,
        .write		    = rlx_br_igmpsnoop_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};

int igmp_db_open(struct inode *inode, struct file *file)
{
        return(single_open(file, igmp_show, NULL));
}

int igmp_db_write(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
        return igmp_write(file, buffer, count,data);
}

struct file_operations igmp_db_seq_file_operations = {
        .open           = igmp_db_open,
        .read           = seq_read,
        .write		= igmp_db_write,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#endif

/*igmp FastFwd proc begin*/
#ifdef CONFIG_RTL_PROC_NEW
static int br_mCastFastFwdRead(struct seq_file *s, void *v)
{
		seq_printf(s,"%c,%c\n",ipMulticastFastFwd + '0',needCheckMfc + '0');
		return 0;
}
#else
static int br_mCastFastFwdRead(char *page, char **start, off_t off, 
		int count, int *eof, void *data)
{

    int len;
    len = sprintf(page, "%c,%c\n", ipMulticastFastFwd + '0',needCheckMfc + '0');

    if (len <= off+count) *eof = 1;
    *start = page + off;
    len -= off;
    if (len>count) len = count;
    if (len<0) len = 0;
    return len;
}
#endif

static int br_mCastFastFwdWrite(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	unsigned int tmp=0; 
	char 		tmpbuf[512];
	char		*strptr;
	char		*tokptr;
	

	if (count < 2) 
		return -EFAULT;

	if (buffer && !copy_from_user(tmpbuf, buffer, count)) 
	{
		tmpbuf[count] = '\0';

		strptr=tmpbuf;

		
		tokptr = strsep(&strptr,",");
		if (tokptr==NULL)
		{
			tmp=simple_strtol(strptr, NULL, 0);
			printk("tmp=%d\n",tmp);
			if(tmp==0)
			{
				ipMulticastFastFwd=0;
			}
			return -EFAULT;
		}
		
		ipMulticastFastFwd = simple_strtol(tokptr, NULL, 0);
		//printk("ipMulticastFastFwd=%d\n",ipMulticastFastFwd);
		if(ipMulticastFastFwd)
		{
			ipMulticastFastFwd=1;
		}

		tokptr = strsep(&strptr,",");
		if (tokptr==NULL)
		{
			return -EFAULT;
		}
		
		needCheckMfc = simple_strtol(tokptr, NULL, 0);

		if(needCheckMfc)
		{
			needCheckMfc=1;
		}

		return count;
	}
	return -EFAULT;
}

#ifdef CONFIG_RTL_PROC_NEW
int rlx_br_mcast_fast_fwd_single_open(struct inode *inode, struct file *file)
{
	return(single_open(file, br_mCastFastFwdRead,NULL));
}
static ssize_t rlx_br_mcast_fast_fwd_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return br_mCastFastFwdWrite(file, userbuf,count, off);
}

struct file_operations rlx_br_mcast_fast_fwd_proc_fops= {
        .open           = rlx_br_mcast_fast_fwd_single_open,
        .write		    = rlx_br_mcast_fast_fwd_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#endif
/*igmp FastFwd proc end*/

#if 1
/*igmp querry proc begin*/
#ifdef CONFIG_RTL_PROC_NEW
static int br_igmpQueryRead(struct seq_file *s, void *v)
{
#if defined(CONFIG_RTL_QUERIER_SELECTION)
	int i;
	int cnt = 0;
	unsigned long elapseJiffies;
#endif

	seq_printf(s,"igmpQueryEnable: %c\n\n",igmpQueryEnabled + '0');
#if defined(CONFIG_RTL_MLD_SNOOPING)
	seq_printf(s,"mldQueryEnable: %c\n\n", mldQueryEnabled + '0');
#endif
	
#if defined(CONFIG_RTL_QUERIER_SELECTION)
	cnt = 0;
	seq_printf(s, "Igmp Querier Info List:\n");
	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if((querierInfoList[i].version==4) && time_after((unsigned long)(querierInfoList[i].lastJiffies+QUERIER_EXPIRED_TIME*HZ),jiffies))
		{
			if(jiffies > querierInfoList[i].lastJiffies)
			{
				elapseJiffies=jiffies-querierInfoList[i].lastJiffies;
			}
			else
			{
				elapseJiffies=jiffies+((unsigned long)0xFFFFFFFF-querierInfoList[i].lastJiffies)+1;
			}
			cnt++;
			seq_printf(s, "%s %d.%d.%d.%d %u\n",
				querierInfoList[i].devName,
				((querierInfoList[i].querierIp[0]>>24)&0xFF) ,
				((querierInfoList[i].querierIp[0]>>16)&0xFF),
				((querierInfoList[i].querierIp[0]>>8)&0xFF),
				(querierInfoList[i].querierIp[0]&0xFF),elapseJiffies/HZ);
		}
	}
	if(cnt == 0)
		seq_printf(s, "NULL\n");
	seq_printf(s, "\n");
#if defined(CONFIG_RTL_MLD_SNOOPING)
	cnt = 0; 
	seq_printf(s, "Mld Querier Info List:\n");
	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if((querierInfoList[i].version==6) && time_after((unsigned long)(querierInfoList[i].lastJiffies+QUERIER_EXPIRED_TIME*HZ),jiffies))
		{
			if(jiffies > querierInfoList[i].lastJiffies)
			{
				elapseJiffies=jiffies-querierInfoList[i].lastJiffies;
			}
			else
			{
				elapseJiffies=jiffies+((unsigned long)0xFFFFFFFF-querierInfoList[i].lastJiffies)+1;
			}
			cnt++;
			seq_printf(s, "%s %x-%x-%x-%x %lu\n",
				querierInfoList[i].devName,
				querierInfoList[i].querierIp[0],
				querierInfoList[i].querierIp[1],
				querierInfoList[i].querierIp[2],
				querierInfoList[i].querierIp[3],elapseJiffies/HZ);
		}
	}
	if(cnt == 0)
		seq_printf(s, "NULL\n");
	seq_printf(s, "\n");
#endif
#endif
	return 0;
}
#else
static int br_igmpQueryRead(char *page, char **start, off_t off, 
		int count, int *eof, void *data)
{
	int len;
#if defined(CONFIG_RTL_QUERIER_SELECTION)
	int i;
	int cnt = 0;
	unsigned long elapseJiffies;
#endif
    len = sprintf(page, "igmpQueryEnable: %c\n\n", igmpQueryEnabled + '0');
	len = sprintf(page, "mldQueryEnable: %c\n\n", mldQueryEnabled + '0');
		
#if defined(CONFIG_RTL_QUERIER_SELECTION)
	cnt = 0;
	len += sprintf(page+len, "Igmp Querier Info List:\n");
	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if((querierInfoList[i].version==4) && time_after((unsigned long)(querierInfoList[i].lastJiffies+QUERIER_EXPIRED_TIME*HZ),jiffies))
		{
			if(jiffies > querierInfoList[i].lastJiffies)
			{
				elapseJiffies=jiffies-querierInfoList[i].lastJiffies;
			}
			else
			{
				elapseJiffies=jiffies+((unsigned long)0xFFFFFFFF-querierInfoList[i].lastJiffies)+1;
			}
			cnt++;
			len += sprintf(page+len, "%s %d.%d.%d.%d %u\n",
				querierInfoList[i].devName,
				((querierInfoList[i].querierIp[0]>>24)&0xFF) ,
				((querierInfoList[i].querierIp[0]>>16)&0xFF),
				((querierInfoList[i].querierIp[0]>>8)&0xFF),
				(querierInfoList[i].querierIp[0]&0xFF),elapseJiffies/HZ);
		}
	}
	if(cnt == 0)
		len += sprintf(page+len, "NULL\n");
	len += sprintf(page+len, "\n");
#if defined(CONFIG_RTL_MLD_SNOOPING)
	cnt = 0; 
	len += sprintf(page+len, "Mld Querier Info List:\n");
	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if((querierInfoList[i].version==6) && time_after((unsigned long)(querierInfoList[i].lastJiffies+QUERIER_EXPIRED_TIME*HZ),jiffies))
		{
			if(jiffies > querierInfoList[i].lastJiffies)
			{
				elapseJiffies=jiffies-querierInfoList[i].lastJiffies;
			}
			else
			{
				elapseJiffies=jiffies+((unsigned long)0xFFFFFFFF-querierInfoList[i].lastJiffies)+1;
			}
			cnt++;
			len += sprintf(page+len, "%s %x-%x-%x-%x %lu\n",
				querierInfoList[i].devName,
				querierInfoList[i].querierIp[0],
				querierInfoList[i].querierIp[1],
				querierInfoList[i].querierIp[2],
				querierInfoList[i].querierIp[3],elapseJiffies/HZ);
		}
	}
	if(cnt == 0)
		len += sprintf(page+len, "NULL\n");
	len += sprintf(page+len, "\n");
#endif
#endif

    if (len <= off+count) *eof = 1;
    *start = page + off;
    len -= off;
    if (len>count) len = count;
    if (len<0) len = 0;
    return len;
}
#endif

static int br_igmpQueryWrite(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
   	unsigned char tmpbuf[128];
    char        *strptr = NULL;
    char        *tokptr = NULL;
 	if (count < 2) 
	 	return -EFAULT;
	  
	if (buffer && !copy_from_user(&tmpbuf, buffer, count)) {
		tmpbuf[count] = '\0';
		strptr = tmpbuf;
	  
		tokptr = strsep(&strptr," ");
	  
		if (tokptr != NULL)
		{
			if(!memcmp(tokptr,"igmpQueryEnable",15))
			{
				tokptr = strsep(&strptr," ");
				if (tokptr==NULL)
				{
					return -EFAULT;
				}
				igmpQueryEnabled= simple_strtol(tokptr, NULL, 0);
				if(igmpQueryEnabled)
				{
					igmpQueryEnabled = 1;
				}
				else
				{
					igmpQueryEnabled = 0;
				}
			}
			#if defined(CONFIG_RTL_MLD_SNOOPING)
			else if(!memcmp(tokptr, "mldQueryEnable", 15))
			{
				tokptr = strsep(&strptr, " ");
				if(tokptr==NULL)
				{   
					return -EFAULT;
				}
				mldQueryEnabled = simple_strtol(tokptr, NULL, 0);
				if(mldQueryEnabled)
				{
					mldQueryEnabled = 1;
				}
				else
				{
					mldQueryEnabled = 0;
				}
	
			}
			#endif
		}
		return count;
	}
   	return -EFAULT;
}

int rlx_br_igmp_query_single_open(struct inode *inode, struct file *file)
{
	return(single_open(file, br_igmpQueryRead,NULL));
}
static ssize_t rlx_br_igmp_query_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return br_igmpQueryWrite(file, userbuf,count, off);
}

struct file_operations rlx_br_igmp_query_proc_fops= {
        .open           = rlx_br_igmp_query_single_open,
        .write		    = rlx_br_igmp_query_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
/*igmp querry proc end*/
#endif

/*mld version proc begin*/
#if defined (CONFIG_RTL_MLD_SNOOPING)
#ifdef CONFIG_RTL_PROC_NEW
static int br_mldVersionRead(struct seq_file *s, void *v)
{
		seq_printf(s,"%c\n", mldVersion + '0');
		return 0;
}
#else
static int br_mldVersionRead(char *page, char **start, off_t off, 
		int count, int *eof, void *data)
{
	int len;
    len = sprintf(page, "%c\n", mldVersion + '0');
    if (len <= off+count) *eof = 1;
    *start = page + off;
    len -= off;
    if (len>count) len = count;
    if (len<0) len = 0;
    return len;

}
#endif

static int br_mldVersionWrite(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
      unsigned char tmp; 
      if (count < 2) 
	    return -EFAULT;
      
	if (buffer && !copy_from_user(&tmp, buffer, 1)) {
		mldVersion = tmp - '0';
		if(mldVersion>=2)
		{
			mldVersion=2;
		}
		else if (mldVersion<=1)
		{
			mldVersion=1;
		}
		else
		{
			mldVersion=2;
		}
	    return count;
      }
      return -EFAULT;
}
int rlx_br_mld_version_single_open(struct inode *inode, struct file *file)
{
	return(single_open(file, br_mldVersionRead,NULL));
}
static ssize_t rlx_br_mld_version_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return br_mldVersionWrite(file, userbuf,count, off);
}

struct file_operations rlx_br_mld_version_proc_fops= {
        .open           = rlx_br_mld_version_single_open,
        .write		    = rlx_br_mld_version_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};

#endif
/*mld version proc begin*/

/*igmp/mld querier info proc begin*/
#if 0//defined (CONFIG_RTL_QUERIER_SELECTION)
struct proc_dir_entry *procIgmpQuerierInfo=NULL;
#ifdef CONFIG_RTL_PROC_NEW
static int br_igmpQuerierInfoRead(struct seq_file *s, void *v)
#else
static int br_igmpQuerierInfoRead(char *page, char **start, off_t off, 
		int count, int *eof, void *data)
#endif
{
#ifndef CONFIG_RTL_PROC_NEW
	int len=0;
#endif
	int i;
	unsigned long elapseJiffies;
	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if((querierInfoList[i].version==4) && time_after((unsigned long)(querierInfoList[i].lastJiffies+QUERIER_EXPIRED_TIME*HZ),jiffies))
		{
			if(jiffies > querierInfoList[i].lastJiffies)
			{
				elapseJiffies=jiffies-querierInfoList[i].lastJiffies;
			}
			else
			{
				elapseJiffies=jiffies+((unsigned long)0xFFFFFFFF-querierInfoList[i].lastJiffies)+1;
			}
#ifdef CONFIG_RTL_PROC_NEW
			seq_printf(s, "%s %d.%d.%d.%d %lu\n",
				querierInfoList[i].devName,
				((querierInfoList[i].querierIp[0]>>24)&0xFF) ,
				((querierInfoList[i].querierIp[0]>>16)&0xFF),
				((querierInfoList[i].querierIp[0]>>8)&0xFF),
				(querierInfoList[i].querierIp[0]&0xFF),elapseJiffies/HZ);
#else
			len += sprintf(page+len, "%s %d.%d.%d.%d %u\n",
				querierInfoList[i].devName,
				((querierInfoList[i].querierIp[0]>>24)&0xFF) ,
				((querierInfoList[i].querierIp[0]>>16)&0xFF),
				((querierInfoList[i].querierIp[0]>>8)&0xFF),
				(querierInfoList[i].querierIp[0]&0xFF),elapseJiffies/HZ);
#endif
		}
	}
#ifdef CONFIG_RTL_PROC_NEW
	return 0;
#else	
	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
#endif
}

static int br_igmpQuerierInfoWrite(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	unsigned char tmp[64]; 

	if (count < 2) 
	{
		return -EFAULT;
	}
	
	if(count >sizeof(tmp))
	{
		return -EFAULT;
	}
	  
	
    return 0;
}
int rlx_br_igmp_querier_info_single_open(struct inode *inode, struct file *file)
{
	return(single_open(file, br_igmpQuerierInfoRead,NULL));
}
static ssize_t rlx_br_igmp_querier_info_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return br_igmpQuerierInfoWrite(file, userbuf,count, off);
}

struct file_operations rlx_br_igmp_querier_info_proc_fops= {
        .open           = rlx_br_igmp_querier_info_single_open,
        .write		    = rlx_br_igmp_querier_info_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};

#if defined(CONFIG_RTL_MLD_SNOOPING)
struct proc_dir_entry *procMldQuerierInfo=NULL;
#ifdef CONFIG_RTL_PROC_NEW
static int br_mldQuerierInfoRead(struct seq_file *s,void *v)
#else
static int br_mldQuerierInfoRead(char *page, char **start, off_t off, 
		int count, int *eof, void *data)
#endif
{
#ifndef CONFIG_RTL_PROC_NEW
	int len=0;
#endif
	int i;
	unsigned long elapseJiffies;

	for(i=0; i<MAX_QUERIER_RECORD; i++)
	{
		if((querierInfoList[i].version==6) && time_after((unsigned long)(querierInfoList[i].lastJiffies+QUERIER_EXPIRED_TIME*HZ),jiffies))
		{
			if(jiffies > querierInfoList[i].lastJiffies)
			{
				elapseJiffies=jiffies-querierInfoList[i].lastJiffies;
			}
			else
			{
				elapseJiffies=jiffies+((unsigned long)0xFFFFFFFF-querierInfoList[i].lastJiffies)+1;
			}
#ifdef CONFIG_RTL_PROC_NEW
			seq_printf(s, "%s %x-%x-%x-%x %lu\n",
				querierInfoList[i].devName,
				querierInfoList[i].querierIp[0],
				querierInfoList[i].querierIp[1],
				querierInfoList[i].querierIp[2],
				querierInfoList[i].querierIp[3],elapseJiffies/HZ);
#else
			len += sprintf(page+len, "%s %x-%x-%x-%x %u\n",
				querierInfoList[i].devName,
				querierInfoList[i].querierIp[0],
				querierInfoList[i].querierIp[1],
				querierInfoList[i].querierIp[2],
				querierInfoList[i].querierIp[3],elapseJiffies/HZ);
#endif
		}
	}
#ifdef CONFIG_RTL_PROC_NEW
	return 0;
#else
	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
#endif
}

static int br_mldQuerierInfoWrite(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	unsigned char tmp[64]; 

	if (count < 2) 
	{
		return -EFAULT;
	}
	
	if(count >sizeof(tmp))
	{
		return -EFAULT;
	}
	  
	
    return 0;
}
int rlx_br_mld_querier_info_single_open(struct inode *inode, struct file *file)
{
	return(single_open(file, br_mldQuerierInfoRead,NULL));
}
static ssize_t rlx_br_mld_querier_info_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return br_mldQuerierInfoWrite(file, userbuf,count, off);
}

struct file_operations rlx_br_mld_querier_info_proc_fops= {
        .open           = rlx_br_mld_querier_info_single_open,
        .write		    = rlx_br_mld_querier_info_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#endif
#endif
/*igmp/mld querier info proc end*/

#if 1
/*igmp proxy proc begin*/
#ifdef CONFIG_RTL_PROC_NEW
static int br_igmpProxyRead(struct seq_file *s, void *v)
{
	seq_printf(s, "igmpProxyOpened: %c\n\n",IGMPProxyOpened + '0');
	seq_printf(s, "igmpProxyNeedFastLeave: %c\n", IGMPPRoxyFastLeave + '0');
	return 0;
}
#else
static int br_igmpProxyRead(char *page, char **start, off_t off, 
		int count, int *eof, void *data)
{
    int len;
    len = sprintf(page, "igmpProxyOpened: %c\n\n", IGMPProxyOpened + '0');
	len += sprintf(page, "igmpProxyNeedFastLeave: %c\n", IGMPPRoxyFastLeave + '0');
    if (len <= off+count) *eof = 1;
    *start = page + off;
    len -= off;
    if (len>count) len = count;
    if (len<0) len = 0;
    return len;
}
#endif

static int br_igmpProxyWrite(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
    unsigned char chartmp; 
	char        tmpbuf[512];
    char        *strptr = NULL;
    char        *tokptr = NULL;

    if (count > 1) {	//call from shell
      	if (buffer && !copy_from_user(&tmpbuf, buffer, count)) {
			tmpbuf[count] = '\0';

			strptr = tmpbuf;
			tokptr = strsep(&strptr, " ");
			if(tokptr == NULL)
				return -EFAULT;
			

			if(!memcmp(tokptr, "opened", 6))
			{	
				tokptr = strsep(&strptr, " ");
				if(tokptr == NULL)
					return -EFAULT;
				IGMPProxyOpened = simple_strtol(tokptr, NULL, 0);
					
			}
			else if(!memcmp(tokptr, "fastleave", 9))
			{
				tokptr = strsep(&strptr, " ");
				if(tokptr == NULL)
					return -EFAULT;
				IGMPPRoxyFastLeave = simple_strtol(tokptr, NULL, 0);
			}
			else
				return -EFAULT;

	    }
	}
	#if 0
	else if(count==1){//call from demon(demon direct call br's ioctl)
			//memcpy(&chartmp,buffer,1);
			if(buffer){
				get_user(tmpbuf,buffer);
				
		    		IGMPProxyOpened = chartmp - '0';
			}else
				return -EFAULT;

	}
	#endif
	else{

		return -EFAULT;
	}
	return count;
}

int rlx_br_igmp_proxy_single_open(struct inode *inode, struct file *file)
{
	return(single_open(file, br_igmpProxyRead,NULL));
}
static ssize_t rlx_br_igmp_proxy_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return br_igmpProxyWrite(file, userbuf,count, off);
}

struct file_operations rlx_br_igmp_proxy_proc_fops= {
        .open           = rlx_br_igmp_proxy_single_open,
        .write		    = rlx_br_igmp_proxy_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
/*igmp proxy proc end*/
#endif

void rtl_IgmpSnooping_ProcCreate_hook(void)
{
#if defined (CONFIG_RTL_QUERIER_SELECTION)
	br_initQuerierInfo();
#endif
#ifdef CONFIG_RTL_PROC_NEW
	proc_create_data("br_igmpsnoop",0,&proc_root,&rlx_br_igmpsnoop_proc_fops,NULL);
	proc_create_data("br_igmpDb",0,&proc_root,&igmp_db_seq_file_operations,NULL);
	proc_create_data("br_igmpQuery",0,&proc_root,&rlx_br_igmp_query_proc_fops,NULL);
	proc_create_data("br_igmpProxy",0,&proc_root,&rlx_br_igmp_proxy_proc_fops,NULL);
	proc_create_data("br_mCastFastFwd",0,&proc_root,&rlx_br_mcast_fast_fwd_proc_fops,NULL);
#if defined CONFIG_RTL_MLD_SNOOPING
	proc_create_data("br_mldVersion",0,&proc_root,&rlx_br_mld_version_proc_fops,NULL);
#endif
#else
	procIgmpSnoop = create_proc_entry("br_igmpsnoop", 0, NULL);
	if (procIgmpSnoop) {
		procIgmpSnoop->read_proc = br_igmpSnoopRead;
		procIgmpSnoop->write_proc = br_igmpSnoopWrite;
	}

	procIgmpDb=create_proc_entry("br_igmpDb", 0, NULL);
	if(procIgmpDb != NULL)
	{
		procIgmpDb->proc_fops = &igmp_db_seq_file_operations;
	}

	procIgmpQuery=create_proc_entry("br_igmpQuery", 0, NULL);
	if(procIgmpQuery != NULL)
	{
		procIgmpQuery->read_proc = br_igmpQueryRead;
		procIgmpQuery->write_proc = br_igmpQueryWrite;
	}

	procIgmpProxy=create_proc_entry("br_igmpProxy", 0, NULL);
	if(procIgmpProxy != NULL)
	{
		procIgmpProxy->read_proc = br_igmpProxyRead;
		procIgmpProxy->write_proc = br_igmpProxyWrite;
	}
	procMCastFastFwd= create_proc_entry("br_mCastFastFwd", 0, NULL);
	if (procMCastFastFwd) {
		procMCastFastFwd->read_proc = br_mCastFastFwdRead;
		procMCastFastFwd->write_proc = br_mCastFastFwdWrite;
	}
	procMldVersion= create_proc_entry("br_mldVersion", 0, NULL);
	if (procMldVersion) {
		procMldVersion->read_proc = br_mldVersionRead;
		procMldVersion->write_proc = br_mldVersionWrite;
	}
#endif
}
void rtl_IgmpSnooping_ProcDestroy_hook(void)
{
#ifdef CONFIG_RTL_PROC_NEW
    remove_proc_entry("br_igmpsnoop", &proc_root);
    remove_proc_entry("br_igmpDb", &proc_root);
	remove_proc_entry("br_igmpQuery", &proc_root);
    remove_proc_entry("br_igmpProxy", &proc_root);
    remove_proc_entry("br_mCastFastFwd", &proc_root);
#if defined CONFIG_RTL_MLD_SNOOPING
	remove_proc_entry("br_mldVersion", &proc_root);
#endif
#else
        if (procIgmpSnoop) {
            remove_proc_entry("br_igmpsnoop", procIgmpSnoop);
            procIgmpSnoop = NULL;
        }
        if(procIgmpDb!=NULL)
        {
            remove_proc_entry("br_igmpDb", procIgmpDb);
            procIgmpDb = NULL;
        }
		
        if (procIgmpQuery) {
            remove_proc_entry("br_igmpQuery", procIgmpQuery);
            procIgmpQuery = NULL;
        }
		
        if (procIgmpProxy) {
            remove_proc_entry("br_igmpProxy", procIgmpProxy);
            procIgmpProxy = NULL;
        }
        if (procMCastFastFwd) {
            remove_proc_entry("br_mCastFastFwd", procMCastFastFwd);
            procMCastFastFwd = NULL;
        }	
#if defined CONFIG_RTL_MLD_SNOOPING
        if (procMldVersion) {
            remove_proc_entry("br_mldVersion", procMldVersion);
            procMldVersion = NULL;
        }

#endif
#endif
}

#endif /*CONFIG_PROC_FS*/


/*init and deinit begin*/
static unsigned short  br_ipv4Checksum(unsigned char *pktBuf, unsigned int pktLen)
{
	/*note: the first bytes of  packetBuf should be two bytes aligned*/
	unsigned int  checksum=0;
	unsigned int  count=pktLen;
	unsigned short   *ptr= (unsigned short *)pktBuf;	
	
	 while(count>1)
	 {
		  checksum+= ntohs(*ptr);
		  ptr++;
		  count -= 2;
	 }
	 
	if(count>0)
	{
		checksum+= *(pktBuf+pktLen-1)<<8; /*the last odd byte is treated as bit 15~8 of unsigned short*/
	}

	/* Roll over carry bits */
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum += (checksum >> 16);

	/* Return checksum */
	return ((unsigned short) ~ checksum);

}

static unsigned char* br_generateIgmpQuery(struct net_bridge * br)
{
	struct net_device* brDev = NULL;
	unsigned short checkSum=0;
	struct in_device *in_dev;	
	struct net_device *landev;
	struct in_ifaddr *ifap = NULL;
	
      
	if(br==NULL)
	{
		return NULL;
	}
	
	brDev = br->dev;
	if(igmpVersion==3)
	{
		memcpy(&igmpV3QueryBuf[6],brDev->dev_addr,6);			/*set source mac address*/
	}
	else
	{
		memcpy(&igmpV2QueryBuf[6],brDev->dev_addr,6);			/*set source mac address*/
	}
	
	/*set source ip address*/
	if ((landev = __dev_get_by_name(&init_net, RTL_PS_BR0_DEV_NAME)) != NULL){
		in_dev=(struct in_device *)(landev->ip_ptr);
		if (in_dev != NULL) {
			for (ifap=in_dev->ifa_list; ifap != NULL; ifap=ifap->ifa_next) {
				if (strcmp(RTL_PS_BR0_DEV_NAME, ifap->ifa_label) == 0){
					if(igmpVersion==3)
					{
						memcpy(&igmpV3QueryBuf[26],&ifap->ifa_address,4);
					}
					else
					{
						memcpy(&igmpV2QueryBuf[26],&ifap->ifa_address,4);
					}
					
				}
			}
			
		}
	}
	else
	{
		return NULL;
	}
	
    #ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if(!strcmp(RTL_PS_BR1_DEV_NAME, br->dev->name))
	{
		if (landev = brDev){
			in_dev=(struct net_device *)(landev->ip_ptr);
			if (in_dev != NULL) {
				for (ifap=in_dev->ifa_list; ifap != NULL; ifap=ifap->ifa_next) {
					if (strcmp(br->dev->name, ifap->ifa_label) == 0){
						if(igmpVersion==3)
						{
							memcpy(&igmpV3QueryBuf[26],&ifap->ifa_address,4);
						}
						else
						{
							memcpy(&igmpV2QueryBuf[26],&ifap->ifa_address,4);
						}
					}
				}
			}
		}
	}
    #endif
	if(igmpVersion==3)
	{
		igmpV3QueryBuf[24]=0;
		igmpV3QueryBuf[25]=0;
	}
	else
	{
		igmpV2QueryBuf[24]=0;
		igmpV2QueryBuf[25]=0;
	}
	
	if(igmpVersion==3)
	{
		checkSum=br_ipv4Checksum(&igmpV3QueryBuf[14],24);
	}
	else
	{
		checkSum=br_ipv4Checksum(&igmpV2QueryBuf[14],20);
	}

	if(igmpVersion==3)
	{
		igmpV3QueryBuf[24]=(checkSum&0xff00)>>8;
		igmpV3QueryBuf[25]=(checkSum&0x00ff);

	}
	else
	{
		igmpV2QueryBuf[24]=(checkSum&0xff00)>>8;
		igmpV2QueryBuf[25]=(checkSum&0x00ff);

	}
	

	if(igmpVersion==3)
	{
		igmpV3QueryBuf[40]=0;
		igmpV3QueryBuf[41]=0;
		checkSum=br_ipv4Checksum(&igmpV3QueryBuf[38],12);
		igmpV3QueryBuf[40]=(checkSum&0xff00)>>8;
		igmpV3QueryBuf[41]=(checkSum&0x00ff);
	}
	else
	{
		igmpV2QueryBuf[36]=0;
		igmpV2QueryBuf[37]=0;
		checkSum=br_ipv4Checksum(&igmpV2QueryBuf[34],8);
		igmpV2QueryBuf[36]=(checkSum&0xff00)>>8;
		igmpV2QueryBuf[37]=(checkSum&0x00ff);
	}

	if(igmpVersion==3)
	{
		return igmpV3QueryBuf;
	}
	else
	{
		return igmpV2QueryBuf;
	}
	
	return NULL;
}

void br_igmpQueryTimerExpired(unsigned long arg)
{
	struct net_bridge *br = (struct net_bridge*) arg;
	unsigned char *igmpBuf=NULL;
	struct sk_buff *skb;
	struct sk_buff *skb2;
	struct net_bridge_port *p, *n;
	struct net_bridge_port *prev;
	unsigned int fwdCnt=0;

//if igmpproxy opened, the igmp query send is handled by igmpproxy daemon
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if(IGMPProxyOpened && strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME))
#else
	if(IGMPProxyOpened)
#endif
	{
		return ;
	}
	
	if(igmpQueryEnabled==0)
	{
		return;
	}

	if(rtl_getGroupNum(IP_VERSION4)==0)
		return;
#if defined (CONFIG_RTL_QUERIER_SELECTION)
	if(br_querierSelection(br,4)==0)
	{
		return;
	}
#endif	

	skb=dev_alloc_skb(1024);
	if(skb==NULL)
	{
		return;
	}

	memset(skb->data,64,0);
	igmpBuf=br_generateIgmpQuery(br);
	if(igmpBuf==NULL)
	{
		return;
	}

	memcpy(skb->data,igmpBuf,64);

	skb->len = 0;
	if(igmpVersion==3)
	{
		skb_put(skb, 50);
	}
	else
	{
		skb_put(skb, 42);
	}
	
	skb->dev=br->dev;
	
	prev = NULL;
	fwdCnt=0;
	list_for_each_entry_safe(p, n, &br->port_list, list) 
	{ 
		if ((p->state == BR_STATE_FORWARDING) && (strncmp(p->dev->name, "peth",4)!=0) && (strncmp(p->dev->name, "pwlan",5)!=0)) 
		{
			if (prev != NULL) 
			{   
				if ((skb2 = skb_clone(skb, GFP_ATOMIC)) == NULL) 
				{
					br->dev->stats.tx_dropped++;
					kfree_skb(skb);
					return;
				} 
				skb2->dev=prev->dev;
				#if defined(CONFIG_COMPAT_NET_DEV_OPS)
				prev->dev->hard_start_xmit(skb2, prev->dev);
				#else
				prev->dev->netdev_ops->ndo_start_xmit(skb2,prev->dev);
				#endif                  
				fwdCnt++;
			}
				                                                                               
			prev = p;
		}
	}

	if (prev != NULL) 
	{
		skb->dev=prev->dev;
	       #if defined(CONFIG_COMPAT_NET_DEV_OPS)
		prev->dev->hard_start_xmit(skb, prev->dev);
		#else
		prev->dev->netdev_ops->ndo_start_xmit(skb,prev->dev);
		#endif                            
		fwdCnt++;
	}

	if(fwdCnt==0)
	{
		/*to avoid memory leak*/
		kfree_skb(skb);
	}
	return;
}

#if defined(CONFIG_RTL_MLD_SNOOPING)
static unsigned short br_ipv6Checksum(unsigned char *pktBuf, unsigned int pktLen, unsigned char  *ipv6PseudoHdrBuf)
{
	unsigned int  checksum=0;
	unsigned int count=pktLen;
	unsigned short   *ptr;

	/*compute ipv6 pseudo-header checksum*/
	ptr= (unsigned short  *) (ipv6PseudoHdrBuf);	
	for(count=0; count<20; count++) /*the pseudo header is 40 bytes long*/
	{
		  checksum+= ntohs(*ptr);
		  ptr++;
	}
	
	/*compute the checksum of mld buffer*/
	 count=pktLen;
	 ptr=(unsigned short  *) (pktBuf);	
	 while(count>1)
	 {
		  checksum+= ntohs(*ptr);
		  ptr++;
		  count -= 2;
	 }
	 
	if(count>0)
	{
		checksum+= *(pktBuf+pktLen-1)<<8; /*the last odd byte is treated as bit 15~8 of unsigned short*/
	}

	/* Roll over carry bits */
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum += (checksum >> 16);

	/* Return checksum */
	return ((uint16) ~ checksum);
	
}

static unsigned char* br_generateMldQuery(struct net_bridge * br)
{
	struct net_device* brDev = NULL;
	unsigned short checkSum=0;
	if(br==NULL)
	{
		return NULL;
	}
	
	brDev = br->dev;
	
	memcpy(&mldQueryBuf[6],brDev->dev_addr,6);			/*set source mac address*/
	
	memcpy(&mldQueryBuf[30],brDev->dev_addr,3);		/*set  mld query packet source ip address*/
	mldQueryBuf[30]=mldQueryBuf[30]|0x02;		
	memcpy(&mldQueryBuf[35],&brDev->dev_addr[3],3);		

	
	memcpy(ipv6PseudoHdrBuf,&mldQueryBuf[22],16);			/*set pseudo-header source ip*/
	if(mldVersion==2)
	{
		mldQueryBuf[19]=	0x24;
	}
	else
	{
		mldQueryBuf[19]=	0x20;
	}

	mldQueryBuf[64]=0;/*reset checksum*/
	mldQueryBuf[65]=0;
	if(mldVersion==2)
	{
		ipv6PseudoHdrBuf[35]=28;
		checkSum=br_ipv6Checksum(&mldQueryBuf[62],28,ipv6PseudoHdrBuf);
	}
	else
	{
		ipv6PseudoHdrBuf[35]=24;
		checkSum=br_ipv6Checksum(&mldQueryBuf[62],24,ipv6PseudoHdrBuf);
	}
	
	
	mldQueryBuf[64]=(checkSum&0xff00)>>8;
	mldQueryBuf[65]=(checkSum&0x00ff);
	return mldQueryBuf;
	
	
}


void br_mldQueryTimerExpired(unsigned long arg)
{
	struct net_bridge *br = (struct net_bridge*) arg;
	struct sk_buff *skb;
	struct sk_buff *skb2;
	struct net_bridge_port *p, *n;
	struct net_bridge_port *prev;
	unsigned int fwdCnt=0;
	unsigned char *mldBuf=NULL;

	if(mldQueryEnabled==0)
	{
		return;
	}
	if(rtl_getGroupNum(IP_VERSION6)==0)
		return;
#if defined (CONFIG_RTL_QUERIER_SELECTION)
	if(br_querierSelection(br,6)==0)
	{
		return;
	}
#endif	

	skb=dev_alloc_skb(1024);
	if(skb==NULL)
	{
		return;
	}
	
	memset(skb->data,86,0);
	mldBuf=br_generateMldQuery(br);
	if(mldBuf==NULL)
	{
		return;
	}
	
	if(mldVersion==2)
	{
		memcpy(skb->data,mldBuf,90);
		skb->len = 0;
		skb_put(skb, 90);
	}
	else
	{
		memcpy(skb->data,mldBuf,86);
		skb->len = 0;
		skb_put(skb, 86);
	}
 
	prev = NULL;
	fwdCnt=0;
	list_for_each_entry_safe(p, n, &br->port_list, list) 
	{ 
		if ((p->state == BR_STATE_FORWARDING) && (strncmp(p->dev->name, "peth",4)!=0) && (strncmp(p->dev->name, "pwlan",5)!=0)) 
		{
			if (prev != NULL) 
			{                                                                                       
				if ((skb2 = skb_clone(skb, GFP_ATOMIC)) == NULL) 
				{
					br->dev->stats.tx_dropped++;
					kfree_skb(skb);
					return;
				} 
				skb2->dev=prev->dev;
				#if defined(CONFIG_COMPAT_NET_DEV_OPS)
				prev->dev->hard_start_xmit(skb2, prev->dev);
				#else
				prev->dev->netdev_ops->ndo_start_xmit(skb2,prev->dev);
				#endif                  
				fwdCnt++;
			}
				                                                                               
			prev = p;
		}
	}

	if (prev != NULL) 
	{
		skb->dev=prev->dev;
	       #if defined(CONFIG_COMPAT_NET_DEV_OPS)
		prev->dev->hard_start_xmit(skb, prev->dev);
		#else
		prev->dev->netdev_ops->ndo_start_xmit(skb,prev->dev);
		#endif                            
		fwdCnt++;
	}

	if(fwdCnt==0)
	{
		/*to avoid memory leak*/
		kfree_skb(skb);
	}
	
	return;
}

#endif
void br_mCastQueryTimerExpired(unsigned long arg)
{
	struct net_bridge *br = (struct net_bridge*) arg;
	
	mod_timer(&br->mCastQuerytimer, jiffies+MCAST_QUERY_INTERVAL*HZ);
    #ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
		if(!strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME))
		{
			br_igmpQueryTimerExpired(arg);
			return;
		}
	#endif
	
	if(mCastQueryTimerCnt%2==0)
	{
		br_igmpQueryTimerExpired(arg);
	}
	else
	{
		#if defined (CONFIG_RTL_MLD_SNOOPING)
		br_mldQueryTimerExpired(arg);
		#endif
	}
	mCastQueryTimerCnt++;
	
	return;
}

void rtl_IgmpSnooping_BrInit_Hook(const char *name,struct net_device *dev)
{
	int res;

	if(strcmp(name,RTL_PS_BR0_DEV_NAME)==0)
	{
		rtl_multicastDeviceInfo_t devInfo;
		memset(&devInfo, 0, sizeof(rtl_multicastDeviceInfo_t ));
		strcpy(devInfo.devName, name);

		res=rtl_registerIgmpSnoopingModule(&brIgmpModuleIndex);
        #if 0
        printk("brIgmpModuleIndex = %d, [%s:%d]\n", brIgmpModuleIndex, __FUNCTION__, __LINE__);
        #endif
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
		if(res==0)
		{
			rtl_setIgmpSnoopingModuleDevInfo(brIgmpModuleIndex,&devInfo);
		}
#endif
		bridge0=netdev_priv(dev);
		if(bridge0!=NULL)
		{
			init_timer(&bridge0->mCastQuerytimer);
			bridge0->mCastQuerytimer.data=(unsigned long)bridge0;
			bridge0->mCastQuerytimer.expires=jiffies+MCAST_QUERY_INTERVAL*HZ;
			bridge0->mCastQuerytimer.function=(void*)br_mCastQueryTimerExpired;
			add_timer(&bridge0->mCastQuerytimer);
		}
		rtl_setIpv4UnknownMCastFloodMap(brIgmpModuleIndex, 0xFFFFFFFF);
#if defined(CONFIG_RTL_MLD_SNOOPING)
		rtl_setIpv6UnknownMCastFloodMap(brIgmpModuleIndex, 0xFFFFFFFF);
#endif
	}
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if(strcmp(name,RTL_PS_BR1_DEV_NAME)==0)
	{
		rtl_multicastDeviceInfo_t devInfo2;
		memset(&devInfo2, 0, sizeof(rtl_multicastDeviceInfo_t ));
		strcpy(devInfo2.devName, RTL_PS_BR1_DEV_NAME);

		res=rtl_registerIgmpSnoopingModule(&brIgmpModuleIndex_2);
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
		if(res==0)
		{
			 rtl_setIgmpSnoopingModuleDevInfo(brIgmpModuleIndex_2,&devInfo2);
		}
#endif
		bridge1=netdev_priv(dev);
		if(bridge1!=NULL)
		{
			init_timer(&bridge1->mCastQuerytimer);
			bridge1->mCastQuerytimer.data=(unsigned long)bridge1;
			bridge1->mCastQuerytimer.expires=jiffies+MCAST_QUERY_INTERVAL*HZ;
			bridge1->mCastQuerytimer.function=(void*)br_mCastQueryTimerExpired;
			add_timer(&bridge1->mCastQuerytimer);
		}
	}
#endif
	return;
}

void rtl_IgmpSnooping_BrDeinit_Hook(const char *name, int ret)
{
	if(ret)
		return;
	if(strcmp(name,RTL_PS_BR0_DEV_NAME)==0)
	{
		rtl_unregisterIgmpSnoopingModule(brIgmpModuleIndex);
#if defined (CONFIG_RTL_MLD_SNOOPING)
		if(bridge0 && timer_pending(&bridge0->mCastQuerytimer))
		{
			del_timer(&bridge0->mCastQuerytimer);
		}
#endif
		bridge0=NULL;
	}
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if(strcmp(name,RTL_PS_BR1_DEV_NAME)==0)
	{
		rtl_unregisterIgmpSnoopingModule(brIgmpModuleIndex_2);
#if defined (CONFIG_RTL_MLD_SNOOPING)
		if(bridge1 && timer_pending(&bridge1->mCastQuerytimer))
		{
			del_timer(&bridge1->mCastQuerytimer);
		}
#endif
		bridge1=NULL;
	}
#endif
	return ;
}

#if defined(CONFIG_RTL_HARDWARE_MULTICAST)
int rtl865x_generateBridgeDeviceInfo( struct net_bridge *br, rtl_multicastDeviceInfo_t *devInfo)
{
	struct net_bridge_port *p, *n;
	if((br==NULL) || (devInfo==NULL))
	{
		return -1;
	}

	memset(devInfo, 0, sizeof(rtl_multicastDeviceInfo_t));

#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)!=0 && strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME)!=0 )
#else
	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)!=0)
#endif
	{
		return -1;
	}
	strcpy(devInfo->devName,br->dev->name);
	list_for_each_entry_safe(p, n, &br->port_list, list)
	{
	    #if defined (CONFIG_OPENWRT_SDK)
		if(memcmp(p->dev->name, RTL_PS_LAN_P0_DEV_NAME,4)!=0)
		#else
		if(memcmp(p->dev->name, RTL_PS_ETH_NAME,3)!=0)
	    #endif
		{
			devInfo->swPortMask|=(1<<p->port_no);
		}
		devInfo->portMask|=(1<<p->port_no);
	}

	return 0;
}
int rtl865x_HwMcast_Setting_HOOK(struct net_bridge *br, struct net_device *dev)
{
	int ret=0;
	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)==0)
	{
		rtl_multicastDeviceInfo_t brDevInfo;
		rtl865x_generateBridgeDeviceInfo(br, &brDevInfo);
		if(brIgmpModuleIndex!=0xFFFFFFFF)
		{
			rtl_setIgmpSnoopingModuleDevInfo(brIgmpModuleIndex,&brDevInfo);
		}
		br0SwFwdPortMask=brDevInfo.swPortMask;
	}
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if(strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME)==0)
	{
		rtl_multicastDeviceInfo_t brDevInfo;
		rtl865x_generateBridgeDeviceInfo(br, &brDevInfo);
		if(brIgmpModuleIndex!=0xFFFFFFFF)
		{
			rtl_setIgmpSnoopingModuleDevInfo(brIgmpModuleIndex_2,&brDevInfo);
		}
		br1SwFwdPortMask=brDevInfo.swPortMask;
	}
#endif/*CONFIG_RTK_VLAN_WAN_TAG_SUPPORT*/
	return ret;
}
#endif
/*int and deint end*/

/*input and out begin*/
static void ConvertMulticatIPtoMacAddr(__u32 group, unsigned char *gmac)
{
	__u32 u32tmp, tmp;
	int i;

	u32tmp = group & 0x007FFFFF;
	gmac[0]=0x01; gmac[1]=0x00; gmac[2]=0x5e;
	for (i=5; i>=3; i--) {
		tmp=u32tmp&0xFF;
		gmac[i]=tmp;
		u32tmp >>= 8;
	}
}
static char igmp_type_check(struct sk_buff *skb, unsigned char *gmac,unsigned int *gIndex,unsigned int *moreFlag)
{
        struct iphdr *iph;
	__u8 hdrlen;
	struct igmphdr *igmph;
	int i;
	unsigned int groupAddr=0;// add  for fit igmp v3
	*moreFlag=0;
	/* check IP header information */
	iph=(struct iphdr *)skb_network_header(skb);
	hdrlen = iph->ihl << 2;
	if ((iph->version != 4) &&  (hdrlen < 20))
		return -1;
	if (ip_fast_csum((u8 *)iph, iph->ihl) != 0)
		return -1;
	{ /* check the length */
		__u32 len = ntohs(iph->tot_len);
		if (skb->len < len || len < hdrlen)
			return -1;
	}
	/* parsing the igmp packet */
	igmph = (struct igmphdr *)((u8*)iph+hdrlen);



	if ((igmph->type==IGMP_HOST_MEMBERSHIP_REPORT) ||
	    (igmph->type==IGMPV2_HOST_MEMBERSHIP_REPORT))
	{
		groupAddr = ntohl(igmph->group);
		if(!IN_MULTICAST(groupAddr))
		{
				return -1;
		}

		ConvertMulticatIPtoMacAddr(groupAddr, gmac);

		return 1; /* report and add it */
	}
	else if (igmph->type==IGMPV3_HOST_MEMBERSHIP_REPORT)	{


		/*for support igmp v3 ; plusWang add 2009-0311*/
		struct igmpv3_report *igmpv3report=(struct igmpv3_report * )igmph;
		struct igmpv3_grec	*igmpv3grec=NULL;
		//printk("%s:%d,*gIndex is %d,igmpv3report->ngrec is %d\n",__FUNCTION__,__LINE__,*gIndex,igmpv3report->ngrec);
		if(*gIndex>=ntohs(igmpv3report->ngrec))
		{
			*moreFlag=0;
			return -1;
		}

		for(i=0;i<ntohs(igmpv3report->ngrec);i++)
		{

			if(i==0)
			{
				igmpv3grec = (struct igmpv3_grec *)(&(igmpv3report->grec)); /*first igmp group record*/
			}
			else
			{
				igmpv3grec=(struct igmpv3_grec *)((unsigned char*)igmpv3grec+8+ntohs(igmpv3grec->grec_nsrcs)*4+(igmpv3grec->grec_auxwords)*4);


			}

			if(i!=*gIndex)
			{

				continue;
			}

			if(i==(ntohs(igmpv3report->ngrec)-1))
			{
				/*last group record*/
				*moreFlag=0;
			}
			else
			{
				*moreFlag=1;
			}

			/*gIndex move to next group*/
			*gIndex=*gIndex+1;

			groupAddr=ntohl(igmpv3grec->grec_mca);
			//printk("%s:%d,groupAddr is %d.%d.%d.%d\n",__FUNCTION__,__LINE__,NIPQUAD(groupAddr));
			if(!IN_MULTICAST(groupAddr))
			{
				return -1;
			}

			ConvertMulticatIPtoMacAddr(groupAddr, gmac);
			if(((igmpv3grec->grec_type == IGMPV3_CHANGE_TO_INCLUDE) || (igmpv3grec->grec_type == IGMPV3_MODE_IS_INCLUDE))&& (ntohs(igmpv3grec->grec_nsrcs)==0))
			{
				return 2; /* leave and delete it */
			}
			else if((igmpv3grec->grec_type == IGMPV3_CHANGE_TO_EXCLUDE) ||
				(igmpv3grec->grec_type == IGMPV3_MODE_IS_EXCLUDE) ||
				(igmpv3grec->grec_type == IGMPV3_ALLOW_NEW_SOURCES))
			{
				return 1;
			}
			else
			{
				/*ignore it*/
			}

			return -1;
		}

		/*avoid dead loop in case of initial gIndex is too big*/
		if(i>=(ntohs(igmpv3report->ngrec)-1))
		{
			/*last group record*/
			*moreFlag=0;
			return -1;
		}


	}
	else if (igmph->type==IGMP_HOST_LEAVE_MESSAGE){

		groupAddr = ntohl(igmph->group);
		if(!IN_MULTICAST(groupAddr))
		{
				return -1;
		}

		ConvertMulticatIPtoMacAddr(groupAddr, gmac);
		return 2; /* leave and delete it */
	}


	return -1;
}

int bitmask_to_id(unsigned char val)
{
	int i;
	for (i=0; i<8; i++) {
		if (val & (1 <<i))
			break;
	}

	if(i>=8)
	{
		i=7;
	}
	return (i);
}

int chk_igmp_ext_entry(
	struct net_bridge_fdb_entry *fdb ,
	unsigned char *srcMac)
{

	int i2;
	unsigned char *add;
	add = fdb->addr.addr;

	for(i2=0 ; i2 < FDB_IGMP_EXT_NUM ; i2++){
		if(fdb->igmp_fdb_arr[i2].valid == 1){
			if(!memcmp(fdb->igmp_fdb_arr[i2].SrcMac , srcMac ,6)){
				return 1;
			}
		}
	}
	return 0;
}

void add_igmp_ext_entry(	struct net_bridge_fdb_entry *fdb ,
	unsigned char *srcMac , unsigned char portComeIn)
{
	int i2;
	unsigned char *add;
	add = fdb->addr.addr;

	DEBUG_PRINT("add_igmp,DA=%02x:%02x:%02x:%02x:%02x:%02x ; SA=%02x:%02x:%02x:%02x:%02x:%02x\n",
		add[0],add[1],add[2],add[3],add[4],add[5],
		srcMac[0],srcMac[1],srcMac[2],srcMac[3],srcMac[4],srcMac[5]);

	for(i2=0 ; i2 < FDB_IGMP_EXT_NUM ; i2++){
		if(fdb->igmp_fdb_arr[i2].valid == 0){
			fdb->igmp_fdb_arr[i2].valid = 1	;
			fdb->igmp_fdb_arr[i2].ageing_time = jiffies ;
			memcpy(fdb->igmp_fdb_arr[i2].SrcMac , srcMac ,6);
			fdb->igmp_fdb_arr[i2].port = portComeIn ;
			fdb->portlist |= portComeIn;
			fdb->portUsedNum[bitmask_to_id(portComeIn)]++;
			DEBUG_PRINT("portUsedNum[%d]=%d\n\n",bitmask_to_id(portComeIn) , fdb->portUsedNum[bitmask_to_id(portComeIn)]);
			return ;
		}
	}
	DEBUG_PRINT("%s:entry Rdy existed!!!\n", __FUNCTION__);
}

void del_igmp_ext_entry(	struct net_bridge_fdb_entry *fdb ,unsigned char *srcMac , unsigned char portComeIn,unsigned char expireFlag )
{
	int i2;
	unsigned char *add;
	add = fdb->addr.addr;

	for(i2=0 ; i2 < FDB_IGMP_EXT_NUM ; i2++){
		if(fdb->igmp_fdb_arr[i2].valid == 1){
			if(!memcmp(fdb->igmp_fdb_arr[i2].SrcMac , srcMac ,6))
			{
				if(expireFlag)
				{
					fdb->igmp_fdb_arr[i2].ageing_time -=  300*HZ;
					fdb->igmp_fdb_arr[i2].valid = 0;
				}
				else
				{
					fdb->igmp_fdb_arr[i2].ageing_time = jiffies-(IGMP_EXPIRE_TIME-M2U_DELAY_DELETE_TIME); //delay 10s to expire
					DEBUG_PRINT("\nexpireFlag:%d,del_igmp_ext_entry,DA=%02x:%02x:%02x:%02x:%02x:%02x ; SA=%02x:%02x:%02x:%02x:%02x:%02x success!!!\n",
						expireFlag,add[0],add[1],add[2],add[3],add[4],add[5],
						srcMac[0],srcMac[1],srcMac[2],srcMac[3],srcMac[4],srcMac[5]);
				}
				DEBUG_PRINT("\ndel_igmp_ext_entry,DA=%02x:%02x:%02x:%02x:%02x:%02x ; SA=%02x:%02x:%02x:%02x:%02x:%02x success!!!\n",
				add[0],add[1],add[2],add[3],add[4],add[5],
				srcMac[0],srcMac[1],srcMac[2],srcMac[3],srcMac[4],srcMac[5]);

				//DEBUG_PRINT("%s:success!!\n", __FUNCTION__);

				if(portComeIn != 0){
					int index;
					index = bitmask_to_id(portComeIn);
					fdb->portUsedNum[index]--;
					if(fdb->portUsedNum[index] <= 0){
						DEBUG_PRINT("portUsedNum[%d] == 0 ,update portlist from (%x)  " ,index ,fdb->portlist);
						fdb->portlist &= ~ portComeIn;
						DEBUG_PRINT("to (%x) \n" ,fdb->portlist);

						if(fdb->portUsedNum[index] < 0){
						DEBUG_PRINT("!! portUsedNum[%d]=%d < 0 at (del_igmp_ext_entry)  \n" ,index ,fdb->portUsedNum[index]);
						fdb->portUsedNum[index] = 0;
						}
					}else{
						DEBUG_PRINT("(del) portUsedNum[%d] = %d \n" ,index, fdb->portUsedNum[index]);
					}

				}
				DEBUG_PRINT("\n");
				return ;
			}
		}
	}

	DEBUG_PRINT("%s:entry not existed!!\n\n", __FUNCTION__);
}

void update_igmp_ext_entry(	struct net_bridge_fdb_entry *fdb ,
	unsigned char *srcMac , unsigned char portComeIn)
{
	int i2;
	unsigned char *add;
	add = fdb->addr.addr;

	DEBUG_PRINT("update_igmp,DA=%02x:%02x:%02x:%02x:%02x:%02x ; SA=%02x:%02x:%02x:%02x:%02x:%02x\n",
	add[0],add[1],add[2],add[3],add[4],add[5],
	srcMac[0],srcMac[1],srcMac[2],srcMac[3],srcMac[4],srcMac[5]);

	for(i2=0 ; i2 < FDB_IGMP_EXT_NUM ; i2++){
		if(fdb->igmp_fdb_arr[i2].valid == 1){
			if(!memcmp(fdb->igmp_fdb_arr[i2].SrcMac , srcMac ,6)){

				fdb->igmp_fdb_arr[i2].ageing_time = jiffies ;
				//DEBUG_PRINT("update jiffies ok!\n");
				if(fdb->igmp_fdb_arr[i2].port != portComeIn){

					unsigned char port_orig = fdb->igmp_fdb_arr[i2].port ;
					int index = bitmask_to_id(port_orig);

					fdb->portUsedNum[index]-- ;
					DEBUG_PRINT("(--) portUsedNum[%d]=%d\n",index , fdb->portUsedNum[index] );
					if(fdb->portUsedNum[index] <= 0){
						fdb->portlist &= ~(port_orig);
						if(fdb->portUsedNum[index]< 0){
							DEBUG_PRINT("!! portNum[%d] < 0 at (update_igmp_ext_entry)\n",index);
							fdb->portUsedNum[index] = 0 ;
						}
					}


					fdb->portUsedNum[bitmask_to_id(portComeIn)]++;
					DEBUG_PRINT("(++) portUsedNum[%d]=%d\n",bitmask_to_id(portComeIn) , fdb->portUsedNum[bitmask_to_id(portComeIn)] );
					fdb->portlist |= portComeIn;


					fdb->igmp_fdb_arr[i2].port = portComeIn ;
					DEBUG_PRINT("	!!! portlist be updated:%x !!!!\n",fdb->portlist);

				}
				return ;
			}
		}
	}

	DEBUG_PRINT("%s: ...fail!!\n", __FUNCTION__);
}

static void br_update_igmp_snoop_fdb(unsigned char op, struct net_bridge *br, struct net_bridge_port *p, unsigned char *dest
										,struct sk_buff *skb)
{
	struct net_bridge_fdb_entry *dst;
	unsigned char *src;
	unsigned short del_group_src=0;
	unsigned char port_comein;
	int tt1;
	u16 vid = 0;

#if defined (MCAST_TO_UNICAST)
    struct net_device *dev = NULL;
#endif

	br_vlan_get_tag(skb, &vid);

#if defined (MCAST_TO_UNICAST)
	if(!dest)	return;
	if( !MULTICAST_MAC(dest)
#if defined (IPV6_MCAST_TO_UNICAST)
		&& !IPV6_MULTICAST_MAC(dest)
#endif
	   )
	   {
	   	return;
	   }
#endif

#if defined( CONFIG_RTL_HARDWARE_MULTICAST) || defined(CONFIG_RTL865X_LANPORT_RESTRICTION)

	if(skb->srcPort!=0xFFFF)
	{
		port_comein = 1<<skb->srcPort;
	}
	else
	{
		port_comein=0x80;
	}

#else
	if(p && p->dev && p->dev->name && !memcmp(p->dev->name, RTL_PS_LAN_P0_DEV_NAME, 4))
	{
		port_comein = 0x01;
	}

	if(p && p->dev && p->dev->name && !memcmp(p->dev->name, RTL_PS_WLAN_NAME, 4))
	{
		port_comein=0x80;
	}

#endif
//	src=(unsigned char*)(skb->mac.raw+ETH_ALEN);
	src=(unsigned char*)(skb_mac_header(skb)+ETH_ALEN);
	/* check whether entry exist */
	dst = __br_fdb_get(br, dest,vid);

	if (op == 1) /* add */
	{
        if(dst == NULL) {
            /* insert one fdb entry */
            DEBUG_PRINT("insert one fdb entry\n");
            br_fdb_insert(br, p, dest,vid);
            dst = __br_fdb_get(br, dest,vid);
            if(dst !=NULL)
            {
                dst->igmpFlag=1;
                dst->is_local=0;
                dst->portlist = port_comein; 
                dst->group_src = dst->group_src | (1 << p->port_no);
            }

        }

        if(dst) {
            dst->group_src = dst->group_src | (1 << p->port_no);
            dst->updated = jiffies;

            tt1 = chk_igmp_ext_entry(dst , src); 
            if(tt1 == 0)
            {
                add_igmp_ext_entry(dst , src , port_comein);									
            }
            else
            {
                update_igmp_ext_entry(dst , src , port_comein);
            }

#if defined (MCAST_TO_UNICAST)
			/*process wlan client join --- start*/
			if (p && p->dev && p->dev->name && !memcmp(p->dev->name, RTL_PS_WLAN_NAME, 4))
			{
				dst->portlist |= 0x80;
				port_comein = 0x80;
				//dev = __dev_get_by_name(&init_net,RTL_PS_WLAN0_DEV_NAME);
				dev=p->dev;
				if (dev)
				{
					unsigned char StaMacAndGroup[20];
					memcpy(StaMacAndGroup, dest, 6);
					memcpy(StaMacAndGroup+6, src, 6);
				#if defined(CONFIG_COMPAT_NET_DEV_OPS)
					if (dev->do_ioctl != NULL)
					{
						dev->do_ioctl(dev, (struct ifreq*)StaMacAndGroup, 0x8B80);
						DEBUG_PRINT("... add to wlan mcast table:  DA:%02x:%02x:%02x:%02x:%02x:%02x ; SA:%02x:%02x:%02x:%02x:%02x:%02x\n",
							StaMacAndGroup[0],StaMacAndGroup[1],StaMacAndGroup[2],StaMacAndGroup[3],StaMacAndGroup[4],StaMacAndGroup[5],
							StaMacAndGroup[6],StaMacAndGroup[7],StaMacAndGroup[8],StaMacAndGroup[9],StaMacAndGroup[10],StaMacAndGroup[11]);
					}
				#else
					if (dev->netdev_ops->ndo_do_ioctl != NULL)
					{
						dev->netdev_ops->ndo_do_ioctl(dev, (struct ifreq*)StaMacAndGroup, 0x8B80);
						DEBUG_PRINT("... add to wlan mcast table:  DA:%02x:%02x:%02x:%02x:%02x:%02x ; SA:%02x:%02x:%02x:%02x:%02x:%02x\n",
							StaMacAndGroup[0],StaMacAndGroup[1],StaMacAndGroup[2],StaMacAndGroup[3],StaMacAndGroup[4],StaMacAndGroup[5],
							StaMacAndGroup[6],StaMacAndGroup[7],StaMacAndGroup[8],StaMacAndGroup[9],StaMacAndGroup[10],StaMacAndGroup[11]);
					}
				#endif


				}
			}
	/*process wlan client join --- end*/
        }
#endif
	}
	else if (op == 2 && dst) /* delete */
	{
		DEBUG_PRINT("dst->group_src = %x change to ",dst->group_src);
			del_group_src = ~(1 << p->port_no);
			dst->group_src = dst->group_src & del_group_src;
		DEBUG_PRINT(" %x ; p->port_no=%x \n",dst->group_src ,p->port_no);

		/*process wlan client leave --- start*/
		if (p && p->dev && p->dev->name && !memcmp(p->dev->name, RTL_PS_WLAN_NAME, 4))
		{
			#if 0//def	MCAST_TO_UNICAST
			//struct net_device *dev = __dev_get_by_name(&init_net,RTL_PS_WLAN0_DEV_NAME);
			struct net_device *dev=p->dev;
			if (dev)
			{
				unsigned char StaMacAndGroup[12];
				memcpy(StaMacAndGroup, dest , 6);
				memcpy(StaMacAndGroup+6, src, 6);
			#if defined(CONFIG_COMPAT_NET_DEV_OPS)
				if (dev->do_ioctl != NULL)
				{
					dev->do_ioctl(dev, (struct ifreq*)StaMacAndGroup, 0x8B81);
					DEBUG_PRINT("(del) wlan0 ioctl (del) M2U entry da:%02x:%02x:%02x-%02x:%02x:%02x; sa:%02x:%02x:%02x-%02x:%02x:%02x\n",
						StaMacAndGroup[0],StaMacAndGroup[1],StaMacAndGroup[2],StaMacAndGroup[3],StaMacAndGroup[4],StaMacAndGroup[5],
						StaMacAndGroup[6],StaMacAndGroup[7],StaMacAndGroup[8],StaMacAndGroup[9],StaMacAndGroup[10],StaMacAndGroup[11]);
				}
			#else
				if (dev->netdev_ops->ndo_do_ioctl != NULL)
				{
					dev->netdev_ops->ndo_do_ioctl(dev, (struct ifreq*)StaMacAndGroup, 0x8B81);
					DEBUG_PRINT("(del) wlan0 ioctl (del) M2U entry da:%02x:%02x:%02x-%02x:%02x:%02x; sa:%02x:%02x:%02x-%02x:%02x:%02x\n",
						StaMacAndGroup[0],StaMacAndGroup[1],StaMacAndGroup[2],StaMacAndGroup[3],StaMacAndGroup[4],StaMacAndGroup[5],
						StaMacAndGroup[6],StaMacAndGroup[7],StaMacAndGroup[8],StaMacAndGroup[9],StaMacAndGroup[10],StaMacAndGroup[11]);
				}
			#endif

			}
			#endif
			//dst->portlist &= ~0x80;	// move to del_igmp_ext_entry
			port_comein	= 0x80;
		}
		/*process wlan client leave --- end*/

		/*process entry del , portlist update*/
		if(dst->portlist)
		{
			del_igmp_ext_entry(dst , src ,port_comein,0);

			if (dst->portlist == 0)  // all joined sta are gone
			{
				DEBUG_PRINT("----all joined sta are gone,make it expired after 10 seconds----\n");
				dst->updated = jiffies -(300*HZ-M2U_DELAY_DELETE_TIME); // make it expired in 10s
		    }
		}

	}
}
static void br_flood(struct net_bridge *br, struct sk_buff *skb,
		     struct sk_buff *skb0,
		     void (*__packet_hook)(const struct net_bridge_port *p,
					   struct sk_buff *skb),
		     bool forward)
{
	struct net_bridge_port *p;
	struct net_bridge_port *prev;
	const unsigned char *dest = eth_hdr(skb)->h_dest;

	prev = NULL;

	list_for_each_entry_rcu(p, &br->port_list, list) {
		if (forward && (p->flags & BR_ISOLATE_MODE))
		{
			continue;
		}

		
		/*patch for wan/lan receive duplicate unknown unicast/broadcast packet when pppoe/ipv6 passthrough enable*/
		/*except the packet dmac=33:33:xx:xx:xx:xx*/
		if((strcmp(skb->dev->name,"peth0")==0)&&(!(dest[0]==0x33&&dest[1]==0x33)))
		{
			 if((strncmp(p->dev->name,"eth",3)==0))
			 {
				continue;
			 }				
		}
		
#if !(defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F))
		
		/*patch for lan->wan duplicat packet(dmac=33:33:ff:xx:xx:xx) when pppoe/ipv6 passthrough enable*/
		if(((strcmp(skb->dev->name,"eth0")==0))
			&&((dest[0]==0x33)&&(dest[1]==0x33)&&(dest[2]==0xff))
		#if defined(CONFIG_RTK_VLAN_NEW_FEATURE)
			&&(rtk_vlan_support_enable==0)
		#endif
		)
		{
			if((strncmp(p->dev->name,"peth0",5)==0))
			{
				continue;
			}
		}
#endif			

		prev = rtl_maybe_deliver(prev, p, skb, __packet_hook);
		if (IS_ERR(prev))
		{
			goto out;
		}
	}

	if (!prev)
	{
		goto out;
	}

	if (skb0)
	{
		rtl_deliver_clone(prev, skb, __packet_hook);
	}
	else
		__packet_hook(prev, skb);
	return;

out:
	if (!skb0)
		kfree_skb(skb);
}


void br_flood_deliver(struct net_bridge *br, struct sk_buff *skb)
{
	br_flood(br, skb, NULL, __rtl_br_deliver, 0);
}
	
/* called under bridge lock */
void br_flood_forward(struct net_bridge *br, struct sk_buff *skb, struct sk_buff *skb2)
{
	br_flood(br, skb, skb2, __rtl_br_forward, 1);
}

static void br_multicast(struct net_bridge *br, unsigned int fwdPortMask, struct sk_buff *skb, int clone,
		  void (*__packet_hook)(const struct net_bridge_port *p, struct sk_buff *skb))
{
	struct net_bridge_port *prev;
	struct net_bridge_port *p, *n;
	unsigned short port_bitmask=0;
	
	prev = NULL;
	list_for_each_entry_safe(p, n, &br->port_list, list) {
		port_bitmask = (1 << p->port_no);
		if ((port_bitmask & fwdPortMask) == 0)
			continue;
		
		prev = rtl_maybe_deliver(prev, p, skb, __packet_hook);
		if (IS_ERR(prev))
		{
			goto out;
		}
	}

	if (!prev)
	{
		goto out;
	}

	if (clone)
	{
		rtl_deliver_clone(prev, skb, __packet_hook);
	}
	else
		__packet_hook(prev, skb);
	return;
	
out:
	if (!clone)
		kfree_skb(skb);
}

void br_multicast_deliver(struct net_bridge *br, unsigned int fwdPortMask, struct sk_buff *skb, int clone)
{
	br_multicast(br, fwdPortMask, skb, clone, __rtl_br_deliver);
}
void br_multicast_forward(struct net_bridge *br, unsigned int fwdPortMask, struct sk_buff *skb, int clone)
{
	br_multicast(br, fwdPortMask, skb, clone, __rtl_br_forward);
}

#if defined(CONFIG_RTL_HARDWARE_MULTICAST)
unsigned int rtl865x_getPhyFwdPortMask(struct net_bridge *br,unsigned int brFwdPortMask)
{
	unsigned int phyPortMask = 0;
	unsigned int port_bitmask=0;
	struct net_bridge_port *p, *n;
	struct dev_priv *devPriv = NULL;
	if(br==NULL)
	{
		return 0;
	}
	list_for_each_entry_safe(p, n, &br->port_list, list)
	{
		port_bitmask=1<<p->port_no;
		if(port_bitmask&brFwdPortMask)
		{
			devPriv=(struct dev_priv *)netdev_priv(p->dev);
			if(devPriv){
				phyPortMask |= devPriv->portmask;
				#if 0
				if(net_ratelimit())
					printk("[%s:%d]%s,%x,\n",__FUNCTION__,__LINE__,p->dev->name,devPriv->portmask);
				#endif
			}
		}
	}
	return phyPortMask;
}

int rtl865x_ipMulticastHardwareAccelerate(struct net_bridge *br, unsigned int brFwdPortMask,
												unsigned int srcPort,unsigned int srcVlanId,
												unsigned int srcIpAddr, unsigned int destIpAddr)
{
	int ret;
	unsigned int tagged_portmask=0;
	struct rtl_multicastDataInfo multicastDataInfo;
	struct rtl_multicastFwdInfo  multicastFwdInfo;

	rtl865x_tblDrv_mCast_t * existMulticastEntry;
	rtl865x_mcast_fwd_descriptor_t  fwdDescriptor;
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
	rtl865x_mcast_fwd_descriptor_t	fwdDescriptor2;
#endif

	#if 0
    //if(net_ratelimit())
	    printk("%s:%d,br:%s,srcPort is %d,srcVlanId is %d,srcIpAddr is 0x%x,destIpAddr is 0x%x\n",
	    __FUNCTION__,__LINE__,br->dev->name,srcPort,srcVlanId,srcIpAddr,destIpAddr);
	#endif


#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT

	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)!=0 &&strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME)!=0 )
	{
		return -1;
	}
	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)==0 && (brFwdPortMask & br0SwFwdPortMask))
	{
		return -1;
	}

	if(strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME)==0 && (brFwdPortMask & br1SwFwdPortMask))
	{
		return -1;
	}
#else

	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)!=0)
	{
		return -1;
	}

#if 0
	if(net_ratelimit())
    	printk("brFwdPortMask = %x, br0SwFwdPortMask = %x, [%s:%d]\n", brFwdPortMask, br0SwFwdPortMask, __FUNCTION__, __LINE__);
#endif

#ifdef CONFIG_RTL_HW_MCAST_WIFI
	if(hwwifiEnable == 0)
	{
		if(brFwdPortMask & br0SwFwdPortMask)
 			return -1;
 	}
#else	
	if(brFwdPortMask & br0SwFwdPortMask)
	{
		return -1;
	}
#endif
#endif

	#if 0
    if(net_ratelimit())
	printk("%s:%d,destIpAddr is 0x%x, srcIpAddr is 0x%x, srcVlanId is %d, srcPort is %d\n",__FUNCTION__,__LINE__,destIpAddr, srcIpAddr, srcVlanId, srcPort);
    #endif
	
	existMulticastEntry=rtl865x_findMCastEntry(destIpAddr, srcIpAddr, (unsigned short)srcVlanId, (unsigned short)srcPort);
	if(existMulticastEntry!=NULL)
	{
		return 0;
	}
	if(brFwdPortMask==0)
	{
		rtl865x_blockMulticastFlow(srcVlanId, srcPort, srcIpAddr, destIpAddr);
		return 0;
	}
	multicastDataInfo.ipVersion=4;
	multicastDataInfo.sourceIp[0]=  srcIpAddr;
	multicastDataInfo.groupAddr[0]=  destIpAddr;

	/*add hardware multicast entry*/
#if 1//!defined(CONFIG_RTL_MULTI_LAN_DEV)

	#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)==0)
	{
		memset(&fwdDescriptor, 0, sizeof(rtl865x_mcast_fwd_descriptor_t ));
		strcpy(fwdDescriptor.netifName,"eth*");
		fwdDescriptor.fwdPortMask=0xFFFFFFFF;
		ret= rtl_getMulticastDataFwdInfo(nicIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
	}
	else if(strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME)==0)
	{
		memset(&fwdDescriptor, 0, sizeof(rtl865x_mcast_fwd_descriptor_t ));
		strcpy(fwdDescriptor.netifName,"eth2");
		fwdDescriptor.fwdPortMask=0xFFFFFFFF;
		ret= rtl_getMulticastDataFwdInfo(nicIgmpModuleIndex_2, &multicastDataInfo, &multicastFwdInfo);
	}
	#else
	memset(&fwdDescriptor, 0, sizeof(rtl865x_mcast_fwd_descriptor_t ));
	strcpy(fwdDescriptor.netifName,"eth*");
	fwdDescriptor.fwdPortMask=0xFFFFFFFF;

	ret= rtl_getMulticastDataFwdInfo(nicIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
    #if 0
    if(net_ratelimit())
	printk("%s:%d,ret:%d,srcPort is %d,srcVlanId is %d,srcIpAddr is 0x%x,destIpAddr is 0x%x\n",
	__FUNCTION__,__LINE__,ret,srcPort,srcVlanId,srcIpAddr,destIpAddr);
    #endif
	#endif
	if(ret!=0)
	{
		return -1;
	}
	else
	{
		if(multicastFwdInfo.cpuFlag)
		{
			fwdDescriptor.toCpu=1;
		}
		fwdDescriptor.fwdPortMask=multicastFwdInfo.fwdPortMask & (~(1<<srcPort));
	}
    #if 0
	if(net_ratelimit())
	printk("[%s:%d]fwdDescriptor.fwdPortMask=%x,dip:%x,sip:%x.\n",__FUNCTION__,__LINE__,
		destIpAddr,srcIpAddr,fwdDescriptor.fwdPortMask);
    #endif
#else/*!CONFIG_RTL_MULTI_LAN_DEV*/
	memset(&fwdDescriptor, 0, sizeof(rtl865x_mcast_fwd_descriptor_t ));
	strcpy(fwdDescriptor.netifName,RTL_BR_NAME);

	ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
	if(multicastFwdInfo.cpuFlag)
	{
		fwdDescriptor.toCpu=1;
	}

	fwdDescriptor.fwdPortMask = rtl865x_getPhyFwdPortMask(br,brFwdPortMask) & (~(1<<srcPort));
    #if 0
    if(net_ratelimit())
	printk("srcPort = %x, fwdDescriptor.fwdPortMask=%x, [%s:%d]\n",srcPort, fwdDescriptor.fwdPortMask, __FUNCTION__,__LINE__);
    #endif
#endif/*!CONFIG_RTL_MULTI_LAN_DEV*/

	if(fwdDescriptor.fwdPortMask==0)
		return -1;

#if defined(CONFIG_RTL_HW_VLAN_SUPPORT)
	if(rtl_hw_vlan_ignore_tagged_mc == 1)
		tagged_portmask = rtl_hw_vlan_get_tagged_portmask();
#endif
#if 0
    if(net_ratelimit())
	printk("%s:%d,srcPort is %d,srcVlanId is %d,srcIpAddr is 0x%x,destIpAddr is 0x%x,pmsk:%x\n",
	__FUNCTION__,__LINE__,srcPort,srcVlanId,srcIpAddr,destIpAddr,fwdDescriptor.fwdPortMask);
#endif
	if((fwdDescriptor.fwdPortMask & tagged_portmask) == 0)
	{
		ret=rtl865x_addMulticastEntry(destIpAddr, srcIpAddr, (unsigned short)srcVlanId, (unsigned short)srcPort,
							&fwdDescriptor, 1, 0, 0, 0);
	}

	
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
	if(hwwifiEnable)
	{
		memset(&fwdDescriptor2, 0, sizeof(rtl865x_mcast_fwd_descriptor_t ));
		
		strcpy(fwdDescriptor2.netifName,RTL_BR_NAME);
				
		if(brFwdPortMask & br0SwFwdPortMask)
				
		{
			fwdDescriptor2.toCpu=1;
		}	
		if(fwdDescriptor2.toCpu)
			fwdDescriptor2.fwdPortMask |= BIT(6);
				
		if((fwdDescriptor2.fwdPortMask & tagged_portmask) == 0)
		{
					
			//printk("%s:%d,br:%s,brFwdPortMask:%x,swFwdPortMask:%x,asicfwdPortmask:%x,srcPort is %d,srcVlanId is %d,srcIpAddr is 0x%x,destIpAddr is 0x%x\n",__FUNCTION__,__LINE__,br->dev->name,brFwdPortMask,swFwdPortMask,fwdDescriptor2.fwdPortMask,srcPort,srcVlanId,srcIpAddr,destIpAddr);
			ret=rtl865x_addMulticastEntry(destIpAddr, srcIpAddr, (unsigned short)srcVlanId, (unsigned short)srcPort,
										&fwdDescriptor2, 0, 0, 0, 0);
		}
	}
#endif

	return 0;
}
#endif

#if defined (CONFIG_RTL_MLD_SNOOPING)
/*Convert  MultiCatst IPV6_Addr to MAC_Addr*/
static void CIPV6toMac
	(unsigned char* icmpv6_McastAddr, unsigned char *gmac )
{
	/*ICMPv6 valid addr 2^32 -1*/
	gmac[0] = 0x33;
	gmac[1] = 0x33;
	gmac[2] = icmpv6_McastAddr[12];
	gmac[3] = icmpv6_McastAddr[13];
	gmac[4] = icmpv6_McastAddr[14];
	gmac[5] = icmpv6_McastAddr[15];
}
static char ICMPv6_check(struct sk_buff *skb , unsigned char *gmac, unsigned int *gIndex,unsigned int *moreFlag)
{

	struct ipv6hdr *ipv6h;
	char* protoType;
	int i = 0;
	*moreFlag=0;

	/* check IPv6 header information */
	//ipv6h = skb->nh.ipv6h;
	ipv6h = (struct ipv6hdr *)skb_network_header(skb);
	if(ipv6h->version != 6){
		//printk("ipv6h->version != 6\n");
		return -1;
	}


	/*Next header: IPv6 hop-by-hop option (0x00)*/
	if(ipv6h->nexthdr == 0)	{
		protoType = (unsigned char*)( (unsigned char*)ipv6h + sizeof(struct ipv6hdr) );
	}else{
		//printk("ipv6h->nexthdr != 0\n");
		return -1;
	}

	if(protoType[0] == 0x3a){

		//printk("recv icmpv6 packet\n");
		struct icmp6hdr* icmpv6h = (struct icmp6hdr*)(protoType + 8);
		unsigned char* icmpv6_McastAddr ;

		if(icmpv6h->icmp6_type == ICMPV6_MGM_REPORT){

			icmpv6_McastAddr = (unsigned char*)((unsigned char*)icmpv6h + 8);
			#ifdef	DBG_ICMPv6
			printk("Type: 0x%x (Multicast listener report) \n",icmpv6h->icmp6_type);
			#endif
			if(icmpv6_McastAddr[0] != 0xFF)
				return -1;
			CIPV6toMac(icmpv6_McastAddr, gmac);
			#ifdef	DBG_ICMPv6
	 		printk("MCAST_IPV6Addr:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x \n",
				icmpv6_McastAddr[0],icmpv6_McastAddr[1],icmpv6_McastAddr[2],icmpv6_McastAddr[3],
				icmpv6_McastAddr[4],icmpv6_McastAddr[5],icmpv6_McastAddr[6],icmpv6_McastAddr[7],
				icmpv6_McastAddr[8],icmpv6_McastAddr[9],icmpv6_McastAddr[10],icmpv6_McastAddr[11],
				icmpv6_McastAddr[12],icmpv6_McastAddr[13],icmpv6_McastAddr[14],icmpv6_McastAddr[15]);
		
			printk("group_mac [%02x:%02x:%02x:%02x:%02x:%02x] \n",
				gmac[0],gmac[1],gmac[2],
				gmac[3],gmac[4],gmac[5]);
			#endif
			return 1;//add

		}else if(icmpv6h->icmp6_type == ICMPV6_MLD2_REPORT){

			icmpv6_McastAddr = (unsigned char*)((unsigned char*)icmpv6h + 8 + 4);
			#ifdef	DBG_ICMPv6
			printk("Type: 0x%x (Multicast listener report v2) \n",icmpv6h->icmp6_type);
			#endif

			
			struct mld2_report *mldv2report = (struct mld2_report * )icmpv6h;
			struct mld2_grec *mldv2grec = NULL;
			#ifdef	DBG_ICMPv6
			printk("%s:%d,*gIndex is %d,mldv2report->ngrec is %d\n",__FUNCTION__,__LINE__,*gIndex,ntohs(mldv2report->mld2r_ngrec));
			#endif
			if(*gIndex >= ntohs(mldv2report->mld2r_ngrec))
			{
				*moreFlag=0;
				return -1;
			}
			
			for(i=0;i<ntohs(mldv2report->mld2r_ngrec);i++)
			{
			
				if(i==0)
				{
					mldv2grec = (struct mld2_grec *)(&(mldv2report->mld2r_grec)); /*first igmp group record*/
				}
				else
				{
					mldv2grec = (struct mld2_grec *)((unsigned char*)mldv2grec+4+16+ntohs(mldv2grec->grec_nsrcs)*16+(mldv2grec->grec_auxwords)*4);
				}
			
				if(i!=*gIndex)
				{
			
					continue;
				}
			
				if(i==(ntohs(mldv2report->mld2r_ngrec)-1))
				{
					/*last group record*/
					*moreFlag=0;
				}
				else
				{
					*moreFlag=1;
				}
			
				/*gIndex move to next group*/
				*gIndex=*gIndex+1;
			
				icmpv6_McastAddr = (unsigned char *)&mldv2grec->grec_mca;
				//printk("%s:%d,groupAddr is %d.%d.%d.%d\n",__FUNCTION__,__LINE__,NIPQUAD(groupAddr));
				if(icmpv6_McastAddr[0] != 0xFF)
					return -1;
				CIPV6toMac(icmpv6_McastAddr, gmac);
				#ifdef	DBG_ICMPv6
	 				printk("MCAST_IPV6Addr:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x \n",
					icmpv6_McastAddr[0],icmpv6_McastAddr[1],icmpv6_McastAddr[2],icmpv6_McastAddr[3],
					icmpv6_McastAddr[4],icmpv6_McastAddr[5],icmpv6_McastAddr[6],icmpv6_McastAddr[7],
					icmpv6_McastAddr[8],icmpv6_McastAddr[9],icmpv6_McastAddr[10],icmpv6_McastAddr[11],
					icmpv6_McastAddr[12],icmpv6_McastAddr[13],icmpv6_McastAddr[14],icmpv6_McastAddr[15]);
		
				printk("group_mac [%02x:%02x:%02x:%02x:%02x:%02x] \n",
					gmac[0],gmac[1],gmac[2],
					gmac[3],gmac[4],gmac[5]);

				printk("grec_type = %d, src_num = %d\n", mldv2grec->grec_type, mldv2grec->grec_nsrcs);
				#endif
				
				if(((mldv2grec->grec_type== MLD2_CHANGE_TO_INCLUDE) || (mldv2grec->grec_type == MLD2_MODE_IS_INCLUDE))&& (ntohs(mldv2grec->grec_nsrcs)==0))
				{
					return 2; /* leave and delete it */
				}
				else if((mldv2grec->grec_type == MLD2_CHANGE_TO_EXCLUDE) ||
					(mldv2grec->grec_type == MLD2_MODE_IS_EXCLUDE) ||
					(mldv2grec->grec_type == MLD2_ALLOW_NEW_SOURCES))
				{
					return 1;
				}
				else
				{
					/*ignore it*/
				}
			
				return -1;
			}
			
			/*avoid dead loop in case of initial gIndex is too big*/
			if(i>=(ntohs(mldv2report->mld2r_ngrec)-1))
			{
				/*last group record*/
				*moreFlag=0;
				return -1;
			}
			
			
			
		}else if(icmpv6h->icmp6_type == ICMPV6_MGM_REDUCTION){

			icmpv6_McastAddr = (unsigned char*)((unsigned char*)icmpv6h + 8 );
			#ifdef	DBG_ICMPv6
			printk("Type: 0x%x (Multicast listener done ) \n",icmpv6h->icmp6_type);
			#endif
			if(icmpv6_McastAddr[0] != 0xFF)
				return -1;
			CIPV6toMac(icmpv6_McastAddr, gmac);
			#ifdef	DBG_ICMPv6
	 		printk("MCAST_IPV6Addr:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x \n",
				icmpv6_McastAddr[0],icmpv6_McastAddr[1],icmpv6_McastAddr[2],icmpv6_McastAddr[3],
				icmpv6_McastAddr[4],icmpv6_McastAddr[5],icmpv6_McastAddr[6],icmpv6_McastAddr[7],
				icmpv6_McastAddr[8],icmpv6_McastAddr[9],icmpv6_McastAddr[10],icmpv6_McastAddr[11],
				icmpv6_McastAddr[12],icmpv6_McastAddr[13],icmpv6_McastAddr[14],icmpv6_McastAddr[15]);
		
			printk("group_mac [%02x:%02x:%02x:%02x:%02x:%02x] \n",
				gmac[0],gmac[1],gmac[2],
				gmac[3],gmac[4],gmac[5]);
			#endif
			return 2;//del
		}
		else{
			#ifdef	DBG_ICMPv6
			printk("Type: 0x%x (unknow type)\n",icmpv6h->icmp6_type);
			#endif
			return -1;
		}
	}
	else{
		//printk("protoType[0] != 0x3a\n");
		return -1;//not icmpv6 type
	}

	return -1;
}

#if (defined(CONFIG_RTL_8198C)||defined(CONFIG_RTL_8197F))&&defined(CONFIG_RTL_HARDWARE_MULTICAST)
int rtl865x_ipv6MulticastHardwareAccelerate(struct net_bridge *br, unsigned int brFwdPortMask,
												unsigned int srcPort,unsigned int srcVlanId,
												struct in6_addr srcIpAddr,struct in6_addr destIpAddr)
{
#if 0
	if(net_ratelimit())
		printk("[%s:%d]\n",__FUNCTION__,__LINE__);
#endif
	int ret;
	unsigned int tagged_portmask=0;
	struct rtl_multicastDataInfo multicastDataInfo;
	struct rtl_multicastFwdInfo  multicastFwdInfo;
	inv6_addr_t sip, dip;

	rtl8198c_tblDrv_mCastv6_t * existMulticastEntry;
	rtl8198c_mcast_fwd_descriptor6_t  fwdDescriptor;

	#if 0
	printk("%s:%d,srcPort is %d,srcVlanId is %d,srcIpAddr is 0x%x,destIpAddr is 0x%x\n",__FUNCTION__,__LINE__,srcPort,srcVlanId,srcIpAddr,destIpAddr);
	#endif

	multicastDataInfo.ipVersion=6;
	memcpy(multicastDataInfo.sourceIp,&srcIpAddr,sizeof(struct in6_addr));
	memcpy(multicastDataInfo.groupAddr,&destIpAddr,sizeof(struct in6_addr));

#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT

	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)!=0 &&strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME)!=0 )
	{
		return -1;
	}
	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)==0 && (brFwdPortMask & br0SwFwdPortMask))
	{
		return -1;
	}

	if(strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME)==0 && (brFwdPortMask & br1SwFwdPortMask))
	{
		return -1;
	}
#else
	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)!=0)
	{
		return -1;
	}

	if(brFwdPortMask & br0SwFwdPortMask)
	{
		return -1;
	}
#endif
	//printk("%s:%d,destIpAddr is 0x%x, srcIpAddr is 0x%x, srcVlanId is %d, srcPort is %d\n",__FUNCTION__,__LINE__,destIpAddr, srcIpAddr, srcVlanId, srcPort);
	memcpy(&sip,&srcIpAddr,sizeof(struct in6_addr));
	memcpy(&dip,&destIpAddr,sizeof(struct in6_addr));
	#if 0
	for(i=0;i<4;i++)
	{
		sip.v6_addr32[i] = srcIpAddr.s6_addr32[i];
		dip.v6_addr32[i] = destIpAddr.s6_addr32[i];
	}
	#endif
	existMulticastEntry=rtl8198C_findMCastv6Entry(dip,sip, (unsigned short)srcVlanId, (unsigned short)srcPort);
	if(existMulticastEntry!=NULL)
	{
		/*it's already in cache */
#if 0
		if(net_ratelimit())printk("[%s:%d]already in cache\n",__FUNCTION__,__LINE__);
#endif
		return 0;

	}

	if(brFwdPortMask==0)
	{
		//if(net_ratelimit())printk("[%s:%d]block\n",__FUNCTION__,__LINE__);
		rtl8198C_blockMulticastv6Flow(srcVlanId, srcPort, sip,dip);
		return 0;
	}

	#if 0
	for(i=0;i<4;i++)
	{
		multicastDataInfo.sourceIp[i] = srcIpAddr.in6_u.u6_addr32[i];
		multicastDataInfo.groupAddr[i] = destIpAddr.in6_u.u6_addr32[i];
	}
	#endif

	/*add hardware multicast entry*/
#if 1//!defined(CONFIG_RTL_MULTI_LAN_DEV)
	#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if(strcmp(br->dev->name,RTL_PS_BR0_DEV_NAME)==0)
	{
		memset(&fwdDescriptor, 0, sizeof(rtl8198c_mcast_fwd_descriptor6_t ));
		strcpy(fwdDescriptor.netifName,"eth*");
		fwdDescriptor.fwdPortMask=0xFFFFFFFF;
		ret= rtl_getMulticastDataFwdInfo(nicIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
	}
	else if(strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME)==0)
	{
		memset(&fwdDescriptor, 0, sizeof(rtl8198c_mcast_fwd_descriptor6_t ));
		strcpy(fwdDescriptor.netifName,"eth2");
		fwdDescriptor.fwdPortMask=0xFFFFFFFF;
		ret= rtl_getMulticastDataFwdInfo(nicIgmpModuleIndex_2, &multicastDataInfo, &multicastFwdInfo);
	}
	#else
	memset(&fwdDescriptor, 0, sizeof(rtl8198c_mcast_fwd_descriptor6_t ));
	strcpy(fwdDescriptor.netifName,"eth*");
	fwdDescriptor.fwdPortMask=0xFFFFFFFF;

	ret= rtl_getMulticastDataFwdInfo(nicIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
	#endif
	if(ret!=0)
	{
		//if(net_ratelimit())printk("[%s:%d]get nic fwd info failed.\n",__FUNCTION__,__LINE__);
		return -1;
	}
	else
	{
		if(multicastFwdInfo.cpuFlag)
		{
			fwdDescriptor.toCpu=1;
		}
		fwdDescriptor.fwdPortMask=multicastFwdInfo.fwdPortMask & (~(1<<srcPort));
	}
#else/*!CONFIG_RTL_MULTI_LAN_DEV*/
	memset(&fwdDescriptor, 0, sizeof(rtl8198c_mcast_fwd_descriptor6_t ));
	strcpy(fwdDescriptor.netifName,RTL_BR_NAME);
    ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
	if(multicastFwdInfo.cpuFlag)
	{
		fwdDescriptor.toCpu=1;
	}
	fwdDescriptor.fwdPortMask = rtl865x_getPhyFwdPortMask(br,brFwdPortMask) & (~(1<<srcPort));
	//printk("[%s:%d]fwdDescriptor.fwdPortMask=%d.\n",__FUNCTION__,__LINE__,fwdDescriptor.fwdPortMask);
#endif/*!CONFIG_RTL_MULTI_LAN_DEV*/

if(fwdDescriptor.fwdPortMask == 0)
	return -1;

#if defined(CONFIG_RTL_HW_VLAN_SUPPORT)
	if(rtl_hw_vlan_ignore_tagged_mc == 1)
		tagged_portmask = rtl_hw_vlan_get_tagged_portmask();
#endif
	if((fwdDescriptor.fwdPortMask & tagged_portmask) == 0)
	{

		ret=rtl8198C_addMulticastv6Entry(dip,sip, (unsigned short)srcVlanId, (unsigned short)srcPort,
							&fwdDescriptor, 1, 0, 0, 0);
	}

	return 0;
}

#endif


#endif

int rtl_IgmpSnooping_Input_Hook(struct net_bridge *br,struct sk_buff *skb,struct sk_buff *skb2)
{
	int retValue= 0;
	const unsigned char *dest = eth_hdr(skb)->h_dest;
	struct net_bridge_port *p = br_port_get_rcu(skb->dev);
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
	unsigned int srcPort=skb->srcPort;
	unsigned int srcVlanId=skb->srcVlanId;
#endif/*CONFIG_RTL_HARDWARE_MULTICAST*/

#if defined (CONFIG_RTL_MLD_SNOOPING)
	struct ipv6hdr *ipv6h=NULL;
#endif/*CONFIG_RTL_MLD_SNOOPING*/
	int ret=FAILED;
	unsigned int fwdPortMask=0;
	unsigned char proto=0;
	unsigned char reserved=0;
	unsigned char macAddr[6];
	unsigned char operation;
	char tmpOp;
	unsigned int gIndex=0;
	unsigned int moreFlag=1;
	struct iphdr *iph=NULL;
	struct rtl_multicastDataInfo multicastDataInfo;
	struct rtl_multicastFwdInfo multicastFwdInfo;

#if defined (CONFIG_RTL_HW_MCAST_WIFI)
	rtl865x_tblDrv_mCast_t * existMulticastEntry;
#endif	


	if (skb)
	{
	
		if (is_multicast_ether_addr(dest)) {
			if (MULTICAST_MAC(dest)
			&& (eth_hdr(skb)->h_proto == htons(ETH_P_IP)) && igmpsnoopenabled)
			{
			
				iph=(struct iphdr *)skb_network_header(skb);
#if defined(CONFIG_USB_UWIFI_HOST)
				if(iph->daddr == htonl(0xEFFFFFFA) || iph->daddr == htonl(0xE1010101))
#else
				if(iph->daddr == htonl(0xEFFFFFFA) || iph->daddr == htonl(0xE00000FB))
#endif
				{
					/*for microsoft upnp*/
					reserved=1;
				}
#if 0
				if((iph->daddr&0xFFFFFF00)==0xE0000000)
				reserved=1;
#endif
				proto =  iph->protocol;
				if (proto == IPPROTO_IGMP)
				{
		#if defined (CONFIG_NETFILTER)
					//filter igmp pkts by upper hook like iptables
					if(IgmpRxFilter_Hook != NULL)
					{
						struct net_device	*origDev=skb->dev;
						struct net_bridge_port *p=br_port_get_rcu(skb->dev);
						if(p && p->br)
						{
							skb->dev=p->br->dev;
						}

						if(IgmpRxFilter_Hook(skb, NF_INET_LOCAL_IN, skb->dev, NULL,dev_net(skb->dev)->ipv4.iptable_filter) !=NF_ACCEPT)
						{
							skb->dev=origDev;							
							DEBUG_PRINT(" filter a pkt from %s %s \n", skb->dev->name, &(dev_net(skb->dev)->ipv4.iptable_filter->name[0]));
							
							retValue = -1;
							goto drop;
						}

						else
						{
							skb->dev=origDev;
						}

					}
					else
						DEBUG_PRINT("IgmpRxFilter_Hook is NULL\n");
		#endif/*CONFIG_NETFILTER*/
					while(moreFlag)
					{
						tmpOp=igmp_type_check(skb, macAddr, &gIndex, &moreFlag);
						if(tmpOp>0)
						{
							operation=(unsigned char)tmpOp;
							br_update_igmp_snoop_fdb(operation, br, p, macAddr,skb);
						}
					}
		#if defined (CONFIG_RTL_QUERIER_SELECTION)
					if(check_igmpQueryExist(iph)==1)
					{
						struct net_bridge_port *p=br_port_get_rcu(skb->dev);
						/*igmp query packet*/
						if(p)
						{
							br_updateQuerierInfo(4,p->br->dev->name,(unsigned int*)&(iph->saddr));
						}
						else
						{
							br_updateQuerierInfo(4,skb->dev->name,(unsigned int*)&(iph->saddr));
						}
					}
		#endif
	    #ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
					if(!strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME))
					{
						rtl_igmpMldProcess(brIgmpModuleIndex_2, skb_mac_header(skb), p->port_no, &fwdPortMask);
						//flooding igmp packet
						fwdPortMask=(~(1<<(p->port_no))) & 0xFFFFFFFF;
					}
					else
		#endif
					rtl_igmpMldProcess(brIgmpModuleIndex, skb_mac_header(skb), p->port_no, &fwdPortMask);
                    br_multicast_forward(br, fwdPortMask, skb, (skb2? 1:0));

					retValue =1;
				}

				else if(((proto ==IPPROTO_UDP) ||(proto ==IPPROTO_TCP)) && (reserved ==0))
				{
					iph=(struct iphdr *)skb_network_header(skb);
					multicastDataInfo.ipVersion=4;
					multicastDataInfo.sourceIp[0]=	(uint32)(iph->saddr);
					multicastDataInfo.groupAddr[0]=  (uint32)(iph->daddr);
					multicastDataInfo.sourceIp[0] = ntohl(multicastDataInfo.sourceIp[0]);
					multicastDataInfo.groupAddr[0] = ntohl(multicastDataInfo.groupAddr[0]);

	    #ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
					if(!strcmp(br->dev->name,RTL_PS_BR1_DEV_NAME))
					{
						ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex_2, &multicastDataInfo, &multicastFwdInfo);
					}
					else
		#endif
					ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
		
		#if defined (CONFIG_RTL_HW_MCAST_WIFI)
					if(hwwifiEnable)
					{
						existMulticastEntry=rtl865x_findMCastEntry(multicastDataInfo.groupAddr[0], multicastDataInfo.sourceIp[0], (unsigned short)srcVlanId, (unsigned short)srcPort);
						if(existMulticastEntry!=NULL)
						{
							/*it's already in cache, only forward to wlan */

							multicastFwdInfo.fwdPortMask &= br0SwFwdPortMask;

						}
					}
		#endif
					br_multicast_forward(br, multicastFwdInfo.fwdPortMask, skb,(skb2? 1:0));

		#if defined (CONFIG_RTL_HW_MCAST_WIFI)
					if((hwwifiEnable && (ret==SUCCESS)) ||
						(hwwifiEnable ==0 && (ret==SUCCESS) && (multicastFwdInfo.cpuFlag==0)))
		#else
					if((ret==SUCCESS) && (multicastFwdInfo.cpuFlag==0))
		#endif
					{
			#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
						if((srcVlanId!=0) && (srcPort!=0xFFFF))
						{
			#if defined(CONFIG_RTK_VLAN_SUPPORT)
							if(rtk_vlan_support_enable == 0)
							{
								rtl865x_ipMulticastHardwareAccelerate(br, multicastFwdInfo.fwdPortMask,srcPort,srcVlanId, multicastDataInfo.sourceIp[0], multicastDataInfo.groupAddr[0]);
							}
			#else
							rtl865x_ipMulticastHardwareAccelerate(br, multicastFwdInfo.fwdPortMask,srcPort,srcVlanId, multicastDataInfo.sourceIp[0], multicastDataInfo.groupAddr[0]);
			#endif
						}
			#endif
					}
					retValue =1;
				}

			}
#if defined (CONFIG_RTL_MLD_SNOOPING)
		else if(IPV6_MULTICAST_MAC(dest)
			&& (eth_hdr(skb)->h_proto == htons(ETH_P_IPV6))
			&& mldSnoopEnabled)
		    {
				ipv6h=(struct ipv6hdr *)skb_network_header(skb);
				proto =  re865x_getIpv6TransportProtocol(ipv6h);
				/*icmpv6 protocol*/
				if (proto == IPPROTO_ICMPV6)
				{
					while(moreFlag)
					{
                    	tmpOp=ICMPv6_check(skb , macAddr, &gIndex, &moreFlag);
                    	if(tmpOp > 0){
                        	operation=(unsigned char)tmpOp;
#ifdef	DBG_ICMPv6
                        	if( operation == 1)
                            	printk("icmpv6 add from frame finish\n");
                        	else if(operation == 2)
                            	printk("icmpv6 del from frame finish\n");
#endif
                            br_update_igmp_snoop_fdb(operation, br, p, macAddr,skb);
                        }
					}
		#if defined (CONFIG_RTL_QUERIER_SELECTION)
					if(check_mldQueryExist(ipv6h)==1)
					{
						struct net_bridge_port *p = br_port_get_rcu(skb->dev);
						if(p)
						{
							br_updateQuerierInfo(6,p->br->dev->name,(unsigned int*)&(ipv6h->saddr));
						}
						else
						{
							br_updateQuerierInfo(6,skb->dev->name,(unsigned int*)&(ipv6h->saddr));
						}

					}
		#endif
					rtl_igmpMldProcess(brIgmpModuleIndex, skb_mac_header(skb), p->port_no, &fwdPortMask);
		
					br_multicast_forward(br, fwdPortMask, skb, (skb2? 1:0));
					retValue =1;
				}
				else if ((proto ==IPPROTO_UDP) ||(proto ==IPPROTO_TCP))
				{
					multicastDataInfo.ipVersion=6;
					memcpy(&multicastDataInfo.sourceIp, &ipv6h->saddr, sizeof(struct in6_addr));
					memcpy(&multicastDataInfo.groupAddr, &ipv6h->daddr, sizeof(struct in6_addr));
					
					multicastDataInfo.sourceIp[0] = ntohl(multicastDataInfo.sourceIp[0]);
					multicastDataInfo.sourceIp[1] = ntohl(multicastDataInfo.sourceIp[1]);
					multicastDataInfo.sourceIp[2] = ntohl(multicastDataInfo.sourceIp[2]);
					multicastDataInfo.sourceIp[3] = ntohl(multicastDataInfo.sourceIp[3]);
					multicastDataInfo.groupAddr[0] = ntohl(multicastDataInfo.groupAddr[0]);
					multicastDataInfo.groupAddr[1] = ntohl(multicastDataInfo.groupAddr[1]);
					multicastDataInfo.groupAddr[2] = ntohl(multicastDataInfo.groupAddr[2]);
					multicastDataInfo.groupAddr[3] = ntohl(multicastDataInfo.groupAddr[3]);

					ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
					br_multicast_forward(br, multicastFwdInfo.fwdPortMask, skb, (skb2? 1:0));
#if (defined(CONFIG_RTL_8198C)||defined(CONFIG_RTL_8197F))&&defined(CONFIG_RTL_HARDWARE_MULTICAST)
					if((ret==SUCCESS)
				#ifndef CONFIG_RTL_HW_MCAST_WIFI
						&& (multicastFwdInfo.cpuFlag==0)
				#endif
						)
					{
						if((srcVlanId!=0) && (srcPort!=0xFFFF))
						{
							struct in6_addr sip;
							struct in6_addr dip;
							memcpy(&sip,multicastDataInfo.sourceIp,sizeof(struct in6_addr));
							memcpy(&dip,multicastDataInfo.groupAddr,sizeof(struct in6_addr));
				#if defined(CONFIG_RTK_VLAN_SUPPORT)
							if(rtk_vlan_support_enable == 0)
							{
								rtl865x_ipv6MulticastHardwareAccelerate(br, multicastFwdInfo.fwdPortMask,srcPort,srcVlanId, sip,dip);
							}
				#else
							rtl865x_ipv6MulticastHardwareAccelerate(br, multicastFwdInfo.fwdPortMask,srcPort,srcVlanId, sip,dip);
				#endif
						}
					}
#endif
					retValue =1;
				}

		    }
#endif   //CONFIG_RTL_MLD_SNOOPING

		}

	}
out:
	return retValue;
drop:
	kfree_skb(skb);
	goto out;

}

int rtl_IgmpSnooping_BrXmit_Hook(struct net_bridge * br, const unsigned char * dest, struct sk_buff * skb)
{
	//const unsigned char *dest = skb->data;
	int retValue =0;
	struct iphdr *iph=NULL;
	unsigned char proto=0;
	unsigned char reserved=0;
#if defined (CONFIG_RTL_MLD_SNOOPING)
	struct ipv6hdr *ipv6h=NULL;
#endif
	struct rtl_multicastDataInfo multicastDataInfo;
	struct rtl_multicastFwdInfo multicastFwdInfo;
	int ret=FAILED;
#if defined (CONFIG_RTL_HARDWARE_MULTICAST) || defined(CONFIG_RTL_IGMP_PROXY)
	unsigned int srcPort=skb->srcPort;
	unsigned int srcVlanId=skb->srcVlanId;
#endif/*CONFIG_RTL_HARDWARE_MULTICAST*/

#if defined (CONFIG_RTL_HW_MCAST_WIFI)
	rtl865x_tblDrv_mCast_t * existMulticastEntry;
#endif

   	if (dest[0] & 1)  // multicast
	{
		if(igmpsnoopenabled && MULTICAST_MAC(dest))
		{

			iph=(struct iphdr *)skb_network_header(skb);
			proto =  iph->protocol;
		#if 0
			if(( iph->daddr&0xFFFFFF00)==0xE0000000)
			{
						reserved=1;
			}
		#endif

	#if defined(CONFIG_USB_UWIFI_HOST)
			if(iph->daddr == htonl(0xEFFFFFFA) || iph->daddr == htonl(0xE1010101))
	#else
			if(iph->daddr == htonl(0xEFFFFFFA) || iph->daddr == htonl(0xE00000FB))
	#endif
			{
			    /*for microsoft upnp*/
				reserved=1;
			}

			if(((proto ==IPPROTO_UDP) ||(proto ==IPPROTO_TCP))	&& (reserved ==0))
			{
				multicastDataInfo.ipVersion=4;
				multicastDataInfo.sourceIp[0]=	(uint32)(iph->saddr);
				multicastDataInfo.groupAddr[0]=  (uint32)(iph->daddr);
				
				multicastDataInfo.sourceIp[0] = ntohl(multicastDataInfo.sourceIp[0]);
				multicastDataInfo.groupAddr[0] = ntohl(multicastDataInfo.groupAddr[0]);

				ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
			#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				if(hwwifiEnable)
				{
					existMulticastEntry=rtl865x_findMCastEntry(multicastDataInfo.groupAddr[0], multicastDataInfo.sourceIp[0], (unsigned short)srcVlanId, (unsigned short)srcPort);
					
					if(existMulticastEntry!=NULL)
					{
						/*it's already in cache, only forward to wlan */
						multicastFwdInfo.fwdPortMask &= br0SwFwdPortMask;
					}
				}
			#endif
			
			#if defined (CONFIG_RTL_IGMP_PROXY)
				if(IGMPPRoxyFastLeave)
				{
					//igmpproxy delete mfc delay, lan vlc client will flooding for a while, drop!
					if((1<<srcPort & RTL_WANPORT_MASK) && multicastFwdInfo.unknownMCast==TRUE)
					{
							kfree_skb(skb);
							return 1;
					}
				}
			#endif
				br_multicast_deliver(br, multicastFwdInfo.fwdPortMask, skb, 0);
			#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				if((hwwifiEnable && ret==SUCCESS)||
			   		(hwwifiEnable==0 && ret==SUCCESS && multicastFwdInfo.cpuFlag==0))
			#else
				if((ret==SUCCESS) && (multicastFwdInfo.cpuFlag==0))
			#endif
				{
				#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
					if((srcVlanId!=0) && (srcPort!=0xFFFF))
					{
					#if defined(CONFIG_RTK_VLAN_SUPPORT)
						if(rtk_vlan_support_enable == 0)
						{
							rtl865x_ipMulticastHardwareAccelerate(br, multicastFwdInfo.fwdPortMask,srcPort,srcVlanId, multicastDataInfo.sourceIp[0], multicastDataInfo.groupAddr[0]);
						}
					#else
						rtl865x_ipMulticastHardwareAccelerate(br, multicastFwdInfo.fwdPortMask,srcPort,srcVlanId, multicastDataInfo.sourceIp[0], multicastDataInfo.groupAddr[0]);
					#endif
					}
				#endif
				}
				retValue =1;

			}


		}
#if defined(CONFIG_RTL_MLD_SNOOPING)
		else if(mldSnoopEnabled && IPV6_MULTICAST_MAC(dest))
		{
			ipv6h=(struct ipv6hdr *)skb_network_header(skb);
			proto=re865x_getIpv6TransportProtocol(ipv6h);
			if ((proto ==IPPROTO_UDP) ||(proto ==IPPROTO_TCP))
			{
				multicastDataInfo.ipVersion=6;
				memcpy(&multicastDataInfo.sourceIp, &ipv6h->saddr, sizeof(struct in6_addr));
				memcpy(&multicastDataInfo.groupAddr, &ipv6h->daddr, sizeof(struct in6_addr));

				multicastDataInfo.sourceIp[0] = ntohl(multicastDataInfo.sourceIp[0]);
				multicastDataInfo.sourceIp[1] = ntohl(multicastDataInfo.sourceIp[1]);
				multicastDataInfo.sourceIp[2] = ntohl(multicastDataInfo.sourceIp[2]);
				multicastDataInfo.sourceIp[3] = ntohl(multicastDataInfo.sourceIp[3]);
				multicastDataInfo.groupAddr[0] = ntohl(multicastDataInfo.groupAddr[0]);
				multicastDataInfo.groupAddr[1] = ntohl(multicastDataInfo.groupAddr[1]);
				multicastDataInfo.groupAddr[2] = ntohl(multicastDataInfo.groupAddr[2]);
				multicastDataInfo.groupAddr[3] = ntohl(multicastDataInfo.groupAddr[3]);

				ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
                #if 0
                if(TEST_PACKETS_ADDRESS(dest))
                    printk("ret = %d, fwdPortMask = %x, [%s:%d]\n", ret, multicastFwdInfo.fwdPortMask, __FUNCTION__, __LINE__);
                #endif
                br_multicast_deliver(br, multicastFwdInfo.fwdPortMask, skb, 0);
			    #if defined (CONFIG_RTL_HARDWARE_MULTICAST) && (defined(CONFIG_RTL_8198C)||defined(CONFIG_RTL_8197F))
				if((ret==SUCCESS) && (multicastFwdInfo.cpuFlag==0))
				{
					struct in6_addr sip;
					struct in6_addr dip;
					memcpy(&sip,multicastDataInfo.sourceIp,sizeof(struct in6_addr));
					memcpy(&dip,multicastDataInfo.groupAddr,sizeof(struct in6_addr));
					if((srcVlanId!=0) && (srcPort!=0xFFFF))
					{
					#if defined(CONFIG_RTK_VLAN_SUPPORT)
						if(rtk_vlan_support_enable == 0)
						{
							rtl865x_ipv6MulticastHardwareAccelerate(br, multicastFwdInfo.fwdPortMask,srcPort,srcVlanId, sip, dip);
						}
					#else
						rtl865x_ipv6MulticastHardwareAccelerate(br, multicastFwdInfo.fwdPortMask,srcPort,srcVlanId, sip, dip);
					#endif
					}
				}
				#endif
				retValue =1;
			}
		}
#endif/*CONFIG_RTL_MLD_SNOOPING*/
	}
    return retValue;
}

/*input and output end*/

/*fdb begin*/
 void br_igmp_fdb_expired(struct net_bridge_fdb_entry *ent)
{
	int i2;
	unsigned long igmp_walktimeout;	
	unsigned char *DA;
	unsigned char *SA;
	#if defined	(MCAST_TO_UNICAST)
	struct net_device *dev=NULL;
	#endif

	igmp_walktimeout = 	jiffies - IGMP_EXPIRE_TIME;	
	    
	//IGMP_EXPIRE_TIME
	for(i2=0 ; i2 < FDB_IGMP_EXT_NUM ; i2++)
	{
		if(ent->igmp_fdb_arr[i2].valid == 1){

			// when timeout expire
			if(time_before_eq(ent->igmp_fdb_arr[i2].ageing_time, igmp_walktimeout))
			{
				DEBUG_PRINT("%s:%d\n",__FUNCTION__,__LINE__);
				SA = ent->igmp_fdb_arr[i2].SrcMac;					
				DEBUG_PRINT("expired src mac:%02x,%02x,%02x,%02x,%02x,%02x\n",
					SA[0],SA[1],SA[2],SA[3],SA[4],SA[5]);								

				DA = ent->addr.addr;					
				DEBUG_PRINT("fdb:%02x:%02x:%02x-%02x:%02x:%02x\n",
					DA[0],DA[1],DA[2],DA[3],DA[4],DA[5]);				



				/*---for process wlan client expired start---*/								
				#if defined	(MCAST_TO_UNICAST)
				#if defined (M2U_DELETE_CHECK)
				if(rtl_M2UDeletecheck(DA,SA))
                {
                #endif
				dev = __dev_get_by_name(&init_net, RTL_PS_WLAN0_DEV_NAME);	
	
				
				if (dev) {		
					unsigned char StaMacAndGroup[20];
					memcpy(StaMacAndGroup, DA , 6);
					memcpy(StaMacAndGroup+6, SA, 6);
				#if defined(CONFIG_COMPAT_NET_DEV_OPS)
					if (dev->do_ioctl != NULL) {
						dev->do_ioctl(dev, (struct ifreq*)StaMacAndGroup, 0x8B81);
				#else
					if (dev->netdev_ops->ndo_do_ioctl != NULL) {
						dev->netdev_ops->ndo_do_ioctl(dev, (struct ifreq*)StaMacAndGroup, 0x8B81);
				#endif
						DEBUG_PRINT("(fdb expire) wlan0 ioctl to DEL! M2U entry da:%02x:%02x:%02x-%02x:%02x:%02x; sa:%02x:%02x:%02x-%02x:%02x:%02x\n",
							StaMacAndGroup[0],StaMacAndGroup[1],StaMacAndGroup[2],StaMacAndGroup[3],StaMacAndGroup[4],StaMacAndGroup[5],
							StaMacAndGroup[6],StaMacAndGroup[7],StaMacAndGroup[8],StaMacAndGroup[9],StaMacAndGroup[10],StaMacAndGroup[11]);
					}
				}
					
				//#if defined(CONFIG_RTL_92D_SUPPORT)|| defined(CONFIG_RTL_8812_SUPPORT)||defined (CONFIG_RTL_8881A)
				//dual band
				#if (defined (CONFIG_USE_PCIE_SLOT_0) )&&(defined (CONFIG_USE_PCIE_SLOT_1)||defined (CONFIG_RTL_8881A) || defined(CONFIG_RTL_8197F))	   
				dev = __dev_get_by_name(&init_net, RTL_PS_WLAN1_DEV_NAME);	
	
				if (dev) {		
					unsigned char StaMacAndGroup[20];
					memcpy(StaMacAndGroup, DA , 6);
					memcpy(StaMacAndGroup+6, SA, 6);
				#if defined(CONFIG_COMPAT_NET_DEV_OPS)
					if (dev->do_ioctl != NULL) {
						dev->do_ioctl(dev, (struct ifreq*)StaMacAndGroup, 0x8B81);
				#else
					if (dev->netdev_ops->ndo_do_ioctl != NULL) {
						dev->netdev_ops->ndo_do_ioctl(dev, (struct ifreq*)StaMacAndGroup, 0x8B81);
				#endif
						DEBUG_PRINT("(fdb expire) wlan1 ioctl to DEL! M2U entry da:%02x:%02x:%02x-%02x:%02x:%02x; sa:%02x:%02x:%02x-%02x:%02x:%02x\n",
							StaMacAndGroup[0],StaMacAndGroup[1],StaMacAndGroup[2],StaMacAndGroup[3],StaMacAndGroup[4],StaMacAndGroup[5],
							StaMacAndGroup[6],StaMacAndGroup[7],StaMacAndGroup[8],StaMacAndGroup[9],StaMacAndGroup[10],StaMacAndGroup[11]);
					}
				}
				#endif
				#ifdef M2U_DELETE_CHECK
                }
                #endif
				#endif			
				/*---for process wlan client expired end---*/

			
				del_igmp_ext_entry(ent , SA , ent->igmp_fdb_arr[i2].port,1);

	
				if ( (ent->portlist & 0x7f)==0){
					ent->group_src &=  ~(1 << 1); // eth0 all leave
				}
			
				if ( (ent->portlist & 0x80)==0){
					ent->group_src &=  ~(1 << 2); // wlan0 all leave
				}
			
			
			}			
			
		}		
		
	}		
	
}

void rtl_igmp_fdb_delete_hook(struct net_bridge * br,struct net_bridge_fdb_entry * f)
{
	if(	f->is_static &&
		f->igmpFlag &&
		(MULTICAST_MAC(f->addr.addr)
#if defined (CONFIG_RTL_MLD_SNOOPING)
		||IPV6_MULTICAST_MAC(f->addr.addr)
#endif
			)
		)
		{
		#if defined	(MCAST_TO_UNICAST)
			br_igmp_fdb_expired(f);
		#endif
			if(time_before_eq(f->updated +300*HZ,  jiffies))
			{
				DEBUG_PRINT("fdb_delete:f->addr.addr is 0x%02x:%02x:%02x-%02x:%02x:%02x\n",
				f->addr.addr[0],f->addr.addr[1],f->addr.addr[2],f->addr.addr[3],f->addr.addr[4],f->addr.addr[5]);
				rtl_igmp_fdb_delete(br,f);
			}
		}
}
void rtl_igmp_fdb_create_hook(struct net_bridge_fdb_entry *fdb)
{
	int i3;
	fdb->group_src = 0;
	fdb->igmpFlag=0;
	for(i3=0 ; i3<FDB_IGMP_EXT_NUM ;i3++)
	{
		fdb->igmp_fdb_arr[i3].valid = 0;
		fdb->portUsedNum[i3] = 0;
	}
}


/*fdb end*/


/*mCastFwd*/
#if defined(CONFIG_RTL_IGMP_PROXY)
int rtl865x_checkMfcCache(struct net *net,struct net_device *dev, uint32 origin,uint32 mcastgrp)
{
	struct mfc_cache *mfc=NULL;
	int vif_index;
	uint32 origin_temp=0;

 	struct mr_table *mrt = rtl_ipmr_get_table(net, RT_TABLE_DEFAULT);
	
	mfc=rtl_ipmr_cache_find(mrt,origin,mcastgrp);
	if(mfc==NULL)
	{
		vif_index = rtl_ipmr_find_vif(mrt,dev);
		origin_temp = vif_index;
		mfc = rtl_ipmr_cache_find(mrt, origin_temp, mcastgrp);
	}
	
	if(mfc!=NULL)
	{
		return 0;
	}
	else
	{
		struct mfc_cache *c;
		list_for_each_entry(c, &mrt->mfc_unres_queue, list) 
		{
			if (c->mfc_mcastgrp == mcastgrp) 
			{
				return 0;
			}
		}
	}
	return -1;
}
#endif

int rtl865x_checkUnknownMCastLoading(struct rtl_multicastDataInfo *mCastInfo)
{
	int i;
	
	if (chkUnknownMcastEnable==0)
		return 0;
	
	if(mCastInfo==NULL)
	{
		return 0;
	}
	
	if(rtl_check_ReservedMCastAddr(mCastInfo->groupAddr[0])==SUCCESS)
	{
		return 0;
	}
	/*check entry existed or not*/
	for(i=0; i<MAX_UNKNOWN_MULTICAST_NUM; i++)
	{
		if((unKnownMCastRecord[i].valid==1) && (unKnownMCastRecord[i].groupAddr==mCastInfo->groupAddr[0]))
		{
			break;
		}
	}

	/*find an empty one*/
	if(i==MAX_UNKNOWN_MULTICAST_NUM)
	{
		for(i=0; i<MAX_UNKNOWN_MULTICAST_NUM; i++)
		{
			if(unKnownMCastRecord[i].valid!=1)
			{
				break;
			}
		}
	}

	/*find an exipired one */
	if(i==MAX_UNKNOWN_MULTICAST_NUM)
	{
		for(i=0; i<MAX_UNKNOWN_MULTICAST_NUM; i++)
		{
			if(	time_before(unKnownMCastRecord[i].lastJiffies+HZ,jiffies)
				|| time_after(unKnownMCastRecord[i].lastJiffies,jiffies+HZ)	)
			{
		
				break;
			}
		}
	}

	if(i==MAX_UNKNOWN_MULTICAST_NUM)
	{
		return 0;
	}

	unKnownMCastRecord[i].groupAddr=mCastInfo->groupAddr[0];
	unKnownMCastRecord[i].valid=1;
	
	if(time_after(unKnownMCastRecord[i].lastJiffies+HZ,jiffies))
	{
		unKnownMCastRecord[i].pktCnt++;
	}
	else
	{
		unKnownMCastRecord[i].lastJiffies=jiffies;
		unKnownMCastRecord[i].pktCnt=0;
	}

	if(unKnownMCastRecord[i].pktCnt>maxUnknownMcastPPS)
	{
		return BLOCK_UNKNOWN_MULTICAST;
	}

	return 0;
}

int rtl865x_ipMulticastFastFwd_hook(struct sk_buff *skb)
{
#if 1
	const unsigned char *dest = NULL;
	unsigned char *ptr;
	struct iphdr *iph=NULL;
	unsigned char proto=0;
	unsigned char reserved=0;
	int ret=-1;

	struct net_bridge_port *prev;
	struct net_bridge_port *p, *n;
	struct rtl_multicastDataInfo multicastDataInfo;
	struct rtl_multicastFwdInfo multicastFwdInfo;
	struct sk_buff *skb2;

	unsigned short port_bitmask=0;
	#if defined (CONFIG_RTL_MLD_SNOOPING)
	struct ipv6hdr * ipv6h=NULL;
	#endif
	unsigned int fwdCnt;
#if	defined (CONFIG_RTL_IGMP_PROXY)
	struct net_device *dev=skb->dev;
#endif
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	struct net_bridge *bridge = bridge0;
	unsigned int brSwFwdPortMask = br0SwFwdPortMask;
#endif	
#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
	unsigned int srcPort=skb->srcPort;
	unsigned int srcVlanId=skb->srcVlanId;
	rtl865x_tblDrv_mCast_t *existMulticastEntry=NULL;
#endif
#if	defined (CONFIG_RTL_IGMP_PROXY)
 	int existMfc = 0;
#endif

	/*to do: swconfig_vlan_enable*/
#if defined (CONFIG_SWCONFIG)
	if(swconfig_vlan_enable)
	{
		return -1;
	}
#endif

	/*check fast forward enable or not*/
	if(ipMulticastFastFwd==0)
	{
		return -1;
	}

	/*check dmac is multicast or not*/
	dest=eth_hdr(skb)->h_dest;
	if((dest[0]&0x01)==0)
	{
		return -1;
	}

	//printk("%s:%d,dest is 0x%x-%x-%x-%x-%x-%x\n",__FUNCTION__,__LINE__,dest[0],dest[1],dest[2],dest[3],dest[4],dest[5]);
	if(igmpsnoopenabled==0)
	{
		return -1;
	}

	/*check bridge0 exist or not*/
	if((bridge0==NULL) ||(bridge0->dev->flags & IFF_PROMISC))
	{
		return -1;
	}

	if((skb->dev==NULL) ||(strncmp(skb->dev->name,RTL_PS_BR0_DEV_NAME,3)==0))
	{
		return -1;
	}
    #ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	if((strncmp(skb->dev->name,RTL_PS_BR1_DEV_NAME,3)==0))
	{
		return -1;
	}
	#endif

	/*check igmp snooping enable or not, and check dmac is ipv4 multicast mac or not*/
	if  ((dest[0]==0x01) && (dest[1]==0x00) && (dest[2]==0x5e))
	{
	
		ptr=(unsigned char *)eth_hdr(skb)+12;
		/*check vlan tag exist or not*/
		if(*(int16 *)(ptr)==(int16)htons(0x8100))
		{
			ptr=ptr+4;
		}

		/*check it's ipv4 packet or not*/
		if(*(int16 *)(ptr)!=(int16)htons(ETH_P_IP))
		{
			return -1;
		}

		iph=(struct iphdr *)(ptr+2);

		if((iph->daddr== htonl(0xEFFFFFFA))||
		(rtl_check_ReservedMCastAddr(ntohl(iph->daddr))==SUCCESS))
		{
			/*for microsoft upnp*/
			reserved=1;
		}

		/*only speed up udp and tcp*/
		proto =  iph->protocol;
		//printk("%s:%d,proto is %d\n",__FUNCTION__,__LINE__,proto);
		 if(((proto ==IPPROTO_UDP) ||(proto ==IPPROTO_TCP)) && (reserved ==0))
		{
			 multicastDataInfo.ipVersion=4;
			 multicastDataInfo.sourceIp[0]=  (unsigned int)(iph->saddr);
			 multicastDataInfo.groupAddr[0]=  (unsigned int)(iph->daddr);
			 multicastDataInfo.sourceIp[0] =  ntohl(multicastDataInfo.sourceIp[0]);
			 multicastDataInfo.groupAddr[0]=  ntohl(multicastDataInfo.groupAddr[0]);

			#if defined (CONFIG_IP_MROUTE)
			/*multicast data comes from wan, need check multicast forwardig cache*/
			if((strncmp(skb->dev->name,RTL_PS_WAN0_DEV_NAME,4)==0) && needCheckMfc )
			{
				#if	defined (CONFIG_RTL_IGMP_PROXY)
				existMfc = rtl865x_checkMfcCache(&init_net,dev,iph->saddr,iph->daddr);
				//existMfc = 0  --> mfc is found, existMfc = -1  --> no mfc
				if(existMfc!=0)
				#endif	
				{
					if(rtl865x_checkUnknownMCastLoading(&multicastDataInfo)==BLOCK_UNKNOWN_MULTICAST)
					{
#if defined( CONFIG_RTL_HARDWARE_MULTICAST) || defined(CONFIG_RTL865X_LANPORT_RESTRICTION)
						if((skb->srcVlanId!=0) && (skb->srcPort!=0xFFFF))
						{
								existMulticastEntry=rtl865x_findMCastEntry(multicastDataInfo.groupAddr[0], multicastDataInfo.sourceIp[0], srcVlanId, srcPort);
								if(existMulticastEntry!=NULL && existMulticastEntry->inAsic)
								{
									rtl865x_blockMulticastFlow(srcVlanId, srcPort, multicastDataInfo.sourceIp[0],multicastDataInfo.groupAddr[0]);
								}
								else
								{
									kfree_skb(skb);
									return 0;
								}
						}
						else
#endif
						{
							kfree_skb(skb);
							return 0;
						}
					}
				
					return -1;
				}
			}
			#endif

            #ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT //fix tim
			if(!strcmp(skb->dev->name,RTL_PS_ETH_NAME_ETH2)){
					ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex_2, &multicastDataInfo, &multicastFwdInfo);
					bridge = bridge1;
					brSwFwdPortMask = br1SwFwdPortMask;
			}
			else
		    #endif
			ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);


			if((ret!=0)||multicastFwdInfo.reservedMCast || multicastFwdInfo.unknownMCast)
			{
				if( multicastFwdInfo.unknownMCast && (strncmp(skb->dev->name,RTL_PS_WAN0_DEV_NAME,4)==0))
				{
					//only block heavyloading multicast data from wan
					if((rtl865x_checkUnknownMCastLoading(&multicastDataInfo)==BLOCK_UNKNOWN_MULTICAST) 
					#ifdef CONFIG_RTL_IGMP_PROXY
						||(needCheckMfc && existMfc == 0 && IGMPPRoxyFastLeave)
					#endif
					)
#if defined( CONFIG_RTL865X_HARDWARE_MULTICAST) || defined(CONFIG_RTL865X_LANPORT_RESTRICTION)
					if((skb->srcVlanId!=0) && (skb->srcPort!=0xFFFF))
					{
						rtl865x_blockMulticastFlow(srcVlanId, srcPort, multicastDataInfo.sourceIp[0],multicastDataInfo.groupAddr[0]);
					}
					else
#endif
					{
					
						kfree_skb(skb);
						return 0;
					}
				}
				return -1;
			}


			//printk("%s:%d,br0SwFwdPortMask is 0x%x,multicastFwdInfo.fwdPortMask is 0x%x\n",__FUNCTION__,__LINE__,br0SwFwdPortMask,multicastFwdInfo.fwdPortMask);
			//printk("%s:%d,dip: 0x%x,sip: 0x%x,svid:%x,srcPort:%x\n",__FUNCTION__,__LINE__,iph->daddr,iph->saddr,srcVlanId,srcPort);
			#if defined (CONFIG_RTL_HARDWARE_MULTICAST)						
			existMulticastEntry=rtl865x_findMCastEntry(multicastDataInfo.groupAddr[0], multicastDataInfo.sourceIp[0], srcVlanId, srcPort);
			
			if(	(existMulticastEntry==NULL)||
				((existMulticastEntry!=NULL) && (existMulticastEntry->inAsic)))
			
			{
				
				if((skb->srcVlanId!=0) && (skb->srcPort!=0xFFFF))
				{
					/*multicast data comes from ethernet port*/
					#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
					if( (brSwFwdPortMask & multicastFwdInfo.fwdPortMask)==0)
					#else
					if( (br0SwFwdPortMask & multicastFwdInfo.fwdPortMask)==0)
					#endif
					{
						/*hardware forwarding ,let slow path handle packets trapped to cpu*/
						return -1;
					}
				#if defined (CONFIG_RTL_HW_MCAST_WIFI)
					else if(hwwifiEnable&&( ((~br0SwFwdPortMask) & multicastFwdInfo.fwdPortMask)!=0)&&(ret==SUCCESS))
					{
						/*eth client , hw forwarding*/
					#if defined(CONFIG_RTK_VLAN_SUPPORT)
						if(rtk_vlan_support_enable == 0)
					#endif
						{
							rtl865x_ipMulticastHardwareAccelerate(bridge0, multicastFwdInfo.fwdPortMask,skb->srcPort,skb->srcVlanId, multicastDataInfo.sourceIp[0], multicastDataInfo.groupAddr[0]);
						}
					}
					
			#endif
				}
			}
			
			#if defined (CONFIG_RTL_HW_MCAST_WIFI)
			if(hwwifiEnable)
			{
				existMulticastEntry=rtl865x_findMCastEntry(multicastDataInfo.groupAddr[0], multicastDataInfo.sourceIp[0], (unsigned short)srcVlanId, (unsigned short)srcPort);
			
				if(existMulticastEntry!=NULL && (existMulticastEntry->inAsic))
				{
					/*it's already in cache, only forward to wlan */
					multicastFwdInfo.fwdPortMask &= br0SwFwdPortMask;
				}
			}
			#endif
			#endif

			skb_push(skb, ETH_HLEN);

			prev = NULL;
			fwdCnt=0;

        #ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
			list_for_each_entry_safe(p, n, &bridge->port_list, list) 
		#else
			list_for_each_entry_safe(p, n, &bridge0->port_list, list)
		#endif
			{
				port_bitmask = (1 << p->port_no);
				if ((port_bitmask & multicastFwdInfo.fwdPortMask) && rtl_should_deliver(p, skb))
				{
					if (prev != NULL)
					{
						if ((skb2 = skb_clone(skb, GFP_ATOMIC)) == NULL)
						{
							LOG_MEM_ERROR("%s(%d) skb clone failed, drop it\n", __FUNCTION__, __LINE__);
                            #ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
							bridge->dev->stats.tx_dropped++;
			    			#else
							bridge0->dev->stats.tx_dropped++;
							#endif
							kfree_skb(skb);
							return 0;
						}
						skb2->dev=prev->dev;
						
						#if defined(CONFIG_COMPAT_NET_DEV_OPS)
						prev->dev->hard_start_xmit(skb2, prev->dev);
						#else
						prev->dev->netdev_ops->ndo_start_xmit(skb2,prev->dev);
						#endif
						fwdCnt++;
					}

					prev = p;
				}
			}

			if (prev != NULL)
			{
				skb->dev=prev->dev;
				
		        #if defined(CONFIG_COMPAT_NET_DEV_OPS)
				prev->dev->hard_start_xmit(skb, prev->dev);
				#else
				prev->dev->netdev_ops->ndo_start_xmit(skb,prev->dev);
				#endif
				fwdCnt++;
			}

			if(fwdCnt==0)
			{
				/*avoid memory leak*/
				skb_pull(skb, ETH_HLEN);
				return -1;
			}

			return 0;

		}

	}

#if 0 //defined (CONFIG_RTL_MLD_SNOOPING)
	/*check igmp snooping enable or not, and check dmac is ipv4 multicast mac or not*/
	if  ((dest[0]==0x33) && (dest[1]==0x33) && (dest[2]!=0xff))
	{
		struct net_bridge_port *p;
		if(mldSnoopEnabled==0)
		{
			return -1;
		}

		/*due to ipv6 passthrough*/
		p= rcu_dereference(skb->dev->br_port);
		if(p==NULL)
		{
			return -1;
		}

		//printk("%s:%d,skb->dev->name is %s\n",__FUNCTION__,__LINE__,skb->dev->name );
		ptr=(unsigned char *)eth_hdr(skb)+12;
		/*check vlan tag exist or not*/
		if(*(int16 *)(ptr)==(int16)htons(0x8100))
		{
			ptr=ptr+4;
		}

		/*check it's ipv6 packet or not*/
		if(*(int16 *)(ptr)!=(int16)htons(ETH_P_IPV6))
		{
			return -1;
		}

		ipv6h=(struct ipv6hdr *)(ptr+2);
		proto =  re865x_getIpv6TransportProtocol(ipv6h);

		//printk("%s:%d,proto is %d\n",__FUNCTION__,__LINE__,proto);
		 if((proto ==IPPROTO_UDP) ||(proto ==IPPROTO_TCP))
		{
			multicastDataInfo.ipVersion=6;
			memcpy(&multicastDataInfo.sourceIp, &ipv6h->saddr, sizeof(struct in6_addr));
			memcpy(&multicastDataInfo.groupAddr, &ipv6h->daddr, sizeof(struct in6_addr));
			/*
			printk("%s:%d,sourceIp is %x-%x-%x-%x\n",__FUNCTION__,__LINE__,
				multicastDataInfo.sourceIp[0],multicastDataInfo.sourceIp[1],multicastDataInfo.sourceIp[2],multicastDataInfo.sourceIp[3]);
			printk("%s:%d,groupAddr is %x-%x-%x-%x\n",__FUNCTION__,__LINE__,
				multicastDataInfo.groupAddr[0],multicastDataInfo.groupAddr[1],multicastDataInfo.groupAddr[2],multicastDataInfo.groupAddr[3]);
			*/
			ret= rtl_getMulticastDataFwdInfo(brIgmpModuleIndex, &multicastDataInfo, &multicastFwdInfo);
			//printk("%s:%d,ret is %d\n",__FUNCTION__,__LINE__,ret);
			if(ret!=0)
			{
				if(multicastFwdInfo.unknownMCast)
				{
					multicastFwdInfo.fwdPortMask=0xFFFFFFFF;
				}
				else
				{
					return -1;
				}

			}

			//printk("%s:%d,multicastFwdInfo.fwdPortMask is 0x%x\n",__FUNCTION__,__LINE__,multicastFwdInfo.fwdPortMask);

			skb_push(skb, ETH_HLEN);

			prev = NULL;
			fwdCnt=0;
			list_for_each_entry_safe(p, n, &bridge0->port_list, list)
			{
				port_bitmask = (1 << p->port_no);
				if ((port_bitmask & multicastFwdInfo.fwdPortMask) && (skb->dev != p->dev && p->state == BR_STATE_FORWARDING))
				{
					if (prev != NULL)
					{
						if ((skb2 = skb_clone(skb, GFP_ATOMIC)) == NULL)
						{
							kfree_skb(skb);
							return 0;
						}
						skb2->dev=prev->dev;
						//printk("%s:%d,prev->dev->name is %s\n",__FUNCTION__,__LINE__,prev->dev->name);
						#if defined(CONFIG_COMPAT_NET_DEV_OPS)
						prev->dev->hard_start_xmit(skb2, prev->dev);
						#else
						prev->dev->netdev_ops->ndo_start_xmit(skb2,prev->dev);
						#endif
						fwdCnt++;
					}

					prev = p;
				}
			}

			if (prev != NULL)
			{
				skb->dev=prev->dev;
				//printk("%s:%d,prev->dev->name is %s\n",__FUNCTION__,__LINE__,prev->dev->name);
			       #if defined(CONFIG_COMPAT_NET_DEV_OPS)
				prev->dev->hard_start_xmit(skb, prev->dev);
				#else
				prev->dev->netdev_ops->ndo_start_xmit(skb,prev->dev);
				#endif
				fwdCnt++;
			}

			if(fwdCnt==0)
			{
				//printk("%s:%d\n",__FUNCTION__,__LINE__);
				/*avoid memory leak*/
				skb_pull(skb, ETH_HLEN);
				return -1;
			}

			return 0;
		}

	}
#endif/*if 0*/

	return -1;
#endif
}

#endif
