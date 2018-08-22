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

//#define Application_2
#define Application_1
#define __TEST_FLX_COM@titron

/* PORT DEFINITIONS */

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

#define EE_FR_PORT_FUNC_TXA   PORT_FUNCTION_ALTLV0
#define EE_FR_PORT_FUNC_TXENA PORT_FUNCTION_ALTLV1
#define EE_FR_PORT_FUNC_RXA   PORT_FUNCTION_ALTLV1

#define EE_FR_PORT_FUNC_TXB   PORT_FUNCTION_ALTLV1
#define EE_FR_PORT_FUNC_TXENB PORT_FUNCTION_ALTLV1
#define EE_FR_PORT_FUNC_RXB   PORT_FUNCTION_ALTLV5

#ifdef CETITEC_MCU

#define EE_FR_PORT_ENA        PORT_12
#define EE_FR_PORT_WAKEA      PORT_11
#define EE_FR_PORT_BGEA       PORT_1
#define EE_FR_PORT_STBNA      PORT_12

#define EE_FR_PORT_BIT_ENA    BIT_2
#define EE_FR_PORT_BIT_WAKEA  BIT_0
#define EE_FR_PORT_BIT_BGEA   BIT_10
#define EE_FR_PORT_BIT_STBNA  BIT_1

/* Not yet enabled due to hardware shortcuts 

#define EE_FR_PORT_ENB        
#define EE_FR_PORT_WAKEB      
#define EE_FR_PORT_BGEB       
#define EE_FR_PORT_STBNB      

#define EE_FR_PORT_BIT_ENA    
#define EE_FR_PORT_BIT_WAKEA  
#define EE_FR_PORT_BIT_BGEA   
#define EE_FR_PORT_BIT_STBNA  

*/

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
