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
//Purpose: RSCFD Hardware Mapping Definition
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

#ifndef _MAP_RSCFD_H
#define _MAP_RSCFD_H

#include <interrupt_reg.h>

//#include <ports\standardports\standardports.h>
#include <standardports.h>

/* MAPPED RSCFD: RSCFD_UCIAPRCN_V3 */

#include <map_device.h>
//#include <rscanfd\rscanfd_uciaprcn_v3\rscfd.h>
#include <rscfd.h>

#ifndef DRIVER_LOCAL
//#include <rscanfd\rscanfd_uciaprcn_v3\rscfd_p.h>
#include <rscfd_p.h>
//#include <rscanfd\rscanfd_uciaprcn_v3\rscfd_a.h>
#include <rscfd_a.h>
#endif

#ifdef  APPLICATION_INTERFACE   /* optional UART settings */
#endif

// added @titron
#define RSCFD_USED_RH850_F1KH_D8

/* FURTHER RSCFD OPERATION PROPERTIES */

#define EE_RSCFD_BASE           ( 0xFFD00000 )

#define EE_RSCFD_OFFSET_COMMON  ( 0x00000000 )
#define EE_RSCFD_OFFSET_AFL     ( 0x00001000 )
#define EE_RSCFD_OFFSET_RXMSG   ( 0x00002000 )
#define EE_RSCFD_OFFSET_RXFIFO  ( 0x00006000 )
#define EE_RSCFD_OFFSET_COMFIFO ( 0x00006400 )
#ifdef RH850_F1H_RSCFD20
#define EE_RSCFD_OFFSET_TXMSG   ( 0x00004000 )
#else
#define EE_RSCFD_OFFSET_TXMSG   ( 0x00008000 )
#endif
#define EE_RSCFD_OFFSET_TXHL    ( 0x00010000 )
#define EE_RSCFD_OFFSET_RAM     ( 0x00010400 )

#define EE_RSCFD_FREQFACTOR  ( 0.5 )

#define EE_RSCFD_MAXBAUDRATE ( ( u32 )( OSCILLATOR_FREQUENCY * EE_RSCFD_FREQFACTOR )\
                               / EE_RSCFD_CLKMINFACTOR )

#define EE_RSCFD_FREQFACTORPLLBP  ( 0.2 )

#ifdef RH850_F1H_RSCFD20
#define EE_RSCFD_MAXBAUDRATEPLLBP ( 8000000 )
#else
#define EE_RSCFD_MAXBAUDRATEPLLBP ( ( u32 )( OSCILLATOR_FREQUENCY * EE_RSCFD_FREQFACTORPLLBP )\
                                    / EE_RSCFD_CLKMINFACTOR )
#endif
#define EE_RSCFD_SHUTDOWNTIMEOUT ( 1000000L )

#define EE_RSCFD_VERBOSE            0

/* PORT DEFINITIONS */

#ifdef EE_PIGGY_V4

#define EE_RSCFD_PORT_M0RX0       PORT_10
#define EE_RSCFD_PORT_M0TX0       PORT_10
#define EE_RSCFD_PORT_M0RX1       PORT_0
#define EE_RSCFD_PORT_M0TX1       PORT_0
#define EE_RSCFD_PORT_M0RX2       PORT_0
#define EE_RSCFD_PORT_M0TX2       PORT_0
#define EE_RSCFD_PORT_M0RX3       PORT_1
#define EE_RSCFD_PORT_M0TX3       PORT_1
#define EE_RSCFD_PORT_M0RX4       PORT_1
#define EE_RSCFD_PORT_M0TX4       PORT_1
#define EE_RSCFD_PORT_M0RX5       PORT_0
#define EE_RSCFD_PORT_M0TX5       PORT_0
#define EE_RSCFD_PORT_M0RX6       PORT_8
#define EE_RSCFD_PORT_M0TX6       PORT_8
#define EE_RSCFD_PORT_M0RX7       PORT_8
#define EE_RSCFD_PORT_M0TX7       PORT_8

