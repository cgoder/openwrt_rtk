#include <asm/asmmacro.h>

#if defined(CONFIG_RTK_VOIP)
		.macro refill_dmem	sel, addr, dma_addr, size
		.set noreorder
		la		t0, ( \dma_addr + 8 )	# CTRL 
		sw		zero, 0(t0)
		la		t1, ( 1 << 21 )
		sw		t1, 0(t0)
		la		t0, ( \dma_addr )	# SA 
		sw		zero, 0(t0)
		la		t0, \addr		# EXT SA
		la		t1, 0x1ffffffc
		and		t1, t0, t1
		la		t0, ( \dma_addr + 4 )
		sw		t1, 0(t0)
		la		t0, ( \dma_addr + 8 ) 	# CTRL 
		la		t1, ( \sel << 23 ) | ( 1 << 22 ) | ( 1 << 19 ) | ( ( ( \size ) >> 2 ) & 0x3FFFF )
		sw		t1, 0(t0)
		la		t4, ( 1 << 20 )
		or		t1, t1, t4
		sw		t1, 0(t0)
1:
		lw		t1, 0(t0)
		and		t1, t1, t4
		bne		t1, zero, 1b
		nop		
		.endm

#endif
	.text
        LEAF(_imem_dmem_init)
        .set noreorder

	#--- initialize and start COP3
        mfc0    $8,$12
        nop
        nop
        or              $8,0x80000000
        mtc0    $8,$12
        nop
        nop

        #--- invalidate the IRAM with a 0->1 transition
        mtc0    $0, $20 # CCTL
        nop
        nop
        li              $8,0x00000020 # IRAM Off
        mtc0    $8, $20
        nop
        nop

        #--- invalidate the icache and dcache with a 0->1 transition
        mtc0    $0, $20 # CCTL
        nop
        nop
        li              $8,0x00000202 # Invalid ICACHE and DCACHE
        mtc0    $8, $20
        nop
        nop

        #--- load iram base and top
#ifdef CONFIG_RTL_819XD
#define IMEM0_SIZE	4096*4
#else
#define IMEM0_SIZE	4096
#endif
#define IMEM1_SIZE	4096
        la              $8,__iram
        la              $9,0x0fffc000
        and             $8,$8,$9
        mtc3    $8,$0                                                           # IW bas
        nop
        nop
#ifdef CONFIG_ARCH_CPU_RLX5281
#if defined(CONFIG_RTL8198_REVISION_B)
        //jasonwang0413
        li	t6,0xb8000000
	lw	t7,0(t6)
	nop
	nop
	and     t7,t7,0x03
	bgtz	t7,rev_b
	nop
rev_a:	// 00
        li     t6,0xfff
        li     t4,0xfff
        j     rev_end
	nop
rev_b:	// 01
rev_c:	// 02
        li     t6,0x7fff
        li     t4,0x1fff
rev_end:
             nop
             nop

        add   $8,$8,t6
#else
        addiu   $8,$8,IMEM0_SIZE-1
#endif
        mtc3    $8,$1                                                           # IW top
        nop
        nop

        #--- Refill the IRAM with a 0->1 transition
        mtc0    $0, $20 # CCTL
        nop
        nop
        li              $8,0x00000010 # IRAM Fill
        mtc0    $8, $20
        nop
        nop
#if !defined(CONFIG_RTL_819XD)
	#--- load iram base1 and top1
        la              $8,__iram
#ifdef CONFIG_RTL8198_REVISION_B
	add             $8,$8,t6
	add             $8,$8,0x01
#else
	add             $8,$8,IMEM0_SIZE
#endif
        la              $9,0x0fffc000
        and             $8,$8,$9
        mtc3    $8,$2                                                           # IW bas 1
        nop
        nop
#ifdef CONFIG_RTL8198_REVISION_B
        add   $8,$8,t4
#else
        addiu   $8,$8,IMEM1_SIZE-1
