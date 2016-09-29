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
#include <linux/netfilter/nf_conntrack_tcp.h>

#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <net/netfilter/nf_conntrack_helper.h>

#include <net/rtl/rtl_types.h>
#include <net/rtl/features/rtl_features.h>
#include <net/rtl/fastpath/fastpath_core.h>

#include <net/rtl/features/rtl_ps_hooks.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#include <net/netfilter/nf_conntrack_timestamp.h>
#endif
unsigned int conntrack_min = 0;
unsigned int conntrack_max= 100;
#define MAX_NF_GC_SEARCH_CNT 128
static LIST_HEAD(close_list);
static LIST_HEAD(last_ack_list);
static LIST_HEAD(close_wait_list);
static LIST_HEAD(fin_wait_list);
static LIST_HEAD(time_wait_list);
static LIST_HEAD(syn_recv_list);
static LIST_HEAD(syn_sent_list);
static LIST_HEAD(established_list);
static LIST_HEAD(listen_list);
static LIST_HEAD(udp_unreply_list);
static LIST_HEAD(udp_assured_list);

__DRAM_FWD int	rtl_newGC_session_status_flags;	/* 0: no congest, 1: congest in 1 second, 2: congest, tring in another second, 3: overflow but could get more session by cut low priority session */
__DRAM_FWD unsigned long rtl_newGC_session_status_time;

struct tcp_state_hash_head Tcp_State_Hash_Head[]={
	{TCP_CONNTRACK_NONE,NULL},
	{TCP_CONNTRACK_SYN_SENT,&syn_sent_list},
	{TCP_CONNTRACK_SYN_RECV,&syn_recv_list},
	{TCP_CONNTRACK_ESTABLISHED,&established_list},
	{TCP_CONNTRACK_FIN_WAIT,&fin_wait_list},
	{TCP_CONNTRACK_CLOSE_WAIT,&close_wait_list},
	{TCP_CONNTRACK_LAST_ACK,&last_ack_list},
	{TCP_CONNTRACK_TIME_WAIT,&time_wait_list},
	{TCP_CONNTRACK_CLOSE,&close_list},
	{TCP_CONNTRACK_LISTEN,&listen_list},
	{TCP_CONNTRACK_MAX,NULL}
	};

struct udp_state_hash_head Udp_State_Hash_Head[]={
	{UDP_UNREPLY,&udp_unreply_list},
	{UDP_ASSURED,&udp_assured_list}
};

struct DROP_PRORITY drop_priority[]={
 	{TCP_CONNTRACK_CLOSE,60},
	{TCP_CONNTRACK_LAST_ACK,30},
	{TCP_CONNTRACK_CLOSE_WAIT,60},
	{TCP_CONNTRACK_TIME_WAIT,120},
	{TCP_CONNTRACK_FIN_WAIT,120},
	{UDP_UNREPLY,85},
//	{TCP_CONNTRACK_SYN_SENT,120},
//	{TCP_CONNTRACK_SYN_RECV,60},
	{TCP_CONNTRACK_SYN_SENT,110},
	{TCP_CONNTRACK_SYN_RECV,30},
	{UDP_ASSURED,10},
	{TCP_CONNTRACK_ESTABLISHED,120}		/* 2*60s	*/
};

/* statistic counters, prot_limit is the threshold for selecting the protocol conntrack to drop.
    eg. if TCP is 95(95%), then when TCP connections occupy more than 95%, gc will choose
    TCP to drop regardless its priority. Andrew
*/

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
int	rtl_nf_conntrack_threshold;
#endif
int	drop_priority_max_idx;
unsigned int prot_limit[PROT_MAX];
static atomic_t prot_counters[PROT_MAX];
static atomic_t _prot_limit[PROT_MAX];

