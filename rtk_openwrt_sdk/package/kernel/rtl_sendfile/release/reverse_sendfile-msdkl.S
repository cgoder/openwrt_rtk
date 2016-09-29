	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
$Ltext0:
	.cfi_sections	.debug_frame
	.align	2
	.globl	rtl_tcp_ctl_init
$LFB3380 = .
	.file 1 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/rtl_sendfile-0.1/reverse_sendfile.c"
	.loc 1 120 0
	.cfi_startproc
	.set	nomips16
	.ent	rtl_tcp_ctl_init
	.type	rtl_tcp_ctl_init, @function
rtl_tcp_ctl_init:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 121 0
	lui	$4,%hi(g2_tcp_ctl)
	li	$3,1			# 0x1
	.loc 1 122 0
	addiu	$2,$4,%lo(g2_tcp_ctl)
	.loc 1 121 0
	sw	$3,%lo(g2_tcp_ctl)($4)
	.loc 1 123 0
	li	$4,16			# 0x10
	sw	$4,8($2)
	.loc 1 124 0
	li	$4,8192			# 0x2000
	sw	$4,12($2)
	.loc 1 125 0
	li	$4,4096			# 0x1000
	sw	$4,16($2)
	.loc 1 126 0
	li	$4,2			# 0x2
	.loc 1 122 0
	sw	$3,4($2)
	.loc 1 126 0
	sw	$4,20($2)
	.loc 1 127 0
	sw	$3,24($2)
	.loc 1 128 0
	j	$31
	sw	$0,28($2)

	.set	macro
	.set	reorder
	.end	rtl_tcp_ctl_init
	.cfi_endproc
$LFE3380:
	.size	rtl_tcp_ctl_init, .-rtl_tcp_ctl_init
	.align	2
	.globl	rtl_splice_from_pipe_feed
$LFB3391 = .
	.loc 1 743 0
	.cfi_startproc
	.set	nomips16
	.ent	rtl_splice_from_pipe_feed
	.type	rtl_splice_from_pipe_feed, @function
rtl_splice_from_pipe_feed:
	.frame	$sp,48,$31		# vars= 0, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 746 0
	lui	$2,%hi(rtl_pipe_to_sendpages)
	.loc 1 743 0
	addiu	$sp,$sp,-48
	.cfi_def_cfa_offset 48
	.loc 1 746 0
	addiu	$2,$2,%lo(rtl_pipe_to_sendpages)
	.loc 1 743 0
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$16,20($sp)
	sw	$31,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$17,24($sp)
	.cfi_offset 19, -16
	.cfi_offset 18, -20
	.cfi_offset 16, -28
	.cfi_offset 31, -4
	.cfi_offset 21, -8
	.cfi_offset 20, -12
	.cfi_offset 17, -24
	.loc 1 743 0
	move	$19,$6
	move	$18,$4
	.loc 1 746 0
	beq	$6,$2,$L3
	move	$16,$5

$LBB80 = .
	.loc 1 820 0
	li	$20,1			# 0x1
$L20:
$LBE80 = .
	.loc 1 788 0
	lw	$2,20($18)
$LBB81 = .
	.loc 1 796 0
	move	$4,$18
$LBE81 = .
	.loc 1 788 0
	bne	$2,$0,$L4
	move	$6,$16

	.loc 1 826 0
	j	$L7
	li	$2,1			# 0x1

$L3:
$LBB82 = .
	.loc 1 750 0
	lw	$2,4($5)
	.loc 1 747 0
	lw	$3,24($4)
	.loc 1 750 0
	bne	$2,$0,$L6
	lw	$5,68($4)

$LBE82 = .
	.loc 1 826 0
	j	$L7
	li	$2,1			# 0x1

$L6:
$LBB83 = .
	.loc 1 747 0
	sll	$2,$3,3
	sll	$3,$3,5
	subu	$17,$3,$2
	addu	$17,$5,$17
	.loc 1 751 0
	move	$5,$17
	jal	rtl_pipe_to_sendpages
	move	$6,$16

	.loc 1 752 0
	bgtz	$2,$L9
	move	$19,$2

$L32:
	.loc 1 753 0
	li	$3,-61			# 0xffffffffffffffc3
	bne	$2,$3,$L34
	lw	$31,44($sp)

$LBE83 = .
	.loc 1 754 0
	j	$L34
	move	$2,$0

$L12:
$LBB84 = .
	.loc 1 760 0
	lw	$3,12($17)
	.loc 1 761 0
	sw	$0,12($17)
	.loc 1 759 0
	subu	$19,$19,$2
	.loc 1 762 0
	lw	$2,16($3)
	jalr	$2
	nop

	.loc 1 764 0
	lw	$4,24($18)
	lw	$2,28($18)
	.loc 1 765 0
	lw	$3,20($18)
	.loc 1 764 0
	addiu	$4,$4,1
	addiu	$2,$2,-1
	and	$2,$2,$4
	.loc 1 769 0
	sll	$4,$2,3
	sll	$17,$2,5
	.loc 1 765 0
	addiu	$3,$3,-1
	.loc 1 769 0
	subu	$4,$17,$4
	.loc 1 764 0
	sw	$2,24($18)
	.loc 1 766 0
	beq	$19,$0,$L11
	sw	$3,20($18)

	.loc 1 769 0
	lw	$17,68($18)
	addu	$17,$17,$4
$L9:
	.loc 1 758 0 discriminator 1
	lw	$2,8($17)
	.loc 1 762 0 discriminator 1
	move	$5,$17
	.loc 1 758 0 discriminator 1
	sltu	$3,$19,$2
	beq	$3,$0,$L12
	move	$4,$18

	.loc 1 771 0
	beq	$19,$0,$L11
	subu	$2,$2,$19

	.loc 1 772 0
	lw	$3,4($17)
	.loc 1 773 0
	sw	$2,8($17)
	.loc 1 772 0
	addu	$19,$3,$19
	sw	$19,4($17)
$L11:
	.loc 1 777 0
	lw	$2,40($18)
	beq	$2,$0,$L14
	nop

	.loc 1 781 0
	li	$2,1			# 0x1
	sb	$2,32($16)
$L14:
	.loc 1 783 0
	lw	$2,4($16)
	j	$L7
	sltu	$2,$0,$2

$L4:
$LBE84 = .
$LBB85 = .
	.loc 1 789 0
	lw	$2,24($18)
	lw	$17,68($18)
	.loc 1 793 0
	lw	$3,4($16)
	.loc 1 789 0
	sll	$5,$2,3
	sll	$2,$2,5
	subu	$2,$2,$5
	addu	$17,$17,$2
	.loc 1 792 0
	lw	$2,8($17)
	.loc 1 790 0
	lw	$21,12($17)
	.loc 1 796 0
	move	$5,$17
	.loc 1 793 0
	sltu	$7,$3,$2
	beq	$7,$0,$L15
	sw	$2,0($16)

	.loc 1 794 0
	sw	$3,0($16)
$L15:
	.loc 1 796 0
	jalr	$19
	nop

	.loc 1 797 0
	blez	$2,$L32
	sra	$6,$2,31

	.loc 1 802 0
	lw	$3,4($17)
	.loc 1 803 0
	lw	$4,8($17)
	.loc 1 802 0
	addu	$3,$3,$2
	.loc 1 803 0
	subu	$4,$4,$2
	sw	$4,8($17)
	.loc 1 802 0
	sw	$3,4($17)
	.loc 1 807 0
	lw	$5,16($16)
	lw	$9,20($16)
	.loc 1 805 0
	lw	$7,28($16)
	.loc 1 806 0
	lw	$8,0($16)
	.loc 1 808 0
	lw	$3,4($16)
	.loc 1 807 0
	addu	$4,$5,$2
	sltu	$5,$4,$5
	addu	$6,$9,$6
	.loc 1 808 0
	subu	$3,$3,$2
	.loc 1 805 0
	addu	$7,$7,$2
	.loc 1 807 0
	addu	$6,$5,$6
	.loc 1 806 0
	subu	$2,$8,$2
	.loc 1 808 0
	sw	$3,4($16)
	.loc 1 805 0
	sw	$7,28($16)
	.loc 1 806 0
	sw	$2,0($16)
	.loc 1 807 0
	sw	$4,16($16)
	sw	$6,20($16)
	.loc 1 810 0
	lw	$2,8($17)
	bne	$2,$0,$L18
	move	$4,$18

	.loc 1 811 0
	sw	$0,12($17)
	.loc 1 812 0
	lw	$2,16($21)
	jalr	$2
	move	$5,$17

	.loc 1 813 0
	lw	$4,24($18)
	lw	$5,28($18)
	.loc 1 814 0
	lw	$3,20($18)
	.loc 1 813 0
	addiu	$4,$4,1
	addiu	$5,$5,-1
	.loc 1 816 0
	lw	$2,40($18)
	.loc 1 814 0
	addiu	$3,$3,-1
	.loc 1 813 0
	and	$4,$5,$4
	sw	$4,24($18)
	.loc 1 814 0
	sw	$3,20($18)
	.loc 1 816 0
	beq	$2,$0,$L18
	lw	$3,4($16)

	.loc 1 820 0
	sb	$20,32($16)
$L18:
	.loc 1 822 0
	bne	$3,$0,$L20
	move	$2,$0

$L7:
$LBE85 = .
	.loc 1 827 0
	lw	$31,44($sp)
$L34:
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,48

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	rtl_splice_from_pipe_feed
	.cfi_endproc
$LFE3391:
	.size	rtl_splice_from_pipe_feed, .-rtl_splice_from_pipe_feed
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"%s: err=-EPIPE!!!\015\012\000"
	.align	2
$LC1:
	.ascii	"*** psize=%d poffset=%d mss_now=%d size_goal=%d ***\012\000"
	.align	2
$LC2:
	.ascii	"%s: goto wait_for_memory\015\012\000"
	.align	2
$LC3:
	.ascii	"%s: skb->len=%d, page_count=%d\015\012\000"
	.align	2
$LC4:
	.ascii	"%s: sk_stream_wait_memory(), err=%d\015\012\000"
	.align	2
$LC5:
	.ascii	"%s: wait_for_memory(), mss_now=%d, size_goal=%d\015\012\000"
	.text
	.align	2
	.globl	tcp_sendpages
$LFB3382 = .
	.loc 1 363 0
	.cfi_startproc
	.set	nomips16
	.ent	tcp_sendpages
	.type	tcp_sendpages, @function
tcp_sendpages:
	.frame	$sp,160,$31		# vars= 96, regs= 10/0, args= 24, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-160
	.cfi_def_cfa_offset 160
	sw	$fp,152($sp)
	sw	$21,140($sp)
	.cfi_offset 30, -8
	.cfi_offset 21, -20
	move	$fp,$5
	sw	$20,136($sp)
	move	$21,$4
	.loc 1 368 0
	move	$5,$0
	addiu	$4,$sp,24
	.cfi_offset 20, -24
	.loc 1 363 0
	move	$20,$6
	.loc 1 368 0
	li	$6,64			# 0x40
	.loc 1 363 0
	sw	$31,156($sp)
	sw	$22,144($sp)
	sw	$19,132($sp)
	sw	$23,148($sp)
	.cfi_offset 31, -4
	.cfi_offset 22, -16
	.cfi_offset 19, -28
	.cfi_offset 23, -12
	move	$19,$7
	sw	$18,128($sp)
	sw	$17,124($sp)
	sw	$16,120($sp)
	.cfi_offset 18, -32
	.cfi_offset 17, -36
	.cfi_offset 16, -40
	.loc 1 368 0
	.set	noreorder
	.set	nomacro
	jal	memset
	lw	$22,176($sp)
	.set	macro
	.set	reorder

	.loc 1 369 0
	lw	$2,24($fp)
	lw	$3,68($fp)
	.loc 1 374 0
	move	$4,$21
	.loc 1 369 0
	sll	$5,$2,3
	sll	$2,$2,5
	subu	$2,$2,$5
	addu	$3,$3,$2
	.loc 1 374 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_sk_route_caps
	sw	$3,96($sp)
	.set	macro
	.set	reorder

	andi	$2,$2,0x1
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L36
	lw	$17,96($sp)
	.set	macro
	.set	reorder

$L105:
	.loc 1 363 0
	move	$16,$0
	.loc 1 386 0
	.set	noreorder
	.set	nomacro
	j	$L37
	li	$23,4096			# 0x1000
	.set	macro
	.set	reorder

$L36:
	.loc 1 376 0 discriminator 1
	.set	noreorder
	.set	nomacro
	jal	rtl_get_sk_route_caps
	move	$4,$21
	.set	macro
	.set	reorder

	andi	$2,$2,0x1a
	.loc 1 374 0 discriminator 1
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L105
	lw	$17,96($sp)
	.set	macro
	.set	reorder

	lw	$4,20($fp)
	lw	$2,96($sp)
	addiu	$3,$sp,24
	sll	$5,$4,3
	sll	$4,$4,5
	subu	$5,$4,$5
	.set	noreorder
	.set	nomacro
	j	$L40
	addu	$5,$2,$5
	.set	macro
	.set	reorder

$L37:
	.loc 1 385 0
	addu	$3,$16,$20
	andi	$3,$3,0xfff
$LBB98 = .
	.loc 1 386 0
	subu	$3,$23,$3
	subu	$2,$19,$16
	sltu	$18,$2,$3
	movz	$2,$3,$18
	move	$18,$2
$LBE98 = .
	.loc 1 379 0
	lw	$2,0($17)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L99
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 379 0 is_stmt 0 discriminator 1
	.set	noreorder
	.set	nomacro
	beq	$16,$19,$L104
	lw	$31,156($sp)
	.set	macro
	.set	reorder

	.loc 1 388 0 is_stmt 1
	jal	rtl_get_sk_socket
	lw	$5,0($17)
	move	$4,$2
	sw	$22,16($sp)
	move	$6,$20
	.set	noreorder
	.set	nomacro
	jal	sock_no_sendpage
	move	$7,$18
	.set	macro
	.set	reorder

	.loc 1 390 0
	bgez	$2,$L44
	.set	noreorder
	.set	nomacro
	j	$L99
	movz	$16,$2,$16
	.set	macro
	.set	reorder

$L44:
	.loc 1 396 0
	.set	noreorder
	.set	nomacro
	bne	$18,$2,$L37
	addu	$16,$16,$2
	.set	macro
	.set	reorder

	.loc 1 396 0 is_stmt 0 discriminator 1
	lw	$2,20($fp)
	.loc 1 397 0 is_stmt 1 discriminator 1
	addiu	$3,$17,24
	.loc 1 396 0 discriminator 1
	sll	$4,$2,3
	sll	$2,$2,5
	subu	$2,$2,$4
	lw	$4,96($sp)
	addu	$2,$4,$2
	sltu	$2,$17,$2
	.set	noreorder
	.set	nomacro
	j	$L37
	movn	$17,$3,$2
	.set	macro
	.set	reorder

$L46:
	.loc 1 404 0 discriminator 2
	lw	$4,0($2)
	addiu	$2,$2,24
	sw	$4,-4($3)
$L40:
	.loc 1 403 0 discriminator 1
	.set	noreorder
	.set	nomacro
	bne	$2,$5,$L46
	addiu	$3,$3,4
	.set	macro
	.set	reorder

$LBB99 = .
$LBB100 = .
	.file 2 "include/net/sock.h"
	.loc 2 1468 0
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jal	lock_sock_nested
	move	$5,$0
	.set	macro
	.set	reorder

$LBE100 = .
$LBE99 = .
$LBB101 = .
$LBB102 = .
	.loc 1 140 0
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jal	rtl_sk_sndtimeo
	move	$5,$22
	.set	macro
	.set	reorder

	.loc 1 145 0
	lbu	$3,18($21)
	.loc 1 140 0
	sw	$2,88($sp)
	.loc 1 145 0
	li	$2,-259			# 0xfffffffffffffefd
	sra	$2,$2,$3
	andi	$2,$2,0x1
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L47
	move	$4,$21
	.set	macro
	.set	reorder

$L50:
	.loc 1 152 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_sk_socket
	move	$4,$21
	.set	macro
	.set	reorder

$LBE102 = .
$LBE101 = .
	.file 3 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/bitops.h"
	.loc 3 128 0
	.set	noreorder
	.set	nomacro
	j	$L48
	addiu	$2,$2,8
	.set	macro
	.set	reorder

$L47:
$LBB130 = .
$LBB119 = .
	.loc 1 146 0
	.set	noreorder
	.set	nomacro
	jal	sk_stream_wait_connect
	addiu	$5,$sp,88
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L49
	move	$16,$2
	.set	macro
	.set	reorder

	j	$L50
$L48:
$LBB103 = .
$LBB104 = .
	.loc 3 145 0
#APP
 # 145 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/bitops.h" 1
		ll	$3, 0($2)		# clear_bit	
	ins	$3, $0, 0, 1			
	sc	$3, 0($2)				

 # 0 "" 2
	.loc 3 151 0
#NO_APP
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L48
	move	$4,$21
	.set	macro
	.set	reorder

$LBE104 = .
$LBE103 = .
	.loc 1 153 0
	addiu	$5,$sp,92
	.set	noreorder
	.set	nomacro
	jal	tcp_send_mss
	move	$6,$22
	.set	macro
	.set	reorder

	sw	$2,108($sp)
	.loc 1 162 0
	lui	$2,%hi(g2_tcp_ctl)
	addiu	$fp,$2,%lo(g2_tcp_ctl)
	lw	$2,8($fp)
	sltu	$3,$2,2
	.set	noreorder
	.set	nomacro
	bne	$3,$0,$L53
	sll	$2,$2,12
	.set	macro
	.set	reorder

	.loc 1 163 0
	addiu	$2,$2,-4096
$L53:
	.loc 1 166 0
	lw	$3,92($sp)
	slt	$3,$2,$3
	beq	$3,$0,$L54
	.loc 1 167 0
	sw	$2,92($sp)
$L54:
	.loc 1 173 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_sk_err
	move	$4,$21
	.set	macro
	.set	reorder

	beq	$2,$0,$L55
$L56:
	.loc 1 175 0
	lui	$4,%hi($LC0)
	lui	$5,%hi(__func__.41332)
	addiu	$4,$4,%lo($LC0)
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$5,$5,%lo(__func__.41332)
	.set	macro
	.set	reorder

$LBE119 = .
$LBE130 = .
	.loc 1 171 0
	.set	noreorder
	.set	nomacro
	j	$L49
	li	$16,-32			# 0xffffffffffffffe0
	.set	macro
	.set	reorder

$L55:
$LBB131 = .
$LBB120 = .
	.loc 1 173 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_sk_shutdown
	move	$4,$21
	.set	macro
	.set	reorder

	andi	$2,$2,0x2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L56
	li	$2,3			# 0x3
	.set	macro
	.set	reorder

	.loc 1 179 0
	lw	$3,4($fp)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L106
	li	$2,2			# 0x2
	.set	macro
	.set	reorder

	.loc 1 181 0
	lw	$16,92($sp)
	.set	noreorder
	.set	nomacro
	jal	rtl_get_tp_snd_wnd
	move	$4,$21
	.set	macro
	.set	reorder

	sltu	$2,$16,$2
	beq	$2,$0,$L58
	.set	noreorder
	.set	nomacro
	j	$L57
	lw	$3,4($fp)
	.set	macro
	.set	reorder

$L58:
	.loc 1 182 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_tp_snd_wnd
	move	$4,$21
	.set	macro
	.set	reorder

	lw	$3,4($fp)
	sw	$2,92($sp)
$L57:
	.loc 1 185 0
	li	$2,2			# 0x2
$L106:
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L107
	li	$2,-65536			# 0xffffffffffff0000
	.set	macro
	.set	reorder

	.loc 1 187 0
	lw	$2,92($sp)
	lw	$7,108($sp)
	lui	$4,%hi($LC1)
	addiu	$4,$4,%lo($LC1)
	sw	$2,16($sp)
	move	$5,$19
	.set	noreorder
	.set	nomacro
	jal	printk
	move	$6,$20
	.set	macro
	.set	reorder

$LBB105 = .
	.loc 1 319 0
	li	$2,-65536			# 0xffffffffffff0000
$L107:
	addiu	$2,$2,32767
	and	$2,$22,$2
	.loc 1 306 0
	sw	$0,100($sp)
	sw	$0,104($sp)
	sw	$0,112($sp)
$LBE105 = .
$LBE120 = .
$LBE131 = .
	.loc 1 319 0
	.set	noreorder
	.set	nomacro
	j	$L60
	sw	$2,116($sp)
	.set	macro
	.set	reorder

$L82:
$LBB132 = .
$LBB121 = .
$LBB111 = .
	.loc 1 193 0
	.set	noreorder
	.set	nomacro
	jal	rtl_tcp_write_queue_tail
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 194 0
	srl	$3,$20,12
	addiu	$4,$sp,24
	sll	$3,$3,2
	addu	$3,$4,$3
	.loc 1 193 0
	move	$16,$2
	.loc 1 196 0
	andi	$18,$20,0xfff
$LBB106 = .
	.loc 1 197 0
	li	$2,4096			# 0x1000
	subu	$2,$2,$18
$LBE106 = .
	.loc 1 194 0
	lw	$3,0($3)
$LBB107 = .
	.loc 1 197 0
	sltu	$17,$19,$2
	movn	$2,$19,$17
