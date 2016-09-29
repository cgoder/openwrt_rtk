#
# Makefile for MIPS-specific library files..
#

lib-y	+= bitops.o csum_partial.o delay.o memcpy.o memset.o \
	   mips-atomic.o strlen_user.o strncpy_user.o \
	   strnlen_user.o uncached.o

obj-y			+= iomap.o
obj-$(CONFIG_PCI)	+= iomap-pci.o

obj-y			+= rlx_dump_tlb.o

# libgcc-style stuff needed in the kernel
obj-y += ashldi3.o ashrdi3.o cmpdi2.o lshrdi3.o ucmpdi2.o
