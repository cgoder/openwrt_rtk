	.file	1 "fastpath_core.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
	.align	2
	.set	nomips16
	.ent	cache_timeout
	.type	cache_timeout, @function
cache_timeout:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lbu	$2,0($4)
	beq	$2,$0,$L6
	nop

	lw	$5,8($4)
	lw	$3,4($4)
	lhu	$2,2($4)
	xor	$3,$5,$3
	lui	$5,%hi(max_udp_frag_entry)
	srl	$8,$3,16
	lw	$5,%lo(max_udp_frag_entry)($5)
	xor	$2,$2,$3
	lbu	$7,1($4)
	xor	$2,$2,$8
	addiu	$3,$5,-1
	lw	$6,44($4)
	srl	$5,$2,8
	xor	$2,$2,$7
	sb	$0,0($4)
	xor	$2,$2,$5
	beq	$6,$0,$L3
	and	$2,$2,$3

	lw	$8,48($4)
	sll	$7,$2,2
	sll	$5,$2,4
	lui	$3,%hi(udp_cache_table)
	sw	$8,48($6)
	j	$L4
	subu	$5,$5,$7

$L3:
	lui	$3,%hi(udp_cache_table)
	sll	$7,$2,2
	lw	$6,%lo(udp_cache_table)($3)
	sll	$5,$2,4
	subu	$5,$5,$7
	lw	$2,0($6)
	lw	$6,48($4)
	addu	$2,$2,$5
	sw	$6,4($2)
$L4:
	lw	$7,48($4)
	lui	$2,%hi(udp_cache_list_free)
	lw	$8,44($4)
	addiu	$2,$2,%lo(udp_cache_list_free)
	addiu	$6,$4,52
	sw	$8,0($7)
	lw	$7,%lo(udp_cache_table)($3)
	lw	$3,4($2)
	lw	$7,0($7)
	addu	$5,$7,$5
	lw	$7,8($5)
	addiu	$7,$7,-1
	sw	$7,8($5)
	sw	$3,56($4)
	sw	$0,52($4)
	sw	$4,0($3)
	lw	$3,8($2)
	sw	$6,4($2)
	addiu	$3,$3,1
	sw	$3,8($2)
$L6:
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	cache_timeout
	.size	cache_timeout, .-cache_timeout
	.align	2
	.set	nomips16
	.ent	negative_cache_timeout
	.type	negative_cache_timeout, @function
negative_cache_timeout:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lw	$5,8($4)
	lw	$3,4($4)
	lhu	$2,2($4)
	xor	$3,$5,$3
	lui	$5,%hi(max_udp_frag_entry)
	srl	$8,$3,16
	lw	$5,%lo(max_udp_frag_entry)($5)
	xor	$2,$2,$3
	lbu	$7,1($4)
	xor	$2,$2,$8
	addiu	$3,$5,-1
	lw	$6,40($4)
	srl	$5,$2,8
	xor	$2,$2,$7
	sb	$0,0($4)
	xor	$2,$2,$5
	beq	$6,$0,$L8
	and	$2,$2,$3

	lw	$5,44($4)
	sll	$7,$2,2
	lui	$3,%hi(negative_cache_table)
	sll	$2,$2,4
	j	$L9
	sw	$5,44($6)

$L8:
	lui	$3,%hi(negative_cache_table)
	sll	$7,$2,2
	lw	$8,%lo(negative_cache_table)($3)
	sll	$2,$2,4
	lw	$6,44($4)
	subu	$5,$2,$7
	addu	$5,$8,$5
	sw	$6,4($5)
$L9:
	lw	$5,44($4)
	subu	$7,$2,$7
	lw	$8,40($4)
	lui	$2,%hi(negative_cache_list_free)
	addiu	$2,$2,%lo(negative_cache_list_free)
	addiu	$6,$4,48
	sw	$8,0($5)
	lw	$5,%lo(negative_cache_table)($3)
	lw	$3,4($2)
	addu	$5,$5,$7
	lw	$7,8($5)
	addiu	$7,$7,-1
	sw	$7,8($5)
	sw	$3,52($4)
	sw	$0,48($4)
	sw	$4,0($3)
	lw	$3,8($2)
	sw	$6,4($2)
	addiu	$3,$3,1
	j	$31
	sw	$3,8($2)

	.set	macro
	.set	reorder
	.end	negative_cache_timeout
	.size	negative_cache_timeout, .-negative_cache_timeout
	.align	2
	.set	nomips16
	.ent	fastpath_napt_single_write
	.type	fastpath_napt_single_write, @function
fastpath_napt_single_write:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$6

	.set	macro
	.set	reorder
	.end	fastpath_napt_single_write
	.size	fastpath_napt_single_write, .-fastpath_napt_single_write
	.align	2
	.set	nomips16
	.ent	fastpath_path_single_write
	.type	fastpath_path_single_write, @function
fastpath_path_single_write:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$6

	.set	macro
	.set	reorder
	.end	fastpath_path_single_write
	.size	fastpath_path_single_write, .-fastpath_path_single_write
	.align	2
	.globl	fastpath_path_single_open
	.set	nomips16
	.ent	fastpath_path_single_open
	.type	fastpath_path_single_open, @function
fastpath_path_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	move	$4,$5
	lui	$25,%hi(single_open)
	lui	$5,%hi(fastpath_table_path)
	move	$6,$0
	addiu	$5,$5,%lo(fastpath_table_path)
	addiu	$25,$25,%lo(single_open)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	fastpath_path_single_open
	.size	fastpath_path_single_open, .-fastpath_path_single_open
	.align	2
	.globl	fastpath_napt_single_open
	.set	nomips16
	.ent	fastpath_napt_single_open
	.type	fastpath_napt_single_open, @function
fastpath_napt_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	move	$4,$5
	lui	$25,%hi(single_open)
	lui	$5,%hi(fastpath_table_napt)
	move	$6,$0
	addiu	$5,$5,%lo(fastpath_table_napt)
	addiu	$25,$25,%lo(single_open)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	fastpath_napt_single_open
	.size	fastpath_napt_single_open, .-fastpath_napt_single_open
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"TCP\000"
	.align	2
$LC1:
	.ascii	"UDP\000"
	.align	2
$LC2:
	.ascii	"~Path: [%s] in-S=0x%08X:%-5u in-D=0x%08X:%-5u out-S=0x%0"
	.ascii	"8X:%-5u out-D=0x%08X:%-5u out-ifname=%-5s <%u> {%d}\000"
	.align	2
$LC3:
	.ascii	",[PreMark:%d,PostMark:%d]\000"
	.align	2
$LC4:
	.ascii	"\012\000"
	.text
	.align	2
	.set	nomips16
	.ent	fastpath_table_path
	.type	fastpath_table_path, @function
fastpath_table_path:
	.frame	$sp,88,$31		# vars= 0, regs= 8/0, args= 56, gp= 0
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-88
	sw	$31,84($sp)
	sw	$22,80($sp)
	sw	$21,76($sp)
	sw	$20,72($sp)
	sw	$19,68($sp)
	sw	$18,64($sp)
	sw	$17,60($sp)
	sw	$16,56($sp)
	lui	$2,%hi(path_list_inuse)
	lui	$19,%hi($LC2)
	lui	$20,%hi($LC3)
	lui	$21,%hi($LC4)
	lui	$17,%hi($LC1)
	lw	$16,%lo(path_list_inuse)($2)
	lui	$18,%hi($LC0)
	addiu	$19,$19,%lo($LC2)
	addiu	$20,$20,%lo($LC3)
	j	$L15
	addiu	$21,$21,%lo($LC4)

$L17:
	lw	$3,4($16)
	li	$2,2			# 0x2
	bne	$3,$2,$L16
	addiu	$5,$17,%lo($LC1)

	addiu	$5,$18,%lo($LC0)
$L16:
	lw	$2,20($16)
	lui	$22,%hi(printk)
	lw	$7,12($16)
	addiu	$22,$22,%lo(printk)
	lw	$6,16($16)
	move	$4,$19
	sw	$2,16($sp)
	lw	$2,8($16)
	sw	$2,20($sp)
	lw	$2,24($16)
	sw	$2,24($sp)
	lw	$2,28($16)
	sw	$2,28($sp)
	lw	$2,32($16)
	sw	$2,32($sp)
	lw	$2,36($16)
	sw	$2,36($sp)
	lw	$2,44($16)
	sw	$2,40($sp)
	lbu	$2,2($16)
	sw	$2,44($sp)
	lbu	$2,1($16)
	jalr	$22
	sw	$2,48($sp)

	lw	$5,48($16)
	lw	$6,52($16)
	jalr	$22
	move	$4,$20

	jalr	$22
	move	$4,$21

	lw	$16,72($16)
$L15:
	bne	$16,$0,$L17
	move	$2,$0

	lw	$31,84($sp)
	lw	$22,80($sp)
	lw	$21,76($sp)
	lw	$20,72($sp)
	lw	$19,68($sp)
	lw	$18,64($sp)
	lw	$17,60($sp)
	lw	$16,56($sp)
	j	$31
	addiu	$sp,$sp,88

	.set	macro
	.set	reorder
	.end	fastpath_table_path
	.size	fastpath_table_path, .-fastpath_table_path
	.section	.rodata.str1.4
	.align	2
$LC5:
	.ascii	"~Napt: [%s] int=0x%08X:%-5u ext=0x%08X:%-5u rem=0x%08X:%"
	.ascii	"-5u flags=0x%08X \012\000"
	.text
	.align	2
	.set	nomips16
	.ent	fastpath_table_napt
	.type	fastpath_table_napt, @function
fastpath_table_napt:
	.frame	$sp,64,$31		# vars= 0, regs= 6/0, args= 40, gp= 0
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-64
	sw	$31,60($sp)
	sw	$20,56($sp)
	sw	$19,52($sp)
	sw	$18,48($sp)
	sw	$17,44($sp)
	sw	$16,40($sp)
	lui	$2,%hi(napt_list_inuse)
	lui	$19,%hi($LC5)
	lui	$17,%hi($LC1)
	lw	$16,%lo(napt_list_inuse)($2)
	lui	$18,%hi($LC0)
	addiu	$19,$19,%lo($LC5)
	j	$L20
	lui	$20,%hi(printk)

$L22:
	lw	$3,4($16)
	li	$2,2			# 0x2
	bne	$3,$2,$L21
	addiu	$5,$17,%lo($LC1)

	addiu	$5,$18,%lo($LC0)
$L21:
	lw	$3,16($16)
	move	$4,$19
	lw	$6,8($16)
	addiu	$2,$20,%lo(printk)
	lw	$7,12($16)
	sw	$3,16($sp)
	lw	$3,20($16)
	sw	$3,20($sp)
	lw	$3,24($16)
	sw	$3,24($sp)
	lw	$3,28($16)
	sw	$3,28($sp)
	lw	$3,32($16)
	jalr	$2
	sw	$3,32($sp)

	lw	$16,44($16)
$L20:
	bne	$16,$0,$L22
	move	$2,$0

	lw	$31,60($sp)
	lw	$20,56($sp)
	lw	$19,52($sp)
	lw	$18,48($sp)
	lw	$17,44($sp)
	lw	$16,40($sp)
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
	.end	fastpath_table_napt
	.size	fastpath_table_napt, .-fastpath_table_napt
	.align	2
	.globl	udp_fragCache_init
	.set	nomips16
	.ent	udp_fragCache_init
	.type	udp_fragCache_init, @function
udp_fragCache_init:
	.frame	$sp,56,$31		# vars= 0, regs= 9/0, args= 16, gp= 0
	.mask	0x80ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$23,48($sp)
	sw	$22,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$20,%hi(kmalloc_caches)
	addiu	$20,$20,%lo(kmalloc_caches)
	move	$19,$4
	lui	$21,%hi(kmem_cache_alloc)
	li	$5,32			# 0x20
	lw	$4,20($20)
	addiu	$21,$21,%lo(kmem_cache_alloc)
	jalr	$21
	lui	$16,%hi(udp_cache_table)

	move	$18,$2
	beq	$2,$0,$L32
	sw	$2,%lo(udp_cache_table)($16)

	lui	$2,%hi(udp_cache_list_free)
	sll	$3,$19,2
	addiu	$17,$2,%lo(udp_cache_list_free)
	sll	$4,$19,4
	sw	$0,%lo(udp_cache_list_free)($2)
	lui	$2,%hi(max_udp_frag_entry)
	sw	$19,%lo(max_udp_frag_entry)($2)
	lui	$2,%hi(__kmalloc)
	subu	$4,$4,$3
	li	$5,32			# 0x20
	sw	$0,8($17)
	addiu	$2,$2,%lo(__kmalloc)
	jalr	$2
	sw	$17,4($17)

	sw	$2,0($18)
	lw	$2,%lo(udp_cache_table)($16)
	lw	$2,0($2)
	beq	$2,$0,$L31
	move	$3,$0

	j	$L26
	move	$2,$0

$L27:
	lw	$4,%lo(udp_cache_table)($16)
	lw	$5,0($4)
	addu	$5,$5,$2
	sw	$0,8($5)
	lw	$4,0($4)
	addu	$4,$4,$2
	sw	$0,0($4)
	lw	$4,%lo(udp_cache_table)($16)
	lw	$4,0($4)
	addu	$4,$4,$2
	addiu	$2,$2,12
	sw	$4,4($4)
$L26:
	slt	$4,$3,$19
	bne	$4,$0,$L27
	addiu	$3,$3,1

	lui	$23,%hi(cache_timeout)
	move	$18,$0
	lui	$22,%hi(init_timer_key)
	j	$L28
	addiu	$23,$23,%lo(cache_timeout)

$L29:
	lw	$4,24($20)
	jalr	$21
	addiu	$18,$18,1

	move	$5,$0
	move	$16,$2
	addiu	$4,$2,16
	move	$6,$0
	move	$7,$0
	beq	$16,$0,$L32
	addiu	$2,$22,%lo(init_timer_key)

	jalr	$2
	nop

	addiu	$3,$16,52
	lw	$2,4($17)
	sw	$16,36($16)
	sw	$2,56($16)
	sw	$23,32($16)
	sw	$0,52($16)
	sw	$16,0($2)
	lw	$2,8($17)
	sw	$3,4($17)
	addiu	$2,$2,1
	sw	$2,8($17)
$L28:
	slt	$2,$18,$19
	bne	$2,$0,$L29
	li	$5,32			# 0x20

	j	$L25
	li	$2,1			# 0x1

$L31:
	j	$L25
	li	$2,-1			# 0xffffffffffffffff

$L32:
	move	$2,$0
$L25:
	lw	$31,52($sp)
	lw	$23,48($sp)
	lw	$22,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,56

	.set	macro
	.set	reorder
	.end	udp_fragCache_init
	.size	udp_fragCache_init, .-udp_fragCache_init
	.align	2
	.globl	negative_fragCache_init
	.set	nomips16
	.ent	negative_fragCache_init
	.type	negative_fragCache_init, @function
negative_fragCache_init:
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
	lui	$20,%hi(kmalloc_caches)
	addiu	$20,$20,%lo(kmalloc_caches)
	lui	$19,%hi(kmem_cache_alloc)
	lw	$4,40($20)
	addiu	$19,$19,%lo(kmem_cache_alloc)
	jalr	$19
	li	$5,32			# 0x20

	lui	$3,%hi(negative_cache_table)
	beq	$2,$0,$L38
	sw	$2,%lo(negative_cache_table)($3)

	lui	$5,%hi(negative_cache_list_free)
	move	$4,$0
	addiu	$17,$5,%lo(negative_cache_list_free)
	li	$8,64			# 0x40
	sw	$0,8($17)
	sw	$0,%lo(negative_cache_list_free)($5)
	sw	$17,4($17)
$L35:
	sll	$5,$4,2
	lw	$6,%lo(negative_cache_table)($3)
	sll	$7,$4,4
	addiu	$4,$4,1
	subu	$5,$7,$5
	addu	$2,$2,$5
	addu	$6,$6,$5
	sw	$0,8($2)
	sw	$0,0($6)
	lw	$2,%lo(negative_cache_table)($3)
	addu	$5,$2,$5
	bne	$4,$8,$L35
	sw	$5,4($5)

	lui	$22,%hi(negative_cache_timeout)
	li	$18,64			# 0x40
	lui	$21,%hi(init_timer_key)
	addiu	$22,$22,%lo(negative_cache_timeout)
