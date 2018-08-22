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
//Purpose: RSCAN Hardware Mapping Definition
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

#ifndef _MAP_RLIN2_H
#define _MAP_RLIN2_H

#include <interrupt_reg.h>

//#include <ports\standardports\standardports.h>
#include <standardports.h>

/* MAPPED RLIN2: RLIN2_UCIAPRLN */

#include <map_device.h>
//#include <rlin2\rlin2_uciaprln\rlin2.h>
#include <rlin2.h>

#ifndef DRIVER_LOCAL
//#include <rlin2\rlin2_uciaprln\rlin2_p.h>
//#include <rlin2\rlin2_uciaprln\rlin2_a.h>
//#include <rlin2\rlin2_uciaprln\rlin2_s.h>
//#include <rlin2\rlin2_uciaprln\rlin2_as.h>
#include <rlin2_p.h>
#include <rlin2_a.h>
#include <rlin2_s.h>
#include <rlin2_as.h>
#endif

/* FURTHER RLIN2 OPERATION PROPERTIES */

#define RLIN2_BASE           ( 0xFFCE0000 )
#define RLIN2_OFFSET_UNIT0   ( 0x00000000 )
#define RLIN2_OFFSET_UNIT1   ( 0x00000080 )
#define RLIN2_OFFSET_UNIT2   ( 0x00000100 )

#define RLIN2_FREQFACTOR        ( 0.5 )

/* Baudrate limits */

#define RLIN2_MINBAUDRATE       ( 100L )
#define RLIN2_MAXBAUDRATE       ( 20000L )

/* #define RLIN2_AUTOSARIF */

/* PORT DEFINITIONS */

/* F1KM-S4 Application Board V4, LIN22 ... LIN29 */

#define RLIN2_PORT_M0RX2        PORT_0
#define RLIN2_PORT_BIT_M0RX2    BIT_9 
#define RLIN2_PORT_M0TX2        PORT_0
#define RLIN2_PORT_BIT_M0TX2    BIT_10
#define RLIN2_PORT_FUNC_M0RX2   PORT_FUNCTION_ALTLV2
#define RLIN2_PORT_FUNC_M0TX2   PORT_FUNCTION_ALTLV2

#define RLIN2_PORT_M0RX3        PORT_1
#define RLIN2_PORT_BIT_M0RX3    BIT_14 
#define RLIN2_PORT_M0TX3        PORT_1
#define RLIN2_PORT_BIT_M0TX3    BIT_15
#define RLIN2_PORT_FUNC_M0RX3   PORT_FUNCTION_ALTLV0
#define RLIN2_PORT_FUNC_M0TX3   PORT_FUNCTION_ALTLV0

#define RLIN2_PORT_M1RX0        PORT_1
#define RLIN2_PORT_BIT_M1RX0    BIT_10 
#define RLIN2_PORT_M1TX0        PORT_1
#define RLIN2_PORT_BIT_M1TX0    BIT_11
#define RLIN2_PORT_FUNC_M1RX0   PORT_FUNCTION_ALTLV0
#define RLIN2_PORT_FUNC_M1TX0   PORT_FUNCTION_ALTLV0

#define RLIN2_PORT_M1RX1        PORT_8
#define RLIN2_PORT_BIT_M1RX1    BIT_11 
#define RLIN2_PORT_M1TX1        PORT_8
#define RLIN2_PORT_BIT_M1TX1    BIT_12
#define RLIN2_PORT_FUNC_M1RX1   PORT_FUNCTION_ALTLV3
#define RLIN2_PORT_FUNC_M1TX1   PORT_FUNCTION_ALTLV3

#define RLIN2_PORT_M1RX2        PORT_0
#define RLIN2_PORT_BIT_M1RX2    BIT_11 
#define RLIN2_PORT_M1TX2        PORT_0
#define RLIN2_PORT_BIT_M1TX2    BIT_12
#define RLIN2_PORT_FUNC_M1RX2   PORT_FUNCTION_ALTLV3
#define RLIN2_PORT_FUNC_M1TX2   PORT_FUNCTION_ALTLV3

#define RLIN2_PORT_M1RX3        PORT_12
#define RLIN2_PORT_BIT_M1RX3    BIT_3 
#define RLIN2_PORT_M1TX3        PORT_12
#define RLIN2_PORT_BIT_M1TX3    BIT_4
#define RLIN2_PORT_FUNC_M1RX3   PORT_FUNCTION_ALTLV0
#define RLIN2_PORT_FUNC_M1TX3   PORT_FUNCTION_ALTLV0

#define RLIN2_PORT_M2RX0        PORT_2
#define RLIN2_PORT_BIT_M2RX0    BIT_2 
#define RLIN2_PORT_M2TX0        PORT_2
#define RLIN2_PORT_BIT_M2TX0    BIT_3
#define RLIN2_PORT_FUNC_M2RX0   PORT_FUNCTION_ALTLV0
#define RLIN2_PORT_FUNC_M2TX0   PORT_FUNCTION_ALTLV0

#define RLIN2_PORT_M2RX1        PORT_2
#define RLIN2_PORT_BIT_M2RX1    BIT_4
#define RLIN2_PORT_M2TX1        PORT_2
#define RLIN2_PORT_BIT_M2TX1    BIT_5
#define RLIN2_PORT_FUNC_M2RX1   PORT_FUNCTION_ALTLV0
#define RLIN2_PORT_FUNC_M2TX1   PORT_FUNCTION_ALTLV0

