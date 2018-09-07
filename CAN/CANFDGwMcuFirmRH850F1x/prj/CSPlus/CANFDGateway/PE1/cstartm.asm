;   Copyright(c) 2013, 2014 Renesas Electronics Corporation
;   RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
;   This program must be used solely for the purpose for which
;   it was furnished by Renesas Electronics Corporation. No part of this
;   program may be reproduced or disclosed to others, in any
;   form, without the prior written permission of Renesas Electronics
;   Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE FOR MULTI CORE PROJECT.

;-----------------------------------------------------------------------------
;	processing module setting table
;-----------------------------------------------------------------------------
	.section	".const.cmn", const
	.public	_pm1_setting_table
	.align	4
_pm1_setting_table:
	.dw	#__start_pm	; ENTRY ADDRESS

;-----------------------------------------------------------------------------
;	system stack
;-----------------------------------------------------------------------------
;STACKSIZE	.set	0x200
STACKSIZE	.set	0x400
	.section	".stack.bss", bss
	.align	4
	.ds	(STACKSIZE)
	.align	4
_stacktop:

;-----------------------------------------------------------------------------
;	section initialize table
;-----------------------------------------------------------------------------
	.section	".INIT_DSEC.const", const
	.align	4
	.dw	#__s.data,	#__e.data,	#__s.data.R

	.section	".INIT_BSEC.const", const
	.align	4
	.dw	#__s.bss,	#__e.bss

;-----------------------------------------------------------------------------
;	startup
;-----------------------------------------------------------------------------
	.section	".text", text
	.public	__start_pm
	.align	2
__start_pm:
	mov	#_stacktop, sp		;  set sp register
	mov	#__gp_data, gp		;  set gp register
	mov	#__ep_data, ep		;  set ep register

	jarl	_hdwinit, lp		;  initialize hardware

	mov	#__s.INIT_DSEC.const, r6
	mov	#__e.INIT_DSEC.const, r7
	mov	#__s.INIT_BSEC.const, r8
	mov	#__e.INIT_BSEC.const, r9
	jarl32	__INITSCT_RH, lp	;  initialize RAM area

	; set various flags to PSW via FEPSW

	stsr	5, r10, 0		; r10 <- PSW

	movhi	0x0001, r0, r11
	or	r11, r10
	ldsr	r10, 5, 0		; enable FPU

	movhi	0x0002, r0, r11
	ldsr	r11, 6, 0		; initialize FPSR
	ldsr	r0, 7, 0		; initialize FPEPC

	;xori	0x0020, r10, r10	; enable interrupt

	;movhi	0x4000, r0, r11
	;or	r11, r10		; supervisor mode -> user mode

	ldsr	r10, 3, 0		; FEPSW <- r10

	mov	#_exit, lp		; lp <- #_exit
	mov	#_main, r10
	ldsr	r10, 2, 0		; FEPC <- #_main

	; apply PSW and PC to start user mode
	feret
	
_exit:
	br	_exit			;  end of program
;-----------------------------------------------------------------------------
;	abort
;-----------------------------------------------------------------------------
	.public	_abort
	.align	2
_abort:
	br	_abort

;-----------------------------------------------------------------------------
;	dummy section
;-----------------------------------------------------------------------------
	.section	".data", data
.L.dummy.data:
	.section	".bss", bss
.L.dummy.bss:
	.section	".const", const
.L.dummy.const:
	.section	".text", text
.L.dummy.text:
;-------------------- end of start up module -------------------;
