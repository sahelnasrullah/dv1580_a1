	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 4
	.globl	_list_init                      ; -- Begin function list_init
	.p2align	2
_list_init:                             ; @list_init
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	str	x1, [sp, #16]
	adrp	x8, _memory_pool@GOTPAGE
	ldr	x8, [x8, _memory_pool@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB0_2
	b	LBB0_1
LBB0_1:
	ldr	x8, [sp, #16]
	mov	x9, #100
	mul	x8, x8, x9
	str	x8, [sp, #8]
	ldr	x0, [sp, #16]
	bl	_mem_init
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	b	LBB0_2
LBB0_2:
	ldur	x8, [x29, #-8]
                                        ; kill: def $x9 killed $xzr
	str	xzr, [x8]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_insert                    ; -- Begin function list_insert
	.p2align	2
_list_insert:                           ; @list_insert
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	mov	x0, #16
	bl	_mem_alloc
	str	x0, [sp, #8]
	ldr	x8, [sp, #8]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB1_2
	b	LBB1_1
LBB1_1:
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	b	LBB1_8
LBB1_2:
	ldur	w8, [x29, #-12]
	ldr	x9, [sp, #8]
	strh	w8, [x9]
	ldr	x8, [sp, #8]
                                        ; kill: def $x9 killed $xzr
	str	xzr, [x8, #8]
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB1_4
	b	LBB1_3
LBB1_3:
	ldr	x8, [sp, #8]
	ldur	x9, [x29, #-8]
	str	x8, [x9]
	b	LBB1_8
LBB1_4:
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	str	x8, [sp]
	b	LBB1_5
LBB1_5:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8, #8]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB1_7
	b	LBB1_6
LBB1_6:                                 ;   in Loop: Header=BB1_5 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8, #8]
	str	x8, [sp]
	b	LBB1_5
LBB1_7:
	ldr	x8, [sp, #8]
	ldr	x9, [sp]
	str	x8, [x9, #8]
	b	LBB1_8
LBB1_8:
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_insert_after              ; -- Begin function list_insert_after
	.p2align	2
_list_insert_after:                     ; @list_insert_after
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	ldur	x8, [x29, #-8]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB2_2
	b	LBB2_1
LBB2_1:
	b	LBB2_5
LBB2_2:
	mov	x0, #16
	bl	_mem_alloc
	str	x0, [sp, #8]
	ldr	x8, [sp, #8]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB2_4
	b	LBB2_3
LBB2_3:
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	b	LBB2_5
LBB2_4:
	ldur	w8, [x29, #-12]
	ldr	x9, [sp, #8]
	strh	w8, [x9]
	ldur	x8, [x29, #-8]
	ldr	x8, [x8, #8]
	ldr	x9, [sp, #8]
	str	x8, [x9, #8]
	ldr	x8, [sp, #8]
	ldur	x9, [x29, #-8]
	str	x8, [x9, #8]
	b	LBB2_5
LBB2_5:
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_insert_before             ; -- Begin function list_insert_before
	.p2align	2
_list_insert_before:                    ; @list_insert_before
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #80
	.cfi_def_cfa_offset 80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	x1, [x29, #-16]
	stur	w2, [x29, #-20]
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB3_2
	b	LBB3_1
LBB3_1:
	ldur	x8, [x29, #-16]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB3_3
	b	LBB3_2
LBB3_2:
	b	LBB3_16
LBB3_3:
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	ldur	x9, [x29, #-16]
	subs	x8, x8, x9
	cset	w8, ne
	tbnz	w8, #0, LBB3_7
	b	LBB3_4
LBB3_4:
	mov	x0, #16
	bl	_mem_alloc
	str	x0, [sp, #32]
	ldr	x8, [sp, #32]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB3_6
	b	LBB3_5
LBB3_5:
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	b	LBB3_16
LBB3_6:
	ldur	w8, [x29, #-20]
	ldr	x9, [sp, #32]
	strh	w8, [x9]
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	ldr	x9, [sp, #32]
	str	x8, [x9, #8]
	ldr	x8, [sp, #32]
	ldur	x9, [x29, #-8]
	str	x8, [x9]
	b	LBB3_16
LBB3_7:
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	str	x8, [sp, #24]
	b	LBB3_8
LBB3_8:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #24]
	subs	x8, x8, #0
	cset	w8, eq
	mov	w9, #0
	str	w9, [sp, #12]                   ; 4-byte Folded Spill
	tbnz	w8, #0, LBB3_10
	b	LBB3_9
LBB3_9:                                 ;   in Loop: Header=BB3_8 Depth=1
	ldr	x8, [sp, #24]
	ldr	x8, [x8, #8]
	ldur	x9, [x29, #-16]
	subs	x8, x8, x9
	cset	w8, ne
	str	w8, [sp, #12]                   ; 4-byte Folded Spill
	b	LBB3_10
LBB3_10:                                ;   in Loop: Header=BB3_8 Depth=1
	ldr	w8, [sp, #12]                   ; 4-byte Folded Reload
	tbz	w8, #0, LBB3_12
	b	LBB3_11
LBB3_11:                                ;   in Loop: Header=BB3_8 Depth=1
	ldr	x8, [sp, #24]
	ldr	x8, [x8, #8]
	str	x8, [sp, #24]
	b	LBB3_8
LBB3_12:
	ldr	x8, [sp, #24]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB3_16
	b	LBB3_13
LBB3_13:
	mov	x0, #16
	bl	_mem_alloc
	str	x0, [sp, #16]
	ldr	x8, [sp, #16]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB3_15
	b	LBB3_14
LBB3_14:
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	b	LBB3_16
LBB3_15:
	ldur	w8, [x29, #-20]
	ldr	x9, [sp, #16]
	strh	w8, [x9]
	ldur	x8, [x29, #-16]
	ldr	x9, [sp, #16]
	str	x8, [x9, #8]
	ldr	x8, [sp, #16]
	ldr	x9, [sp, #24]
	str	x8, [x9, #8]
	b	LBB3_16
LBB3_16:
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_delete                    ; -- Begin function list_delete
	.p2align	2
_list_delete:                           ; @list_delete
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB4_2
	b	LBB4_1
LBB4_1:
	b	LBB4_13
LBB4_2:
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	str	x8, [sp, #24]
                                        ; kill: def $x8 killed $xzr
	str	xzr, [sp, #16]
	ldr	x8, [sp, #24]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB4_5
	b	LBB4_3
LBB4_3:
	ldr	x8, [sp, #24]
	ldrh	w8, [x8]
	ldur	w9, [x29, #-12]
	subs	w8, w8, w9
	cset	w8, ne
	tbnz	w8, #0, LBB4_5
	b	LBB4_4
LBB4_4:
	ldr	x8, [sp, #24]
	ldr	x8, [x8, #8]
	ldur	x9, [x29, #-8]
	str	x8, [x9]
	ldr	x0, [sp, #24]
	bl	_mem_free
	b	LBB4_13
LBB4_5:
	b	LBB4_6
LBB4_6:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #24]
	subs	x8, x8, #0
	cset	w8, eq
	mov	w9, #0
	str	w9, [sp, #12]                   ; 4-byte Folded Spill
	tbnz	w8, #0, LBB4_8
	b	LBB4_7
LBB4_7:                                 ;   in Loop: Header=BB4_6 Depth=1
	ldr	x8, [sp, #24]
	ldrh	w8, [x8]
	ldur	w9, [x29, #-12]
	subs	w8, w8, w9
	cset	w8, ne
	str	w8, [sp, #12]                   ; 4-byte Folded Spill
	b	LBB4_8
LBB4_8:                                 ;   in Loop: Header=BB4_6 Depth=1
	ldr	w8, [sp, #12]                   ; 4-byte Folded Reload
	tbz	w8, #0, LBB4_10
	b	LBB4_9
LBB4_9:                                 ;   in Loop: Header=BB4_6 Depth=1
	ldr	x8, [sp, #24]
	str	x8, [sp, #16]
	ldr	x8, [sp, #24]
	ldr	x8, [x8, #8]
	str	x8, [sp, #24]
	b	LBB4_6
LBB4_10:
	ldr	x8, [sp, #24]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB4_12
	b	LBB4_11
LBB4_11:
	b	LBB4_13
LBB4_12:
	ldr	x8, [sp, #24]
	ldr	x8, [x8, #8]
	ldr	x9, [sp, #16]
	str	x8, [x9, #8]
	ldr	x0, [sp, #24]
	bl	_mem_free
	b	LBB4_13
LBB4_13:
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_search                    ; -- Begin function list_search
	.p2align	2
_list_search:                           ; @list_search
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, #16]
	str	w1, [sp, #12]
	ldr	x8, [sp, #16]
	ldr	x8, [x8]
	str	x8, [sp]
	b	LBB5_1
LBB5_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB5_5
	b	LBB5_2
LBB5_2:                                 ;   in Loop: Header=BB5_1 Depth=1
	ldr	x8, [sp]
	ldrh	w8, [x8]
	ldr	w9, [sp, #12]
	subs	w8, w8, w9
	cset	w8, ne
	tbnz	w8, #0, LBB5_4
	b	LBB5_3
LBB5_3:
	ldr	x8, [sp]
	str	x8, [sp, #24]
	b	LBB5_6
LBB5_4:                                 ;   in Loop: Header=BB5_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8, #8]
	str	x8, [sp]
	b	LBB5_1
LBB5_5:
                                        ; kill: def $x8 killed $xzr
	str	xzr, [sp, #24]
	b	LBB5_6
LBB5_6:
	ldr	x0, [sp, #24]
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_display                   ; -- Begin function list_display
	.p2align	2
_list_display:                          ; @list_display
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB6_2
	b	LBB6_1
LBB6_1:
	adrp	x0, l_.str.4@PAGE
	add	x0, x0, l_.str.4@PAGEOFF
	bl	_printf
	b	LBB6_8
LBB6_2:
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	str	x8, [sp, #16]
	adrp	x0, l_.str.5@PAGE
	add	x0, x0, l_.str.5@PAGEOFF
	bl	_printf
	b	LBB6_3
LBB6_3:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #16]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB6_7
	b	LBB6_4
LBB6_4:                                 ;   in Loop: Header=BB6_3 Depth=1
	ldr	x8, [sp, #16]
	ldrh	w10, [x8]
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x10
	str	x8, [x9]
	adrp	x0, l_.str.6@PAGE
	add	x0, x0, l_.str.6@PAGEOFF
	bl	_printf
	ldr	x8, [sp, #16]
	ldr	x8, [x8, #8]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB6_6
	b	LBB6_5
LBB6_5:                                 ;   in Loop: Header=BB6_3 Depth=1
	adrp	x0, l_.str.7@PAGE
	add	x0, x0, l_.str.7@PAGEOFF
	bl	_printf
	b	LBB6_6
LBB6_6:                                 ;   in Loop: Header=BB6_3 Depth=1
	ldr	x8, [sp, #16]
	ldr	x8, [x8, #8]
	str	x8, [sp, #16]
	b	LBB6_3
LBB6_7:
	adrp	x0, l_.str.8@PAGE
	add	x0, x0, l_.str.8@PAGEOFF
	bl	_printf
	b	LBB6_8
LBB6_8:
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_display_range             ; -- Begin function list_display_range
	.p2align	2
_list_display_range:                    ; @list_display_range
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	x1, [x29, #-16]
	str	x2, [sp, #24]
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	subs	x8, x8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB7_2
	b	LBB7_1
LBB7_1:
	adrp	x0, l_.str.9@PAGE
	add	x0, x0, l_.str.9@PAGEOFF
	bl	_printf
	b	LBB7_12
LBB7_2:
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	str	x8, [sp, #16]
	ldur	x8, [x29, #-16]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB7_4
	b	LBB7_3
LBB7_3:
	ldur	x8, [x29, #-16]
	str	x8, [sp, #16]
	b	LBB7_4
LBB7_4:
	adrp	x0, l_.str.5@PAGE
	add	x0, x0, l_.str.5@PAGEOFF
	bl	_printf
	b	LBB7_5
LBB7_5:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #16]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB7_11
	b	LBB7_6
LBB7_6:                                 ;   in Loop: Header=BB7_5 Depth=1
	ldr	x8, [sp, #16]
	ldrh	w10, [x8]
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x10
	str	x8, [x9]
	adrp	x0, l_.str.6@PAGE
	add	x0, x0, l_.str.6@PAGEOFF
	bl	_printf
	ldr	x8, [sp, #16]
	ldr	x9, [sp, #24]
	subs	x8, x8, x9
	cset	w8, ne
	tbnz	w8, #0, LBB7_8
	b	LBB7_7
LBB7_7:
	b	LBB7_11
LBB7_8:                                 ;   in Loop: Header=BB7_5 Depth=1
	ldr	x8, [sp, #16]
	ldr	x8, [x8, #8]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB7_10
	b	LBB7_9
LBB7_9:                                 ;   in Loop: Header=BB7_5 Depth=1
	adrp	x0, l_.str.7@PAGE
	add	x0, x0, l_.str.7@PAGEOFF
	bl	_printf
	b	LBB7_10
LBB7_10:                                ;   in Loop: Header=BB7_5 Depth=1
	ldr	x8, [sp, #16]
	ldr	x8, [x8, #8]
	str	x8, [sp, #16]
	b	LBB7_5
LBB7_11:
	adrp	x0, l_.str.10@PAGE
	add	x0, x0, l_.str.10@PAGEOFF
	bl	_printf
	b	LBB7_12
LBB7_12:
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_count_nodes               ; -- Begin function list_count_nodes
	.p2align	2
_list_count_nodes:                      ; @list_count_nodes
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, #24]
	str	wzr, [sp, #20]
	ldr	x8, [sp, #24]
	ldr	x8, [x8]
	str	x8, [sp, #8]
	b	LBB8_1
LBB8_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #8]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB8_3
	b	LBB8_2
LBB8_2:                                 ;   in Loop: Header=BB8_1 Depth=1
	ldr	w8, [sp, #20]
	add	w8, w8, #1
	str	w8, [sp, #20]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #8]
	str	x8, [sp, #8]
	b	LBB8_1
LBB8_3:
	ldr	w0, [sp, #20]
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_list_cleanup                   ; -- Begin function list_cleanup
	.p2align	2
_list_cleanup:                          ; @list_cleanup
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	str	x8, [sp, #16]
	b	LBB9_1
LBB9_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #16]
	subs	x8, x8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB9_3
	b	LBB9_2
LBB9_2:                                 ;   in Loop: Header=BB9_1 Depth=1
	ldr	x8, [sp, #16]
	ldr	x8, [x8, #8]
	str	x8, [sp, #8]
	ldr	x0, [sp, #16]
	bl	_mem_free
	ldr	x8, [sp, #8]
	str	x8, [sp, #16]
	b	LBB9_1
LBB9_3:
	ldur	x8, [x29, #-8]
                                        ; kill: def $x9 killed $xzr
	str	xzr, [x8]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Memory pool initialized in list_init\n"

l_.str.1:                               ; @.str.1
	.asciz	"Failed to allocate memory for new node (list_insert)\n"

l_.str.2:                               ; @.str.2
	.asciz	"Failed to allocate memory for new node (list_insert_after)\n"

l_.str.3:                               ; @.str.3
	.asciz	"Failed to allocate memory for new node (list_insert_before)\n"

l_.str.4:                               ; @.str.4
	.asciz	"[]\n"

l_.str.5:                               ; @.str.5
	.asciz	"["

l_.str.6:                               ; @.str.6
	.asciz	"%d"

l_.str.7:                               ; @.str.7
	.asciz	", "

l_.str.8:                               ; @.str.8
	.asciz	"]\n"

l_.str.9:                               ; @.str.9
	.asciz	"[]"

l_.str.10:                              ; @.str.10
	.asciz	"]"

.subsections_via_symbols
