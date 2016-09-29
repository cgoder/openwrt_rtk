/*
 * Realtek Semiconductor Corp.
 *
 * bsp/pci-ops.c:
 * 	bsp PCI operation code
 */
#include <linux/types.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/delay.h>

#include <asm/pci.h>
#include <asm/io.h>

//#include "bspchip.h"
#include <asm/mach-realtek/bspchip.h>

#undef DEBUG_PCI_READ
#define DEBUG_PCI_WRITE

#define PCI_8BIT_ACCESS    1
#define PCI_16BIT_ACCESS   2
#define PCI_32BIT_ACCESS   4
#define PCI_ACCESS_READ    8
#define PCI_ACCESS_WRITE   16
#define MAX_NUM_DEV  4

static int pci0_bus_number = 0xff;
static int pci1_bus_number = 0xff;

static int rtl819x_pcibios_config_access(unsigned char access_type,
       unsigned int addr, unsigned int *data)
{
   /* Do 8bit/16bit/32bit access */
   if (access_type & PCI_ACCESS_WRITE)
   {
      if (access_type & PCI_8BIT_ACCESS)
         WRITE_MEM8(addr, *data);
      else if (access_type & PCI_16BIT_ACCESS)
         WRITE_MEM16(addr, *data);
      else
         WRITE_MEM32(addr, *data);
   }
   else if (access_type & PCI_ACCESS_READ)
   {
      if (access_type & PCI_8BIT_ACCESS) { 
      #ifdef CONFIG_RTL8198_REVISION_B  
         unsigned int data_temp=0;  int swap[4]={0,8,16,24};  int diff = addr&0x3;
        data_temp=READ_MEM32(addr);
        *data=(unsigned int)(( data_temp>>swap[diff])&0xff);

#else
         *data = READ_MEM8(addr);
#endif
       } else if (access_type & PCI_16BIT_ACCESS) { 
       #ifdef CONFIG_RTL8198_REVISION_B  
        unsigned int data_temp=0;  int swap[4]={0,8,16,24};  int diff = addr&0x3;
        data_temp=READ_MEM32(addr);
        *data=(unsigned int)(( data_temp>>swap[diff])&0xffff);

#else
         *data = READ_MEM16(addr);
#endif
      } else
         *data = READ_MEM32(addr);
   }

   /* If need to check for PCIE access timeout, put code here */
   /* ... */

   return 0;
}

