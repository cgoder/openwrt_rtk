/*
 * LZMA compressed kernel loader for Realtek 819X
 *
 * Copyright (C) 2011 Gabor Juhos <juhosg@openwrt.org>
 *
 * Some parts of this code was based on the OpenWrt specific lzma-loader
 * for the BCM47xx and ADM5120 based boards:
 *	Copyright (C) 2004 Manuel Novoa III (mjn3@codepoet.org)
 *	Copyright (C) 2005 by Oleg I. Vdovikin <oleg@cs.msu.su>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#include <asm/asm.h>
#include <asm/regdef.h>


	.text

LEAF(startup)
	.set noreorder		

__reloc_done:
	/* clear bss */
	la	t0, _bss_start
	la	t1, _bss_end
	b	__bss_check
	nop

__bss_fill:
	sw	zero, 0(t0)
	addi	t0, 4

__bss_check:
	bne	t0, t1, __bss_fill
	nop

	/* Setup new "C" stack */
	la	sp, _stack

	/* jump to the decompressor routine */
	la	t0, loader_main
	jr	t0
	nop

	.set reorder
END(startup)
