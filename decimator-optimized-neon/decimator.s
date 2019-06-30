	.arch armv8-a+crc
	.file	"decimator.c"
	.text
	.align	2
	.p2align 3,,7
	.global	fastdecimator_init
	.type	fastdecimator_init, %function
fastdecimator_init:
.LFB3859:
	.cfi_startproc
	stp	x29, x30, [sp, -176]!
	.cfi_def_cfa_offset 176
	.cfi_offset 29, -176
	.cfi_offset 30, -168
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -160
	.cfi_offset 20, -152
	mov	w20, w3
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -144
	.cfi_offset 22, -136
	mov	w22, w4
	stp	x23, x24, [sp, 48]
	.cfi_offset 23, -128
	.cfi_offset 24, -120
	mov	x24, x0
	mov	w0, 0
	stp	x25, x26, [sp, 64]
	stp	d8, d9, [sp, 96]
	.cfi_offset 25, -112
	.cfi_offset 26, -104
	.cfi_offset 72, -80
	.cfi_offset 73, -72
	fmov	s9, s0
	stp	d10, d11, [sp, 112]
	.cfi_offset 74, -64
	.cfi_offset 75, -56
	cbnz	w1, .L27
.L2:
	fcvt	d9, s9
	fmov	d0, 4.0e+0
	ucvtf	d2, w20
	fmov	d8, 1.0e+0
	fmov	d1, 5.0e-1
	strb	w0, [x24]
	str	wzr, [x24, 1120]
	add	x26, x24, 96
	fdiv	d0, d0, d9
	fdiv	d8, d8, d2
	fadd	d0, d0, d1
	fcvt	s8, d8
	fcvtzs	w19, d0
	orr	w19, w19, 1
	add	w0, w19, 6
	adds	w1, w19, 3
	csel	w0, w0, w1, mi
	add	w23, w19, w19, lsr 31
	asr	w0, w0, 2
	stp	w20, w0, [x24, 80]
	asr	w23, w23, 1
	cbz	w0, .L3
	sub	w0, w0, #1
	add	x0, x24, x0, lsl 4
	stp	xzr, xzr, [x0, 96]
