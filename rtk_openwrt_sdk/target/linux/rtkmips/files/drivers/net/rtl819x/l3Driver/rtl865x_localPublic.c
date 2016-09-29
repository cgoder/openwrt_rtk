/*
 *
 *  Copyright (c) 2011 Realtek Semiconductor Corp.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include <net/rtl/rtl_types.h>
//#include "rtl_utils.h"
#include <net/rtl/rtl_queue.h>
#include <net/rtl/rtl_glue.h>
#include <net/rtl/rtl865x_localPublic.h>
#include "common/rtl_errno.h"

#include "AsicDriver/rtl865x_asicCom.h"
#include "AsicDriver/rtl865xc_asicregs.h"
#include <net/rtl/rtl865x_netif.h>
#include "common/rtl865x_netif_local.h"
#include "common/rtl865x_vlan.h"

#include "l3Driver/rtl865x_ip.h"
//#include "l3Driver/rtl865x_ppp.h"
#include "l3Driver/rtl865x_ppp_local.h"
#include "l3Driver/rtl865x_route.h"
#include "l3Driver/rtl865x_arp.h"
#include "l3Driver/rtl865x_nexthop.h"
#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
#include <l2Driver/rtl865x_outputQueue.h>
#endif

#include <linux/ip.h>
#include <linux/if_arp.h>
#include <linux/udp.h>
#include <linux/proc_fs.h>
//#include <linux/jiffies.h>

/*for dhcp protocol */

/*****************************************************************/
/* Do not modify below here unless you know what you are doing!! */
/*****************************************************************/

/* DHCP protocol -- see RFC 2131 */
#define SERVER_PORT		67
#define CLIENT_PORT		68

#define DHCP_MAGIC		0x63825363

/* DHCP option codes (partial list) */
#define DHCP_PADDING		0x00
#define DHCP_SUBNET		0x01
#define DHCP_TIME_OFFSET	0x02
#define DHCP_ROUTER		0x03
#define DHCP_TIME_SERVER	0x04
#define DHCP_NAME_SERVER	0x05
#define DHCP_DNS_SERVER		0x06
#define DHCP_LOG_SERVER		0x07
#define DHCP_COOKIE_SERVER	0x08
#define DHCP_LPR_SERVER		0x09
#define DHCP_HOST_NAME		0x0c
#define DHCP_BOOT_SIZE		0x0d
#define DHCP_DOMAIN_NAME	0x0f
#define DHCP_SWAP_SERVER	0x10
#define DHCP_ROOT_PATH		0x11
#define DHCP_IP_TTL		0x17
#define DHCP_MTU		0x1a
#define DHCP_BROADCAST		0x1c
#define DHCP_NTP_SERVER		0x2a
#define DHCP_WINS_SERVER	0x2c
#define DHCP_REQUESTED_IP	0x32
#define DHCP_LEASE_TIME		0x33
#define DHCP_OPTION_OVER	0x34
#define DHCP_MESSAGE_TYPE	0x35
#define DHCP_SERVER_ID		0x36
#define DHCP_PARAM_REQ		0x37
#define DHCP_MESSAGE		0x38
#define DHCP_MAX_SIZE		0x39
#define DHCP_T1			0x3a
#define DHCP_T2			0x3b
#define DHCP_VENDOR		0x3c
#define DHCP_CLIENT_ID		0x3d
#define DHCP_FQDN		0x51

#define DHCP_END		0xFF


#define BOOTREQUEST		1
#define BOOTREPLY		2

#define ETH_10MB		1
#define ETH_10MB_LEN		6

#define DHCPDISCOVER		1
#define DHCPOFFER		2
#define DHCPREQUEST		3
#define DHCPDECLINE		4
#define DHCPACK			5
#define DHCPNAK			6
#define DHCPRELEASE		7
#define DHCPINFORM		8

#define BROADCAST_FLAG		0x8000

#define OPTION_FIELD		0
#define FILE_FIELD		1
#define SNAME_FIELD		2

/* miscellaneous defines */
#define OPT_CODE 0
#define OPT_LEN 1
#define OPT_DATA 2

struct dhcp_option {
	char name[12];
	char flags;
	unsigned char code;
};


struct dhcpMessage {
	unsigned char op;
	unsigned char htype;
	unsigned char hlen;
	unsigned char hops;
	uint32 xid;
	uint16 secs;
	uint16 flags;
	unsigned int ciaddr;
	unsigned int yiaddr;
	unsigned int siaddr;
	unsigned int giaddr;
	unsigned char  chaddr[16];
	unsigned char sname[64];
	unsigned char file[128];
	unsigned int cookie;
	unsigned char options[308]; /* 312 - cookie */
};

/* get an option with bounds checking (warning, not aligned). */
unsigned char  *get_dhcpOption(struct dhcpMessage *packet, int code)
{
	int i, length;
	unsigned char  *optionptr;
	int over = 0, done = 0, curr = OPTION_FIELD;

	optionptr = packet->options;
	i = 0;
	length = 308;
	while (!done) {
		if (i >= length) {
			//printk("bogus packet, option fields too long");
			return NULL;
		}
		if (optionptr[i + OPT_CODE] == code) {
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				//printk("bogus packet, option fields too long");
				return NULL;
			}
			return optionptr + i + 2;
		}
		switch (optionptr[i + OPT_CODE]) {
		case DHCP_PADDING:
			i++;
			break;
		case DHCP_OPTION_OVER:
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				//printk("bogus packet, option fields too long");
				return NULL;
			}
			over = optionptr[i + 3];
			i += optionptr[OPT_LEN] + 2;
			break;
		case DHCP_END:
			if (curr == OPTION_FIELD && over & FILE_FIELD) {
				optionptr = packet->file;
				i = 0;
				length = 128;
				curr = FILE_FIELD;
			} else if (curr == FILE_FIELD && over & SNAME_FIELD) {
				optionptr = packet->sname;
				i = 0;
				length = 64;
				curr = SNAME_FIELD;
			} else done = 1;
			break;
		default:
			i += optionptr[OPT_LEN + i] + 2;
		}
	}
	return NULL;
}
/**********************************************************************/

//#define CONFIG_RTL_LOCAL_PUBLIC_DEBUG

typedef CTAILQ_HEAD(_rtl865x_localPublicList,  rtl865x_localPublic) rtl865x_localPublicList;

#if defined(CONFIG_RTL_PUBLIC_SSID)
static struct list_head public_ssid_list_head;
static struct proc_dir_entry *public_ssid_proc_entry;
static char public_ssid_netif[4][16];
#endif
static struct proc_dir_entry *localPublicProcEntry;
static unsigned int localPublicInitialized=FALSE;	
static unsigned int localPublicEnabled=FALSE;	

static rtl865x_localPublicList freeLocalPublicList;
static rtl865x_localPublicList usedLocalPublicList ;

static struct rtl865x_localPublic* localPublicPool;
static unsigned int maxLocalPublicNum;
static struct rtl865x_interface_info wanIfInfo;
static struct rtl865x_interface_info lanIfInfo;
static unsigned char zeroMac[6]={0,0,0,0,0,0};
static enum ENUM_NETDEC_POLICY savedNetDecPolicy;

/*for network interface decision missed defaul acl usage*/
static char savedDefInAclStart;
static char savedDefInAclEnd;
static char savedDefOutAclStart;
static char savedDefOutAclEnd;

static char mCastNetIf[16]={"mCastNetIf"};
static char mCastNetIfMac[6]={ 0x00, 0x11, 0x12, 0x13, 0x14, 0x15 };
static int rtl865x_getAllHWLocalPublic(struct rtl865x_localPublic localPublicArray [ ],int arraySize);
static int rtl865x_addOutboundRedirectAcl(struct rtl865x_localPublic *entry);
static int rtl865x_delOutboundRedirectAcl(struct rtl865x_localPublic *entry);


static struct rtl865x_localPublic* rtl865x_searchLocalPublic(unsigned int ipAddr)
{
	struct rtl865x_localPublic* entry;
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		if(entry->ipAddr==ipAddr)
		{
			return  entry;
		}	
		
	}

	return NULL;
}

static int rtl865x_cntTotalLocalPublicNum(void)
{
	struct rtl865x_localPublic* entry;
	unsigned int cnt=0;

	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		cnt++;
	}

	return cnt;
}

static int rtl865x_cntHwLocalPublicNum(void)
{
	struct rtl865x_localPublic* entry;
	unsigned int hwCnt=0;

	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		if(entry->hw)
		{
			hwCnt++;
		}
	}

	return hwCnt;
}

#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
int rtl_checkLocalPublicNetifIngressRule(rtl865x_AclRule_t *rule)
{
	int	i;
	struct rtl865x_localPublic		lp[MAX_HW_LOCAL_PUBLIC_NUM];
	
	if (rtl865x_cntHwLocalPublicNum()==0 || rule==NULL)
		return FAILED;

	memset(lp, 0, sizeof(struct rtl865x_localPublic)*MAX_HW_LOCAL_PUBLIC_NUM);
	
	rtl865x_getAllHWLocalPublic(lp, MAX_HW_LOCAL_PUBLIC_NUM);
	
	switch (rule->ruleType_)
	{
		case	RTL865X_ACL_IP:
		case	RTL865X_ACL_ICMP:
		case	RTL865X_ACL_IGMP:
		case	RTL865X_ACL_TCP:
		case	RTL865X_ACL_UDP:
		{
			for (i=0;i<MAX_HW_LOCAL_PUBLIC_NUM;i++)
			{
				if (lp[i].hw&&(((lp[i].ipAddr&rule->dstIpAddrMask_)==(rule->dstIpAddr_&rule->dstIpAddrMask_))))
				{
					rtl865x_del_acl(rule, lp[i].lpNetif, RTL865X_ACL_QOS_USED0);
					rtl865x_add_acl(rule, lp[i].lpNetif, RTL865X_ACL_QOS_USED0);
				}

				if((rule->dstIpAddr_&0xf0000000)==0xe0000000)
				{
					rtl865x_del_acl(rule, "virtualNetif", RTL865X_ACL_QOS_USED0);
					rtl865x_add_acl(rule, "virtualNetif", RTL865X_ACL_QOS_USED0);
				}
			}
			break;
		}
		case	RTL865X_ACL_IP_RANGE:
		case	RTL865X_ACL_ICMP_IPRANGE:
		case	RTL865X_ACL_IGMP_IPRANGE:
		case	RTL865X_ACL_TCP_IPRANGE:
		case	RTL865X_ACL_UDP_IPRANGE:
		{
			for (i=0;i<MAX_HW_LOCAL_PUBLIC_NUM;i++)
			{
				if (lp[i].hw&&(((lp[i].ipAddr>rule->dstIpAddrLB_)&&(lp[i].ipAddr<rule->dstIpAddrUB_))))
				{
					rtl865x_del_acl(rule, lp[i].lpNetif, RTL865X_ACL_QOS_USED0);
					rtl865x_add_acl(rule, lp[i].lpNetif, RTL865X_ACL_QOS_USED0);
				}

				if (((rule->dstIpAddrLB_&0xf0000000)==0xe0000000)&&((rule->dstIpAddrUB_&0xf0000000)==0xe0000000))
				{
					rtl865x_del_acl(rule, "virtualNetif", RTL865X_ACL_QOS_USED0);
					rtl865x_add_acl(rule, "virtualNetif", RTL865X_ACL_QOS_USED0);
				}
			}
			break;
		}
		default:
			break;
	}

	return FAILED;
}
#endif

static struct rtl865x_localPublic* rtl865x_allocLocalPublic(void)
{
	struct rtl865x_localPublic* entry=NULL;

	entry = CTAILQ_FIRST(&freeLocalPublicList);
	
	if(entry!=NULL)
	{
		CTAILQ_REMOVE(&freeLocalPublicList, entry, next);
		memset(entry, 0 , sizeof (struct rtl865x_localPublic));
	}
	
	return entry;
	
}

static int rtl865x_copyLocalPublic(struct rtl865x_localPublic* to, struct rtl865x_localPublic* from)
{
	if((from==NULL) || (to==NULL))
	{
		return FAILED;
	}

	to->ipAddr = from->ipAddr;	
	to->netMask= from->netMask;	
	to->defGateway= from->defGateway;	
		
	strcpy(to->dev, from->dev);
	memcpy(to->mac, from->mac, 6);
	memcpy(to->defGwMac, from->defGwMac, 6);
	strcpy(to->lpNetif, from->lpNetif);
	
	to->hw = from->hw;
	
	return SUCCESS;
}