static void init_conntrack_state_hash(void)
{
	int i;
	for (i = 0; i < sizeof(Tcp_State_Hash_Head)/sizeof(struct tcp_state_hash_head); i++)
	{
		struct tcp_state_hash_head *p;
		p = &Tcp_State_Hash_Head[i];
		if (p->state_hash)
			INIT_LIST_HEAD(p->state_hash);
	}
	for (i = 0; i < sizeof(Udp_State_Hash_Head)/sizeof(struct udp_state_hash_head); i++)
	{
		struct udp_state_hash_head *p;
		p = &Udp_State_Hash_Head[i];
		if (p->state_hash)
			INIT_LIST_HEAD(p->state_hash);
	}

	memset(prot_limit, 0, sizeof(unsigned int)*PROT_MAX);
	for (i=0;i<PROT_MAX;i++)
	{
		atomic_set(&prot_counters[i], 0);
		atomic_set(&_prot_limit[i], 0);
	}

	drop_priority_max_idx = sizeof(drop_priority)/sizeof(struct DROP_PRORITY);
	rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL_IDLE;
	return;
}

int drop_one_conntrack(const struct nf_conntrack_tuple *orig,const struct nf_conntrack_tuple *repl);
static inline void recalculate(void) {
	int i;
	for (i = 0; i < PROT_MAX; i++) {
		atomic_set(&_prot_limit[i], nf_conntrack_max * prot_limit[i] /100);
	}

	rtl_nf_conntrack_threshold = (nf_conntrack_max * 4)/5;
	if((nf_conntrack_max- rtl_nf_conntrack_threshold) > 64)
		rtl_nf_conntrack_threshold = nf_conntrack_max-64;

	if (nf_conntrack_max && unlikely(rtl_gc_threshold_check(NULL)==SUCCESS)) {
		if (rtl_newGC_session_status_flags!=RTL_FP_SESSION_LEVEL3) {
			rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL3;
			rtl_newGC_session_status_time=jiffies+RTL_FP_SESSION_LEVEL3_INTERVAL;
		}
	} else {
		rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL_IDLE;
	}
	//printk("icmp=%u  tcp=%u  udp=%u\n", _prot_limit[PROT_ICMP], _prot_limit[PROT_TCP], _prot_limit[PROT_UDP]);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
int conntrack_dointvec(ctl_table *table, int write, 
		     void *buffer, size_t *lenp, loff_t *ppos) 
#else
int conntrack_dointvec(ctl_table *table, int write, struct file *filp,
		     void *buffer, size_t *lenp, loff_t *ppos) 
#endif
{

	int err;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	err = proc_dointvec(table, write,  buffer, lenp, ppos);
#else
	err = proc_dointvec(table, write, filp, buffer, lenp, ppos);
#endif
	if (err != 0)
		return err;
	if (write)
		recalculate();
	return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
int conntrack_dointvec_minmax(ctl_table *table, int write, 
		     void *buffer, size_t *lenp, loff_t *ppos) 
#else
int conntrack_dointvec_minmax(ctl_table *table, int write, struct file *filp,
		     void *buffer, size_t *lenp, loff_t *ppos) 
#endif
{

	int err;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	err = proc_dointvec_minmax(table, write,  buffer, lenp, ppos);
#else
	err = proc_dointvec_minmax(table, write, filp, buffer, lenp, ppos);
#endif
	if (err != 0)
		return err;
	if (write)
		recalculate();
	return 0;
}
void clean_from_lists(void *ct, void *net)
{
	//pr_debug("clean_from_lists(%p)\n", ct);
	rtl_hlist_nulls_del_rcu(ct, IP_CT_DIR_ORIGINAL);
	rtl_hlist_nulls_del_rcu(ct, IP_CT_DIR_REPLY);

	/* has already spin_lock_bh() in the caller function	*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#else
	read_lock_bh(&nf_conntrack_lock); 
#endif
       switch (rtl_new_gc_get_ct_protonum(ct, IP_CT_DIR_ORIGINAL))
	{
	      	case IPPROTO_TCP:
	       		atomic_dec(&prot_counters[PROT_TCP] );
	        	break;
	        case IPPROTO_UDP:
	        	atomic_dec(&prot_counters[PROT_UDP] );
	        	break;
	        case IPPROTO_ICMP:
	        	atomic_dec(&prot_counters[PROT_ICMP] );
	        	break;
	}

	if((rtl_new_gc_get_ct_protonum(ct, IP_CT_DIR_ORIGINAL) == IPPROTO_TCP)||
		(rtl_new_gc_get_ct_protonum(ct, IP_CT_DIR_ORIGINAL) == IPPROTO_UDP)) {
		clean_from_lists_hooks(ct, net);
		rtl_list_del(ct);
		//list_del(&ct->state_tuple);

		if (nf_conntrack_max && unlikely(rtl_gc_threshold_check(net) == SUCCESS)) {
			if (rtl_newGC_session_status_flags!=RTL_FP_SESSION_LEVEL3) {
				rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL3;
				rtl_newGC_session_status_time=jiffies+RTL_FP_SESSION_LEVEL3_INTERVAL;
			}
		} else {
			rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL_IDLE;
		}

		//rtl_fp_mark_invalid(ct);
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#else
	read_unlock_bh(&nf_conntrack_lock); 
#endif

	/* Destroy all pending expectations */
	nf_ct_remove_expectations(ct);
	return;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
void rtl_death_action(void *ct_tmp)
{
	//struct nf_conn *ct = (void *)ul_conntrack;
	struct nf_conn *ct = (void *)ct_tmp;
	struct nf_conn_tstamp *tstamp;

	tstamp = nf_conn_tstamp_find(ct);
	if (tstamp && tstamp->stop == 0)
		tstamp->stop = ktime_to_ns(ktime_get_real());

	if (!test_bit(IPS_DYING_BIT, &ct->status) &&
	    unlikely(nf_conntrack_event(IPCT_DESTROY, ct) < 0)) {
		/* destroy event was not delivered */
		nf_ct_delete_from_lists(ct);
		nf_ct_dying_timeout(ct);
		return;
	}
	set_bit(IPS_DYING_BIT, &ct->status);
	nf_ct_delete_from_lists(ct);
	nf_ct_put(ct);
}
#else
void rtl_death_action(void *ct)
{
	void *net = (void*)nf_ct_net(ct);
	struct nf_conn_help *help = nfct_help(ct);
	struct nf_conntrack_helper *helper;

	if (help) {
		rcu_read_lock();
		helper = rcu_dereference(help->helper);
		if (helper && helper->destroy)
			helper->destroy(ct);
		rcu_read_unlock();
	}

	spin_lock_bh(&nf_conntrack_lock);
	/* Inside lock so preempt is disabled on module removal path.
	 * Otherwise we can get spurious warnings. */
	rtl_nf_ct_stat_inc(net);
	//NF_CT_STAT_INC(net, delete_list);
	clean_from_lists(ct, net);
	spin_unlock_bh(&nf_conntrack_lock);
	nf_ct_put(ct);
	return;
}
#endif

int32 rtl_connGC_addList(void *skb, void *ct)
{
	if(NULL == rtl_new_gc_ip_hdr(skb))
		return SUCCESS;
	switch (rtl_new_gc_get_skb_protocol(skb))
	{
		case IPPROTO_TCP:
			if(Tcp_State_Hash_Head[rtl_new_gc_get_ct_tcp_state(ct)].state_hash!=NULL)
			{
				rtl_list_add_tail(ct, PROT_TCP, 0);
				//list_add_tail(&ct->state_tuple,Tcp_State_Hash_Head[ct->proto.tcp.state].state_hash);
			}
			atomic_inc(&prot_counters[PROT_TCP] );
			break;
		case IPPROTO_UDP:
			if(rtl_new_gc_get_ct_udp_status(ct) & IPS_SEEN_REPLY)
				rtl_list_add_tail(ct, PROT_UDP, 1);
				//list_add_tail(&ct->state_tuple,Udp_State_Hash_Head[1].state_hash);
			else
				rtl_list_add_tail(ct, PROT_UDP, 0);
				//list_add_tail(&ct->state_tuple,Udp_State_Hash_Head[0].state_hash);
			atomic_inc(&prot_counters[PROT_UDP] );
			break;
		case IPPROTO_ICMP:
			atomic_inc(&prot_counters[PROT_ICMP] );
			break;
	}
	return SUCCESS;
}

#if defined(CONFIG_NETFILTER_XT_MATCH_LAYER7)
#include <net/netfilter/nf_conntrack_acct.h>
#endif //#if defined(CONFIG_NETFILTER_XT_MATCH_LAYER7)

void __nf_ct_refresh_acct_proto(void *ct,
				      enum ip_conntrack_info ctinfo,
				      const void *skb,
				      unsigned long extra_jiffies,
				      int do_acct,
				      unsigned char proto,
				      void * extra1,
				      void * extra2)
{

	int event = 0;

	//IP_NF_ASSERT(ct->timeout.data == (unsigned long)ct);
	//IP_NF_ASSERT(skb);

	spin_lock_bh(&nf_conntrack_lock);

	/* Only update if this is not a fixed timeout */
	if (rtl_test_bit(ct, IPS_FIXED_TIMEOUT_BIT) == SUCCESS) {
#if defined(CONFIG_NETFILTER_XT_MATCH_LAYER7)
		if (do_acct) {
			struct nf_conn_counter *acct;

			acct = nf_conn_acct_find(ct);
			if (acct) {
				acct[CTINFO2DIR(ctinfo)].packets++;
				acct[CTINFO2DIR(ctinfo)].bytes +=
					rtl_get_skb_len(skb) - rtl_skb_network_offset(skb);
			}
		}
#endif //#if defined(CONFIG_NETFILTER_XT_MATCH_LAYER7)
		spin_unlock_bh(&nf_conntrack_lock);
		return;
	}

	/* If not in hash table, timer will not be active yet */
	if (rtl_test_bit(ct, IPS_CONFIRMED_BIT) == FAILED) {
		rtl_new_gc_set_ct_timeout_expires(ct, extra_jiffies);
		event = IPCT_REFRESH;
	} else {
		/* Need del_timer for race avoidance (may already be dying). */
		if (rtl_del_ct_timer(ct)) {
			rtl_new_gc_set_ct_timeout_expires(ct, jiffies + extra_jiffies);
			rtl_add_ct_timer(ct);
			event = IPCT_REFRESH;

			switch(proto) {
			case 6:
				rtl_list_move_tail(ct, PROT_TCP, extra2);
				break;
			case 17:
				if (rtl_new_gc_get_ct_udp_status(ct) & IPS_SEEN_REPLY) {
					rtl_list_move_tail(ct, PROT_UDP, 1);
				} else {
					rtl_list_move_tail(ct, PROT_UDP, 0);
				}
				break;
			}
		}
	}

	__nf_ct_refresh_acct_proto_hooks(ct, ctinfo, skb, do_acct, &event);

#if defined(CONFIG_NETFILTER_XT_MATCH_LAYER7)
	if (do_acct) {
		struct nf_conn_counter *acct;

		acct = nf_conn_acct_find(ct);
		if (acct) {
			acct[CTINFO2DIR(ctinfo)].packets++;
			acct[CTINFO2DIR(ctinfo)].bytes +=
				rtl_get_skb_len(skb) - rtl_skb_network_offset(skb);
		}
	}
#endif //#if defined(CONFIG_NETFILTER_XT_MATCH_LAYER7)

	spin_unlock_bh(&nf_conntrack_lock);

	/* must be unlocked when calling event cache */
	if (event)
		nf_conntrack_event_cache(event, ct);
	return;
}

char __conntrack_drop_check(void* tmp)
{
	uint32	sip, dip, sip2, dip2;
	uint32 	proto, sport, dport, sport2, dport2;

	proto=rtl_new_gc_get_ct_protonum(tmp, IP_CT_DIR_ORIGINAL);
	sport = rtl_new_gc_get_ct_port_by_dir(tmp, IP_CT_DIR_ORIGINAL, 0);
	dport = rtl_new_gc_get_ct_port_by_dir(tmp, IP_CT_DIR_ORIGINAL, 1);
	sport2 = rtl_new_gc_get_ct_port_by_dir(tmp, IP_CT_DIR_REPLY, 0);
	dport2 = rtl_new_gc_get_ct_port_by_dir(tmp, IP_CT_DIR_REPLY, 1);


	sip = rtl_new_gc_get_ct_ip_by_dir(tmp, IP_CT_DIR_ORIGINAL, 0);
	dip = rtl_new_gc_get_ct_ip_by_dir(tmp, IP_CT_DIR_ORIGINAL, 1);
	sip2 = rtl_new_gc_get_ct_ip_by_dir(tmp, IP_CT_DIR_REPLY, 0);
	dip2 = rtl_new_gc_get_ct_ip_by_dir(tmp, IP_CT_DIR_REPLY, 1);
	if ( (IS_CLASSD_ADDR(ntohl(dip))) ||
		(IS_CLASSD_ADDR(ntohl(dip2))) ||
		((sip==dip2)&&(dip==sip2)) ||
		((sport<htons(1024)) || (dport<htons(1024))||(sport2<htons(1024))||(dport2<htons(1024))) ||
		((sport==htons(8080)) || (dport==htons(8080))||(sport2==htons(8080))||(dport2==htons(8080)))) {
		return FAILED;
	} else {
		return SUCCESS;
	}
}
/* It's possible that no conntrack deleted due to large threshold value.
     Perhaps we can try to dynamically reduce the threshold if nothing can be removed.
*/
static inline int __drop_one_udp(void){
	int i;
	struct list_head *head, *ptr;
	struct nf_conn* tmp;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	spin_lock_bh(&nf_conntrack_lock);
#else
	read_lock_bh(&nf_conntrack_lock);
#endif
	for(i =0; i<drop_priority_max_idx; i++)
	{

		if(drop_priority[i].state <= TCP_CONNTRACK_MAX )	 //ramen--drop tcp conntrack
			continue;

	 	head = Udp_State_Hash_Head[drop_priority[i].state-UDP_UNREPLY].state_hash;
		if (!list_empty(head)) {
		    struct list_head *nn = NULL;
			list_for_each_safe(ptr, nn, head) {
				tmp=list_entry(ptr,struct nf_conn, state_tuple);

				if (tmp->drop_flag == -1) {
					tmp->drop_flag = __conntrack_drop_check(tmp);
				}
				if ( SUCCESS!=tmp->drop_flag) {
					continue;
				}

				if (rtl_del_ct_timer(tmp)) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
					spin_unlock_bh(&nf_conntrack_lock);
#else
					read_unlock_bh(&nf_conntrack_lock);
#endif
					rtl_death_action((void*)tmp);
					return 1;
				}
			}
		}
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	spin_unlock_bh(&nf_conntrack_lock);
#else
	read_unlock_bh(&nf_conntrack_lock);
#endif
       return 0;
}


static inline int __drop_one_tcp(void){
	int i;
	struct list_head *head, *ptr;
	struct nf_conn* tmp;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	spin_lock_bh(&nf_conntrack_lock);
#else
	read_lock_bh(&nf_conntrack_lock);
#endif
	for(i =0; i<drop_priority_max_idx; i++)
	{

		if(drop_priority[i].state >= TCP_CONNTRACK_MAX )	 //ramen--drop tcp conntrack
			continue;

	 	head = Tcp_State_Hash_Head[drop_priority[i].state].state_hash;
 		if (!list_empty(head)) {
		    struct list_head *nn = NULL;
			list_for_each_safe(ptr, nn, head) {
				tmp = list_entry(ptr,struct nf_conn, state_tuple);

				if (tmp->drop_flag == -1) {
					tmp->drop_flag = __conntrack_drop_check(tmp);
				}
				if ( SUCCESS!=tmp->drop_flag) {
					continue;
				}

				if (rtl_del_ct_timer(tmp)) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
					spin_unlock_bh(&nf_conntrack_lock);
#else
					read_unlock_bh(&nf_conntrack_lock);
#endif
					rtl_death_action((void*)tmp);
					return 1;
				}
			}
		}
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	spin_unlock_bh(&nf_conntrack_lock);
#else
	read_unlock_bh(&nf_conntrack_lock);
#endif
       return 0;
}

static inline int __drop_one_conntrack_process(struct list_head *head, int dropPrioIdx, int factor, int checkFlags, int tcpUdpState)
{
	struct list_head *ptr;
	struct nf_conn* tmp;
	int32 ret;
	int search_count;

	if(!list_empty(head))
	{
		search_count= 0;
		struct list_head *nn = NULL;
		list_for_each_safe(ptr, nn, head) {
			tmp=list_entry(ptr,struct nf_conn, state_tuple);

			search_count++;

			if (tmp->drop_flag == -1) {
				tmp->drop_flag = __conntrack_drop_check(tmp);
			}
			if ( SUCCESS!=tmp->drop_flag) {
				continue;
			}

#if (HZ==100)
			if ((((rtl_get_ct_timer_expires(tmp) - jiffies) >> (factor+7))<=drop_priority[dropPrioIdx].threshold) && rtl_del_ct_timer(tmp))
#elif (HZ==1000)
			if ((((rtl_get_ct_timer_expires(tmp) - jiffies) >> (factor+10))<=drop_priority[dropPrioIdx].threshold) && rtl_del_ct_timer(tmp))
#else
			#error "Please Check the HZ defination."
#endif
			{
				ret=__drop_one_conntrack_process_hooks1(tmp, dropPrioIdx, factor, checkFlags, tcpUdpState);
				if(ret==RTL_PS_HOOKS_BREAK)
				{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
					spin_unlock_bh(&nf_conntrack_lock);
#else
					read_unlock_bh(&nf_conntrack_lock);
#endif
					rtl_death_action((void*)tmp);
					return 1;
				}
				else if(ret==RTL_PS_HOOKS_RETURN)
				{
					return 1;
				}

				__drop_one_conntrack_process_hooks2(tmp, dropPrioIdx, factor, checkFlags, tcpUdpState);
			}

			if(search_count>MAX_NF_GC_SEARCH_CNT){
				break; //for next list
			}
		}
	}

	return 0;
}

static inline int __drop_one_conntrack(int factor, int checkFlags)
{
       //DEBUGP("enter the drop_one_tcp_conntrack.............\n");
	int 	i;
	struct list_head *ptr, *head;
	//struct nf_conn* tmp;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	spin_lock_bh(&nf_conntrack_lock);
#else
	read_lock_bh(&nf_conntrack_lock);
#endif
	for(i =0; i<drop_priority_max_idx; i++)
	{
		if(drop_priority[i].state < TCP_CONNTRACK_MAX )	 //ramen--drop tcp conntrack
		{
			head = Tcp_State_Hash_Head[drop_priority[i].state].state_hash;

			if(__drop_one_conntrack_process(head, i, factor, checkFlags, TCP_CONNTRACK_ESTABLISHED)==1)
				return 1;

		} else //ramen--drop udp conntrack
		{
 			head = Udp_State_Hash_Head[drop_priority[i].state-UDP_UNREPLY].state_hash;

			if(__drop_one_conntrack_process(head, i, factor, checkFlags, UDP_ASSURED)==1)
				return 1;
		}
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	spin_unlock_bh(&nf_conntrack_lock);
#else
	read_unlock_bh(&nf_conntrack_lock);
#endif
       return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
static inline int _isReservedL4Port(unsigned short port)
{
	//if((port < 1024) || (port == 8080))
	if((port == htons(80)) || (port == htons(8080)))
		return 1;

	return 0;
}

static inline int _isReservedIPAddr(unsigned int srcIP, unsigned int dstIP)
{
	if(IS_CLASSD_ADDR(ntohl(dstIP)) ||
		IS_BROADCAST_ADDR(ntohl(dstIP)) ||
		IS_ALLZERO_ADDR(ntohl(srcIP)))
		return 1;

	return 0;
}

int isReservedConntrack(const struct nf_conntrack_tuple *orig,
				   const struct nf_conntrack_tuple *repl)
{
	if(orig->dst.protonum==IPPROTO_ICMP)
	{
		return 1;
	}


	if(_isReservedIPAddr(orig->src.u3.ip, orig->dst.u3.ip) ||
		_isReservedIPAddr(repl->src.u3.ip, repl->dst.u3.ip))
	{
		return 1;
	}


	if(_isReservedL4Port(orig->src.u.all) ||
		_isReservedL4Port(orig->dst.u.all) ||
		_isReservedL4Port(repl->src.u.all) ||
		_isReservedL4Port(repl->dst.u.all))
	{
		return 1;
	}




	return 0;
}
#endif
int drop_one_conntrack(const struct nf_conntrack_tuple *orig,const struct nf_conntrack_tuple *repl)
{
	#if 0
	if(_isReservedL4Port(orig->src.u.all) ||
		_isReservedL4Port(orig->dst.u.all) ||
		_isReservedL4Port(repl->src.u.all) ||
		_isReservedL4Port(repl->dst.u.all))
	{
		return 1;
	}

	if(_isReservedIPAddr(orig->src.u3.ip, orig->dst.u3.ip) ||
		_isReservedIPAddr(repl->src.u3.ip, repl->dst.u3.ip))
	{
		return 1;
	}
	#endif

	if ((atomic_read(&_prot_limit[PROT_TCP]) < atomic_read(&prot_counters[PROT_TCP])) && __drop_one_tcp()) {
		if (rtl_newGC_session_status_flags==RTL_FP_SESSION_LEVEL_IDLE) {
			rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL3;
			rtl_newGC_session_status_time = jiffies+RTL_FP_SESSION_LEVEL3_INTERVAL;
		}
		return 1;
	}

	if ((atomic_read(&_prot_limit[PROT_UDP]) < atomic_read(&prot_counters[PROT_UDP])) && __drop_one_udp()) {
		if (rtl_newGC_session_status_flags==RTL_FP_SESSION_LEVEL_IDLE) {
			rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL3;
			rtl_newGC_session_status_time = jiffies+RTL_FP_SESSION_LEVEL3_INTERVAL;
		}
		return 1;
	}

#if 1
	if (__drop_one_conntrack(0, 1)||__drop_one_conntrack(2, 0)) {
		if (rtl_newGC_session_status_flags==RTL_FP_SESSION_LEVEL_IDLE) {
			rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL3;
			rtl_newGC_session_status_time = jiffies+RTL_FP_SESSION_LEVEL3_INTERVAL;
		}
		return 1;
	} else {
		// Note: util now, our code not go here during bt test!

		if (rtl_newGC_session_status_flags!=RTL_FP_SESSION_LEVEL1) {
			rtl_newGC_session_status_flags = RTL_FP_SESSION_LEVEL1;
			rtl_newGC_session_status_time = jiffies+RTL_FP_SESSION_LEVEL1_INTERVAL;
		}

		return 0;
	}
#else
	if ( __drop_one_conntrack(0) ||
	     __drop_one_conntrack(1) ||
	     __drop_one_conntrack(31))
		return 1;
	else
		return 0;
#endif
	return 0;
}

int32 rtl_nf_conn_GC_init(void)
{
	init_conntrack_state_hash();
	//proc_net_create ("conntrack_proto", 0, getinfo_conntrack_proto);
	prot_limit[PROT_ICMP] = 2;
	prot_limit[PROT_TCP] = 90;
	prot_limit[PROT_UDP] = 60;
	recalculate();

	rtl_nf_conn_GC_init_hooks();

	return SUCCESS;
}