$L36:
	lw	$4,24($20)
	li	$5,32			# 0x20
	jalr	$19
	addiu	$18,$18,-1

	move	$5,$0
	move	$16,$2
	addiu	$4,$2,12
	move	$6,$0
	move	$7,$0
	beq	$16,$0,$L38
	addiu	$2,$21,%lo(init_timer_key)

	jalr	$2
	nop

	addiu	$3,$16,48
	lw	$2,4($17)
	sw	$16,32($16)
	sw	$2,52($16)
	sw	$22,28($16)
	sw	$0,48($16)
	sw	$16,0($2)
	lw	$2,8($17)
	sw	$3,4($17)
	addiu	$2,$2,1
	bne	$18,$0,$L36
	sw	$2,8($17)

	j	$L34
	li	$2,1			# 0x1

$L38:
	move	$2,$0
$L34:
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
	.end	negative_fragCache_init
	.size	negative_fragCache_init, .-negative_fragCache_init
	.align	2
	.globl	rtk_addArp
	.set	nomips16
	.ent	rtk_addArp
	.type	rtk_addArp, @function
rtk_addArp:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	rtk_addArp
	.size	rtk_addArp, .-rtk_addArp
	.align	2
	.globl	rtk_modifyArp
	.set	nomips16
	.ent	rtk_modifyArp
	.type	rtk_modifyArp, @function
rtk_modifyArp:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	rtk_modifyArp
	.size	rtk_modifyArp, .-rtk_modifyArp
	.align	2
	.globl	rtk_delArp
	.set	nomips16
	.ent	rtk_delArp
	.type	rtk_delArp, @function
rtk_delArp:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	li	$2,-4			# 0xfffffffffffffffc

	.set	macro
	.set	reorder
	.end	rtk_delArp
	.size	rtk_delArp, .-rtk_delArp
	.align	2
	.globl	rtk_addRoute
	.set	nomips16
	.ent	rtk_addRoute
	.type	rtk_addRoute, @function
rtk_addRoute:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	rtk_addRoute
	.size	rtk_addRoute, .-rtk_addRoute
	.align	2
	.globl	rtk_modifyRoute
	.set	nomips16
	.ent	rtk_modifyRoute
	.type	rtk_modifyRoute, @function
rtk_modifyRoute:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	rtk_modifyRoute
	.size	rtk_modifyRoute, .-rtk_modifyRoute
	.align	2
	.globl	rtk_delRoute
	.set	nomips16
	.ent	rtk_delRoute
	.type	rtk_delRoute, @function
rtk_delRoute:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	li	$2,-4			# 0xfffffffffffffffc

	.set	macro
	.set	reorder
	.end	rtk_delRoute
	.size	rtk_delRoute, .-rtk_delRoute
	.align	2
	.globl	rtk_addSession
	.set	nomips16
	.ent	rtk_addSession
	.type	rtk_addSession, @function
rtk_addSession:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	rtk_addSession
	.size	rtk_addSession, .-rtk_addSession
	.align	2
	.globl	rtk_delSession
	.set	nomips16
	.ent	rtk_delSession
	.type	rtk_delSession, @function
rtk_delSession:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	rtk_delSession
	.size	rtk_delSession, .-rtk_delSession
	.align	2
	.globl	set_bypass_connmark
	.set	nomips16
	.ent	set_bypass_connmark
	.type	set_bypass_connmark, @function
set_bypass_connmark:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	li	$2,1			# 0x1
	j	$31
	sw	$2,136($4)

	.set	macro
	.set	reorder
	.end	set_bypass_connmark
	.size	set_bypass_connmark, .-set_bypass_connmark
	.align	2
	.globl	reset_bypass_connmark
	.set	nomips16
	.ent	reset_bypass_connmark
	.type	reset_bypass_connmark, @function
reset_bypass_connmark:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$31
	sw	$0,136($4)

	.set	macro
	.set	reorder
	.end	reset_bypass_connmark
	.size	reset_bypass_connmark, .-reset_bypass_connmark
	.align	2
	.globl	rtk_delNaptConnection
	.set	nomips16
	.ent	rtk_delNaptConnection
	.type	rtk_delNaptConnection, @function
rtk_delNaptConnection:
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
	li	$2,17			# 0x11
	lw	$3,0($4)
	li	$18,6			# 0x6
	xori	$3,$3,0x2
	movn	$18,$2,$3
	lui	$2,%hi(arch_local_irq_save)
	addiu	$2,$2,%lo(arch_local_irq_save)
	jalr	$2
	move	$16,$4

	move	$17,$2
	lw	$4,20($16)
	lui	$2,%hi(filter_delconnect)
	addiu	$2,$2,%lo(filter_delconnect)
	jalr	$2
	nop

	lui	$8,%hi(napt_table_list_max)
	lw	$5,4($16)
	lw	$6,8($16)
	lw	$7,20($16)
	srl	$2,$5,16
	lw	$10,24($16)
	xor	$3,$6,$5
	xor	$3,$3,$7
	lw	$4,0($16)
	xor	$3,$3,$10
	lw	$8,%lo(napt_table_list_max)($8)
	xor	$3,$3,$2
	lui	$2,%hi(table_napt)
	srl	$11,$7,16
	lw	$9,%lo(table_napt)($2)
	xor	$3,$3,$11
	addiu	$8,$8,-1
	andi	$2,$4,0xffff
	lw	$11,0($9)
	xor	$3,$3,$2
	srl	$2,$3,12
	xor	$2,$2,$3
	and	$2,$2,$8
	sll	$3,$2,2
	sll	$2,$2,4
	subu	$8,$2,$3
	addu	$2,$11,$8
	lw	$2,0($2)
	j	$L53
	nop

$L77:
	lw	$3,4($2)
	bne	$4,$3,$L54
	nop

	lw	$3,8($2)
	bne	$5,$3,$L54
	nop

	lw	$3,12($2)
	bne	$6,$3,$L54
	nop

	lw	$11,16($2)
	lw	$3,12($16)
	bne	$11,$3,$L54
	nop

	lw	$11,20($2)
	lw	$3,16($16)
	bne	$11,$3,$L54
	nop

	lw	$3,24($2)
	bne	$7,$3,$L54
	nop

	lw	$3,28($2)
	bne	$10,$3,$L54
	nop

	lw	$3,36($2)
	beq	$3,$0,$L55
	sb	$0,0($2)

	lw	$4,40($2)
	j	$L56
	sw	$4,40($3)

$L55:
	lw	$3,0($9)
	lw	$4,40($2)
	addu	$3,$3,$8
	sw	$4,4($3)
$L56:
	lw	$3,40($2)
	lw	$4,36($2)
	sw	$4,0($3)
	lw	$3,0($9)
	addu	$8,$3,$8
	lw	$3,8($8)
	addiu	$3,$3,-1
	sw	$3,8($8)
	lw	$3,44($2)
	beq	$3,$0,$L57
	nop

	lw	$4,48($2)
	lui	$5,%hi(napt_list_inuse)
	sw	$4,48($3)
	lw	$3,48($2)
	lw	$4,44($2)
	j	$L58
	addiu	$5,$5,%lo(napt_list_inuse)

$L57:
	lw	$3,48($2)
	lui	$5,%hi(napt_list_inuse)
	addiu	$5,$5,%lo(napt_list_inuse)
	move	$4,$0
	sw	$3,4($5)
$L58:
	sw	$4,0($3)
	lui	$3,%hi(napt_list_free)
	addiu	$3,$3,%lo(napt_list_free)
	addiu	$7,$2,44
	lw	$8,8($5)
	lui	$4,%hi(table_path)
	lw	$6,4($3)
	addiu	$8,$8,-1
	sw	$6,48($2)
	sw	$0,44($2)
	sw	$8,8($5)
	sw	$2,0($6)
	lw	$2,8($3)
	sw	$7,4($3)
	lui	$7,%hi(path_table_list_max)
	addiu	$2,$2,1
	sw	$2,8($3)
	lw	$10,4($16)
	lw	$3,20($16)
	lw	$5,24($16)
	srl	$6,$10,8
	xor	$2,$3,$10
	lw	$12,8($16)
	xor	$2,$2,$5
	lw	$11,%lo(path_table_list_max)($7)
	xor	$2,$2,$6
	lw	$6,%lo(table_path)($4)
	srl	$7,$3,16
	addiu	$11,$11,-1
	xor	$7,$2,$7
	lw	$9,0($6)
	srl	$2,$12,4
	lw	$6,12($16)
	xor	$2,$7,$2
	lw	$7,16($16)
	xor	$2,$2,$18
	srl	$8,$2,12
	xor	$2,$8,$2
	and	$2,$2,$11
	sll	$8,$2,2
	sll	$2,$2,4
	subu	$8,$2,$8
	addu	$2,$9,$8
	lw	$2,0($2)
	j	$L59
	li	$13,1			# 0x1

$L66:
	lw	$15,4($2)
	lw	$14,0($16)
	bne	$15,$14,$L60
	nop

	lbu	$14,2($2)
	bne	$14,$13,$L60
	nop

	lw	$14,16($2)
	bne	$10,$14,$L60
	nop

	lw	$14,12($2)
	bne	$12,$14,$L60
	nop

	lw	$14,24($2)
	bne	$14,$6,$L60
	nop

	lw	$14,28($2)
	bne	$14,$7,$L60
	nop

	lw	$14,20($2)
	bne	$3,$14,$L60
	nop

	lw	$14,8($2)
	bne	$5,$14,$L60
	nop

	lw	$3,64($2)
	beq	$3,$0,$L61
	sb	$0,0($2)

	lw	$5,68($2)
	j	$L62
	sw	$5,68($3)

$L61:
	lw	$3,%lo(table_path)($4)
	lw	$5,68($2)
	lw	$3,0($3)
	addu	$3,$3,$8
	sw	$5,4($3)
$L62:
	lw	$3,68($2)
	lw	$5,64($2)
	sw	$5,0($3)
	lw	$3,%lo(table_path)($4)
	lw	$3,0($3)
	addu	$8,$3,$8
	lw	$3,8($8)
	addiu	$3,$3,-1
	sw	$3,8($8)
	lw	$5,72($2)
	beq	$5,$0,$L63
	nop

	lw	$6,76($2)
	lui	$3,%hi(path_list_inuse)
	sw	$6,76($5)
	lw	$5,76($2)
	lw	$6,72($2)
	j	$L64
	addiu	$3,$3,%lo(path_list_inuse)

$L63:
	lw	$5,76($2)
	lui	$3,%hi(path_list_inuse)
	addiu	$3,$3,%lo(path_list_inuse)
	move	$6,$0
	sw	$5,4($3)
$L64:
	sw	$6,0($5)
	lui	$5,%hi(path_list_free)
	addiu	$5,$5,%lo(path_list_free)
	addiu	$7,$2,72
	lw	$8,8($3)
	lw	$6,4($5)
	addiu	$8,$8,-1
	sw	$0,72($2)
	sw	$6,76($2)
	sw	$8,8($3)
	sw	$2,0($6)
	lw	$3,8($5)
	lw	$2,%lo(table_path)($4)
	addiu	$3,$3,1
	sw	$7,4($5)
	sw	$3,8($5)
	lw	$9,0($2)
	lw	$3,20($16)
	lw	$5,24($16)
	lw	$6,12($16)
	lw	$7,16($16)
	j	$L80
	xor	$8,$3,$6

$L60:
	lw	$2,64($2)
$L59:
	bne	$2,$0,$L66
	nop

	xor	$8,$3,$6
$L80:
	xor	$8,$8,$18
	srl	$2,$3,8
	xor	$8,$8,$7
	xor	$8,$8,$2
	srl	$2,$6,16
	xor	$8,$8,$2
	srl	$2,$5,4
	xor	$2,$8,$2
	srl	$8,$2,12
	xor	$2,$8,$2
	and	$2,$2,$11
	sll	$8,$2,2
	sll	$2,$2,4
	subu	$8,$2,$8
	addu	$9,$9,$8
	lw	$2,0($9)
	j	$L67
	li	$10,2			# 0x2

$L74:
	lw	$11,4($2)
	lw	$9,0($16)
	bne	$11,$9,$L68
	nop

	lbu	$9,2($2)
	bne	$9,$10,$L68
	nop

	lw	$9,20($2)
	bne	$9,$6,$L68
	nop

	lw	$9,8($2)
	bne	$9,$7,$L68
	nop

	lw	$9,24($2)
	bne	$9,$3,$L68
	nop

	lw	$9,28($2)
	bne	$9,$5,$L68
	nop

	lw	$11,32($2)
	lw	$9,4($16)
	bne	$11,$9,$L68
	nop

	lw	$11,36($2)
	lw	$9,8($16)
	bne	$11,$9,$L68
	nop

	lw	$3,64($2)
	beq	$3,$0,$L69
	sb	$0,0($2)

	lw	$5,68($2)
	j	$L70
	sw	$5,68($3)

$L69:
	lw	$3,%lo(table_path)($4)
	lw	$5,68($2)
	lw	$3,0($3)
	addu	$3,$3,$8
	sw	$5,4($3)
$L70:
	lw	$3,68($2)
	lw	$5,64($2)
	sw	$5,0($3)
	lw	$3,%lo(table_path)($4)
	lw	$3,0($3)
	addu	$8,$3,$8
	lw	$3,8($8)
	addiu	$3,$3,-1
	sw	$3,8($8)
	lw	$4,72($2)
	beq	$4,$0,$L71
	lui	$3,%hi(path_list_inuse)

	lw	$5,76($2)
	sw	$5,76($4)
	lw	$4,76($2)
	lw	$5,72($2)
	j	$L72
	addiu	$3,$3,%lo(path_list_inuse)

$L71:
	lw	$4,76($2)
	addiu	$3,$3,%lo(path_list_inuse)
	move	$5,$0
	sw	$4,4($3)
$L72:
	sw	$5,0($4)
	lui	$4,%hi(path_list_free)
	addiu	$4,$4,%lo(path_list_free)
	addiu	$6,$2,72
	lw	$7,8($3)
	lw	$5,4($4)
	addiu	$7,$7,-1
	sw	$0,72($2)
	sw	$5,76($2)
	sw	$7,8($3)
	sw	$2,0($5)
	lw	$2,8($4)
	sw	$6,4($4)
	addiu	$2,$2,1
	j	$L73
	sw	$2,8($4)

$L68:
	lw	$2,64($2)
$L67:
	bne	$2,$0,$L74
	nop

$L73:
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$2,$2,%lo(arch_local_irq_restore)
	jalr	$2
	move	$4,$17

	j	$L76
	move	$2,$0

$L54:
	lw	$2,36($2)
$L53:
	bne	$2,$0,$L77
	nop

	lui	$2,%hi(arch_local_irq_restore)
	addiu	$2,$2,%lo(arch_local_irq_restore)
	jalr	$2
	move	$4,$17

	li	$2,-4			# 0xfffffffffffffffc
$L76:
	lw	$31,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	rtk_delNaptConnection
	.size	rtk_delNaptConnection, .-rtk_delNaptConnection
	.align	2
	.globl	rtk_idleNaptConnection
	.set	nomips16
	.ent	rtk_idleNaptConnection
	.type	rtk_idleNaptConnection, @function
rtk_idleNaptConnection:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	li	$7,6			# 0x6
	lw	$9,4($4)
	li	$13,-16777216			# 0xffffffffff000000
	lw	$6,20($4)
	lw	$10,24($4)
	srl	$8,$9,8
	xor	$3,$6,$9
	lw	$2,0($4)
	xor	$3,$3,$10
	lw	$14,8($4)
	xor	$3,$3,$8
	lui	$8,%hi(path_table_list_max)
	lw	$12,%lo(path_table_list_max)($8)
	srl	$8,$6,16
	xori	$11,$2,0x2
	xor	$3,$3,$8
	li	$8,17			# 0x11
	movn	$7,$8,$11
	srl	$11,$14,4
	lui	$8,%hi(table_path)
	xor	$3,$3,$11
	lw	$8,%lo(table_path)($8)
	xor	$3,$3,$7
	addiu	$12,$12,-1
	lw	$11,0($8)
	srl	$8,$3,12
	xor	$3,$8,$3
	lui	$8,%hi(jiffies)
	and	$3,$3,$12
	lw	$25,%lo(jiffies)($8)
	sll	$15,$3,2
	lw	$8,12($4)
	sll	$24,$3,4
	lw	$4,16($4)
	subu	$15,$24,$15
	addiu	$3,$13,256
	addu	$15,$11,$15
	lw	$15,0($15)
	j	$L83
	ori	$13,$13,0xff00