.L3:
	cmp	w19, 1
	ble	.L4
	adrp	x0, .LC3
	sxtw	x21, w23
	scvtf	s0, w23
	fcvt	d8, s8
	add	x21, x21, 23
	ldr	d9, [x0, #:lo12:.LC3]
	fmov	s10, 1.0e+0
	adrp	x0, .LC4
	lsl	x21, x21, 2
	str	x27, [sp, 80]
	.cfi_offset 27, -96
	add	x27, x21, 4
	movi	v11.2s, #0
	mov	x25, 1
	fmul	d8, d8, d9
	fdiv	s10, s10, s0
	add	x27, x24, x27
	add	x21, x24, x21
	stp	d12, d13, [sp, 128]
	.cfi_offset 77, -40
	.cfi_offset 76, -48
	fmov	d12, 5.0e-1
	stp	d14, d15, [sp, 144]
	.cfi_offset 79, -24
	.cfi_offset 78, -32
	fmov	d15, 1.0e+0
	ldr	d14, [x0, #:lo12:.LC4]
	b	.L9
	.p2align 2
.L5:
	fcvt	d1, s1
	fmul	d0, d1, d14
	str	d1, [sp, 160]
	bl	cos
	fmov	d13, d0
	ldr	d1, [sp, 160]
	fmul	d0, d1, d9
	bl	cos
	adrp	x0, .LC5
	ldr	d1, [x0, #:lo12:.LC5]
	adrp	x0, .LC6
	ldr	d2, [x0, #:lo12:.LC6]
	fmadd	d2, d13, d1, d2
	fmsub	d2, d0, d12, d2
	fcvt	s2, d2
.L8:
	scvtf	d13, w20
	str	s2, [sp, 160]
	fmul	d0, d13, d8
	bl	sin
	fdiv	d0, d0, d13
	ldr	s2, [sp, 160]
	fmov	s1, 2.0e+0
	fcvt	d2, s2
	fmul	d0, d0, d2
	fcvt	s0, d0
	str	s0, [x21], -4
	fmadd	s11, s0, s1, s11
	str	s0, [x27, x25, lsl 2]
	add	x25, x25, 1
	cmp	w23, w25
	blt	.L28
.L9:
	scvtf	s1, w25
	cmp	w22, 1
	mov	w20, w25
	fmul	s1, s1, s10
	fcvt	d1, s1
	fadd	d1, d1, d15
	fmul	d1, d1, d12
	fcvt	s1, d1
	beq	.L5
	cmp	w22, 2
	bne	.L29
	fcvt	d1, s1
	fmul	d0, d1, d9
	bl	cos
	adrp	x0, .LC7
	ldr	d1, [x0, #:lo12:.LC7]
	adrp	x0, .LC8
	ldr	d2, [x0, #:lo12:.LC8]
	fmsub	d0, d0, d1, d2
	fcvt	s2, d0
	b	.L8
	.p2align 2
.L28:
	ldr	x27, [sp, 80]
	.cfi_restore 27
	ldp	d12, d13, [sp, 128]
	.cfi_restore 77
	.cfi_restore 76
	ldp	d14, d15, [sp, 144]
	.cfi_restore 79
	.cfi_restore 78
.L10:
	fmov	s0, 1.0e+0
	sub	w0, w19, #1
	fdiv	s11, s0, s11
	cmp	w0, 2
	bls	.L16
	lsr	w0, w19, 2
	mov	x1, x26
	dup	v1.4s, v11.s[0]
	add	x0, x26, x0, uxtw 4
	.p2align 3
.L13:
	ldr	q0, [x1]
	fmul	v0.4s, v0.4s, v1.4s
	str	q0, [x1], 16
	cmp	x1, x0
	bne	.L13
	and	w0, w19, -4
	cmp	w0, w19
	beq	.L11
.L12:
	sxtw	x2, w0
	add	w1, w0, 1
	cmp	w19, w1
	lsl	x1, x2, 2
	ldr	s0, [x26, x2, lsl 2]
	fmul	s0, s0, s11
	str	s0, [x26, x2, lsl 2]
	ble	.L11
	add	x2, x1, 4
	add	w0, w0, 2
	cmp	w19, w0
	ldr	s0, [x26, x2]
	fmul	s0, s0, s11
	str	s0, [x26, x2]
	ble	.L11
	add	x1, x1, 8
	ldr	s0, [x26, x1]
	fmul	s11, s0, s11
	str	s11, [x26, x1]
.L11:
	adrp	x0, :got:stderr
	mov	w2, w19
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	ldr	x19, [x0, #:got_lo12:stderr]
	ldr	x0, [x19]
	bl	fprintf
	ldr	w2, [x24, 84]
	adrp	x1, .LC2
	ldr	x0, [x19]
	add	x1, x1, :lo12:.LC2
	bl	fprintf
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	d8, d9, [sp, 96]
	ldp	d10, d11, [sp, 112]
	ldp	x29, x30, [sp], 176
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 74
	.cfi_restore 75
	.cfi_restore 72
	.cfi_restore 73
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.p2align 2
.L27:
	.cfi_restore_state
	adrp	x0, .LC3
	ucvtf	d8, w1
	ucvtf	d0, w2
	add	x21, sp, 172
	ldr	d1, [x0, #:lo12:.LC3]
	add	x23, sp, 168
	mov	x0, x21
	mov	x1, x23
	fmul	d8, d8, d1
	fdiv	d8, d8, d0
	fcvt	s8, d8
	fmov	s0, s8
	bl	sincosf
	fadd	s0, s8, s8
	fmov	s1, 1.0e+0
	ldr	w2, [sp, 168]
	mov	x1, x23
	mov	x0, x21
	str	s1, [x24, 16]
	ldr	w26, [sp, 172]
	str	w2, [x24, 20]
	bl	sincosf
	fmov	s0, 3.0e+0
	mov	x1, x23
	ldp	w2, w25, [sp, 168]
	fmul	s0, s8, s0
	str	w2, [x24, 24]
	mov	x0, x21
	bl	sincosf
	fmov	s0, 4.0e+0
	mov	x1, x23
	ldp	w3, w2, [sp, 168]
	fmul	s0, s8, s0
	stp	w3, wzr, [x24, 28]
	mov	x0, x21
	stp	w26, w25, [x24, 36]
	str	w2, [x24, 44]
	bl	sincosf
	ldp	w2, w1, [sp, 168]
	mov	w0, 1
	stp	w2, w2, [x24, 48]
	stp	w2, w2, [x24, 56]
	stp	w1, w1, [x24, 64]
	stp	w1, w1, [x24, 72]
	b	.L2
	.p2align 2
.L4:
	bne	.L11
	movi	v11.2s, #0
	b	.L10
	.p2align 2
.L16:
	mov	w0, 0
	b	.L12
	.p2align 2
.L29:
	.cfi_offset 27, -96
	.cfi_offset 76, -48
	.cfi_offset 77, -40
	.cfi_offset 78, -32
	.cfi_offset 79, -24
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	puts
	mov	w0, -1
	bl	exit
	.cfi_endproc
.LFE3859:
	.size	fastdecimator_init, .-fastdecimator_init
	.align	2
	.p2align 3,,7
	.global	fastdecimator
	.type	fastdecimator, %function
fastdecimator:
.LFB3860:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	mov	x4, x1
	mov	x29, sp
	ldr	w5, [x4], 4
	str	x23, [sp, 48]
	.cfi_offset 23, -16
	ldr	w23, [x2, 1120]
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -32
	.cfi_offset 22, -24
	mov	x21, x2
	ldrb	w2, [x2]
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -48
	.cfi_offset 20, -40
	add	x19, x1, 397312
	mov	x20, x1
	ubfiz	x1, x23, 2, 32
	mov	x22, x0
	add	x1, x1, 1124
	add	x19, x19, 2692
	add	x0, x21, x1
	cbz	w2, .L31
	lsr	w3, w5, 2
	add	x1, x1, 401408
	add	x1, x1, 16
	add	x2, x21, x1
	tst	x3, 3
	bne	.L45
	add	x6, x21, 16
	ldr	q1, [x21, 16]
	ldr	q0, [x6, 16]
	ldr	q7, [x6, 32]
	ldr	q16, [x6, 48]
	cbz	w3, .L41
	sub	w3, w3, #1
	mov	x1, 0
	lsr	w3, w3, 2
	add	x3, x3, 1
	lsl	x3, x3, 4
	.p2align 3
.L34:
	ldr	q5, [x4, x1]
	ldr	q6, [x19, x1]
	fmul	v4.4s, v5.4s, v1.4s
	fmul	v2.4s, v7.4s, v1.4s
	fmul	v3.4s, v6.4s, v1.4s
	fmul	v17.4s, v7.4s, v0.4s
	fmls	v4.4s, v6.4s, v0.4s
	fmls	v2.4s, v16.4s, v0.4s
	fmla	v3.4s, v5.4s, v0.4s
	mov	v0.16b, v17.16b
	str	q4, [x0, x1]
	str	q3, [x2, x1]
	add	x1, x1, 16
	cmp	x3, x1
	fmla	v0.4s, v16.4s, v1.4s
	mov	v1.16b, v2.16b
	bne	.L34
.L33:
	str	q2, [x21, 16]
	str	q0, [x6, 16]
	b	.L35
.L31:
	ubfiz	x2, x5, 2, 32
	mov	x1, x4
	add	x2, x2, 4
	add	x2, x20, x2
	sub	x2, x2, x4
	asr	x2, x2, 2
	bl	memcpy
	ldr	w2, [x20]
	mov	x1, x19
	ldr	w0, [x21, 1120]
	add	x2, x2, 98304
	add	x2, x2, 1697
	add	x0, x0, 98304
	add	x0, x0, 2333
	add	x2, x20, x2, lsl 2
	sub	x2, x2, x19
	add	x0, x21, x0, lsl 2
	asr	x2, x2, 2
	bl	memcpy
	ldr	w5, [x20]
	ldr	w23, [x21, 1120]
.L35:
	add	w23, w23, w5
	add	x3, x21, 112
	ldp	w6, w5, [x21, 80]
	add	x7, x22, 397312
	mov	x8, 9236
	add	x7, x7, 2688
	sub	w0, w5, #1
	mov	x20, 1
	add	w4, w6, w5, lsl 2
	mov	w1, 0
	add	x3, x3, x0, uxtw 4
	sub	w4, w23, w4
	mov	w19, 0
	movk	x8, 0x6, lsl 16
	str	w23, [x21, 1120]
	.p2align 3
.L36:
	movi	v1.2s, #0
	fmov	s2, s1
	cbz	w5, .L40
	movi	v1.4s, 0
	sbfiz	x1, x1, 2, 32
	add	x2, x1, 1028
	add	x0, x21, 96
	add	x1, x1, x8
	mov	v2.16b, v1.16b
	.p2align 3
.L37:
	ldr	q0, [x0]
	ldr	q4, [x0, x2]
	ldr	q3, [x0, x1]
	add	x0, x0, 16
	fmla	v2.4s, v0.4s, v4.4s
	cmp	x3, x0
	fmla	v1.4s, v0.4s, v3.4s
	bne	.L37
	dup	s3, v2.s[3]
	dup	s7, v2.s[2]
	dup	s0, v1.s[3]
	dup	s6, v1.s[2]
	dup	s5, v2.s[1]
	dup	s4, v1.s[1]
	fadd	s3, s3, s7
	fadd	s0, s0, s6
	fadd	s3, s3, s5
	fadd	s0, s0, s4
	fadd	s2, s3, s2
	fadd	s1, s0, s1
.L40:
	str	s2, [x22, x20, lsl 2]
	add	w19, w19, w6
	str	s1, [x7, x20, lsl 2]
	cmp	w4, w19
	mov	w1, w19
	add	x0, x20, 1
	bcc	.L38
	mov	x20, x0
	b	.L36
	.p2align 2
.L38:
	add	x1, x21, x19, sxtw 2
	add	x2, x21, 1124
	add	x1, x1, 1124
	mov	x0, x2
	sub	x2, x1, x2
	sub	w19, w23, w19
	asr	x2, x2, 2
	bl	memmove
	ldr	x23, [sp, 48]
	str	w19, [x21, 1120]
	str	w20, [x22]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L41:
	.cfi_restore_state
	mov	v2.16b, v1.16b
	b	.L33
.L45:
	adrp	x3, :got:stderr
	mov	x2, 43
	mov	x1, 1
	adrp	x0, .LC9
	ldr	x3, [x3, #:got_lo12:stderr]
	add	x0, x0, :lo12:.LC9
	ldr	x3, [x3]
	bl	fwrite
	mov	w0, -1
	bl	exit
	.cfi_endproc
.LFE3860:
	.size	fastdecimator, .-fastdecimator
	.section	.rodata.cst8,"aM",@progbits,8
	.align	3
.LC3:
	.word	1413754136
	.word	1075388923
.LC4:
	.word	1413754136
	.word	1076437499
.LC5:
	.word	1202590843
	.word	1068792545
.LC6:
	.word	2920577761
	.word	1071309127
.LC7:
	.word	3607772529
	.word	1071476899
.LC8:
	.word	343597384
	.word	1071728558
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"Bad type of filter! Exit."
	.zero	6
.LC1:
	.string	"taps_len: %d\n"
	.zero	2
.LC2:
	.string	"coefflen4: %d * 4\n"
	.zero	5
.LC9:
	.string	"Input sample len must multiple of 4 float.\n"
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
