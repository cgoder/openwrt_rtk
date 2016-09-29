	.file	1 "reverse_sendfile.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
	.align	2
	.globl	rtl_tcp_ctl_init
	.set	nomips16
	.ent	rtl_tcp_ctl_init
	.type	rtl_tcp_ctl_init, @function
rtl_tcp_ctl_init:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$4,%hi(g2_tcp_ctl)
	li	$3,1			# 0x1
	addiu	$2,$4,%lo(g2_tcp_ctl)
	sw	$3,%lo(g2_tcp_ctl)($4)
	li	$4,16			# 0x10
	sw	$4,8($2)
	li	$4,8192			# 0x2000
	sw	$4,12($2)
	li	$4,4096			# 0x1000
	sw	$4,16($2)
	li	$4,2			# 0x2
	sw	$3,4($2)
	sw	$4,20($2)
	sw	$3,24($2)
	j	$31
	sw	$0,28($2)

	.set	macro
	.set	reorder
	.end	rtl_tcp_ctl_init
	.size	rtl_tcp_ctl_init, .-rtl_tcp_ctl_init
	.align	2
	.globl	rtl_splice_from_pipe_feed
	.set	nomips16
	.ent	rtl_splice_from_pipe_feed
	.type	rtl_splice_from_pipe_feed, @function
rtl_splice_from_pipe_feed:
	.frame	$sp,48,$31		# vars= 0, regs= 8/0, args= 16, gp= 0
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$22,40($sp)
	sw	$21,36($sp)
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(rtl_pipe_to_sendpages)
	addiu	$2,$2,%lo(rtl_pipe_to_sendpages)
	move	$20,$6
	move	$19,$4
	bne	$6,$2,$L3
	move	$16,$5

	lw	$3,4($5)
	lw	$2,68($4)
	lw	$5,24($4)
	beq	$3,$0,$L15
	sll	$3,$5,3

	sll	$17,$5,5
	subu	$17,$17,$3
	move	$6,$16
	addu	$17,$2,$17
	jalr	$20
	move	$5,$17

	bgtz	$2,$L19
	move	$18,$2

	j	$L25
	li	$2,-61			# 0xffffffffffffffc3

$L8:
	lw	$3,12($17)
	subu	$18,$18,$2
	sw	$0,12($17)
	lw	$2,16($3)
	jalr	$2
	nop

	lw	$3,24($19)
	lw	$2,28($19)
	lw	$4,20($19)
	addiu	$3,$3,1
	addiu	$2,$2,-1
	and	$2,$2,$3
	addiu	$4,$4,-1
	sll	$3,$2,3
	sw	$2,24($19)
	sll	$2,$2,5
	sw	$4,20($19)
	beq	$18,$0,$L7
	subu	$2,$2,$3

	lw	$17,68($19)
	addu	$17,$17,$2
$L19:
	lw	$2,8($17)
	move	$5,$17
	sltu	$3,$18,$2
	beq	$3,$0,$L8
	move	$4,$19

	beq	$18,$0,$L7
	subu	$2,$2,$18

	lw	$3,4($17)
	sw	$2,8($17)
	addu	$18,$3,$18
	sw	$18,4($17)
$L7:
	lw	$2,40($19)
	beq	$2,$0,$L9
	li	$2,1			# 0x1

	sb	$2,32($16)
$L9:
	lw	$18,4($16)
	j	$L4
	sltu	$18,$0,$18

$L14:
	lw	$2,24($19)
	lw	$17,68($19)
	sll	$5,$2,3
	lw	$3,4($16)
	sll	$2,$2,5
	subu	$2,$2,$5
	addu	$17,$17,$2
	lw	$2,8($17)
	move	$5,$17
	lw	$21,12($17)
	sltu	$7,$3,$2
	beq	$7,$0,$L10
	sw	$2,0($16)

	sw	$3,0($16)
$L10:
	jalr	$20
	nop

	move	$18,$2
	bgtz	$2,$L11
	sra	$4,$2,31

	li	$2,-61			# 0xffffffffffffffc3
$L25:
	xor	$2,$18,$2
	j	$L4
	movz	$18,$0,$2

$L11:
	lw	$2,4($17)
	lw	$3,8($17)
	addu	$2,$2,$18
	subu	$3,$3,$18
	sw	$3,8($17)
	sw	$2,4($17)
	lw	$3,20($16)
	lw	$8,16($16)
	addu	$2,$3,$18
	lw	$6,28($16)
	sltu	$3,$2,$3
	lw	$5,0($16)
	addu	$4,$8,$4
	lw	$7,4($16)
	addu	$6,$6,$18
	subu	$5,$5,$18
	addu	$4,$3,$4
	subu	$18,$7,$18
	sw	$18,4($16)
	sw	$6,28($16)
	sw	$5,0($16)
	sw	$4,16($16)
	sw	$2,20($16)
	lw	$2,8($17)
	bne	$2,$0,$L12
	move	$4,$19

	sw	$0,12($17)
	lw	$2,16($21)
	jalr	$2
	move	$5,$17

	lw	$5,24($19)
	lw	$4,28($19)
	lw	$3,20($19)
	addiu	$5,$5,1
	addiu	$4,$4,-1
	and	$4,$4,$5
	addiu	$3,$3,-1
	lw	$2,40($19)
	sw	$4,24($19)
	sw	$3,20($19)
	lw	$18,4($16)
	beq	$2,$0,$L12
	nop

	sb	$22,32($16)
$L12:
	bne	$18,$0,$L20
	move	$18,$0

	j	$L26
	move	$2,$18

$L3:
	li	$22,1			# 0x1
$L20:
	lw	$2,20($19)
	move	$4,$19
	bne	$2,$0,$L14
	move	$6,$16

$L15:
	li	$18,1			# 0x1
$L4:
	move	$2,$18
$L26:
	lw	$31,44($sp)
	lw	$22,40($sp)
	lw	$21,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
	.end	rtl_splice_from_pipe_feed
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
	.set	nomips16
	.ent	tcp_sendpages
	.type	tcp_sendpages, @function
tcp_sendpages:
	.frame	$sp,152,$31		# vars= 88, regs= 10/0, args= 24, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-152
	sw	$31,148($sp)
	sw	$fp,144($sp)
	sw	$23,140($sp)
	sw	$22,136($sp)
	sw	$21,132($sp)
	sw	$20,128($sp)
	sw	$19,124($sp)
	sw	$18,120($sp)
	sw	$17,116($sp)
	sw	$16,112($sp)
	lui	$2,%hi(memset)
	sw	$5,156($sp)
	move	$22,$4
	move	$5,$0
	addiu	$4,$sp,32
	move	$21,$6
	addiu	$2,$2,%lo(memset)
	li	$6,64			# 0x40
	jalr	$2
	move	$20,$7

	lui	$16,%hi(rtl_get_sk_route_caps)
	lw	$3,156($sp)
	move	$4,$22
	addiu	$16,$16,%lo(rtl_get_sk_route_caps)
	lw	$2,24($3)
	lw	$3,68($3)
	sll	$5,$2,3
	sll	$2,$2,5
	subu	$2,$2,$5
	addu	$3,$3,$2
	jalr	$16
	sw	$3,100($sp)

	andi	$3,$3,0x1
	beq	$3,$0,$L28
	nop

	jalr	$16
	move	$4,$22

	andi	$3,$3,0x1a
	beq	$3,$0,$L28
	addiu	$2,$sp,32

	lw	$4,156($sp)
	lw	$3,100($sp)
	lw	$5,20($4)
	sll	$5,$5,2
	j	$L31
	addu	$5,$2,$5

