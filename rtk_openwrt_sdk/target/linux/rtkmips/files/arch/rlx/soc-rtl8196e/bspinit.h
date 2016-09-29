/*
 * Realtek Semiconductor Corp.
 *
 * bsp/bspinit.h:
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */
#ifndef __BSPINIT_H_
#define __BSPINIT_H_

#include <asm/asm.h>

#define IMEM_ENABLE
#define DMEM_ENABLE

.macro  kernel_entry_setup
	.set    push
	.set    noreorder

	#---------------------------------------------------------------------
	#--- initialize and start COP3
	mfc0	$8, $12
	nop
	or	$8, 0x80000000
	mtc0	$8, $12
	nop
	nop

	#---------------------------------------------------------------------
	# first block
	# IMEM0 off
	mtc0	$0, $20 # CCTL
	nop
	nop
	li	$8, 0x00000020
	mtc0	$8, $20
	nop
	nop

	# DMEM0 off
	mtc0	$0, $20 # CCTL
	nop
	nop
	li	$8, 0x00000800
	mtc0	$8, $20
	nop
	nop

	#---------------------------------------------------------------------
	#--- invalidate the icache and dcache with a 0->1 transition
	mtc0	$0, $20 # CCTL
	nop
	nop
	li	$8, 0x00000202 # Invalid ICACHE and DCACHE
	mtc0	$8, $20
	nop
	nop

#ifdef IMEM_ENABLE
#define IMEM0_SIZE		0x4000
#define IMEM1_SIZE		0x0
	#---------------------------------------------------------------------
	la      $8, __iram_start
	la      $9, __iram_tail
	beq     $8, $9, skip_imem_init
	nop

	#---------------------------------------------------------------------
	#--- load IMEM0 base and top
	la	$8, __iram
	la	$9, 0x0fffc000	# 16K-byte(IMEM0_SIZE) alignment
	and	$8, $8, $9
	mtc3	$8, $0	# IW bas
	nop
	nop
	add	$8, $8, (IMEM0_SIZE-1) # 0x3fff
	mtc3	$8, $1	# IW top
	nop
	nop

	#--- Refill IMEM0 with a 0->1 transition
	mtc0	$0, $20 # CCTL
	nop
	nop
	li	$8, 0x00000010	# IMEM0 Fill
	mtc0	$8, $20
	nop
	nop

skip_imem_init:
	nop
#endif

#ifdef DMEM_ENABLE
#define DMEM0_SIZE		0x2000
#define DMEM1_SIZE		0x0
#define TOTAL_DMEM_SIZE		(DMEM0_SIZE+DMEM1_SIZE)
#define WORD_SZIE		4
	#---------------------------------------------------------------------
	la      $8, __dram_start
	la      $9, __dram_tail
	beq     $8, $9, skip_dmem_init
	nop

	#---------------------------------------------------------------------
	#--- load DMEM0 base and top
	la	$8, (__dram+TOTAL_DMEM_SIZE)
	la	$9, 0x0fffe000	# 8K-byte(DMEM0_SIZE) alignment
	and	$8, $8, $9
	mtc3	$8, $4	# DW bas
	nop
	nop
	add	$8, $8, (DMEM0_SIZE-1) # 0x1fff
	mtc3	$8,$5	# DW top
	nop
	nop
	
	# DMEM0 on
	mtc0	$0, $20 # CCTL
	nop
	nop
	li	$8, 0x00000400
	mtc0	$8, $20
	nop
	nop

	#---------------------------------------------------------------------
	#--- backup sdram to DMEM
	la	$10, TOTAL_DMEM_SIZE			#copy size
	la	$8, (__dram+TOTAL_DMEM_SIZE+TOTAL_DMEM_SIZE-WORD_SZIE)	#dst
	la	$9, (__dram+TOTAL_DMEM_SIZE-WORD_SZIE)	#src

1:
	lw	$12, 0($9)
	sub	$9, $9, WORD_SZIE
	sub	$10, $10, WORD_SZIE
	sw	$12, 0($8)
	sub	$8, $8, WORD_SZIE
	bnez	$10, 1b
	nop
	nop

	#---------------------------------------------------------------------
	# DMEM0 off
	mtc0	$0, $20 # CCTL
	nop
	nop
	li	$8, 0x00000800 
	mtc0	$8, $20
	nop
	nop	

	#---------------------------------------------------------------------
	#--- load DMEM0 base and top
	la	$8, __dram
	la	$9, 0x0fffe000
	and	$8, $8, $9
	mtc3	$8, $4	# DW bas
	nop
	nop
	addiu	$8, $8, (DMEM0_SIZE-1)
	mtc3	$8, $5	# DW top
	nop
	nop
	
	# DMEM0 on
	mtc0	$0, $20 # CCTL
	nop
	nop
	li	$8,0x00000400
	mtc0	$8, $20
	nop
	nop

skip_dmem_init:
	nop
#endif

	.set	pop
.endm

.macro  smp_slave_setup
.endm

#endif