void rtl865x_flushHwLpOutRedirectAcl(void)
{
	int i=0;
	struct rtl865x_localPublic lpArray[MAX_HW_LOCAL_PUBLIC_NUM];
	int hwLpCnt = 0;
	
	memset(lpArray,0,sizeof(struct rtl865x_localPublic) * MAX_HW_LOCAL_PUBLIC_NUM);
	hwLpCnt = rtl865x_getAllHWLocalPublic(lpArray,MAX_HW_LOCAL_PUBLIC_NUM);
	for(i = 0;i<hwLpCnt;i++)
	{
		rtl865x_delOutboundRedirectAcl(&lpArray[i]);
	}
	return;
}

void rtl865x_reArrangeHwLpOutRedirectAcl(void)
{
	int i=0;
	struct rtl865x_localPublic lpArray[MAX_HW_LOCAL_PUBLIC_NUM];
	int hwLpCnt = 0;
	
	memset(lpArray,0,sizeof(struct rtl865x_localPublic) * MAX_HW_LOCAL_PUBLIC_NUM);
	hwLpCnt = rtl865x_getAllHWLocalPublic(lpArray,MAX_HW_LOCAL_PUBLIC_NUM);
	for(i = 0;i<hwLpCnt;i++)
	{
		
		rtl865x_addOutboundRedirectAcl(&lpArray[i]);
	}
	
	return;		
}	

int rtl865x_addLocalPublic(struct rtl865x_localPublic* newEntry)
{
	struct rtl865x_localPublic* entry;
	
	if(localPublicInitialized==FALSE)
	{
		return FAILED;
	}
	
	if(newEntry==NULL)
	{
		return SUCCESS;
	}
	
	if(newEntry->hw)
	{
		if(rtl865x_cntHwLocalPublicNum()>=MAX_HW_LOCAL_PUBLIC_NUM)
		{
			return FAILED;
		}
	}
	
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		if(entry->ipAddr == newEntry->ipAddr)
		{
			/*local public entry has already existed*/
			return SUCCESS;
		}
	}

	if(newEntry->ipAddr==0)
	{
		return FAILED;
	}

	if(newEntry->hw && (newEntry->defGateway==0))
	{
		return FAILED;
	}
	
	
	//hyking:when add hw local public, please change the redirect ACL...
		rtl865x_flushHwLpOutRedirectAcl();

	
	entry=rtl865x_allocLocalPublic();

	rtl865x_copyLocalPublic(entry, newEntry);	
	
	if(entry!=NULL)
	{
		CTAILQ_INSERT_TAIL(&usedLocalPublicList,entry,next);
	}

	if(localPublicEnabled==FALSE)
	{
		localPublicEnabled=TRUE;
	}
	
	//hyking:when add hw local public, please change the redirect ACL...
		rtl865x_reArrangeHwLpOutRedirectAcl();

	
	return SUCCESS;
	
}

static int rtl865x_addInboundAclToCpu(struct rtl865x_localPublic *entry)
{
	rtl865x_AclRule_t	rule;
	enum ENUM_NETDEC_POLICY policy; 
	int ret=-1;
	
	
	
	//printk("%s:%d\n",__FUNCTION__,__LINE__);
	
	rtl865xC_getNetDecisionPolicy( &policy);
	
	/*add acl rule at wan side to trap local public mac*/
	if(policy!=NETIF_MAC_BASED)
	{
		if(entry->hw)
	{
			return FAILED;
		}
		
		if(wanIfInfo.ifname[0]=='\0')
		{
			return FAILED;
		}
		bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
		rule.ruleType_ = RTL865X_ACL_MAC;
		rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
		rule.actionType_ = RTL865X_ACL_TOCPU;
		memset(rule.dstMacMask_.octet, 0xff, ETHER_ADDR_LEN);
		memcpy(rule.dstMac_.octet, entry->mac, ETHER_ADDR_LEN);
		ret=rtl865x_add_acl(&rule, wanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
	}	
	return ret;
}

static int rtl865x_delInboundAclToCpu(struct rtl865x_localPublic *entry)
{
	rtl865x_AclRule_t	rule;
	enum ENUM_NETDEC_POLICY policy; 
	int ret=-1;
	
	
	rtl865xC_getNetDecisionPolicy( &policy);
	//printk("%s:%d\n",__FUNCTION__,__LINE__);
	/*del acl rule at wan side*/
	if(policy!=NETIF_MAC_BASED)
	{
	if(entry->hw)
	{
		return FAILED;
	}

		if(wanIfInfo.ifname[0]=='\0')
		{
			return FAILED;
		}
		
		bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
		rule.ruleType_ = RTL865X_ACL_MAC;
		rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
		rule.actionType_ = RTL865X_ACL_TOCPU;
		memset(rule.dstMacMask_.octet, 0xff, ETHER_ADDR_LEN);
		memcpy(rule.dstMac_.octet, entry->mac, ETHER_ADDR_LEN);
		
		ret=rtl865x_del_acl(&rule, wanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
	}
	return ret;

}

static void rtl865x_addNetifMissedDefAclForLP(void)
{
	rtl865x_AclRule_t	rule;
	int ret;
	rtl865x_route_t routeTbl[RT_DRV_ENTRY_NUM];
	int routeCnt, i;

	ret=-1;
	/*permit multicast data*/
	/*delete old acl rule*/
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_PERMIT;
#if 0
	memset(rule.dstMacMask_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMacMask_.octet[0]=0xff;
	rule.dstMacMask_.octet[1]=0xff;
	rule.dstMacMask_.octet[2]=0xff;
	
	memset(rule.dstMac_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMac_.octet[0]=0x01;
	rule.dstMac_.octet[1]=0x00;
	rule.dstMac_.octet[2]=0x5e;
	ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);
	//printk("%s:%d, ret is %d\n",__FUNCTION__,__LINE__,ret);
	/*add new acl rule*/
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_PERMIT;
	memset(rule.dstMacMask_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMacMask_.octet[0]=0xff;
	rule.dstMacMask_.octet[1]=0xff;
	rule.dstMacMask_.octet[2]=0xff;
	
	memset(rule.dstMac_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMac_.octet[0]=0x01;
	rule.dstMac_.octet[1]=0x00;
	rule.dstMac_.octet[2]=0x5e;
	ret=rtl865x_add_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);
#else
	memset(rule.dstMacMask_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMacMask_.octet[0]=0x01;
	memset(rule.dstMac_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMac_.octet[0]=0x01;
	ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);
	//printk("%s:%d, ret is %d\n",__FUNCTION__,__LINE__,ret);
	/*add new acl rule*/
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_PERMIT;
	memset(rule.dstMacMask_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMacMask_.octet[0]=0x01;
	memset(rule.dstMac_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMac_.octet[0]=0x01;
	ret=rtl865x_add_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);

	//permit arp
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_PERMIT;	
	rule.typeLen_ = 0x0806;
	rule.typeLenMask_ = 0xffff;
	ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);

	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_PERMIT;	
	rule.typeLen_ = 0x0806;
	rule.typeLenMask_ = 0xffff;
	ret=rtl865x_add_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);
	
	//for lan side netbios...
	routeCnt=rtl865x_getLanRoute(routeTbl,RT_DRV_ENTRY_NUM);
	for(i=0;i<routeCnt;i++)
	{		
		if((routeTbl[i].ipMask!=0xFFFFFFFF) && (routeTbl[i].ipMask!=0))
		{
			bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
			rule.ruleType_ = RTL865X_ACL_IP;
			rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
			rule.actionType_ = RTL865X_ACL_PERMIT;
			rule.dstIpAddr_ = routeTbl[i].ipAddr;
			rule.dstIpAddrMask_ = routeTbl[i].ipMask;
			rule.srcIpAddr_ = routeTbl[i].ipAddr;
			rule.srcIpAddrMask_ = routeTbl[i].ipMask;
			ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);
			/*add new acl rule*/
			bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
			rule.ruleType_ = RTL865X_ACL_IP;
			rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
			rule.actionType_ = RTL865X_ACL_PERMIT;
			rule.dstIpAddr_ = routeTbl[i].ipAddr;
			rule.dstIpAddrMask_ = routeTbl[i].ipMask;
			rule.srcIpAddr_ = routeTbl[i].ipAddr;
			rule.srcIpAddrMask_ = routeTbl[i].ipMask;
		ret=rtl865x_add_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED); 
		}
	}
#endif
	//printk("%s:%d, ret is %d\n",__FUNCTION__,__LINE__,ret);
	/*-------------------------------------------------------------*/
	/*to make sure last one is to cpu*/
	/*delete old acl rule*/
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_TOCPU;
	ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);
	/*add new acl rule*/
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_TOCPU;
	ret=rtl865x_add_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED); 
	//printk("%s:%d, ret is %d\n",__FUNCTION__,__LINE__,ret);
	return;	
}

static void rtl865x_delNetifMissedDefAclForLP(void)
{
	rtl865x_AclRule_t	rule;
	int ret=-1;
	int routeCnt, i;
	rtl865x_route_t routeTbl[RT_DRV_ENTRY_NUM];
	
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_PERMIT;
	memset(rule.dstMacMask_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMacMask_.octet[0]=0x01;
	memset(rule.dstMac_.octet, 0, ETHER_ADDR_LEN);
	rule.dstMac_.octet[0]=0x01;
	ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);

	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_PERMIT;	
	rule.typeLen_ = 0x0806;
	rule.typeLenMask_ = 0xffff;
	ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);

	routeCnt=rtl865x_getLanRoute(routeTbl,RT_DRV_ENTRY_NUM);
	for(i=0;i<routeCnt;i++)
	{
		if((routeTbl[i].ipMask!=0xFFFFFFFF) && (routeTbl[i].ipMask!=0))
		{
			bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
			rule.ruleType_ = RTL865X_ACL_IP;
			rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
			rule.actionType_ = RTL865X_ACL_PERMIT;
			rule.dstIpAddr_ = routeTbl[i].ipAddr;
			rule.dstIpAddrMask_ = routeTbl[i].ipMask;
			rule.srcIpAddr_ = routeTbl[i].ipAddr;
			rule.srcIpAddrMask_ = routeTbl[i].ipMask;
			ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);		
		}
	}
	
	/*-------------------------------------------------------------*/
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_MAC;
	rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
	rule.actionType_ = RTL865X_ACL_TOCPU;
	ret=rtl865x_del_acl(&rule, "virtualNetif", RTL865X_ACL_SYSTEM_USED);

	
	
	return;	
}

static int rtl865x_addAllInboundAclToCpu(void)
{
	struct rtl865x_localPublic* entry;
	enum ENUM_NETDEC_POLICY policy; 

	
	rtl865xC_getNetDecisionPolicy( &policy);
	if(policy==NETIF_MAC_BASED)
	{
		rtl865x_addNetifMissedDefAclForLP();
		
	}
	else
	{
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		rtl865x_addInboundAclToCpu(entry);
	}
	}
	return SUCCESS;
}

