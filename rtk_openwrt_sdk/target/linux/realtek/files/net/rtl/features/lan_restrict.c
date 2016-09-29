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
#include <net/rtl/features/lan_restrict.h>

#include <linux/version.h>


#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#include <linux/ctype.h>
#endif

static char				lan_restrict_flag[1024];
int8					enable_lanrestrict = FALSE;
static struct proc_dir_entry *res=NULL;
#define RTL_LAN_RESTRICT_STAT2	2
#define RTL_LAN_RESTRICT_STAT1	1
#define RTL_LAN_RESTRICT_STAT0	0


static inline int _strncasecmp(const char *s1, const char *s2, unsigned int n)
{
     if (n == 0)
         return 0;
 
     while ((n-- != 0)
            && (tolower(*(unsigned char *) s1) ==
                tolower(*(unsigned char *) s2))) {
         if (n == 0 || *s1 == '\0' || *s2 == '\0')
             return 0;
         s1++;
         s2++;
     }
 
     return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}

int	lan_restrict_rcv(struct sk_buff *skb, struct net_device *dev)
{
	int32 found = FAILED;
	ether_addr_t *macAddr;
//	int8 port_num;
	int32 column;
	int32 SrcBlk;

	if ((memcmp(skb->dev->name, RTL_PS_BR0_DEV_NAME, 3) ==0) || (memcmp(skb->dev->name, RTL_PS_LAN_P0_DEV_NAME, 4) ==0) )
	{
		macAddr = (ether_addr_t *)(eth_hdr(skb)->h_source);
		found = rtl_check_fdb_entry_check_exist(RTL_LAN_FID, macAddr, FDB_DYNAMIC);
/*		printk("\nrecv packet from dev:%s\n", skb->dev->name);*/
		/*can found in asic , do noting here , in linux fdb module , it can be authed*/
		if (found == SUCCESS )
		{
#if 0		
			port_num = rtl865x_ConvertPortMasktoPortNum(fdbEntry.memberPortMask);
			
			if (lan_restrict_tbl[port_num].enable == TRUE)
			{
				if ((lan_restrict_tbl[port_num].curr_num < lan_restrict_tbl[port_num].max_num))
				{
/*					printk("\nPASS:lan_restrict_tbl[%d] current number is %d\n", port_num, lan_restrict_tbl[port_num].curr_num);*/
					return NET_RX_SUCCESS;
				}
				else
				{					
					if (fdbEntry.auth == TRUE)
					{
/*						printk("\nPASS1:lan_restrict_tbl[%d] current number is %d\n", port_num, lan_restrict_tbl[port_num].curr_num);*/
						return NET_RX_SUCCESS;
					}
					else
					{
/*						printk("\nDROP:lan_restrict_tbl[%d] current number is %d\n", port_num, lan_restrict_tbl[port_num].curr_num);*/
						l2temp_entry.l2type = (fdbEntry.nhFlag==0)?RTL865x_L2_TYPEI: RTL865x_L2_TYPEII;
						l2temp_entry.process = FDB_TYPE_FWD;
						l2temp_entry.memberPortMask = fdbEntry.memberPortMask;
						l2temp_entry.auth = FALSE;
						l2temp_entry.SrcBlk = TRUE;
						memcpy(&(l2temp_entry.macAddr), macAddr, sizeof(ether_addr_t));
						rtl865x_addAuthFilterDatabaseEntryExtension(fdbEntry.fid, &l2temp_entry);
						return NET_RX_AUTH_BLOCK;
					}
				}
			}
			else
			{
				return NET_RX_SUCCESS;				
			}			
#endif		
			return NET_RX_SUCCESS;		
		}
		else
		{
/*			printk(" \nnot found in hw table, src port is %d\n", skb->srcPort);*/
			if (lan_restrict_tbl[skb->srcPort].enable == TRUE)
			{
				/*found in sw l2 table*/
				if(rtl_check_fdb_entry_check_srcBlock(0, macAddr, &SrcBlk) == SUCCESS)
				{
					if (SrcBlk == TRUE)/*sw block*/
					{
						return NET_RX_AUTH_BLOCK;
					}
					else
					{
						return NET_RX_SUCCESS;
					}
				}
				else	/*not found in sw l2 table*/
				{
/*					printk(" \nnot found ind hw and sw table\n");*/
					if ((lan_restrict_tbl[skb->srcPort].curr_num < lan_restrict_tbl[skb->srcPort].max_num))
					{
						/*try to add into sw l2 table*/
/*						printk("\ntry to add into sw l2 table\n");*/
						rtl865x_addAuthFDBEntry((unsigned char *)macAddr, TRUE, skb->srcPort,FALSE);
						return NET_RX_SUCCESS;
					}
					else
					{
						return NET_RX_AUTH_BLOCK;
					}
				}

			}
			else
			{
/*				printk("dev name is %s\n", skb->dev->name);*/
				return NET_RX_SUCCESS;
			}
		}
	}
	else
	{
		return NET_RX_SUCCESS;
	}
}
#if 0
static struct packet_type lan_restrict_packet_type = {
	.type =	__constant_htons(ETH_P_ALL),
	.func =	lan_restrict_rcv,
};
#endif
static int  lan_restrict_tbl_int(void)
{
	uint8 i;

	for (i=0; i < LAN_RESTRICT_PORT_NUMBER; i++  )
	{
		lan_restrict_tbl[i].port_num	=	i;
		lan_restrict_tbl[i].enable		=	FALSE;
		lan_restrict_tbl[i].max_num	=	0;
		lan_restrict_tbl[i].curr_num	= 	0;
	}
	return TRUE;
}

