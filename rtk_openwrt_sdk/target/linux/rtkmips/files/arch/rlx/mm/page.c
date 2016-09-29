/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2003, 04, 05 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2007  Maciej W. Rozycki
 * Copyright (C) 2008  Thiemo Seufer
 * Copyright (C) 2012  MIPS Technologies, Inc.
 *
 * Modified for RLX processors
 * Copyright (C) 2008-2012 Tony Wu (tonywu@realtek.com)
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/smp.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#include <asm/bugs.h>
#include <asm/cacheops.h>
#include <asm/inst.h>
#include <asm/io.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/prefetch.h>
#include <asm/bootinfo.h>
#include <asm/rlxregs.h>
#include <asm/mmu_context.h>
#include <asm/cpu.h>

#include <asm/uasm.h>

/* Registers used in the assembled routines. */
#define ZERO 0
#define AT 2
#define A0 4
#define A1 5
#define A2 6
#define T0 8
#define T1 9
#define T2 10
#define T3 11
#define T9 25
#define RA 31

/* Handle labels (which must be positive integers). */
enum label_id {
	label_clear_nopref = 1,
	label_clear_pref,
	label_copy_nopref,
	label_copy_pref_both,
	label_copy_pref_store,
};

UASM_L_LA(_clear_nopref)
UASM_L_LA(_clear_pref)
UASM_L_LA(_copy_nopref)
UASM_L_LA(_copy_pref_both)
UASM_L_LA(_copy_pref_store)

/* We need one branch and therefore one relocation per target label. */
static struct uasm_label __cpuinitdata labels[5];
static struct uasm_reloc __cpuinitdata relocs[5];

static inline void __cpuinit
pg_addiu(u32 **buf, unsigned int reg1, unsigned int reg2, unsigned int off)
{
	UASM_i_ADDIU(buf, reg1, reg2, off);
}

static void __cpuinit build_clear_store(u32 **buf, int off)
{
	uasm_i_sw(buf, ZERO, off, A0);
}

extern u32 __clear_page_start;
extern u32 __clear_page_end;
extern u32 __copy_page_start;
extern u32 __copy_page_end;

void __cpuinit build_clear_page(void)
{
	u32 *buf = &__clear_page_start;
	struct uasm_label *l = labels;
	struct uasm_reloc *r = relocs;
	int i;
	static atomic_t run_once = ATOMIC_INIT(0);

	if (atomic_xchg(&run_once, 1)) {
		return;
	}

	memset(labels, 0, sizeof(labels));
	memset(relocs, 0, sizeof(relocs));

	pg_addiu(&buf, A2, A0, PAGE_SIZE);

	uasm_l_clear_pref(&l, buf);
	build_clear_store(&buf, 0);
	build_clear_store(&buf, 4);
	build_clear_store(&buf, 8);
	build_clear_store(&buf, 12);

	pg_addiu(&buf, A0, A0, 32);
	build_clear_store(&buf, -16);
	build_clear_store(&buf, -12);
	build_clear_store(&buf, -8);
	uasm_il_bne(&buf, &r, A0, A2, label_clear_pref);
	build_clear_store(&buf, -4);

	uasm_i_jr(&buf, RA);
	uasm_i_nop(&buf);

	BUG_ON(buf > &__clear_page_end);

	uasm_resolve_relocs(relocs, labels);

	pr_debug("Synthesized clear page handler (%u instructions).\n",
		 (u32)(buf - &__clear_page_start));

	pr_debug("\t.set push\n");
	pr_debug("\t.set noreorder\n");
	for (i = 0; i < (buf - &__clear_page_start); i++)
		pr_debug("\t.word 0x%08x\n", (&__clear_page_start)[i]);
	pr_debug("\t.set pop\n");
}

static void __cpuinit build_copy_load(u32 **buf, int reg, int off)
{
	uasm_i_lw(buf, reg, off, A1);
}

static void __cpuinit build_copy_store(u32 **buf, int reg, int off)
{
	uasm_i_sw(buf, reg, off, A0);
}

void __cpuinit build_copy_page(void)
{
	u32 *buf = &__copy_page_start;
	struct uasm_label *l = labels;
	struct uasm_reloc *r = relocs;
	int i;
	static atomic_t run_once = ATOMIC_INIT(0);

	if (atomic_xchg(&run_once, 1)) {
		return;
	}

	memset(labels, 0, sizeof(labels));
	memset(relocs, 0, sizeof(relocs));

	pg_addiu(&buf, A2, A0, PAGE_SIZE);

	uasm_l_copy_pref_both(&l, buf);
	build_copy_load(&buf, T0, 0);
	build_copy_load(&buf, T1, 4);
	build_copy_load(&buf, T2, 8);
	build_copy_load(&buf, T3, 12);
	build_copy_store(&buf, T0, 0);
	build_copy_store(&buf, T1, 4);
	build_copy_store(&buf, T2, 8);
	build_copy_store(&buf, T3, 12);

	pg_addiu(&buf, A1, A1, 32);
	pg_addiu(&buf, A0, A0, 32);

	build_copy_load(&buf, T0, -16);
	build_copy_load(&buf, T1, -12);
	build_copy_load(&buf, T2, -8);
	build_copy_load(&buf, T3, -4);
	build_copy_store(&buf, T0, -16);
	build_copy_store(&buf, T1, -12);
	build_copy_store(&buf, T2, -8);
	uasm_il_bne(&buf, &r, A2, A0, label_copy_pref_both);
	build_copy_store(&buf, T3, -4);

	uasm_i_jr(&buf, RA);
	uasm_i_nop(&buf);

	BUG_ON(buf > &__copy_page_end);

	uasm_resolve_relocs(relocs, labels);

	pr_debug("Synthesized copy page handler (%u instructions).\n",
		 (u32)(buf - &__copy_page_start));

	pr_debug("\t.set push\n");
	pr_debug("\t.set noreorder\n");
	for (i = 0; i < (buf - &__copy_page_start); i++)
		pr_debug("\t.word 0x%08x\n", (&__copy_page_start)[i]);
	pr_debug("\t.set pop\n");
}