static int rtl865x_delAllInboundAclToCpu(void)
{
	struct rtl865x_localPublic* entry;
	enum ENUM_NETDEC_POLICY policy; 

	rtl865xC_getNetDecisionPolicy( &policy);
	if(policy==NETIF_MAC_BASED)
	{
		rtl865x_delNetifMissedDefAclForLP();
	}
	else
	{
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		rtl865x_delInboundAclToCpu(entry);
	}
	}
	return SUCCESS;
}
static int rtl865x_addMCastNetif(void)
{
	rtl865x_netif_t netif;
	int ret=FAILED;
	
	rtl865x_delVlan(MCAST_NETIF_VLAN_ID);
	rtl865x_addVlan(MCAST_NETIF_VLAN_ID);
	ret=rtl865x_addVlanPortMember(MCAST_NETIF_VLAN_ID,wanIfInfo.memPort);
	ret=rtl865x_setVlanFilterDatabase(MCAST_NETIF_VLAN_ID,wanIfInfo.fid);
	
	if(_rtl865x_getNetifByName(mCastNetIf)!=NULL)
	{
		return SUCCESS;
	}
	
	memset(&netif, 0, sizeof(rtl865x_netif_t));
	strcpy(netif.name, mCastNetIf);
	memcpy(&netif.macAddr, mCastNetIfMac, 6);;
	netif.mtu = 1500;
	netif.if_type = IF_ETHER;
	netif.vid = MCAST_NETIF_VLAN_ID;
	netif.is_wan = 1;
	netif.is_slave = 0;
	netif.enableRoute=1;
	netif.forMacBasedMCast=TRUE;
	//printk("%s:%d,entry->lpNetif is %s \n",__FUNCTION__,__LINE__,entry->lpNetif);
	ret = rtl865x_addNetif(&netif);
	if(ret!=SUCCESS)
	{
		rtl865x_delVlan(MCAST_NETIF_VLAN_ID);
		return FAILED;
	}

#if defined(CONFIG_RTK_VLAN_SUPPORT)
	{
		rtl865x_AclRule_t	rule;
		bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
		rule.ruleType_ = RTL865X_ACL_MAC;
		rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
		rule.actionType_ = RTL865X_ACL_PERMIT;
		ret=rtl865x_add_acl(&rule, mCastNetIf, RTL865X_ACL_SYSTEM_USED);
	}
#endif

	return ret;
}

static int rtl865x_delMCastNetif(void)
{
	int ret=FAILED;

#if defined(CONFIG_RTK_VLAN_SUPPORT)
	{
		rtl865x_AclRule_t	rule;
		bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
		rule.ruleType_ = RTL865X_ACL_MAC;
		rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
		rule.actionType_ = RTL865X_ACL_PERMIT;
		ret=rtl865x_del_acl(&rule, mCastNetIf, RTL865X_ACL_SYSTEM_USED);
	}
#endif

	ret=rtl865x_delNetif(mCastNetIf);

	if(ret==SUCCESS)
	{
		ret=rtl865x_delVlan(MCAST_NETIF_VLAN_ID);
	}
	return ret;
	
}

int rtl865x_setMCastSrcMac(unsigned char *srcMac)
{

	if(srcMac==NULL)
	{
		return FAILED;
	}
	
	memcpy(mCastNetIfMac, srcMac, 6);

	if(_rtl865x_getNetifByName(mCastNetIf)!=NULL)
	{
		rtl865x_delMCastNetif();
		rtl865x_addMCastNetif();
	}
	
	return SUCCESS;
}

static int rtl865x_addLocalPublicExtIp(struct rtl865x_localPublic *entry)
{
	int ret=FAILED;
	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}
	
	ret=rtl865x_addIp(entry->ipAddr, entry->ipAddr, IP_TYPE_LOCALSERVER);
	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);

	return ret;
}


static int rtl865x_delLocalPublicExtIp(struct rtl865x_localPublic *entry)
{
	int ret=FAILED;
	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}
	
	ret=rtl865x_delIp(entry->ipAddr);
	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
	return ret;
}


static int rtl865x_addLocalPublicRoute(struct rtl865x_localPublic *entry)
{
	int ret;
	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}
	
	ret=rtl865x_addRoute(entry->ipAddr,0xFFFFFFFF, entry->ipAddr, lanIfInfo.ifname,0);
	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
	return SUCCESS;

}

static int rtl865x_delLocalPublicRoute(struct rtl865x_localPublic *entry)
{
	int ret=FAILED;
	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}
	
	ret=rtl865x_delRoute(entry->ipAddr, 0xFFFFFFFF);
	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
	return SUCCESS;
}

#if 0
//quick sort the localpublic ip address
static void rtl865x_qsort(int s[], int l, int r)
{
	int i, j, x;
	if (l < r)
	{
		i = l;
		j = r;
		x = s[i];
		while (i < j)
		{
			while(i < j && s[j] > x) j--; 
			if(i < j) s[i++] = s[j];
			while(i < j && s[i] < x) i++; 
			if(i < j) s[j--] = s[i];
		}
		s[i] = x;
		rtl865x_qsort(s, l, i-1); 
		rtl865x_qsort(s, i+1, r);
	}
}
#endif

static int rtl865x_addIpRangeAclToCpu(unsigned int srcIpStart,unsigned int srcIpEnd,unsigned int dstIpStart,unsigned int dstIpEnd)
{
	rtl865x_AclRule_t	rule;
	int ret=-1;
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_IP_RANGE;
	rule.actionType_		= RTL865X_ACL_TOCPU;
	rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
	rule.srcIpAddrLB_ 	= srcIpStart;
	rule.srcIpAddrUB_ 	= srcIpEnd;

	rule.dstIpAddrLB_ 	= dstIpStart;
	rule.dstIpAddrUB_ 	= dstIpEnd;

	ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
	
	return ret;
}

static int rtl865x_delIpRangeAclToCpu(unsigned int srcIpStart,unsigned int srcIpEnd,unsigned int dstIpStart,unsigned int dstIpEnd)
{
	rtl865x_AclRule_t	rule;
	int ret=-1;
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_ = RTL865X_ACL_IP_RANGE;
	rule.actionType_		= RTL865X_ACL_TOCPU;
	rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
	rule.srcIpAddrLB_ 	= srcIpStart;
	rule.srcIpAddrUB_ 	= srcIpEnd;

	rule.dstIpAddrLB_ 	= dstIpStart;
	rule.dstIpAddrUB_ 	= dstIpEnd;

	ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
	
	return ret;
}


static int rtl865x_addOutboundToCpuAcl(struct rtl865x_localPublic *entry)
{
	struct rtl865x_localPublic* lpEntry=NULL;
#if defined(CONFIG_RTL_PUBLIC_SSID)	
	struct rtl865x_public_ssid_entry *ssidEntry=NULL;
	struct list_head *p,*n;
#endif
	int i;
	rtl865x_route_t routeTbl[RT_DRV_ENTRY_NUM];
	rtl865x_route_t *rt=NULL;
	int routeCnt=0;

	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}

	/*let hardware local public to local public to cpu*/
	CTAILQ_FOREACH(lpEntry, &usedLocalPublicList, next)
	{
		if(lpEntry->ipAddr==entry->ipAddr)
		{
			continue;
		}

		rtl865x_addIpRangeAclToCpu(entry->ipAddr, entry->ipAddr, lpEntry->ipAddr, lpEntry->ipAddr);
	}

	/*let hardware local public to public ssid to cpu*/
#if defined(CONFIG_RTL_PUBLIC_SSID)
	list_for_each_safe(p,n,&public_ssid_list_head)
	{
		ssidEntry = list_entry(p,struct rtl865x_public_ssid_entry,list);
		if(ssidEntry->public_addr==entry->ipAddr)
		{
			continue;
		}
		rtl865x_addIpRangeAclToCpu(entry->ipAddr, entry->ipAddr, ssidEntry->public_addr, ssidEntry->public_addr);
	}
#endif

	/*let hardware local public to lan  to cpu*/
	routeCnt=rtl865x_getLanRoute(routeTbl,RT_DRV_ENTRY_NUM);
	for(i=0; i<routeCnt; i++)
	{
		rt=&routeTbl[i];
		if((rt->ipMask!=0xFFFFFFFF) && (rt->ipMask!=0))
		{
			rtl865x_addIpRangeAclToCpu(entry->ipAddr, entry->ipAddr, rt->ipAddr & rt->ipMask, ((rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1)));
		}
	}
	

	return SUCCESS;
}

static int rtl865x_delOutboundToCpuAcl(struct rtl865x_localPublic *entry)
{
	struct rtl865x_localPublic* lpEntry=NULL;
#if defined(CONFIG_RTL_PUBLIC_SSID)	
	struct rtl865x_public_ssid_entry *ssidEntry=NULL;
	struct list_head *p,*n;
#endif
	int i;

	rtl865x_route_t routeTbl[RT_DRV_ENTRY_NUM];
	rtl865x_route_t *rt=NULL;
	int routeCnt=0;

	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}


	/*let hardware local public to local public to cpu*/
	CTAILQ_FOREACH(lpEntry, &usedLocalPublicList, next)
	{
		if(lpEntry->ipAddr==entry->ipAddr)
		{
			continue;
		}

		rtl865x_delIpRangeAclToCpu(entry->ipAddr, entry->ipAddr, lpEntry->ipAddr, lpEntry->ipAddr);
	}

	/*let hardware local public to public ssid to cpu*/
#if defined(CONFIG_RTL_PUBLIC_SSID)
	list_for_each_safe(p,n,&public_ssid_list_head)
	{
		ssidEntry = list_entry(p,struct rtl865x_public_ssid_entry,list);
		if(ssidEntry->public_addr==entry->ipAddr)
		{
			continue;
		}
		rtl865x_delIpRangeAclToCpu(entry->ipAddr, entry->ipAddr, ssidEntry->public_addr, ssidEntry->public_addr);
	}
#endif

	/*let hardware local public to lan  to cpu*/
	routeCnt=rtl865x_getLanRoute(routeTbl,RT_DRV_ENTRY_NUM);
	for(i=0; i<routeCnt; i++)
	{
		rt=&routeTbl[i];
		if((rt->ipMask!=0xFFFFFFFF) && (rt->ipMask!=0))
		{
			rtl865x_delIpRangeAclToCpu(entry->ipAddr, entry->ipAddr, rt->ipAddr & rt->ipMask, ((rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1)));
		}
	}
	

	return SUCCESS;
}
static int rtl865x_getAllHWLocalPublic(struct rtl865x_localPublic localPublicArray [ ],int arraySize)
{
		struct rtl865x_localPublic* entry;
		int cnt=0;
		if((localPublicArray==NULL) || (arraySize==0))
		{
			return 0;
		}
		
		if((localPublicInitialized==FALSE) || (localPublicEnabled==FALSE))
		{
			return 0;
		}
		
		CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
		{
			if(entry->hw == 0)
				continue;
			//hardware localpublic
			rtl865x_copyLocalPublic(&localPublicArray[cnt], entry);
			cnt++;
			if(cnt>=arraySize)
			{
				break;
			}
		}
		
		return cnt;
}


