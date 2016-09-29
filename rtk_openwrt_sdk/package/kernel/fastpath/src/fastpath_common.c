//#if !defined(CONFIG_RTK_VLAN_SUPPORT)
#include <net/rtl/rtl_types.h>
#include <linux/version.h>
//#endif

#ifdef CONFIG_RTL_FAST_IPV6
#include <net/ipv6.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>
#include <linux/netfilter_ipv6/ip6_tables.h>
#endif
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>

#ifdef CONFIG_BRIDGE
#include <bridge/br_private.h>
#endif

#if defined (FAST_PPTP) || defined(FAST_L2TP)
	#include <net/ip.h>
#endif

#if defined(CONFIG_NET_SCHED)
#include <linux/netfilter_ipv4/ip_tables.h>
extern int gQosEnabled;
#endif
#if defined (CONFIG_RTL_HW_QOS_SUPPORT)
#include <net/rtl/features/rtl_sched_hooks.h>
#endif
#include <net/ip_fib.h>
#include <net/ip_vs.h>
#include <net/rtl/features/rtl_features.h>

#include <net/rtl/fastpath/fastpath_core.h>
#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
#include <net/rtl/features/rtl_features.h>
#endif
#include <net/rtl/rtl865x_nat.h>
#include <net/rtl/features/rtl_ps_log.h>

#include <net/rtl/rtl_nic.h>

#if defined(RTL_FASTPATH_FRAGMENT_SUPPORT)
#include <net/ip.h>
#include <net/icmp.h>
#include <linux/netfilter_bridge.h>
#endif


#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#include <net/netfilter/nf_conntrack_tuple.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>
#include <net/route.h>
#include <net/arp.h>
#ifdef CONFIG_RTL_FAST_IPV6
#include <net/ip6_route.h>
#endif
#endif

#include <net/rtl/rtl865x_fdb_api.h>

#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
static int	rtl_fp_gc_rx_threshold;
#endif
//#if 1//defined(CONFIG_RTL_ETH_DRIVER_REFINE)
//int fast_nat_fw = 1;
//#else
//static int fast_nat_fw = 1;
//#endif
extern int fast_nat_fw;
#include <linux/version.h>
#if defined (CONFIG_RTL_FAST_GRE)
extern int fast_gre_fw;
static struct proc_dir_entry *gre_proc=NULL;
static int fast_gre_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
	int len;
	int i;

	len = sprintf(page, "fast gre %s\n",(fast_gre_fw?"enable":"disable"));
	
	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;

	return len;
}

static int fast_gre_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
      char gre_tmp;

      if (count < 2)
	    return -EFAULT;

      if (buffer && !copy_from_user(&gre_tmp, buffer, 1)) 
	  {
	    	fast_gre_fw = gre_tmp - '0';

			return count;
      }
      return -EFAULT;
}

int fast_gre_init(void)
{
	gre_proc = create_proc_entry("fast_gre", 0, NULL);
	if (gre_proc) {
		gre_proc->read_proc = fast_gre_read_proc;
		gre_proc->write_proc = fast_gre_write_proc;
	}	
	fast_gre_fw=1;	
	return 0;	
}

int  fast_gre_exit(void)
{
	if (gre_proc) {
		remove_proc_entry("fast_gre", gre_proc);		
		gre_proc = NULL;
	}
	return 0;
}

#endif
#if defined(CONFIG_RTL_SPEED_MONITOR)
#include <net/rtl/features/rtl_dev_stats.h>
#endif
spinlock_t lock_rtl_feature;


#ifdef CONFIG_RTL_PPPOE_DIRECT_REPLY
extern int magicNum;
#if 0
int magicNum=-1;
//void (*tx_pppoe_request_hook)(struct sk_buff *skb) = NULL;
void clear_magicNum(struct sk_buff *pskb)
{
	//panic_printk("%s:%d\n",__FUNCTION__,__LINE__);
	magicNum = -1;
}
#endif

int is_pppoe_lcp_echo_req(struct sk_buff *skb)
{
	unsigned char *mac_hdr=NULL;
	if(skb->dev==NULL)
	{
		return 0;
	}
	
	if(strncmp(skb->dev->name, "ppp" ,3)==0)
	{
		return 0;
	}
	//printk("%s:%d,%s\n",__FUNCTION__,__LINE__,skb->dev->name);
	mac_hdr=rtl_skb_mac_header(skb);
	if(mac_hdr==NULL)
	{
		return 0;
	}
	
	if( (mac_hdr[12]!=0x88) || (mac_hdr[13]!=0x64) \
		||(mac_hdr[20]!=0xc0) || (mac_hdr[21]!=0x21) \
		|| (mac_hdr[22]!=0x09))
	{		
		return 0;
	}
	//panic_printk("%s:%d,rx pppoe lcp req\n",__FUNCTION__,__LINE__);	
	return 1;

}


#if 0
void extract_magicNum(struct sk_buff *skb)
{
	unsigned char *mac_hdr = skb->data;
	int i;
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
		return 0;
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
#endif

int direct_send_reply(struct sk_buff *skb)
{	

	unsigned char tmp[6];
	
	if(strncmp(skb->dev->name, "ppp" ,3)!=0)
	{
		skb_push(skb,14);
		
		// swap src and dst mac  	
		memcpy(tmp,skb->data,6);
		memcpy(skb->data,(skb->data+6),6);
		memcpy((skb->data+6),tmp,6);		
			
		// build ppp session header
		skb->data[22] = 0x0a;			//reply num
		memcpy((skb->data+26),&magicNum ,4);
		
		skb->dev->netdev_ops->ndo_start_xmit(skb,skb->dev);
		//panic_printk("%s:%d, direct_send_reply  tx\n",__FUNCTION__,__LINE__);		
		return 1;
	}
	return 0;
}


#endif

#if defined(IMPROVE_QOS) || defined(CONFIG_RTL_HW_QOS_SUPPORT)
#include <net/arp.h>
#include <net/rtl/rtl865x_netif.h>
//To query hardware address based on IP through arp table of dev
int arp_req_get_ha(__be32 queryIP, struct net_device *dev, unsigned char * resHwAddr)
{
	__be32 ip = queryIP;
	struct neighbour *neigh;
	int err = -ENXIO;

	neigh = neigh_lookup(&arp_tbl, &ip, dev);
	if (neigh) {
		read_lock_bh(&neigh->lock);
		memcpy(resHwAddr, neigh->ha, dev->addr_len);
		read_unlock_bh(&neigh->lock);
		neigh_release(neigh);
		err = 0;
	}
	//else
	//{
	//	resHwAddr=NULL;
	//}

	return err;
}
//EXPORT_SYMBOL(arp_req_get_ha);
#endif

#if defined(CONFIG_PROC_FS)
static struct proc_dir_entry *res1=NULL;
static int write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	unsigned char tmpbuf[16];
	struct net *net;

	if (count < 2)
		return -EFAULT;

	memset(tmpbuf, 0, sizeof(tmpbuf));
	if (buffer && !copy_from_user(tmpbuf, buffer, count))  {
		if (tmpbuf[0] == '2'&&count==2){
			/* first byte == 2, second byte == "enter" */
			for_each_net(net) {
                #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
				nf_conntrack_flush_report(net, 0, 0);		//clean conntrack table
				#else
				nf_conntrack_flush(net, 0, 0);		//clean conntrack table
				#endif
			}
			#if defined(CONFIG_RTL_LAYERED_DRIVER_L4)
			#if defined(CONFIG_RTL_8198) || defined (CONFIG_RTL_8196CT)
			rtl865x_nat_reinit();
			/* the following 2 values MUST set behind reinit nat module	*/
			//rtl_nat_expire_interval_update(RTL865X_PROTOCOL_TCP, tcp_get_timeouts_by_state(TCP_CONNTRACK_ESTABLISHED));
			//rtl_nat_expire_interval_update(RTL865X_PROTOCOL_UDP, nf_ct_udp_timeout>nf_ct_udp_timeout_stream?nf_ct_udp_timeout:nf_ct_udp_timeout_stream);
			#endif
			#endif
		}else{
			sscanf(tmpbuf, "%d", &fast_nat_fw);
			#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
			if (fast_nat_fw>2) {
				rtl_fp_gc_rx_threshold = fast_nat_fw;
			}
			#endif
		}
		return count;
	}

	return -EFAULT;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int read_proc(struct seq_file *s, void *v)
{
	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	seq_printf(s, "fastpath %s, GC_RX_Count %d, Status: %d\n", fast_nat_fw!=0?"Enabled":"Disabled", rtl_fp_gc_rx_threshold, rtl_newGC_session_status_flags);
	#else
	seq_printf(s, "fastpath: [%d]\n", fast_nat_fw+10);
	#endif

	return 0;
}

int fastpath_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, read_proc, NULL));
}

static ssize_t fastpath_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return write_proc(file, userbuf,count, off);
}

struct file_operations fastpath_proc_fops = {
        .open           = fastpath_single_open,
	 .write		= fastpath_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#else
static int read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
	int len = 0;
	
	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	len = sprintf(page, "fastpath %s, GC_RX_Count %d, Status: %d\n", fast_nat_fw!=0?"Enabled":"Disabled", rtl_fp_gc_rx_threshold, rtl_newGC_session_status_flags);
	#else
	len = sprintf(page, "fastpath: [%d]\n", fast_nat_fw+10);
	#endif
	len = fastpath_dump_napt_entry_num(page, len);

	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
}
#endif

#if defined(FAST_PATH_SPI_ENABLED)
int fast_spi =1;
static struct proc_dir_entry *res_spi=NULL;

static int spi_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	unsigned char tmpbuf[16];

	memset(tmpbuf, 0, sizeof(tmpbuf));
	if (buffer && !copy_from_user(tmpbuf, buffer, count))
		sscanf(tmpbuf, "%d", &fast_spi);

	return count;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int spi_read_proc(struct seq_file *s, void *v)
{

	seq_printf(s, "fast_spi %s\n", fast_spi==1?"Enabled":"Disabled");

	return 0;
}

int fastspi_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, spi_read_proc, NULL));
}

static ssize_t fastspi_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return spi_write_proc(file, userbuf,count, off);
}

struct file_operations fastspi_proc_fops = {
        .open           = fastspi_single_open,
	 .write		= fastspi_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#else
static int spi_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
	int len = 0;

	len = sprintf(page, "fast_spi %s\n", fast_spi==1?"Enabled":"Disabled");

	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;

}
#endif
#endif

#endif

#if defined(RTL_FASTPATH_FRAGMENT_SUPPORT)
static void rtl_ip_copy_metadata(struct sk_buff *to, struct sk_buff *from)
{
	to->pkt_type = from->pkt_type;
	to->priority = from->priority;
	to->protocol = from->protocol;
	dst_release(to->dst);
	to->dst = dst_clone(from->dst);
	to->dev = from->dev;
	to->mark = from->mark;

	/* Copy the flags to each fragment. */
	IPCB(to)->flags = IPCB(from)->flags;

#if (defined(CONFIG_RTL_QOS_PATCH) || defined(CONFIG_RTK_VOIP_QOS)|| defined(CONFIG_RTK_VLAN_WAN_TAG_SUPPORT))&& defined(CONFIG_RTL_819X) 
        to->srcPhyPort = from->srcPhyPort;
#endif

#ifdef CONFIG_NET_SCHED
	to->tc_index = from->tc_index;
#endif
	nf_copy(to, from);
#if defined(CONFIG_NETFILTER_XT_TARGET_TRACE) || \
    defined(CONFIG_NETFILTER_XT_TARGET_TRACE_MODULE)
	to->nf_trace = from->nf_trace;
#endif
#if defined(CONFIG_IP_VS) || defined(CONFIG_IP_VS_MODULE)
	to->ipvs_property = from->ipvs_property;
#endif
	skb_copy_secmark(to, from);
}

