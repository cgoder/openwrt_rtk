/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994 - 2002 by Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 * Copyright (C) 2002  Maciej W. Rozycki
 *
 * Modified for RLX Linux for RLX
 * Copyright (C) 2012  Tony Wu (tonywu@realtek.com)
 */
#ifndef _ASM_PGTABLE_BITS_H
#define _ASM_PGTABLE_BITS_H


/*
 * Note that we shift the lower 32bits of each EntryLo[01] entry
 * 6 bits to the left. That way we can convert the PFN into the
 * physical address by a single 'and' operation and gain 6 additional
 * bits for storing information which isn't present in a normal
 * MIPS page table.
 *
 * Similar to the Alpha port, we need to keep track of the ref
 * and mod bits in software.  We have a software "yeah you can read
 * from this page" bit, and a hardware one which actually lets the
 * process read from the page.	On the same token we have a software
 * writable bit and the real hardware one which actually lets the
 * process write to the page, this keeps a mod bit via the hardware
 * dirty bit.
 *
 * Certain revisions of the R4000 and R5000 have a bug where if a
 * certain sequence occurs in the last 3 instructions of an executable
 * page, and the following page is not mapped, the cpu can do
 * unpredictable things.  The code (when it is written) to deal with
 * this problem will be in the update_mmu_cache() code for the r4k.
 */
/*
 * The following are implemented by software
 *
 * _PAGE_FILE semantics: set:pagecache unset:swap
 */
#define _PAGE_PRESENT_SHIFT	0
#define _PAGE_PRESENT		(1 <<  _PAGE_PRESENT_SHIFT)
#define _PAGE_READ_SHIFT	1
#define _PAGE_READ		(1 <<  _PAGE_READ_SHIFT)
#define _PAGE_WRITE_SHIFT	2
#define _PAGE_WRITE		(1 <<  _PAGE_WRITE_SHIFT)
#define _PAGE_ACCESSED_SHIFT	3
#define _PAGE_ACCESSED		(1 <<  _PAGE_ACCESSED_SHIFT)
#define _PAGE_MODIFIED_SHIFT	4
#define _PAGE_MODIFIED		(1 <<  _PAGE_MODIFIED_SHIFT)
#define _PAGE_FILE_SHIFT	4
#define _PAGE_FILE		(1 <<  _PAGE_FILE_SHIFT)

/*
 * And these are the hardware TLB bits
 */
#define _PAGE_WALLOCATE_SHIFT	5
#define _PAGE_WALLOCATE		(1 << _PAGE_WALLOCATE_SHIFT)
#define _PAGE_MERGEABLE_SHIFT	6
#define _PAGE_MERGEABLE		(1 << _PAGE_MERGEABLE_SHIFT)
#define _PAGE_COHERENT_SHIFT	7
#define _PAGE_COHERENT		(1 << _PAGE_COHERENT_SHIFT)
#define _PAGE_GLOBAL_SHIFT	8
#define _PAGE_GLOBAL		(1 <<  _PAGE_GLOBAL_SHIFT)
#define _PAGE_VALID_SHIFT	9
#define _PAGE_VALID		(1 <<  _PAGE_VALID_SHIFT)
#define _PAGE_SILENT_READ	(1 <<  _PAGE_VALID_SHIFT)	/* synonym  */
#define _PAGE_DIRTY_SHIFT	10
#define _PAGE_DIRTY		(1 << _PAGE_DIRTY_SHIFT)
#define _PAGE_SILENT_WRITE	(1 << _PAGE_DIRTY_SHIFT)
#define _CACHE_UNCACHED_SHIFT	11
#define _CACHE_UNCACHED		(1 << _CACHE_UNCACHED_SHIFT)
#define _CACHE_MASK		(1 << _CACHE_UNCACHED_SHIFT)
#define _CCA_SHIFT		5
#define _CCA_MASK		(7 << 5)

#ifndef _PFN_SHIFT
#define _PFN_SHIFT		    PAGE_SHIFT
#endif
#define _PFN_MASK		(~((1 << (_PFN_SHIFT)) - 1))

#ifndef _PAGE_NO_READ
#define _PAGE_NO_READ ({BUG(); 0; })
#define _PAGE_NO_READ_SHIFT ({BUG(); 0; })
#endif
#ifndef _PAGE_NO_EXEC
#define _PAGE_NO_EXEC ({BUG(); 0; })
#endif
#ifndef _PAGE_GLOBAL_SHIFT
#define _PAGE_GLOBAL_SHIFT ilog2(_PAGE_GLOBAL)
#endif


#ifndef __ASSEMBLY__
/*
 * pte_to_entrylo converts a page table entry (PTE) into a Mips
 * entrylo0/1 value.
 */
static inline uint64_t pte_to_entrylo(unsigned long pte_val)
{
	return pte_val;
}
#endif

/*
 * entrylo cache attribute bits
 *
 * bit 11: Cachable
 * bit 7: (C) Coherent
 * bit 6: (M) Mergeable / (T) Write-through
 * bit 5: (W) Write-allocate
 *
 * Let C => coherent
 * Let M => mergable
 * Let T => write-through
 * Let W => write-allocate
 * Let X => disabled
 */

/* cached mode, bit 11 = 0 */
#define _CACHE_ENTRYLO_XXX		(0 << _CCA_SHIFT)
#define _CACHE_ENTRYLO_XXW		(1 << _CCA_SHIFT)
#define _CACHE_ENTRYLO_XMX		(2 << _CCA_SHIFT)
#define _CACHE_ENTRYLO_XMW		(3 << _CCA_SHIFT)
#define _CACHE_ENTRYLO_CXX		(4 << _CCA_SHIFT)
#define _CACHE_ENTRYLO_CXW		(5 << _CCA_SHIFT)

/* uncached mode, bit 11 = 1 */
#define _CACHE_ENTRYLO_XTX		(2 << _CCA_SHIFT)

/*
 * So far, only the following three combinations are used
 */
#define _CACHE_UNCACHED_WRITETHROUGH	_CACHE_ENTRYLO_XXX
#define _CACHE_UNCACHED_MERGEABLE	_CACHE_ENTRYLO_XMX
#define _CACHE_CACHABLE_NONCOHERENT	_CACHE_ENTRYLO_XXW
#define _CACHE_CACHABLE_COHERENT	_CACHE_ENTRYLO_CXW

#define __READABLE	(_PAGE_SILENT_READ | _PAGE_ACCESSED | _PAGE_READ)
#define __WRITEABLE	(_PAGE_WRITE | _PAGE_SILENT_WRITE | _PAGE_MODIFIED)

#define _PAGE_CHG_MASK	(_PFN_MASK | _PAGE_ACCESSED | _PAGE_MODIFIED | _CACHE_MASK | _CCA_MASK)

#endif /* _ASM_PGTABLE_BITS_H */