$L87:
	lw	$24,4($15)
	bne	$2,$24,$L84
	nop

	lw	$24,0($15)
	and	$24,$24,$13
	bne	$24,$3,$L84
	nop

	lw	$24,16($15)
	bne	$9,$24,$L84
	nop

	lw	$24,12($15)
	bne	$14,$24,$L84
	nop

	lw	$24,24($15)
	bne	$24,$8,$L84
	nop

	lw	$24,28($15)
	bne	$24,$4,$L84
	nop

	lw	$24,20($15)
	bne	$6,$24,$L84
	nop

	lw	$24,8($15)
	bne	$10,$24,$L84
	nop

	lw	$3,40($15)
	subu	$13,$25,$5
	subu	$13,$13,$3
	bgez	$13,$L85
	nop

	lw	$4,56($15)
	lui	$2,%hi(rtl_set_ct_timeout_expires)
	addiu	$2,$2,%lo(rtl_set_ct_timeout_expires)
	jalr	$2
	addu	$5,$5,$3

	j	$L86
	li	$2,-1			# 0xffffffffffffffff

$L84:
	lw	$15,64($15)
$L83:
	bne	$15,$0,$L87
	nop

$L85:
	xor	$3,$8,$6
	li	$13,-16777216			# 0xffffffffff000000
	srl	$24,$6,8
	addiu	$15,$13,512
	xor	$3,$3,$4
	xor	$3,$3,$24
	srl	$24,$8,16
	xor	$3,$3,$24
	srl	$24,$10,4
	xor	$3,$3,$24
	xor	$7,$3,$7
	srl	$3,$7,12
	xor	$7,$3,$7
	and	$12,$7,$12
	sll	$3,$12,2
	sll	$12,$12,4
	subu	$12,$12,$3
	addu	$11,$11,$12
	lw	$3,0($11)
	j	$L88
	ori	$13,$13,0xff00

$L90:
	lw	$7,4($3)
	bne	$2,$7,$L89
	nop

	lw	$7,0($3)
	and	$7,$7,$13
	bne	$7,$15,$L89
	nop

	lw	$7,20($3)
	bne	$7,$8,$L89
	nop

	lw	$7,8($3)
	bne	$7,$4,$L89
	nop

	lw	$7,24($3)
	bne	$6,$7,$L89
	nop

	lw	$7,28($3)
	bne	$10,$7,$L89
	nop

	lw	$7,32($3)
	bne	$9,$7,$L89
	nop

	lw	$7,36($3)
	bne	$14,$7,$L89
	nop

	lw	$2,40($3)
	subu	$25,$25,$5
	subu	$25,$25,$2
	bgez	$25,$L92
	nop

	addu	$5,$5,$2
	lui	$2,%hi(rtl_set_ct_timeout_expires)
	lw	$4,56($3)
	addiu	$2,$2,%lo(rtl_set_ct_timeout_expires)
	jalr	$2
	nop

	j	$L86
	li	$2,-1			# 0xffffffffffffffff

$L89:
	lw	$3,64($3)
$L88:
	bne	$3,$0,$L90
	nop

$L92:
	move	$2,$0
$L86:
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	rtk_idleNaptConnection
	.size	rtk_idleNaptConnection, .-rtk_idleNaptConnection
	.align	2
	.globl	rtl_fpTimer_update
	.set	nomips16
	.ent	rtl_fpTimer_update
	.type	rtl_fpTimer_update, @function
rtl_fpTimer_update:
	.frame	$sp,80,$31		# vars= 32, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-80
	sw	$31,76($sp)
	sw	$21,72($sp)
	sw	$20,68($sp)
	sw	$19,64($sp)
	sw	$18,60($sp)
	sw	$17,56($sp)
	sw	$16,52($sp)
	lui	$16,%hi(rtl_get_ct_protonum)
	lui	$2,%hi(jiffies)
	move	$5,$0
	addiu	$16,$16,%lo(rtl_get_ct_protonum)
	move	$17,$4
	lw	$21,%lo(jiffies)($2)
	jalr	$16
	nop

	li	$3,17			# 0x11
	bne	$2,$3,$L94
	move	$4,$17

	lui	$2,%hi(rtl_get_ct_udp_status)
	addiu	$2,$2,%lo(rtl_get_ct_udp_status)
	jalr	$2
	nop

	andi	$2,$2,0x2
	beq	$2,$0,$L95
	nop

	j	$L105
	li	$4,1			# 0x1

$L95:
	move	$4,$0
$L105:
	lui	$2,%hi(udp_get_timeouts_by_state)
	move	$5,$17
	addiu	$2,$2,%lo(udp_get_timeouts_by_state)
	jalr	$2
	li	$6,1			# 0x1

	li	$19,1			# 0x1
	j	$L96
	move	$20,$2

$L94:
	jalr	$16
	move	$5,$0

	li	$3,6			# 0x6
	bne	$2,$3,$L104
	lui	$2,%hi(rtl_get_ct_tcp_state)

	addiu	$2,$2,%lo(rtl_get_ct_tcp_state)
	jalr	$2
	move	$4,$17

	sltu	$2,$2,6
	beq	$2,$0,$L104
	lui	$2,%hi(rtl_tcp_get_timeouts)

	move	$4,$17
	addiu	$2,$2,%lo(rtl_tcp_get_timeouts)
	jalr	$2
	li	$19,2			# 0x2

	move	$20,$2
$L96:
	lui	$18,%hi(rtl_get_ct_ip_by_dir)
	move	$5,$0
	move	$6,$0
	addiu	$18,$18,%lo(rtl_get_ct_ip_by_dir)
	jalr	$18
	move	$4,$17

	move	$4,$17
	li	$5,1			# 0x1
	li	$6,1			# 0x1
	jalr	$18
	move	$16,$2

	bne	$16,$2,$L98
	li	$6,1			# 0x1

	move	$4,$17
	li	$5,1			# 0x1
	move	$6,$0
	lui	$16,%hi(rtl_get_ct_port_by_dir)
	sw	$19,16($sp)
	jalr	$18
	addiu	$16,$16,%lo(rtl_get_ct_port_by_dir)

	move	$4,$17
	li	$5,1			# 0x1
	move	$6,$0
	jalr	$16
	sw	$2,20($sp)

	move	$4,$17
	move	$5,$0
	li	$6,1			# 0x1
	jalr	$18
	sw	$2,24($sp)

	move	$4,$17
	move	$5,$0
	li	$6,1			# 0x1
	jalr	$16
	sw	$2,28($sp)

	move	$4,$17
	move	$5,$0
	move	$6,$0
	jalr	$18
	sw	$2,32($sp)

	move	$4,$17
	j	$L108
	move	$5,$0

$L98:
	move	$5,$0
	jalr	$18
	move	$4,$17

	move	$4,$17
	li	$5,1			# 0x1
	move	$6,$0
	jalr	$18
	move	$16,$2

	bne	$16,$2,$L97
	li	$2,-1			# 0xffffffffffffffff

	move	$4,$17
	move	$5,$0
	move	$6,$0
	lui	$16,%hi(rtl_get_ct_port_by_dir)
	sw	$19,16($sp)
	jalr	$18
	addiu	$16,$16,%lo(rtl_get_ct_port_by_dir)

	move	$4,$17
	move	$5,$0
	move	$6,$0
	jalr	$16
	sw	$2,20($sp)

	move	$4,$17
	li	$5,1			# 0x1
	li	$6,1			# 0x1
	jalr	$18
	sw	$2,24($sp)

	move	$4,$17
	li	$5,1			# 0x1
	li	$6,1			# 0x1
	jalr	$16
	sw	$2,28($sp)

	move	$4,$17
	li	$5,1			# 0x1
	move	$6,$0
	jalr	$18
	sw	$2,32($sp)

	move	$4,$17
	li	$5,1			# 0x1
$L108:
	move	$6,$0
	jalr	$16
	sw	$2,36($sp)

	lui	$3,%hi(FastPath_hook11)
	lw	$3,%lo(FastPath_hook11)($3)
	beq	$3,$0,$L104
	sw	$2,40($sp)

	addiu	$4,$sp,16
	jalr	$3
	move	$5,$20

	bne	$2,$0,$L99
	lui	$2,%hi(rtl_check_for_acc)

$L104:
	li	$2,-1			# 0xffffffffffffffff
$L97:
	lw	$31,76($sp)
	lw	$21,72($sp)
	lw	$20,68($sp)
	lw	$19,64($sp)
	lw	$18,60($sp)
	lw	$17,56($sp)
	lw	$16,52($sp)
	j	$31
	addiu	$sp,$sp,80

$L99:
	move	$4,$17
	addiu	$2,$2,%lo(rtl_check_for_acc)
	jalr	$2
	addu	$5,$20,$21

	j	$L97
	move	$2,$0

	.set	macro
	.set	reorder
	.end	rtl_fpTimer_update
	.size	rtl_fpTimer_update, .-rtl_fpTimer_update
	.align	2
	.globl	rtl_br_fdb_time_update
	.set	nomips16
	.ent	rtl_br_fdb_time_update
	.type	rtl_br_fdb_time_update, @function
rtl_br_fdb_time_update:
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
	lui	$2,%hi(rtl_get_hw_fdb_age)
	move	$18,$4
	addiu	$2,$2,%lo(rtl_get_hw_fdb_age)
	move	$16,$5
	move	$4,$0
	move	$5,$6
	jalr	$2
	li	$6,2			# 0x2

	li	$3,300			# 0x12c
	beq	$2,$3,$L112
	li	$3,450			# 0x1c2

	beq	$2,$3,$L113
	li	$3,150			# 0x96

	bne	$2,$3,$L110
	lui	$17,%hi(jiffies)

	j	$L116
	nop

$L113:
	lui	$17,%hi(jiffies)
	lui	$2,%hi(rtl_set_fdb_aging)
	lw	$5,%lo(jiffies)($17)
	addiu	$2,$2,%lo(rtl_set_fdb_aging)
	jalr	$2
	move	$4,$16

	j	$L117
	lui	$2,%hi(rtl_get_fdb_aging)

$L112:
	lui	$17,%hi(jiffies)
	lui	$2,%hi(rtl_set_fdb_aging)
	lw	$5,%lo(jiffies)($17)
	move	$4,$16
	addiu	$2,$2,%lo(rtl_set_fdb_aging)
	jalr	$2
	addiu	$5,$5,-15000

	j	$L117
	lui	$2,%hi(rtl_get_fdb_aging)

$L116:
	lw	$5,%lo(jiffies)($17)
	lui	$2,%hi(rtl_set_fdb_aging)
	move	$4,$16
	addiu	$2,$2,%lo(rtl_set_fdb_aging)
	jalr	$2
	addiu	$5,$5,-30000

$L110:
	lui	$2,%hi(rtl_get_fdb_aging)
$L117:
	move	$4,$16
	addiu	$2,$2,%lo(rtl_get_fdb_aging)
	lw	$17,%lo(jiffies)($17)
	jalr	$2
	nop

	move	$16,$2
	lui	$2,%hi(rtl_hold_time)
	addiu	$2,$2,%lo(rtl_hold_time)
	jalr	$2
	move	$4,$18

	li	$3,-1			# 0xffffffffffffffff
	addu	$16,$2,$16
	subu	$17,$17,$16
	slt	$17,$17,0
	lw	$31,28($sp)
	movn	$3,$0,$17
	lw	$18,24($sp)
	move	$2,$3
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	rtl_br_fdb_time_update
	.size	rtl_br_fdb_time_update, .-rtl_br_fdb_time_update
	.align	2
	.globl	FastPath_Route
	.set	nomips16
	.ent	FastPath_Route
	.type	FastPath_Route, @function
FastPath_Route:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$2,%hi(route_list_inuse)
	move	$8,$0
	lw	$3,%lo(route_list_inuse)($2)
	j	$L119
	move	$2,$0

$L121:
	lw	$5,8($3)
	sltu	$6,$5,$8
	bne	$6,$0,$L120
	and	$7,$4,$5

	lw	$6,4($3)
	bne	$7,$6,$L120
	nop

	addiu	$2,$3,16
	move	$8,$5
$L120:
	lw	$3,44($3)
$L119:
	bne	$3,$0,$L121
	nop

	j	$31
	nop

	.set	macro
	.set	reorder
	.end	FastPath_Route
	.size	FastPath_Route, .-FastPath_Route
	.align	2
	.globl	rtk_addNaptConnection
	.set	nomips16
	.ent	rtk_addNaptConnection
	.type	rtk_addNaptConnection, @function
rtk_addNaptConnection:
	.frame	$sp,176,$31		# vars= 120, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-176
	sw	$31,172($sp)
	sw	$fp,168($sp)
	sw	$23,164($sp)
	sw	$22,160($sp)
	sw	$21,156($sp)
	sw	$20,152($sp)
	sw	$19,148($sp)
	sw	$18,144($sp)
	sw	$17,140($sp)
	sw	$16,136($sp)
	move	$18,$5
	move	$16,$4
	sw	$6,184($sp)
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L162
	move	$17,$7
	.set	macro
	.set	reorder

	lui	$23,%hi(rtl_eth_hdr)
	addiu	$23,$23,%lo(rtl_eth_hdr)
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$5
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L162
	li	$2,17			# 0x11
	.set	macro
	.set	reorder

	lw	$3,0($16)
	li	$22,6			# 0x6
	xori	$3,$3,0x2
	lw	$4,20($16)
	movn	$22,$2,$3
	lui	$2,%hi(filter_addconnect)
	addiu	$2,$2,%lo(filter_addconnect)
	jalr	$2
	lui	$3,%hi(arch_local_irq_save)
	addiu	$3,$3,%lo(arch_local_irq_save)
	jalr	$3
	lui	$6,%hi(napt_table_list_max)
	lw	$5,4($16)
	lw	$8,8($16)
	lw	$9,20($16)
	lw	$10,24($16)
	xor	$3,$8,$5
	xor	$3,$3,$9
	sw	$2,88($sp)
	lw	$4,0($16)
	srl	$2,$5,16
	xor	$3,$3,$10
	lw	$6,%lo(napt_table_list_max)($6)
	xor	$3,$3,$2
	lui	$2,%hi(table_napt)
	srl	$11,$9,16
	lw	$7,%lo(table_napt)($2)
	xor	$3,$3,$11
	addiu	$6,$6,-1
	andi	$2,$4,0xffff
	lw	$11,0($7)
	xor	$3,$3,$2
	srl	$2,$3,12
	xor	$2,$2,$3
	and	$2,$2,$6
	sll	$3,$2,2
	sll	$6,$2,4
	subu	$6,$6,$3
	addu	$2,$11,$6
	lw	$2,0($2)
	j	$L125
$L128:
	lw	$3,4($2)
	bne	$4,$3,$L126
	lw	$3,8($2)
	bne	$5,$3,$L126
	lw	$3,12($2)
	bne	$8,$3,$L126
	lw	$11,16($2)
	lw	$3,12($16)
	bne	$11,$3,$L126
	lw	$11,20($2)
	lw	$3,16($16)
	bne	$11,$3,$L126
	lw	$3,24($2)
	bne	$9,$3,$L126
	lw	$3,28($2)
	bne	$10,$3,$L126
	lw	$4,184($sp)
	lui	$2,%hi(rtl_conntrack_drop_check_hook)
	addiu	$2,$2,%lo(rtl_conntrack_drop_check_hook)
	move	$5,$22
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$6,$4
	.set	macro
	.set	reorder

	lw	$4,88($sp)
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$2,$2,%lo(arch_local_irq_restore)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L123
	move	$2,$0
	.set	macro
	.set	reorder

