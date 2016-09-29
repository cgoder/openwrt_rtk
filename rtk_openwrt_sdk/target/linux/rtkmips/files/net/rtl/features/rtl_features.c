#include <linux/types.h>
#include <linux/netfilter.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/moduleparam.h>
#include <linux/notifier.h>
#include <linux/kernel.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/tcp.h>

#if defined(CONFIG_PROC_FS)
#include <linux/proc_fs.h>
#endif

#if	defined(CONFIG_RTL_HARDWARE_NAT )&&defined(CONFIG_RTL_MULTIPLE_WAN)
#include <net/arp.h>
#endif
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <net/netfilter/nf_conntrack_helper.h>
#if defined(CONFIG_RTL_HARDWARE_NAT)
#include <net/ip_fib.h>
#include <net/ip_vs.h>
#include <net/netfilter/nf_nat.h>
#include <net/netfilter/nf_nat_core.h>
#endif
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
#include <linux/interrupt.h>
#include <linux/netfilter.h>
#endif
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_nic.h>
#if defined(CONFIG_RTL_HARDWARE_NAT)
#include <net/rtl/rtl865x_nat.h>
#endif

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

#include <net/rtl/features/rtl_features.h>
#include <linux/version.h>

#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
#include <linux/netfilter/nf_conntrack_tcp.h>
#endif

#if defined(CONFIG_RTL_FAST_IPV6)
#include <linux/in6.h>
#include <linux/icmpv6.h>
#include <linux/mroute6.h>

#include <net/ipv6.h>
#include <net/transp_v6.h>
#include <net/rawv6.h>
#include <net/ndisc.h>
#include <net/ip6_route.h>
#include <net/addrconf.h>
#include <net/xfrm.h>
#endif
//#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
#include <net/rtl/fastpath/fastpath_core.h>
//#endif

#if defined(CONFIG_RTL_LOCAL_PUBLIC) || defined(CONFIG_RTL_MULTIPLE_WAN) || (defined(CONFIG_NET_SCHED)&&defined(CONFIG_RTL_IPTABLES_FAST_PATH)) || defined(CONFIG_RTL_HW_QOS_SUPPORT)  ||defined(CONFIG_RTL_HARDWARE_NAT)
#include <net/rtl/rtl865x_netif.h>
#endif

#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
#include <net/rtl/rtl865x_outputQueue.h>
#endif

#if defined (CONFIG_RTL_LOCAL_PUBLIC)
#include <net/rtl/rtl865x_localPublic.h>
extern int rtl865x_curOpMode;
#endif

#if defined(CONFIG_RTL_FAST_BRIDGE)
#include <net/rtl/fastpath/fast_br.h>
#endif

#if defined(CONFIG_BRIDGE)&&defined(CONFIG_RTL_AVOID_ADDING_WLAN_PKT_TO_HW_NAT)
#include <bridge/br_private.h>
#endif

#if defined(CONFIG_NET_SCHED)
__DRAM_GEN int gQosEnabled;
#endif

#ifdef CONFIG_RTL_HARDWARE_NAT
/*2007-12-19*/
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
#include <net/rtl/rtl865x_ip_api.h>
#endif
#endif

#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_ipv4/ip_tables.h>

#if defined(FAST_PATH_SPI_ENABLED)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#include <net/netfilter/nf_conntrack_zones.h>
#endif
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#include <linux/seq_file.h>
extern struct proc_dir_entry proc_root;
#endif

#if defined(CONFIG_FAST_PATH_MODULE) && defined(CONFIG_RTL_IPTABLES_FAST_PATH)
enum LR_RESULT (*FastPath_hook4)( rtl_fp_napt_entry *fpNaptEntry)=NULL;
enum LR_RESULT (*FastPath_hook6)( rtl_fp_napt_entry *fpNaptEntry,
#if defined(IMPROVE_QOS)
									void *pskb, void *ct,
#endif
                                                               enum NP_FLAGS flags)=NULL;
#include <linux/version.h>
enum LR_RESULT (*FastPath_hook11)(rtl_fp_napt_entry *fpNaptEntry, uint32 interval)=NULL;
int (*fast_path_hook)(struct sk_buff **pskb) = NULL;
EXPORT_SYMBOL(FastPath_hook4);
EXPORT_SYMBOL(FastPath_hook6);
EXPORT_SYMBOL(FastPath_hook11);
EXPORT_SYMBOL(fast_path_hook);

enum LR_RESULT (*FastPath_hook1)( ipaddr_t ip, ipaddr_t mask ) = NULL;
enum LR_RESULT (*FastPath_hook2)( ipaddr_t ip, ipaddr_t mask, ipaddr_t gateway, uint8* ifname, enum RT_FLAGS flags ) = NULL;
enum LR_RESULT (*FastPath_hook3)( ipaddr_t ip, ipaddr_t mask, ipaddr_t gateway, uint8* ifname, enum RT_FLAGS flags ) = NULL;

int (*FastPath_hook9)( void )=NULL;
int (*FastPath_hook10)(void *skb)=NULL;
EXPORT_SYMBOL(FastPath_hook9);
EXPORT_SYMBOL(FastPath_hook10);

EXPORT_SYMBOL(FastPath_hook1);
EXPORT_SYMBOL(FastPath_hook2);
EXPORT_SYMBOL(FastPath_hook3);
#endif
#if defined(CONFIG_RTL_HW_QOS_SUPPORT)

int (*qosGetSkbMarkByNaptEntryHook)(rtl865x_napt_entry *naptEntry, rtl865x_qos_mark *qosMark, struct sk_buff *pskb)=NULL;
EXPORT_SYMBOL(qosGetSkbMarkByNaptEntryHook);
#endif

#ifdef FAST_PPTP
	void (*sync_tx_pptp_gre_seqno_hook)(void *skb) = NULL;
#ifdef CONFIG_FAST_PATH_MODULE
EXPORT_SYMBOL(sync_tx_pptp_gre_seqno_hook);
#endif
#endif

void htonl_array(u32 *org_buf, u32 *dst_buf, unsigned int words)
{
	int i = 0;
	
	if (!org_buf || !dst_buf)
		return;
	while (words--) {
		dst_buf[i] = htonl(org_buf[i]);
		i++;
	}
	
	return;
}
void ntohl_array(u32 *org_buf, u32 *dst_buf, unsigned int words)
{
	int i = 0;
	
	if (!org_buf || !dst_buf)
		return;
	while (words--) {
		dst_buf[i] = ntohl(org_buf[i]);
		i++;
	}

	return;
}
#if !defined(CONFIG_RTK_VLAN_SUPPORT)
extern int32 rtl8651_setAsicOperationLayer(uint32 layer); 
#endif

int routerTypeFlag = 0;

#if	defined(CONFIG_RTL_HARDWARE_NAT)
__DRAM_GEN int gHwNatEnabled = 1;
EXPORT_SYMBOL(gHwNatEnabled);
#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
int  rtl_qosGetSkbMarkByNaptEntryHook(rtl865x_napt_entry *naptEntry, rtl865x_qos_mark *qosMark, struct sk_buff *pskb)
{
	int ret=0;
	 if(qosGetSkbMarkByNaptEntryHook)
		ret =qosGetSkbMarkByNaptEntryHook(naptEntry,qosMark,pskb);
	return ret;
}
#endif
int32 rtl865x_handle_nat(struct nf_conn *ct, int act, struct sk_buff *skb)
{
	struct nf_conn_nat *nat;
	u_int32_t sip, dip, gip;
	u_int16_t sp, dp, gp, proto=0;
	int timeval;
	int rc=0;

#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
	uint32 ret;
	struct net_device	*lanDev, *wanDev;
#endif

#if defined(CONFIG_RTL_LAYERED_DRIVER_L4)
	rtl865x_napt_entry rtl865xNaptEntry;
	rtl865x_priority rtl865xPrio;
	#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
	rtl865x_qos_mark rtl865xQosMark;
	#endif
#endif

	if (gHwNatEnabled!=1)
		return -1;

	proto = (ct->tuplehash[0].tuple.dst.protonum==IPPROTO_TCP)?RTL865X_PROTOCOL_TCP:RTL865X_PROTOCOL_UDP;

	if (ct->status & IPS_SRC_NAT)
	{ /* outbound flow */
		sip	= ct->tuplehash[0].tuple.src.u3.ip;
		dip 	= ct->tuplehash[0].tuple.dst.u3.ip;
		gip 	= ct->tuplehash[1].tuple.dst.u3.ip;
		sp  	= (proto)? ct->tuplehash[0].tuple.src.u.tcp.port: ct->tuplehash[0].tuple.src.u.udp.port;
		dp  	= (proto)? ct->tuplehash[0].tuple.dst.u.tcp.port: ct->tuplehash[0].tuple.dst.u.udp.port;
		gp  	= (proto)? ct->tuplehash[1].tuple.dst.u.tcp.port: ct->tuplehash[1].tuple.dst.u.udp.port;
	}
	else if (ct->status & IPS_DST_NAT)
	{ /* inbound flow */
		sip	= ct->tuplehash[1].tuple.src.u3.ip;
		dip 	= ct->tuplehash[1].tuple.dst.u3.ip;
		gip 	= ct->tuplehash[0].tuple.dst.u3.ip;
		sp  	= (proto)? ct->tuplehash[1].tuple.src.u.tcp.port: ct->tuplehash[1].tuple.src.u.udp.port;
		dp  	= (proto)? ct->tuplehash[1].tuple.dst.u.tcp.port: ct->tuplehash[1].tuple.dst.u.udp.port;
		gp  	= (proto)? ct->tuplehash[0].tuple.dst.u.tcp.port: ct->tuplehash[0].tuple.dst.u.udp.port;
	}
	else
		return -1;

	/* do not add hardware NAPT table if protocol is UDP and source IP address is equal to gateway IP address */
	if ((act == 1) && (proto == 0) && (sip == gip))
		return -1;

	/* for TZO DDNS */
	if ((act == 1) && (proto == 1) && (dp == htons(21347))) {
		return -1;
	}

	if (act == 2) {
		/* query for idle */
		timeval = 0;
#ifdef CONFIG_RTL_LAYERED_DRIVER_L4
		rtl865xNaptEntry.protocol=proto;
		rtl865xNaptEntry.intIp=sip;
		rtl865xNaptEntry.intPort=sp;
		rtl865xNaptEntry.extIp=gip;
		rtl865xNaptEntry.extPort=gp;
		rtl865xNaptEntry.remIp=dip;
		rtl865xNaptEntry.remPort=dp;

		timeval = rtl865x_naptSync(&rtl865xNaptEntry, 0);
#endif
		return timeval;
	}
	else if (act == 0) {
		/* delete */
		rc = 0;
#ifdef CONFIG_RTL_LAYERED_DRIVER_L4
		rtl865xNaptEntry.protocol=proto;
		rtl865xNaptEntry.intIp=sip;
		rtl865xNaptEntry.intPort=sp;
		rtl865xNaptEntry.extIp=gip;
		rtl865xNaptEntry.extPort=gp;
		rtl865xNaptEntry.remIp=dip;
		rtl865xNaptEntry.remPort=dp;

		rc = rtl865x_delNaptConnection(&rtl865xNaptEntry);
#endif
	}
	else {
		#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
		if (NULL!=skb)
		{
			rtl865xNaptEntry.protocol=proto;
			rtl865xNaptEntry.intIp=sip;
			rtl865xNaptEntry.intPort=sp;
			rtl865xNaptEntry.extIp=gip;
			rtl865xNaptEntry.extPort=gp;
			rtl865xNaptEntry.remIp=dip;
			rtl865xNaptEntry.remPort=dp;
	
			rtl865xQosMark.downlinkMark=0;	//Initial
			rtl865xQosMark.uplinkMark=0;	//Initial
			ret=rtl_qosGetSkbMarkByNaptEntryHook(&rtl865xNaptEntry, &rtl865xQosMark, skb);

			lanDev=rtl865x_getLanDev();
			wanDev=rtl865x_getWanDev();
			if(lanDev){
				rtl865xPrio.downlinkPrio=rtl_qosGetPriorityByMark(lanDev->name, rtl865xQosMark.downlinkMark);
			}
			if(wanDev){
				rtl865xPrio.uplinkPrio=rtl_qosGetPriorityByMark(wanDev->name, rtl865xQosMark.uplinkMark);
			}

			if(lanDev)
				dev_put(lanDev);

			if(wanDev)
				dev_put(wanDev);
		} else
		#endif
		{
			rtl865xPrio.downlinkPrio=0;
			rtl865xPrio.uplinkPrio=0;
		}

#if defined(CONFIG_RTL_LAYERED_DRIVER_L4)
		rtl865xNaptEntry.protocol=proto;
		rtl865xNaptEntry.intIp=sip;
		rtl865xNaptEntry.intPort=sp;
		rtl865xNaptEntry.extIp=gip;
		rtl865xNaptEntry.extPort=gp;
		rtl865xNaptEntry.remIp=dip;
		rtl865xNaptEntry.remPort=dp;
#endif

		/* add */
#if defined(CONFIG_PROC_FS) && defined(CONFIG_NET_SCHED) && !defined(CONFIG_RTL_HW_QOS_SUPPORT)
		if (gQosEnabled == 0)
		{
#ifdef CONFIG_RTL_LAYERED_DRIVER_L4
			rc =  rtl865x_addNaptConnection(&rtl865xNaptEntry, &rtl865xPrio);
#endif
		}
		else
		{
			act = 0;
		}
#else
#ifdef CONFIG_RTL_LAYERED_DRIVER_L4
		rc =  rtl865x_addNaptConnection(&rtl865xNaptEntry, &rtl865xPrio);
#endif

#endif
       }

	nat = nfct_nat(ct);
	if (!rc && nat && act == 1) /* mark it as an asic entry */
		nat->hw_acc = 1;
	if (!rc && nat && act == 0) /* unmark it */
		nat->hw_acc = 0;

	#ifdef CONFIG_HARDWARE_NAT_DEBUG
	/*2007-12-19*/
	DEBUGP("%s:%d:(%s): errno=%d\n %s (%u.%u.%u.%u:%u -> %u.%u.%u.%u:%u) g:(%u.%u.%u.%u:%u)\n",
			__FUNCTION__,__LINE__,((is_add)?"add_nat": "del_nat"), rc, ((proto)? "tcp": "udp"),
			NIPQUAD(sip), sp, NIPQUAD(dip), dp, NIPQUAD(gip), gp);
	#endif

	return 0;
}

/* return value:
	FAILED:		ct should be delete
	SUCCESS:	ct should NOT be delete.
*/
int rtl_hwnat_timer_update(struct nf_conn *ct)
{
	unsigned long expires, now, elasped;
	struct nf_conn_nat *nat;

	if (gHwNatEnabled!=1)
		return FAILED;

	nat = nfct_nat(ct);
	if (nat==NULL || nat->hw_acc!=1)
		return FAILED;

	now = jiffies;
	//read_lock_bh(&nf_conntrack_lock);
	if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_UDP)	{
		if(ct->status & IPS_SEEN_REPLY) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			expires = udp_get_timeouts_by_state(UDP_CT_REPLIED,(void *)ct,1);
#else
            #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
			expires = udp_get_timeouts_by_state(UDP_CT_REPLIED);
			#else
			expires = nf_ct_udp_timeout_stream;
			#endif
#endif
		} else {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			expires = udp_get_timeouts_by_state(UDP_CT_UNREPLIED,(void *)ct,1);
#else
            #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
			expires = udp_get_timeouts_by_state(UDP_CT_UNREPLIED);
			#else
			expires = nf_ct_udp_timeout;
			#endif
#endif
		}
	} else if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_TCP &&
		ct->proto.tcp.state < TCP_CONNTRACK_LAST_ACK) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		expires = tcp_get_timeouts_by_state(ct->proto.tcp.state,(void *)ct,1);
#else
		expires = tcp_get_timeouts_by_state(ct->proto.tcp.state);
#endif
	} else {
		//read_unlock_bh(&nf_conntrack_lock);
		return FAILED;
	}
	//read_unlock_bh(&nf_conntrack_lock);

	elasped = rtl865x_handle_nat(ct, 2, NULL);
	if (elasped>=0 && (elasped*HZ)<expires) {
		/* update ct expires time */
		ct->timeout.expires = now+(expires-(elasped*HZ));
		rtl_check_for_acc(ct, ct->timeout.expires);
		return SUCCESS;
	} else {
		return FAILED;
	}

}
#endif

int get_dev_ip_mask(const char * name, unsigned int *ip, unsigned int *mask)
{
	struct in_device *in_dev;
	struct net_device *landev;
	struct in_ifaddr *ifap = NULL;
	
	if((name == NULL) || (ip==NULL) || (mask == NULL)) 
	{
		return -1;
	}
	
	if ((landev = __dev_get_by_name(&init_net, name)) != NULL)
	{
		in_dev=(struct in_device *)(landev->ip_ptr);
		if (in_dev != NULL) 
		{
			for (ifap=in_dev->ifa_list; ifap != NULL; ifap=ifap->ifa_next)
			{
				if (strcmp(name, ifap->ifa_label) == 0)
				{
					#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
					if (strncmp(landev->name, "ppp", strlen("ppp"))==0)
						*ip = ifap->ifa_local;
					else
					#endif
					*ip = ifap->ifa_address;
					*mask = ifap->ifa_mask;
					return 0;
				}
			}

		}
	}

	return -1;
}


#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT) || defined(CONFIG_RTL_WLAN_DOS_FILTER) ||defined(CONFIG_RTL_BATTLENET_ALG)
unsigned int _br0_ip;
unsigned int _br0_mask;
#ifndef CONFIG_RTL8686_GMAC
static void get_br0_ip_mask(void)
#else
void get_br0_ip_mask(void)
#endif
{

	get_dev_ip_mask(RTL_PS_BR0_DEV_NAME, &_br0_ip, &_br0_mask);
}
#endif

#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
int smart_count=0;
unsigned long smart_count_start_timer;

/* return value:
	FAILED:			ct should be delete
	SUCCESS:		ct should NOT be delete.
*/
void rtl_delConnCache(struct nf_conn *ct)
{
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	enum NP_PROTOCOL protocol;
	rtl_fp_napt_entry rtlFpNaptEntry;
	#endif
	#ifdef CONFIG_RTL_HARDWARE_NAT
	struct nf_conn_nat *nat;
	#endif
#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	if (ct->removed == 1) // this ct's fastpath entry was already deleted.
		return;
#endif
	if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_TCP) {
		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
		protocol = NP_TCP;
		#endif
	} else if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_UDP) {
		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
		protocol = NP_UDP;
		#endif
	}
