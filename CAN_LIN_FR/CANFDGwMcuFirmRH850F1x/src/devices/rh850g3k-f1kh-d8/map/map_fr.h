//============================================================================
// PROJECT = RH850/F1KH-D8
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2017 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: FlexRay Hardware Mapping Definition
//
//Warranty Disclaimer
//
//Because the Product(s) is licensed free of charge, there is no warranty 
//of any kind whatsoever and expressly disclaimed and excluded by RENESAS, 
//either expressed or implied, including but not limited to those for 
//non-infringement of intellectual property, merchantability and/or 
//fitness for the particular purpose. 
//RENESAS shall not have any obligation to maintain, service or provide bug 
//fixes for the supplied Product(s) and/or the Application.
//
//Each User is solely responsible for determining the appropriateness of 
//using the Product(s) and assumes all risks associated with its exercise 
//of rights under this Agreement, including, but not limited to the risks 
//and costs of program errors, compliance with applicable laws, damage to 
//or loss of data, programs or equipment, and unavailability or 
//interruption of operations.
//
//Limitation of Liability
//
//In no event shall RENESAS be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. RENESAS shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by RENESAS in connection with the Product(s) and/or the 
//Application.
//
//
//
//============================================================================
// Environment: Devices:          RH850/F1KH-D8
//              Assembler:        GHS MULTI 
//              C-Compiler:       GHS MULTI 
//              Linker:           GHS MULTI 
//              Debugger:         GHS MULTI 
//============================================================================

#ifndef _MAP_FR_H
#define _MAP_FR_H

/* MAPPED FR: fr_flxa_0012 */

#include <map_device.h>
//#include <fr\fr_flxa_0012\fr_flxa_0012_Node2_a.h>
#include <fr_flxa_0012_Node2_a.h>

#define Application_2
//#define Application_1

// test mode definition ---start @titron
#include "TypeDefines.h"

#define __TEST_PAYLOAD_0  //added @titron

#define INDEX_SFDL_1_BUSLOAD_100_PERCENT	0 /* 2 bytes, 100% */
#define INDEX_SFDL_2_BUSLOAD_100_PERCENT	1 /* 4 bytes, 100% */
#define INDEX_SFDL_127_BUSLOAD_100_PERCENT	2 /* 254 bytes, 100% */
//#define FLX_CURRENT_TEST_MODE 				INDEX_SFDL_127_BUSLOAD_100_PERCENT
#define FLX_CURRENT_TEST_MODE 				INDEX_SFDL_1_BUSLOAD_100_PERCENT
#define FLX_TEST_TOTAL_MODE_NUM             3

typedef struct{
	u32 reg_GTUC7_SSl; /* GTUC7 (gdStaticSlot), 4~659MT */

	u32 reg_GTUC1_UT; /* GTUC1 (pMicroPerCycle), 640~640000uT */
	u32 reg_GTUC2_MPC; /* GTUC2 (gMacroPerCycle), 10~16000 MT */
	u32 reg_GTUC4_NIT; /* GTUC4: Network Idle Time Start, 7~15997MT */
	u32 reg_GTUC4_OCS; /* GTUC4 (gOffsetCorrectionStart), 8~15998MT */
	u32 reg_SUCC2_LT; /* SUCC2 (pdListenTimeout), 1284~1283846uT */

	u32 reg_MHDC_SFDL; /* MHDC (gPayloadLengthStatic), 0~127 */
	u32 quadByteNum; /* quad-byte number, 1~64 */

	u32 testData;
}s_busload_paras;


extern s_busload_paras testModeParas[FLX_TEST_TOTAL_MODE_NUM];
// test mode definition ---start @titron

/* PORT DEFINITIONS */
#define CETITEC_MCU
#define EE_FR_PORT_TXA        PORT_11
#define EE_FR_PORT_TXENA      PORT_10
#define EE_FR_PORT_RXA        PORT_10

#define EE_FR_PORT_TXB        PORT_10
#define EE_FR_PORT_TXENB      PORT_10
#define EE_FR_PORT_RXB        PORT_10

#define EE_FR_PORT_BIT_TXA    BIT_1
#define EE_FR_PORT_BIT_TXENA  BIT_11
#define EE_FR_PORT_BIT_RXA    BIT_14

#define EE_FR_PORT_BIT_TXB    BIT_8
#define EE_FR_PORT_BIT_TXENB  BIT_13
#define EE_FR_PORT_BIT_RXB    BIT_9

