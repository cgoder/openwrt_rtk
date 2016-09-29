/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 2003 Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 *
 * Modified for RLX processors
 * Copyright (C) 2008-2011 Tony Wu (tonywu@realtek.com)
 */
#ifndef _ASM_PGTABLE_32_H
#define _ASM_PGTABLE_32_H

#include <asm/addrspace.h>
#include <asm/page.h>

#include <linux/linkage.h>
#include <asm/cachectl.h>
#include <asm/fixmap.h>

#include <asm-generic/pgtable-nopmd.h>

/*
 * Basically we have the same two-level (which is the logical three level
 * Linux page table layout folded) page tables as the i386.  Some day
 * when we have proper page coloring support we can have a 1% quicker
 * tlb refill handling mechanism, but for now it is a bit slower but
 * works even with the cache aliasing problem the R4k and above have.
 */

/* PGDIR_SHIFT determines what a third-level page table entry can map */
#define PGDIR_SHIFT	(2 * PAGE_SHIFT + PTE_ORDER - PTE_T_LOG2)
#define PGDIR_SIZE	(1UL << PGDIR_SHIFT)
#define PGDIR_MASK	(~(PGDIR_SIZE-1))

/*
 * Entries per page directory level: we use two-level, so
 * we don't really have any PUD/PMD directory physically.
 */
#define __PGD_ORDER	(32 - 3 * PAGE_SHIFT + PGD_T_LOG2 + PTE_T_LOG2)
#define PGD_ORDER	(__PGD_ORDER >= 0 ? __PGD_ORDER : 0)
#define PUD_ORDER	aieeee_attempt_to_allocate_pud
#define PMD_ORDER	1
#define PTE_ORDER	0

#define PTRS_PER_PGD	(USER_PTRS_PER_PGD * 2)
#define PTRS_PER_PTE	((PAGE_SIZE << PTE_ORDER) / sizeof(pte_t))

#define USER_PTRS_PER_PGD	(0x80000000UL/PGDIR_SIZE)
#define FIRST_USER_ADDRESS	0

#define VMALLOC_START	  MAP_BASE

#define PKMAP_BASE		(0xfe000000UL)

#ifdef CONFIG_HIGHMEM
# define VMALLOC_END	(PKMAP_BASE-2*PAGE_SIZE)
#else
# define VMALLOC_END	(FIXADDR_START-2*PAGE_SIZE)
#endif

#define pte_ERROR(e) \
	printk("%s:%d: bad pte %08lx.\n", __FILE__, __LINE__, pte_val(e))
#define pgd_ERROR(e) \
	printk("%s:%d: bad pgd %08lx.\n", __FILE__, __LINE__, pgd_val(e))

extern void load_pgd(unsigned long pg_dir);

extern pte_t invalid_pte_table[PAGE_SIZE/sizeof(pte_t)];

/*
 * Empty pgd/pmd entries point to the invalid_pte_table.
 */
static inline int pmd_none(pmd_t pmd)
{
	return pmd_val(pmd) == (unsigned long) invalid_pte_table;
}

#define pmd_bad(pmd)		(pmd_val(pmd) & ~PAGE_MASK)

static inline int pmd_present(pmd_t pmd)
{
	return pmd_val(pmd) != (unsigned long) invalid_pte_table;
}

static inline void pmd_clear(pmd_t *pmdp)
{
	pmd_val(*pmdp) = ((unsigned long) invalid_pte_table);
}

#define pte_page(x)		pfn_to_page(pte_pfn(x))

#define pte_pfn(x)		((unsigned long)((x).pte >> _PFN_SHIFT))
#define pfn_pte(pfn, prot)	__pte(((unsigned long long)(pfn) << _PFN_SHIFT) | pgprot_val(prot))

#define __pgd_offset(address)	pgd_index(address)
#define __pud_offset(address)	(((address) >> PUD_SHIFT) & (PTRS_PER_PUD-1))
#define __pmd_offset(address)	(((address) >> PMD_SHIFT) & (PTRS_PER_PMD-1))

/* to find an entry in a kernel page-table-directory */
#define pgd_offset_k(address) pgd_offset(&init_mm, address)

#define pgd_index(address)	(((address) >> PGDIR_SHIFT) & (PTRS_PER_PGD-1))

/* to find an entry in a page-table-directory */
#define pgd_offset(mm, addr)	((mm)->pgd + pgd_index(addr))

/* Find an entry in the third-level page table.. */
#define __pte_offset(address)						\
	(((address) >> PAGE_SHIFT) & (PTRS_PER_PTE - 1))
#define pte_offset(dir, address)					\
	((pte_t *) pmd_page_vaddr(*(dir)) + __pte_offset(address))
#define pte_offset_kernel(dir, address)					\
	((pte_t *) pmd_page_vaddr(*(dir)) + __pte_offset(address))

#define pte_offset_map(dir, address)					\
	((pte_t *)page_address(pmd_page(*(dir))) + __pte_offset(address))
#define pte_unmap(pte) ((void)(pte))

/* Swap entries must have VALID bit cleared. */
#define __swp_type(x)		(((x).val >> 10) & 0x1f)
#define __swp_offset(x)		((x).val >> 15)
#define __swp_entry(type,offset)	\
	((swp_entry_t) { ((type) << 10) | ((offset) << 15) })

/*
 * Bits 0, 4, 8, and 9 are taken, split up 28 bits of offset into this range:
 */
#define PTE_FILE_MAX_BITS	28

#define pte_to_pgoff(_pte)	((((_pte).pte >> 1 ) & 0x07) | \
				 (((_pte).pte >> 2 ) & 0x38) | \
				 (((_pte).pte >> 10) <<	 6 ))

#define pgoff_to_pte(off)	((pte_t) { (((off) & 0x07) << 1 ) | \
					   (((off) & 0x38) << 2 ) | \
					   (((off) >>  6 ) << 10) | \
					   _PAGE_FILE })

#define __pte_to_swp_entry(pte) ((swp_entry_t) { pte_val(pte) })
#define __swp_entry_to_pte(x)	((pte_t) { (x).val })

#endif /* _ASM_PGTABLE_32_H */