#if  defined(CONFIG_RTL_FAST_GRE)
	else if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_GRE) {
		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
		protocol = NP_GRE;
		#endif
	}
#endif
	else {
		return;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#else
	spin_lock_bh(&nf_conntrack_lock);
#endif
	#if defined(CONFIG_RTL_HARDWARE_NAT)
	nat = nfct_nat(ct);
	if ((nat!=NULL) && (nat->hw_acc==1)) {
		rtl865x_handle_nat(ct, 0, NULL);
	}
	#endif

	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	if(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip
		   == ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip) {
		   /*case  WAN->LAN(BC->AB) use C|A-B*/

		rtlFpNaptEntry.protocol=protocol;
		rtlFpNaptEntry.intIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
		rtlFpNaptEntry.intPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;
		rtlFpNaptEntry.extIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip;
		rtlFpNaptEntry.extPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all;
		rtlFpNaptEntry.remIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
		rtlFpNaptEntry.remPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;

		#ifdef CONFIG_FAST_PATH_MODULE
		if(FastPath_hook4!=NULL)
		{
			FastPath_hook4(&rtlFpNaptEntry) ;
		}
		#else
		rtk_delNaptConnection(&rtlFpNaptEntry) ;
		#endif
	}	else if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip
			== ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip) {
		/*case  LAN->WAN(AB->BC) use A|C-B*/

		rtlFpNaptEntry.protocol=protocol;
		rtlFpNaptEntry.intIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
		rtlFpNaptEntry.intPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;
		rtlFpNaptEntry.extIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip;
		rtlFpNaptEntry.extPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u.all;
		rtlFpNaptEntry.remIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
		rtlFpNaptEntry.remPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;

		#ifdef CONFIG_FAST_PATH_MODULE
		if(FastPath_hook4!=NULL)
		{
			FastPath_hook4(&rtlFpNaptEntry);
		}
		#else
		rtk_delNaptConnection(&rtlFpNaptEntry);
		#endif
	}
	#endif

#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	ct->removed = 1; // set this ct has delete fastpath entry
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#else
	spin_unlock_bh(&nf_conntrack_lock);
#endif
}

void rtl_check_for_acc(struct nf_conn *ct, unsigned long expires)
{
	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	int	newstate;
	struct list_head* state_hash;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#else
	write_lock_bh(&nf_conntrack_lock);
#endif
	if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_TCP) {
		newstate = ct->proto.tcp.state;
		state_hash = Tcp_State_Hash_Head[newstate].state_hash;
	} else if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_UDP) {
		if(ct->status & IPS_SEEN_REPLY)
			newstate = 1;
		else
			newstate = 0;
		state_hash = Udp_State_Hash_Head[newstate].state_hash;
	} else {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#else
		write_unlock_bh(&nf_conntrack_lock);
#endif
		return;
	}

	list_move_tail(&ct->state_tuple, state_hash);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#else
	write_unlock_bh(&nf_conntrack_lock);
#endif
	#endif
}
EXPORT_SYMBOL(rtl_check_for_acc);

extern int rtl_fpTimer_update_hook(void *ct);
int32 rtl_connCache_timer_update(struct nf_conn *ct)
{
	spin_lock_bh(&nf_conntrack_lock);
	if (time_after_eq(jiffies, ct->timeout.expires)) {
		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
		//if (SUCCESS==rtl_fpTimer_update((void*)ct))
		if (SUCCESS==rtl_fpTimer_update_hook((void*)ct)) {
			add_timer(&ct->timeout);
			spin_unlock_bh(&nf_conntrack_lock);
			return SUCCESS;
		}
		#endif

		#if defined(CONFIG_RTL_HARDWARE_NAT)
		if (SUCCESS==rtl_hwnat_timer_update(ct)) {
			add_timer(&ct->timeout);
			spin_unlock_bh(&nf_conntrack_lock);
			return SUCCESS;
		}
		#endif
	}
	spin_unlock_bh(&nf_conntrack_lock);
	return FAILED;
}

#ifdef CONFIG_RTL_FAST_IPV6
int rtl_V6_connCache_timer_update(struct nf_conn *ct)
{
	spin_lock_bh(&nf_conntrack_lock);
	if (time_after_eq(jiffies, ct->timeout.expires)) 
	{
		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
			if (SUCCESS== rtl_V6_Cache_Timer_update((void*)ct))
			{
				add_timer(&ct->timeout);
				spin_unlock_bh(&nf_conntrack_lock);
				return SUCCESS;
			}
		#endif
	}
	spin_unlock_bh(&nf_conntrack_lock);
	return FAILED;

}

#endif
#if defined(IMPROVE_QOS)
/*
 * ### for iperf application test ###
 * the behavior of iperf UDP test is LAN PC (client) will burst UDP from LAN to WAN (by one way),
 * WAN PC (server) will only send one UDP packet (statistics) at the end of test.
 * so the fastpath or hardware NAT will create link at the end of test.
 *
 * the purpose for adding the following code is to create fastpath or hardware NAT link
 * when we only get one packet from LAN to WAN in UDP case.
 */
static inline int32 rtl_addConnCheck(struct nf_conn *ct, struct iphdr *iph, struct sk_buff *skb)
{
	extern unsigned int	_br0_ip;
	extern unsigned int	_br0_mask;
	extern int			smart_count;
	extern unsigned long smart_count_start_timer;
	struct tcphdr		*tcph;
	uint32	sip, dip;
	int32	create_conn;

	sip = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
	dip = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
	create_conn = FALSE;

	if (((ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip
			 == ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip) ||
			(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip
			 == ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip))
	#if defined(UNNUMBER_IP)
		 && (is_unnumber_ip(dip)==FALSE)
	#endif
	) {
		/* UDP and "LAN to WAN" */
		/* ignore some cases:
		 *	1. sip = br0's ip -----> (ex. sip 192.168.1.254 ==> dip 239.255.255.250)
		 * 	2. (sip & br0's mask) != (br0's ip & br0's mask) -----> sip is not in br0's subnet
		 *	3. (dip & br0's mask) =  (br0's ip & br0's mask) -----> dip is in br0's subnet
		 *	4. dip != multicast IP address
		 *	5. sip != gip
		 */
		if (iph->protocol == IPPROTO_UDP) {
			if ((ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip
					 == ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip)&&
				(sip != _br0_ip) &&
				((sip & _br0_mask) == (_br0_ip & _br0_mask)) &&
				((dip & _br0_mask) != (_br0_ip & _br0_mask)) &&
				((dip & htonl(0xf0000000)) != htonl(0xe0000000)) &&
				(sip != (ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip))) {
				create_conn = TRUE;
			} else if ((ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip
					 	== ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip)&&
					 ((sip & _br0_mask) != (_br0_ip & _br0_mask))&&
					 ((dip & _br0_mask) == (_br0_ip & _br0_mask))&&
					 (iph->daddr ==dip)) {
				create_conn = TRUE;
			}
		} else if (iph->protocol == IPPROTO_TCP) {
			tcph=(void *) iph + iph->ihl*4;
			if (!tcph->fin && !tcph->syn && !tcph->rst &&
				#if !defined(CONFIG_RTL_URL_PATCH)
				tcph->psh==1 &&
				#endif
				tcph->ack ==1 &&
				(((ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip==ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip) &&
				(iph->daddr !=_br0_ip) && ((sip & _br0_mask) == (_br0_ip & _br0_mask)) &&
				((dip & _br0_mask) != (_br0_ip & _br0_mask)) && (sip != (ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip)))||
				((ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip==ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip) &&
				((sip & _br0_mask) != (_br0_ip & _br0_mask)) &&
				((dip & _br0_mask) == (_br0_ip & _br0_mask))&& (sip == iph->saddr)))) {

				#if defined(CONFIG_RTL_URL_PATCH)
				if((ntohs(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all) == URL_PROTO_PORT) ||
				   ((ntohs(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all) != URL_PROTO_PORT) &&
				    (tcph->psh==1)))
				#endif
				{
					if (smart_count==0) {
						smart_count_start_timer = jiffies+HZ;
					}

				if (time_after(jiffies, smart_count_start_timer)) {
					smart_count_start_timer = jiffies+HZ;
					smart_count=0;
				}

					smart_count++;
					if(smart_count >810){
						//panic_printk("the case hit for mart flow:tcp state=%d, assured=%d\n",ct->proto.tcp.state,test_bit(IPS_ASSURED_BIT, &ct->status));
						create_conn=TRUE;
					}
				}
			}
		} else {
			return create_conn;
		}

#if defined(UNNUMBER_IP)
		if ((!create_conn)
			&& (is_unnumber_ip(sip)==TRUE))
			){
				create_conn = TRUE;
		}
#endif
	}

	return create_conn;
}

#if defined(CONFIG_RTL_AVOID_ADDING_WLAN_PKT_TO_HW_NAT)
static int rtl_isWlanPkt(struct nf_conn *ct)
{
	int ret = FALSE;
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	u16 vid = 0;
	#endif
	
#if defined(CONFIG_BRIDGE)
	struct net_device *lan_dev = __dev_get_by_name(&init_net, RTL_PS_BR0_DEV_NAME);
	struct net_bridge *br = netdev_priv(lan_dev);
	struct net_bridge_fdb_entry *dst;
	unsigned char Mac[6];
	__be32 intIp;

	if(ct->status & IPS_SRC_NAT){
		intIp = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
	}else if(ct->status & IPS_DST_NAT){
		intIp = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
	}

	if((intIp & _br0_mask) == (_br0_ip & _br0_mask)){
		if(arp_req_get_ha(intIp, lan_dev, Mac)==0){
            #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			#if defined(CONFIG_BRIDGE_VLAN_FILTERING)
				/*Fix jwj: todo...*/
			#else
			vid = 0;
			#endif
			if((dst = __br_fdb_get(br, Mac, vid))!=NULL)
			#else
			if((dst = __br_fdb_get(br, Mac))!=NULL)
			#endif
			{
				if(!memcmp(dst->dst->dev->name, "wlan", strlen("wlan")))
							return TRUE;
			}
		}
	}

#endif

	return ret;
}


static int rtl_checkLanIp(struct nf_conn *ct)
{

	__be32 lanIp=0;

	if(ct->status & IPS_SRC_NAT)
	{
		lanIp = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
	}
	else if(ct->status & IPS_DST_NAT)
	{
		lanIp = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
	}
	else
	{
		return FAILED;
	}

	if(rtl865x_isEthArp(htonl(lanIp))==TRUE)
	{
		return SUCCESS;
	}

	return FAILED;
}

#endif


void rtl_addConnCache(struct nf_conn *ct, struct sk_buff *skb)
{
	int assured;
	int create_conn;
	struct iphdr *iph;
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_URL_PATCH)
	enum NP_PROTOCOL protocol;
	#endif
	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	rtl_fp_napt_entry rtlFpNaptEntry;
	#endif

	if (nfct_help(ct))
		return;

	iph=ip_hdr(skb);
	if (iph->protocol== IPPROTO_TCP) {
		assured = ((ct->proto.tcp.state==TCP_CONNTRACK_ESTABLISHED)&&
					(test_bit(IPS_DST_NAT_DONE_BIT, &ct->status) ||
					test_bit(IPS_SRC_NAT_DONE_BIT, &ct->status)));

		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_URL_PATCH)
		protocol = NP_TCP;
		#endif
	} else if (iph->protocol== IPPROTO_UDP) {
		assured = (test_bit(IPS_DST_NAT_DONE_BIT, &ct->status) ||
				test_bit(IPS_SRC_NAT_DONE_BIT, &ct->status));

		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_URL_PATCH)
		protocol = NP_UDP;
		#endif
	} 
#if  defined(CONFIG_RTL_FAST_GRE)
	else if (iph->protocol== IPPROTO_GRE) {
		assured = (test_bit(IPS_DST_NAT_DONE_BIT, &ct->status) ||
				test_bit(IPS_SRC_NAT_DONE_BIT, &ct->status));

		#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_URL_PATCH)
		protocol = NP_GRE;
		#endif
	} 	
#endif
		else {
		return;
	}


#if defined(CONFIG_RTL_URL_PATCH)
	if((protocol == NP_TCP)&&(ntohs(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all) == URL_PROTO_PORT)&&assured)
		assured = 0;
#endif

	if (!assured) {
	        create_conn = rtl_addConnCheck(ct, iph, skb);
	} else
		create_conn = 0;

#if defined(CONFIG_RTL_HW_NAT_BYPASS_PKT)
	if (ct->rtl_ct.count++ < RTL_HW_NAT_BYPASS_PKT_NUM) {
		assured = 0;
		create_conn = 0;
	}
#endif

	#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
	/*1.add "!(ct->helper)" to fix ftp-cmd type packet
	  2.add identify case LAN->WAN(AB->BC) or WAN->LAN(BC->AB)
	  3.add !(ct->nat.info.helper) for best ALG avoid
	  */
	if (assured || create_conn) {
		if(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip
			== ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip) {
			/*case BC->AB*/
			/* wan->lan */

			rtlFpNaptEntry.protocol=protocol;
			rtlFpNaptEntry.intIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
			rtlFpNaptEntry.intPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;
			rtlFpNaptEntry.extIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip;
			rtlFpNaptEntry.extPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all;
			rtlFpNaptEntry.remIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
			rtlFpNaptEntry.remPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;

			#ifdef CONFIG_FAST_PATH_MODULE
			if(FastPath_hook6!=NULL)
			{
				FastPath_hook6(&rtlFpNaptEntry,
					skb, ct,
					NP_NONE);
			}
			#else
			rtk_addNaptConnection(&rtlFpNaptEntry,
				(void *)skb, (void*)ct,
				NP_NONE);
			#endif
		} else if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip
			== ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip) {
			/*case AB->BC*/
			/* lan->wan */

			rtlFpNaptEntry.protocol=protocol;
			rtlFpNaptEntry.intIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
			rtlFpNaptEntry.intPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;
			rtlFpNaptEntry.extIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip;
			rtlFpNaptEntry.extPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u.all;
			rtlFpNaptEntry.remIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
			rtlFpNaptEntry.remPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;

			#ifdef CONFIG_FAST_PATH_MODULE
			if(FastPath_hook6!=NULL)
			{
				FastPath_hook6(&rtlFpNaptEntry,
					skb, ct,
					NP_NONE);
			}
			#else
			rtk_addNaptConnection(&rtlFpNaptEntry,
				skb, ct,
				NP_NONE);
			#endif
		}
	}
	#endif

#if defined(CONFIG_RTL_FAST_GRE)
	if(protocol == NP_GRE)
		return ;
#endif
	#if	defined(CONFIG_RTL_HARDWARE_NAT)
	/*2007-12-19*/
	#if !defined(CONFIG_RTL865x_TCPFLOW_NONE_STATUS_CHECK)
	if (assured || create_conn)
	#endif
	{
		#if defined(CONFIG_RTL_AVOID_ADDING_WLAN_PKT_TO_HW_NAT)
		//if(rtl_isWlanPkt(ct) == TRUE)
		//	return;
		if(rtl_checkLanIp(ct)==SUCCESS)
		{
			rtl865x_handle_nat(ct, 1, skb);
		}
		#else
		rtl865x_handle_nat(ct, 1, skb);
		#endif

	}
	#endif
}

#endif  /* defined(IMPROVE_QOS)  */

#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
#if !defined(IMPROVE_QOS) ||defined(CONFIG_RTL_ROUTER_FAST_PATH)
/*
 * ### for iperf application test ###
 * the behavior of iperf UDP test is LAN PC (client) will burst UDP from LAN to WAN (by one way),
 * WAN PC (server) will only send one UDP packet (statistics) at the end of test.
 * so the fastpath or hardware NAT will create link at the end of test.
 *
 * the purpose for adding the following code is to create fastpath or hardware NAT link
 * when we only get one packet from LAN to WAN in UDP case.
 */
static int32 rtl_fpAddConnCheck(struct nf_conn *ct, struct iphdr *iph, struct sk_buff *skb)
{
	extern unsigned int	_br0_ip;
	extern unsigned int	_br0_mask;
	struct tcphdr		*tcph;
	uint32	sip, dip;
	int32	create_conn;

	sip = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
	dip = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
	create_conn = FALSE;

	if ((ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip
		 == ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip)
	#if defined(UNNUMBER_IP)
		 && (is_unnumber_ip(dip)==FALSE)
	#endif
	) {
		/* lan -> wan */
		if (iph->protocol == IPPROTO_UDP &&
			(sip != _br0_ip) &&
			((((sip & _br0_mask) == (_br0_ip & _br0_mask)) &&
			((dip & _br0_mask) != (_br0_ip & _br0_mask))) ||
			(((sip & _br0_mask) != (_br0_ip & _br0_mask))&&
			((dip & _br0_mask) == (_br0_ip & _br0_mask))))&&
			(!IS_CLASSD_ADDR(ntohl(dip))) &&
			((routerTypeFlag == 1) ||(sip != (ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip)))
			) {
			create_conn = TRUE;
			/* copied from last 2 line of this function **/
			set_bit(IPS_SEEN_REPLY_BIT, &ct->status);
			/* next 3 lines are copied from udp_packet() in ip_conntrack_proto_udp.c */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			nf_ct_refresh(ct,skb, udp_get_timeouts_by_state(UDP_CT_REPLIED,(void *)ct,1));
#else
            #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
			nf_ct_refresh(ct,skb, udp_get_timeouts_by_state(UDP_CT_REPLIED));
			#else
			nf_ct_refresh(ct,skb, nf_ct_udp_timeout_stream);
			#endif
#endif
			/* Also, more likely to be important, and not a probe */
			set_bit(IPS_ASSURED_BIT, &ct->status);
		} else if (iph->protocol == IPPROTO_TCP) {
			tcph=(void *) iph + iph->ihl*4;
			if (!tcph->fin && !tcph->syn && !tcph->rst && tcph->psh==1 &&
				tcph->ack ==TRUE &&  (iph->daddr !=_br0_ip) &&
				((((sip & _br0_mask) == (_br0_ip & _br0_mask)) &&
				((dip & _br0_mask) != (_br0_ip & _br0_mask))) ||
				(((sip & _br0_mask) != (_br0_ip & _br0_mask))&&
				((dip & _br0_mask) == (_br0_ip & _br0_mask))))&&
				((routerTypeFlag == 1) || (sip != (ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip)))
				) {
				if (smart_count==0) {
					smart_count_start_timer = jiffies+HZ;
				}

				if (time_after(jiffies, smart_count_start_timer)) {
					smart_count_start_timer = jiffies+HZ;
					smart_count=0;
				}

				smart_count++;
				if(smart_count >810){
					//panic_printk("the case hit for mart flow:tcp state=%d, assured=%d\n",ct->proto.tcp.state,test_bit(IPS_ASSURED_BIT, &ct->status));
					create_conn=TRUE;
				}
			}
		} else {
			return FALSE;
		}

#if defined(UNNUMBER_IP)
		if ((!create_conn)
			&& (is_unnumber_ip(sip)==TRUE))
			){
				create_conn = TRUE;
		}
#endif
	}

	return create_conn;
}

