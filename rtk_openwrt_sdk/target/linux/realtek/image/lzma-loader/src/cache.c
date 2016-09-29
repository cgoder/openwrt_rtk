/*
 * LZMA compressed kernel loader for Realtek 819X
 *
 * Copyright (C) 2011 Gabor Juhos <juhosg@openwrt.org>
 *
 * The cache manipulation routine has been taken from the U-Boot project.
 *	(C) Copyright 2003
 *	Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 */
//#include <linux/autoconf.h> //mark_310
#include <generated/autoconf.h> 
#include <linux/linkage.h>
#include <asm/ptrace.h>
#include <asm/rlxregs.h>
#include <asm/addrspace.h>


/* For Realtek RTL865XC Network platform series */
#define _ICACHE_SIZE		(16 * 1024)		/* 16K bytes */
#define _DCACHE_SIZE		(8 * 1024)		/* 8K bytes */
#define _CACHE_LINE_SIZE	4			/* 4 words */

void flush_cache(void);
static void flush_icache(unsigned int start, unsigned int end);
static void flush_dcache(unsigned int start, unsigned int end);

void flush_cache(void)
{

	flush_dcache(KSEG0, KSEG0+_DCACHE_SIZE);		
	flush_icache(KSEG0, KSEG0+_ICACHE_SIZE);	

}

/*Cyrus Tsai*/
static  void flush_icache(unsigned int start, unsigned int end)
{

	
	flush_dcache(start, end);

	/*Invalidate I-Cache*/
	__asm__ volatile(
		"mtc0 $0,$20\n\t"
		"nop\n\t"
		"li $8,2\n\t"
		"mtc0 $8,$20\n\t"
		"nop\n\t"
		"nop\n\t"
		"mtc0 $0,$20\n\t"
		"nop"
		: /* no output */
		: /* no input */
			);

}

static void flush_dcache(unsigned int start, unsigned int end)
{    

	/* Flush D-Cache using its range */
	unsigned char *p;
	unsigned int size;
	unsigned int flags;
	unsigned int i;
   
	size = end - start;
   
	/* correctness check : flush all if any parameter is illegal */
// david	
//	if (	(size >= dcache_size) ||
	if ((size >= _DCACHE_SIZE) ||	(KSEGX(start) != KSEG0)	)
	{
		/*
		 *	ghhguang
		 *		=> For Realtek Lextra CPU,
		 *		   the cache would NOT be flushed only if the Address to-be-flushed
		 *		   is the EXPLICIT address ( which is really stored in that cache line ).
		 *		   For the aliasd addresses, the cache entry would NOT be flushed even
		 *		   it matchs same cache-index.
		 *
		 *		   => This is different from traditional MIPS-based CPU's configuration.
		 *		      So if we want to flush ALL-cache entries, we would need to use "mtc0"
		 *		      instruction instead of simply modifying the "size" to "dcache_size"
		 *		      and "start" to "KSEG0".
		 *
		 */
		__asm__ volatile(
			"mtc0 $0,$20\n\t"
			"nop\n\t"
			"li $8,512\n\t"
			"mtc0 $8,$20\n\t"
			"nop\n\t"
			"nop\n\t"
			"mtc0 $0,$20\n\t"
			"nop"
			: /* no output */
			: /* no input */
				);
	} 
	else
	{
		/* Start to isolate cache space */
		p = (char *)start;
   
		flags = read_c0_status();
   
		/* isolate cache space */
		write_c0_status( (ST0_ISC | flags) &~ ST0_IEC );
   
		for (i = 0; i < size; i += 0x040)
		{
			asm ( 	
			#ifdef OPEN_RSDK_RTL865x
				".word 0xbc750000\n\t"
				".word 0xbc750010\n\t"
				".word 0xbc750020\n\t"
				".word 0xbc750030\n\t"
			#endif
				"cache 0x15, 0x000(%0)\n\t"
			 	"cache 0x15, 0x010(%0)\n\t"
			 	"cache 0x15, 0x020(%0)\n\t"
			 	"cache 0x15, 0x030(%0)\n\t"
				:		/* No output registers */
				:"r"(p)		/* input : 'p' as %0 */
				);
			p += 0x040;
		}
   
		write_c0_status(flags);
	}    
   
}