static int rtl865x_addOutboundRedirectAcl(struct rtl865x_localPublic *entry)
{
	rtl865x_AclRule_t	rule;
	int ret=FAILED;
	int nextHopIndex=-1;
	rtl865x_netif_local_t * localPublicInterface=NULL;
	#if 0
	int i;
	rtl865x_route_t routeTbl[RT_DRV_ENTRY_NUM];
	rtl865x_route_t *rt=NULL;
	int routeCnt=0,hwLpCnt = 0;
	struct rtl865x_localPublic lpArray[MAX_HW_LOCAL_PUBLIC_NUM];
	//int lpIpAddr[MAX_HW_LOCAL_PUBLIC_NUM];
	int anotherLPAddr = 0;
	#endif
	
	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}

	if(entry->defGateway==0)
	{
		return FAILED;
	}

	if(memcmp(entry->defGwMac, zeroMac, 6) ==0)
	{
		return FAILED;
	}

	if(memcmp(entry->mac, zeroMac, 6) ==0)
	{
		return FAILED;
	}
	
	if(entry->lpNetif[0]==0)
	{
		return FAILED;
	}
	
	localPublicInterface=_rtl865x_getNetifByName(entry->lpNetif);
	if(localPublicInterface==NULL)
	{
		return FAILED;
	}	

	nextHopIndex= rtl865x_getNxtHopIdx(NEXTHOP_DEFREDIRECT_ACL, localPublicInterface, entry->defGateway);
	if(nextHopIndex == -1)
	{
		ret=rtl865x_addNxtHop(NEXTHOP_DEFREDIRECT_ACL, NULL, localPublicInterface, entry->defGateway);	
		if(ret!=SUCCESS)
		{
			return FAILED;
		}
		
		nextHopIndex= rtl865x_getNxtHopIdx(NEXTHOP_DEFREDIRECT_ACL, localPublicInterface, entry->defGateway);
		if(nextHopIndex==-1)
		{
			return FAILED;	
		}
	}

	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
	#if 0

	memset(lpArray,0,sizeof(struct rtl865x_localPublic) * MAX_HW_LOCAL_PUBLIC_NUM);
	//hyking:do NOT redirect when localpublic to the other localpublics
	hwLpCnt = rtl865x_getAllHWLocalPublic(lpArray,MAX_HW_LOCAL_PUBLIC_NUM);
	if(hwLpCnt < 1 || hwLpCnt > 2)
		return FAILED;

	//NOTE:because there are ONLY two HW localpublic!!
	anotherLPAddr = 0;
	for(i = 0; i < hwLpCnt; i++)
	{
		if(lpArray[i].ipAddr == entry->ipAddr)
			continue;
			
		anotherLPAddr = lpArray[i].ipAddr;
	}
	//sort the localpublic
	//rtl865x_qsort(lpIpAddr,0,hwLpCnt-1);	
	
	routeCnt=rtl865x_getLanRoute(routeTbl,RT_DRV_ENTRY_NUM);

	if(routeCnt==0)
	{
		return FAILED;
	}
		
	
	
	for(i=0; i<routeCnt; i++)
	{
		rt=&routeTbl[i];
		if(rt->ipMask!=0xFFFFFFFF && (rt->ipMask!=0))
		{
			if(anotherLPAddr == 0)
			{
			/*-----------------------------------------------------------*/
			bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
			rule.ruleType_ = RTL865X_ACL_IP_RANGE;
			rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
			rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
			rule.srcIpAddrLB_ 	= entry->ipAddr;
			rule.srcIpAddrUB_ 	= entry->ipAddr;
			
			rule.dstIpAddrLB_ 	= 0;
			rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
			
			rule.nexthopIdx_	= nextHopIndex;
			
			ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
			//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
			if(ret!=SUCCESS)
			{
				rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);	
				return FAILED;
			}
			
			/*-----------------------------------------------------------*/
			bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
			rule.ruleType_ = RTL865X_ACL_IP_RANGE;
			rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
			rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
			
			rule.srcIpAddrLB_ 	= entry->ipAddr;
			rule.srcIpAddrUB_ 	= entry->ipAddr;
			
			rule.dstIpAddrLB_ 	= (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1);
			rule.dstIpAddrUB_ 	= 0xFFFFFFFF;

			rule.nexthopIdx_	= nextHopIndex;

			ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
			
			//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
			if(ret!=SUCCESS)
			{
				/*delete previous acl*/
				bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
				rule.ruleType_ = RTL865X_ACL_IP_RANGE;
				rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
				rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
				rule.srcIpAddrLB_ 	= entry->ipAddr;
				rule.srcIpAddrUB_ 	= entry->ipAddr;
				
				rule.dstIpAddrLB_ 	= 0;
				rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
				
				rule.nexthopIdx_	= nextHopIndex;
				
				ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
				
				rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);	
				return FAILED;
			}
		}
			else
			{
				/*-----------------------------------------------------------*/
				bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
				rule.ruleType_ = RTL865X_ACL_IP_RANGE;
				rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
				rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
				rule.srcIpAddrLB_ 	= entry->ipAddr;
				rule.srcIpAddrUB_ 	= entry->ipAddr;
				
				rule.dstIpAddrLB_ 	= 0;
				if(anotherLPAddr < (rt->ipAddr & rt->ipMask))
					rule.dstIpAddrUB_ 	= anotherLPAddr -1;
				else
					rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
				
				rule.nexthopIdx_	= nextHopIndex;
				
				ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
				//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
				if(ret!=SUCCESS)
				{
					rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);	
					return FAILED;
				}

				if(anotherLPAddr < (rt->ipAddr & rt->ipMask))
				{
					/*-----------------------------------------------------------*/
					bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
					rule.ruleType_ = RTL865X_ACL_IP_RANGE;
					rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
					rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					
					rule.srcIpAddrLB_ 	= entry->ipAddr;
					rule.srcIpAddrUB_ 	= entry->ipAddr;
					
					rule.dstIpAddrLB_ 	= anotherLPAddr + 1;
					rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;

					rule.nexthopIdx_	= nextHopIndex;

					ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
					
					//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
					if(ret!=SUCCESS)
					{
						/*delete previous acl*/
						bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
						rule.ruleType_ = RTL865X_ACL_IP_RANGE;
						rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
						rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
						rule.srcIpAddrLB_ 	= entry->ipAddr;
						rule.srcIpAddrUB_ 	= entry->ipAddr;
						
						rule.dstIpAddrLB_ 	= 0;
						rule.dstIpAddrUB_ 	= anotherLPAddr -1;
						
						rule.nexthopIdx_	= nextHopIndex;
						
						ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
						
						rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);	
						return FAILED;
					}

					/*-----------------------------------------------------------*/
					bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
					rule.ruleType_ = RTL865X_ACL_IP_RANGE;
					rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
					rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					
					rule.srcIpAddrLB_ 	= entry->ipAddr;
					rule.srcIpAddrUB_ 	= entry->ipAddr;
					
					rule.dstIpAddrLB_ 	= (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1);
					rule.dstIpAddrUB_ 	= 0xFFFFFFFF;

					rule.nexthopIdx_	= nextHopIndex;

					ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
					
					//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
					if(ret!=SUCCESS)
					{
						/*delete previous acl*/
						bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
						rule.ruleType_ = RTL865X_ACL_IP_RANGE;
						rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
						rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
						rule.srcIpAddrLB_ 	= entry->ipAddr;
						rule.srcIpAddrUB_ 	= entry->ipAddr;
						
						rule.dstIpAddrLB_ 	= 0;
						rule.dstIpAddrUB_ 	= anotherLPAddr -1;
						
						rule.nexthopIdx_	= nextHopIndex;
						
						ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
						
						/*----------------------------------------*/						
						bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
						rule.ruleType_ = RTL865X_ACL_IP_RANGE;
						rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
						rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
						rule.srcIpAddrLB_ 	= entry->ipAddr;
						rule.srcIpAddrUB_ 	= entry->ipAddr;
						
						rule.dstIpAddrLB_ 	= anotherLPAddr + 1;
						rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
						
						rule.nexthopIdx_	= nextHopIndex;
						
						ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
						
						rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);	
						return FAILED;
					}
				}
				else if(anotherLPAddr > (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1))
				{	
					/*-----------------------------------------------------------*/
					bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
					rule.ruleType_ = RTL865X_ACL_IP_RANGE;
					rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
					rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					
					rule.srcIpAddrLB_ 	= entry->ipAddr;
					rule.srcIpAddrUB_ 	= entry->ipAddr;
					
					rule.dstIpAddrLB_ 	= (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1);					
					rule.dstIpAddrUB_ 	= anotherLPAddr -1;

					rule.nexthopIdx_	= nextHopIndex;

					ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
					
					//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
					if(ret!=SUCCESS)
					{
						/*delete previous acl*/
						bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
						rule.ruleType_ = RTL865X_ACL_IP_RANGE;
						rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
						rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
						rule.srcIpAddrLB_ 	= entry->ipAddr;
						rule.srcIpAddrUB_ 	= entry->ipAddr;
						
						rule.dstIpAddrLB_ 	= 0;
						rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
						
						rule.nexthopIdx_	= nextHopIndex;
						
						ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
						
						rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);	
						return FAILED;
					}

					/*-----------------------------------------------------------*/
					bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
					rule.ruleType_ = RTL865X_ACL_IP_RANGE;
					rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
					rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					
					rule.srcIpAddrLB_ 	= entry->ipAddr;
					rule.srcIpAddrUB_ 	= entry->ipAddr;
					
					rule.dstIpAddrLB_ 	= anotherLPAddr + 1;					
					rule.dstIpAddrUB_ 	= 0xffffffff;

					rule.nexthopIdx_	= nextHopIndex;

					ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
					
					//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
					if(ret!=SUCCESS)
					{
						/*delete previous acl*/						
						bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
						rule.ruleType_ = RTL865X_ACL_IP_RANGE;
						rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
						rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
						rule.srcIpAddrLB_ 	= entry->ipAddr;
						rule.srcIpAddrUB_ 	= entry->ipAddr;
						
						rule.dstIpAddrLB_ 	= 0;
						rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
						
						rule.nexthopIdx_	= nextHopIndex;
						
						ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);

						/*delete previous acl*/	
						bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
						rule.ruleType_ = RTL865X_ACL_IP_RANGE;
						rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
						rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
						rule.srcIpAddrLB_ 	= entry->ipAddr;
						rule.srcIpAddrUB_ 	= entry->ipAddr;
						
						rule.dstIpAddrLB_ 	= (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1);
						rule.dstIpAddrUB_ 	= anotherLPAddr - 1;
						
						rule.nexthopIdx_	= nextHopIndex;
						
						ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
						
						rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);	
						return FAILED;
					}
				}
				else
				{
					//impossible
					printk("BUG!!!\n");
				}
			}
		}
	}

	#else
	rtl865x_addOutboundToCpuAcl(entry);
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	
	rule.ruleType_			= RTL865X_ACL_IP;
	rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
	rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;

	rule.srcIpAddr_		= entry->ipAddr;
	rule.srcIpAddrMask_	= 0xffffffff;
	rule.dstIpAddr_		= 0x0;
	rule.dstIpAddrMask_	= 0x0;

	nextHopIndex= rtl865x_getNxtHopIdx(NEXTHOP_DEFREDIRECT_ACL, localPublicInterface, entry->defGateway);
	//printk("%s:%d,nextHopIndex is %d \n",__FUNCTION__,__LINE__,nextHopIndex);
	if(nextHopIndex==-1)
	{
		return FAILED;	
	}
	
	rule.nexthopIdx_=nextHopIndex;
	
	ret= rtl865x_add_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
	if(ret!=SUCCESS)
	{
		rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);	
		return FAILED;
	}

	#endif
	rtl865x_reConfigDefaultAcl( lanIfInfo.ifname);
	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
	return ret;

}