int rtl_ip_fragment_for_fastpath(struct sk_buff *skb, int (*output)(struct sk_buff *))
{
	struct iphdr *iph;
	int raw = 0;
	int ptr;
	struct net_device *dev;
	struct sk_buff *skb2;
	unsigned int mtu, hlen, left, len, ll_rs, pad;
	int offset;
	__be16 not_last_frag;
	struct rtable *rt = skb->rtable;
	int err = -1;

	dev = rt->u.dst.dev;
	/*
	 *	Point into the IP datagram header.
	 */
	iph = ip_hdr(skb);

	if (unlikely((iph->frag_off & htons(IP_DF)) && !skb->local_df)) {
		IP_INC_STATS(dev_net(dev), IPSTATS_MIB_FRAGFAILS);
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
			  htonl(dst_mtu(skb->dst)));
		kfree_skb(skb);
		return -EMSGSIZE;
	}

		/*
	 *	Setup starting values.
	 */

	hlen = iph->ihl * 4;
	mtu = dst_mtu(&rt->u.dst) - hlen;	/* Size of data space */
	IPCB(skb)->flags |= IPSKB_FRAG_COMPLETE;
	
	left = skb->len - hlen;		/* Space per frame */
	ptr = raw + hlen;		/* Where to start from */

	/* for bridged IP traffic encapsulated inside f.e. a vlan header,
	 * we need to make room for the encapsulating header
	 */
	pad = nf_bridge_pad(skb);
	ll_rs = LL_RESERVED_SPACE_EXTRA(rt->u.dst.dev, pad);
	mtu -= pad;

	/*
	 *	Fragment the datagram.
	 */
	offset = (ntohs(iph->frag_off) & IP_OFFSET) << 3;
	not_last_frag = iph->frag_off & htons(IP_MF);

	/*
	 *	Keep copying data until we run out.
	 */
	while (left > 0) {
		len = left;
		/* IF: it doesn't fit, use 'mtu' - the data space left */
		if (len > mtu)
			len = mtu;
		/* IF: we are not sending upto and including the packet end
		   then align the next start on an eight byte boundary */
		if (len < left)	{
			len &= ~7;
		}
		/*
		 *	Allocate buffer.
		 */

		if ((skb2 = alloc_skb(len+hlen+ll_rs, GFP_ATOMIC)) == NULL) {
			NETDEBUG(KERN_INFO "IP: frag: no memory for new fragment!\n");
			err = -ENOMEM;
			goto fail;
		}

		/*
		 *	Set up data on packet
		 */

		rtl_ip_copy_metadata(skb2, skb);
		skb_reserve(skb2, ll_rs);
		skb_put(skb2, len + hlen);
		skb_reset_network_header(skb2);
		skb2->transport_header = skb2->network_header + hlen;

		/*
		 *	Charge the memory for the fragment to any owner
		 *	it might possess
		 */

		if (skb->sk)
			skb_set_owner_w(skb2, skb->sk);

		/*
		 *	Copy the packet header into the new buffer.
		 */

		skb_copy_from_linear_data(skb, skb_network_header(skb2), hlen);

		/*
		 *	Copy a block of the IP datagram.
		 */
		if (skb_copy_bits(skb, ptr, skb_transport_header(skb2), len))
			BUG();
		left -= len;

		/*
		 *	Fill in the new header fields.
		 */
		iph = ip_hdr(skb2);
		iph->frag_off = htons((offset >> 3));

		/* ANK: dirty, but effective trick. Upgrade options only if
		 * the segment to be fragmented was THE FIRST (otherwise,
		 * options are already fixed) and make it ONCE
		 * on the initial skb, so that all the following fragments
		 * will inherit fixed options.
		 */
		if (offset == 0)
			ip_options_fragment(skb);

		/*
		 *	Added AC : If we are fragmenting a fragment that's not the
		 *		   last fragment then keep MF on each bit
		 */
		if (left > 0 || not_last_frag)
			iph->frag_off |= htons(IP_MF);
		ptr += len;
		offset += len;

		/*
		 *	Put this fragment into the sending queue.
		 */
		iph->tot_len = htons(len + hlen);

		ip_send_check(iph);

		/*output can handle skb2, xmit it or kfree it, so do not need to care the
		value of err.*/
		err = output(skb2);
		//panic_printk("%s[%d], err is %d, id is %d\n", __FUNCTION__, __LINE__, err, iph->id);
		//if (err == 0)
			//goto fail;
		
		IP_INC_STATS(dev_net(dev), IPSTATS_MIB_FRAGCREATES);
	}
	kfree_skb(skb);
	IP_INC_STATS(dev_net(dev), IPSTATS_MIB_FRAGOKS);
	return 1;
fail:
	kfree_skb(skb);
	IP_INC_STATS(dev_net(dev), IPSTATS_MIB_FRAGFAILS);
	return err;
}
#endif

#if	defined(CONFIG_RTL_HW_QOS_SUPPORT)
int32 rtl_qosGetSkbMarkByNaptEntry(rtl865x_napt_entry *naptEntry, rtl865x_qos_mark *qosMark, struct sk_buff *pskb)
{
	struct iphdr *iph;
	struct tcphdr *tcphupuh;  //just keep one , don't care tcp or udp //
	u_int ori_saddr, ori_daddr;
	u_short ori_sport, ori_dport;
	struct net_device	*lanDev, *wanDev;
	//struct dst_entry *dst_tmp;
	unsigned char oriSrcMac[6],oriDstMac[6],resMac[14];
	u_short proto;
	unsigned char pppProto[2],ipProto[2];
	__u32 oriSkbMark;
	unsigned long irq_flags;
	uint32 preMark, postMark;
    unsigned long lock_flags;

	if(pskb==NULL)
		return FAILED;

	//initial
	pppProto[0]=0x00;
	pppProto[1]=0x21;
	ipProto[0]=0x08;
	ipProto[1]=0x00;

	lanDev=rtl865x_getLanDev();
	wanDev=rtl865x_getWanDev();
	proto = ntohs(pskb->protocol);
	iph = ip_hdr(pskb);
	if(iph==NULL)
	{
		return FAILED;
	}
	tcphupuh = (struct tcphdr*)((__u32 *)iph + iph->ihl);

	if(eth_hdr(pskb)==NULL)
	{
		return FAILED;
	}
	//To bak origal protol mac
	memcpy(oriSrcMac,eth_hdr(pskb)->h_source,ETH_ALEN);
	memcpy(oriDstMac,eth_hdr(pskb)->h_dest,ETH_ALEN);

	//Bak orignal skb mark
	oriSkbMark=pskb->mark;

	//check ip-based qos rule at iptables mangle table
	//To record original info
	ori_saddr=iph->saddr;
	ori_sport=tcphupuh->source;
	ori_daddr=iph->daddr;
	ori_dport=tcphupuh->dest;

	/* for dst mac match, please refer to the xt_mac.c */
	
	//dst_tmp = skb_dst(pskb);
	//pskb->dst = NULL;
	//skb_dst_set(pskb,NULL);
    spin_lock_irqsave(&lock_rtl_feature,lock_flags);
	rtl_store_skb_dst(pskb);
    if(!dst_tmp&&rtl_ip_route_input(pskb, iph->daddr, iph->saddr, iph->tos))
        return FAILED;
#if defined (CONFIG_OPENWRT_SDK)
        if (proto == ETH_P_IP)
		pskb->bypass_connmark = 1;
#endif
	//For uplink
#if defined(CONFIG_NET_SCHED)
	preMark = 0;
	postMark= 0;
	{
	//Replace source addr to check uplink mark
	iph->saddr=naptEntry->intIp;
	tcphupuh->source=naptEntry->intPort;
	iph->daddr=naptEntry->remIp;
	tcphupuh->dest=naptEntry->remPort;

	memset(resMac,0,14);
	if((lanDev!=NULL)&&(arp_req_get_ha(naptEntry->intIp,lanDev,resMac)==0))
	{
		//Patch for pppoe wantype: run udp chariot
		//bak skb mac header
		if((memcmp(pskb->data-2, pppProto,2)==0)	//equal 0x0021
			&&(skb_mac_header_was_set(pskb)==1)
			&&(eth_hdr(pskb)->h_proto!=ntohs(0x0800))) //not equal to 0x0800
		{
				skb_set_mac_header(pskb, -22);
		}

		//Replace source mac addr to check uplink mark
		memcpy(eth_hdr(pskb)->h_source,resMac, ETH_ALEN);
		memcpy(eth_hdr(pskb)->h_dest,lanDev->dev_addr, ETH_ALEN);
	}

	pskb->mark=0;//initial
#if defined (CONFIG_OPENWRT_SDK)
	if(proto == ETH_P_IP){
		(list_empty(&nf_hooks[PF_INET][NF_IP_FORWARD]))?: \
			ipt_do_table(pskb, NF_IP_FORWARD, lanDev,wanDev,\
			dev_net(lanDev)->ipv4.iptable_mangle);
		DEBUGP_API("[%s][%d]:[%s][%s][%d]\n", __FUNCTION__, __LINE__,
						lanDev?lanDev->name:"NULL",
						wanDev?wanDev->name:"NULL",
						 pskb->mark);
	}
#else
	if(proto == ETH_P_IP){
		(list_empty(&nf_hooks[PF_INET][NF_IP_PRE_ROUTING]))?: \
			ipt_do_table(pskb, NF_IP_PRE_ROUTING, lanDev,wanDev,\
			dev_net(lanDev)->ipv4.iptable_mangle);
	}
#endif
	DEBUGP_API("[%s][%d]:[%s][%s][%d]\n", __FUNCTION__, __LINE__,
					lanDev?lanDev->name:"NULL",
					wanDev?wanDev->name:"NULL",
					pskb->mark);
	preMark = pskb->mark;

	//Replace dest addr to check uplink mark
	iph->saddr=naptEntry->extIp;
	tcphupuh->source=naptEntry->extPort;
	iph->daddr=naptEntry->remIp;
	tcphupuh->dest=naptEntry->remPort;

	memset(resMac,0,14);
	if((wanDev!=NULL)&&(arp_req_get_ha(naptEntry->remIp,wanDev,resMac)==0))
	{
		//Patch for pppoe wantype: run udp chariot
		//bak skb mac header
		if((memcmp(pskb->data-2, pppProto,2)==0)	//equal 0x0021
			&&(skb_mac_header_was_set(pskb)==1)
			&&(eth_hdr(pskb)->h_proto!=ntohs(0x0800))) //not equal to 0x0800
		{
				skb_set_mac_header(pskb, -22);
		}

		//Replace source mac addr to check uplink mark
		memcpy(eth_hdr(pskb)->h_dest,resMac, ETH_ALEN);
		memcpy(eth_hdr(pskb)->h_source,wanDev->dev_addr, ETH_ALEN);
	}

	pskb->mark=0;//initial
#if defined (CONFIG_OPENWRT_SDK)
	if(proto == ETH_P_IP){
		(list_empty(&nf_hooks[PF_INET][NF_IP_FORWARD]))?: \
			ipt_do_table(pskb, NF_IP_FORWARD, lanDev, wanDev,\
			dev_net(wanDev)->ipv4.iptable_mangle);
		DEBUGP_API("[%s][%d]:[%s][%s][%d]\n", __FUNCTION__, __LINE__,
						lanDev?lanDev->name:"NULL",
						wanDev?wanDev->name:"NULL",
						 pskb->mark);
	}
#else
	if(proto == ETH_P_IP){
		(list_empty(&nf_hooks[PF_INET][NF_IP_POST_ROUTING]))?: \
			ipt_do_table(pskb, NF_IP_POST_ROUTING, lanDev, wanDev,\
			dev_net(wanDev)->ipv4.iptable_mangle);
	}
#endif	
	DEBUGP_API("[%s][%d]:[%s][%s][%d]\n", __FUNCTION__, __LINE__,
					lanDev?lanDev->name:"NULL",
					wanDev?wanDev->name:"NULL",
					pskb->mark);
		postMark= pskb->mark;
	}

#if defined (CONFIG_OPENWRT_SDK)
	qosMark->uplinkMark=preMark;
#else
	qosMark->uplinkMark=(postMark?postMark:preMark);
#endif
#endif

	//for downlink
#if defined(CONFIG_NET_SCHED)
	preMark = 0;
	postMark = 0;
	{
		//Replace source addr to check uplink mark
		iph->saddr=naptEntry->remIp;
		tcphupuh->source=naptEntry->remPort;
		iph->daddr=naptEntry->extIp;
		tcphupuh->dest=naptEntry->extPort;

		memset(resMac,0,14);
		if((wanDev!=NULL)&&(arp_req_get_ha(naptEntry->remIp,wanDev,resMac)==0))
		{
			//Patch for pppoe wantype: run udp chariot
			if((memcmp(pskb->data-2, pppProto,2)==0)	//equal 0x0021
				&&(skb_mac_header_was_set(pskb)==1)
				&&(eth_hdr(pskb)->h_proto!=ntohs(0x0800))) //not equal to 0x0800
			{
				skb_set_mac_header(pskb, -22);
			}

			//Replace source mac addr to check uplink mark
			memcpy(eth_hdr(pskb)->h_source,resMac, ETH_ALEN);
			memcpy(eth_hdr(pskb)->h_dest, wanDev->dev_addr, ETH_ALEN);
		}

		pskb->mark=0;//initial
#if defined (CONFIG_OPENWRT_SDK)
		if(proto == ETH_P_IP){
			(list_empty(&nf_hooks[PF_INET][NF_IP_FORWARD]))?: \
				ipt_do_table(pskb, NF_IP_FORWARD, wanDev,lanDev,\
				dev_net(wanDev)->ipv4.iptable_mangle);
			DEBUGP_API("[%s][%d]:[%s][%s][%d]\n", __FUNCTION__, __LINE__,
						lanDev?lanDev->name:"NULL",
						wanDev?wanDev->name:"NULL",
						 pskb->mark);
		}
#else
		if(proto == ETH_P_IP){
			(list_empty(&nf_hooks[PF_INET][NF_IP_PRE_ROUTING]))?: \
				ipt_do_table(pskb, NF_IP_PRE_ROUTING, wanDev,lanDev,\
				dev_net(wanDev)->ipv4.iptable_mangle);
		}
#endif		
		DEBUGP_API("[%s][%d]:[%s][%s][%d]\n", __FUNCTION__, __LINE__,
						lanDev?lanDev->name:"NULL",
						wanDev?wanDev->name:"NULL",
						 pskb->mark);
		preMark = pskb->mark;

		//Replace dest addr to check uplink mark
		iph->saddr=naptEntry->remIp;
		tcphupuh->source=naptEntry->remPort;
		iph->daddr=naptEntry->intIp;
		tcphupuh->dest=naptEntry->intPort;

		memset(resMac,0,14);
		if ((lanDev!=NULL)&&(arp_req_get_ha(naptEntry->intIp,lanDev,resMac)==0))
		{
			//Patch for pppoe wantype: run udp chariot
			if((memcmp(pskb->data-2, pppProto,2)==0)	//equal 0x0021
				&&(skb_mac_header_was_set(pskb)==1)
				&&(eth_hdr(pskb)->h_proto!=ntohs(0x0800))) //not equal to 0x0800
			{
				skb_set_mac_header(pskb, -22);
			}
			//Replace dest mac addr and  hh data mac to check uplink mark
			memcpy(eth_hdr(pskb)->h_dest,resMac,ETH_ALEN);
			memcpy(eth_hdr(pskb)->h_source, lanDev->dev_addr, ETH_ALEN);
		}
		pskb->mark=0;//initial
#if defined (CONFIG_OPENWRT_SDK)
		if(proto == ETH_P_IP){
			(list_empty(&nf_hooks[PF_INET][NF_IP_FORWARD]))?: \
				ipt_do_table(pskb, NF_IP_FORWARD, wanDev, lanDev,\
				dev_net(lanDev)->ipv4.iptable_mangle);
			DEBUGP_API("[%s][%d]:[%s][%s][%d]\n", __FUNCTION__, __LINE__,
						lanDev?lanDev->name:"NULL",
						wanDev?wanDev->name:"NULL",
						pskb->mark);
		}
#else
		if(proto == ETH_P_IP){
			(list_empty(&nf_hooks[PF_INET][NF_IP_POST_ROUTING]))?: \
				ipt_do_table(pskb, NF_IP_POST_ROUTING, wanDev, lanDev,\
				dev_net(lanDev)->ipv4.iptable_mangle);
		}
#endif		
		DEBUGP_API("[%s][%d]:[%s][%s][%d]\n", __FUNCTION__, __LINE__,
						lanDev?lanDev->name:"NULL",
						wanDev?wanDev->name:"NULL",
						pskb->mark);
		postMark= pskb->mark;
	}
#if defined (CONFIG_OPENWRT_SDK)
	qosMark->downlinkMark=postMark;
#else
	qosMark->downlinkMark=(postMark?postMark:preMark);
#endif
#endif

#if defined (CONFIG_OPENWRT_SDK)
	if (proto == ETH_P_IP)
		pskb->bypass_connmark = 0;
#endif
	//Back to original value
	//Back to orignal protol mac
	memcpy(eth_hdr(pskb)->h_source,oriSrcMac, ETH_ALEN);
	memcpy(eth_hdr(pskb)->h_dest,oriDstMac, ETH_ALEN);

	//Back to original skb mark
	pskb->mark=oriSkbMark;

	//back to original info
	iph->saddr=ori_saddr;
	tcphupuh->source=ori_sport;
	iph->daddr=ori_daddr;
	tcphupuh->dest=ori_dport;

	//pskb->dst = dst_tmp;
	//skb_dst_set(pskb,dst_tmp);
	rtl_set_skb_dst(pskb);
    spin_unlock_irqrestore(&lock_rtl_feature,lock_flags);
	if(lanDev)
		dev_put(lanDev);

	if(wanDev)
		dev_put(wanDev);

	return SUCCESS;
}
#endif