#define EE_RSCFD_PORT_BIT_M0RX0   BIT_0
#define EE_RSCFD_PORT_BIT_M0TX0   BIT_1
#define EE_RSCFD_PORT_BIT_M0RX1   BIT_2
#define EE_RSCFD_PORT_BIT_M0TX1   BIT_3
#define EE_RSCFD_PORT_BIT_M0RX2   BIT_5
#define EE_RSCFD_PORT_BIT_M0TX2   BIT_4
#define EE_RSCFD_PORT_BIT_M0RX3   BIT_2
#define EE_RSCFD_PORT_BIT_M0TX3   BIT_3
#define EE_RSCFD_PORT_BIT_M0RX4   BIT_12
#define EE_RSCFD_PORT_BIT_M0TX4   BIT_13
#define EE_RSCFD_PORT_BIT_M0RX5   BIT_13
#define EE_RSCFD_PORT_BIT_M0TX5   BIT_14
#define EE_RSCFD_PORT_BIT_M0RX6   BIT_0
#define EE_RSCFD_PORT_BIT_M0TX6   BIT_1
#define EE_RSCFD_PORT_BIT_M0RX7   BIT_4
#define EE_RSCFD_PORT_BIT_M0TX7   BIT_3

#define EE_RSCFD_PORT_FUNC_M0RX0  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0TX0  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0RX1  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0TX1  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0RX2  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0TX2  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0RX3  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0TX3  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0RX4  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0TX4  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0RX5  PORT_FUNCTION_ALTLV4
#define EE_RSCFD_PORT_FUNC_M0TX5  PORT_FUNCTION_ALTLV4
#define EE_RSCFD_PORT_FUNC_M0RX6  PORT_FUNCTION_ALTLV3
#define EE_RSCFD_PORT_FUNC_M0TX6  PORT_FUNCTION_ALTLV3
#define EE_RSCFD_PORT_FUNC_M0RX7  PORT_FUNCTION_ALTLV3
#define EE_RSCFD_PORT_FUNC_M0TX7  PORT_FUNCTION_ALTLV3

#else
#ifndef RH850_F1H_RSCFD20// CetiBox-MCU board
#define EE_RSCFD_PORT_M0RX0       PORT_0
#define EE_RSCFD_PORT_M0TX0       PORT_0
#define EE_RSCFD_PORT_M0RX1       PORT_10
#define EE_RSCFD_PORT_M0TX1       PORT_10
#define EE_RSCFD_PORT_M0RX2       PORT_11
#define EE_RSCFD_PORT_M0TX2       PORT_12
#define EE_RSCFD_PORT_M0RX3       PORT_1
#define EE_RSCFD_PORT_M0TX3       PORT_1
#define EE_RSCFD_PORT_M0RX4       PORT_1
#define EE_RSCFD_PORT_M0TX4       PORT_1
#define EE_RSCFD_PORT_M0RX5       PORT_11
#define EE_RSCFD_PORT_M0TX5       PORT_11
#define EE_RSCFD_PORT_M0RX6       PORT_20
#define EE_RSCFD_PORT_M0TX6       PORT_20
#define EE_RSCFD_PORT_M0RX7       PORT_20
#define EE_RSCFD_PORT_M0TX7       PORT_20

