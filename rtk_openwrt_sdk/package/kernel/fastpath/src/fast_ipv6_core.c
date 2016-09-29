#ifdef CONFIG_RTL_FAST_IPV6
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/kernel_stat.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
//#include <linux/brlock.h>
#include <linux/net.h>
#include <linux/socket.h>
#include <linux/version.h>

#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/string.h>
#include <net/ip.h>
#include <net/protocol.h>
#include <net/route.h>
#include <net/sock.h>
#include <net/arp.h>
#include <net/raw.h>
#include <net/checksum.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#include <uapi/linux/netfilter.h>
#else
#include <linux/netfilter.h>
#endif
#include <linux/netfilter_ipv4.h>
#include <linux/netlink.h>

#include <linux/in.h>
#include <linux/udp.h>
#include <linux/if_tunnel.h>
#include <linux/if_ether.h>


//ipv6 header 
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

/*common*/

#include <net/netfilter/nf_conntrack.h>
#include <net/rtl/rtl_types.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>
#include <net/rtl/fastpath/fastpath_core.h>
//#include <net/rtl/rtl865x_netif.h>
//#include <net/rtl/rtl_nic.h>
#include <net/rtl/rtl_queue.h>
#include <linux/netfilter_ipv6/ip6_tables.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <linux/netfilter/nf_conntrack_tcp.h>
#if defined(CONFIG_RTL_819X)
#include <net/rtl/features/rtl_features.h>
#endif



/*	Global Variable define		*/
int  fast_ipv6_fw =0;
#define IPV6_PROTO 0x86dd

/*****************	data structures define******************/

struct V6_PATH_List_Entry
{
	/* hash 5 tuple */
	struct V6_Tuple u;
	
#define 	saddr_v6		u.saddr
#define 	daddr_v6		u.daddr
#define 	protocol_v6		u.protocol
#define 	sport_v6		u.sport
#define 	dport_v6		u.dport

	uint32			last_used;
#if defined(IMPROVE_QOS)
#if defined(CONFIG_NET_SCHED)
	uint32 mark;	
#endif
#endif

	CTAILQ_ENTRY(V6_PATH_List_Entry) path_link;
	CTAILQ_ENTRY(V6_PATH_List_Entry) tqe_link;
};


struct V6_Path_Table
{
	#if defined(CONFIG_SMP)
	spinlock_t			v6_path_table_lock;
	#endif
	CTAILQ_HEAD(V6_Path_list_entry_head, V6_PATH_List_Entry) *list;
};

CTAILQ_HEAD(V6_Path_list_inuse_head, V6_PATH_List_Entry) v6_path_list_inuse;
CTAILQ_HEAD(V6_Path_list_free_head, V6_PATH_List_Entry) v6_path_list_free;

struct V6_Path_Table *v6_table_path;
static int v6_path_table_list_max;
/************data structures define End ***************************/


/**************UDP fragment struct define*/
#ifdef CONFIG_V6_UDP_FRAG_CACHE
#define V6_FRAG_IDLE 0
#define V6_FRAG_FORWADING 1
#define V6_FRAG_CACHE_TIMEOUT (10 * HZ)
struct V6_udp_FragCache_Entry 
{
	unsigned int	frag_id;
		/* hash 5 tuple */
	struct V6_Tuple u;
		
#define 	saddr_v6		u.saddr
#define 	daddr_v6		u.daddr
#define 	protocol_v6		u.protocol
#define 	sport_v6		u.sport
#define 	dport_v6		u.dport
	uint8	status;
	struct timer_list timer;
	CTAILQ_ENTRY(V6_udp_FragCache_Entry) path_link;
	CTAILQ_ENTRY(V6_udp_FragCache_Entry) tqe_link;
};

struct V6_udp_FragCache_Table
{
	#if defined(CONFIG_SMP)
	spinlock_t			v6_udp_fragcache_table_lock;
	#endif
	CTAILQ_HEAD(V6_udp_cache_list_head, V6_udp_FragCache_Entry) *list;
};

CTAILQ_HEAD(V6_udp_cache_free_head,V6_udp_FragCache_Entry) V6_udp_cache_list_free;

struct V6_udp_FragCache_Table *V6_udp_cache_table;
static int V6_max_udp_frag_entry;

#endif
/*****************UDP structures  end ***************************/

/*
	V6 fastpath hash function
*/
__IRAM_GEN inline static uint32
V6_FastPath_Hash_PATH_Entry(struct in6_addr sip,uint32 sport,struct in6_addr dip,uint32 dport,uint16 protocol)
{
	register uint32 hash;
	hash =  ((sip.s6_addr32[0]>>8)^(sip.s6_addr32[0]));	
	hash ^= ((sip.s6_addr32[1]>>8)^(sip.s6_addr32[1]));
	hash ^= ((sip.s6_addr32[2]>>8)^(sip.s6_addr32[2]));
	hash ^= ((sip.s6_addr32[3]>>8)^(sip.s6_addr32[3]));	

	hash ^= ((dip.s6_addr32[0]>>16)^(dip.s6_addr32[0]));	
	hash ^= ((dip.s6_addr32[1]>>16)^(dip.s6_addr32[1]));
	hash ^= ((dip.s6_addr32[2]>>16)^(dip.s6_addr32[2]));
	hash ^= ((dip.s6_addr32[3]>>16)^(dip.s6_addr32[3]));	

	hash ^= sport>>4;
	hash ^= dport;
	hash ^= protocol;
	return (v6_path_table_list_max-1) & (hash ^ (hash >> 12));	
}

