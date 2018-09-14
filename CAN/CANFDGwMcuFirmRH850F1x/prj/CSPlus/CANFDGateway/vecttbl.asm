;   Copyright(c) 2013, 2014 Renesas Electronics Corporation
;   RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
;   This program must be used solely for the purpose for which
;   it was furnished by Renesas Electronics Corporation. No part of this
;   program may be reproduced or disclosed to others, in any
;   form, without the prior written permission of Renesas Electronics
;   Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE FOR MULTI CORE PROJECT.
	; OSTIMER 0
	.extern _Isr_OsTimer0
	; RSCANFD 0
	.extern _INTRCANGERR0
	.extern _INTRCANGRECC0
	.extern _INTRCAN0ERR
	.extern _INTRCAN0REC
	.extern _INTRCAN0TRX
	; RSCANFD 1
	.extern _INTRCANGERR1
	.extern _INTRCANGRECC1
	.extern _INTRCAN1ERR
	.extern _INTRCAN1REC
	.extern _INTRCAN1TRX
	; RSCANFD 2
	.extern _INTRCANGERR2
	.extern _INTRCANGRECC2
	.extern _INTRCAN2ERR
	.extern _INTRCAN2REC
	.extern _INTRCAN2TRX
	; RSCANFD 3
	.extern _INTRCANGERR3
	.extern _INTRCANGRECC3
	.extern _INTRCAN3ERR
	.extern _INTRCAN3REC
	.extern _INTRCAN3TRX
	; RSCANFD 4
	.extern _INTRCANGERR4
	.extern _INTRCANGRECC4
	.extern _INTRCAN4ERR
	.extern _INTRCAN4REC
	.extern _INTRCAN4TRX
	; RSCANFD 5
	.extern _INTRCANGERR5
	.extern _INTRCANGRECC5
	.extern _INTRCAN5ERR
	.extern _INTRCAN5REC
	.extern _INTRCAN5TRX
	; RSCANFD 6
	.extern _INTRCANGERR6
	.extern _INTRCANGRECC6
	.extern _INTRCAN6ERR
	.extern _INTRCAN6REC
	.extern _INTRCAN6TRX
	; FLEXRAY 0
	.extern _INTFLXA0LINE0
	.extern _INTFLXA0LINE1
	.extern _INTFLXA0TIM0
	.extern _INTFLXA0TIM1
	.extern _INTFLXA0TIM2
	; RIIC0
	.extern _riic0_eei_isr
	.extern _riic0_txi_isr
	.extern _riic0_rxi_isr
	.extern _riic0_tei_isr

	.section "RESET", text

	.align	512
        jr32	__start ; RESET

	.align	16
	jr32	_Dummy ; SYSERR

	.align	16
	jr32	_Dummy ; HVTRAP

	.align	16
	jr32	_Dummy ; FETRAP

	.align	16
	jr32	_Dummy_EI ; TRAP0

	.align	16
	jr32	_Dummy_EI ; TRAP1

	.align	16
	jr32	_Dummy ; RIE

	.align	16
	jr32	_Dummy_EI ; FPP/FPI

	.align	16
	jr32	_Dummy ; UCPOP

	.align	16
	jr32	_Dummy ; MIP/MDP

	.align	16
	jr32	_Dummy ; PIE

	.align	16
	jr32	_Dummy ; Debug

	.align	16
	jr32	_Dummy ; MAE

	.align	16
	jr32	_Dummy ; (R.F.U)

	.align	16
	jr32	_Dummy ; FENMI

	.align	16
	jr32	_Dummy ; FEINT

	.align	16
	jr32	_Dummy_EI ; INTn(priority0)

	.align	16
	jr32	_Dummy_EI ; INTn(priority1)

	.align	16
	jr32	_Dummy_EI ; INTn(priority2)

	.align	16
	jr32	_Dummy_EI ; INTn(priority3)

	.align	16
	jr32	_Dummy_EI ; INTn(priority4)

	.align	16
	jr32	_Dummy_EI ; INTn(priority5)

	.align	16
	jr32	_Dummy_EI ; INTn(priority6)

	.align	16
	jr32	_Dummy_EI ; INTn(priority7)

	.align	16
	jr32	_Dummy_EI ; INTn(priority8)

	.align	16
	jr32	_Dummy_EI ; INTn(priority9)

	.align	16
	jr32	_Dummy_EI ; INTn(priority10)

	.align	16
	jr32	_Dummy_EI ; INTn(priority11)

	.align	16
	jr32	_Dummy_EI ; INTn(priority12)

	.align	16
	jr32	_Dummy_EI ; INTn(priority13)

	.align	16
	jr32	_Dummy_EI ; INTn(priority14)

	.align	16
	jr32	_Dummy_EI ; INTn(priority15)

	.section "EIINTTBL", const
	.align	512
	.dw	#_Dummy_EI ; 0: INT0-ICIPIR0
	.dw	#_Dummy_EI ; 1: INT1-ICIPIR1
	.dw	#_Dummy_EI ; 2: INT2-ICIPIR2
	.dw	#_Dummy_EI ; 3: ICIPIR3
	.dw	#_Dummy_EI ; 4: ICBN0
	.dw	#_Dummy_EI ; 5: reserved
	.dw	#_Dummy_EI ; 6: reserved
	.dw	#_Dummy_EI ; 7: reserved
	.dw	#_Dummy_EI ; 8 - ICTAUD0I0, ICCSIH2IC_1
	.dw	#_Dummy_EI ; 9 - ICTAUD0I2, ICCSIH3IC_1
	.dw	#_Dummy_EI ; 10 - ICTAUD0I4, ICCSIH2IR_1
	.dw	#_Dummy_EI ; 11 - ICTAUD0I6, ICCSIH2IRE_1
	.dw	#_Dummy_EI ; 12 - ICTAUD0I8, ICCSIH2IJC_1
	.dw	#_Dummy_EI ; 13 - ICTAUD0I10, ICCSIH3IR_1
	.dw	#_Dummy_EI ; 14 - ICTAUD0I12, ICCSIH3IRE_1
	.dw	#_Dummy_EI ; 15 - ICTAUD0I14, ICCSIH3IJC_1
	.dw	#_Dummy_EI ; 16 - ICTAPA0IPEK0, ICCSIH1IC_1
	.dw	#_Dummy_EI ; 17 - ICTAPA0IVLY0, ICCSIH1IR_1
	.dw	#_Dummy_EI ; 18 - ICADCA0I0
	.dw	#_Dummy_EI ; 19 - ICADCA0I1
	.dw	#_Dummy_EI ; 20 - ICADCA0I2, ICCSIH0IJC_1
	.dw	#_Dummy_EI ; 21 - ICDCUTDI
	.dw	#_INTRCANGERR0 ; 22 - ICRCANGERR0
	;.dw	#_Dummy_EI ; 22 - ICRCANGERR0
	.dw	#_INTRCANGRECC0 ; 23 - ICRCANGRECC0
	;.dw	#_Dummy_EI ; 23 - ICRCANGRECC0
	.dw	#_INTRCAN0ERR ; 24 - ICRCAN0ERR
	;.dw	#_Dummy_EI ; 24 - ICRCAN0ERR
	.dw	#_INTRCAN0REC ; 25 - ICRCAN0REC
	;.dw	#_Dummy_EI ; 25 - ICRCAN0REC
	.dw	#_INTRCAN0TRX ; 26 - ICRCAN0TRX
	;.dw	#_Dummy_EI ; 26 - ICRCAN0TRX
	.dw	#_Dummy_EI ; 27 - ICCSIG0IC, ICCSIH1IRE_1
	.dw	#_Dummy_EI ; 28 - ICCSIG0IR, ICCSIH1IJC_1
	.dw	#_Dummy_EI ; 29 - ICCSIH0IC
	.dw	#_Dummy_EI ; 30 - ICCSIH0IR
	.dw	#_Dummy_EI ; 31 - ICCSIH0IRE
	.dw	#_Dummy_EI ; 32 - ICCSIH0IJC, ICADCA0I2_2
	.dw	#_Dummy_EI ; 33 - ICRLIN30
	.dw	#_Dummy_EI ; 34 - ICRLIN30UR0
	.dw	#_Dummy_EI ; 35 - ICRLIN30UR1
	.dw	#_Dummy_EI ; 36 - ICRLIN30UR2
	.dw	#_Dummy_EI ; 37 - ICP0
	.dw	#_Dummy_EI ; 38 - ICP1
	.dw	#_Dummy_EI ; 39 - ICP2
	.dw	#_Dummy_EI ; 40 - ICWDTA0
	.dw	#_Dummy_EI ; 41 - ICWDTA1
	.dw	#_Dummy_EI ; 42 - ICWDTA2
	.dw	#_Dummy_EI ; 43 - ICP3
	.dw	#_Dummy_EI ; 44 - ICP4
	.dw	#_Dummy_EI ; 45 - ICP5
	.dw	#_Dummy_EI ; 46 - ICP10
	.dw	#_Dummy_EI ; 47 - ICP11
	.dw	#_Dummy_EI ; 48 - ICTAUD0I1
	.dw	#_Dummy_EI ; 49 - ICTAUD0I3
	.dw	#_Dummy_EI ; 50 - ICTAUD0I5
	.dw	#_Dummy_EI ; 51 - ICTAUD0I7
	.dw	#_Dummy_EI ; 52 - ICTAUD0I9
	.dw	#_Dummy_EI ; 53 - ICTAUD0I11
	.dw	#_Dummy_EI ; 54 - ICTAUD0I13
	.dw	#_Dummy_EI ; 55 - ICTAUD0I15
	.dw	#_Dummy_EI ; 56 - ICADCA0ERR
	.dw	#_Dummy_EI ; 57 - ICCSIG0IRE
	.dw	#_Dummy_EI ; 58 - ICRLIN20
	.dw	#_Dummy_EI ; 59 - ICRLIN21
	.dw	#_Dummy_EI ; 60 - ICDMA0
	.dw	#_Dummy_EI ; 61 - ICDMA1
	.dw	#_Dummy_EI ; 62 - ICDMA2
	.dw	#_Dummy_EI ; 63 - ICDMA3
	.dw	#_Dummy_EI ; 64 - ICDMA4
	.dw	#_Dummy_EI ; 65 - ICDMA5
	.dw	#_Dummy_EI ; 66 - ICDMA6
	.dw	#_Dummy_EI ; 67 - ICDMA7
	.dw	#_Dummy_EI ; 68 - ICDMA8
	.dw	#_Dummy_EI ; 69 - ICDMA9
	.dw	#_Dummy_EI ; 70 - ICDMA10
	.dw	#_Dummy_EI ; 71 - ICDMA11
	.dw	#_Dummy_EI ; 72 - ICDMA12
	.dw	#_Dummy_EI ; 73 - ICDMA13
	.dw	#_Dummy_EI ; 74 - ICDMA14
	.dw	#_Dummy_EI ; 75 - ICDMA15
	;.dw	#_Dummy_EI ; 76 - ICRIIC0TI
	.dw #_riic0_txi_isr
	;.dw	#_Dummy_EI ; 77 - ICRIIC0TEI
	.dw #_riic0_eei_isr
	;.dw	#_Dummy_EI ; 78 - ICRIIC0RI
	.dw #_riic0_rxi_isr
	;.dw	#_Dummy_EI ; 79 - ICRIIC0EE
	.dw #_riic0_tei_isr
	.dw	#_Dummy_EI ; 80 - ICTAUJ0I0
	.dw	#_Dummy_EI ; 81 - ICTAUJ0I1
	.dw	#_Dummy_EI ; 82 - ICTAUJ0I2
	.dw	#_Dummy_EI ; 83 - ICTAUJ0I3
	;.dw	#_Dummy_EI ; 84 - ICOSTM0
	.dw	#_Isr_OsTimer0 ; 84 - ICOSTM0
	.dw	#_Dummy_EI ; 85 - ICENCA0IOV, ICPWGA4
	.dw	#_Dummy_EI ; 86 - ICENCA0IUD, ICPWGA5
	.dw	#_Dummy_EI ; 87 - ICENCA0I0, ICPWGA6
	.dw	#_Dummy_EI ; 88 - ICENCA0I1, ICPWGA7
	.dw	#_Dummy_EI ; 89 - ICENCA0IEC
	.dw	#_Dummy_EI ; 90 - ICKR0
	.dw	#_Dummy_EI ; 91 - ICQFULL
	.dw	#_Dummy_EI ; 92 - ICPWGA0
	.dw	#_Dummy_EI ; 93 - ICPWGA1
	.dw	#_Dummy_EI ; 94 - ICPWGA2
	.dw	#_Dummy_EI ; 95 - ICPWGA3
	.dw	#_Dummy_EI ; 96 - ICPWGA8
	.dw	#_Dummy_EI ; 97 - ICPWGA9
	.dw	#_Dummy_EI ; 98 - ICPWGA10
	.dw	#_Dummy_EI ; 99 - ICPWGA11
	.dw	#_Dummy_EI ; 100 - ICPWGA12
	.dw	#_Dummy_EI ; 101 - ICPWGA13
	.dw	#_Dummy_EI ; 102 - ICPWGA14
	.dw	#_Dummy_EI ; 103 - ICPWGA15
	.dw	#_Dummy_EI ; 104 - reserved
	.dw	#_Dummy_EI ; 105 - reserved
	.dw	#_Dummy_EI ; 106 - reserved
	.dw	#_Dummy_EI ; 107 - reserved
	.dw	#_Dummy_EI ; 108 - reserved
	.dw	#_Dummy_EI ; 109 - reserved
	.dw	#_Dummy_EI ; 110 - ICFLERR
	.dw	#_Dummy_EI ; 111 - ICFLENDNM
	.dw	#_Dummy_EI ; 112 - ICCWEND
	;.dw	#_Dummy_EI ; 113 - ICRCAN1ERR
	.dw	#_INTRCAN1ERR ; 113 - ICRCAN1ERR
	;.dw	#_Dummy_EI ; 114 - ICRCAN1REC
	.dw	#_INTRCAN1REC ; 114 - ICRCAN1REC
	;.dw	#_Dummy_EI ; 115 - ICRCAN1TRX
	.dw	#_INTRCAN1TRX ; 115 - ICRCAN1TRX
	.dw	#_Dummy_EI ; 116 - ICCSIH1IC, ICTAPA0IPEK0_2
	.dw	#_Dummy_EI ; 117 - ICCSIH1IR, ICTAPA0IVLY0_2
	.dw	#_Dummy_EI ; 118 - ICCSIH1IRE, ICCSIG0IC_2
	.dw	#_Dummy_EI ; 119 - ICCSIH1IJC, ICCSIG0IR_2
	.dw	#_Dummy_EI ; 120 - ICRLIN31
	.dw	#_Dummy_EI ; 121 - ICRLIN31UR0
	.dw	#_Dummy_EI ; 122 - ICRLIN31UR1
	.dw	#_Dummy_EI ; 123 - ICRLIN31UR2
	.dw	#_Dummy_EI ; 124 - ICPWGA20
	.dw	#_Dummy_EI ; 125 - ICPWGA21
	.dw	#_Dummy_EI ; 126 - ICPWGA22
	.dw	#_Dummy_EI ; 127 - ICPWGA23
	.dw	#_Dummy_EI ; 128 - ICP6
	.dw	#_Dummy_EI ; 129 - ICP7
	.dw	#_Dummy_EI ; 130 - ICP8
	.dw	#_Dummy_EI ; 131 - ICP12
	.dw	#_Dummy_EI ; 132 - ICCSIH2IC, ICTAUD0I0_2
	.dw	#_Dummy_EI ; 133 - ICCSIH2IR, ICTAUD0I4_2
	.dw	#_Dummy_EI ; 134 - ICCSIH2IRE, ICTAUD0I6_2
	.dw	#_Dummy_EI ; 135 - ICCSIH2IJC, ICTAUD0I8_2
	.dw	#_Dummy_EI ; 136 - reserved
	.dw	#_Dummy_EI ; 137 - reserved
	.dw	#_Dummy_EI ; 138 - reserved
	.dw	#_Dummy_EI ; 139 - reserved
	.dw	#_Dummy_EI ; 140 - reserved
	.dw	#_Dummy_EI ; 141 - reserved
	.dw	#_Dummy_EI ; 142 - ICTAUB0I0
	.dw	#_Dummy_EI ; 143 - ICTAUB0I1
	.dw	#_Dummy_EI ; 144 - ICTAUB0I2
	.dw	#_Dummy_EI ; 145 - ICTAUB0I3, ICPWGA16
	.dw	#_Dummy_EI ; 146 - ICTAUB0I4
	.dw	#_Dummy_EI ; 147 - ICTAUB0I5, ICPWGA17
	.dw	#_Dummy_EI ; 148 - ICTAUB0I6
	.dw	#_Dummy_EI ; 149 - ICTAUB0I7, ICPWGA18
	.dw	#_Dummy_EI ; 150 - ICPWGA18
	.dw	#_Dummy_EI ; 151 - ICTAUB0I9, ICPWGA19
	.dw	#_Dummy_EI ; 152 - ICTAUB0I10
	.dw	#_Dummy_EI ; 153 - ICTAUB0I11, ICPWGA26
	.dw	#_Dummy_EI ; 154 - ICTAUB0I12
	.dw	#_Dummy_EI ; 155 - ICTAUB0I13, ICPWGA30
	.dw	#_Dummy_EI ; 156 - ICTAUB0I14
	.dw	#_Dummy_EI ; 157 - ICTAUB0I15, ICPWGA31
	.dw	#_Dummy_EI ; 158 - ICCSIH3IC, ICTAUD0I2
	.dw	#_Dummy_EI ; 159 - ICCSIH3IR, ICTAUD0I10
	.dw	#_Dummy_EI ; 160 - ICCSIH3IRE, ICTAUD0I12
	.dw	#_Dummy_EI ; 161 - ICCSIH3IJC, ICTAUD0I14
	.dw	#_Dummy_EI ; 162 - ICRLIN22
	.dw	#_Dummy_EI ; 163 - ICRLIN23
	.dw	#_Dummy_EI ; 164 - ICRLIN32
	.dw	#_Dummy_EI ; 165 - ICRLIN32UR0
	.dw	#_Dummy_EI ; 166 - ICRLIN32UR1
	.dw	#_Dummy_EI ; 167 - ICRLIN32UR2
	.dw	#_Dummy_EI ; 168 - ICTAUJ1I0
	.dw	#_Dummy_EI ; 169 - ICTAUJ1I1
	.dw	#_Dummy_EI ; 170 - ICTAUJ1I2
	.dw	#_Dummy_EI ; 171 - ICTAUJ1I3
	.dw	#_Dummy_EI ; 172 - reserved
	.dw	#_Dummy_EI ; 173 - ICFLX0FDA
	.dw	#_Dummy_EI ; 174 - ICFLX0FW
	.dw	#_Dummy_EI ; 175 - ICFLX0IQE
	.dw	#_Dummy_EI ; 176 - ICFLX0IQF
	.dw	#_Dummy_EI ; 177 - ICFLX0OW
	.dw	#_Dummy_EI ; 178 - ICFLX0OT
	.dw	#_INTFLXA0LINE0 ; 179 - ICFLX0LINE0
	;.dw	#_Dummy_EI ; 179 - ICFLX0LINE0
	.dw	#_INTFLXA0LINE1 ; 180 - ICFLX0LINE1
	;.dw	#_Dummy_EI ; 180 - ICFLX0LINE1
	.dw	#_INTFLXA0TIM0 ; 181 - ICFLX0TIM0
	;.dw	#_Dummy_EI ; 181 - ICFLX0TIM0
	.dw	#_INTFLXA0TIM1 ; 182 - ICFLX0TIM1
	;.dw	#_Dummy_EI ; 182 - ICFLX0TIM1
	.dw	#_INTFLXA0TIM2 ; 183 - ICFLX0TIM2
	;.dw	#_Dummy_EI ; 183 - ICFLX0TIM2
	.dw	#_Dummy_EI ; 184 - ICPWGA24
	.dw	#_Dummy_EI ; 185 - ICPWGA25
	.dw	#_Dummy_EI ; 186 - ICPWGA27
	.dw	#_Dummy_EI ; 187 - ICPWGA28
	.dw	#_Dummy_EI ; 188 - ICPWGA29
	.dw	#_Dummy_EI ; 189 - ICPWGA32
	.dw	#_Dummy_EI ; 190 - ICPWGA33
	.dw	#_Dummy_EI ; 191 - ICPWGA34
	.dw	#_Dummy_EI ; 192 - ICPWGA35
	.dw	#_Dummy_EI ; 193 - ICPWGA36
	.dw	#_Dummy_EI ; 194 - ICPWGA37
	.dw	#_Dummy_EI ; 195 - ICPWGA38
	.dw	#_Dummy_EI ; 196 - ICPWGA39
	.dw	#_Dummy_EI ; 197 - ICPWGA40
	.dw	#_Dummy_EI ; 198 - ICPWGA41
	.dw	#_Dummy_EI ; 199 - ICPWGA42
	.dw	#_Dummy_EI ; 200 - ICPWGA43
	.dw	#_Dummy_EI ; 201 - ICPWGA44
	.dw	#_Dummy_EI ; 202 - ICPWGA45
	.dw	#_Dummy_EI ; 203 - ICPWGA46
	.dw	#_Dummy_EI ; 204 - ICPWGA47
	.dw	#_Dummy_EI ; 205 - ICP9
	.dw	#_Dummy_EI ; 206 - ICP13
	.dw	#_Dummy_EI ; 207 - ICP14
	.dw	#_Dummy_EI ; 208 - ICP15
	.dw	#_Dummy_EI ; 209 - ICRTCA01S
	.dw	#_Dummy_EI ; 210 - ICRTCA0AL
	.dw	#_Dummy_EI ; 211 - ICRTCA0R
	.dw	#_Dummy_EI ; 212 - ICADCA1ERR
	.dw	#_Dummy_EI ; 213 - ICADCA1I0
	.dw	#_Dummy_EI ; 214 - ICADCA1I1
	.dw	#_Dummy_EI ; 215 - ICADCA1I2
	.dw	#_Dummy_EI ; 216 - reserved
	;.dw	#_Dummy_EI ; 217 - ICRCAN2ERR
	.dw	#_INTRCAN2ERR ; 217 - ICRCAN2ERR
	;.dw	#_Dummy_EI ; 218 - ICRCAN2REC
	.dw	#_INTRCAN2REC ; 218 - ICRCAN2REC
	;.dw	#_Dummy_EI ; 219 - ICRCAN2TRX
	.dw	#_INTRCAN2TRX ; 219 - ICRCAN2TRX
	;.dw	#_Dummy_EI ; 220 - ICRCAN3ERR
	.dw	#_INTRCAN3ERR ; 220 - ICRCAN3ERR
	;.dw	#_Dummy_EI ; 221 - ICRCAN3REC
	.dw	#_INTRCAN3REC ; 221 - ICRCAN3REC
	;.dw	#_Dummy_EI ; 222 - ICRCAN3TRX
	.dw	#_INTRCAN3TRX ; 222 - ICRCAN3TRX
	.dw	#_Dummy_EI ; 223 - ICCSIG1IC
	.dw	#_Dummy_EI ; 224 - ICCSIG1IR
	.dw	#_Dummy_EI ; 225 - ICCSIG1IRE
	.dw	#_Dummy_EI ; 226 - ICRLIN24
	.dw	#_Dummy_EI ; 227 - ICRLIN25
	.dw	#_Dummy_EI ; 228 - ICRLIN33
	.dw	#_Dummy_EI ; 229 - ICRLIN33UR0
	.dw	#_Dummy_EI ; 230 - ICRLIN33UR1
	.dw	#_Dummy_EI ; 231 - ICRLIN33UR2
	.dw	#_Dummy_EI ; 232 - ICRLIN34
	.dw	#_Dummy_EI ; 233 - ICRLIN34UR0
	.dw	#_Dummy_EI ; 234 - ICRLIN34UR1
	.dw	#_Dummy_EI ; 235 - ICRLIN34UR2
	.dw	#_Dummy_EI ; 236 - ICRLIN35
	.dw	#_Dummy_EI ; 237 - ICRLIN35UR0
	.dw	#_Dummy_EI ; 238 - ICRLIN35UR1
	.dw	#_Dummy_EI ; 239 - ICRLIN35UR2
	.dw	#_Dummy_EI ; 240 - ICPWGA48
	.dw	#_Dummy_EI ; 241 - ICPWGA49
	.dw	#_Dummy_EI ; 242 - ICPWGA50
	.dw	#_Dummy_EI ; 243 - ICPWGA51
	.dw	#_Dummy_EI ; 244 - ICPWGA52
	.dw	#_Dummy_EI ; 245 - ICPWGA53
	.dw	#_Dummy_EI ; 246 - ICPWGA54
	.dw	#_Dummy_EI ; 247 - ICPWGA55
	.dw	#_Dummy_EI ; 248 - ICPWGA56
	.dw	#_Dummy_EI ; 249 - ICPWGA57
	.dw	#_Dummy_EI ; 250 - ICPWGA58
	.dw	#_Dummy_EI ; 251 - ICPWGA59
	.dw	#_Dummy_EI ; 252 - ICPWGA60
	.dw	#_Dummy_EI ; 253 - ICPWGA61
	.dw	#_Dummy_EI ; 254 - ICPWGA62
	.dw	#_Dummy_EI ; 255 - ICPWGA63
	.dw	#_Dummy_EI ; 256 - ICTAUB1I0
	.dw	#_Dummy_EI ; 257 - ICTAUB1I1
	.dw	#_Dummy_EI ; 258 - ICTAUB1I2
	.dw	#_Dummy_EI ; 259 - ICTAUB1I3
	.dw	#_Dummy_EI ; 260 - ICTAUB1I4
	.dw	#_Dummy_EI ; 261 - ICTAUB1I5
	.dw	#_Dummy_EI ; 262 - ICTAUB1I6
	.dw	#_Dummy_EI ; 263 - ICTAUB1I7
	.dw	#_Dummy_EI ; 264 - ICTAUB1I8
	.dw	#_Dummy_EI ; 265 - ICTAUB1I9
	.dw	#_Dummy_EI ; 266 - ICTAUB1I10
	.dw	#_Dummy_EI ; 267 - ICTAUB1I11
	.dw	#_Dummy_EI ; 268 - ICTAUB1I12
	.dw	#_Dummy_EI ; 269 - ICTAUB1I13
	.dw	#_Dummy_EI ; 270 - ICTAUB1I14
	.dw	#_Dummy_EI ; 271 - ICTAUB1I15
	;.dw	#_Dummy_EI ; 272 - ICRCAN4ERR
	.dw	#_INTRCAN4ERR ; 272 - ICRCAN4ERR
	;.dw	#_Dummy_EI ; 273 - ICRCAN4REC
	.dw	#_INTRCAN4REC ; 273 - ICRCAN4REC
	;.dw	#_Dummy_EI ; 274 - ICRCAN4TRX
	.dw	#_INTRCAN4TRX ; 274 - ICRCAN4TRX
	.dw	#_Dummy_EI ; 275 - ICRLIN26
	.dw	#_Dummy_EI ; 276 - ICRLIN27
	.dw	#_Dummy_EI ; 277 - ICPWGA64
	.dw	#_Dummy_EI ; 278 - ICPWGA65
	.dw	#_Dummy_EI ; 279 - ICPWGA66
	.dw	#_Dummy_EI ; 280 - ICPWGA67
	.dw	#_Dummy_EI ; 281 - ICPWGA68
	.dw	#_Dummy_EI ; 282 - ICPWGA69
	.dw	#_Dummy_EI ; 283 - ICPWGA70
	.dw	#_Dummy_EI ; 284 - ICPWGA71
	.dw	#_Dummy_EI ; 285 - ICRLIN28
	.dw	#_Dummy_EI ; 286 - ICRLIN29
	;.dw	#_Dummy_EI ; 287 - ICRCAN5ERR
	.dw	#_INTRCAN5ERR ; 287 - ICRCAN5ERR
	;.dw	#_Dummy_EI ; 288 - ICRCAN5REC
	.dw	#_INTRCAN5REC ; 288 - ICRCAN5REC
	;.dw	#_Dummy_EI ; 289 - ICRCAN5TRX
	.dw	#_INTRCAN5TRX ; 289 - ICRCAN5TRX
	.dw	#_Dummy_EI ; 290 - ICPWGA72
	.dw	#_Dummy_EI ; 291 - ICPWGA73
	.dw	#_Dummy_EI ; 292 - ICPWGA74
	.dw	#_Dummy_EI ; 293 - ICPWGA75
	.dw	#_Dummy_EI ; 294 - ICPWGA76
	.dw	#_Dummy_EI ; 295 - ICPWGA77
	.dw	#_Dummy_EI ; 296 - ICPWGA78
	.dw	#_Dummy_EI ; 297 - ICPWGA79
	.dw	#_Dummy_EI ; 298 - ICDMA16
	.dw	#_Dummy_EI ; 299 - ICDMA17
	.dw	#_Dummy_EI ; 300 - ICDMA18
	.dw	#_Dummy_EI ; 301 - ICDMA19
	.dw	#_Dummy_EI ; 302 - ICDMA20
	.dw	#_Dummy_EI ; 303 - ICDMA21
	.dw	#_Dummy_EI ; 304 - ICDMA22
	.dw	#_Dummy_EI ; 305 - ICDMA23
	.dw	#_Dummy_EI ; 306 - ICDMA24
	.dw	#_Dummy_EI ; 307 - ICDMA25
	.dw	#_Dummy_EI ; 308 - ICDMA26
	.dw	#_Dummy_EI ; 309 - ICDMA27
	.dw	#_Dummy_EI ; 310 - ICDMA28
	.dw	#_Dummy_EI ; 311 - ICDMA29
	.dw	#_Dummy_EI ; 312 - ICDMA30
	.dw	#_Dummy_EI ; 313 - ICDMA31
	.dw	#_Dummy_EI ; 314 - ICOSTM5
	.dw	#_Dummy_EI ; 315 - ICETNB0DATA
	.dw	#_Dummy_EI ; 316 - IC_ETH1
	.dw	#_Dummy_EI ; 317 - IC_ETH2
	.dw	#_Dummy_EI ; 318 - IC_ETH3
	.dw	#_Dummy_EI ; 319 - ICRCANGERR1
	.dw	#_Dummy_EI ; 320 - ICRCANGRECC1
	;.dw	#_Dummy_EI ; 321 - ICRCAN6ERR
	.dw	#_INTRCAN6ERR ; 321 - ICRCAN6ERR
	;.dw	#_Dummy_EI ; 322 - ICRCAN6REC
	.dw	#_INTRCAN6REC ; 322 - ICRCAN6REC
	;.dw	#_Dummy_EI ; 323 - ICRCAN6TRX
	.dw	#_INTRCAN6TRX ; 323 - ICRCAN6TRX
	.dw	#_Dummy_EI ; 324 - ICRLIN210
	.dw	#_Dummy_EI ; 325 - ICRLIN211
	.dw	#_Dummy_EI ; 326 - ICCSIG2IC
	.dw	#_Dummy_EI ; 327 - ICCSIG2IR
	.dw	#_Dummy_EI ; 328 - ICCSIG2IRE
	.dw	#_Dummy_EI ; 329 - ICCSIG3IC
	.dw	#_Dummy_EI ; 330 - ICCSIG3IR
	.dw	#_Dummy_EI ; 331 - ICCSIG3IRE
	;.dw	#_Dummy_EI ; 332 - ICRCAN7ERR
	.dw	#_INTRCAN7ERR ; 332 - ICRCAN6ERR
	;.dw	#_Dummy_EI ; 333 - ICRCAN7REC
	.dw	#_INTRCAN7REC ; 333 - ICRCAN6REC
	;.dw	#_Dummy_EI ; 334 - ICRCAN7TRX
	.dw	#_INTRCAN7TRX ; 334 - ICRCAN6TRX
	.dw	#_Dummy_EI ; 335 - ICPWGA80
	.dw	#_Dummy_EI ; 336 - ICPWGA81
	.dw	#_Dummy_EI ; 337 - ICPWGA82
	.dw	#_Dummy_EI ; 338 - ICPWGA83
	.dw	#_Dummy_EI ; 339 - ICPWGA84
	.dw	#_Dummy_EI ; 340 - ICPWGA85
	.dw	#_Dummy_EI ; 341 - ICPWGA86
	.dw	#_Dummy_EI ; 342 - ICPWGA87
	.dw	#_Dummy_EI ; 343 - ICPWGA88
	.dw	#_Dummy_EI ; 344 - ICPWGA89
	.dw	#_Dummy_EI ; 345 - ICPWGA90
	.dw	#_Dummy_EI ; 346 - ICPWGA91
	.dw	#_Dummy_EI ; 347 - ICPWGA92
	.dw	#_Dummy_EI ; 348 - ICPWGA93
	.dw	#_Dummy_EI ; 349 - ICPWGA94
	.dw	#_Dummy_EI ; 350 - ICPWGA95

	.rept	512 - 3
	.dw	#_Dummy_EI ; INTn
	.endm

	.section ".text", text
	.align	2
_Dummy:
	br	_Dummy

_Dummy_EI:
	br	_Dummy_EI