#define EE_RSCFD_PORT_BIT_M0RX0   BIT_1
#define EE_RSCFD_PORT_BIT_M0TX0   BIT_0
#define EE_RSCFD_PORT_BIT_M0RX1   BIT_6
#define EE_RSCFD_PORT_BIT_M0TX1   BIT_7
#define EE_RSCFD_PORT_BIT_M0RX2   BIT_15
#define EE_RSCFD_PORT_BIT_M0TX2   BIT_0
#define EE_RSCFD_PORT_BIT_M0RX3   BIT_2
#define EE_RSCFD_PORT_BIT_M0TX3   BIT_3
#define EE_RSCFD_PORT_BIT_M0RX4   BIT_12
#define EE_RSCFD_PORT_BIT_M0TX4   BIT_13
#define EE_RSCFD_PORT_BIT_M0RX5   BIT_5
#define EE_RSCFD_PORT_BIT_M0TX5   BIT_6
#define EE_RSCFD_PORT_BIT_M0RX6   BIT_0
#define EE_RSCFD_PORT_BIT_M0TX6   BIT_1
#define EE_RSCFD_PORT_BIT_M0RX7   BIT_4
#define EE_RSCFD_PORT_BIT_M0TX7   BIT_5
#else /* RH850/F1H */
#define EE_RSCFD_PORT_M0RX0       PORT_0 /* CAN0RX - P0_1, CAN0RX - P0_1 */
#define EE_RSCFD_PORT_M0TX0       PORT_0 /* CAN0TX - P0_0, CAN0TX - P0_0 */
#define EE_RSCFD_PORT_M0RX1       PORT_0 /* CAN1TX - P0_3, CAN1RX - P0_2 */
#define EE_RSCFD_PORT_M0TX1       PORT_0 /* CAN1TX - P0_3, CAN1RX - P0_2 */
#define EE_RSCFD_PORT_M0RX2       PORT_0 /* CAN2TX - P0_4, CAN4RX - P0_5 */
#define EE_RSCFD_PORT_M0TX2       PORT_0 /* CAN2TX - P0_4, CAN4RX - P0_5 */
#define EE_RSCFD_PORT_M0RX3       PORT_0 /* CAN3TX - P0_8, CAN3RX - P0_7 */
#define EE_RSCFD_PORT_M0TX3       PORT_0 /* CAN3TX - P0_8, CAN3RX - P0_7 */
#define EE_RSCFD_PORT_M0RX4       PORT_1 /* CAN4TX - P1_13, CAN4RX - P1_12 */
#define EE_RSCFD_PORT_M0TX4       PORT_1 /* CAN4TX - P1_13, CAN4RX - P1_12 */
#define EE_RSCFD_PORT_M0RX5       PORT_0 /* CAN5TX - P0_14, CAN5RX - P0_13 */
#define EE_RSCFD_PORT_M0TX5       PORT_0 /* CAN5TX - P0_14, CAN5RX - P0_13 */
//#define EE_RSCFD_PORT_M1RX6       PORT_1 /* CAN6TX - PX_XX, CAN6RX - PX_XX */
//#define EE_RSCFD_PORT_M1TX6       PORT_1 /* CAN6TX - PX_XX, CAN6RX - PX_XX */
//#define EE_RSCFD_PORT_M1RX7       PORT_1 /* CAN7TX - PX_XX, CAN7RX - PX_XX */
//#define EE_RSCFD_PORT_M1TX7       PORT_1 /* CAN7TX - PX_XX, CAN7RX - PX_XX */

#define EE_RSCFD_PORT_BIT_M0RX0   BIT_1
#define EE_RSCFD_PORT_BIT_M0TX0   BIT_0
#define EE_RSCFD_PORT_BIT_M0RX1   BIT_2
#define EE_RSCFD_PORT_BIT_M0TX1   BIT_3
#define EE_RSCFD_PORT_BIT_M0RX2   BIT_5
#define EE_RSCFD_PORT_BIT_M0TX2   BIT_4
#define EE_RSCFD_PORT_BIT_M0RX3   BIT_7
#define EE_RSCFD_PORT_BIT_M0TX3   BIT_8
#define EE_RSCFD_PORT_BIT_M0RX4   BIT_12
#define EE_RSCFD_PORT_BIT_M0TX4   BIT_13
#define EE_RSCFD_PORT_BIT_M0RX5   BIT_13
#define EE_RSCFD_PORT_BIT_M0TX5   BIT_14
//#define EE_RSCFD_PORT_BIT_M0RX6   BIT_X
//#define EE_RSCFD_PORT_BIT_M0TX6   BIT_X
//#define EE_RSCFD_PORT_BIT_M0RX7   BIT_XX
//#define EE_RSCFD_PORT_BIT_M0TX7   BIT_XX
#endif