/*
	Add one V6 connnection info to V6 fastpath table
*/
int rtk_addV6Connection(struct V6_Tuple *PathEntry, struct sk_buff *pskb ,void *ct)
{	
	uint32 hash;	
	struct V6_PATH_List_Entry *entry_path;	
#if defined(IMPROVE_QOS)
	void *InDev, *OutDev;
	struct ipv6hdr *ipheader;
	struct tcphdr *tcpheader;
	u_short proto;

	__u32 ori_mark;
	struct dst_entry *ori_dst;
	struct  in6_addr ori_saddr, ori_daddr;
	unsigned short ori_sport, ori_dport;

	rtl_store_skb_ipv6_dst(pskb);
	InDev = rtl_get_skb_dev(pskb);
	if (rtl_ip6_route_input(pskb) == FAILED)
		return 0;
			
	if (rtl_get_skb_ipv6_dst(pskb) == NULL)
	{
		rtl_set_skb_ipv6_dst(pskb);
		OutDev = NULL;
	}
	else
	{
		OutDev = rtl_get_skb_ipv6_dst_dev(pskb);	//store out device	
		rtl_dst_release(pskb);		//release dst
		rtl_set_skb_ipv6_dst(pskb);
	}
#endif

	#if defined(CONFIG_SMP)
	spin_lock(&v6_table_path->v6_path_table_lock);
	#endif

	/*original direction */
	hash = V6_FastPath_Hash_PATH_Entry(PathEntry->saddr, PathEntry->sport, 
		PathEntry->daddr, PathEntry->dport, PathEntry->protocol);

	CTAILQ_FOREACH(entry_path, &v6_table_path->list[hash],path_link)
	{
		if( (entry_path->sport_v6 == PathEntry->sport) &&
			(entry_path->dport_v6 == PathEntry->dport) &&
			(!ipv6_addr_cmp(&(entry_path->saddr_v6),&(PathEntry->saddr))) &&
			(!ipv6_addr_cmp(&(entry_path->daddr_v6),&(PathEntry->daddr))) &&
			(entry_path->protocol_v6 == PathEntry->protocol))
		{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG					
			panic_printk("%s,%d,Entry already Exist!!!\n",__FUNCTION__,__LINE__);
#endif
			goto Reply_Direction;
		}
	}
	
	if(!CTAILQ_EMPTY(&v6_path_list_free))
	{
		entry_path = CTAILQ_FIRST(&v6_path_list_free);
#if defined(IMPROVE_QOS)			
		proto = ntohs(rtl_get_skb_protocol(pskb));
		ipheader = rtl_ipv6_hdr(pskb);
		tcpheader = (struct tcphdr *)(((unsigned char *)ipheader) + sizeof(struct ipv6hdr));

		/*backup original info to check qos rule at iptables mangle table*/
		ori_mark = rtl_get_skb_mark(pskb);
		ori_saddr = ipheader->saddr;
		ori_sport = tcpheader->source;
		ori_daddr = ipheader->daddr;
		ori_dport = tcpheader->dest;

		/*Replace sip/sport dip/dport to get mark value for Qos!!*/
		rtl_set_skb_mark(pskb, 0);
		ipheader->saddr= PathEntry->saddr;
		tcpheader->source = PathEntry->sport;
		ipheader->daddr = PathEntry->daddr;
		tcpheader->dest = PathEntry->dport;		
		
		//do ip6table to get mark value for qos!!!
		if(proto == ETH_P_IPV6)
		{
			#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			(list_empty(&nf_hooks[PF_INET6][NF_INET_PRE_ROUTING]))?: \
				rtl_ipt6_do_table(pskb, NF_INET_PRE_ROUTING, InDev,NULL);
		
			(list_empty(&nf_hooks[PF_INET6][NF_INET_POST_ROUTING]))?: \	
				rtl_ipt6_do_table(pskb, NF_INET_POST_ROUTING,NULL,OutDev);
			#else
			(list_empty(&nf_hooks[PF_INET6][NF_IP_PRE_ROUTING]))?: \
				rtl_ipt6_do_table(pskb, NF_IP_PRE_ROUTING, InDev,NULL);
		
			(list_empty(&nf_hooks[PF_INET6][NF_IP_POST_ROUTING]))?: \	
				rtl_ipt6_do_table(pskb, NF_IP_POST_ROUTING,NULL,OutDev);	
			#endif
			//save the qos mark value	
			entry_path->mark = rtl_get_skb_mark(pskb);
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG			
			if(net_ratelimit())
				panic_printk("%s,%d,qos mark value is:%d\n",__FUNCTION__,__LINE__,entry_path->mark);
#endif		
		}

		/*restore the info*/
		rtl_set_skb_mark(pskb, ori_mark);
		ipheader->saddr= ori_saddr;
		tcpheader->source = ori_sport;
		ipheader->daddr = ori_daddr;
		tcpheader->dest = ori_dport;	
#endif
		//add info	
		entry_path->saddr_v6 = PathEntry->saddr;
		entry_path->daddr_v6 = PathEntry->daddr;
		entry_path->protocol_v6 = PathEntry->protocol;
		entry_path->sport_v6 = PathEntry->sport;
		entry_path->dport_v6 = PathEntry->dport;	
		entry_path->last_used=jiffies;
		
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG	
		panic_printk("%s,%d,Add session success \n",__FUNCTION__,__LINE__);
		panic_printk("%s,%d,Add INFO :\n",__FUNCTION__,__LINE__);
		panic_printk(" PathEntry->sport(%d)\n",entry_path->sport_v6);
		panic_printk(" PathEntry->dport(%d)\n",entry_path->dport_v6);
		panic_printk(" PathEntry->protocol(%d)\n",entry_path->protocol_v6);
		
		panic_printk(" PathEntry->saddr1(%u)\n",entry_path->saddr_v6.s6_addr32[0]); 			
		panic_printk(" PathEntry->saddr2(%u)\n",entry_path->saddr_v6.s6_addr32[1]);
		panic_printk(" PathEntry->saddr3(%u)\n",entry_path->saddr_v6.s6_addr32[2]);
		panic_printk(" PathEntry->saddr4(%u)\n",entry_path->saddr_v6.s6_addr32[3]); 
		
		panic_printk(" PathEntry->daddr1(%u)\n",entry_path->daddr_v6.s6_addr32[0]); 			
		panic_printk(" PathEntry->daddr2(%u)\n",entry_path->daddr_v6.s6_addr32[1]);
		panic_printk(" PathEntry->daddr3(%u)\n",entry_path->daddr_v6.s6_addr32[2]);
		panic_printk(" PathEntry->daddr4(%u)\n",entry_path->daddr_v6.s6_addr32[3]);
		panic_printk("**************************************\n");		
#endif	

		CTAILQ_REMOVE(&v6_path_list_free, entry_path, tqe_link);
		CTAILQ_INSERT_TAIL(&v6_path_list_inuse, entry_path, tqe_link);
		CTAILQ_INSERT_TAIL(&v6_table_path->list[hash], entry_path, path_link);	
	}

Reply_Direction:
	/*#############################################################################*/
	/*#############################################################################*/	
	/*Reply direction ,sIP<->dIp sPort<->dPort exchange*/
	hash = V6_FastPath_Hash_PATH_Entry(PathEntry->daddr,PathEntry->dport,
		PathEntry->saddr,PathEntry->sport,PathEntry->protocol);
	
	CTAILQ_FOREACH(entry_path, &v6_table_path->list[hash],path_link)
	{
		if( (entry_path->sport_v6 == PathEntry->dport) &&
			(entry_path->dport_v6 == PathEntry->sport) &&
			(!ipv6_addr_cmp(&(entry_path->saddr_v6),&(PathEntry->daddr))) &&
			(!ipv6_addr_cmp(&(entry_path->daddr_v6),&(PathEntry->saddr))) &&
			(entry_path->protocol_v6 == PathEntry->protocol))
		{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG					
			panic_printk("%s,%d,Entry already Exist!!!\n",__FUNCTION__,__LINE__);
#endif
            #if defined(CONFIG_SMP)
            spin_unlock(&v6_table_path->v6_path_table_lock);
            #endif
			return 0;
		}
	}
	
	if(!CTAILQ_EMPTY(&v6_path_list_free))
	{
	
		entry_path = CTAILQ_FIRST(&v6_path_list_free);
#if defined(IMPROVE_QOS)	

		proto = ntohs(rtl_get_skb_protocol(pskb));
		ipheader = rtl_ipv6_hdr(pskb);
		tcpheader = (struct tcphdr *)(((unsigned char *)ipheader) + sizeof(struct ipv6hdr));
		/*backup original info to check qos rule at iptables mangle table*/
		ori_mark = rtl_get_skb_mark(pskb);
		ori_saddr = ipheader->saddr;
		ori_sport = tcpheader->source;
		ori_daddr = ipheader->daddr;
		ori_dport = tcpheader->dest;

		/*Replace sip/sport dip/dport to get mark value for Qos!!*/
		rtl_set_skb_mark(pskb, 0);
		ipheader->saddr= PathEntry->daddr;
		tcpheader->source = PathEntry->dport;
		ipheader->daddr = PathEntry->saddr;
		tcpheader->dest = PathEntry->sport;		

		//do ip6table to get mark value for qos!!!
		if(proto == ETH_P_IPV6)
		{

		#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			(list_empty(&nf_hooks[PF_INET6][NF_INET_PRE_ROUTING]))?: \
				rtl_ipt6_do_table(pskb, NF_INET_PRE_ROUTING, OutDev,NULL);
		
			(list_empty(&nf_hooks[PF_INET6][NF_INET_POST_ROUTING]))?: \	
				rtl_ipt6_do_table(pskb, NF_INET_POST_ROUTING,NULL,InDev);
		#else
			(list_empty(&nf_hooks[PF_INET6][NF_IP_PRE_ROUTING]))?: \
				rtl_ipt6_do_table(pskb, NF_IP_PRE_ROUTING, OutDev,NULL);
		
			(list_empty(&nf_hooks[PF_INET6][NF_IP_POST_ROUTING]))?: \	
				rtl_ipt6_do_table(pskb, NF_IP_POST_ROUTING,NULL,InDev);
		#endif

			entry_path->mark = rtl_get_skb_mark(pskb);
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG	
			if(net_ratelimit())
				panic_printk("%s,%d, qos mark value is:%d\n",__FUNCTION__,__LINE__,entry_path->mark);
#endif			
		}

		/*restore the info*/
		rtl_set_skb_mark(pskb, ori_mark);
		ipheader->saddr= ori_saddr;
		tcpheader->source = ori_sport;
		ipheader->daddr = ori_daddr;
		tcpheader->dest = ori_dport;	
#endif
		//add info	
		entry_path->saddr_v6 = PathEntry->daddr;
		entry_path->daddr_v6 = PathEntry->saddr;
		entry_path->protocol_v6 = PathEntry->protocol;
		entry_path->sport_v6 = PathEntry->dport;
		entry_path->dport_v6 = PathEntry->sport;	
		entry_path->last_used=jiffies;
		
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG	
		panic_printk("%s,%d,Add session success \n",__FUNCTION__,__LINE__);
		panic_printk("%s,%d,Add INFO :\n",__FUNCTION__,__LINE__);
		panic_printk(" PathEntry->sport(%d)\n",entry_path->sport_v6);
		panic_printk(" PathEntry->dport(%d)\n",entry_path->dport_v6);
		panic_printk(" PathEntry->protocol(%d)\n",entry_path->protocol_v6);
		
		panic_printk(" PathEntry->saddr1(%u)\n",entry_path->saddr_v6.s6_addr32[0]); 			
		panic_printk(" PathEntry->saddr2(%u)\n",entry_path->saddr_v6.s6_addr32[1]);
		panic_printk(" PathEntry->saddr3(%u)\n",entry_path->saddr_v6.s6_addr32[2]);
		panic_printk(" PathEntry->saddr4(%u)\n",entry_path->saddr_v6.s6_addr32[3]); 
		
		panic_printk(" PathEntry->daddr1(%u)\n",entry_path->daddr_v6.s6_addr32[0]); 			
		panic_printk(" PathEntry->daddr2(%u)\n",entry_path->daddr_v6.s6_addr32[1]);
		panic_printk(" PathEntry->daddr3(%u)\n",entry_path->daddr_v6.s6_addr32[2]);
		panic_printk(" PathEntry->daddr4(%u)\n",entry_path->daddr_v6.s6_addr32[3]);
		panic_printk("**************************************\n");		
#endif	
		
		CTAILQ_REMOVE(&v6_path_list_free, entry_path, tqe_link);
		CTAILQ_INSERT_TAIL(&v6_path_list_inuse, entry_path, tqe_link);
		CTAILQ_INSERT_TAIL(&v6_table_path->list[hash], entry_path, path_link);			
        #if defined(CONFIG_SMP)
        spin_unlock(&v6_table_path->v6_path_table_lock);
        #endif
		return 1;
	}

    #if defined(CONFIG_SMP)
    spin_unlock(&v6_table_path->v6_path_table_lock);
    #endif
	return 0;
}	