void fastpath_set_qos_mark(struct sk_buff *skb, unsigned int preRouteMark, unsigned int postRouteMark)
{
	if(skb->mark == 0)
		skb->mark = (postRouteMark?postRouteMark:preRouteMark);
}

#if	defined(FAST_L2TP)
static inline void enter_fast_path_fast_l2tp_pre_process(struct sk_buff *skb)
{
	struct net_device *l2tprx_dev;
	struct in_device *skbIn_dev;
	struct net_device *skbNetDevice;

	if(fast_l2tp_fw){
		l2tprx_dev = skb->dev;
		skbIn_dev = (struct in_device *)skb->dev->ip_ptr;
		if(skbIn_dev == NULL){
			if ((skbNetDevice = __dev_get_by_name(&init_net,l2tprx_dev->name)) != NULL){
				if((skbIn_dev= (struct in_device*)skbNetDevice->ip_ptr) != NULL)
					skb->dev->ip_ptr = (void *)skbIn_dev;
			}
		}
	}
}
#endif

#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
static inline int rtl_fp_gc_status_check_priority(uint32 sIp, uint32 dIp, uint16 sPort, uint16 dPort)
{
	extern unsigned int	_br0_ip;

	#define	RTL_FP_GC_HIGH_PRIORITY_PORT_CHECK(__FP__GC__PORT__)	((sPort!=(__FP__GC__PORT__))&&dPort!=(__FP__GC__PORT__))

	if ( (dIp!=_br0_ip && sIp!=_br0_ip) &&
		(sPort>htons(1024) && dPort>htons(1024)) &&
		(sPort!=htons(8080) && dPort!=htons(8080)) &&
		(!(IS_CLASSD_ADDR(ntohl(dIp)))) &&
		(!(IS_BROADCAST_ADDR(ntohl(dIp)))) &&
		(!(IS_ALLZERO_ADDR(ntohl(sIp)))))
	{
		return NET_RX_DROP;
	}
	else
		return NET_RX_SUCCESS;
	#undef	RTL_FP_GC_HIGH_PRIORITY_PORT_CHECK
}

static inline int rtl_fp_gc_status_check(struct iphdr *iph, struct tcphdr *tcph, struct sk_buff *skb)
{
	uint32 sIp, dIp;
	uint16 sPort, dPort;
	int	ret;
	static int	rx_count=0;

	ret = NET_RX_SUCCESS;
	if ((rtl_newGC_session_status_flags!=RTL_FP_SESSION_LEVEL_IDLE)&&time_after_eq(rtl_newGC_session_status_time, jiffies)) {
		sIp = iph->saddr;
		dIp = iph->daddr;
		sPort = tcph->source;
		dPort = tcph->dest;
		if (rtl_fp_gc_status_check_priority(sIp, dIp, sPort, dPort)==NET_RX_DROP) {
			kfree_skb(skb);
			ret = NET_RX_DROP;
		}
	} else {
		if (rtl_newGC_session_status_flags==RTL_FP_SESSION_LEVEL3) {
			if ((rx_count++)>rtl_fp_gc_rx_threshold) {
				rx_count = 0;
				rtl_newGC_session_status_time = jiffies+RTL_FP_SESSION_LEVEL3_INTERVAL;
			}
		} else if (rtl_newGC_session_status_flags==RTL_FP_SESSION_LEVEL1) {
			rx_count += RTL_FP_SESSION_LEVEL1_RX_WEIGHT;
			if ((rx_count)>rtl_fp_gc_rx_threshold) {
				rx_count = 0;
				rtl_newGC_session_status_time=jiffies+RTL_FP_SESSION_LEVEL1_INTERVAL;
			}
		}
	}

	return ret;
}
#endif

int fast_path_pre_process_check(struct iphdr *iph, struct tcphdr *tcphupuh, struct sk_buff *skb)
{
	#if	defined(FAST_L2TP)
	enter_fast_path_fast_l2tp_pre_process(skb);
	#endif

	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	if ((iph->protocol==IPPROTO_TCP) &&
		(tcphupuh->syn) && (!(tcphupuh->ack))) {
		return rtl_fp_gc_status_check(iph, tcphupuh, skb);
	}
	#endif

	return NET_RX_PASSBY;
}



extern int fast_l2tp_to_wan_hook(void *skb);
static inline int enter_fast_path_fast_l2tp_post_process(struct sk_buff *skb)
{
#if	defined(FAST_L2TP)
	if (fast_l2tp_fw && skb->dev && (!memcmp(skb->dev->name, RTL_FASTPATH_PPP0_DEV_NAME, 4)) )
	{
		#if defined(RTL_FASTPATH_FRAGMENT_SUPPORT)
		if (skb->len > dst_mtu(skb->dst)) 
		{
			if (fast_l2tp_to_wan_check(skb) == 0)
				return NET_RX_SUCCESS;
			/*Acturally, rtl_ip_fragment_for_fastpath will never return 0.*/
			if (rtl_ip_fragment_for_fastpath(skb, fast_l2tp_to_wan2))
				return NET_RX_DROP;
		} else
		#endif
		if (fast_l2tp_to_wan_hook((void*)skb)) // success
		{
			return NET_RX_DROP;
		}
	}
#endif	
	return NET_RX_SUCCESS;
}


static inline int enter_fast_path_fast_pppoe_post_process(struct sk_buff *skb)
{
	
#if defined(CONFIG_RTL_FAST_PPPOE)
	#if defined(RTL_FASTPATH_FRAGMENT_SUPPORT)
	if (skb->len > dst_mtu(skb->dst)) 
	{
		if (fast_pppoe_xmit_check(skb) == 0)
			return NET_RX_SUCCESS;
		/*rtl_ip_fragment_for_fastpath always will not return 0 now, skb will be
		xmit or kfree in this func, so the return value is NET_RX_DROP.*/
		if (rtl_ip_fragment_for_fastpath(skb, fast_pppoe_xmit2))
			return NET_RX_DROP;
	} else
	#endif
	if (fast_pppoe_xmit(skb)) // success
	{
		return NET_RX_DROP;
	}
#endif
	return NET_RX_SUCCESS;
}


#if defined(FASTPTH_INDEPENDENCE_KERNEL)
struct dst_entry *dst_tmp = NULL;
#ifdef CONFIG_RTL_FAST_IPV6
struct dst_entry *ipv6_dst_tmp = NULL;
#endif

void rtl_dev_put(struct net_device *dev)
{
    return dev_put(dev);
}

/*As these API are used in fastpath, so skb will be check as valid, I will not check
skb again*/

unsigned int rtl_get_skb_len(struct sk_buff *skb)
{
	return skb->len;
}

