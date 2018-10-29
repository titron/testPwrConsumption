;   Copyright(c) 2013, 2014 Renesas Electronics Corporation
;   RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
;   This program must be used solely for the purpose for which
;   it was furnished by Renesas Electronics Corporation. No part of this
;   program may be reproduced or disclosed to others, in any
;   form, without the prior written permission of Renesas Electronics
;   Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE FOR MULTI CORE PROJECT.

	; example of using eiint as table reference method
	USE_TABLE_REFERENCE_METHOD .set 1

	; offset of processing module setting table element
	.OFFSET_ENTRY	.set	0

	; the following is the addresses on R7F701Z07.
	; specify values suitable to your system if needed.
	GLOBAL_RAM_ADDR 	.set	0xfeefc000
	GLOBAL_RAM_END		.set	0xfeefffff

	LOCAL_RAM_PE1_ADDR	.set	0xfebe4000
	LOCAL_RAM_PE1_END	.set	0xfebfffff

	LOCAL_RAM_PE2_ADDR	.set	0xfe9e4000
	LOCAL_RAM_PE2_END	.set	0xfe9fffff

;-----------------------------------------------------------------------------
;	startup
;-----------------------------------------------------------------------------
	.section	".text", text
	.public	__start
	.align	2
__start:
$if 1	; initialize register
	$nowarning
	mov	r0, r1
	$warning
	mov	r0, r2
	mov	r0, r3
	mov	r0, r4
	mov	r0, r5
	mov	r0, r6
	mov	r0, r7
	mov	r0, r8
	mov	r0, r9
	mov	r0, r10
	mov	r0, r11
	mov	r0, r12
	mov	r0, r13
	mov	r0, r14
	mov	r0, r15
	mov	r0, r16
	mov	r0, r17
	mov	r0, r18
	mov	r0, r19
	mov	r0, r20
	mov	r0, r21
	mov	r0, r22
	mov	r0, r23
	mov	r0, r24
	mov	r0, r25
	mov	r0, r26
	mov	r0, r27
	mov	r0, r28
	mov	r0, r29
	mov	r0, r30
	mov	r0, r31
	ldsr	r0, 0, 0		;  EIPC
	ldsr	r0, 16, 0		;  CTPC
$endif

	; jump to entry point of each PE
	stsr	0, r10, 2		; get HTCFG0
	shr	16, r10			; get PEID

	cmp	1, r10
	bz	__start_PE1
	cmp	2, r10
	bz	__start_PE2
	;cmp	3, r10
	;bz	__start_PE3
__exit:
	br	__exit

__start_PE1:
	jarl	_hdwinit_PE1, lp	; initialize hardware
$ifdef USE_TABLE_REFERENCE_METHOD
	jarl	_init_eiint, lp		; initialize exception
$endif

	mov	#_pm1_setting_table, r13
	ld.w	.OFFSET_ENTRY[r13], r10	; r10 <- #__start
	jmp	[r10]			; jump to #__start

__start_PE2:
jarl	_hdwinit_PE2, lp	; initialize hardware
;$ifdef USE_TABLE_REFERENCE_METHOD
;	jarl	_init_eiint, lp		; initialize exception
;$endif

;	mov	#_pm2_setting_table, r13
;	ld.w	.OFFSET_ENTRY[r13], r10	; r10 <- #__start
;	jmp	[r10]			; jump to #__start
	br	__exit


__start_PE3:
;	jarl	_hdwinit_PE3, lp	; initialize hardware
;$ifdef USE_TABLE_REFERENCE_METHOD
;	jarl	_init_eiint, lp		; initialize exception
;$endif
;	mov	#_pm3_setting_table, r13
;	ld.w	.OFFSET_ENTRY[r13], r10	; r10 <- #__start
;	jmp	[r10]			; jump to #__start

	br	__exit

;-----------------------------------------------------------------------------
;	hdwinit_PE1
;-----------------------------------------------------------------------------
	.section	".text", text
	.align	2
_hdwinit_PE1:
	mov	lp, r14			; save return address

	; clear Global RAM
	mov	GLOBAL_RAM_ADDR, r6
	mov	GLOBAL_RAM_END, r7
	jarl	_zeroclr4, lp

	; clear Local RAM PE1
	mov	LOCAL_RAM_PE1_ADDR, r6
	mov	LOCAL_RAM_PE1_END, r7
	jarl	_zeroclr4, lp

	mov	r14, lp
	jmp	[lp]

;-----------------------------------------------------------------------------
;	hdwinit_PE2
; Specify RAM addresses suitable to your system if needed.
;-----------------------------------------------------------------------------

	.align	2
_hdwinit_PE2:
	mov	lp, r14			; save return address

	; clear Local RAM PE2
	mov	LOCAL_RAM_PE2_ADDR, r6
	mov	LOCAL_RAM_PE2_END, r7
	jarl	_zeroclr4, lp

	mov	r14, lp
	jmp	[lp]

;-----------------------------------------------------------------------------
;	hdwinit_PE3
;-----------------------------------------------------------------------------
;	.section	".text", text
;	.align	2
;_hdwinit_PE3:
;	mov	lp, r14			; save return address
;
;	; clear Local RAM PE3
;	mov	LOCAL_RAM_PE3_ADDR, r6
;	mov	LOCAL_RAM_PE3_END, r7
;	jarl	_zeroclr4, lp
;
;	mov	r14, lp
;	jmp	[lp]

;-----------------------------------------------------------------------------
;	zeroclr4
;-----------------------------------------------------------------------------
	.align	2
_zeroclr4:
	br	.L.zeroclr4.2
.L.zeroclr4.1:
	st.w	r0, [r6]
	add	4, r6
.L.zeroclr4.2:
	cmp	r6, r7
	bh	.L.zeroclr4.1
	jmp	[lp]

$ifdef USE_TABLE_REFERENCE_METHOD
;-----------------------------------------------------------------------------
;	init_eiint
;-----------------------------------------------------------------------------
	; interrupt control register address
	ICBASE	.set	0xfffeea00

	.align	2
_init_eiint:
	mov	#__sEIINTTBL, r10
	ldsr	r10, 4, 1		; set INTBP

	; some inetrrupt channels use the table reference method.
	mov	ICBASE, r10		; get interrupt control register address
	set1	6, 0[r10]		; set INT0 as table reference
	set1	6, 2[r10]		; set INT1 as table reference
	set1	6, 4[r10]		; set INT2 as table reference

	jmp	[lp]
$endif
;-------------------- end of start up module -------------------;
