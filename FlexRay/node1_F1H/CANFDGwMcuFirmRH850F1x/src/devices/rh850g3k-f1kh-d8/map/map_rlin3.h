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
//Purpose: RLIN3 Hardware Mapping Definition
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

#ifndef _MAP_RLIN3_H
#define _MAP_RLIN3_H


#include <interrupt_reg.h>

//#include <ports\standardports\standardports.h>
#include <standardports.h>

/* MAPPED RLIN3: RLIN3_UCIAPRLN */

#include <map_device.h>
//#include <rlin3\rlin3_uciaprln\rlin3.h>
#include <rlin3.h>

#ifndef DRIVER_LOCAL
//#include <rlin3\rlin3_uciaprln\rlin3_p.h>
//#include <rlin3\rlin3_uciaprln\rlin3_a.h>
//#include <rlin3\rlin3_uciaprln\rlin3_s.h>
//#include <rlin3\rlin3_uciaprln\rlin3_as.h>
#include <rlin3_p.h>
#include <rlin3_a.h>
#include <rlin3_s.h>
#include <rlin3_as.h>

#endif

/* FURTHER RLIN3 OPERATION PROPERTIES */

#define RLIN3_BASE              ( 0xFFCE2000 )
#define RLIN3_OFFSET_CHANNEL0   ( 0x00000000 )
#define RLIN3_OFFSET_CHANNEL1   ( 0x00000040 )
#define RLIN3_OFFSET_CHANNEL2   ( 0x00000080 )
#define RLIN3_OFFSET_CHANNEL3   ( 0x000000C0 )
#define RLIN3_OFFSET_CHANNEL4   ( 0x00000100 )
#define RLIN3_OFFSET_CHANNEL5   ( 0x00000140 )
#define RLIN3_OFFSET_CHANNEL6   ( 0x00000180 )
#define RLIN3_OFFSET_CHANNEL7   ( 0x000001C0 )


#define RLIN3_FREQFACTOR        ( 0.5 )

#define RLIN3_AUTOSARIF

/* Baudrate limits */

#define RLIN3_MINBAUDRATE       ( 100L )
#define RLIN3_MAXBAUDRATE       ( 2000000L )

/* Maximum Waiting Loop Counts */

#define RLIN3_SENDTIMEOUT       ( 1000000L )


/* PORT DEFINITIONS */

#ifdef EE_PIGGY_V4

/* F1KH-D8 Application Board, UART0 / LIN0 */
/* in conflict with FLEXRAY, exclusive switching is required */

#define RLIN3_PORT_RXD0         PORT_10
#define RLIN3_PORT_BIT_RXD0     BIT_9 
#define RLIN3_PORT_TXD0         PORT_10
#define RLIN3_PORT_BIT_TXD0     BIT_10
#define RLIN3_PORT_FUNC_RXD0    PORT_FUNCTION_ALTLV1
#define RLIN3_PORT_FUNC_TXD0    PORT_FUNCTION_ALTLV1

/* F1KH-D8 Application Board, UART1 / LIN1 */

#define RLIN3_PORT_RXD1         PORT_0
#define RLIN3_PORT_BIT_RXD1     BIT_4 
#define RLIN3_PORT_TXD1         PORT_0
#define RLIN3_PORT_BIT_TXD1     BIT_5
#define RLIN3_PORT_FUNC_RXD1    PORT_FUNCTION_ALTLV0
#define RLIN3_PORT_FUNC_TXD1    PORT_FUNCTION_ALTLV0

/* F1KH-D8 Application Board, LIN12 */
/* in conflict with FLEXRAY, exclusive switching is required */

#define RLIN3_PORT_RXD2         PORT_10
#define RLIN3_PORT_BIT_RXD2     BIT_13 
#define RLIN3_PORT_TXD2         PORT_10
#define RLIN3_PORT_BIT_TXD2     BIT_14
#define RLIN3_PORT_FUNC_RXD2    PORT_FUNCTION_ALTLV1
#define RLIN3_PORT_FUNC_TXD2    PORT_FUNCTION_ALTLV1

/* F1KH-D8 Application Board, LIN13 */