__be16 rtl_get_skb_protocol(struct sk_buff *skb)
{
	return skb->protocol;
}

void rtl_set_skb_protocol(struct sk_buff *skb,__be16 protocol)
{
	skb->protocol=protocol;
}

unsigned char rtl_get_skb_type(struct sk_buff *skb)
{
	return skb->pkt_type;
}


__wsum rtl_get_skb_csum(struct sk_buff *skb)
{
	return skb->csum;
}


unsigned char *rtl_get_skb_data(struct sk_buff* skb)
{
	return skb->data;
}


void rtl_set_skb_data(struct sk_buff *skb, int offset, int action)
{
	if(action == 1)
		skb->data -= offset;
	else if(action == 0)
		skb->data += offset;

	return;
}

unsigned char *rtl_skb_mac_header(struct sk_buff * skb)
{
	return skb_mac_header(skb);
}

void rtl_skb_set_mac_header(struct sk_buff *skb, int offset)
{
	return skb_set_mac_header(skb, offset);
}


int rtl_skb_mac_header_was_set(struct sk_buff *skb)
{
	return skb_mac_header_was_set(skb);
}


void rtl_set_skb_dmac(struct sk_buff *skb, void *device)
{
	struct net_device *dev = (struct net_device *)device;

	memcpy(eth_hdr(skb)->h_dest, dev->dev_addr, ETH_ALEN);

	return;
}

void rtl_set_skb_smac(struct sk_buff *skb, void *device)
{
	struct net_device *dev = (struct net_device *)device;

	memcpy(eth_hdr(skb)->h_source, dev->dev_addr, ETH_ALEN);

	return;
}

unsigned char *rtl_skb_network_header(struct sk_buff * skb)
{
	return skb_network_header(skb);
}


void rtl_skb_set_network_header(struct sk_buff * skb,const int offset)
{
	skb_set_network_header(skb,offset);
}

void rtl_skb_reset_network_header(struct sk_buff *skb)
{
	return skb_reset_network_header(skb);
}

void rtl_set_skb_network_header(struct sk_buff * skb, unsigned char *network_header)
{
	skb->network_header=network_header;
}

unsigned char *rtl_skb_transport_header(struct sk_buff * skb)
{
	return skb_transport_header(skb);
}

void rtl_skb_set_transport_header(struct sk_buff * skb,const int offset)
{
	skb_set_transport_header(skb,offset);
}

void rtl_skb_reset_transport_header(struct sk_buff *skb)
{
	return skb_reset_transport_header(skb);
}

void rtl_set_skb_transport_header(struct sk_buff * skb, unsigned char *transport_header)
{
	skb->transport_header=transport_header;
}


unsigned char *rtl_skb_pull(struct sk_buff *skb, unsigned int len)
{
	return skb_pull(skb,len);
}

unsigned char *rtl_skb_push(struct sk_buff *skb, unsigned int len)
{
	return skb_push(skb,len);
}


int rtl_ppp_proto_check(struct sk_buff *skb, unsigned char* ppp_proto)
{
	if(memcmp(skb->data-2, ppp_proto,2)==0)
		return 1;
	else
		return 0;
}

unsigned int rtl_ipt_do_table(struct sk_buff * skb, unsigned int hook, void *in, void *out)
{
	struct net_device *out_dev = (struct net_device *)out;
	struct net_device *in_dev;

	if(in == NULL)
		in_dev = skb->dev;
	else
		in_dev = (struct net_device *)in;

	return ipt_do_table(skb, hook, in_dev, out_dev, dev_net(skb->dev)->ipv4.iptable_mangle);
}

int rtl_ip_route_input(struct sk_buff  *skb, __be32 daddr, __be32 saddr, u8 tos)
{
	return ip_route_input(skb, daddr, saddr, tos, skb->dev);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static void rtl_neigh_probe(struct neighbour *neigh)
	__releases(neigh->lock)
{
	struct sk_buff *skb = skb_peek(&neigh->arp_queue);
	/* keep skb alive even if arp_queue overflows */
	if (skb)
		skb = skb_copy(skb, GFP_ATOMIC);
	write_unlock(&neigh->lock);
	neigh->ops->solicit(neigh, skb);
	atomic_inc(&neigh->probes);
	kfree_skb(skb);
}
extern void neigh_probe(struct neighbour *neigh);
int rtl_skb_dst_check(struct sk_buff *skb, unsigned long dip,void *ct_tmp,uint8 type)
{
	int ret = SUCCESS;
	struct dst_entry *dst = skb_dst(skb);
	struct rtable *rt = (struct rtable *)dst;
	struct net_device *dev = dst->dev;
	struct neighbour *neigh;
	u32 nexthop;
	struct nf_conn *ct = (struct nf_conn *)ct_tmp;
    /*
	if (rtl_get_ct_protonum(ct, IP_CT_DIR_ORIGINAL)  == IPPROTO_UDP) {
		if (!(rtl_get_ct_udp_status(ct) & IPS_ASSURED)) {
		    return FAILED;
		}
	}
    */
	if (rt == NULL)
		return FAILED;

#if !defined(RTL_FASTPATH_FRAGMENT_SUPPORT)
    if(skb->len>dst_mtu(dst))
        return FAILED;
#endif

    rcu_read_lock_bh();
	nexthop = (__force u32) rt_nexthop(rt, dip);
	neigh = __ipv4_neigh_lookup_noref(dev, nexthop);
	/*linux kernel 3.4 struct hh_cache is in struct neighbour*/
    if(neigh != NULL)
        write_lock(&neigh->lock);
	if ( (neigh==NULL) ||!(neigh->nud_state & NUD_CONNECTED))
	{
        if((neigh!=NULL)&&!(neigh->nud_state & NUD_CONNECTED))
            rtl_neigh_probe(neigh);
        else if(neigh != NULL)
            write_unlock(&neigh->lock);
		ret = FAILED;
        rcu_read_unlock_bh();
		return ret;
	}
	neigh->confirmed = jiffies;
    write_unlock(&neigh->lock);
    rcu_read_unlock_bh();

	if (rtl_get_ct_protonum(ct, IP_CT_DIR_ORIGINAL)  == IPPROTO_UDP) {
        if((type & 0xF)&&(test_bit(IPS_SEEN_REPLY_BIT, &ct->status))&&!test_and_set_bit(IPS_ASSURED_BIT, &ct->status)) 
        {
            unsigned long newtime;
            newtime = jiffies + udp_get_timeouts_by_state(UDP_CT_REPLIED,(void *)ct,1);
            //printk("[%s:] %d, interval = %d\n",__func__,__LINE__,udp_get_timeouts_by_state(UDP_CT_REPLIED,(void *)ct,1));

            if (newtime - ct->timeout.expires >= HZ){
                //printk("[%s:] %d, interval = %d\n",__func__,__LINE__,udp_get_timeouts_by_state(UDP_CT_REPLIED,(void *)ct,1));
                mod_timer_pending(&ct->timeout, newtime);
            }
        }else if(type & 12)
            test_and_set_bit(IPS_SEEN_REPLY_BIT, &ct->status);
    }

#if defined(CONFIG_RTL_SPEED_MONITOR)
    if(type&3)
        rtl_update_dev_stats_hook(ct,skb,PACKET_DIR_ORIGINAL);
    else if(type&12)
        rtl_update_dev_stats_hook(ct,skb,PACKET_DIR_REPLY);
#endif
	return ret;
}

#ifdef CONFIG_RTL_FAST_IPV6
int rtl_skb_dst_check_ipv6(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct net_device *dev = dst->dev;
	struct neighbour *neigh;
	struct in6_addr *nexthop;
	int ret = SUCCESS;

	if (dst == NULL)
		return FAILED;

    if(skb->len>dst_mtu(dst))
        return FAILED;
	
	rcu_read_lock_bh();
	nexthop = rt6_nexthop((struct rt6_info *)dst);
	neigh = __ipv6_neigh_lookup_noref(dst->dev, nexthop);
	
    if(neigh != NULL)
        write_lock(&neigh->lock);
	if ( (neigh==NULL) ||!(neigh->nud_state & NUD_CONNECTED))
	{
        if((neigh!=NULL)&&!(neigh->nud_state & NUD_CONNECTED))
            neigh_probe(neigh);
        else if(neigh != NULL)
            write_unlock(&neigh->lock);
		ret = FAILED;
        rcu_read_unlock_bh();
		return ret;
	}
	neigh->confirmed = jiffies;
    write_unlock(&neigh->lock);
    rcu_read_unlock_bh();
	
	return ret;
}
#endif
#else
int rtl_skb_dst_check(struct sk_buff *skb)
{
	int ret = SUCCESS;

	if( !(skb->dst->hh || skb->dst->neighbour)  ||skb->len > dst_mtu(skb->dst))
		ret = FAILED;
	
	return ret;
}

#endif

void rtl_set_skb_ip_summed(struct sk_buff *skb, int value)
{
	skb->ip_summed = value;
	return;
}

void rtl_dst_release(struct sk_buff *skb)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	struct dst_entry *dst = skb_dst(skb);
	
	dst_release(dst);
	skb->_skb_refdst = 0UL;
#else
	dst_release(skb->dst);
	skb->dst = NULL;
#endif

	return;
}


__u32 rtl_get_skb_mark(struct sk_buff *skb)
{
	return skb->mark;
}

void rtl_set_skb_mark(struct sk_buff *skb, unsigned int value)
{
	skb->mark = value;

	return;
}


void rtl_store_skb_dst(struct sk_buff *skb)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	dst_tmp = rtl_skb_dst(skb);
#if !defined (CONFIG_OPENWRT_SDK)
	skb->_skb_refdst = 0UL;
#endif
#else
	dst_tmp = skb->dst;

	skb->dst = NULL;
#endif
	return;
}

void rtl_set_skb_dst(struct sk_buff *skb)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	skb_dst_set(skb, dst_tmp);
#else
	skb->dst = dst_tmp;
#endif
	return;
}

int rtl_tcp_get_timeouts(void *ptr)
{
	struct nf_conn *ct = (struct nf_conn *)ptr;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	return tcp_get_timeouts_by_state(ct->proto.tcp.state,(void *)ct,1);
#else
	return tcp_get_timeouts_by_state(ct->proto.tcp.state);
#endif
}

int rtl_arp_req_get_ha(__be32 queryIP, void *device, unsigned char * resHwAddr)
{
	struct net_device *dev = (struct net_device *)device;

	return arp_req_get_ha(queryIP, dev, resHwAddr);
}



u_int8_t rtl_get_ct_protonum(void *ct_ptr, enum ip_conntrack_dir dir)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	return ct->tuplehash[dir].tuple.dst.protonum;
}

unsigned long rtl_get_ct_udp_status(void *ct_ptr)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	return ct->status;
}

u_int8_t rtl_get_ct_tcp_state(void *ct_ptr)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	return ct->proto.tcp.state;
}

/*flag = 0 for src; flag = 1 for dst*/
__be32 rtl_get_ct_ip_by_dir(void *ct_ptr, enum ip_conntrack_dir dir, int flag)
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
	printk("[%s:] %d, get ct dir error\n",__func__,__LINE__);
	return __cpu_to_be32(0xdead);
}

/*flag = 0 for src; flag = 1 for dst*/
__be16 rtl_get_ct_port_by_dir(void *ct_ptr, enum ip_conntrack_dir dir, int flag)
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
	printk("[%s:] %d, get ct dir error\n",__func__,__LINE__);
	return __cpu_to_be32(0xdead);
}

void rtl_set_ct_timeout_expires(void *ct_ptr, unsigned long value)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	ct->timeout.expires = value;

	return;
}

unsigned long rtl_hold_time(void *br_ptr)
{
	struct net_bridge *br = (struct net_bridge *)br_ptr;

	return br->topology_change ? br->forward_delay : br->ageing_time;
}

void rtl_set_fdb_aging(void *fdb_ptr, unsigned long value)
{
	struct net_bridge_fdb_entry *fdb = (struct net_bridge_fdb_entry *)fdb_ptr;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	fdb->updated = value;
#else
	fdb->ageing_timer = value;
#endif

	return;
}