#define EE_RSCFD_PORT_FUNC_M0RX0  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0TX0  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0RX1  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0TX1  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0RX2  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0TX2  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0RX3  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0TX3  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0RX4  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0TX4  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0RX5  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0TX5  PORT_FUNCTION_ALTLV0
#define EE_RSCFD_PORT_FUNC_M0RX6  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0TX6  PORT_FUNCTION_ALTLV1
#define EE_RSCFD_PORT_FUNC_M0RX7  PORT_FUNCTION_ALTLV5
#define EE_RSCFD_PORT_FUNC_M0TX7  PORT_FUNCTION_ALTLV5

#endif

/* INTERRUPT REGISTER MAPPING */

#define EE_RSCFD_INT_BUNDLINGHOOK ( RSCFD_IntBundlingDecode )  // external bundling decoder
#ifndef CSPLUS_PRJ_USED
#define EE_RSCFD_INT_M0GERR     ( INTC1ICRCANGERR0 )
#define EE_RSCFD_INT_M0RXF0     ( INTC1ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF1     ( INTC1ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF2     ( INTC1ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF3     ( INTC1ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF4     ( INTC1ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF5     ( INTC1ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF6     ( INTC1ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF7     ( INTC1ICRCANGRECC0 )

#define EE_RSCFD_INT_M0TX0      ( INTC1ICRCAN0TRX )
#define EE_RSCFD_INT_M0TXA0     ( INTC1ICRCAN0TRX )
#define EE_RSCFD_INT_M0TXQ0     ( INTC1ICRCAN0TRX )
#define EE_RSCFD_INT_M0ERR0     ( INTC1ICRCAN0ERR )
#define EE_RSCFD_INT_M0THL0     ( INTC1ICRCAN0TRX )
#define EE_RSCFD_INT_M0RXCF0    ( INTC1ICRCAN0REC )
#define EE_RSCFD_INT_M0TXCF0    ( INTC1ICRCAN0TRX )

#define EE_RSCFD_INT_M0TX1      ( INTC2ICRCAN1TRX )
#define EE_RSCFD_INT_M0TXA1     ( INTC2ICRCAN1TRX )
#define EE_RSCFD_INT_M0TXQ1     ( INTC2ICRCAN1TRX )
#define EE_RSCFD_INT_M0ERR1     ( INTC2ICRCAN1ERR )
#define EE_RSCFD_INT_M0THL1     ( INTC2ICRCAN1TRX )
#define EE_RSCFD_INT_M0RXCF1    ( INTC2ICRCAN1REC )
#define EE_RSCFD_INT_M0TXCF1    ( INTC2ICRCAN1TRX )

#define EE_RSCFD_INT_M0TX2      ( INTC2ICRCAN2TRX )
#define EE_RSCFD_INT_M0TXA2     ( INTC2ICRCAN2TRX )
#define EE_RSCFD_INT_M0TXQ2     ( INTC2ICRCAN2TRX )
#define EE_RSCFD_INT_M0ERR2     ( INTC2ICRCAN2ERR )
#define EE_RSCFD_INT_M0THL2     ( INTC2ICRCAN2TRX )
#define EE_RSCFD_INT_M0RXCF2    ( INTC2ICRCAN2REC )
#define EE_RSCFD_INT_M0TXCF2    ( INTC2ICRCAN2TRX )