/*
	Delete one V6 connnection info to V6 fastpath table
*/
int rtk_delV6Connection(struct V6_Tuple *PathEntry)
{	
	uint32	hash;
	struct V6_PATH_List_Entry *entry_path;	
	#if defined(CONFIG_SMP)
	spin_lock(&v6_table_path->v6_path_table_lock);
	#endif
	hash = V6_FastPath_Hash_PATH_Entry(PathEntry->saddr,PathEntry->sport,
		PathEntry->daddr,PathEntry->dport,PathEntry->protocol);
	
	CTAILQ_FOREACH(entry_path, &v6_table_path->list[hash],path_link)
	{
		if( (entry_path->sport_v6 == PathEntry->sport) &&
			(entry_path->dport_v6 == PathEntry->dport) &&
			(!ipv6_addr_cmp(&(entry_path->saddr_v6),&(PathEntry->saddr))) &&
			(!ipv6_addr_cmp(&(entry_path->daddr_v6),&(PathEntry->daddr))) &&
			(entry_path->protocol_v6 == PathEntry->protocol))		
		{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG		
			panic_printk("%s,%d, delete fastpath entry !!!\n",__FUNCTION__,__LINE__);
#endif		
			CTAILQ_REMOVE(&v6_table_path->list[hash], entry_path, path_link);
			CTAILQ_REMOVE(&v6_path_list_inuse, entry_path, tqe_link);
			CTAILQ_INSERT_TAIL(&v6_path_list_free, entry_path, tqe_link);			
		}
	}
    #if defined(CONFIG_SMP)
    spin_unlock(&v6_table_path->v6_path_table_lock);
    #endif
}

