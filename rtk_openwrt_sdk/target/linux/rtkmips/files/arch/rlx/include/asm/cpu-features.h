/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2003, 2004 Ralf Baechle
 * Copyright (C) 2004  Maciej W. Rozycki
 */
#ifndef __ASM_CPU_FEATURES_H
#define __ASM_CPU_FEATURES_H

#include <asm/cpu.h>
#include <asm/cpu-info.h>
#include <bspcpu.h>

#ifndef current_cpu_type
#define current_cpu_type()	current_cpu_data.cputype
#endif

/*
 * SMP assumption: Options of CPU 0 are a superset of all processors.
 * This is true for all known MIPS systems.
 */
#ifndef cpu_has_tlb
#define cpu_has_tlb		1
#endif
#ifndef cpu_has_4kex
#define cpu_has_4kex		0
#endif
#ifndef cpu_has_3k_cache
#define cpu_has_3k_cache	1
#endif
#define cpu_has_6k_cache	0
#define cpu_has_8k_cache	0
#ifndef cpu_has_4k_cache
#define cpu_has_4k_cache	0
#endif
#ifndef cpu_has_tx39_cache
#define cpu_has_tx39_cache	0
#endif
#ifndef cpu_has_octeon_cache
#define cpu_has_octeon_cache	0
#endif
#ifdef CONFIG_CPU_HAS_FPU
#define cpu_has_fpu		1
#define raw_cpu_has_fpu		1
#define cpu_has_32fpr		1
#else
#define cpu_has_fpu		0
#define raw_cpu_has_fpu		0
#define cpu_has_32fpr		0
#endif
#ifndef cpu_has_counter
#define cpu_has_counter		1
#endif
#ifdef CONFIG_CPU_HAS_WMPU
#define cpu_has_watch		1
#else
#define cpu_has_watch		0
#endif
#ifndef cpu_has_divec
#define cpu_has_divec		0
#endif
#ifndef cpu_has_vce
#define cpu_has_vce		0
#endif
#ifndef cpu_has_cache_cdex_p
#define cpu_has_cache_cdex_p	0
#endif
#ifndef cpu_has_cache_cdex_s
#define cpu_has_cache_cdex_s	0
#endif
#ifndef cpu_has_prefetch
#define cpu_has_prefetch	0
#endif
#ifndef cpu_has_mcheck
#define cpu_has_mcheck		0
#endif
#ifndef cpu_has_ejtag
#define cpu_has_ejtag		0
#endif
#ifdef CONFIG_CPU_HAS_LLSC
#define cpu_has_llsc		1
#define kernel_uses_llsc	1
#else
#define cpu_has_llsc		0
#define kernel_uses_llsc	0
#endif
#ifndef cpu_has_mips16
#define cpu_has_mips16		1
#endif
#ifndef cpu_has_mdmx
#define cpu_has_mdmx		0
#endif
#ifndef cpu_has_mips3d
#define cpu_has_mips3d		0
#endif
#ifndef cpu_has_smartmips
#define cpu_has_smartmips	0
#endif
#ifndef cpu_has_rixi
#define cpu_has_rixi		0
#endif
#ifndef cpu_has_mmips
#define cpu_has_mmips		0
#endif
#ifndef cpu_has_vtag_icache
#define cpu_has_vtag_icache	0
#endif
#ifndef cpu_has_dc_aliases
#define cpu_has_dc_aliases	0
#endif
#ifndef cpu_has_ic_fills_f_dc
#define cpu_has_ic_fills_f_dc	0
#endif
#ifndef cpu_has_pindexed_dcache
#define cpu_has_pindexed_dcache	1
#endif
#ifndef cpu_has_local_ebase
#define cpu_has_local_ebase	0
#endif

/*
 * I-Cache snoops remote store.	 This only matters on SMP.  Some multiprocessors
 * such as the R10000 have I-Caches that snoop local stores; the embedded ones
 * don't.  For maintaining I-cache coherency this means we need to flush the
 * D-cache all the way back to whever the I-cache does refills from, so the
 * I-cache has a chance to see the new data at all.  Then we have to flush the
 * I-cache also.
 * Note we may have been rescheduled and may no longer be running on the CPU
 * that did the store so we can't optimize this into only doing the flush on
 * the local CPU.
 */
#ifndef cpu_icache_snoops_remote_store
#ifdef CONFIG_SMP
#define cpu_icache_snoops_remote_store	0
#else
#define cpu_icache_snoops_remote_store	1
#endif
#endif

#ifndef cpu_has_mips_1
#define cpu_has_mips_1		1
#endif
#ifndef cpu_has_mips_2
#define cpu_has_mips_2		0
#endif
#ifndef cpu_has_mips_3
#define cpu_has_mips_3		0
#endif
#ifndef cpu_has_mips_4
#define cpu_has_mips_4		0
#endif
#ifndef cpu_has_mips_5
#define cpu_has_mips_5		0
#endif
#ifndef cpu_has_mips32r1
#define cpu_has_mips32r1	0
#endif
#ifndef cpu_has_mips32r2
#define cpu_has_mips32r2	0
#endif
#ifndef cpu_has_mips64r1
#define cpu_has_mips64r1	0
#endif
#ifndef cpu_has_mips64r2
#define cpu_has_mips64r2	0
#endif