#define RLIN3_PORT_RXD3         PORT_1
#define RLIN3_PORT_BIT_RXD3     BIT_0 
#define RLIN3_PORT_TXD3         PORT_1
#define RLIN3_PORT_BIT_TXD3     BIT_1
#define RLIN3_PORT_FUNC_RXD3    PORT_FUNCTION_ALTLV0
#define RLIN3_PORT_FUNC_TXD3    PORT_FUNCTION_ALTLV0

/* F1KH-D8 Application Board, LIN14 */

#define RLIN3_PORT_RXD4         PORT_8
#define RLIN3_PORT_BIT_RXD4     BIT_8 
#define RLIN3_PORT_TXD4         PORT_8
#define RLIN3_PORT_BIT_TXD4     BIT_9
#define RLIN3_PORT_FUNC_RXD4    PORT_FUNCTION_ALTLV3
#define RLIN3_PORT_FUNC_TXD4    PORT_FUNCTION_ALTLV3

/* F1KH-D8 Application Board, LIN15 */

#define RLIN3_PORT_RXD5         PORT_1
#define RLIN3_PORT_BIT_RXD5     BIT_4 
#define RLIN3_PORT_TXD5         PORT_1
#define RLIN3_PORT_BIT_TXD5     BIT_5
#define RLIN3_PORT_FUNC_RXD5    PORT_FUNCTION_ALTLV0
#define RLIN3_PORT_FUNC_TXD5    PORT_FUNCTION_ALTLV0

/* F1KH-D8 Application Board, LIN11 (wired manually) */

#define RLIN3_PORT_RXD6         PORT_12
#define RLIN3_PORT_BIT_RXD6     BIT_0 
#define RLIN3_PORT_TXD6         PORT_11
#define RLIN3_PORT_BIT_TXD6     BIT_15
#define RLIN3_PORT_FUNC_RXD6    PORT_FUNCTION_ALTLV4
#define RLIN3_PORT_FUNC_TXD6    PORT_FUNCTION_ALTLV4

/* F1KH-D8 Application Board, LIN10 */

#define RLIN3_PORT_RXD7         PORT_8
#define RLIN3_PORT_BIT_RXD7     BIT_10 
#define RLIN3_PORT_TXD7         PORT_8
#define RLIN3_PORT_BIT_TXD7     BIT_2
#define RLIN3_PORT_FUNC_RXD7    PORT_FUNCTION_ALTLV3
#define RLIN3_PORT_FUNC_TXD7    PORT_FUNCTION_ALTLV3

#else

/* F1KH-D8 Application Board, UART0/LIN0 */

#define RLIN3_PORT_RXD0         PORT_10
#define RLIN3_PORT_BIT_RXD0     BIT_9 
#define RLIN3_PORT_TXD0         PORT_10
#define RLIN3_PORT_BIT_TXD0     BIT_10
#define RLIN3_PORT_FUNC_RXD0    PORT_FUNCTION_ALTLV1
#define RLIN3_PORT_FUNC_TXD0    PORT_FUNCTION_ALTLV1

/* F1KH-D8 Application Board, LIN11 */

#define RLIN3_PORT_RXD1         PORT_0
#define RLIN3_PORT_BIT_RXD1     BIT_4 
#define RLIN3_PORT_TXD1         PORT_0
#define RLIN3_PORT_BIT_TXD1     BIT_5
#define RLIN3_PORT_FUNC_RXD1    PORT_FUNCTION_ALTLV0
#define RLIN3_PORT_FUNC_TXD1    PORT_FUNCTION_ALTLV0

/* F1KH-D8 Application Board, LIN12 */

#define RLIN3_PORT_RXD2         PORT_0
#define RLIN3_PORT_BIT_RXD2     BIT_13 
#define RLIN3_PORT_TXD2         PORT_0
#define RLIN3_PORT_BIT_TXD2     BIT_14
#define RLIN3_PORT_FUNC_RXD2    PORT_FUNCTION_ALTLV0
#define RLIN3_PORT_FUNC_TXD2    PORT_FUNCTION_ALTLV0

/* F1KH-D8 Application Board, LIN13 */