void rtl_fpAddConnCache(struct nf_conn *ct, struct sk_buff *skb)
{
	int assured;
	int create_conn;
	struct iphdr *iph;
	enum NP_PROTOCOL protocol;
	rtl_fp_napt_entry rtlFpNaptEntry;

	if (nfct_help(ct))
		return;

	iph=ip_hdr(skb);
	create_conn = rtl_fpAddConnCheck(ct, iph, skb);
	assured = test_bit(IPS_ASSURED_BIT, &ct->status);

	/*1.add "!(ct->helper)" to fix ftp-cmd type packet
	  2.add identify case LAN->WAN(AB->BC) or WAN->LAN(BC->AB)
	  3.add !(ct->nat.info.helper) for best ALG avoid
	  */

	if ((assured) || (TRUE==create_conn))
	{
		if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_TCP) {
			protocol = NP_TCP;
		} else if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum == IPPROTO_UDP) {
			protocol = NP_UDP;
		}


#if !defined(IMPROVE_QOS)
	if(((!rtl_isRouterType(ct)) && rtl_isNatTypeWantoLan(ct)) ||rtl_isRouterTypeWantoLan(ct))
#else
	if(rtl_isRouterTypeWantoLan(ct))
#endif
		{
			/*case BC->AB*/
			/* wan->lan */

			rtlFpNaptEntry.protocol=protocol;
			rtlFpNaptEntry.intIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
			rtlFpNaptEntry.intPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;
			rtlFpNaptEntry.extIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip;
			rtlFpNaptEntry.extPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all;
			rtlFpNaptEntry.remIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
			rtlFpNaptEntry.remPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;

			#ifdef CONFIG_FAST_PATH_MODULE
			if(FastPath_hook6!=NULL)
			{
				FastPath_hook6(&rtlFpNaptEntry,
				#if defined(IMPROVE_QOS)
				skb, ct,
				#endif
					NP_NONE);
			}
			#else
			rtk_addNaptConnection(&rtlFpNaptEntry,
							#if defined(IMPROVE_QOS)
							(void*)skb, (void*)ct,
							#endif
							NP_NONE);
			#endif
		}
#if !defined(IMPROVE_QOS)
	else if(((!rtl_isRouterType(ct)) && rtl_isNatTypeLantoWan(ct)) ||rtl_isRouterTypeLantoWan(ct))
#else
	else if(rtl_isRouterTypeLantoWan(ct))
#endif
		{
			/*case AB->BC*/
			/* lan->wan */

			rtlFpNaptEntry.protocol=protocol;
			rtlFpNaptEntry.intIp=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
			rtlFpNaptEntry.intPort=ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;
			rtlFpNaptEntry.extIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip;
			rtlFpNaptEntry.extPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u.all;
			rtlFpNaptEntry.remIp=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
			rtlFpNaptEntry.remPort=ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;

			#ifdef CONFIG_FAST_PATH_MODULE
			if(FastPath_hook6!=NULL)
			{
				FastPath_hook6(&rtlFpNaptEntry,
					#if defined(IMPROVE_QOS)
					skb, ct,
					#endif
					NP_NONE);
			}
			#else
			rtk_addNaptConnection(&rtlFpNaptEntry,
				#if defined(IMPROVE_QOS)
				skb, ct,
				#endif
				NP_NONE);
			#endif
		}
	}

}
#endif	/* defined(IMPROVE_QOS)  */
#endif
#endif


#ifdef CONFIG_RTL_FAST_IPV6
#define CON_SESSION_SINGLE_DIRECTION 1
#ifdef CON_SESSION_SINGLE_DIRECTION 
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
extern int	ipv6_chk_prefix(const struct in6_addr *addr, struct net_device *dev);
extern int	ipv6_chk_addr(struct net *net, const struct in6_addr *addr,
					      const struct net_device *dev, int strict);
#else
extern int ipv6_chk_prefix(struct in6_addr *addr, struct net_device *dev);
extern int ipv6_chk_addr(struct net *net, struct in6_addr *addr,
		  struct net_device *dev, int strict);
#endif
#endif
static inline int32 rtl_addV6ConnCheck
	(struct nf_conn *ct, struct ipv6hdr *iph, struct tcphdr *tcph,struct sk_buff *skb)
{
#ifdef CON_SESSION_SINGLE_DIRECTION 
    	int onlink = 0;
	int addr_chk= 0;
	int create_conn = 0;
    	struct  in6_addr	s6addr;
    	struct  in6_addr	d6addr;
   	struct net_device *dev = skb->dev;
	struct inet6_ifaddr	*addr_list=NULL;
	//struct inet6_dev *idev = in6_dev_get(dev);
#endif

	if(iph->nexthdr == IPPROTO_TCP)
	{
		if(!tcph->fin && !tcph->syn && !tcph->rst && tcph->ack ==1)
		{
			enum ip_conntrack_info ctinfo;
			ctinfo = (enum ip_conntrack_info)(skb->nfctinfo);	
			return 1;
		}
	}
	else if(iph->nexthdr == IPPROTO_UDP)
	{
		enum ip_conntrack_info ctinfo;
		ctinfo = (enum ip_conntrack_info)(skb->nfctinfo);
		if (CTINFO2DIR(ctinfo) == IP_CT_DIR_REPLY)
		{
			// receive reply udp ptk!			
			return 1;
		}
	}
	
#ifdef CON_SESSION_SINGLE_DIRECTION 
	enum ip_conntrack_info ctinfo;
	ctinfo = (enum ip_conntrack_info)(skb->nfctinfo);
	if ((dev!=NULL) && (CTINFO2DIR(ctinfo)==IP_CT_DIR_ORIGINAL)){
		  s6addr = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.in6;
		  d6addr = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.in6;
		  onlink = ipv6_chk_prefix(&s6addr,dev); /*2*/
		  addr_chk = ipv6_chk_addr(&init_net, &s6addr, dev, 0); /*1*/
		  create_conn = onlink && !addr_chk;
		  onlink = ipv6_chk_prefix(&d6addr,dev); /*3*/
		  create_conn = (create_conn && !onlink &&!ipv6_addr_is_multicast(&d6addr)) ; /*4*/
		  #ifdef CONFIG_RTL_FAST_IPV6_DEBUG
		  panic_printk("[%s:] %d, devname:%s, create_conn:%d\n",__func__,__LINE__,dev->name,create_conn);
          #endif
	}
	return create_conn;
#else
	return 0;
#endif
}

int rtl_AddV6ConnCache(struct nf_conn *ct, struct sk_buff *skb)
{
	int assured = 0;
	int create_conn = 0;
	struct ipv6hdr *iph =ipv6_hdr(skb);
	struct tcphdr *tcph = (struct tcphdr *)(((unsigned char *)iph) + sizeof(struct ipv6hdr));

	if(iph->version !=6)	
		return 0;

	if (skb->dev == NULL)
		return 0;
	
	if ((iph->nexthdr != IPPROTO_TCP)&& (iph->nexthdr != IPPROTO_UDP))
		return 0;
	
	create_conn = rtl_addV6ConnCheck(ct,iph,tcph,skb);

	if(create_conn)
	{
		struct V6_Tuple V6PathEntry;		
		enum ip_conntrack_info ctinfo;
		ctinfo = (enum ip_conntrack_info)(skb->nfctinfo);		
		memset(&V6PathEntry,0,sizeof(struct V6_Tuple));
		if (CTINFO2DIR(ctinfo) == IP_CT_DIR_ORIGINAL)
		{
			V6PathEntry.saddr = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.in6;
			V6PathEntry.daddr = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.in6;	
			V6PathEntry.protocol = iph->nexthdr;		
			V6PathEntry.sport = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;
			V6PathEntry.dport = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all;	
		}
		else if(CTINFO2DIR(ctinfo) == IP_CT_DIR_REPLY)
		{
			V6PathEntry.saddr = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.in6;
			V6PathEntry.daddr = ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.in6;	
			V6PathEntry.protocol = iph->nexthdr;		
			V6PathEntry.sport = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;
			V6PathEntry.dport = ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u.all;				
		}
		else
			return 0;
		
		rtk_addV6Connection(&V6PathEntry,skb,ct);
	}
}

int rtl_DelV6ConnCache(struct nf_conn *ct)
{	
	struct V6_Tuple V6PathEntry;
	
	if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum != IPPROTO_TCP && 
		ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum != IPPROTO_UDP)
	{
		return 0;
	}

	//delete original dir		
	memset(&V6PathEntry,0,sizeof(struct V6_Tuple));
	V6PathEntry.saddr = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.in6;
	V6PathEntry.daddr = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.in6;		
	V6PathEntry.protocol = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum;
	V6PathEntry.sport = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;
	V6PathEntry.dport = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all;		
	rtk_delV6Connection(&V6PathEntry);

	//delelte reply dir
	memset(&V6PathEntry,0,sizeof(struct V6_Tuple));
	V6PathEntry.saddr = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.in6;
	V6PathEntry.daddr = ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.in6;	
	V6PathEntry.protocol = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum;
	V6PathEntry.sport = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;
	V6PathEntry.dport = ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u.all;			
	rtk_delV6Connection(&V6PathEntry);		
	return 1;
}
#endif
#if defined(CONFIG_PROC_FS) && defined(CONFIG_RTL_HARDWARE_NAT)
static struct proc_dir_entry *proc_hw_nat=NULL;
static char gHwNatSetting[16];
//extern unsigned int ldst, lmask, wdst, wmask;

static void rtl_get_extIp_router_timer_fn(unsigned long arg);
static int hw_nat_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	if (count < 2)
		return -EFAULT;

	if (buffer && !copy_from_user(&gHwNatSetting, buffer, 8)) {
		if ((gHwNatSetting[0] == '-')&&(gHwNatSetting[1] == '1') ) { /* hardware NAT disabled, operation mode = gateway */
			ACCESS_ONCE(gHwNatEnabled) = 0;
			rtl865x_nat_reinit();
			rtl865x_reChangeOpMode();
			//rtl8651_setAsicOperationLayer(4);
		}
		else if (gHwNatSetting[0] == '0') { /* hardware NAT disabled, operation mode = gateway */
			ACCESS_ONCE(gHwNatEnabled) = 0;
			rtl865x_nat_reinit();
			rtl865x_changeOpMode(GATEWAY_MODE);
			#if !defined(CONFIG_RTK_VLAN_SUPPORT)
			rtl8651_setAsicOperationLayer(4);
			#endif
		}
		else if (gHwNatSetting[0] == '1') { /* hardware NAT enabled, operation mode = gateway */

			rtl865x_changeOpMode(GATEWAY_MODE);
			#if !defined(CONFIG_RTK_VLAN_SUPPORT)
			rtl8651_setAsicOperationLayer(4);
			#endif
			ACCESS_ONCE(gHwNatEnabled) = 1;
            rtl_get_extIp_router_timer_fn(0);
		}
		else if (gHwNatSetting[0] == '2') { /* hardware NAT enabled, operation mode = bridge mode*/
			//rtl865x_delRoute(wdst, wmask);
			//rtl865x_delRoute(ldst, lmask);
			rtl865x_changeOpMode(BRIDGE_MODE);
			//rtl8651_setAsicOperationLayer(3);
			ACCESS_ONCE(gHwNatEnabled) = 2;
            rtl_get_extIp_router_timer_fn(0);
		}
		else if(gHwNatSetting[0] == '3'){ /* hardware NAT enabled, operation mode = wisp mode */
			rtl865x_changeOpMode(WISP_MODE);
			//rtl8651_setAsicOperationLayer(3);
			ACCESS_ONCE(gHwNatEnabled) = 3;
            rtl_get_extIp_router_timer_fn(0);
		}
		else if ((gHwNatSetting[0] == '8')&&
			((gHwNatSetting[1] == '5') /* L2TP */
			||(gHwNatSetting[1] == '4') /* PPTP */))
		{
			ACCESS_ONCE(gHwNatEnabled) = 0;
		}
		#if defined(CONFIG_RTL_HARDWARE_NAT) || defined(CONFIG_RTL_IPTABLES_FAST_PATH) ||defined(CONFIG_RTL_BATTLENET_ALG)
		else if (gHwNatSetting[0] == '9') {
			get_br0_ip_mask();
		}
		else if(gHwNatSetting[0] == '7'){
			routerTypeFlag = 1;
		}
		#endif
	
		if((count>0)&& (count<sizeof(gHwNatSetting)))
		{
			gHwNatSetting[count]=0;
		}
		return count;
	}
	return -EFAULT;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int hw_nat_read_proc(struct seq_file *s, void *v)
{
	seq_printf(s, "%s\n", gHwNatSetting);

	return 0;
}

int hw_nat_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, hw_nat_read_proc, NULL));
}

static ssize_t hw_nat_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return hw_nat_write_proc(file, userbuf,count, off);
}


struct file_operations hw_nat_proc_fops = {
        .open           = hw_nat_single_open,
	 .write		= hw_nat_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#else
static int hw_nat_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
	int len;

	len = sprintf(page, "%s\n", gHwNatSetting);

	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
}
#endif

#endif

#if defined(CONFIG_RTL_819X_SWCORE) && (defined(CONFIG_PROC_FS) && !defined(CONFIG_RTL_HARDWARE_NAT))
static struct proc_dir_entry *proc_sw_nat=NULL;
static char gSwNatSetting[16];


static int sw_nat_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	if (count < 2)
		return -EFAULT;

	if (buffer && !copy_from_user(&gSwNatSetting, buffer, 8)) {
		if (gSwNatSetting[0] == '0'){  /* operation mode = GATEWAY */
			//SoftNAT_OP_Mode(2);
			rtl865x_changeOpMode(GATEWAY_MODE);
			//rtl8651_setAsicOperationLayer(2);
		}
		else if (gSwNatSetting[0] == '1'){  /* operation mode = BRIDGE*/
			//SoftNAT_OP_Mode(1);
			rtl865x_changeOpMode(BRIDGE_MODE);
			//rtl8651_setAsicOperationLayer(2);
		}
		else if(gSwNatSetting[0] == '2'){ /* operation mode = WISP */
			rtl865x_changeOpMode(WISP_MODE);
			//rtl8651_setAsicOperationLayer(2);
		}
#if defined(CONFIG_RTL_HARDWARE_NAT) || defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_WLAN_DOS_FILTER) ||defined(CONFIG_RTL_BATTLENET_ALG)
		else if(gSwNatSetting[0] == '9'){
			get_br0_ip_mask();
		}
		else if(gSwNatSetting[0] == '7'){
			routerTypeFlag = 1;
		}
#endif

#ifdef CONFIG_RTL_WLAN_DOS_FILTER
		else if(gSwNatSetting[0] == 'a') {
			extern int wlan_dos_filter_enabled;
			wlan_dos_filter_enabled = 0;
		}
		else if(gSwNatSetting[0] == 'b') {
			extern int wlan_dos_filter_enabled;
			wlan_dos_filter_enabled = 1;
		}
#endif

		return count;
	}
	return -EFAULT;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int sw_nat_read_proc(struct seq_file *s, void *v)
{
	seq_printf(s, "%s\n", gSwNatSetting);

	return 0;
}

int sw_nat_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, sw_nat_read_proc, NULL));
}

static ssize_t sw_nat_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return sw_nat_write_proc(file, userbuf,count, off);
}


struct file_operations sw_nat_proc_fops = {
        .open           = sw_nat_single_open,
	 .write		= sw_nat_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#else
static int sw_nat_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
	int len;

	len = sprintf(page, "%s\n", gSwNatSetting);

	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
}
#endif

#endif /* defined(CONFIG_RTL_819X) && (defined(CONFIG_PROC_FS) && !defined(CONFIG_RTL_HARDWARE_NAT))	*/

#if defined(CONFIG_RTL_819X_SWCORE)
int32 rtl_nat_init(void)
{
	#if defined(CONFIG_PROC_FS) && defined(CONFIG_RTL_HARDWARE_NAT)
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	proc_hw_nat = proc_create_data("hw_nat", 0, &proc_root,
			 &hw_nat_proc_fops, NULL);
	#else
	proc_hw_nat = create_proc_entry("hw_nat", 0, NULL);
	if (proc_hw_nat) {
		proc_hw_nat->read_proc = hw_nat_read_proc;
		proc_hw_nat->write_proc = hw_nat_write_proc;
	}
	#endif
	#endif
	#if defined(CONFIG_PROC_FS) && !defined(CONFIG_RTL_HARDWARE_NAT)
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	proc_sw_nat = proc_create_data("sw_nat", 0, &proc_root,
			 &sw_nat_proc_fops, NULL);
	#else
	proc_sw_nat = create_proc_entry("sw_nat", 0, NULL);
	if (proc_sw_nat) {
		proc_sw_nat->read_proc = sw_nat_read_proc;
		proc_sw_nat->write_proc = sw_nat_write_proc;
	}
	#endif
	#endif

	#if	defined(CONFIG_RTL_HARDWARE_NAT)
	ACCESS_ONCE(gHwNatEnabled)=1;
	#endif

	return SUCCESS;
}
#endif

#if defined(CONFIG_RTL_LOCAL_PUBLIC) || defined(CONFIG_RTL_MULTIPLE_WAN) || (defined(CONFIG_NET_SCHED)&&defined(CONFIG_RTL_IPTABLES_FAST_PATH)) ||defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
extern int rtl865x_curOpMode;
struct net_device *rtl865x_getWanDev(void )
{
	struct net_device * wanDev=NULL;

