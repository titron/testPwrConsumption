//============================================================================
// PROJECT = RLIN2 Type RLIN2_UCIAPRLN
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2014 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RLIN2 LIN Operation Setup
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
// Environment: Devices:          All featuring RLIN2_UCIAPRLN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================
//
// Test Registers not included
//
//============================================================================

#ifndef _RLIN2_S_H
#define _RLIN2_S_H
                   
#include <ree_types.h>

#include "rlin2.h"

#define RLIN2_A_LIN_MASTERTABLES   ( 10 )
#define RLIN2_A_LIN_MAXTABLELENGTH ( 3 )

#define RLIN2_A_LIN_MAXDATA        ( RLIN2_LINDATALEN_MAX )
#define RLIN2_A_LIN_BREAKLENGTH    ( RLIN2_SBF15BITS )
#define RLIN2_A_LIN_INITIALNAD     ( 0x7F )
#define RLIN2_A_LIN_CLASSCHKSUMLIM ( 0x3C )
#define RLIN2_A_LIN_ENHANCEDCHKSUM ( RLIN2_CHECKSUM_ENHANCED )

#define RLIN2_A_MODE_LINSLAVE      ( RLIN2_MODE_LINSLAVE_AUTO )

#define RLIN2_A_LIN_STATE_IDLE     ( 0x00 )
#define RLIN2_A_LIN_STATE_BUSY     ( 0x01 )
#define RLIN2_A_LIN_STATE_SLEEP    ( 0x02 )
#define RLIN2_A_LIN_STATE_ERROR    ( 0x04 )

#define RLIN2_A_LIN_STATE_NEWSDATA ( 0x08 )

#define RLIN2_A_LIN_STATE_APIMASK  ( 0xFF )

#define RLIN2_A_LIN_STATE_TXBREAK  ( 0x11 )
#define RLIN2_A_LIN_STATE_RXDATA   ( 0x51 )
#define RLIN2_A_LIN_STATE_TXDATA   ( 0x41 )
#define RLIN2_A_LIN_STATE_BRKDEL   ( 0x81 )
#define RLIN2_A_LIN_STATE_RXSLEEP  ( 0x91 )

#define RLIN2_A_LIN_STATE_FSMERROR ( 0x14 )
#define RLIN2_A_LIN_STATE_UNEXRECV ( 0x24 )
#define RLIN2_A_LIN_STATE_DLLERROR ( 0x34 )
#define RLIN2_A_LIN_STATE_DCCERROR ( 0x44 )
#define RLIN2_A_LIN_STATE_PIDERROR ( 0x54 )
#define RLIN2_A_LIN_STATE_RPRERROR ( 0x74 )
#define RLIN2_A_LIN_STATE_CHSERROR ( 0x84 )

#define RLIN2_A_LIN_STATE_WAKEUP   ( 0x12 )

#define RLIN2_A_RX     ( RLIN2_RESPONSE_RECEIVE )
#define RLIN2_A_TX     ( RLIN2_RESPONSE_TRANSMIT )
#define RLIN2_A_AA     ( 0x10 )
#define RLIN2_A_NO     ( 0xFF )

#define RLIN2_A_NADPOS ( 7 )
#define RLIN2_A_SIDPOS ( 2 )
#define RLIN2_A_SIDAA  ( 0xB5 )

typedef struct rlin2_a_lintable_entry
{
  u08 Type_u08;
  u08 PID_u08;
  u08 DataLength_u08;
  u08 Data[ RLIN2_A_LIN_MAXDATA ];
  
} rlin2_a_lintable_entry;

/* All tables are the base tables.
   Their content is the default configuration / response. */

/* Master Table Set */

/* RLIN2_A_TX: Master Sending Configuration
   RLIN2_A_RX: Master Receiving Responses
   RLIN2_A_NO: Sleep Sequence, only valid as last entry in table */

static struct rlin2_a_lintable_entry RLIN2_A_TAB_MASTER_BASE
                                      [ RLIN2_A_LIN_MASTERTABLES ]
                                      [ RLIN2_A_LIN_MAXTABLELENGTH ] =
{
  {      /* TYP   PID   LEN     DATA     [0xFF: Content is not relevant]     */
         /* last entry in each table must be the sleep command (RLIN2_A_NO)  */

   { RLIN2_A_TX, 0x10, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x20, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x11, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x21, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x12, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x22, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x13, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x23, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x14, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x24, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x15, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x25, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x16, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x26, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x17, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x27, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x18, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x28, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  },
  {
   { RLIN2_A_TX, 0x19, 0x08, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 } },
   { RLIN2_A_RX, 0x29, 0x08, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
   { RLIN2_A_NO, 0x3C, 0x08, { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } }
  }
};

#endif