$L28:
	lw	$18,100($sp)
	move	$17,$0
	li	$23,4096			# 0x1000
	lui	$fp,%hi(rtl_get_sk_socket)
$L78:
	addu	$19,$17,$21
	subu	$2,$20,$17
	andi	$19,$19,0xfff
	lw	$3,0($18)
	subu	$19,$23,$19
	addiu	$6,$fp,%lo(rtl_get_sk_socket)
	sltu	$5,$2,$19
	move	$4,$22
	beq	$3,$0,$L33
	movn	$19,$2,$5

	bne	$17,$20,$L34
	nop

$L33:
	j	$L35
	move	$16,$17

$L34:
	jalr	$6
	nop

	lui	$3,%hi(sock_no_sendpage)
	move	$4,$2
	addiu	$2,$3,%lo(sock_no_sendpage)
	lw	$3,168($sp)
	move	$6,$21
	lw	$5,0($18)
	move	$7,$19
	jalr	$2
	sw	$3,16($sp)

	bgez	$2,$L36
	move	$16,$2

	j	$L35
	movn	$16,$17,$17

$L36:
	bne	$19,$2,$L78
	addu	$17,$17,$2

	lw	$4,156($sp)
	addiu	$3,$18,24
	lw	$2,20($4)
	sll	$4,$2,3
	sll	$2,$2,5
	subu	$2,$2,$4
	lw	$4,100($sp)
	addu	$2,$4,$2
	sltu	$2,$18,$2
	j	$L78
	movn	$18,$3,$2

$L38:
	lw	$4,0($3)
	addiu	$3,$3,24
	sw	$4,0($2)
	addiu	$2,$2,4
$L31:
	bne	$2,$5,$L38
	move	$4,$22

	lui	$2,%hi(lock_sock_nested)
	addiu	$2,$2,%lo(lock_sock_nested)
	jalr	$2
	move	$5,$0

	lui	$2,%hi(rtl_sk_sndtimeo)
	lw	$5,168($sp)
	addiu	$2,$2,%lo(rtl_sk_sndtimeo)
	jalr	$2
	move	$4,$22

	lbu	$3,18($22)
	sw	$2,24($sp)
	li	$2,-259			# 0xfffffffffffffefd
	sra	$3,$2,$3
	andi	$3,$3,0x1
	beq	$3,$0,$L83
	lui	$3,%hi(rtl_get_sk_socket)

	lui	$2,%hi(sk_stream_wait_connect)
	move	$4,$22
	addiu	$2,$2,%lo(sk_stream_wait_connect)
	jalr	$2
	addiu	$5,$sp,24

	bne	$2,$0,$L40
	move	$17,$2

	lui	$3,%hi(rtl_get_sk_socket)
$L83:
	addiu	$3,$3,%lo(rtl_get_sk_socket)
	jalr	$3
	move	$4,$22

	addiu	$5,$2,8
	lui	$2,%hi(__mips_clear_bit)
	addiu	$2,$2,%lo(__mips_clear_bit)
	jalr	$2
	move	$4,$0

	lui	$3,%hi(tcp_send_mss)
	lw	$6,168($sp)
	move	$4,$22
	addiu	$3,$3,%lo(tcp_send_mss)
	jalr	$3
	addiu	$5,$sp,28

	lui	$4,%hi(g2_tcp_ctl)
	addiu	$4,$4,%lo(g2_tcp_ctl)
	sw	$2,104($sp)
	lw	$2,8($4)
	sltu	$3,$2,2
	bne	$3,$0,$L42
	sll	$2,$2,12

	addiu	$2,$2,-4096
$L42:
	lw	$3,28($sp)
	slt	$3,$2,$3
	beq	$3,$0,$L43
	nop

	sw	$2,28($sp)
$L43:
	lui	$2,%hi(rtl_get_sk_err)
	addiu	$2,$2,%lo(rtl_get_sk_err)
	jalr	$2
	move	$4,$22

	bne	$2,$0,$L44
	lui	$2,%hi(rtl_get_sk_shutdown)

	addiu	$2,$2,%lo(rtl_get_sk_shutdown)
	jalr	$2
	move	$4,$22

	andi	$2,$2,0x2
	beq	$2,$0,$L45
	lui	$2,%hi(g2_tcp_ctl)

$L44:
	lui	$4,%hi($LC0)
	lui	$5,%hi(__func__.40504)
	lui	$2,%hi(printk)
	addiu	$4,$4,%lo($LC0)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	addiu	$5,$5,%lo(__func__.40504)

	j	$L40
	li	$17,-32			# 0xffffffffffffffe0

$L45:
	addiu	$2,$2,%lo(g2_tcp_ctl)
	lw	$3,4($2)
	li	$2,3			# 0x3
	bne	$3,$2,$L80
	li	$2,2			# 0x2

	lui	$16,%hi(rtl_get_tp_snd_wnd)
	lw	$17,28($sp)
	addiu	$16,$16,%lo(rtl_get_tp_snd_wnd)
	jalr	$16
	move	$4,$22

	sltu	$2,$17,$2
	beq	$2,$0,$L47
	lui	$4,%hi(g2_tcp_ctl)

	addiu	$4,$4,%lo(g2_tcp_ctl)
	lw	$3,4($4)
	j	$L80
	li	$2,2			# 0x2

$L47:
	jalr	$16
	move	$4,$22

	lui	$4,%hi(g2_tcp_ctl)
	addiu	$4,$4,%lo(g2_tcp_ctl)
	lw	$3,4($4)
	sw	$2,28($sp)
	li	$2,2			# 0x2
$L80:
	bne	$3,$2,$L48
	lui	$4,%hi($LC1)

	lw	$2,28($sp)
	lw	$7,104($sp)
	addiu	$4,$4,%lo($LC1)
	sw	$2,16($sp)
	lui	$2,%hi(printk)
	move	$5,$20
	addiu	$2,$2,%lo(printk)
	jalr	$2
	move	$6,$21

$L48:
	move	$16,$0
	sw	$0,100($sp)
	j	$L79
	sw	$0,108($sp)

$L70:
	addiu	$2,$3,%lo(rtl_tcp_write_queue_tail)
	jalr	$2
	move	$4,$22

	lui	$4,%hi(rtl_get_tcp_send_head)
	srl	$3,$21,12
	move	$17,$2
	addiu	$2,$4,%lo(rtl_get_tcp_send_head)
	sll	$3,$3,2
	addiu	$4,$sp,24
	addu	$3,$4,$3
	move	$4,$22
	lw	$3,8($3)
	jalr	$2
	sw	$3,96($sp)

	beq	$2,$0,$L50
	lui	$2,%hi(rtl_get_skb_len_common)

	lw	$18,28($sp)
	addiu	$2,$2,%lo(rtl_get_skb_len_common)
	jalr	$2
	move	$4,$17

	subu	$2,$18,$2
	bgtz	$2,$L84
	lui	$3,%hi(rtl_skb_shared_info)

$L50:
	lui	$2,%hi(rtl_sk_stream_memory_free)
$L81:
	addiu	$2,$2,%lo(rtl_sk_stream_memory_free)
	jalr	$2
	move	$4,$22

	beq	$2,$0,$L52
	move	$4,$22

	lui	$2,%hi(rtl_get_sk_allocation)
	addiu	$2,$2,%lo(rtl_get_sk_allocation)
	jalr	$2
	nop

	move	$4,$22
	move	$6,$2
	lui	$2,%hi(sk_stream_alloc_skb)
	addiu	$2,$2,%lo(sk_stream_alloc_skb)
	jalr	$2
	move	$5,$0

	bne	$2,$0,$L53
	move	$17,$2

	lui	$4,%hi($LC2)
	lui	$5,%hi(__func__.40504)
	lui	$2,%hi(printk)
	addiu	$4,$4,%lo($LC2)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	addiu	$5,$5,%lo(__func__.40504)

	j	$L54
	nop

