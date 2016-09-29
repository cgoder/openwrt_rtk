	.file	1 "fast_pppoe_core.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
	.align	2
	.set	nomips16
	.ent	fastpath_pppoe_single_write
	.type	fastpath_pppoe_single_write, @function
fastpath_pppoe_single_write:
	.frame	$sp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-16
	sw	$31,12($sp)
	sltu	$4,$6,2
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L6
	move	$2,$6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L6
	addiu	$4,$5,1
	.set	macro
	.set	reorder

	or	$3,$4,$5
	lw	$4,24($28)
	#nop
	and	$3,$3,$4
	.set	noreorder
	.set	nomacro
	bne	$3,$0,$L6
	move	$4,$sp
	.set	macro
	.set	reorder

	li	$6,1			# 0x1
 #APP
 # 69 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx4181-linux/linux-realtek_rtl8196e/fastpath-0.1/fast_pppoe_core.c" 1
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
	bne	$6,$0,$L6
	lui	$3,%hi(fast_pppoe_fw)
	.set	macro
	.set	reorder

	lb	$4,0($sp)
	#nop
	addiu	$4,$4,-48
	.set	noreorder
	.set	nomacro
	j	$L2
	sw	$4,%lo(fast_pppoe_fw)($3)
	.set	macro
	.set	reorder

$L6:
	li	$2,-14			# 0xfffffffffffffff2
$L2:
	lw	$31,12($sp)
	#nop
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,16
	.set	macro
	.set	reorder

	.end	fastpath_pppoe_single_write
	.size	fastpath_pppoe_single_write, .-fastpath_pppoe_single_write
	.align	2
	.set	nomips16
	.ent	find_pppoe_info
	.type	find_pppoe_info, @function
find_pppoe_info:
	.frame	$sp,64,$31		# vars= 8, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-64
	sw	$31,60($sp)
	sw	$fp,56($sp)
	sw	$23,52($sp)
	sw	$22,48($sp)
	sw	$21,44($sp)
	sw	$20,40($sp)
	sw	$19,36($sp)
	sw	$18,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	lw	$23,84($sp)
	lw	$22,88($sp)
	lui	$17,%hi(fast_pppoe_info+54)
	lui	$18,%hi(fast_pppoe_info)
	move	$20,$4
	move	$21,$5
	move	$fp,$7
	sw	$6,20($sp)
	addiu	$17,$17,%lo(fast_pppoe_info+54)
	move	$16,$0
	addiu	$18,$18,%lo(fast_pppoe_info)
	li	$19,16			# 0x10
$L17:
	lhu	$2,0($17)
	#nop
	beq	$2,$0,$L9
	.set	noreorder
	.set	nomacro
	beq	$20,$0,$L10
	sll	$3,$16,4
	.set	macro
	.set	reorder

	sll	$2,$16,2
	subu	$2,$3,$2
	subu	$2,$2,$16
	sll	$2,$2,3
	addiu	$3,$2,16
	addu	$3,$18,$3
	move	$4,$20
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx4181-linux/linux-realtek_rtl8196e/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$5,($3)
1:	lbu	$1,($4)
	addiu	$3,1
	bne	$1,$5,2f
	addiu	$4,1
	bnez	$5,1b
	lbu	$5,($3)
	nop
	move	$5,$1
2:	subu	$5,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L11
	addu	$2,$18,$2
	.set	macro
	.set	reorder

$L10:
	.set	noreorder
	.set	nomacro
	beq	$21,$0,$L12
	sll	$3,$16,4
	.set	macro
	.set	reorder

	sll	$2,$16,2
	subu	$2,$3,$2
	subu	$2,$2,$16
	sll	$2,$2,3
	addu	$2,$18,$2
	move	$3,$2
	move	$4,$21
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx4181-linux/linux-realtek_rtl8196e/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$5,($3)
1:	lbu	$1,($4)
	addiu	$3,1
	bne	$1,$5,2f
	addiu	$4,1
	bnez	$5,1b
	lbu	$5,($3)
	nop
	move	$5,$1