$L126:
	lw	$2,36($2)
$L125:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L128
	lui	$3,%hi(napt_list_free)
	.set	macro
	.set	reorder

	lw	$2,%lo(napt_list_free)($3)
	beq	$2,$0,$L129
	sw	$4,4($2)
	lw	$4,4($16)
	lw	$5,44($2)
	sw	$4,8($2)
	lw	$4,8($16)
	sw	$4,12($2)
	lw	$4,12($16)
	sw	$4,16($2)
	lw	$4,16($16)
	sw	$4,20($2)
	lw	$4,20($16)
	sw	$4,24($2)
	lw	$4,24($16)
	sw	$17,32($2)
	sw	$4,28($2)
	li	$4,-1			# 0xffffffffffffffff
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L130
	sb	$4,0($2)
	.set	macro
	.set	reorder

	lw	$8,48($2)
	addiu	$4,$3,%lo(napt_list_free)
	sw	$8,48($5)
	lw	$5,48($2)
	lw	$3,44($2)
	.set	noreorder
	.set	nomacro
	j	$L168
	sw	$3,0($5)
	.set	macro
	.set	reorder

$L130:
	lw	$5,48($2)
	addiu	$4,$3,%lo(napt_list_free)
	move	$3,$0
	sw	$5,4($4)
	sw	$3,0($5)
$L168:
	lui	$3,%hi(napt_list_inuse)
	lw	$10,8($4)
	addiu	$3,$3,%lo(napt_list_inuse)
	lw	$5,4($3)
	addiu	$9,$2,44
	addiu	$10,$10,-1
	addiu	$8,$2,36
	sw	$10,8($4)
	sw	$5,48($2)
	sw	$0,44($2)
	sw	$2,0($5)
	lw	$4,8($3)
	sw	$9,4($3)
	addiu	$4,$4,1
	sw	$0,36($2)
	sw	$4,8($3)
	lw	$3,0($7)
	addu	$3,$3,$6
	lw	$3,4($3)
	sw	$3,40($2)
	lw	$3,0($7)
	addu	$3,$3,$6
	lw	$3,4($3)
	sw	$2,0($3)
	li	$3,33			# 0x21
	lw	$2,0($7)
	addu	$2,$2,$6
	sw	$8,4($2)
	lw	$2,0($7)
	sb	$3,17($sp)
	addu	$6,$2,$6
	lw	$2,8($6)
	sb	$0,16($sp)
	addiu	$2,$2,1
	sw	$2,8($6)
	lui	$2,%hi(rtl865x_getLanDev)
	addiu	$2,$2,%lo(rtl865x_getLanDev)
	jalr	$2
	sw	$2,64($sp)
	lui	$2,%hi(rtl865x_getWanDev)
	addiu	$2,$2,%lo(rtl865x_getWanDev)
	jalr	$2
	sw	$2,92($sp)
	lui	$2,%hi(rtl_get_skb_protocol)
	addiu	$2,$2,%lo(rtl_get_skb_protocol)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	sw	$2,132($sp)
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	move	$4,$18
	lbu	$21,0($2)
	move	$19,$2
	andi	$21,$21,0xf
	sll	$21,$21,2
	.set	noreorder
	.set	nomacro
	jalr	$23
	addu	$21,$2,$21
	.set	macro
	.set	reorder

	lui	$7,%hi(memcpy)
	addiu	$7,$7,%lo(memcpy)
	addiu	$5,$2,6
	li	$6,6			# 0x6
	.set	noreorder
	.set	nomacro
	jalr	$7
	addiu	$4,$sp,28
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$3,%hi(memcpy)
	li	$6,6			# 0x6
	addiu	$4,$sp,20
	addiu	$3,$3,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$3
	move	$5,$2
	.set	macro
	.set	reorder

	lui	$5,%hi(rtl_get_skb_mark)
	addiu	$5,$5,%lo(rtl_get_skb_mark)
	.set	noreorder
	.set	nomacro
	jalr	$5
	move	$4,$18
	.set	macro
	.set	reorder

	sw	$2,100($sp)
	lw	$7,12($19)
	lhu	$2,0($21)
	lw	$3,16($19)
	lhu	$4,2($21)
	sw	$7,104($sp)
	sw	$2,108($sp)
	sw	$3,112($sp)
	sw	$4,116($sp)
	lui	$2,%hi(rtl_store_skb_dst)
	addiu	$2,$2,%lo(rtl_store_skb_dst)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$2,%hi(dst_tmp)
	lw	$2,%lo(dst_tmp)($2)
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L171
	lui	$5,%hi(path_table_list_max)
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_ip_route_input)
	lw	$5,16($19)
	addiu	$2,$2,%lo(rtl_ip_route_input)
	lw	$6,12($19)
	lbu	$7,1($19)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L162
	lui	$5,%hi(path_table_list_max)
	.set	macro
	.set	reorder

$L171:
	lui	$7,%hi(path_list_free)
	lw	$6,%lo(path_table_list_max)($5)
	lw	$2,8($16)
	lw	$3,20($16)
	addiu	$6,$6,-1
	lw	$4,24($16)
	lw	$17,%lo(path_list_free)($7)
	lw	$fp,4($16)
	sw	$6,84($sp)
	sw	$2,76($sp)
	sw	$3,68($sp)
	.set	noreorder
	.set	nomacro
	bne	$17,$0,$L165
	sw	$4,80($sp)
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_mark)
	addiu	$2,$2,%lo(rtl_set_skb_mark)
	.set	noreorder
	.set	nomacro
	j	$L133
	sw	$2,60($sp)
	.set	macro
	.set	reorder

$L165:
	lw	$2,0($16)
	lui	$3,%hi(FastPath_Route)
	addiu	$3,$3,%lo(FastPath_Route)
	sw	$2,4($17)
	lw	$20,4($16)
	sw	$20,16($17)
	lw	$5,8($16)
	sw	$5,12($17)
	lw	$2,20($16)
	sw	$5,56($sp)
	sw	$2,20($17)
	lw	$2,24($16)
	sw	$2,8($17)
	lw	$7,12($16)
	sw	$7,24($17)
	lw	$2,16($16)
	sw	$7,60($sp)
	sw	$2,28($17)
	lw	$4,20($16)
	sw	$2,72($sp)
	sw	$4,32($17)
	lw	$2,24($16)
	.set	noreorder
	.set	nomacro
	jalr	$3
	sw	$2,36($17)
	.set	macro
	.set	reorder

	li	$3,1			# 0x1
	lw	$4,60($sp)
	sw	$2,44($17)
	li	$2,-1			# 0xffffffffffffffff
	sb	$3,2($17)
	sb	$2,0($17)
	.set	noreorder
	.set	nomacro
	beq	$20,$4,$L134
	sb	$0,1($17)
	.set	macro
	.set	reorder

	sb	$3,1($17)
$L134:
	lw	$5,56($sp)
	lw	$7,72($sp)
	beq	$5,$7,$L135
	lbu	$2,1($17)
	ori	$2,$2,0x2
	sb	$2,1($17)
$L135:
	sw	$0,48($17)
	lui	$3,%hi(memset)
	sw	$0,52($17)
	move	$5,$0
	lw	$2,4($16)
	addiu	$4,$sp,36
	li	$6,14			# 0xe
	addiu	$3,$3,%lo(memset)
	sw	$2,12($19)
	lw	$2,8($16)
	sh	$2,0($21)
	lw	$2,20($16)
	sw	$2,16($19)
	lw	$2,24($16)
	.set	noreorder
	.set	nomacro
	jalr	$3
	sh	$2,2($21)
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_mark)
	addiu	$2,$2,%lo(rtl_set_skb_mark)
	move	$4,$18
	move	$5,$0
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$2,60($sp)
	.set	macro
	.set	reorder

	lw	$4,64($sp)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L136
	move	$5,$4
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_arp_req_get_ha)
	lw	$4,4($16)
	addiu	$2,$2,%lo(rtl_arp_req_get_ha)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$6,$sp,36
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L172
	li	$2,6			# 0x6
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_ppp_proto_check)
	move	$4,$18
	addiu	$2,$2,%lo(rtl_ppp_proto_check)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$5,$sp,16
	.set	macro
	.set	reorder

	move	$20,$2
	li	$2,1			# 0x1
	.set	noreorder
	.set	nomacro
	bne	$20,$2,$L137
	lui	$2,%hi(rtl_skb_mac_header_was_set)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_skb_mac_header_was_set)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	bne	$2,$20,$L137
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$18
	.set	macro
	.set	reorder

	lbu	$3,12($2)
	lbu	$2,13($2)
	sll	$3,$3,8
	or	$3,$2,$3
	li	$2,2048			# 0x800
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L137
	lui	$2,%hi(rtl_skb_set_mac_header)
	.set	macro
	.set	reorder

	move	$4,$18
	addiu	$2,$2,%lo(rtl_skb_set_mac_header)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,-22			# 0xffffffffffffffea
	.set	macro
	.set	reorder

$L137:
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$7,%hi(memcpy)
	li	$6,6			# 0x6
	addiu	$4,$2,6
	addiu	$7,$7,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$7
	addiu	$5,$sp,36
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_dmac)
	lw	$5,64($sp)
	addiu	$2,$2,%lo(rtl_set_skb_dmac)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	li	$2,2048			# 0x800
	lw	$3,132($sp)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L172
	li	$2,6			# 0x6
	.set	macro
	.set	reorder

	li	$2,1			# 0x1
	sw	$2,136($18)
	lui	$2,%hi(nf_hooks+144)
	lw	$3,%lo(nf_hooks+144)($2)
	addiu	$2,$2,%lo(nf_hooks+144)
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L138
	lui	$2,%hi(rtl_ipt_do_table)
	.set	macro
	.set	reorder

	move	$4,$18
	lw	$6,64($sp)
	lw	$7,92($sp)
	addiu	$2,$2,%lo(rtl_ipt_do_table)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,2			# 0x2
	.set	macro
	.set	reorder

$L138:
	lui	$5,%hi(rtl_get_skb_mark)
	addiu	$5,$5,%lo(rtl_get_skb_mark)
	.set	noreorder
	.set	nomacro
	jalr	$5
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L139
	lui	$7,%hi(rtl_get_skb_mark)
	.set	macro
	.set	reorder

	addiu	$7,$7,%lo(rtl_get_skb_mark)
	.set	noreorder
	.set	nomacro
	jalr	$7
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L169
	sw	$2,48($17)
	.set	macro
	.set	reorder

$L139:
	lw	$2,48($17)
	sw	$2,48($17)
$L169:
	sw	$0,136($18)
$L136:
	li	$2,6			# 0x6
$L172:
	.set	noreorder
	.set	nomacro
	bne	$22,$2,$L141
	lui	$2,%hi(udp_get_timeouts_by_state)
	.set	macro
	.set	reorder

	lw	$4,184($sp)
	lui	$2,%hi(rtl_tcp_get_timeouts)
	addiu	$2,$2,%lo(rtl_tcp_get_timeouts)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L142
	sw	$2,60($17)
	.set	macro
	.set	reorder

$L141:
	lw	$5,184($sp)
	li	$4,1			# 0x1
	addiu	$2,$2,%lo(udp_get_timeouts_by_state)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,1			# 0x1
	.set	macro
	.set	reorder

	sw	$2,60($17)
$L142:
	lui	$2,%hi(jiffies)
	lw	$3,%lo(jiffies)($2)
	lw	$4,184($sp)
	lw	$2,72($17)
	sw	$4,56($17)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L143
	sw	$3,40($17)
	.set	macro
	.set	reorder

	lw	$4,76($17)
	lui	$3,%hi(path_list_free)
	addiu	$3,$3,%lo(path_list_free)
	sw	$4,76($2)
	sw	$3,56($sp)
	lw	$2,76($17)
	lw	$3,72($17)
	j	$L144
$L143:
	lw	$2,76($17)
	lui	$5,%hi(path_list_free)
	addiu	$5,$5,%lo(path_list_free)
	move	$3,$0
	sw	$5,56($sp)
	sw	$2,4($5)
$L144:
	lw	$7,68($sp)
	lui	$20,%hi(path_list_inuse)
	sw	$3,0($2)
	addiu	$20,$20,%lo(path_list_inuse)
	lw	$2,80($sp)
	xor	$3,$7,$fp
	lw	$5,56($sp)
	srl	$fp,$fp,8
	xor	$3,$3,$2
	lw	$2,4($20)
	lw	$4,8($5)
	xor	$fp,$3,$fp
	srl	$3,$7,16
	lw	$7,76($sp)
	xor	$fp,$fp,$3
	lw	$3,56($sp)
	srl	$5,$7,4
	addiu	$4,$4,-1
	sw	$2,76($17)
	xor	$fp,$fp,$5
	sw	$0,72($17)
	sw	$4,8($3)
	xor	$3,$fp,$22
	sw	$17,0($2)
	lui	$fp,%hi(table_path)
	lw	$5,8($20)
	srl	$6,$3,12
	lw	$7,84($sp)
	addiu	$4,$17,72
	lw	$2,%lo(table_path)($fp)
	addiu	$5,$5,1
	xor	$6,$6,$3
	sw	$0,64($17)
	sw	$5,8($20)
	and	$6,$6,$7
	sw	$4,4($20)
	sll	$5,$6,2
	lw	$7,0($2)
	sll	$3,$6,4
	subu	$3,$3,$5
	addiu	$4,$17,64
	addu	$7,$7,$3
	lw	$5,4($7)
	lui	$7,%hi(path_table_list_max)
	lw	$6,%lo(path_table_list_max)($7)
	sw	$5,68($17)
	lui	$5,%hi(path_list_free)
	lw	$2,0($2)
	addiu	$6,$6,-1
	sw	$6,128($sp)
	addu	$2,$2,$3
	lw	$2,4($2)
	sw	$17,0($2)
	lw	$2,%lo(table_path)($fp)
	lw	$17,%lo(path_list_free)($5)
	lw	$5,0($2)
	addu	$5,$5,$3
	sw	$4,4($5)
	lw	$2,0($2)
	addu	$3,$2,$3
	lw	$2,8($3)
	addiu	$2,$2,1
	sw	$2,8($3)
	lw	$7,20($16)
	sw	$7,96($sp)
	lw	$2,24($16)
	lw	$3,12($16)
	lw	$4,16($16)
	sw	$2,124($sp)
	sw	$3,72($sp)
	.set	noreorder
	.set	nomacro
	beq	$17,$0,$L133
	sw	$4,120($sp)
	.set	macro
	.set	reorder

	lw	$2,0($16)
	sw	$2,4($17)
	lw	$2,20($16)
	sw	$2,16($17)
	lw	$2,24($16)
	sw	$2,12($17)
	lw	$5,12($16)
	sw	$5,20($17)
	lw	$7,16($16)
	sw	$5,76($sp)
	lui	$5,%hi(FastPath_Route)
	sw	$7,8($17)
	addiu	$5,$5,%lo(FastPath_Route)
	lw	$2,20($16)
	sw	$7,80($sp)
	sw	$2,24($17)
	lw	$2,24($16)
	sw	$2,28($17)
	lw	$2,4($16)
	sw	$2,32($17)
	move	$4,$2
	lw	$3,8($16)
	sw	$2,68($sp)
	sw	$3,84($sp)
	.set	noreorder
	.set	nomacro
	jalr	$5
	sw	$3,36($17)
	.set	macro
	.set	reorder

	sw	$2,44($17)
	li	$2,2			# 0x2
	sb	$2,2($17)
	li	$2,-1			# 0xffffffffffffffff
	sb	$2,0($17)
	lw	$7,76($sp)
	lw	$2,68($sp)
	.set	noreorder
	.set	nomacro
	beq	$7,$2,$L145
	sb	$0,1($17)
	.set	macro
	.set	reorder

	li	$2,4			# 0x4
	sb	$2,1($17)
$L145:
	lw	$3,80($sp)
	lw	$4,84($sp)
	beq	$3,$4,$L146
	lbu	$2,1($17)
	ori	$2,$2,0x8
	sb	$2,1($17)