	if(rtl865x_curOpMode==GATEWAY_MODE)
	{
#if defined(CONFIG_RTL_PUBLIC_SSID)
		wanDev=dev_get_by_name(&init_net,RTL_GW_WAN_DEVICE_NAME);
#else
		//Try ppp0 first
#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
#if defined(CONFIG_SWCONFIG_SUPPORT_HW_NAT)
		if (swconfig_vlan_enable)
			wanDev=dev_get_by_name(&init_net, RTL_SWCONFIG_DRV_PPP_NETIF_NAME);
		else
#endif
			wanDev=dev_get_by_name(&init_net, RTL_DRV_PPP_NETIF_NAME);
#else
		wanDev=dev_get_by_name(&init_net, RTL_PS_PPP0_DEV_NAME);
#endif
		if(wanDev==NULL)
		{
			//Try eth1 then
#if defined(CONFIG_SWCONFIG_SUPPORT_HW_NAT)
			if (swconfig_vlan_enable)
				wanDev=dev_get_by_name(&init_net, hw_nat_wan_dev_name);
			else
#endif
				wanDev=dev_get_by_name(&init_net,RTL_PS_WAN0_DEV_NAME);
		}
#endif
	}
	else if(rtl865x_curOpMode==WISP_MODE)
	{
#if defined(CONFIG_RTL_PUBLIC_SSID)
		wanDev=dev_get_by_name(&init_net,RTL_WISP_WAN_DEVICE_NAME);
#else
		wanDev=dev_get_by_name(&init_net,RTL_PS_WLAN0_DEV_NAME);
#endif
	}
	else if(rtl865x_curOpMode==BRIDGE_MODE)
	{
#if defined(CONFIG_RTL_PUBLIC_SSID)
		wanDev=dev_get_by_name(&init_net,RTL_BR_WAN_DEVICE_NAME);
#else
		wanDev=dev_get_by_name(&init_net,RTL_PS_BR0_DEV_NAME);
#endif
	}

	return wanDev;
}
EXPORT_SYMBOL(rtl865x_getWanDev);

struct net_device *rtl865x_getLanDev(void )
{
	struct net_device * lanDev=NULL;
	lanDev=dev_get_by_name(&init_net,RTL_PS_BR0_DEV_NAME);
	return lanDev;
}
EXPORT_SYMBOL(rtl865x_getLanDev);
#endif

#if defined (CONFIG_RTL_LOCAL_PUBLIC) || defined(CONFIG_RTL_HW_QOS_SUPPORT)
int rtl865x_attainDevType(unsigned char *devName, unsigned int *isLanDev, unsigned int *isWanDev)
{
	*isLanDev=0;
	*isWanDev=0;
	if(rtl865x_curOpMode==GATEWAY_MODE)
	{
#if defined(CONFIG_RTL_PUBLIC_SSID)
		if(strncmp(devName, RTL_PS_WAN0_DEV_NAME, 4) ==0 || strncmp(devName, RTL_GW_WAN_DEVICE_NAME, 3) ==0 ||
			rtl865x_from_public_ssid_device(devName)
			)
#else
		if(strncmp(devName, RTL_PS_WAN0_DEV_NAME, 4) ==0)
#endif
		{
			*isWanDev=1;
		}
		else if(	(strncmp(devName, RTL_PS_BR0_DEV_NAME, 3) ==0)||
				(strncmp(devName, RTL_PS_ETH_NAME, 3) ==0) ||
				(strncmp(devName, RTL_PS_WLAN_NAME, 4) ==0))
		{
			*isLanDev=1;
		}
		else
		{
			return -1;
		}

	}
	else if(rtl865x_curOpMode==WISP_MODE)
	{
		if(strncmp(devName, RTL_PS_WAN0_DEV_NAME, 4)==0)
		{
			*isWanDev=1;
		}
		else if(	(strncmp(devName, RTL_PS_BR0_DEV_NAME, 3) ==0) ||
				(strncmp(devName, RTL_PS_ETH_NAME, 3) ==0))
		{
			*isLanDev=1;
		}
		else
		{
			return -1;
		}
	}
	else if(rtl865x_curOpMode==BRIDGE_MODE)
	{
		if(	(strncmp(devName, RTL_PS_BR0_DEV_NAME, 3) ==0) ||
			(strncmp(devName, RTL_PS_ETH_NAME, 3) ==0) ||
			(strncmp(devName, RTL_PS_WLAN_NAME, 4) ==0))
		{
			*isLanDev=0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}

	return 0;
}
#endif

#if defined (CONFIG_RTL_LOCAL_PUBLIC)
int rtl865x_localPublicRx(struct sk_buff *skb)
{
	struct rtl865x_pktInfo pktInfo;
	unsigned int rxFromLan, rxFromWan;

	if(rtl865x_localPublicEnabled() ==0)
	{
		goto end_of_local_public_rx;
	}

	if(rtl865x_attainDevType(skb->dev->name, &rxFromLan, &rxFromWan))
	{
		return NET_RX_SUCCESS;
	}

	if(skb->localPublicFlags == 0x1)
	{
		//local public has done
		return NET_RX_SUCCESS;
	}
	#if 0
	printk("%s:%d,skb->dev->name is %s,rxFromLan is %d,rxFromWan is %d\n",__FUNCTION__,__LINE__,skb->dev->name,rxFromLan,rxFromWan);
	printk("EtherType: 0x%x\n", *((uint16*)&skb->mac.raw[12]));
	printk("%x:%x:%x:%x:%x:%x ==> %x:%x:%x:%x:%x:%x \n\n",
	skb->mac.raw[6], skb->mac.raw[7], skb->mac.raw[8],
	skb->mac.raw[9], skb->mac.raw[10], skb->mac.raw[11],
	skb->mac.raw[0], skb->mac.raw[1], skb->mac.raw[2],
	skb->mac.raw[3], skb->mac.raw[4], skb->mac.raw[5]);
	#endif
	if(rxFromWan)
	{
		/*rx from ethernet wan*/
		/*direction WAN--->LAN*/
		//pktInfo.data=skb->mac.raw;
		pktInfo.data=skb_mac_header(skb);
		pktInfo.action=RX_WAN_PACKET;
		rtl865x_checkLocalPublic(&pktInfo);

		if(pktInfo.fromLocalPublic==1)
		{
			kfree_skb(skb);
			return NET_RX_DROP;
		}
		else if(pktInfo.toLocalPublic==1)
		{

			skb->pkt_type=PACKET_HOST;
			//printk("%s:%d,pktInfo.fromLocalPublic is %d,pktInfo.toLocalPublic is %d\n",__FUNCTION__,__LINE__,pktInfo.fromLocalPublic,pktInfo.toLocalPublic );
			memcpy(eth_hdr(skb)->h_dest, skb->dev->dev_addr, 6);
		 }

	}
	else if (rxFromLan)
	{
		/*rx from ethernet lan*/
		pktInfo.data=skb_mac_header(skb);
		pktInfo.port=skb->srcPort;
		pktInfo.action=RX_LAN_PACKET;
		strcpy(pktInfo.dev, skb->dev->name);
		rtl865x_checkLocalPublic(&pktInfo);
		//printk("%s:%d,pktInfo.fromLocalPublic is %d,pktInfo.toLocalPublic is %d\n",__FUNCTION__,__LINE__,pktInfo.fromLocalPublic,pktInfo.toLocalPublic );
		if(pktInfo.fromLocalPublic==1)
		{
			skb->fromLocalPublic=1;
			skb->srcLocalPublicIp=pktInfo.srcIp;
			//if(pktInfo.toLocalPublic==1)
			{
				skb->pkt_type=PACKET_HOST;
				memcpy(eth_hdr(skb)->h_dest, skb->dev->dev_addr, 6);
				#if 0
				dest = eth_hdr(skb)->h_dest;
				src = eth_hdr(skb)->h_source;
				printk("=========%s(%d),dst(%x:%x:%x:%x:%x:%x),src(%x:%x:%x:%x:%x:%x)\n",__FUNCTION__,__LINE__,
					dest[0],dest[1],dest[2],dest[3],dest[4],dest[5],
					src[0],src[1],src[2],src[3],src[4],src[5]);
				#endif

			}
		}

	}
	skb->localPublicFlags = 0x1;

end_of_local_public_rx:
	return NET_RX_SUCCESS;
}

int rtl865x_localPublicTx(struct sk_buff *skb, struct net_device *dev)
{
	unsigned int txToLan, txToWan;
	if(rtl865x_attainDevType(skb->dev->name, &txToLan, &txToWan))
	{
		return NET_RX_SUCCESS;
	}

	if(txToWan)
	{
		if((skb->fromLocalPublic==1) && (skb->srcLocalPublicIp!=0))
		{
			rtl865x_getLocalPublicMac(skb->srcLocalPublicIp, eth_hdr(skb)->h_source);
		}

	}
	else if (txToLan)
	{
		/*needn't do anything*/

	}
	return NET_RX_SUCCESS;
}

#endif

int rtl865x_getDevIpAndNetmask(struct net_device * dev, unsigned int *ipAddr, unsigned int *netMask )
{
	struct in_device *in_dev;
	struct in_ifaddr *ifap = NULL;

	if((dev==NULL) || (ipAddr==NULL) || (netMask==NULL))
	{
		return FAILED;
	}

	*ipAddr=0;
	*netMask=0;

	in_dev=(struct in_device *)(dev->ip_ptr);
	if (in_dev != NULL) {
		for (ifap=in_dev->ifa_list; ifap != NULL; ifap=ifap->ifa_next) {
			if (strcmp(dev->name, ifap->ifa_label) == 0){
				if (strncmp(dev->name, "ppp", strlen("ppp"))==0)
					*ipAddr = ifap->ifa_local;
				else
					*ipAddr = ifap->ifa_address;
				*netMask = ifap->ifa_mask;
				return SUCCESS;
			}
		}

	}

	return FAILED;

}


#if defined(CONFIG_PROC_FS) && defined(CONFIG_NET_SCHED)
#define	QOS_CLASSIFY_INFO_LEN	16
typedef struct {
	/*	classify	*/
	unsigned int protocol;
	struct in_addr local_ip;
	struct in_addr  remote_ip;
	unsigned short lo_port;
	unsigned short re_port;

	/*	tc	*/
	uint32		mark;
	unsigned char	prio;
} rtl865x_qos_cache_t;

static struct proc_dir_entry *proc_qos=NULL;

static char *gQosSetting = NULL;
#ifdef CONFIG_FAST_PATH_MODULE
EXPORT_SYMBOL(gQosEnabled);
#endif

static int qos_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
      if ( gQosSetting==NULL || count < 2)
	    return -EFAULT;

      if (buffer && !copy_from_user(gQosSetting, buffer, count)) {
          gQosSetting[count-1] = 0; /* remove 0x0a */
          if (gQosSetting[0] == '0')
                gQosEnabled = 0;
          else
                gQosEnabled = 1;

#if defined (CONFIG_RTL_HW_QOS_SUPPORT) && defined(CONFIG_RTL_QOS_PATCH)
	if(gQosEnabled == 1){
		rtl865x_reinitOutputQueuePatchForQoS(TRUE);
	}
	else{
		rtl865x_reinitOutputQueuePatchForQoS(FALSE);
	}
#endif

	    return count;
      }
      return -EFAULT;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int qos_read_proc(struct seq_file *s, void *v)
{
	seq_printf(s, "%d\n", gQosEnabled);

      return 0;
}

static int qos_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, qos_read_proc, NULL));
}

static ssize_t qos_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return qos_write_proc(file, userbuf,count, off);
}

struct file_operations qos_proc_fops = {
        .open           = qos_single_open,
	 .write		= qos_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#else
static int qos_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
      int len;

      len = sprintf(page, "%d\n", gQosEnabled);
	

      if (len <= off+count) *eof = 1;
      *start = page + off;
      len -= off;
      if (len>count) len = count;
      if (len<0) len = 0;
      return len;
}
#endif

#endif

#if defined(CONFIG_NET_SCHED)
#define	RTL_QOS_PROC_MAX_LEN		1024
#if defined(CONFIG_RTL_QOS_SYNC_SUPPORT)
extern void rtl_clear_dev_qos_config(void);
#endif
int32 rtl_qos_init(void)
{
	#if defined(CONFIG_PROC_FS)
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	proc_qos = proc_create_data("qos", 0, &proc_root,
			 &qos_proc_fops, NULL);
	#else
	proc_qos = create_proc_entry("qos", 0, NULL);
	if (proc_qos) {
		proc_qos->read_proc = qos_read_proc;
		proc_qos->write_proc = qos_write_proc;
	}
	#endif
	#endif
	gQosSetting = kmalloc(RTL_QOS_PROC_MAX_LEN, GFP_ATOMIC);
	memset(gQosSetting, 0, RTL_QOS_PROC_MAX_LEN);
	gQosEnabled = 0;
#if defined(CONFIG_RTL_QOS_SYNC_SUPPORT)	
	rtl_clear_dev_qos_config( );
#endif	
	return SUCCESS;
}

int32 rtl_qos_cleanup(void)
{
	kfree(gQosSetting);
	gQosEnabled = 0;
	return SUCCESS;
}
#endif


#if defined(CONFIG_RTL_FAST_BRIDGE)
int32 rtl_fb_add_br_entry(skb)
{
	struct net_bridge_fdb_entry *dst;
	const unsigned char *dest = eth_hdr(skb)->h_dest;
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	u16 vid = 0;
	#endif
	if (!is_multicast_ether_addr(dest))
	{
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		#if defined(CONFIG_BRIDGE_VLAN_FILTERING)
			/*Fix jwj: todo...*/
		#else
		vid = 0;
		#endif
		
		dst = __br_fdb_get(skb->dev->br_port->br, dest, vid);
		#else
		dst = __br_fdb_get(skb->dev->br_port->br, dest);
		#endif
		if(dst != NULL && dst->dst->dev == skb->dev)
		{
			fast_br_cache_entry entry;
			memset(&entry,0,sizeof(fast_br_cache_entry));
			memcpy(&entry.mac_addr,dest,6);
			entry.ageing_timer = jiffies;
			entry.to_dev = skb->dev;
			entry.valid = 1;

			rtl_add_fast_br_entry(&entry);
		}
	}
}
#endif

#if defined(FAST_PATH_SPI_ENABLED)
enum tcp_bit_set {
	TCP_SYN_SET,
	TCP_SYNACK_SET,
	TCP_FIN_SET,
	TCP_ACK_SET,
	TCP_RST_SET,
	TCP_NONE_SET,
};

static unsigned int rtl_spi_get_conntrack_index(const struct tcphdr *tcph)
			{
				if (tcph->rst) return TCP_RST_SET;
				else if (tcph->syn) return (tcph->ack ? TCP_SYNACK_SET : TCP_SYN_SET);
				else if (tcph->fin) return TCP_FIN_SET;
				else if (tcph->ack) return TCP_ACK_SET;
				else return TCP_NONE_SET;
			}

extern bool tcp_in_window(const struct nf_conn *ct,
			  struct ip_ct_tcp *state,
			  enum ip_conntrack_dir dir,
			  unsigned int index,
			  const struct sk_buff *skb,
			  unsigned int dataoff,
			  const struct tcphdr *tcph,
			  u_int8_t pf);

static inline struct nf_conn *
rtl_resolve_normal_ct(struct net *net,
		  struct sk_buff *skb,
		  unsigned int dataoff,
		  u_int16_t l3num,
		  u_int8_t protonum,
		  struct nf_conntrack_l3proto *l3proto,
		  struct nf_conntrack_l4proto *l4proto,
		  int *set_reply,
		  enum ip_conntrack_info *ctinfo)
{
	struct nf_conntrack_tuple tuple;
	struct nf_conntrack_tuple_hash *h;
	struct nf_conn *ct;

	if (!nf_ct_get_tuple(skb, skb_network_offset(skb),
			     dataoff, l3num, protonum, &tuple, l3proto,
			     l4proto)) {
		pr_debug("resolve_normal_ct: Can't get tuple\n");
		return NULL;
	}

	/* look for tuple match */
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	h = nf_conntrack_find_get(net, NF_CT_DEFAULT_ZONE, &tuple);
	#else
	h = nf_conntrack_find_get(net, &tuple);
	#endif

	if (!h) {
		//h = init_conntrack(net, &tuple, l3proto, l4proto, skb, dataoff);
		//if (!h)
		return NULL;
		//if (IS_ERR(h))
		//	return (void *)h;
	}
	ct = nf_ct_tuplehash_to_ctrack(h);

	/* It exists; we have (non-exclusive) reference. */
	if (NF_CT_DIRECTION(h) == IP_CT_DIR_REPLY) {
		*ctinfo = IP_CT_ESTABLISHED + IP_CT_IS_REPLY;
	} else {
		/* Once we've had two way comms, always ESTABLISHED. */
		if (test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) {
			pr_debug("nf_conntrack_in: normal packet for %p\n", ct);
			*ctinfo = IP_CT_ESTABLISHED;
		} else if (test_bit(IPS_EXPECTED_BIT, &ct->status)) {
			pr_debug("nf_conntrack_in: related packet for %p\n",
				 ct);
			*ctinfo = IP_CT_RELATED;
		} else {
			pr_debug("nf_conntrack_in: new packet for %p\n", ct);
			*ctinfo = IP_CT_NEW;
		}
	}
	skb->nfct = &ct->ct_general;
	skb->nfctinfo = *ctinfo;
	return ct;
}


unsigned int
rtl_nf_conntrack_in(struct net *net, unsigned int dataoff, unsigned int hooknum,
		struct sk_buff *skb)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	struct nf_conntrack_l3proto *l3proto;
	struct nf_conntrack_l4proto *l4proto;
	int set_reply = 0;
	enum ip_conntrack_dir dir;
	const struct tcphdr *th;
	struct tcphdr _tcph;
	unsigned int index;


	/* Previously seen (loopback or untracked)?  Ignore. */
	if (skb->nfct) {
		NF_CT_STAT_INC_ATOMIC(net, ignore);
		return NF_ACCEPT;
	}


	/* rcu_read_lock()ed by nf_hook_slow */
	l3proto = rcu_dereference(nf_ct_l3protos[PF_INET]);

	l4proto = rcu_dereference(nf_ct_protos[PF_INET][IPPROTO_TCP]);

	ct = rtl_resolve_normal_ct(net, skb, dataoff, PF_INET, IPPROTO_TCP,
			       l3proto, l4proto, &set_reply, &ctinfo);

	if (!ct) {
		/* Not valid part of a connection */
		return NF_ACCEPT;
	}

	if (IS_ERR(ct)) {
		/* Too stressed to deal. */
		return NF_DROP;
	}

	NF_CT_ASSERT(skb->nfct);


	th = skb_header_pointer(skb, dataoff, sizeof(_tcph), &_tcph);
	BUG_ON(th == NULL);

	dir = CTINFO2DIR(ctinfo);

	index = rtl_spi_get_conntrack_index(th);

	NF_CT_ASSERT(skb->nfct);

	if (!tcp_in_window(ct, &ct->proto.tcp, dir, index,
			   skb, dataoff, th, PF_INET)) {
		return NF_DROP;
	}
	return NF_ACCEPT;

}
#endif

