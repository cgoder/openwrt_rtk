/*
 * Realtek Semiconductor Corp.
 *
 * bsp/bspchip.h:
 *   bsp chip address and IRQ mapping file
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */

#ifndef _BSPCHIP_H_
#define _BSPCHIP_H_

#define BSP_HZ 100

#ifndef CONFIG_WRT_BARRIER_BREAKER
#include <linux/autoconf.h>
#else 
#include <generated/autoconf.h>
#endif
/*
 * Register access macro
 */
#define REG32(reg)	(*(volatile unsigned int   *)((unsigned int)reg))
#define REG16(reg)	(*(volatile unsigned short *)((unsigned int)reg))
#define REG08(reg)	(*(volatile unsigned char  *)((unsigned int)reg))
#define REG8(reg)   (*(volatile unsigned char  *)((unsigned int)reg))

#define WRITE_MEM32(addr, val)   (*(volatile unsigned int *)   (addr)) = (val)
#define READ_MEM32(addr)         (*(volatile unsigned int *)   (addr))
#define WRITE_MEM16(addr, val)   (*(volatile unsigned short *) (addr)) = (val)
#define READ_MEM16(addr)         (*(volatile unsigned short *) (addr))
#define WRITE_MEM8(addr, val)    (*(volatile unsigned char *)  (addr)) = (val)
#define READ_MEM8(addr)          (*(volatile unsigned char *)  (addr))

#define PADDR(addr)  ((addr) & 0x1FFFFFFF)

/*
 * IRQ Controller
 */
#define BSP_IRQ_CPU_BASE   0
#define BSP_IRQ_CPU_NUM    8

#define BSP_IRQ_LOPI_BASE   (BSP_IRQ_CPU_BASE + BSP_IRQ_CPU_NUM)
#define BSP_IRQ_LOPI_NUM   8

#define BSP_IRQ_ICTL_BASE  (BSP_IRQ_LOPI_BASE + BSP_IRQ_LOPI_NUM)
#define BSP_IRQ_ICTL_NUM   32

/*
 *  ====================================
 *  Platform Configurable Common Options
 *  ====================================
 */

#define PROM_DEBUG      0

#ifdef CONFIG_FPGA_PLATFORM
//#define BSP_SYS_CLK_RATE	  	(33860000)      //33.86MHz
#define BSP_SYS_CLK_RATE	  	(27000000)      //27MHz
#else
#define BSP_SYS_CLK_RATE	  	(200000000)     //HS1 clock : 200 MHz
#endif

#define BSP_BAUDRATE        38400  /* ex. 19200 or 38400 or 57600 or 115200 */ 
                               /* For Early Debug */

/*-------------------------------------------------------------------------*/
/*
 * Interrupt Controller
 */
#define BSP_GIMR            0xB8003000
   #define BSP_CPU_WAKEUP_IE   (1 << 27)
   #define BSP_I2S_IE          (1 << 26)
   #define BSP_GDMA_IE         (1 << 23)
   #define BSP_PCIE2_IE        (1 << 22)
   #define BSP_PCIE_IE         (1 << 21)
   #define BSP_SECURITY_IE     (1 << 20)
   #define BSP_PCM_IE          (1 << 19)
   #define BSP_NFBI_IE         (1 << 18)
   #define BSP_GPIO_EFGH_IE    (1 << 17)
   #define BSP_GPIO_ABCD_IE    (1 << 16)
   #define BSP_SW_IE           (1 << 15)
   #define BSP_UART1_IE        (1 << 13)
   #define BSP_UART0_IE        (1 << 12)
   #define BSP_OTG_IE          (1 << 11)
   #define BSP_USB_H_IE        (1 << 10)
   #define BSP_TC1_IE          (1 << 9)
   #define BSP_TC0_IE          (1 << 8)