#define EE_RSCFD_INT_M0TX3      ( INTC2ICRCAN3TRX )
#define EE_RSCFD_INT_M0TXA3     ( INTC2ICRCAN3TRX )
#define EE_RSCFD_INT_M0TXQ3     ( INTC2ICRCAN3TRX )
#define EE_RSCFD_INT_M0ERR3     ( INTC2ICRCAN3ERR )
#define EE_RSCFD_INT_M0THL3     ( INTC2ICRCAN3TRX )
#define EE_RSCFD_INT_M0RXCF3    ( INTC2ICRCAN3REC )
#define EE_RSCFD_INT_M0TXCF3    ( INTC2ICRCAN3TRX )

#define EE_RSCFD_INT_M0TX4      ( INTC2ICRCAN4TRX )
#define EE_RSCFD_INT_M0TXA4     ( INTC2ICRCAN4TRX )
#define EE_RSCFD_INT_M0TXQ4     ( INTC2ICRCAN4TRX )
#define EE_RSCFD_INT_M0ERR4     ( INTC2ICRCAN4ERR )
#define EE_RSCFD_INT_M0THL4     ( INTC2ICRCAN4TRX )
#define EE_RSCFD_INT_M0RXCF4    ( INTC2ICRCAN4REC )
#define EE_RSCFD_INT_M0TXCF4    ( INTC2ICRCAN4TRX )

#define EE_RSCFD_INT_M0TX5      ( INTC2ICRCAN5TRX )
#define EE_RSCFD_INT_M0TXA5     ( INTC2ICRCAN5TRX )
#define EE_RSCFD_INT_M0TXQ5     ( INTC2ICRCAN5TRX )
#define EE_RSCFD_INT_M0ERR5     ( INTC2ICRCAN5ERR )
#define EE_RSCFD_INT_M0THL5     ( INTC2ICRCAN5TRX )
#define EE_RSCFD_INT_M0RXCF5    ( INTC2ICRCAN5REC )
#define EE_RSCFD_INT_M0TXCF5    ( INTC2ICRCAN5TRX )

#define EE_RSCFD_INT_M0TX6      ( INTC2ICRCAN6TRX )
#define EE_RSCFD_INT_M0TXA6     ( INTC2ICRCAN6TRX )
#define EE_RSCFD_INT_M0TXQ6     ( INTC2ICRCAN6TRX )
#define EE_RSCFD_INT_M0ERR6     ( INTC2ICRCAN6ERR )
#define EE_RSCFD_INT_M0THL6     ( INTC2ICRCAN6TRX )
#define EE_RSCFD_INT_M0RXCF6    ( INTC2ICRCAN6REC )
#define EE_RSCFD_INT_M0TXCF6    ( INTC2ICRCAN6TRX )

#define EE_RSCFD_INT_M0TX7      ( INTC2ICRCAN7TRX )
#define EE_RSCFD_INT_M0TXA7     ( INTC2ICRCAN7TRX )
#define EE_RSCFD_INT_M0TXQ7     ( INTC2ICRCAN7TRX )
#define EE_RSCFD_INT_M0ERR7     ( INTC2ICRCAN7ERR )
#define EE_RSCFD_INT_M0THL7     ( INTC2ICRCAN7TRX )
#define EE_RSCFD_INT_M0RXCF7    ( INTC2ICRCAN7REC )
#define EE_RSCFD_INT_M0TXCF7    ( INTC2ICRCAN7TRX )
#else
#define EE_RSCFD_INT_M0GERR     ( REG_ICRCANGERR0 )
#define EE_RSCFD_INT_M0RXF0     ( REG_ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF1     ( REG_ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF2     ( REG_ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF3     ( REG_ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF4     ( REG_ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF5     ( REG_ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF6     ( REG_ICRCANGRECC0 )
#define EE_RSCFD_INT_M0RXF7     ( REG_ICRCANGRECC0 )