#if defined(CONFIG_RTL_IPTABLES_RULE_2_ACL) || defined(CONFIG_RTL_HARDWARE_NAT)
/*get the chain number of the ipt_entry*/
int get_hookNum(struct ipt_entry *e, unsigned char *base, const unsigned int valid_hooks,const unsigned int *hook_entries)
{
	int h;
	unsigned int offset = 0;
	int hook_num = -1;

	offset = (void *)e - (void *)base;
	for(h = 0; h < NF_INET_NUMHOOKS; h++)
	{
		if(!(valid_hooks & (1 << h)))
			continue;

		if(offset >= hook_entries[h])
			hook_num = h;
	}

	return hook_num;
}
#endif

#if defined(CONFIG_RTL_HARDWARE_NAT) ||(defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C))
int syn_asic_arp(struct neighbour *n, int add)
{
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
	{
		int rc;
		u32 arp_ip = htonl(*((u32 *)n->primary_key));
		
		#if defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C)
		/*ipv4 lookup in arp_tbl*/
		if (n->tbl && (n->tbl->family==AF_INET) && (n->tbl->key_len==4))
		#endif
			rc = add? rtl865x_addArp(arp_ip, (void *)n->ha): rtl865x_delArp(arp_ip);
	}
#endif
#if defined(CONFIG_IPV6)&&defined(CONFIG_RTL_8198C)
	{
		int rc_ipv6;
		inv6_addr_t nd_ip = *((inv6_addr_t *)n->primary_key);
		inv6_addr_t tmp_ip;

		//change ipv6 address to big endian
		htonl_array((u32 *)&nd_ip.v6_addr32[0], (u32 *)&tmp_ip.v6_addr32[0], 4);
		/*ipv6 lookup in nd_tbl*/
		if (n->tbl && (n->tbl->family==AF_INET6) && (n->tbl->key_len==sizeof(inv6_addr_t)))
			rc_ipv6 = add? rtl8198c_addIpv6Arp(tmp_ip, (void *)n->ha): rtl8198c_delIpv6Arp(tmp_ip);
	}
		
#endif
	return 0;
}
#endif

#if	defined(CONFIG_RTL_HARDWARE_NAT)
#if defined(CONFIG_RTL_MULTIPLE_WAN)
int rtl_get_ps_arp_mapping(u32 ip, void *arp_entry_tmp)
{
	rtl865x_arpMapping_entry_t *arp_entry;
	struct neighbour *dst_n;
	struct net_device *wanDev;
	wanDev=rtl865x_getWanDev();

	if(wanDev == NULL)
		return FAILED;

	arp_entry = (rtl865x_arpMapping_entry_t*)arp_entry_tmp;

	dst_n = neigh_lookup(&arp_tbl,&ip,wanDev);
	dev_put(wanDev);
	if(dst_n != NULL)
	{
		arp_entry->ip = ip;
		memcpy(arp_entry->mac.octet,dst_n->ha,ETHER_ADDR_LEN);
		return SUCCESS;
	}

	return FAILED;
}
#endif

rtl_masq_if rtl_masq_info[RTL_MULTIPLE_WAN_NUM];

rtl_masq_if *rtl_get_masq_info_by_devName(const char* name)
{
	int i;
	if(name == NULL)
		return NULL;

	for(i = 0; i < RTL_MULTIPLE_WAN_NUM;i++)
	{
		if(rtl_masq_info[i].valid == 1 &&strcmp(rtl_masq_info[i].ifName,name) == 0)
			return &rtl_masq_info[i];
	}

	return NULL;
}

int rtl_add_masq_info(const char *name, unsigned int ipAddr)
{
	int i;
#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
	int empty = -1;
#endif

	if(strlen(name) >=IFNAMSIZ || ipAddr ==0)
		return FAILED;

#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
	for (i=0; i<RTL_MULTIPLE_WAN_NUM; i++)
	{
		if (rtl_masq_info[i].valid == 1) {
			if (strncmp(rtl_masq_info[i].ifName, name, IFNAMSIZ) == 0) {
				if (rtl_masq_info[i].ipAddr != ipAddr) {
					rtl_masq_info[i].valid = 0;
					/*Delete the old extIp firstly*/
					if (rtl865x_delIp(htonl(rtl_masq_info[i].ipAddr)) == SUCCESS) {
						rtl865x_nat_init();
					}
					empty = i;
					break;
				} else {
					return -2;//RTL_EENTRYALREADYEXIST;
				}
			}
		} else {
			if (empty == -1)
				empty = i;
		}
	}

	if (empty != -1)
		i = empty;
#else
	for (i=0; i<RTL_MULTIPLE_WAN_NUM; i++)
	{
		if (rtl_masq_info[i].valid == 0)
			break;
	}
#endif

	if(i == RTL_MULTIPLE_WAN_NUM)
		return FAILED;

	rtl_masq_info[i].valid = 1;
	rtl_masq_info[i].ipAddr = ipAddr;
	memcpy(rtl_masq_info[i].ifName,name,strlen(name));
	rtl_masq_info[i].ifName[strlen(name)] ='\0';
	return SUCCESS;
}

int rtl_init_masq_info(void)
{
	int i;
	for(i = 0; i < RTL_MULTIPLE_WAN_NUM;i++)
	{
		memset(&rtl_masq_info[i],0,sizeof(rtl_masq_if));
	}

	return SUCCESS;
}

/* Performance critical */
static inline struct ipt_entry *
get_entry(void *base, unsigned int offset)
{
	return (struct ipt_entry *)(base + offset);
}

#ifdef CONFIG_NETFILTER_DEBUG
#define IP_NF_ASSERT(x)						\
do {								\
	if (!(x))						\
		printk("IP_NF_ASSERT: %s:%s:%u\n",		\
		       __func__, __FILE__, __LINE__);	\
} while(0)
#else
#define IP_NF_ASSERT(x)
#endif

static int rtl_get_masquerade_netif(struct xt_table_info *private,struct ipt_entry *masq_entry)
{
	void *table_base;
	struct ipt_entry *e, *back;
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	struct xt_entry_target *t;
	#else
	struct ipt_entry_target *t;
	#endif
	struct net_device *dev;
	char masq_name[IFNAMSIZ]={'\0'};

	if(masq_entry && masq_entry->ip.outiface[0] !='\0')
	{
		memcpy(masq_name, masq_entry->ip.outiface, IFNAMSIZ);
		//return 0;
	}
	else
	{
		table_base = private->entries[smp_processor_id()];
		e = get_entry(table_base, private->hook_entry[NF_INET_POST_ROUTING]);
		back = get_entry(table_base, private->underflow[NF_INET_POST_ROUTING]);

		//clear masq_name;
		memset(masq_name,0,IFNAMSIZ);
		while(e)
		{

			if(e == masq_entry)
				break;

			//record the entry's outif name
			if(e->ip.outiface[0] !='\0')
				memcpy(masq_name,e->ip.outiface,IFNAMSIZ);

			//target
			t = ipt_get_target(e);
			IP_NF_ASSERT(t->u.kernel.target);


			//if error target
			if(strcmp(t->u.kernel.target->name, "ERROR") == 0)
			{
				memset(masq_name,0,IFNAMSIZ);
				break;
			}

			/* Standard target? */
			if (!t->u.kernel.target->target)
			{
				int v;
                #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
				v = ((struct xt_standard_target *)t)->verdict;
				#else
				v = ((struct ipt_standard_target *)t)->verdict;
				#endif

				if (v < 0 )
				{
                    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
					if(v == XT_RETURN)
					#else
					if(v == IPT_RETURN)
					#endif
					{
						e = back;
						back = get_entry(table_base, back->comefrom);
					}
					else
					{
						e = (void *)e + e->next_offset;
					}

					continue;
				}

				//jump ?
				if (table_base + v != (void *)e + e->next_offset
				    && !(e->ip.flags & IPT_F_GOTO)) {
					/* Save old back ptr in next entry */
					struct ipt_entry *next
						= (void *)e + e->next_offset;
					next->comefrom
						= (void *)back - table_base;
					/* set back pointer to next entry */
					back = next;
				}
				e = get_entry(table_base, v);
				continue;
			}

			/*user define target?*/
			e = (void *)e + e->next_offset;
		}

	}

	if(masq_name[0] !='\0')
	{
		struct in_ifaddr *ina;
		dev = __dev_get_by_name(&init_net,masq_name);
		if ((dev)&&(dev->ip_ptr))
		{

			ina=(struct in_ifaddr *)(((struct in_device *)(dev->ip_ptr))->ifa_list);
			if (ina!=NULL)
			{
				rtl_add_masq_info(masq_name,ina->ifa_local);
			}
		}
	}


	return 0;
}

static int rtl_check_for_masquerade_entry(struct ipt_entry *e,
	unsigned char *base,
	const char *name,
	unsigned int size,
	const unsigned int valid_hooks,
	const unsigned int *hook_entries,
	struct xt_table_info *private)
{
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	struct xt_entry_target *t;
	#else
	struct ipt_entry_target *t;
	#endif
	unsigned int hook;
	int ret = 0;

	t = ipt_get_target(e);
	if ( !t)
	{
		goto err;
	}

	hook = get_hookNum(e,base,valid_hooks,hook_entries);
	if ((hook == NF_INET_POST_ROUTING) &&
		((strcmp(t->u.kernel.target->name, "MASQUERADE") == 0)))
		{
			rtl_get_masquerade_netif(private,e);
		}
 err:
	return ret;
}

int rtl_check_for_extern_ip(const char *name,
		unsigned int valid_hooks,
		struct xt_table_info *newinfo,
		void *entry0,
		unsigned int size,
		unsigned int number,
		const unsigned int *hook_entries,
		const unsigned int *underflows)
{
	int i;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	int ret;
	struct ipt_entry *iter;

	xt_entry_foreach(iter, entry0, size) {
		ret = rtl_check_for_masquerade_entry(iter, entry0, name, size, valid_hooks, hook_entries, newinfo);
	}
#else
	IPT_ENTRY_ITERATE(entry0, size,rtl_check_for_masquerade_entry, entry0,name,size,valid_hooks,hook_entries,newinfo);
#endif
	//found masq entry
	for(i = 0; i < RTL_MULTIPLE_WAN_NUM;i++)
	{
		if(rtl_masq_info[i].valid == 1 && rtl_masq_info[i].ipAddr)
		{
			rtl865x_addIp(0,htonl(rtl_masq_info[i].ipAddr),IP_TYPE_NAPT);
		}
	}

	return 0;
}

 int rtl_flush_extern_ip(void)
{
	int i;
	for(i = 0; i < RTL_MULTIPLE_WAN_NUM;i++)
	{
		if(rtl_masq_info[i].valid == 1)
		{
			//delete....
			rtl865x_delIp(htonl(rtl_masq_info[i].ipAddr));
		}
	}

	return SUCCESS;
}

int32 rtl_update_ip_tables(char *name,  unsigned long event, struct in_ifaddr *ina)
{
	rtl_masq_if *entry;

	/*2007-12-19*/
	#ifdef CONFIG_HARDWARE_NAT_DEBUG
		/*2007-12-19*/
		printk("%s:%d\n",__FUNCTION__,__LINE__);
	#endif
	if (ina==NULL)
		return SUCCESS;

	entry = rtl_get_masq_info_by_devName(name);
	if (entry!=NULL)
	{
		if (event == NETDEV_UP )
		{
			rtl865x_addIp(0,htonl(ina->ifa_local),IP_TYPE_NAPT);
			//update the ip address
			entry->ipAddr = ina->ifa_local;
		}
		else if(event == NETDEV_DOWN)
		{
			if(rtl865x_delIp(htonl(ina->ifa_local))==SUCCESS)
			{
				rtl865x_nat_init();
			}
		}
	}

	return SUCCESS;
}

int32 rtl_fn_insert(struct fib_table *tb, struct fib_config *cfg, struct fib_info *fi)
{
	int rc;
	unsigned int ipDst, ipMask, ipGw;
	unsigned int srcIp,srcMask;
	struct net_device *netif;
	char *dev_t;

	/*2007-12-19*/
#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
    if ((tb->tb_id == RT_TABLE_MAIN) && (gHwNatEnabled ==1) && (router_support_hw_nat != 0))
#else
	if ((tb->tb_id == RT_TABLE_MAIN) && (gHwNatEnabled ==1)) 
#endif
    {
		if(cfg->fc_oif) {
			netif = __dev_get_by_index(&init_net,cfg->fc_oif);
		} else {
			netif=NULL;
		}

		dev_t	= (netif)? netif->name: NULL;
		ipDst =  cfg->fc_dst ;
		ipMask = inet_make_mask(cfg->fc_dst_len);
		ipGw = cfg->fc_gw;
		rtl865x_getDevIpAndNetmask(netif,&srcIp,&srcMask);
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		if (!ipDst || (!ipv4_is_multicast(ipDst) && !ipv4_is_loopback(ipDst) && (ipDst != 0xffffffff)))
		#else
		if (!ipDst || (!MULTICAST(ipDst) && !LOOPBACK(ipDst) && (ipDst != 0xffffffff)))
		#endif
		{
			#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
			//printk("-------------------%s(%d)\n",__FUNCTION__,__LINE__);
			rc = rtl865x_addRoute(htonl(ipDst),htonl(ipMask),htonl(ipGw),dev_t,srcIp);
			//printk("-------------------%s(%d),rc(%d)\n",__FUNCTION__,__LINE__,rc);
			#endif
	        	#ifdef CONFIG_HARDWARE_NAT_DEBUG
			/*2007-12-19*/
			printk("%s:%d:(%s): dst:%u.%u.%u.%u/%u, gw:%u.%u.%u.%u, dev: %s, errno=%d\n",
				__FUNCTION__,__LINE__,"add_rt",  NIPQUAD(ipDst), cfg->fc_dst_len, NIPQUAD(ipGw), dev_t? dev_t: "null", rc
		);
		#endif

		}
	}

	return SUCCESS;
}

int32 rtl_fn_delete(struct fib_table *tb, struct fib_config *cfg)
{
	int rc;
	unsigned int ipDst, ipMask;

	/*2007-12-19*/
	if (tb->tb_id == RT_TABLE_MAIN) {
		ipDst = cfg->fc_dst;
		ipMask =  inet_make_mask(cfg->fc_dst_len);

        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		if (!ipDst || (!ipv4_is_multicast(ipDst) && !ipv4_is_loopback(ipDst) && (ipDst != 0xffffffff)))
		#else
		if (!ipDst || (!MULTICAST(ipDst) && !LOOPBACK(ipDst) && (ipDst != 0xffffffff))) 
		#endif	
		{
			rc = 0;
			#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
			rc = rtl865x_delRoute(htonl(ipDst), htonl(ipMask));
			#endif
		}
	}

	return SUCCESS;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
int32 rtl_fib_flush(u32 tb_id, u32 fn_key, u32 ip_mask)
{
	int rc;
	unsigned int ipDst, ipMask;
	/*2007-12-19*/
	if (tb_id==RT_TABLE_MAIN) {
		ipDst =fn_key;
		ipMask = ip_mask;

		if (!ipDst || (!ipv4_is_multicast(ipDst) && !ipv4_is_loopback(ipDst) && (ipDst != 0xffffffff))) {
			rc = 0;
			#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
			rc = rtl865x_delRoute(htonl(ipDst), htonl(ipMask));
			#endif
		}
	}

	return SUCCESS;
}
#endif

int32 rtl_fn_flush(int	 fz_order, int idx, u32 tb_id, u32 fn_key)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
	int rc;
	unsigned int ipDst, ipMask;
	/*2007-12-19*/
	if (tb_id==RT_TABLE_MAIN) {
		ipDst =fn_key;
		ipMask = inet_make_mask(fz_order);

		if (!ipDst || (!MULTICAST(ipDst) && !LOOPBACK(ipDst) && (ipDst != 0xffffffff))) {
			rc = 0;
			#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
			rc = rtl865x_delRoute(htonl(ipDst), htonl(ipMask));
			#endif
		}
	}
#endif
	return SUCCESS;
}

#if !defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
int32 rtl_ip_vs_conn_expire_check(struct ip_vs_conn *cp)
{
	int elapsed;
	u_int32_t expires;
	rtl865x_napt_entry rtl865xNaptEntry;

	if (cp->protocol==IPPROTO_UDP)	{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		expires = udp_get_timeouts_by_state(UDP_CT_UNREPLIED,(void *)cp,0);
#else
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
		expires = udp_get_timeouts_by_state(UDP_CT_UNREPLIED);
		#else
		expires = nf_ct_udp_timeout;
		#endif
#endif
	} else if (cp->protocol==IPPROTO_TCP) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		expires = tcp_get_timeouts_by_state(cp->state,(void *)cp,0);	/* does cp->state right here? */
#else
		expires = tcp_get_timeouts_by_state(cp->state);	/* does cp->state right here? */
#endif
	} else {
		return FAILED;
	}

/*   chhuang:
	printk("ip_vs_conn_expire: c:(%u.%u.%u.%u:%d), v:(%u.%u.%u.%u:%d), \n\td:(%u.%u.%u.%u:%d), p:(%x), f: %x, s: %x\n",
			NIPQUAD(cp->caddr), cp->cport, NIPQUAD(cp->vaddr), cp->vport, NIPQUAD(cp->daddr), cp->dport,
			cp->protocol, cp->flags, cp->state);
*/
	if (cp->hw_acc) {
		rtl865xNaptEntry.protocol=((cp->protocol==IPPROTO_TCP)? 1: 0);
		rtl865xNaptEntry.intIp=cp->daddr.ip;
		rtl865xNaptEntry.intPort=cp->dport;
		rtl865xNaptEntry.extIp=cp->vaddr.ip;
		rtl865xNaptEntry.extPort=cp->vport;
		rtl865xNaptEntry.remIp=cp->caddr.ip;
		rtl865xNaptEntry.remPort=cp->cport;

		elapsed = rtl865x_naptSync(&rtl865xNaptEntry, 0);

		if (elapsed >= 0 && (cp->protocol==IPPROTO_UDP))
		{
			cp->timer.expires = jiffies + (expires-elapsed)*HZ;
			add_timer(&cp->timer);
			#ifdef CONFIG_HARDWARE_NAT_DEBUG
			/*2007-12-19*/
			printk("%s:%d:(%s): expired time = %d\n %s (%u.%u.%u.%u:%u -> %u.%u.%u.%u:%u) g:(%u.%u.%u.%u:%u)\n",
					__FUNCTION__,__LINE__,"poll_nat", timeval, (cp->protocol==IPPROTO_TCP)? "tcp": "udp",
					NIPQUAD(cp->daddr), cp->dport, NIPQUAD(cp->caddr), cp->cport,
					NIPQUAD(cp->vaddr), cp->vport
			);
			#endif

			return FAILED;
		}
	}

	return SUCCESS;
}