$LBE107 = .
	.loc 1 201 0
	move	$4,$21
	.loc 1 194 0
	sw	$3,96($sp)
	.loc 1 201 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_tcp_send_head
	move	$17,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L61
	lw	$23,92($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len_common
	move	$4,$16
	.set	macro
	.set	reorder

	subu	$2,$23,$2
	bgtz	$2,$L62
$L61:
	.loc 1 204 0
	.set	noreorder
	.set	nomacro
	jal	rtl_sk_stream_memory_free
	move	$4,$21
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L63
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 210 0
	jal	rtl_get_sk_allocation
	move	$6,$2
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jal	sk_stream_alloc_skb
	move	$5,$0
	.set	macro
	.set	reorder

	.loc 1 211 0
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L64
	move	$16,$2
	.set	macro
	.set	reorder

	.loc 1 213 0
	lui	$2,%hi($LC2)
	lui	$5,%hi(__func__.41332)
	addiu	$4,$2,%lo($LC2)
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$5,$5,%lo(__func__.41332)
	.set	macro
	.set	reorder

$LBE111 = .
$LBE121 = .
$LBE132 = .
	.loc 1 316 0
	.set	noreorder
	.set	nomacro
	j	$L101
	lw	$2,100($sp)
	.set	macro
	.set	reorder

$L64:
$LBB133 = .
$LBB122 = .
$LBB112 = .
	.loc 1 219 0
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_entail
	move	$5,$2
	.set	macro
	.set	reorder

	.loc 1 217 0
	li	$3,1			# 0x1
	sw	$3,112($sp)
$L62:
	.loc 1 226 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared_info
	move	$4,$16
	.set	macro
	.set	reorder

	lbu	$23,0($2)
	.loc 1 228 0
	lw	$6,96($sp)
	move	$4,$16
	move	$5,$23
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_can_coalesce
	move	$7,$18
	.set	macro
	.set	reorder

	.loc 1 229 0
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L66
	move	$4,$21
	.set	macro
	.set	reorder

	sltu	$2,$23,17
	bne	$2,$0,$L67
	.loc 1 232 0
	.set	noreorder
	.set	nomacro
	jal	rtl_tcp_mark_push
	move	$5,$16
	.set	macro
	.set	reorder

	j	$L61
$L84:
	.loc 1 242 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared_info
	move	$4,$16
	.set	macro
	.set	reorder

	addiu	$3,$23,-1
	sll	$3,$3,3
	addu	$2,$2,$3
	lhu	$3,50($2)
	addu	$3,$17,$3
$LBE112 = .
$LBE122 = .
$LBE133 = .
	.set	noreorder
	.set	nomacro
	j	$L68
	sh	$3,50($2)
	.set	macro
	.set	reorder

$L85:
$LBB134 = .
$LBB123 = .
$LBB113 = .
	.loc 1 246 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_page
	lw	$4,96($sp)
	.set	macro
	.set	reorder

	.loc 1 248 0
	lw	$6,96($sp)
	sw	$17,16($sp)
	move	$4,$16
	move	$5,$23
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_fill_page_desc
	move	$7,$18
	.set	macro
	.set	reorder

$L68:
	.loc 1 252 0
	move	$4,$16
	.set	noreorder
	.set	nomacro
	jal	rtl_add_skb_len_common
	move	$5,$17
	.set	macro
	.set	reorder

	.loc 1 254 0
	move	$4,$16
	.set	noreorder
	.set	nomacro
	jal	rtl_add_skb_data_len_common
	move	$5,$17
	.set	macro
	.set	reorder

	.loc 1 256 0
	move	$4,$16
	.set	noreorder
	.set	nomacro
	jal	rtl_add_skb_truesize_common
	move	$5,$17
	.set	macro
	.set	reorder

	.loc 1 258 0
	move	$5,$17
	.set	noreorder
	.set	nomacro
	jal	rtl_add_skb_sk_wmem_queued
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 259 0
	lw	$2,96($21)
	.loc 1 261 0
	move	$4,$16
	.loc 1 259 0
	subu	$2,$2,$17
	.loc 1 261 0
	.set	noreorder
	.set	nomacro
	jal	rtl_set_tcp_skb_ip_summed
	sw	$2,96($21)
	.set	macro
	.set	reorder

	.loc 1 263 0
	move	$5,$17
	.set	noreorder
	.set	nomacro
	jal	rtl_add_tp_write_seq
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 265 0
	.set	noreorder
	.set	nomacro
	jal	rtl_TCP_SKB_CB
	move	$4,$16
	.set	macro
	.set	reorder

	move	$4,$2
	.set	noreorder
	.set	nomacro
	jal	rtl_add_skb_cb_end_seq
	move	$5,$17
	.set	macro
	.set	reorder

	.loc 1 267 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared_info
	move	$4,$16
	.set	macro
	.set	reorder

	.loc 1 269 0
	lw	$4,100($sp)
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L69
	sh	$0,4($2)
	.set	macro
	.set	reorder

	.loc 1 272 0
	.set	noreorder
	.set	nomacro
	jal	rtl_TCP_SKB_CB
	move	$4,$16
	.set	macro
	.set	reorder

	move	$4,$2
	.set	noreorder
	.set	nomacro
	jal	rtl_and_skb_cb_tcp_flags
	li	$5,-9			# 0xfffffffffffffff7
	.set	macro
	.set	reorder

$L69:
	.loc 1 274 0
	lw	$2,100($sp)
	.loc 1 276 0
	lw	$3,104($sp)
	.loc 1 277 0
	subu	$19,$19,$17
	.loc 1 274 0
	addu	$2,$2,$17
	.loc 1 276 0
	addiu	$3,$3,1
	.loc 1 274 0
	sw	$2,100($sp)
	.loc 1 275 0
	addu	$20,$20,$17
	.loc 1 277 0
	.set	noreorder
	.set	nomacro
	bne	$19,$0,$L70
	sw	$3,104($sp)
	.set	macro
	.set	reorder

	.loc 1 279 0
	lw	$3,4($fp)
	li	$2,2			# 0x2
	bne	$3,$2,$L71
	.loc 1 282 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len_common
	move	$4,$16
	.set	macro
	.set	reorder

	lw	$7,104($sp)
	lui	$4,%hi($LC3)
	lui	$5,%hi(__func__.41332)
	addiu	$4,$4,%lo($LC3)
	addiu	$5,$5,%lo(__func__.41332)
	.set	noreorder
	.set	nomacro
	jal	printk
	move	$6,$2
	.set	macro
	.set	reorder

$LBE113 = .
$LBE123 = .
$LBE134 = .
	.loc 1 349 0
	.set	noreorder
	.set	nomacro
	j	$L102
	lw	$3,100($sp)
	.set	macro
	.set	reorder

$L70:
$LBB135 = .
$LBB124 = .
$LBB114 = .
	.loc 1 288 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len_common
	move	$4,$16
	.set	macro
	.set	reorder

	lw	$3,92($sp)
	sltu	$2,$2,$3
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L60
	andi	$2,$22,0x1
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L60
	lw	$4,112($sp)
	.set	macro
	.set	reorder

	.loc 1 294 0
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L73
	lw	$3,104($sp)
	.set	macro
	.set	reorder

	lw	$2,8($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L60
$L73:
	.loc 1 296 0
	.set	noreorder
	.set	nomacro
	jal	forced_push
	move	$4,$21
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L74
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 299 0
	.set	noreorder
	.set	nomacro
	jal	rtl_tcp_mark_push
	move	$5,$16
	.set	macro
	.set	reorder

	.loc 1 300 0
	lw	$5,108($sp)
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jal	__tcp_push_pending_frames
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	.loc 1 307 0
	sw	$0,104($sp)
$LBE114 = .
$LBE124 = .
$LBE135 = .
	.loc 1 306 0
	.set	noreorder
	.set	nomacro
	j	$L60
	sw	$0,112($sp)
	.set	macro
	.set	reorder

$L74:
$LBB136 = .
$LBB125 = .
$LBB115 = .
	.loc 1 302 0
	jal	rtl_tcp_send_head
	.loc 1 307 0
	sw	$0,104($sp)
	.loc 1 302 0
	.set	noreorder
	.set	nomacro
	bne	$16,$2,$L60
	sw	$0,112($sp)
	.set	macro
	.set	reorder

	.loc 1 304 0
	lw	$5,108($sp)
	.set	noreorder
	.set	nomacro
	jal	tcp_push_one
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 306 0
	lw	$4,104($sp)
$LBE115 = .
$LBE125 = .
$LBE136 = .
	.set	noreorder
	.set	nomacro
	j	$L60
	sw	$4,112($sp)
	.set	macro
	.set	reorder

$L63:
$LBB137 = .
$LBB126 = .
$LBB116 = .
	.loc 1 314 0
	jal	rtl_get_sk_socket
$LBB108 = .
$LBB109 = .
	.loc 3 76 0
	addiu	$2,$2,8
	.loc 3 93 0
	li	$3,-1			# 0xffffffffffffffff
$L75:
#APP
 # 93 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/bitops.h" 1
		ll	$4, 0($2)		# set_bit	
	ins	$4, $3, 2, 1			
	sc	$4, 0($2)				

 # 0 "" 2
	.loc 3 99 0
#NO_APP
	beq	$4,$0,$L75
$L65 = .
$LBE109 = .
$LBE108 = .
	.loc 1 316 0
	lw	$2,100($sp)
$L101:
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L108
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 319 0
	lw	$5,116($sp)
	lw	$6,108($sp)
	.set	noreorder
	.set	nomacro
	jal	rtl_tcp_push
	li	$7,4			# 0x4
	.set	macro
	.set	reorder

	.loc 1 322 0
	move	$4,$21
$L108:
	.set	noreorder
	.set	nomacro
	jal	sk_stream_wait_memory
	addiu	$5,$sp,88
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L77
	move	$16,$2
	.set	macro
	.set	reorder

	.loc 1 324 0
	lw	$3,4($fp)
	li	$2,2			# 0x2
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L78
	lui	$4,%hi($LC4)
	.set	macro
	.set	reorder

	.loc 1 325 0
	lui	$5,%hi(__func__.41332)
	addiu	$4,$4,%lo($LC4)
	addiu	$5,$5,%lo(__func__.41332)
	.set	noreorder
	.set	nomacro
	jal	printk
	move	$6,$16
	.set	macro
	.set	reorder

$LBE116 = .
$LBE126 = .
$LBE137 = .
	.loc 1 355 0
	.set	noreorder
	.set	nomacro
	j	$L103
	lw	$4,100($sp)
	.set	macro
	.set	reorder

$L77:
$LBB138 = .
$LBB127 = .
$LBB117 = .
	.loc 1 330 0
	move	$4,$21
	addiu	$5,$sp,92
	.set	noreorder
	.set	nomacro
	jal	tcp_send_mss
	move	$6,$22
	.set	macro
	.set	reorder

	sw	$2,108($sp)
	.loc 1 331 0
	lw	$2,8($fp)
	sltu	$3,$2,2
	.set	noreorder
	.set	nomacro
	bne	$3,$0,$L80
	sll	$2,$2,12
	.set	macro
	.set	reorder

	.loc 1 332 0
	addiu	$2,$2,-4096
$L80:
	.loc 1 336 0
	lw	$3,92($sp)
	slt	$3,$2,$3
	beq	$3,$0,$L81
	.loc 1 337 0
	sw	$2,92($sp)
$L81:
$LBB110 = .
	.loc 1 339 0
	jal	_cond_resched
$LBE110 = .
	.loc 1 341 0
	lw	$3,4($fp)
	li	$2,2			# 0x2
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L60
	lw	$7,92($sp)
	.set	macro
	.set	reorder

	.loc 1 343 0
	lw	$6,108($sp)
	lui	$4,%hi($LC5)
	lui	$5,%hi(__func__.41332)
	addiu	$4,$4,%lo($LC5)
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$5,$5,%lo(__func__.41332)
	.set	macro
	.set	reorder

$L60:
$LBE117 = .
	.loc 1 190 0
	bne	$19,$0,$L82
$L71:
	.loc 1 349 0
	lw	$3,100($sp)
$L102:
$L109:
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L83
	move	$16,$0
	.set	macro
	.set	reorder

	.loc 1 351 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_tcp_sock_nonagle
	move	$4,$21
	.set	macro
	.set	reorder

	lw	$6,108($sp)
	move	$4,$21
	move	$5,$22
	.set	noreorder
	.set	nomacro
	jal	rtl_tcp_push
	move	$7,$2
	.set	macro
	.set	reorder

$LBE127 = .
$LBE138 = .
	.set	noreorder
	.set	nomacro
	j	$L83
	lw	$16,100($sp)
	.set	macro
	.set	reorder

$L78:
$LBB139 = .
$LBB128 = .
	.loc 1 355 0
	lw	$4,100($sp)
$L103:
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L109
	lw	$3,100($sp)
	.set	macro
	.set	reorder

$L49:
	.loc 1 358 0
	move	$6,$16
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jal	sk_stream_error
	move	$5,$22
	.set	macro
	.set	reorder

	move	$16,$2
$L83:
$LBE128 = .
$LBE139 = .
	.loc 1 412 0
	.set	noreorder
	.set	nomacro
	jal	release_sock
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 413 0
	.set	noreorder
	.set	nomacro
	j	$L104
	lw	$31,156($sp)
	.set	macro
	.set	reorder

$L66:
$LBB140 = .
$LBB129 = .
$LBB118 = .
	.loc 1 236 0
	.set	noreorder
	.set	nomacro
	jal	rtl_sk_wmem_schedule
	move	$5,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L84
	lw	$2,100($sp)
	.set	macro
	.set	reorder

	j	$L101
$L67:
	.set	noreorder
	.set	nomacro
	jal	rtl_sk_wmem_schedule
	move	$5,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L85
	lw	$2,100($sp)
	.set	macro
	.set	reorder

	j	$L101
$L99:
$LBE118 = .
$LBE129 = .
$LBE140 = .
	.loc 1 414 0
	lw	$31,156($sp)
$L104:
	move	$2,$16
	lw	$fp,152($sp)
	lw	$23,148($sp)
	lw	$22,144($sp)
	lw	$21,140($sp)
	lw	$20,136($sp)
	lw	$19,132($sp)
	lw	$18,128($sp)
	lw	$17,124($sp)
	lw	$16,120($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,160
	.set	macro
	.set	reorder

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 23
	.cfi_restore 30
	.cfi_restore 31
	.end	tcp_sendpages
	.cfi_endproc
$LFE3382:
	.size	tcp_sendpages, .-tcp_sendpages
	.align	2
	.globl	inet_sendpages
$LFB3383 = .
	.loc 1 418 0
	.cfi_startproc
	.set	nomips16
	.ent	inet_sendpages
	.type	inet_sendpages, @function
inet_sendpages:
	.frame	$sp,40,$31		# vars= 0, regs= 6/0, args= 16, gp= 0
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	.cfi_def_cfa_offset 40
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$31,36($sp)
	sw	$16,16($sp)
	.cfi_offset 20, -8
	.cfi_offset 19, -12
	.cfi_offset 18, -16
	.cfi_offset 17, -20
	.cfi_offset 31, -4
	.cfi_offset 16, -24
	.loc 1 419 0
	lw	$16,20($4)
	.loc 1 418 0
	move	$17,$5
	move	$18,$6
	.loc 1 422 0
	move	$4,$16
	.loc 1 418 0
	move	$19,$7
	.loc 1 422 0
	jal	rtl_sock_rps_record_flow
	lw	$20,56($sp)

	.loc 1 426 0
	jal	rtl_get_sk_inet_num
	move	$4,$16

	beq	$2,$0,$L111
	nop

$L112:
	.loc 1 430 0
	sw	$20,56($sp)
	.loc 1 431 0
	lw	$31,36($sp)
	lw	$20,32($sp)
	.loc 1 430 0
	move	$4,$16
	move	$5,$17
	.loc 1 431 0
	lw	$16,16($sp)
	lw	$17,20($sp)
	.loc 1 430 0
	move	$6,$18
	move	$7,$19
	.loc 1 431 0
	lw	$18,24($sp)
	lw	$19,28($sp)
	.cfi_remember_state
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 31
	.loc 1 430 0
	j	tcp_sendpages
	addiu	$sp,$sp,40

	.cfi_def_cfa_offset 0
$L111:
	.cfi_restore_state
	.loc 1 426 0 discriminator 1
	jal	rtl_get_sk_no_autobind
	move	$4,$16

	bne	$2,$0,$L112
	nop

	.loc 1 427 0 discriminator 1
	jal	inet_autobind
	move	$4,$16

	.loc 1 426 0 discriminator 1
	beq	$2,$0,$L112
	lw	$31,36($sp)

	.loc 1 431 0
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	li	$2,-11			# 0xfffffffffffffff5
	j	$31
	addiu	$sp,$sp,40

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	inet_sendpages
	.cfi_endproc
$LFE3383:
	.size	inet_sendpages, .-inet_sendpages
	.align	2
	.globl	sock_sendpages
$LFB3385 = .
	.loc 1 443 0
	.cfi_startproc
	.set	nomips16
	.ent	sock_sendpages
	.type	sock_sendpages, @function
sock_sendpages:
	.frame	$sp,48,$31		# vars= 0, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	.cfi_def_cfa_offset 48
	sw	$21,40($sp)
	.cfi_offset 21, -8
	move	$21,$4
	sw	$31,44($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	.cfi_offset 31, -4
	.cfi_offset 20, -12
	.cfi_offset 19, -16
	lw	$20,68($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	.cfi_offset 18, -20
	.cfi_offset 17, -24
	move	$18,$5
	move	$17,$6
	sw	$16,20($sp)
	.cfi_offset 16, -28
	.loc 1 448 0
	jal	rtl_get_file_private_data
	move	$16,$7

	.loc 1 450 0
	move	$4,$21
	jal	rtl_get_file_flags
	move	$19,$2

	andi	$2,$2,0x80
	li	$3,64			# 0x40
	movz	$3,$0,$2
	.loc 1 452 0
	ori	$2,$3,0x8000
	movn	$3,$2,$20
	.loc 1 455 0
	lw	$31,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
$LBB141 = .
$LBB142 = .
	.loc 1 437 0
	move	$4,$19
	move	$5,$18
$LBE142 = .
$LBE141 = .
	.loc 1 455 0
	lw	$19,32($sp)
	lw	$18,28($sp)
$LBB145 = .
$LBB143 = .
	.loc 1 437 0
	move	$6,$17
	move	$7,$16
$LBE143 = .
$LBE145 = .
	.loc 1 455 0
	lw	$17,24($sp)
	lw	$16,20($sp)
$LBB146 = .
$LBB144 = .
	.loc 1 437 0
	sw	$3,64($sp)
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 31
	j	inet_sendpages
	addiu	$sp,$sp,48

	.cfi_def_cfa_offset 0
$LBE144 = .
$LBE146 = .
	.set	macro
	.set	reorder
	.end	sock_sendpages
	.cfi_endproc
$LFE3385:
	.size	sock_sendpages, .-sock_sendpages
	.section	.rodata.str1.4
	.align	2
$LC6:
	.ascii	"\0013%s confirm err=%d\012\000"
	.text
	.align	2
	.globl	rtl_pipe_to_sendpages
$LFB3386 = .
	.loc 1 459 0
	.cfi_startproc
	.set	nomips16
	.ent	rtl_pipe_to_sendpages
	.type	rtl_pipe_to_sendpages, @function
rtl_pipe_to_sendpages:
	.frame	$sp,64,$31		# vars= 8, regs= 8/0, args= 24, gp= 0
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-64
	.cfi_def_cfa_offset 64
	sw	$20,48($sp)
	sw	$19,44($sp)
	sw	$18,40($sp)
	sw	$17,36($sp)
	sw	$16,32($sp)
	sw	$31,60($sp)
	sw	$22,56($sp)
	sw	$21,52($sp)
	.cfi_offset 20, -16
	.cfi_offset 19, -20
	.cfi_offset 18, -24
	.cfi_offset 17, -28
	.cfi_offset 16, -32
	.cfi_offset 31, -4
	.cfi_offset 22, -8
	.cfi_offset 21, -12
	.loc 1 462 0
	lw	$2,16($6)
	lw	$3,20($6)
	.loc 1 459 0
	move	$19,$6
	move	$20,$5
	move	$18,$4
	.loc 1 461 0
	lw	$21,12($6)
	.loc 1 462 0
	sw	$2,24($sp)
	sw	$3,28($sp)
	.loc 1 460 0
	move	$16,$5
	.loc 1 466 0
	j	$L125
	move	$17,$0

$L128:
	.loc 1 467 0
	lw	$2,12($16)
	.loc 1 466 0
	addiu	$17,$17,1
	.loc 1 467 0
	lw	$2,12($2)
	jalr	$2
	addiu	$16,$16,24

	.loc 1 468 0
	beq	$2,$0,$L125
	move	$22,$2

	.loc 1 469 0
	lui	$4,%hi($LC6)
	lui	$5,%hi(__func__.41410)
	addiu	$4,$4,%lo($LC6)
	addiu	$5,$5,%lo(__func__.41410)
	jal	printk
	move	$6,$2

	.loc 1 470 0
	j	$L127
	move	$2,$22

$L125:
	.loc 1 466 0 discriminator 1
	lw	$2,20($18)
	.loc 1 467 0 discriminator 1
	move	$5,$16
	.loc 1 466 0 discriminator 1
	sltu	$2,$17,$2
	bne	$2,$0,$L128
	move	$4,$18

	.loc 1 476 0
	lw	$7,4($19)
	.loc 1 477 0
	lw	$2,8($19)
	.loc 1 478 0
	addiu	$3,$sp,24
	.loc 1 476 0
	sw	$7,0($19)
	.loc 1 478 0
	lw	$6,4($20)
	.loc 1 477 0
	ext	$2,$2,2,1
	.loc 1 478 0
	sw	$3,16($sp)
	sw	$2,20($sp)
	move	$4,$21
	jal	sock_sendpages
	move	$5,$18

	.loc 1 480 0
	bltz	$2,$L127
	sra	$8,$2,31

	.loc 1 484 0
	lw	$4,16($19)
	lw	$9,20($19)
	.loc 1 482 0
	lw	$7,28($19)
	.loc 1 483 0
	lw	$6,0($19)
	.loc 1 485 0
	lw	$5,4($19)
	.loc 1 484 0
	addu	$3,$4,$2
	sltu	$4,$3,$4
	addu	$8,$9,$8
	.loc 1 482 0
	addu	$7,$7,$2
	.loc 1 483 0
	subu	$6,$6,$2
	.loc 1 484 0
	addu	$4,$4,$8
	.loc 1 485 0
	subu	$5,$5,$2
	.loc 1 482 0
	sw	$7,28($19)
	.loc 1 483 0
	sw	$6,0($19)
	.loc 1 484 0
	sw	$3,16($19)
	sw	$4,20($19)
	.loc 1 485 0
	sw	$5,4($19)
$L127:
	.loc 1 488 0
	lw	$31,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,64

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	rtl_pipe_to_sendpages
	.cfi_endproc
$LFE3386:
	.size	rtl_pipe_to_sendpages, .-rtl_pipe_to_sendpages
	.align	2
	.globl	balance_dirty_pages_ratelimited_nr
$LFB3388 = .
	.loc 1 526 0
	.cfi_startproc
	.set	nomips16
	.ent	balance_dirty_pages_ratelimited_nr
	.type	balance_dirty_pages_ratelimited_nr, @function
balance_dirty_pages_ratelimited_nr:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.loc 1 531 0
	lw	$2,60($4)
	.loc 1 530 0
	lui	$6,%hi(ratelimit_pages)
	lw	$3,%lo(ratelimit_pages)($6)
	.loc 1 531 0
	lw	$7,112($2)
	.loc 1 530 0
	li	$2,8			# 0x8
	movz	$2,$3,$7
	.loc 1 538 0
	.loc 1 540 0
	lui	$3,%hi(bdp_ratelimits)
	lw	$7,%lo(bdp_ratelimits)($3)
	addu	$5,$5,$7
	.loc 1 541 0
	sltu	$2,$5,$2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L133
	sw	$5,%lo(bdp_ratelimits)($3)
	.set	macro
	.set	reorder

$LBB147 = .
$LBB148 = .
	.loc 1 502 0
	lw	$2,%lo(ratelimit_pages)($6)
$LBE148 = .
$LBE147 = .
	.loc 1 543 0
	sw	$0,%lo(bdp_ratelimits)($3)
	sltu	$3,$5,$2
	movn	$5,$2,$3
	.loc 1 544 0
$LBB150 = .
$LBB149 = .
	.loc 1 505 0
	srl	$2,$5,1
$LBE149 = .
$LBE150 = .
	.loc 1 545 0
	.set	noreorder
	.set	nomacro
	j	balance_dirty_pages
	addu	$5,$2,$5
	.set	macro
	.set	reorder

$L133:
	.loc 1 548 0
	j	$31
	.end	balance_dirty_pages_ratelimited_nr
	.cfi_endproc
$LFE3388:
	.size	balance_dirty_pages_ratelimited_nr, .-balance_dirty_pages_ratelimited_nr
	.section	.rodata.str1.4
	.align	2
$LC7:
	.ascii	"%s: %d: %s:count(%d) exceed maxinum\012\000"
	.align	2
$LC8:
	.ascii	"/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_"
	.ascii	"v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_"
	.ascii	"20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/l"
	.ascii	"inux-rtkmipsel_rtl8197f/rtl_sendfile-0.1/reverse_sendfil"
	.ascii	"e.c\000"
	.align	2
$LC9:
	.ascii	"%s: %d: %s: write_end fail,ret = %d\012\000"
	.text
	.align	2
	.globl	do_splice_from_socket
$LFB3389 = .
	.loc 1 556 0
	.cfi_startproc
	.set	nomips16
	.ent	do_splice_from_socket
	.type	do_splice_from_socket, @function
do_splice_from_socket:
	.frame	$sp,672,$31		# vars= 600, regs= 10/0, args= 32, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-672
	.cfi_def_cfa_offset 672
	sw	$fp,664($sp)
	sw	$19,644($sp)
	sw	$6,680($sp)
	sw	$7,684($sp)
	sw	$31,668($sp)
	sw	$23,660($sp)
	sw	$22,656($sp)
	sw	$21,652($sp)
	sw	$20,648($sp)
	sw	$18,640($sp)
	sw	$17,636($sp)
	sw	$16,632($sp)
	.cfi_offset 30, -8
	.cfi_offset 19, -28
	.cfi_offset 31, -4
	.cfi_offset 23, -12
	.cfi_offset 22, -16
	.cfi_offset 21, -20
	.cfi_offset 20, -24
	.cfi_offset 18, -32
	.cfi_offset 17, -36
	.cfi_offset 16, -40
	.loc 1 556 0
	move	$fp,$4
	.loc 1 558 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_file_mapping
	sw	$5,676($sp)
	.set	macro
	.set	reorder

$LBB151 = .
$LBB152 = .
	.loc 1 571 0
	lw	$3,680($sp)
$LBE152 = .
$LBE151 = .
	.loc 1 558 0
	move	$19,$2
	.loc 1 559 0
	lw	$7,0($19)
$LBB155 = .
$LBB153 = .
	.loc 1 571 0
	addiu	$2,$3,8
	or	$2,$2,$3
	sw	$2,628($sp)
	lw	$6,628($sp)
	lw	$2,24($28)
	and	$2,$6,$2
$LBE153 = .
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L136
	sw	$7,624($sp)
	.set	macro
	.set	reorder

$LBB154 = .
	.loc 1 571 0 is_stmt 0 discriminator 1
	addiu	$4,$sp,608
	move	$5,$3
	li	$6,8			# 0x8
#APP
 # 571 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/rtl_sendfile-0.1/reverse_sendfile.c" 1
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
$LBE154 = .
$LBE155 = .
	.set	noreorder
	.set	nomacro
	bne	$6,$0,$L136
	li	$3,65536			# 0x10000
	.set	macro
	.set	reorder

	.loc 1 574 0 is_stmt 1
	lw	$2,684($sp)
	addiu	$3,$3,1
	sltu	$3,$2,$3
	.set	noreorder
	.set	nomacro
	bne	$3,$0,$L137
	lui	$4,%hi($LC7)
	.set	macro
	.set	reorder

	.loc 1 575 0
	lui	$5,%hi($LC8)
	lui	$7,%hi(__func__.41460)
	sw	$2,16($sp)
	addiu	$4,$4,%lo($LC7)
	addiu	$5,$5,%lo($LC8)
	li	$6,575			# 0x23f
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$7,$7,%lo(__func__.41460)
	.set	macro
	.set	reorder

	.loc 1 576 0
	.set	noreorder
	.set	nomacro
	j	$L156
	li	$2,-22			# 0xffffffffffffffea
	.set	macro
	.set	reorder

$L137:
	.loc 1 579 0
	.set	noreorder
	.set	nomacro
	jal	rtl_inode_mutex_lock
	lw	$4,624($sp)
	.set	macro
	.set	reorder

	.loc 1 582 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_inode_sb
	lw	$4,624($sp)
	.set	macro
	.set	reorder

	move	$4,$2
	.set	noreorder
	.set	nomacro
	jal	rtl_vfs_check_frozen
	li	$5,1			# 0x1
	.set	macro
	.set	reorder

	.loc 1 585 0
	lw	$3,60($19)
	lw	$2,0($28)
	.loc 1 588 0
	lw	$7,624($sp)
	move	$4,$fp
	addiu	$5,$sp,608
	.loc 1 585 0
	sw	$3,996($2)
	.loc 1 588 0
	.set	noreorder
	.set	nomacro
	jal	rtl_generic_write_checks
	addiu	$6,$sp,684
	.set	macro
	.set	reorder

	.loc 1 589 0
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L139
	move	$21,$2
	.set	macro
	.set	reorder

	.loc 1 589 0 is_stmt 0 discriminator 1
	lw	$2,684($sp)
	beq	$2,$0,$L152
	.loc 1 592 0 is_stmt 1
	.set	noreorder
	.set	nomacro
	jal	file_remove_suid
	move	$4,$fp
	.set	macro
	.set	reorder

	.loc 1 593 0
	.set	noreorder
	.set	nomacro
	jal	file_update_time
	move	$4,$fp
	.set	macro
	.set	reorder

	.loc 1 595 0
	lw	$18,684($sp)
	lw	$6,608($sp)
	lw	$7,612($sp)
	addiu	$20,$sp,440
	addiu	$16,$sp,48
	.loc 1 564 0
	move	$23,$0
$L146:
$LBB156 = .
	.loc 1 602 0
	andi	$22,$6,0xfff
	.loc 1 603 0
	li	$3,4096			# 0x1000
	subu	$2,$3,$22
	sltu	$17,$18,$2
	movn	$2,$18,$17
	.loc 1 607 0
	lw	$3,52($19)
	move	$17,$2
	sw	$2,16($sp)
	li	$2,1			# 0x1
	sw	$2,20($sp)
	addiu	$2,$sp,616
	sw	$2,24($sp)
	addiu	$2,$sp,576
	sw	$2,28($sp)
	lw	$2,20($3)
	move	$4,$fp
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$19
	.set	macro
	.set	reorder

	move	$21,$2
	.loc 1 609 0
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L141
	subu	$18,$18,$17
	.set	macro
	.set	reorder

	addiu	$16,$sp,48
$LBE156 = .
	.set	noreorder
	.set	nomacro
	j	$L142
	move	$17,$0
	.set	macro
	.set	reorder

$L143:
$LBB169 = .
	.loc 1 615 0 discriminator 2
	lw	$2,0($16)
	lw	$9,-16($16)
	lw	$8,4($16)
	lw	$3,52($19)
	lw	$6,-8($16)
	lw	$7,-4($16)
	sw	$2,16($sp)
	sw	$2,20($sp)
	sw	$9,24($sp)
	sw	$8,28($sp)
	lw	$2,24($3)
	.loc 1 613 0 discriminator 2
	addiu	$17,$17,1
	.loc 1 615 0 discriminator 2
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$16,$16,24
	.set	macro
	.set	reorder

$L142:
	.loc 1 613 0 discriminator 1
	slt	$2,$17,$23
	.loc 1 615 0 discriminator 1
	move	$4,$fp
	.loc 1 613 0 discriminator 1
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L143
	move	$5,$19
	.set	macro
	.set	reorder

$LBE169 = .
	.loc 1 680 0
	.set	noreorder
	.set	nomacro
	j	$L158
	lw	$2,0($28)
	.set	macro
	.set	reorder

$L141:
$LBB170 = .
$LBB157 = .
$LBB158 = .
$LBB159 = .
	.file 4 "include/linux/mm.h"
	.loc 4 771 0
	lui	$6,%hi(mem_map)
$LBE159 = .
$LBE158 = .
$LBE157 = .
	.loc 1 620 0
	lw	$4,616($sp)
$LBB166 = .
$LBB163 = .
$LBB160 = .
	.loc 4 771 0
	lw	$5,%lo(mem_map)($6)
$LBE160 = .
$LBE163 = .
$LBE166 = .
	.loc 1 621 0
	lw	$2,608($sp)
	lw	$3,612($sp)
$LBB167 = .
$LBB164 = .
$LBB161 = .
	.loc 4 771 0
	subu	$5,$4,$5
	sra	$5,$5,5
$LBE161 = .
$LBE164 = .
$LBE167 = .
	.loc 1 628 0
	addu	$6,$2,$17
$LBB168 = .
$LBB165 = .
$LBB162 = .
	.loc 4 771 0
	li	$7,-2147483648			# 0xffffffff80000000
	sll	$5,$5,12
	addu	$5,$5,$7
$LBE162 = .
$LBE165 = .
$LBE168 = .
	.loc 1 621 0
	sw	$2,-8($16)
	.loc 1 628 0
	sltu	$7,$6,$2
	.loc 1 623 0
	lw	$2,576($sp)
	.loc 1 628 0
	addu	$7,$7,$3
	.loc 1 624 0
	addu	$22,$5,$22
	.loc 1 620 0
	sw	$4,-16($16)
	.loc 1 621 0
	sw	$3,-4($16)
	.loc 1 622 0
	sw	$17,0($16)
	.loc 1 623 0
	sw	$2,4($16)
	.loc 1 624 0
	sw	$22,0($20)
	.loc 1 625 0
	sw	$17,4($20)
	.loc 1 626 0
	addiu	$23,$23,1
	.loc 1 628 0
	sw	$6,608($sp)
	sw	$7,612($sp)
	addiu	$16,$16,24
$LBE170 = .
	.loc 1 629 0
	.set	noreorder
	.set	nomacro
	bne	$18,$0,$L146
	addiu	$20,$20,8
	.set	macro
	.set	reorder

	.loc 1 640 0
	lw	$4,676($sp)
	.loc 1 634 0
	addiu	$2,$sp,440
	sw	$2,584($sp)
	.loc 1 638 0
	li	$2,65536			# 0x10000
	.loc 1 635 0
	sw	$23,588($sp)
	.loc 1 638 0
	sw	$2,600($sp)
	.loc 1 632 0
	sw	$0,576($sp)
	.loc 1 633 0
	sw	$0,580($sp)
	.loc 1 636 0
	sw	$0,592($sp)
	.loc 1 640 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_sk_rcvtimeo
	sw	$0,596($sp)
	.set	macro
	.set	reorder

	.loc 1 642 0
	lw	$4,676($sp)
	li	$5,300			# 0x12c
	.set	noreorder
	.set	nomacro
	jal	rtl_set_sk_rcvtimeo
	move	$16,$2
	.set	macro
	.set	reorder

	.loc 1 644 0
	lw	$2,684($sp)
	lw	$4,676($sp)
	addiu	$5,$sp,576
	sw	$2,16($sp)
	li	$2,131072			# 0x20000
	addiu	$2,$2,256
	sw	$2,20($sp)
	addiu	$6,$sp,440
	.set	noreorder
	.set	nomacro
	jal	kernel_recvmsg
	move	$7,$23
	.set	macro
	.set	reorder

	.loc 1 647 0
	lw	$4,676($sp)
	.loc 1 644 0
	move	$21,$2
	.loc 1 647 0
	.set	noreorder
	.set	nomacro
	jal	rtl_set_sk_rcvtimeo
	move	$5,$16
	.set	macro
	.set	reorder

	.loc 1 648 0
	.set	noreorder
	.set	nomacro
	bgez	$21,$L147
	lw	$3,608($sp)
	.set	macro
	.set	reorder

	addiu	$16,$sp,48
	move	$17,$0
$L148:
	.loc 1 653 0 discriminator 2
	lw	$2,0($16)
	lw	$5,-16($16)
	lw	$4,4($16)
	lw	$3,52($19)
	lw	$6,-8($16)
	lw	$7,-4($16)
	sw	$5,24($sp)
	sw	$4,28($sp)
	sw	$2,16($sp)
	sw	$2,20($sp)
	lw	$2,24($3)
	move	$4,$fp
	move	$5,$19
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$17,$17,1
	.set	macro
	.set	reorder

	.loc 1 651 0 discriminator 2
	slt	$2,$17,$23
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L148
	addiu	$16,$16,24
	.set	macro
	.set	reorder

	.loc 1 680 0
	.set	noreorder
	.set	nomacro
	j	$L158
	lw	$2,0($28)
	.set	macro
	.set	reorder

$L147:
	.loc 1 662 0
	lw	$2,684($sp)
	lw	$6,612($sp)
	sra	$5,$21,31
	subu	$2,$3,$2
	sltu	$4,$3,$2
	subu	$4,$6,$4
	addu	$3,$2,$21
	sltu	$2,$3,$2
	addu	$4,$4,$5
	addu	$2,$2,$4
	.loc 1 673 0
	lui	$18,%hi($LC9)
	lui	$20,%hi($LC8)
	.loc 1 663 0
	sw	$21,684($sp)
	.loc 1 662 0
	sw	$3,608($sp)
	sw	$2,612($sp)
	.loc 1 663 0
	addiu	$16,$sp,48
	.loc 1 666 0
	move	$17,$0
	.loc 1 673 0
	addiu	$18,$18,%lo($LC9)
	addiu	$20,$20,%lo($LC8)
	lui	$21,%hi(__func__.41460)
$L151:
	.loc 1 669 0
	lw	$2,0($16)
	lw	$5,-16($16)
	lw	$4,4($16)
	lw	$3,52($19)
	lw	$6,-8($16)
	lw	$7,-4($16)
	sw	$5,24($sp)
	sw	$4,28($sp)
	sw	$2,16($sp)
	sw	$2,20($sp)
	lw	$2,24($3)
	move	$4,$fp
	move	$5,$19
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$17,$17,1
	.set	macro
	.set	reorder

	.loc 1 672 0
	.set	noreorder
	.set	nomacro
	bgez	$2,$L149
	move	$4,$18
	.set	macro
	.set	reorder

	.loc 1 673 0
	sw	$2,16($sp)
	move	$5,$20
	li	$6,673			# 0x2a1
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$7,$21,%lo(__func__.41460)
	.set	macro
	.set	reorder

$L149:
	.loc 1 666 0
	slt	$2,$17,$23
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L151
	addiu	$16,$16,24
	.set	macro
	.set	reorder

	.loc 1 676 0
	move	$4,$19
	.set	noreorder
	.set	nomacro
	jal	balance_dirty_pages_ratelimited_nr
	move	$5,$23
	.set	macro
	.set	reorder

$LBB171 = .
$LBB172 = .
	.loc 1 677 0
	lw	$2,24($28)
	lw	$3,628($sp)
	and	$2,$3,$2
$LBE172 = .
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L152
	lw	$4,680($sp)
	.set	macro
	.set	reorder

$LBB173 = .
	.loc 1 677 0 is_stmt 0 discriminator 1
	addiu	$5,$sp,608
	li	$6,8			# 0x8
#APP
 # 677 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/rtl_sendfile-0.1/reverse_sendfile.c" 1
	.set	noat
	la	$1, __copy_user
	jalr	$1
	.set	at
	
 # 0 "" 2
#NO_APP
$LBE173 = .
$LBE171 = .
	.loc 1 680 0 is_stmt 1 discriminator 1
	.set	noreorder
	.set	nomacro
	j	$L159
	lw	$2,0($28)
	.set	macro
	.set	reorder

$L136:
	.loc 1 572 0
	.set	noreorder
	.set	nomacro
	j	$L156
	li	$2,-14			# 0xfffffffffffffff2
	.set	macro
	.set	reorder

$L152:
	.loc 1 680 0
	lw	$2,0($28)
$L159:
	.loc 1 682 0
	lw	$4,624($sp)
	.set	noreorder
	.set	nomacro
	jal	rtl_inode_mutex_unlock
	sw	$0,996($2)
	.set	macro
	.set	reorder

	.loc 1 688 0
	.set	noreorder
	.set	nomacro
	j	$L156
	lw	$2,684($sp)
	.set	macro
	.set	reorder

$L139:
	.loc 1 680 0
	lw	$2,0($28)
$L158:
	.loc 1 682 0
	lw	$4,624($sp)
	.set	noreorder
	.set	nomacro
	jal	rtl_inode_mutex_unlock
	sw	$0,996($2)
	.set	macro
	.set	reorder

	move	$2,$21
$L156:
	.loc 1 689 0
	lw	$31,668($sp)
	lw	$fp,664($sp)
	lw	$23,660($sp)
	lw	$22,656($sp)
	lw	$21,652($sp)
	lw	$20,648($sp)
	lw	$19,644($sp)
	lw	$18,640($sp)
	lw	$17,636($sp)
	lw	$16,632($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,672
	.set	macro
	.set	reorder

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 23
	.cfi_restore 30
	.cfi_restore 31
	.end	do_splice_from_socket
	.cfi_endproc
$LFE3389:
	.size	do_splice_from_socket, .-do_splice_from_socket
	.section	.rodata.str1.4
	.align	2
$LC10:
	.ascii	"ufsd\000"
	.align	2
$LC11:
	.ascii	"fuseblk\000"
	.align	2
$LC12:
	.ascii	"[%s][%d]: Trap %s filesystem\012\000"
	.text
	.align	2
	.globl	rtl_splice
$LFB3390 = .
	.loc 1 692 0
	.cfi_startproc
	.set	nomips16
	.ent	rtl_splice
	.type	rtl_splice, @function
rtl_splice:
	.frame	$sp,48,$31		# vars= 8, regs= 6/0, args= 16, gp= 0
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-48
	.cfi_def_cfa_offset 48
	.loc 1 701 0
	li	$2,-9			# 0xfffffffffffffff7
	.loc 1 692 0
	sw	$19,36($sp)
	.cfi_offset 19, -12
	move	$19,$5
	.loc 1 702 0
	addiu	$5,$sp,16
	.loc 1 692 0
	sw	$18,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	sw	$31,44($sp)
	sw	$20,40($sp)
	.cfi_offset 18, -16
	.cfi_offset 17, -20
	.cfi_offset 16, -24
	.cfi_offset 31, -4
	.cfi_offset 20, -8
	.loc 1 692 0
	move	$17,$6
	move	$18,$7
	.loc 1 702 0
	.set	noreorder
	.set	nomacro
	jal	sockfd_lookup
	sw	$2,16($sp)
	.set	macro
	.set	reorder

	.loc 1 703 0
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L161
	move	$16,$2
	.set	macro
	.set	reorder

	.loc 1 705 0
	lw	$2,20($2)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L167
	move	$4,$17
	.set	macro
	.set	reorder

	.loc 1 708 0
	.set	noreorder
	.set	nomacro
	jal	fget_light
	addiu	$5,$sp,20
	.set	macro
	.set	reorder

	.loc 1 709 0
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L167
	move	$17,$2
	.set	macro
	.set	reorder

	.loc 1 712 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_file_mode
	move	$4,$2
	.set	macro
	.set	reorder

	andi	$2,$2,0x2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L187
	lw	$2,20($sp)
	.set	macro
	.set	reorder

	.loc 1 716 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_file_mapping
	move	$4,$17
	.set	macro
	.set	reorder

	.loc 1 719 0
	lw	$4,0($2)
	.set	noreorder
	.set	nomacro
	jal	rtl_get_inode_sb
	move	$20,$2
	.set	macro
	.set	reorder

	lw	$2,32($2)
$LBB174 = .
$LBB175 = .
	.file 5 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/string.h"
	.loc 5 77 0
	lui	$4,%hi($LC10)
	addiu	$4,$4,%lo($LC10)
$LBE175 = .
$LBE174 = .
	.loc 1 719 0
	lw	$7,0($2)
$LBB177 = .
$LBB176 = .
	.loc 5 77 0
	move	$3,$7
#APP
 # 77 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$2,($3)
1:	lbu	$1,($4)
	addiu	$3,1
	bne	$1,$2,2f
	addiu	$4,1
	bnez	$2,1b
	lbu	$2,($3)
	move	$2,$1
2:	subu	$2,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
#NO_APP
$LBE176 = .
$LBE177 = .
	.loc 1 720 0
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L164
	lui	$4,%hi($LC11)
	.set	macro
	.set	reorder

$LBB178 = .
$LBB179 = .
	.loc 5 77 0
	move	$3,$7
	addiu	$4,$4,%lo($LC11)
#APP
 # 77 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$2,($3)
1:	lbu	$1,($4)
	addiu	$3,1
	bne	$1,$2,2f
	addiu	$4,1
	bnez	$2,1b
	lbu	$2,($3)
	move	$2,$1
2:	subu	$2,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
#NO_APP
$LBE179 = .
$LBE178 = .
	.loc 1 720 0
	bne	$2,$0,$L165
$L164:
	.loc 1 721 0
	lui	$4,%hi($LC12)
	lui	$5,%hi(__func__.41504)
	addiu	$4,$4,%lo($LC12)
	addiu	$5,$5,%lo(__func__.41504)
	.set	noreorder
	.set	nomacro
	jal	printk
	li	$6,721			# 0x2d1
	.set	macro
	.set	reorder

	.loc 1 722 0
	.set	noreorder
	.set	nomacro
	j	$L187
	lw	$2,20($sp)
	.set	macro
	.set	reorder

$L165:
	.loc 1 726 0
	lw	$3,52($20)
	lui	$2,%hi(jffs2_file_address_operations)
	addiu	$2,$2,%lo(jffs2_file_address_operations)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L166
	move	$4,$17
	.set	macro
	.set	reorder

	.loc 1 727 0
	lw	$2,64($sp)
	li	$3,1			# 0x1
	.loc 1 728 0
	.set	noreorder
	.set	nomacro
	j	$L163
	sw	$3,0($2)
	.set	macro
	.set	reorder

$L166:
	.loc 1 731 0
	move	$5,$16
	move	$6,$19
	.set	noreorder
	.set	nomacro
	jal	do_splice_from_socket
	move	$7,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L163
	sw	$2,16($sp)
	.set	macro
	.set	reorder

$L186:
$LBB180 = .
$LBB181 = .
	.file 6 "include/linux/file.h"
	.loc 6 26 0
	.set	noreorder
	.set	nomacro
	jal	fput
	move	$4,$17
	.set	macro
	.set	reorder

$L167:
$LBE181 = .
$LBE180 = .
	.loc 1 736 0
	.set	noreorder
	.set	nomacro
	jal	fput
	lw	$4,16($16)
	.set	macro
	.set	reorder

$L161:
	.loc 1 738 0
	lw	$2,16($sp)
	.loc 1 739 0
	lw	$31,44($sp)
	lw	$20,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

	.cfi_remember_state
	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 31
$L163:
	.cfi_restore_state
$LBB183 = .
$LBB182 = .
	.loc 6 25 0
	lw	$2,20($sp)
$L187:
	beq	$2,$0,$L167
	j	$L186
$LBE182 = .
$LBE183 = .
	.end	rtl_splice
	.cfi_endproc
$LFE3390:
	.size	rtl_splice, .-rtl_splice
	.align	2
	.globl	memcpy_tokerneliovec
$LFB3392 = .
	.loc 1 839 0
	.cfi_startproc
	.set	nomips16
	.ent	memcpy_tokerneliovec
	.type	memcpy_tokerneliovec, @function
memcpy_tokerneliovec:
	.frame	$sp,40,$31		# vars= 0, regs= 5/0, args= 16, gp= 0
	.mask	0x800f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	.cfi_def_cfa_offset 40
	sw	$19,32($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	sw	$31,36($sp)
	sw	$18,28($sp)
	.cfi_offset 19, -8
	.cfi_offset 17, -16
	.cfi_offset 16, -20
	.cfi_offset 31, -4
	.cfi_offset 18, -12
	.loc 1 839 0
	move	$16,$4
	move	$19,$5
	.loc 1 840 0
	j	$L189
	move	$17,$6

$L191:
	.loc 1 842 0
	lw	$2,4($16)
$LBB184 = .
$LBB185 = .
	.loc 1 844 0
	sltu	$18,$2,$17
	move	$3,$2
	movz	$3,$17,$18
	move	$18,$3
$LBE185 = .
$LBE184 = .
	.loc 1 842 0
	beq	$2,$0,$L190
	move	$6,$3

$LBB188 = .
$LBB186 = .
	.loc 1 845 0
	lw	$4,0($16)
$LBE186 = .
	.loc 1 846 0
	addu	$19,$19,$3
$LBB187 = .
	.loc 1 845 0
	jal	memcpy
	subu	$17,$17,$3

$LBE187 = .
	.loc 1 848 0
	lw	$2,4($16)
	.loc 1 849 0
	lw	$3,0($16)
	.loc 1 848 0
	subu	$2,$2,$18
	.loc 1 849 0
	addu	$18,$3,$18
	.loc 1 848 0
	sw	$2,4($16)
	.loc 1 849 0
	sw	$18,0($16)
$L190:
$LBE188 = .
	.loc 1 851 0
	addiu	$16,$16,8
$L189:
	.loc 1 840 0 discriminator 1
	bgtz	$17,$L191
	move	$5,$19

	.loc 1 854 0
	lw	$31,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,40

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	memcpy_tokerneliovec
	.cfi_endproc
$LFE3392:
	.size	memcpy_tokerneliovec, .-memcpy_tokerneliovec
	.align	2
	.globl	rtl_skb_copy_datagram_to_kernel_iovec
$LFB3393 = .
	.loc 1 868 0
	.cfi_startproc
	.set	nomips16
	.ent	rtl_skb_copy_datagram_to_kernel_iovec
	.type	rtl_skb_copy_datagram_to_kernel_iovec, @function
rtl_skb_copy_datagram_to_kernel_iovec:
	.frame	$sp,64,$31		# vars= 8, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-64
	.cfi_def_cfa_offset 64
	sw	$20,40($sp)
	sw	$19,36($sp)
	sw	$17,28($sp)
	sw	$31,60($sp)
	sw	$fp,56($sp)
	sw	$23,52($sp)
	sw	$22,48($sp)
	sw	$21,44($sp)
	sw	$18,32($sp)
	sw	$16,24($sp)
	.cfi_offset 20, -24
	.cfi_offset 19, -28
	.cfi_offset 17, -36
	.cfi_offset 31, -4
	.cfi_offset 30, -8
	.cfi_offset 23, -12
	.cfi_offset 22, -16
	.cfi_offset 21, -20
	.cfi_offset 18, -32
	.cfi_offset 16, -40
	.loc 1 868 0
	move	$20,$4
	move	$17,$5
	sw	$6,72($sp)
	.loc 1 872 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared_info
	move	$19,$7
	.set	macro
	.set	reorder

	lw	$2,8($2)
	.loc 1 874 0
	.set	noreorder
	.set	nomacro
	beq	$19,$0,$L197
	sw	$2,16($sp)
	.set	macro
	.set	reorder

	move	$22,$0
$LBB189 = .
$LBB190 = .
$LBB191 = .
$LBB192 = .
$LBB193 = .
$LBB194 = .
	.loc 4 771 0
	lui	$fp,%hi(mem_map)
$L198:
$LBE194 = .
$LBE193 = .
$LBE192 = .
$LBE191 = .
$LBE190 = .
$LBE189 = .
	.loc 1 879 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_headlen
	move	$4,$20
	.set	macro
	.set	reorder

	.loc 1 880 0
	li	$16,-1			# 0xffffffffffffffff
$L203:
$LBB206 = .
	.loc 1 885 0
	addu	$18,$22,$2
$LBB203 = .
	.loc 1 886 0
	subu	$2,$18,$17
$LBE203 = .
	.loc 1 885 0
	slt	$3,$17,$18
$LBB204 = .
$LBB201 = .
	.loc 1 895 0
	move	$4,$20
$LBE201 = .
$LBE204 = .
	.loc 1 885 0
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L199
	slt	$21,$19,$2
	.set	macro
	.set	reorder

	movn	$2,$19,$21
	move	$21,$2
$LBB205 = .
	.loc 1 890 0
	li	$2,-1			# 0xffffffffffffffff
	.set	noreorder
	.set	nomacro
	bne	$16,$2,$L200
	subu	$22,$17,$22
	.set	macro
	.set	reorder

	.loc 1 892 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data_common
	subu	$19,$19,$21
	.set	macro
	.set	reorder

	lw	$4,72($sp)
	addu	$5,$2,$22
	.set	noreorder
	.set	nomacro
	jal	memcpy_tokerneliovec
	move	$6,$21
	.set	macro
	.set	reorder

	j	$L213
$L200:
$LBB202 = .
	.loc 1 895 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared_info
	subu	$19,$19,$21
	.set	macro
	.set	reorder

	addiu	$3,$16,5
	sll	$3,$3,3
	addu	$2,$2,$3
$LBB199 = .
$LBB197 = .
$LBB195 = .
	.loc 4 771 0
	lw	$23,4($2)
$LBE195 = .
$LBE197 = .
$LBE199 = .
	.loc 1 903 0
	addiu	$4,$2,4
$LBB200 = .
$LBB198 = .
$LBB196 = .
	.loc 4 771 0
	lw	$2,%lo(mem_map)($fp)
	subu	$23,$23,$2
	sra	$23,$23,5
	li	$2,-2147483648			# 0xffffffff80000000
	sll	$23,$23,12
$LBE196 = .
$LBE198 = .
$LBE200 = .
	.loc 1 903 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_frag_offset
	addu	$23,$23,$2
	.set	macro
	.set	reorder

	.loc 1 904 0
	lw	$4,72($sp)
	.loc 1 903 0
	addu	$2,$2,$22
	.loc 1 904 0
	addu	$5,$23,$2
	.set	noreorder
	.set	nomacro
	jal	memcpy_tokerneliovec
	move	$6,$21
	.set	macro
	.set	reorder

$L213:
$LBE202 = .
	.loc 1 908 0
	.set	noreorder
	.set	nomacro
	beq	$19,$0,$L197
	addu	$17,$17,$21
	.set	macro
	.set	reorder

$L199:
$LBE205 = .
	.loc 1 913 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared_info
	move	$4,$20
	.set	macro
	.set	reorder

	lbu	$2,0($2)
	addiu	$16,$16,1
	slt	$2,$16,$2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L202
	move	$4,$20
	.set	macro
	.set	reorder

	.loc 1 916 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared_info
	move	$22,$18
	.set	macro
	.set	reorder

	addiu	$3,$16,5
	sll	$3,$3,3
	addu	$2,$2,$3
$LBE206 = .
	.loc 1 917 0
	.set	noreorder
	.set	nomacro
	j	$L203
	lhu	$2,10($2)
	.set	macro
	.set	reorder

$L202:
	.loc 1 918 0
	lw	$2,16($sp)
	beq	$2,$0,$L205
	.loc 1 921 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared_info
	move	$4,$2
	.set	macro
	.set	reorder

$LBB207 = .
$LBB208 = .
	.file 7 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/bug.h"
	.loc 7 29 0
	lw	$2,8($2)
#APP
 # 29 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/bug.h" 1
	tne $0, $2, 12
 # 0 "" 2
#NO_APP
$LBE208 = .
$LBE207 = .
	.loc 1 922 0
	lw	$20,16($sp)
$LBB209 = .
	.loc 1 885 0
	move	$22,$18
$LBE209 = .
	.loc 1 922 0
	lw	$2,0($20)
	.loc 1 923 0
	.set	noreorder
	.set	nomacro
	j	$L198
	sw	$2,16($sp)
	.set	macro
	.set	reorder

$L197:
	.loc 1 875 0
	.set	noreorder
	.set	nomacro
	j	$L204
	move	$2,$0
	.set	macro
	.set	reorder

$L205:
	.loc 1 925 0
	li	$2,-14			# 0xfffffffffffffff2
$L204:
	.loc 1 1028 0
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

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 23
	.cfi_restore 30
	.cfi_restore 31
	.end	rtl_skb_copy_datagram_to_kernel_iovec
	.cfi_endproc
$LFE3393:
	.size	rtl_skb_copy_datagram_to_kernel_iovec, .-rtl_skb_copy_datagram_to_kernel_iovec
	.section	.rodata.str1.4
	.align	2
$LC13:
	.ascii	"rtl_sendfile installed\012\000"
	.section	.init.text,"ax",@progbits
	.align	2
$LFB3394 = .
	.loc 1 1039 0
	.cfi_startproc
	.set	nomips16
	.ent	rtl_sendfile_init
	.type	rtl_sendfile_init, @function
rtl_sendfile_init:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 1040 0
	lui	$4,%hi($LC13)
	.loc 1 1039 0
	addiu	$sp,$sp,-24
	.cfi_def_cfa_offset 24
	sw	$31,20($sp)
	.cfi_offset 31, -4
	.loc 1 1040 0
	jal	printk
	addiu	$4,$4,%lo($LC13)

	.loc 1 1044 0
	lw	$31,20($sp)
	.loc 1 1041 0
	lui	$3,%hi(_rtl_sendfile_hook)
	lui	$2,%hi(rtl_sendfile_hook)
	addiu	$3,$3,%lo(_rtl_sendfile_hook)
	sw	$3,%lo(rtl_sendfile_hook)($2)
	.loc 1 1044 0
	move	$2,$0
	j	$31
	addiu	$sp,$sp,24

	.cfi_def_cfa_offset 0
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	rtl_sendfile_init
	.cfi_endproc
$LFE3394:
	.size	rtl_sendfile_init, .-rtl_sendfile_init
	.globl	init_module
	init_module = rtl_sendfile_init
	.section	.rodata.str1.4
	.align	2
$LC14:
	.ascii	"rtl_sendfile removed\012\000"
	.section	.exit.text,"ax",@progbits
	.align	2
$LFB3395 = .
	.loc 1 1047 0
	.cfi_startproc
	.set	nomips16
	.ent	rtl_sendfile_cleanup
	.type	rtl_sendfile_cleanup, @function
rtl_sendfile_cleanup:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 1048 0
	lui	$4,%hi($LC14)
	.loc 1 1047 0
	addiu	$sp,$sp,-24
	.cfi_def_cfa_offset 24
	sw	$31,20($sp)
	.cfi_offset 31, -4
	.loc 1 1048 0
	jal	printk
	addiu	$4,$4,%lo($LC14)

	.loc 1 1050 0
	lw	$31,20($sp)
	.loc 1 1049 0
	lui	$2,%hi(rtl_sendfile_hook)
	sw	$0,%lo(rtl_sendfile_hook)($2)
	.loc 1 1050 0
	j	$31
	addiu	$sp,$sp,24

	.cfi_def_cfa_offset 0
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	rtl_sendfile_cleanup
	.cfi_endproc
$LFE3395:
	.size	rtl_sendfile_cleanup, .-rtl_sendfile_cleanup
	.globl	cleanup_module
	cleanup_module = rtl_sendfile_cleanup
	.rdata
	.align	2
	.type	__func__.41504, @object
	.size	__func__.41504, 11
__func__.41504:
	.ascii	"rtl_splice\000"
	.align	2
	.type	__func__.41460, @object
	.size	__func__.41460, 22
__func__.41460:
	.ascii	"do_splice_from_socket\000"
	.align	2
	.type	__func__.41410, @object
	.size	__func__.41410, 22
__func__.41410:
	.ascii	"rtl_pipe_to_sendpages\000"
	.align	2
	.type	__func__.41332, @object
	.size	__func__.41332, 19
__func__.41332:
	.ascii	"do_tcp_send_mpages\000"
	.section	.modinfo,"a",@progbits
	.type	__UNIQUE_ID_license1, @object
	.size	__UNIQUE_ID_license1, 12
__UNIQUE_ID_license1:
	.ascii	"license=GPL\000"
	.data
	.align	2
	.type	_rtl_sendfile_hook, @object
	.size	_rtl_sendfile_hook, 20
_rtl_sendfile_hook:
	.word	rtl_splice
	.word	rtl_splice_from_pipe_feed
	.word	rtl_pipe_to_sendpages
	.word	rtl_tcp_ctl_init
	.word	rtl_skb_copy_datagram_to_kernel_iovec
	.section	.data,"aw",@progbits
	.align	2
	.type	bdp_ratelimits, @object
	.size	bdp_ratelimits, 4
bdp_ratelimits:
	.space	4
	.globl	g2_tcp_ctl
	.section	.bss,"aw",@nobits
	.align	2
	.type	g2_tcp_ctl, @object
	.size	g2_tcp_ctl, 32
g2_tcp_ctl:
	.space	32
	.text
$Letext0:
	.file 8 "include/uapi/asm-generic/int-ll64.h"
	.file 9 "include/asm-generic/int-ll64.h"
	.file 10 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/include/uapi/asm-generic/posix_types.h"
	.file 11 "include/uapi/linux/types.h"
	.file 12 "include/linux/types.h"
	.file 13 "include/asm-generic/atomic-long.h"
	.file 14 "include/linux/stddef.h"
	.file 15 "include/linux/fs.h"
	.file 16 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/page.h"
	.file 17 "include/linux/splice.h"
	.file 18 "include/linux/netdev_features.h"
	.file 19 "include/linux/skbuff.h"
	.file 20 "include/uapi/linux/netfilter.h"
	.file 21 "include/uapi/linux/netfilter/nf_conntrack_tcp.h"
	.file 22 "include/net/netns/conntrack.h"
	.file 23 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/include/uapi/linux/xfrm.h"
	.file 24 "include/uapi/linux/if_link.h"
	.file 25 "include/uapi/linux/rtnetlink.h"
	.file 26 "include/net/tcp_states.h"
	.file 27 "include/linux/interrupt.h"
	.file 28 "include/net/ndisc.h"
	.file 29 "include/linux/kernel.h"
	.file 30 "include/linux/highmem.h"
	.file 31 "include/net/cls_cgroup.h"
	.file 32 "include/linux/tcp.h"
	.file 33 "include/net/inet_sock.h"
	.file 34 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/thread_info.h"
	.file 35 "include/net/inet_frag.h"
	.file 36 "include/linux/export.h"
	.file 37 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/cpu-info.h"
	.file 38 "include/linux/printk.h"
	.file 39 "include/linux/cpumask.h"
	.file 40 "include/linux/time.h"
	.file 41 "include/linux/highuid.h"
	.file 42 "include/linux/seq_file.h"
	.file 43 "include/linux/sched.h"
	.file 44 "include/linux/quota.h"
	.file 45 "include/linux/jiffies.h"
	.file 46 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/cacheflush.h"
	.file 47 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/io.h"
	.file 48 "include/linux/mmzone.h"
	.file 49 "include/linux/workqueue.h"
	.file 50 "include/linux/debug_locks.h"
	.file 51 "include/linux/swap.h"
	.file 52 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/pgtable-32.h"
	.file 53 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/pgtable.h"
	.file 54 "include/asm-generic/pgtable.h"
	.file 55 "include/linux/vmstat.h"
	.file 56 "include/linux/slab.h"
	.file 57 "include/linux/ioport.h"
	.file 58 "include/linux/netfilter.h"
	.file 59 "include/net/net_namespace.h"
	.file 60 "include/net/inet_connection_sock.h"
	.file 61 "include/net/route.h"
	.file 62 "include/net/ip.h"
	.file 63 "include/net/tcp.h"
	.file 64 "include/net/rtl/rtl_sendfile.h"
	.file 65 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/rtl_sendfile-0.1/../linux-3.10.49/fs/jffs2/os-linux.h"
	.section	.debug_info,"",@progbits
$Ldebug_info0:
	.4byte	0x1bfe
	.2byte	0x4
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$LASF416
	.byte	0x1
	.4byte	$LASF417
	.4byte	$LASF418
	.4byte	$Ldebug_ranges0+0x2a8
	.4byte	0
	.4byte	$Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	$LASF0
	.uleb128 0x3
	.4byte	$LASF4
	.byte	0x8
	.byte	0x14
	.4byte	0x37
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	$LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	$LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	$LASF3
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.4byte	$LASF5
	.byte	0x8
	.byte	0x1a
	.4byte	0x5e
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	$LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	$LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	$LASF8
	.uleb128 0x5
	.ascii	"u16\000"
	.byte	0x9
	.byte	0x13
	.4byte	0x45
	.uleb128 0x5
	.ascii	"u32\000"
	.byte	0x9
	.byte	0x16
	.4byte	0x5e
	.uleb128 0x5
	.ascii	"u64\000"
	.byte	0x9
	.byte	0x19
	.4byte	0x6c
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	$LASF9
	.uleb128 0x6
	.byte	0x4
	.byte	0xe
	.byte	0xa
	.4byte	0xb0
	.uleb128 0x7
	.4byte	$LASF10
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF11
	.sleb128 1
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	$LASF12
	.uleb128 0x3
	.4byte	$LASF13
	.byte	0xa
	.byte	0x43
	.4byte	0x5e
	.uleb128 0x3
	.4byte	$LASF14
	.byte	0xa
	.byte	0x44
	.4byte	0x4c
	.uleb128 0x3
	.4byte	$LASF15
	.byte	0xa
	.byte	0x57
	.4byte	0x65
	.uleb128 0x8
	.byte	0x4
	.4byte	0xde
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	$LASF16
	.uleb128 0x3
	.4byte	$LASF17
	.byte	0xb
	.byte	0x23
	.4byte	0x53
	.uleb128 0x3
	.4byte	$LASF18
	.byte	0xc
	.byte	0x1d
	.4byte	0xfb
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	$LASF19
	.uleb128 0x3
	.4byte	$LASF20
	.byte	0xc
	.byte	0x2d
	.4byte	0xcd
	.uleb128 0x3
	.4byte	$LASF21
	.byte	0xc
	.byte	0x36
	.4byte	0xb7
	.uleb128 0x3
	.4byte	$LASF22
	.byte	0xc
	.byte	0x3b
	.4byte	0xc2
	.uleb128 0x3
	.4byte	$LASF23
	.byte	0xc
	.byte	0x9e
	.4byte	0x5e
	.uleb128 0x3
	.4byte	$LASF24
	.byte	0xc
	.byte	0xa4
	.4byte	0x7e
	.uleb128 0x9
	.uleb128 0x3
	.4byte	$LASF25
	.byte	0xc
	.byte	0xb1
	.4byte	0x139
	.uleb128 0xa
	.4byte	$LASF26
	.uleb128 0xa
	.4byte	$LASF27
	.uleb128 0x8
	.byte	0x4
	.4byte	0x155
	.uleb128 0xb
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	$LASF28
	.uleb128 0xa
	.4byte	$LASF29
	.uleb128 0x3
	.4byte	$LASF30
	.byte	0xd
	.byte	0x8d
	.4byte	0x13a
	.uleb128 0xc
	.byte	0x4
	.uleb128 0x8
	.byte	0x4
	.4byte	0x175
	.uleb128 0xd
	.4byte	0x180
	.uleb128 0xe
	.4byte	0x94
	.byte	0
	.uleb128 0xf
	.ascii	"pid\000"
	.uleb128 0x8
	.byte	0x4
	.4byte	0x18b
	.uleb128 0xa
	.4byte	$LASF31
	.uleb128 0xa
	.4byte	$LASF32
	.uleb128 0x8
	.byte	0x4
	.4byte	0x19b
	.uleb128 0xa
	.4byte	$LASF33
	.uleb128 0xa
	.4byte	$LASF34
	.uleb128 0xa
	.4byte	$LASF35
	.uleb128 0xa
	.4byte	$LASF36
	.uleb128 0x10
	.byte	0x4
	.byte	0xf
	.2byte	0x4c2
	.4byte	0x1d7
	.uleb128 0x7
	.4byte	$LASF37
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF38
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF39
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF40
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF41
	.sleb128 4
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x1dd
	.uleb128 0x11
	.4byte	0xde
	.uleb128 0x9
	.uleb128 0x3
	.4byte	$LASF42
	.byte	0x10
	.byte	0x69
	.4byte	0x1e2
	.uleb128 0xa
	.4byte	$LASF43
	.uleb128 0x8
	.byte	0x4
	.4byte	0x102
	.uleb128 0xa
	.4byte	$LASF44
	.uleb128 0xa
	.4byte	$LASF45
	.uleb128 0xa
	.4byte	$LASF46
	.uleb128 0xa
	.4byte	$LASF47
	.uleb128 0xa
	.4byte	$LASF48
	.uleb128 0xa
	.4byte	$LASF49
	.uleb128 0xa
	.4byte	$LASF50
	.uleb128 0xa
	.4byte	$LASF51
	.uleb128 0x3
	.4byte	$LASF52
	.byte	0x11
	.byte	0x3e
	.4byte	0x22c
	.uleb128 0x12
	.4byte	0x4c
	.4byte	0x245
	.uleb128 0xe
	.4byte	0x245
	.uleb128 0xe
	.4byte	0x24b
	.uleb128 0xe
	.4byte	0x251
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x212
	.uleb128 0x8
	.byte	0x4
	.4byte	0x20d
	.uleb128 0x8
	.byte	0x4
	.4byte	0x21c
	.uleb128 0xa
	.4byte	$LASF53
	.uleb128 0xa
	.4byte	$LASF54
	.uleb128 0xa
	.4byte	$LASF55
	.uleb128 0xa
	.4byte	$LASF56
	.uleb128 0x3
	.4byte	$LASF57
	.byte	0x12
	.byte	0xf
	.4byte	0x89
	.uleb128 0x6
	.byte	0x4
	.byte	0x12
	.byte	0x11
	.4byte	0x36f
	.uleb128 0x7
	.4byte	$LASF58
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF59
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF60
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF61
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF62
	.sleb128 4
	.uleb128 0x7
	.4byte	$LASF63
	.sleb128 5
	.uleb128 0x7
	.4byte	$LASF64
	.sleb128 6
	.uleb128 0x7
	.4byte	$LASF65
	.sleb128 7
	.uleb128 0x7
	.4byte	$LASF66
	.sleb128 8
	.uleb128 0x7
	.4byte	$LASF67
	.sleb128 9
	.uleb128 0x7
	.4byte	$LASF68
	.sleb128 10
	.uleb128 0x7
	.4byte	$LASF69
	.sleb128 11
	.uleb128 0x7
	.4byte	$LASF70
	.sleb128 12
	.uleb128 0x7
	.4byte	$LASF71
	.sleb128 13
	.uleb128 0x7
	.4byte	$LASF72
	.sleb128 14
	.uleb128 0x7
	.4byte	$LASF73
	.sleb128 15
	.uleb128 0x7
	.4byte	$LASF74
	.sleb128 16
	.uleb128 0x7
	.4byte	$LASF75
	.sleb128 16
	.uleb128 0x7
	.4byte	$LASF76
	.sleb128 17
	.uleb128 0x7
	.4byte	$LASF77
	.sleb128 18
	.uleb128 0x7
	.4byte	$LASF78
	.sleb128 19
	.uleb128 0x7
	.4byte	$LASF79
	.sleb128 20
	.uleb128 0x7
	.4byte	$LASF80
	.sleb128 21
	.uleb128 0x7
	.4byte	$LASF81
	.sleb128 22
	.uleb128 0x7
	.4byte	$LASF82
	.sleb128 23
	.uleb128 0x7
	.4byte	$LASF83
	.sleb128 23
	.uleb128 0x7
	.4byte	$LASF84
	.sleb128 24
	.uleb128 0x7
	.4byte	$LASF85
	.sleb128 25
	.uleb128 0x7
	.4byte	$LASF86
	.sleb128 26
	.uleb128 0x7
	.4byte	$LASF87
	.sleb128 27
	.uleb128 0x7
	.4byte	$LASF88
	.sleb128 28
	.uleb128 0x7
	.4byte	$LASF89
	.sleb128 29
	.uleb128 0x7
	.4byte	$LASF90
	.sleb128 30
	.uleb128 0x7
	.4byte	$LASF91
	.sleb128 31
	.uleb128 0x7
	.4byte	$LASF92
	.sleb128 32
	.uleb128 0x7
	.4byte	$LASF93
	.sleb128 33
	.uleb128 0x7
	.4byte	$LASF94
	.sleb128 34
	.uleb128 0x7
	.4byte	$LASF95
	.sleb128 35
	.uleb128 0x7
	.4byte	$LASF96
	.sleb128 36
	.uleb128 0x7
	.4byte	$LASF97
	.sleb128 37
	.byte	0
	.uleb128 0x3
	.4byte	$LASF98
	.byte	0x13
	.byte	0x99
	.4byte	0x37a
	.uleb128 0xa
	.4byte	$LASF99
	.uleb128 0x8
	.byte	0x4
	.4byte	0x37
	.uleb128 0xa
	.4byte	$LASF100
	.uleb128 0x6
	.byte	0x4
	.byte	0x14
	.byte	0x36
	.4byte	0x3bd
	.uleb128 0x7
	.4byte	$LASF101
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF102
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF103
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF104
	.sleb128 7
	.uleb128 0x7
	.4byte	$LASF105
	.sleb128 10
	.uleb128 0x7
	.4byte	$LASF106
	.sleb128 12
	.uleb128 0x7
	.4byte	$LASF107
	.sleb128 13
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x385
	.uleb128 0xa
	.4byte	$LASF108
	.uleb128 0xa
	.4byte	$LASF109
	.uleb128 0xf
	.ascii	"net\000"
	.uleb128 0x13
	.4byte	$LASF125
	.byte	0x4
	.byte	0x15
	.byte	0x8
	.4byte	0x439
	.uleb128 0x7
	.4byte	$LASF110
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF111
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF112
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF113
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF114
	.sleb128 4
	.uleb128 0x7
	.4byte	$LASF115
	.sleb128 5
	.uleb128 0x7
	.4byte	$LASF116
	.sleb128 6
	.uleb128 0x7
	.4byte	$LASF117
	.sleb128 7
	.uleb128 0x7
	.4byte	$LASF118
	.sleb128 8
	.uleb128 0x7
	.4byte	$LASF119
	.sleb128 9
	.uleb128 0x7
	.4byte	$LASF120
	.sleb128 10
	.uleb128 0x7
	.4byte	$LASF121
	.sleb128 11
	.uleb128 0x7
	.4byte	$LASF122
	.sleb128 12
	.uleb128 0x7
	.4byte	$LASF123
	.sleb128 13
	.uleb128 0x7
	.4byte	$LASF124
	.sleb128 14
	.byte	0
	.uleb128 0x13
	.4byte	$LASF126
	.byte	0x4
	.byte	0x16
	.byte	0x25
	.4byte	0x458
	.uleb128 0x7
	.4byte	$LASF127
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF128
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF129
	.sleb128 2
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.byte	0x17
	.byte	0x84
	.4byte	0x47f
	.uleb128 0x7
	.4byte	$LASF130
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF131
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF132
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF133
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF134
	.sleb128 3
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.byte	0x18
	.byte	0x65
	.4byte	0x55a
	.uleb128 0x7
	.4byte	$LASF135
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF136
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF137
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF138
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF139
	.sleb128 4
	.uleb128 0x7
	.4byte	$LASF140
	.sleb128 5
	.uleb128 0x7
	.4byte	$LASF141
	.sleb128 6
	.uleb128 0x7
	.4byte	$LASF142
	.sleb128 7
	.uleb128 0x7
	.4byte	$LASF143
	.sleb128 8
	.uleb128 0x7
	.4byte	$LASF144
	.sleb128 9
	.uleb128 0x7
	.4byte	$LASF145
	.sleb128 10
	.uleb128 0x7
	.4byte	$LASF146
	.sleb128 11
	.uleb128 0x7
	.4byte	$LASF147
	.sleb128 12
	.uleb128 0x7
	.4byte	$LASF148
	.sleb128 13
	.uleb128 0x7
	.4byte	$LASF149
	.sleb128 14
	.uleb128 0x7
	.4byte	$LASF150
	.sleb128 15
	.uleb128 0x7
	.4byte	$LASF151
	.sleb128 16
	.uleb128 0x7
	.4byte	$LASF152
	.sleb128 17
	.uleb128 0x7
	.4byte	$LASF153
	.sleb128 18
	.uleb128 0x7
	.4byte	$LASF154
	.sleb128 19
	.uleb128 0x7
	.4byte	$LASF155
	.sleb128 20
	.uleb128 0x7
	.4byte	$LASF156
	.sleb128 21
	.uleb128 0x7
	.4byte	$LASF157
	.sleb128 22
	.uleb128 0x7
	.4byte	$LASF158
	.sleb128 23
	.uleb128 0x7
	.4byte	$LASF159
	.sleb128 24
	.uleb128 0x7
	.4byte	$LASF160
	.sleb128 25
	.uleb128 0x7
	.4byte	$LASF161
	.sleb128 26
	.uleb128 0x7
	.4byte	$LASF162
	.sleb128 27
	.uleb128 0x7
	.4byte	$LASF163
	.sleb128 28
	.uleb128 0x7
	.4byte	$LASF164
	.sleb128 29
	.uleb128 0x7
	.4byte	$LASF165
	.sleb128 30
	.uleb128 0x7
	.4byte	$LASF166
	.sleb128 31
	.uleb128 0x7
	.4byte	$LASF167
	.sleb128 32
	.uleb128 0x7
	.4byte	$LASF168
	.sleb128 33
	.uleb128 0x7
	.4byte	$LASF169
	.sleb128 34
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x1aa
	.uleb128 0x10
	.byte	0x4
	.byte	0x19
	.2byte	0x167
	.4byte	0x5ca
	.uleb128 0x7
	.4byte	$LASF170
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF171
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF172
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF173
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF174
	.sleb128 4
	.uleb128 0x7
	.4byte	$LASF175
	.sleb128 5
	.uleb128 0x7
	.4byte	$LASF176
	.sleb128 6
	.uleb128 0x7
	.4byte	$LASF177
	.sleb128 7
	.uleb128 0x7
	.4byte	$LASF178
	.sleb128 8
	.uleb128 0x7
	.4byte	$LASF179
	.sleb128 9
	.uleb128 0x7
	.4byte	$LASF180
	.sleb128 10
	.uleb128 0x7
	.4byte	$LASF181
	.sleb128 11
	.uleb128 0x7
	.4byte	$LASF182
	.sleb128 12
	.uleb128 0x7
	.4byte	$LASF183
	.sleb128 13
	.uleb128 0x7
	.4byte	$LASF184
	.sleb128 14
	.uleb128 0x7
	.4byte	$LASF185
	.sleb128 15
	.byte	0
	.uleb128 0xa
	.4byte	$LASF186
	.uleb128 0xa
	.4byte	$LASF187
	.uleb128 0xa
	.4byte	$LASF188
	.uleb128 0x6
	.byte	0x4
	.byte	0x1a
	.byte	0x24
	.4byte	0x62a
	.uleb128 0x7
	.4byte	$LASF189
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF190
	.sleb128 4
	.uleb128 0x7
	.4byte	$LASF191
	.sleb128 8
	.uleb128 0x7
	.4byte	$LASF192
	.sleb128 16
	.uleb128 0x7
	.4byte	$LASF193
	.sleb128 32
	.uleb128 0x7
	.4byte	$LASF194
	.sleb128 64
	.uleb128 0x7
	.4byte	$LASF195
	.sleb128 128
	.uleb128 0x7
	.4byte	$LASF196
	.sleb128 256
	.uleb128 0x7
	.4byte	$LASF197
	.sleb128 512
	.uleb128 0x7
	.4byte	$LASF198
	.sleb128 1024
	.uleb128 0x7
	.4byte	$LASF199
	.sleb128 2048
	.byte	0
	.uleb128 0xa
	.4byte	$LASF200
	.uleb128 0x10
	.byte	0x4
	.byte	0x1b
	.2byte	0x1c3
	.4byte	0x67b
	.uleb128 0x7
	.4byte	$LASF201
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF202
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF203
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF204
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF205
	.sleb128 4
	.uleb128 0x7
	.4byte	$LASF206
	.sleb128 5
	.uleb128 0x7
	.4byte	$LASF207
	.sleb128 6
	.uleb128 0x7
	.4byte	$LASF208
	.sleb128 7
	.uleb128 0x7
	.4byte	$LASF209
	.sleb128 8
	.uleb128 0x7
	.4byte	$LASF210
	.sleb128 9
	.uleb128 0x7
	.4byte	$LASF211
	.sleb128 10
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.byte	0x1c
	.byte	0x1b
	.4byte	0x6c6
	.uleb128 0x7
	.4byte	$LASF212
	.sleb128 0
	.uleb128 0x7
	.4byte	$LASF213
	.sleb128 1
	.uleb128 0x7
	.4byte	$LASF214
	.sleb128 2
	.uleb128 0x7
	.4byte	$LASF215
	.sleb128 3
	.uleb128 0x7
	.4byte	$LASF216
	.sleb128 4
	.uleb128 0x7
	.4byte	$LASF217
	.sleb128 5
	.uleb128 0x7
	.4byte	$LASF218
	.sleb128 6
	.uleb128 0x7
	.4byte	$LASF219
	.sleb128 24
	.uleb128 0x7
	.4byte	$LASF220
	.sleb128 25
	.uleb128 0x7
	.4byte	$LASF221
	.sleb128 31
	.uleb128 0x7
	.4byte	$LASF222
	.sleb128 32
	.byte	0
	.uleb128 0xa
	.4byte	$LASF223
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	$LASF224
	.uleb128 0xa
	.4byte	$LASF225
	.uleb128 0x14
	.4byte	$LASF230
	.byte	0x18
	.byte	0x1
	.byte	0x20
	.4byte	0x714
	.uleb128 0x15
	.4byte	$LASF226
	.byte	0x1
	.byte	0x22
	.4byte	0x195
	.byte	0
	.uleb128 0x15
	.4byte	$LASF227
	.byte	0x1
	.byte	0x23
	.4byte	0x102
	.byte	0x8
	.uleb128 0x15
	.4byte	$LASF228
	.byte	0x1
	.byte	0x24
	.4byte	0x10d
	.byte	0x10
	.uleb128 0x15
	.4byte	$LASF229
	.byte	0x1
	.byte	0x25
	.4byte	0x16d
	.byte	0x14
	.byte	0
	.uleb128 0x14
	.4byte	$LASF231
	.byte	0x20
	.byte	0x1
	.byte	0x6c
	.4byte	0x781
	.uleb128 0x15
	.4byte	$LASF232
	.byte	0x1
	.byte	0x6d
	.4byte	0x5e
	.byte	0
	.uleb128 0x15
	.4byte	$LASF233
	.byte	0x1
	.byte	0x6e
	.4byte	0x5e
	.byte	0x4
	.uleb128 0x15
	.4byte	$LASF234
	.byte	0x1
	.byte	0x6f
	.4byte	0x5e
	.byte	0x8
	.uleb128 0x15
	.4byte	$LASF235
	.byte	0x1
	.byte	0x70
	.4byte	0x5e
	.byte	0xc
	.uleb128 0x15
	.4byte	$LASF236
	.byte	0x1
	.byte	0x71
	.4byte	0x5e
	.byte	0x10
	.uleb128 0x15
	.4byte	$LASF237
	.byte	0x1
	.byte	0x72
	.4byte	0x5e
	.byte	0x14
	.uleb128 0x15
	.4byte	$LASF238
	.byte	0x1
	.byte	0x73
	.4byte	0x5e
	.byte	0x18
	.uleb128 0x15
	.4byte	$LASF239
	.byte	0x1
	.byte	0x74
	.4byte	0x5e
	.byte	0x1c
	.byte	0
	.uleb128 0x16
	.ascii	"BUG\000"
	.byte	0x7
	.byte	0xb
	.byte	0x3
	.uleb128 0x17
	.4byte	$LASF242
	.byte	0x1d
	.byte	0xa6
	.byte	0x3
	.4byte	0x7b7
	.uleb128 0x18
	.4byte	$LASF36
	.byte	0x1d
	.byte	0xa6
	.4byte	0x1d7
	.uleb128 0x18
	.4byte	$LASF240
	.byte	0x1d
	.byte	0xa6
	.4byte	0x4c
	.uleb128 0x18
	.4byte	$LASF241
	.byte	0x1d
	.byte	0xa7
	.4byte	0x4c
	.byte	0
	.uleb128 0x19
	.4byte	$LASF244
	.byte	0x4
	.2byte	0x301
	.4byte	0x16d
	.byte	0x3
	.4byte	0x7d5
	.uleb128 0x1a
	.4byte	$LASF33
	.byte	0x4
	.2byte	0x301
	.4byte	0x7d5
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x7db
	.uleb128 0x11
	.4byte	0x19b
	.uleb128 0x17
	.4byte	$LASF243
	.byte	0x1e
	.byte	0x3e
	.byte	0x3
	.4byte	0x7f8
	.uleb128 0x18
	.4byte	$LASF33
	.byte	0x1e
	.byte	0x3e
	.4byte	0x195
	.byte	0
	.uleb128 0x19
	.4byte	$LASF245
	.byte	0x13
	.2byte	0x82a
	.4byte	0x195
	.byte	0x3
	.4byte	0x816
	.uleb128 0x1a
	.4byte	$LASF246
	.byte	0x13
	.2byte	0x82a
	.4byte	0x816
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x81c
	.uleb128 0x11
	.4byte	0x36f
	.uleb128 0x17
	.4byte	$LASF247
	.byte	0x1f
	.byte	0x40
	.byte	0x3
	.4byte	0x838
	.uleb128 0x1b
	.ascii	"sk\000"
	.byte	0x1f
	.byte	0x40
	.4byte	0x838
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x5cf
	.uleb128 0x19
	.4byte	$LASF248
	.byte	0x20
	.2byte	0x151
	.4byte	0x85b
	.byte	0x3
	.4byte	0x85b
	.uleb128 0x1c
	.ascii	"sk\000"
	.byte	0x20
	.2byte	0x151
	.4byte	0x861
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x62a
	.uleb128 0x8
	.byte	0x4
	.4byte	0x867
	.uleb128 0x11
	.4byte	0x5cf
	.uleb128 0x17
	.4byte	$LASF249
	.byte	0x3
	.byte	0x7e
	.byte	0x3
	.4byte	0x8ad
	.uleb128 0x1b
	.ascii	"nr\000"
	.byte	0x3
	.byte	0x7e
	.4byte	0x94
	.uleb128 0x18
	.4byte	$LASF250
	.byte	0x3
	.byte	0x7e
	.4byte	0x8ad
	.uleb128 0x1d
	.ascii	"m\000"
	.byte	0x3
	.byte	0x80
	.4byte	0x8b8
	.uleb128 0x1d
	.ascii	"bit\000"
	.byte	0x3
	.byte	0x81
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF251
	.byte	0x3
	.byte	0x82
	.4byte	0x94
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x8b3
	.uleb128 0x1f
	.4byte	0x94
	.uleb128 0x8
	.byte	0x4
	.4byte	0x94
	.uleb128 0x20
	.4byte	$LASF252
	.byte	0x21
	.byte	0xb7
	.4byte	0x8d9
	.byte	0x3
	.4byte	0x8d9
	.uleb128 0x1b
	.ascii	"sk\000"
	.byte	0x21
	.byte	0xb7
	.4byte	0x861
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x5d4
	.uleb128 0x17
	.4byte	$LASF253
	.byte	0x3
	.byte	0x4a
	.byte	0x3
	.4byte	0x920
	.uleb128 0x1b
	.ascii	"nr\000"
	.byte	0x3
	.byte	0x4a
	.4byte	0x94
	.uleb128 0x18
	.4byte	$LASF250
	.byte	0x3
	.byte	0x4a
	.4byte	0x8ad
	.uleb128 0x1d
	.ascii	"m\000"
	.byte	0x3
	.byte	0x4c
	.4byte	0x8b8
	.uleb128 0x1d
	.ascii	"bit\000"
	.byte	0x3
	.byte	0x4d
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF251
	.byte	0x3
	.byte	0x4e
	.4byte	0x94
	.byte	0
	.uleb128 0x21
	.4byte	$LASF254
	.byte	0x2
	.2byte	0x5ba
	.byte	0x3
	.4byte	0x939
	.uleb128 0x1c
	.ascii	"sk\000"
	.byte	0x2
	.2byte	0x5ba
	.4byte	0x838
	.byte	0
	.uleb128 0x19
	.4byte	$LASF255
	.byte	0x1
	.2byte	0x1b1
	.4byte	0x4c
	.byte	0x1
	.4byte	0x987
	.uleb128 0x1a
	.4byte	$LASF187
	.byte	0x1
	.2byte	0x1b1
	.4byte	0x987
	.uleb128 0x1a
	.4byte	$LASF256
	.byte	0x1
	.2byte	0x1b1
	.4byte	0x245
	.uleb128 0x1a
	.4byte	$LASF257
	.byte	0x1
	.2byte	0x1b1
	.4byte	0x4c
	.uleb128 0x1a
	.4byte	$LASF258
	.byte	0x1
	.2byte	0x1b2
	.4byte	0x10d
	.uleb128 0x1a
	.4byte	$LASF259
	.byte	0x1
	.2byte	0x1b2
	.4byte	0x4c
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x266
	.uleb128 0x19
	.4byte	$LASF260
	.byte	0x1
	.2byte	0x1f4
	.4byte	0xb0
	.byte	0x3
	.4byte	0x9ab
	.uleb128 0x1a
	.4byte	$LASF261
	.byte	0x1
	.2byte	0x1f4
	.4byte	0x94
	.byte	0
	.uleb128 0x20
	.4byte	$LASF262
	.byte	0x22
	.byte	0x3d
	.4byte	0x9c7
	.byte	0x3
	.4byte	0x9c7
	.uleb128 0x1e
	.4byte	$LASF263
	.byte	0x22
	.byte	0x3f
	.4byte	0x9c7
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x15d
	.uleb128 0x22
	.4byte	$LASF264
	.byte	0x1d
	.byte	0xc7
	.byte	0x3
	.uleb128 0x20
	.4byte	$LASF265
	.byte	0x1e
	.byte	0x38
	.4byte	0x16d
	.byte	0x3
	.4byte	0x9f1
	.uleb128 0x18
	.4byte	$LASF33
	.byte	0x1e
	.byte	0x38
	.4byte	0x195
	.byte	0
	.uleb128 0x20
	.4byte	$LASF266
	.byte	0x5
	.byte	0x49
	.4byte	0x4c
	.byte	0x3
	.4byte	0xa23
	.uleb128 0x18
	.4byte	$LASF267
	.byte	0x5
	.byte	0x49
	.4byte	0x1d7
	.uleb128 0x18
	.4byte	$LASF268
	.byte	0x5
	.byte	0x49
	.4byte	0x1d7
	.uleb128 0x1e
	.4byte	$LASF269
	.byte	0x5
	.byte	0x4b
	.4byte	0x4c
	.byte	0
	.uleb128 0x17
	.4byte	$LASF270
	.byte	0x6
	.byte	0x17
	.byte	0x3
	.4byte	0xa46
	.uleb128 0x18
	.4byte	$LASF36
	.byte	0x6
	.byte	0x17
	.4byte	0x55a
	.uleb128 0x18
	.4byte	$LASF271
	.byte	0x6
	.byte	0x17
	.4byte	0x4c
	.byte	0
	.uleb128 0x17
	.4byte	$LASF272
	.byte	0x7
	.byte	0x15
	.byte	0x3
	.4byte	0xa5e
	.uleb128 0x18
	.4byte	$LASF273
	.byte	0x7
	.byte	0x15
	.4byte	0x94
	.byte	0
	.uleb128 0x23
	.4byte	$LASF419
	.byte	0x1
	.byte	0x77
	.4byte	$LFB3380
	.4byte	$LFE3380-$LFB3380
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x24
	.4byte	$LASF297
	.byte	0x1
	.2byte	0x2e5
	.4byte	0x4c
	.4byte	$LFB3391
	.4byte	$LFE3391-$LFB3391
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb07
	.uleb128 0x25
	.4byte	$LASF256
	.byte	0x1
	.2byte	0x2e5
	.4byte	0x245
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x26
	.ascii	"sd\000"
	.byte	0x1
	.2byte	0x2e5
	.4byte	0x251
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x25
	.4byte	$LASF274
	.byte	0x1
	.2byte	0x2e6
	.4byte	0xb07
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x27
	.ascii	"ret\000"
	.byte	0x1
	.2byte	0x2e8
	.4byte	0x4c
	.uleb128 0x28
	.4byte	$Ldebug_ranges0+0
	.4byte	0xae4
	.uleb128 0x29
	.ascii	"buf\000"
	.byte	0x1
	.2byte	0x315
	.4byte	0x24b
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x29
	.ascii	"ops\000"
	.byte	0x1
	.2byte	0x316
	.4byte	0xb0d
	.uleb128 0x1
	.byte	0x65
	.byte	0
	.uleb128 0x2a
	.4byte	$Ldebug_ranges0+0x20
	.uleb128 0x29
	.ascii	"buf\000"
	.byte	0x1
	.2byte	0x2eb
	.4byte	0x24b
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x29
	.ascii	"ops\000"
	.byte	0x1
	.2byte	0x2ec
	.4byte	0xb0d
	.uleb128 0x1
	.byte	0x53
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x221
	.uleb128 0x8
	.byte	0x4
	.4byte	0xb13
	.uleb128 0x11
	.4byte	0x217
	.uleb128 0x20
	.4byte	$LASF275
	.byte	0x1
	.byte	0x83
	.4byte	0x118
	.byte	0x1
	.4byte	0xc6d
	.uleb128 0x1b
	.ascii	"sk\000"
	.byte	0x1
	.byte	0x83
	.4byte	0x838
	.uleb128 0x18
	.4byte	$LASF276
	.byte	0x1
	.byte	0x83
	.4byte	0xc6d
	.uleb128 0x18
	.4byte	$LASF277
	.byte	0x1
	.byte	0x84
	.4byte	0x4c
	.uleb128 0x18
	.4byte	$LASF278
	.byte	0x1
	.byte	0x84
	.4byte	0x10d
	.uleb128 0x18
	.4byte	$LASF259
	.byte	0x1
	.byte	0x84
	.4byte	0x4c
	.uleb128 0x1d
	.ascii	"tp\000"
	.byte	0x1
	.byte	0x86
	.4byte	0x85b
	.uleb128 0x1e
	.4byte	$LASF279
	.byte	0x1
	.byte	0x87
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF280
	.byte	0x1
	.byte	0x87
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF281
	.byte	0x1
	.byte	0x87
	.4byte	0x4c
	.uleb128 0x1d
	.ascii	"err\000"
	.byte	0x1
	.byte	0x88
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF282
	.byte	0x1
	.byte	0x89
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF283
	.byte	0x1
	.byte	0x89
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF284
	.byte	0x1
	.byte	0x8a
	.4byte	0x118
	.uleb128 0x1e
	.4byte	$LASF285
	.byte	0x1
	.byte	0x8c
	.4byte	0xb0
	.uleb128 0x1e
	.4byte	$LASF286
	.byte	0x1
	.byte	0x8d
	.4byte	0x8d9
	.uleb128 0x2b
	.4byte	$LASF288
	.byte	0x1
	.2byte	0x165
	.uleb128 0x2c
	.4byte	$LASF287
	.4byte	0xc83
	.4byte	$LASF275
	.uleb128 0x2b
	.4byte	$LASF289
	.byte	0x1
	.2byte	0x162
	.uleb128 0x2d
	.4byte	$LASF290
	.byte	0x1
	.byte	0xca
	.uleb128 0x2b
	.4byte	$LASF291
	.byte	0x1
	.2byte	0x138
	.uleb128 0x2b
	.4byte	$LASF292
	.byte	0x1
	.2byte	0x13b
	.uleb128 0x2e
	.ascii	"out\000"
	.byte	0x1
	.2byte	0x15b
	.uleb128 0x2f
	.uleb128 0x1d
	.ascii	"skb\000"
	.byte	0x1
	.byte	0xc1
	.4byte	0x3bd
	.uleb128 0x1e
	.4byte	$LASF33
	.byte	0x1
	.byte	0xc2
	.4byte	0x195
	.uleb128 0x1e
	.4byte	$LASF293
	.byte	0x1
	.byte	0xc3
	.4byte	0x4c
	.uleb128 0x1d
	.ascii	"i\000"
	.byte	0x1
	.byte	0xc3
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF294
	.byte	0x1
	.byte	0xc3
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF257
	.byte	0x1
	.byte	0xc4
	.4byte	0x4c
	.uleb128 0x1e
	.4byte	$LASF258
	.byte	0x1
	.byte	0xc5
	.4byte	0x4c
	.uleb128 0x2f
	.uleb128 0x1e
	.4byte	$LASF295
	.byte	0x1
	.byte	0xc5
	.4byte	0x10d
	.uleb128 0x1e
	.4byte	$LASF296
	.byte	0x1
	.byte	0xc5
	.4byte	0x10d
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x195
	.uleb128 0x30
	.4byte	0xde
	.4byte	0xc83
	.uleb128 0x31
	.4byte	0x156
	.byte	0x12
	.byte	0
	.uleb128 0x11
	.4byte	0xc73
	.uleb128 0x24
	.4byte	$LASF298
	.byte	0x1
	.2byte	0x169
	.4byte	0x4c
	.4byte	$LFB3382
	.4byte	$LFE3382-$LFB3382
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xefb
	.uleb128 0x26
	.ascii	"sk\000"
	.byte	0x1
	.2byte	0x169
	.4byte	0x838
	.uleb128 0x1
	.byte	0x65
	.uleb128 0x25
	.4byte	$LASF256
	.byte	0x1
	.2byte	0x169
	.4byte	0x245
	.uleb128 0x1
	.byte	0x6e
	.uleb128 0x25
	.4byte	$LASF257
	.byte	0x1
	.2byte	0x169
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x25
	.4byte	$LASF258
	.byte	0x1
	.2byte	0x16a
	.4byte	0x10d
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x25
	.4byte	$LASF259
	.byte	0x1
	.2byte	0x16a
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x66
	.uleb128 0x29
	.ascii	"res\000"
	.byte	0x1
	.2byte	0x16c
	.4byte	0x118
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x32
	.4byte	$LASF284
	.byte	0x1
	.2byte	0x16d
	.4byte	0x10d
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x32
	.4byte	$LASF299
	.byte	0x1
	.2byte	0x16e
	.4byte	0x10d
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x33
	.4byte	$LASF300
	.byte	0x1
	.2byte	0x16f
	.4byte	0x10d
	.uleb128 0x32
	.4byte	$LASF276
	.byte	0x1
	.2byte	0x170
	.4byte	0xefb
	.uleb128 0x3
	.byte	0x91
	.sleb128 -136
	.uleb128 0x27
	.ascii	"buf\000"
	.byte	0x1
	.2byte	0x171
	.4byte	0x24b
	.uleb128 0x27
	.ascii	"tmp\000"
	.byte	0x1
	.2byte	0x172
	.4byte	0x24b
	.uleb128 0x27
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x173
	.4byte	0x4c
	.uleb128 0x34
	.4byte	$LBB98
	.4byte	$LBE98-$LBB98
	.4byte	0xd75
	.uleb128 0x33
	.4byte	$LASF295
	.byte	0x1
	.2byte	0x182
	.4byte	0x10d
	.uleb128 0x33
	.4byte	$LASF296
	.byte	0x1
	.2byte	0x182
	.4byte	0x10d
	.byte	0
	.uleb128 0x35
	.4byte	0x920
	.4byte	$LBB99
	.4byte	$LBE99-$LBB99
	.byte	0x1
	.2byte	0x197
	.4byte	0xd8f
	.uleb128 0x36
	.4byte	0x92d
	.byte	0
	.uleb128 0x37
	.4byte	0xb18
	.4byte	$LBB101
	.4byte	$Ldebug_ranges0+0x40
	.byte	0x1
	.2byte	0x19a
	.uleb128 0x36
	.4byte	0xb53
	.uleb128 0x36
	.4byte	0xb48
	.uleb128 0x36
	.4byte	0xb3d
	.uleb128 0x36
	.4byte	0xb32
	.uleb128 0x36
	.4byte	0xb28
	.uleb128 0x2a
	.4byte	$Ldebug_ranges0+0x40
	.uleb128 0x38
	.4byte	0xb5e
	.uleb128 0x39
	.4byte	0xb68
	.uleb128 0x3
	.byte	0x8d
	.sleb128 108
	.uleb128 0x39
	.4byte	0xb73
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x38
	.4byte	0xb7e
	.uleb128 0x38
	.4byte	0xb89
	.uleb128 0x39
	.4byte	0xb94
	.uleb128 0x3
	.byte	0x8d
	.sleb128 112
	.uleb128 0x39
	.4byte	0xb9f
	.uleb128 0x3
	.byte	0x8d
	.sleb128 104
	.uleb128 0x38
	.4byte	0xbaa
	.uleb128 0x39
	.4byte	0xbb5
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x38
	.4byte	0xbc0
	.uleb128 0x3a
	.4byte	0xbcb
	.4byte	$L49
	.uleb128 0x3a
	.4byte	0xbe0
	.4byte	$L78
	.uleb128 0x3a
	.4byte	0xbe8
	.4byte	$L61
	.uleb128 0x3a
	.4byte	0xbef
	.4byte	$L63
	.uleb128 0x3a
	.4byte	0xbf7
	.4byte	$L65
	.uleb128 0x3a
	.4byte	0xbff
	.4byte	$L71
	.uleb128 0x39
	.4byte	0xbd3
	.uleb128 0x5
	.byte	0x3
	.4byte	__func__.41332
	.uleb128 0x3b
	.4byte	0x86c
	.4byte	$LBB103
	.4byte	$LBE103-$LBB103
	.byte	0x1
	.byte	0x98
	.4byte	0xe7d
	.uleb128 0x36
	.4byte	0x882
	.uleb128 0x36
	.4byte	0x878
	.uleb128 0x3c
	.4byte	$LBB104
	.4byte	$LBE104-$LBB104
	.uleb128 0x39
	.4byte	0x88d
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x38
	.4byte	0x896
	.uleb128 0x38
	.4byte	0x8a1
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	$Ldebug_ranges0+0xa8
	.uleb128 0x39
	.4byte	0xc08
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x39
	.4byte	0xc13
	.uleb128 0x3
	.byte	0x8d
	.sleb128 96
	.uleb128 0x38
	.4byte	0xc1e
	.uleb128 0x38
	.4byte	0xc29
	.uleb128 0x38
	.4byte	0xc32
	.uleb128 0x39
	.4byte	0xc3d
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x38
	.4byte	0xc48
	.uleb128 0x28
	.4byte	$Ldebug_ranges0+0xf8
	.4byte	0xec1
	.uleb128 0x38
	.4byte	0xc54
	.uleb128 0x38
	.4byte	0xc5f
	.byte	0
	.uleb128 0x3d
	.4byte	0x8df
	.4byte	$LBB108
	.4byte	$LBE108-$LBB108
	.byte	0x1
	.2byte	0x13a
	.uleb128 0x36
	.4byte	0x8f5
	.uleb128 0x36
	.4byte	0x8eb
	.uleb128 0x3c
	.4byte	$LBB109
	.4byte	$LBE109-$LBB109
	.uleb128 0x39
	.4byte	0x900
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x38
	.4byte	0x909
	.uleb128 0x38
	.4byte	0x914
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x30
	.4byte	0x195
	.4byte	0xf0b
	.uleb128 0x31
	.4byte	0x156
	.byte	0xf
	.byte	0
	.uleb128 0x3e
	.4byte	$LASF301
	.byte	0x1
	.2byte	0x1a0
	.4byte	0x118
	.4byte	$LFB3383
	.4byte	$LFE3383-$LFB3383
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf79
	.uleb128 0x25
	.4byte	$LASF187
	.byte	0x1
	.2byte	0x1a0
	.4byte	0x987
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x25
	.4byte	$LASF256
	.byte	0x1
	.2byte	0x1a0
	.4byte	0x245
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x25
	.4byte	$LASF257
	.byte	0x1
	.2byte	0x1a0
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x25
	.4byte	$LASF258
	.byte	0x1
	.2byte	0x1a1
	.4byte	0x10d
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x25
	.4byte	$LASF259
	.byte	0x1
	.2byte	0x1a1
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x29
	.ascii	"sk\000"
	.byte	0x1
	.2byte	0x1a3
	.4byte	0x838
	.uleb128 0x1
	.byte	0x60
	.byte	0
	.uleb128 0x3e
	.4byte	$LASF302
	.byte	0x1
	.2byte	0x1b8
	.4byte	0x118
	.4byte	$LFB3385
	.4byte	$LFE3385-$LFB3385
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x102f
	.uleb128 0x25
	.4byte	$LASF36
	.byte	0x1
	.2byte	0x1b8
	.4byte	0x55a
	.uleb128 0x1
	.byte	0x65
	.uleb128 0x25
	.4byte	$LASF256
	.byte	0x1
	.2byte	0x1b8
	.4byte	0x245
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x25
	.4byte	$LASF257
	.byte	0x1
	.2byte	0x1b9
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x25
	.4byte	$LASF258
	.byte	0x1
	.2byte	0x1b9
	.4byte	0x10d
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x25
	.4byte	$LASF303
	.byte	0x1
	.2byte	0x1b9
	.4byte	0x1f3
	.uleb128 0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x25
	.4byte	$LASF304
	.byte	0x1
	.2byte	0x1b9
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x32
	.4byte	$LASF187
	.byte	0x1
	.2byte	0x1bc
	.4byte	0x987
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x32
	.4byte	$LASF259
	.byte	0x1
	.2byte	0x1bd
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x37
	.4byte	0x939
	.4byte	$LBB141
	.4byte	$Ldebug_ranges0+0x110
	.byte	0x1
	.2byte	0x1c6
	.uleb128 0x36
	.4byte	0x97a
	.uleb128 0x36
	.4byte	0x96e
	.uleb128 0x36
	.4byte	0x962
	.uleb128 0x36
	.4byte	0x956
	.uleb128 0x36
	.4byte	0x94a
	.byte	0
	.byte	0
	.uleb128 0x24
	.4byte	$LASF305
	.byte	0x1
	.2byte	0x1c9
	.4byte	0x4c
	.4byte	$LFB3386
	.4byte	$LFE3386-$LFB3386
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10cf
	.uleb128 0x25
	.4byte	$LASF256
	.byte	0x1
	.2byte	0x1c9
	.4byte	0x245
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x26
	.ascii	"buf\000"
	.byte	0x1
	.2byte	0x1ca
	.4byte	0x24b
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x26
	.ascii	"sd\000"
	.byte	0x1
	.2byte	0x1ca
	.4byte	0x251
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x27
	.ascii	"tmp\000"
	.byte	0x1
	.2byte	0x1cc
	.4byte	0x24b
	.uleb128 0x32
	.4byte	$LASF36
	.byte	0x1
	.2byte	0x1cd
	.4byte	0x55a
	.uleb128 0x1
	.byte	0x65
	.uleb128 0x29
	.ascii	"pos\000"
	.byte	0x1
	.2byte	0x1ce
	.4byte	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x27
	.ascii	"ret\000"
	.byte	0x1
	.2byte	0x1cf
	.4byte	0x4c
	.uleb128 0x33
	.4byte	$LASF304
	.byte	0x1
	.2byte	0x1cf
	.4byte	0x4c
	.uleb128 0x29
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x1d0
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x3f
	.4byte	$LASF287
	.4byte	0x10df
	.uleb128 0x5
	.byte	0x3
	.4byte	__func__.41410
	.byte	0
	.uleb128 0x30
	.4byte	0xde
	.4byte	0x10df
	.uleb128 0x31
	.4byte	0x156
	.byte	0x15
	.byte	0
	.uleb128 0x11
	.4byte	0x10cf
	.uleb128 0x40
	.4byte	$LASF420
	.byte	0x1
	.2byte	0x20c
	.4byte	$LFB3388
	.4byte	$LFE3388-$LFB3388
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1145
	.uleb128 0x25
	.4byte	$LASF306
	.byte	0x1
	.2byte	0x20c
	.4byte	0x1145
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x25
	.4byte	$LASF307
	.byte	0x1
	.2byte	0x20d
	.4byte	0x94
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x32
	.4byte	$LASF308
	.byte	0x1
	.2byte	0x20f
	.4byte	0x94
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x27
	.ascii	"p\000"
	.byte	0x1
	.2byte	0x210
	.4byte	0x8b8
	.uleb128 0x37
	.4byte	0x98d
	.4byte	$LBB147
	.4byte	$Ldebug_ranges0+0x130
	.byte	0x1
	.2byte	0x21e
	.uleb128 0x36
	.4byte	0x99e
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x1a5
	.uleb128 0x24
	.4byte	$LASF309
	.byte	0x1
	.2byte	0x22b
	.4byte	0x118
	.4byte	$LFB3389
	.4byte	$LFE3389-$LFB3389
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1413
	.uleb128 0x25
	.4byte	$LASF36
	.byte	0x1
	.2byte	0x22b
	.4byte	0x55a
	.uleb128 0x1
	.byte	0x6e
	.uleb128 0x25
	.4byte	$LASF187
	.byte	0x1
	.2byte	0x22b
	.4byte	0x987
	.uleb128 0x3
	.byte	0x8d
	.sleb128 676
	.uleb128 0x25
	.4byte	$LASF303
	.byte	0x1
	.2byte	0x22b
	.4byte	0x1f3
	.uleb128 0x3
	.byte	0x8d
	.sleb128 680
	.uleb128 0x25
	.4byte	$LASF310
	.byte	0x1
	.2byte	0x22b
	.4byte	0x10d
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x32
	.4byte	$LASF306
	.byte	0x1
	.2byte	0x22e
	.4byte	0x1145
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x32
	.4byte	$LASF31
	.byte	0x1
	.2byte	0x22f
	.4byte	0x185
	.uleb128 0x3
	.byte	0x8d
	.sleb128 624
	.uleb128 0x29
	.ascii	"pos\000"
	.byte	0x1
	.2byte	0x230
	.4byte	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x32
	.4byte	$LASF311
	.byte	0x1
	.2byte	0x231
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x29
	.ascii	"err\000"
	.byte	0x1
	.2byte	0x232
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x65
	.uleb128 0x33
	.4byte	$LASF312
	.byte	0x1
	.2byte	0x233
	.4byte	0x4c
	.uleb128 0x32
	.4byte	$LASF313
	.byte	0x1
	.2byte	0x234
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x67
	.uleb128 0x32
	.4byte	$LASF314
	.byte	0x1
	.2byte	0x235
	.4byte	0x1413
	.uleb128 0x3
	.byte	0x91
	.sleb128 -640
	.uleb128 0x29
	.ascii	"iov\000"
	.byte	0x1
	.2byte	0x236
	.4byte	0x1423
	.uleb128 0x3
	.byte	0x91
	.sleb128 -232
	.uleb128 0x29
	.ascii	"msg\000"
	.byte	0x1
	.2byte	0x237
	.4byte	0x261
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x32
	.4byte	$LASF315
	.byte	0x1
	.2byte	0x238
	.4byte	0xb0
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x29
	.ascii	"ret\000"
	.byte	0x1
	.2byte	0x239
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3f
	.4byte	$LASF287
	.4byte	0x1433
	.uleb128 0x5
	.byte	0x3
	.4byte	__func__.41460
	.uleb128 0x2b
	.4byte	$LASF316
	.byte	0x1
	.2byte	0x2a7
	.uleb128 0x28
	.4byte	$Ldebug_ranges0+0x148
	.4byte	0x1304
	.uleb128 0x33
	.4byte	$LASF317
	.byte	0x1
	.2byte	0x23b
	.4byte	0x16d
	.uleb128 0x33
	.4byte	$LASF318
	.byte	0x1
	.2byte	0x23b
	.4byte	0x1438
	.uleb128 0x33
	.4byte	$LASF319
	.byte	0x1
	.2byte	0x23b
	.4byte	0xb0
	.uleb128 0x28
	.4byte	$Ldebug_ranges0+0x160
	.4byte	0x12cf
	.uleb128 0x33
	.4byte	$LASF320
	.byte	0x1
	.2byte	0x23b
	.4byte	0x94
	.uleb128 0x33
	.4byte	$LASF321
	.byte	0x1
	.2byte	0x23b
	.4byte	0x94
	.uleb128 0x33
	.4byte	$LASF322
	.byte	0x1
	.2byte	0x23b
	.4byte	0x94
	.uleb128 0x33
	.4byte	$LASF323
	.byte	0x1
	.2byte	0x23b
	.4byte	0x94
	.byte	0
	.uleb128 0x3c
	.4byte	$LBB154
	.4byte	$LBE154-$LBB154
	.uleb128 0x32
	.4byte	$LASF324
	.byte	0x1
	.2byte	0x23b
	.4byte	0x16d
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x32
	.4byte	$LASF325
	.byte	0x1
	.2byte	0x23b
	.4byte	0x1438
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x32
	.4byte	$LASF326
	.byte	0x1
	.2byte	0x23b
	.4byte	0xb0
	.uleb128 0x1
	.byte	0x56
	.byte	0
	.byte	0
	.uleb128 0x28
	.4byte	$Ldebug_ranges0+0x178
	.4byte	0x1372
	.uleb128 0x33
	.4byte	$LASF327
	.byte	0x1
	.2byte	0x255
	.4byte	0x94
	.uleb128 0x32
	.4byte	$LASF257
	.byte	0x1
	.2byte	0x256
	.4byte	0x94
	.uleb128 0x1
	.byte	0x66
	.uleb128 0x32
	.4byte	$LASF328
	.byte	0x1
	.2byte	0x257
	.4byte	0x195
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x32
	.4byte	$LASF329
	.byte	0x1
	.2byte	0x258
	.4byte	0x16d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x37
	.4byte	0x9d5
	.4byte	$LBB157
	.4byte	$Ldebug_ranges0+0x198
	.byte	0x1
	.2byte	0x270
	.uleb128 0x36
	.4byte	0x9e5
	.uleb128 0x41
	.4byte	0x7b7
	.4byte	$LBB158
	.4byte	$Ldebug_ranges0+0x198
	.byte	0x1e
	.byte	0x3b
	.uleb128 0x36
	.4byte	0x7c8
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3c
	.4byte	$LBB171
	.4byte	$LBE171-$LBB171
	.uleb128 0x33
	.4byte	$LASF317
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x16d
	.uleb128 0x33
	.4byte	$LASF318
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x1438
	.uleb128 0x33
	.4byte	$LASF319
	.byte	0x1
	.2byte	0x2a5
	.4byte	0xb0
	.uleb128 0x34
	.4byte	$LBB172
	.4byte	$LBE172-$LBB172
	.4byte	0x13dd
	.uleb128 0x33
	.4byte	$LASF320
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x94
	.uleb128 0x33
	.4byte	$LASF321
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x94
	.uleb128 0x33
	.4byte	$LASF322
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x94
	.uleb128 0x33
	.4byte	$LASF323
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x94
	.byte	0
	.uleb128 0x3c
	.4byte	$LBB173
	.4byte	$LBE173-$LBB173
	.uleb128 0x32
	.4byte	$LASF324
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x16d
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x32
	.4byte	$LASF325
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x1438
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x32
	.4byte	$LASF326
	.byte	0x1
	.2byte	0x2a5
	.4byte	0xb0
	.uleb128 0x1
	.byte	0x56
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x30
	.4byte	0x6d7
	.4byte	0x1423
	.uleb128 0x31
	.4byte	0x156
	.byte	0x10
	.byte	0
	.uleb128 0x30
	.4byte	0x25c
	.4byte	0x1433
	.uleb128 0x31
	.4byte	0x156
	.byte	0x10
	.byte	0
	.uleb128 0x11
	.4byte	0x10cf
	.uleb128 0x8
	.byte	0x4
	.4byte	0x143e
	.uleb128 0x42
	.uleb128 0x24
	.4byte	$LASF330
	.byte	0x1
	.2byte	0x2b3
	.4byte	0x118
	.4byte	$LFB3390
	.4byte	$LFE3390-$LFB3390
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1580
	.uleb128 0x25
	.4byte	$LASF331
	.byte	0x1
	.2byte	0x2b3
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x25
	.4byte	$LASF332
	.byte	0x1
	.2byte	0x2b3
	.4byte	0x1f3
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x25
	.4byte	$LASF333
	.byte	0x1
	.2byte	0x2b3
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x26
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x2b3
	.4byte	0x10d
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x25
	.4byte	$LASF334
	.byte	0x1
	.2byte	0x2b3
	.4byte	0x1580
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x32
	.4byte	$LASF335
	.byte	0x1
	.2byte	0x2b5
	.4byte	0x55a
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x32
	.4byte	$LASF336
	.byte	0x1
	.2byte	0x2b6
	.4byte	0x4c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x32
	.4byte	$LASF337
	.byte	0x1
	.2byte	0x2b7
	.4byte	0x4c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x32
	.4byte	$LASF306
	.byte	0x1
	.2byte	0x2b8
	.4byte	0x1145
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x32
	.4byte	$LASF187
	.byte	0x1
	.2byte	0x2ba
	.4byte	0x987
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x32
	.4byte	$LASF338
	.byte	0x1
	.2byte	0x2bb
	.4byte	0xd8
	.uleb128 0x1
	.byte	0x57
	.uleb128 0x2b
	.4byte	$LASF316
	.byte	0x1
	.2byte	0x2dd
	.uleb128 0x3f
	.4byte	$LASF287
	.4byte	0x1596
	.uleb128 0x5
	.byte	0x3
	.4byte	__func__.41504
	.uleb128 0x43
	.4byte	0x9f1
	.4byte	$LBB174
	.4byte	$Ldebug_ranges0+0x1c0
	.byte	0x1
	.2byte	0x2d0
	.4byte	0x1536
	.uleb128 0x36
	.4byte	0xa0c
	.uleb128 0x36
	.4byte	0xa01
	.uleb128 0x2a
	.4byte	$Ldebug_ranges0+0x1c0
	.uleb128 0x38
	.4byte	0xa17
	.byte	0
	.byte	0
	.uleb128 0x35
	.4byte	0x9f1
	.4byte	$LBB178
	.4byte	$LBE178-$LBB178
	.byte	0x1
	.2byte	0x2d0
	.4byte	0x1564
	.uleb128 0x36
	.4byte	0xa0c
	.uleb128 0x36
	.4byte	0xa01
	.uleb128 0x3c
	.4byte	$LBB179
	.4byte	$LBE179-$LBB179
	.uleb128 0x38
	.4byte	0xa17
	.byte	0
	.byte	0
	.uleb128 0x37
	.4byte	0xa23
	.4byte	$LBB180
	.4byte	$Ldebug_ranges0+0x1d8
	.byte	0x1
	.2byte	0x2df
	.uleb128 0x36
	.4byte	0xa3a
	.uleb128 0x36
	.4byte	0xa2f
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x4c
	.uleb128 0x30
	.4byte	0xde
	.4byte	0x1596
	.uleb128 0x31
	.4byte	0x156
	.byte	0xa
	.byte	0
	.uleb128 0x11
	.4byte	0x1586
	.uleb128 0x24
	.4byte	$LASF339
	.byte	0x1
	.2byte	0x346
	.4byte	0x4c
	.4byte	$LFB3392
	.4byte	$LFE3392-$LFB3392
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1636
	.uleb128 0x26
	.ascii	"iov\000"
	.byte	0x1
	.2byte	0x346
	.4byte	0x1636
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x25
	.4byte	$LASF340
	.byte	0x1
	.2byte	0x346
	.4byte	0x37f
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x26
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x346
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x2a
	.4byte	$Ldebug_ranges0+0x1f0
	.uleb128 0x33
	.4byte	$LASF293
	.byte	0x1
	.2byte	0x34c
	.4byte	0x4c
	.uleb128 0x34
	.4byte	$LBB185
	.4byte	$LBE185-$LBB185
	.4byte	0x1616
	.uleb128 0x33
	.4byte	$LASF295
	.byte	0x1
	.2byte	0x34c
	.4byte	0x5e
	.uleb128 0x33
	.4byte	$LASF296
	.byte	0x1
	.2byte	0x34c
	.4byte	0x5e
	.byte	0
	.uleb128 0x2a
	.4byte	$Ldebug_ranges0+0x208
	.uleb128 0x33
	.4byte	$LASF341
	.byte	0x1
	.2byte	0x34d
	.4byte	0x10d
	.uleb128 0x33
	.4byte	$LASF342
	.byte	0x1
	.2byte	0x34d
	.4byte	0x16d
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x257
	.uleb128 0x24
	.4byte	$LASF343
	.byte	0x1
	.2byte	0x362
	.4byte	0x4c
	.4byte	$LFB3393
	.4byte	$LFE3393-$LFB3393
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x176b
	.uleb128 0x26
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x362
	.4byte	0x176b
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x25
	.4byte	$LASF257
	.byte	0x1
	.2byte	0x362
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x26
	.ascii	"to\000"
	.byte	0x1
	.2byte	0x363
	.4byte	0x1636
	.uleb128 0x3
	.byte	0x8d
	.sleb128 72
	.uleb128 0x26
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x363
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x29
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x366
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x32
	.4byte	$LASF344
	.byte	0x1
	.2byte	0x366
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x27
	.ascii	"end\000"
	.byte	0x1
	.2byte	0x366
	.4byte	0x4c
	.uleb128 0x33
	.4byte	$LASF345
	.byte	0x1
	.2byte	0x368
	.4byte	0x3bd
	.uleb128 0x44
	.4byte	$LASF421
	.byte	0x1
	.2byte	0x36d
	.4byte	$L198
	.uleb128 0x28
	.4byte	$Ldebug_ranges0+0x220
	.4byte	0x1754
	.uleb128 0x33
	.4byte	$LASF346
	.byte	0x1
	.2byte	0x373
	.4byte	0x4c
	.uleb128 0x2a
	.4byte	$Ldebug_ranges0+0x240
	.uleb128 0x33
	.4byte	$LASF293
	.byte	0x1
	.2byte	0x376
	.4byte	0x4c
	.uleb128 0x29
	.ascii	"o\000"
	.byte	0x1
	.2byte	0x376
	.4byte	0x4c
	.uleb128 0x1
	.byte	0x66
	.uleb128 0x2a
	.4byte	$Ldebug_ranges0+0x268
	.uleb128 0x33
	.4byte	$LASF246
	.byte	0x1
	.2byte	0x37f
	.4byte	0x1776
	.uleb128 0x33
	.4byte	$LASF33
	.byte	0x1
	.2byte	0x381
	.4byte	0x195
	.uleb128 0x27
	.ascii	"p\000"
	.byte	0x1
	.2byte	0x387
	.4byte	0x16d
	.uleb128 0x37
	.4byte	0x9d5
	.4byte	$LBB192
	.4byte	$Ldebug_ranges0+0x288
	.byte	0x1
	.2byte	0x387
	.uleb128 0x36
	.4byte	0x9e5
	.uleb128 0x41
	.4byte	0x7b7
	.4byte	$LBB193
	.4byte	$Ldebug_ranges0+0x288
	.byte	0x1e
	.byte	0x3b
	.uleb128 0x36
	.4byte	0x7c8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3d
	.4byte	0xa46
	.4byte	$LBB207
	.4byte	$LBE207-$LBB207
	.byte	0x1
	.2byte	0x399
	.uleb128 0x36
	.4byte	0xa52
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x1771
	.uleb128 0x11
	.4byte	0x385
	.uleb128 0x8
	.byte	0x4
	.4byte	0x36f
	.uleb128 0x45
	.4byte	$LASF422
	.byte	0x1
	.2byte	0x40e
	.4byte	0x4c
	.4byte	$LFB3394
	.4byte	$LFE3394-$LFB3394
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x46
	.4byte	$LASF423
	.byte	0x1
	.2byte	0x416
	.4byte	$LFB3395
	.4byte	$LFE3395-$LFB3395
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xa
	.4byte	$LASF347
	.uleb128 0xa
	.4byte	$LASF348
	.uleb128 0xa
	.4byte	$LASF349
	.uleb128 0x47
	.4byte	$LASF350
	.byte	0x23
	.byte	0x6c
	.4byte	0x5e
	.4byte	0x1fbd0
	.uleb128 0x32
	.4byte	$LASF351
	.byte	0x1
	.2byte	0x1fc
	.4byte	0x4c
	.uleb128 0x5
	.byte	0x3
	.4byte	bdp_ratelimits
	.uleb128 0x32
	.4byte	$LASF352
	.byte	0x1
	.2byte	0x406
	.4byte	0x6c6
	.uleb128 0x5
	.byte	0x3
	.4byte	_rtl_sendfile_hook
	.uleb128 0x30
	.4byte	0xde
	.4byte	0x17f6
	.uleb128 0x31
	.4byte	0x156
	.byte	0xb
	.byte	0
	.uleb128 0x32
	.4byte	$LASF353
	.byte	0x1
	.2byte	0x41f
	.4byte	0x1808
	.uleb128 0x5
	.byte	0x3
	.4byte	__UNIQUE_ID_license1
	.uleb128 0x11
	.4byte	0x17e6
	.uleb128 0x48
	.4byte	$LASF354
	.byte	0x24
	.byte	0x21
	.4byte	0x6d2
	.uleb128 0x30
	.4byte	0x14a
	.4byte	0x1823
	.uleb128 0x49
	.byte	0
	.uleb128 0x48
	.4byte	$LASF355
	.byte	0x25
	.byte	0x54
	.4byte	0x1818
	.uleb128 0x30
	.4byte	0x4c
	.4byte	0x1839
	.uleb128 0x49
	.byte	0
	.uleb128 0x48
	.4byte	$LASF356
	.byte	0x26
	.byte	0x24
	.4byte	0x182e
	.uleb128 0x30
	.4byte	0xde
	.4byte	0x184f
	.uleb128 0x49
	.byte	0
	.uleb128 0x4a
	.4byte	$LASF357
	.byte	0x1d
	.2byte	0x1b2
	.4byte	0x185b
	.uleb128 0x11
	.4byte	0x1844
	.uleb128 0x30
	.4byte	0x94
	.4byte	0x1876
	.uleb128 0x31
	.4byte	0x156
	.byte	0x20
	.uleb128 0x31
	.4byte	0x156
	.byte	0
	.byte	0
	.uleb128 0x4a
	.4byte	$LASF358
	.byte	0x27
	.2byte	0x2f9
	.4byte	0x1882
	.uleb128 0x11
	.4byte	0x1860
	.uleb128 0x48
	.4byte	$LASF359
	.byte	0x28
	.byte	0x76
	.4byte	0xf0
	.uleb128 0x48
	.4byte	$LASF360
	.byte	0x29
	.byte	0x22
	.4byte	0x4c
	.uleb128 0x48
	.4byte	$LASF361
	.byte	0x29
	.byte	0x23
	.4byte	0x4c
	.uleb128 0x48
	.4byte	$LASF362
	.byte	0x2a
	.byte	0x8d
	.4byte	0x17a4
	.uleb128 0x4a
	.4byte	$LASF363
	.byte	0x2b
	.2byte	0x799
	.4byte	0x17a9
	.uleb128 0x48
	.4byte	$LASF32
	.byte	0x2c
	.byte	0xfd
	.4byte	0x190
	.uleb128 0x48
	.4byte	$LASF364
	.byte	0x2d
	.byte	0x4d
	.4byte	0x8b3
	.uleb128 0x48
	.4byte	$LASF365
	.byte	0x10
	.byte	0x3f
	.4byte	0x94
	.uleb128 0x48
	.4byte	$LASF366
	.byte	0x2e
	.byte	0x60
	.4byte	0x16f
	.uleb128 0x48
	.4byte	$LASF367
	.byte	0x2f
	.byte	0x3f
	.4byte	0x18f6
	.uleb128 0x11
	.4byte	0x94
	.uleb128 0x48
	.4byte	$LASF368
	.byte	0x4
	.byte	0x1d
	.4byte	0x94
	.uleb128 0x48
	.4byte	$LASF369
	.byte	0x30
	.byte	0x4c
	.4byte	0x4c
	.uleb128 0x4a
	.4byte	$LASF370
	.byte	0x30
	.2byte	0x2ad
	.4byte	0x195
	.uleb128 0x4a
	.4byte	$LASF371
	.byte	0x31
	.2byte	0x151
	.4byte	0x1929
	.uleb128 0x8
	.byte	0x4
	.4byte	0x17ae
	.uleb128 0x4a
	.4byte	$LASF372
	.byte	0x31
	.2byte	0x154
	.4byte	0x1929
	.uleb128 0x4a
	.4byte	$LASF373
	.byte	0x30
	.2byte	0x391
	.4byte	0x1ee
	.uleb128 0x4a
	.4byte	$LASF374
	.byte	0x2b
	.2byte	0x61e
	.4byte	0x1953
	.uleb128 0x8
	.byte	0x4
	.4byte	0x180
	.uleb128 0x48
	.4byte	$LASF375
	.byte	0x32
	.byte	0xa
	.4byte	0x4c
	.uleb128 0x48
	.4byte	$LASF376
	.byte	0x33
	.byte	0xe1
	.4byte	0x94
	.uleb128 0x30
	.4byte	0x1e3
	.4byte	0x1980
	.uleb128 0x4b
	.4byte	0x156
	.2byte	0x3ff
	.byte	0
	.uleb128 0x48
	.4byte	$LASF377
	.byte	0x34
	.byte	0x48
	.4byte	0x196f
	.uleb128 0x48
	.4byte	$LASF378
	.byte	0x35
	.byte	0x4d
	.4byte	0x94
	.uleb128 0x4a
	.4byte	$LASF379
	.byte	0x36
	.2byte	0x1cb
	.4byte	0x94
	.uleb128 0x30
	.4byte	0x162
	.4byte	0x19b2
	.uleb128 0x31
	.4byte	0x156
	.byte	0x1b
	.byte	0
	.uleb128 0x48
	.4byte	$LASF380
	.byte	0x37
	.byte	0x5d
	.4byte	0x19a2
	.uleb128 0x4a
	.4byte	$LASF381
	.byte	0x4
	.2byte	0x555
	.4byte	0x1844
	.uleb128 0x4a
	.4byte	$LASF382
	.byte	0x4
	.2byte	0x555
	.4byte	0x1844
	.uleb128 0x48
	.4byte	$LASF383
	.byte	0x2e
	.byte	0x45
	.4byte	0x14f
	.uleb128 0x48
	.4byte	$LASF384
	.byte	0x2e
	.byte	0x4d
	.4byte	0x14f
	.uleb128 0xd
	.4byte	0x19fb
	.uleb128 0xe
	.4byte	0x94
	.uleb128 0xe
	.4byte	0x4c
	.byte	0
	.uleb128 0x48
	.4byte	$LASF385
	.byte	0x2e
	.byte	0x7f
	.4byte	0x1a06
	.uleb128 0x8
	.byte	0x4
	.4byte	0x19eb
	.uleb128 0x30
	.4byte	0x1a1c
	.4byte	0x1a1c
	.uleb128 0x31
	.4byte	0x156
	.byte	0xd
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x1fe
	.uleb128 0x48
	.4byte	$LASF386
	.byte	0x38
	.byte	0xe0
	.4byte	0x1a0c
	.uleb128 0x48
	.4byte	$LASF387
	.byte	0x39
	.byte	0x8a
	.4byte	0x208
	.uleb128 0x4a
	.4byte	$LASF388
	.byte	0x33
	.2byte	0x114
	.4byte	0x4c
	.uleb128 0x4a
	.4byte	$LASF389
	.byte	0x33
	.2byte	0x16b
	.4byte	0x162
	.uleb128 0x4a
	.4byte	$LASF390
	.byte	0x33
	.2byte	0x16c
	.4byte	0xb0
	.uleb128 0x30
	.4byte	0x145
	.4byte	0x1a72
	.uleb128 0x31
	.4byte	0x156
	.byte	0xc
	.uleb128 0x31
	.4byte	0x156
	.byte	0x7
	.byte	0
	.uleb128 0x48
	.4byte	$LASF391
	.byte	0x3a
	.byte	0x62
	.4byte	0x1a5c
	.uleb128 0x30
	.4byte	0x1a8d
	.4byte	0x1a8d
	.uleb128 0x31
	.4byte	0x156
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x1a93
	.uleb128 0x11
	.4byte	0x3c3
	.uleb128 0x48
	.4byte	$LASF108
	.byte	0x3a
	.byte	0xea
	.4byte	0x1a7d
	.uleb128 0xd
	.4byte	0x1ab3
	.uleb128 0xe
	.4byte	0x3bd
	.uleb128 0xe
	.4byte	0x1ab3
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.4byte	0x3c8
	.uleb128 0x4a
	.4byte	$LASF392
	.byte	0x3a
	.2byte	0x114
	.4byte	0x1ac5
	.uleb128 0x8
	.byte	0x4
	.4byte	0x1aa3
	.uleb128 0x48
	.4byte	$LASF393
	.byte	0x3b
	.byte	0x86
	.4byte	0x3cd
	.uleb128 0x4a
	.4byte	$LASF394
	.byte	0x2
	.2byte	0x2b8
	.4byte	0x203
	.uleb128 0x48
	.4byte	$LASF395
	.byte	0x21
	.byte	0xcd
	.4byte	0x7e
	.uleb128 0x48
	.4byte	$LASF396
	.byte	0x21
	.byte	0xce
	.4byte	0x7e
	.uleb128 0x48
	.4byte	$LASF397
	.byte	0x3c
	.byte	0xb9
	.4byte	0x1b03
	.uleb128 0x11
	.4byte	0x1844
	.uleb128 0x4a
	.4byte	$LASF398
	.byte	0x1b
	.2byte	0x1f4
	.4byte	0x1b14
	.uleb128 0x8
	.byte	0x4
	.4byte	0x1f9
	.uleb128 0x48
	.4byte	$LASF399
	.byte	0x1c
	.byte	0x3e
	.4byte	0x5ca
	.uleb128 0x30
	.4byte	0x2c
	.4byte	0x1b35
	.uleb128 0x31
	.4byte	0x156
	.byte	0xf
	.byte	0
	.uleb128 0x48
	.4byte	$LASF400
	.byte	0x3d
	.byte	0xd4
	.4byte	0x1b40
	.uleb128 0x11
	.4byte	0x1b25
	.uleb128 0x4a
	.4byte	$LASF401
	.byte	0x3d
	.2byte	0x135
	.4byte	0x4c
	.uleb128 0x48
	.4byte	$LASF402
	.byte	0x3e
	.byte	0xcd
	.4byte	0x8b8
	.uleb128 0x48
	.4byte	$LASF403
	.byte	0x3f
	.byte	0xfa
	.4byte	0x4c
	.uleb128 0x48
	.4byte	$LASF404
	.byte	0x3f
	.byte	0xfb
	.4byte	0x4c
	.uleb128 0x48
	.4byte	$LASF405
	.byte	0x3f
	.byte	0xfc
	.4byte	0x4c
	.uleb128 0x48
	.4byte	$LASF406
	.byte	0x3f
	.byte	0xfd
	.4byte	0x4c
	.uleb128 0x4a
	.4byte	$LASF407
	.byte	0x3f
	.2byte	0x109
	.4byte	0x4c
	.uleb128 0x4a
	.4byte	$LASF408
	.byte	0x3f
	.2byte	0x10b
	.4byte	0x4c
	.uleb128 0x4a
	.4byte	$LASF409
	.byte	0x3f
	.2byte	0x110
	.4byte	0x4c
	.uleb128 0x4a
	.4byte	$LASF410
	.byte	0x3f
	.2byte	0x11e
	.4byte	0x4c
	.uleb128 0x4a
	.4byte	$LASF411
	.byte	0x3f
	.2byte	0x11f
	.4byte	0x4c
	.uleb128 0x48
	.4byte	$LASF412
	.byte	0x40
	.byte	0x15
	.4byte	0x1bcf
	.uleb128 0x8
	.byte	0x4
	.4byte	0x6c6
	.uleb128 0x48
	.4byte	$LASF413
	.byte	0x41
	.byte	0x9b
	.4byte	0x1be0
	.uleb128 0x11
	.4byte	0x1a0
	.uleb128 0x48
	.4byte	$LASF414
	.byte	0x1
	.byte	0x2c
	.4byte	0xb0
	.uleb128 0x4c
	.4byte	$LASF415
	.byte	0x1
	.byte	0x75
	.4byte	0x714
	.uleb128 0x5
	.byte	0x3
	.4byte	g2_tcp_ctl
	.byte	0
	.section	.debug_abbrev,"",@progbits
$Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x15
	.byte	0
	.uleb128 0x27
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x1c
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0xa
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x42
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x43
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x44
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x45
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x46
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x47
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x48
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x49
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x4b
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x4c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	$Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	$LFB3394
	.4byte	$LFE3394-$LFB3394
	.4byte	$LFB3395
	.4byte	$LFE3395-$LFB3395
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
$Ldebug_ranges0:
	.4byte	$LBB80
	.4byte	$LBE80
	.4byte	$LBB81
	.4byte	$LBE81
	.4byte	$LBB85
	.4byte	$LBE85
	.4byte	0
	.4byte	0
	.4byte	$LBB82
	.4byte	$LBE82
	.4byte	$LBB83
	.4byte	$LBE83
	.4byte	$LBB84
	.4byte	$LBE84
	.4byte	0
	.4byte	0
	.4byte	$LBB101
	.4byte	$LBE101
	.4byte	$LBB130
	.4byte	$LBE130
	.4byte	$LBB131
	.4byte	$LBE131
	.4byte	$LBB132
	.4byte	$LBE132
	.4byte	$LBB133
	.4byte	$LBE133
	.4byte	$LBB134
	.4byte	$LBE134
	.4byte	$LBB135
	.4byte	$LBE135
	.4byte	$LBB136
	.4byte	$LBE136
	.4byte	$LBB137
	.4byte	$LBE137
	.4byte	$LBB138
	.4byte	$LBE138
	.4byte	$LBB139
	.4byte	$LBE139
	.4byte	$LBB140
	.4byte	$LBE140
	.4byte	0
	.4byte	0
	.4byte	$LBB105
	.4byte	$LBE105
	.4byte	$LBB111
	.4byte	$LBE111
	.4byte	$LBB112
	.4byte	$LBE112
	.4byte	$LBB113
	.4byte	$LBE113
	.4byte	$LBB114
	.4byte	$LBE114
	.4byte	$LBB115
	.4byte	$LBE115
	.4byte	$LBB116
	.4byte	$LBE116
	.4byte	$LBB117
	.4byte	$LBE117
	.4byte	$LBB118
	.4byte	$LBE118
	.4byte	0
	.4byte	0
	.4byte	$LBB106
	.4byte	$LBE106
	.4byte	$LBB107
	.4byte	$LBE107
	.4byte	0
	.4byte	0
	.4byte	$LBB141
	.4byte	$LBE141
	.4byte	$LBB145
	.4byte	$LBE145
	.4byte	$LBB146
	.4byte	$LBE146
	.4byte	0
	.4byte	0
	.4byte	$LBB147
	.4byte	$LBE147
	.4byte	$LBB150
	.4byte	$LBE150
	.4byte	0
	.4byte	0
	.4byte	$LBB151
	.4byte	$LBE151
	.4byte	$LBB155
	.4byte	$LBE155
	.4byte	0
	.4byte	0
	.4byte	$LBB152
	.4byte	$LBE152
	.4byte	$LBB153
	.4byte	$LBE153
	.4byte	0
	.4byte	0
	.4byte	$LBB156
	.4byte	$LBE156
	.4byte	$LBB169
	.4byte	$LBE169
	.4byte	$LBB170
	.4byte	$LBE170
	.4byte	0
	.4byte	0
	.4byte	$LBB157
	.4byte	$LBE157
	.4byte	$LBB166
	.4byte	$LBE166
	.4byte	$LBB167
	.4byte	$LBE167
	.4byte	$LBB168
	.4byte	$LBE168
	.4byte	0
	.4byte	0
	.4byte	$LBB174
	.4byte	$LBE174
	.4byte	$LBB177
	.4byte	$LBE177
	.4byte	0
	.4byte	0
	.4byte	$LBB180
	.4byte	$LBE180
	.4byte	$LBB183
	.4byte	$LBE183
	.4byte	0
	.4byte	0
	.4byte	$LBB184
	.4byte	$LBE184
	.4byte	$LBB188
	.4byte	$LBE188
	.4byte	0
	.4byte	0
	.4byte	$LBB186
	.4byte	$LBE186
	.4byte	$LBB187
	.4byte	$LBE187
	.4byte	0
	.4byte	0
	.4byte	$LBB189
	.4byte	$LBE189
	.4byte	$LBB206
	.4byte	$LBE206
	.4byte	$LBB209
	.4byte	$LBE209
	.4byte	0
	.4byte	0
	.4byte	$LBB190
	.4byte	$LBE190
	.4byte	$LBB203
	.4byte	$LBE203
	.4byte	$LBB204
	.4byte	$LBE204
	.4byte	$LBB205
	.4byte	$LBE205
	.4byte	0
	.4byte	0
	.4byte	$LBB191
	.4byte	$LBE191
	.4byte	$LBB201
	.4byte	$LBE201
	.4byte	$LBB202
	.4byte	$LBE202
	.4byte	0
	.4byte	0
	.4byte	$LBB192
	.4byte	$LBE192
	.4byte	$LBB199
	.4byte	$LBE199
	.4byte	$LBB200
	.4byte	$LBE200
	.4byte	0
	.4byte	0
	.4byte	$Ltext0
	.4byte	$Letext0
	.4byte	$LFB3394
	.4byte	$LFE3394
	.4byte	$LFB3395
	.4byte	$LFE3395
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
$Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
$LASF303:
	.ascii	"ppos\000"
$LASF70:
	.ascii	"NETIF_F_LLTX_BIT\000"
$LASF218:
	.ascii	"__ND_OPT_ARRAY_MAX\000"
$LASF198:
	.ascii	"TCPF_LISTEN\000"
$LASF278:
	.ascii	"psize\000"
$LASF270:
	.ascii	"fput_light\000"
$LASF111:
	.ascii	"TCP_CONNTRACK_SYN_SENT\000"
$LASF89:
	.ascii	"NETIF_F_RXCSUM_BIT\000"
$LASF180:
	.ascii	"RTAX_HOPLIMIT\000"
$LASF398:
	.ascii	"ksoftirqd\000"
$LASF234:
	.ascii	"mpages\000"
$LASF361:
	.ascii	"overflowgid\000"
$LASF313:
	.ascii	"cPagesAllocated\000"
$LASF16:
	.ascii	"char\000"
$LASF311:
	.ascii	"count_tmp\000"
$LASF121:
	.ascii	"TCP_CONNTRACK_IGNORE\000"
$LASF387:
	.ascii	"ioport_resource\000"
$LASF115:
	.ascii	"TCP_CONNTRACK_CLOSE_WAIT\000"
$LASF329:
	.ascii	"fsdata\000"
$LASF362:
	.ascii	"init_user_ns\000"
$LASF229:
	.ascii	"rv_fsdata\000"
$LASF356:
	.ascii	"console_printk\000"
$LASF210:
	.ascii	"RCU_SOFTIRQ\000"
$LASF219:
	.ascii	"ND_OPT_ROUTE_INFO\000"
$LASF259:
	.ascii	"flags\000"
$LASF304:
	.ascii	"more\000"
$LASF212:
	.ascii	"__ND_OPT_PREFIX_INFO_END\000"
$LASF87:
	.ascii	"NETIF_F_NTUPLE_BIT\000"
$LASF35:
	.ascii	"address_space\000"
$LASF41:
	.ascii	"SB_FREEZE_COMPLETE\000"
$LASF179:
	.ascii	"RTAX_REORDERING\000"
$LASF145:
	.ascii	"IFLA_MASTER\000"
$LASF6:
	.ascii	"unsigned int\000"
$LASF137:
	.ascii	"IFLA_BROADCAST\000"
$LASF345:
	.ascii	"next\000"
$LASF206:
	.ascii	"BLOCK_IOPOLL_SOFTIRQ\000"
$LASF132:
	.ascii	"XFRM_POLICY_FWD\000"
$LASF406:
	.ascii	"sysctl_tcp_keepalive_intvl\000"
$LASF292:
	.ascii	"wait_for_memory\000"
$LASF43:
	.ascii	"pglist_data\000"
$LASF160:
	.ascii	"IFLA_PORT_SELF\000"
$LASF235:
	.ascii	"ackcnt\000"
$LASF348:
	.ascii	"pid_namespace\000"
$LASF277:
	.ascii	"poffset\000"
$LASF85:
	.ascii	"NETIF_F_SCTP_CSUM_BIT\000"
$LASF246:
	.ascii	"frag\000"
$LASF260:
	.ascii	"sync_writeback_pages\000"
$LASF139:
	.ascii	"IFLA_MTU\000"
$LASF359:
	.ascii	"persistent_clock_exist\000"
$LASF223:
	.ascii	"rtl_sendfile_ops\000"
$LASF149:
	.ascii	"IFLA_MAP\000"
$LASF214:
	.ascii	"ND_OPT_TARGET_LL_ADDR\000"
$LASF407:
	.ascii	"sysctl_tcp_max_orphans\000"
$LASF167:
	.ascii	"IFLA_NUM_RX_QUEUES\000"
$LASF334:
	.ascii	"run_normal\000"
$LASF401:
	.ascii	"sysctl_ip_default_ttl\000"
$LASF283:
	.ascii	"page_count\000"
$LASF337:
	.ascii	"error\000"
$LASF221:
	.ascii	"ND_OPT_DNSSL\000"
$LASF318:
	.ascii	"__cu_from\000"
$LASF267:
	.ascii	"__cs\000"
$LASF171:
	.ascii	"RTAX_LOCK\000"
$LASF94:
	.ascii	"NETIF_F_HW_VLAN_STAG_TX_BIT\000"
$LASF408:
	.ascii	"sysctl_tcp_reordering\000"
$LASF103:
	.ascii	"NFPROTO_ARP\000"
$LASF242:
	.ascii	"__might_sleep\000"
$LASF119:
	.ascii	"TCP_CONNTRACK_LISTEN\000"
$LASF216:
	.ascii	"ND_OPT_REDIRECT_HDR\000"
$LASF354:
	.ascii	"__this_module\000"
$LASF275:
	.ascii	"do_tcp_send_mpages\000"
$LASF130:
	.ascii	"XFRM_POLICY_IN\000"
$LASF320:
	.ascii	"__addr\000"
$LASF293:
	.ascii	"copy\000"
$LASF15:
	.ascii	"__kernel_loff_t\000"
$LASF68:
	.ascii	"NETIF_F_VLAN_CHALLENGED_BIT\000"
$LASF309:
	.ascii	"do_splice_from_socket\000"
$LASF333:
	.ascii	"fd_out\000"
$LASF50:
	.ascii	"pipe_buf_operations\000"
$LASF370:
	.ascii	"mem_map\000"
$LASF332:
	.ascii	"off_out\000"
$LASF288:
	.ascii	"out_err\000"
$LASF51:
	.ascii	"splice_desc\000"
$LASF164:
	.ascii	"IFLA_EXT_MASK\000"
$LASF62:
	.ascii	"NETIF_F_IPV6_CSUM_BIT\000"
$LASF67:
	.ascii	"NETIF_F_HW_VLAN_CTAG_FILTER_BIT\000"
$LASF248:
	.ascii	"tcp_sk\000"
$LASF104:
	.ascii	"NFPROTO_BRIDGE\000"
$LASF393:
	.ascii	"init_net\000"
$LASF272:
	.ascii	"__BUG_ON\000"
$LASF397:
	.ascii	"inet_csk_timer_bug_msg\000"
$LASF409:
	.ascii	"sysctl_tcp_adv_win_scale\000"
$LASF341:
	.ascii	"__len\000"
$LASF159:
	.ascii	"IFLA_VF_PORTS\000"
$LASF14:
	.ascii	"__kernel_ssize_t\000"
$LASF52:
	.ascii	"splice_actor\000"
$LASF245:
	.ascii	"skb_frag_page\000"
$LASF384:
	.ascii	"__flush_cache_vunmap\000"
$LASF202:
	.ascii	"TIMER_SOFTIRQ\000"
$LASF351:
	.ascii	"bdp_ratelimits\000"
$LASF8:
	.ascii	"long long unsigned int\000"
$LASF42:
	.ascii	"pte_t\000"
$LASF378:
	.ascii	"zero_page_mask\000"
$LASF276:
	.ascii	"pages\000"
$LASF184:
	.ascii	"RTAX_INITRWND\000"
$LASF29:
	.ascii	"thread_info\000"
$LASF255:
	.ascii	"kernel_sendpages\000"
$LASF76:
	.ascii	"NETIF_F_UFO_BIT\000"
$LASF120:
	.ascii	"TCP_CONNTRACK_MAX\000"
$LASF27:
	.ascii	"cpuinfo_mips\000"
$LASF256:
	.ascii	"pipe\000"
$LASF372:
	.ascii	"system_freezable_wq\000"
$LASF107:
	.ascii	"NFPROTO_NUMPROTO\000"
$LASF152:
	.ascii	"IFLA_LINKMODE\000"
$LASF290:
	.ascii	"new_segment\000"
$LASF146:
	.ascii	"IFLA_WIRELESS\000"
$LASF106:
	.ascii	"NFPROTO_DECNET\000"
$LASF162:
	.ascii	"IFLA_GROUP\000"
$LASF338:
	.ascii	"fs_name\000"
$LASF88:
	.ascii	"NETIF_F_RXHASH_BIT\000"
$LASF21:
	.ascii	"size_t\000"
$LASF257:
	.ascii	"offset\000"
$LASF178:
	.ascii	"RTAX_ADVMSS\000"
$LASF195:
	.ascii	"TCPF_CLOSE\000"
$LASF157:
	.ascii	"IFLA_VFINFO_LIST\000"
$LASF86:
	.ascii	"NETIF_F_FCOE_MTU_BIT\000"
$LASF226:
	.ascii	"rv_page\000"
$LASF380:
	.ascii	"vm_stat\000"
$LASF19:
	.ascii	"_Bool\000"
$LASF326:
	.ascii	"__cu_len_r\000"
$LASF90:
	.ascii	"NETIF_F_NOCACHE_COPY_BIT\000"
$LASF420:
	.ascii	"balance_dirty_pages_ratelimited_nr\000"
$LASF389:
	.ascii	"nr_swap_pages\000"
$LASF385:
	.ascii	"__flush_kernel_vmap_range\000"
$LASF215:
	.ascii	"ND_OPT_PREFIX_INFO\000"
$LASF47:
	.ascii	"resource\000"
$LASF69:
	.ascii	"NETIF_F_GSO_BIT\000"
$LASF416:
	.ascii	"GNU C 4.8.3 -fpreprocessed -G 0 -mno-check-zero-division"
	.ascii	" -mabi=32 -mno-abicalls -mno-branch-likely -msoft-float "
	.ascii	"-march=mips32r2 -mno-long-calls -mllsc -mplt -mno-shared"
	.ascii	" -g -O2 -fno-strict-aliasing -fno-common -fno-delete-nul"
	.ascii	"l-pointer-checks -fno-reorder-blocks -fno-tree-ch -fno-c"
	.ascii	"aller-saves -fno-pic -ffreestanding -fno-stack-protector"
	.ascii	" -fomit-frame-pointer -femit-struct-debug-baseonly -fno-"
	.ascii	"var-tracking -fno-strict-overflow -fconserve-stack\000"
$LASF186:
	.ascii	"neigh_table\000"
$LASF403:
	.ascii	"sysctl_tcp_fin_timeout\000"
$LASF249:
	.ascii	"clear_bit\000"
$LASF96:
	.ascii	"NETIF_F_HW_VLAN_STAG_FILTER_BIT\000"
$LASF339:
	.ascii	"memcpy_tokerneliovec\000"
$LASF358:
	.ascii	"cpu_bit_bitmap\000"
$LASF367:
	.ascii	"mips_io_port_base\000"
$LASF151:
	.ascii	"IFLA_OPERSTATE\000"
$LASF197:
	.ascii	"TCPF_LAST_ACK\000"
$LASF289:
	.ascii	"do_error\000"
$LASF244:
	.ascii	"lowmem_page_address\000"
$LASF353:
	.ascii	"__UNIQUE_ID_license1\000"
$LASF11:
	.ascii	"true\000"
$LASF203:
	.ascii	"NET_TX_SOFTIRQ\000"
$LASF40:
	.ascii	"SB_FREEZE_FS\000"
$LASF261:
	.ascii	"dirtied\000"
$LASF34:
	.ascii	"address_space_operations\000"
$LASF158:
	.ascii	"IFLA_STATS64\000"
$LASF61:
	.ascii	"NETIF_F_HW_CSUM_BIT\000"
$LASF310:
	.ascii	"count\000"
$LASF422:
	.ascii	"rtl_sendfile_init\000"
$LASF291:
	.ascii	"wait_for_sndbuf\000"
$LASF392:
	.ascii	"nf_nat_decode_session_hook\000"
$LASF352:
	.ascii	"_rtl_sendfile_hook\000"
$LASF213:
	.ascii	"ND_OPT_SOURCE_LL_ADDR\000"
$LASF211:
	.ascii	"NR_SOFTIRQS\000"
$LASF200:
	.ascii	"tcp_sock\000"
$LASF228:
	.ascii	"rv_count\000"
$LASF81:
	.ascii	"NETIF_F_GSO_GRE_BIT\000"
$LASF264:
	.ascii	"might_fault\000"
$LASF201:
	.ascii	"HI_SOFTIRQ\000"
$LASF225:
	.ascii	"module\000"
$LASF376:
	.ascii	"totalram_pages\000"
$LASF421:
	.ascii	"next_skb\000"
$LASF417:
	.ascii	"/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_"
	.ascii	"v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_"
	.ascii	"20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/l"
	.ascii	"inux-rtkmipsel_rtl8197f/rtl_sendfile-0.1/reverse_sendfil"
	.ascii	"e.c\000"
$LASF182:
	.ascii	"RTAX_FEATURES\000"
$LASF49:
	.ascii	"pipe_inode_info\000"
$LASF325:
	.ascii	"__cu_from_r\000"
$LASF187:
	.ascii	"sock\000"
$LASF379:
	.ascii	"zero_pfn\000"
$LASF328:
	.ascii	"pageP\000"
$LASF138:
	.ascii	"IFLA_IFNAME\000"
$LASF323:
	.ascii	"__ok\000"
$LASF305:
	.ascii	"rtl_pipe_to_sendpages\000"
$LASF319:
	.ascii	"__cu_len\000"
$LASF22:
	.ascii	"ssize_t\000"
$LASF36:
	.ascii	"file\000"
$LASF297:
	.ascii	"rtl_splice_from_pipe_feed\000"
$LASF194:
	.ascii	"TCPF_TIME_WAIT\000"
$LASF5:
	.ascii	"__u32\000"
$LASF349:
	.ascii	"workqueue_struct\000"
$LASF110:
	.ascii	"TCP_CONNTRACK_NONE\000"
$LASF126:
	.ascii	"udp_conntrack\000"
$LASF0:
	.ascii	"signed char\000"
$LASF314:
	.ascii	"rv_cb\000"
$LASF185:
	.ascii	"__RTAX_MAX\000"
$LASF271:
	.ascii	"fput_needed\000"
$LASF116:
	.ascii	"TCP_CONNTRACK_LAST_ACK\000"
$LASF154:
	.ascii	"IFLA_NET_NS_PID\000"
$LASF37:
	.ascii	"SB_UNFROZEN\000"
$LASF140:
	.ascii	"IFLA_LINK\000"
$LASF400:
	.ascii	"ip_tos2prio\000"
$LASF44:
	.ascii	"task_struct\000"
$LASF322:
	.ascii	"__mask\000"
$LASF281:
	.ascii	"goal\000"
$LASF26:
	.ascii	"list_head\000"
$LASF141:
	.ascii	"IFLA_QDISC\000"
$LASF7:
	.ascii	"long long int\000"
$LASF222:
	.ascii	"__ND_OPT_MAX\000"
$LASF91:
	.ascii	"NETIF_F_LOOPBACK_BIT\000"
$LASF175:
	.ascii	"RTAX_RTTVAR\000"
$LASF101:
	.ascii	"NFPROTO_UNSPEC\000"
$LASF113:
	.ascii	"TCP_CONNTRACK_ESTABLISHED\000"
$LASF31:
	.ascii	"inode\000"
$LASF155:
	.ascii	"IFLA_IFALIAS\000"
$LASF220:
	.ascii	"ND_OPT_RDNSS\000"
$LASF33:
	.ascii	"page\000"
$LASF316:
	.ascii	"done\000"
$LASF286:
	.ascii	"inet\000"
$LASF38:
	.ascii	"SB_FREEZE_WRITE\000"
$LASF18:
	.ascii	"bool\000"
$LASF208:
	.ascii	"SCHED_SOFTIRQ\000"
$LASF340:
	.ascii	"kdata\000"
$LASF59:
	.ascii	"NETIF_F_IP_CSUM_BIT\000"
$LASF312:
	.ascii	"cPagePtr\000"
$LASF236:
	.ascii	"var1\000"
$LASF237:
	.ascii	"var2\000"
$LASF188:
	.ascii	"inet_sock\000"
$LASF199:
	.ascii	"TCPF_CLOSING\000"
$LASF306:
	.ascii	"mapping\000"
$LASF143:
	.ascii	"IFLA_COST\000"
$LASF117:
	.ascii	"TCP_CONNTRACK_TIME_WAIT\000"
$LASF365:
	.ascii	"shm_align_mask\000"
$LASF207:
	.ascii	"TASKLET_SOFTIRQ\000"
$LASF258:
	.ascii	"size\000"
$LASF371:
	.ascii	"system_wq\000"
$LASF114:
	.ascii	"TCP_CONNTRACK_FIN_WAIT\000"
$LASF124:
	.ascii	"TCP_CONNTRACK_TIMEOUT_MAX\000"
$LASF112:
	.ascii	"TCP_CONNTRACK_SYN_RECV\000"
$LASF402:
	.ascii	"sysctl_local_reserved_ports\000"
$LASF189:
	.ascii	"TCPF_ESTABLISHED\000"
$LASF98:
	.ascii	"skb_frag_t\000"
$LASF344:
	.ascii	"fraglen\000"
$LASF196:
	.ascii	"TCPF_CLOSE_WAIT\000"
$LASF205:
	.ascii	"BLOCK_SOFTIRQ\000"
$LASF360:
	.ascii	"overflowuid\000"
$LASF75:
	.ascii	"NETIF_F_TSO_BIT\000"
$LASF118:
	.ascii	"TCP_CONNTRACK_CLOSE\000"
$LASF233:
	.ascii	"recvfile\000"
$LASF369:
	.ascii	"page_group_by_mobility_disabled\000"
$LASF254:
	.ascii	"lock_sock\000"
$LASF161:
	.ascii	"IFLA_AF_SPEC\000"
$LASF125:
	.ascii	"tcp_conntrack\000"
$LASF181:
	.ascii	"RTAX_INITCWND\000"
$LASF74:
	.ascii	"NETIF_F_GSO_SHIFT\000"
$LASF343:
	.ascii	"rtl_skb_copy_datagram_to_kernel_iovec\000"
$LASF347:
	.ascii	"user_namespace\000"
$LASF269:
	.ascii	"__res\000"
$LASF342:
	.ascii	"__ret\000"
$LASF99:
	.ascii	"skb_frag_struct\000"
$LASF243:
	.ascii	"kunmap\000"
$LASF64:
	.ascii	"NETIF_F_FRAGLIST_BIT\000"
$LASF386:
	.ascii	"kmalloc_caches\000"
$LASF279:
	.ascii	"mss_now\000"
$LASF82:
	.ascii	"NETIF_F_GSO_UDP_TUNNEL_BIT\000"
$LASF373:
	.ascii	"contig_page_data\000"
$LASF165:
	.ascii	"IFLA_PROMISCUITY\000"
$LASF414:
	.ascii	"ratelimit_pages\000"
$LASF58:
	.ascii	"NETIF_F_SG_BIT\000"
$LASF173:
	.ascii	"RTAX_WINDOW\000"
$LASF156:
	.ascii	"IFLA_NUM_VF\000"
$LASF227:
	.ascii	"rv_pos\000"
$LASF56:
	.ascii	"socket\000"
$LASF39:
	.ascii	"SB_FREEZE_PAGEFAULT\000"
$LASF191:
	.ascii	"TCPF_SYN_RECV\000"
$LASF92:
	.ascii	"NETIF_F_RXFCS_BIT\000"
$LASF399:
	.ascii	"nd_tbl\000"
$LASF377:
	.ascii	"invalid_pte_table\000"
$LASF109:
	.ascii	"flowi\000"
$LASF48:
	.ascii	"pipe_buffer\000"
$LASF169:
	.ascii	"__IFLA_MAX\000"
$LASF24:
	.ascii	"phys_addr_t\000"
$LASF32:
	.ascii	"dqstats\000"
$LASF28:
	.ascii	"sizetype\000"
$LASF128:
	.ascii	"UDP_CT_REPLIED\000"
$LASF268:
	.ascii	"__ct\000"
$LASF274:
	.ascii	"actor\000"
$LASF315:
	.ascii	"rcvtimeo\000"
$LASF307:
	.ascii	"nr_pages_dirtied\000"
$LASF2:
	.ascii	"short int\000"
$LASF295:
	.ascii	"__min1\000"
$LASF296:
	.ascii	"__min2\000"
$LASF317:
	.ascii	"__cu_to\000"
$LASF241:
	.ascii	"preempt_offset\000"
$LASF252:
	.ascii	"inet_sk\000"
$LASF12:
	.ascii	"long int\000"
$LASF174:
	.ascii	"RTAX_RTT\000"
$LASF327:
	.ascii	"bytes\000"
$LASF170:
	.ascii	"RTAX_UNSPEC\000"
$LASF147:
	.ascii	"IFLA_PROTINFO\000"
$LASF390:
	.ascii	"total_swap_pages\000"
$LASF93:
	.ascii	"NETIF_F_RXALL_BIT\000"
$LASF166:
	.ascii	"IFLA_NUM_TX_QUEUES\000"
$LASF394:
	.ascii	"memalloc_socks\000"
$LASF172:
	.ascii	"RTAX_MTU\000"
$LASF45:
	.ascii	"kmem_cache\000"
$LASF251:
	.ascii	"temp\000"
$LASF231:
	.ascii	"g2_tcp_sysctl\000"
$LASF23:
	.ascii	"fmode_t\000"
$LASF66:
	.ascii	"NETIF_F_HW_VLAN_CTAG_RX_BIT\000"
$LASF391:
	.ascii	"nf_hooks\000"
$LASF72:
	.ascii	"NETIF_F_GRO_BIT\000"
$LASF153:
	.ascii	"IFLA_LINKINFO\000"
$LASF102:
	.ascii	"NFPROTO_IPV4\000"
$LASF13:
	.ascii	"__kernel_size_t\000"
$LASF105:
	.ascii	"NFPROTO_IPV6\000"
$LASF368:
	.ascii	"max_mapnr\000"
$LASF135:
	.ascii	"IFLA_UNSPEC\000"
$LASF301:
	.ascii	"inet_sendpages\000"
$LASF374:
	.ascii	"cad_pid\000"
$LASF357:
	.ascii	"hex_asc\000"
$LASF284:
	.ascii	"copied\000"
$LASF396:
	.ascii	"ipv6_hash_secret\000"
$LASF133:
	.ascii	"XFRM_POLICY_MASK\000"
$LASF336:
	.ascii	"fput_needed_out\000"
$LASF97:
	.ascii	"NETDEV_FEATURE_COUNT\000"
$LASF73:
	.ascii	"NETIF_F_LRO_BIT\000"
$LASF239:
	.ascii	"iscsi_rx_acc\000"
$LASF346:
	.ascii	"start\000"
$LASF230:
	.ascii	"RECV_FILE_CONTROL_BLOCK\000"
$LASF298:
	.ascii	"tcp_sendpages\000"
$LASF375:
	.ascii	"debug_locks\000"
$LASF46:
	.ascii	"static_key\000"
$LASF80:
	.ascii	"NETIF_F_FSO_BIT\000"
$LASF55:
	.ascii	"msghdr\000"
$LASF71:
	.ascii	"NETIF_F_NETNS_LOCAL_BIT\000"
$LASF331:
	.ascii	"fd_in\000"
$LASF25:
	.ascii	"atomic_t\000"
$LASF247:
	.ascii	"sock_update_classid\000"
$LASF9:
	.ascii	"long unsigned int\000"
$LASF4:
	.ascii	"__u8\000"
$LASF364:
	.ascii	"jiffies\000"
$LASF280:
	.ascii	"size_goal\000"
$LASF381:
	.ascii	"__init_begin\000"
$LASF108:
	.ascii	"nf_afinfo\000"
$LASF418:
	.ascii	"/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_"
	.ascii	"v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_"
	.ascii	"20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/l"
	.ascii	"inux-rtkmipsel_rtl8197f/linux-3.10.49\000"
$LASF84:
	.ascii	"NETIF_F_FCOE_CRC_BIT\000"
$LASF190:
	.ascii	"TCPF_SYN_SENT\000"
$LASF355:
	.ascii	"cpu_data\000"
$LASF410:
	.ascii	"sysctl_tcp_thin_dupack\000"
$LASF134:
	.ascii	"XFRM_POLICY_MAX\000"
$LASF404:
	.ascii	"sysctl_tcp_keepalive_time\000"
$LASF335:
	.ascii	"out_file\000"
$LASF163:
	.ascii	"IFLA_NET_NS_FD\000"
$LASF54:
	.ascii	"kvec\000"
$LASF20:
	.ascii	"loff_t\000"
$LASF1:
	.ascii	"unsigned char\000"
$LASF95:
	.ascii	"NETIF_F_HW_VLAN_STAG_RX_BIT\000"
$LASF136:
	.ascii	"IFLA_ADDRESS\000"
$LASF395:
	.ascii	"inet_ehash_secret\000"
$LASF423:
	.ascii	"rtl_sendfile_cleanup\000"
$LASF240:
	.ascii	"line\000"
$LASF294:
	.ascii	"can_coalesce\000"
$LASF192:
	.ascii	"TCPF_FIN_WAIT1\000"
$LASF193:
	.ascii	"TCPF_FIN_WAIT2\000"
$LASF10:
	.ascii	"false\000"
$LASF183:
	.ascii	"RTAX_RTO_MIN\000"
$LASF177:
	.ascii	"RTAX_CWND\000"
$LASF350:
	.ascii	"frag_percpu_counter_batch\000"
$LASF382:
	.ascii	"__init_end\000"
$LASF363:
	.ascii	"init_pid_ns\000"
$LASF413:
	.ascii	"jffs2_file_address_operations\000"
$LASF250:
	.ascii	"addr\000"
$LASF383:
	.ascii	"__flush_cache_vmap\000"
$LASF123:
	.ascii	"TCP_CONNTRACK_UNACK\000"
$LASF263:
	.ascii	"__current_thread_info\000"
$LASF17:
	.ascii	"__be32\000"
$LASF148:
	.ascii	"IFLA_TXQLEN\000"
$LASF168:
	.ascii	"IFLA_CARRIER\000"
$LASF127:
	.ascii	"UDP_CT_UNREPLIED\000"
$LASF415:
	.ascii	"g2_tcp_ctl\000"
$LASF79:
	.ascii	"NETIF_F_TSO6_BIT\000"
$LASF122:
	.ascii	"TCP_CONNTRACK_RETRANS\000"
$LASF265:
	.ascii	"kmap\000"
$LASF217:
	.ascii	"ND_OPT_MTU\000"
$LASF63:
	.ascii	"NETIF_F_HIGHDMA_BIT\000"
$LASF330:
	.ascii	"rtl_splice\000"
$LASF412:
	.ascii	"rtl_sendfile_hook\000"
$LASF388:
	.ascii	"vm_swappiness\000"
$LASF131:
	.ascii	"XFRM_POLICY_OUT\000"
$LASF150:
	.ascii	"IFLA_WEIGHT\000"
$LASF3:
	.ascii	"short unsigned int\000"
$LASF366:
	.ascii	"flush_data_cache_page\000"
$LASF405:
	.ascii	"sysctl_tcp_keepalive_probes\000"
$LASF238:
	.ascii	"iscsi_tx_acc\000"
$LASF53:
	.ascii	"iovec\000"
$LASF204:
	.ascii	"NET_RX_SOFTIRQ\000"
$LASF83:
	.ascii	"NETIF_F_GSO_LAST\000"
$LASF287:
	.ascii	"__func__\000"
$LASF142:
	.ascii	"IFLA_STATS\000"
$LASF419:
	.ascii	"rtl_tcp_ctl_init\000"
$LASF282:
	.ascii	"push_flag\000"
$LASF262:
	.ascii	"current_thread_info\000"
$LASF224:
	.ascii	"double\000"
$LASF65:
	.ascii	"NETIF_F_HW_VLAN_CTAG_TX_BIT\000"
$LASF299:
	.ascii	"per_tx_size\000"
$LASF232:
	.ascii	"sendfile\000"
$LASF144:
	.ascii	"IFLA_PRIORITY\000"
$LASF57:
	.ascii	"netdev_features_t\000"
$LASF60:
	.ascii	"__UNUSED_NETIF_F_1\000"
$LASF285:
	.ascii	"timeo\000"
$LASF308:
	.ascii	"ratelimit\000"
$LASF77:
	.ascii	"NETIF_F_GSO_ROBUST_BIT\000"
$LASF30:
	.ascii	"atomic_long_t\000"
$LASF209:
	.ascii	"HRTIMER_SOFTIRQ\000"
$LASF321:
	.ascii	"__size\000"
$LASF273:
	.ascii	"condition\000"
$LASF300:
	.ascii	"per_offset\000"
$LASF324:
	.ascii	"__cu_to_r\000"
$LASF100:
	.ascii	"sk_buff\000"
$LASF253:
	.ascii	"set_bit\000"
$LASF411:
	.ascii	"sysctl_tcp_early_retrans\000"
$LASF302:
	.ascii	"sock_sendpages\000"
$LASF78:
	.ascii	"NETIF_F_TSO_ECN_BIT\000"
$LASF266:
	.ascii	"strcmp\000"
$LASF129:
	.ascii	"UDP_CT_MAX\000"
$LASF176:
	.ascii	"RTAX_SSTHRESH\000"
	.ident	"GCC: (OpenWrt/Linaro GCC 4.8-2014.04 r39885) 4.8.3"