#define RLIN3_PORT_RXD3         PORT_1
#define RLIN3_PORT_BIT_RXD3     BIT_0 
#define RLIN3_PORT_TXD3         PORT_1
#define RLIN3_PORT_BIT_TXD3     BIT_1
#define RLIN3_PORT_FUNC_RXD3    PORT_FUNCTION_ALTLV0
#define RLIN3_PORT_FUNC_TXD3    PORT_FUNCTION_ALTLV0

/* F1KH-D8 Application Board, LIN14 */

#define RLIN3_PORT_RXD4         PORT_8
#define RLIN3_PORT_BIT_RXD4     BIT_8 
#define RLIN3_PORT_TXD4         PORT_8
#define RLIN3_PORT_BIT_TXD4     BIT_9
#define RLIN3_PORT_FUNC_RXD4    PORT_FUNCTION_ALTLV3
#define RLIN3_PORT_FUNC_TXD4    PORT_FUNCTION_ALTLV3

/* F1KH-D8 Application Board, LIN15 */

#define RLIN3_PORT_RXD5         PORT_1
#define RLIN3_PORT_BIT_RXD5     BIT_4 
#define RLIN3_PORT_TXD5         PORT_1
#define RLIN3_PORT_BIT_TXD5     BIT_5
#define RLIN3_PORT_FUNC_RXD5    PORT_FUNCTION_ALTLV0
#define RLIN3_PORT_FUNC_TXD5    PORT_FUNCTION_ALTLV0

/* F1KH-D8 Application Board, not assignable on V3 or lower: RLIN3 channel 6 */

/* F1KH-D8 Application Board, V3 or lower: PWM22(TX), PWM42(RX) manual cabling required */

#define RLIN3_PORT_RXD7         PORT_8
#define RLIN3_PORT_BIT_RXD7     BIT_10 
#define RLIN3_PORT_TXD7         PORT_8
#define RLIN3_PORT_BIT_TXD7     BIT_2
#define RLIN3_PORT_FUNC_RXD7    PORT_FUNCTION_ALTLV3
#define RLIN3_PORT_FUNC_TXD7    PORT_FUNCTION_ALTLV3

#endif