int32 rtl_ip_vs_conn_expire_check_delete(struct ip_vs_conn *cp)
{
	rtl865x_napt_entry rtl865xNaptEntry;

	if (cp->hw_acc) {
		int rc;

		rtl865xNaptEntry.protocol=((cp->protocol==IPPROTO_TCP)? 1: 0);
		rtl865xNaptEntry.intIp=cp->daddr.ip;
		rtl865xNaptEntry.intPort=cp->dport;
		rtl865xNaptEntry.extIp=cp->vaddr.ip;
		rtl865xNaptEntry.extPort=cp->vport;
		rtl865xNaptEntry.remIp=cp->caddr.ip;
		rtl865xNaptEntry.remPort=cp->cport;

		rc = rtl865x_delNaptConnection(&rtl865xNaptEntry);

		#ifdef CONFIG_HARDWARE_NAT_DEBUG
		/*2007-12-19*/
		printk("%s:%d:(%s): errno=%d\n %s (%u.%u.%u.%u:%u -> %u.%u.%u.%u:%u) g:(%u.%u.%u.%u:%u)\n",
			__FUNCTION__,__LINE__,"del_nat", rc, (cp->protocol==IPPROTO_TCP)? "tcp": "udp",
			NIPQUAD(cp->daddr.ip), cp->dport, NIPQUAD(cp->caddr.ip), cp->cport,
			NIPQUAD(cp->vaddr.ip), cp->vport
		);
		#endif
	}

	return SUCCESS;
}
#if	defined(CONFIG_RTL_HW_QOS_SUPPORT)
extern int32 rtl_qosGetSkbMarkByNaptEntry(rtl865x_napt_entry *naptEntry, rtl865x_qos_mark *qosMark, struct sk_buff *pskb);
#endif

void rtl_tcp_state_transition_check(struct ip_vs_conn *cp, int direction, const struct sk_buff *skb, struct ip_vs_protocol *pp)
{
	#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
	uint32			ret;
	struct net_device	*lanDev, *wanDev;
	#endif

	#if defined(CONFIG_RTL_LAYERED_DRIVER_L4)
	rtl865x_napt_entry rtl865xNaptEntry;
	rtl865x_priority rtl865xPrio;
	rtl865x_qos_mark rtl865xQosMark;
	#endif

	/*2007-12-19*/
	/*
	printk("ip_vs_set_state: c:(%u.%u.%u.%u:%d), v:(%u.%u.%u.%u:%d), \n\td:(%u.%u.%u.%u:%d), p:(%x), f: %x, s: %x, master: %s\n\tapp_data: %x, app: %x\n",
		NIPQUAD(cp->caddr), cp->cport, NIPQUAD(cp->vaddr), cp->vport, NIPQUAD(cp->daddr), cp->dport, cp->protocol, cp->flags, cp->state,
		cp->control? "yes": "no", cp->app_data, cp->app);
	*/
	#if 0
	if (!cp->hw_acc && !cp->app &&
		cp->state==IP_VS_S_ESTABLISHED)
	#else
	if (!cp->hw_acc && !cp->app &&
		cp->state==IP_VS_TCP_S_ESTABLISHED)
	#endif
	{
		int rc;
		rc = 0;

		#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
		if (NULL!=skb)
		{
			rtl865xNaptEntry.protocol=RTL865X_PROTOCOL_TCP;
			rtl865xNaptEntry.intIp=cp->daddr.ip;
			rtl865xNaptEntry.intPort=cp->dport;
			rtl865xNaptEntry.extIp=cp->vaddr.ip;
			rtl865xNaptEntry.extPort=cp->vport;
			rtl865xNaptEntry.remIp=cp->caddr.ip;
			rtl865xNaptEntry.remPort=cp->cport;

			rtl865xQosMark.downlinkMark=0;	//Initial
			rtl865xQosMark.uplinkMark=0;	//Initial
			ret=rtl_qosGetSkbMarkByNaptEntryHook(&rtl865xNaptEntry, &rtl865xQosMark, skb);

			lanDev=rtl865x_getLanDev();
			wanDev=rtl865x_getWanDev();
			if(lanDev){
				rtl865xPrio.downlinkPrio=rtl_qosGetPriorityByMark(lanDev->name, rtl865xQosMark.downlinkMark);
			}
			if(wanDev){
				rtl865xPrio.uplinkPrio=rtl_qosGetPriorityByMark(wanDev->name, rtl865xQosMark.uplinkMark);
			}
			if(lanDev)
				dev_put(lanDev);

			if(wanDev)
				dev_put(wanDev);
		}else
		#endif
		{
			rtl865xPrio.downlinkPrio=0;
			rtl865xPrio.uplinkPrio=0;
		}

		#if defined(CONFIG_RTL_LAYERED_DRIVER_L4)
		rtl865xNaptEntry.protocol=RTL865X_PROTOCOL_TCP;
		rtl865xNaptEntry.intIp=cp->daddr.ip;
		rtl865xNaptEntry.intPort=cp->dport;
		rtl865xNaptEntry.extIp=cp->vaddr.ip;
		rtl865xNaptEntry.extPort=cp->vport;
		rtl865xNaptEntry.remIp=cp->caddr.ip;
		rtl865xNaptEntry.remPort=cp->cport;
		rc = rtl865x_addNaptConnection(&rtl865xNaptEntry, &rtl865xPrio);
		#endif
		if (!rc)
			cp->hw_acc = 1;
		#ifdef CONFIG_HARDWARE_NAT_DEBUG
		/*2007-12-19*/
		printk("%s:%d:(%s): errno=%d\n %s (%u.%u.%u.%u:%u -> %u.%u.%u.%u:%u) g:(%u.%u.%u.%u:%u)\n",
				__FUNCTION__,__LINE__,"add_nat", rc, "tcp", NIPQUAD(cp->daddr), cp->dport,
				NIPQUAD(cp->caddr), cp->cport, NIPQUAD(cp->vaddr), cp->vport
		);
		#endif
	}
}

void rtl_udp_state_transition_check(struct ip_vs_conn *cp, int direction, const struct sk_buff *skb, struct ip_vs_protocol *pp)
{
	#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
	uint32 ret;
	struct net_device	*lanDev, *wanDev;
	#endif
	#if defined(CONFIG_RTL_LAYERED_DRIVER_L4)
	rtl865x_napt_entry rtl865xNaptEntry;
	rtl865x_priority rtl865xPrio;
	rtl865x_qos_mark rtl865xQosMark;
	#endif

	/*2007-12-19*/
	if (!cp->hw_acc && !cp->app)
	{
		int rc;
		rc = 0;
		#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
		if (NULL!=skb)
		{
			rtl865xNaptEntry.protocol=RTL865X_PROTOCOL_UDP;
			rtl865xNaptEntry.intIp=cp->daddr.ip;
			rtl865xNaptEntry.intPort=cp->dport;
			rtl865xNaptEntry.extIp=cp->vaddr.ip;
			rtl865xNaptEntry.extPort=cp->vport;
			rtl865xNaptEntry.remIp=cp->caddr.ip;
			rtl865xNaptEntry.remPort=cp->cport;

			rtl865xQosMark.downlinkMark=0;	//Initial
			rtl865xQosMark.uplinkMark=0;	//Initial
			ret=rtl_qosGetSkbMarkByNaptEntryHook(&rtl865xNaptEntry, &rtl865xQosMark, skb);

			lanDev=rtl865x_getLanDev();
			wanDev=rtl865x_getWanDev();
			if(lanDev){
				rtl865xPrio.downlinkPrio=rtl_qosGetPriorityByMark(lanDev->name, rtl865xQosMark.downlinkMark);
			}
			if(wanDev){
				rtl865xPrio.uplinkPrio=rtl_qosGetPriorityByMark(wanDev->name, rtl865xQosMark.uplinkMark);
			}

			if(lanDev)
				dev_put(lanDev);

			if(wanDev)
				dev_put(wanDev);
		} else
		#endif
		{
			rtl865xPrio.downlinkPrio=0;
			rtl865xPrio.uplinkPrio=0;
		}

		#if defined(CONFIG_RTL_LAYERED_DRIVER_L4)
		rtl865xNaptEntry.protocol=RTL865X_PROTOCOL_UDP;
		rtl865xNaptEntry.intIp=cp->daddr.ip;
		rtl865xNaptEntry.intPort=cp->dport;
		rtl865xNaptEntry.extIp=cp->vaddr.ip;
		rtl865xNaptEntry.extPort=cp->vport;
		rtl865xNaptEntry.remIp=cp->caddr.ip;
		rtl865xNaptEntry.remPort=cp->cport;

		rc = rtl865x_addNaptConnection(&rtl865xNaptEntry, &rtl865xPrio);
		#endif
		if (!rc)
			cp->hw_acc = 1;
		#ifdef CONFIG_HARDWARE_NAT_DEBUG
		/*2007-12-19*/
		printk("%s:%d:(%s): errno=%d\n %s (%u.%u.%u.%u:%u -> %u.%u.%u.%u:%u) g:(%u.%u.%u.%u:%u)\n",
				__FUNCTION__,__LINE__,"add_nat", rc, "udp", NIPQUAD(cp->daddr), cp->dport,
				NIPQUAD(cp->caddr), cp->cport, NIPQUAD(cp->vaddr), cp->vport
		);
		#endif
	}
}
#endif
#endif

#if defined(CONFIG_IPV6) && defined(CONFIG_RTL_8198C)
int32 rtl8198c_ipv6_router_add(struct rt6_info *rt)
{
	char *dev_t;
	int rc, fc_dst_len, addr_type;
	inv6_addr_t ipDst, ipGw, tmp_dst, tmp_gw;
	struct net_device *netif;
	uint32 tb6_id = 0;
	
	if (rt && rt->rt6i_table) {
		//read_lock_bh(&rt->rt6i_table->tb6_lock);
		tb6_id = rt->rt6i_table->tb6_id;
		//read_unlock_bh(&rt->rt6i_table->tb6_lock);
	};

	if (tb6_id == RT6_TABLE_MAIN) {
		if (rt->dst.dev) {
			netif = rt->dst.dev;
		} else {
			netif = NULL;
		}

		dev_t	= (netif)? netif->name: NULL;
		memcpy(&ipDst, &rt->rt6i_dst.addr, sizeof(inv6_addr_t));
		fc_dst_len = rt->rt6i_dst.plen;
		memcpy(&ipGw, &rt->rt6i_gateway, sizeof(inv6_addr_t));

		//change ipv6 address to CPU endian, 98C big endian, 97F little endian
		htonl_array((u32 *)&ipDst.v6_addr32[0], (u32 *)&tmp_dst.v6_addr32[0], 4);
		htonl_array((u32 *)&ipGw.v6_addr32[0], (u32 *)&tmp_gw.v6_addr32[0], 4);

		addr_type = ipv6_addr_type(&ipDst);
		if ((((ipDst.v6_addr32[0]==0)&&(ipDst.v6_addr32[1]==0)&&(ipDst.v6_addr32[2]==0)&&(ipDst.v6_addr32[3]==0)) ||
		     ((!(addr_type&IPV6_ADDR_MULTICAST))&&(!(addr_type&IPV6_ADDR_LOOPBACK))))&&(fc_dst_len != 128)) {
			rc = rtl8198c_addIpv6Route(tmp_dst, fc_dst_len, tmp_gw, dev_t);
			#if 0
			printk("%s:%d:(%s): dst: 0x%8x%8x%8x%8x, fc_dst_len is %d, gw:  0x%8x%8x%8x%8x, dev: %s, errno=%d\n",
					__FUNCTION__, __LINE__,"add_ipv6_rt",  
					ipDst.v6_addr32[0], ipDst.v6_addr32[1] ,ipDst.v6_addr32[2], ipDst.v6_addr32[3],fc_dst_len, 
					ipGw.v6_addr32[0], ipGw.v6_addr32[1] ,ipGw.v6_addr32[2], ipGw.v6_addr32[3], 
					 dev_t? dev_t: "null", rc);
			#endif
		}
	}
	
	return SUCCESS;
}

int32 rtl8198c_ipv6_router_del(struct rt6_info *rt)
{
	int rc, fc_dst_len, addr_type;
	inv6_addr_t ipDst, tmp_ip;
	uint32 tb6_id = 0;	
	
	if (rt && rt->rt6i_table) {
		//read_lock_bh(&rt->rt6i_table->tb6_lock);
		tb6_id = rt->rt6i_table->tb6_id;
		//read_unlock_bh(&rt->rt6i_table->tb6_lock);
	};

	if (tb6_id == RT6_TABLE_MAIN) {
		memcpy(&ipDst, &rt->rt6i_dst.addr, sizeof(inv6_addr_t));
		fc_dst_len = rt->rt6i_dst.plen;
		
		//change ipv6 address to big endian
		htonl_array((u32 *)&ipDst.v6_addr32[0], (u32 *)&tmp_ip.v6_addr32[0], 4);

		addr_type = ipv6_addr_type(&ipDst);
		if (((ipDst.v6_addr32[0]==0)&&(ipDst.v6_addr32[1]==0)&&(ipDst.v6_addr32[2]==0)&&(ipDst.v6_addr32[3]==0)) ||
		     ((!(addr_type&IPV6_ADDR_MULTICAST))&&(!(addr_type&IPV6_ADDR_LOOPBACK)))) {
			rc = rtl8198c_delIpv6Route(tmp_ip, fc_dst_len);
		}
	}
	
	return SUCCESS;
}
#endif

#if defined(CONFIG_PROC_FS) && defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
static struct proc_dir_entry *proc_gc_overflow_timout=NULL;

static int gc_overflow_timout_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	uint32 tmpBuf[32];

      if (count < 2)
	    return -EFAULT;

      if (buffer && !copy_from_user(tmpBuf, buffer, count)) {
	    tmpBuf[count-1]=0;
	    rtl_gc_overflow_timout=simple_strtol((const char *)tmpBuf, NULL, 0);

	    return count;
      }
      return -EFAULT;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int gc_overflow_timout_read_proc(struct seq_file *s, void *v)
{
      seq_printf(s, "rtl_gc_overflow_timout(%d), HZ(%d)\n", rtl_gc_overflow_timout, HZ);

      return 0;
}

int gc_overflow_timout_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, gc_overflow_timout_read_proc, NULL));
}

static ssize_t gc_overflow_timout_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return gc_overflow_timout_write_proc(file, userbuf,count, off);
}

struct file_operations gc_overflow_timout_proc_fops = {
        .open           = gc_overflow_timout_single_open,
	 .write		= gc_overflow_timout_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#else
static int gc_overflow_timout_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
      int len;

      len = sprintf(page, "rtl_gc_overflow_timout(%d), HZ(%d)\n", rtl_gc_overflow_timout, HZ);

      if (len <= off+count) *eof = 1;
      *start = page + off;
      len -= off;
      if (len>count) len = count;
      if (len<0) len = 0;
      return len;
}
#endif

void gc_overflow_timout_proc_init(void)
{
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	proc_gc_overflow_timout = proc_create_data("gc_overflow_timout", 0, &proc_root,
			 &gc_overflow_timout_proc_fops, NULL);
	#else
	proc_gc_overflow_timout = create_proc_entry("gc_overflow_timout", 0, NULL);
	if (proc_gc_overflow_timout) {
		proc_gc_overflow_timout->read_proc = gc_overflow_timout_read_proc;
		proc_gc_overflow_timout->write_proc = gc_overflow_timout_write_proc;
	}
	#endif
}
#endif

#if defined(CONFIG_RTL_LOG_DEBUG)
struct RTL_LOG_PRINT_MASK
/*{
	uint32 ERROR:1;
	uint32 WARN:1;
	uint32 INFO:1;
}*/ RTL_LogTypeMask;
struct RTL_LOG_ERROR_MASK
/*{
	uint32 MEM:1;
	uint32 SKB:1;
}*/RTL_LogErrorMask;
struct RTL_LOG_MODULE_MASK
/*{
	uint8 NIC:1;
	uint8 WIRELESS:1;
	uint8 PROSTACK:1;
}*/RTL_LogModuleMask;
uint32 RTL_LogRatelimit=1;

static struct proc_dir_entry *proc_log_print_control=NULL;
static struct proc_dir_entry *proc_printMask=NULL;
static struct proc_dir_entry *proc_errMask=NULL;
static struct proc_dir_entry *proc_printModule=NULL;
static struct proc_dir_entry *proc_print_rateLimit=NULL;
const char *print_Mask_ID="typeMask";
const char *print_errMask_ID="errMask";
const char *print_rateLimit_ID="rateLimit_enable";
const char *print_module_ID="module_mask";

static int print_log_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	unsigned char tmpBuf[32];
	int tmp;
	if (count < 2)
		return -EFAULT;

	if (!buffer || copy_from_user(tmpBuf, buffer, count)) {
		return -EFAULT;
	}

	if(0==strcmp(data, print_Mask_ID))
	{
		sscanf(tmpBuf, "%x", &tmp);
		*(uint32 *)&RTL_LogTypeMask=tmp;
	}
	else if(0==strcmp(data, print_errMask_ID))
	{
		sscanf(tmpBuf, "%x", &tmp);
		*(uint32 *)&RTL_LogErrorMask=tmp;
	}
	else if(0==strcmp(data, print_rateLimit_ID))
	{
		tmpBuf[count-1]=0;
		RTL_LogRatelimit=simple_strtol((const char *)tmpBuf, NULL, 0);
	}
	else if(0==strcmp(data, print_module_ID))
	{
		sscanf(tmpBuf, "%x", &tmp);
		*(uint32 *)&RTL_LogModuleMask=tmp;
	}

	return count;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int print_log_read_proc(struct seq_file *s, void *v)
{
	char * data = (char *)s->private;
	
	if(0==strcmp(data, print_Mask_ID))
	{
		seq_printf(s, "RTL_LogTypeMask(0x%x)\n\tbit means:\n\t ERROR %d\n\t WARN %d \n\t INFO %d \n", \
						*(uint32 *)&RTL_LogTypeMask, RTL_LogTypeMask.ERROR, RTL_LogTypeMask.WARN, RTL_LogTypeMask.INFO);
	}
	else if(0==strcmp(data, print_errMask_ID))
	{
		seq_printf(s, "RTL_LogErrorMask(0x%x)\n\tbit means:\n\t MEM %d\n\t SKB %d \n", \
						*(uint32 *)&RTL_LogErrorMask, RTL_LogErrorMask.MEM, RTL_LogErrorMask.SKB);
	}
	else if(0==strcmp(data, print_rateLimit_ID))
	{
		seq_printf(s, "rate_limit %d \n", RTL_LogRatelimit);
	}
	else if(0==strcmp(data, print_module_ID))
	{
		seq_printf(s, "RTL_LogModuleMask(0x%x)\n\tbit means:\n\t NIC %d\n\t WIRELESS %d \n\t PROSTACK %d \n", \
			  *(uint32 *)&RTL_LogModuleMask, RTL_LogModuleMask.NIC, RTL_LogModuleMask.WIRELESS, RTL_LogModuleMask.PROSTACK);
	}

	return 0;
}