/*
	flush all V6 connnection info
*/
int rtk_flushV6Connection()
{
	uint32	hash;
	struct V6_PATH_List_Entry *entry_path;
    #if defined(CONFIG_SMP)
    spin_lock(&v6_table_path->v6_path_table_lock);
    #endif
	for( hash =0 ;hash < v6_path_table_list_max ; ++hash)
	{				
		CTAILQ_FOREACH(entry_path, &v6_table_path->list[hash],path_link)
		{
			CTAILQ_REMOVE(&v6_table_path->list[hash], entry_path, path_link);
			CTAILQ_REMOVE(&v6_path_list_inuse, entry_path, tqe_link);
			CTAILQ_INSERT_TAIL(&v6_path_list_free, entry_path, tqe_link);
		}
	}
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG	
		panic_printk("%s,%d, flush all fastpath entry !!!\n",__FUNCTION__,__LINE__);
#endif	
    #if defined(CONFIG_SMP)
    spin_unlock(&v6_table_path->v6_path_table_lock);
    #endif
}


/*
	idle handle to V6 Connectiont
*/
int rtk_idleV6Connection(struct V6_Tuple *PathEntry,uint32 interval)
{
	uint16 ipprotocol;
	uint32	hash;
	unsigned long now, last_used;
	struct V6_PATH_List_Entry *entry_path;	

	now = jiffies;
    #if defined(CONFIG_SMP)
    spin_lock(&v6_table_path->v6_path_table_lock);
    #endif

	hash = V6_FastPath_Hash_PATH_Entry(PathEntry->saddr,PathEntry->sport,
		PathEntry->daddr,PathEntry->dport,PathEntry->protocol);
	
	CTAILQ_FOREACH(entry_path, &v6_table_path->list[hash],path_link)
	{
		if( (entry_path->sport_v6 == PathEntry->sport) &&
			(entry_path->dport_v6 == PathEntry->dport) &&
			(!ipv6_addr_cmp(&(entry_path->saddr_v6),&(PathEntry->saddr))) &&
			(!ipv6_addr_cmp(&(entry_path->daddr_v6),&(PathEntry->daddr))) &&
			(entry_path->protocol_v6 == PathEntry->protocol))
			{			
				last_used = entry_path->last_used;
				if (time_before((now - interval), last_used))
				{
                    #if defined(CONFIG_SMP)
                    spin_unlock(&v6_table_path->v6_path_table_lock);
                    #endif
					return LR_FAILED;
				}
				break;
			}
	}
	
	hash = V6_FastPath_Hash_PATH_Entry(PathEntry->daddr,PathEntry->dport,
		PathEntry->saddr,PathEntry->sport,PathEntry->protocol);
	
	CTAILQ_FOREACH(entry_path, &v6_table_path->list[hash],path_link)
	{
		if( (entry_path->sport_v6 == PathEntry->sport) &&
			(entry_path->dport_v6 == PathEntry->dport) &&
			(!ipv6_addr_cmp(&(entry_path->saddr_v6),&(PathEntry->saddr))) &&
			(!ipv6_addr_cmp(&(entry_path->daddr_v6),&(PathEntry->daddr))) &&
			(entry_path->protocol_v6 == PathEntry->protocol))
			{			
				last_used = entry_path->last_used;
				if (time_before((now - interval), last_used))
				{
                    #if defined(CONFIG_SMP)
                    spin_unlock(&v6_table_path->v6_path_table_lock);
                    #endif
					return LR_FAILED;
				}
				break;
			}
	}
    #if defined(CONFIG_SMP)
    spin_unlock(&v6_table_path->v6_path_table_lock);
    #endif
	return LR_SUCCESS;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
/* return value:
	FAILED:	ct should be delete
	SUCCESS:		ct should NOT be delete.
*/
static u_int8_t rtl_get_ct_protonum(void *ct_ptr, enum ip_conntrack_dir dir)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	return ct->tuplehash[dir].tuple.dst.protonum;
}
#endif