/* INTERRUPT REGISTER MAPPING */
#ifndef CSPLUS_PRJ_USED
#define RLIN3_INTM0TX           INTC2ICRLIN30UR0
#define RLIN3_INTM0RX           INTC2ICRLIN30UR1
#define RLIN3_INTM0ERR          INTC2ICRLIN30UR2
#define RLIN3_INTM0COM          INTC2ICRLIN30
#define RLIN3_INTM1TX           INTC2ICRLIN31UR0
#define RLIN3_INTM1RX           INTC2ICRLIN31UR1
#define RLIN3_INTM1ERR          INTC2ICRLIN31UR2
#define RLIN3_INTM1COM          INTC2ICRLIN31
#define RLIN3_INTM2TX           INTC2ICRLIN32UR0
#define RLIN3_INTM2RX           INTC2ICRLIN32UR1
#define RLIN3_INTM2ERR          INTC2ICRLIN32UR2
#define RLIN3_INTM2COM          INTC2ICRLIN32
#define RLIN3_INTM3TX           INTC2ICRLIN33UR0
#define RLIN3_INTM3RX           INTC2ICRLIN33UR1
#define RLIN3_INTM3ERR          INTC2ICRLIN33UR2
#define RLIN3_INTM3COM          INTC2ICRLIN33
#define RLIN3_INTM4TX           INTC2ICRLIN34UR0
#define RLIN3_INTM4RX           INTC2ICRLIN34UR1
#define RLIN3_INTM4ERR          INTC2ICRLIN34UR2
#define RLIN3_INTM4COM          INTC2ICRLIN34
#define RLIN3_INTM5TX           INTC2ICRLIN35UR0
#define RLIN3_INTM5RX           INTC2ICRLIN35UR1
#define RLIN3_INTM5ERR          INTC2ICRLIN35UR2
#define RLIN3_INTM5COM          INTC2ICRLIN35
#define RLIN3_INTM6TX           INTC2ICRLIN36UR0
#define RLIN3_INTM6RX           INTC2ICRLIN36UR1
#define RLIN3_INTM6ERR          INTC2ICRLIN36UR2
#define RLIN3_INTM6COM          INTC2ICRLIN36
#define RLIN3_INTM7TX           INTC2ICRLIN37UR0
#define RLIN3_INTM7RX           INTC2ICRLIN37UR1
#define RLIN3_INTM7ERR          INTC2ICRLIN37UR2
#define RLIN3_INTM7COM          INTC2ICRLIN37
#else
#define RLIN3_INTM0TX           REG_ICRLIN30UR0
#define RLIN3_INTM0RX           REG_ICRLIN30UR1
#define RLIN3_INTM0ERR          REG_ICRLIN30UR2
#define RLIN3_INTM0COM          REG_ICRLIN30
#define RLIN3_INTM1TX           REG_ICRLIN31UR0
#define RLIN3_INTM1RX           REG_ICRLIN31UR1
#define RLIN3_INTM1ERR          REG_ICRLIN31UR2
#define RLIN3_INTM1COM          REG_ICRLIN31
#define RLIN3_INTM2TX           REG_ICRLIN32UR0
#define RLIN3_INTM2RX           REG_ICRLIN32UR1
#define RLIN3_INTM2ERR          REG_ICRLIN32UR2
#define RLIN3_INTM2COM          REG_ICRLIN32
#define RLIN3_INTM3TX           REG_ICRLIN33UR0
#define RLIN3_INTM3RX           REG_ICRLIN33UR1
#define RLIN3_INTM3ERR          REG_ICRLIN33UR2
#define RLIN3_INTM3COM          REG_ICRLIN33
#define RLIN3_INTM4TX           REG_ICRLIN34UR0
#define RLIN3_INTM4RX           REG_ICRLIN34UR1
#define RLIN3_INTM4ERR          REG_ICRLIN34UR2
#define RLIN3_INTM4COM          REG_ICRLIN34
#define RLIN3_INTM5TX           REG_ICRLIN35UR0
#define RLIN3_INTM5RX           REG_ICRLIN35UR1
#define RLIN3_INTM5ERR          REG_ICRLIN35UR2
#define RLIN3_INTM5COM          REG_ICRLIN35
//#define RLIN3_INTM6TX           INTC2ICRLIN36UR0
//#define RLIN3_INTM6RX           INTC2ICRLIN36UR1
//#define RLIN3_INTM6ERR          INTC2ICRLIN36UR2
//#define RLIN3_INTM6COM          REG_ICRLIN36
//#define RLIN3_INTM7TX           INTC2ICRLIN37UR0
//#define RLIN3_INTM7RX           INTC2ICRLIN37UR1
//#define RLIN3_INTM7ERR          INTC2ICRLIN37UR2
//#define RLIN3_INTM7COM          INTC2ICRLIN37
#endif

#define RLIN3_INTCLEAR         ( 0x008F )       // Interrupt mask bit
#define RLIN3_INTENABLEDEFAULT ( 0x0040 )
#define RLIN3_INTFLAG          ( 0x1000 )


/* The RLIN3 Memory Mapping */  

static struct rlin3 *rlin3_p[ RLIN3_MACROS ] =
{
    ( rlin3 * )( RLIN3_BASE + RLIN3_OFFSET_CHANNEL0 ),              /* unit 0 */
    ( rlin3 * )( RLIN3_BASE + RLIN3_OFFSET_CHANNEL1 ),              /* unit 1 */
    ( rlin3 * )( RLIN3_BASE + RLIN3_OFFSET_CHANNEL2 ),              /* unit 2 */
    ( rlin3 * )( RLIN3_BASE + RLIN3_OFFSET_CHANNEL3 ),              /* unit 3 */
    ( rlin3 * )( RLIN3_BASE + RLIN3_OFFSET_CHANNEL4 ),              /* unit 4 */
    ( rlin3 * )( RLIN3_BASE + RLIN3_OFFSET_CHANNEL5 ),              /* unit 5 */
    ( rlin3 * )( RLIN3_BASE + RLIN3_OFFSET_CHANNEL6 ),              /* unit 6 */
    ( rlin3 * )( RLIN3_BASE + RLIN3_OFFSET_CHANNEL7 )               /* unit 7 */
};   


#endif
