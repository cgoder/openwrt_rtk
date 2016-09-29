#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <asm/addrspace.h>
#include <asm/bootinfo.h>
#include <asm/gcmpregs.h>
#include <asm/mach-realtek/bspchip.h>


#define cpu_mem_size        (32 << 20)

#define cpu_imem_size       0
#define cpu_dmem_size       0
#define cpu_smem_size       0

#define REG32(reg)	(*(volatile unsigned int *)(reg))
#define DCR			(0xB8001004)
#define DCR_BANKCNT_FD_S	(28)
#define DCR_DBUSWID_FD_S	(24)
#define DCR_ROWCNT_FD_S		(20)
#define DCR_COLCNT_FD_S		(16)
#define DCR_DCHIPSEL_FD_S	(15)
#define DCR_BANKCNT_MASK	(0xF << DCR_BANKCNT_FD_S)
#define DCR_DBUSWID_MASK	(0xF << DCR_DBUSWID_FD_S)
#define DCR_ROWCNT_MASK		(0xF << DCR_ROWCNT_FD_S)
#define DCR_COLCNT_MASK		(0xF << DCR_COLCNT_FD_S)
#define DCR_DCHIPSEL_MASK	(1 << DCR_DCHIPSEL_FD_S)

unsigned int _DCR_get_buswidth(void)
{
	unsigned int buswidth;

	buswidth = ((REG32(DCR) & DCR_DBUSWID_MASK) >> DCR_DBUSWID_FD_S);

	switch (buswidth) {
		case 0:
			return (8);
		case 1:
			return (16);
		case 2:
			return (32); 
		default:
			return 0;
	}
}

unsigned int _DCR_get_chipsel(void)
{
	unsigned int chipsel;

	chipsel = ((REG32(DCR) & DCR_DCHIPSEL_MASK) >> DCR_DCHIPSEL_FD_S);

	if(chipsel)
		return 2;
	else
		return 1;
}
unsigned int _DCR_get_rowcnt(void)
{
	unsigned int rowcnt;

	rowcnt = ((REG32(DCR) & DCR_ROWCNT_MASK) >> DCR_ROWCNT_FD_S);
	
	return (2048 << rowcnt);
}
unsigned int _DCR_get_colcnt(void)
{
	unsigned int colcnt;

	colcnt = ((REG32(DCR) & DCR_COLCNT_MASK) >> DCR_COLCNT_FD_S);

	if(4 < colcnt)
		return 0;
	else
		return (256 << colcnt);
}
unsigned int _DCR_get_bankcnt(void)
{
	unsigned int bankcnt;

	bankcnt = ((REG32(DCR) & DCR_BANKCNT_MASK) >> DCR_BANKCNT_FD_S);
	
	switch (bankcnt)
	{
		case 0:
			return 2;
		case 1:
			return 4;
		case 2:
			return 8;
	}
	return 0;
}

#ifdef CONFIG_SMP
void __init bsp_smp_init(void)
{
#ifdef CONFIG_MIPS_CMP
      if (gcmp_probe(GCMP_BASE_ADDR, GCMP_BASE_SIZE))
        if (register_cmp_smp_ops())
                panic("failed to register_vsmp_smp_ops()");
#endif
}
#endif

void prom_soc_init(void)
{
       u_long mem_size;
	unsigned int	buswidth, chipsel, rowcnt;
	unsigned int	colcnt, bankcnt;	

	/* 
	 * Check DCR
	 */
	/* 1. Bus width     */
	buswidth = _DCR_get_buswidth();

	/* 2. Chip select   */
	chipsel = _DCR_get_chipsel();

	/* 3. Row count     */
	rowcnt = _DCR_get_rowcnt();

	/* 4. Column count  */
	colcnt = _DCR_get_colcnt();

	/* 5. Bank count    */
	bankcnt = _DCR_get_bankcnt();

	if ((buswidth == 0) || (colcnt == 0) || (bankcnt == 0))
		mem_size = cpu_mem_size;	
	else
		mem_size = rowcnt*colcnt*(buswidth/8)*chipsel*bankcnt;

#ifdef CONFIG_HIGHMEM
        //force to  256Mx2 = 512M , FIXME!!
        mem_size = 256 * 1024 * 1024;
        add_memory_region(0, mem_size, BOOT_MEM_RAM);
        add_memory_region(0x30000000, mem_size,BOOT_MEM_RAM);
#else
        if(mem_size > (320<<20)) //patch for Memory address bigger than 256 MB
        mem_size = (320 << 20);
        add_memory_region(0, mem_size, BOOT_MEM_RAM);
#endif
#ifdef CONFIG_SMP
	bsp_smp_init();	
#endif

}

int bsp_has_pci_slot(int pci_slot)
{
	//8198c hav2 2 pci slot
	if( pci_slot < 2)
		return 1;
	
	return 0;	
}