static int rtl865x_delOutboundRedirectAcl(struct rtl865x_localPublic *entry)
{
	rtl865x_AclRule_t	rule;
	rtl865x_netif_local_t * localPublicInterface=NULL;
	int nextHopIndex=-1;
	int ret=FAILED;
	#if 0
	int i;
	rtl865x_route_t routeTbl[RT_DRV_ENTRY_NUM];
	rtl865x_route_t *rt=NULL;
	int routeCnt=0,hwLpCnt = 0;
	struct rtl865x_localPublic lpArray[MAX_HW_LOCAL_PUBLIC_NUM];
	//int lpIpAddr[MAX_HW_LOCAL_PUBLIC_NUM];
	int anotherLPAddr = 0;
	#endif
	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}

	if(entry->defGateway==0)
	{
		return FAILED;
	}

	if(memcmp(entry->defGwMac, zeroMac, 6) ==0)
	{
		return FAILED;
	}

	if(entry->lpNetif[0]==0)
	{
		return FAILED;
	}

	localPublicInterface=_rtl865x_getNetifByName(entry->lpNetif);
	if(localPublicInterface == NULL)
	{
		return FAILED;
	}
	
	nextHopIndex= rtl865x_getNxtHopIdx(NEXTHOP_DEFREDIRECT_ACL, localPublicInterface, entry->defGateway);
	//printk("%s:%d,nextHopIndex is %d ,localpublicnetif(%s)\n",__FUNCTION__,__LINE__,nextHopIndex,localPublicInterface->name);
	if(nextHopIndex == -1)
	{
		return FAILED;
	}
	
	#if 0
	memset(lpArray,0,sizeof(struct rtl865x_localPublic) * MAX_HW_LOCAL_PUBLIC_NUM);
	//hyking:do NOT redirect when localpublic to the other localpublics
	hwLpCnt = rtl865x_getAllHWLocalPublic(lpArray,MAX_HW_LOCAL_PUBLIC_NUM);
	if(hwLpCnt < 1 || hwLpCnt > 2)
		return FAILED;

	//NOTE:because there are ONLY two HW localpublic!!
	anotherLPAddr = 0;
	for(i = 0; i < hwLpCnt; i++)
	{
		if(lpArray[i].ipAddr == entry->ipAddr)
			continue;
			
		anotherLPAddr = lpArray[i].ipAddr;
	}
	//sort the localpublic
	//rtl865x_qsort(lpIpAddr,0,hwLpCnt-1);
	
	routeCnt=rtl865x_getLanRoute(routeTbl,RT_DRV_ENTRY_NUM);
	
	if(routeCnt==0)
	{
		return FAILED;
	}
	
	for(i=0; i<routeCnt; i++)
	{
		rt=&routeTbl[i];
		#if 0
		if(rt->ipMask!=0xFFFFFFFF && (rt->ipMask!=0))
		{
			/*-----------------------------------------------------------*/
			bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
			rule.ruleType_ = RTL865X_ACL_IP_RANGE;
			rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
			rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
			rule.srcIpAddrLB_ 	= entry->ipAddr;
			rule.srcIpAddrUB_ 	= entry->ipAddr;
			
			rule.dstIpAddrLB_ 	= 0;
			rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
			
			rule.nexthopIdx_	= nextHopIndex;
			
			ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
			//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
		
			/*-----------------------------------------------------------*/
			bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
			rule.ruleType_ = RTL865X_ACL_IP_RANGE;
			rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
			rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
			
			rule.srcIpAddrLB_ 	= entry->ipAddr;
			rule.srcIpAddrUB_ 	= entry->ipAddr;
			
			rule.dstIpAddrLB_ 	= (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1);
			rule.dstIpAddrUB_ 	= 0xFFFFFFFF;

			rule.nexthopIdx_	= nextHopIndex;

			ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
			//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
		}
		#endif
		if(rt->ipMask!=0xFFFFFFFF && (rt->ipMask!=0))
		{
			if(anotherLPAddr == 0)
			{
				/*-----------------------------------------------------------*/
				bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
				rule.ruleType_ = RTL865X_ACL_IP_RANGE;
				rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
				rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
				rule.srcIpAddrLB_ 	= entry->ipAddr;
				rule.srcIpAddrUB_ 	= entry->ipAddr;
				
				rule.dstIpAddrLB_ 	= 0;
				rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
				
				rule.nexthopIdx_	= nextHopIndex;
				
				ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
				//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
				
				
				/*-----------------------------------------------------------*/
				bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
				rule.ruleType_ = RTL865X_ACL_IP_RANGE;
				rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
				rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
				
				rule.srcIpAddrLB_ 	= entry->ipAddr;
				rule.srcIpAddrUB_ 	= entry->ipAddr;
				
				rule.dstIpAddrLB_ 	= (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1);
				rule.dstIpAddrUB_ 	= 0xFFFFFFFF;

				rule.nexthopIdx_	= nextHopIndex;

				ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);				
				//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);				
			}
			else
			{
				/*-----------------------------------------------------------*/
				bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
				rule.ruleType_ = RTL865X_ACL_IP_RANGE;
				rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
				rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
				rule.srcIpAddrLB_ 	= entry->ipAddr;
				rule.srcIpAddrUB_ 	= entry->ipAddr;
				
				rule.dstIpAddrLB_ 	= 0;
				if(anotherLPAddr < (rt->ipAddr & rt->ipMask))
					rule.dstIpAddrUB_ 	= anotherLPAddr -1;
				else
					rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;
				
				rule.nexthopIdx_	= nextHopIndex;
				
				ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
				//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);				

				if(anotherLPAddr < (rt->ipAddr & rt->ipMask))
				{
					/*-----------------------------------------------------------*/
					bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
					rule.ruleType_ = RTL865X_ACL_IP_RANGE;
					rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
					rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					
					rule.srcIpAddrLB_ 	= entry->ipAddr;
					rule.srcIpAddrUB_ 	= entry->ipAddr;
					
					rule.dstIpAddrLB_ 	= anotherLPAddr + 1;
					rule.dstIpAddrUB_ 	= rt->ipAddr & rt->ipMask;

					rule.nexthopIdx_	= nextHopIndex;

					ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
					
					//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);					

					/*-----------------------------------------------------------*/
					bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
					rule.ruleType_ = RTL865X_ACL_IP_RANGE;
					rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
					rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					
					rule.srcIpAddrLB_ 	= entry->ipAddr;
					rule.srcIpAddrUB_ 	= entry->ipAddr;
					
					rule.dstIpAddrLB_ 	= (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1);
					rule.dstIpAddrUB_ 	= 0xFFFFFFFF;

					rule.nexthopIdx_	= nextHopIndex;

					ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);					
					//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
					
				}
				else if(anotherLPAddr > (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1))
				{	
					/*-----------------------------------------------------------*/
					bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
					rule.ruleType_ = RTL865X_ACL_IP_RANGE;
					rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
					rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					
					rule.srcIpAddrLB_ 	= entry->ipAddr;
					rule.srcIpAddrUB_ 	= entry->ipAddr;
					
					rule.dstIpAddrLB_ 	= (rt->ipAddr & rt->ipMask) + ((~rt->ipMask)+1);					
					rule.dstIpAddrUB_ 	= anotherLPAddr -1;

					rule.nexthopIdx_	= nextHopIndex;

					ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);					
					//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);					

					/*-----------------------------------------------------------*/
					bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
					rule.ruleType_ = RTL865X_ACL_IP_RANGE;
					rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
					rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;
					
					rule.srcIpAddrLB_ 	= entry->ipAddr;
					rule.srcIpAddrUB_ 	= entry->ipAddr;
					
					rule.dstIpAddrLB_ 	= anotherLPAddr + 1;					
					rule.dstIpAddrUB_ 	= 0xffffffff;

					rule.nexthopIdx_	= nextHopIndex;

					ret= rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);					
					//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
					
				}
				else
				{
					//impossible
					printk("BUG!!!\n");
				}
			}
		}
	}
	#else
	rtl865x_delOutboundToCpuAcl(entry);
	bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
	rule.ruleType_			= RTL865X_ACL_IP;
	rule.actionType_		= RTL865X_ACL_DEFAULT_REDIRECT;
	rule.pktOpApp_ 		= RTL865X_ACL_ALL_LAYER;

	rule.srcIpAddr_		= entry->ipAddr;
	rule.srcIpAddrMask_	= 0xffffffff;
	rule.dstIpAddr_		= 0x0;
	rule.dstIpAddrMask_	= 0x0;

	rule.nexthopIdx_ = nextHopIndex;
	
	ret = rtl865x_del_acl(&rule, lanIfInfo.ifname, RTL865X_ACL_SYSTEM_USED);
	#endif
	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
	ret = rtl865x_delNxtHop(NEXTHOP_DEFREDIRECT_ACL, nextHopIndex);
	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);	
	return SUCCESS;

}


static int rtl865x_addLocalPublicInterface(struct rtl865x_localPublic *entry)
{
	int i;
	rtl865x_netif_t netif;
	//rtl865x_AclRule_t	rule;
	unsigned int vid=0;
	int ret=FAILED;

		
	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}
	
	if(memcmp(entry->mac, zeroMac, 6)==0)
	{
		return FAILED;
	}

	if(entry->lpNetif[0]==0)
	{
		if(entry->lpVid!=0)
		{
			ret=rtl865x_delVlan(entry->lpVid);
			entry->lpVid=0;
		}
		
		for(vid=LOCAL_PUBLIC_VLAN_START; vid<=LOCAL_PUBLIC_VLAN_END; vid++)
		{
			if(rtl865x_addVlan(vid)==SUCCESS)
			{
			 	entry->lpVid=vid;
				break;
			}
		}

		if((vid>LOCAL_PUBLIC_VLAN_END) || (entry->lpVid==0))
		{
			/*can not find proper vlan for local public wan interface*/
			return FAILED;
		}
		
		ret=rtl865x_addVlanPortMember(entry->lpVid,wanIfInfo.memPort);
		//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
		ret=rtl865x_setVlanFilterDatabase(entry->lpVid,wanIfInfo.fid);
		
		for(i=0; i< MAX_HW_LOCAL_PUBLIC_NUM; i++)
		{
			sprintf(entry->lpNetif, "lp%d", i);
			if(_rtl865x_getNetifByName(entry->lpNetif)!=NULL)
			{
				continue;
			}
			else
			{
				break;
			}
		
		}	

		if(i==MAX_HW_LOCAL_PUBLIC_NUM)
		{
			rtl865x_delVlan(entry->lpVid);
			memset(entry->lpNetif, 0, 16);
			return FAILED;
		}

		memset(&netif, 0, sizeof(rtl865x_netif_t));
		memcpy(netif.name, entry->lpNetif, 16);
		memcpy(&netif.macAddr, entry->mac, 6);;
		netif.mtu = 1500;
		netif.if_type = IF_ETHER;
		netif.vid = entry->lpVid;
		netif.is_wan = 1;
		netif.is_slave = 0;
		netif.enableRoute=1;
		//printk("%s:%d,entry->lpNetif is %s \n",__FUNCTION__,__LINE__,entry->lpNetif);
		ret = rtl865x_addNetif(&netif);
		if(ret!=SUCCESS)
		{
			rtl865x_delVlan(entry->lpVid);
			memset(entry->lpNetif, 0, 16);
			return FAILED;
		}

		//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
		/*add acl rule at wan side to trap local public mac*/
		//hyking:default permit, it's NOT necessary to add this acl rule:)
		/*qinjunjie:but if CONFIG_RTK_VLAN_SUPPORT is enable, default is to cpu*/
#if defined(CONFIG_RTK_VLAN_SUPPORT)
		{
			rtl865x_AclRule_t	rule;
			bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
			rule.ruleType_ = RTL865X_ACL_MAC;
			rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
			rule.actionType_ = RTL865X_ACL_PERMIT;
			ret=rtl865x_add_acl(&rule, entry->lpNetif, RTL865X_ACL_SYSTEM_USED);
		}
#endif		
		

		if(memcmp(entry->defGwMac, zeroMac, 6)!=0)
		{
			/*add back local public redirect acl*/
			rtl865x_addOutboundRedirectAcl(entry);
		}
	
	}	
	
	return ret;
}

static int rtl865x_delLocalPublicInterface(struct rtl865x_localPublic *entry)
{
	int ret=FAILED;
	if((entry==NULL) || (entry->hw==0))
	{
		return FAILED;
	}

#if defined(CONFIG_RTK_VLAN_SUPPORT)
	{
		rtl865x_AclRule_t	rule;
		bzero((void*)&rule,sizeof(rtl865x_AclRule_t));
		rule.ruleType_ = RTL865X_ACL_MAC;
		rule.pktOpApp_ = RTL865X_ACL_ALL_LAYER;
		rule.actionType_ = RTL865X_ACL_PERMIT;
		ret=rtl865x_del_acl(&rule, entry->lpNetif, RTL865X_ACL_SYSTEM_USED);
	}
#endif

	if(memcmp(entry->defGwMac, zeroMac, 6)!=0)
	{
		/*for de-rerefence network interface*/
		ret=rtl865x_delOutboundRedirectAcl(entry);
	}
	
	ret=rtl865x_delNetif(entry->lpNetif);
	if(ret==SUCCESS)
	{
		memset(entry->lpNetif, 0 , 16);
		ret=rtl865x_delVlan(entry->lpVid);
		entry->lpVid=0;
	}
	//printk("%s:%d,ret is %d \n",__FUNCTION__,__LINE__,ret);
	return SUCCESS;
	
}

static int rtl865x_disableLocalPublicHwFwd(struct rtl865x_localPublic *entry)
{
	if(entry ==NULL)
	{
		return FAILED;
	}
	
	if(entry->hw==0)
	{
		return FAILED;
	}
		
	rtl865x_delLocalPublicExtIp(entry);
	rtl865x_delLocalPublicRoute( entry);
	rtl865x_delLocalPublicInterface(entry);	
	
	return SUCCESS;
}

static int rtl865x_clearLocalPublic(struct rtl865x_localPublic* entry)
{
	if(entry ==NULL)
	{
		return FAILED;
	}
	
	if(entry->hw)
	{
		rtl865x_disableLocalPublicHwFwd(entry);
	}
	else
	{
		rtl865x_delInboundAclToCpu(entry);
	}
	
	//memset(entry, 0, sizeof(struct rtl865x_localPublic) -8);
	
	return SUCCESS;
	
}