/*
 * Shortcuts ...
 */
#define cpu_has_mips32	(cpu_has_mips32r1 | cpu_has_mips32r2)
#define cpu_has_mips64	(cpu_has_mips64r1 | cpu_has_mips64r2)
#define cpu_has_mips_r1 (cpu_has_mips32r1 | cpu_has_mips64r1)
#define cpu_has_mips_r2 (cpu_has_mips32r2 | cpu_has_mips64r2)
#define cpu_has_mips_r	(cpu_has_mips32r1 | cpu_has_mips32r2 | \
			 cpu_has_mips64r1 | cpu_has_mips64r2)

#ifndef cpu_has_mips_r2_exec_hazard
#define cpu_has_mips_r2_exec_hazard cpu_has_mips_r2
#endif

/*
 * MIPS32, MIPS64, VR5500, IDT32332, IDT32334 and maybe a few other
 * pre-MIPS32/MIPS53 processors have CLO, CLZ.	The IDT RC64574 is 64-bit and
 * has CLO and CLZ but not DCLO nor DCLZ.  For 64-bit kernels
 * cpu_has_clo_clz also indicates the availability of DCLO and DCLZ.
 */
#ifndef cpu_has_clo_clz
#define cpu_has_clo_clz	cpu_has_mips_r
#endif

#ifdef CONFIG_CPU_HAS_CLS
#define cpu_has_cls			1
#else
#define cpu_has_cls			0
#endif

#ifndef cpu_has_dsp
#define cpu_has_dsp			0
#endif

#ifndef cpu_has_dsp2
#define cpu_has_dsp2			0
#endif

#ifndef cpu_has_mipsmt
#define cpu_has_mipsmt			0
#endif

#ifdef CONFIG_CPU_HAS_TLS
#define cpu_has_userlocal		1
#else
#define cpu_has_userlocal		0
#endif

#ifdef CONFIG_32BIT
# ifdef CONFIG_CPU_HAS_FPU
# define cpu_has_nofpuex		0
# else
# define cpu_has_nofpuex		1
# endif
# ifndef cpu_has_64bits
# define cpu_has_64bits			0
# endif
# ifndef cpu_has_64bit_zero_reg
# define cpu_has_64bit_zero_reg		0
# endif
# ifndef cpu_has_64bit_gp_regs
# define cpu_has_64bit_gp_regs		0
# endif
# ifndef cpu_has_64bit_addresses
# define cpu_has_64bit_addresses	0
# endif
# ifndef cpu_vmbits
# define cpu_vmbits 31
# endif
#endif

#ifdef CONFIG_64BIT
# ifndef cpu_has_nofpuex
# define cpu_has_nofpuex		0
# endif
# ifndef cpu_has_64bits
# define cpu_has_64bits			1
# endif
# ifndef cpu_has_64bit_zero_reg
# define cpu_has_64bit_zero_reg		1
# endif
# ifndef cpu_has_64bit_gp_regs
# define cpu_has_64bit_gp_regs		1
# endif
# ifndef cpu_has_64bit_addresses
# define cpu_has_64bit_addresses	1
# endif
# ifndef cpu_vmbits
# define cpu_vmbits cpu_data[0].vmbits
# define __NEED_VMBITS_PROBE
# endif
#endif

#ifdef CONFIG_CPU_MIPSR2_IRQ_VI
# define cpu_has_vint			1
#else
# define cpu_has_vint			0
#endif

#ifdef CONFIG_CPU_MIPSR2_IRQ_EI
# define cpu_has_veic			1
#else
# define cpu_has_veic			0
#endif

#ifndef cpu_has_inclusive_pcaches
#define cpu_has_inclusive_pcaches	0
#endif

#ifndef cpu_dcache_line_size
#define cpu_dcache_line_size()		cpu_dcache_line
#endif
#ifndef cpu_icache_line_size
#define cpu_icache_line_size()		cpu_icache_line
#endif
#ifndef cpu_scache_line_size
#define cpu_scache_line_size()		cpu_scache_line
#endif

#ifndef cpu_scache_line
#define cpu_scache_line			0
#endif

#ifndef cpu_dcache_line
#define cpu_dcache_line			0
#endif

#ifndef cpu_icache_line
#define cpu_icache_line			0
#endif

#ifndef cpu_scache_size
#define cpu_scache_size			0
#endif

#ifndef cpu_dcache_size
#define cpu_dcache_size			0
#endif

#ifndef cpu_icache_size
#define cpu_icache_size			0
#endif

#ifndef cpu_tlb_entry
#define cpu_tlb_entry			0
#endif

#ifndef cpu_hwrena_impl_bits
#define cpu_hwrena_impl_bits		0
#endif

#ifndef cpu_has_perf_cntr_intr_bit
#define cpu_has_perf_cntr_intr_bit	0
#endif

#ifndef cpu_has_vz
#define cpu_has_vz			0
#endif

#endif /* __ASM_CPU_FEATURES_H */