#define EE_RSCFD_INT_M0TX0      ( REG_ICRCAN0TRX )
#define EE_RSCFD_INT_M0TXA0     ( REG_ICRCAN0TRX )
#define EE_RSCFD_INT_M0TXQ0     ( REG_ICRCAN0TRX )
#define EE_RSCFD_INT_M0ERR0     ( REG_ICRCAN0ERR )
#define EE_RSCFD_INT_M0THL0     ( REG_ICRCAN0TRX )
#define EE_RSCFD_INT_M0RXCF0    ( REG_ICRCAN0REC )
#define EE_RSCFD_INT_M0TXCF0    ( REG_ICRCAN0TRX )

#define EE_RSCFD_INT_M0TX1      ( REG_ICRCAN1TRX )
#define EE_RSCFD_INT_M0TXA1     ( REG_ICRCAN1TRX )
#define EE_RSCFD_INT_M0TXQ1     ( REG_ICRCAN1TRX )
#define EE_RSCFD_INT_M0ERR1     ( REG_ICRCAN1ERR )
#define EE_RSCFD_INT_M0THL1     ( REG_ICRCAN1TRX )
#define EE_RSCFD_INT_M0RXCF1    ( REG_ICRCAN1REC )
#define EE_RSCFD_INT_M0TXCF1    ( REG_ICRCAN1TRX )

#define EE_RSCFD_INT_M0TX2      ( REG_ICRCAN2TRX )
#define EE_RSCFD_INT_M0TXA2     ( REG_ICRCAN2TRX )
#define EE_RSCFD_INT_M0TXQ2     ( REG_ICRCAN2TRX )
#define EE_RSCFD_INT_M0ERR2     ( REG_ICRCAN2ERR )
#define EE_RSCFD_INT_M0THL2     ( REG_ICRCAN2TRX )
#define EE_RSCFD_INT_M0RXCF2    ( REG_ICRCAN2REC )
#define EE_RSCFD_INT_M0TXCF2    ( REG_ICRCAN2TRX )

#define EE_RSCFD_INT_M0TX3      ( REG_ICRCAN3TRX )
#define EE_RSCFD_INT_M0TXA3     ( REG_ICRCAN3TRX )
#define EE_RSCFD_INT_M0TXQ3     ( REG_ICRCAN3TRX )
#define EE_RSCFD_INT_M0ERR3     ( REG_ICRCAN3ERR )
#define EE_RSCFD_INT_M0THL3     ( REG_ICRCAN3TRX )
#define EE_RSCFD_INT_M0RXCF3    ( REG_ICRCAN3REC )
#define EE_RSCFD_INT_M0TXCF3    ( REG_ICRCAN3TRX )

#define EE_RSCFD_INT_M0TX4      ( REG_ICRCAN4TRX )
#define EE_RSCFD_INT_M0TXA4     ( REG_ICRCAN4TRX )
#define EE_RSCFD_INT_M0TXQ4     ( REG_ICRCAN4TRX )
#define EE_RSCFD_INT_M0ERR4     ( REG_ICRCAN4ERR )
#define EE_RSCFD_INT_M0THL4     ( REG_ICRCAN4TRX )
#define EE_RSCFD_INT_M0RXCF4    ( REG_ICRCAN4REC )
#define EE_RSCFD_INT_M0TXCF4    ( REG_ICRCAN4TRX )

#define EE_RSCFD_INT_M0TX5      ( REG_ICRCAN5TRX )
#define EE_RSCFD_INT_M0TXA5     ( REG_ICRCAN5TRX )
#define EE_RSCFD_INT_M0TXQ5     ( REG_ICRCAN5TRX )
#define EE_RSCFD_INT_M0ERR5     ( REG_ICRCAN5ERR )
#define EE_RSCFD_INT_M0THL5     ( REG_ICRCAN5TRX )
#define EE_RSCFD_INT_M0RXCF5    ( REG_ICRCAN5REC )
#define EE_RSCFD_INT_M0TXCF5    ( REG_ICRCAN5TRX )