$L53:
	move	$5,$2
	lui	$2,%hi(rtl_skb_entail)
	addiu	$2,$2,%lo(rtl_skb_entail)
	jalr	$2
	move	$4,$22

	li	$2,1			# 0x1
	sw	$2,108($sp)
	lui	$3,%hi(rtl_skb_shared_info)
$L84:
	move	$4,$17
	addiu	$3,$3,%lo(rtl_skb_shared_info)
	jalr	$3
	andi	$fp,$21,0xfff

	move	$4,$17
	lbu	$23,0($2)
	lui	$2,%hi(rtl_skb_can_coalesce)
	lw	$6,96($sp)
	move	$7,$fp
	addiu	$2,$2,%lo(rtl_skb_can_coalesce)
	jalr	$2
	move	$5,$23

	bne	$2,$0,$L55
	move	$19,$2

	sltu	$2,$23,17
	bne	$2,$0,$L85
	li	$18,4096			# 0x1000

	lui	$2,%hi(rtl_tcp_mark_push)
	move	$4,$22
	addiu	$2,$2,%lo(rtl_tcp_mark_push)
	jalr	$2
	move	$5,$17

	j	$L81
	lui	$2,%hi(rtl_sk_stream_memory_free)

$L55:
	li	$18,4096			# 0x1000
$L85:
	move	$4,$22
	subu	$18,$18,$fp
	sltu	$2,$20,$18
	movn	$18,$20,$2
	lui	$2,%hi(rtl_sk_wmem_schedule)
	addiu	$2,$2,%lo(rtl_sk_wmem_schedule)
	jalr	$2
	move	$5,$18

	beq	$2,$0,$L54
	nop

	beq	$19,$0,$L56
	lui	$2,%hi(rtl_get_page)

	lui	$3,%hi(rtl_skb_shared_info)
	move	$4,$17
	addiu	$3,$3,%lo(rtl_skb_shared_info)
	jalr	$3
	addiu	$23,$23,4

	sll	$23,$23,3
	addu	$2,$2,$23
	lhu	$3,10($2)
	addu	$3,$18,$3
	j	$L57
	sh	$3,10($2)

$L56:
	lw	$4,96($sp)
	addiu	$2,$2,%lo(rtl_get_page)
	jalr	$2
	nop

	lui	$2,%hi(rtl_skb_fill_page_desc)
	lw	$6,96($sp)
	move	$4,$17
	move	$5,$23
	sw	$18,16($sp)
	addiu	$2,$2,%lo(rtl_skb_fill_page_desc)
	jalr	$2
	move	$7,$fp

$L57:
	lui	$2,%hi(rtl_add_skb_len_common)
	move	$4,$17
	addiu	$2,$2,%lo(rtl_add_skb_len_common)
	jalr	$2
	move	$5,$18

	lui	$2,%hi(rtl_add_skb_data_len_common)
	move	$4,$17
	addiu	$2,$2,%lo(rtl_add_skb_data_len_common)
	move	$5,$18
	jalr	$2
	lui	$19,%hi(rtl_TCP_SKB_CB)

	lui	$2,%hi(rtl_add_skb_truesize_common)
	move	$4,$17
	addiu	$2,$2,%lo(rtl_add_skb_truesize_common)
	move	$5,$18
	jalr	$2
	addiu	$19,$19,%lo(rtl_TCP_SKB_CB)

	lui	$2,%hi(rtl_add_skb_sk_wmem_queued)
	move	$5,$18
	addiu	$2,$2,%lo(rtl_add_skb_sk_wmem_queued)
	jalr	$2
	move	$4,$22

	lw	$2,96($22)
	subu	$2,$2,$18
	sw	$2,96($22)
	lui	$2,%hi(rtl_set_tcp_skb_ip_summed)
	addiu	$2,$2,%lo(rtl_set_tcp_skb_ip_summed)
	jalr	$2
	move	$4,$17

	lui	$2,%hi(rtl_add_tp_write_seq)
	move	$5,$18
	addiu	$2,$2,%lo(rtl_add_tp_write_seq)
	jalr	$2
	move	$4,$22

	jalr	$19
	move	$4,$17

	move	$4,$2
	lui	$2,%hi(rtl_add_skb_cb_end_seq)
	addiu	$2,$2,%lo(rtl_add_skb_cb_end_seq)
	jalr	$2
	move	$5,$18

	lui	$3,%hi(rtl_skb_shared_info)
	addiu	$3,$3,%lo(rtl_skb_shared_info)
	jalr	$3
	move	$4,$17

	bne	$16,$0,$L58
	sh	$0,4($2)

	jalr	$19
	move	$4,$17

	move	$4,$2
	lui	$2,%hi(rtl_and_skb_cb_tcp_flags)
	addiu	$2,$2,%lo(rtl_and_skb_cb_tcp_flags)
	jalr	$2
	li	$5,-9			# 0xfffffffffffffff7

$L58:
	lw	$4,100($sp)
	subu	$20,$20,$18
	addu	$16,$16,$18
	addu	$21,$21,$18
	addiu	$4,$4,1
	bne	$20,$0,$L59
	sw	$4,100($sp)

	lui	$2,%hi(g2_tcp_ctl)
	addiu	$2,$2,%lo(g2_tcp_ctl)
	lw	$3,4($2)
	li	$2,2			# 0x2
	bne	$3,$2,$L60
	lui	$2,%hi(rtl_get_skb_len_common)

	addiu	$2,$2,%lo(rtl_get_skb_len_common)
	jalr	$2
	move	$4,$17

	lui	$4,%hi($LC3)
	move	$6,$2
	lui	$5,%hi(__func__.40504)
	lw	$7,100($sp)
	lui	$2,%hi(printk)
	addiu	$4,$4,%lo($LC3)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	addiu	$5,$5,%lo(__func__.40504)

	j	$L60
	nop

$L59:
	lui	$2,%hi(rtl_get_skb_len_common)
	addiu	$2,$2,%lo(rtl_get_skb_len_common)
	jalr	$2
	move	$4,$17

	lw	$3,28($sp)
	sltu	$2,$2,$3
	bne	$2,$0,$L79
	nop

	lw	$3,168($sp)
	andi	$2,$3,0x1
	bne	$2,$0,$L79
	nop

	lw	$4,108($sp)
	bne	$4,$0,$L62
	lui	$3,%hi(g2_tcp_ctl)

	addiu	$3,$3,%lo(g2_tcp_ctl)
	lw	$2,8($3)
	lw	$4,100($sp)
	sltu	$2,$4,$2
	bne	$2,$0,$L79
	nop

$L62:
	lui	$2,%hi(forced_push)
	addiu	$2,$2,%lo(forced_push)
	jalr	$2
	move	$4,$22

	beq	$2,$0,$L63
	move	$4,$22

	lui	$2,%hi(rtl_tcp_mark_push)
	addiu	$2,$2,%lo(rtl_tcp_mark_push)
	jalr	$2
	move	$5,$17

	lui	$2,%hi(__tcp_push_pending_frames)
	lw	$5,104($sp)
	move	$4,$22
	addiu	$2,$2,%lo(__tcp_push_pending_frames)
	jalr	$2
	li	$6,4			# 0x4

	sw	$0,100($sp)
	j	$L79
	sw	$0,108($sp)

