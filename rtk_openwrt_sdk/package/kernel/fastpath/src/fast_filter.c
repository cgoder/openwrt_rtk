#if	defined(CONFIG_RTL_FAST_FILTER)

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
#include <linux/net.h>
#include <linux/socket.h>

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
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netlink.h>
#include <linux/inetdevice.h>
#include <linux/icmp.h>
#include <net/udp.h>
#include <net/tcp.h>

#include <linux/version.h>
#include <net/rtl/rtl_types.h>
#include <net/rtl/fastpath/fastpath_core.h>

#include <net/rtl/rtl865x_netif.h>
#include <net/rtl/rtl_nic.h>

#define MAX_FILTER_RULE_NUM	100
#define MAX_FILTER_RULE_LEN	1024
#define MAX_URL_KEY_LEN		64

/*---------------------------------------------netlink--start---------------------------------------------*/
#define ETH_ALEN 6
//add/delete/flush/enableLog/disableLog 
#define FILTER_ADD 		1
#define FILTER_DEL 		2
#define FILTER_FLUSH 	3
#define FILTER_EN_LOG 	4
#define FILTER_DIS_LOG 	5
#define FILTER_SHOW 	6

//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) printk(fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

struct respond_struct
{
	int flag;
	char data[1024];
};
typedef struct filter_flag{
	unsigned int ip_filter:4;			/*0:no ip filter, bit0~1: source ip filter, bit0:1 source ip filter, bit1:1 ip range filter
											bit2~bit3: destination ip filter, bit2:1 destination ip filter, bit3:1 ip range filter*/
	unsigned int port_filter:4;			/*0:no port filter, bit0~1: source port filter, bit0:1 source port filter, bit1:1 port range filter
											bit2~bit3: destination port filter, bit2:1 destination port filter, bit3:1 dst port range filter*/
	unsigned int mac_filter:4;			/*0:no mac filter, bit0~1: source mac filter, bit0:1 is source mac filter, bit1: mac range filter
											bit2~bit3: destination mac filter, bit2:1 destination mac filter, bit3:1 mac range filter*/
	unsigned int protocol_filter:2;		/*0:no protocol filter, bit0:1 tcp filter, bit1:udp filter*/														
	unsigned int url_filter:2;			/*0:no url filter, 1:match in url 2:url_key is part of url, 3:char match*/
	unsigned int src_phy_port_filter:8;	/*port mask*/
	unsigned int schedule_filter:2;		/*0:no schedule filter, 1:forever filter, 2:filter accord to timer*/
	unsigned int priority:3;				/*priority*/
	unsigned int action:3;				/*0:drop, 1:fastpath, 2:linux_protocol_stack, 3:mark, 4:finish 5:user_register*/
	unsigned int mark;
}filter_flag_s;

typedef struct mac_mask_filter{
	unsigned char mac[ETH_ALEN];
	unsigned char mask[ETH_ALEN];
}mac_filter_s, *mac_filter_p;

typedef struct mac_range_filter{
	unsigned char smac[ETH_ALEN];
	unsigned char emac[ETH_ALEN];
}mac_range_s, *mac_range_p;

typedef struct ip_mask_filter{
	struct in_addr	addr;
	struct in_addr	mask;
}ip_filter_s;

typedef struct ip_range_filter{
	struct in_addr	saddr;
	struct in_addr	eaddr;
}ip_range_filter_s;

typedef struct port_filter{
	unsigned int sport;
	unsigned int eport;
}port_filter_s;

typedef struct schedule_filter{
	unsigned char	day_mask;
	unsigned char	all_hours;
	unsigned int	stime;
	unsigned int	etime;
}schedule_filter_s, *schedule_filter_p;

typedef struct url_filter{
	unsigned char  url_key[MAX_URL_KEY_LEN];
}url_filter_s, *url_filter_p;

typedef struct tcp_ip_filter{
	union	{
		mac_filter_p	mac_mask;
		mac_range_p 	mac_range;	
	}nf_mac;
	union {
		ip_filter_s 		ip_mask;
		ip_range_filter_s	ip_range;
	}nf_ip;
	port_filter_s	nf_port;	
}tcp_ip_filter_s, *tcp_ip_filter_p;

typedef struct filter_rule{
	struct list_head	list;
	filter_flag_s		nf_flag;
	tcp_ip_filter_p		nf_src_filter;	/*include the src MAC, src IP and src port*/
	tcp_ip_filter_p		nf_dst_filter;	/*include the dst MAC, dst IP and dst port*/
	schedule_filter_s	nf_schedule;	
	url_filter_p		nf_url;
}filter_rule_s, *filter_rule_p;

typedef struct tcp_ip_filter_ap{
	union	{
		mac_filter_s	mac_mask;
		mac_range_s 	mac_range;	
	}nf_mac;
	union {
		ip_filter_s 		ip_mask;
		ip_range_filter_s	ip_range;
	}nf_ip;
	port_filter_s	nf_port;	
}tcp_ip_filter_ap_s, *tcp_ip_filter_ap_p;

typedef struct filter_rule_ap{
	filter_flag_s			nf_flag;
	tcp_ip_filter_ap_s		nf_src_filter;	/*include the src MAC, src IP and src port*/
	tcp_ip_filter_ap_s		nf_dst_filter;	/*include the dst MAC, dst IP and dst port*/
	schedule_filter_s		nf_schedule;	
	url_filter_s			nf_url;
}filter_rule_ap_s, *filter_rule_ap_p;

typedef struct filter_info{
	int action;
	filter_rule_ap_s	filter_data;
}filter_info_s, *filter_info_p;

static char 	rule_from_proc[MAX_FILTER_RULE_LEN];
static int   	log_enabled=0;
static char 	log_info[32];

static unsigned int	fast_filter_rule_num=0;
unsigned int max_fast_filter_rule_num = MAX_FILTER_RULE_NUM;

struct list_head	rtk_filter_list_head;

int rtl_fastFilterCheck(void)
{
	return (fast_filter_rule_num>0);
}

/////////////////
struct sock *filter_sk = NULL;

int rtk_filter_rule_insert(filter_rule_s *rule);
int rtk_filter_rule_delete(filter_rule_s *rule);
int rtk_filter_rule_memory_free(filter_rule_p _exist_list_entry);
int rtk_filter_list_flush(void);
int rtk_filter_show_rule(filter_rule_p exist_list_entry,char* str_buf);

