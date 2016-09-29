/*
 * Copyright 2006, Realtek Semiconductor Corp.
 *
 * arch/rlx/rlxocp/prom.c
 *   Early initialization code for the RTL819xD
 *
 * Tony Wu (tonywu@realtek.com.tw)
 * Nov. 7, 2006
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <asm/bootinfo.h>
#include <asm/addrspace.h>
#include <asm/page.h>
#include <asm/cpu.h>

//#include <asm/rlxbsp.h>

#include "bspcpu.h"

#if defined(CONFIG_RTL_819X)
#include "bspchip.h"
#endif
#ifndef BSP_MC_MTCR0 
#define BSP_MC_MTCR0        0xB8001004
#endif
extern char arcs_cmdline[];

#ifdef CONFIG_EARLY_PRINTK
static int promcons_output __initdata = 0;
                                                                                                    
void unregister_prom_console(void)
{
    if (promcons_output) {
        promcons_output = 0;
    }
}
                                                                                                    
void disable_early_printk(void)
    __attribute__ ((alias("unregister_prom_console")));
#endif
                                                                                                    

const char *get_system_type(void)
{
    return "RTL8881a";
}

static __init void rtl819xd_init_cmdline(int argc, char **argv)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		strlcat(arcs_cmdline, " ", sizeof(arcs_cmdline));
		strlcat(arcs_cmdline, argv[i], sizeof(arcs_cmdline));
	}
}

/* Do basic initialization */
void __init bsp_init(void)
{
    u_long mem_size;

    /*user CMLLINE created by menuconfig*/
    /*
    arcs_cmdline[0] = '\0';
    strcpy(arcs_cmdline, "console=ttyS0,38400");
    */

	rtl819xd_init_cmdline(fw_arg0, (char **)fw_arg1);

#if 1 //8881A
        {
                unsigned int DCRvalue = 0;
                unsigned int bus_width = 0, chip_sel = 0, row_cnt = 0, col_cnt = 0,bank_cnt = 0;
 
                //DCRvalue = ( (*(volatile unsigned int *)BSP_MC_MTCR0));

		#define REG32(reg)	(*(volatile unsigned int *)(reg))
		#define DCR_REG 		0xb8001004
		#define EDTCR_REG 	0xb800100c
		
		DCRvalue=REG32(DCR_REG);	
 
 	#define GET_BITVAL(v,bitpos,pat) ((v& ((unsigned int)pat<<bitpos))>>bitpos)
	#define RANG1 1
	#define RANG2 3
	#define RANG3  7
	#define RANG4 0xf	
	
		unsigned int EDTCR_val=REG32(EDTCR_REG);
               
                switch( (GET_BITVAL(EDTCR_val, 30, RANG2)<<1) | GET_BITVAL(DCRvalue, 17, RANG1) )
                {  /*  
                         000: 2 bank
                         001: 4 bank
                         011: 8 bank
                     */	
                        case 0:       bank_cnt = 2;                   break;
                        case 1:       bank_cnt = 4;                   break;
			   case 3: 	 bank_cnt = 8; 		     break;
                        default:      bank_cnt = 0;                   break;
                }
 
 
                switch(GET_BITVAL(DCRvalue, 20, RANG3))
                {
                        case 0:          col_cnt = 256;               break;
                        case 1:          col_cnt = 512;                break;
                        case 2:          col_cnt = 1024;              break;
                        case 3:         col_cnt = 2048;               break;
                        case 4:         col_cnt = 4096;               break;
                        default:        printk("unknow colomn \n");     break;
                }
 
    
                switch(GET_BITVAL(DCRvalue, 23, RANG2))
                {
                        case 0:          row_cnt = 2048;         break;
                        case 1:          row_cnt = 4096;         break;
                        case 2:          row_cnt = 8192;         break;
                        case 3:          row_cnt = 16384;        break;
			default:		printk("unknow row count\n");break;
                }
 
           
                switch(GET_BITVAL(DCRvalue, 25, RANG1))
                {
                        case 0:         chip_sel = 1;              break;
                        case 1:         chip_sel = 2;               break;
			default:			printk("unknow chip select count\n");	break;
                }
 
           
                switch(GET_BITVAL(DCRvalue, 26, RANG2))
                {
                        case 0:                 bus_width = 1;                     break;
                        case 1:                 bus_width = 2;                    break;
                        case 2:                 bus_width = 3;                     break;
                        default:               printk("bus width is reseved!\n");                break;
                }
 		
                /*total size(Byte)*/
		mem_size = (row_cnt * col_cnt *bank_cnt) * (bus_width) * chip_sel;     
        }


#endif
    if(mem_size == (256 << 20))
    {
                mem_size =(256 << 20) -32;
    }
	
    add_memory_region(0, mem_size, BOOT_MEM_RAM);
}

void __init bsp_free_prom_memory(void)
{
  return;
}
