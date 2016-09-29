/*
 * Realtek Semiconductor Corp.
 *
 * pci.c:
 *     bsp PCI initialization code
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/types.h>
#include <linux/delay.h>

#include <asm/cpu.h>
#include <asm/io.h>
#include <asm/pci.h>

//#include "bspchip.h"
#include <asm/mach-realtek/bspchip.h>

extern struct pci_ops bsp_pcie_ops;
extern struct pci_ops bsp_pcie_ops1;
extern int PCIE_reset_procedure(int portnum, int Use_External_PCIE_CLK, int mdio_reset); //fixup.c
extern int bsp_has_pci_slot(int pci_slot);


static struct resource pcie_mem_resource = {
	.name = "PCIe Memory resources",
	.start = PADDR(BSP_PCIE0_D_MEM),
	.end = PADDR(BSP_PCIE0_D_MEM + 0xFFFFFF),
	.flags = IORESOURCE_MEM,
};

static struct resource pcie_io_resource = {
	.name = "PCIe I/O resources",
	.start = PADDR(BSP_PCIE0_D_IO),
	.end = PADDR(BSP_PCIE0_D_IO + 0x1FFFFF),
	.flags = IORESOURCE_IO,
};

static struct pci_controller bsp_pcie_controller = {
	.pci_ops = &bsp_pcie_ops,
	.mem_resource = &pcie_mem_resource,
	.io_resource = &pcie_io_resource,
};

static struct resource pcie_mem_resource1 = {
	.name = "PCIe1 Memory resources",
	.start = PADDR(BSP_PCIE1_D_MEM),
	.end = PADDR(BSP_PCIE1_D_MEM + 0xFFFFFF),
	.flags = IORESOURCE_MEM,
};

static struct resource pcie_io_resource1 = {
	.name = "PCIe1 I/O resources",
	.start = PADDR(BSP_PCIE1_D_IO),
	.end = PADDR(BSP_PCIE1_D_IO + 0x1FFFFF),
	.flags = IORESOURCE_IO,
};

static struct pci_controller bsp_pcie_controller1 = {
	.pci_ops = &bsp_pcie_ops1,
	.mem_resource = &pcie_mem_resource1,
	.io_resource = &pcie_io_resource1,
};

static int __init bsp_pcie_init(void)
{
	int pci_slot=0;
	int pci_exist0=0;
	int pci_exist1=0;

	 //pci 0 
	if(bsp_has_pci_slot(pci_slot)) //if have pcie0	
		if(PCIE_reset_procedure(pci_slot, 0, 1)) // (port,externalClk,mdio_reset)		
			pci_exist0=1;

	pci_slot=1;
	if(bsp_has_pci_slot(pci_slot)) //if have pcie1	
		if(PCIE_reset_procedure(pci_slot, 0, 1)) // (port,externalClk,mdio_reset)		
			pci_exist1=1;

	if(pci_exist0)		
		register_pci_controller(&bsp_pcie_controller);

	if(pci_exist1)		
		register_pci_controller(&bsp_pcie_controller1);

	return 0;
}
arch_initcall(bsp_pcie_init);
