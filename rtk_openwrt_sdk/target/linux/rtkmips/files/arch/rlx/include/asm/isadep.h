/*
 * Various ISA level dependent constants.
 * Most of the following constants reflect the different layout
 * of Coprocessor 0 registers.
 *
 * Copyright (c) 1998 Harald Koerfgen
 */

#ifndef __ASM_ISADEP_H
#define __ASM_ISADEP_H

/*
 * R2000 or R3000
 */

/*
 * kernel or user mode? (CP0_STATUS)
 */
#define KU_MASK 0x08
#define KU_USER 0x08
#define KU_KERN 0x00

#endif /* __ASM_ISADEP_H */