$L63:
	lui	$2,%hi(rtl_tcp_send_head)
	addiu	$2,$2,%lo(rtl_tcp_send_head)
	jalr	$2
	nop

	bne	$17,$2,$L73
	lui	$2,%hi(tcp_push_one)

	lw	$5,104($sp)
	addiu	$2,$2,%lo(tcp_push_one)
	jalr	$2
	move	$4,$22

	sw	$0,100($sp)
	j	$L79
	sw	$0,108($sp)

$L52:
	lui	$3,%hi(rtl_get_sk_socket)
	addiu	$3,$3,%lo(rtl_get_sk_socket)
	jalr	$3
	nop

	addiu	$5,$2,8
	lui	$2,%hi(__mips_set_bit)
	addiu	$2,$2,%lo(__mips_set_bit)
	jalr	$2
	li	$4,2			# 0x2

$L54:
	beq	$16,$0,$L86
	lui	$2,%hi(sk_stream_wait_memory)

	lw	$2,168($sp)
	li	$5,-65536			# 0xffffffffffff0000
	addiu	$5,$5,32767
	move	$4,$22
	and	$5,$2,$5
	lw	$6,104($sp)
	lui	$2,%hi(rtl_tcp_push)
	addiu	$2,$2,%lo(rtl_tcp_push)
	jalr	$2
	li	$7,4			# 0x4

	lui	$2,%hi(sk_stream_wait_memory)
$L86:
	move	$4,$22
	addiu	$2,$2,%lo(sk_stream_wait_memory)
	jalr	$2
	addiu	$5,$sp,24

	beq	$2,$0,$L65
	move	$17,$2

	lui	$4,%hi(g2_tcp_ctl)
	li	$2,2			# 0x2
	addiu	$4,$4,%lo(g2_tcp_ctl)
	lw	$3,4($4)
	bne	$3,$2,$L66
	lui	$4,%hi($LC4)

	lui	$5,%hi(__func__.40504)
	lui	$2,%hi(printk)
	addiu	$4,$4,%lo($LC4)
	addiu	$5,$5,%lo(__func__.40504)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	move	$6,$17

	j	$L66
	nop

$L65:
	lw	$6,168($sp)
	lui	$3,%hi(tcp_send_mss)
	move	$4,$22
	addiu	$3,$3,%lo(tcp_send_mss)
	jalr	$3
	addiu	$5,$sp,28

	lui	$4,%hi(g2_tcp_ctl)
	addiu	$4,$4,%lo(g2_tcp_ctl)
	sw	$2,104($sp)
	lw	$2,8($4)
	sltu	$3,$2,2
	bne	$3,$0,$L68
	sll	$2,$2,12

	addiu	$2,$2,-4096
$L68:
	lw	$3,28($sp)
	slt	$3,$2,$3
	beq	$3,$0,$L69
	nop

	sw	$2,28($sp)
$L69:
	lui	$2,%hi(_cond_resched)
	addiu	$2,$2,%lo(_cond_resched)
	jalr	$2
	nop

	lui	$2,%hi(g2_tcp_ctl)
	addiu	$2,$2,%lo(g2_tcp_ctl)
	lw	$3,4($2)
	li	$2,2			# 0x2
	bne	$3,$2,$L79
	lui	$4,%hi($LC5)

	lui	$5,%hi(__func__.40504)
	lw	$7,28($sp)
	lui	$2,%hi(printk)
	lw	$6,104($sp)
	addiu	$4,$4,%lo($LC5)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	addiu	$5,$5,%lo(__func__.40504)

	j	$L79
	nop

$L73:
	sw	$0,100($sp)
	sw	$0,108($sp)
$L79:
	bne	$20,$0,$L70
	lui	$3,%hi(rtl_tcp_write_queue_tail)

$L60:
	beq	$16,$0,$L71
	lui	$2,%hi(rtl_get_tcp_sock_nonagle)

$L87:
	addiu	$2,$2,%lo(rtl_get_tcp_sock_nonagle)
	jalr	$2
	move	$4,$22

	move	$7,$2
	lw	$5,168($sp)
	lw	$6,104($sp)
	lui	$2,%hi(rtl_tcp_push)
	addiu	$2,$2,%lo(rtl_tcp_push)
	jalr	$2
	move	$4,$22

	j	$L82
	lui	$2,%hi(release_sock)

$L66:
	bne	$16,$0,$L87
	lui	$2,%hi(rtl_get_tcp_sock_nonagle)

$L40:
	lw	$5,168($sp)
	lui	$2,%hi(sk_stream_error)
	move	$4,$22
	addiu	$2,$2,%lo(sk_stream_error)
	jalr	$2
	move	$6,$17

	move	$16,$2
$L71:
	lui	$2,%hi(release_sock)
$L82:
	addiu	$2,$2,%lo(release_sock)
	jalr	$2
	move	$4,$22

$L35:
	move	$2,$16
	lw	$31,148($sp)
	lw	$fp,144($sp)
	lw	$23,140($sp)
	lw	$22,136($sp)
	lw	$21,132($sp)
	lw	$20,128($sp)
	lw	$19,124($sp)
	lw	$18,120($sp)
	lw	$17,116($sp)
	lw	$16,112($sp)
	j	$31
	addiu	$sp,$sp,152

	.set	macro
	.set	reorder
	.end	tcp_sendpages
	.size	tcp_sendpages, .-tcp_sendpages
	.align	2
	.globl	inet_sendpages
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
	sw	$31,36($sp)
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(rtl_sock_rps_record_flow)
	lw	$16,20($4)
	addiu	$2,$2,%lo(rtl_sock_rps_record_flow)
	move	$17,$5
	lw	$20,56($sp)
	move	$4,$16
	move	$18,$6
	jalr	$2
	move	$19,$7

	lui	$2,%hi(rtl_get_sk_inet_num)
	addiu	$2,$2,%lo(rtl_get_sk_inet_num)
	jalr	$2
	move	$4,$16

	bne	$2,$0,$L91
	move	$4,$16

	lui	$2,%hi(rtl_get_sk_no_autobind)
	addiu	$2,$2,%lo(rtl_get_sk_no_autobind)
	jalr	$2
	move	$4,$16

	bne	$2,$0,$L91
	move	$4,$16

	lui	$2,%hi(inet_autobind)
	addiu	$2,$2,%lo(inet_autobind)
	jalr	$2
	move	$4,$16

	bne	$2,$0,$L90
	move	$4,$16

$L91:
	sw	$20,56($sp)
	move	$5,$17
	lui	$25,%hi(tcp_sendpages)
	move	$6,$18
	lw	$31,36($sp)
	move	$7,$19
	lw	$20,32($sp)
	lw	$19,28($sp)
	addiu	$25,$25,%lo(tcp_sendpages)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	jr	$25
	addiu	$sp,$sp,40

$L90:
	lw	$31,36($sp)
	li	$2,-11			# 0xfffffffffffffff5
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	inet_sendpages
	.size	inet_sendpages, .-inet_sendpages
	.align	2
	.globl	sock_sendpages
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
	sw	$31,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$2,%hi(rtl_get_file_private_data)
	addiu	$2,$2,%lo(rtl_get_file_private_data)
	move	$16,$5
	move	$17,$6
	lw	$21,68($sp)
	move	$18,$7
	jalr	$2
	move	$19,$4

	move	$20,$2
	lui	$2,%hi(rtl_get_file_flags)
	addiu	$2,$2,%lo(rtl_get_file_flags)
	jalr	$2
	move	$4,$19

	li	$3,64			# 0x40
	andi	$2,$2,0x80
	lui	$25,%hi(inet_sendpages)
	movz	$3,$0,$2
	move	$4,$20
	move	$2,$3
	lw	$31,44($sp)
	ori	$3,$3,0x8000
	lw	$20,36($sp)
	movn	$2,$3,$21
	move	$5,$16
	move	$6,$17
	lw	$21,40($sp)
	move	$7,$18
	lw	$19,32($sp)
	lw	$18,28($sp)
	addiu	$25,$25,%lo(inet_sendpages)
	lw	$17,24($sp)
	lw	$16,20($sp)
	sw	$2,64($sp)
	jr	$25
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
	.end	sock_sendpages
	.size	sock_sendpages, .-sock_sendpages
	.section	.rodata.str1.4
	.align	2