#define BSP_GISR            0xB8003004
   #define BSP_CPU_WAKEUP_IP   (1 << 27)
   #define BSP_I2S_IP          (1 << 26)
   #define BSP_GDMA_IP         (1 << 23)
   #define BSP_PCIE2_IP        (1 << 22)
   #define BSP_PCIE_IP         (1 << 21)
   #define BSP_SECURITY_IP     (1 << 20)
   #define BSP_PCM_IP          (1 << 19)
   #define BSP_NFBI_IP         (1 << 18)
   #define BSP_GPIO_EFGH_IP    (1 << 17)
   #define BSP_GPIO_ABCD_IP    (1 << 16)
   #define BSP_SW_IP           (1 << 15)
   #define BSP_UART1_IP        (1 << 13)
   #define BSP_UART0_IP        (1 << 12)
   #define BSP_OTG_IP          (1 << 11)
   #define BSP_USB_H_IP        (1 << 10)
   #define BSP_TC1_IP          (1 << 9)
   #define BSP_TC0_IP          (1 << 8)

/*
 *   RTL8196b Interrupt Scheme (Subject to change)
 *                       (CPU:2~7,LOPI:8~15)
 *   Source       bit#         RS              IRQ      
 *   --------   -------  -------------------  ------   
 *   TC1	     9          8             16+9
 *   TC0	     8         15              15
 *   UART0          12          9               9
 *   UART1          13          8             16+13
 *   SW		    15          12             12
 *   GPIO_ABCD      16          8             16+16
 *   GPIO_EFGH      17          8             16+17
 *   NFBI           18          8             16+18
 *   PCM            19          8             16+19
 *   SECURITY       20          9             16+20
 *   PCIE0	    21         14              14
 *   PCIE1          22         13              13
 *   GDMA	    23          8             16+23
 *   I2S	    26	        8      	      16+26
 *   CPU_WAKEUP	    27          8             16+27
 */                               
/*                        
 * IRQ Mapping
 */
#define BSP_IRQ_ICTL_MASK       (~(BSP_TC0_IE|BSP_PCIE_IE|BSP_SW_IE|BSP_UART0_IE))
#define BSP_ICTL_IRQ		(8) //BSP_IRQ_LOPI_BASE+0 //LOPI0 for irq cascade

#define BSP_TC0_IRQ             (11)	/* 15->11 BSP_IRQ_LOPI_BASE + 7	*/
#define BSP_TC1_IRQ             (BSP_IRQ_ICTL_BASE + 9)
#define BSP_USB_IRQ             (10)	/* BSP_IRQ_LOPI_BASE + 2	*/
#define BSP_OTG_IRQ             (15)  //11->15 (BSP_IRQ_LOPI_BASE + 7)   //wei add ,bit 15=8+7
#define BSP_UART0_IRQ           (9)	/* BSP_IRQ_LOPI_BASE + 1	*/
#define BSP_UART1_IRQ           (BSP_IRQ_ICTL_BASE + 13)
#define BSP_SWCORE_IRQ          (12)	/* BSP_IRQ_LOPI_BASE + 4	*/
#define BSP_GPIO_ABCD_IRQ       (BSP_IRQ_ICTL_BASE + 16)
#define BSP_GPIO_EFGH_IRQ       (BSP_IRQ_ICTL_BASE + 17)
#define BSP_NFBI_IRQ            (BSP_IRQ_ICTL_BASE + 18)
#define BSP_PCM_IRQ             (BSP_IRQ_ICTL_BASE + 19)
#define BSP_SECURITY_IRQ        (BSP_IRQ_ICTL_BASE + 20)
#define BSP_GDMA_IRQ            (BSP_IRQ_ICTL_BASE + 23)
#define BSP_PCIE_IRQ            (14)	/* BSP_IRQ_LOPI_BASE + 6	*/
#define BSP_PCIE2_IRQ           (13)	/* BSP_IRQ_LOPI_BASE + 5	*/

/*
 * Interrupt Routing Selection
 */
#define BSP_IRQ_ZER0		0
#define BSP_IRQ_CASCADE		BSP_ICTL_IRQ
#define BSP_NONE_RS		0