2:	subu	$5,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	beq	$5,$0,$L11
$L12:
	.set	noreorder
	.set	nomacro
	beq	$22,$0,$L13
	sll	$3,$16,4
	.set	macro
	.set	reorder

	sll	$2,$16,2
	subu	$2,$3,$2
	subu	$2,$2,$16
	sll	$2,$2,3
	addu	$4,$18,$2
	lui	$3,%hi(memcmp)
	sw	$2,16($sp)
	addiu	$4,$4,38
	move	$5,$22
	addiu	$2,$3,%lo(memcmp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,6			# 0x6
	.set	macro
	.set	reorder

	beq	$2,$0,$L19
$L13:
	.set	noreorder
	.set	nomacro
	beq	$23,$0,$L14
	sll	$3,$16,4
	.set	macro
	.set	reorder

	sll	$2,$16,2
	subu	$2,$3,$2
	subu	$2,$2,$16
	sll	$2,$2,3
	addiu	$4,$2,32
	lui	$3,%hi(memcmp)
	sw	$2,16($sp)
	addu	$4,$18,$4
	move	$5,$23
	addiu	$2,$3,%lo(memcmp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,6			# 0x6
	.set	macro
	.set	reorder

	bne	$2,$0,$L14
$L19:
	lw	$3,16($sp)
	.set	noreorder
	.set	nomacro
	j	$L11
	addu	$2,$18,$3
	.set	macro
	.set	reorder

$L14:
	lw	$2,80($sp)
	#nop
	beq	$2,$0,$L15
	lw	$2,-6($17)
	lw	$3,80($sp)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$3,$L21
	sll	$2,$16,2
	.set	macro
	.set	reorder

$L15:
	beq	$fp,$0,$L16
	lw	$2,-10($17)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$fp,$L21
	sll	$2,$16,2
	.set	macro
	.set	reorder

$L16:
	lw	$2,20($sp)
	#nop
	beq	$2,$0,$L9
	lhu	$2,-2($17)
	lw	$3,20($sp)
	#nop
	.set	noreorder
	.set	nomacro
	bne	$2,$3,$L22
	addiu	$16,$16,1
	.set	macro
	.set	reorder

	addiu	$16,$16,-1
	sll	$2,$16,2
$L21:
	sll	$3,$16,4
	subu	$2,$3,$2
	subu	$16,$2,$16
	lui	$2,%hi(fast_pppoe_info)
	sll	$16,$16,3
	addiu	$2,$2,%lo(fast_pppoe_info)
	.set	noreorder
	.set	nomacro
	j	$L11
	addu	$2,$2,$16
	.set	macro
	.set	reorder

$L9:
	addiu	$16,$16,1
$L22:
	.set	noreorder
	.set	nomacro
	bne	$16,$19,$L17
	addiu	$17,$17,88
	.set	macro
	.set	reorder

	move	$2,$0
$L11:
	lw	$31,60($sp)
	lw	$fp,56($sp)
	lw	$23,52($sp)
	lw	$22,48($sp)
	lw	$21,44($sp)
	lw	$20,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,64
	.set	macro
	.set	reorder

	.end	find_pppoe_info
	.size	find_pppoe_info, .-find_pppoe_info
	.align	2
	.globl	get_pppoe_last_rx_tx
	.set	nomips16
	.ent	get_pppoe_last_rx_tx
	.type	get_pppoe_last_rx_tx, @function
get_pppoe_last_rx_tx:
	.frame	$sp,40,$31		# vars= 0, regs= 1/0, args= 32, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	lw	$2,56($sp)
	nop
	sw	$2,16($sp)
	lw	$2,60($sp)
	nop
	sw	$2,20($sp)
	lw	$2,64($sp)
	nop
	sw	$2,24($sp)
	lui	$2,%hi(find_pppoe_info)
	addiu	$2,$2,%lo(find_pppoe_info)
	jalr	$2
	andi	$6,$6,0xffff

	beq	$2,$0,$L24
	nop

	lw	$4,56($2)
	lw	$3,68($sp)
	nop
	sw	$4,0($3)
	lw	$3,60($2)
	lw	$2,72($sp)
	nop
	sw	$3,0($2)
$L24:
	lw	$31,36($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	get_pppoe_last_rx_tx
	.size	get_pppoe_last_rx_tx, .-get_pppoe_last_rx_tx
	.align	2
	.globl	set_pppoe_info
	.set	nomips16
	.ent	set_pppoe_info
	.type	set_pppoe_info, @function
set_pppoe_info:
	.frame	$sp,72,$31		# vars= 0, regs= 9/0, args= 32, gp= 0
	.mask	0x80ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-72
	sw	$31,68($sp)
	sw	$23,64($sp)
	sw	$22,60($sp)
	sw	$21,56($sp)
	sw	$20,52($sp)
	sw	$19,48($sp)
	sw	$18,44($sp)
	sw	$17,40($sp)
	sw	$16,36($sp)
	lw	$23,88($sp)
	lw	$20,92($sp)
	lw	$19,96($sp)
	lui	$2,%hi(find_pppoe_info)
	move	$17,$5
	andi	$21,$6,0xffff
	move	$5,$0
	move	$6,$0
	sw	$23,16($sp)
	sw	$20,20($sp)
	sw	$19,24($sp)
	addiu	$2,$2,%lo(find_pppoe_info)
	move	$18,$4
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$22,$7
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L26
	move	$16,$2
	.set	macro
	.set	reorder

	lui	$2,%hi(fast_pppoe_info+54)
	addiu	$2,$2,%lo(fast_pppoe_info+54)
	move	$3,$0
	li	$5,16			# 0x10
$L29:
	lhu	$4,0($2)
	#nop
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L27
	addiu	$2,$2,88
	.set	macro
	.set	reorder

	sll	$2,$3,2
	sll	$16,$3,4
	subu	$16,$16,$2
	subu	$3,$16,$3
	lui	$16,%hi(fast_pppoe_info)
	sll	$3,$3,3
	addiu	$16,$16,%lo(fast_pppoe_info)
	addu	$16,$16,$3
	bne	$16,$0,$L26
	j	$L30
$L27:
	addiu	$3,$3,1
	bne	$3,$5,$L29
	lui	$16,%hi(fast_pppoe_info)
	lui	$2,%hi(memset)
	addiu	$4,$16,%lo(fast_pppoe_info)
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,1408			# 0x580
	.set	macro
	.set	reorder

	addiu	$16,$16,%lo(fast_pppoe_info)
$L26:
	beq	$21,$0,$L31
	sh	$21,52($16)
$L31:
	beq	$22,$0,$L32
	sw	$22,44($16)
$L32:
	beq	$23,$0,$L33
	sw	$23,48($16)
$L33:
	.set	noreorder
	.set	nomacro
	beq	$18,$0,$L34
	addiu	$2,$16,16
	.set	macro
	.set	reorder

 #APP
 # 30 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx4181-linux/linux-realtek_rtl8196e/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
1:	lbu	$1,($18)
	addiu	$18,1
	sb	$1,($2)
	bnez	$1,1b
	addiu	$2,1
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
$L34:
	.set	noreorder
	.set	nomacro
	beq	$17,$0,$L35
	move	$2,$16
	.set	macro
	.set	reorder

 #APP
 # 30 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx4181-linux/linux-realtek_rtl8196e/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
1:	lbu	$1,($17)
	addiu	$17,1
	sb	$1,($2)
	bnez	$1,1b
	addiu	$2,1
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
$L35:
	.set	noreorder
	.set	nomacro
	beq	$19,$0,$L36
	lui	$2,%hi(memcpy)
	.set	macro
	.set	reorder

	addiu	$4,$16,38
	move	$5,$19
	addiu	$2,$2,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,6			# 0x6
	.set	macro
	.set	reorder

$L36:
	.set	noreorder
	.set	nomacro
	beq	$20,$0,$L37
	lui	$2,%hi(memcpy)
	.set	macro
	.set	reorder

	addiu	$4,$16,32
	move	$5,$20
	addiu	$2,$2,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,6			# 0x6
	.set	macro
	.set	reorder

$L37:
	li	$2,1			# 0x1
	sh	$2,54($16)
$L30:
	lw	$31,68($sp)
	lw	$23,64($sp)
	lw	$22,60($sp)
	lw	$21,56($sp)
	lw	$20,52($sp)
	lw	$19,48($sp)
	lw	$18,44($sp)
	lw	$17,40($sp)
	lw	$16,36($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,72
	.set	macro
	.set	reorder

	.end	set_pppoe_info
	.size	set_pppoe_info, .-set_pppoe_info
	.align	2
	.globl	clear_pppoe_info
	.set	nomips16
	.ent	clear_pppoe_info
	.type	clear_pppoe_info, @function
clear_pppoe_info:
	.frame	$sp,64,$31		# vars= 8, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-64
	sw	$31,60($sp)
	sw	$fp,56($sp)
	sw	$23,52($sp)
	sw	$22,48($sp)
	sw	$21,44($sp)
	sw	$20,40($sp)
	sw	$19,36($sp)
	sw	$18,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	lw	$22,84($sp)
	lw	$23,88($sp)
	andi	$6,$6,0xffff
	lui	$17,%hi(fast_pppoe_info+54)
	lui	$18,%hi(fast_pppoe_info)
	move	$20,$4
	move	$21,$5
	sw	$6,16($sp)
	addiu	$17,$17,%lo(fast_pppoe_info+54)
	move	$16,$0
	addiu	$18,$18,%lo(fast_pppoe_info)
	li	$19,16			# 0x10
$L45:
	lhu	$2,0($17)
	#nop
	beq	$2,$0,$L40
	.set	noreorder
	.set	nomacro
	beq	$20,$0,$L41
	sll	$2,$16,2
	.set	macro
	.set	reorder

	sll	$4,$16,4
	subu	$4,$4,$2
	subu	$4,$4,$16
	sll	$4,$4,3
	addiu	$2,$4,16
	addu	$2,$18,$2
	move	$3,$20
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx4181-linux/linux-realtek_rtl8196e/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$5,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$5,2f
	addiu	$3,1
	bnez	$5,1b
	lbu	$5,($2)
	nop
	move	$5,$1
2:	subu	$5,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L41
	lui	$3,%hi(memset)
	.set	macro
	.set	reorder

	addu	$4,$18,$4
	addiu	$2,$3,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,88			# 0x58
	.set	macro
	.set	reorder

$L41:
	.set	noreorder
	.set	nomacro
	beq	$21,$0,$L42
	sll	$2,$16,2
	.set	macro
	.set	reorder

	sll	$4,$16,4
	subu	$4,$4,$2
	subu	$4,$4,$16
	sll	$4,$4,3
	addu	$4,$18,$4
	move	$2,$4
	move	$3,$21
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx4181-linux/linux-realtek_rtl8196e/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$5,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$5,2f
	addiu	$3,1
	bnez	$5,1b
	lbu	$5,($2)
	nop
	move	$5,$1
2:	subu	$5,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L42
	lui	$3,%hi(memset)
	.set	macro
	.set	reorder

	addiu	$2,$3,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,88			# 0x58
	.set	macro
	.set	reorder

$L42:
	.set	noreorder
	.set	nomacro
	beq	$23,$0,$L43
	sll	$2,$16,2
	.set	macro
	.set	reorder

	sll	$fp,$16,4
	subu	$fp,$fp,$2
	subu	$fp,$fp,$16
	sll	$fp,$fp,3
	addu	$4,$18,$fp
	lui	$3,%hi(memcmp)
	addiu	$4,$4,38
	move	$5,$23
	addiu	$2,$3,%lo(memcmp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,6			# 0x6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L43
	lui	$3,%hi(memset)
	.set	macro
	.set	reorder

	addu	$4,$18,$fp
	move	$5,$0
	addiu	$2,$3,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,88			# 0x58
	.set	macro
	.set	reorder

$L43:
	.set	noreorder
	.set	nomacro
	beq	$22,$0,$L44
	sll	$2,$16,2
	.set	macro
	.set	reorder

	sll	$fp,$16,4
	subu	$fp,$fp,$2
	subu	$fp,$fp,$16
	sll	$fp,$fp,3
	addiu	$4,$fp,32
	lui	$3,%hi(memcmp)
	addu	$4,$18,$4
	move	$5,$22
	addiu	$2,$3,%lo(memcmp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,6			# 0x6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L44
	lui	$3,%hi(memset)
	.set	macro
	.set	reorder

	addu	$4,$18,$fp
	move	$5,$0
	addiu	$2,$3,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,88			# 0x58
	.set	macro
	.set	reorder

$L44:
	lhu	$2,-2($17)
	lw	$3,16($sp)
	#nop
	.set	noreorder
	.set	nomacro
	bne	$2,$3,$L40
	sll	$2,$16,2
	.set	macro
	.set	reorder

	sll	$4,$16,4
	subu	$4,$4,$2
	subu	$4,$4,$16
	sll	$4,$4,3
	lui	$3,%hi(memset)
	addu	$4,$18,$4
	move	$5,$0
	addiu	$2,$3,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,88			# 0x58
	.set	macro
	.set	reorder

$L40:
	addiu	$16,$16,1
	.set	noreorder
	.set	nomacro
	bne	$16,$19,$L45
	addiu	$17,$17,88
	.set	macro
	.set	reorder

	lw	$31,60($sp)
	lw	$fp,56($sp)
	lw	$23,52($sp)
	lw	$22,48($sp)
	lw	$21,44($sp)
	lw	$20,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,64
	.set	macro
	.set	reorder

	.end	clear_pppoe_info
	.size	clear_pppoe_info, .-clear_pppoe_info
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"fast_pppoe\000"
	.section	.exit.text,"ax",@progbits
	.align	2
	.globl	fast_pppoe_exit
	.set	nomips16
	.ent	fast_pppoe_exit
	.type	fast_pppoe_exit, @function
fast_pppoe_exit:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$3,%hi(clear_pppoe_info_fphook)
	lui	$16,%hi(fast_pppoe_proc)
	sw	$0,%lo(clear_pppoe_info_fphook)($3)
	lw	$2,%lo(fast_pppoe_proc)($16)
	lui	$3,%hi(set_pppoe_info_fphook)
	sw	$0,%lo(set_pppoe_info_fphook)($3)
	lui	$3,%hi(get_pppoe_last_rx_tx_fphook)
	sw	$0,%lo(get_pppoe_last_rx_tx_fphook)($3)
	lui	$3,%hi(fast_pppoe_fw)
	beq	$2,$0,$L48
	sw	$0,%lo(fast_pppoe_fw)($3)

	lui	$4,%hi($LC0)
	lui	$5,%hi(proc_root)
	lui	$2,%hi(remove_proc_entry)
	addiu	$4,$4,%lo($LC0)
	addiu	$2,$2,%lo(remove_proc_entry)
	jalr	$2
	addiu	$5,$5,%lo(proc_root)

	sw	$0,%lo(fast_pppoe_proc)($16)
$L48:
	lw	$31,20($sp)
	lw	$16,16($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	fast_pppoe_exit
	.size	fast_pppoe_exit, .-fast_pppoe_exit
	.section	.init.text,"ax",@progbits
	.align	2
	.globl	fast_pppoe_init
	.set	nomips16
	.ent	fast_pppoe_init
	.type	fast_pppoe_init, @function
fast_pppoe_init:
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 24, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$17,32($sp)
	sw	$16,28($sp)
	lui	$3,%hi(clear_pppoe_info)
	addiu	$3,$3,%lo(clear_pppoe_info)
	lui	$2,%hi(clear_pppoe_info_fphook)
	sw	$3,%lo(clear_pppoe_info_fphook)($2)
	lui	$3,%hi(set_pppoe_info)
	addiu	$3,$3,%lo(set_pppoe_info)
	lui	$2,%hi(set_pppoe_info_fphook)
	sw	$3,%lo(set_pppoe_info_fphook)($2)
	lui	$3,%hi(get_pppoe_last_rx_tx)
	addiu	$3,$3,%lo(get_pppoe_last_rx_tx)
	lui	$2,%hi(get_pppoe_last_rx_tx_fphook)
	lui	$17,%hi(fast_pppoe_fw)
	li	$16,1			# 0x1
	sw	$3,%lo(get_pppoe_last_rx_tx_fphook)($2)
	lui	$4,%hi($LC0)
	lui	$6,%hi(proc_root)
	lui	$7,%hi(fastpath_pppoe_proc_fops)
	lui	$2,%hi(proc_create_data)
	addiu	$7,$7,%lo(fastpath_pppoe_proc_fops)
	sw	$16,%lo(fast_pppoe_fw)($17)
	addiu	$4,$4,%lo($LC0)
	move	$5,$0
	addiu	$6,$6,%lo(proc_root)
	addiu	$2,$2,%lo(proc_create_data)
	jalr	$2
	sw	$0,16($sp)

	lui	$3,%hi(fast_pppoe_proc)
	sw	$2,%lo(fast_pppoe_proc)($3)
	lui	$4,%hi(fast_pppoe_info)
	lui	$2,%hi(memset)
	addiu	$4,$4,%lo(fast_pppoe_info)
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,1408			# 0x580

	sw	$16,%lo(fast_pppoe_fw)($17)
	lw	$31,36($sp)
	lw	$17,32($sp)
	lw	$16,28($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	fast_pppoe_init
	.size	fast_pppoe_init, .-fast_pppoe_init
	.text
	.align	2
	.globl	fastpath_pppoe_single_open
	.set	nomips16
	.ent	fastpath_pppoe_single_open
	.type	fastpath_pppoe_single_open, @function
fastpath_pppoe_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	move	$4,$5
	lui	$25,%hi(single_open)
	lui	$5,%hi(fast_pppoe_read_proc)
	move	$6,$0
	addiu	$5,$5,%lo(fast_pppoe_read_proc)
	addiu	$25,$25,%lo(single_open)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	fastpath_pppoe_single_open
	.size	fastpath_pppoe_single_open, .-fastpath_pppoe_single_open
	.section	.rodata.str1.4
	.align	2
$LC1:
	.ascii	"fast pppoe enable:%c\012\000"
	.align	2
$LC2:
	.ascii	"[%d] null,null,0\012\000"
	.align	2
$LC3:
	.ascii	"[%d] %s,%s,%d,0x%x:%x:%x:%x:%x:%x\012\000"
	.text
	.align	2
	.set	nomips16
	.ent	fast_pppoe_read_proc
	.type	fast_pppoe_read_proc, @function
fast_pppoe_read_proc:
	.frame	$sp,80,$31		# vars= 0, regs= 8/0, args= 48, gp= 0
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-80
	sw	$31,76($sp)
	sw	$22,72($sp)
	sw	$21,68($sp)
	sw	$20,64($sp)
	sw	$19,60($sp)
	sw	$18,56($sp)
	sw	$17,52($sp)
	sw	$16,48($sp)
	lui	$2,%hi(fast_pppoe_fw)
	lw	$6,%lo(fast_pppoe_fw)($2)
	lui	$5,%hi($LC1)
	lui	$20,%hi(seq_printf)
	addiu	$5,$5,%lo($LC1)
	addiu	$6,$6,48
	addiu	$20,$20,%lo(seq_printf)
	lui	$17,%hi(fast_pppoe_info+54)
	lui	$18,%hi(fast_pppoe_info)
	lui	$22,%hi($LC3)
	move	$19,$4
	jalr	$20
	addiu	$17,$17,%lo(fast_pppoe_info+54)

	move	$16,$0
	addiu	$18,$18,%lo(fast_pppoe_info)
	addiu	$22,$22,%lo($LC3)
	lui	$21,%hi($LC2)
$L54:
	sll	$2,$16,2
	sll	$3,$16,4
	subu	$3,$3,$2
	subu	$3,$3,$16
	lhu	$2,0($17)
	sll	$3,$3,3
	addiu	$7,$3,16
	move	$4,$19
	addiu	$5,$21,%lo($LC2)
	move	$6,$16
	addu	$3,$18,$3
	bne	$2,$0,$L52
	addu	$7,$18,$7

	jalr	$20
	addiu	$16,$16,1

	j	$L57
	li	$2,16			# 0x10

$L52:
	lhu	$13,-2($17)
	lbu	$12,-16($17)
	lbu	$11,-15($17)
	lbu	$10,-14($17)
	lbu	$9,-13($17)
	lbu	$8,-12($17)
	lbu	$2,-11($17)
	move	$6,$16
	move	$4,$19
	move	$5,$22
	sw	$3,16($sp)
	sw	$13,20($sp)
	sw	$12,24($sp)
	sw	$11,28($sp)
	sw	$10,32($sp)
	sw	$9,36($sp)
	sw	$8,40($sp)
	jalr	$20
	sw	$2,44($sp)

	addiu	$16,$16,1
	li	$2,16			# 0x10
$L57:
	bne	$16,$2,$L54
	addiu	$17,$17,88

	lw	$31,76($sp)
	lw	$22,72($sp)
	lw	$21,68($sp)
	lw	$20,64($sp)
	lw	$19,60($sp)
	lw	$18,56($sp)
	lw	$17,52($sp)
	lw	$16,48($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,80

	.set	macro
	.set	reorder
	.end	fast_pppoe_read_proc
	.size	fast_pppoe_read_proc, .-fast_pppoe_read_proc
	.section	.rodata.str1.4
	.align	2
$LC4:
	.ascii	"ppp\000"
	.text
	.align	2
	.globl	fast_pppoe_xmit
	.set	nomips16
	.ent	fast_pppoe_xmit
	.type	fast_pppoe_xmit, @function
fast_pppoe_xmit:
	.frame	$sp,64,$31		# vars= 0, regs= 7/0, args= 32, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-64
	sw	$31,60($sp)
	sw	$21,56($sp)
	sw	$20,52($sp)
	sw	$19,48($sp)
	sw	$18,44($sp)
	sw	$17,40($sp)
	sw	$16,36($sp)
	lui	$2,%hi(fast_pppoe_fw)
	lw	$2,%lo(fast_pppoe_fw)($2)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L64
	move	$17,$4
	.set	macro
	.set	reorder

	lui	$16,%hi(rtl_get_skb_dev)
	addiu	$16,$16,%lo(rtl_get_skb_dev)
	jalr	$16
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L59
	move	$2,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$17
	.set	macro
	.set	reorder

	lui	$3,%hi($LC4)
	addiu	$3,$3,%lo($LC4)
	li	$4,3			# 0x3
 #APP
 # 111 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx4181-linux/linux-realtek_rtl8196e/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
1:	lbu	$5,($2)
	beqz	$4,2f
	lbu	$1,($3)
	subu	$4,1
	bne	$1,$5,3f
	addiu	$2,1
	bnez	$5,1b
	addiu	$3,1
2:
	nop
	move	$5,$1
3:	subu	$5,$1
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L59
	move	$2,$0
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_skb_headroom)
	addiu	$2,$2,%lo(rtl_skb_headroom)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	sltu	$2,$2,22
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L59
	move	$2,$0
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_skb_cloned)
	addiu	$2,$2,%lo(rtl_skb_cloned)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L59
	move	$2,$0
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_skb_shared)
	addiu	$2,$2,%lo(rtl_skb_shared)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L59
	move	$2,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$17
	.set	macro
	.set	reorder

	move	$4,$2
	lui	$2,%hi(find_pppoe_info)
	move	$5,$0
	move	$6,$0
	move	$7,$0
	sw	$0,16($sp)
	sw	$0,20($sp)
	addiu	$2,$2,%lo(find_pppoe_info)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$0,24($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L64
	move	$18,$2
	.set	macro
	.set	reorder

	lb	$2,16($2)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L59
	move	$2,$0
	.set	macro
	.set	reorder

	lb	$2,0($18)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L59
	move	$2,$0
	.set	macro
	.set	reorder

	lhu	$2,52($18)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L59
	move	$2,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$17
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_get_skb_len)
	addiu	$2,$2,%lo(rtl_get_skb_len)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	move	$21,$2
	lui	$2,%hi(rtl_get_dev_by_name)
	addiu	$2,$2,%lo(rtl_get_dev_by_name)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L64
	move	$20,$2
	.set	macro
	.set	reorder

	lui	$16,%hi(rtl_skb_push)
	addiu	$16,$16,%lo(rtl_skb_push)
	li	$5,2			# 0x2
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jalr	$16
	lui	$19,%hi(rtl_get_skb_data)
	.set	macro
	.set	reorder

	addiu	$19,$19,%lo(rtl_get_skb_data)
	.set	noreorder
	.set	nomacro
	jalr	$19
	move	$4,$17
	.set	macro
	.set	reorder

	li	$3,33			# 0x21
	li	$5,6			# 0x6
	sh	$3,0($2)
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$19
	move	$4,$17
	.set	macro
	.set	reorder

	li	$3,17			# 0x11
	sb	$3,0($2)
	sb	$0,1($2)
	lhu	$3,52($18)
	addiu	$21,$21,2
	andi	$21,$21,0xffff
	srl	$6,$3,8
	srl	$4,$21,8
	sb	$6,2($2)
	sb	$3,3($2)
	sb	$4,4($2)
	sb	$21,5($2)
	lui	$2,%hi(rtl_set_skb_dev)
	move	$5,$20
	addiu	$2,$2,%lo(rtl_set_skb_dev)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	li	$5,2			# 0x2
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$19
	move	$4,$17
	.set	macro
	.set	reorder

	li	$3,-30620			# 0xffffffffffff8864
	sh	$3,0($2)
	li	$5,12			# 0xc
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$19
	move	$4,$17
	.set	macro
	.set	reorder

	lui	$16,%hi(memcpy)
	addiu	$5,$18,38
	li	$6,6			# 0x6
	addiu	$16,$16,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$19
	move	$4,$17
	.set	macro
	.set	reorder

	lw	$5,396($20)
	li	$6,6			# 0x6
	.set	noreorder
	.set	nomacro
	jalr	$16
	addiu	$4,$2,6
	.set	macro
	.set	reorder

	lui	$2,%hi(ip_finish_output4)
	addiu	$2,$2,%lo(ip_finish_output4)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	lui	$2,%hi(jiffies)
	lw	$3,%lo(jiffies)($2)
	li	$2,1			# 0x1
	.set	noreorder
	.set	nomacro
	j	$L59
	sw	$3,60($18)
	.set	macro
	.set	reorder

$L64:
	move	$2,$0
$L59:
	lw	$31,60($sp)
	lw	$21,56($sp)
	lw	$20,52($sp)
	lw	$19,48($sp)
	lw	$18,44($sp)
	lw	$17,40($sp)
	lw	$16,36($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,64
	.set	macro
	.set	reorder

	.end	fast_pppoe_xmit
	.size	fast_pppoe_xmit, .-fast_pppoe_xmit
	.align	2
	.globl	check_and_restore_pppoe_hdr
	.set	nomips16
	.ent	check_and_restore_pppoe_hdr
	.type	check_and_restore_pppoe_hdr, @function
check_and_restore_pppoe_hdr:
	.frame	$sp,32,$31		# vars= 0, regs= 4/0, args= 16, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(fast_pppoe_fw)
	lw	$2,%lo(fast_pppoe_fw)($2)
	nop
	beq	$2,$0,$L72
	move	$16,$4

	lui	$2,%hi(rtl_get_skb_pppoe_flag)
	addiu	$2,$2,%lo(rtl_get_skb_pppoe_flag)
	jalr	$2
	nop

	beq	$2,$0,$L72
	lui	$2,%hi(rtl_skb_push)

	li	$5,8			# 0x8
	move	$4,$16
	addiu	$2,$2,%lo(rtl_skb_push)
	jalr	$2
	lui	$17,%hi(rtl_get_skb_data)

	addiu	$17,$17,%lo(rtl_get_skb_data)
	jalr	$17
	move	$4,$16

	move	$5,$2
	lui	$2,%hi(rtl_set_skb_network_header)
	addiu	$2,$2,%lo(rtl_set_skb_network_header)
	jalr	$2
	move	$4,$16

	jalr	$17
	move	$4,$16

	move	$5,$2
	lui	$2,%hi(rtl_set_skb_transport_header)
	move	$4,$16
	addiu	$2,$2,%lo(rtl_set_skb_transport_header)
	jalr	$2
	lui	$17,%hi(rtl_get_skb_dev)

	addiu	$17,$17,%lo(rtl_get_skb_dev)
	jalr	$17
	move	$4,$16

	lw	$3,128($2)
	move	$4,$16
	addiu	$3,$3,-1
	jalr	$17
	sw	$3,128($2)

	lw	$18,136($2)
	move	$17,$2
	lui	$2,%hi(rtl_get_skb_len)
	addiu	$2,$2,%lo(rtl_get_skb_len)
	jalr	$2
	move	$4,$16

	subu	$2,$18,$2
	sw	$2,136($17)
	lui	$2,%hi(rtl_get_skb_rx_dev)
	addiu	$2,$2,%lo(rtl_get_skb_rx_dev)
	jalr	$2
	move	$4,$16

	move	$5,$2
	lui	$2,%hi(rtl_set_skb_dev)
	addiu	$2,$2,%lo(rtl_set_skb_dev)
	jalr	$2
	move	$4,$16

	lui	$2,%hi(rtl_set_skb_protocol)
	move	$4,$16
	addiu	$2,$2,%lo(rtl_set_skb_protocol)
	jalr	$2
	li	$5,34916			# 0x8864

	move	$4,$16
	lw	$31,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	lui	$25,%hi(rtl_set_skb_pppoe_flag)
	move	$5,$0
	addiu	$25,$25,%lo(rtl_set_skb_pppoe_flag)
	jr	$25
	addiu	$sp,$sp,32

$L72:
	lw	$31,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	check_and_restore_pppoe_hdr
	.size	check_and_restore_pppoe_hdr, .-check_and_restore_pppoe_hdr
	.align	2
	.globl	check_and_pull_pppoe_hdr
	.set	nomips16
	.ent	check_and_pull_pppoe_hdr
	.type	check_and_pull_pppoe_hdr, @function
check_and_pull_pppoe_hdr:
	.frame	$sp,64,$31		# vars= 8, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-64
	sw	$31,60($sp)
	sw	$fp,56($sp)
	sw	$23,52($sp)
	sw	$22,48($sp)
	sw	$21,44($sp)
	sw	$20,40($sp)
	sw	$19,36($sp)
	sw	$18,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	lui	$2,%hi(fast_pppoe_fw)
	lw	$2,%lo(fast_pppoe_fw)($2)
	nop
	beq	$2,$0,$L81
	move	$19,$4

	lui	$21,%hi(rtl_set_skb_pppoe_flag)
	addiu	$21,$21,%lo(rtl_set_skb_pppoe_flag)
	jalr	$21
	move	$5,$0

	lui	$2,%hi(rtl_skb_mac_header)
	addiu	$2,$2,%lo(rtl_skb_mac_header)
	jalr	$2
	move	$4,$19

	beq	$2,$0,$L81
	move	$18,$2

	lhu	$3,12($2)
	li	$2,34916			# 0x8864
	bne	$3,$2,$L75
	move	$2,$0

	lhu	$2,20($18)
	li	$3,33			# 0x21
	beq	$2,$3,$L77
	li	$3,87			# 0x57

	bne	$2,$3,$L75
	move	$2,$0

$L77:
	lhu	$22,16($18)
	addiu	$2,$18,6
	lui	$16,%hi(fast_pppoe_info+54)
	lui	$fp,%hi(fast_pppoe_info)
	sw	$2,16($sp)
	addiu	$16,$16,%lo(fast_pppoe_info+54)
	move	$17,$0
	addiu	$fp,$fp,%lo(fast_pppoe_info)
	li	$20,16			# 0x10
$L80:
	lhu	$2,0($16)
	nop
	beq	$2,$0,$L78
	nop

	lhu	$2,-2($16)
	nop
	bne	$2,$22,$L78
	sll	$2,$17,2

	sll	$23,$17,4
	subu	$23,$23,$2
	subu	$23,$23,$17
	sll	$23,$23,3
	lw	$5,16($sp)
	addu	$4,$fp,$23
	lui	$3,%hi(memcmp)
	addiu	$4,$4,38
	addiu	$2,$3,%lo(memcmp)
	jalr	$2
	li	$6,6			# 0x6

	bne	$2,$0,$L89
	addiu	$17,$17,1

	addiu	$17,$17,-1
	addu	$23,$fp,$23
	bne	$23,$0,$L88
	move	$2,$0

	j	$L75
	nop

$L78:
	addiu	$17,$17,1
$L89:
	bne	$17,$20,$L80
	addiu	$16,$16,88

	j	$L75
	move	$2,$0

$L88:
	lui	$2,%hi(rtl_get_dev_by_name)
	addiu	$2,$2,%lo(rtl_get_dev_by_name)
	jalr	$2
	addiu	$4,$23,16

	beq	$2,$0,$L81
	move	$16,$2

	addiu	$18,$18,22
	lui	$2,%hi(rtl_set_skb_network_header)
	move	$4,$19
	addiu	$2,$2,%lo(rtl_set_skb_network_header)
	jalr	$2
	move	$5,$18

	lui	$2,%hi(rtl_set_skb_transport_header)
	move	$4,$19
	addiu	$2,$2,%lo(rtl_set_skb_transport_header)
	jalr	$2
	move	$5,$18

	lui	$2,%hi(rtl_skb_pull)
	li	$5,8			# 0x8
	move	$4,$19
	addiu	$2,$2,%lo(rtl_skb_pull)
	jalr	$2
	lui	$17,%hi(rtl_get_skb_dev)

	addiu	$17,$17,%lo(rtl_get_skb_dev)
	jalr	$17
	move	$4,$19

	move	$5,$2
	lui	$2,%hi(rtl_set_skb_rx_dev)
	addiu	$2,$2,%lo(rtl_set_skb_rx_dev)
	jalr	$2
	move	$4,$19

	lui	$2,%hi(rtl_set_skb_protocol)
	move	$4,$19
	addiu	$2,$2,%lo(rtl_set_skb_protocol)
	jalr	$2
	li	$5,2048			# 0x800

	lui	$2,%hi(rtl_set_skb_dev)
	move	$5,$16
	addiu	$2,$2,%lo(rtl_set_skb_dev)
	jalr	$2
	move	$4,$19

	jalr	$17
	move	$4,$19

	lw	$3,128($2)
	move	$4,$19
	addiu	$3,$3,1
	jalr	$17
	sw	$3,128($2)

	lw	$17,136($2)
	move	$16,$2
	lui	$2,%hi(rtl_get_skb_len)
	addiu	$2,$2,%lo(rtl_get_skb_len)
	jalr	$2
	move	$4,$19

	addu	$2,$2,$17
	sw	$2,136($16)
	move	$4,$19
	jalr	$21
	li	$5,1			# 0x1

	lui	$2,%hi(jiffies)
	lw	$3,%lo(jiffies)($2)
	li	$2,1			# 0x1
	j	$L75
	sw	$3,56($23)

$L81:
	move	$2,$0
$L75:
	lw	$31,60($sp)
	lw	$fp,56($sp)
	lw	$23,52($sp)
	lw	$22,48($sp)
	lw	$21,44($sp)
	lw	$20,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
	.end	check_and_pull_pppoe_hdr
	.size	check_and_pull_pppoe_hdr, .-check_and_pull_pppoe_hdr
	.section	___ksymtab+fast_pppoe_xmit,"a",@progbits
	.align	2
	.type	__ksymtab_fast_pppoe_xmit, @object
	.size	__ksymtab_fast_pppoe_xmit, 8
__ksymtab_fast_pppoe_xmit:
	.word	fast_pppoe_xmit
	.word	__kstrtab_fast_pppoe_xmit
	.section	___ksymtab+check_and_restore_pppoe_hdr,"a",@progbits
	.align	2
	.type	__ksymtab_check_and_restore_pppoe_hdr, @object
	.size	__ksymtab_check_and_restore_pppoe_hdr, 8
__ksymtab_check_and_restore_pppoe_hdr:
	.word	check_and_restore_pppoe_hdr
	.word	__kstrtab_check_and_restore_pppoe_hdr
	.section	___ksymtab+check_and_pull_pppoe_hdr,"a",@progbits
	.align	2
	.type	__ksymtab_check_and_pull_pppoe_hdr, @object
	.size	__ksymtab_check_and_pull_pppoe_hdr, 8
__ksymtab_check_and_pull_pppoe_hdr:
	.word	check_and_pull_pppoe_hdr
	.word	__kstrtab_check_and_pull_pppoe_hdr
	.section	___ksymtab+fast_pppoe_exit,"a",@progbits
	.align	2
	.type	__ksymtab_fast_pppoe_exit, @object
	.size	__ksymtab_fast_pppoe_exit, 8
__ksymtab_fast_pppoe_exit:
	.word	fast_pppoe_exit
	.word	__kstrtab_fast_pppoe_exit
	.section	___ksymtab+fast_pppoe_init,"a",@progbits
	.align	2
	.type	__ksymtab_fast_pppoe_init, @object
	.size	__ksymtab_fast_pppoe_init, 8
__ksymtab_fast_pppoe_init:
	.word	fast_pppoe_init
	.word	__kstrtab_fast_pppoe_init
	.globl	fastpath_pppoe_proc_fops
	.data
	.align	2
	.type	fastpath_pppoe_proc_fops, @object
	.size	fastpath_pppoe_proc_fops, 108
fastpath_pppoe_proc_fops:
	.space	4
	.word	seq_lseek
	.word	seq_read
	.word	fastpath_pppoe_single_write
	.space	28
	.word	fastpath_pppoe_single_open
	.space	4
	.word	single_release
	.space	52
	.globl	fast_pppoe_proc
	.section	.bss,"aw",@nobits
	.align	2
	.type	fast_pppoe_proc, @object
	.size	fast_pppoe_proc, 4
fast_pppoe_proc:
	.space	4
	.globl	fast_pppoe_info
	.align	2
	.type	fast_pppoe_info, @object
	.size	fast_pppoe_info, 1408
fast_pppoe_info:
	.space	1408
	.section	__ksymtab_strings,"a",@progbits
	.type	__kstrtab_fast_pppoe_xmit, @object
	.size	__kstrtab_fast_pppoe_xmit, 16
__kstrtab_fast_pppoe_xmit:
	.ascii	"fast_pppoe_xmit\000"
	.type	__kstrtab_check_and_restore_pppoe_hdr, @object
	.size	__kstrtab_check_and_restore_pppoe_hdr, 28
__kstrtab_check_and_restore_pppoe_hdr:
	.ascii	"check_and_restore_pppoe_hdr\000"
	.type	__kstrtab_check_and_pull_pppoe_hdr, @object
	.size	__kstrtab_check_and_pull_pppoe_hdr, 25
__kstrtab_check_and_pull_pppoe_hdr:
	.ascii	"check_and_pull_pppoe_hdr\000"
	.type	__kstrtab_fast_pppoe_exit, @object
	.size	__kstrtab_fast_pppoe_exit, 16
__kstrtab_fast_pppoe_exit:
	.ascii	"fast_pppoe_exit\000"
	.type	__kstrtab_fast_pppoe_init, @object
	.size	__kstrtab_fast_pppoe_init, 16
__kstrtab_fast_pppoe_init:
	.ascii	"fast_pppoe_init\000"
	.ident	"GCC: (Realtek RSDK-4.6.4 Build 424) 4.6.4"