$L146:
	sw	$0,48($17)
	lui	$7,%hi(memset)
	sw	$0,52($17)
	move	$5,$0
	lw	$2,20($16)
	addiu	$4,$sp,36
	li	$6,14			# 0xe
	addiu	$7,$7,%lo(memset)
	sw	$2,12($19)
	lw	$2,24($16)
	sh	$2,0($21)
	lw	$2,4($16)
	sw	$2,16($19)
	lw	$2,8($16)
	.set	noreorder
	.set	nomacro
	jalr	$7
	sh	$2,2($21)
	.set	macro
	.set	reorder

	move	$4,$18
	lw	$2,60($sp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$0
	.set	macro
	.set	reorder

	lw	$3,64($sp)
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L147
	lui	$2,%hi(rtl_arp_req_get_ha)
	.set	macro
	.set	reorder

	move	$5,$3
	lw	$4,4($16)
	addiu	$2,$2,%lo(rtl_arp_req_get_ha)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$6,$sp,36
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L173
	lui	$5,%hi(rtl_get_skb_mark)
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_ppp_proto_check)
	move	$4,$18
	addiu	$2,$2,%lo(rtl_ppp_proto_check)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$5,$sp,16
	.set	macro
	.set	reorder

	move	$16,$2
	li	$2,1			# 0x1
	.set	noreorder
	.set	nomacro
	bne	$16,$2,$L148
	lui	$2,%hi(rtl_skb_mac_header_was_set)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_skb_mac_header_was_set)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	bne	$2,$16,$L148
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$18
	.set	macro
	.set	reorder

	lbu	$3,12($2)
	lbu	$2,13($2)
	sll	$3,$3,8
	or	$3,$2,$3
	li	$2,2048			# 0x800
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L148
	lui	$2,%hi(rtl_skb_set_mac_header)
	.set	macro
	.set	reorder

	move	$4,$18
	addiu	$2,$2,%lo(rtl_skb_set_mac_header)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,-22			# 0xffffffffffffffea
	.set	macro
	.set	reorder

$L148:
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$7,%hi(memcpy)
	move	$4,$2
	addiu	$5,$sp,36
	addiu	$7,$7,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$7
	li	$6,6			# 0x6
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_smac)
	lw	$5,64($sp)
	addiu	$2,$2,%lo(rtl_set_skb_smac)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	li	$2,2048			# 0x800
	lw	$3,132($sp)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L173
	lui	$5,%hi(rtl_get_skb_mark)
	.set	macro
	.set	reorder

	li	$2,1			# 0x1
	sw	$2,136($18)
	lui	$2,%hi(nf_hooks+144)
	lw	$3,%lo(nf_hooks+144)($2)
	addiu	$2,$2,%lo(nf_hooks+144)
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L149
	lui	$2,%hi(rtl_ipt_do_table)
	.set	macro
	.set	reorder

	move	$4,$18
	lw	$6,64($sp)
	lw	$7,92($sp)
	addiu	$2,$2,%lo(rtl_ipt_do_table)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,2			# 0x2
	.set	macro
	.set	reorder

$L149:
	sw	$0,136($18)
$L147:
	lui	$5,%hi(rtl_get_skb_mark)
$L173:
	addiu	$5,$5,%lo(rtl_get_skb_mark)
	.set	noreorder
	.set	nomacro
	jalr	$5
	move	$4,$18
	.set	macro
	.set	reorder

	sw	$2,48($17)
	li	$2,6			# 0x6
	.set	noreorder
	.set	nomacro
	bne	$22,$2,$L150
	lui	$2,%hi(udp_get_timeouts_by_state)
	.set	macro
	.set	reorder

	lw	$4,184($sp)
	lui	$2,%hi(rtl_tcp_get_timeouts)
	addiu	$2,$2,%lo(rtl_tcp_get_timeouts)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L151
	sw	$2,60($17)
	.set	macro
	.set	reorder

$L150:
	lw	$5,184($sp)
	li	$4,1			# 0x1
	addiu	$2,$2,%lo(udp_get_timeouts_by_state)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,1			# 0x1
	.set	macro
	.set	reorder

	sw	$2,60($17)
$L151:
	lui	$7,%hi(jiffies)
	lw	$3,%lo(jiffies)($7)
	lw	$4,184($sp)
	lw	$2,72($17)
	sw	$4,56($17)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L152
	sw	$3,40($17)
	.set	macro
	.set	reorder

	lw	$3,76($17)
	sw	$3,76($2)
	lw	$2,76($17)
	lw	$3,72($17)
	.set	noreorder
	.set	nomacro
	j	$L170
	sw	$3,0($2)
	.set	macro
	.set	reorder

$L152:
	lw	$2,76($17)
	move	$3,$0
	lw	$5,56($sp)
	sw	$2,4($5)
	sw	$3,0($2)
$L170:
	lw	$5,56($sp)
	lw	$7,120($sp)
	lw	$3,72($sp)
	lw	$4,8($5)
	xor	$2,$7,$3
	lw	$7,96($sp)
	srl	$3,$3,16
	addiu	$4,$4,-1
	xor	$2,$2,$3
	lw	$3,4($20)
	xor	$2,$2,$22
	sw	$4,8($5)
	xor	$2,$2,$7
	sw	$3,76($17)
	srl	$4,$7,8
	sw	$0,72($17)
	xor	$2,$2,$4
	sw	$17,0($3)
	lw	$4,124($sp)
	lw	$5,8($20)
	srl	$3,$4,4
	addiu	$4,$17,72
	xor	$2,$2,$3
	addiu	$5,$5,1
	sw	$5,8($20)
	srl	$6,$2,12
	lw	$5,128($sp)
	xor	$6,$6,$2
	lw	$3,%lo(table_path)($fp)
	sw	$0,64($17)
	and	$6,$6,$5
	sw	$4,4($20)
	sll	$5,$6,2
	lw	$4,0($3)
	sll	$2,$6,4
	subu	$2,$2,$5
	addiu	$5,$17,64
	addu	$4,$4,$2
	lw	$4,4($4)
	sw	$4,68($17)
	lw	$3,0($3)
	addu	$3,$3,$2
	lw	$3,4($3)
	sw	$17,0($3)
	lw	$3,%lo(table_path)($fp)
	lw	$4,0($3)
	addu	$4,$4,$2
	sw	$5,4($4)
	lw	$3,0($3)
	addu	$2,$3,$2
	lw	$3,8($2)
	addiu	$3,$3,1
	sw	$3,8($2)
$L133:
	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$7,%hi(memcpy)
	addiu	$7,$7,%lo(memcpy)
	li	$6,6			# 0x6
	addiu	$5,$sp,28
	.set	noreorder
	.set	nomacro
	jalr	$7
	addiu	$4,$2,6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$23
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$3,%hi(memcpy)
	li	$6,6			# 0x6
	addiu	$3,$3,%lo(memcpy)
	move	$4,$2
	.set	noreorder
	.set	nomacro
	jalr	$3
	addiu	$5,$sp,20
	.set	macro
	.set	reorder

	lw	$5,100($sp)
	lw	$7,60($sp)
	.set	noreorder
	.set	nomacro
	jalr	$7
	move	$4,$18
	.set	macro
	.set	reorder

	move	$4,$18
	lw	$2,104($sp)
	lw	$3,108($sp)
	lw	$5,112($sp)
	lw	$7,116($sp)
	sw	$2,12($19)
	lui	$2,%hi(rtl_set_skb_dst)
	sh	$3,0($21)
	addiu	$2,$2,%lo(rtl_set_skb_dst)
	sw	$5,16($19)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sh	$7,2($21)
	.set	macro
	.set	reorder

	lw	$2,64($sp)
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L166
	lui	$3,%hi(arch_local_irq_save)
	.set	macro
	.set	reorder

	lui	$16,%hi(arch_local_irq_restore)
	.set	noreorder
	.set	nomacro
	j	$L154
	addiu	$16,$16,%lo(arch_local_irq_restore)
	.set	macro
	.set	reorder

$L166:
	lui	$16,%hi(arch_local_irq_restore)
	addiu	$3,$3,%lo(arch_local_irq_save)
	.set	noreorder
	.set	nomacro
	jalr	$3
	addiu	$16,$16,%lo(arch_local_irq_restore)
	.set	macro
	.set	reorder

	lw	$4,64($sp)
	lw	$3,500($4)
	move	$4,$2
	lw	$2,0($3)
	addiu	$2,$2,-1
	.set	noreorder
	.set	nomacro
	jalr	$16
	sw	$2,0($3)
	.set	macro
	.set	reorder

$L154:
	lw	$5,92($sp)
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L155
	lui	$7,%hi(arch_local_irq_save)
	.set	macro
	.set	reorder

	addiu	$7,$7,%lo(arch_local_irq_save)
	jalr	$7
	lw	$4,92($sp)
	lw	$3,500($4)
	move	$4,$2
	lw	$2,0($3)
	addiu	$2,$2,-1
	.set	noreorder
	.set	nomacro
	jalr	$16
	sw	$2,0($3)
	.set	macro
	.set	reorder

$L155:
	lw	$5,88($sp)
	andi	$2,$5,0x1
	bne	$2,$0,$L156
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$5
	.set	macro
	.set	reorder

	j	$L157
$L156:
	lw	$4,88($sp)
	jalr	$16
	j	$L157
$L129:
	lw	$7,88($sp)
	andi	$2,$7,0x1
	bne	$2,$0,$L158
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$2,$2,%lo(arch_local_irq_restore)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$7
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L123
	li	$2,-1			# 0xffffffffffffffff
	.set	macro
	.set	reorder

$L158:
	lw	$4,88($sp)
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$2,$2,%lo(arch_local_irq_restore)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L123
	li	$2,-1			# 0xffffffffffffffff
	.set	macro
	.set	reorder

$L157:
	lw	$4,184($sp)
	lui	$2,%hi(rtl_conntrack_drop_check_hook)
	addiu	$2,$2,%lo(rtl_conntrack_drop_check_hook)
	move	$5,$22
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$6,$4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L123
	move	$2,$0
	.set	macro
	.set	reorder

$L162:
	li	$2,-1			# 0xffffffffffffffff