int get_info_from_user(filter_rule_ap_p _user_info, filter_rule_p  _filter_info)
{
	memcpy(&(_filter_info->nf_flag),&(_user_info->nf_flag),sizeof(filter_flag_s));
	memcpy(&(_filter_info->nf_schedule),&(_user_info->nf_schedule),sizeof(schedule_filter_s));

//	DEBUG_PRINT("==_filter_info->nf_schedule.day_mask is %d, _filter_info->nf_schedule.all_hours is %d, _filter_info->nf_schedule.stime is %d ,_filter_info->nf_schedule.etime is %d,_filter_info->nf_flag.schedule_filter is %d\n",
//		_filter_info->nf_schedule.day_mask, _filter_info->nf_schedule.all_hours, _filter_info->nf_schedule.stime, _filter_info->nf_schedule.etime, _filter_info->nf_flag.schedule_filter);

	if((_filter_info->nf_flag.ip_filter & 0x3) || (_filter_info->nf_flag.mac_filter & 0x3) ||(_filter_info->nf_flag.port_filter& 0x3) )
	{//src ip
		_filter_info->nf_src_filter=kmalloc(sizeof(tcp_ip_filter_s), GFP_KERNEL);
		memcpy(&(_filter_info->nf_src_filter->nf_ip.ip_mask),&(_user_info->nf_src_filter.nf_ip.ip_mask),sizeof(ip_range_filter_s));
		memcpy(&(_filter_info->nf_src_filter->nf_port),&(_user_info->nf_src_filter.nf_port),sizeof(port_filter_s));
		if(_filter_info->nf_flag.mac_filter & 0x3)
		{
			_filter_info->nf_src_filter->nf_mac.mac_range=kmalloc(sizeof(mac_range_s), GFP_KERNEL); 
			memcpy(_filter_info->nf_src_filter->nf_mac.mac_range,&(_user_info->nf_src_filter.nf_mac.mac_range),sizeof(mac_range_s));
		}
		else
		{
			_filter_info->nf_src_filter->nf_mac.mac_mask=NULL;
		}		
	}
	else
	{
		_filter_info->nf_src_filter=NULL;
	}
	
	if((_filter_info->nf_flag.ip_filter & 0xC) || (_filter_info->nf_flag.mac_filter& 0xC) ||(_filter_info->nf_flag.port_filter& 0xC) )
	{//dst ip
		_filter_info->nf_dst_filter=kmalloc(sizeof(tcp_ip_filter_s), GFP_KERNEL);
		memcpy(&(_filter_info->nf_dst_filter->nf_ip.ip_mask),&(_user_info->nf_dst_filter.nf_ip.ip_mask),sizeof(ip_range_filter_s));
		memcpy(&(_filter_info->nf_dst_filter->nf_port),&(_user_info->nf_dst_filter.nf_port),sizeof(port_filter_s));
		
		if(_filter_info->nf_flag.mac_filter & 0xC) 
		{
			_filter_info->nf_dst_filter->nf_mac.mac_range=kmalloc(sizeof(mac_range_s), GFP_KERNEL); 	
			memcpy(_filter_info->nf_dst_filter->nf_mac.mac_range,&(_user_info->nf_dst_filter.nf_mac.mac_range),sizeof(mac_range_s));
		}
		else
		{
			_filter_info->nf_dst_filter->nf_mac.mac_mask=NULL;
		}	
	}
	else
	{
		_filter_info->nf_dst_filter=NULL;
	}
	
	if(_filter_info->nf_flag.url_filter)
	{
		_filter_info->nf_url=kmalloc(sizeof(url_filter_s), GFP_KERNEL);
		memset(_filter_info->nf_url, 0, sizeof(url_filter_s));
		memcpy(_filter_info->nf_url->url_key,_user_info->nf_url.url_key,MAX_URL_KEY_LEN);
	}
	else
		_filter_info->nf_url=NULL;

	return 0;
}

int rtk_filter_rule_show(char *_str)
{
	filter_rule_p exist_list_entry;
	int  i,ret,length=0;
	struct list_head *lh;
	char str_info[1024];
	sprintf(_str,"<<rtk_filter>> ");
	list_for_each(lh, &rtk_filter_list_head)
	{		
		exist_list_entry=list_entry(lh, filter_rule_s, list);
		ret=rtk_filter_show_rule(exist_list_entry,str_info);	
		if(ret)
		{
			if((length+ret) > 1024) break;
			length=+ret;			
			strcat(_str,str_info);
			memset(str_info, 0, 1024);
		}
	}	
	return length;
}		
void filter_data_ready (struct sk_buff *__skb)
{
  	u32 pid;
	struct respond_struct send_data;
	filter_info_s recv_data;
	filter_rule_s  filter_info;
	int ret; 

	ret=0;
	pid=0;
 	pid=rtk_nlrecvmsg(__skb,sizeof(filter_info_s),&recv_data);
	if(pid < 0) return ;
	get_info_from_user(&(recv_data.filter_data), &filter_info);

	if(recv_data.action == FILTER_ADD)
	{
		ret = rtk_filter_rule_insert(&filter_info);
		if(ret == 0)
		{
			DEBUG_PRINT("finish insert a new rule to rtk_filter_list, the fast_filter_rule_num is %d now\n", fast_filter_rule_num);
		}
		else
		{
			DEBUG_PRINT("insert a new rule to rtk_filter_list failed\n");
		}
	}
	else if(recv_data.action == FILTER_DEL)
	{
		ret = rtk_filter_rule_delete(&filter_info);
		if(ret == 0)
		{
			DEBUG_PRINT("finish delete a rule from rtk_filter_list, the filter rule num is %d now\n", fast_filter_rule_num);
		}
		else
		{
			DEBUG_PRINT("delete filter rule failed!!!!!!!!!!!\n");
		}
	}
	else if(recv_data.action == FILTER_FLUSH)
	{
		rtk_filter_list_flush();
	}
	else if(recv_data.action == FILTER_EN_LOG)
	{
		log_enabled = 1;
	}
	else if(recv_data.action == FILTER_DIS_LOG)
	{
		log_enabled = 0;
	}
	else if(recv_data.action == FILTER_SHOW)
	{
		DEBUG_PRINT("fast fitler show\n");		
	}
	else
		DEBUG_PRINT("the filter data receive from netlink is fault\n");

	if(recv_data.action == FILTER_SHOW)
	{
		struct list_head *lh;
		filter_rule_p exist_list_entry;
		memset(&send_data, 0, sizeof(struct respond_struct));
		list_for_each(lh, &rtk_filter_list_head)
		{		
			exist_list_entry=list_entry(lh, filter_rule_s, list);
			ret=rtk_filter_show_rule(exist_list_entry,send_data.data);	
			send_data.flag=ret;	
			DEBUG_PRINT("pid=%d\n",pid);
			DEBUG_PRINT("<<len=%d>>\n%s\n",send_data.flag,send_data.data);
			rtk_nlsendmsg(pid,filter_sk,sizeof(struct respond_struct),&send_data);
			memset(&send_data, 0, sizeof(struct respond_struct));
		}	
		memset(&send_data, 0, sizeof(struct respond_struct));
		rtk_nlsendmsg(pid,filter_sk,sizeof(struct respond_struct),&send_data);
	}
	else
	{
		send_data.flag=recv_data.action;
		sprintf(send_data.data,"fastpath filter");
		rtk_nlsendmsg(pid,filter_sk,sizeof(struct respond_struct),&send_data);
	}
  	return;
}

static int filter_netlink(void) 
{
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	struct netlink_kernel_cfg cfg = {
		.groups		= 0,
		.input		= filter_data_ready,
		.cb_mutex	= NULL,
	};
	  filter_sk = netlink_kernel_create(&init_net, NETLINK_RTK_FILTER, &cfg);
	#else
  	filter_sk = netlink_kernel_create(&init_net, NETLINK_RTK_FILTER, 0, filter_data_ready, NULL, THIS_MODULE);
	#endif
	
  	if (!filter_sk) {
    		printk(KERN_ERR "Netlink[Kernel] Cannot create netlink socket.\n");
    		return -EIO;
  	}	
  	DEBUG_PRINT("Netlink[filter netlink] create socket ok.\n");
  	return 0;
}
/////////////////
static int find_pattern(const char *data, size_t dlen, const char *pattern, size_t plen, char term, unsigned int *numoff, unsigned int *numlen)
{
	size_t i,j,k;
	int state =0;
	*numoff = *numlen=0;
	for(i=0; i <= (dlen -plen);i++)
	{
	      if (*(data + i) == '\r')
	      {
            	  if (!(state % 2)) state++;  /* forwarding move */
              	  else state = 0;             /* reset */
              }
	      else if (*(data + i) == '\n')
	      {
	          if (state % 2) state++;
	          else state = 0;
              }
              else state = 0;

	      if (state >= 4)
	           break;
	      if(memcmp(data + i, pattern, plen)!=0)
		      continue;
	      *numoff=i + plen;
	      for (j = *numoff, k = 0; data[j] != term; j++, k++)
	        if (j > dlen) return 0 ;   /* no terminal char */
	      *numlen = k;
	      return 1;
		      
	}
 return 0;

}

