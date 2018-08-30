//============================================================================
// PROJECT = RLIN3 Type RLIN3_UCIAPRLN
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2014 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RLIN3 LIN Operation Setup
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
// Environment: Devices:          All featuring RLIN3_UCIAPRLN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================
//
// Test Registers not included
//
//============================================================================

#ifndef _RLIN3_S_H
#define _RLIN3_S_H
                   
#include <ree_types.h>

#include "rlin3.h"

#define RLIN3_A_LIN_MASTERTABLES   ( 4 )
#define RLIN3_A_LIN_MAXTABLELENGTH ( 20 )

#define RLIN3_A_LIN_MAXDATA        ( RLIN3_LINDATALEN_MAX )
#define RLIN3_A_LIN_BREAKLENGTH    ( RLIN3_SBF15BITS )
#define RLIN3_A_LIN_INITIALNAD     ( 0x7F )
#define RLIN3_A_LIN_CLASSCHKSUMLIM ( 0x3C )
#define RLIN3_A_LIN_ENHANCEDCHKSUM ( RLIN3_CHECKSUM_ENHANCED )

#define RLIN3_A_MODE_LINSLAVE      ( RLIN3_MODE_LINSLAVE_AUTO )

#define RLIN3_A_LIN_STATE_IDLE     ( 0x00 )
#define RLIN3_A_LIN_STATE_BUSY     ( 0x01 )
#define RLIN3_A_LIN_STATE_SLEEP    ( 0x02 )
#define RLIN3_A_LIN_STATE_ERROR    ( 0x04 )

#define RLIN3_A_LIN_STATE_NEWSDATA ( 0x08 )

#define RLIN3_A_LIN_STATE_APIMASK  ( 0xFF )

#define RLIN3_A_LIN_STATE_TXBREAK  ( 0x11 )
#define RLIN3_A_LIN_STATE_RXDATA   ( 0x51 )
#define RLIN3_A_LIN_STATE_TXDATA   ( 0x41 )
#define RLIN3_A_LIN_STATE_BRKDEL   ( 0x81 )
#define RLIN3_A_LIN_STATE_RXSLEEP  ( 0x91 )

#define RLIN3_A_LIN_STATE_FSMERROR ( 0x14 )
#define RLIN3_A_LIN_STATE_UNEXRECV ( 0x24 )
#define RLIN3_A_LIN_STATE_DLLERROR ( 0x34 )
#define RLIN3_A_LIN_STATE_DCCERROR ( 0x44 )
#define RLIN3_A_LIN_STATE_PIDERROR ( 0x54 )
#define RLIN3_A_LIN_STATE_RPRERROR ( 0x74 )
#define RLIN3_A_LIN_STATE_CHSERROR ( 0x84 )

#define RLIN3_A_LIN_STATE_WAKEUP   ( 0x12 )

#define RLIN3_A_RX     ( RLIN3_RESPONSE_RECEIVE )
#define RLIN3_A_TX     ( RLIN3_RESPONSE_TRANSMIT )
#define RLIN3_A_AA     ( 0x10 )
#define RLIN3_A_NO     ( 0xFF )

#define RLIN3_A_NADPOS ( 7 )
#define RLIN3_A_SIDPOS ( 2 )
#define RLIN3_A_SIDAA  ( 0xB5 )

typedef struct rlin3_a_lintable_entry
{
  u08 Type_u08;
  u08 PID_u08;
  u08 DataLength_u08;
  u08 Data[ RLIN3_A_LIN_MAXDATA ];
  
} rlin3_a_lintable_entry;

/* All tables are the base tables.
   Their content is the default configuration / response. */

/* Master Table Set */

/* RLIN3_A_TX: Master Sending Configuration
   RLIN3_A_RX: Master Receiving Responses
   RLIN3_A_NO: Sleep Sequence, only valid as last entry in table */

static struct rlin3_a_lintable_entry RLIN3_A_TAB_MASTER_BASE
                                      [ RLIN3_A_LIN_MASTERTABLES ]
                                      [ RLIN3_A_LIN_MAXTABLELENGTH ] =
{
  {   /* TYP   PID   LEN     DATA     [0xFF: Content is not relevant]     */
      /* last entry in each table must be the sleep command (RLIN3_A_NO)  */

 { RLIN3_A_TX, 0x00, 0x01, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x01, 0x02, { 0x10, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x02, 0x03, { 0x20, 0x21, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x10, 0x04, { 0x30, 0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x11, 0x05, { 0x40, 0x41, 0x42, 0x43, 0x44, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x12, 0x06, { 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x13, 0x07, { 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x00 } },
 { RLIN3_A_TX, 0x14, 0x08, { 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77 } },
 { RLIN3_A_RX, 0x21, 0x01, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x22, 0x02, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x30, 0x03, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x31, 0x04, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x32, 0x05, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x33, 0x06, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x34, 0x07, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x35, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
      /* Table 1: Master Testing table TX response only */
  {
 { RLIN3_A_TX, 0x18, 0x08, { 0x1F, 0x2E, 0x3D, 0x4C, 0x5B, 0x6A, 0x79, 0x88 } },
 { RLIN3_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
      /* Table 2: Master Testing table TX response only */
  {
 { RLIN3_A_TX, 0x19, 0x08, { 0xF1, 0xE2, 0xD3, 0xC4, 0xB5, 0xA6, 0x97, 0x88 } },
 { RLIN3_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
      /* Table 3: Master Testing table RX response only */
  {
 { RLIN3_A_RX, 0x28, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  }
};

/* Slave Table */

/* RLIN3_A_TX: Slave Sending Response
   RLIN3_A_RX: Slave Receiving Configuration
   RLIN3_A_AS: Slave Autoaddressing Start Code
   RLIN3_A_AM: Slave Autoaddressing Measurement Cycle
   RLIN3_A_AE: Slave Autoaddressing End Code
   RLIN3_A_NO: Sleep Sequence, only valid as last entry in table */

static struct rlin3_a_lintable_entry RLIN3_A_TAB_SLAVE_BASE
                                      [ RLIN3_A_LIN_MAXTABLELENGTH ] =
{
      /* TYP   PID   LEN     DATA     [0xFF: Content is not relevant]     */
      /* last entry in each table must be the sleep command (RLIN3_A_NO)  */
    
 { RLIN3_A_RX, 0x00, 0x01, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x01, 0x02, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x02, 0x03, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x10, 0x04, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x11, 0x05, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x12, 0x06, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x13, 0x07, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x14, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x18, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_RX, 0x19, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x21, 0x01, { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x22, 0x02, { 0xEF, 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x30, 0x03, { 0xDF, 0xDE, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x31, 0x04, { 0xCF, 0xCE, 0xCD, 0xCC, 0x00, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x32, 0x05, { 0xBF, 0xBE, 0xBD, 0xBC, 0xBA, 0x00, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x33, 0x06, { 0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0x00, 0x00 } },
 { RLIN3_A_TX, 0x34, 0x07, { 0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x00 } },
 { RLIN3_A_TX, 0x35, 0x08, { 0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88 } },
 { RLIN3_A_TX, 0x28, 0x08, { 0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8 } },
 { RLIN3_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } } 
};

#endif