#if 0
#define EE_FR_PORT_FUNC_TXA   PORT_FUNCTION_ALTLV0
#define EE_FR_PORT_FUNC_TXENA PORT_FUNCTION_ALTLV1
#define EE_FR_PORT_FUNC_RXA   PORT_FUNCTION_ALTLV1

#define EE_FR_PORT_FUNC_TXB   PORT_FUNCTION_ALTLV1
#define EE_FR_PORT_FUNC_TXENB PORT_FUNCTION_ALTLV1
#define EE_FR_PORT_FUNC_RXB   PORT_FUNCTION_ALTLV5
#else
#define EE_FR_PORT_FUNC_TXA   PORT_FUNCTION_ALTLV1
#define EE_FR_PORT_FUNC_TXENA PORT_FUNCTION_ALTLV2
#define EE_FR_PORT_FUNC_RXA   PORT_FUNCTION_ALTLV2

#define EE_FR_PORT_FUNC_TXB   PORT_FUNCTION_ALTLV2
#define EE_FR_PORT_FUNC_TXENB PORT_FUNCTION_ALTLV2
#define EE_FR_PORT_FUNC_RXB   PORT_FUNCTION_ALTLV6
#endif

#define EE_FR_PORT_FUNC_RXENA // P10_10, Added @Titron
#define EE_FR_PORT_FUNC_ERRNA // P10_15, Added @Titron
#define EE_FR_PORT_FUNC_RXENB // P0_6, Added @Titron
#define EE_FR_PORT_FUNC_ERRNB // P8_11, Added @Titron

#ifdef CETITEC_MCU

#define EE_FR_PORT_ENA        PORT_8
#define EE_FR_PORT_WAKEA      PORT_11
#define EE_FR_PORT_BGEA       PORT_1
#define EE_FR_PORT_STBNA      PORT_1

#define EE_FR_PORT_BIT_ENA    BIT_10
#define EE_FR_PORT_BIT_WAKEA  BIT_0
#define EE_FR_PORT_BIT_BGEA   BIT_10
#define EE_FR_PORT_BIT_STBNA  BIT_11

/* Not yet enabled due to hardware shortcuts 
*/
#if 1
#define EE_FR_PORT_ENB        PORT_12
#define EE_FR_PORT_WAKEB      PORT_1
#define EE_FR_PORT_BGEB       PORT_1
#define EE_FR_PORT_STBNB      PORT_12

#define EE_FR_PORT_BIT_ENB    BIT_2
#define EE_FR_PORT_BIT_WAKEB  BIT_14
#define EE_FR_PORT_BIT_BGEB   BIT_15
#define EE_FR_PORT_BIT_STBNB  BIT_1
#endif


#else //RH850/F1x FPGA BOARD
#define EE_FR_PORT_ENA        PORT_11
//#define EE_FR_PORT_WAKEA      PORT_11
//#define EE_FR_PORT_BGEA       PORT_1
#define EE_FR_PORT_STBNA      PORT_11

#define EE_FR_PORT_BIT_ENA    BIT_7
//#define EE_FR_PORT_BIT_WAKEA  BIT_0
//#define EE_FR_PORT_BIT_BGEA   BIT_10
#define EE_FR_PORT_BIT_STBNA  BIT_6

#define EE_FR_PORT_ENB        PORT_11
//#define EE_FR_PORT_WAKEB
//#define EE_FR_PORT_BGEB
#define EE_FR_PORT_STBNB      PORT_11

#define EE_FR_PORT_BIT_ENB    BIT_3
//#define EE_FR_PORT_BIT_WAKEB
//#define EE_FR_PORT_BIT_BGEB
#define EE_FR_PORT_BIT_STBNB  BIT_2
#endif

/* INTERRUPT REGISTER MAPPING */

#define EE_FR_INT_INT0      ( INTC2ICFLXA0LINE0 )
#define EE_FR_INT_INT1      ( INTC2ICFLXA0LINE1 )
#define EE_FR_INT_TIMER0    ( INTC2ICFLXA0TIM0 )
#define EE_FR_INT_TIMER1    ( INTC2ICFLXA0TIM1 )
#define EE_FR_INT_TIMER2    ( INTC2ICFLXA0TIM2 )

#define EE_FR_INTLEV_INT0   ( 0x0042 )
#define EE_FR_INTLEV_INT1   ( 0x0043 )
#define EE_FR_INTLEV_TIMER0 ( 0x0041 )
#define EE_FR_INTLEV_TIMER1 ( 0x0044 )
#define EE_FR_INTLEV_TIMER2 ( 0x0045 )

#endif
