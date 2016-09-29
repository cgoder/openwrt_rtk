/*
* Program : multiple wan
* Abstract : 
* Author : hyking (hyking_liu@realsil.com.cn)  
*
*  Copyright (c) 2011 Realtek Semiconductor Corp.
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License version 2 as
*  published by the Free Software Foundation.
*/

#include <linux/proc_fs.h>
//#include <linux/seq_file.h>


#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_glue.h>
#include "common/rtl_errno.h"
#include <net/rtl/rtl865x_netif.h>
#include "common/rtl865x_netif_local.h"
#include "rtl865x_ppp_local.h"
#include "rtl865x_route.h"
#include "rtl865x_nexthop.h"
#include <net/rtl/rtl865x_arp_api.h>
#include "rtl865x_arp.h"

#include <net/rtl/rtl865x_multipleWan_api.h>
#include "rtl865x_multipleWan.h"

#include "AsicDriver/rtl865x_asicCom.h"
#include "AsicDriver/asicRegs.h"
#include "AsicDriver/rtl865x_asicBasic.h"

#include <linux/skbuff.h>
#include <net/netfilter/nf_conntrack.h>

#include <net/rtl/rtl865x_netif.h>

#if defined(CONFIG_RTL_PROC_NEW)
#include <linux/seq_file.h>
extern struct proc_dir_entry proc_root;
#endif

#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
extern unsigned int _br0_ip;
extern unsigned int _br0_mask;
#endif

static rtl_advRoute_entry_t rtl_advRt_table[RTL_ADVRT_MAX_NUM];
static enum ENUM_NETDEC_POLICY oldNetDecision;
static struct proc_dir_entry *adv_rt_entry;

