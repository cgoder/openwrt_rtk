	.file	1 "fast_l2tp_core.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
	.align	2
	.set	nomips16
	.ent	get_fast_l2tp_lastxmit
	.type	get_fast_l2tp_lastxmit, @function
get_fast_l2tp_lastxmit:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$2,%hi(l2tpInfo)
	li	$3,1			# 0x1
	addiu	$2,$2,%lo(l2tpInfo)
	lhu	$4,38($2)
	bne	$4,$3,$L3
	nop

	lw	$2,8($2)
	j	$31
	nop

$L3:
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	get_fast_l2tp_lastxmit
	.size	get_fast_l2tp_lastxmit, .-get_fast_l2tp_lastxmit
	.align	2
	.set	nomips16
	.ent	check_for_fast_l2tp_to_wan
	.type	check_for_fast_l2tp_to_wan, @function
check_for_fast_l2tp_to_wan:
	.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$16,%hi(rtl_ip_hdr)
	addiu	$16,$16,%lo(rtl_ip_hdr)
	jalr	$16
	move	$17,$4

	jalr	$16
	move	$4,$17

	lw	$3,12($2)
	li	$2,-256			# 0xffffffffffffff00
	lw	$31,28($sp)
	and	$2,$3,$2
	li	$3,-172032000			# 0xfffffffff5bf0000
	ori	$3,$3,0xc000
	lw	$17,24($sp)
	addu	$2,$2,$3
	lw	$16,20($sp)
	sltu	$2,$0,$2
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	check_for_fast_l2tp_to_wan
	.size	check_for_fast_l2tp_to_wan, .-check_for_fast_l2tp_to_wan
	.align	2
	.set	nomips16
	.ent	is_l2tp_device
	.type	is_l2tp_device, @function
is_l2tp_device:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(l2tpInfo+4)
	move	$16,$4
	lw	$4,%lo(l2tpInfo+4)($2)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L8
	lui	$2,%hi(rtl_get_ppp_dev_name)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_get_ppp_dev_name)
	jalr	$2
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$3,($2)
1:	lbu	$1,($16)
	addiu	$2,1
	bne	$1,$3,2f
	addiu	$16,1
	bnez	$3,1b
	lbu	$3,($2)
	move	$3,$1
2:	subu	$3,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	j	$L7
	sltu	$2,$3,1
	.set	macro
	.set	reorder

$L8:
	move	$2,$0