#define EE_RSCFD_INT_M0TX6      ( REG_ICRCAN6TRX )
#define EE_RSCFD_INT_M0TXA6     ( REG_ICRCAN6TRX )
#define EE_RSCFD_INT_M0TXQ6     ( REG_ICRCAN6TRX )
#define EE_RSCFD_INT_M0ERR6     ( REG_ICRCAN6ERR )
#define EE_RSCFD_INT_M0THL6     ( REG_ICRCAN6TRX )
#define EE_RSCFD_INT_M0RXCF6    ( REG_ICRCAN6REC )
#define EE_RSCFD_INT_M0TXCF6    ( REG_ICRCAN6TRX )

#define EE_RSCFD_INT_M0TX7      ( REG_ICRCAN7TRX )
#define EE_RSCFD_INT_M0TXA7     ( REG_ICRCAN7TRX )
#define EE_RSCFD_INT_M0TXQ7     ( REG_ICRCAN7TRX )
#define EE_RSCFD_INT_M0ERR7     ( REG_ICRCAN7ERR )
#define EE_RSCFD_INT_M0THL7     ( REG_ICRCAN7TRX )
#define EE_RSCFD_INT_M0RXCF7    ( REG_ICRCAN7REC )
#define EE_RSCFD_INT_M0TXCF7    ( REG_ICRCAN7TRX )
#endif
#define EE_RSCFD_INTCLEAR         ( 0x008F )       // Interrupt mask bit
#define EE_RSCFD_INTENABLEDEFAULT ( 0x0040 )


/* The RSCFD Memory Mapping */  

#define EE_RSCFD_RAMTEST_PAGES          ( 265 )
#define EE_RSCFD_RAMTEST_LASTPGENTRIES  ( 64 )

static const u08 ee_rscfd_channels[ EE_RSCFD_MACROS ] =
{
    8                                                 /* unit 0 */
};   

static const u08 ee_rscfd_txqentries[ EE_RSCFD_MACROS ]
                                    [ EE_RSCFD_MAXCHANNELS ]
                                    [ EE_RSCFD_MAXTXQUEUES ] =
{
  {
    { ( EE_RSCFD_MAXTXBUFFERS/2 - 1 ), ( EE_RSCFD_MAXTXBUFFERS - 1 ) },
    { ( EE_RSCFD_MAXTXBUFFERS/2 - 1 ), ( EE_RSCFD_MAXTXBUFFERS - 1 ) },
    { ( EE_RSCFD_MAXTXBUFFERS/2 - 1 ), ( EE_RSCFD_MAXTXBUFFERS - 1 ) },
    { ( EE_RSCFD_MAXTXBUFFERS/2 - 1 ), ( EE_RSCFD_MAXTXBUFFERS - 1 ) },
    { ( EE_RSCFD_MAXTXBUFFERS/2 - 1 ), ( EE_RSCFD_MAXTXBUFFERS - 1 ) },
    { ( EE_RSCFD_MAXTXBUFFERS/2 - 1 ), ( EE_RSCFD_MAXTXBUFFERS - 1 ) },
    { ( EE_RSCFD_MAXTXBUFFERS/2 - 1 ), ( EE_RSCFD_MAXTXBUFFERS - 1 ) },
    { ( EE_RSCFD_MAXTXBUFFERS/2 - 1 ), ( EE_RSCFD_MAXTXBUFFERS - 1 ) }
  }
};

static struct ee_rscfd_common *ee_rscfd_common_p[ EE_RSCFD_MACROS ] =
{
    ( ee_rscfd_common * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMMON
                       + 0x00000000 )                               /* unit 0 */
};   

static struct ee_rscfd_aflpage *ee_rscfd_aflpage_p[ EE_RSCFD_MACROS ] =
{
    ( ee_rscfd_aflpage * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_AFL 
                        + 0x00000000 )                              /* unit 0 */
};   

static struct ee_rscfd_rxmsg *ee_rscfd_rxmsg_p[ EE_RSCFD_MACROS ] =
{
    ( ee_rscfd_rxmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_RXMSG 
                      + 0x00000000 )                                /* unit 0 */
};   