#ifdef CONFIG_RTL_PROC_NEW
static void rtl_show_advRoute(struct seq_file *s, rtl_advRoute_entry_t *rule)
{
	switch(rule->ruleType_)	
	{
			case RTL_ADVRT_MAC:
				seq_printf(s,"rule type: %s\n", "MAC based");
				seq_printf(s,"\tether type: %x   ether type mask: %x\n", rule->advrt_typeLen_, rule->advrt_typeLenMask_);
				seq_printf(s,"\tDMAC: %x:%x:%x:%x:%x:%x  DMACM: %x:%x:%x:%x:%x:%x\n",
						rule->advrt_dstMac_.octet[0], rule->advrt_dstMac_.octet[1], rule->advrt_dstMac_.octet[2],
						rule->advrt_dstMac_.octet[3], rule->advrt_dstMac_.octet[4], rule->advrt_dstMac_.octet[5],
						rule->advrt_dstMacMask_.octet[0], rule->advrt_dstMacMask_.octet[1], rule->advrt_dstMacMask_.octet[2],
						rule->advrt_dstMacMask_.octet[3], rule->advrt_dstMacMask_.octet[4], rule->advrt_dstMacMask_.octet[5]
						);
				
				seq_printf(s, "\tSMAC: %x:%x:%x:%x:%x:%x  SMACM: %x:%x:%x:%x:%x:%x\n",
						rule->advrt_srcMac_.octet[0], rule->advrt_srcMac_.octet[1], rule->advrt_srcMac_.octet[2],
						rule->advrt_srcMac_.octet[3], rule->advrt_srcMac_.octet[4], rule->advrt_srcMac_.octet[5],
						rule->advrt_srcMacMask_.octet[0], rule->advrt_srcMacMask_.octet[1], rule->advrt_srcMacMask_.octet[2],
						rule->advrt_srcMacMask_.octet[3], rule->advrt_srcMacMask_.octet[4], rule->advrt_srcMacMask_.octet[5]
					);
				break;

			case RTL_ADVRT_IP:
				seq_printf(s,"rule type: %s\n", "IP");
				seq_printf(s, "\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				seq_printf(s,"\tTos: %x   TosM: %x   ipProto: %x   ipProtoM: %x   ipFlag: %x   ipFlagM: %x\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_ipProto_, rule->advrt_ipProtoMask_, rule->advrt_ipFlag_, rule->advrt_ipFlagMask_
					);
				
				seq_printf(s,"\t<FOP:%x> <FOM:%x> <http:%x> <httpM:%x> <IdentSdip:%x> <IdentSdipM:%x> \n",
						rule->advrt_ipFOP_, rule->advrt_ipFOM_, rule->advrt_ipHttpFilter_, rule->advrt_ipHttpFilterM_, rule->advrt_ipIdentSrcDstIp_,
						rule->advrt_ipIdentSrcDstIpM_
						);
				seq_printf(s, "\t<DF:%x> <MF:%x>\n", rule->advrt_ipDF_, rule->advrt_ipMF_); 
					break;
					
			case RTL_ADVRT_IP_RANGE:
				seq_printf(s,"rule type: %s \n", "IP Range");
				seq_printf(s,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				seq_printf(s,"\tTos: %x   TosM: %x   ipProto: %x   ipProtoM: %x   ipFlag: %x   ipFlagM: %x\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_ipProto_, rule->advrt_ipProtoMask_, rule->advrt_ipFlag_, rule->advrt_ipFlagMask_
						);
				seq_printf(s,"\t<FOP:%x> <FOM:%x> <http:%x> <httpM:%x> <IdentSdip:%x> <IdentSdipM:%x> \n",
						rule->advrt_ipFOP_, rule->advrt_ipFOM_, rule->advrt_ipHttpFilter_, rule->advrt_ipHttpFilterM_, rule->advrt_ipIdentSrcDstIp_,
						rule->advrt_ipIdentSrcDstIpM_
						);
					seq_printf(s,"\t<DF:%x> <MF:%x>\n", rule->advrt_ipDF_, rule->advrt_ipMF_); 
					break;			
			case RTL_ADVRT_ICMP:
				seq_printf(s,"rule type: %s\n", "ICMP");
				seq_printf(s,"\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				seq_printf(s,"\tTos: %x   TosM: %x   type: %x   typeM: %x   code: %x   codeM: %x\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_icmpType_, rule->advrt_icmpTypeMask_, 
						rule->advrt_icmpCode_, rule->advrt_icmpCodeMask_);
				break;
			case RTL_ADVRT_ICMP_IPRANGE:
				seq_printf(s,"rule type: %s\n","ICMP IP RANGE");
				seq_printf(s,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				seq_printf(s,"\tTos: %x   TosM: %x   type: %x   typeM: %x   code: %x   codeM: %x\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_icmpType_, rule->advrt_icmpTypeMask_, 
						rule->advrt_icmpCode_, rule->advrt_icmpCodeMask_);
				break;
			case RTL_ADVRT_IGMP:
				seq_printf(s,"rule type: %s\n", "IGMP");
				seq_printf(s,"\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				seq_printf(s,"\tTos: %x   TosM: %x   type: %x   typeM: %x\n", rule->advrt_tos_, rule->advrt_tosMask_,
						rule->advrt_igmpType_, rule->advrt_igmpTypeMask_
						);
				break;


			case RTL_ADVRT_IGMP_IPRANGE:
				seq_printf(s," rule type: %s\n",  "IGMP IP RANGE");
				seq_printf(s,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				seq_printf(s,"\tTos: %x   TosM: %x   type: %x   typeM: %x\n", rule->advrt_tos_, rule->advrt_tosMask_,
						rule->advrt_igmpType_, rule->advrt_igmpTypeMask_
						);
				break;

			case RTL_ADVRT_TCP:
				seq_printf(s,"rule type: %s\n","TCP");
				seq_printf(s,"\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);				
				seq_printf(s,"\tTos:%x  TosM:%x  sportL:%d  sportU:%d  dportL:%d  dportU:%d\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_tcpSrcPortLB_, rule->advrt_tcpSrcPortUB_,
						rule->advrt_tcpDstPortLB_, rule->advrt_tcpDstPortUB_
						);
				seq_printf(s,"\tflag: %x  flagM: %x  <URG:%x> <ACK:%x> <PSH:%x> <RST:%x> <SYN:%x> <FIN:%x>\n",
						rule->advrt_tcpFlag_, rule->advrt_tcpFlagMask_, rule->advrt_tcpURG_, rule->advrt_tcpACK_,
						rule->advrt_tcpPSH_, rule->advrt_tcpRST_, rule->advrt_tcpSYN_, rule->advrt_tcpFIN_
						);
				break;
			case RTL_ADVRT_TCP_IPRANGE:
					seq_printf(s,"rule type: %s\n","TCP IP RANGE");
					seq_printf(s,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
					seq_printf(s,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
					seq_printf(s,"\tTos:%x  TosM:%x  sportL:%d  sportU:%d  dportL:%d  dportU:%d\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_tcpSrcPortLB_, rule->advrt_tcpSrcPortUB_,
						rule->advrt_tcpDstPortLB_, rule->advrt_tcpDstPortUB_
						);
					seq_printf(s,"\tflag: %x  flagM: %x  <URG:%x> <ACK:%x> <PSH:%x> <RST:%x> <SYN:%x> <FIN:%x>\n",
						rule->advrt_tcpFlag_, rule->advrt_tcpFlagMask_, rule->advrt_tcpURG_, rule->advrt_tcpACK_,
						rule->advrt_tcpPSH_, rule->advrt_tcpRST_, rule->advrt_tcpSYN_, rule->advrt_tcpFIN_
					);
				break;

			case RTL_ADVRT_UDP:
				seq_printf(s,"rule type: %s\n","UDP");
				seq_printf(s,"\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				seq_printf(s,"\tTos:%x  TosM:%x  sportL:%d  sportU:%d  dportL:%d  dportU:%d\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_udpSrcPortLB_, rule->advrt_udpSrcPortUB_,
						rule->advrt_udpDstPortLB_, rule->advrt_udpDstPortUB_
						);
				break;				
			case RTL_ADVRT_UDP_IPRANGE:
				seq_printf(s,"rule type: %s\n","UDP IP RANGE");
				seq_printf(s,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				seq_printf(s,"\tTos:%x  TosM:%x  sportL:%d  sportU:%d  dportL:%d  dportU:%d\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_udpSrcPortLB_, rule->advrt_udpSrcPortUB_,
						rule->advrt_udpDstPortLB_, rule->advrt_udpDstPortUB_
					);
				break;
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
			case RTL_ADVRT_SRCFILTER:
				seq_printf(s,"rule->ruleType_(0x%x)\n", rule->ruleType_);
				seq_printf(s,"\tsip: %d.%d.%d.%d sip_mask: %d.%d.%d.%d\n", (rule->advrt_srcFilterIpAddr_>>24),
						((rule->advrt_srcFilterIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcFilterIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcFilterIpAddr_&0xff), (rule->advrt_srcFilterIpAddrMask_>>24), ((rule->advrt_srcFilterIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcFilterIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcFilterIpAddrMask_&0xff)
						);
				seq_printf(s,"\tsrc phy port:0x%x\n", rule->advrt_srcFilterPort_);
				break;
#endif
				default:
					seq_printf(s,"rule->ruleType_(0x%x)\n", rule->ruleType_);

		}

		seq_printf(s,"\tNexthop(%u.%u.%u.%u),extip(%u.%u.%u.%u),outif(%s),Op(%d)\n", NIPQUAD(rule->nexthop),NIPQUAD(rule->extIp),rule->outIfName,rule->pktOpApp_);
	
}

#else
static void rtl_show_advRoute(char *page, int *ret_len, rtl_advRoute_entry_t *rule)
{
    int len = *ret_len;
	switch(rule->ruleType_)	
	{
			case RTL_ADVRT_MAC:
				len += sprintf(page+len,"rule type: %s\n", "MAC based");
				len += sprintf(page+len,"\tether type: %x   ether type mask: %x\n", rule->advrt_typeLen_, rule->advrt_typeLenMask_);
				len += sprintf(page+len,"\tDMAC: %x:%x:%x:%x:%x:%x  DMACM: %x:%x:%x:%x:%x:%x\n",
						rule->advrt_dstMac_.octet[0], rule->advrt_dstMac_.octet[1], rule->advrt_dstMac_.octet[2],
						rule->advrt_dstMac_.octet[3], rule->advrt_dstMac_.octet[4], rule->advrt_dstMac_.octet[5],
						rule->advrt_dstMacMask_.octet[0], rule->advrt_dstMacMask_.octet[1], rule->advrt_dstMacMask_.octet[2],
						rule->advrt_dstMacMask_.octet[3], rule->advrt_dstMacMask_.octet[4], rule->advrt_dstMacMask_.octet[5]
						);
				
				len += sprintf(page+len, "\tSMAC: %x:%x:%x:%x:%x:%x  SMACM: %x:%x:%x:%x:%x:%x\n",
						rule->advrt_srcMac_.octet[0], rule->advrt_srcMac_.octet[1], rule->advrt_srcMac_.octet[2],
						rule->advrt_srcMac_.octet[3], rule->advrt_srcMac_.octet[4], rule->advrt_srcMac_.octet[5],
						rule->advrt_srcMacMask_.octet[0], rule->advrt_srcMacMask_.octet[1], rule->advrt_srcMacMask_.octet[2],
						rule->advrt_srcMacMask_.octet[3], rule->advrt_srcMacMask_.octet[4], rule->advrt_srcMacMask_.octet[5]
					);
				break;

			case RTL_ADVRT_IP:
				len += sprintf(page+len,"rule type: %s\n", "IP");
				len += sprintf(page+len, "\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tTos: %x   TosM: %x   ipProto: %x   ipProtoM: %x   ipFlag: %x   ipFlagM: %x\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_ipProto_, rule->advrt_ipProtoMask_, rule->advrt_ipFlag_, rule->advrt_ipFlagMask_
					);
				
				len += sprintf(page+len,"\t<FOP:%x> <FOM:%x> <http:%x> <httpM:%x> <IdentSdip:%x> <IdentSdipM:%x> \n",
						rule->advrt_ipFOP_, rule->advrt_ipFOM_, rule->advrt_ipHttpFilter_, rule->advrt_ipHttpFilterM_, rule->advrt_ipIdentSrcDstIp_,
						rule->advrt_ipIdentSrcDstIpM_
						);
				len += sprintf(page+len, "\t<DF:%x> <MF:%x>\n", rule->advrt_ipDF_, rule->advrt_ipMF_); 
					break;
					
			case RTL_ADVRT_IP_RANGE:
				len += sprintf(page+len,"rule type: %s \n", "IP Range");
				len += sprintf(page+len,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tTos: %x   TosM: %x   ipProto: %x   ipProtoM: %x   ipFlag: %x   ipFlagM: %x\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_ipProto_, rule->advrt_ipProtoMask_, rule->advrt_ipFlag_, rule->advrt_ipFlagMask_
						);
				len += sprintf(page+len,"\t<FOP:%x> <FOM:%x> <http:%x> <httpM:%x> <IdentSdip:%x> <IdentSdipM:%x> \n",
						rule->advrt_ipFOP_, rule->advrt_ipFOM_, rule->advrt_ipHttpFilter_, rule->advrt_ipHttpFilterM_, rule->advrt_ipIdentSrcDstIp_,
						rule->advrt_ipIdentSrcDstIpM_
						);
					len += sprintf(page+len,"\t<DF:%x> <MF:%x>\n", rule->advrt_ipDF_, rule->advrt_ipMF_); 
					break;			
			case RTL_ADVRT_ICMP:
				len += sprintf(page+len,"rule type: %s\n", "ICMP");
				len += sprintf(page+len,"\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tTos: %x   TosM: %x   type: %x   typeM: %x   code: %x   codeM: %x\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_icmpType_, rule->advrt_icmpTypeMask_, 
						rule->advrt_icmpCode_, rule->advrt_icmpCodeMask_);
				break;
			case RTL_ADVRT_ICMP_IPRANGE:
				len += sprintf(page+len,"rule type: %s\n","ICMP IP RANGE");
				len += sprintf(page+len,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tTos: %x   TosM: %x   type: %x   typeM: %x   code: %x   codeM: %x\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_icmpType_, rule->advrt_icmpTypeMask_, 
						rule->advrt_icmpCode_, rule->advrt_icmpCodeMask_);
				break;
			case RTL_ADVRT_IGMP:
				len += sprintf(page+len,"rule type: %s\n", "IGMP");
				len += sprintf(page+len,"\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tTos: %x   TosM: %x   type: %x   typeM: %x\n", rule->advrt_tos_, rule->advrt_tosMask_,
						rule->advrt_igmpType_, rule->advrt_igmpTypeMask_
						);
				break;


			case RTL_ADVRT_IGMP_IPRANGE:
				len += sprintf(page+len," rule type: %s\n",  "IGMP IP RANGE");
				len += sprintf(page+len,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tTos: %x   TosM: %x   type: %x   typeM: %x\n", rule->advrt_tos_, rule->advrt_tosMask_,
						rule->advrt_igmpType_, rule->advrt_igmpTypeMask_
						);
				break;

			case RTL_ADVRT_TCP:
				len += sprintf(page+len,"rule type: %s\n","TCP");
				len += sprintf(page+len,"\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);				
				len += sprintf(page+len,"\tTos:%x  TosM:%x  sportL:%d  sportU:%d  dportL:%d  dportU:%d\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_tcpSrcPortLB_, rule->advrt_tcpSrcPortUB_,
						rule->advrt_tcpDstPortLB_, rule->advrt_tcpDstPortUB_
						);
				len += sprintf(page+len,"\tflag: %x  flagM: %x  <URG:%x> <ACK:%x> <PSH:%x> <RST:%x> <SYN:%x> <FIN:%x>\n",
						rule->advrt_tcpFlag_, rule->advrt_tcpFlagMask_, rule->advrt_tcpURG_, rule->advrt_tcpACK_,
						rule->advrt_tcpPSH_, rule->advrt_tcpRST_, rule->advrt_tcpSYN_, rule->advrt_tcpFIN_
						);
				break;
			case RTL_ADVRT_TCP_IPRANGE:
					len += sprintf(page+len,"rule type: %s\n","TCP IP RANGE");
					len += sprintf(page+len,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
					len += sprintf(page+len,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
					len += sprintf(page+len,"\tTos:%x  TosM:%x  sportL:%d  sportU:%d  dportL:%d  dportU:%d\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_tcpSrcPortLB_, rule->advrt_tcpSrcPortUB_,
						rule->advrt_tcpDstPortLB_, rule->advrt_tcpDstPortUB_
						);
					len += sprintf(page+len,"\tflag: %x  flagM: %x  <URG:%x> <ACK:%x> <PSH:%x> <RST:%x> <SYN:%x> <FIN:%x>\n",
						rule->advrt_tcpFlag_, rule->advrt_tcpFlagMask_, rule->advrt_tcpURG_, rule->advrt_tcpACK_,
						rule->advrt_tcpPSH_, rule->advrt_tcpRST_, rule->advrt_tcpSYN_, rule->advrt_tcpFIN_
					);
				break;

			case RTL_ADVRT_UDP:
				len += sprintf(page+len,"rule type: %s\n","UDP");
				len += sprintf(page+len,"\tdip: %d.%d.%d.%d dipM: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsip: %d.%d.%d.%d sipM: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tTos:%x  TosM:%x  sportL:%d  sportU:%d  dportL:%d  dportU:%d\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_udpSrcPortLB_, rule->advrt_udpSrcPortUB_,
						rule->advrt_udpDstPortLB_, rule->advrt_udpDstPortUB_
						);
				break;				
			case RTL_ADVRT_UDP_IPRANGE:
				len += sprintf(page+len,"rule type: %s\n","UDP IP RANGE");
				len += sprintf(page+len,"\tdipU: %d.%d.%d.%d dipL: %d.%d.%d.%d\n", (rule->advrt_dstIpAddr_>>24),
						((rule->advrt_dstIpAddr_&0x00ff0000)>>16), ((rule->advrt_dstIpAddr_&0x0000ff00)>>8),
						(rule->advrt_dstIpAddr_&0xff), (rule->advrt_dstIpAddrMask_>>24), ((rule->advrt_dstIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_dstIpAddrMask_&0x0000ff00)>>8), (rule->advrt_dstIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tsipU: %d.%d.%d.%d sipL: %d.%d.%d.%d\n", (rule->advrt_srcIpAddr_>>24),
						((rule->advrt_srcIpAddr_&0x00ff0000)>>16), ((rule->advrt_srcIpAddr_&0x0000ff00)>>8),
						(rule->advrt_srcIpAddr_&0xff), (rule->advrt_srcIpAddrMask_>>24), ((rule->advrt_srcIpAddrMask_&0x00ff0000)>>16),
						((rule->advrt_srcIpAddrMask_&0x0000ff00)>>8), (rule->advrt_srcIpAddrMask_&0xff)
						);
				len += sprintf(page+len,"\tTos:%x  TosM:%x  sportL:%d  sportU:%d  dportL:%d  dportU:%d\n",
						rule->advrt_tos_, rule->advrt_tosMask_, rule->advrt_udpSrcPortLB_, rule->advrt_udpSrcPortUB_,
						rule->advrt_udpDstPortLB_, rule->advrt_udpDstPortUB_
					);
				break;

				default:
					len += sprintf(page+len,"rule->ruleType_(0x%x)\n", rule->ruleType_);

		}

		len += sprintf(page+len,"\tNexthop(%u.%u.%u.%u),extip(%u.%u.%u.%u),outif(%s),Op(%d)\n", NIPQUAD(rule->nexthop),NIPQUAD(rule->extIp),rule->outIfName,rule->pktOpApp_);
	    *ret_len = len;
}
#endif

#ifdef CONFIG_RTL_PROC_NEW
void rtl_show_advRt_table(struct seq_file *s)
{
	rtl_advRoute_entry_t *tmp_entry;
	int i;
	
	for(i = 0; i < RTL_ADVRT_MAX_NUM; i++)
	{
		tmp_entry = &rtl_advRt_table[i];
		if(tmp_entry->valid_)
		{
			seq_printf(s, "idx(%d):\n",i);
			rtl_show_advRoute(s, tmp_entry);
		}
		
	}
}
#else
void rtl_show_advRt_table(char *page, int *ret_len)
{
	rtl_advRoute_entry_t *tmp_entry;
	int i;
    int len = *ret_len;
	
	for(i = 0; i < RTL_ADVRT_MAX_NUM; i++)
	{
		tmp_entry = &rtl_advRt_table[i];
		if(tmp_entry->valid_)
		{
			len += sprintf(page+len, "idx(%d):\n",i);
			rtl_show_advRoute(page, &len, tmp_entry);
		}
		
	}
    *ret_len = len;
}
#endif

static int8 _rtl_same_AdvRt_rule(rtl_advRoute_entry_t *rule1, rtl_advRoute_entry_t *rule2)
{

	if (rule1->ruleType_ != rule2->ruleType_)
		return FALSE;

	switch(rule1->ruleType_) 
	{
	case RTL_ADVRT_MAC:
		 if (rule1->advrt_typeLen_ != rule2->advrt_typeLen_ || rule1->advrt_typeLenMask_ != rule2->advrt_typeLenMask_)
		 	return FALSE;
		 if (memcmp(&rule1->advrt_dstMac_, &rule2->advrt_dstMac_, sizeof(ether_addr_t)) || 
		 	 memcmp(&rule1->advrt_dstMacMask_, &rule2->advrt_dstMacMask_, sizeof(ether_addr_t)) ||
			 memcmp(&rule1->advrt_srcMac_, &rule2->advrt_srcMac_, sizeof(ether_addr_t)) ||
			 memcmp(&rule1->advrt_srcMacMask_, &rule2->advrt_srcMacMask_, sizeof(ether_addr_t)) )
			 return FALSE;
		 return TRUE;
	case RTL_ADVRT_IP:
	case RTL_ADVRT_IP_RANGE:
		 if (rule1->advrt_ipProto_ != rule2->advrt_ipProto_ || rule1->advrt_ipProtoMask_ != rule2->advrt_ipProtoMask_ ||
			rule1->advrt_ipFlag_ != rule2->advrt_ipFlag_ || rule1->advrt_ipFlagMask_ != rule2->advrt_ipFlagMask_)
			return FALSE; 
		break;
			
	case RTL_ADVRT_ICMP:
	case RTL_ADVRT_ICMP_IPRANGE:
		 if (rule1->advrt_icmpType_ != rule2->advrt_icmpType_ || rule1->advrt_icmpTypeMask_ != rule2->advrt_icmpTypeMask_ ||
			rule1->advrt_icmpCode_ != rule2->advrt_icmpCode_ || rule1->advrt_icmpCodeMask_ != rule2->advrt_icmpCodeMask_)
			return FALSE; 
		 break;

	case RTL_ADVRT_IGMP:
	case RTL_ADVRT_IGMP_IPRANGE:
		 if(rule1->advrt_igmpType_ != rule2->advrt_igmpType_ || rule1->advrt_igmpTypeMask_ != rule2->advrt_igmpTypeMask_)
		 	return FALSE; 
		 break;
	case RTL_ADVRT_TCP:
	case RTL_ADVRT_TCP_IPRANGE:
		 if(rule1->advrt_tcpFlag_ != rule2->advrt_tcpFlag_ || rule1->advrt_tcpFlagMask_ != rule2->advrt_tcpFlagMask_ ||
			rule1->advrt_tcpSrcPortUB_ != rule2->advrt_tcpSrcPortUB_ || rule1->advrt_tcpSrcPortLB_ != rule2->advrt_tcpSrcPortLB_ ||
			rule1->advrt_tcpDstPortUB_ != rule2->advrt_tcpDstPortUB_ || rule1->advrt_tcpDstPortLB_ != rule2->advrt_tcpDstPortLB_)
		 	return FALSE; 
		 break;
	case RTL_ADVRT_UDP:
	case RTL_ADVRT_UDP_IPRANGE:
		 if(rule1->advrt_udpSrcPortUB_ != rule2->advrt_udpSrcPortUB_ || rule1->advrt_udpSrcPortLB_ != rule2->advrt_udpSrcPortLB_ ||
			rule1->advrt_udpDstPortUB_ != rule2->advrt_udpDstPortUB_ || rule1->advrt_udpDstPortLB_ != rule2->advrt_udpDstPortLB_)
			return FALSE;
		 break;

	case RTL_ADVRT_SRCFILTER:
	case RTL_ADVRT_SRCFILTER_IPRANGE:
		if((rule1->advrt_srcFilterPort_ != rule2->advrt_srcFilterPort_)||
			memcmp(&rule1->advrt_srcFilterMac_, &rule2->advrt_srcFilterMac_, sizeof(ether_addr_t)) != 0||
			memcmp(&rule1->advrt_srcFilterMacMask_, &rule2->advrt_srcFilterMacMask_,sizeof(ether_addr_t)) != 0||
			(rule1->advrt_srcFilterVlanIdx_ != rule2->advrt_srcFilterVlanIdx_)||
			(rule1->advrt_srcFilterVlanIdxMask_ != rule2->advrt_srcFilterVlanIdxMask_)||
			(rule1->advrt_srcFilterIgnoreL3L4_ != rule2->advrt_srcFilterIgnoreL3L4_)||
			(rule1->advrt_srcFilterIgnoreL4_ != rule2->advrt_srcFilterIgnoreL4_))
		{
			return FALSE;
		}

		if(rule1->advrt_srcFilterIgnoreL4_==0 && rule1->advrt_srcFilterIgnoreL3L4_==0)
		{
			if((rule1->advrt_srcFilterPortUpperBound_ != rule2->advrt_srcFilterPortUpperBound_)||
			   (rule1->advrt_srcFilterPortLowerBound_ != rule2->advrt_srcFilterPortLowerBound_))
				return FALSE;
		}

		if(rule1->advrt_srcFilterIgnoreL3L4_==0)
		{
			if((rule1->advrt_srcFilterIpAddr_ != rule2->advrt_srcFilterIpAddr_)||
				(rule2->advrt_srcFilterIpAddrMask_ != rule2->advrt_srcFilterIpAddrMask_))
				return FALSE;
		}
		
		break;
		
	case RTL_ADVRT_DSTFILTER:
	case RTL_ADVRT_DSTFILTER_IPRANGE:
		if(	memcmp(&rule1->advrt_dstFilterMac_, &rule2->advrt_dstFilterMac_, sizeof(ether_addr_t)) != 0||
			memcmp(&rule1->advrt_dstFilterMacMask_, &rule2->advrt_dstFilterMacMask_,sizeof(ether_addr_t)) != 0||
			(rule1->advrt_dstFilterVlanIdx_ != rule2->advrt_dstFilterVlanIdx_)||
			(rule1->advrt_dstFilterVlanIdxMask_ != rule2->advrt_dstFilterVlanIdxMask_)||
			(rule1->advrt_dstFilterIgnoreL3L4_ != rule2->advrt_dstFilterIgnoreL3L4_)||
			(rule1->advrt_dstFilterIgnoreL4_ != rule2->advrt_dstFilterIgnoreL4_))
		{
			return FALSE;
		}

		if(rule1->advrt_dstFilterIgnoreL4_==0 && rule1->advrt_dstFilterIgnoreL4_==0)
		{
			if((rule1->advrt_dstFilterPortUpperBound_ != rule2->advrt_dstFilterPortUpperBound_)||
			   (rule1->advrt_dstFilterPortLowerBound_ != rule2->advrt_dstFilterPortLowerBound_))
				return FALSE;
		}

		if(rule1->advrt_dstFilterIgnoreL3L4_==0)
		{
			if((rule1->advrt_dstFilterIpAddr_ != rule2->advrt_dstFilterIpAddr_)||
				(rule2->advrt_dstFilterIpAddrMask_ != rule2->advrt_dstFilterIpAddrMask_))
				return FALSE;
		}
		
		break;
	default: return FALSE; /* Unknown rule type */
	
	}
	/* Compare common part */
	if (rule1->advrt_srcIpAddr_ != rule2->advrt_srcIpAddr_ || rule1->advrt_srcIpAddrMask_ != rule2->advrt_srcIpAddrMask_ ||
		rule1->advrt_dstIpAddr_ != rule2->advrt_dstIpAddr_ || rule1->advrt_dstIpAddrMask_ != rule2->advrt_dstIpAddrMask_ ||
		rule1->advrt_tos_ != rule2->advrt_tos_ || rule1->advrt_tosMask_ != rule2->advrt_tosMask_ )
		return FALSE;
	return TRUE;				
}

static int _rtl_advRt_to_acl(rtl_advRoute_entry_t *advRt, rtl865x_AclRule_t *acl)
{
	if(NULL == advRt || NULL == acl)
		return RTL_EINVALIDINPUT;
	
	switch(advRt->ruleType_)
	{		
		case RTL_ADVRT_IP:
		case RTL_ADVRT_IP_RANGE:
			memcpy(&acl->un_ty,&advRt->un_ty,sizeof(advRt->un_ty));
			acl->pktOpApp_ = advRt->pktOpApp_;
			
			if(advRt->ruleType_ == RTL_ADVRT_IP)
				acl->ruleType_ = RTL865X_ACL_IP;
			else
				acl->ruleType_ = RTL865X_ACL_IP_RANGE;
			
		break;
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
		case RTL_ADVRT_SRCFILTER:
		case RTL_ADVRT_SRCFILTER_IPRANGE:
			memcpy(&acl->un_ty,&advRt->un_ty,sizeof(advRt->un_ty));
			acl->pktOpApp_ = advRt->pktOpApp_;

			if(advRt->ruleType_ == RTL_ADVRT_SRCFILTER)
				acl->ruleType_ = RTL865X_ACL_SRCFILTER;
			else
				acl->ruleType_ = RTL865X_ACL_SRCFILTER_IPRANGE;
		break;
#endif
		default:
			panic_printk("ruletype(0x%x) is NOT support now!\n",advRt->ruleType_);
	}
	
	return SUCCESS;
}

static int _rtl_advRt_fullMatch_with_route(rtl_advRoute_entry_t *entry)
{
	int retval = FAILED;
	rtl865x_netif_local_t *dstNetif;
	rtl865x_route_t rt;

	memset(&rt,0,sizeof(rtl865x_route_t));
	
	retval = rtl865x_getRouteEntry(entry->nexthop,&rt);
	if(SUCCESS == retval)
	{
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
		if (rt.process != RT_NEXTHOP)
			return FAILED;
#endif

		dstNetif = _rtl865x_getNetifByName(entry->outIfName);
		if(rt.dstNetif == dstNetif)
			return SUCCESS;
	}
	
	return FAILED;
}

static int _rtl_flush_multiWan_redirectACL(void)
{
	rtl_advRoute_entry_t *entry;
	rtl865x_netif_local_t *netif;
	int nexthopIdx;
	int i;

	/*delete nexthop entry which used for redirectacl*/
	for(i = 0; i < RTL_ADVRT_MAX_NUM; i++)
	{
		entry = &rtl_advRt_table[i];
		if(entry->valid_)
		{	
			if(SUCCESS == _rtl_advRt_fullMatch_with_route(entry))
				continue;
			
			netif = _rtl865x_getSWNetifByName(entry->outIfName);
			if(NULL == netif)
			{
				panic_printk("====%s(%d),netif(%s) is NULL\n",__FUNCTION__,__LINE__,entry->outIfName);
				continue;
			}

			#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
			if(netif->if_type == IF_PPPOE) {
				rtl865x_ppp_t *ppp;		
	
				/* get session ID from pppoe table */
				ppp = rtl865x_getPppByNetifName(netif->name);		
				if (ppp == NULL)	
					continue;	

				nexthopIdx = rtl865x_getNxtHopIdx(NEXTHOP_DEFREDIRECT_ACL, netif, ppp->sessionId);
				if (nexthopIdx == -1) {
					 panic_printk("====%s(%d),get ppp nxthop error, nxthop(%u.%u.%u.%u)!!\n", __FUNCTION__, __LINE__, NIPQUAD(entry->nexthop));
					 continue;
				}
			} else 
			#endif
			{
				nexthopIdx = rtl865x_getNxtHopIdx(NEXTHOP_DEFREDIRECT_ACL,netif,entry->nexthop);
				if(nexthopIdx == -1)
				{
					 panic_printk("====%s(%d),get nxthop error, nxthop(%u.%u.%u.%u)!!\n",__FUNCTION__,__LINE__,NIPQUAD(entry->nexthop));
					 continue;
				}
			}
			rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL,nexthopIdx);
		}
	}

	/*delete all acl rule*/
	rtl865x_flush_allAcl_fromChain(RTL_DRV_LAN_NETIF_NAME,RTL865X_ACL_MULTIWAN_USED,RTL865X_ACL_INGRESS);

	return SUCCESS;
}

static int _rtl_rearrange_multiWan_redirectACL(void)
{
	rtl865x_AclRule_t acl_entry;
	rtl_advRoute_entry_t *entry;
	rtl865x_netif_local_t *netif;
	int nexthopIdx;
	int i,ret;
	rtl865x_arpMapping_entry_t arp;
#if defined(CONFIG_RTL_AVOID_ADDING_WAN_SUBNET_PKT_TO_HW_NAT)
	unsigned int j, wan_ip=0, wan_mask=0;
#endif

	for(i = 0; i < RTL_ADVRT_MAX_NUM; i++)
	{
		entry = &rtl_advRt_table[i];
		if(entry->valid_)
		{
			if (SUCCESS == _rtl_advRt_fullMatch_with_route(entry)) {
				#if !defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
				if ((strncmp(entry->outIfName, RTL_DRV_WAN0_NETIF_NAME, 16)==0) ||
				     (strncmp(entry->outIfName, RTL_DRV_WAN1_NETIF_NAME, 16)==0))
					rtl865x_addRoute(0,0,htonl(entry->nexthop),entry->outIfName,0);
				#endif
				
				continue;
			}

			netif = _rtl865x_getSWNetifByName(entry->outIfName);
			if(NULL == netif)
			{
				panic_printk("====%s(%d),netif(%s) is NULL\n",__FUNCTION__,__LINE__,entry->outIfName);
				continue;
			}

#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
			if(netif->if_type == IF_PPPOE) {
				rtl865x_ppp_t *ppp;		
	
				/* get session ID from pppoe table */
				ppp = rtl865x_getPppByNetifName(netif->name);		
				if (ppp == NULL)	
					continue;	

				ret = rtl865x_addNxtHop(NEXTHOP_DEFREDIRECT_ACL, NULL, netif, htonl(ppp->sessionId), htonl(entry->extIp));
				nexthopIdx = rtl865x_getNxtHopIdx(NEXTHOP_DEFREDIRECT_ACL, netif, ppp->sessionId);
				if (nexthopIdx == -1) {
					 panic_printk("====%s(%d),get ppp nxthop error, nxthop(%u.%u.%u.%u)!!\n",__FUNCTION__,__LINE__,NIPQUAD(entry->nexthop));
					 continue;
				}
			} else
#endif
			{
			/*add nexthop entry*/
			ret = rtl865x_addNxtHop(NEXTHOP_DEFREDIRECT_ACL,NULL,netif,htonl(entry->nexthop),htonl(entry->extIp));
			nexthopIdx = rtl865x_getNxtHopIdx(NEXTHOP_DEFREDIRECT_ACL,netif,entry->nexthop);
				if (nexthopIdx == -1) {
					 panic_printk("====%s(%d),get nxthop error, nxthop(%u.%u.%u.%u)!!\n",__FUNCTION__,__LINE__,NIPQUAD(entry->nexthop));
					 continue;
				}
			}

#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
			/*To fix lan pc ping dut fail when redirect acl rule setup*/
			memset(&acl_entry,0,sizeof(rtl865x_AclRule_t));

			acl_entry.ruleType_ 		= RTL865X_ACL_IP;
			acl_entry.actionType_		= RTL865X_ACL_PERMIT;
			acl_entry.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
			acl_entry.srcIpAddr_		= _br0_ip&_br0_mask;
			acl_entry.srcIpAddrMask_	= _br0_mask;
			acl_entry.dstIpAddr_		= _br0_ip&_br0_mask;
			acl_entry.dstIpAddrMask_	= _br0_mask;
			
			ret = rtl865x_add_acl(&acl_entry,RTL_DRV_LAN_NETIF_NAME,RTL865X_ACL_MULTIWAN_USED);

#if defined(CONFIG_RTL_AVOID_ADDING_WAN_SUBNET_PKT_TO_HW_NAT)
			/*wan is ppp, no need to add this rule.*/
			if (strncmp(entry->outIfName, "ppp", 3)) {
				for (j=0; j<2; j++)
				{
					extern int get_dev_ip_mask(const char * name, unsigned int *ip, unsigned int *mask);
					/*To fix dip is wan subnet, the pkt will be forward to gw by redirect acl rule*/
					memset(&acl_entry,0,sizeof(rtl865x_AclRule_t));

					if ((get_dev_ip_mask(entry->outIfName, &wan_ip, &wan_mask)==-1) ||(wan_mask==0)) {
						printk("%s[%d], get %s ip and mask fail\n", __FUNCTION__, __LINE__, entry->outIfName);
						wan_ip = entry->extIp&0xffffff00;	//default netmask is 255.255.255.0
						wan_mask = 0xffffff00;
					}
					acl_entry.ruleType_ 		= RTL865X_ACL_IP_RANGE;
					acl_entry.actionType_		= RTL865X_ACL_PERMIT;
					acl_entry.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					acl_entry.srcIpAddrLB_	= _br0_ip&_br0_mask;
					acl_entry.srcIpAddrUB_	=(_br0_ip&_br0_mask) + (~_br0_mask);
					if ((entry->nexthop&wan_mask) != (wan_ip&wan_mask)) {
						if (j == 0) {
							acl_entry.dstIpAddrLB_	= wan_ip&wan_mask;
							acl_entry.dstIpAddrUB_	= (wan_ip&wan_mask) + (~wan_mask);
						}
					} else {
						if (j == 0) {
							acl_entry.dstIpAddrLB_	= wan_ip&wan_mask;
							acl_entry.dstIpAddrUB_	= entry->nexthop - 1;
						} else if (j == 1) {
							acl_entry.dstIpAddrLB_	= entry->nexthop + 1;
							acl_entry.dstIpAddrUB_	= (wan_ip&wan_mask) + (~wan_mask);
						}
					}
					
					ret = rtl865x_add_acl(&acl_entry,RTL_DRV_LAN_NETIF_NAME,RTL865X_ACL_MULTIWAN_USED);
				}
			}
#endif
#endif
			//add acl
			memset(&acl_entry,0,sizeof(rtl865x_AclRule_t));
			_rtl_advRt_to_acl(entry,&acl_entry);

			acl_entry.actionType_ = RTL865X_ACL_DEFAULT_REDIRECT;
			acl_entry.nexthopIdx_ = nexthopIdx;

			ret = rtl865x_add_acl(&acl_entry,RTL_DRV_LAN_NETIF_NAME,RTL865X_ACL_MULTIWAN_USED);
			if(SUCCESS != ret)
			{
				rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL,nexthopIdx);
				continue;
			}

			/*callback function for sync arp/l2*/
			memset(&arp,0,sizeof(rtl865x_arpMapping_entry_t));
			ret = rtl865x_get_ps_arpMapping(entry->nexthop,&arp);
			if(SUCCESS == ret)
			{
				rtl865x_eventHandle_addArp_for_multiWan(&arp);
			}
			
			
		}
	}
	
	return SUCCESS;
}

#if 0
static int _rtl_get_advRt_num(void)
{
	int cnt = 0;
	int i = 0;
	for(i = 0; i < RTL_ADVRT_MAX_NUM; i++)
	{	
		if(rtl_advRt_table[i].valid_)
		{
			cnt++;
		}
	}

	return cnt;
}
#endif

#if defined(CONFIG_RTL_PROC_NEW)
static int32 rtl_advRt_read(struct seq_file *s, void *v)
{
	rtl_show_advRt_table(s);
	return 0;
}
#else
static int32 adv_rt_read( char *page, char **start, off_t off, int count, int *eof, void *data )
{
	int len = 0;
	rtl_show_advRt_table(page, &len);
    
	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count)
		len = count;
	if (len<0)
	  	len = 0;

	return len;
}
#endif
static int32 adv_rt_write( struct file *filp, const char *buff,unsigned long len, void *data )	
{
	char 		tmpbuf[128];
	char cmd[8];
	char outif_name[16];
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
	int bind_port_mask = 0;
#else
	int srcip_start[4];
	int srcip_end[4];
	int dst_start[4];
	int dst_end[4];
	int retval = 0;
	char netif_name[MAX_IFNAMESIZE];
#endif
	int ext_ip[4];
	int nexthop_ip[4];
	int num = 0;
//	int retval = 0;
	rtl_advRoute_entry_t rule;
	
	if (buff && !copy_from_user(tmpbuf, buff, len))
	{
		tmpbuf[len -1] = '\0';	
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
		num= sscanf(tmpbuf, "%s %d %d.%d.%d.%d %d.%d.%d.%d %s", cmd, 
			&bind_port_mask, &ext_ip[0], &ext_ip[1], &ext_ip[2], &ext_ip[3], 
			&nexthop_ip[0], &nexthop_ip[1], &nexthop_ip[2], &nexthop_ip[3], 
			outif_name);
		
		if (num !=  11) 
			return -EFAULT;		
#else
		num= sscanf(tmpbuf, "%s %d.%d.%d.%d %d.%d.%d.%d %d.%d.%d.%d %d.%d.%d.%d %d.%d.%d.%d %d.%d.%d.%d %s", cmd, 
			&srcip_start[0], &srcip_start[1], &srcip_start[2], &srcip_start[3],
			&srcip_end[0], &srcip_end[1], &srcip_end[2], &srcip_end[3],
			&dst_start[0], &dst_start[1], &dst_start[2], &dst_start[3],
			&dst_end[0], &dst_end[1], &dst_end[2], &dst_end[3],
			&ext_ip[0], &ext_ip[1], &ext_ip[2], &ext_ip[3], 
			&nexthop_ip[0], &nexthop_ip[1], &nexthop_ip[2], &nexthop_ip[3], 
			outif_name);
		
		if (num !=  26) 
			return -EFAULT;		
#endif
		if(strlen(outif_name) >= 15)
			return -EFAULT;

#if !defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
		retval = rtl865x_get_drvNetifName_by_psName(outif_name,netif_name);
		if(retval != SUCCESS)
			return -EFAULT;
#endif		
		memset(&rule,0,sizeof(rtl_advRoute_entry_t));
		rule.extIp = (ext_ip[0]<<24)|(ext_ip[1]<<16)|(ext_ip[2]<<8)|(ext_ip[3]<<0);
		rule.nexthop = (nexthop_ip[0]<<24)|(nexthop_ip[1]<<16)|(nexthop_ip[2]<<8)|(nexthop_ip[3]<<0);
		rule.pktOpApp_ = 6;
		rule.valid_ = 1;
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
		if (rule.nexthop == 0)
			return -EFAULT;
		memcpy(rule.outIfName,outif_name,strlen(outif_name));		
		rule.outIfName[strlen(outif_name)+1] ='\0';
		rule.ruleType_ 					= RTL_ADVRT_SRCFILTER;
		rule.advrt_srcFilterPort_			= bind_port_mask & (RTL_LANPORT_MASK&(~0x100));
		rule.advrt_srcFilterIpAddr_			= _br0_ip&_br0_mask;
		rule.advrt_srcFilterIpAddrMask_		= _br0_mask;
		rule.advrt_srcFilterPortMask_		= RTL_LANPORT_MASK&(~0x100);
		rule.advrt_srcFilterIgnoreL4_		= 1;
#else
		memcpy(rule.outIfName,netif_name,strlen(netif_name));		
		rule.outIfName[strlen(netif_name)+1] ='\0';
		
		rule.ruleType_ = RTL_ADVRT_IP_RANGE;
		rule.advrt_srcIpAddrStart_ = (srcip_start[0]<<24)|(srcip_start[1]<<16)|(srcip_start[2]<<8)|(srcip_start[3]<<0);
		rule.advrt_srcIpAddrEnd_ = (srcip_end[0]<<24)|(srcip_end[1]<<16)|(srcip_end[2]<<8)|(srcip_end[3]<<0);
		rule.advrt_dstIpAddrStart_ = (dst_start[0]<<24)|(dst_start[1]<<16)|(dst_start[2]<<8)|(dst_start[3]<<0);
		rule.advrt_dstIpAddrEnd_ = (dst_end[0]<<24)|(dst_end[1]<<16)|(dst_end[2]<<8)|(dst_end[3]<<0);
#endif
		
		if((strcmp(cmd, "add")==0) || (strcmp(cmd, "ADD")==0))
		{
			rtl_add_advRt_entry(&rule);
		}
		else if((strcmp(cmd, "del")==0) || (strcmp(cmd, "DEL")==0))
		{
			rtl_del_advRt_entry(&rule);
		}
		
	}
	return len;
}

#if defined(CONFIG_RTL_PROC_NEW)
int rtl_advRt_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, rtl_advRt_read, NULL));
}
static ssize_t rtl_advRt_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	    return adv_rt_write(file, userbuf,count, off);
}
struct file_operations rtl_advRt_proc_fops= {
        .open           = rtl_advRt_single_open,
        .write		    = rtl_advRt_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#endif

int rtl_exit_advRt(void)
{
	_rtl_flush_multiWan_redirectACL();
	/*unregist the acl chain*/
	rtl865x_unRegist_aclChain(RTL_DRV_LAN_NETIF_NAME,RTL865X_ACL_MULTIWAN_USED,RTL865X_ACL_INGRESS);
	memset(rtl_advRt_table,0,RTL_ADVRT_MAX_NUM*sizeof(rtl_advRoute_entry_t));
	/*switch back old netdecision policy*/
	rtl865xC_setNetDecisionPolicy(oldNetDecision);	
	if(adv_rt_entry)
	{
	#if defined(CONFIG_RTL_PROC_NEW)
		remove_proc_entry("adv_rt", &proc_root);
	#else
		remove_proc_entry("adv_rt",NULL);
	#endif
		adv_rt_entry = NULL;
	}
	return SUCCESS;
}

int rtl_init_advRt(void)
{	
	if(adv_rt_entry)
	{
	#if defined(CONFIG_RTL_PROC_NEW)
		remove_proc_entry("adv_rt", &proc_root);
	#else
		remove_proc_entry("adv_rt",NULL);
	#endif
		adv_rt_entry = NULL;
	}

#if defined(CONFIG_RTL_PROC_NEW)
	adv_rt_entry = proc_create_data("adv_rt", 0, &proc_root,
			 &rtl_advRt_proc_fops, NULL);
#else
	adv_rt_entry = create_proc_entry("adv_rt", 0, NULL);
	if(adv_rt_entry)
	{
		adv_rt_entry->read_proc = adv_rt_read;
		adv_rt_entry->write_proc = adv_rt_write;
		
	}
#endif
	memset(rtl_advRt_table,0,RTL_ADVRT_MAX_NUM*sizeof(rtl_advRoute_entry_t));
	rtl865x_regist_aclChain(RTL_DRV_LAN_NETIF_NAME,RTL865X_ACL_MULTIWAN_USED,RTL865X_ACL_INGRESS);
#if !defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
	//switch to mac based
	rtl865xC_getNetDecisionPolicy(&oldNetDecision);
	rtl865xC_setNetDecisionPolicy(NETIF_MAC_BASED );
#endif
	rtl865x_setDefACLForNetDecisionMiss(RTL865X_ACLTBL_IPV6_TO_CPU,RTL865X_ACLTBL_PERMIT_ALL,RTL865X_ACLTBL_PERMIT_ALL,RTL865X_ACLTBL_PERMIT_ALL);
	return SUCCESS;
}

rtl_advRoute_entry_t* rtl_get_advRt_entry_by_nexthop(ipaddr_t nexthop)
{
	int i;
	rtl_advRoute_entry_t *tmp_entry;
	for(i = 0; i < RTL_ADVRT_MAX_NUM; i++)
	{
		tmp_entry = &rtl_advRt_table[i];
		if(tmp_entry->valid_)
		{
			if(tmp_entry->nexthop == nexthop)
				return tmp_entry;
		}
	}
	return NULL;	
}

int rtl_add_advRt_entry(rtl_advRoute_entry_t *entry)
{	
	int i;
	rtl_advRoute_entry_t *tmp_entry,*ready_entry;	
	if(NULL == entry)
		return RTL_EINVALIDINPUT;

	ready_entry = NULL;
	
	/*duplicate check & try to find a usable entry*/
	for(i = 0; i < RTL_ADVRT_MAX_NUM; i++)
	{
		tmp_entry = &rtl_advRt_table[i];
		if(tmp_entry->valid_)
		{
			if(_rtl_same_AdvRt_rule(entry,tmp_entry))
				return RTL_EENTRYALREADYEXIST;
		}
		else
		{
			if(NULL==ready_entry)
				ready_entry = &rtl_advRt_table[i];
		}
	}

	if(NULL == ready_entry)
		return RTL_ENOFREEBUFFER;

	/*flush acl firstly*/
	_rtl_flush_multiWan_redirectACL();
	
	/*add entry*/
	memcpy(ready_entry,entry,sizeof(rtl_advRoute_entry_t));
	ready_entry->valid_ = 1;

	_rtl_rearrange_multiWan_redirectACL();
	
	return SUCCESS;
}

int rtl_del_advRt_entry(rtl_advRoute_entry_t *entry)
{
	int i;
	rtl_advRoute_entry_t *tmp_entry;	
	if(NULL == entry)
		return RTL_EINVALIDINPUT;

	for(i = 0; i < RTL_ADVRT_MAX_NUM; i++)
	{
		tmp_entry = &rtl_advRt_table[i];
		if(tmp_entry->valid_)
		{
			if(_rtl_same_AdvRt_rule(entry,tmp_entry))
				break;
		}
	}

	if(RTL_ADVRT_MAX_NUM == i)
		return RTL_EENTRYNOTFOUND;

	/*flush acl firstly*/
	_rtl_flush_multiWan_redirectACL();
	
	/*delete entry*/
	memset(tmp_entry,0,sizeof(rtl_advRoute_entry_t));

	/*rearrange for redirect acl*/
	_rtl_rearrange_multiWan_redirectACL();
	return SUCCESS;
}

int rtl_enable_advRt_by_netifName(const char *name)
{
	int i;
	_rtl_flush_multiWan_redirectACL();
	for(i = 0;i < RTL_ADVRT_MAX_NUM;i++)
	{
		if(strcmp(rtl_advRt_table[i].outIfName,name) == 0)
			rtl_advRt_table[i].valid_ = 1;
	}
	_rtl_rearrange_multiWan_redirectACL();

	return SUCCESS;
}
int rtl_disable_advRt_by_netifName(const char *name)
{
	int i;

	#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
	int num = 0;
	unsigned char ppp_name[16];

	if (strncmp(name, ALIASNAME_ETH_WAN, strlen(ALIASNAME_ETH_WAN)) == 0) {
		num = name[strlen(name)-1] - '0';
		if ((num>0) && (num<8))
			sprintf(ppp_name, "ppp%d", num);
	}
	#endif
	_rtl_flush_multiWan_redirectACL();
	for(i = 0;i < RTL_ADVRT_MAX_NUM;i++)
	{
		if(strcmp(rtl_advRt_table[i].outIfName,name) == 0)
			rtl_advRt_table[i].valid_ = 0;
		/*Delete the matched ppp dev rule too.*/
		#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
		if(strncmp(rtl_advRt_table[i].outIfName, ppp_name, 16) == 0)
			rtl_advRt_table[i].valid_ = 0;
		#endif
	}
	_rtl_rearrange_multiWan_redirectACL();

	return SUCCESS;
}

int rtl_is_gw_ip_by_dev_name(char *name, ipaddr_t ip)
{
	int i;

	for (i = 0;i < RTL_ADVRT_MAX_NUM;i++)
	{
		if (rtl_advRt_table[i].valid_ == 1) {
			if ((strcmp(rtl_advRt_table[i].outIfName,name)==0) && (rtl_advRt_table[i].nexthop==ip))
				return TRUE;
		}
	}

	return FALSE;
}