unsigned long rtl_get_fdb_aging(void *fdb_ptr)
{
	struct net_bridge_fdb_entry *fdb = (struct net_bridge_fdb_entry *)fdb_ptr;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	return fdb->updated;
#else
	return fdb->ageing_timer;
#endif
}

struct ethhdr *rtl_eth_hdr(struct sk_buff *skb)
{
	return eth_hdr(skb);
}


struct iphdr *rtl_ip_hdr(struct sk_buff *skb)
{
	return ip_hdr(skb);
}


struct net_device * rtl_get_dev_by_name(char *name)
{
	return __dev_get_by_name(&init_net, name);
}

struct net_device *rtl_get_skb_dev(struct sk_buff* skb)
{
	return skb->dev;
}


void rtl_set_skb_dev(struct sk_buff *skb, struct net_device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	if(dev == NULL) {
		struct dst_entry *dst = skb_dst(skb);
		skb->dev = dst->dev;
	}
	else
		skb->dev = dev;
#else
	if(dev == NULL)
		skb->dev = skb->dst->dev;
	else
		skb->dev = dev;
#endif
	return;
}

char *rtl_get_skb_dev_name(struct sk_buff *skb)
{
	return skb->dev->name;
}


void rtl_set_skb_inDev(struct sk_buff *skb)
{

    //openwrt remove it, because it only for debug
	//skb->inDev = skb->dev;

	return;
}

unsigned int rtl_get_skb_pppoe_flag(struct sk_buff* skb)
{
	#if defined (CONFIG_RTL_FAST_PPPOE)
	return skb->pppoe_flag;
	#else
	return 0;
	#endif
}

void rtl_set_skb_pppoe_flag(struct sk_buff* skb, unsigned int pppoe_flag)
{
	#if defined (CONFIG_RTL_FAST_PPPOE)
	skb->pppoe_flag=pppoe_flag;
	#endif
	return;
}

struct net_device *rtl_get_skb_rx_dev(struct sk_buff* skb)
{
	#if defined (CONFIG_RTL_FAST_PPPOE)
	return skb->rx_dev;
	#else
	return NULL;
	#endif
}

void rtl_set_skb_rx_dev(struct sk_buff* skb,struct net_device *dev)
{
	#if defined (CONFIG_RTL_FAST_PPPOE)
	skb->rx_dev=dev;
	#endif

	return;
}


char *rtl_get_ppp_dev_name(struct net_device *ppp_dev)
{
	return ppp_dev->name;
}

void * rtl_get_ppp_dev_priv(struct net_device *ppp_dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	return netdev_priv(ppp_dev);
#else
	return ppp_dev->priv;
#endif
}

int rtl_call_skb_ndo_start_xmit(struct sk_buff *skb)
{
	return skb->dev->netdev_ops->ndo_start_xmit(skb,skb->dev);
}

void rtl_inc_ppp_stats(struct ppp *ppp, int act, int len)
{

	if(act == 0){	//rx
		//ppp->stats.rx_packets ++;
		//ppp->stats.rx_bytes += len;
		ppp->dev->stats.rx_packets ++;
		ppp->dev->stats.rx_bytes += len;

		
	}else if(act == 1){ //tx
		//ppp->stats.tx_packets ++;
		//ppp->stats.tx_bytes += len;
		ppp->dev->stats.tx_packets ++;
		ppp->dev->stats.tx_bytes += len;

	}

	return;
}


void rtl_set_skb_tail(struct sk_buff *skb, int offset, int action)
{
	if(action == 1)
		skb->tail -= offset;
	else if(action == 0)
		skb->tail += offset;

	return;
}

struct sk_buff *rtl_ppp_receive_nonmp_frame(struct ppp *ppp, struct sk_buff *skb, int is_fast_fw)
{
	return ppp_receive_nonmp_frame(ppp, skb, is_fast_fw);
}

int rtl_ppp_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	return ppp_start_xmit(skb, dev);
}

void rtl_set_skb_cb(struct sk_buff *skb, char *value, int len)
{
	memcpy(skb->cb, value, len);

	return;
}

int rtl_ppp_vj_check(struct ppp* ppp)
{
	if(ppp->vj && !((ppp->xstate & SC_COMP_RUN) && ppp->xc_state))
		return 1;
	else
		return 0;
}

void *rtl_get_ppp_xmit_pending(struct ppp* ppp)
{
	return (void*)ppp->xmit_pending;
}

void rtl_set_ppp_xmit_pending(struct ppp* ppp, struct sk_buff* skb)
{
	ppp->xmit_pending = skb;

	return;
}

void rtl_set_skb_nfct(struct sk_buff *skb, void *value)
{
	skb->nfct = value;

	return;
}

struct neighbour *rtl_neigh_lookup(const void *pkey, struct net_device *dev)
{
	return neigh_lookup(&arp_tbl, pkey, dev);
}

struct hh_cache *rtl_get_hh_from_neigh(struct neighbour *neigh)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	/*linux-3.4, hh is struct in neigh;linux-2.6.30, hh is pointer in neigh*/
	return &(neigh->hh);
#else
	return neigh->hh;
#endif
}

seqlock_t rtl_get_lock_from_hh(struct hh_cache * hh)
{
	return hh->hh_lock;
}

unsigned short rtl_get_len_from_hh(struct hh_cache * hh)
{
	return hh->hh_len;
}

unsigned long *rtl_get_data_from_hh(struct hh_cache * hh)
{
	return hh->hh_data;
}

unsigned int rtl_skb_headroom(struct sk_buff *skb)
{
	return skb_headroom(skb);
}

int rtl_skb_cloned(struct sk_buff *skb)
{
	return skb_cloned(skb);
}

int rtl_skb_shared(const struct sk_buff *skb)
{
	return skb_shared(skb);
}

#if defined(CONFIG_RTL_DSCP_IPTABLE_CHECK) && defined(IMPROVE_QOS)
__u8 rtl_get_skb_orig_dscp(struct sk_buff *skb)
{
	return skb->original_dscp;
}
#endif

#endif	//#if defined(FASTPTH_INDEPENDENCE_KERNEL)

void rtl_conntrack_drop_check_hook(struct nf_conn *ct_tmp, uint16 ipprotocol, struct nf_conn *ct)
{	
#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	if (ct_tmp->drop_flag == -1 && (ipprotocol == IPPROTO_TCP || ipprotocol == IPPROTO_UDP))
	{
		ct_tmp->drop_flag = __conntrack_drop_check(ct);
	}
#endif
}

int  rtl_Add_Pattern_ACL_For_ContentFilter(void)
{
#if defined (CONFIG_RTL_LAYERED_DRIVER_L4)
#ifdef CONFIG_RTL_LAYERED_DRIVER_ACL
        rtl865x_AclRule_t rule;
 #if 0  //### add by sen_liu 2011.5.4 for lan("br0"),don't add pattern acl                     
        memset(&rule,0,sizeof(rtl865x_AclRule_t));                      
        rule.actionType_ = RTL865X_ACL_TOCPU;
        rule.ruleType_ = RTL865X_ACL_IP;
        rule.ipHttpFilter_=rule.ipHttpFilterM_=1;
        rule.pktOpApp_ = RTL865X_ACL_L3_AND_L4;

	#if defined(CONFIG_RTL_NETIF_MAPPING)
	{
		ps_drv_netif_mapping_t *entry;
		struct net_device *dev;
		dev = dev_get_by_name(&init_net,RTL_PS_BR0_DEV_NAME);
		if(dev == NULL)
			return 0;
		
		entry = rtl_get_ps_drv_netif_mapping_by_psdev(dev);
		dev_put(dev);
		if(entry == NULL)
		{
			printk("====%s(%d),ERROR,can't get lan device!\n",__FUNCTION__,__LINE__);
			return 0;
		}
		rtl865x_add_pattern_acl_for_contentFilter(&rule,entry->drvName);
	}
	#else
	rtl865x_add_pattern_acl_for_contentFilter(&rule,"br0");
	#endif
#endif

#ifdef CONFIG_RTL_IPTABLES_RULE_2_ACL
#else
	//Patch: lan pkt rcv to cpu
	memset(&rule,0,sizeof(rtl865x_AclRule_t));                      
        rule.actionType_ = RTL865X_ACL_PERMIT;
        rule.ruleType_ = RTL865X_ACL_MAC;
        rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	#if defined(CONFIG_RTL_NETIF_MAPPING)
	{
		ps_drv_netif_mapping_t *entry;
		void *dev;

		#if 0//### add by sen_liu 2011.5.4 for lan("br0"),don't add pattern acl 
		dev = dev_get_by_name(&init_net,RTL_PS_BR0_DEV_NAME);
		if(dev == NULL)
			return 0;
		
		entry = rtl_get_ps_drv_netif_mapping_by_psdev(dev);
		dev_put(dev);
		if(entry == NULL)
		{
			printk("====%s(%d),ERROR,can't get lan device!\n",__FUNCTION__,__LINE__);
			return 0;
		}
		rtl865x_add_pattern_acl_for_contentFilter(&rule,entry->drvName);
		#endif
		
		//wan
		dev = rtl_get_dev_by_name(RTL_PS_WAN0_DEV_NAME);
		if(dev == NULL)
			return 0;
		entry = rtl_get_ps_drv_netif_mapping_by_psdev(dev);
		dev_put(dev);
		if(entry == NULL)
		{
			printk("====%s(%d),ERROR,can't get wan device!\n",__FUNCTION__,__LINE__);
			return 0;
		}
		rtl865x_add_pattern_acl_for_contentFilter(&rule,entry->drvName);
	}
	#else
	//rtl865x_add_pattern_acl_for_contentFilter(&rule,"br0"); //### add by sen_liu 2011.5.4 for lan("br0"),don't add pattern acl 
	rtl865x_add_pattern_acl_for_contentFilter(&rule,"eth1");
	#endif
	//End patch
#endif
#endif
 #endif
        return 0;
}

int  Add_Pattern_ACL_For_ContentFilter(void)
{
	return rtl_Add_Pattern_ACL_For_ContentFilter();
}

 int  Del_Pattern_ACL_For_ContentFilter(void)
{
#if defined (CONFIG_RTL_LAYERED_DRIVER_L4)
#ifdef CONFIG_RTL_LAYERED_DRIVER_ACL
        rtl865x_AclRule_t rule;
                               
        memset(&rule,0,sizeof(rtl865x_AclRule_t));                      
        rule.actionType_ = RTL865X_ACL_TOCPU;
        rule.ruleType_ = RTL865X_ACL_IP;
        rule.ipHttpFilter_=rule.ipHttpFilterM_=1;
        rule.pktOpApp_ = RTL865X_ACL_L3_AND_L4;
	#if defined(CONFIG_RTL_NETIF_MAPPING)
	{
		ps_drv_netif_mapping_t *entry;
		void *dev;
		dev = rtl_get_dev_by_name(RTL_PS_BR0_DEV_NAME);
		if(dev == NULL)
			return 0;
		
		entry = rtl_get_ps_drv_netif_mapping_by_psdev(dev);
		dev_put(dev);
		if(entry == NULL)
		{
			printk("====%s(%d),ERROR,can't get lan device!\n",__FUNCTION__,__LINE__);
			return 0;
		}
		rtl865x_del_pattern_acl_for_contentFilter(&rule,entry->drvName);
	}
	#else	
	rtl865x_del_pattern_acl_for_contentFilter(&rule,"br0");
	#endif

//2010-12-29
//when wan is connected,if url filter entry is NULL, default acl will be deleted!!
//don't delete the default acl now...
#if 0	
#ifdef CONFIG_RTL_IPTABLES_RULE_2_ACL
#else
	//Patch: lan pkt rcv to cpu
	memset(&rule,0,sizeof(rtl865x_AclRule_t));                      
        rule.actionType_ = RTL865X_ACL_PERMIT;
        rule.ruleType_ = RTL865X_ACL_MAC;
        rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	#if defined(CONFIG_RTL_NETIF_MAPPING)
	{
		ps_drv_netif_mapping_t *entry;
		struct net_device *dev;
		dev = dev_get_by_name(&init_net,RTL_PS_BR0_DEV_NAME);
		if(dev == NULL)
			return 0;
		
		entry = rtl_get_ps_drv_netif_mapping_by_psdev(dev);
		if(entry == NULL)
		{
			printk("====%s(%d),ERROR,can't get lan device!\n",__FUNCTION__,__LINE__);
			return 0;
		}
		rtl865x_del_pattern_acl_for_contentFilter(&rule,entry->drvName);

		dev = dev_get_by_name(&init_net,RTL_PS_WAN0_DEV_NAME);
		if(dev == NULL)
			return 0;
		
		entry = rtl_get_ps_drv_netif_mapping_by_psdev(dev);
		if(entry == NULL)
		{
			printk("====%s(%d),ERROR,can't get wan device!\n",__FUNCTION__,__LINE__);
			return 0;
		}
		rtl865x_del_pattern_acl_for_contentFilter(&rule,entry->drvName);
		
	}
	#else	
	rtl865x_del_pattern_acl_for_contentFilter(&rule,"br0"); 
	rtl865x_del_pattern_acl_for_contentFilter(&rule,"eth1"); 
	#endif
	//End patch
#endif
#endif
#endif
#endif
        return 0;
}

