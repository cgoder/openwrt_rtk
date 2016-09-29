/*
 * Realtek Semiconductor Corp.
 *
 * bsp/bspinit.h:
 *
 * Copyright (C) 2006-2012  Tony Wu (tonywu@realtek.com)
 */
#ifndef __BSPINIT_WRT_H_
#define __BSPINIT_WRT_H_

#include <asm/mipsregs.h>
#define IF_NEQ(a,b,lab)         or t6,zero,a;\
                                or t7,zero,b;\
                                bne t6,t7,lab;\
                                nop;


//-------------------------------------------------
// Using register: t6, t7
// t6=value
// t7=address
#define REG32_R(addr,v)  	li t7,addr;\
				lw v, 0(t7);\
				nop;

#define RTL98_V0 0x8198C000
	.macro  kernel_entry_setup
/* flush caches */
/* flush dcache all */
	REG32_R(0xb8000000,t8);
        nop
	nop

	IF_NEQ(t8, RTL98_V0, lab_SC); //jason
    nop
    nop
	la	t1, mips_flush_dcache_all
	srl	t0, t1, 16
	ori	t0, t0, 0x2000
	sll	t0, t0, 16
	sll	t1, t1, 16
	srl	t1, t1, 16
	or	t0, t0, t1
	jalr	t0

/* flush L2 cache all */
	la	t1, mips_flush_l2cache_all
	srl	t0, t1, 16
	ori	t0, t0, 0x2000
	sll	t0, t0, 16
	sll	t1, t1, 16
	srl	t1, t1, 16
	or	t0, t0, t1
	jalr	t0

/* flush icache all */
	la	t1, mips_invalid_icache_all
	srl	t0, t1, 16
	ori	t0, t0, 0x2000
	sll	t0, t0, 16
	sll	t1, t1, 16
	srl	t1, t1, 16
	or	t0, t0, t1
	jalr	t0

	nop
       
/* disable L2 cache */
	mfc0	t0, CP0_CONFIG, 2
	ori	t0, t0, 0x1 << 12
	mtc0	t0, CP0_CONFIG, 2
	nop
	nop
	nop
	nop
lab_SC:
	nop
	nop
/* jump to cacheable address */
	la	t1, cacheable
	srl	t0, t1, 16
	andi	t0, t0, 0xdfff
	sll	t0, t0, 16
	sll	t1, t1, 16
	srl	t1, t1, 16
	or	t0, t0, t1
	jr	t0

cacheable:


	.endm

	.macro  smp_slave_setup
	.endm

#endif