#endif
        mtc3    $8,$3                                                           # IW top 1
        nop
        nop

        #--- Refill the IRAM with a 0->1 transition
        mtc0    $0, $20,1 # CCTL
        nop
        nop
        li              $8,0x00000010 # IRAM Fill
        mtc0    $8, $20,1
#endif
        nop
        nop

        #--- load dram base and top
        la              $8,__dram_start
        la              $9,__dram_end
        beq             $8,$9,skip_dramInit
	nop
        la              $9,0x0fffe000
        and             $8,$8,$9
        mtc3    $8,$4                                                           # DW bas
        nop
        nop
#if defined(CONFIG_RTL_819XD)
        #define DMEM0_SIZE	4096*2

	addiu   $8,$8,(DMEM0_SIZE-1)
#else
        addiu   $8,$8,0xfff
#endif
        mtc3    $8,$5                                                           # DW top
        nop
        nop
	#la              $8,__dram_start
        #la              $9,__dram_end
        #beq             $8,$9,skip_dramInit
	#nop
        #la              $9,0x0fffe000
        add		$8,$8,1
	#and             $8,$8,$9
#if !defined(CONFIG_RTL_819XD)
        mtc3    $8,$6                                                           # DW bas 1
        nop
        nop
        addiu   $8,$8,0xfff
        mtc3    $8,$7                                                           # DW top 1
#endif
        nop
        nop
//#if defined(CONFIG_RTK_VOIP) && !defined(CONFIG_RTL_89xxD)
#if defined(CONFIG_RTK_VOIP)
	#--- Refill the DRAM -----
#if defined(CONFIG_RTL_89xxC)
#define DMEM_DMA_ADDR      0xB800B800
	refill_dmem 2, __dram_start, DMEM_DMA_ADDR, 0x1000		# DMEM 0 (4k)
	refill_dmem 3, __dram_start + 0x1000, DMEM_DMA_ADDR, 0x1000	# DMEM 1 (4k)
#endif
#if defined(CONFIG_RTL_89xxD)
#define DMEM_DMA_ADDR      0xB8006000
	refill_dmem 2, __dram_start, DMEM_DMA_ADDR, 0x2000		# DMEM 0 (8k)
#endif
#endif
#if 0//  defined(CONFIG_RTL_89xxD)
	mfc0    t0, $20
	or	t0, 0x00000800
	mtc0    t0, $20		# DMEM0 OFF
#else
	mfc0	t0, $20
	or	t0, 0x00000400	# DMEM On	// pkshih: add to enable DMEM0 and DMEM1
        mtc0    t0, $20		# DMEM0 ON
#endif
#if !defined(CONFIG_RTL_819XD)
        mfc0	t0, $20,1
	or	t0, 0x00000400	# DMEM On	// pkshih: add to enable DMEM0 and DMEM1
	mtc0	t0, $20,1	# DMEM1 ON
#endif
		nop
		nop

#else
        addiu   $8,$8,0x3fff
        mtc3    $8,$1                                                           # IW top
        nop
        nop

        #--- Refill the IRAM with a 0->1 transition
        mtc0    $0, $20 # CCTL
        nop
        nop
        li              $8,0x00000010 # IRAM Fill
        mtc0    $8, $20
        nop
        nop

        #--- load dram base and top
        la              $8,__dram_start
        la              $9,__dram_end
        beq             $8,$9,skip_dramInit
	nop
        la              $9,0x0fffe000
        and             $8,$8,$9
        mtc3    $8,$4                                                           # DW bas
        nop
        nop
        addiu   $8,$8,0x1fff
        mtc3    $8,$5                                                           # DW top
        nop
        nop
#endif
skip_dramInit:
        #--- enable icache and dcache
        mtc0    $0, $20 # CCTL
        nop
        nop

        .set    reorder
        j               $31
	END(_imem_dmem_init)


