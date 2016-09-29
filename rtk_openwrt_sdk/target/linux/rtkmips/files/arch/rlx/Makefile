#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 1994, 95, 96, 2003 by Ralf Baechle
# DECStation modifications by Paul M. Antoine, 1996
# Copyright (C) 2002, 2003, 2004  Maciej W. Rozycki
#
# Modified for RLX Linux for RLX
# Copyright (C) 2008-2011 Tony Wu (tonywu@realtek.com)
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies. Remember to do have actions
# for "archclean" cleaning up for this architecture.
#

KBUILD_DEFCONFIG := rlx_defconfig

#
# Select the object file format to substitute into the linker script.
#
ifdef CONFIG_CPU_LITTLE_ENDIAN
32bit-tool-archpref	= mips
32bit-bfd		= elf32-tradlittlemips
32bit-emul		= elf32ltsmip
else
32bit-tool-archpref	= mips
32bit-bfd		= elf32-tradbigmips
32bit-emul		= elf32btsmip
endif

ifdef CONFIG_32BIT
tool-archpref		= $(32bit-tool-archpref)
UTS_MACHINE		:= rlx
endif

ifneq ($(SUBARCH),$(ARCH))
  ifeq ($(CROSS_COMPILE),)
    CROSS_COMPILE := $(call cc-cross-prefix, $(tool-archpref)-linux-)
  endif
endif

ifdef CONFIG_FUNCTION_GRAPH_TRACER
  ifndef KBUILD_MCOUNT_RA_ADDRESS
    ifeq ($(call cc-option-yn,-mmcount-ra-address), y)
      cflags-y += -mmcount-ra-address -DKBUILD_MCOUNT_RA_ADDRESS
    endif
  endif
endif
cflags-y += $(call cc-option, -mno-check-zero-division)

ifdef CONFIG_32BIT
ld-emul			= $(32bit-emul)
vmlinux-32		= vmlinux
vmlinux-64		= vmlinux.64

cflags-y		+= -mabi=32
endif

ifdef CONFIG_64BIT
ld-emul			= $(64bit-emul)
vmlinux-32		= vmlinux.32
vmlinux-64		= vmlinux

cflags-y		+= -mabi=64
endif

all-$(CONFIG_BOOT_ELF32)	:= $(vmlinux-32)
all-$(CONFIG_BOOT_ELF64)	:= $(vmlinux-64)
all-$(CONFIG_SYS_SUPPORTS_ZBOOT)+= vmlinuz

#
# GCC uses -G 0 -mabicalls -fpic as default.  We don't want PIC in the kernel
# code since it only slows down the whole thing.  At some point we might make
# use of global pointer optimizations but their use of $28 conflicts with
# the current pointer optimization.
#
# The DECStation requires an ECOFF kernel for remote booting, other MIPS
# machines may also.  Since BFD is incredibly buggy with respect to
# crossformat linking we rely on the elf2ecoff tool for format conversion.
#
cflags-y			+= -G 0 -mno-abicalls -fno-pic -pipe
LDFLAGS_vmlinux			+= -G 0 -static -n -nostdlib --gc-sections
KBUILD_AFLAGS_MODULE		+= -mlong-calls
KBUILD_CFLAGS_MODULE		+= -mlong-calls

ifndef CONFIG_FUNCTION_TRACER
KBUILD_CFLAGS_KERNEL		+= -ffunction-sections -fdata-sections
endif

cflags-y += -ffreestanding