static int rtl865x_updateLocalPublicMac(struct rtl865x_localPublic *entry, unsigned char *newMac)
{
	unsigned char oldMac[6];
	
	memcpy(oldMac, entry->mac, 6);


	if(memcmp(oldMac, newMac, 6) !=0)
	{
		/*if old local public mac is not zero, delete it first*/
		if(memcmp(oldMac, zeroMac, 6) !=0)
		{
			if(entry->hw)
			{
				rtl865x_disableLocalPublicHwFwd(entry);
			}
			else
			{
				rtl865x_delInboundAclToCpu(entry);
			}
		}

		memcpy(entry->mac, newMac, ETHER_ADDR_LEN);	

		/*if new local public mac is not zero, add it*/
		if(memcmp(newMac, zeroMac, 6) !=0)
		{
			if(entry->hw)
			{
				rtl865x_addLocalPublicExtIp(entry);
				rtl865x_addLocalPublicRoute( entry);
				rtl865x_addLocalPublicInterface(entry);
				#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
				rtl865x_regist_aclChain(entry->lpNetif, RTL865X_ACL_QOS_USED0, RTL865X_ACL_INGRESS);
				rtl865x_regist_aclChain(entry->lpNetif, RTL865X_ACL_QOS_USED1, RTL865X_ACL_INGRESS);
				rtl865x_qosArrangeRuleByNetif();
				#endif
			}
			else
			{
				rtl865x_addInboundAclToCpu(entry);
			}
		}
		
	}
		
	return SUCCESS;
}

static int rtl865x_updateDefaultGatewayMac(struct rtl865x_localPublic *entry, unsigned char *newMac)
{

	unsigned char oldMac[6];
	
	memcpy(oldMac, entry->defGwMac, 6);


	if(memcmp(oldMac, newMac, 6) !=0)
	{
		if(memcmp(oldMac, zeroMac, 6) !=0)
		{
			if(entry->hw)
			{
				rtl865x_delOutboundRedirectAcl( entry);
			}
		}

		memcpy(entry->defGwMac, newMac, 6);	
		if(memcmp(newMac, zeroMac, 6) !=0)
		{
			if(entry->hw)
			{
				rtl865x_addOutboundRedirectAcl( entry);
			}
		}
		
	}

	return SUCCESS;

}

int rtl865x_delLocalPublic(struct rtl865x_localPublic* delEntry)
{
	struct rtl865x_localPublic* entry;
	struct rtl865x_localPublic* nextEntry;
	struct rtl865x_localPublic savedEntry;
	
	if(localPublicInitialized==FALSE)
	{
		return FAILED;
	}
		
	if(delEntry==NULL)
	{
		return SUCCESS;
	}
	
	memcpy(&savedEntry,delEntry,sizeof(struct rtl865x_localPublic));

	//hyking:when del hw local public, please change the redirect ACL...
	if(delEntry->hw == 1)
	{
		
		#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
		rtl865x_unRegist_aclChain(delEntry->lpNetif, RTL865X_ACL_QOS_USED0, RTL865X_ACL_INGRESS);
		rtl865x_unRegist_aclChain(delEntry->lpNetif, RTL865X_ACL_QOS_USED1, RTL865X_ACL_INGRESS);
		#endif

	}
	/*for hardware local public communication with public ssid  when they are different subnet*/
	rtl865x_flushHwLpOutRedirectAcl();
	
	entry = CTAILQ_FIRST(&usedLocalPublicList);
	while(entry)
	{
		nextEntry = CTAILQ_NEXT( entry, next );
		if(entry->ipAddr == delEntry->ipAddr)
		{
			rtl865x_clearLocalPublic(entry); //????? why put this line here?
			CTAILQ_REMOVE(&usedLocalPublicList, entry, next);
			//rtl865x_clearLocalPublic(entry);
			memset(entry, 0, sizeof(struct rtl865x_localPublic) -8);
			CTAILQ_INSERT_HEAD(&freeLocalPublicList, entry, next);
			break;
		}
		entry = nextEntry;
	}
	
	
	//if(delEntry->hw == 1) /*delEntry has already been cleared, can not be used*/
		rtl865x_reArrangeHwLpOutRedirectAcl();
	
	entry = CTAILQ_FIRST(&usedLocalPublicList);
	if(entry == NULL)
	{
		localPublicEnabled=FALSE;
	}
	return SUCCESS;
	
}
 

static int32 rtl865x_flushUsedLocalPublicList(void)
{
	struct rtl865x_localPublic* entry;
	struct rtl865x_localPublic* nextEntry;
	
	rtl865x_flushHwLpOutRedirectAcl();
	
	entry = CTAILQ_FIRST(&usedLocalPublicList);
	while(entry)
	{
		nextEntry = CTAILQ_NEXT( entry, next );
		rtl865x_clearLocalPublic(entry);
		CTAILQ_REMOVE(&usedLocalPublicList, entry, next);
		memset(entry, 0, sizeof(struct rtl865x_localPublic) -8);
		CTAILQ_INSERT_HEAD(&freeLocalPublicList, entry, next);
		entry = nextEntry;
	}
	
	return SUCCESS;
}

#if 0
static int proc_read_local_public(char *page, char **start, off_t off,
        int count, int *eof, void *data)
{

 	struct rtl865x_localPublic* entry;
	unsigned int entryCnt=0;
   	int len=0;
	unsigned char null[16]={"NULL"};
	if(localPublicEnabled==TRUE)
	{
		len +=sprintf(page+len, "local public is enable\n");
	}
	else
	{
		len +=sprintf(page+len, "local public is disable\n");
	}
	
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
			entryCnt++;
			len +=sprintf(page+len, "[%2d]  ip:%d.%d.%d.%d, netmask:%d.%d.%d.%d, gateway:%d.%d.%d.%d,hw:%d, dev:%s, mac:0x%x:%x:%x:%x:%x:%x,gw mac:0x%x:%x:%x:%x:%x:%x, lpNetif:%s\n", 
				entryCnt,NIPQUAD(entry->ipAddr), NIPQUAD(entry->netMask),NIPQUAD(entry->defGateway),
				entry->hw,(entry->dev[0]?entry->dev:null),
				entry->mac[0],entry->mac[1],entry->mac[2],entry->mac[3],entry->mac[4],entry->mac[5],
				entry->defGwMac[0],entry->defGwMac[1],entry->defGwMac[2],entry->defGwMac[3],entry->defGwMac[4],entry->defGwMac[5], entry->lpNetif[0]?entry->lpNetif:null);
	}	
	
	if (len <= off+count) 
		*eof = 1;    

	*start = page + off;      
	len -= off;

	if (len > count) 
		len = count;    

	if (len < 0) 
		len = 0;      

	return len; 
	
}
#endif
int localpublic_show(struct seq_file *s, void *v)
{
	struct rtl865x_localPublic* entry;
	unsigned int entryCnt=0;   	
	unsigned char null[16]={"NULL"};
	if(localPublicEnabled==TRUE)
	{
		seq_printf(s, "local public is enable\n");
	}
	else
	{
		seq_printf(s, "local public is disable\n");
	}
	
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
			entryCnt++;
			seq_printf(s, "[%2d]  ip:%d.%d.%d.%d, netmask:%d.%d.%d.%d, gateway:%d.%d.%d.%d,hw:%d, dev:%s, mac:0x%x:%x:%x:%x:%x:%x,gw mac:0x%x:%x:%x:%x:%x:%x, lpNetif:%s\n", 
				entryCnt,NIPQUAD(entry->ipAddr), NIPQUAD(entry->netMask),NIPQUAD(entry->defGateway),
				entry->hw,(entry->dev[0]?entry->dev:null),
				entry->mac[0],entry->mac[1],entry->mac[2],entry->mac[3],entry->mac[4],entry->mac[5],
				entry->defGwMac[0],entry->defGwMac[1],entry->defGwMac[2],entry->defGwMac[3],entry->defGwMac[4],entry->defGwMac[5], entry->lpNetif[0]?entry->lpNetif:null);
	}
	
	return 0;
}

int localpublic_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, localpublic_show, NULL));
}


static void rtl865x_saveNetDecPolicyAndDefACL(void)
{
	rtl865xC_getNetDecisionPolicy(&savedNetDecPolicy);
	rtl865x_getDefACLForNetDecisionMiss(&savedDefInAclStart, &savedDefInAclEnd, &savedDefOutAclStart, &savedDefOutAclEnd);
}

static void rtl865x_restoreNetDecPolicyAndDefACL(void)
{
	rtl865xC_setNetDecisionPolicy(savedNetDecPolicy );
	rtl865x_setDefACLForNetDecisionMiss(savedDefInAclStart, savedDefInAclEnd, savedDefOutAclStart, savedDefOutAclEnd);
}

static ssize_t proc_write_local_public(struct file *file, const char __user *buffer, size_t count, loff_t *data)
	
{
	
	char tmp[128];
	char cmd[16];
	int localPublicIp[4];
	int netMask[4];
	int defGateway[4];
	int hw=0;
	struct rtl865x_localPublic entry;
	struct rtl865x_localPublic *existEntry;
	unsigned int totalCnt=0;
	
	rtl865x_netif_t vituralNetif;
	int ret=-1;

	if (count < 2)
		return -EFAULT;

	if(localPublicInitialized==FALSE)
	{
		return -EFAULT;
	}
	
	memset(&entry, 0, sizeof(struct rtl865x_localPublic) );
	
	if (buffer && !copy_from_user(tmp, buffer, 128)) {

		int num = sscanf(tmp, "%s %d.%d.%d.%d %d.%d.%d.%d %d.%d.%d.%d %d", cmd, 
			&localPublicIp[0], &localPublicIp[1], &localPublicIp[2], &localPublicIp[3],
			&netMask[0], &netMask[1], &netMask[2], &netMask[3],
			&defGateway[0], &defGateway[1], &defGateway[2], &defGateway[3], &hw);
		
		if (num !=  14) 
		{
			return -EFAULT;
		}
		
		totalCnt=rtl865x_cntTotalLocalPublicNum();
	
		entry.ipAddr=(localPublicIp[0]<<24)|(localPublicIp[1]<<16)|(localPublicIp[2]<<8)|localPublicIp[3];
		entry.netMask=(netMask[0]<<24)|(netMask[1]<<16)|(netMask[2]<<8)|netMask[3];
		entry.defGateway=(defGateway[0]<<24)|(defGateway[1]<<16)|(defGateway[2]<<8)|defGateway[3];
		entry.hw=hw?1:0;
		
		if((strcmp(cmd, "add")==0) || (strcmp(cmd, "ADD")==0))
		{
			if(totalCnt==0)
			{
				/*save original default acl num*/
				rtl865x_saveNetDecPolicyAndDefACL();
				/*use virtual network interface to config default acl*/
				memset(&vituralNetif, 0, sizeof(rtl865x_netif_t));
				strcpy(vituralNetif.name,"virtualNetif");
				vituralNetif.if_type = IF_ETHER;
				vituralNetif.enableRoute=1;
				ret=rtl865x_addVirtualNetif(&vituralNetif);
				#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
				rtl865x_regist_aclChain("virtualNetif", RTL865X_ACL_QOS_USED0, RTL865X_ACL_INGRESS);
				rtl865x_regist_aclChain("virtualNetif", RTL865X_ACL_QOS_USED1, RTL865X_ACL_INGRESS);
				rtl865x_qosArrangeRuleByNetif();
				#endif
				//printk("%s:%d,ret is %d\n",__FUNCTION__,__LINE__,ret);
			}
			rtl865x_addLocalPublic(&entry);
		}

		if((strcmp(cmd, "del")==0) || (strcmp(cmd, "DEL")==0))
		{
			existEntry=rtl865x_searchLocalPublic(entry.ipAddr);
			if((existEntry!=NULL) && (existEntry->hw==entry.hw))
			{
				rtl865x_delLocalPublic(&entry);
			}
			else
			{
				return count;	
			}
		}
		
		totalCnt=rtl865x_cntTotalLocalPublicNum();
		
		if(totalCnt>0)
		{
		rtl865x_delAllInboundAclToCpu();
			rtl865xC_setNetDecisionPolicy(NETIF_MAC_BASED );
		rtl865x_addAllInboundAclToCpu();
			rtl865x_addMCastNetif();
			localPublicEnabled=TRUE;
		}
		else
		{
			
			rtl865x_delAllInboundAclToCpu();
			#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
			rtl865x_unRegist_aclChain("virtualNetif", RTL865X_ACL_QOS_USED0, RTL865X_ACL_INGRESS);
			rtl865x_unRegist_aclChain("virtualNetif", RTL865X_ACL_QOS_USED1, RTL865X_ACL_INGRESS);
			#endif
			ret=rtl865x_delVirtualNetif("virtualNetif");
			//printk("%s:%d,ret is %d\n",__FUNCTION__,__LINE__,ret);
			rtl865x_restoreNetDecPolicyAndDefACL();
			rtl865x_delMCastNetif();
			localPublicEnabled=FALSE;
		}
		
			//rtl865x_setDefACLForNetDecisionMiss(RTL865X_ACLTBL_ALL_TO_CPU, RTL865X_ACLTBL_ALL_TO_CPU, RTL865X_ACLTBL_PERMIT_ALL, RTL865X_ACLTBL_PERMIT_ALL);
		
		
		
	}

	return count;	
}