#define BSP_CPU_WAKEUP_RS	BSP_IRQ_ZER0
#define BSP_PCIE_RS		BSP_PCIE_IRQ
#define BSP_PCIE2_RS		BSP_PCIE2_IRQ
#define BSP_GDMA_RS		BSP_IRQ_ZER0
#define BSP_SECURITY_RS		BSP_IRQ_ZER0
#define BSP_PCM_RS		BSP_IRQ_ZER0
#define BSP_NFBI_RS		BSP_IRQ_ZER0
#define BSP_GPIO_EFGH_RS	BSP_IRQ_ZER0
#define BSP_GPIO_ABCD_RS	BSP_IRQ_ZER0
#define BSP_SW_RS		BSP_SWCORE_IRQ
#define BSP_UART0_RS		BSP_UART0_IRQ
#define BSP_UART1_RS		BSP_IRQ_ZER0
#define BSP_USB_H_RS		BSP_USB_IRQ
#define BSP_OTG_RS		BSP_OTG_IRQ
#define BSP_TC0_RS		BSP_TC0_IRQ
#define BSP_TC1_RS		BSP_IRQ_ZER0


#define BSP_IRR0            0xB8003008
#define BSP_IRR0_SETTING    ((BSP_NONE_RS << 28) | \
                         (BSP_NONE_RS << 24) | \
                         (BSP_NONE_RS << 20) | \
                         (BSP_NONE_RS << 16) | \
                         (BSP_NONE_RS << 12) | \
                         (BSP_NONE_RS << 8)  | \
                         (BSP_NONE_RS << 4)  | \
                         (BSP_NONE_RS << 0)    \
                        )

#define BSP_IRR1            0xB800300C
#define BSP_IRR1_SETTING    ((BSP_SW_RS << 28) | \
                         (BSP_NONE_RS << 24) | \
                         (BSP_UART1_RS << 20) | \
                         (BSP_UART0_RS << 16) | \
                         (BSP_OTG_RS << 12) | \
                         (BSP_USB_H_RS << 8)  | \
                         (BSP_TC1_RS   << 4)  | \
                         (BSP_TC0_RS   << 0)    \
                        )

#define BSP_IRR2            0xB8003010
#define BSP_IRR2_SETTING    ((BSP_GDMA_RS      << 28) | \
                         (BSP_PCIE2_RS     << 24) | \
                         (BSP_PCIE_RS      << 20) | \
                         (BSP_SECURITY_RS  << 16) | \
                         (BSP_PCM_RS       << 12) | \
                         (BSP_NFBI_RS      << 8)  | \
                         (BSP_GPIO_EFGH_RS << 4)  | \
                         (BSP_GPIO_ABCD_RS << 0)    \
                        )

#define BSP_IRR3            0xB8003014
#define BSP_IRR3_SETTING    ((BSP_NONE_RS << 28) | \
                         (BSP_NONE_RS << 24) | \
                         (BSP_NONE_RS << 20) | \
                         (BSP_NONE_RS << 16) | \
                         (BSP_CPU_WAKEUP_RS << 12) | \
                         (BSP_NONE_RS << 4)  | \
                         (BSP_NONE_RS << 0)    \
                        )
/*-------------------------------------------------------------------------*/

#define BSP_DIVISOR         200

#if BSP_DIVISOR > (1 << 16)
#error "Exceed the Maximum Value of DivFactor"
#endif

/*
 *  ==========================
 *  Platform Register Settings
 *  ==========================
 */

/*
 * CPU
 */
#define BSP_IMEM_BASE       0x00C00000
#define BSP_IMEM_TOP        0x00C03FFF

#define BSP_DMEM_BASE       0x00C04000
#define BSP_DMEM_TOP        0x00C05FFF

/*
 * Memory Controller
 */
#define BSP_MC_MCR          0xB8001000
   #define BSP_MC_MCR_VAL      0x92A28000

#define BSP_MC_MTCR0        0xB8001004
   #define BSP_MC_MTCR0_VAL    0x12120000

#define BSP_MC_MTCR1        0xB8001008
   #define BSP_MC_MTCR1_VAL    0x00000FEB

#define BSP_MC_PFCR         0xB8001010
   #define BSP_MC_PFCR_VAL     0x00000101


#define BSP_MC_BASE         0xB8001000
#define BSP_NCR             (BSP_MC_BASE + 0x100)
#define BSP_NSR             (BSP_MC_BASE + 0x104)
#define BSP_NCAR            (BSP_MC_BASE + 0x108)
#define BSP_NADDR           (BSP_MC_BASE + 0x10C)
#define BSP_NDR             (BSP_MC_BASE + 0x110)