$L123:
	lw	$31,172($sp)
	lw	$fp,168($sp)
	lw	$23,164($sp)
	lw	$22,160($sp)
	lw	$21,156($sp)
	lw	$20,152($sp)
	lw	$19,148($sp)
	lw	$18,144($sp)
	lw	$17,140($sp)
	lw	$16,136($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,176
	.set	macro
	.set	reorder

	.end	rtk_addNaptConnection
	.size	rtk_addNaptConnection, .-rtk_addNaptConnection
	.section	.rodata.str1.4
	.align	2
$LC6:
	.ascii	"lo\000"
	.text
	.align	2
	.globl	enter_fast_path
	.set	nomips16
	.ent	enter_fast_path
	.type	enter_fast_path, @function
enter_fast_path:
	.frame	$sp,88,$31		# vars= 32, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-88
	sw	$31,84($sp)
	sw	$fp,80($sp)
	sw	$23,76($sp)
	sw	$22,72($sp)
	sw	$21,68($sp)
	sw	$20,64($sp)
	sw	$19,60($sp)
	sw	$18,56($sp)
	sw	$17,52($sp)
	sw	$16,48($sp)
	lui	$2,%hi(rtl_get_skb_dev_name)
	addiu	$2,$2,%lo(rtl_get_skb_dev_name)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$18,$4
	.set	macro
	.set	reorder

	move	$16,$2
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	move	$17,$2
	lbu	$2,8($2)
	sltu	$2,$2,2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L175
	move	$2,$0
	.set	macro
	.set	reorder

	lbu	$19,9($17)
	li	$2,6			# 0x6
	.set	noreorder
	.set	nomacro
	beq	$19,$2,$L176
	li	$2,17			# 0x11
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$19,$2,$L175
	move	$2,$0
	.set	macro
	.set	reorder

$L176:
	lbu	$22,0($17)
	lui	$2,%hi(fast_path_pre_process_check)
	move	$4,$17
	addiu	$2,$2,%lo(fast_path_pre_process_check)
	andi	$22,$22,0xf
	sll	$22,$22,2
	addu	$22,$17,$22
	move	$6,$18
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$22
	.set	macro
	.set	reorder

	li	$3,6			# 0x6
	.set	noreorder
	.set	nomacro
	bne	$2,$3,$L175
	lui	$3,%hi($LC6)
	.set	macro
	.set	reorder

	addiu	$3,$3,%lo($LC6)
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$4,($16)
1:	lbu	$1,($3)
	addiu	$16,1
	bne	$1,$4,2f
	addiu	$3,1
	bnez	$4,1b
	lbu	$4,($16)
	move	$4,$1
2:	subu	$4,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	beq	$4,$0,$L285
	lw	$4,16($17)
	lhu	$3,6($17)
	lw	$23,12($17)
	sw	$4,16($sp)
	lhu	$20,0($22)
	lhu	$fp,2($22)
	.set	noreorder
	.set	nomacro
	bne	$19,$2,$L178
	andi	$2,$3,0x3fff
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L179
	li	$4,8192			# 0x2000
	.set	macro
	.set	reorder

	bne	$3,$4,$L180
	j	$L179
$L297:
	lw	$5,16($sp)
	lw	$7,16($sp)
	lui	$2,%hi(path_table_list_max)
	xor	$6,$23,$5
	lw	$5,%lo(path_table_list_max)($2)
	xori	$6,$6,0x6
	lui	$2,%hi(table_path)
	xor	$6,$6,$fp
	addiu	$5,$5,-1
	xor	$6,$6,$3
	lw	$4,%lo(table_path)($2)
	srl	$3,$7,16
	xor	$6,$6,$3
	lw	$4,0($4)
	srl	$3,$20,4
	xor	$3,$6,$3
	srl	$6,$3,12
	xor	$3,$6,$3
	and	$3,$3,$5
	sll	$6,$3,2
	sll	$3,$3,4
	subu	$3,$3,$6
	addu	$3,$4,$3
	lw	$3,0($3)
	.set	noreorder
	.set	nomacro
	j	$L181
	li	$7,255			# 0xff
	.set	macro
	.set	reorder

$L185:
	lw	$4,12($3)
	bne	$20,$4,$L182
	lw	$4,8($3)
	bne	$fp,$4,$L182
	lw	$4,16($3)
	bne	$23,$4,$L182
	lw	$4,20($3)
	lw	$8,16($sp)
	bne	$8,$4,$L182
	lbu	$4,0($3)
	.set	noreorder
	.set	nomacro
	bne	$4,$7,$L182
	li	$4,1			# 0x1
	.set	macro
	.set	reorder

	lbu	$6,2($3)
	.set	noreorder
	.set	nomacro
	bne	$6,$4,$L183
	sb	$0,0($3)
	.set	macro
	.set	reorder

	lw	$4,24($3)
	lhu	$3,30($3)
	j	$L184
$L183:
	lw	$4,32($3)
	lhu	$3,38($3)
	j	$L184
$L182:
	lw	$3,64($3)
$L181:
	bne	$3,$0,$L185
	.set	noreorder
	.set	nomacro
	j	$L175
	move	$2,$0
	.set	macro
	.set	reorder

$L184:
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L285
	li	$7,1			# 0x1
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$6,$7,$L186
	xori	$7,$23,0x6
	.set	macro
	.set	reorder

	lw	$11,16($sp)
	srl	$6,$11,8
	xori	$7,$11,0x6
	xor	$7,$7,$6
	srl	$6,$fp,4
	xor	$6,$7,$6
	xor	$6,$6,$4
	xor	$3,$6,$3
	srl	$4,$4,16
	xor	$3,$3,$4
	srl	$4,$3,12
	xor	$3,$4,$3
	.set	noreorder
	.set	nomacro
	j	$L187
	and	$5,$3,$5
	.set	macro
	.set	reorder

$L186:
	xor	$7,$7,$20
	srl	$6,$23,16
	xor	$6,$7,$6
	xor	$6,$6,$4
	srl	$4,$4,8
	xor	$4,$6,$4
	srl	$3,$3,4
	xor	$3,$4,$3
	srl	$4,$3,12
	xor	$3,$4,$3
	and	$5,$3,$5
$L187:
	li	$4,12			# 0xc
	mult	$5,$4
	lw	$2,%lo(table_path)($2)
	lw	$2,0($2)
	mflo	$5
	addu	$5,$2,$5
	lw	$2,0($5)
	.set	noreorder
	.set	nomacro
	j	$L188
	li	$3,255			# 0xff
	.set	macro
	.set	reorder

$L190:
	lw	$4,24($2)
	lw	$5,16($sp)
	bne	$5,$4,$L189
	lw	$4,28($2)
	bne	$fp,$4,$L189
	lw	$4,32($2)
	bne	$23,$4,$L189
	lw	$4,36($2)
	bne	$20,$4,$L189
	lbu	$4,0($2)
	bne	$4,$3,$L189
	sb	$0,0($2)
$L189:
	lw	$2,64($2)
$L188:
	bne	$2,$0,$L190
	j	$L175
$L290:
	li	$5,393216			# 0x60000
	and	$4,$4,$5
	bne	$4,$0,$L285
$L178:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L191
	li	$7,1			# 0x1
	.set	macro
	.set	reorder

	lw	$6,16($sp)
	move	$21,$0
	xor	$6,$6,$23
	sw	$0,32($sp)
	sw	$6,20($sp)
	sw	$0,28($sp)
	.set	noreorder
	.set	nomacro
	j	$L192
	sw	$7,40($sp)
	.set	macro
	.set	reorder

$L191:
	li	$2,8192			# 0x2000
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L279
	li	$8,1			# 0x1
	.set	macro
	.set	reorder

$L180:
	andi	$2,$3,0x2000
	bne	$2,$0,$L280
	andi	$3,$3,0x1fff
	sw	$0,28($sp)
	sltu	$3,$0,$3
	.set	noreorder
	.set	nomacro
	j	$L193
	sw	$3,32($sp)
	.set	macro
	.set	reorder

$L279:
	sw	$0,32($sp)
	.set	noreorder
	.set	nomacro
	j	$L193
	sw	$8,28($sp)
	.set	macro
	.set	reorder

$L280:
	sw	$0,32($sp)
	sw	$0,28($sp)
$L193:
	lw	$11,16($sp)
	lhu	$5,4($17)
	xor	$11,$11,$23
	lbu	$8,9($17)
	srl	$2,$11,16
	sw	$11,20($sp)
	xor	$3,$5,$11
	xor	$3,$3,$2
	lui	$2,%hi(max_udp_frag_entry)
	lw	$7,%lo(max_udp_frag_entry)($2)
	srl	$4,$3,8
	xor	$3,$3,$8
	lui	$2,%hi(negative_cache_table)
	xor	$6,$3,$4
	addiu	$7,$7,-1
	and	$6,$6,$7
	lw	$4,%lo(negative_cache_table)($2)
	sll	$7,$6,2
	sll	$9,$6,4
	subu	$3,$9,$7
	addu	$3,$4,$3
	lw	$3,0($3)
	.set	noreorder
	.set	nomacro
	j	$L194
	li	$10,3			# 0x3
	.set	macro
	.set	reorder

$L196:
	lhu	$4,2($3)
	bne	$4,$5,$L195
	lw	$4,4($3)
	bne	$23,$4,$L195
	lw	$4,8($3)
	lw	$11,16($sp)
	bne	$11,$4,$L195
	lbu	$4,1($3)
	bne	$4,$8,$L195
	lbu	$4,0($3)
	beq	$4,$10,$L285
$L195:
	lw	$3,40($3)
$L194:
	bne	$3,$0,$L196
	.set	noreorder
	.set	nomacro
	j	$L295
	lui	$3,%hi(udp_cache_table)
	.set	macro
	.set	reorder

$L200:
	lhu	$3,2($21)
	bne	$3,$5,$L198
	lw	$3,4($21)
	bne	$23,$3,$L198
	lw	$3,8($21)
	lw	$7,16($sp)
	bne	$7,$3,$L198
	lbu	$3,1($21)
	bne	$3,$8,$L198
	lbu	$3,0($21)
	beq	$3,$4,$L199
$L198:
	lw	$21,44($21)
$L272:
	bne	$21,$0,$L200
	j	$L296
$L199:
	lw	$8,28($sp)
	lhu	$20,12($21)
	lhu	$fp,14($21)
	.set	noreorder
	.set	nomacro
	bne	$8,$0,$L283
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L192
	sw	$0,40($sp)
	.set	macro
	.set	reorder

$L273:
	lw	$3,%lo(negative_cache_list_free)($4)
	beq	$3,$0,$L285
	lw	$11,16($sp)
	lw	$7,48($3)
	sh	$5,2($3)
	li	$5,3			# 0x3
	sb	$5,0($3)
	sw	$23,4($3)
	sw	$11,8($3)
	sb	$8,1($3)
	lw	$5,52($3)
	.set	noreorder
	.set	nomacro
	beq	$7,$0,$L202
	addiu	$4,$4,%lo(negative_cache_list_free)
	.set	macro
	.set	reorder

	sw	$5,52($7)
	lw	$7,48($3)
	lw	$5,52($3)
	.set	noreorder
	.set	nomacro
	j	$L298
	li	$8,12			# 0xc
	.set	macro
	.set	reorder

$L202:
	sw	$5,4($4)
	li	$8,12			# 0xc
$L298:
	mult	$6,$8
	sw	$7,0($5)
	lw	$8,8($4)
	lw	$5,%lo(negative_cache_table)($2)
	addiu	$7,$3,40
	addiu	$8,$8,-1
	mflo	$6
	sw	$8,8($4)
	sw	$0,40($3)
	addu	$5,$5,$6
	lw	$8,4($5)
	addiu	$4,$3,12
	sw	$8,44($3)
	lw	$5,4($5)
	sw	$3,0($5)
	lw	$5,%lo(negative_cache_table)($2)
	lui	$2,%hi(jiffies)
	lw	$2,%lo(jiffies)($2)
	addu	$6,$5,$6
	lw	$5,8($6)
	addiu	$2,$2,1000
	sw	$7,4($6)
	addiu	$5,$5,1
	sw	$5,8($6)
	sw	$2,20($3)
	lui	$2,%hi(add_timer)
	addiu	$2,$2,%lo(add_timer)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L175
	move	$2,$0
	.set	macro
	.set	reorder

$L283:
	li	$3,1			# 0x1
	sw	$2,28($sp)
	sw	$3,40($sp)
$L192:
	lw	$4,16($sp)
	srl	$3,$23,8
	lui	$2,%hi(path_table_list_max)
	li	$7,2			# 0x2
	srl	$4,$4,16
	lw	$5,20($sp)
	xor	$3,$4,$3
	lw	$9,%lo(path_table_list_max)($2)
	xor	$3,$3,$19
	lui	$2,%hi(table_path)
	xor	$3,$3,$fp
	sw	$4,24($sp)
	xor	$3,$3,$5
	lw	$4,%lo(table_path)($2)
	srl	$2,$20,4
	addiu	$9,$9,-1
	xor	$3,$3,$2
	lw	$4,0($4)
	srl	$2,$3,12
	li	$5,255			# 0xff
	xor	$2,$2,$3
	li	$6,1			# 0x1
	and	$2,$2,$9
	li	$8,17			# 0x11
	sll	$9,$2,2
	sll	$2,$2,4
	subu	$2,$2,$9
	addu	$2,$4,$2
	lw	$16,0($2)
	.set	noreorder
	.set	nomacro
	j	$L204
	li	$3,6			# 0x6
	.set	macro
	.set	reorder

$L269:
	lw	$2,12($16)
	bne	$2,$20,$L205
	lw	$2,8($16)
	bne	$2,$fp,$L205
	lw	$2,16($16)
	bne	$2,$23,$L205
	lw	$2,20($16)
	lw	$11,16($sp)
	bne	$2,$11,$L205
	lbu	$2,0($16)
	bne	$2,$5,$L205
	lw	$2,4($16)
	bne	$2,$7,$L206
	.set	noreorder
	.set	nomacro
	bne	$19,$3,$L205
	lui	$2,%hi(rtl_ip_route_input)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L302
	move	$4,$18
	.set	macro
	.set	reorder

$L206:
	bne	$2,$6,$L205
	.set	noreorder
	.set	nomacro
	bne	$19,$8,$L205
	lui	$2,%hi(rtl_ip_route_input)
	.set	macro
	.set	reorder

	move	$4,$18
$L302:
	lw	$5,32($16)
	lbu	$7,1($17)
	addiu	$2,$2,%lo(rtl_ip_route_input)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$6,$23
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L175
	move	$2,$0
	.set	macro
	.set	reorder

	lw	$5,32($16)
	lui	$2,%hi(rtl_skb_dst_check)
	lw	$6,56($16)
	lbu	$7,1($16)
	addiu	$2,$2,%lo(rtl_skb_dst_check)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	li	$3,-1			# 0xffffffffffffffff
	.set	noreorder
	.set	nomacro
	beq	$2,$3,$L301
	lui	$2,%hi(rtl_dst_release)
	.set	macro
	.set	reorder

	li	$2,6			# 0x6
	.set	noreorder
	.set	nomacro
	bne	$19,$2,$L209
	addiu	$2,$22,16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L210
	sw	$2,36($sp)
	.set	macro
	.set	reorder

$L209:
	lhu	$2,6($22)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L286
	addiu	$3,$22,6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L210
	sw	$3,36($sp)
	.set	macro
	.set	reorder

$L286:
	sw	$0,36($sp)
$L210:
	lw	$4,28($sp)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L211
	lui	$4,%hi(udp_cache_list_free)
	.set	macro
	.set	reorder

	lui	$3,%hi(max_udp_frag_entry)
	lw	$2,%lo(udp_cache_list_free)($4)
	lhu	$6,4($17)
	lw	$9,%lo(max_udp_frag_entry)($3)
	beq	$2,$0,$L212
	lw	$5,16($sp)
	lw	$3,52($2)
	sw	$5,8($2)
	li	$5,1			# 0x1
	sb	$5,0($2)
	sh	$6,2($2)
	sw	$23,4($2)
	sb	$19,1($2)
	sh	$20,12($2)
	sh	$fp,14($2)
	lw	$5,56($2)
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L213
	addiu	$4,$4,%lo(udp_cache_list_free)
	.set	macro
	.set	reorder

	sw	$5,56($3)
	lw	$3,52($2)
	lw	$5,56($2)
	j	$L214
$L213:
	sw	$5,4($4)
$L214:
	lw	$7,20($sp)
	addiu	$9,$9,-1
	sw	$3,0($5)
	xor	$6,$7,$6
	sw	$0,44($2)
	srl	$3,$7,16
	lw	$7,8($4)
	xor	$3,$6,$3
	li	$6,12			# 0xc
	xor	$8,$3,$19
	addiu	$7,$7,-1
	srl	$5,$3,8
	lui	$3,%hi(udp_cache_table)
	xor	$8,$8,$5
	lw	$5,%lo(udp_cache_table)($3)
	and	$8,$8,$9
	sw	$7,8($4)
	mult	$8,$6
	lw	$7,0($5)
	addiu	$8,$2,44
	addiu	$4,$2,16
	mflo	$6
	addu	$7,$7,$6
	lw	$7,4($7)
	sw	$7,48($2)
	lw	$5,0($5)
	addu	$5,$5,$6
	lw	$5,4($5)
	sw	$2,0($5)
	lui	$5,%hi(jiffies)
	lw	$3,%lo(udp_cache_table)($3)
	lw	$5,%lo(jiffies)($5)
	lw	$7,0($3)
	addiu	$5,$5,1000
	addu	$7,$7,$6
	sw	$8,4($7)
	lw	$3,0($3)
	addu	$6,$3,$6
	lw	$3,8($6)
	addiu	$3,$3,1
	sw	$3,8($6)
	sw	$5,24($2)
	lui	$2,%hi(add_timer)
	addiu	$2,$2,%lo(add_timer)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L300
	lui	$2,%hi(fast_path_before_nat_check)
	.set	macro
	.set	reorder

$L212:
	lui	$2,%hi(rtl_dst_release)
$L301:
	addiu	$2,$2,%lo(rtl_dst_release)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L175
	move	$2,$0
	.set	macro
	.set	reorder

$L211:
	lw	$2,32($sp)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L215
	lui	$2,%hi(del_timer)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(del_timer)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$4,$21,16
	.set	macro
	.set	reorder

	lui	$5,%hi(max_udp_frag_entry)
	lw	$2,4($21)
	lw	$4,8($21)
	lhu	$3,2($21)
	xor	$4,$4,$2
	lbu	$2,1($21)
	srl	$6,$4,16
	lw	$5,%lo(max_udp_frag_entry)($5)
	xor	$3,$3,$4
	lw	$4,44($21)
	xor	$3,$3,$6
	addiu	$5,$5,-1
	srl	$6,$3,8
	sb	$0,0($21)
	xor	$2,$3,$2
	xor	$2,$2,$6
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L216
	and	$2,$2,$5
	.set	macro
	.set	reorder

	lw	$5,48($21)
	lui	$3,%hi(udp_cache_table)
	.set	noreorder
	.set	nomacro
	j	$L217
	sw	$5,48($4)
	.set	macro
	.set	reorder

$L216:
	li	$4,12			# 0xc
	lui	$3,%hi(udp_cache_table)
	mult	$2,$4
	lw	$6,%lo(udp_cache_table)($3)
	lw	$5,48($21)
	lw	$6,0($6)
	mflo	$4
	addu	$4,$6,$4
	sw	$5,4($4)
$L217:
	lw	$4,48($21)
	li	$6,12			# 0xc
	lw	$5,44($21)
	mult	$2,$6
	sw	$5,0($4)
	lui	$4,%hi(udp_cache_list_free)
	lw	$6,%lo(udp_cache_table)($3)
	addiu	$4,$4,%lo(udp_cache_list_free)
	mflo	$2
	lw	$3,4($4)
	lw	$6,0($6)
	addiu	$5,$21,52
	addu	$2,$6,$2
	lw	$6,8($2)
	addiu	$6,$6,-1
	sw	$6,8($2)
	sw	$0,52($21)
	sw	$3,56($21)
	sw	$21,0($3)
	lw	$2,8($4)
	sw	$5,4($4)
	addiu	$2,$2,1
	sw	$2,8($4)
$L215:
	lui	$2,%hi(fast_path_before_nat_check)
$L300:
	move	$4,$18
	move	$5,$17
	addiu	$2,$2,%lo(fast_path_before_nat_check)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$6,$19
	.set	macro
	.set	reorder

	li	$3,1			# 0x1
	beq	$2,$3,$L175
	li	$2,6			# 0x6
	.set	noreorder
	.set	nomacro
	bne	$19,$2,$L218
	li	$3,1048576			# 0x100000
	.set	macro
	.set	reorder

	lw	$2,12($22)
	and	$2,$3,$2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L218
	li	$2,40			# 0x28
	.set	macro
	.set	reorder

	lhu	$3,2($17)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L218
	lui	$2,%hi(skb_trim)
	.set	macro
	.set	reorder

	move	$4,$18
	addiu	$2,$2,%lo(skb_trim)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,40			# 0x28
	.set	macro
	.set	reorder

$L218:
	lbu	$2,1($16)
	sltu	$3,$2,13
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L219
	lui	$3,%hi($L225)
	.set	macro
	.set	reorder

	sll	$2,$2,2
	addiu	$3,$3,%lo($L225)
	addu	$2,$3,$2
	lw	$2,0($2)
	j	$2
	.rdata
	.align	2
	.align	2
$L225:
	.word	$L220
	.word	$L221
	.word	$L222
	.word	$L222
	.word	$L223
	.word	$L219
	.word	$L219
	.word	$L219
	.word	$L224
	.word	$L219
	.word	$L219
	.word	$L219
	.word	$L224
	.text
$L221:
	lw	$3,24($16)
	srl	$4,$23,16
	lhu	$2,10($17)
	andi	$23,$23,0xffff
	andi	$5,$3,0xffff
	srl	$3,$3,16
	addu	$3,$5,$3
	subu	$3,$4,$3
	addu	$23,$3,$23
	addu	$2,$2,$23
	.set	noreorder
	.set	nomacro
	bgez	$2,$L226
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L227
	sh	$2,10($17)
	.set	macro
	.set	reorder

$L226:
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	sh	$2,10($17)
$L227:
	lw	$2,40($sp)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L235
	li	$2,17			# 0x11
	.set	macro
	.set	reorder

	bne	$19,$2,$L229
	lw	$3,36($sp)
	beq	$3,$0,$L235
	lhu	$3,0($3)
	beq	$3,$0,$L235
	lw	$2,24($16)
	lw	$4,12($17)
	srl	$6,$2,16
	andi	$2,$2,0xffff
	srl	$5,$4,16
	addu	$2,$6,$2
	subu	$2,$5,$2
	andi	$4,$4,0xffff
	addu	$2,$2,$4
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L230
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	lw	$4,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L235
	sh	$2,0($4)
	.set	macro
	.set	reorder

$L230:
	lw	$5,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	j	$L235
	sh	$2,0($5)
	.set	macro
	.set	reorder

$L229:
	lw	$4,24($16)
	lw	$3,12($17)
	andi	$6,$4,0xffff
	lw	$7,36($sp)
	srl	$4,$4,16
	srl	$5,$3,16
	addu	$4,$6,$4
	lhu	$2,0($7)
	subu	$4,$5,$4
	andi	$3,$3,0xffff
	addu	$3,$4,$3
	addu	$2,$2,$3
	.set	noreorder
	.set	nomacro
	bgez	$2,$L231
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L232
	sh	$2,0($7)
	.set	macro
	.set	reorder

$L231:
	lw	$8,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	sh	$2,0($8)
$L232:
	lw	$2,12($22)
	li	$3,1048576			# 0x100000
	and	$2,$3,$2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L235
	li	$2,40			# 0x28
	.set	macro
	.set	reorder

	lhu	$3,2($17)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L235
	lui	$2,%hi(skb_trim)
	.set	macro
	.set	reorder

	move	$4,$18
	addiu	$2,$2,%lo(skb_trim)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,40			# 0x28
	.set	macro
	.set	reorder

	j	$L235
$L222:
	lw	$3,24($16)
	srl	$4,$23,16
	lhu	$2,10($17)
	andi	$23,$23,0xffff
	andi	$5,$3,0xffff
	srl	$3,$3,16
	addu	$3,$5,$3
	subu	$3,$4,$3
	addu	$23,$3,$23
	addu	$2,$2,$23
	.set	noreorder
	.set	nomacro
	bgez	$2,$L233
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L234
	sh	$2,10($17)
	.set	macro
	.set	reorder

$L233:
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	sh	$2,10($17)
$L234:
	lw	$11,40($sp)
	.set	noreorder
	.set	nomacro
	beq	$11,$0,$L235
	li	$2,17			# 0x11
	.set	macro
	.set	reorder

	bne	$19,$2,$L236
	lw	$2,36($sp)
	beq	$2,$0,$L237
	lhu	$3,0($2)
	beq	$3,$0,$L237
	lw	$2,24($16)
	lw	$4,12($17)
	andi	$8,$2,0xffff
	lhu	$6,0($22)
	srl	$2,$2,16
	lhu	$5,30($16)
	srl	$7,$4,16
	addu	$2,$8,$2
	subu	$2,$7,$2
	andi	$4,$4,0xffff
	addu	$4,$2,$4
	addu	$2,$6,$4
	subu	$2,$2,$5
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L238
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	lw	$3,36($sp)
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L237
	sh	$2,0($3)
	.set	macro
	.set	reorder

$L238:
	lw	$4,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	j	$L237
	sh	$2,0($4)
	.set	macro
	.set	reorder

$L236:
	lw	$2,24($16)
	lw	$3,12($17)
	andi	$7,$2,0xffff
	lhu	$5,0($22)
	srl	$2,$2,16
	lhu	$4,30($16)
	srl	$6,$3,16
	addu	$2,$7,$2
	subu	$2,$6,$2
	andi	$3,$3,0xffff
	addu	$3,$2,$3
	addu	$2,$5,$3
	lw	$5,36($sp)
	subu	$2,$2,$4
	lhu	$3,0($5)
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L239
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L240
	sh	$2,0($5)
	.set	macro
	.set	reorder

$L239:
	lw	$6,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	sh	$2,0($6)
$L240:
	lw	$2,12($22)
	li	$3,1048576			# 0x100000
	and	$2,$3,$2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L237
	li	$2,40			# 0x28
	.set	macro
	.set	reorder

	lhu	$3,2($17)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L237
	lui	$2,%hi(skb_trim)
	.set	macro
	.set	reorder

	move	$4,$18
	addiu	$2,$2,%lo(skb_trim)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,40			# 0x28
	.set	macro
	.set	reorder

$L237:
	lw	$2,28($16)
	sh	$2,0($22)
$L235:
	lw	$2,24($16)
	.set	noreorder
	.set	nomacro
	j	$L220
	sw	$2,12($17)
	.set	macro
	.set	reorder

$L223:
	lw	$4,32($16)
	lhu	$3,18($sp)
	lw	$7,24($sp)
	andi	$5,$4,0xffff
	lhu	$2,10($17)
	srl	$4,$4,16
	addu	$3,$3,$7
	subu	$5,$3,$5
	subu	$4,$5,$4
	addu	$2,$2,$4
	.set	noreorder
	.set	nomacro
	bgez	$2,$L241
	sra	$4,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$4,$2,16
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L242
	sh	$2,10($17)
	.set	macro
	.set	reorder

$L241:
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	sh	$2,10($17)
$L242:
	lw	$8,40($sp)
	.set	noreorder
	.set	nomacro
	beq	$8,$0,$L291
	li	$2,17			# 0x11
	.set	macro
	.set	reorder

	bne	$19,$2,$L244
	lw	$11,36($sp)
	beq	$11,$0,$L291
	lhu	$4,0($11)
	beq	$4,$0,$L291
	lw	$5,32($16)
	andi	$2,$5,0xffff
	subu	$2,$3,$2
	srl	$5,$5,16
	subu	$2,$2,$5
	addu	$2,$4,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L245
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L291
	sh	$2,0($11)
	.set	macro
	.set	reorder

$L245:
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	lw	$3,36($sp)
	.set	noreorder
	.set	nomacro
	j	$L291
	sh	$2,0($3)
	.set	macro
	.set	reorder

$L244:
	lw	$4,32($16)
	lw	$5,36($sp)
	lhu	$2,0($5)
	andi	$5,$4,0xffff
	subu	$3,$3,$5
	srl	$4,$4,16
	subu	$3,$3,$4
	addu	$2,$2,$3
	.set	noreorder
	.set	nomacro
	bgez	$2,$L246
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	lw	$6,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L291
	sh	$2,0($6)
	.set	macro
	.set	reorder

$L246:
	lw	$7,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	j	$L291
	sh	$2,0($7)
	.set	macro
	.set	reorder

$L224:
	lw	$4,32($16)
	lhu	$3,18($sp)
	lw	$8,24($sp)
	andi	$5,$4,0xffff
	lhu	$2,10($17)
	srl	$4,$4,16
	addu	$3,$3,$8
	subu	$5,$3,$5
	subu	$4,$5,$4
	addu	$2,$2,$4
	.set	noreorder
	.set	nomacro
	bgez	$2,$L247
	sra	$4,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$4,$2,16
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L248
	sh	$2,10($17)
	.set	macro
	.set	reorder

$L247:
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	sh	$2,10($17)
$L248:
	lw	$11,40($sp)
	.set	noreorder
	.set	nomacro
	beq	$11,$0,$L291
	li	$2,17			# 0x11
	.set	macro
	.set	reorder

	bne	$19,$2,$L250
	lw	$2,36($sp)
	beq	$2,$0,$L251
	lhu	$4,0($2)
	beq	$4,$0,$L251
	lw	$5,32($16)
	lhu	$2,2($22)
	andi	$7,$5,0xffff
	lhu	$6,38($16)
	subu	$3,$3,$7
	srl	$5,$5,16
	subu	$3,$3,$5
	addu	$2,$2,$3
	subu	$2,$2,$6
	addu	$2,$4,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L252
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	lw	$3,36($sp)
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L251
	sh	$2,0($3)
	.set	macro
	.set	reorder

$L252:
	lw	$4,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	j	$L251
	sh	$2,0($4)
	.set	macro
	.set	reorder

$L250:
	lw	$4,32($16)
	lhu	$2,2($22)
	andi	$6,$4,0xffff
	lhu	$5,38($16)
	subu	$3,$3,$6
	srl	$4,$4,16
	lw	$6,36($sp)
	subu	$3,$3,$4
	addu	$2,$2,$3
	lhu	$3,0($6)
	subu	$2,$2,$5
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L253
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L251
	sh	$2,0($6)
	.set	macro
	.set	reorder

$L253:
	lw	$7,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	sh	$2,0($7)
$L251:
	lw	$2,36($16)
	.set	noreorder
	.set	nomacro
	j	$L291
	sh	$2,2($22)
	.set	macro
	.set	reorder

$L219:
	lw	$3,24($16)
	andi	$4,$23,0xffff
	srl	$23,$23,16
	lhu	$2,10($17)
	addu	$23,$4,$23
	andi	$4,$3,0xffff
	subu	$4,$23,$4
	srl	$3,$3,16
	subu	$3,$4,$3
	addu	$2,$2,$3
	.set	noreorder
	.set	nomacro
	bgez	$2,$L254
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L255
	sh	$2,10($17)
	.set	macro
	.set	reorder

$L254:
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	sh	$2,10($17)
$L255:
	lw	$4,32($16)
	lhu	$3,18($sp)
	lw	$8,24($sp)
	andi	$5,$4,0xffff
	lhu	$2,10($17)
	srl	$4,$4,16
	addu	$3,$3,$8
	subu	$5,$3,$5
	subu	$4,$5,$4
	addu	$2,$2,$4
	.set	noreorder
	.set	nomacro
	bgez	$2,$L256
	sra	$4,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$4,$2,16
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L257
	sh	$2,10($17)
	.set	macro
	.set	reorder

$L256:
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	sh	$2,10($17)
$L257:
	lw	$11,40($sp)
	.set	noreorder
	.set	nomacro
	beq	$11,$0,$L258
	li	$2,17			# 0x11
	.set	macro
	.set	reorder

	bne	$19,$2,$L259
	lw	$2,36($sp)
	beq	$2,$0,$L260
	lhu	$4,0($2)
	beq	$4,$0,$L260
	lw	$5,24($16)
	lhu	$2,0($22)
	andi	$7,$5,0xffff
	lhu	$6,30($16)
	subu	$23,$23,$7
	srl	$5,$5,16
	subu	$5,$23,$5
	addu	$2,$2,$5
	subu	$2,$2,$6
	addu	$2,$4,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L261
	sra	$4,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$4,$2,16
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	lw	$4,36($sp)
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L262
	sh	$2,0($4)
	.set	macro
	.set	reorder

$L261:
	lw	$5,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	sh	$2,0($5)
$L262:
	lw	$4,32($16)
	lhu	$2,2($22)
	andi	$6,$4,0xffff
	lhu	$5,38($16)
	subu	$3,$3,$6
	srl	$4,$4,16
	lw	$6,36($sp)
	subu	$3,$3,$4
	addu	$2,$2,$3
	lhu	$3,0($6)
	subu	$2,$2,$5
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L263
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L260
	sh	$2,0($6)
	.set	macro
	.set	reorder

$L263:
	lw	$7,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	j	$L260
	sh	$2,0($7)
	.set	macro
	.set	reorder

$L259:
	lw	$4,24($16)
	lhu	$2,0($22)
	andi	$6,$4,0xffff
	lw	$8,36($sp)
	subu	$23,$23,$6
	srl	$4,$4,16
	subu	$4,$23,$4
	lhu	$5,30($16)
	addu	$2,$2,$4
	lhu	$4,0($8)
	subu	$2,$2,$5
	addu	$2,$4,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L264
	sra	$4,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$4,$2,16
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L265
	sh	$2,0($8)
	.set	macro
	.set	reorder

$L264:
	lw	$11,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$4,$2
	sra	$4,$2,16
	addu	$2,$4,$2
	sh	$2,0($11)
$L265:
	lw	$4,32($16)
	lhu	$2,2($22)
	andi	$6,$4,0xffff
	lhu	$5,38($16)
	srl	$4,$4,16
	subu	$3,$3,$6
	subu	$3,$3,$4
	lw	$4,36($sp)
	addu	$2,$2,$3
	subu	$2,$2,$5
	lhu	$3,0($4)
	addu	$2,$3,$2
	.set	noreorder
	.set	nomacro
	bgez	$2,$L266
	sra	$3,$2,16
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L260
	sh	$2,0($4)
	.set	macro
	.set	reorder

$L266:
	lw	$5,36($sp)
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	sh	$2,0($5)
$L260:
	lw	$2,28($16)
	sh	$2,0($22)
	lw	$2,36($16)
	sh	$2,2($22)
$L258:
	lw	$2,24($16)
	sw	$2,12($17)
$L291:
	lw	$2,32($16)
	sw	$2,16($17)
$L220:
	lbu	$2,8($17)
	lbu	$3,9($17)
	addiu	$4,$2,-1
	sll	$2,$2,8
	andi	$4,$4,0x00ff
	lhu	$5,10($17)
	sll	$6,$4,8
	or	$2,$2,$3
	or	$3,$6,$3
	subu	$3,$2,$3
	addu	$2,$5,$3
	.set	noreorder
	.set	nomacro
	bgez	$2,$L267
	sb	$4,8($17)
	.set	macro
	.set	reorder

	subu	$2,$0,$2
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	nor	$2,$0,$2
	.set	noreorder
	.set	nomacro
	j	$L268
	sh	$2,10($17)
	.set	macro
	.set	reorder

$L267:
	sra	$3,$2,16
	andi	$2,$2,0xffff
	addu	$2,$3,$2
	sra	$3,$2,16
	addu	$2,$3,$2
	sh	$2,10($17)
$L268:
	lui	$2,%hi(rtl_set_skb_ip_summed)
	move	$5,$0
	addiu	$2,$2,%lo(rtl_set_skb_ip_summed)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_dev)
	move	$4,$18
	addiu	$2,$2,%lo(rtl_set_skb_dev)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$0
	.set	macro
	.set	reorder

	lui	$2,%hi(fastpath_set_qos_mark)
	lw	$5,48($16)
	lw	$6,52($16)
	addiu	$2,$2,%lo(fastpath_set_qos_mark)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$2,%hi(jiffies)
	lw	$2,%lo(jiffies)($2)
	move	$4,$17
	move	$5,$22
	sw	$2,40($16)
	lui	$2,%hi(fast_path_post_process_xmit_check)
	addiu	$2,$2,%lo(fast_path_post_process_xmit_check)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$6,$18
	.set	macro
	.set	reorder

	li	$3,1			# 0x1
	.set	noreorder
	.set	nomacro
	beq	$2,$3,$L287
	lui	$2,%hi(statistic_fastpath)
	.set	macro
	.set	reorder

	lw	$3,%lo(statistic_fastpath)($2)
	addiu	$3,$3,1
	sw	$3,%lo(statistic_fastpath)($2)
	lui	$2,%hi(ip_finish_output3)
	addiu	$2,$2,%lo(ip_finish_output3)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L175
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L205:
	lw	$16,64($16)