static int rtl819x_pcibios0_read(struct pci_bus *bus, unsigned int devfn,
                                  int where, int size, unsigned int *val)
{
   unsigned int data = 0;
   unsigned int addr = 0;

   if (pci0_bus_number == 0xff)
      pci0_bus_number = bus->number;
   #if 0//  DEBUG_PRINTK
	//printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   printk("rtl819x_pcibios0_read Bus: %d, Slot: %d, Func: %d, Where: %d, Size: %d\n", bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size);
   #endif

   if (bus->number == pci0_bus_number)
   {
      /* PCIE host controller */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE0_H_CFG + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_READ | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;

         if (size == 1)
            *val = (data >> ((where & 3) << 3)) & 0xff;
         else if (size == 2)
            *val = (data >> ((where & 3) << 3)) & 0xffff;
         else
            *val = data;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else if (bus->number == (pci0_bus_number + 1))
   {
      /* PCIE devices directly connected */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE0_D_CFG0 + (PCI_FUNC(devfn) << 12) + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_READ | size, addr, val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else
   {
      /* Devices connected through bridge */
      if (PCI_SLOT(devfn) < MAX_NUM_DEV)
      {
         WRITE_MEM32(BSP_PCIE0_H_IPCFG, ((bus->number) << 8) | (PCI_SLOT(devfn) << 3) | PCI_FUNC(devfn));
         addr = BSP_PCIE0_D_CFG1 + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_READ | size, addr, val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   #if 0
   REG32(0xb8000014)=0x800200; //mark_pci
   #if DEBUG_PRINTK
   printk("0xb8000014:%x\n",REG32(0xb8000014));
	//printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Read Value: 0x%08X\n", *val);
   #endif
   printk("PCI_EP_READ: addr= %x, size=%d, value= %x\n", addr, size, *val);
   #endif   
   return PCIBIOS_SUCCESSFUL;
}

//========================================================================================
static int rtl819x_pcibios0_write(struct pci_bus *bus, unsigned int devfn,
                                   int where, int size, unsigned int val)
{
   unsigned int data = 0;
   unsigned int addr = 0;

   static int pci0_bus_number = 0xff;
   if (pci0_bus_number == 0xff)
      pci0_bus_number = bus->number;

   #if DEBUG_PRINTK
   //printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Bus: %d, Slot: %d, Func: %d, Where: %d, Size: %d\n", bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size);
   #endif

   if (bus->number == pci0_bus_number)
   {
      /* PCIE host controller */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE0_H_CFG + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_READ | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;

         if (size == 1)
            data = (data & ~(0xff << ((where & 3) << 3))) | (val << ((where & 3) << 3));
         else if (size == 2)
            data = (data & ~(0xffff << ((where & 3) << 3))) | (val << ((where & 3) << 3));
         else
            data = val;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_WRITE | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else if (bus->number == (pci0_bus_number + 1))
   {
      /* PCIE devices directly connected */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE0_D_CFG0 + (PCI_FUNC(devfn) << 12) + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_WRITE | size, addr, &val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else
   {
      /* Devices connected through bridge */
      if (PCI_SLOT(devfn) < MAX_NUM_DEV)
      {
         WRITE_MEM32(BSP_PCIE0_H_IPCFG, ((bus->number) << 8) | (PCI_SLOT(devfn) << 3) | PCI_FUNC(devfn));
         addr = BSP_PCIE0_D_CFG1 + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_WRITE | size, addr, &val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }

   return PCIBIOS_SUCCESSFUL;
}

static int rtl819x_pcibios1_read(struct pci_bus *bus, unsigned int devfn,
                                  int where, int size, unsigned int *val)
{
   unsigned int data = 0;
   unsigned int addr = 0;

   if (pci1_bus_number == 0xff)
      pci1_bus_number = bus->number;
   #if 0//  DEBUG_PRINTK
    //printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
	   printk("rtl819x_pcibios1_read Bus: %d, Slot: %d, Func: %d, Where: %d, Size: %d\n", bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size);
   #endif

   if (bus->number == pci1_bus_number)
   {
      /* PCIE host controller */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE1_H_CFG + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_READ | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;

         if (size == 1)
            *val = (data >> ((where & 3) << 3)) & 0xff;
         else if (size == 2)
            *val = (data >> ((where & 3) << 3)) & 0xffff;
         else
            *val = data;
      }
      else
		return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else if (bus->number == (pci1_bus_number + 1))
   {
      /* PCIE devices directly connected */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE1_D_CFG0 + (PCI_FUNC(devfn) << 12) + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_READ | size, addr, val))
            return PCIBIOS_DEVICE_NOT_FOUND;
	}
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else
   {
      /* Devices connected through bridge */
      if (PCI_SLOT(devfn) < MAX_NUM_DEV)
      {
         WRITE_MEM32(BSP_PCIE1_H_IPCFG, ((bus->number) << 8) | (PCI_SLOT(devfn) << 3) | PCI_FUNC(devfn));
         addr = BSP_PCIE1_D_CFG1 + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_READ | size, addr, val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   #if 0
   REG32(0xb8000014)=0x800200; //mark_pci
   #if DEBUG_PRINTK
   printk("0xb8000014:%x\n",REG32(0xb8000014));
	//printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Read Value: 0x%08X\n", *val);
   #endif
   printk("PCI_EP_READ: addr= %x, size=%d, value= %x\n", addr, size, *val);
#endif
	return PCIBIOS_SUCCESSFUL;
}
 
//========================================================================================
static int rtl819x_pcibios1_write(struct pci_bus *bus, unsigned int devfn,
                                   int where, int size, unsigned int val)
{
   unsigned int data = 0;
   unsigned int addr = 0;
   
   if (pci1_bus_number == 0xff)
      pci1_bus_number = bus->number;

   #if DEBUG_PRINTK
   //printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Bus: %d, Slot: %d, Func: %d, Where: %d, Size: %d\n", bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size);
   #endif

   if (bus->number == pci1_bus_number)
   {
      /* PCIE host controller */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE1_H_CFG + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_READ | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;

         if (size == 1)
            data = (data & ~(0xff << ((where & 3) << 3))) | (val << ((where & 3) << 3));
         else if (size == 2)
            data = (data & ~(0xffff << ((where & 3) << 3))) | (val << ((where & 3) << 3));
         else
            data = val;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_WRITE | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
	}
   else if (bus->number == (pci1_bus_number + 1))
   {
      /* PCIE devices directly connected */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE1_D_CFG0 + (PCI_FUNC(devfn) << 12) + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_WRITE | size, addr, &val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else
   {
      /* Devices connected through bridge */
      if (PCI_SLOT(devfn) < MAX_NUM_DEV)
      {
         WRITE_MEM32(BSP_PCIE1_H_IPCFG, ((bus->number) << 8) | (PCI_SLOT(devfn) << 3) | PCI_FUNC(devfn));
         addr = BSP_PCIE1_D_CFG1 + where;

         if (rtl819x_pcibios_config_access(PCI_ACCESS_WRITE | size, addr, &val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	return PCIBIOS_SUCCESSFUL;
}

struct pci_ops bsp_pcie_ops = {
	.read = rtl819x_pcibios0_read,
	.write = rtl819x_pcibios0_write,	
};

struct pci_ops bsp_pcie_ops1 = {
	.read = rtl819x_pcibios1_read,
	.write = rtl819x_pcibios1_write,	
};

/* Do platform specific device initialization at pci_enable_device() time */

int pcibios_plat_dev_init(struct pci_dev *dev)
{
#if 0
	unsigned int val;

	val = REG32(0xbb004000);
	if (val != 0x3)
		return 0;

	val = REG32(BSP_PCIE_EP_CFG+0x78);
	printk("INFO: Address %lx = 0x%x\n", BSP_PCIE_EP_CFG + 0x78, val);

	REG32(BSP_PCIE_EP_CFG + 0x78) = 0x105030;
	printk("INFO: Set PCIE payload to 128\n");

	val = REG32(BSP_PCIE_EP_CFG+0x78);
	printk("INFO: Address %lx = 0x%x\n",BSP_PCIE_EP_CFG + 0x78, val);
#endif
	printk("pcibios_plat_dev_init INFO: bus=%d \n", dev->bus->number);
	return 0;
}


int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	int irq;

      if (dev->bus->number < pci1_bus_number)
  	      irq=BSP_PCIE_IRQ;
      else
	      irq=BSP_PCIE2_IRQ;

	printk("INFO: map_irq: bus=%d ,slot=%d, pin=%d  irq=%d\n", dev->bus->number ,slot, pin,irq);
	return irq;
}