#define BSP_SFCR            (BSP_MC_BASE + 0x200)
#define BSP_SFDR            (BSP_MC_BASE + 0x204)

/*
 * UART
 */
#define BSP_UART0_BASE      0xB8002000
#define BSP_UART0_MAP_BASE  0x18002000
#define BSP_UART0_RBR       (BSP_UART0_BASE + 0x000)
#define BSP_UART0_THR       (BSP_UART0_BASE + 0x000)
#define BSP_UART0_DLL       (BSP_UART0_BASE + 0x000)
#define BSP_UART0_IER       (BSP_UART0_BASE + 0x004)
#define BSP_UART0_DLM       (BSP_UART0_BASE + 0x004)
#define BSP_UART0_IIR       (BSP_UART0_BASE + 0x008)
#define BSP_UART0_FCR       (BSP_UART0_BASE + 0x008)
#define BSP_UART0_LCR       (BSP_UART0_BASE + 0x00C)
#define BSP_UART0_MCR       (BSP_UART0_BASE + 0x010)
#define BSP_UART0_LSR       (BSP_UART0_BASE + 0x014)

#define BSP_UART1_BASE      0xB8002100
#define BSP_UART1_MAP_BASE  0x18002100
#define BSP_UART1_RBR       (BSP_UART1_BASE + 0x000)
#define BSP_UART1_THR       (BSP_UART1_BASE + 0x000)
#define BSP_UART1_DLL       (BSP_UART1_BASE + 0x000)
#define BSP_UART1_IER       (BSP_UART1_BASE + 0x004)
#define BSP_UART1_DLM       (BSP_UART1_BASE + 0x004)
#define BSP_UART1_IIR       (BSP_UART1_BASE + 0x008)
#define BSP_UART1_FCR       (BSP_UART1_BASE + 0x008)
   #define BSP_FCR_EN          0x01
   #define BSP_FCR_RXRST       0x02
   #define     BSP_RXRST             0x02
   #define BSP_FCR_TXRST       0x04
   #define     BSP_TXRST             0x04
   #define BSP_FCR_DMA         0x08
   #define BSP_FCR_RTRG        0xC0
   #define     BSP_CHAR_TRIGGER_01   0x00
   #define     BSP_CHAR_TRIGGER_04   0x40
   #define     BSP_CHAR_TRIGGER_08   0x80
   #define     BSP_CHAR_TRIGGER_14   0xC0
#define BSP_UART1_LCR       (BSP_UART1_BASE + 0x00C)
   #define BSP_LCR_WLN         0x03
   #define     BSP_CHAR_LEN_5        0x00
   #define     BSP_CHAR_LEN_6        0x01
   #define     BSP_CHAR_LEN_7        0x02
   #define     BSP_CHAR_LEN_8        0x03
   #define BSP_LCR_STB         0x04
   #define     BSP_ONE_STOP          0x00
   #define     BSP_TWO_STOP          0x04
   #define BSP_LCR_PEN         0x08
   #define     BSP_PARITY_ENABLE     0x01
   #define     BSP_PARITY_DISABLE    0x00
   #define BSP_LCR_EPS         0x30
   #define     BSP_PARITY_ODD        0x00
   #define     BSP_PARITY_EVEN       0x10
   #define     BSP_PARITY_MARK       0x20
   #define     BSP_PARITY_SPACE      0x30
   #define BSP_LCR_BRK         0x40
   #define BSP_LCR_DLAB        0x80
   #define     BSP_DLAB              0x80
#define BSP_UART1_MCR       (BSP_UART1_BASE + 0x010)
#define BSP_UART1_LSR       (BSP_UART1_BASE + 0x014)
   #define BSP_LSR_DR          0x01
   #define     BSP_RxCHAR_AVAIL      0x01
   #define BSP_LSR_OE          0x02
   #define BSP_LSR_PE          0x04
   #define BSP_LSR_FE          0x08
   #define BSP_LSR_BI          0x10
   #define BSP_LSR_THRE        0x20
   #define     BSP_TxCHAR_AVAIL      0x00
   #define     BSP_TxCHAR_EMPTY      0x20
   #define BSP_LSR_TEMT        0x40
   #define BSP_LSR_RFE         0x80