$L7:
	lw	$31,20($sp)
	lw	$16,16($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,24
	.set	macro
	.set	reorder

	.end	is_l2tp_device
	.size	is_l2tp_device, .-is_l2tp_device
	.align	2
	.globl	fastpath_l2tp_single_open
	.set	nomips16
	.ent	fastpath_l2tp_single_open
	.type	fastpath_l2tp_single_open, @function
fastpath_l2tp_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	move	$4,$5
	lui	$25,%hi(single_open)
	lui	$5,%hi(l2tp_read_proc)
	move	$6,$0
	addiu	$5,$5,%lo(l2tp_read_proc)
	addiu	$25,$25,%lo(single_open)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	fastpath_l2tp_single_open
	.size	fastpath_l2tp_single_open, .-fastpath_l2tp_single_open
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"%c\012\000"
	.text
	.align	2
	.set	nomips16
	.ent	l2tp_read_proc
	.type	l2tp_read_proc, @function
l2tp_read_proc:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$2,%hi(fast_l2tp_fw)
	lw	$6,%lo(fast_l2tp_fw)($2)
	lui	$5,%hi($LC0)
	lui	$2,%hi(seq_printf)
	addiu	$5,$5,%lo($LC0)
	addiu	$2,$2,%lo(seq_printf)
	jalr	$2
	addiu	$6,$6,48

	move	$2,$0
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	l2tp_read_proc
	.size	l2tp_read_proc, .-l2tp_read_proc
	.section	.rodata.str1.4
	.align	2
$LC1:
	.ascii	"ppp0\000"
	.align	2
$LC2:
	.ascii	"eth1\000"
	.align	2
$LC3:
	.ascii	"wlan\000"
	.text
	.align	2
	.globl	l2tp_tx_id
	.set	nomips16
	.ent	l2tp_tx_id
	.type	l2tp_tx_id, @function
l2tp_tx_id:
	.frame	$sp,40,$31		# vars= 0, regs= 5/0, args= 16, gp= 0
	.mask	0x800f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$2,%hi(rtl_get_skb_data)
	addiu	$2,$2,%lo(rtl_get_skb_data)
	jalr	$2
	move	$16,$4

	move	$17,$2
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	move	$4,$16

	beq	$2,$0,$L11
	li	$5,1701			# 0x6a5

	lbu	$3,0($2)
	andi	$3,$3,0xf
	sll	$3,$3,2
	addu	$3,$2,$3
	lhu	$4,0($3)
	bne	$4,$5,$L11
	nop

	lhu	$5,2($3)
	bne	$5,$4,$L11
	nop

	lhu	$4,8($3)
	sll	$5,$4,16
	sra	$5,$5,16
	bgez	$5,$L13
	andi	$4,$4,0x4000

	bne	$4,$0,$L14
	nop

	j	$L15
	addiu	$3,$3,10

$L14:
	addiu	$3,$3,12
$L15:
	lhu	$4,14($3)
	li	$5,4			# 0x4
	bne	$4,$5,$L16
	li	$5,11			# 0xb

	lui	$4,%hi(l2tpInfo)
	addiu	$4,$4,%lo(l2tpInfo)
	lhu	$5,20($4)
	lhu	$2,0($3)
	bne	$5,$2,$L11
	lui	$2,%hi(memset)

	move	$5,$0
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,40			# 0x28

	lui	$4,%hi($LC1)
	lui	$2,%hi(rtl865x_setNetifType)
	addiu	$4,$4,%lo($LC1)
	addiu	$2,$2,%lo(rtl865x_setNetifType)
	jalr	$2
	li	$5,2			# 0x2

	lui	$2,%hi(state)
	j	$L11
	sw	$0,%lo(state)($2)

$L16:
	bne	$4,$5,$L17
	lui	$18,%hi(state)

	lw	$2,%lo(state)($18)
	bne	$2,$0,$L11
	lui	$19,%hi(rtl865x_curOpMode)

	lw	$2,%lo(rtl865x_curOpMode)($19)
	bne	$2,$0,$L32
	li	$3,2			# 0x2

	lui	$2,%hi(rtl_get_skb_dev_name)
	addiu	$2,$2,%lo(rtl_get_skb_dev_name)
	jalr	$2
	move	$4,$16

	lui	$5,%hi($LC2)
	move	$4,$2
	lui	$2,%hi(memcmp)
	addiu	$5,$5,%lo($LC2)
	addiu	$2,$2,%lo(memcmp)
	jalr	$2
	li	$6,4			# 0x4

	beq	$2,$0,$L33
	lui	$2,%hi(rtl_get_skb_dev)

	lw	$2,%lo(rtl865x_curOpMode)($19)
	li	$3,2			# 0x2
$L32:
	bne	$2,$3,$L11
	lui	$2,%hi(rtl_get_skb_dev_name)

	addiu	$2,$2,%lo(rtl_get_skb_dev_name)
	jalr	$2
	move	$4,$16

	lui	$5,%hi($LC3)
	move	$4,$2
	lui	$2,%hi(memcmp)
	addiu	$5,$5,%lo($LC3)
	addiu	$2,$2,%lo(memcmp)
	jalr	$2
	li	$6,4			# 0x4

	bne	$2,$0,$L11
	lui	$2,%hi(rtl_get_skb_dev)

$L33:
	move	$4,$16
	addiu	$2,$2,%lo(rtl_get_skb_dev)
	jalr	$2
	lui	$16,%hi(memcpy)

	lui	$3,%hi(l2tpInfo)
	lui	$4,%hi(l2tpInfo+24)
	addiu	$16,$16,%lo(memcpy)
	sw	$2,%lo(l2tpInfo)($3)
	addiu	$4,$4,%lo(l2tpInfo+24)
	addiu	$5,$17,-8
	jalr	$16
	li	$6,6			# 0x6

	lui	$4,%hi(l2tpInfo+30)
	addiu	$4,$4,%lo(l2tpInfo+30)
	addiu	$5,$17,-14
	jalr	$16
	li	$6,6			# 0x6

	lui	$4,%hi(l2tpInfo+36)
	addiu	$4,$4,%lo(l2tpInfo+36)
	addiu	$5,$17,-2
	jalr	$16
	li	$6,2			# 0x2

	li	$2,1			# 0x1
	j	$L11
	sw	$2,%lo(state)($18)

$L17:
	li	$5,12			# 0xc
	bne	$4,$5,$L11
	nop

	lhu	$4,2($3)
	beq	$4,$0,$L11
	lui	$17,%hi(state)

	lw	$4,%lo(state)($17)
	sltu	$4,$4,2
	beq	$4,$0,$L11
	lui	$18,%hi(l2tpInfo)

	lhu	$4,0($3)
	addiu	$18,$18,%lo(l2tpInfo)
	sh	$4,20($18)
	lhu	$3,2($3)
	sh	$3,22($18)
	lw	$3,12($2)
	sw	$3,16($18)
	lw	$2,16($2)
	move	$4,$2
	sw	$2,12($18)
	lui	$2,%hi(filter_addconnect)
	addiu	$2,$2,%lo(filter_addconnect)
	jalr	$2
	nop

	li	$2,1			# 0x1
	sh	$2,38($18)
	lui	$4,%hi($LC1)
	lui	$2,%hi(rtl865x_setNetifType)
	addiu	$4,$4,%lo($LC1)
	addiu	$2,$2,%lo(rtl865x_setNetifType)
	jalr	$2
	li	$5,4			# 0x4

	li	$2,2			# 0x2
	j	$L11
	sw	$2,%lo(state)($17)

$L27:
	addiu	$16,$3,10
$L31:
	lui	$18,%hi(l2tpInfo)
	lui	$2,%hi(filter_checkConnect)
	addiu	$17,$18,%lo(l2tpInfo)
	addiu	$2,$2,%lo(filter_checkConnect)
	lw	$4,12($17)
	jalr	$2
	nop

	beq	$2,$0,$L21
	lui	$2,%hi(filter_addconnect)

	lw	$4,12($17)
	addiu	$2,$2,%lo(filter_addconnect)
	jalr	$2
	nop

$L21:
	lhu	$3,6($16)
	li	$2,49185			# 0xc021
	bne	$3,$2,$L11
	li	$3,5			# 0x5

	lbu	$2,8($16)
	bne	$2,$3,$L34
	li	$3,6			# 0x6

	lui	$2,%hi(memset)
	addiu	$4,$18,%lo(l2tpInfo)
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,40			# 0x28

	lui	$3,%hi(state)
	lbu	$2,8($16)
	sw	$0,%lo(state)($3)
	li	$3,6			# 0x6
$L34:
	bne	$2,$3,$L35
	li	$3,1			# 0x1

	lhu	$3,20($17)
	lhu	$2,0($16)
	bne	$3,$2,$L11
	nop

	lhu	$3,22($17)
	lhu	$2,2($16)
	bne	$3,$2,$L11
	lui	$2,%hi(memset)

	move	$4,$17
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,40			# 0x28

	lui	$3,%hi(state)
	lbu	$2,8($16)
	sw	$0,%lo(state)($3)
	li	$3,1			# 0x1
$L35:
	bne	$2,$3,$L11
	addiu	$7,$16,8

	li	$2,4			# 0x4
	lhu	$6,10($16)
	j	$L24
	li	$8,5			# 0x5

$L26:
	lbu	$4,0($3)
	lbu	$5,1($3)
	bne	$4,$8,$L25
	addu	$2,$2,$5

	lw	$3,2($3)
	lui	$2,%hi(l2tp_ppp_imagic)
	j	$L11
	sw	$3,%lo(l2tp_ppp_imagic)($2)

$L25:
$L24:
	slt	$4,$2,$6
	bne	$4,$0,$L26
	addu	$3,$7,$2

	j	$L11
	nop

$L13:
	beq	$4,$0,$L27
	addiu	$16,$3,12

	j	$L31
	nop

$L11:
	lw	$31,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	l2tp_tx_id
	.size	l2tp_tx_id, .-l2tp_tx_id
	.align	2
	.set	nomips16
	.ent	fastpath_l2tp_single_write
	.type	fastpath_l2tp_single_write, @function
fastpath_l2tp_single_write:
	.frame	$sp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$16,24($sp)
	sltu	$3,$6,2
	.set	noreorder
	.set	nomacro
	bne	$3,$0,$L43
	move	$16,$6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L43
	addiu	$3,$5,1
	.set	macro
	.set	reorder

	or	$2,$3,$5
	lw	$3,24($28)
	and	$2,$2,$3
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L43
	addiu	$4,$sp,16
	.set	macro
	.set	reorder

	li	$6,1			# 0x1
 #APP
 # 722 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/fastpath-0.1/fast_l2tp_core.c" 1
	.set	noreorder
	.set	noat
	la	$1, __copy_user
	jalr	$1
	.set	at
	.set	noat
	addu	$1, $5, $6
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$6,$0,$L43
	lui	$3,%hi(fast_l2tp_fw)
	.set	macro
	.set	reorder

	lb	$2,16($sp)
	addiu	$2,$2,-48
	sw	$2,%lo(fast_l2tp_fw)($3)
	li	$3,1			# 0x1
	.set	noreorder
	.set	nomacro
	bne	$2,$3,$L38
	lui	$4,%hi(l2tpInfo)
	.set	macro
	.set	reorder

	lui	$3,%hi(l2tp_tx_id)
	lui	$2,%hi(l2tp_tx_id_hook)
	addiu	$3,$3,%lo(l2tp_tx_id)
	.set	noreorder
	.set	nomacro
	j	$L39
	sw	$3,%lo(l2tp_tx_id_hook)($2)
	.set	macro
	.set	reorder

$L38:
	addiu	$2,$4,%lo(l2tpInfo)
	lui	$3,%hi(l2tp_tx_id_hook)
	sw	$0,%lo(l2tp_tx_id_hook)($3)
	sh	$0,20($2)
$L39:
	lui	$2,%hi(memset)
	addiu	$4,$4,%lo(l2tpInfo)
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,40			# 0x28
	.set	macro
	.set	reorder

	lui	$2,%hi(state)
	sw	$0,%lo(state)($2)
	.set	noreorder
	.set	nomacro
	j	$L37
	move	$2,$16
	.set	macro
	.set	reorder

$L43:
	li	$2,-14			# 0xfffffffffffffff2
$L37:
	lw	$31,28($sp)
	lw	$16,24($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,32
	.set	macro
	.set	reorder

	.end	fastpath_l2tp_single_write
	.size	fastpath_l2tp_single_write, .-fastpath_l2tp_single_write
	.align	2
	.set	nomips16
	.ent	fast_l2tp_to_wan
	.type	fast_l2tp_to_wan, @function
fast_l2tp_to_wan:
	.frame	$sp,88,$31		# vars= 40, regs= 8/0, args= 16, gp= 0
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-88
	sw	$31,84($sp)
	sw	$22,80($sp)
	sw	$21,76($sp)
	sw	$20,72($sp)
	sw	$19,68($sp)
	sw	$18,64($sp)
	sw	$17,60($sp)
	sw	$16,56($sp)
	lui	$2,%hi(fast_l2tp_fw)
	lw	$2,%lo(fast_l2tp_fw)($2)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L57
	move	$16,$4
	.set	macro
	.set	reorder

	lui	$18,%hi(l2tpInfo)
	addiu	$17,$18,%lo(l2tpInfo)
	lhu	$2,20($17)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L45
	move	$2,$0
	.set	macro
	.set	reorder

	lhu	$2,22($17)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L45
	move	$2,$0
	.set	macro
	.set	reorder

	lw	$2,%lo(l2tpInfo)($18)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L57
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

	lhu	$3,38($17)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L45
	move	$2,$0
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	lhu	$22,2($2)
	move	$20,$2
	lui	$2,%hi(rtl_skb_headroom)
	addiu	$2,$2,%lo(rtl_skb_headroom)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$16
	.set	macro
	.set	reorder

	sltu	$2,$2,52
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L62
	lui	$2,%hi(skb_realloc_headroom)
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_skb_cloned)
	addiu	$2,$2,%lo(rtl_skb_cloned)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L62
	lui	$2,%hi(skb_realloc_headroom)
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_skb_shared)
	addiu	$2,$2,%lo(rtl_skb_shared)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L58
	move	$19,$16
	.set	macro
	.set	reorder

	lui	$2,%hi(skb_realloc_headroom)