#ifdef CONFIG_RTL_FAST_IPV6
struct ipv6hdr *rtl_ipv6_hdr(const struct sk_buff *skb)
{
	return ipv6_hdr(skb);
}


void rtl_store_skb_ipv6_dst(struct sk_buff *skb)
{
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0) 
	ipv6_dst_tmp = rtl_skb_dst(skb);
	skb->_skb_refdst = 0UL;
	#else
	ipv6_dst_tmp = skb->dst;
	skb->dst = NULL;
	#endif
	
	return;
}

void rtl_set_skb_ipv6_dst(struct sk_buff *skb)
{
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0) 
	skb_dst_set(skb, ipv6_dst_tmp);
	#else
	skb->dst = ipv6_dst_tmp;
	#endif
	return;
}

struct  dst_entry *rtl_get_skb_ipv6_dst(struct sk_buff *skb) 
{
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0) 
	return skb_dst(skb);
	#else
	return skb->dst;
	#endif
}

struct net_device *rtl_get_skb_ipv6_dst_dev(struct sk_buff *skb)
{
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0) 
	return skb_dst(skb)->dev;
	#else
	return skb->dst->dev;
	#endif
}

/*flag = 0 for src; flag = 1 for dst*/
void rtl_get_ct_v6_ip_by_dir(void *ct_ptr, enum ip_conntrack_dir dir, int flag,struct in6_addr *addr)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	if(flag == 0)
		memcmp(addr, &ct->tuplehash[dir].tuple.src.u3.in6, sizeof(struct  in6_addr));
	else if(flag == 1)
		memcmp(addr, &ct->tuplehash[dir].tuple.dst.u3.in6, sizeof(struct  in6_addr));
}


int rtl_skb_ipv6_dst_check(struct sk_buff *skb)
{
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		return rtl_skb_dst_check_ipv6(skb);
	#else
	int ret = SUCCESS;
	if(!(skb->dst->hh || skb->dst->neighbour || skb->dst->output)){
		ret = FAILED;
	}
	return ret;
	#endif
}

/*	
	syn from v6 protocol original code
*/
inline int rtl_ip6_skb_dst_mtu(struct sk_buff *skb)
{
	struct ipv6_pinfo *np = skb->sk ? rtl_inet6_sk(skb->sk) : NULL;

	#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	return (np && np->pmtudisc == IPV6_PMTUDISC_PROBE) ?
       skb_dst(skb)->dev->mtu : dst_mtu(skb_dst(skb));
	
	#else
		return (np && np->pmtudisc == IPV6_PMTUDISC_PROBE) ?
	       skb->dst->dev->mtu : dst_mtu(skb->dst);
	#endif
}

/* return value:
	FAILED:	ct should be delete
	SUCCESS:		ct should NOT be delete.
*/
u_int8_t rtl_get_ct_protonum_ipv6(void *ct_ptr, enum ip_conntrack_dir dir)
{
	struct nf_conn *ct = (struct nf_conn *)ct_ptr;

	return ct->tuplehash[dir].tuple.dst.protonum;
}


int rtl_skb_is_gso(struct sk_buff *skb)
{
	return skb_is_gso(skb);
}


u32 rtl_dst_allfrag(struct sk_buff *skb) 
{
	struct dst_entry *dst;
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)	
	dst = skb_dst(skb);
	#else
	dst = skb->dst;
	#endif
	
	return dst_allfrag(dst);
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)	
struct hh_cache *rtl_get_hh_from_skb(struct sk_buff *skb)
{
	return skb->dst->hh;
}

struct neighbour *rtl_get_neigh_from_skb(struct sk_buff *skb)
{
	return skb->dst->neighbour;
}

int rtl_check_skb_dst_output_exist(struct sk_buff *skb)
{
	int ret = FALSE;
	
	if (skb->dst->output)
		ret = TRUE;
	
	return ret;
}

int rtl_neigh_hh_output(struct sk_buff *skb)
{
	return neigh_hh_output(skb->dst->hh, skb);
}

int rtl_neigh_output(struct sk_buff *skb)
{
	return skb->dst->neighbour->output(skb);
}

int rtl_dst_output(struct sk_buff *skb)
{
	return skb->dst->output(skb);
}
#endif

int rtl_ip6_route_input(struct sk_buff *skb)
{
	int ret = SUCCESS;
	
	ip6_route_input(skb);	//get out device

	return ret;
}

int rtl_ipt6_do_table(struct sk_buff * skb, unsigned int hook, void *in, void *out)
{
	int ret = FAILED;
	struct net_device *out_dev = (struct net_device *)out;
	struct net_device *in_dev = (struct net_device *)in;

	ret = ip6t_do_table(skb, hook, in_dev, out_dev, dev_net(skb->dev)->ipv6.ip6table_mangle);
	return ret;
}

int rtl_check_dst_input(struct sk_buff * skb)
{
	int ret = SUCCESS;
	
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	if (skb_dst(skb)->input != ip6_forward)
		ret = FAILED;
	#else
	if (skb->dst->input != ip6_forward)
		ret = FAILED;
	#endif

	return ret;
}
#endif

int fast_path_before_nat_check(struct sk_buff *skb, struct iphdr *iph, uint32 iphProtocol)
{
	#if defined(RTL_FP_CHECK_SPI_ENABLED) || defined(FAST_PATH_SPI_ENABLED)
	int	ret;
	#endif
	#if defined(FAST_PATH_SPI_ENABLED)
	unsigned int dataoff;
	if(fast_spi == 0)
		return NET_RX_PASSBY;
	#endif

	#if defined(FAST_PATH_SPI_ENABLED)
	if (iphProtocol== IPPROTO_TCP){
		dataoff = skb_network_offset(skb) + (iph->ihl<<2);
		ret = rtl_nf_conntrack_in(dev_net(skb->dev), dataoff, NF_INET_PRE_ROUTING, skb);
		switch (ret){
			case	NF_DROP:
				kfree_skb(skb);
				return NET_RX_DROP;
			case	NF_ACCEPT:
				break;
			default:
				kfree_skb(skb);
				return NET_RX_DROP;
			}
	}
	#endif

	return NET_RX_PASSBY;
}

int fast_path_post_process_xmit_check(struct iphdr *iph, struct tcphdr *tcphupuh, struct sk_buff *skb)
{
	#if	defined(FAST_L2TP) || defined (CONFIG_RTL_FAST_PPPOE)
	if (enter_fast_path_fast_l2tp_post_process(skb)==NET_RX_DROP) 
	{
		return NET_RX_DROP;
	}
	else if (enter_fast_path_fast_pppoe_post_process(skb)==NET_RX_DROP)
	{
		return NET_RX_DROP;
	}	
	else
	{
		return NET_RX_SUCCESS;
	}
	#else
	return NET_RX_SUCCESS;
	#endif
}

int fast_path_post_process_return_check(struct iphdr *iph, struct tcphdr *tcphupuh, struct sk_buff *skb)
{
	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	if (iph->protocol==IPPROTO_UDP)
		return rtl_fp_gc_status_check(iph, tcphupuh, skb);
	#endif

	return NET_RX_SUCCESS;

}

int32 rtl_fp_dev_queue_xmit_check(struct sk_buff *skb, struct net_device *dev)
{
	#ifdef FAST_L2TP
	if (l2tp_tx_id_hook != NULL)
		l2tp_tx_id_hook((void*)skb);
	#endif

	#ifdef FAST_PPTP
	if (sync_tx_pptp_gre_seqno_hook != NULL)
		sync_tx_pptp_gre_seqno_hook(skb);
	#endif

	return SUCCESS;
}

int32 rtl_fp_dev_hard_start_xmit_check(struct sk_buff *skb, struct net_device *dev, struct netdev_queue *txq)
{
#if	defined(FAST_L2TP)
	#if	defined(CONFIG_NET_SCHED)
	if(!gQosEnabled)
	#endif
	if (l2tp_tx_id_hook != NULL)
		l2tp_tx_id_hook((void*)skb);
#endif

#if defined (CONFIG_RTL_LOCAL_PUBLIC)
	if(	(skb->srcLocalPublicIp!=0) &&
		(rtl865x_curOpMode==GATEWAY_MODE) &&
		#if defined(CONFIG_RTL_PUBLIC_SSID)
		(strncmp(dev->name,RTL_GW_WAN_DEVICE_NAME, 3)==0)
		#else
		(strncmp(dev->name,RTL_PS_WAN0_DEV_NAME, 4)==0)
		#endif
		) {
		rtl865x_getLocalPublicMac(skb->srcLocalPublicIp, skb->data+6);
	}
#endif
	return SUCCESS;
}

int _ip_finish_output3(struct sk_buff *skb)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	struct dst_entry *dst = skb_dst(skb);
	struct hh_cache *hh=NULL;
	struct neighbour *neigh = NULL;
	struct rtable *rt = (struct rtable *)dst;
	struct net_device *dev = dst->dev;
	u32 nexthop;
	u16 vid = 0;
#else
	struct dst_entry *dst;
	struct hh_cache *hh;

	dst = skb->dst;
	hh = dst->hh;
#endif
#if !defined(IMPROVE_QOS)
#if defined(CONFIG_NET_SCHED)
    if (gQosEnabled) {
		u_short proto = ntohs(skb->protocol);
		if(proto == ETH_P_IP){
			(list_empty(&nf_hooks[PF_INET][NF_IP_POST_ROUTING]))?: \
				ipt_do_table(skb, NF_IP_POST_ROUTING, skb->dev, NULL, \
				dev_net(skb->dev)->ipv4.iptable_mangle);
		}
    }
#endif
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	if (rt) {
		nexthop = (__force u32) rt_nexthop(rt, ip_hdr(skb)->daddr);
		neigh = __ipv4_neigh_lookup_noref(dev, nexthop);
		if (neigh) {
			hh = &(neigh->hh);
		}
	}

	if (neigh&&hh&&(neigh->nud_state & NUD_CONNECTED)&&hh->hh_len)
#else
	if (hh) 
#endif
	{
// ------------------------------------------------
#if 1
		memcpy(skb->data - 16, hh->hh_data, 16);
#else
		memcpy((unsigned char*)UNCACHE(skb->data - 16), hh->hh_data, 16);
#endif
		skb_push(skb, hh->hh_len);

#ifdef FAST_L2TP
		if (fast_l2tp_fw)
			l2tp_tx_id((void*)skb);
#endif

		if (skb->dev->flags & IFF_UP) {
#if defined(CONFIG_NET_SCHED)
			if (gQosEnabled) {
				// call dev_queue_xmit() instead of hard_start_xmit(), because I want the packets be sent through Traffic Control module
				dev_queue_xmit(skb);
				return 0;
			} else
#endif
			{

		#if defined(CONFIG_BRIDGE)
				/*	In order to improve performance
				*	We'd like to directly xmit and bypass the bridge check
				*/
				if (skb->dev->priv_flags == IFF_EBRIDGE)
				{
					/*	wan->lan	*/
					struct net_bridge *br = netdev_priv(skb->dev);
					const unsigned char *dest = skb->data;
					struct net_bridge_fdb_entry *dst;
					
                    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
					#if defined(CONFIG_BRIDGE_VLAN_FILTERING)
					/*Fix jwj: todo...*/
					#else
					vid = 0;
					#endif
					if ((dst = __br_fdb_get(br, dest, vid)) != NULL)
					#else
					if ((dst = __br_fdb_get(br, dest)) != NULL)
					#endif
					{
						//skb->dev->stats.tx_packets++;
						//skb->dev->stats.tx_bytes += skb->len;
						skb->dev = dst->dst->dev;
					}
				}
		#endif
				{
					if(!skb->dev->netdev_ops->ndo_start_xmit(skb,skb->dev))
						return 0;
				}
			}
		}
//------------------------------- david+2007-05-25

	} 
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	else if (neigh) {
		return neigh->output(neigh, skb);
	}
	#else
	else if (dst->neighbour) {
		return dst->neighbour->output(skb);
	}
	#endif