#
# We explicitly add the endianness specifier if needed, this allows
# to compile kernels with a toolchain for the other endianness. We
# carefully avoid to add it redundantly because gcc 3.3/3.4 complains
# when fed the toolchain default!
#
# Certain gcc versions up to gcc 4.1.1 (probably 4.2-subversion as of
# 2006-10-10 don't properly change the predefined symbols if -EB / -EL
# are used, so we kludge that here.  A bug has been filed at
# http://gcc.gnu.org/bugzilla/show_bug.cgi?id=29413.
#
undef-all += -UMIPSEB -U_MIPSEB -U__MIPSEB -U__MIPSEB__
undef-all += -UMIPSEL -U_MIPSEL -U__MIPSEL -U__MIPSEL__
predef-be += -DMIPSEB -D_MIPSEB -D__MIPSEB -D__MIPSEB__
predef-le += -DMIPSEL -D_MIPSEL -D__MIPSEL -D__MIPSEL__
cflags-$(CONFIG_CPU_BIG_ENDIAN)		+= -EB $(undef-all) $(predef-be)
cflags-$(CONFIG_CPU_LITTLE_ENDIAN)	+= -EL $(undef-all) $(predef-le)

#
# Firmware support
#
libs-y				+= arch/rlx/fw/lib/

#
# Kernel compression
#
ifdef SYS_SUPPORTS_ZBOOT
COMPRESSION_FNAME		= vmlinuz
else
COMPRESSION_FNAME		= vmlinux
endif

#
# Board-dependent options and extra files
#
soc-$(CONFIG_SOC_RTL8196C) := rtl8196c
soc-$(CONFIG_SOC_RTL8196E) := rtl8196e
soc-$(CONFIG_SOC_RTL819XD) := rtl819xd
soc-$(CONFIG_SOC_RTL8881A) := rtl8881a

ifneq ($(soc-y),)
ARCH_SOC := $(patsubst %,soc-%,$(soc-y))
else
ARCH_SOC :=
endif

# add DIR_LINUX for realtek drivers
export DIR_LINUX := $(srctree)

# specified soc
core-y += arch/rlx/$(ARCH_SOC)/

# default include
cflags-y += -I$(srctree)/arch/rlx/
cflags-y += -I$(srctree)/arch/rlx/$(ARCH_SOC)/
cflags-y += -Iinclude/asm-rlx -I$(srctree)/arch/rlx/include/asm/mach-generic

# platform specified load-y, cflags, or...
include $(patsubst %, $(srctree)/arch/rlx/%/Platform, $(ARCH_SOC))

drivers-$(CONFIG_PCI) += arch/rlx/pci/

ifdef CONFIG_PHYSICAL_START
load-y				= $(CONFIG_PHYSICAL_START)
endif


#
# Automatically detect the build format. By default we choose
# the elf format according to the load address.
# We can always force a build with a 64-bits symbol format by
# passing 'KBUILD_SYM32=no' option to the make's command line.
#
ifdef CONFIG_64BIT
  ifndef KBUILD_SYM32
    ifeq ($(shell expr $(load-y) \< 0xffffffff80000000), 0)
      KBUILD_SYM32 = y
    endif
  endif

  ifeq ($(KBUILD_SYM32)$(call cc-option-yn,-msym32), yy)
    cflags-y += -msym32 -DKBUILD_64BIT_SYM32
  else
    ifeq ($(CONFIG_CPU_DADDI_WORKAROUNDS), y)
      $(error CONFIG_CPU_DADDI_WORKAROUNDS unsupported without -msym32)
    endif
  endif
endif

KBUILD_AFLAGS	+= $(cflags-y)
KBUILD_CFLAGS	+= $(cflags-y)
KBUILD_CPPFLAGS += -DVMLINUX_LOAD_ADDRESS=$(load-y)
KBUILD_CPPFLAGS += -DDATAOFFSET=$(if $(dataoffset-y),$(dataoffset-y),0)

LDFLAGS			+= -m $(ld-emul)

ifdef CONFIG_MIPS
CHECKFLAGS += $(shell $(CC) $(KBUILD_CFLAGS) -dM -E -x c /dev/null | \
	egrep -vw '__GNUC_(|MINOR_|PATCHLEVEL_)_' | \
	sed -e "s/^\#define /-D'/" -e "s/ /'='/" -e "s/$$/'/")