$L62:
	move	$4,$16
	addiu	$2,$2,%lo(skb_realloc_headroom)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,52			# 0x34
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L57
	move	$19,$2
	.set	macro
	.set	reorder

	lui	$2,%hi(consume_skb)
	addiu	$2,$2,%lo(consume_skb)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L61
	lui	$2,%hi(skb_push)
	.set	macro
	.set	reorder

$L58:
	lui	$2,%hi(skb_push)
$L61:
	li	$5,52			# 0x34
	move	$4,$19
	addiu	$2,$2,%lo(skb_push)
	lbu	$20,1($20)
	.set	noreorder
	.set	nomacro
	jalr	$2
	lui	$16,%hi(memcpy)
	.set	macro
	.set	reorder

	lui	$5,%hi(l2tpInfo+24)
	move	$4,$2
	li	$6,14			# 0xe
	addiu	$16,$16,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$16
	addiu	$5,$5,%lo(l2tpInfo+24)
	.set	macro
	.set	reorder

	li	$6,268369920			# 0xfff0000
	lw	$2,36($sp)
	ori	$6,$6,0xffff
	li	$4,-251723776			# 0xfffffffff0ff0000
	move	$5,$0
	and	$6,$2,$6
	li	$2,1073741824			# 0x40000000
	or	$6,$6,$2
	lw	$2,16($17)
	ori	$4,$4,0xffff
	lw	$3,12($17)
	and	$6,$6,$4
	li	$4,83886080			# 0x5000000
	or	$6,$6,$4
	sw	$2,48($sp)
	sw	$6,36($sp)
	li	$2,64			# 0x40
	li	$6,16384			# 0x4000
	move	$4,$19
	sh	$6,42($sp)
	li	$6,17			# 0x11
	sb	$2,44($sp)
	lui	$2,%hi(rtl_set_skb_ip_summed)
	sb	$6,45($sp)
	addiu	$2,$2,%lo(rtl_set_skb_ip_summed)
	sw	$3,52($sp)
	lui	$21,%hi(rtl_get_skb_len)
	sb	$20,37($sp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$21,$21,%lo(rtl_get_skb_len)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$21
	move	$4,$19
	.set	macro
	.set	reorder

	addiu	$3,$sp,52
	addiu	$2,$2,-14
	sh	$2,38($sp)
	sh	$0,40($sp)
	lw	$2,36($sp)
	lw	$7,40($sp)
	sh	$0,46($sp)
	srl	$5,$2,22
	lw	$4,44($sp)
	addu	$2,$7,$2
	lw	$6,48($sp)
	sltu	$7,$2,$7
	addu	$2,$2,$4
	andi	$5,$5,0x3c
	addu	$7,$2,$7
	addiu	$2,$sp,36
	sltu	$4,$7,$4
	addu	$7,$7,$6
	addu	$4,$7,$4
	addu	$5,$2,$5
	sltu	$2,$4,$6
	addu	$2,$2,$4
$L49:
	lw	$4,0($3)
	addiu	$3,$3,4
	addu	$2,$4,$2
	sltu	$4,$2,$4
	.set	noreorder
	.set	nomacro
	bne	$5,$3,$L49
	addu	$2,$4,$2
	.set	macro
	.set	reorder

	lui	$20,%hi(rtl_get_skb_data)
	move	$4,$19
	addiu	$20,$20,%lo(rtl_get_skb_data)
	addiu	$22,$22,18
 #APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_fold
	.set	noat		
	sll	$1, $2, 16	
	addu	$2, $1		
	sltu	$1, $2, $1	
	srl	$2, $2, 16	
	addu	$2, $1		
	xori	$2, 0xffff	
	.set	pop
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	jalr	$20
	sh	$2,46($sp)
	.set	macro
	.set	reorder

	li	$6,20			# 0x14
	addiu	$5,$sp,36
	.set	noreorder
	.set	nomacro
	jalr	$16
	addiu	$4,$2,14
	.set	macro
	.set	reorder

	li	$2,1701			# 0x6a5
	sh	$2,16($sp)
	move	$4,$19
	sh	$2,18($sp)
	li	$2,2			# 0x2
	lhu	$3,22($17)
	lhu	$5,20($17)
	sh	$2,24($sp)
	li	$2,-253			# 0xffffffffffffff03
	sh	$2,30($sp)
	li	$2,33			# 0x21
	sh	$3,28($sp)
	sh	$5,26($sp)
	sh	$22,20($sp)
	sh	$0,22($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	sh	$2,32($sp)
	.set	macro
	.set	reorder

	li	$6,18			# 0x12
	addiu	$5,$sp,16
	.set	noreorder
	.set	nomacro
	jalr	$16
	addiu	$4,$2,34
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_dev)
	lw	$5,%lo(l2tpInfo)($18)
	addiu	$2,$2,%lo(rtl_set_skb_dev)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$19
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$20
	move	$4,$19
	.set	macro
	.set	reorder

	addiu	$4,$2,52
	lui	$2,%hi(timeoutCheck_skipp_pkt)
	addiu	$2,$2,%lo(timeoutCheck_skipp_pkt)
	jalr	$2
	li	$3,1			# 0x1
	.set	noreorder
	.set	nomacro
	beq	$2,$3,$L50
	lui	$2,%hi(jiffies)
	.set	macro
	.set	reorder

	lw	$2,%lo(jiffies)($2)
	sw	$2,8($17)
$L50:
	lw	$4,4($17)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L51
	lui	$16,%hi(rtl_get_ppp_dev_priv)
	.set	macro
	.set	reorder

	addiu	$16,$16,%lo(rtl_get_ppp_dev_priv)
	jalr	$16
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L63
	lui	$2,%hi(gQosEnabled)
	.set	macro
	.set	reorder

	lw	$4,4($17)
	jalr	$16
	move	$4,$19
	.set	noreorder
	.set	nomacro
	jalr	$21
	move	$16,$2
	.set	macro
	.set	reorder

	move	$6,$2
	lui	$2,%hi(rtl_inc_ppp_stats)
	move	$4,$16
	addiu	$2,$2,%lo(rtl_inc_ppp_stats)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,1			# 0x1
	.set	macro
	.set	reorder

$L51:
	lui	$2,%hi(gQosEnabled)
$L63:
	lw	$2,%lo(gQosEnabled)($2)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L52
	move	$4,$19
	.set	macro
	.set	reorder

	lui	$2,%hi(dev_queue_xmit)
	addiu	$2,$2,%lo(dev_queue_xmit)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L45
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L52:
	lui	$2,%hi(rtl_call_skb_ndo_start_xmit)
	addiu	$2,$2,%lo(rtl_call_skb_ndo_start_xmit)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L45
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L57:
	move	$2,$0
$L45:
	lw	$31,84($sp)
	lw	$22,80($sp)
	lw	$21,76($sp)
	lw	$20,72($sp)
	lw	$19,68($sp)
	lw	$18,64($sp)
	lw	$17,60($sp)
	lw	$16,56($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,88
	.set	macro
	.set	reorder

	.end	fast_l2tp_to_wan
	.size	fast_l2tp_to_wan, .-fast_l2tp_to_wan
	.align	2
	.set	nomips16
	.ent	event_ppp_dev_down
	.type	event_ppp_dev_down, @function
event_ppp_dev_down:
	.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$17,%hi(l2tpInfo)
	addiu	$17,$17,%lo(l2tpInfo)
	lhu	$2,38($17)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L64
	move	$16,$4
	.set	macro
	.set	reorder

	lw	$4,4($17)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L64
	lui	$2,%hi(rtl_get_ppp_dev_name)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_get_ppp_dev_name)
	jalr	$2
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$3,($2)
1:	lbu	$1,($16)
	addiu	$2,1
	bne	$1,$3,2f
	addiu	$16,1
	bnez	$3,1b
	lbu	$3,($2)
	move	$3,$1
2:	subu	$3,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$3,$0,$L64
	lui	$2,%hi(memset)
	.set	macro
	.set	reorder

	move	$4,$17
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,40			# 0x28
	.set	macro
	.set	reorder

	lui	$2,%hi(state)
	sw	$0,%lo(state)($2)
$L64:
	lw	$31,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,32
	.set	macro
	.set	reorder

	.end	event_ppp_dev_down
	.size	event_ppp_dev_down, .-event_ppp_dev_down
	.align	2
	.set	nomips16
	.ent	set_l2tp_device
	.type	set_l2tp_device, @function
set_l2tp_device:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$2,%hi(fast_l2tp_fw)
	lw	$2,%lo(fast_l2tp_fw)($2)
	beq	$2,$0,$L66
	lui	$2,%hi(rtl_get_dev_by_name)

	addiu	$2,$2,%lo(rtl_get_dev_by_name)
	jalr	$2
	nop

	lui	$3,%hi(l2tpInfo+4)
	sw	$2,%lo(l2tpInfo+4)($3)
$L66:
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	set_l2tp_device
	.size	set_l2tp_device, .-set_l2tp_device
	.align	2
	.globl	fast_l2tp_rx
	.set	nomips16
	.ent	fast_l2tp_rx
	.type	fast_l2tp_rx, @function
fast_l2tp_rx:
	.frame	$sp,48,$31		# vars= 0, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	move	$17,$4

	lui	$19,%hi(rtl_get_skb_len)
	lbu	$20,0($2)
	move	$16,$2
	lui	$2,%hi(rtl_get_skb_data)
	move	$4,$17
	addiu	$2,$2,%lo(rtl_get_skb_data)
	jalr	$2
	addiu	$19,$19,%lo(rtl_get_skb_len)

	move	$4,$17
	jalr	$19
	move	$18,$2

	sltu	$2,$2,40
	bne	$2,$0,$L89
	andi	$20,$20,0xf

	sll	$20,$20,2
	li	$3,1701			# 0x6a5
	addu	$20,$16,$20
	lhu	$2,0($20)
	bne	$2,$3,$L89
	nop

	lhu	$3,2($20)
	bne	$3,$2,$L69
	move	$2,$0

	lui	$21,%hi(l2tpInfo)
	lw	$2,%lo(l2tpInfo)($21)
	bne	$2,$0,$L70
	lui	$2,%hi(l2tp_tx_id)

	addiu	$2,$2,%lo(l2tp_tx_id)
	jalr	$2
	move	$4,$17

$L70:
	lbu	$2,28($18)
	li	$20,2			# 0x2
	move	$4,$18
	andi	$3,$2,0x40
	movz	$20,$0,$3
	andi	$2,$2,0x2
	addu	$20,$20,$2
	lui	$2,%hi(fast_l2tp_tx_lcp_echo_reply)
	move	$6,$17
	addiu	$2,$2,%lo(fast_l2tp_tx_lcp_echo_reply)
	jalr	$2
	move	$5,$20

	li	$3,1			# 0x1
	beq	$2,$3,$L79
	addiu	$21,$21,%lo(l2tpInfo)

	lhu	$2,20($21)
	beq	$2,$0,$L69
	move	$2,$0

	lhu	$2,22($21)
	beq	$2,$0,$L89
	addu	$2,$18,$20

	lbu	$3,36($2)
	bne	$3,$0,$L89
	nop

	lbu	$3,37($2)
	li	$2,33			# 0x21
	bne	$3,$2,$L69
	move	$2,$0

	lui	$2,%hi(l2tpInfo)
	lw	$2,%lo(l2tpInfo)($2)
	beq	$2,$0,$L69
	move	$2,$0

	lw	$3,16($21)
	lw	$2,16($16)
	bne	$3,$2,$L69
	move	$2,$0

	lw	$2,4($21)
	bne	$2,$0,$L90
	addiu	$20,$20,38

	addiu	$20,$20,-38
	lui	$4,%hi($LC1)
	lui	$2,%hi(rtl_get_dev_by_name)
	addiu	$2,$2,%lo(rtl_get_dev_by_name)
	jalr	$2
	addiu	$4,$4,%lo($LC1)

	beq	$2,$0,$L89
	sw	$2,4($21)

	addiu	$20,$20,38
$L90:
	li	$4,6			# 0x6
	addu	$18,$18,$20
	lbu	$3,9($18)
	beq	$3,$4,$L74
	li	$4,17			# 0x11

	beq	$3,$4,$L74
	li	$4,1			# 0x1

	beq	$3,$4,$L74
	li	$4,47			# 0x2f

	bne	$3,$4,$L89
	nop

$L74:
	move	$5,$2
	lui	$2,%hi(rtl_set_skb_dev)
	addiu	$2,$2,%lo(rtl_set_skb_dev)
	jalr	$2
	move	$4,$17

	lui	$2,%hi(skb_pull)
	move	$5,$20
	addiu	$2,$2,%lo(skb_pull)
	jalr	$2
	move	$4,$17

	lui	$2,%hi(rtl_skb_reset_network_header)
	addiu	$2,$2,%lo(rtl_skb_reset_network_header)
	jalr	$2
	move	$4,$17

	lui	$2,%hi(rtl_skb_reset_transport_header)
	addiu	$2,$2,%lo(rtl_skb_reset_transport_header)
	jalr	$2
	move	$4,$17

	lw	$4,4($21)
	beq	$4,$0,$L89
	lui	$16,%hi(rtl_get_ppp_dev_priv)

	addiu	$16,$16,%lo(rtl_get_ppp_dev_priv)
	jalr	$16
	nop

	beq	$2,$0,$L89
	nop

	lw	$4,4($21)
	jalr	$16
	nop

	move	$4,$17
	jalr	$19
	move	$16,$2

	move	$6,$2
	lui	$2,%hi(rtl_inc_ppp_stats)
	addiu	$2,$2,%lo(rtl_inc_ppp_stats)
	move	$4,$16
	jalr	$2
	move	$5,$0

	j	$L69
	move	$2,$0

$L79:
	j	$L69
	li	$2,1			# 0x1

$L89:
	move	$2,$0
$L69:
	lw	$31,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
	.end	fast_l2tp_rx
	.size	fast_l2tp_rx, .-fast_l2tp_rx
	.section	.rodata.str1.4
	.align	2
$LC4:
	.ascii	"fast_l2tp\000"
	.section	.init.text,"ax",@progbits
	.align	2
	.globl	fast_l2tp_init
	.set	nomips16
	.ent	fast_l2tp_init
	.type	fast_l2tp_init, @function
fast_l2tp_init:
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 24, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	lui	$3,%hi(event_ppp_dev_down)
	addiu	$3,$3,%lo(event_ppp_dev_down)
	lui	$2,%hi(event_ppp_dev_down_fphook)
	sw	$3,%lo(event_ppp_dev_down_fphook)($2)
	lui	$3,%hi(set_l2tp_device)
	addiu	$3,$3,%lo(set_l2tp_device)
	lui	$2,%hi(set_l2tp_device_fphook)
	sw	$3,%lo(set_l2tp_device_fphook)($2)
	lui	$3,%hi(get_fast_l2tp_lastxmit)
	addiu	$3,$3,%lo(get_fast_l2tp_lastxmit)
	lui	$2,%hi(get_fast_l2tp_lastxmit_fphook)
	sw	$3,%lo(get_fast_l2tp_lastxmit_fphook)($2)
	lui	$3,%hi(is_l2tp_device)
	addiu	$3,$3,%lo(is_l2tp_device)
	lui	$2,%hi(is_l2tp_device_fphook)
	sw	$3,%lo(is_l2tp_device_fphook)($2)
	lui	$3,%hi(check_for_fast_l2tp_to_wan)
	addiu	$3,$3,%lo(check_for_fast_l2tp_to_wan)
	lui	$2,%hi(check_for_fast_l2tp_to_wan_fphook)
	sw	$3,%lo(check_for_fast_l2tp_to_wan_fphook)($2)
	lui	$3,%hi(fast_l2tp_to_wan)
	addiu	$3,$3,%lo(fast_l2tp_to_wan)
	lui	$2,%hi(fast_l2tp_to_wan_fphook)
	sw	$3,%lo(fast_l2tp_to_wan_fphook)($2)
	lui	$4,%hi($LC4)
	lui	$6,%hi(proc_root)
	lui	$7,%hi(fastpath_l2tp_proc_fops)
	lui	$2,%hi(proc_create_data)
	addiu	$7,$7,%lo(fastpath_l2tp_proc_fops)
	addiu	$4,$4,%lo($LC4)
	move	$5,$0
	addiu	$6,$6,%lo(proc_root)
	addiu	$2,$2,%lo(proc_create_data)
	jalr	$2
	sw	$0,16($sp)

	lui	$3,%hi(res1)
	sw	$2,%lo(res1)($3)
	lui	$2,%hi(l2tp_tx_id_hook)
	sw	$0,%lo(l2tp_tx_id_hook)($2)
	lui	$2,%hi(fast_l2tp_fw)
	sw	$0,%lo(fast_l2tp_fw)($2)
	lui	$2,%hi(state)
	sw	$0,%lo(state)($2)
	lui	$4,%hi(l2tpInfo)
	lui	$2,%hi(memset)
	addiu	$4,$4,%lo(l2tpInfo)
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,40			# 0x28

	move	$2,$0
	lw	$31,28($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	fast_l2tp_init
	.size	fast_l2tp_init, .-fast_l2tp_init
	.section	.exit.text,"ax",@progbits
	.align	2
	.globl	fast_l2tp_exit
	.set	nomips16
	.ent	fast_l2tp_exit
	.type	fast_l2tp_exit, @function
fast_l2tp_exit:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$3,%hi(event_ppp_dev_down_fphook)
	sw	$0,%lo(event_ppp_dev_down_fphook)($3)
	lui	$3,%hi(set_l2tp_device_fphook)
	sw	$0,%lo(set_l2tp_device_fphook)($3)
	lui	$3,%hi(get_fast_l2tp_lastxmit_fphook)
	sw	$0,%lo(get_fast_l2tp_lastxmit_fphook)($3)
	lui	$3,%hi(is_l2tp_device_fphook)
	lui	$16,%hi(res1)
	sw	$0,%lo(is_l2tp_device_fphook)($3)
	lui	$3,%hi(check_for_fast_l2tp_to_wan_fphook)
	sw	$0,%lo(check_for_fast_l2tp_to_wan_fphook)($3)
	lui	$3,%hi(fast_l2tp_to_wan_fphook)
	lw	$2,%lo(res1)($16)
	sw	$0,%lo(fast_l2tp_to_wan_fphook)($3)
	lui	$3,%hi(fast_l2tp_fw)
	beq	$2,$0,$L92
	sw	$0,%lo(fast_l2tp_fw)($3)

	lui	$4,%hi($LC4)
	lui	$5,%hi(proc_root)
	lui	$2,%hi(remove_proc_entry)
	addiu	$4,$4,%lo($LC4)
	addiu	$2,$2,%lo(remove_proc_entry)
	jalr	$2
	addiu	$5,$5,%lo(proc_root)

	sw	$0,%lo(res1)($16)
$L92:
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	fast_l2tp_exit
	.size	fast_l2tp_exit, .-fast_l2tp_exit
	.globl	fastpath_l2tp_proc_fops
	.data
	.align	2
	.type	fastpath_l2tp_proc_fops, @object
	.size	fastpath_l2tp_proc_fops, 108
fastpath_l2tp_proc_fops:
	.space	4
	.word	seq_lseek
	.word	seq_read
	.word	fastpath_l2tp_single_write
	.space	28
	.word	fastpath_l2tp_single_open
	.space	4
	.word	single_release
	.space	52
	.globl	l2tp_ppp_imagic
	.section	.bss,"aw",@nobits
	.align	2
	.type	l2tp_ppp_imagic, @object
	.size	l2tp_ppp_imagic, 4
l2tp_ppp_imagic:
	.space	4
	.globl	l2tpInfo
	.align	2
	.type	l2tpInfo, @object
	.size	l2tpInfo, 40
l2tpInfo:
	.space	40
	.globl	l2tp_tx_id_hook
	.align	2
	.type	l2tp_tx_id_hook, @object
	.size	l2tp_tx_id_hook, 4
l2tp_tx_id_hook:
	.space	4
	.local	res1
	.comm	res1,4,4
	.ident	"GCC: (Realtek RSDK-4.6.4 Build 2002) 4.6.4"