$L204:
	.set	noreorder
	.set	nomacro
	bne	$16,$0,$L269
	lui	$2,%hi(rtl_set_skb_inDev)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_set_skb_inDev)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	move	$4,$17
	move	$5,$22
	lui	$25,%hi(fast_path_post_process_return_check)
	move	$6,$18
	lw	$31,84($sp)
	lw	$fp,80($sp)
	addiu	$25,$25,%lo(fast_path_post_process_return_check)
	lw	$23,76($sp)
	lw	$22,72($sp)
	lw	$21,68($sp)
	lw	$20,64($sp)
	lw	$19,60($sp)
	lw	$18,56($sp)
	lw	$17,52($sp)
	lw	$16,48($sp)
	.set	noreorder
	.set	nomacro
	jr	$25
	addiu	$sp,$sp,88
	.set	macro
	.set	reorder

$L285:
	.set	noreorder
	.set	nomacro
	j	$L175
	move	$2,$0
	.set	macro
	.set	reorder

$L287:
	li	$2,1			# 0x1
$L175:
	lw	$31,84($sp)
	lw	$fp,80($sp)
	lw	$23,76($sp)
	lw	$22,72($sp)
	lw	$21,68($sp)
	lw	$20,64($sp)
	lw	$19,60($sp)
	lw	$18,56($sp)
	lw	$17,52($sp)
	lw	$16,48($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,88
	.set	macro
	.set	reorder

$L179:
	lw	$4,12($22)
	li	$5,65536			# 0x10000
	and	$5,$4,$5
	beq	$5,$0,$L290
	.set	noreorder
	.set	nomacro
	j	$L297
	srl	$3,$23,8
	.set	macro
	.set	reorder

$L295:
	subu	$7,$9,$7
	lw	$3,%lo(udp_cache_table)($3)
	lw	$9,0($3)
	addu	$7,$9,$7
	lw	$21,0($7)
	.set	noreorder
	.set	nomacro
	j	$L272
	li	$4,1			# 0x1
	.set	macro
	.set	reorder

$L296:
	lw	$7,28($sp)
	.set	noreorder
	.set	nomacro
	beq	$7,$0,$L273
	lui	$4,%hi(negative_cache_list_free)
	.set	macro
	.set	reorder

	li	$8,1			# 0x1
	li	$11,1			# 0x1
	sw	$8,28($sp)
	.set	noreorder
	.set	nomacro
	j	$L192
	sw	$11,40($sp)
	.set	macro
	.set	reorder

	.end	enter_fast_path
	.size	enter_fast_path, .-enter_fast_path
	.section	.rodata.str1.4
	.align	2
$LC7:
	.ascii	"napt num: %d, path num: %d.\012\000"
	.text
	.align	2
	.globl	fastpath_dump_napt_entry_num
	.set	nomips16
	.ent	fastpath_dump_napt_entry_num
	.type	fastpath_dump_napt_entry_num, @function
fastpath_dump_napt_entry_num:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(path_list_inuse)
	move	$16,$5
	lw	$2,%lo(path_list_inuse)($2)
	j	$L304
	move	$7,$0

$L305:
	lw	$2,72($2)
	addiu	$7,$7,1
$L304:
	bne	$2,$0,$L305
	move	$6,$0

	lui	$2,%hi(napt_list_inuse)
	lw	$2,%lo(napt_list_inuse)($2)
	j	$L306
	nop

$L307:
	lw	$2,44($2)
	addiu	$6,$6,1
$L306:
	bne	$2,$0,$L307
	lui	$5,%hi($LC7)

	lui	$2,%hi(sprintf)
	addu	$4,$4,$16
	addiu	$2,$2,%lo(sprintf)
	jalr	$2
	addiu	$5,$5,%lo($LC7)

	addu	$2,$2,$16
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	fastpath_dump_napt_entry_num
	.size	fastpath_dump_napt_entry_num, .-fastpath_dump_napt_entry_num
	.section	.rodata.str1.4
	.align	2
$LC8:
	.ascii	"fp_napt\000"
	.align	2
$LC9:
	.ascii	"fp_path\000"
	.text
	.align	2
	.globl	init_fastpath_debug_proc
	.set	nomips16
	.ent	init_fastpath_debug_proc
	.type	init_fastpath_debug_proc, @function
init_fastpath_debug_proc:
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 24, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$17,32($sp)
	sw	$16,28($sp)
	lui	$16,%hi(proc_root)
	lui	$4,%hi($LC8)
	lui	$7,%hi(fastpath_napt_proc_fops)
	lui	$17,%hi(proc_create_data)
	addiu	$6,$16,%lo(proc_root)
	addiu	$17,$17,%lo(proc_create_data)
	addiu	$4,$4,%lo($LC8)
	move	$5,$0
	addiu	$7,$7,%lo(fastpath_napt_proc_fops)
	jalr	$17
	sw	$0,16($sp)

	lui	$4,%hi($LC9)
	lui	$7,%hi(fastpath_path_proc_fops)
	addiu	$6,$16,%lo(proc_root)
	lui	$3,%hi(fp_napt)
	addiu	$4,$4,%lo($LC9)
	move	$5,$0
	addiu	$7,$7,%lo(fastpath_path_proc_fops)
	sw	$2,%lo(fp_napt)($3)
	jalr	$17
	sw	$0,16($sp)

	lui	$3,%hi(fp_path)
	lw	$31,36($sp)
	lw	$17,32($sp)
	lw	$16,28($sp)
	sw	$2,%lo(fp_path)($3)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	init_fastpath_debug_proc
	.size	init_fastpath_debug_proc, .-init_fastpath_debug_proc
	.align	2
	.globl	remove_fastpath_debug_proc
	.set	nomips16
	.ent	remove_fastpath_debug_proc
	.type	remove_fastpath_debug_proc, @function
remove_fastpath_debug_proc:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$16,%hi(fp_napt)
	lw	$2,%lo(fp_napt)($16)
	beq	$2,$0,$L310
	lui	$4,%hi($LC8)

	lui	$5,%hi(proc_root)
	lui	$2,%hi(remove_proc_entry)
	addiu	$4,$4,%lo($LC8)
	addiu	$2,$2,%lo(remove_proc_entry)
	jalr	$2
	addiu	$5,$5,%lo(proc_root)

	sw	$0,%lo(fp_napt)($16)
$L310:
	lui	$16,%hi(fp_path)
	lw	$2,%lo(fp_path)($16)
	beq	$2,$0,$L309
	lui	$4,%hi($LC9)

	lui	$5,%hi(proc_root)
	lui	$2,%hi(remove_proc_entry)
	addiu	$4,$4,%lo($LC9)
	addiu	$2,$2,%lo(remove_proc_entry)
	jalr	$2
	addiu	$5,$5,%lo(proc_root)

	sw	$0,%lo(fp_path)($16)
$L309:
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	remove_fastpath_debug_proc
	.size	remove_fastpath_debug_proc, .-remove_fastpath_debug_proc
	.align	2
	.globl	init_table_napt
	.set	nomips16
	.ent	init_table_napt
	.type	init_table_napt, @function
init_table_napt:
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
	lui	$19,%hi(kmalloc_caches)
	addiu	$19,$19,%lo(kmalloc_caches)
	move	$17,$4
	lui	$18,%hi(kmem_cache_alloc)
	move	$20,$5
	lw	$4,20($19)
	addiu	$18,$18,%lo(kmem_cache_alloc)
	li	$5,32			# 0x20
	jalr	$18
	lui	$22,%hi(table_napt)

	move	$21,$2
	beq	$2,$0,$L319
	sw	$2,%lo(table_napt)($22)

	lui	$6,%hi(napt_list_inuse)
	lui	$3,%hi(napt_list_free)
	addiu	$2,$6,%lo(napt_list_inuse)
	addiu	$16,$3,%lo(napt_list_free)
	sw	$0,8($2)
	sll	$5,$17,4
	sw	$2,4($2)
	lui	$2,%hi(napt_table_list_max)
	sw	$17,%lo(napt_table_list_max)($2)
	sll	$4,$17,2
	lui	$2,%hi(__kmalloc)
	subu	$4,$5,$4
	sw	$0,%lo(napt_list_free)($3)
	li	$5,32			# 0x20
	sw	$0,%lo(napt_list_inuse)($6)
	addiu	$2,$2,%lo(__kmalloc)
	sw	$0,8($16)
	jalr	$2
	sw	$16,4($16)

	lw	$3,%lo(table_napt)($22)
	sw	$2,0($21)
	lw	$2,0($3)
	beq	$2,$0,$L319
	move	$4,$0

	j	$L314
	move	$2,$0

$L315:
	lw	$5,0($3)
	addu	$5,$5,$2
	sw	$0,8($5)
	lw	$5,0($3)
	addu	$5,$5,$2
	sw	$0,0($5)
	lw	$5,0($3)
	addu	$5,$5,$2
	addiu	$2,$2,12
	sw	$5,4($5)
$L314:
	slt	$5,$4,$17
	bne	$5,$0,$L315
	addiu	$4,$4,1

	j	$L316
	move	$17,$0

$L317:
	lw	$4,24($19)
	jalr	$18
	addiu	$17,$17,1

	beq	$2,$0,$L320
	addiu	$4,$2,44

	lw	$3,4($16)
	sw	$0,44($2)
	sw	$3,48($2)
	sw	$2,0($3)
	lw	$2,8($16)
	sw	$4,4($16)
	addiu	$2,$2,1
	sw	$2,8($16)
$L316:
	slt	$2,$17,$20
	bne	$2,$0,$L317
	li	$5,32			# 0x20

	j	$L313
	move	$2,$0

$L319:
	j	$L313
	li	$2,-1			# 0xffffffffffffffff

$L320:
	li	$2,-2			# 0xfffffffffffffffe
$L313:
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
	.end	init_table_napt
	.size	init_table_napt, .-init_table_napt
	.align	2
	.globl	init_table_path
	.set	nomips16
	.ent	init_table_path
	.type	init_table_path, @function
init_table_path:
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
	lui	$20,%hi(kmalloc_caches)
	addiu	$20,$20,%lo(kmalloc_caches)
	move	$18,$4
	lui	$19,%hi(kmem_cache_alloc)
	move	$21,$5
	lw	$4,20($20)
	addiu	$19,$19,%lo(kmem_cache_alloc)
	li	$5,32			# 0x20
	jalr	$19
	lui	$17,%hi(table_path)

	move	$22,$2
	beq	$2,$0,$L328
	sw	$2,%lo(table_path)($17)

	lui	$6,%hi(path_list_inuse)
	lui	$3,%hi(path_list_free)
	addiu	$2,$6,%lo(path_list_inuse)
	addiu	$16,$3,%lo(path_list_free)
	sw	$0,8($2)
	sll	$5,$18,4
	sw	$2,4($2)
	lui	$2,%hi(path_table_list_max)
	sw	$18,%lo(path_table_list_max)($2)
	sll	$4,$18,2
	lui	$2,%hi(__kmalloc)
	subu	$4,$5,$4
	sw	$0,%lo(path_list_inuse)($6)
	li	$5,32			# 0x20
	sw	$0,8($16)
	addiu	$2,$2,%lo(__kmalloc)
	sw	$0,%lo(path_list_free)($3)
	jalr	$2
	sw	$16,4($16)

	sw	$2,0($22)
	lw	$2,%lo(table_path)($17)
	lw	$2,0($2)
	beq	$2,$0,$L328
	move	$3,$0

	j	$L323
	move	$2,$0

$L324:
	lw	$4,%lo(table_path)($17)
	lw	$5,0($4)
	addu	$5,$5,$2
	sw	$0,8($5)
	lw	$4,0($4)
	addu	$4,$4,$2
	sw	$0,0($4)
	lw	$4,%lo(table_path)($17)
	lw	$4,0($4)
	addu	$4,$4,$2
	addiu	$2,$2,12
	sw	$4,4($4)
$L323:
	slt	$4,$3,$18
	bne	$4,$0,$L324
	addiu	$3,$3,1

	j	$L325
	move	$17,$0

$L326:
	lw	$4,4($20)
	jalr	$19
	addiu	$17,$17,1

	beq	$2,$0,$L329
	addiu	$4,$2,72

	lw	$3,4($16)
	sw	$0,72($2)
	sw	$3,76($2)
	sw	$2,0($3)
	lw	$2,8($16)
	sw	$4,4($16)
	addiu	$2,$2,1
	sw	$2,8($16)
$L325:
	slt	$2,$17,$21
	bne	$2,$0,$L326
	li	$5,32			# 0x20

	j	$L322
	move	$2,$0

$L328:
	j	$L322
	li	$2,-1			# 0xffffffffffffffff

$L329:
	li	$2,-2			# 0xfffffffffffffffe
$L322:
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
	.end	init_table_path
	.size	init_table_path, .-init_table_path
	.section	.rodata.str1.4
	.align	2
$LC10:
	.ascii	"%s:%s\012\000"
	.align	2
$LC11:
	.ascii	"Realtek FastPath\000"
	.align	2
$LC12:
	.ascii	"v1.03\000"
	.text
	.align	2
	.globl	get_fastpath_module_info
	.set	nomips16
	.ent	get_fastpath_module_info
	.type	get_fastpath_module_info, @function
get_fastpath_module_info:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L332
	nop

	lui	$5,%hi($LC10)
	lui	$6,%hi($LC11)
	lui	$7,%hi($LC12)
	lui	$25,%hi(sprintf)
	addiu	$5,$5,%lo($LC10)
	addiu	$6,$6,%lo($LC11)
	addiu	$7,$7,%lo($LC12)
	addiu	$25,$25,%lo(sprintf)
	jr	$25
	nop

$L332:
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	get_fastpath_module_info
	.size	get_fastpath_module_info, .-get_fastpath_module_info
	.globl	fastpath_path_proc_fops
	.data
	.align	2
	.type	fastpath_path_proc_fops, @object
	.size	fastpath_path_proc_fops, 108
fastpath_path_proc_fops:
	.space	4
	.word	seq_lseek
	.word	seq_read
	.word	fastpath_path_single_write
	.space	28
	.word	fastpath_path_single_open
	.space	4
	.word	single_release
	.space	52
	.globl	fastpath_napt_proc_fops
	.align	2
	.type	fastpath_napt_proc_fops, @object
	.size	fastpath_napt_proc_fops, 108
fastpath_napt_proc_fops:
	.space	4
	.word	seq_lseek
	.word	seq_read
	.word	fastpath_napt_single_write
	.space	28
	.word	fastpath_napt_single_open
	.space	4
	.word	single_release
	.space	52
	.globl	negative_cache_table
	.section	.bss,"aw",@nobits
	.align	2
	.type	negative_cache_table, @object
	.size	negative_cache_table, 4
negative_cache_table:
	.space	4
	.globl	negative_cache_list_free
	.align	2
	.type	negative_cache_list_free, @object
	.size	negative_cache_list_free, 12
negative_cache_list_free:
	.space	12
	.globl	udp_cache_table
	.align	2
	.type	udp_cache_table, @object
	.size	udp_cache_table, 4
udp_cache_table:
	.space	4
	.globl	udp_cache_list_free
	.align	2
	.type	udp_cache_list_free, @object
	.size	udp_cache_list_free, 12
udp_cache_list_free:
	.space	12
	.globl	fp_napt
	.align	2
	.type	fp_napt, @object
	.size	fp_napt, 4
fp_napt:
	.space	4
	.globl	fp_route
	.align	2
	.type	fp_route, @object
	.size	fp_route, 4
fp_route:
	.space	4
	.globl	fp_path
	.align	2
	.type	fp_path, @object
	.size	fp_path, 4
fp_path:
	.space	4
	.globl	fp_arp
	.align	2
	.type	fp_arp, @object
	.size	fp_arp, 4
fp_arp:
	.space	4
	.globl	table_path
	.align	2
	.type	table_path, @object
	.size	table_path, 4
table_path:
	.space	4
	.globl	path_list_free
	.align	2
	.type	path_list_free, @object
	.size	path_list_free, 12
path_list_free:
	.space	12
	.globl	path_list_inuse
	.align	2
	.type	path_list_inuse, @object
	.size	path_list_inuse, 12
path_list_inuse:
	.space	12
	.globl	napt_list_free
	.align	2
	.type	napt_list_free, @object
	.size	napt_list_free, 12
napt_list_free:
	.space	12
	.globl	napt_list_inuse
	.align	2
	.type	napt_list_inuse, @object
	.size	napt_list_inuse, 12
napt_list_inuse:
	.space	12
	.globl	route_list_free
	.align	2
	.type	route_list_free, @object
	.size	route_list_free, 12
route_list_free:
	.space	12
	.globl	route_list_inuse
	.align	2
	.type	route_list_inuse, @object
	.size	route_list_inuse, 12
route_list_inuse:
	.space	12
	.local	max_udp_frag_entry
	.comm	max_udp_frag_entry,4,4
	.local	napt_table_list_max
	.comm	napt_table_list_max,4,4
	.local	table_napt
	.comm	table_napt,4,4
	.local	path_table_list_max
	.comm	path_table_list_max,4,4
	.ident	"GCC: (Realtek RSDK-4.6.4 Build 2002) 4.6.4"