static struct ee_rscfd_txmsg *ee_rscfd_txmsg_p[ EE_RSCFD_MACROS ]
                                              [ EE_RSCFD_MAXCHANNELS ] =
{
  {
    ( ee_rscfd_txmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXMSG + 0x00000000 ),        /* unit 0, ch 0 */
    ( ee_rscfd_txmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXMSG + 0x00001000 ),        /* unit 0, ch 1 */
    ( ee_rscfd_txmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXMSG + 0x00002000 ),        /* unit 0, ch 2 */
    ( ee_rscfd_txmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXMSG + 0x00003000 ),        /* unit 0, ch 3 */
    ( ee_rscfd_txmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXMSG + 0x00004000 ),        /* unit 0, ch 4 */
    ( ee_rscfd_txmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXMSG + 0x00005000 ),        /* unit 0, ch 5 */
    ( ee_rscfd_txmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXMSG + 0x00006000 ),        /* unit 0, ch 6 */
    ( ee_rscfd_txmsg * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXMSG + 0x00007000 )         /* unit 0, ch 7 */
  }
};   

static struct ee_rscfd_rxfifo *ee_rscfd_rxfifo_p[ EE_RSCFD_MACROS ] =
{
    ( ee_rscfd_rxfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_RXFIFO 
                       + 0x00000000 )                               /* unit 0 */
};   

static struct ee_rscfd_comfifo *ee_rscfd_comfifo_p[ EE_RSCFD_MACROS ]
                                                  [ EE_RSCFD_MAXCHANNELS ] =
{
  {
    ( ee_rscfd_comfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMFIFO + 0x00000000 ),    /* unit 0, ch 0 */
    ( ee_rscfd_comfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMFIFO + 0x00000180 ),    /* unit 0, ch 1 */
    ( ee_rscfd_comfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMFIFO + 0x00000300 ),    /* unit 0, ch 2 */
    ( ee_rscfd_comfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMFIFO + 0x00000480 ),    /* unit 0, ch 3 */
    ( ee_rscfd_comfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMFIFO + 0x00000600 ),    /* unit 0, ch 4 */
    ( ee_rscfd_comfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMFIFO + 0x00000780 ),    /* unit 0, ch 5 */
    ( ee_rscfd_comfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMFIFO + 0x00000900 ),    /* unit 0, ch 6 */
    ( ee_rscfd_comfifo * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_COMFIFO + 0x00000A80 )     /* unit 0, ch 7 */
  }
};   

static struct ee_rscfd_thl *ee_rscfd_thl_p[ EE_RSCFD_MACROS ]
                                          [ EE_RSCFD_MAXCHANNELS ] =
{
  {
    ( ee_rscfd_thl * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXHL + 0x00000000 ),           /* unit 0, ch 0 */
    ( ee_rscfd_thl * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXHL + 0x00000008 ),           /* unit 0, ch 1 */
    ( ee_rscfd_thl * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXHL + 0x00000010 ),           /* unit 0, ch 2 */
    ( ee_rscfd_thl * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXHL + 0x00000018 ),           /* unit 0, ch 3 */
    ( ee_rscfd_thl * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXHL + 0x00000020 ),           /* unit 0, ch 4 */
    ( ee_rscfd_thl * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXHL + 0x00000028 ),           /* unit 0, ch 5 */
    ( ee_rscfd_thl * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXHL + 0x00000030 ),           /* unit 0, ch 6 */
    ( ee_rscfd_thl * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_TXHL + 0x00000038 )            /* unit 0, ch 7 */
  }
};

static struct ee_rscfd_ram *ee_rscfd_ram_p[ EE_RSCFD_MACROS ] =
{
  ( ee_rscfd_ram * )( EE_RSCFD_BASE + EE_RSCFD_OFFSET_RAM
                    + 0x00000000 )                                  /* unit 0 */
};


#endif