/*
 * Timer/Counter
 */
#define BSP_TC_BASE         0xB8003100
#define BSP_TC0DATA         (BSP_TC_BASE + 0x00)
#define BSP_TC1DATA         (BSP_TC_BASE + 0x04)
   #define BSP_TCD_OFFSET      4
#define BSP_TC0CNT          (BSP_TC_BASE + 0x08)
#define BSP_TC1CNT          (BSP_TC_BASE + 0x0C)
#define BSP_TCCNR           (BSP_TC_BASE + 0x10)
   #define BSP_TC0EN           (1 << 31)
   #define BSP_TC0MODE_TIMER   (1 << 30)
   #define BSP_TC1EN           (1 << 29)
   #define BSP_TC1MODE_TIMER   (1 << 28)
#define BSP_TCIR            (BSP_TC_BASE + 0x14)
   #define BSP_TC0IE           (1 << 31)
   #define BSP_TC1IE           (1 << 30)
   #define BSP_TC0IP           (1 << 29)
   #define BSP_TC1IP           (1 << 28)
#define BSP_CDBR            (BSP_TC_BASE + 0x18)
   #define BSP_DIVF_OFFSET     16
#define BSP_WDTCNR          (BSP_TC_BASE + 0x1C)

/*
 * PCIE Host Controller
 */
#define BSP_PCIE0_H_CFG     0xB8B00000
#define BSP_PCIE0_H_EXT     0xB8B01000
#define BSP_PCIE0_H_MDIO    (BSP_PCIE0_H_EXT + 0x00)
#define BSP_PCIE0_H_INTSTR  (BSP_PCIE0_H_EXT + 0x04)
#define BSP_PCIE0_H_PWRCR   (BSP_PCIE0_H_EXT + 0x08)
#define BSP_PCIE0_H_IPCFG   (BSP_PCIE0_H_EXT + 0x0C)
#define BSP_PCIE0_H_MISC    (BSP_PCIE0_H_EXT + 0x10)
#define BSP_PCIE0_D_CFG0    0xB8B10000
#define BSP_PCIE0_D_CFG1    0xB8B11000
#define BSP_PCIE0_D_MSG     0xB8B12000

#define BSP_PCIE1_H_CFG     0xB8B20000
#define BSP_PCIE1_H_EXT     0xB8B21000
#define BSP_PCIE1_H_MDIO    (BSP_PCIE1_H_EXT + 0x00)
#define BSP_PCIE1_H_INTSTR  (BSP_PCIE1_H_EXT + 0x04)
#define BSP_PCIE1_H_PWRCR   (BSP_PCIE1_H_EXT + 0x08)
#define BSP_PCIE1_H_IPCFG   (BSP_PCIE1_H_EXT + 0x0C)
#define BSP_PCIE1_H_MISC    (BSP_PCIE1_H_EXT + 0x10)
#define BSP_PCIE1_D_CFG0    0xB8B30000
#define BSP_PCIE1_D_CFG1    0xB8B31000
#define BSP_PCIE1_D_MSG     0xB8B32000

#define BSP_PCIE0_D_IO      0xB8C00000
#define BSP_PCIE1_D_IO      0xB8E00000
#define BSP_PCIE_FUN_OFS      0xC00000
#define BSP_PCIE0_D_MEM     0xB9000000
#define BSP_PCIE0_F1_D_MEM  (BSP_PCIE0_D_MEM + BSP_PCIE_FUN_OFS)
#define BSP_PCIE1_D_MEM     0xBA000000
#define BSP_PCIE1_F1_D_MEM  (BSP_PCIE1_D_MEM + BSP_PCIE_FUN_OFS)