/* INTERRUPT REGISTER MAPPING */

#define RLIN2_INT_BUNDLINGHOOK ( RLIN2_IntBundlingDecode )  // external bundling decoder
#ifndef CSPLUS_PRJ_USED
#define RLIN2_INTM0C0TX        INTC2ICRLIN20
#define RLIN2_INTM0C0RX        INTC2ICRLIN20
#define RLIN2_INTM0C0ERR       INTC2ICRLIN20

#define RLIN2_INTM0C1TX        INTC2ICRLIN21
#define RLIN2_INTM0C1RX        INTC2ICRLIN21
#define RLIN2_INTM0C1ERR       INTC2ICRLIN21

#define RLIN2_INTM0C2TX        INTC2ICRLIN22
#define RLIN2_INTM0C2RX        INTC2ICRLIN22
#define RLIN2_INTM0C2ERR       INTC2ICRLIN22

#define RLIN2_INTM0C3TX        INTC2ICRLIN23
#define RLIN2_INTM0C3RX        INTC2ICRLIN23
#define RLIN2_INTM0C3ERR       INTC2ICRLIN23

#define RLIN2_INTM1C0TX        INTC2ICRLIN24
#define RLIN2_INTM1C0RX        INTC2ICRLIN24
#define RLIN2_INTM1C0ERR       INTC2ICRLIN24

#define RLIN2_INTM1C1TX        INTC2ICRLIN25
#define RLIN2_INTM1C1RX        INTC2ICRLIN25
#define RLIN2_INTM1C1ERR       INTC2ICRLIN25

#define RLIN2_INTM1C2TX        INTC2ICRLIN26
#define RLIN2_INTM1C2RX        INTC2ICRLIN26
#define RLIN2_INTM1C2ERR       INTC2ICRLIN26

#define RLIN2_INTM1C3TX        INTC2ICRLIN27
#define RLIN2_INTM1C3RX        INTC2ICRLIN27
#define RLIN2_INTM1C3ERR       INTC2ICRLIN27

#define RLIN2_INTM2C0TX        INTC2ICRLIN28
#define RLIN2_INTM2C0RX        INTC2ICRLIN28
#define RLIN2_INTM2C0ERR       INTC2ICRLIN28

#define RLIN2_INTM2C1TX        INTC2ICRLIN29
#define RLIN2_INTM2C1RX        INTC2ICRLIN29
#define RLIN2_INTM2C1ERR       INTC2ICRLIN29
#else
#define RLIN2_INTM0C0TX        REG_ICRLIN20
#define RLIN2_INTM0C0RX        REG_ICRLIN20
#define RLIN2_INTM0C0ERR       REG_ICRLIN20

#define RLIN2_INTM0C1TX        REG_ICRLIN21
#define RLIN2_INTM0C1RX        REG_ICRLIN21
#define RLIN2_INTM0C1ERR       REG_ICRLIN21

#define RLIN2_INTM0C2TX        REG_ICRLIN22
#define RLIN2_INTM0C2RX        REG_ICRLIN22
#define RLIN2_INTM0C2ERR       REG_ICRLIN22

#define RLIN2_INTM0C3TX        REG_ICRLIN23
#define RLIN2_INTM0C3RX        REG_ICRLIN23
#define RLIN2_INTM0C3ERR       REG_ICRLIN23

#define RLIN2_INTM1C0TX        REG_ICRLIN24
#define RLIN2_INTM1C0RX        REG_ICRLIN24
#define RLIN2_INTM1C0ERR       REG_ICRLIN24

#define RLIN2_INTM1C1TX        REG_ICRLIN25
#define RLIN2_INTM1C1RX        REG_ICRLIN25
#define RLIN2_INTM1C1ERR       REG_ICRLIN25

#define RLIN2_INTM1C2TX        REG_ICRLIN26
#define RLIN2_INTM1C2RX        REG_ICRLIN26
#define RLIN2_INTM1C2ERR       REG_ICRLIN26

#define RLIN2_INTM1C3TX        REG_ICRLIN27
#define RLIN2_INTM1C3RX        REG_ICRLIN27
#define RLIN2_INTM1C3ERR       REG_ICRLIN27

#define RLIN2_INTM2C0TX        REG_ICRLIN28
#define RLIN2_INTM2C0RX        REG_ICRLIN28
#define RLIN2_INTM2C0ERR       REG_ICRLIN28

#define RLIN2_INTM2C1TX        REG_ICRLIN29
#define RLIN2_INTM2C1RX        REG_ICRLIN29
#define RLIN2_INTM2C1ERR       REG_ICRLIN29
#endif

#define RLIN2_INTCLEAR         ( 0x008F )       // Interrupt mask bit
#define RLIN2_INTENABLEDEFAULT ( 0x0040 )
#define RLIN2_INTFLAG          ( 0x1000 )

/* The RLIN2 Memory Mapping */  

static const u08 ee_rlin2_channels[ RLIN2_MACROS ] =
{
    4, 4, 2
};   

static struct rlin2 *rlin2_p[ RLIN2_MACROS ] =
{
    ( rlin2 * )( RLIN2_BASE + RLIN2_OFFSET_UNIT0 ),              /* unit 0 */
    ( rlin2 * )( RLIN2_BASE + RLIN2_OFFSET_UNIT1 ),              /* unit 1 */
    ( rlin2 * )( RLIN2_BASE + RLIN2_OFFSET_UNIT2 )               /* unit 2 */
};   


#endif