struct file_operations localpublic_single_seq_file_operations = {
	.open           = localpublic_single_open,
	.write		= proc_write_local_public,
	.read           = seq_read,
	.llseek         = seq_lseek,
	.release        = single_release,
};

#if defined(CONFIG_RTL_PUBLIC_SSID)
static struct rtl865x_public_ssid_entry* rtl865x_get_public_ssid_entry(unsigned int ipAddr)
{
	struct rtl865x_public_ssid_entry *entry,*ret_entry;
	struct list_head *p,*n;
	entry = ret_entry = NULL;
	
	list_for_each_safe(p,n,&public_ssid_list_head)
	{
		entry = list_entry(p,struct rtl865x_public_ssid_entry,list);
		if(entry->public_addr == ipAddr)
		{
			ret_entry = entry;
			break;
		}
	}

	return ret_entry;
}
static int rtl865x_add_public_ssid_entry(unsigned int ipAddr,unsigned int flag)
{
	struct rtl865x_public_ssid_entry *entry;
	entry = rtl865x_get_public_ssid_entry(ipAddr);
	if(entry)
		return -1;

	entry = kmalloc(sizeof(struct rtl865x_public_ssid_entry),GFP_KERNEL);
	if(NULL == entry)
		return -2;
	

	entry->public_addr = ipAddr;
	entry->flags = flag;
	/*for hardware local public communication with public ssid  when they are different subnet*/
	rtl865x_flushHwLpOutRedirectAcl();
	list_add(&entry->list,&public_ssid_list_head);
	
	/*for hardware local public communication with public ssid  when they are different subnet*/
	rtl865x_reArrangeHwLpOutRedirectAcl();	
	
	return 0;
	
}
static int rtl865x_del_public_ssid_entry(unsigned int ipAddr)
{
	struct rtl865x_public_ssid_entry *entry;

	entry = rtl865x_get_public_ssid_entry(ipAddr);
	if(entry)
	{	
		/*for hardware local public communication with public ssid  when they are different subnet*/
		rtl865x_flushHwLpOutRedirectAcl();
		list_del(&entry->list);
		kfree(entry);
		
		/*for hardware local public communication with public ssid  when they are different subnet*/
		rtl865x_reArrangeHwLpOutRedirectAcl();	
	}
	
	return 0;
}

int rtl865x_from_public_ssid_device(unsigned char *name)
{
	int i;
	for(i = 0; i < 4; i++)
	{
		if(strcmp(public_ssid_netif[i],name) == 0)
			return 1;
	}

	return 0;
}

int rtl865x_is_public_ssid_entry(unsigned int ipAddr)
{
	struct rtl865x_public_ssid_entry *entry;
	entry = rtl865x_get_public_ssid_entry(ipAddr);

	if(entry)
		return 1;
	
	return 0;
}

int public_SSID_show(struct seq_file *s, void *v)
{
	struct rtl865x_public_ssid_entry *entry;
	struct list_head *p, *n;
	
	unsigned int entryCnt=0;   	
	
	list_for_each_safe(p,n,&public_ssid_list_head)	
	{
			entryCnt++;
			entry = list_entry(p,struct rtl865x_public_ssid_entry, list);
			seq_printf(s, "[%2d]  public ssid ip:%d.%d.%d.%d,flag(0x%x)\n", 
				entryCnt,NIPQUAD(entry->public_addr), entry->flags );
	}

	seq_printf(s,"public ssid netif name:\n");
	for(entryCnt = 0; entryCnt < 4; entryCnt++)
	{
		seq_printf(s,"[%2d], netif:%s\n",entryCnt,public_ssid_netif[entryCnt]);
	}	
	
	return 0;
}


int public_SSID_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, public_SSID_show, NULL));
}

static ssize_t proc_write_public_SSID(struct file *file, const char __user *buffer, size_t count, loff_t *data)	
{	
	char tmpbuf[128];
	int public_ssid_ip[4];
	unsigned int ipAddr;
	int num;
	
	char		*strptr, *cmd_addr;
	char		*tokptr;
	
	if (count < 2)
		return -EFAULT;

	if (buffer && !copy_from_user(tmpbuf, buffer, 128)) 
	{

		tmpbuf[count -1] = '\0';
		strptr=tmpbuf;

		cmd_addr = strsep(&strptr," ");
		if (cmd_addr==NULL)
		{
			goto errout;
		}
		
		tokptr = strsep(&strptr," ");
		if (tokptr==NULL)
		{
			goto errout;
		}		

		if (!strcmp(cmd_addr, "add") || !strcmp(cmd_addr,"ADD"))
		{
			num = sscanf(tokptr,"%d.%d.%d.%d",&public_ssid_ip[0], &public_ssid_ip[1], &public_ssid_ip[2], &public_ssid_ip[3]);
			if(num != 4)
				goto errout;

			ipAddr = public_ssid_ip[0]<<24 | public_ssid_ip[1]<<16 | public_ssid_ip[2]<<8 | public_ssid_ip[3];			
			rtl865x_add_public_ssid_entry(ipAddr,0);
		}		
		else if((strcmp(cmd_addr, "del")==0) || (strcmp(cmd_addr, "DEL")==0))
		{
			num = sscanf(tokptr,"%d.%d.%d.%d",&public_ssid_ip[0], &public_ssid_ip[1], &public_ssid_ip[2], &public_ssid_ip[3]);
			if(num != 4)
				goto errout;

			ipAddr = public_ssid_ip[0]<<24 | public_ssid_ip[1]<<16 | public_ssid_ip[2]<<8 | public_ssid_ip[3];
			rtl865x_del_public_ssid_entry(ipAddr);
		}
		else if((strcmp(cmd_addr,"pssid_netif") == 0) || (strcmp(cmd_addr,"PSSID_NETIF") == 0))
		{
			num = 0;
			memset(public_ssid_netif,0,4*16);
			while(tokptr)
			{
				printk("==netif(%s),strlen(%d)\n",tokptr,strlen(tokptr));
				strcpy(public_ssid_netif[num],tokptr);
				num++;
				tokptr = strsep(&strptr," ");
				if(num >= 4)
					goto errout;
			}
		}
	}
	return count;
errout:
	printk("public ssid write format:\n");
	printk("add/del ipAddress(*.*.*.*)\n");
	printk("pssid_netif name1 name2(max = 4)\n");
	
	return count;	
}



struct file_operations public_SSID_single_seq_fop = {
	.open           = public_SSID_single_open,
	.write		= proc_write_public_SSID,
	.read           = seq_read,
	.llseek         = seq_lseek,
	.release        = single_release,
};
#endif
int rtl865x_initLocalPublic(struct rtl865x_localPublicPara* para)
{
	int32 i;
	uint32 bondOptReg=0;
	if(localPublicInitialized==TRUE)
	{
		return SUCCESS;
	}
	#if 1
	/*here to check ic version: local public only is bound to RTL8196BT*/
	/*bond option register(0xB800000C idcode[3:0]:bit3~bit0).*/
	/*RTL8196BU:0x3B*/
	/*RTL8196BT:0x3C*/
	/*RTL8972B:0x30?*/
	bondOptReg=READ_MEM32(0xB800000C);
	if(((bondOptReg&0x0F)!=0x0C) && ((bondOptReg&0x0F)!=0x00))
	{
		printk("current chip doesn't support local public feature!!! ");
		return FAILED;
	}
	#endif
	printk("Start Init Local Public\n");
	
	CTAILQ_INIT(&freeLocalPublicList);
	CTAILQ_INIT(&usedLocalPublicList);

	if((para!=NULL) && (para->maxEntryNum!=0))
	{
		if(para->maxEntryNum<=MAX_LOCAL_PUBLIC_NUM)
		{
			maxLocalPublicNum=para->maxEntryNum;
		}
		else
		{
			maxLocalPublicNum=MAX_LOCAL_PUBLIC_NUM;
		}
		
	}
	else
	{
		maxLocalPublicNum=DEF_LOCAL_PUBLIC_NUM;
	}
	
	TBL_MEM_ALLOC(localPublicPool, struct rtl865x_localPublic, maxLocalPublicNum)
	if(localPublicPool!=NULL)
	{
		memset( localPublicPool, 0, maxLocalPublicNum * sizeof(struct rtl865x_localPublic));	
	}
	else
	{		
		return FAILED;
	}
	
	for(i = 0; i<maxLocalPublicNum;i++)
	{
		CTAILQ_INSERT_HEAD(&freeLocalPublicList, &localPublicPool[i], next);
	}

	localPublicProcEntry=create_proc_entry("localPublic", 0, NULL);
	if(localPublicProcEntry != NULL)
	{
		localPublicProcEntry->proc_fops = &localpublic_single_seq_file_operations;
	}

	rtl865x_saveNetDecPolicyAndDefACL();
	
	localPublicInitialized=TRUE;
	localPublicEnabled=FALSE;
#if defined(CONFIG_RTL_PUBLIC_SSID)
	//public ssid
	INIT_LIST_HEAD(&public_ssid_list_head);
	public_ssid_proc_entry = create_proc_entry("public_ssid",0,NULL);
	if(public_ssid_proc_entry != NULL)
		public_ssid_proc_entry->proc_fops = &public_SSID_single_seq_fop;
#endif	
	return SUCCESS;
}



int rtl865x_reInitLocalPublic(void)
{
	if(localPublicInitialized==FALSE)
	{
		return FAILED;
	}

	if(localPublicEnabled==FALSE)
	{
		return SUCCESS;
	}
	
	rtl865x_flushUsedLocalPublicList();
	memset(&wanIfInfo, 0, sizeof(struct rtl865x_interface_info));
	memset(&lanIfInfo, 0 , sizeof(struct rtl865x_interface_info));
	
	rtl865x_delAllInboundAclToCpu();
	rtl865x_delVirtualNetif("virtualNetif");
	rtl865x_restoreNetDecPolicyAndDefACL();
	
	localPublicEnabled=FALSE;

	
	return SUCCESS;
}