$LC6:
	.ascii	"\0013%s confirm err=%d\012\000"
	.text
	.align	2
	.globl	rtl_pipe_to_sendpages
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
	sw	$31,60($sp)
	sw	$22,56($sp)
	sw	$21,52($sp)
	sw	$20,48($sp)
	sw	$19,44($sp)
	sw	$18,40($sp)
	sw	$17,36($sp)
	sw	$16,32($sp)
	move	$19,$0
	lw	$3,20($6)
	move	$20,$6
	lw	$2,16($6)
	move	$21,$5
	move	$18,$4
	lw	$22,12($6)
	sw	$3,28($sp)
	move	$17,$5
	j	$L97
	sw	$2,24($sp)

$L100:
	lw	$2,12($17)
	lw	$2,12($2)
	jalr	$2
	addiu	$17,$17,24

	beq	$2,$0,$L97
	move	$16,$2

	move	$6,$2
	lui	$4,%hi($LC6)
	lui	$5,%hi(__func__.40582)
	lui	$2,%hi(printk)
	addiu	$4,$4,%lo($LC6)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	addiu	$5,$5,%lo(__func__.40582)

	j	$L101
	move	$2,$16

$L97:
	lw	$2,20($18)
	move	$5,$17
	move	$4,$18
	sltu	$2,$19,$2
	bne	$2,$0,$L100
	addiu	$19,$19,1

	lw	$2,8($20)
	addiu	$3,$sp,24
	lw	$7,4($20)
	move	$4,$22
	andi	$2,$2,0x4
	sw	$7,0($20)
	sltu	$2,$0,$2
	lw	$6,4($21)
	move	$5,$18
	sw	$2,20($sp)
	lui	$2,%hi(sock_sendpages)
	addiu	$2,$2,%lo(sock_sendpages)
	jalr	$2
	sw	$3,16($sp)

	bltz	$2,$L99
	move	$16,$2

	lw	$3,20($20)
	sra	$7,$2,31
	lw	$8,16($20)
	lw	$6,28($20)
	addu	$2,$3,$2
	lw	$5,0($20)
	sltu	$3,$2,$3
	lw	$4,4($20)
	addu	$7,$8,$7
	addu	$6,$6,$16
	subu	$5,$5,$16
	addu	$3,$3,$7
	subu	$4,$4,$16
	sw	$6,28($20)
	sw	$5,0($20)
	sw	$3,16($20)
	sw	$2,20($20)
	sw	$4,4($20)
$L99:
	move	$2,$16
$L101:
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

	.set	macro
	.set	reorder
	.end	rtl_pipe_to_sendpages
	.size	rtl_pipe_to_sendpages, .-rtl_pipe_to_sendpages
	.align	2
	.globl	balance_dirty_pages_ratelimited_nr
	.set	nomips16
	.ent	balance_dirty_pages_ratelimited_nr
	.type	balance_dirty_pages_ratelimited_nr, @function
balance_dirty_pages_ratelimited_nr:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	lw	$7,60($4)
	lui	$3,%hi(ratelimit_pages)
	lw	$6,%lo(ratelimit_pages)($3)
	li	$2,8			# 0x8
	lw	$7,112($7)
	movz	$2,$6,$7
	lui	$6,%hi(bdp_ratelimits)
	lw	$7,%lo(bdp_ratelimits)($6)
	addu	$5,$5,$7
	sltu	$2,$5,$2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L104
	sw	$5,%lo(bdp_ratelimits)($6)
	.set	macro
	.set	reorder

	lw	$2,%lo(ratelimit_pages)($3)
	sw	$0,%lo(bdp_ratelimits)($6)
	sltu	$3,$5,$2
	movn	$5,$2,$3
	lui	$25,%hi(balance_dirty_pages)
	srl	$2,$5,1
	addu	$5,$2,$5
	addiu	$25,$25,%lo(balance_dirty_pages)
	jr	$25
$L104:
	j	$31
	.end	balance_dirty_pages_ratelimited_nr
	.size	balance_dirty_pages_ratelimited_nr, .-balance_dirty_pages_ratelimited_nr
	.section	.rodata.str1.4
	.align	2
$LC7:
	.ascii	"%s: %d: %s:count(%d) exceed maxinum\012\000"
	.align	2
$LC8:
	.ascii	"/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_"
	.ascii	"v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_"
	.ascii	"20160603/build_dir/target-mips-rlx5281-linux/linux-realt"
	.ascii	"ek_rtl8881a/rtl_sendfile-0.1/reverse_sendfile.c\000"
	.align	2
$LC9:
	.ascii	"%s: %d: %s: write_end fail,ret = %d\012\000"
	.text
	.align	2
	.globl	do_splice_from_socket
	.set	nomips16
	.ent	do_splice_from_socket
	.type	do_splice_from_socket, @function
do_splice_from_socket:
	.frame	$sp,680,$31		# vars= 608, regs= 10/0, args= 32, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-680
	sw	$31,676($sp)
	sw	$fp,672($sp)
	sw	$23,668($sp)
	sw	$22,664($sp)
	sw	$21,660($sp)
	sw	$20,656($sp)
	sw	$19,652($sp)
	sw	$18,648($sp)
	sw	$17,644($sp)
	sw	$16,640($sp)
	lui	$2,%hi(rtl_get_file_mapping)
	sw	$5,684($sp)
	addiu	$2,$2,%lo(rtl_get_file_mapping)
	sw	$6,688($sp)
	move	$22,$4
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$7,692($sp)
	.set	macro
	.set	reorder

	lw	$3,688($sp)
	move	$17,$2
	lw	$4,0($17)
	addiu	$2,$3,8
	or	$2,$2,$3
	sw	$4,624($sp)
	sw	$2,632($sp)
	lw	$5,632($sp)
	lw	$2,24($28)
	and	$2,$5,$2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L122
	addiu	$4,$sp,40
	.set	macro
	.set	reorder

	move	$5,$3
	li	$6,8			# 0x8
 #APP
 # 571 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/rtl_sendfile-0.1/reverse_sendfile.c" 1
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
	bne	$6,$0,$L122
	li	$3,65536			# 0x10000
	.set	macro
	.set	reorder

	lw	$2,692($sp)
	addiu	$3,$3,1
	sltu	$3,$2,$3
	.set	noreorder
	.set	nomacro
	bne	$3,$0,$L108
	lui	$4,%hi($LC7)
	.set	macro
	.set	reorder

	sw	$2,16($sp)
	lui	$5,%hi($LC8)
	lui	$7,%hi(__func__.40632)
	lui	$2,%hi(printk)
	addiu	$4,$4,%lo($LC7)
	addiu	$5,$5,%lo($LC8)
	li	$6,575			# 0x23f
	addiu	$7,$7,%lo(__func__.40632)
	addiu	$2,$2,%lo(printk)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$16,-22			# 0xffffffffffffffea
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L128
	move	$2,$16
	.set	macro
	.set	reorder