int print_log_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, print_log_read_proc, PDE_DATA(inode)));
}

static ssize_t print_log_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return print_log_write_proc(file, userbuf,count, off);
}

struct file_operations print_log_proc_fops = {
        .open           = print_log_single_open,
	 .write		= print_log_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#else
static int print_log_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
	int len;

	if(0==strcmp(data, print_Mask_ID))
	{
		len = sprintf(page, "RTL_LogTypeMask(0x%x)\n\tbit means:\n\t ERROR %d\n\t WARN %d \n\t INFO %d \n", \
						*(uint32 *)&RTL_LogTypeMask, RTL_LogTypeMask.ERROR, RTL_LogTypeMask.WARN, RTL_LogTypeMask.INFO);
	}
	else if(0==strcmp(data, print_errMask_ID))
	{
		len = sprintf(page, "RTL_LogErrorMask(0x%x)\n\tbit means:\n\t MEM %d\n\t SKB %d \n", \
						*(uint32 *)&RTL_LogErrorMask, RTL_LogErrorMask.MEM, RTL_LogErrorMask.SKB);
	}
	else if(0==strcmp(data, print_rateLimit_ID))
	{
		len = sprintf(page, "rate_limit %d \n", RTL_LogRatelimit);
	}
	else if(0==strcmp(data, print_module_ID))
	{
		len = sprintf(page, "RTL_LogModuleMask(0x%x)\n\tbit means:\n\t NIC %d\n\t WIRELESS %d \n\t PROSTACK %d \n", \
			  *(uint32 *)&RTL_LogModuleMask, RTL_LogModuleMask.NIC, RTL_LogModuleMask.WIRELESS, RTL_LogModuleMask.PROSTACK);
	}

	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
}
#endif

void log_print_proc_init(void)
{
	RTL_LogTypeMask.ERROR=1;
		RTL_LogErrorMask.MEM=1;
		RTL_LogErrorMask.SKB=1;

	RTL_LogTypeMask.WARN=1;
	RTL_LogTypeMask.INFO=0;

	RTL_LogModuleMask.NIC=1;
	RTL_LogModuleMask.WIRELESS=1;
	RTL_LogModuleMask.PROSTACK=1;

	RTL_LogRatelimit=1;

	proc_log_print_control= proc_mkdir("log_print_control",NULL);
	if(proc_log_print_control)
	{
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		proc_printMask = proc_create_data(print_Mask_ID, 0, proc_log_print_control,
			 &print_log_proc_fops, print_Mask_ID);

		proc_printMask = proc_create_data(print_errMask_ID, 0, proc_log_print_control,
			 &print_log_proc_fops, print_errMask_ID);

		proc_printMask = proc_create_data(print_rateLimit_ID, 0, proc_log_print_control,
			 &print_log_proc_fops, print_rateLimit_ID);

		proc_printMask = proc_create_data(print_module_ID, 0, proc_log_print_control,
			 &print_log_proc_fops, print_module_ID);
		#else
		proc_printMask = create_proc_entry(print_Mask_ID, 0, proc_log_print_control);
		if (proc_printMask) {
			proc_printMask->read_proc = print_log_read_proc;
			proc_printMask->write_proc = print_log_write_proc;
			proc_printMask->data = (void *)print_Mask_ID;
		}

		proc_errMask = create_proc_entry(print_errMask_ID, 0, proc_log_print_control);
		if (proc_errMask) {
			proc_errMask->read_proc = print_log_read_proc;
			proc_errMask->write_proc = print_log_write_proc;
			proc_errMask->data = (void *)print_errMask_ID;
		}

		proc_print_rateLimit = create_proc_entry(print_rateLimit_ID, 0, proc_log_print_control);
		if (proc_print_rateLimit) {
			proc_print_rateLimit->read_proc = print_log_read_proc;
			proc_print_rateLimit->write_proc = print_log_write_proc;
			proc_print_rateLimit->data = (void *)print_rateLimit_ID;
		}

		proc_printModule = create_proc_entry(print_module_ID, 0, proc_log_print_control);
		if (proc_printModule) {
			proc_printModule->read_proc = print_log_read_proc;
			proc_printModule->write_proc = print_log_write_proc;
			proc_printModule->data = (void *)print_module_ID;
		}
		#endif
	}
}
#endif

#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW) //CONFIG_RTL_GC_INDEPENDENCE_ON_KERNEL
int rtl_gc_threshold_check(struct net* net)
{
	int ret = FAILED;

	if(net == NULL){
		if(atomic_read(&(init_net.ct.count)) > rtl_nf_conntrack_threshold)
			ret = SUCCESS;
	}else{
		if(atomic_read(&net->ct.count) > rtl_nf_conntrack_threshold)
			ret = SUCCESS;
	}

	return ret;
}

void rtl_list_del(struct nf_conn* ct)
{
	return	list_del(&ct->state_tuple);
}

void rtl_hlist_nulls_del_rcu(struct nf_conn* ct, enum ip_conntrack_dir dir)
{
	return	hlist_nulls_del_rcu(&ct->tuplehash[dir].hnnode);
}

void rtl_list_add_tail(struct nf_conn* ct, int proto, int flag)
{
	if(proto == PROT_UDP)
		return list_add_tail(&ct->state_tuple,Udp_State_Hash_Head[flag].state_hash);
	else if(proto == PROT_TCP)
		return list_add_tail(&ct->state_tuple,Tcp_State_Hash_Head[ct->proto.tcp.state].state_hash);
}


int rtl_test_bit(struct nf_conn* ct, int num)
{
	if(test_bit(num, &ct->status))
		return SUCCESS;
	else
		return FAILED;
}

int rtl_del_ct_timer(struct nf_conn *ct)
{
	return del_timer(&ct->timeout);
}

void rtl_add_ct_timer(struct nf_conn *ct)
{
	return add_timer(&ct->timeout);
}

void rtl_list_move_tail(struct nf_conn *ct, int proto, int state)
{
	if(proto == PROT_UDP)
		return list_move_tail(&ct->state_tuple, Udp_State_Hash_Head[state].state_hash);
	else if(proto == PROT_TCP)
		return list_move_tail(&ct->state_tuple, Tcp_State_Hash_Head[(enum tcp_conntrack)state].state_hash);
}

unsigned long rtl_get_ct_timer_expires(struct nf_conn* ct)
{
	return ct->timeout.expires;
}

void rtl_nf_ct_stat_inc(struct net* net)
{
	NF_CT_STAT_INC(net, delete_list);

	return;
}

int rtl_skb_network_offset(struct sk_buff *skb)
{
	return skb_network_offset(skb);
}

u_int8_t rtl_new_gc_get_ct_protonum(void *ct_ptr, enum ip_conntrack_dir dir)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	return ct->tuplehash[dir].tuple.dst.protonum;
}

struct iphdr *rtl_new_gc_ip_hdr(struct sk_buff *skb)
{
	return ip_hdr(skb);
}

__be16 rtl_new_gc_get_skb_protocol(struct sk_buff *skb)
{
	struct iphdr *iph;
	iph = ip_hdr(skb);
	
	return iph->protocol;
	//return skb->protocol;
}

unsigned long rtl_new_gc_get_ct_udp_status(void *ct_ptr)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	return ct->status;
}

u_int8_t rtl_new_gc_get_ct_tcp_state(void *ct_ptr)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	return ct->proto.tcp.state;
}

void rtl_new_gc_set_ct_timeout_expires(void *ct_ptr, unsigned long value)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	ct->timeout.expires = value;

	return;
}

/*flag = 0 for src; flag = 1 for dst*/
__be32 rtl_new_gc_get_ct_ip_by_dir(void *ct_ptr, enum ip_conntrack_dir dir, int flag)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	if(dir == IP_CT_DIR_ORIGINAL)
	{
		if(flag == 0)
			return ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
		else if(flag == 1)
			return ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip;
	}
	else if(dir == IP_CT_DIR_REPLY)
	{
		if(flag == 0)
			return ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
		else if(flag == 1)
			return ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip;
	}
}

/*flag = 0 for src; flag = 1 for dst*/
__be16 rtl_new_gc_get_ct_port_by_dir(void *ct_ptr, enum ip_conntrack_dir dir, int flag)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	if(dir == IP_CT_DIR_ORIGINAL)
	{
		if(flag == 0)
			return ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;
		else if(flag == 1)
			return ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all;

	}
	else if(dir == IP_CT_DIR_REPLY)
	{
		if(flag == 0)
			return ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all;
		else if(flag == 1)
			return ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u.all;
	}
}
#endif

#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
#include "../../ipv4/fib_lookup.h"
#include <linux/inetdevice.h>
#include <linux/ppp_channel.h>
#include <linux/if_pppox.h>
#include <net/arp.h>

extern int rtl_del_ps_drv_netif_mapping_by_name(const char *name);
extern int32 rtl_fn_hash_insert_hooks(struct fib_table *tb, struct fib_config *cfg, struct fib_info *fi);
extern int rtl_clear_router_exist_in_ps_flag(void);
extern int rtl_del_router_not_exist_in_ps(void);
extern int rtl_clear_arp_exist_in_ps_flag(void);
extern int rtl_del_arp_not_exist_in_ps(void);
extern int32 rtl_nat_init_hooks(void);
extern int32 rtl_ip_tables_init_hooks(void);
extern int rtl_enable_netif_routing(void);
extern int32 rtl8651_getAsicOperationLayer(void) ;
/*===========================Sync fib trie API Start==========================*/
/*Keep the following items the same with fib_trie.c*/
#define MAX_STAT_DEPTH 32
#define KEYLENGTH (8*sizeof(t_key))
typedef unsigned int t_key;
#define T_TNODE 0
#define T_LEAF  1
#define NODE_TYPE_MASK	0x1UL
#define NODE_TYPE(node) ((node)->parent & NODE_TYPE_MASK)
#define IS_LEAF(n) (n->parent & T_LEAF)

struct rt_trie_node {
	unsigned long parent;
	t_key key;
};

struct leaf {
	unsigned long parent;
	t_key key;
	struct hlist_head list;
	struct rcu_head rcu;
};

struct leaf_info {
	struct hlist_node hlist;
	int plen;
	u32 mask_plen; /* ntohl(inet_make_mask(plen)) */
	struct list_head falh;
	struct rcu_head rcu;
};

struct tnode {
	unsigned long parent;
	t_key key;
	unsigned char pos;		/* 2log(KEYLENGTH) bits needed */
	unsigned char bits;		/* 2log(KEYLENGTH) bits needed */
	unsigned int full_children;	/* KEYLENGTH bits needed */
	unsigned int empty_children;	/* KEYLENGTH bits needed */
	union {
		struct rcu_head rcu;
		struct tnode *tnode_free;
	};
	struct rt_trie_node __rcu *child[0];
};

#ifdef CONFIG_IP_FIB_TRIE_STATS
struct trie_use_stats {
	unsigned int gets;
	unsigned int backtrack;
	unsigned int semantic_match_passed;
	unsigned int semantic_match_miss;
	unsigned int null_node_hit;
	unsigned int resize_node_skipped;
};
#endif

struct trie_stat {
	unsigned int totdepth;
	unsigned int maxdepth;
	unsigned int tnodes;
	unsigned int leaves;
	unsigned int nullpointers;
	unsigned int prefixes;
	unsigned int nodesizes[MAX_STAT_DEPTH];
};

struct trie {
	struct rt_trie_node __rcu *trie;
#ifdef CONFIG_IP_FIB_TRIE_STATS
	struct trie_use_stats stats;
#endif
};

#define RTL_GET_EXTIP_ROUTER_EXPIRE (10*HZ)
static char    wan_dev_name_bak[IFNAMSIZ];	/*now only consider single wan*/
static struct timer_list hw_extIp_router_timer;
int router_support_hw_nat = 1;

static inline t_key rtl_tkey_extract_bits(t_key a, unsigned int offset, unsigned int bits)
{
	if (offset < KEYLENGTH)
		return ((t_key)(a << offset)) >> (KEYLENGTH - bits);
	else
		return 0;
}

/*
 * caller must hold RCU read lock or RTNL
 */
static inline struct tnode *rtl_node_parent_rcu(const struct rt_trie_node *node)
{
	unsigned long parent;

	parent = rcu_dereference_index_check(node->parent, rcu_read_lock_held() ||
							   lockdep_rtnl_is_held());

	return (struct tnode *)(parent & ~NODE_TYPE_MASK);
}

/*
 * caller must hold RCU read lock or RTNL
 */
static inline struct rt_trie_node *rtl_tnode_get_child_rcu(const struct tnode *tn, unsigned int i)
{
	BUG_ON(i >= 1U << tn->bits);

	return rcu_dereference_rtnl(tn->child[i]);
}

/*
 * Scan for the next right leaf starting at node p->child[idx]
 * Since we have back pointer, no recursion necessary.
 */
static struct leaf *rtl_leaf_walk_rcu(struct tnode *p, struct rt_trie_node *c)
{
	do {
		t_key idx;

		if (c)
			idx = rtl_tkey_extract_bits(c->key, p->pos, p->bits) + 1;
		else
			idx = 0;

		while (idx < 1u << p->bits) {
			c = rtl_tnode_get_child_rcu(p, idx++);
			if (!c)
				continue;

			if (IS_LEAF(c))
				return (struct leaf *) c;

			/* Rescan start scanning in new node */
			p = (struct tnode *) c;
			idx = 0;
		}

		/* Node empty, walk back up to parent */
		c = (struct rt_trie_node *) p;
	} while ((p = rtl_node_parent_rcu(c)) != NULL);

	return NULL; /* Root of trie */
}

static struct leaf *rtl_trie_firstleaf(struct trie *t)
{
	struct tnode *n = (struct tnode *)rcu_dereference_rtnl(t->trie);

	if (!n)
		return NULL;

	if (IS_LEAF(n))          /* trie is just a leaf */
		return (struct leaf *) n;

	return rtl_leaf_walk_rcu(n, NULL);
}

static struct leaf *rtl_trie_nextleaf(struct leaf *l)
{
	struct rt_trie_node *c = (struct rt_trie_node *) l;
	struct tnode *p = rtl_node_parent_rcu(c);

	if (!p)
		return NULL;	/* trie with just one leaf */

	return rtl_leaf_walk_rcu(p, c);
}

static int rtl_trie_search_leaf(struct fib_table *tb, struct leaf *l, u32 tb_id)
{
	int found = 0;
    int flag = 1;
	struct hlist_head *lih = &l->list;
	struct hlist_node *tmp;
	struct leaf_info *li = NULL;
	struct fib_alias *fa, *fa_node;

	hlist_for_each_entry_safe(li, tmp, lih, hlist) {
		list_for_each_entry_safe(fa, fa_node, &li->falh, fa_list) {
			
			struct fib_info *fi = fa->fa_info;
			if (fi) {
				struct fib_config cfg;
					
				memset(&cfg, 0, sizeof(struct fib_config));
				if (fi->fib_dev)
					cfg.fc_oif = fi->fib_dev->ifindex;
				cfg.fc_dst =  htonl(l->key);
				cfg.fc_dst_len = inet_mask_len(htonl(li->mask_plen));
				cfg.fc_gw = fi->fib_nh->nh_gw;
                if ((cfg.fc_gw==0) && (cfg.fc_dst_len<24))//A or B class ip addr
                    flag = 0;

				//printk("%s[%d], oif is %d, dst is 0x%x, dst_len is %d, gw is 0x%x\n", __FUNCTION__, __LINE__,
					//cfg.fc_oif, cfg.fc_dst, cfg.fc_dst_len, cfg.fc_gw);
				
				rtl_fn_hash_insert_hooks(tb, &cfg, fi);
				found++;
			}
		}
		
	}

    if (router_support_hw_nat != flag)
        router_support_hw_nat = flag;
	
	return found;
}

int rtl_add_router_to_hw_l3_table(void)
{
	struct trie *t;
	struct leaf *l = NULL;
	struct fib_table *tb;
	unsigned int found = 0;
	int flag = 1;
	unsigned int irq_flags = 0;

	//rtnl_lock();
	rcu_read_lock();
	tb = fib_get_table(&init_net, RT_TABLE_MAIN);
	if (tb) {
		t = (struct trie *) tb->tb_data;
		for (l = rtl_trie_firstleaf(t); l; l = rtl_trie_nextleaf(l)) {
			//found += rtl_trie_search_leaf(tb, l, tb->tb_id);
			struct hlist_head *lih = &l->list;
			struct hlist_node *tmp;
			struct leaf_info *li = NULL;
			struct fib_alias *fa, *fa_node;
		
			hlist_for_each_entry_safe(li, tmp, lih, hlist) {
				list_for_each_entry_safe(fa, fa_node, &li->falh, fa_list) {
					
					struct fib_info *fi = fa->fa_info;
					if (fi) {
						struct fib_config cfg;
							
						memset(&cfg, 0, sizeof(struct fib_config));
						if (fi->fib_dev)
							cfg.fc_oif = fi->fib_dev->ifindex;
						cfg.fc_dst =  htonl(l->key);
						cfg.fc_dst_len = inet_mask_len(htonl(li->mask_plen));
						cfg.fc_gw = fi->fib_nh->nh_gw;
		                if ((cfg.fc_gw==0) && (cfg.fc_dst_len<24))//A or B class ip addr
		                    flag = 0;
		
						//printk("%s[%d], oif is %d, dst is 0x%x, dst_len is %d, gw is 0x%x\n", __FUNCTION__, __LINE__,
						//	cfg.fc_oif, cfg.fc_dst, cfg.fc_dst_len, cfg.fc_gw);
						
						rtl_fn_hash_insert_hooks(tb, &cfg, fi);
						found++;
					}
				}
				
			}
		}

		if (router_support_hw_nat != flag){
		    local_irq_save(irq_flags);
			if(!flag){
				ACCESS_ONCE(router_support_hw_nat) = flag;
				ACCESS_ONCE(gHwNatEnabled) = flag;
				memset(gHwNatSetting,0,16);
				strcpy(gHwNatSetting,"0");
				mb();
				rtl865x_nat_reinit();
				rtl865x_changeOpMode(GATEWAY_MODE);
				#if !defined(CONFIG_RTK_VLAN_SUPPORT)
				rtl8651_setAsicOperationLayer(4);
				#endif
			}else{
				rtl865x_changeOpMode(GATEWAY_MODE);
				#if !defined(CONFIG_RTK_VLAN_SUPPORT)
				rtl8651_setAsicOperationLayer(4);
				#endif
				ACCESS_ONCE(gHwNatEnabled) = 1;
				memset(gHwNatSetting,0,16);
				strcpy(gHwNatSetting,"1");
				ACCESS_ONCE(router_support_hw_nat) = flag;
				mb();
			}
			local_irq_restore(irq_flags);
		}
	}
	rcu_read_unlock();
	//rtnl_unlock();
	return found;
}
/*===========================Sync fib trie API End==========================*/