static int rtl865x_checkIpHdr(struct rtl865x_pktInfo* pktInfo)
{
	unsigned char		*ptr;
	struct iphdr		*iph;
	unsigned int 		ipHdrLen;
	struct udphdr 	*udph;
	struct dhcpMessage *dhcph;
	unsigned char 	*requestedIp;
	
	unsigned int 		srcIpAddr=0;
	unsigned int 		dstIpAddr=0;
	struct rtl865x_localPublic* entry;


	ptr = pktInfo->ipHdr;
	iph = (struct iphdr*) ptr;

	srcIpAddr=iph->saddr;
	dstIpAddr=iph->daddr;

	if((srcIpAddr!=0) && (rtl865x_searchLocalPublic(srcIpAddr)!=NULL))
	{
		pktInfo->srcIp=srcIpAddr;
		pktInfo->fromLocalPublic=1;
		//printk("%s:%d, match src ip:%d.%d.%d.%d\n",__FUNCTION__,__LINE__,NIPQUAD(srcIpAddr));
	}

	if((dstIpAddr !=0) && (rtl865x_searchLocalPublic(dstIpAddr)!=NULL))
	{
		//printk("%s:%d, match dst ip:%d.%d.%d.%d\n",__FUNCTION__,__LINE__,NIPQUAD(dstIpAddr));
		pktInfo->dstIp=dstIpAddr;
		pktInfo->toLocalPublic=1;
		
	}

	if((pktInfo->fromLocalPublic==1) || (pktInfo->toLocalPublic==1))
	{
		return SUCCESS;
	}
	
	/*udp*/
	if(iph->protocol==0x11)
	{
		ipHdrLen=((*ptr)&0x0F)<<2;

		ptr=ptr+ipHdrLen;
		udph = (struct udphdr*)ptr;
		/*parse dhcp packet*/
		if((udph->source==CLIENT_PORT) && (udph->dest==SERVER_PORT))
		{
			/*client--->server*/
			ptr=ptr+8;
			dhcph=(struct dhcpMessage *)ptr;
			srcIpAddr=dhcph->ciaddr;
			
			if(srcIpAddr==0)
			{
				requestedIp=get_dhcpOption(dhcph, DHCP_REQUESTED_IP);
				if(requestedIp != NULL)
				{
					memcpy(&srcIpAddr, requestedIp, 4);
				}
			}
			
			if(srcIpAddr==0)
			{
				return FAILED;
			}
			
			entry=rtl865x_searchLocalPublic(srcIpAddr);
			if(entry!=NULL)
			{
				pktInfo->srcIp=srcIpAddr;
				pktInfo->fromLocalPublic=TRUE;
				
				
				if(pktInfo->action==RX_LAN_PACKET)
				{
					/*learning port and mac information*/
					strcpy(entry->dev, pktInfo->dev);
					entry->port=pktInfo->port;
					if((entry->hw) && (strncmp(pktInfo->dev, RTL_WLAN_NAME, 4) ==0))
					{
						rtl865x_disableLocalPublicHwFwd(entry);
						entry->hw=0;
					}
					rtl865x_updateLocalPublicMac(entry, dhcph->chaddr);
				}
				//printk("%s:%d, match dhcp src ip:%d.%d.%d.%d\n",__FUNCTION__,__LINE__,NIPQUAD(srcIpAddr));
				return SUCCESS;
			}
		}
		else if ((udph->source==SERVER_PORT) && (udph->dest==CLIENT_PORT))
		{
			/*server--->client*/
			ptr=ptr+8;
			dhcph=(struct dhcpMessage *)ptr;
			dstIpAddr=dhcph->yiaddr;
			
			entry=rtl865x_searchLocalPublic(dstIpAddr);
			if(entry!=NULL)
			{
				pktInfo->dstIp=dstIpAddr;
				pktInfo->toLocalPublic=1;
				//printk("%s:%d, match dhcp dst ip:%d.%d.%d.%d\n",__FUNCTION__,__LINE__,NIPQUAD(dstIpAddr));
				return SUCCESS;
			}
		}
		else
		{
			return FAILED;
		}
	}

	return FAILED;
}

static int rtl865x_checkArpHdr(struct rtl865x_pktInfo* pktInfo)
{
	unsigned char		*ptr;
	struct arphdr		*arph;
	unsigned char		*ar_sha;	/* sender hardware address	*/
	unsigned char		*ar_sip;		/* sender IP address		*/
	unsigned char		*ar_tha;	/* target hardware address	*/
	unsigned char		*ar_tip;		/* target IP address		*/
	
	unsigned int srcIpAddr=0;
	unsigned int dstIpAddr=0;
	struct rtl865x_localPublic* entry;

	ptr	= pktInfo->arpHdr;
	arph = (struct arphdr *)ptr;
	
	if(arph->ar_hrd != ARPHRD_ETHER)
	{
		return FAILED;
	}

	if(arph->ar_pro!=0x0800)
	{
		return FAILED;
	}
	ar_sha =  ptr+8;
	ar_sip = ptr+14;
	ar_tha = ptr+18;
	ar_tip = ptr+24;
	
	memcpy(&srcIpAddr, ar_sip, 4);
	entry=rtl865x_searchLocalPublic(srcIpAddr);
	if(entry!=NULL)
	{
		pktInfo->srcIp=srcIpAddr;
		pktInfo->fromLocalPublic=1;
		if(pktInfo->action==RX_LAN_PACKET)
		{
			/*learning dev/mac information*/
			strcpy(entry->dev, pktInfo->dev);
			entry->port=pktInfo->port;
			
			if((entry->hw) && (strncmp(pktInfo->dev, RTL_WLAN_NAME, 4) ==0))
			{
				rtl865x_disableLocalPublicHwFwd(entry);
				entry->hw=0;
			}
			
			rtl865x_updateLocalPublicMac(entry, ar_sha);
		}
		//printk("%s:%d, match arp source ip:%d.%d.%d.%d\n",__FUNCTION__,__LINE__,NIPQUAD(srcIpAddr));
		return SUCCESS;
	}
	else
	{
		/*receive arp reply*/
		//printk("%s:%d, RX_WAN_PACKET ,arph->ar_op is %d, source ip:%d.%d.%d.%d\n",__FUNCTION__,__LINE__,arph->ar_op, NIPQUAD(srcIpAddr));
		if((pktInfo->action==RX_WAN_PACKET) && (arph->ar_op== 0x02))
		{
			/*to check if sip is default gw*/
			CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
			{
				if((entry->hw) && (entry->defGateway==srcIpAddr))
				{
					rtl865x_updateDefaultGatewayMac(entry, ar_sha);
				}	
				
			}
		}
		
	}

	memcpy(&dstIpAddr, ar_tip, 4);
	entry=rtl865x_searchLocalPublic(dstIpAddr);
	if(entry !=NULL)
	{
		//printk("%s:%d, match arp dst ip:%d.%d.%d.%d\n",__FUNCTION__,__LINE__,NIPQUAD(dstIpAddr));
		pktInfo->dstIp=dstIpAddr;
		pktInfo->toLocalPublic=1;
		return SUCCESS;
	}

	return FAILED;
}

int rtl865x_isLocalPublicIp(unsigned int ipAddr)
{
	struct rtl865x_localPublic* entry;

	if(localPublicEnabled==FALSE)
	{
		return FALSE;
	}
	
	entry=rtl865x_searchLocalPublic(ipAddr);
	if(entry != NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return FALSE;
		
}

int rtl865x_isLocalPublicDefGw(unsigned int ipAddr)
{
	struct rtl865x_localPublic* entry;
	if(localPublicEnabled!=TRUE)
	{
		return FALSE;
	}
	
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		if(entry->defGateway==ipAddr)
		{
			return  TRUE;
		}	
		
	}
	return FALSE;
	
}


int rtl865x_getLocalPublicMac(unsigned int ip, unsigned char mac[])
{
	struct rtl865x_localPublic* entry;

	entry=rtl865x_searchLocalPublic(ip);
	if(entry != NULL)
	{
		if(memcmp(entry->mac, zeroMac, 6) !=0)
		{
			memcpy(mac, entry->mac, 6);
			return SUCCESS;
		}
		else
		{
			return FAILED;
		}
	}
	else
	{
		return FAILED;
	}

	return FAILED;	
}

int rtl865x_getLocalPublicArpMapping(unsigned int ip, rtl865x_arpMapping_entry_t * arp_mapping)
{
	struct rtl865x_localPublic* entry;

	if(arp_mapping==NULL)
	{
		return FAILED;
	}
	
	memset(arp_mapping, 0, sizeof(rtl865x_arpMapping_entry_t));

	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		if(entry->ipAddr==ip)
		{
			if(memcmp(entry->mac, zeroMac, 6) !=0)
			{
				arp_mapping->ip=(ipaddr_t)ip;
				memcpy(&(arp_mapping->mac), entry->mac, 6);
				//rtl865x_getNetifFid(lanIfInfo.ifname, &arp_mapping->fid);
				return SUCCESS;
			}
		}
		else if(entry->defGateway==ip)
		{
			if(memcmp(entry->defGwMac, zeroMac, 6) !=0)
			{
				arp_mapping->ip=(ipaddr_t)ip;
				memcpy(&(arp_mapping->mac), entry->defGwMac, 6);
				//rtl865x_getNetifFid(wanIfInfo.ifname, &arp_mapping->fid);
				return SUCCESS;
			}
		}
	};
	
	return FAILED;
}


int  rtl865x_checkLocalPublic(struct rtl865x_pktInfo* pktInfo) 
{
	
//MAC Frame :DA(6 bytes)+SA(6 bytes)+ CPU tag(4 bytes) + VlAN tag(Optional, 4 bytes)
//                   +Type(IPv4:0x0800, IPV6:0x86DD, PPPOE:0x8864, 2 bytes )+Data(46~1500 bytes)+CRC(4 bytes)
	
	uint8 *ptr;
	uint8 *srcMac;

	if(pktInfo==NULL)
	{
		return FAILED;
	}

	if(pktInfo->data==NULL )
	{
		return FAILED;
	}
	
	if(localPublicEnabled==FALSE)
	{
		return FAILED;
	}
	
	pktInfo->arpHdr=NULL;
	pktInfo->ipHdr=NULL;
	pktInfo->fromLocalPublic=FALSE;
	pktInfo->toLocalPublic=FALSE;
	pktInfo->srcIp=0;
	pktInfo->dstIp=0;
	ptr=pktInfo->data;

	srcMac=ptr+6;
	
/*		0800	IP
 *		8100    802.1Q VLAN
 *		0001	802.3
 *		0002	AX.25
 *		0004	802.2
 *		8035	RARP
 *		0005	SNAP
 *		0805	X.25
 *		0806	ARP
 *		8137	IPX
 *		0009	Localtalk
 *		8864	PPPOE
 *		86DD	IPv6
 */
	
	ptr=ptr+12;
	if((*ptr==0x81) && (*(ptr+1)==0x00))
	{
		/*check the presence of VLAN tag*/	
		ptr=ptr+4;
	}

	if((*ptr==0x08) && (*(ptr+1)==0x00))
	{
		ptr=ptr+2;
		pktInfo->ipHdr = ptr;
		return rtl865x_checkIpHdr(pktInfo);
	}
	else if((*ptr==0x08) && (*(ptr+1)==0x06))
	{
		ptr=ptr+2;
		pktInfo->arpHdr = ptr;
		return rtl865x_checkArpHdr(pktInfo);
	}
	else
	{
		return FAILED;
	}

	return FAILED;

}



int rtl865x_getLocalPublicInfo(unsigned int ipAddr, struct rtl865x_localPublic *localPublicInfo)
{
	struct rtl865x_localPublic* entry;
	if(localPublicInfo==NULL)
	{
		return FAILED;
	}

	if(localPublicEnabled==FALSE)
	{
		return FAILED;
	}
	
	memset(localPublicInfo, 0, sizeof(struct rtl865x_localPublic));

	
	entry = rtl865x_searchLocalPublic(ipAddr);

	if(entry==NULL)
	{
		return FAILED;
	}

	rtl865x_copyLocalPublic(localPublicInfo, entry);

	return SUCCESS;
	
}

int rtl865x_setLpIfInfo(struct rtl865x_interface_info *ifInfo)
{
	if(ifInfo==NULL)
	{
		return FAILED;
	}
	if(ifInfo->isWan)
	{
		memcpy(&wanIfInfo, ifInfo, sizeof(struct rtl865x_interface_info));
	}
	else
	{
		memcpy(&lanIfInfo, ifInfo, sizeof(struct rtl865x_interface_info));
	}
	return SUCCESS;
}

int rtl865x_getAllLocalPublic(struct rtl865x_localPublic localPublicArray[], int arraySize)
{
	struct rtl865x_localPublic* entry;
	int cnt=0;
	if((localPublicArray==NULL) || (arraySize==0))
	{
		return 0;
	}
	
	if((localPublicInitialized==FALSE) || (localPublicEnabled==FALSE))
	{
		return 0;
	}
	
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		rtl865x_copyLocalPublic(&localPublicArray[cnt], entry);
		cnt++;
		if(cnt>=arraySize)
		{
			break;
		}
	}
	
	return cnt;
	
}

int rtl865x_localPublicEnabled(void)
{
	return localPublicEnabled;
}
/*
int rtl865x_configLocalPublicMTU(unsigned int mtu)
{
	rtl865x_netif_t netif;
	struct rtl865x_localPublic *entry;

	if(localPublicEnabled!=TRUE)
	{
		return FAILED;
	}
	
	CTAILQ_FOREACH(entry, &usedLocalPublicList, next)
	{
		if(entry->hw)
		{
			if(entry->lpNetif[0])
			{
				memcpy(netif.name,entry->lpNetif,16);
				netif.mtu = mtu;
				rtl865x_setNetifMtu(&netif);
			}
		}
	}
	
	return SUCCESS;
}
*/