static int  lan_restrict_tbl_reset(void)
{
	uint8 i;

	for (i=0; i < LAN_RESTRICT_PORT_NUMBER; i++  )
	{
		lan_restrict_tbl[i].port_num	=	i;
		lan_restrict_tbl[i].enable		=	FALSE;
		lan_restrict_tbl[i].max_num	=	0;
		lan_restrict_tbl[i].curr_num	= 	0;
	}
	return TRUE;
}


static int  lan_restrict_set_singleport(uint8 portnum , int8 enable, int32 max_num)
{
	int32 ret;
	if (enable == TRUE)
	{
		lan_restrict_tbl[portnum].max_num = max_num;
	}
	else
	{
		lan_restrict_tbl[portnum].max_num = 0;		
	}
	
	ret =rtl865x_setRestrictPortNum(portnum, enable, max_num);
	return ret;
}

static int  lan_restrict_perport_setting(void)
{
	int i;
	for (i=0; i < LAN_RESTRICT_PORT_NUMBER; i++  )
	{
		lan_restrict_set_singleport(lan_restrict_tbl[i].port_num, lan_restrict_tbl[i].enable, lan_restrict_tbl[i].max_num);
	}
	return TRUE;
}

static int lan_restrict_enable(void)
{
	/*
		enable
	*/
	rtl865x_enableLanPortNumRestrict(TRUE);
	lan_restrict_perport_setting();
	return TRUE;
}

static int lan_restrict_disable(void)
{
	/*
		disable
	*/
	rtl865x_enableLanPortNumRestrict(FALSE);	
	lan_restrict_tbl_reset();
	lan_restrict_perport_setting();
	return TRUE;
}
/*
int32 lanrestrict_addfdbentry(const unsigned char *addr)
{
	int32 found = FAILED;
	ether_addr_t *macAddr;
	int32 ret=FAILED;
	int8 port_num;
	int32 column;
	rtl865x_tblAsicDrv_l2Param_t	fdbEntry;
	rtl865x_filterDbTableEntry_t		l2temp_entry;

	macAddr = (ether_addr_t *)(addr);
	found = rtl865x_Lookup_fdb_entry(0, macAddr, FDB_DYNAMIC, &column, &fdbEntry);
	if (found == SUCCESS )
	{
		port_num = rtl865x_ConvertPortMasktoPortNum(fdbEntry.memberPortMask);
		
		if (rtl865x_lookup_FilterDatabaseEntry(fdbEntry.fid, macAddr) != SUCCESS)
		{
			l2temp_entry.l2type = (fdbEntry.nhFlag==0)?RTL865x_L2_TYPEI: RTL865x_L2_TYPEII;
			l2temp_entry.process = FDB_TYPE_FWD;
			l2temp_entry.memberPortMask = fdbEntry.memberPortMask;
			l2temp_entry.auth = TRUE;
			l2temp_entry.SrcBlk = FALSE;
			memcpy(&(l2temp_entry.macAddr), macAddr, sizeof(ether_addr_t));
			ret =rtl865x_addAuthFilterDatabaseEntryExtension(fdbEntry.fid, &l2temp_entry);						
		}	
	}
	return ret;
}
*/

int32 lan_restrict_getBlockAddr(int32 port , const unsigned char *swap_addr)
{
	int32 ret = FAILED;

	if 	(lan_restrict_tbl[port].enable == TRUE) 
	{
		ret = rtl865x_check_authfdbentry_Byport(port , swap_addr);
	}

	return ret;
}

