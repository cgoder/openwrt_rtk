/*
 * Realtek Semiconductor Corp.
 *
 * arch/rlx/include/asm/mmcr.h:
 * Taroko MP MMCR definitions and marcos
 *
 * Copyright 2012 Tony Wu (tonywu@realtek.com)
 */
#ifndef _ASM_MMCR_H_
#define _ASM_MMCR_H_

#ifdef BSP_MMCR_BASE
#define MMCR_BASE		BSP_MMCR_BASE
#else
#define MMCR_BASE		0xbfbfa000
#endif

/* MMCR accessors */
#define _MMSK(n)		((1 << (n)) - 1)
#define _MR32(addr,offs)	(*(volatile unsigned int *) ((addr) + (offs)))

#define MMCR_SHF(reg,bit)	(MMCR_##reg##_##bit##_SHF)
#define MMCR_MSK(reg,bit)	(_MMSK(MMCR_##reg##_##bit##_BIT) << MMCR_SHF(reg,bit))
#define MMCR_REG32(reg)		_MR32(MMCR_BASE, MMCR_##reg##_OFS)
#define MMCR_REG32p(reg,p)	_MR32(MMCR_BASE, MMCR_##reg##_OFS + p)

#define MMCR_VAL32(reg,bit)	((MMCR_REG32(reg) & MMCR_MSK(reg,bit)) >> MMCR_SHF(reg,bit))
#define MMCR_VAL32p(reg,p,bit)	((MMCR_REG32p(reg,p) & MMCR_MSK(reg,bit)) >> MMCR_SHF(reg,bit))

/* Core registers */
#define MMCR_CORE_OFS			0x0008	/* Core Register */
#define  MMCR_CORE_CPUNUM_SHF		0
#define  MMCR_CORE_CPUNUM_BIT		4
#define  MMCR_CORE_NUMCORES_SHF		4
#define  MMCR_CORE_NUMCORES_BIT		4
#define  MMCR_CORE_NUMINTS_SHF		16
#define  MMCR_CORE_NUMINTS_BIT		9
#define MMCR_CORESTATE_OFS		0x0010	/* Core State 0 Register */
#define MMCR_CORESTATE0_OFS		0x0010	/* Core State 0 Register */
#define MMCR_CORESTATE1_OFS		0x0014	/* Core State 1 Register */
#define MMCR_CORESTATE2_OFS		0x0018	/* Core State 2 Register */
#define MMCR_CORESTATE3_OFS		0x001c	/* Core State 3 Register */
#define  MMCR_CORESTATE_ONLINE_SHF	0
#define  MMCR_CORESTATE_ONLINE_BIT	4
#define  MMCR_CORESTATE_COHERENT_SHF	8
#define  MMCR_CORESTATE_COHERENT_BIT	4
#define  MMCR_CORESTATE_SLEEPING_SHF	16
#define  MMCR_CORESTATE_SLEEPING_BIT	4
#define MMCR_CORE_ENTRY_OFS		0x0018	/* Core Entry Register */
#define MMCR_SMMU_CCA_OFS		0x0020	/* SMMU CCA Register */

/* CCU registers */
#define MMCR_CCU_BWSLOT_OFS		0x0300	/* CCU bandwidth slot register */
#define MMCR_CCU_FLAG_OFS		0x0308	/* CCU flag register */
#define MMCR_CCU_CONTROL_OFS		0x0310	/* CCU control register */

/* CAP registers */
#define MMCR_CAP_CONTROL_OFS		0x0400	/* CAP control register */

/* L2C registers */
#define MMCR_L2C_CTRL_OFS		0x0500	/* L2C control register */
#define  MMCR_L2C_CTRL_L2C_SHF		0
#define  MMCR_L2C_CTRL_L2C_BIT		1
#define  MMCR_L2C_CTRL_L2M_SHF		1
#define  MMCR_L2C_CTRL_L2M_BIT		1

/* MP registers */
#define MMCR_MP_PERF_OFS		0x0800	/* MP perf counter control register */
#define MMCR_MP_COUNTER_OFS		0x0810	/* MP perf counter0 register */
#define MMCR_MP_COUNTER0_OFS		0x0810	/* MP perf counter0 register */
#define MMCR_MP_COUNTER1_OFS		0x0818	/* MP perf counter1 register */
#define MMCR_MP_COUNTER2_OFS		0x0820	/* MP perf counter2 register */
#define MMCR_MP_COUNTER3_OFS		0x0828	/* MP perf counter3 register */

/* GIC registers */
/* defined in gic.h */

#ifndef __ASSEMBLY__
extern void mmcr_init_core(unsigned int);
#endif
#endif /* _ASM_MMCR_H */