#if 0
	if (net_ratelimit())
		printk(KERN_DEBUG "ip_finish_output3: No header cache and no neighbour!\n");
#endif
	kfree_skb(skb);
	return -EINVAL;
}

int ip_finish_output3(struct sk_buff *skb)
{
	int ret = 0;
	#if defined(RTL_FASTPATH_FRAGMENT_SUPPORT)
	if (skb->len > dst_mtu(skb->dst)) 
		ret = rtl_ip_fragment_for_fastpath(skb, _ip_finish_output3);
	else
	#endif
		ret = _ip_finish_output3(skb);

	return ret;
}

#if defined (CONFIG_RTL_FAST_PPPOE)
int ip_finish_output4(struct sk_buff *skb)
{

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	u16 vid = 0;
#endif
#if !defined(IMPROVE_QOS)
#if defined(CONFIG_NET_SCHED)
	if (gQosEnabled) {
		u_short proto = ntohs(skb->protocol);
		if(proto == ETH_P_IP){
			(list_empty(&nf_hooks[PF_INET][NF_IP_POST_ROUTING]))?: \
				ipt_do_table(skb, NF_IP_POST_ROUTING, skb->dev, NULL, \
				dev_net(skb->dev)->ipv4.iptable_mangle);
		}
	}
#endif
#endif

	if (skb->dev->flags & IFF_UP) 
	{
#if defined(CONFIG_NET_SCHED)
		if (gQosEnabled) 
		{
			// call dev_queue_xmit() instead of hard_start_xmit(), because I want the packets be sent through Traffic Control module
			dev_queue_xmit(skb);		
		}
		else            
#endif
		{

#if defined(CONFIG_BRIDGE)
			/*	In order to improve performance
			*	We'd like to directly xmit and bypass the bridge check
			*/
			if (skb->dev->priv_flags == IFF_EBRIDGE)
			{
				/*	wan->lan	*/
				struct net_bridge *br = netdev_priv(skb->dev);
				const unsigned char *dest = skb->data;
				struct net_bridge_fdb_entry *dst;

                #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
				#if defined(CONFIG_BRIDGE_VLAN_FILTERING)
					/*Fix jwj: todo...*/
				#else
				vid = 0;
				#endif
				if ((dst = __br_fdb_get(br, dest, vid)) != NULL)
				#else
				if ((dst = __br_fdb_get(br, dest)) != NULL)
				#endif
				{
					//skb->dev->stats.tx_packets++;
					//skb->dev->stats.tx_bytes += skb->len;
					skb->dev = dst->dst->dev;
				}
				else
				{
					kfree_skb(skb);
					return 0;
				}
			}
#endif
	
			skb->dev->netdev_ops->ndo_start_xmit(skb,skb->dev);
			//skb->dev->stats.tx_packets++;
			//skb->dev->stats.tx_bytes += skb->len;
			return 0;
		}

	}
	else
	{

		kfree_skb(skb);
	}
	
	return 0;
}
#endif

#ifdef CONFIG_RTL_FAST_IPV6
int ip_finish_output6(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct rtable *rt = (struct rtable *)dst;
	struct net_device *dev = dst->dev;
	unsigned int hh_len = LL_RESERVED_SPACE(dev);
	struct neighbour *neigh;
    int ret;
	u32 nexthop;

	rcu_read_lock_bh();
	nexthop = rt6_nexthop((struct rt6_info *)dst);
	neigh = __ipv6_neigh_lookup_noref(dst->dev, nexthop);

	if (!IS_ERR(neigh)) {
		ret = dst_neigh_output(dst, neigh, skb);
		rcu_read_unlock_bh();
		return ret;
	}
	rcu_read_unlock_bh();

	kfree_skb(skb);
	return -EINVAL;
}
#endif

int FastPath_Enter(struct sk_buff **pskb)
{
	int ret;
	struct sk_buff *skb;

	skb=*pskb;
	//skb->nh.raw = skb->data;
	skb->transport_header=skb->data;
	skb->network_header = skb->data;
	//skb_reset_network_header(skb);
#ifdef CONFIG_RTL_PPPOE_DIRECT_REPLY
		if((magicNum != -1) && is_pppoe_lcp_echo_req(skb))
		{	
			if(direct_send_reply(skb)==1)
				return 1;							
		}
#endif
	
#if defined(CONFIG_RTL_FAST_PPPOE)
	extern int fast_pppoe_fw;
	check_and_pull_pppoe_hdr(*pskb);

	if(fast_pppoe_fw)
	{
		if((strncmp(skb->dev->name, RTL_PS_PPP_NAME, strlen(RTL_PS_PPP_NAME))==0) && 
			(rtl_get_skb_pppoe_flag(*pskb)==0))
			return 0;
	}	
#endif
#ifdef CONFIG_RTL_FAST_IPV6
	if(fast_ipv6_fw){
		ret = ipv6_fast_enter(*pskb);
		if(ret == 1)
		{
			return 1;
		}
	}
#endif

//hyking:
//bug fix:when port filter is enable,application will disable fast_nat_fw,at this moment,url filter is abnormal...
#if defined (DOS_FILTER) || defined (URL_FILTER)
		ret = filter_enter((void*)skb);
		if (ret == NF_DROP) {
			LOG_INFO("%s filter pkt, drop it\n", __FUNCTION__);
			kfree_skb(skb);
			return 1;
		}
#if	defined(CONFIG_RTL_FAST_FILTER)
	else if(ret == NF_FASTPATH)
	{
		//continue the fastpath
	}
	else if(ret == NF_OMIT)
	{
		//don't support this in driver now
		ret=0;
		goto out;
	}
	else if(ret == NF_LINUX)
	{
		//don't do rtk fastpath
		ret=0;
		goto out;
	}
#endif
	else if(ret != NF_ACCEPT)
	{
		ret=0;
		goto out;
	}
#endif

	if(!(skb->pkt_type == PACKET_HOST))
	{
		ret=0;
		goto out;
	}

	if (!fast_nat_fw)
	{
		ret=0;
		goto out;
	}

	/* Fix jwj: echo 0 > /proc/fast_l2tp cause coredump */
	if (skb_headroom(skb) < ETH_HLEN)
	{
		ret=0;
		goto out;
	}

#ifdef FILTER_UPNP_BR
	if (upnp_br_enabled && skb->dev && !memcmp(skb->dev->name, RTL_PS_WAN0_DEV_NAME, 4) && filter_upnp_and_fw(skb)){
		return 1;
	}
#endif

#ifdef FAST_PPTP
	if (fast_pptp_fw) {
		fast_pptp_filter((void*)skb);
		ret = fast_pptp_to_lan((void*)&skb);
		if (ret < 0)	// error, skb has been free
		{
			return 1;
		}
		*pskb=skb;
	}
#endif

#ifdef FAST_L2TP
	if (fast_l2tp_fw)
#if !defined(CONFIG_SUPPORT_RUSSIA_FEATURES) && !defined(CONFIG_RTL_L2TP_DIRECT_PPP_REPLY)
		fast_l2tp_rx((void*)skb);
#else
	{
		ret=fast_l2tp_rx((void*)skb);
		if(ret==1)
		{
			return 1;
		}
	}
#endif
#endif

	ret = enter_fast_path((void*)skb);

#if 0
	if(ret != NET_RX_DROP)
	{
		struct tcphdr *tcpudph;
		printk("-------%s(%d),ret(%d), src(0x%x),dst(0x%x), len is %d, version is %d\n",__FUNCTION__,__LINE__,ret,ip_hdr(skb)->saddr,ip_hdr(skb)->daddr, ip_hdr(skb)->ihl, ip_hdr(skb)->version);
		if(ip_hdr(skb)->protocol == IPPROTO_TCP)
		{
			tcpudph = (struct tcphdr*)((__u32 *)skb->data + ip_hdr(skb)->ihl);
			printk("===%s(%d),sport(%d),dport(%d),syn(%d),fin(%d),rst(%d)\n",__FUNCTION__,__LINE__,tcpudph->source,tcpudph->dest,tcpudph->syn,tcpudph->fin,tcpudph->rst);
		}
	}
#endif
#ifdef FAST_PPTP
	if (fast_pptp_fw && ret == 0 && ip_hdr(skb)->protocol == IPPROTO_GRE && skb->len > sizeof(struct iphdr)&& pptp_tcp_finished==1)
		if(Check_GRE_rx_net_device((void*)skb))
		{
			fast_pptp_sync_rx_seq((void*)skb);
		}
#endif


out:
#if defined(CONFIG_RTL_FAST_PPPOE)
	if(ret!=NET_RX_DROP)
	{
		check_and_restore_pppoe_hdr(skb);
	
	}
#endif
	return ret;
}

//======================================
extern int (*rtl_fpTimer_update_fphook)(void *ct);
extern int rtl_fpTimer_update(void *ct);
extern int32 (*rtl_br_fdb_time_update_fphook)(void *br_dummy, void *fdb_dummy, const unsigned char *addr);
extern int32 rtl_br_fdb_time_update(void *br_dummy, void *fdb_dummy, const unsigned char *addr);
extern int32 (*rtl_fp_dev_hard_start_xmit_check_fphook)(struct sk_buff *skb, struct net_device *dev, struct netdev_queue *txq);
extern int32 (*rtl_fp_dev_queue_xmit_check_fphook)(struct sk_buff *skb, struct net_device *dev);