int32 lan_restrict_CheckStatusByport(int32 port)
{
	if 	(lan_restrict_tbl[port].enable == TRUE) 
	{
		if (lan_restrict_tbl[port].curr_num < lan_restrict_tbl[port].max_num)
		{
			return RTL_LAN_RESTRICT_STAT2;
		}
		else
		{
			return RTL_LAN_RESTRICT_STAT1;
		}
	}
	else
	{
		return RTL_LAN_RESTRICT_STAT0;
	}
}
static int lan_restrict_write_proc(struct file *file, const char *buffer,
		      unsigned long count, void *data)
{
	char tmpbuf[1024];
	char *entryPtr, *portnumPtr, *enablePtr, *maxnumPtr, *strptr=tmpbuf;
	int8 port, port_enable, maxnum;

	if (count < 2)
		return -EFAULT;
	/*
	format:  entry1;entry2;entry3
	entry format: port_num enable max_num curr_num;
	port_num: 	0,1,2...
	enable:		on/off
	max_num:	0,1,2...
	curr_num:	0,1,2..., can not write, can only read from proc file and write again, just for display
	*/

	memset(lan_restrict_flag,0,strlen(lan_restrict_flag));
	if (buffer && !copy_from_user(tmpbuf, buffer, count))
 	{
 		if(memcmp(strptr,"enable", strlen("enable")) == 0)
		{
			lan_restrict_enable();
			enable_lanrestrict = TRUE;	
			lanrestrict_unRegister_event();
			lanrestrict_register_event();

			printk("enable lan restrict FUNC.....\n");			
		}
		else if(memcmp(strptr,"disable", strlen("disable")) == 0)
		{
			lan_restrict_disable();
			enable_lanrestrict = FALSE;
			printk("disable lan restrict FUNC.....\n");		
		}
		else
		{
			if (enable_lanrestrict == FALSE)
				return count;

				/*
				format:  entry1;entry2;entry3
				entry format: port_num enable max_num curr_num;
				port_num: 	0,1,2...
				enable:		on/off
				max_num:	0,1,2...
				curr_num:	0,1,2..., can not write, can only read from proc file and write again, just for display
				*/
				entryPtr = strsep(&strptr,";");
				while (entryPtr != NULL)
		      		{
					/*1. port_num*/
					portnumPtr = strsep(&entryPtr," ");
					if(portnumPtr == NULL)
					{
						printk("lan restrict setting format error1\n");
						break;
					}	
			      		port = simple_strtol(portnumPtr,NULL,0);	
					printk("set port num is %d\n", port);	

					/*2. enable or not*/	
			      		enablePtr = strsep(&entryPtr," ");			
					if(enablePtr == NULL)
					{
						printk("lan restrict setting format error2\n");
						break;
					}
					if(_strncasecmp(enablePtr,"OFF",3) == 0)
					{
						port_enable = FALSE;
					}
					else if (_strncasecmp(enablePtr,"ON",2) == 0)
					{
						port_enable = TRUE;
					}
					else
					{
						printk("lan restrict setting format error3\n");						
						break;
					}
					printk("port_enable is %d\n", port_enable);

					/*3max num*/
					maxnumPtr = strsep(&entryPtr," ");
					if(maxnumPtr == NULL)
					{
						printk("lan restrict setting format error4\n");
						break;
					}
			      		maxnum = simple_strtol(maxnumPtr,NULL,0);	
					printk("set max num is %d\n", maxnum);						
					
					lan_restrict_tbl[port].enable = 	port_enable;
					lan_restrict_tbl[port].max_num = maxnum;
					/*
						set Asic
					*/
					lan_restrict_set_singleport(port, port_enable, maxnum);
				}
		}
	}

	return count;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
#include <linux/seq_file.h>
extern struct proc_dir_entry proc_root;

static int lan_restrict_read_proc(struct seq_file *s, void *v)
{
	int i ;
	seq_printf(s, "%s\n", "lan restrict table:");

	for (i = 0; i < LAN_RESTRICT_PORT_NUMBER; i++)
	{
		seq_printf(s, "  PORT[%d]      ", i);
		seq_printf(s,"%6s %6d %6d  ",lan_restrict_tbl[i].enable?"ON":"OFF", lan_restrict_tbl[i].max_num,  lan_restrict_tbl[i].curr_num);
		seq_printf(s,"\n");
	}

	return 0;
}

int lan_restrict_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, lan_restrict_read_proc, NULL));
}

static ssize_t lan_restrict_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return lan_restrict_write_proc(file, userbuf,count, off);
}

struct file_operations lan_restrict_proc_fops = {
        .open           = lan_restrict_single_open,
	 .write		= lan_restrict_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};

#else
static int lan_restrict_read_proc(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
	int len, i ;
	len = sprintf(page, "%s\n", "lan restrict table:");
	if (len <= off+count) 
		*eof = 1;

	for (i = 0; i < LAN_RESTRICT_PORT_NUMBER; i++)
	{
		len += sprintf(page + len, "  PORT[%d]      ", i);
		len += sprintf(page + len,"%6s %6d %6d  ",lan_restrict_tbl[i].enable?"ON":"OFF", lan_restrict_tbl[i].max_num,  lan_restrict_tbl[i].curr_num);
		len += sprintf(page + len,"\n");
	}

	return len;
}
#endif

static int lan_restrict_proc_init(void)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	res = proc_create_data("lan_restrict_info", 0, &proc_root,
			 &lan_restrict_proc_fops, NULL);
	if (res)
		return TRUE;
#else		
	res = create_proc_entry("lan_restrict_info",0,NULL);
	if(res)
	{
		res->read_proc = lan_restrict_read_proc;
		res->write_proc = lan_restrict_write_proc;
		return TRUE;
	}
#endif
	return FALSE;
	
}
	
int __init lan_restrict_init(void)
{
	lan_restrict_tbl_int();
//	dev_add_pack(&lan_restrict_packet_type);
	lan_restrict_proc_init();
	
	return 0;
}