static int find_url_key(const char *data, size_t dlen, const char *pattern, size_t plen, char term)
{
	int i;

	/*
	if(pattern[plen] == '\0')
	{
		plen--;
	}
	*/
	if(plen > dlen)
	  	return 0;
	
	for(i=0; data[i+plen] !=term ;i++)
	{
		//DEBUG_PRINT("===%s---%d, i is %d,pattern is %s\n", __FUNCTION__, __LINE__, i, pattern);
		if(memcmp(data + i, pattern, plen)!=0)
			continue;
		else
			return 1;
	}
  return 0;
}



int rtk_filter_list_head_init(void)
{
	INIT_LIST_HEAD(&rtk_filter_list_head);
	fast_filter_rule_num = 0;
}
 
char *transfer_ip(struct in_addr ipaddr,char *str)
{
	uint8 *ucp = (unsigned char *)&ipaddr.s_addr;
	sprintf(str,"%d.%d.%d.%d",ucp[0] & 0xFF,ucp[1] & 0xFF,ucp[2] & 0xFF,ucp[3] & 0xFF);
	return str;
}
//inet_aton(address, (struct in_addr *) &a.sin_addr.s_addr
int rtk_filter_show_rule(filter_rule_p exist_list_entry,char* str_buf)
{
	char str_tmp[128];
	
	sprintf(str_tmp,"0x%x:\n",exist_list_entry->nf_flag);
	strcat(str_buf,str_tmp);	
	memset(str_tmp, 0, 128);
	
	if(exist_list_entry->nf_flag.ip_filter & 0x1)
	{
		char str_ip[32],str_ip1[32];
		sprintf(str_tmp,"source ip %s mask %s ",
										transfer_ip(exist_list_entry->nf_src_filter->nf_ip.ip_mask.addr,str_ip),
										transfer_ip(exist_list_entry->nf_src_filter->nf_ip.ip_mask.mask,str_ip1));	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	if(exist_list_entry->nf_flag.ip_filter & 0x2)
	{
		char str_ip[32],str_ip1[32];
		sprintf(str_tmp,"source start ip %s end ip %s ",transfer_ip(exist_list_entry->nf_src_filter->nf_ip.ip_range.saddr,str_ip),transfer_ip(exist_list_entry->nf_src_filter->nf_ip.ip_range.eaddr,str_ip1));	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	if(exist_list_entry->nf_flag.ip_filter & 0x4)
	{
		char str_ip[32],str_ip1[32];
		sprintf(str_tmp,"destination ip %s mask %s ",transfer_ip(exist_list_entry->nf_dst_filter->nf_ip.ip_mask.addr,str_ip),transfer_ip(exist_list_entry->nf_dst_filter->nf_ip.ip_mask.mask,str_ip1));	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	if(exist_list_entry->nf_flag.ip_filter & 0x8)
	{
		char str_ip[32],str_ip1[32];
		sprintf(str_tmp,"destination start ip %s end ip %s ",transfer_ip(exist_list_entry->nf_dst_filter->nf_ip.ip_range.saddr,str_ip),transfer_ip(exist_list_entry->nf_dst_filter->nf_ip.ip_range.eaddr,str_ip1));	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}

	if(exist_list_entry->nf_flag.port_filter & 0x1)
	{
		sprintf(str_tmp,"source port start %d end %d ",exist_list_entry->nf_src_filter->nf_port.sport,exist_list_entry->nf_src_filter->nf_port.eport);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	if(exist_list_entry->nf_flag.port_filter & 0x4)
	{
		sprintf(str_tmp,"destination port start %d end %d ",exist_list_entry->nf_dst_filter->nf_port.sport,exist_list_entry->nf_dst_filter->nf_port.eport);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}

	if(exist_list_entry->nf_flag.mac_filter& 0x1)
	{
		sprintf(str_tmp,"source mac %02x:%02x:%02x:%02x:%02x:%02x mac mask %02x:%02x:%02x:%02x:%02x:%02x ",
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mac[0],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mac[1],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mac[2],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mac[3],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mac[4],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mac[5],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mask[0],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mask[1],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mask[2],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mask[3],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mask[4],
											exist_list_entry->nf_src_filter->nf_mac.mac_mask->mask[5]
											);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	if(exist_list_entry->nf_flag.mac_filter& 0x2)
	{
		sprintf(str_tmp,"source start mac %02x:%02x:%02x:%02x:%02x:%02x end mac %02x:%02x:%02x:%02x:%02x:%02x ",
											exist_list_entry->nf_src_filter->nf_mac.mac_range->smac[0],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->smac[1],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->smac[2],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->smac[3],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->smac[4],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->smac[5],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->emac[0],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->emac[1],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->emac[2],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->emac[3],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->emac[4],
											exist_list_entry->nf_src_filter->nf_mac.mac_range->emac[5]
											);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	if(exist_list_entry->nf_flag.mac_filter& 0x4)
	{
		sprintf(str_tmp,"destination mac %02x:%02x:%02x:%02x:%02x:%02x mac mask %02x:%02x:%02x:%02x:%02x:%02x ",
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mac[0],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mac[1],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mac[2],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mac[3],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mac[4],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mac[5],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mask[0],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mask[1],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mask[2],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mask[3],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mask[4],
											exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mask[5]
											);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	if(exist_list_entry->nf_flag.mac_filter& 0x8)
	{
		sprintf(str_tmp,"destination start mac %02x:%02x:%02x:%02x:%02x:%02x end mac %02x:%02x:%02x:%02x:%02x:%02x ",
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->smac[0],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->smac[1],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->smac[2],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->smac[3],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->smac[4],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->smac[5],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->emac[0],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->emac[1],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->emac[2],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->emac[3],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->emac[4],
											exist_list_entry->nf_dst_filter->nf_mac.mac_range->emac[5]
											);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}

	if(exist_list_entry->nf_flag.protocol_filter)
	{
		if(exist_list_entry->nf_flag.protocol_filter == 1)
			sprintf(str_tmp,"protocol tcp ");	
		else if(exist_list_entry->nf_flag.protocol_filter == 2)
			sprintf(str_tmp,"protocol udp ");	
		else if(exist_list_entry->nf_flag.protocol_filter == 3)
			sprintf(str_tmp,"protocol tcp and udp ");	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}

	if(exist_list_entry->nf_flag.url_filter)
	{
		sprintf(str_tmp,"url %s ",exist_list_entry->nf_url->url_key);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}

	if(exist_list_entry->nf_flag.src_phy_port_filter)
	{
		sprintf(str_tmp,"phyiscal port mask 0x%x ",exist_list_entry->nf_flag.src_phy_port_filter);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}

	if(exist_list_entry->nf_flag.src_phy_port_filter)
	{
		sprintf(str_tmp,"phyiscal port mask 0x%x ",exist_list_entry->nf_flag.src_phy_port_filter);	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}

	if(exist_list_entry->nf_flag.schedule_filter )
	{
		if((exist_list_entry->nf_flag.schedule_filter ) == 0x1)
		{
			sprintf(str_tmp,"schedule forever ");	
			strcat(str_buf,str_tmp);	
			memset(str_tmp, 0, 128);
		}
		else if((exist_list_entry->nf_flag.schedule_filter ) ==  0x2)
		{
			if(exist_list_entry->nf_schedule.all_hours)
				sprintf(str_tmp,"schedule day mask 0x%08x all hours ",exist_list_entry->nf_schedule.day_mask);	
			else
				sprintf(str_tmp,"schedule day mask 0x%08x start time %d:%d end time %d:%d ",
																exist_list_entry->nf_schedule.day_mask,
																exist_list_entry->nf_schedule.stime/60,
																exist_list_entry->nf_schedule.stime%60,
																exist_list_entry->nf_schedule.etime/60,
																exist_list_entry->nf_schedule.etime%60
																);	
			strcat(str_buf,str_tmp);	
			memset(str_tmp, 0, 128);
		}
	}

	sprintf(str_tmp,"priority %d ",exist_list_entry->nf_flag.priority);	
	strcat(str_buf,str_tmp);	
	memset(str_tmp, 0, 128);

	if(exist_list_entry->nf_flag.action == NF_DROP)
	{
		sprintf(str_tmp,"policy  drop");	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	else if(exist_list_entry->nf_flag.action == NF_FASTPATH)
	{
		sprintf(str_tmp,"policy  accept and fastpath");	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	else if(exist_list_entry->nf_flag.action == NF_LINUX)
	{
		sprintf(str_tmp,"policy  accept and to protocol");	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	else if(exist_list_entry->nf_flag.action == NF_MARK)
	{
		sprintf(str_tmp,"policy  mark");	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	else if(exist_list_entry->nf_flag.action == NF_OMIT)
	{
		sprintf(str_tmp,"policy  NULL");	
		strcat(str_buf,str_tmp);	
		memset(str_tmp, 0, 128);
	}
	//printk("%s\n",str_buf);
	return strlen(str_buf);
}

int rtk_filter_rule_insert(filter_rule_s *rule)
{
#if 1
	struct list_head	*exist_list_entry;
	filter_rule_s		*new_list_entry;
	int priority;
	int i;

	new_list_entry = kmalloc(sizeof(filter_rule_s), GFP_KERNEL);
	if(new_list_entry == NULL)
		return -ENOMEM;

	memcpy(new_list_entry, rule, sizeof(filter_rule_s));
	INIT_LIST_HEAD(&new_list_entry->list);

	if (fast_filter_rule_num==0)
	{
		list_add(&new_list_entry->list, &rtk_filter_list_head);
	}
	else
	{
		exist_list_entry = &rtk_filter_list_head;
		for(i=0;i<fast_filter_rule_num;i++)
		{
			if (((filter_rule_s*)(exist_list_entry->next))->nf_flag.priority>=priority)
			{
				break;
			} else {
				exist_list_entry = exist_list_entry->next;
			}
		}
		list_add(&new_list_entry->list, exist_list_entry);
	}

	fast_filter_rule_num++;
	return SUCCESS;
#else
	filter_rule_s 		*exist_list_entry;
	filter_rule_s		*new_list_entry;
	struct list_head *lh;
	int priority;
	int i;

	new_list_entry = kmalloc(sizeof(filter_rule_s), GFP_KERNEL);
	if(new_list_entry == NULL)
		return -ENOMEM;

	memcpy(new_list_entry, rule, sizeof(filter_rule_s));
	INIT_LIST_HEAD(&new_list_entry->list);
	priority = new_list_entry->nf_flag.priority;

	if (fast_filter_rule_num==0)
	{
		list_add(&new_list_entry->list, &rtk_filter_list_head);
	}
	else
	{
		
		list_for_each(lh, &rtk_filter_list_head)
		{
			exist_list_entry=list_entry(lh, filter_rule_s, list);
			if (exist_list_entry->nf_flag.priority >= priority)
			{
				break;
			} 
		}
		list_add(&new_list_entry->list, exist_list_entry);
	}
	rtk_filter_show_rule(new_list_entry);

	fast_filter_rule_num++;
	return SUCCESS;
#endif
}

int rtk_filter_rule_memory_free(filter_rule_p exist_list_entry)
{
	if(exist_list_entry->nf_src_filter != NULL)
	{
		if(exist_list_entry->nf_src_filter->nf_mac.mac_mask != NULL)
		{
			kfree(exist_list_entry->nf_src_filter->nf_mac.mac_mask);
			exist_list_entry->nf_src_filter->nf_mac.mac_mask = NULL;
		}
		kfree(exist_list_entry->nf_src_filter);
		exist_list_entry->nf_src_filter = NULL;
	}

	if(exist_list_entry->nf_dst_filter != NULL)
	{
		if(exist_list_entry->nf_dst_filter->nf_mac.mac_mask != NULL)
		{
			kfree(exist_list_entry->nf_dst_filter->nf_mac.mac_mask);
			exist_list_entry->nf_dst_filter->nf_mac.mac_mask = NULL;
		}
		kfree(exist_list_entry->nf_dst_filter);
		exist_list_entry->nf_dst_filter = NULL;
	}

	if(exist_list_entry->nf_url != NULL)
	{
		kfree(exist_list_entry->nf_url);
		exist_list_entry->nf_url = NULL;
	}	
	exist_list_entry->list.next= NULL;
	exist_list_entry->list.prev= NULL;

	return 0;
}

int rtk_filter_rule_delete(filter_rule_s *rule)
{
#if 1
	struct list_head *exist_list_entry;
	filter_flag_s *p1, *p2;
	int matched, i;

	exist_list_entry = &rtk_filter_list_head;
	i = 0;

	DEBUG_PRINT("filter list len [%d]\n", fast_filter_rule_num);
	while(i<fast_filter_rule_num)
	{
		i++;
		matched = 0;
		exist_list_entry = exist_list_entry->next;
			
		if(exist_list_entry== NULL)
		{
			DEBUG_PRINT("filter list entry is NULL, it seems to be error!!!\n");
			return -EINVAL;
		}

		p1 = &(rule->nf_flag);
		p2 = &(((filter_rule_s*)exist_list_entry)->nf_flag);

		if (memcmp(p1, p2, sizeof(filter_flag_s))==0)
		{
			DEBUG_PRINT("rule search: flags equals.\n");
			DEBUG_PRINT("rule search: check nf src filter[0x%p]:[0x%p].\n", rule->nf_src_filter, ((filter_rule_s*)exist_list_entry)->nf_src_filter);
			if(rule->nf_src_filter !=NULL && ((filter_rule_s*)exist_list_entry)->nf_src_filter != NULL)
			{	
				DEBUG_PRINT("rule search: check src ip filter flags[0x%x].\n", rule->nf_flag.ip_filter);
				if(rule->nf_flag.ip_filter != 0)
				{
					if(rule->nf_flag.ip_filter & 0x2) //iprange filter
					{
						if((rule->nf_src_filter->nf_ip.ip_range.saddr.s_addr != ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_ip.ip_range.saddr.s_addr)
							|| (rule->nf_src_filter->nf_ip.ip_range.eaddr.s_addr != ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_ip.ip_range.eaddr.s_addr))
							continue;
						else 
							matched = 1;
					}
					else if(rule->nf_flag.ip_filter & 0x1) //ip mask
					{
						if(rule->nf_src_filter->nf_ip.ip_mask.addr.s_addr != ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_ip.ip_mask.addr.s_addr
							|| rule->nf_src_filter->nf_ip.ip_mask.mask.s_addr != ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_ip.ip_mask.mask.s_addr)
							continue;
						else 
							matched = 1;
					}
				}
				
				DEBUG_PRINT("rule search: check src mac flags[0x%x].\n", rule->nf_flag.mac_filter);
				if(rule->nf_flag.mac_filter != 0)
				{
					if(rule->nf_flag.mac_filter & 0x2) // mac range filter
					{
						if(memcmp(rule->nf_src_filter->nf_mac.mac_range->smac, ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_mac.mac_range->smac, ETH_ALEN)
							|| memcmp(rule->nf_src_filter->nf_mac.mac_range->emac, ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_mac.mac_range->emac, ETH_ALEN))
							continue;
						else 
							matched = 1;
					}
					else if(rule->nf_flag.mac_filter & 0x1)
					{
						if(memcmp(rule->nf_src_filter->nf_mac.mac_mask->mac, ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_mac.mac_mask->mac, ETH_ALEN))
							continue;
						else 
							matched = 1;
					}
				}

				DEBUG_PRINT("rule search: check src port flags[0x%x].\n", rule->nf_flag.port_filter);
	 			if(rule->nf_flag.port_filter != 0)
	 			{

					if(rule->nf_flag.port_filter&0x3) //source port filter
					{
						if((rule->nf_src_filter->nf_port.sport != ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_port.sport)
							|| (rule->nf_src_filter->nf_port.eport != ((filter_rule_s*)exist_list_entry)->nf_src_filter->nf_port.eport))
							continue;
						else
						{
							matched = 1;
						}
					}
	 			}				
			}//end of nf_src_filter matching

			DEBUG_PRINT("rule search: check nf dst filter[0x%p]:[0x%p].\n", rule->nf_dst_filter, ((filter_rule_s*)exist_list_entry)->nf_dst_filter);
			if(rule->nf_dst_filter != NULL && ((filter_rule_s*)exist_list_entry)->nf_dst_filter != NULL)
			{
				DEBUG_PRINT("rule search: check dst ip filter flags[0x%x].\n", rule->nf_flag.ip_filter);
				if(rule->nf_flag.ip_filter != 0)
				{
					if(rule->nf_flag.ip_filter & 0x8) //iprange filter
					{
						if(rule->nf_dst_filter->nf_ip.ip_range.saddr.s_addr != ((filter_rule_s*)exist_list_entry)->nf_dst_filter->nf_ip.ip_range.saddr.s_addr 
							|| rule->nf_dst_filter->nf_ip.ip_range.eaddr.s_addr != ((filter_rule_s*)exist_list_entry)->nf_dst_filter->nf_ip.ip_range.eaddr.s_addr)
							continue;
						else 
							matched = 1;
						
 					}
					else if(rule->nf_flag.ip_filter & 0x4)
					{
 						if(rule->nf_dst_filter->nf_ip.ip_mask.addr.s_addr != ((filter_rule_s*)exist_list_entry)->nf_dst_filter->nf_ip.ip_mask.addr.s_addr)
							continue;
						else 
							matched = 1;
 					}
 				}

				DEBUG_PRINT("rule search: check dst mac filter flags[0x%x].\n", rule->nf_flag.mac_filter);
 				if(rule->nf_flag.mac_filter != 0)
				{			
					if(rule->nf_flag.mac_filter & 0x8) // mac range filter
					{
						if(memcmp(rule->nf_dst_filter->nf_mac.mac_range->smac, ((filter_rule_s*)exist_list_entry)->nf_dst_filter->nf_mac.mac_range->smac, ETH_ALEN)
							|| memcmp(rule->nf_dst_filter->nf_mac.mac_range->emac, ((filter_rule_s*)exist_list_entry)->nf_dst_filter->nf_mac.mac_range->emac, ETH_ALEN))
							continue;
						else 
							matched = 1;
					}
 					else if(rule->nf_flag.mac_filter & 0x4)
					{
						if(!memcmp(rule->nf_dst_filter->nf_mac.mac_mask->mac, ((filter_rule_s*)exist_list_entry)->nf_dst_filter->nf_mac.mac_mask->mac, ETH_ALEN))
							continue;
						else 
							matched = 1;
					}
 				}

				DEBUG_PRINT("rule search: check dst port filter flags[0x%x].\n", rule->nf_flag.port_filter);
				if(rule->nf_flag.port_filter != 0)
	 			{
					if(rule->nf_flag.port_filter&0xc)
					{
						if((rule->nf_dst_filter->nf_port.sport != ((filter_rule_s*)exist_list_entry)->nf_dst_filter->nf_port.sport)
							|| (rule->nf_dst_filter->nf_port.eport != ((filter_rule_s*)exist_list_entry)->nf_dst_filter->nf_port.eport))
							continue;
						else 
							matched = 1;
					}
						
				} //end of nf_port matching

 			}//end of nf_dst_filter matching
			

			DEBUG_PRINT("rule search: check schedule [0x%x]\n", rule->nf_flag.schedule_filter);
			if(rule->nf_flag.schedule_filter != 0)
			{			
				if(rule->nf_schedule.day_mask != ((filter_rule_s*)exist_list_entry)->nf_schedule.day_mask
					|| rule->nf_schedule.all_hours != ((filter_rule_s*)exist_list_entry)->nf_schedule.all_hours
					|| rule->nf_schedule.stime != ((filter_rule_s*)exist_list_entry)->nf_schedule.stime
					|| rule->nf_schedule.etime != ((filter_rule_s*)exist_list_entry)->nf_schedule.etime)
					continue;	
				else 
					matched = 1;
			} //end of nf_schedule matching

			if(rule->nf_flag.url_filter != 0)
			{
				if(rule->nf_url == NULL || ((filter_rule_s*)exist_list_entry)->nf_url == NULL)
					continue;
				else 
					matched = 1;
				
				if(memcmp(rule->nf_url, ((filter_rule_s*)exist_list_entry)->nf_url, strlen(rule->nf_url))) ////
					continue;
				else 
					matched = 1;
			} //end of nf_url matching

			if(rule->nf_flag.protocol_filter != 0)
			{
				if(rule->nf_flag.protocol_filter != ((filter_rule_s*)exist_list_entry)->nf_flag.protocol_filter)
					continue;
				else
					matched = 1;
			}

			if(rule->nf_flag.src_phy_port_filter != 0)
			{
				if(rule->nf_flag.src_phy_port_filter != ((filter_rule_s*)exist_list_entry)->nf_flag.src_phy_port_filter)
					continue;
				else
					matched = 1;
			}

			DEBUG_PRINT("rule search: matched [%d]\n", matched);
			if(matched == 1)
			{
				list_del(exist_list_entry);
				rtk_filter_rule_memory_free((filter_rule_s*)exist_list_entry);
				kfree(exist_list_entry);
				fast_filter_rule_num--;
				return SUCCESS;
			}
		}
	}

	return -EINVAL;
#else
	filter_rule_s *exist_list_entry;
	filter_flag_s *p1;
	int matched, i;
	struct list_head *lh;

	p1 = &(rule->nf_flag);

	list_for_each(lh, &rtk_filter_list_head)
 	{
		matched = 0;			
		exist_list_entry=list_entry(lh, filter_rule_s, list);

		if(exist_list_entry== NULL)
		{
			DEBUG_PRINT("filter list entry is NULL, it seems to be error!!!\n");
			return -EINVAL;
		}		

		if (memcmp(p1, &(exist_list_entry->nf_flag), sizeof(filter_rule_s))==0)
		{	
			if(rule->nf_src_filter !=NULL && exist_list_entry->nf_src_filter != NULL)
			{	
				if(rule->nf_flag.ip_filter != 0)
				{
					if(rule->nf_flag.ip_filter & 0x2) //iprange filter
					{
						if((rule->nf_src_filter->nf_ip.ip_range.saddr.s_addr != exist_list_entry->nf_src_filter->nf_ip.ip_range.saddr.s_addr)
							|| (rule->nf_src_filter->nf_ip.ip_range.eaddr.s_addr != exist_list_entry->nf_src_filter->nf_ip.ip_range.eaddr.s_addr))
							continue;
						else 
							matched = 1;
					}
					else if(rule->nf_flag.ip_filter & 0x1) //ip mask
					{
						if(rule->nf_src_filter->nf_ip.ip_mask.addr.s_addr != exist_list_entry->nf_src_filter->nf_ip.ip_mask.addr.s_addr
							|| rule->nf_src_filter->nf_ip.ip_mask.mask.s_addr != exist_list_entry->nf_src_filter->nf_ip.ip_mask.mask.s_addr)
							continue;
						else 
							matched = 1;
					}
				}
				

				if(rule->nf_flag.mac_filter != 0)
				{
					if(rule->nf_flag.mac_filter & 0x2) // mac range filter
					{
						if(memcmp(rule->nf_src_filter->nf_mac.mac_range->smac, exist_list_entry->nf_src_filter->nf_mac.mac_range->smac, ETH_ALEN)
							|| memcmp(rule->nf_src_filter->nf_mac.mac_range->emac, exist_list_entry->nf_src_filter->nf_mac.mac_range->emac, ETH_ALEN))
							continue;
						else 
							matched = 1;
					}
					else if(rule->nf_flag.mac_filter & 0x1)
					{
						if(memcmp(rule->nf_src_filter->nf_mac.mac_mask->mac, exist_list_entry->nf_src_filter->nf_mac.mac_mask->mac, ETH_ALEN))
							continue;
						else 
							matched = 1;
					}
				}

	 			if(rule->nf_flag.port_filter != 0)
	 			{

					if(rule->nf_flag.port_filter&0x3) //source port filter
					{
						if((rule->nf_src_filter->nf_port.sport != exist_list_entry->nf_src_filter->nf_port.sport)
							|| (rule->nf_src_filter->nf_port.eport != exist_list_entry->nf_src_filter->nf_port.eport))
							continue;
						else
						{
							matched = 1;
						}
					}
	 			}				
			}//end of nf_src_filter matching
			
			if(rule->nf_dst_filter != NULL && exist_list_entry->nf_dst_filter != NULL)
			{

				if(rule->nf_flag.ip_filter != 0)
				{

					if(rule->nf_flag.ip_filter & 0x8) //iprange filter
					{
						if(rule->nf_dst_filter->nf_ip.ip_range.saddr.s_addr != exist_list_entry->nf_dst_filter->nf_ip.ip_range.saddr.s_addr 
							|| rule->nf_dst_filter->nf_ip.ip_range.eaddr.s_addr != exist_list_entry->nf_dst_filter->nf_ip.ip_range.eaddr.s_addr)
							continue;
						else 
							matched = 1;
						
 					}
					else if(rule->nf_flag.ip_filter & 0x4)
					{
 						if(rule->nf_dst_filter->nf_ip.ip_mask.addr.s_addr != exist_list_entry->nf_dst_filter->nf_ip.ip_mask.addr.s_addr)
							continue;
						else 
							matched = 1;
 					}
 				}
 				if(rule->nf_flag.mac_filter != 0)
				{			
					if(rule->nf_flag.mac_filter & 0x8) // mac range filter
					{
						if(memcmp(rule->nf_dst_filter->nf_mac.mac_range->smac, exist_list_entry->nf_dst_filter->nf_mac.mac_range->smac, ETH_ALEN)
							|| memcmp(rule->nf_dst_filter->nf_mac.mac_range->emac, exist_list_entry->nf_dst_filter->nf_mac.mac_range->emac, ETH_ALEN))
							continue;
						else 
							matched = 1;
					}
 					else if(rule->nf_flag.mac_filter & 0x4)
					{
						if(!memcmp(rule->nf_dst_filter->nf_mac.mac_mask->mac, exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mac, ETH_ALEN))
							continue;
						else 
							matched = 1;
					}
 				}

				if(rule->nf_flag.port_filter != 0)
	 			{
					if(rule->nf_flag.port_filter&0xc)
					{
						if((rule->nf_dst_filter->nf_port.sport != exist_list_entry->nf_dst_filter->nf_port.sport)
							|| (rule->nf_dst_filter->nf_port.eport != exist_list_entry->nf_dst_filter->nf_port.eport))
							continue;
						else 
							matched = 1;
					}
						
				} //end of nf_port matching

 			}//end of nf_dst_filter matching
			

			if(rule->nf_flag.schedule_filter != 0)
			{			
				if(rule->nf_schedule.day_mask != exist_list_entry->nf_schedule.day_mask
					|| rule->nf_schedule.all_hours != exist_list_entry->nf_schedule.all_hours
					|| rule->nf_schedule.stime != exist_list_entry->nf_schedule.stime
					|| rule->nf_schedule.etime != exist_list_entry->nf_schedule.etime)
					continue;	
				else 
					matched = 1;
			} //end of nf_schedule matching

			if(rule->nf_flag.url_filter != 0)
			{
				if(rule->nf_url == NULL || exist_list_entry->nf_url == NULL)
					continue;
				else 
					matched = 1;
				
				if(memcmp(rule->nf_url, exist_list_entry->nf_url, strlen(rule->nf_url))) ////
					continue;
				else 
					matched = 1;
			} //end of nf_url matching

			if(rule->nf_flag.protocol_filter != 0)
			{
				if(rule->nf_flag.protocol_filter != exist_list_entry->nf_flag.protocol_filter)
					continue;
				else
					matched = 1;
			}

			if(rule->nf_flag.src_phy_port_filter != 0)
			{
				if(rule->nf_flag.src_phy_port_filter != exist_list_entry->nf_flag.src_phy_port_filter)
					continue;
				else
					matched = 1;
			}

			if(matched == 1)
			{
				list_del(exist_list_entry);

				rtk_filter_rule_memory_free(exist_list_entry);
		
				kfree(exist_list_entry);
				fast_filter_rule_num--;
				return SUCCESS;
			}
		}
   	}

	return -EINVAL;
#endif
}

int rtk_filter_list_flush(void)
{
#if 1
	struct list_head *exist_list_entry;

	while(fast_filter_rule_num>0)
	{
		exist_list_entry = rtk_filter_list_head.next;
		list_del(exist_list_entry);
		rtk_filter_rule_memory_free((filter_rule_s*)exist_list_entry);
		kfree(exist_list_entry);
		fast_filter_rule_num--;
 	}
	
	return SUCCESS;
#else
	filter_rule_s *exist_list_entry,*next_list_entry;
	struct list_head *lh;

	list_for_each(lh, &rtk_filter_list_head)
 	{
 		exist_list_entry=list_entry(lh, filter_rule_s, list);
 		list_del(exist_list_entry);
		rtk_filter_show_rule(exist_list_entry);
		printk("%s----->%d\n",__FUNCTION__,__LINE__);
		rtk_filter_rule_memory_free(exist_list_entry);
		printk("%s----->%d\n",__FUNCTION__,__LINE__);	
		if(exist_list_entry!= NULL)
			kfree(exist_list_entry);	
    	}
	fast_filter_rule_num=0;
	return SUCCESS;
#endif
}

int fast_filter_init(void)
{
	rtk_filter_list_head_init();
	filter_netlink();
	return 0;
}


int rtk_filter_schedule(filter_rule_p exist_list_entry, struct sk_buff *skb)
{
	struct timeval tv;
	unsigned int today, hour,minute;
	unsigned int curtime;
	unsigned int start,end,day;

	if(exist_list_entry->nf_flag.schedule_filter == 1)
		return 0;

	start = exist_list_entry->nf_schedule.stime;
	end = exist_list_entry->nf_schedule.etime;
	day = exist_list_entry->nf_schedule.day_mask;
	
	/*get system time*/
	do_gettimeofday(&tv);
	today = ((tv.tv_sec/86400) + 4)%7;
#if (!(defined(CONFIG_RTL8186_KB_N) ||defined(CONFIG_RTL8186_KB)))	
	hour = (tv.tv_sec/3600)%24;
#endif
	minute = (tv.tv_sec/60)%60;
	curtime = hour * 60 + minute;
	//printk("start=0x%x, end=0x%x, day=%x\n", start, end, day);
	//printk("hour=%d, today=0x%x, curtime is %d\n",hour,today, curtime);
	
	if((day & (0x1 << 7)) || (day & (0x1 << today)))
	{		
		if( ((start == 0 ) && (end == 0)) || ((start <= curtime) && (curtime <=end)))
		{
			return 0;
		}
	}
	return -1;
}


int rtk_filter_mac(filter_rule_p exist_list_entry, struct sk_buff *skb)
{
	int i;
	char *smac, *emac;
	

	if(exist_list_entry->nf_flag.mac_filter & 0x1) //source MAC
	{
		smac = &exist_list_entry->nf_src_filter->nf_mac.mac_mask->mac;
		for(i=0; i<ETH_ALEN; i++)
		{
			if((smac[i]&0xff) != skb_mac_header(skb)[ETH_ALEN+i])
				break;
		}
		
		if(i != ETH_ALEN)
			goto unmatch;	
	}

	if(exist_list_entry->nf_flag.mac_filter & 0x2) //src MAC range
	{
		smac = &exist_list_entry->nf_src_filter->nf_mac.mac_range->smac;
		emac = &exist_list_entry->nf_src_filter->nf_mac.mac_range->emac;
		for(i=0; i<ETH_ALEN; i++)
		{
			if( (smac[i]&0xff) == (emac[i]&0xff) )
			{
				if(skb_mac_header(skb)[ETH_ALEN+i] != (smac[i]&0xff) )
					break;
			}
			else if((smac[i]&0xff) < (emac[i]&0xff))
			{
				if( (skb_mac_header(skb)[ETH_ALEN+i] > (smac[i]&0xff)) && (skb_mac_header(skb)[ETH_ALEN+i] < (emac[i]&0xff)))
				{
					i = ETH_ALEN;
					break;
				}
				else if(skb_mac_header(skb)[ETH_ALEN+i] == (smac[i]&0xff))
				{
					i++;
					while(i<ETH_ALEN)
					{
						if(skb_mac_header(skb)[ETH_ALEN+i] < (smac[i]&0xff))
							goto unmatch;
						else
							i++;
					}
				}
				else if(skb_mac_header(skb)[ETH_ALEN+i] == (emac[i]&0xff))
				{
					i++;
					while(i<ETH_ALEN)
					{
						if(skb_mac_header(skb)[ETH_ALEN+i] > (emac[i]&0xff))
							goto unmatch;
						else
							i++;
					}
				}
			}
			
		}

		if(i != ETH_ALEN)
			goto unmatch;		
	}


	if(exist_list_entry->nf_flag.mac_filter & 0x4) //dst MAC
	{
		smac = &exist_list_entry->nf_dst_filter->nf_mac.mac_mask->mac;
		for(i=0; i<ETH_ALEN; i++)
		{
			if((smac[i]&0xff) != skb_mac_header(skb)[i])
				break;
		}
		
		if(i != ETH_ALEN)
			goto unmatch;	
	}

	if(exist_list_entry->nf_flag.mac_filter & 0x8) //dst MAC range
	{
		smac = &exist_list_entry->nf_dst_filter->nf_mac.mac_range->smac;
		emac = &exist_list_entry->nf_dst_filter->nf_mac.mac_range->emac;
		for(i=0; i<ETH_ALEN; i++)
		{
			if( (smac[i]&0xff) == (emac[i]&0xff) )
			{
				if(skb_mac_header(skb)[i] != (smac[i]&0xff) )
					break;
			}
			else if((smac[i]&0xff) < (emac[i]&0xff))
			{
				if( (skb_mac_header(skb)[i] > (smac[i]&0xff)) && (skb_mac_header(skb)[i] < (emac[i]&0xff)))
				{
					i = ETH_ALEN;
					break;
				}
				else if(skb_mac_header(skb)[i] == (smac[i]&0xff))
				{
					i++;
					while(i<ETH_ALEN)
					{
						if(skb_mac_header(skb)[i] < (smac[i]&0xff))
							goto unmatch;
						else
							i++;
					}
				}
				else if(skb_mac_header(skb)[i] == (emac[i]&0xff))
				{
					i++;
					while(i<ETH_ALEN)
					{
						if(skb_mac_header(skb)[i] > (emac[i]&0xff))
							goto unmatch;
						else
							i++;
					}
				}
			}
			
		}

		if(i < ETH_ALEN)
			goto unmatch;		
	}
	
	return 0;
	
unmatch:
	return -1;
}


int rtk_filter_ip(filter_rule_p exist_list_entry, struct sk_buff *skb)
{
	struct iphdr *iph;
	unsigned int saddr, eaddr, addr, mask;

	iph=ip_hdr(skb);

	DEBUG_PRINT("exist_list_entry->nf_flag.ip_filter is %x\n", exist_list_entry->nf_flag.ip_filter);
	
	if(exist_list_entry->nf_flag.ip_filter & 0x1) //source IP
	{
		addr = exist_list_entry->nf_src_filter->nf_ip.ip_mask.addr.s_addr;
		mask = exist_list_entry->nf_src_filter->nf_ip.ip_mask.mask.s_addr;
		if((iph->saddr&mask) == (addr&mask))
			DEBUG_PRINT("===src ip matched\n");
		else
			return -1;
	}

	if(exist_list_entry->nf_flag.ip_filter & 0x2) //source IP range
	{
		saddr = exist_list_entry->nf_src_filter->nf_ip.ip_range.saddr.s_addr;
		eaddr = exist_list_entry->nf_src_filter->nf_ip.ip_range.eaddr.s_addr;
		if((iph->saddr >= saddr) && (iph->saddr <= eaddr) )
		{
			DEBUG_PRINT("===src ip range matched\n");
		}
		else
			return -1;
	}

	if(exist_list_entry->nf_flag.ip_filter & 0x4) //destination IP
	{
		addr = exist_list_entry->nf_dst_filter->nf_ip.ip_mask.addr.s_addr;
		mask = exist_list_entry->nf_dst_filter->nf_ip.ip_mask.mask.s_addr;
		if((iph->daddr&mask) == (addr&mask))
			DEBUG_PRINT("===dst ip matched\n");
		else
			return -1;
	}

	if(exist_list_entry->nf_flag.ip_filter & 0x8) //source IP range
	{
		saddr = exist_list_entry->nf_dst_filter->nf_ip.ip_range.saddr.s_addr;
		eaddr = exist_list_entry->nf_dst_filter->nf_ip.ip_range.eaddr.s_addr;
		if((iph->daddr >= saddr) && (iph->daddr <= eaddr) )
		{
			DEBUG_PRINT("===dst ip matched\n");
		}
		else
			return -1;
	}

	DEBUG_PRINT("===IP filter matched\n");
	return 0;
}


int rtk_filter_port(filter_rule_p exist_list_entry, struct sk_buff *skb)
{
	struct iphdr *iph;
	unsigned int ssport, seport, dsport, deport;	
	unsigned int sPort, dPort;
	struct tcphdr *tcphupuh;
	
	iph = ip_hdr(skb);
	tcphupuh = (struct tcphdr*)((__u32 *)iph + iph->ihl);
	sPort = tcphupuh->source;
	dPort = tcphupuh->dest;	

	if(exist_list_entry->nf_flag.port_filter & 0x01)
	{
		ssport = exist_list_entry->nf_src_filter->nf_port.sport;
		if(sPort != ssport)
			return -1;
	}

	if(exist_list_entry->nf_flag.port_filter & 0x02)
	{
		ssport = exist_list_entry->nf_src_filter->nf_port.sport;
		seport = exist_list_entry->nf_src_filter->nf_port.eport;
		if( sPort<ssport|| sPort>seport)
			return -1;
	}

	if(exist_list_entry->nf_flag.port_filter & 0x04)
	{
		dsport = exist_list_entry->nf_dst_filter->nf_port.sport;
		if(dPort != dsport)
			return -1;
	}

	if(exist_list_entry->nf_flag.port_filter & 0x08)
	{
		dsport = exist_list_entry->nf_dst_filter->nf_port.sport;
		deport = exist_list_entry->nf_dst_filter->nf_port.eport;
		if(dPort<dsport || dPort>deport)
			return -1;
	}

	DEBUG_PRINT("===port matched\n");
	return 0;
}


int rtk_filter_phyport(filter_rule_p exist_list_entry, struct sk_buff *skb)
{
	unsigned char srcPhyPort, dstPhyPort;
	
	srcPhyPort = exist_list_entry->nf_flag.src_phy_port_filter;
	
	DEBUG_PRINT("srcPhyPort is %d, skb->srcPhyPort is %d\n", srcPhyPort, skb->srcPhyPort);
	if( (srcPhyPort & 1<<7) && (srcPhyPort& (1<<(skb->srcPhyPort)))  )
	{
		DEBUG_PRINT("source phy port filter matched\n");
	}
	else
		return -1;

	DEBUG_PRINT("phy port filter matched\n");
	return 0;
}


int rtk_filter_protocol(filter_rule_p exist_list_entry, struct sk_buff *skb)
{
	struct iphdr *iph;
	int protocol;

	iph = ip_hdr(skb);
	protocol = iph->protocol;

	if(exist_list_entry->nf_flag.protocol_filter & 0x1) //tcp filter
	{
		if(protocol == 6)
		{
			DEBUG_PRINT("protocol filter matched\n");
			return 0;
		}
	}
	if(exist_list_entry->nf_flag.protocol_filter & 0x2)
	{
		if(protocol == 17)
		{
			DEBUG_PRINT("protocol filter matched\n");
			return 0;
		}
	}

	return -1;
}

int rtk_filter_url(filter_rule_p exist_list_entry, struct sk_buff *skb)
{
	struct iphdr *iph;
 	struct tcphdr *tcph;
	unsigned char *data, *data1;
	int found=0, offset,hostlen,pathlen;
	int datalen,i;
	char *str;
 	int ret;

	iph=ip_hdr(skb);
	if(iph->protocol == IPPROTO_TCP)
		tcph = (struct tcphdr *)((void *)iph + iph->ihl*4);
	else
		return -1;

	str = kmalloc(sizeof(char) * 1518, GFP_KERNEL);
	if(str == NULL)
		return -1;
	memset(str, 0, 1518);

	data = (void *)tcph + (tcph->doff)*4;	
	datalen= ntohs(iph->tot_len) -(iph->ihl*8);
	data1 = exist_list_entry->nf_url->url_key;
	if(memcmp(data, "GET ",sizeof("GET ") -1)!=0)
	{
		kfree(str);
		return -1;
	}
	
	found = find_pattern(data,datalen,"Host: ",sizeof("Host: ")-1,'\r',&offset, &hostlen);
	if(!found)
	{
		kfree(str);
		return -1;
	}
	
	strncpy(str,data+offset,hostlen);
	*(str+hostlen)=0;
	found = find_pattern(data,datalen,"GET ",sizeof("GET ")-1,'\r',&offset, &pathlen);
    if (!found || (pathlen -= (sizeof(" HTTP/x.x") - 1)) <= 0)
    {
    	kfree(str);
		return -1;	
    }
	
	
	strncpy(str+hostlen,data+offset,pathlen);
	*(str+hostlen+pathlen)='\0';
	//DEBUG_PRINT("data1=%s, str=%s\n",data1,str);
	ret=find_url_key(str, strlen(str), data1, strlen(data1), '\0');	

	//sprintf(log_info,"%s",str);

	if(str)
		kfree(str);

	DEBUG_PRINT("the return value from find_url_key is %d\n", ret);
	
	return ret?0:-1;

}

int fast_filter(struct sk_buff *skb)
{
	filter_rule_p exist_list_entry;
	int  i;
	struct list_head *lh;
	int ret;
	int matched;

	ret=-1;
	
	list_for_each(lh, &rtk_filter_list_head)
	{
		matched = 0;
		exist_list_entry = list_entry(lh, filter_rule_s, list);
		if(exist_list_entry->nf_flag.schedule_filter != 0)
		{
			ret = rtk_filter_schedule(exist_list_entry, skb);
			if(ret != 0)
				continue;
			else
				matched = 1;
		}
		if(exist_list_entry->nf_flag.mac_filter != 0)
		{
			ret = rtk_filter_mac(exist_list_entry, skb);
			if(ret != 0)
			{
				continue;
			}
			else
				matched = 1;
		}
		if(exist_list_entry->nf_flag.ip_filter != 0)
		{
			ret = rtk_filter_ip(exist_list_entry, skb);
			if(ret != 0)
			{
				continue;
			}
			else
				matched = 1;
		}
		if(exist_list_entry->nf_flag.port_filter != 0)
		{
			ret = rtk_filter_port(exist_list_entry, skb);
			if(ret != 0)
			{
				continue;
			}
			else
				matched = 1;
		}
		if(exist_list_entry->nf_flag.src_phy_port_filter) // || exist_list_entry->nf_flag.dst_phy_port_filter)
		{
			ret = rtk_filter_phyport(exist_list_entry, skb);
			if(ret != 0)
			{
				continue;
			}
			else
				matched = 1;
		}
		if(exist_list_entry->nf_flag.protocol_filter != 0)
		{
			ret = rtk_filter_protocol(exist_list_entry, skb);
			if(ret != 0)
			{
				continue;
			}
			else
				matched = 1;
		}
		if(exist_list_entry->nf_flag.url_filter != 0)
		{
			ret = rtk_filter_url(exist_list_entry, skb);
			if(ret != 0)
			{
				continue;
			}
			else
				matched = 1;
		}

		if(matched == 1)
		{
			if (exist_list_entry->nf_flag.action==NF_MARK)
			{
				skb->mark = exist_list_entry->nf_flag.mark;
			}
			ret = exist_list_entry->nf_flag.action;
			DEBUG_PRINT("this packet match a filter rule, the filter action is %d\n", ret);
			return ret;
		}
	}

	return NF_FASTPATH;	
}



#endif