static int __init fastpath_init(void)
{
	int			ret;
	int			buf[64];
	fast_path_hook=FastPath_Enter;
	#ifdef CONFIG_FAST_PATH_MODULE
	FastPath_hook1=rtk_delRoute;
	FastPath_hook2=rtk_modifyRoute;
	FastPath_hook3=rtk_addRoute;
	FastPath_hook4=rtk_delNaptConnection;
	FastPath_hook5=rtk_addArp;
	FastPath_hook6=rtk_addNaptConnection;
	FastPath_hook7=rtk_delArp;
	FastPath_hook8=rtk_modifyArp;
	FastPath_hook9=Get_fast_pptp_fw;
	FastPath_hook10=fast_pptp_to_wan;
	FastPath_hook11=rtk_idleNaptConnection;
	
#if	defined(CONFIG_RTL_HW_QOS_SUPPORT)
		qosGetSkbMarkByNaptEntryHook=rtl_qosGetSkbMarkByNaptEntry;
#endif
	#endif
	rtl_fpTimer_update_fphook = rtl_fpTimer_update;
    #if defined(CONFIG_BRIDGE)
	rtl_br_fdb_time_update_fphook = rtl_br_fdb_time_update;
    #endif
	rtl_fp_dev_hard_start_xmit_check_fphook = rtl_fp_dev_hard_start_xmit_check;
	rtl_fp_dev_queue_xmit_check_fphook = rtl_fp_dev_queue_xmit_check;
    spin_lock_init(&lock_rtl_feature);

	#ifdef	DEBUG_PROCFILE
	/* proc file for debug */
	init_fastpath_debug_proc();
	#endif	/* DEBUG_PROCFILE */

	#ifndef NO_ARP_USED
	/* Arp-Table Init */
	ret=init_table_arp(ARP_TABLE_LIST_MAX,ARP_TABLE_ENTRY_MAX);
	if(ret!=0) {
		DEBUGP_SYS("init_table_arp Failed!\n");
	}
	#endif

	#ifndef DEL_ROUTE_TBL
	/* Route-Table Init */
	ret=init_table_route(ROUTE_TABLE_LIST_MAX, ROUTE_TABLE_ENTRY_MAX);
	if(ret!=0) {
		DEBUGP_SYS("init_table_route Failed!\n");
	}
	#endif

	#ifndef DEL_NAPT_TBL
	/* Napt-Table Init */
	ret=init_table_napt(NAPT_TABLE_LIST_MAX, NAPT_TABLE_ENTRY_MAX);
	if(ret!=0)
	{
		DEBUGP_SYS("init_table_napt Failed!\n");
	}
	#endif

	/* Path-Table Init */
	ret=init_table_path(PATH_TABLE_LIST_MAX, PATH_TABLE_ENTRY_MAX);
	if(ret!=0) {
		DEBUGP_SYS("init_table_path Failed!\n");
	}

	#ifdef CONFIG_UDP_FRAG_CACHE
	if(!udp_fragCache_init(MAX_UDP_FRAG_ENTRY))
		return -1;
	
	if(!negative_fragCache_init())
		return -1;
	#endif

	#ifdef DOS_FILTER
	filter_init();
	#endif

	#ifdef FAST_PPTP
	fast_pptp_init();
	#endif

	#ifdef FAST_L2TP
	fast_l2tp_init();
	#endif
	
	#if defined (CONFIG_RTL_FAST_PPPOE)
	fast_pppoe_init();
	#endif
	
	#if defined (CONFIG_RTL_FAST_GRE)	
	fast_gre_init();
	#endif
	
	#ifdef CONFIG_RTL_FAST_IPV6
	
	ipv6_fast_forward_init();
	
	ret = init_V6_table_path(PATH_TABLE_LIST_MAX, PATH_TABLE_ENTRY_MAX);
	//ret = init_V6_table_path(50,50);
	if(ret!=0) {
		printk("init_V6_table_path Failed!\n");
	}
	#define MAX_V6_UDP_FRAG_ENTRY 500
	if(!V6_udp_fragCache_init(MAX_V6_UDP_FRAG_ENTRY))
		return -1;
		
	#endif
	#ifdef CONFIG_PROC_FS
	
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	res1 = proc_create_data("fast_nat", 0, &proc_root,
			 &fastpath_proc_fops, NULL);
	#else
	res1 = create_proc_entry("fast_nat",0,NULL);
	if (res1) {
	    res1->read_proc=read_proc;
	    res1->write_proc=write_proc;
	}
	#endif

	#if defined(FAST_PATH_SPI_ENABLED)
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	res_spi = proc_create_data("fast_spi", 0, &proc_root,
			 &fastspi_proc_fops, NULL);
	#else
	res_spi = create_proc_entry("fast_spi",0,NULL);
	if(res_spi){
		res_spi->read_proc = spi_read_proc;
		res_spi->write_proc = spi_write_proc;
	}
	#endif
	#endif
	
	#endif

	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	rtl_fp_gc_rx_threshold = RTL_FP_SESSION_LEVEL3_ALLOW_COUNT;
	#endif
	
	get_fastpath_module_info((unsigned char *)buf);
	printk("%s",(char *)buf);
	fast_nat_fw = 1;


	return 0;
}

static void __exit fastpath_exit(void)
{
	fast_nat_fw = 0;
#ifdef CONFIG_FAST_PATH_MODULE
	fast_path_hook=NULL;
	FastPath_hook1=NULL;
	FastPath_hook2=NULL;
	FastPath_hook3=NULL;
	FastPath_hook4=NULL;
	FastPath_hook5=NULL;
	FastPath_hook6=NULL;
	FastPath_hook7=NULL;
	FastPath_hook8=NULL;
	FastPath_hook9=NULL;
	FastPath_hook10=NULL;
	FastPath_hook11=NULL;
#endif
#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
	qosGetSkbMarkByNaptEntryHook=NULL;
#endif
	rtl_fpTimer_update_fphook = NULL;
    #if defined(CONFIG_BRIDGE)
	rtl_br_fdb_time_update_fphook = NULL;
    #endif
	rtl_fp_dev_hard_start_xmit_check_fphook = NULL;
    rtl_fp_dev_queue_xmit_check_fphook  = NULL;

#ifdef	DEBUG_PROCFILE
	/* proc file for debug */
	remove_fastpath_debug_proc();
#endif	/* DEBUG_PROCFILE */

#ifdef DOS_FILTER
	filter_exit();
#endif

#ifdef FAST_PPTP
	fast_pptp_exit();
#endif

#if defined (CONFIG_RTL_FAST_PPPOE)
	fast_pppoe_exit();
#endif

#if defined (CONFIG_RTL_FAST_GRE)
	fast_gre_exit();
#endif

#ifdef CONFIG_PROC_FS
	if (res1) {
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		remove_proc_entry("fast_nat", &proc_root);
		#else
		remove_proc_entry("fast_nat", res1);
		#endif
		res1 = NULL;
	}

	#if defined(FAST_PATH_SPI_ENABLED)
	if(res_spi){
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		remove_proc_entry("fast_spi", &proc_root);
		#else
		remove_proc_entry("fast_spi", res_spi);
		#endif
		res_spi = NULL;
	}
	#endif
#endif




	//printk("%s %s removed!\n", MODULE_NAME, MODULE_VERSION);
}

// direct tx ppp reply ptk to l2tp server
#if defined(CONFIG_SUPPORT_RUSSIA_FEATURES) || defined(CONFIG_RTL_L2TP_DIRECT_PPP_REPLY)
extern unsigned int l2tp_ppp_imagic;
extern struct l2tp_info l2tpInfo;
#endif

int Direct_Send_Reply(struct sk_buff * skb, int offset)
{
#if defined(CONFIG_SUPPORT_RUSSIA_FEATURES) || defined(CONFIG_RTL_L2TP_DIRECT_PPP_REPLY)
	int header_len;
	struct iphdr *iph,*iph_new, iph_newone;
	struct Rus_l2tp_ext_hdr *l2tph, l2tphone;
	unsigned char tos;
	unsigned short frag_off;
	struct sk_buff *new_skb;
	// var define ---------
	unsigned char *data;
	data = rtl_get_skb_data(skb);	
	unsigned char req_id;
	unsigned short req_len;

	//if the info is integrity, conitune to contruct the ptk.
	if(!fast_l2tp_fw || l2tpInfo.tid==0 || l2tpInfo.cid==0 || !l2tpInfo.wan_dev)
		return 0;

	if(l2tpInfo.valid != 1 || !l2tp_ppp_imagic)
		return 0;

	//extract necessary info
	{
		req_id = data[offset+1];
		req_len = ntohs(*((unsigned short*)(&data[offset+2])));
	}

	//contruct the ptk
	skb_push(skb,ETH_HLEN);			//mac header push 
	{
		// build the mac header 
		memcpy(skb->data, l2tpInfo.mac_header, ETH_HLEN);
		
		// build ip header
		iph_new = &iph_newone;
		iph_new->version	=	4;
		iph_new->ihl		=	sizeof(struct iphdr) >> 2;
		//iph_new->frag_off =	frag_off;
		iph_new->frag_off	=	htons(0x4000);
		iph_new->protocol	=	IPPROTO_UDP;

		//need confirm the value --------------------------------------
		iph_new->tos		=	0;
		
		iph_new->daddr	=	l2tpInfo.daddr;
		iph_new->saddr	=	l2tpInfo.saddr;
		
		iph_new->ttl		=	IPDEFTTL;
		skb->ip_summed	=	CHECKSUM_NONE;
		iph_new->tot_len	=	htons(skb->len - ETH_HLEN);
		iph_new->id 	=	0;

		iph_new->check	=	0;
		iph_new->check	=	htons(ip_fast_csum((unsigned char *)iph_new, iph_new->ihl));	
		memcpy(skb->data + ETH_HLEN, &iph_newone, sizeof(iph_newone));

		// build udp header
		l2tph = &l2tphone;
		l2tph->source	=htons(1701);
		l2tph->dest =htons(1701);
		//len ,need to confirm to modify
		if(req_len >8)
			l2tph->len	= htons(30);	
		else
			l2tph->len	= htons(26);				
		l2tph->checksum=0;
		
		//build l2tp header
		l2tph->type =htons(0x0002);
		l2tph->tid	=l2tpInfo.tid;
		l2tph->cid	=l2tpInfo.cid;
		
		//build ppp header
		l2tph->addr_control= htons(0xff03);
		l2tph->protocol =htons(0xc021);
		l2tph->code = 0x0a;
		l2tph->id = req_id;
		l2tph->lcp_length= htons(req_len);
		//message && imagicNumber has the same value
		l2tph->imagicNumber = l2tp_ppp_imagic;
		if(req_len > 8 )
		l2tph->message = l2tp_ppp_imagic;
		
		memcpy(skb->data+ETH_HLEN+sizeof(struct iphdr), &l2tphone, sizeof(struct Rus_l2tp_ext_hdr));

		//reset the skb info
		skb->len = ETH_HLEN+sizeof(struct iphdr)+sizeof(struct Rus_l2tp_ext_hdr);
		
		//set the ethx device to xmit
		skb->dev=l2tpInfo.wan_dev;
		l2tpInfo.last_xmit = jiffies;

		//panic_printk("%s[%d] --\n",__FUNCTION__,__LINE__);
		skb->dev->netdev_ops->ndo_start_xmit(skb,skb->dev);
		//kfree_skb(skb);
		return 1;		
	}
#else
	return 0;
#endif
}

int fast_l2tp_tx_lcp_echo_reply(unsigned char *data, int rightShift, void *skb)
{	
#if !defined(CONFIG_SUPPORT_RUSSIA_FEATURES) && !defined(CONFIG_RTL_L2TP_DIRECT_PPP_REPLY)
	return 0;

#else
	//patch for russia ppp disconnect 
	__u16 *ppp_protocol;
	ppp_protocol = &data[36+rightShift];
	
	if(*ppp_protocol == htons(0xc021))
	{
		if( *((u_int8_t *)(((u_int8_t *)ppp_protocol) + 2)) == 0x09)//request
		{
			//contruct the reply ptk to eth dirver to send		
			Direct_Send_Reply(skb,38+rightShift);
			return 1;
		}
	}
	
	return 0;
#endif
}

void rtl_fp_mark_invalid(void *ct)
{
	#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
	u_int8_t reply_proto, ori_proto;
	__be32 reply_sip, reply_dip, ori_sip, ori_dip;
	__be16 reply_sport, reply_dport, ori_sport, ori_dport;

	reply_sip = rtl_get_ct_ip_by_dir(ct, IP_CT_DIR_REPLY, 0);
	reply_dip = rtl_get_ct_ip_by_dir(ct, IP_CT_DIR_REPLY, 1);
	ori_sip = rtl_get_ct_ip_by_dir(ct, IP_CT_DIR_ORIGINAL, 0);
	ori_dip = rtl_get_ct_ip_by_dir(ct, IP_CT_DIR_ORIGINAL, 1);

	reply_sport = rtl_get_ct_port_by_dir(ct, IP_CT_DIR_REPLY, 0);
	reply_dport = rtl_get_ct_port_by_dir(ct, IP_CT_DIR_REPLY, 1);
	ori_sport = rtl_get_ct_port_by_dir(ct, IP_CT_DIR_ORIGINAL, 0);
	ori_dport = rtl_get_ct_port_by_dir(ct, IP_CT_DIR_ORIGINAL, 1);

	reply_proto = rtl_get_ct_protonum(ct, IP_CT_DIR_REPLY);
	ori_proto = rtl_get_ct_protonum(ct, IP_CT_DIR_ORIGINAL);

	mark_path_invalid(reply_sip, reply_sport, reply_dip, reply_dport, reply_proto);

	mark_path_invalid(ori_sip, ori_sport, ori_dip, ori_dport, ori_proto);
	#endif
	
	return;
}


module_init(fastpath_init);
module_exit(fastpath_exit);
MODULE_LICENSE("GPL");