$L108:
	lw	$4,624($sp)
	lui	$2,%hi(rtl_inode_mutex_lock)
	addiu	$2,$2,%lo(rtl_inode_mutex_lock)
	jalr	$2
	lui	$2,%hi(rtl_get_inode_sb)
	lw	$4,624($sp)
	addiu	$2,$2,%lo(rtl_get_inode_sb)
	jalr	$2
	move	$4,$2
	lui	$2,%hi(rtl_vfs_check_frozen)
	addiu	$2,$2,%lo(rtl_vfs_check_frozen)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,1			# 0x1
	.set	macro
	.set	reorder

	move	$4,$22
	lw	$2,0($28)
	addiu	$5,$sp,40
	lw	$3,60($17)
	lw	$7,624($sp)
	sw	$3,672($2)
	lui	$2,%hi(rtl_generic_write_checks)
	addiu	$2,$2,%lo(rtl_generic_write_checks)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$6,$sp,692
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L109
	move	$16,$2
	.set	macro
	.set	reorder

	lw	$2,692($sp)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L110
	move	$4,$22
	.set	macro
	.set	reorder

	lui	$2,%hi(file_remove_suid)
	addiu	$2,$2,%lo(file_remove_suid)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$16,$sp,232
	.set	macro
	.set	reorder

	lui	$2,%hi(file_update_time)
	addiu	$2,$2,%lo(file_update_time)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$22
	.set	macro
	.set	reorder

	addiu	$23,$sp,76
	lw	$20,692($sp)
	move	$18,$16
	lw	$6,40($sp)
	move	$fp,$0
	lw	$7,44($sp)
$L114:
	andi	$8,$7,0xfff
	li	$4,4096			# 0x1000
	subu	$3,$4,$8
	li	$5,1			# 0x1
	sltu	$19,$20,$3
	lw	$2,52($17)
	movn	$3,$20,$19
	move	$4,$22
	sw	$3,16($sp)
	move	$19,$3
	sw	$8,628($sp)
	addiu	$3,$sp,32
	addiu	$8,$sp,36
	subu	$20,$20,$19
	sw	$5,20($sp)
	sw	$8,24($sp)
	sw	$3,28($sp)
	lw	$2,20($2)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L111
	move	$21,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L112
	move	$18,$0
	.set	macro
	.set	reorder

$L113:
	lw	$9,0($16)
	move	$5,$17
	lw	$8,-16($16)
	lw	$3,4($16)
	lw	$2,52($17)
	lw	$7,-4($16)
	lw	$6,-8($16)
	sw	$9,16($sp)
	sw	$9,20($sp)
	sw	$8,24($sp)
	sw	$3,28($sp)
	lw	$2,24($2)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$16,$16,24
	.set	macro
	.set	reorder

$L112:
	slt	$2,$18,$fp
	addiu	$18,$18,1
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L113
	move	$4,$22
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L109
	move	$16,$21
	.set	macro
	.set	reorder