int rtl_del_masq_info_by_dev_name(const char *name)
{
	int ret = FAILED;
	rtl_masq_if *entry;

	entry = rtl_get_masq_info_by_devName(name);
	if (entry != NULL)
	{
		entry->valid = 0;
		if (rtl865x_delIp(htonl(entry->ipAddr)) == SUCCESS) {
			rtl865x_nat_init();
			ret = SUCCESS;
		}
	}

	return ret;
}

static int rtl_add_wan_masq_info(void)
{
	int ret;
	unsigned int ip, mask;
	struct net_device *wanDev;

	if ((wanDev=rtl865x_getWanDev())&&(wanDev->flags&IFF_UP)) {
		/*If wan dev changed, such as ppp0->eth1, we need to delete the old wan
		dev eth1.*/
		if ((wan_dev_name_bak[0]!=0) && (strncmp(wan_dev_name_bak, wanDev->name, IFNAMSIZ))) {
			ret = rtl_del_masq_info_by_dev_name(wan_dev_name_bak);
			if (ret == SUCCESS)
				memset(wan_dev_name_bak, 0, IFNAMSIZ);
		}
		
		if (rtl865x_getDevIpAndNetmask(wanDev, &ip, &mask) == SUCCESS) {
			rtl_add_masq_info(wanDev->name, ip);
			memcpy(wan_dev_name_bak, wanDev->name, strlen(wanDev->name));
			wan_dev_name_bak[strlen(wanDev->name)] = '\0';
		}

		dev_put(wanDev);
	} else if (wan_dev_name_bak[0] != 0) {
		ret = rtl_del_masq_info_by_dev_name(wan_dev_name_bak);
		if (ret == SUCCESS)
			memset(wan_dev_name_bak, 0, IFNAMSIZ);
	}

	return SUCCESS;
}

#if defined(CONFIG_RTL_MULTIPLE_WAN)
static int rtl_add_multi_wan_masq_info(void)
{
	unsigned int ip, mask;

	if (get_dev_ip_mask(RTL_DRV_WAN1_NETIF_NAME, &ip, &mask) == 0) {
		rtl_add_masq_info(RTL_DRV_WAN1_NETIF_NAME, ip);
	} else {
		rtl_del_masq_info_by_dev_name(RTL_DRV_WAN1_NETIF_NAME);
	}

	return SUCCESS;
}
#endif

static int rtl_add_masq_info_to_hw_ip_table(void)
{
	int i;
	
	for (i=0; i<RTL_MULTIPLE_WAN_NUM; i++)
	{
		if ((rtl_masq_info[i].valid==1) && rtl_masq_info[i].ipAddr) {
			rtl865x_addIp(0, htonl(rtl_masq_info[i].ipAddr), IP_TYPE_NAPT);
		}
	}

	return SUCCESS;
}

static int rtl_sync_ppp_info_to_hw_ppp_table(void)
{
	int ret = FAILED;
	struct list_head *list = NULL;
	struct ppp *ppp = NULL;
	struct channel *pch = NULL;
	struct net_device *ppp_dev;
	struct sock *sk = NULL; 
	struct pppox_sock *po = NULL; 
	struct net_device *local_dev = NULL; 
	char ppp_dev_name[MAX_IFNAMESIZE] = {0};

	/*use gHwNatEnabled to instead of pch->pppoe==TRUE, if ppp dev exist, 
	and wan type is l2tp and pptp, gHwNatEnabled=0.*/
	if (gHwNatEnabled == 0)
		return FAILED;

#if defined(CONFIG_SWCONFIG_SUPPORT_HW_NAT)
	if (swconfig_vlan_enable) 
		strncpy(ppp_dev_name, RTL_SWCONFIG_DRV_PPP_NETIF_NAME, MAX_IFNAMESIZE);
	else
#endif
		strncpy(ppp_dev_name, RTL_DRV_PPP_NETIF_NAME, MAX_IFNAMESIZE);

	/*only consider ppp0 run hw nat, so here use RTL_DRV_PPP_NETIF_NAME to
	lookup ppp dev.*/
	if ((ppp_dev=__dev_get_by_name(&init_net, ppp_dev_name)) != NULL) {
		if ((ppp=netdev_priv(ppp_dev)) != NULL) {
			list = &ppp->channels;
			if ((!list_empty(list)) && list->next) {
				/*Here only check the first channel*/
				list = list->next;
				pch = list_entry(list, struct channel, clist);

				spin_lock_bh(&pch->downl);
				if (pch && pch->chan && pch->chan->private) {
#if defined (CONFIG_RTL_FAST_PPPOE)
                    if (pch->pppoe == TRUE)
#endif
                    {
                        sk = (struct sock *) pch->chan->private;
                        po = pppox_sk(sk);

                        if (po) {
                            local_dev = po->pppoe_dev;
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
                            if (local_dev) {			
                                rtl865x_attachMasterNetif(pch->ppp->dev->name, local_dev->name);
                                //add the netif mapping table
                                rtl_add_ps_drv_netif_mapping(pch->ppp->dev,pch->ppp->dev->name);	// sync from voip customer for multiple ppp
                                rtl865x_addPpp(pch->ppp->dev->name , (ether_addr_t*)po->pppoe_pa.remote, htons(po->pppoe_pa.sid), SE_PPPOE);
                                ret = SUCCESS;
                            }
#endif
                        }
                    }
				}
				spin_unlock_bh(&pch->downl);
			}
		}
	} else {	//del ppp info, just as ppp_shutdown_interface()
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
		rtl865x_detachMasterNetif(ppp_dev_name);
#if 0//def CONFIG_RTL_LAYERED_DRIVER_L2	
		#if defined (CONFIG_RTL_HW_QOS_SUPPORT)
		rtl865x_qosFlushMarkRuleByDev(ppp_dev_name);
		#endif
#endif
		rtl_del_ps_drv_netif_mapping_by_name(ppp_dev_name);	// sync from voip customer for multiple ppp
		rtl865x_delPppbyIfName(ppp_dev_name);
#endif
		ret = SUCCESS;
	}

	return ret;
}

static int rtl_add_arp_to_hw_arp_table(void)
{
	unsigned int i;
	struct neighbour *n;
	struct neighbour __rcu **np;
	struct neigh_hash_table *nht;
	struct neigh_table *tbl = &arp_tbl;

	read_lock_bh(&tbl->lock);
	nht = rcu_dereference_protected(tbl->nht,
					lockdep_is_held(&tbl->lock));

	for (i = 0 ; i < (1 << nht->hash_shift); i++)
	{
		np = &nht->hash_buckets[i];
		while ((n = rcu_dereference_protected(*np,
				lockdep_is_held(&tbl->lock))) != NULL)
		{
			unsigned int state;

			read_lock(&n->lock);

			state = n->nud_state;
			/*now only add NUD_CONNECTED to hw arp table, but neigh_update
				call rtl_neigh_update_hooks, neigh state may not be NUD_CONNECTED,
				so need test here.*/
			//if (htonl(*((u32 *)n->primary_key)) == 0xc0a802c8)
				//printk("arp of 192.168.2.200 state is 0x%x\n", state);
			
			if (state & (NUD_CONNECTED|NUD_STALE)) {
				syn_asic_arp(n,  1);
			}
			
			read_unlock(&n->lock);
			np = &n->next;
		}

		nht = rcu_dereference_protected(tbl->nht,
						lockdep_is_held(&tbl->lock));
	}

	read_unlock_bh(&tbl->lock);

	return SUCCESS;
}

#if defined(CONFIG_SWCONFIG_SUPPORT_HW_NAT)
int rtl_sync_hw_nat_wan_dev_addr_to_netif(void)
{
	rtl865x_netif_t netif;
	int retval = FAILED;
	uint8* wan_netif_addr = NULL;
	struct net_device *wan_dev = NULL;

	if (swconfig_vlan_enable) {
		if ((wan_dev = __dev_get_by_name(&init_net, hw_nat_wan_dev_name)) != NULL) {
			if ((wan_netif_addr=rtl_get_netif_gmac(hw_nat_wan_dev_name)) && 
				memcmp(wan_netif_addr, wan_dev->dev_addr, ETHER_ADDR_LEN)) {
				memcpy(netif.macAddr.octet, wan_dev->dev_addr, ETHER_ADDR_LEN);
				memcpy(netif.name, hw_nat_wan_dev_name, MAX_IFNAMESIZE);
				retval = rtl865x_setNetifMac(&netif);
			}
		}
	}
	return retval;
}
#endif

int rtl_check_pre_reserver_conn(struct nf_conntrack_tuple *tuple, const struct nf_conntrack_tuple *orig_tuple,
		 										const struct nf_nat_range *range, struct nf_conn *ct, enum nf_nat_manip_type maniptype)
{
	int ret = SUCCESS;
	
	if((gHwNatEnabled) && (maniptype==NF_NAT_MANIP_SRC) &&
		((orig_tuple->dst.protonum==IPPROTO_TCP) ||(orig_tuple->dst.protonum==IPPROTO_UDP)))
	{
		unsigned int asicNaptHashScore=0;
		rtl865x_napt_entry rtl865xNaptEntry;
		
		rtl865xNaptEntry.protocol = (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum==IPPROTO_TCP)? 1: 0;

		rtl865xNaptEntry.intIp = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
		rtl865xNaptEntry.remIp = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip;
		rtl865xNaptEntry.extIp = tuple->src.u3.ip;
		rtl865xNaptEntry.intPort = rtl865xNaptEntry.protocol?ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.tcp.port:ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.udp.port;
		rtl865xNaptEntry.remPort = rtl865xNaptEntry.protocol?ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.tcp.port:ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.udp.port;
		rtl865xNaptEntry.extPort = rtl865xNaptEntry.protocol?tuple->src.u.tcp.port:tuple->src.u.udp.port;
		
		rtl865x_getAsicNaptHashScore(&rtl865xNaptEntry, &asicNaptHashScore);
		/*
		printk("%s:%d:maniptype is %d,%s (%u.%u.%u.%u:%u ->  %u.%u.%u.%u:%u ->%u.%u.%u.%u:%u),asicNaptHashScore is %d\n\n\n",
			__FUNCTION__,__LINE__,maniptype, proto?"tcp":"udp", 
			NIPQUAD(sip), sp, NIPQUAD(gip), gp, NIPQUAD(dip), dp,asicNaptHashScore);	
		*/
		ret = FAILED;
		if (asicNaptHashScore ==100) {
			rtl865x_preReserveConn(&rtl865xNaptEntry);
			ret = SUCCESS;
		}
	}
	
	return ret;
}


int rtl_get_new_rover(__be16 *portptr, unsigned int min, u_int16_t off_old, unsigned int range_size, u16 *rover,
								struct nf_conntrack_tuple *tuple, const struct nf_nat_range *range,
				 				enum nf_nat_manip_type maniptype, const struct nf_conn *ct)
{
	int i;
	u_int16_t off = off_old;
	unsigned int tryCnt=0;
	rtl865x_napt_entry rtl865xNaptEntry;
	unsigned int asicNaptHashScore=0;
	unsigned int highestScore=0;
	unsigned int lowestScore=0;
	__be16 bestCandidatePort=0;
	__be16 newOff=0;

	if(ct->master || (ct->status & IPS_EXPECTED)){
		for (i = 0; i < range_size; i++, off++) {
			*portptr = htons(min + off % range_size);
			if (nf_nat_used_tuple(tuple, ct))
				continue;
			if (!(range->flags & NF_NAT_RANGE_PROTO_RANDOM))
				*rover = off;
			return SUCCESS;
		}
	}else
	{
		for (i=0; i<range_size; i++) 
		{
		    if ((gHwNatEnabled) && (maniptype==NF_NAT_MANIP_SRC)) {
				rtl865x_optimizeExtPort(off++, range_size, &newOff);
				*portptr = htons(min + newOff % range_size);
			} else {
		    	*portptr = htons(min + off % range_size);
				off++;
			}

			if (nf_nat_used_tuple(tuple, ct))
				continue;

			if ((gHwNatEnabled) && (maniptype==NF_NAT_MANIP_SRC)) {
				/* outbound flow */
				rtl865xNaptEntry.protocol = (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum==IPPROTO_TCP)? 1: 0;
				rtl865xNaptEntry.intIp = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
				rtl865xNaptEntry.remIp = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip;
				rtl865xNaptEntry.extIp = tuple->src.u3.ip;
				rtl865xNaptEntry.intPort = rtl865xNaptEntry.protocol?ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.tcp.port:ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.udp.port;
				rtl865xNaptEntry.remPort = rtl865xNaptEntry.protocol?ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.tcp.port:ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.udp.port;
				rtl865xNaptEntry.extPort= rtl865xNaptEntry.protocol?tuple->src.u.tcp.port:tuple->src.u.udp.port;

				rtl865x_getAsicNaptHashScore(&rtl865xNaptEntry,&asicNaptHashScore);

				if (asicNaptHashScore == 100) {
				    highestScore=asicNaptHashScore;
					lowestScore=asicNaptHashScore;
					bestCandidatePort=*portptr;
				} else {
				    /*otherwise use the best cadidate port*/
				    if (bestCandidatePort == 0) {
						bestCandidatePort=*portptr;
						highestScore=asicNaptHashScore;
						lowestScore=asicNaptHashScore;
					}

					if (asicNaptHashScore > highestScore) {
						highestScore=asicNaptHashScore;
						bestCandidatePort=*portptr;
					}

					if (asicNaptHashScore < lowestScore) {
						lowestScore=asicNaptHashScore;
					}

					if (tryCnt++ <= MAX_EXTPORT_TRY_CNT) {
						continue;
					} else {
		    			*portptr=bestCandidatePort;
					}
				}

				rtl865xNaptEntry.extPort=*portptr;
				rtl865x_preReserveConn(&rtl865xNaptEntry);
			}
			/*
		    printk("%s:%d:maniptype is %d, %s (%u.%u.%u.%u:%u -> %u.%u.%u.%u:%u -> %u.%u.%u.%u:%u) ,lowestScore is %d,highestScore is %d\n\n\n",
			__FUNCTION__,__LINE__,maniptype, rtl865xNaptEntry.protocol?"tcp":"udp",
			NIPQUAD(rtl865xNaptEntry.intIp), rtl865xNaptEntry.intPort, NIPQUAD(rtl865xNaptEntry.extIp), rtl865xNaptEntry.extPort, NIPQUAD(rtl865xNaptEntry.remIp), rtl865xNaptEntry.remPort,lowestScore, highestScore);
			*/

			if (!(range->flags & NF_NAT_RANGE_PROTO_RANDOM))
				*rover = off;

			return SUCCESS;
		}
	}

	return FAILED;
}

spinlock_t lock_hwnapt;
static void rtl_get_extIp_router_timer_fn(unsigned long arg)
{	
	/*===========================check extIp===========================*/
    spin_lock_bh(&lock_hwnapt);
	rtl_add_wan_masq_info();
#if defined(CONFIG_RTL_MULTIPLE_WAN)
	rtl_add_multi_wan_masq_info();
#endif
	rtl_add_masq_info_to_hw_ip_table();

	/*============================check ppp============================*/
	rtl_sync_ppp_info_to_hw_ppp_table();

	/*===========================check router==========================*/
	rtl_clear_router_exist_in_ps_flag();
	rtl_add_router_to_hw_l3_table();
	rtl_del_router_not_exist_in_ps();

	/*============================check arp============================*/
	rtl_clear_arp_exist_in_ps_flag();
	rtl_add_arp_to_hw_arp_table();
	rtl_del_arp_not_exist_in_ps();

	if (rtl8651_getAsicOperationLayer() > 2)
		rtl_enable_netif_routing();

#if defined(CONFIG_SWCONFIG_SUPPORT_HW_NAT)
	rtl_sync_hw_nat_wan_dev_addr_to_netif();
#endif
	
      	mod_timer(&hw_extIp_router_timer, jiffies + RTL_GET_EXTIP_ROUTER_EXPIRE);
    spin_unlock_bh(&lock_hwnapt);
}


int rtl_hw_nat_init_refine(void)
{
	memset(wan_dev_name_bak, 0, IFNAMSIZ);
	rtl_nat_init_hooks();
	rtl_ip_tables_init_hooks();

	init_timer(&hw_extIp_router_timer);
	hw_extIp_router_timer.expires  = jiffies + RTL_GET_EXTIP_ROUTER_EXPIRE;
	hw_extIp_router_timer.data     = 0L;
	hw_extIp_router_timer.function = rtl_get_extIp_router_timer_fn;
	mod_timer(&hw_extIp_router_timer, jiffies + RTL_GET_EXTIP_ROUTER_EXPIRE);
	spin_lock_init(&lock_hwnapt);

	return SUCCESS;
}
#endif

#if defined (CONFIG_RTL819X_WDT)

#define _WDTCNR_			0xB800311C

#define _WDTKICK_			(1 << 23)
#ifdef __ECOS
#define _WDTSTOP_			(0xA5000000)
#else
#define _WDTSTOP_			(0xA5f00000)
#endif

static unsigned long	watchDogval;
 void rtl_watchdog_stop(void)
{
	*((volatile unsigned long *)_WDTCNR_) |= _WDTKICK_;
	watchDogval = *((volatile unsigned long *)_WDTCNR_);
	*((volatile unsigned long *)_WDTCNR_) = _WDTSTOP_;

}

void rtl_watchdog_resume(void)
{
	*((volatile unsigned long *)_WDTCNR_) = watchDogval;
	*((volatile unsigned long *)_WDTCNR_) |= _WDTKICK_;
}


void rtl_watchdog_kick(void)
{
	*((volatile unsigned long *)_WDTCNR_) |= _WDTKICK_;
}

#else // no watchdog support

void rtl_watchdog_stop(void)
{}

void rtl_watchdog_resume(void)
{}

 void rtl_watchdog_kick(void)
{}

#endif