int rtl_V6_Cache_Timer_update(void *ct)
{
	unsigned int expires, now;
	int		drop;
	rtl_fp_napt_entry rtlFpNaptEntry;
	now = jiffies;
	//read_lock_bh(&nf_conntrack_lock);

	if (rtl_get_ct_protonum(ct, (enum ip_conntrack_dir)IP_CT_DIR_ORIGINAL)  == IPPROTO_UDP)	
	{
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		if(rtl_get_ct_udp_status(ct) & IPS_SEEN_REPLY)
			expires = udp_get_timeouts_by_state(UDP_CT_REPLIED,ct,1);
		else
			expires = udp_get_timeouts_by_state(UDP_CT_UNREPLIED,ct,1);
	#else
		if(rtl_get_ct_udp_status(ct) & IPS_SEEN_REPLY)
			expires = nf_ct_udp_timeout_stream;
		else
			expires = nf_ct_udp_timeout;
	#endif
	}
	else if (rtl_get_ct_protonum(ct, IP_CT_DIR_ORIGINAL) == IPPROTO_TCP &&
		rtl_get_ct_tcp_state(ct) < TCP_CONNTRACK_LAST_ACK) 
	{
		expires = rtl_tcp_get_timeouts(ct);
	}
	else 
	{
		//read_unlock_bh(&nf_conntrack_lock);
		return FAILED;
	}

	drop = TRUE;
	
	{
		struct V6_Tuple V6PathEntry;		
		memset(&V6PathEntry,0,sizeof(struct V6_Tuple));
		struct nf_conn *tmp_ct = (struct nf_conn *)ct;

		V6PathEntry.protocol = rtl_get_ct_protonum_ipv6(tmp_ct, IP_CT_DIR_ORIGINAL);
		rtl_get_ct_v6_ip_by_dir(tmp_ct, IP_CT_DIR_ORIGINAL, 0, &V6PathEntry.saddr);
		rtl_get_ct_v6_ip_by_dir(tmp_ct, IP_CT_DIR_ORIGINAL, 1, &V6PathEntry.daddr);
		V6PathEntry.sport = ntohs(rtl_get_ct_port_by_dir(ct, IP_CT_DIR_ORIGINAL, 0));
		V6PathEntry.dport = ntohs(rtl_get_ct_port_by_dir(ct, IP_CT_DIR_ORIGINAL, 1));
		
		if(rtk_idleV6Connection(&V6PathEntry,expires) != LR_SUCCESS)
		{
			drop = FALSE;
		}
	} 
	//read_unlock_bh(&nf_conntrack_lock);

	if (drop == FALSE) 
	{
		rtl_check_for_acc(ct, (now+expires));
		return SUCCESS;
	} else{
		return FAILED;
	}
}

#ifdef CONFIG_V6_UDP_FRAG_CACHE
static inline unsigned int V6_frag_hashfn(unsigned int id, 
		struct in6_addr sip, struct in6_addr dip, uint16 protocol)
{
	register uint32 hash;
	hash =  ((sip.s6_addr32[0]>>8)^(sip.s6_addr32[0]));	
	hash ^= ((sip.s6_addr32[1]>>8)^(sip.s6_addr32[1]));
	hash ^= ((sip.s6_addr32[2]>>8)^(sip.s6_addr32[2]));
	hash ^= ((sip.s6_addr32[3]>>8)^(sip.s6_addr32[3]));	

	hash ^= ((dip.s6_addr32[0]>>16)^(dip.s6_addr32[0]));	
	hash ^= ((dip.s6_addr32[1]>>16)^(dip.s6_addr32[1]));
	hash ^= ((dip.s6_addr32[2]>>16)^(dip.s6_addr32[2]));
	hash ^= ((dip.s6_addr32[3]>>16)^(dip.s6_addr32[3]));	

	hash ^= (hash>>16)^id;
	hash ^=  protocol;

	return hash & (V6_max_udp_frag_entry - 1);
}