/* GPIO Register Set */
#define BSP_GPIO_BASE	(0xB8003500)
#define BSP_PABCD_CNR	(0x000 + BSP_GPIO_BASE) /* Port ABCD control */
#define BSP_PABCD_PTYPE	(0x004 + BSP_GPIO_BASE) /* Port ABCD type */
#define BSP_PABCD_DIR	(0x008 + BSP_GPIO_BASE) /* Port ABCD direction */
#define BSP_PABCD_DAT	(0x00C + BSP_GPIO_BASE) /* Port ABCD data */
#define BSP_PABCD_ISR	(0x010 + BSP_GPIO_BASE) /* Port ABCD interrupt status */
#define BSP_PAB_IMR	(0x014 + BSP_GPIO_BASE) /* Port AB interrupt mask */
#define BSP_PCD_IMR	(0x018 + BSP_GPIO_BASE) /* Port CD interrupt mask */
#define BSP_PEFGH_CNR	(0x01C + BSP_GPIO_BASE) /* Port ABCD control */
#define BSP_PEFGHP_TYPE	(0x020 + BSP_GPIO_BASE) /* Port ABCD type */
#define BSP_PEFGH_DIR	(0x024 + BSP_GPIO_BASE) /* Port ABCD direction */
#define BSP_PEFGH_DAT	(0x028 + BSP_GPIO_BASE) /* Port ABCD data */
#define BSP_PEFGH_ISR	(0x02C + BSP_GPIO_BASE) /* Port ABCD interrupt status */
#define BSP_PEF_IMR	(0x030 + BSP_GPIO_BASE) /* Port AB interrupt mask */
#define BSP_PGH_IMR	(0x034 + BSP_GPIO_BASE) /* Port CD interrupt mask */


#define BSP_CLK_MANAGE 	0xB8000010

/*
 * Revision
 */
#define BSP_REVR		0xB8000000
#define BSP_RTL8198_REVISION_A	0xC0000000
#define BSP_RTL8198_REVISION_B	0xC0000001
#define BSP_RTL8197D		0x8197C000
#define BSP_RTL8196E		0x8196E000

/*
 * PIN MUX
 */
#define BSP_PIN_MUX_SEL1	0xB8000040
#define BSP_PIN_MUX_SEL2	0xB8000044

/*
 * GPIO PIN
 */
enum BSP_GPIO_PIN
{
	BSP_GPIO_PIN_A0 = 0,
	BSP_GPIO_PIN_A1,
	BSP_GPIO_PIN_A2,
	BSP_GPIO_PIN_A3,
	BSP_GPIO_PIN_A4,
	BSP_GPIO_PIN_A5,
	BSP_GPIO_PIN_A6,
	BSP_GPIO_PIN_A7,

	BSP_GPIO_PIN_B0,
	BSP_GPIO_PIN_B1,
	BSP_GPIO_PIN_B2,
	BSP_GPIO_PIN_B3,
	BSP_GPIO_PIN_B4,
	BSP_GPIO_PIN_B5,
	BSP_GPIO_PIN_B6,
	BSP_GPIO_PIN_B7,

	BSP_GPIO_PIN_C0,
	BSP_GPIO_PIN_C1,
	BSP_GPIO_PIN_C2,
	BSP_GPIO_PIN_C3,
	BSP_GPIO_PIN_C4,
	BSP_GPIO_PIN_C5,
	BSP_GPIO_PIN_C6,
	BSP_GPIO_PIN_C7,

	BSP_GPIO_PIN_D0,
	BSP_GPIO_PIN_D1,
	BSP_GPIO_PIN_D2,
	BSP_GPIO_PIN_D3,
	BSP_GPIO_PIN_D4,
	BSP_GPIO_PIN_D5,
	BSP_GPIO_PIN_D6,
	BSP_GPIO_PIN_D7,

	BSP_GPIO_2ND_REG, 
	BSP_GPIO_PIN_MAX = BSP_GPIO_2ND_REG
};

#define BSP_GPIO_BIT(pin)  		(pin & ~(BSP_GPIO_2ND_REG))
#define BSP_GPIO_CNR_REG(pin) 	((pin & BSP_GPIO_2ND_REG) ? BSP_PEFGH_CNR : BSP_PABCD_CNR)
#define BSP_GPIO_DIR_REG(pin) 	((pin & BSP_GPIO_2ND_REG) ? BSP_PEFGH_DIR : BSP_PABCD_DIR)
#define BSP_GPIO_DAT_REG(pin) 	((pin & BSP_GPIO_2ND_REG) ? BSP_PEFGH_DAT : BSP_PABCD_DAT)

#endif   /* _BSPCHIP_H */