ifdef CONFIG_64BIT
CHECKFLAGS		+= -m64
endif
endif

OBJCOPYFLAGS		+= --remove-section=.reginfo

head-y := arch/rlx/kernel/head.o

libs-y			+= arch/rlx/lib/

# See arch/rlx/Kbuild for content of core part of the kernel
core-y += arch/rlx/

drivers-$(CONFIG_OPROFILE)	+= arch/rlx/oprofile/

# suspend and hibernation support
drivers-$(CONFIG_PM)	+= arch/rlx/power/

#
# Some machines like the Indy need 32-bit ELF binaries for booting purposes.
# Other need ECOFF, so we build a 32-bit ELF binary for them which we then
# convert to ECOFF using elf2ecoff.
#
vmlinux.32: vmlinux
	$(OBJCOPY) -O $(32bit-bfd) $(OBJCOPYFLAGS) $< $@


#obj-$(CONFIG_KPROBES)		+= kprobes.o

#
# The 64-bit ELF tools are pretty broken so at this time we generate 64-bit
# ELF files from 32-bit files by conversion.
#
vmlinux.64: vmlinux
	$(OBJCOPY) -O $(64bit-bfd) $(OBJCOPYFLAGS) $< $@

all:	$(all-y)

# boot
vmlinux.bin vmlinux.ecoff vmlinux.srec: $(vmlinux-32) FORCE
	$(Q)$(MAKE) $(build)=arch/rlx/boot VMLINUX=$(vmlinux-32) arch/rlx/boot/$@

# boot/compressed
vmlinuz vmlinuz.bin vmlinuz.ecoff vmlinuz.srec: $(vmlinux-32) FORCE
	$(Q)$(MAKE) $(build)=arch/rlx/boot/compressed \
	   VMLINUX_LOAD_ADDRESS=$(load-y) 32bit-bfd=$(32bit-bfd) $@


CLEAN_FILES += vmlinux.32 vmlinux.64

archprepare:
ifdef CONFIG_MIPS32_N32
	@echo '  Checking missing-syscalls for N32'
	$(Q)$(MAKE) $(build)=. missing-syscalls missing_syscalls_flags="-mabi=n32"
endif
ifdef CONFIG_MIPS32_O32
	@echo '  Checking missing-syscalls for O32'
	$(Q)$(MAKE) $(build)=. missing-syscalls missing_syscalls_flags="-mabi=32"
endif
	ln -fsn $(ARCH_SOC) arch/rlx/bsp

archmrproper:
	rm -f arch/rlx/bsp

install:
	$(Q)install -D -m 755 vmlinux $(INSTALL_PATH)/vmlinux-$(KERNELRELEASE)
ifdef CONFIG_SYS_SUPPORTS_ZBOOT
	$(Q)install -D -m 755 vmlinuz $(INSTALL_PATH)/vmlinuz-$(KERNELRELEASE)
endif
	$(Q)install -D -m 644 .config $(INSTALL_PATH)/config-$(KERNELRELEASE)
	$(Q)install -D -m 644 System.map $(INSTALL_PATH)/System.map-$(KERNELRELEASE)

archclean:
	$(Q)$(MAKE) $(clean)=arch/rlx/boot
	$(Q)$(MAKE) $(clean)=arch/rlx/boot/compressed

define archhelp
	echo '  install              - install kernel into $(INSTALL_PATH)'
	echo '  vmlinux.ecoff        - ECOFF boot image'
	echo '  vmlinux.bin          - Raw binary boot image'
	echo '  vmlinux.srec         - SREC boot image'
	echo '  vmlinuz              - Compressed boot(zboot) image'
	echo '  vmlinuz.ecoff        - ECOFF zboot image'
	echo '  vmlinuz.bin          - Raw binary zboot image'
	echo '  vmlinuz.srec         - SREC zboot image'
	echo
	echo '  These will be default as appropriate for a configured platform.'
endef