$L111:
	lui	$6,%hi(mem_map)
	li	$8,-2147483648			# 0xffffffff80000000
	lw	$4,36($sp)
	addiu	$fp,$fp,1
	lw	$5,%lo(mem_map)($6)
	lw	$2,44($sp)
	subu	$5,$4,$5
	sra	$5,$5,5
	lw	$3,40($sp)
	sll	$5,$5,12
	addu	$7,$2,$19
	addu	$5,$5,$8
	sltu	$6,$7,$2
	lw	$8,628($sp)
	addu	$6,$6,$3
	sw	$2,-4($18)
	lw	$2,32($sp)
	addu	$5,$5,$8
	sw	$4,-16($18)
	sw	$3,-8($18)
	sw	$19,0($18)
	sw	$2,4($18)
	addiu	$18,$18,24
	sw	$5,0($23)
	sw	$19,4($23)
	addiu	$23,$23,8
	sw	$6,40($sp)
	.set	noreorder
	.set	nomacro
	bne	$20,$0,$L114
	sw	$7,44($sp)
	.set	macro
	.set	reorder

	addiu	$2,$sp,76
	lui	$20,%hi(rtl_set_sk_rcvtimeo)
	sw	$2,56($sp)
	li	$2,65536			# 0x10000
	lw	$4,684($sp)
	addiu	$20,$20,%lo(rtl_set_sk_rcvtimeo)
	sw	$2,72($sp)
	lui	$2,%hi(rtl_get_sk_rcvtimeo)
	sw	$0,48($sp)
	addiu	$2,$2,%lo(rtl_get_sk_rcvtimeo)
	sw	$0,52($sp)
	sw	$fp,60($sp)
	sw	$0,64($sp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$0,68($sp)
	.set	macro
	.set	reorder

	li	$5,300			# 0x12c
	lw	$4,684($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	move	$18,$2
	.set	macro
	.set	reorder

	addiu	$5,$sp,48
	lw	$2,692($sp)
	addiu	$6,$sp,76
	lw	$4,684($sp)
	sw	$2,16($sp)
	li	$2,131072			# 0x20000
	addiu	$2,$2,256
	sw	$2,20($sp)
	lui	$2,%hi(kernel_recvmsg)
	addiu	$2,$2,%lo(kernel_recvmsg)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$7,$fp
	.set	macro
	.set	reorder

	move	$5,$18
	lw	$4,684($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	move	$19,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bgez	$19,$L125
	sra	$5,$19,31
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L127
	move	$18,$0
	.set	macro
	.set	reorder

$L117:
	lw	$9,0($16)
	move	$5,$17
	lw	$8,-16($16)
	lw	$3,4($16)
	lw	$2,52($17)
	lw	$7,-4($16)
	lw	$6,-8($16)
	sw	$9,16($sp)
	sw	$9,20($sp)
	sw	$8,24($sp)
	sw	$3,28($sp)
	lw	$2,24($2)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$16,$16,24
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L129
	slt	$2,$18,$fp
	.set	macro
	.set	reorder

$L127:
	slt	$2,$18,$fp
$L129:
	addiu	$18,$18,1
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L117
	move	$4,$22
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L109
	move	$16,$19
	.set	macro
	.set	reorder

$L125:
	lw	$3,44($sp)
	lw	$2,692($sp)
	lui	$20,%hi($LC9)
	lw	$6,40($sp)
	lui	$21,%hi($LC8)
	subu	$2,$3,$2
	lui	$23,%hi(__func__.40632)
	sltu	$4,$3,$2
	addu	$3,$2,$19
	subu	$4,$6,$4
	sltu	$2,$3,$2
	addu	$4,$4,$5
	move	$18,$0
	addu	$2,$2,$4
	addiu	$20,$20,%lo($LC9)
	sw	$19,692($sp)
	addiu	$21,$21,%lo($LC8)
	sw	$2,40($sp)
	addiu	$23,$23,%lo(__func__.40632)
	sw	$3,44($sp)
	.set	noreorder
	.set	nomacro
	j	$L118
	lui	$19,%hi(printk)
	.set	macro
	.set	reorder

$L120:
	lw	$9,0($16)
	lw	$8,-16($16)
	lw	$3,4($16)
	lw	$2,52($17)
	lw	$7,-4($16)
	lw	$6,-8($16)
	sw	$9,16($sp)
	sw	$9,20($sp)
	sw	$8,24($sp)
	sw	$3,28($sp)
	lw	$2,24($2)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$16,$16,24
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bgez	$2,$L118
	move	$4,$20
	.set	macro
	.set	reorder

	li	$6,673			# 0x2a1
	move	$5,$21
	addiu	$3,$19,%lo(printk)
	move	$7,$23
	.set	noreorder
	.set	nomacro
	jalr	$3
	sw	$2,16($sp)
	.set	macro
	.set	reorder

$L118:
	slt	$2,$18,$fp
	addiu	$18,$18,1
	move	$4,$22
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L120
	move	$5,$17
	.set	macro
	.set	reorder

	lui	$2,%hi(balance_dirty_pages_ratelimited_nr)
	move	$4,$17
	addiu	$2,$2,%lo(balance_dirty_pages_ratelimited_nr)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$fp
	.set	macro
	.set	reorder

	lw	$2,24($28)
	lw	$3,632($sp)
	and	$2,$3,$2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L110
	addiu	$5,$sp,40
	.set	macro
	.set	reorder

	lw	$4,688($sp)
	li	$6,8			# 0x8
 #APP
 # 677 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/rtl_sendfile-0.1/reverse_sendfile.c" 1
	.set	noat
	la	$1, __copy_user
	jalr	$1
	.set	at
	
 # 0 "" 2
 #NO_APP
	j	$L110
$L109:
	lw	$2,0($28)
	lw	$4,624($sp)
	sw	$0,672($2)
	lui	$2,%hi(rtl_inode_mutex_unlock)
	addiu	$2,$2,%lo(rtl_inode_mutex_unlock)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L128
	move	$2,$16
	.set	macro
	.set	reorder

$L122:
	li	$16,-14			# 0xfffffffffffffff2
	move	$2,$16
$L128:
	lw	$31,676($sp)
	lw	$fp,672($sp)
	lw	$23,668($sp)
	lw	$22,664($sp)
	lw	$21,660($sp)
	lw	$20,656($sp)
	lw	$19,652($sp)
	lw	$18,648($sp)
	lw	$17,644($sp)
	lw	$16,640($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,680
	.set	macro
	.set	reorder

$L110:
	lw	$2,0($28)
	lw	$4,624($sp)
	sw	$0,672($2)
	lui	$2,%hi(rtl_inode_mutex_unlock)
	addiu	$2,$2,%lo(rtl_inode_mutex_unlock)
	jalr	$2
	lw	$16,692($sp)
	.set	noreorder
	.set	nomacro
	j	$L128
	move	$2,$16
	.set	macro
	.set	reorder

	.end	do_splice_from_socket
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
	.set	nomips16
	.ent	rtl_splice
	.type	rtl_splice, @function
rtl_splice:
	.frame	$sp,48,$31		# vars= 8, regs= 6/0, args= 16, gp= 0
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$20,40($sp)
	sw	$19,36($sp)
	sw	$18,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	li	$2,-9			# 0xfffffffffffffff7
	sw	$2,16($sp)
	lui	$2,%hi(sockfd_lookup)
	move	$18,$5
	addiu	$2,$2,%lo(sockfd_lookup)
	addiu	$5,$sp,16
	move	$16,$6
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$19,$7
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L131
	move	$17,$2
	.set	macro
	.set	reorder

	lw	$2,20($2)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L144
	lui	$2,%hi(fget_light)
	.set	macro
	.set	reorder

	move	$4,$16
	addiu	$2,$2,%lo(fget_light)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$5,$sp,20
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L144
	move	$16,$2
	.set	macro
	.set	reorder

	move	$4,$2
	lui	$2,%hi(rtl_get_file_mode)
	addiu	$2,$2,%lo(rtl_get_file_mode)
	jalr	$2
	andi	$2,$2,0x2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L133
	lui	$2,%hi(rtl_get_file_mapping)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_get_file_mapping)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$16
	.set	macro
	.set	reorder

	lw	$4,0($2)
	move	$20,$2
	lui	$2,%hi(rtl_get_inode_sb)
	addiu	$2,$2,%lo(rtl_get_inode_sb)
	jalr	$2
	lui	$3,%hi($LC10)
	lw	$2,32($2)
	addiu	$3,$3,%lo($LC10)
	lw	$7,0($2)
	move	$2,$7
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$4,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$4,2f
	addiu	$3,1
	bnez	$4,1b
	lbu	$4,($2)
	move	$4,$1
2:	subu	$4,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L134
	lui	$3,%hi($LC11)
	.set	macro
	.set	reorder

	move	$2,$7
	addiu	$3,$3,%lo($LC11)
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$4,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$4,2f
	addiu	$3,1
	bnez	$4,1b
	lbu	$4,($2)
	move	$4,$1
2:	subu	$4,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L135
	lui	$2,%hi(jffs2_file_address_operations)
	.set	macro
	.set	reorder

$L134:
	lui	$4,%hi($LC12)
	lui	$5,%hi(__func__.40676)
	lui	$2,%hi(printk)
	addiu	$4,$4,%lo($LC12)
	addiu	$5,$5,%lo(__func__.40676)
	addiu	$2,$2,%lo(printk)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,721			# 0x2d1
	.set	macro
	.set	reorder

	j	$L133
$L135:
	lw	$3,52($20)
	addiu	$2,$2,%lo(jffs2_file_address_operations)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L136
	lui	$2,%hi(do_splice_from_socket)
	.set	macro
	.set	reorder

	lw	$2,64($sp)
	li	$3,1			# 0x1
	.set	noreorder
	.set	nomacro
	j	$L133
	sw	$3,0($2)
	.set	macro
	.set	reorder

$L136:
	move	$4,$16
	move	$5,$17
	addiu	$2,$2,%lo(do_splice_from_socket)
	move	$6,$18
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$7,$19
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L133
	sw	$2,16($sp)
	.set	macro
	.set	reorder

$L132 = .
$L138:
	lui	$16,%hi(fput)
	addiu	$16,$16,%lo(fput)
	jalr	$16
$L137:
	lw	$4,16($17)
	jalr	$16
$L131:
	lw	$2,16($sp)
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

$L133:
	lw	$2,20($sp)
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L138
	move	$4,$16
	.set	macro
	.set	reorder

$L144:
	lui	$16,%hi(fput)
	.set	noreorder
	.set	nomacro
	j	$L137
	addiu	$16,$16,%lo(fput)
	.set	macro
	.set	reorder

	.end	rtl_splice
	.size	rtl_splice, .-rtl_splice
	.align	2
	.globl	memcpy_tokerneliovec
	.set	nomips16
	.ent	memcpy_tokerneliovec
	.type	memcpy_tokerneliovec, @function
memcpy_tokerneliovec:
	.frame	$sp,40,$31		# vars= 0, regs= 6/0, args= 16, gp= 0
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	lui	$20,%hi(memcpy)
	move	$16,$4
	move	$19,$5
	j	$L146
	move	$17,$6

$L148:
	lw	$2,4($16)
	beq	$2,$0,$L147
	sltu	$18,$2,$17

	lw	$4,0($16)
	movz	$2,$17,$18
	move	$18,$2
	move	$6,$2
	addiu	$2,$20,%lo(memcpy)
	jalr	$2
	move	$5,$19

	addu	$19,$19,$18
	lw	$2,4($16)
	subu	$17,$17,$18
	lw	$3,0($16)
	subu	$2,$2,$18
	addu	$18,$3,$18
	sw	$2,4($16)
	sw	$18,0($16)
$L147:
	addiu	$16,$16,8
$L146:
	bgtz	$17,$L148
	move	$2,$0

	lw	$31,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	memcpy_tokerneliovec
	.size	memcpy_tokerneliovec, .-memcpy_tokerneliovec
	.align	2
	.globl	rtl_skb_copy_datagram_to_kernel_iovec
	.set	nomips16
	.ent	rtl_skb_copy_datagram_to_kernel_iovec
	.type	rtl_skb_copy_datagram_to_kernel_iovec, @function
rtl_skb_copy_datagram_to_kernel_iovec:
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
	lui	$23,%hi(rtl_skb_shared_info)
	addiu	$23,$23,%lo(rtl_skb_shared_info)
	move	$22,$4
	move	$17,$5
	sw	$6,72($sp)
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$19,$7
	.set	macro
	.set	reorder

	lw	$2,8($2)
	.set	noreorder
	.set	nomacro
	beq	$19,$0,$L159
	sw	$2,20($sp)
	.set	macro
	.set	reorder

	move	$21,$0
	lui	$fp,%hi(mem_map)
$L151:
	lui	$3,%hi(rtl_skb_headlen)
	move	$4,$22
	addiu	$3,$3,%lo(rtl_skb_headlen)
	.set	noreorder
	.set	nomacro
	jalr	$3
	li	$16,-1			# 0xffffffffffffffff
	.set	macro
	.set	reorder

$L156:
	addu	$18,$21,$2
	slt	$2,$17,$18
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L152
	subu	$2,$18,$17
	.set	macro
	.set	reorder

	subu	$21,$17,$21
	slt	$20,$19,$2
	movn	$2,$19,$20
	move	$20,$2
	li	$2,-1			# 0xffffffffffffffff
	.set	noreorder
	.set	nomacro
	bne	$16,$2,$L153
	move	$4,$22
	.set	macro
	.set	reorder

	lui	$3,%hi(rtl_get_skb_data_common)
	addiu	$2,$3,%lo(rtl_get_skb_data_common)
	.set	noreorder
	.set	nomacro
	jalr	$2
	subu	$19,$19,$20
	.set	macro
	.set	reorder

	lui	$3,%hi(memcpy_tokerneliovec)
	lw	$4,72($sp)
	addu	$5,$2,$21
	addiu	$2,$3,%lo(memcpy_tokerneliovec)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$6,$20
	.set	macro
	.set	reorder

	j	$L161
$L153:
	.set	noreorder
	.set	nomacro
	jalr	$23
	subu	$19,$19,$20
	.set	macro
	.set	reorder

	addiu	$4,$16,5
	sll	$4,$4,3
	lw	$5,%lo(mem_map)($fp)
	addu	$4,$2,$4
	lui	$2,%hi(rtl_get_frag_offset)
	lw	$6,4($4)
	addiu	$3,$2,%lo(rtl_get_frag_offset)
	li	$2,-2147483648			# 0xffffffff80000000
	addiu	$4,$4,4
	subu	$5,$6,$5
	sra	$5,$5,5
	sll	$5,$5,12
	addu	$5,$5,$2
	.set	noreorder
	.set	nomacro
	jalr	$3
	sw	$5,16($sp)
	.set	macro
	.set	reorder

	lw	$3,16($sp)
	addu	$21,$2,$21
	lw	$4,72($sp)
	addu	$5,$3,$21
	lui	$3,%hi(memcpy_tokerneliovec)
	addiu	$2,$3,%lo(memcpy_tokerneliovec)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$6,$20
	.set	macro
	.set	reorder

$L161:
	.set	noreorder
	.set	nomacro
	beq	$19,$0,$L159
	addu	$17,$17,$20
	.set	macro
	.set	reorder

$L152:
	move	$4,$22
	.set	noreorder
	.set	nomacro
	jalr	$23
	addiu	$16,$16,1
	.set	macro
	.set	reorder

	lbu	$2,0($2)
	slt	$2,$16,$2
	beq	$2,$0,$L155
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$22
	.set	macro
	.set	reorder

	addiu	$3,$16,5
	sll	$3,$3,3
	addu	$2,$2,$3
	lhu	$2,10($2)
	.set	noreorder
	.set	nomacro
	j	$L156
	move	$21,$18
	.set	macro
	.set	reorder

$L155:
	lw	$2,20($sp)
	beq	$2,$0,$L160
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$2
	.set	macro
	.set	reorder

	lw	$2,8($2)
	beq	$2,$0,$L157
 #APP
 # 13 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/bug.h" 1
	break 12
 # 0 "" 2
 #NO_APP
$L157:
	lw	$22,20($sp)
	move	$21,$18
	lw	$3,0($22)
	.set	noreorder
	.set	nomacro
	j	$L151
	sw	$3,20($sp)
	.set	macro
	.set	reorder

$L159:
	.set	noreorder
	.set	nomacro
	j	$L150
	move	$2,$0
	.set	macro
	.set	reorder

$L160:
	li	$2,-14			# 0xfffffffffffffff2
$L150:
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

	.end	rtl_skb_copy_datagram_to_kernel_iovec
	.size	rtl_skb_copy_datagram_to_kernel_iovec, .-rtl_skb_copy_datagram_to_kernel_iovec
	.section	.rodata.str1.4
	.align	2
$LC13:
	.ascii	"rtl_sendfile installed\012\000"
	.section	.init.text,"ax",@progbits
	.align	2
	.set	nomips16
	.ent	rtl_sendfile_init
	.type	rtl_sendfile_init, @function
rtl_sendfile_init:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$4,%hi($LC13)
	lui	$2,%hi(printk)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	addiu	$4,$4,%lo($LC13)

	lui	$3,%hi(_rtl_sendfile_hook)
	addiu	$3,$3,%lo(_rtl_sendfile_hook)
	lui	$2,%hi(rtl_sendfile_hook)
	lw	$31,20($sp)
	sw	$3,%lo(rtl_sendfile_hook)($2)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	rtl_sendfile_init
	.size	rtl_sendfile_init, .-rtl_sendfile_init
	.section	.rodata.str1.4
	.align	2
$LC14:
	.ascii	"rtl_sendfile removed\012\000"
	.section	.exit.text,"ax",@progbits
	.align	2
	.set	nomips16
	.ent	rtl_sendfile_cleanup
	.type	rtl_sendfile_cleanup, @function
rtl_sendfile_cleanup:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$4,%hi($LC14)
	lui	$2,%hi(printk)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	addiu	$4,$4,%lo($LC14)

	lui	$2,%hi(rtl_sendfile_hook)
	lw	$31,20($sp)
	sw	$0,%lo(rtl_sendfile_hook)($2)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	rtl_sendfile_cleanup
	.size	rtl_sendfile_cleanup, .-rtl_sendfile_cleanup
	.section	.modinfo,"a",@progbits
	.type	__UNIQUE_ID_license1, @object
	.size	__UNIQUE_ID_license1, 12
__UNIQUE_ID_license1:
	.ascii	"license=GPL\000"
	.globl	g2_tcp_ctl
	.section	.bss,"aw",@nobits
	.align	2
	.type	g2_tcp_ctl, @object
	.size	g2_tcp_ctl, 32
g2_tcp_ctl:
	.space	32
	.rdata
	.align	2
	.type	__func__.40504, @object
	.size	__func__.40504, 19
__func__.40504:
	.ascii	"do_tcp_send_mpages\000"
	.align	2
	.type	__func__.40582, @object
	.size	__func__.40582, 22
__func__.40582:
	.ascii	"rtl_pipe_to_sendpages\000"
	.section	.data,"aw",@progbits
	.align	2
	.type	bdp_ratelimits, @object
	.size	bdp_ratelimits, 4
bdp_ratelimits:
	.space	4
	.rdata
	.align	2
	.type	__func__.40632, @object
	.size	__func__.40632, 22
__func__.40632:
	.ascii	"do_splice_from_socket\000"
	.align	2
	.type	__func__.40676, @object
	.size	__func__.40676, 11
__func__.40676:
	.ascii	"rtl_splice\000"
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
	.globl	init_module
	init_module = rtl_sendfile_init
	.globl	cleanup_module
	cleanup_module = rtl_sendfile_cleanup
	.ident	"GCC: (Realtek RSDK-4.6.4 Build 2002) 4.6.4"