static inline struct V6_udp_FragCache_Entry *V6_find_fragEntry
	(unsigned int id, struct in6_addr sip, struct in6_addr dip, uint16 protocol)
{
	unsigned int hash = V6_frag_hashfn(id, sip, dip, protocol);
	struct V6_udp_FragCache_Entry *entry;

	#if defined(CONFIG_SMP)
    spin_lock(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
	#endif
	CTAILQ_FOREACH(entry, &V6_udp_cache_table->list[hash], path_link)
	{
		if ((entry->frag_id== id) &&
			(!ipv6_addr_cmp(&(entry->saddr_v6),&sip)) &&
			(!ipv6_addr_cmp(&(entry->daddr_v6),&dip)) &&
			(entry->protocol_v6== protocol))
		{
            #if defined(CONFIG_SMP)
            spin_unlock(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
            #endif
			return ((struct V6_udp_FragCache_Entry *)entry);
		}
	}
    #if defined(CONFIG_SMP)
    spin_unlock(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
    #endif
	return NULL;
}

static inline int V6_add_fragEntry(unsigned int id, struct in6_addr sip, uint16 sport, 
			struct in6_addr dip, uint16 dport, unsigned int protocol)
{
	unsigned int hash = V6_frag_hashfn(id, sip, dip, protocol);
	struct V6_udp_FragCache_Entry *entry;

    #if defined(CONFIG_SMP)
    spin_lock(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
    #endif
	if(CTAILQ_EMPTY(&V6_udp_cache_list_free))
	{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG	
		panic_printk("[%s],[%d],table full ,fail!!!\n",__FUNCTION__,__LINE__);
#endif	
        #if defined(CONFIG_SMP)
        spin_unlock(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
        #endif
		return 0;
	}
	
	entry = CTAILQ_FIRST(&V6_udp_cache_list_free);
	entry->frag_id= id;
	entry->saddr_v6= sip;
	entry->daddr_v6= dip;
	entry->protocol_v6= protocol;
	entry->sport_v6= sport;
	entry->dport_v6= dport;
	entry->status= V6_FRAG_FORWADING;

#ifdef CONFIG_RTL_FAST_IPV6_DEBUG	
	panic_printk("%s,%d,Add session success \n",__FUNCTION__,__LINE__);
	panic_printk(" PathEntry->frag_id(%d)\n",entry->frag_id);
	panic_printk(" PathEntry->sport(%d)\n",entry->sport_v6);
	panic_printk(" PathEntry->dport(%d)\n",entry->dport_v6);
	panic_printk(" PathEntry->protocol(%d)\n",entry->protocol_v6);
	
	panic_printk(" PathEntry->saddr1(%u)\n",entry->saddr_v6.s6_addr32[0]); 			
	panic_printk(" PathEntry->saddr2(%u)\n",entry->saddr_v6.s6_addr32[1]);
	panic_printk(" PathEntry->saddr3(%u)\n",entry->saddr_v6.s6_addr32[2]);
	panic_printk(" PathEntry->saddr4(%u)\n",entry->saddr_v6.s6_addr32[3]); 
	
	panic_printk(" PathEntry->daddr1(%u)\n",entry->daddr_v6.s6_addr32[0]); 			
	panic_printk(" PathEntry->daddr2(%u)\n",entry->daddr_v6.s6_addr32[1]);
	panic_printk(" PathEntry->daddr3(%u)\n",entry->daddr_v6.s6_addr32[2]);
	panic_printk(" PathEntry->daddr4(%u)\n",entry->daddr_v6.s6_addr32[3]);
	panic_printk("**************************************\n");		
#endif

	CTAILQ_REMOVE(&V6_udp_cache_list_free, entry, tqe_link);
	CTAILQ_INSERT_TAIL(&V6_udp_cache_table->list[hash], entry, path_link);
	entry->timer.expires = jiffies + V6_FRAG_CACHE_TIMEOUT;
	add_timer(&entry->timer);
    #if defined(CONFIG_SMP)
    spin_unlock(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
    #endif

	return 1;
}

static inline void V6_free_fragEntry(struct V6_udp_FragCache_Entry *entry)
{
	unsigned int hash = V6_frag_hashfn(entry->frag_id,entry->saddr_v6,entry->daddr_v6,entry->protocol_v6);
    #if defined(CONFIG_SMP)
    spin_lock(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
    #endif
	entry->status= V6_FRAG_IDLE;
	CTAILQ_REMOVE(&V6_udp_cache_table->list[hash], entry, path_link);
	CTAILQ_INSERT_TAIL(&V6_udp_cache_list_free, entry, tqe_link);
    #if defined(CONFIG_SMP)
    spin_unlock(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
    #endif
}
static inline void V6_free_cache(struct V6_udp_FragCache_Entry *entry)
{
	del_timer(&entry->timer);
	V6_free_fragEntry(entry);
}

static void V6_cache_timeout(unsigned long arg)
{
	struct V6_udp_FragCache_Entry *entry = (struct V6_udp_FragCache_Entry *)arg;
	if(entry->status == V6_FRAG_IDLE)
	{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG		
		panic_printk("[%s][%d],timeout But IDLE\n",__FUNCTION__,__LINE__);
#endif
		return;
	}
	V6_free_fragEntry(entry);
}

int V6_udp_fragCache_init(int V6_udp_frag_entry_max)
{
	int i;
	V6_udp_cache_table = (struct V6_udp_FragCache_Table *)kzalloc(sizeof(struct V6_udp_FragCache_Table), GFP_ATOMIC);
    #if defined(CONFIG_SMP)
    spin_lock_init(&V6_udp_cache_table->v6_udp_fragcache_table_lock);
    #endif
	if (V6_udp_cache_table == NULL) 
	{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG		
		panic_printk("MALLOC Failed! (Udp_FragCache_Table) \n");
#endif
		return 0;
	}
	CTAILQ_INIT(&V6_udp_cache_list_free);

	V6_max_udp_frag_entry = V6_udp_frag_entry_max;
	V6_udp_cache_table->list=(struct V6_udp_cache_list_head *)kmalloc(V6_udp_frag_entry_max*sizeof(struct V6_udp_cache_list_head), GFP_ATOMIC);
	if (V6_udp_cache_table->list == NULL) 
	{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG		
		panic_printk("MALLOC Failed! (Udp_FragCache_Table List) \n");
#endif
		return -1;
	}
	for (i=0; i< V6_udp_frag_entry_max; i++) 
	{
		CTAILQ_INIT(&V6_udp_cache_table->list[i]);
	}
	for (i=0; i< V6_max_udp_frag_entry; i++) 
	{
		struct V6_udp_FragCache_Entry *entry = (struct V6_udp_FragCache_Entry *)kmalloc(sizeof(struct V6_udp_FragCache_Entry), GFP_ATOMIC);
		if (entry == NULL) 
		{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG			
			panic_printk("MALLOC Failed! (UDP Path Table Entry) \n");
#endif
			return 0;
		}
		//init timer , start timer in add_entry!!!
		init_timer(&entry->timer);
		entry->timer.data = (unsigned long)entry;	/* pointer to queue	*/
		entry->timer.function = V6_cache_timeout;		/* expire function	*/		
		CTAILQ_INSERT_TAIL(&V6_udp_cache_list_free, entry, tqe_link);
	}
	return 1;
}
#endif

/*
	V6 fastpath Enter 
*/

extern int rtl_skb_dst_check_ipv6(struct sk_buff *skb);
extern int ip_finish_output6(struct sk_buff *skb);
extern unsigned int statistic_ipv6_fp;
extern int rtl_ip6_skb_dst_mtu(struct sk_buff *skb);
int ipv6_fast_enter(struct sk_buff *pskb)
{
	struct V6_PATH_List_Entry *entry_path;
	struct ethhdr *pMac=(struct ethhdr *)(rtl_skb_mac_header(pskb));;
	struct ipv6hdr *pHeader = rtl_ipv6_hdr(pskb);	
	struct tcphdr *tHeader = (struct tcphdr *)(((unsigned char *)pHeader) + sizeof(struct ipv6hdr));
	struct  in6_addr sIp,dIp;	
	uint32 sPort,dPort;
	uint32 iphProtocol;
	uint32 hash;
#ifdef CONFIG_V6_UDP_FRAG_CACHE	
	int first_frag=0,last_frag=0;
	struct frag_hdr *fh = NULL;
	struct V6_udp_FragCache_Entry * iter_entry = NULL;
	uint16 frag_off = 0;
#endif	
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	struct  dst_entry	*dst;
	struct  neighbour* neigh = NULL;
	struct hh_cache * hh = NULL;
#endif
	/*only handle ipv6 protocal */
#ifdef CONFIG_RTL_FAST_PPPOE
	if (rtl_get_skb_pppoe_flag(pskb) == 0)
#endif
	if(pMac->h_proto != ntohs(IPV6_PROTO))
		return 0;

	/*
		skip the link local/Mcast ip address packet!!!
	*/
	if((ipv6_addr_type(&pHeader->saddr) & IPV6_ADDR_LINKLOCAL)
		|| (ipv6_addr_type(&pHeader->daddr) & (IPV6_ADDR_MULTICAST|IPV6_ADDR_LINKLOCAL)))		
			return 0;
	
	/*
		only handle tcp/udp/frag packet!
	*/
	if((pHeader->nexthdr != NEXTHDR_TCP) && 
		(pHeader->nexthdr != NEXTHDR_UDP) &&
		(pHeader->nexthdr != NEXTHDR_FRAGMENT))
	{
		return 0;
	}

	if((pHeader->nexthdr == NEXTHDR_TCP) &&(tHeader->fin || tHeader->rst || tHeader->syn))
		return 0;

	sIp = pHeader->saddr;
	dIp = pHeader->daddr;
	iphProtocol =pHeader->nexthdr;
	sPort = tHeader->source;
	dPort = tHeader->dest;

#ifdef CONFIG_V6_UDP_FRAG_CACHE
	/*	handle ipv6 udp fragment packet!!!!*/

	if(pHeader->nexthdr == NEXTHDR_FRAGMENT)
	{
		fh = (struct frag_hdr *)(((unsigned char *)pHeader) + sizeof(struct ipv6hdr));
		if(fh->nexthdr == NEXTHDR_UDP)
		{
			frag_off = htons(fh->frag_off);
			if((!(frag_off & 0xfff8)) && (frag_off & 0x1))		//more =1,offset ==0
				first_frag = 1;

			else if((frag_off &0xfff8) && (!(frag_off & 0x1)))	//more =0,offest !=0 
				last_frag = 1;
			
			if(first_frag)
			{			
				tHeader = (struct tcphdr *)(((unsigned char *)tHeader) + sizeof(struct frag_hdr));
				iphProtocol = NEXTHDR_UDP;
				sPort = tHeader->source;
				dPort = tHeader->dest;
			}
			else
			{
				iphProtocol = NEXTHDR_UDP;
				iter_entry = V6_find_fragEntry(fh->identification,sIp,dIp,iphProtocol);
				
				if(iter_entry != NULL)
				{
					sPort = iter_entry->sport_v6;
					dPort = iter_entry->dport_v6;
				}
				else{					
					return 0;	//can't find the udp fragment cache,skip fast forward!!!
				}
			}
		}
	}
	
#endif
    #if defined(CONFIG_SMP)
    spin_lock(&v6_table_path->v6_path_table_lock);
    #endif
	hash = V6_FastPath_Hash_PATH_Entry(sIp, sPort, dIp, dPort, iphProtocol);
	CTAILQ_FOREACH(entry_path, &v6_table_path->list[hash],path_link)
	{
		if( ((entry_path->sport_v6 == sPort) &&
			(entry_path->dport_v6 == dPort) &&
			(!ipv6_addr_cmp(&(entry_path->saddr_v6),&sIp)) &&
			(!ipv6_addr_cmp(&(entry_path->daddr_v6),&dIp)) &&
			(entry_path->protocol_v6 ==iphProtocol)))
		{
			
			if (rtl_ip6_route_input(pskb) == FAILED)
				return 0;

			if (rtl_get_skb_ipv6_dst(pskb) == NULL)
				return 0;

			if (rtl_skb_ipv6_dst_check(pskb) == FAILED)
			{
				rtl_dst_release(pskb);
				#if defined(CONFIG_SMP)
                spin_unlock(&v6_table_path->v6_path_table_lock);
                #endif
				return 0;
			}

			if (rtl_check_dst_input(pskb) == FAILED)
			{
				rtl_dst_release(pskb);
                #if defined(CONFIG_SMP)
                spin_unlock(&v6_table_path->v6_path_table_lock);
                #endif
				return 0;
            }
			
#ifdef CONFIG_V6_UDP_FRAG_CACHE
			if(first_frag)	//first fragment,try to cache the info
			{	
				if(!V6_add_fragEntry(fh->identification,sIp,sPort,dIp,dPort,iphProtocol))
				{					
					rtl_dst_release(pskb);
					return 0;
				}
			}
			else if(last_frag)
			{
				//free the cache!!!!!
				if(iter_entry !=NULL)
					V6_free_cache(iter_entry);
			}
#endif
			
			rtl_set_skb_dev(pskb, NULL);
			
			//check the hop limit
			if(pHeader->hop_limit <= 1)
			{
				goto out_kfree_skb;			
			}			
			/* Mangling hops number*/
			pHeader->hop_limit--;			
									
#if defined(IMPROVE_QOS)
#if defined(CONFIG_NET_SCHED)			
			//pskb->mark = entry_path->mark;		//set mark!!!
			rtl_set_skb_mark(pskb, entry_path->mark);
#endif
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			if((rtl_get_skb_len(pskb) > rtl_ip6_skb_dst_mtu(pskb) && !rtl_skb_is_gso(pskb)) ||
				rtl_dst_allfrag(pskb))
			{		
				goto out_kfree_skb;		
			}

			//update the time
			entry_path->last_used = jiffies;

            #if defined(CONFIG_SMP)
            spin_unlock(&v6_table_path->v6_path_table_lock);
            #endif

            ip_finish_output6(pskb);
			statistic_ipv6_fp++;
			return NET_RX_DROP;
#else
			if((rtl_get_skb_len(pskb) > rtl_ip6_skb_dst_mtu(pskb) && !rtl_skb_is_gso(pskb)) ||
				rtl_dst_allfrag(pskb))
			{		
				goto out_kfree_skb;		
			}

			//update the time
			entry_path->last_used = jiffies;
			//try to fast forward!!!
			if (rtl_get_hh_from_skb(pskb))
			{
				rtl_neigh_hh_output(pskb);
				goto __out;
			}
			else if (rtl_get_neigh_from_skb(pskb))
			{
				rtl_neigh_output(pskb);
				goto __out;
			}
			else if (rtl_check_skb_dst_output_exist(pskb) == TRUE)
			{
				rtl_dst_output(pskb);
				goto __out;
			}
#endif		
out_kfree_skb:
			kfree_skb(pskb);
__out:
            #if defined(CONFIG_SMP)
            spin_unlock(&v6_table_path->v6_path_table_lock);
            #endif
			return NET_RX_DROP;
		}
	}
    #if defined(CONFIG_SMP)
    spin_unlock(&v6_table_path->v6_path_table_lock);
    #endif
	return 0;
}

int init_V6_table_path(int v6_path_tbl_list_max, int v6_path_tbl_entry_max)
{
	int i;

	v6_table_path = (struct V6_Path_Table *)kzalloc(sizeof(struct V6_Path_Table), GFP_ATOMIC);
	if (v6_table_path == NULL) {
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG				
		panic_printk("MALLOC Failed! (Path Table) \n");
#endif
		return -1;
	}
    #if defined(CONFIG_SMP)
    spin_lock_init(&v6_table_path->v6_path_table_lock);
    #endif
	CTAILQ_INIT(&v6_path_list_inuse);
	CTAILQ_INIT(&v6_path_list_free);

	v6_path_table_list_max = v6_path_tbl_list_max;
	v6_table_path->list = (struct V6_Path_list_entry_head *)kmalloc(v6_path_tbl_list_max*sizeof(struct V6_Path_list_entry_head), GFP_ATOMIC);
	if(v6_table_path->list == NULL)
	{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG	
		DEBUGP_SYS("MALLOC Failed! (Path Table list) \n");
#endif
		return -1;
	}
	for (i=0; i<v6_path_tbl_list_max; i++) 
	{
		CTAILQ_INIT(&v6_table_path->list[i]);
	}

	/* Path-List Init */
	for (i=0; i<v6_path_tbl_entry_max; i++) 
	{
		struct V6_PATH_List_Entry *entry_path = (struct V6_PATH_List_Entry *)kmalloc(sizeof(struct V6_PATH_List_Entry), GFP_ATOMIC);
		if (entry_path == NULL) 
		{
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG				
			panic_printk("MALLOC Failed! (Path Table Entry) \n");
#endif
			return -2;
		}
		CTAILQ_INSERT_TAIL(&v6_path_list_free, entry_path, tqe_link);
	}
	
	return 0;
}


#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int ipv6_forward_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data);
static int ipv6_forward_read_proc(struct seq_file *s, void *v)
{
      seq_printf(s, "%c\n", fast_ipv6_fw + '0');
      return 0;
}
int ipv6_fast_forward_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, ipv6_forward_read_proc, NULL));
}

static ssize_t ipv6_fast_forward_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return ipv6_forward_write_proc(file, userbuf,count, off);
}

struct file_operations ipv6_fast_forward_proc_fops= {
        .open           = ipv6_fast_forward_single_open,
        .write		    = ipv6_fast_forward_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#else
static int ipv6_forward_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
      int len;

      len = sprintf(page, "%c\n", fast_ipv6_fw + '0');

      if (len <= off+count) *eof = 1;
      *start = page + off;
      len -= off;
      if (len>count) len = count;
      if (len<0) len = 0;
      return len;
}
#endif

static int ipv6_forward_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
      char ipv6_tmp;

      if (count < 2)
	    return -EFAULT;
	  
      if (buffer && !copy_from_user(&ipv6_tmp, buffer, 1)) 
	  {
	    	fast_ipv6_fw = ipv6_tmp - '0';
#ifdef CONFIG_RTL_FAST_IPV6_DEBUG					
			panic_printk("%s,%d, fast_ipv6_fw(%d) \n",__FUNCTION__,__LINE__,fast_ipv6_fw);
#endif
			//if echo 0 > proc/ipv6_fast_forward,flush the original sesson info!!!
			if(!fast_ipv6_fw)
				rtk_flushV6Connection();
			
			return count;
      }
      return -EFAULT;
}

#if defined(CONFIG_PROC_FS)
static struct proc_dir_entry *ipv6_res=NULL;
#endif

int __init ipv6_fast_forward_init(void)
{
#if defined(CONFIG_PROC_FS)
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	ipv6_res = proc_create_data("ipv6_fast_forward", 0, &proc_root,
			 &ipv6_fast_forward_proc_fops, NULL);
    #else
	ipv6_res = create_proc_entry("ipv6_fast_forward", 0, NULL);
	if (ipv6_res) {
		ipv6_res->read_proc =  ipv6_forward_read_proc;
		ipv6_res->write_proc = ipv6_forward_write_proc;		
	}
    #endif
#endif
	//fast_ipv6_fw = 1;	//control by set_init now
	return 0;
}

void __exit ipv6_fast_forward_exit(void)
{
#if defined(CONFIG_PROC_FS)
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	if (ipv6_res) {
        remove_proc_entry("ipv6_fast_forward", &proc_root);
    }
    #else
	if (ipv6_res) {
		remove_proc_entry("ipv6_fast_forward", ipv6_res);
		ipv6_res = NULL;
	}
    #endif
#endif
	fast_ipv6_fw = 0 ;
}
#endif
