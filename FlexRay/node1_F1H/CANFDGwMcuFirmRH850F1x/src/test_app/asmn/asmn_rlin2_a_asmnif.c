//============================================================================
// PROJECT = ASMN Test Monitor
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2015 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
// Purpose: RLIN2 Application Access Interface
//
//Warranty Disclaimer
//
//Because the Product(s) is licensed free of charge, there is no warranty 
//of any kind whatsoever and expressly disclaimed and excluded by Renesas, 
//either expressed or implied, including but not limited to those for 
//non-infringement of intellectual property, merchantability and/or 
//fitness for the particular purpose. 
//Renesas shall not have any obligation to maintain, service or provide bug 
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
//In no event shall Renesas be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. Renesas shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by Renesas in conRenesastion with the Product(s) and/or the 
//Application.
//
//============================================================================
// Environment: Devices:          All featuring ASMN Monitor (min. 128k ROM)
//============================================================================

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ree_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef RLIN2_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#elif( ASMN_UARTINTERFACE == UARTD_STANDARD )
#include <map_uartd.h>

#elif( ASMN_UARTINTERFACE == UARTE_STANDARD )
#include <map_uarte.h>

#elif( ASMN_UARTINTERFACE == UARTF_STANDARD )
#include <map_uartf.h>

#elif( ASMN_UARTINTERFACE == RLIN3_STANDARD )
#include <map_rlin3.h>

#elif( ASMN_UARTINTERFACE == DEBUG_INTERNAL )
extern bit ASMN_SendString( u08   UnitNumber_u08,
                            char *SendString,
                            u08   TTYMode_u08 );
extern bit ASMN_SendByte( u08 UnitNumber_u08,
                          u08 SendByte_u08 );
extern bit ASMN_ReceiveByte( u08  UnitNumber_u08,
                             pu08 ReceiveByte_pu08 );
extern bit ASMN_ReceiveInteger( u08    UnitNumber_u08,
                                u16    ReceiveLength_u16,
                                char  *RequestString,
                                int   *Result,
                                pu08   ScanState_pu08 );
extern bit ASMN_ReceiveULong( u08            UnitNumber_u08,
                              u16            ReceiveLength_u16,
                              char          *RequestString,
                              unsigned long *Result,
                              pu08           ScanState_pu08 );
extern bit ASMN_ReceiveFloat( u08    UnitNumber_u08,
                              u16    ReceiveLength_u16,
                              char  *RequestString,
                              float *Result,
                              pu08   ScanState_pu08 );

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* RLIN2 Driver Interface */
//#include <rlin2\rlin2_uciaprln\rlin2.h>
//#include <rlin2\rlin2_uciaprln\rlin2_a.h>
//#include <rlin2\rlin2_uciaprln\rlin2_s.h>
#include <rlin2.h>
#include <rlin2_a.h>
#include <rlin2_s.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "RLIN2 APPLICATION MENU\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 04/2015    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( ( RLIN2_TYPE == RLIN2_UCIAPRLN ) ||\
     ( RLIN2_TYPE == RLIN2_STANDARD ) )
#define ASMN_MENULINE_MEN1  "1 -> Set LIN Master Table\n"
#define ASMN_MENULINE_MEN2  "2 -> Send LIN Master Table Entries\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT        "\n Enter Unit: "
#define ASMN_MENUINPUT_CHANNEL     "\n Enter Channel: "
#define ASMN_MENUINPUT_BAUDRATE    "\n Enter Baudrate: "
#define ASMN_MENUINPUT_TABLE       "\n Enter Table: "
#define ASMN_MENUINPUT_MASTERDELAY "\n Enter Master Delay: "

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1
#define ASMN_MENUINPUT_TIMEOUT    MAX_CPU_FREQUENCY

#define ASMN_MENUCODE_SCANOK    1
#define ASMN_MENUCODE_NOCMD    -1
#define ASMN_MENUCODE_EXIT      0
#define ASMN_MENUCODE_BACK      0
#define ASMN_MENUCODE_LINMSTART 1
#define ASMN_MENUCODE_LINMNEXT  2

/*
 * external functions
 */

extern bit ASMN_UARTSENDSTRING( u08, char*, u08 );
extern bit ASMN_UARTSENDBYTE( u08, u08 );
extern bit ASMN_UARTRECEIVEBYTE( u08, pu08 );
extern bit ASMN_UARTRECEIVEINT( u08, u16, char*, int*, pu08 );
extern bit ASMN_UARTRECEIVELONG( u08, u16, char*, unsigned long*, pu08 );
extern bit ASMN_UARTRECEIVEFLOAT( u08, u16, char*, float*, pu08 );

/*
 * functions
 */

static bit                /* local submenu: invisible from outside */
DisplayMainMenu( u08   MenuCom,
                 char *MenuCommand )
{
  bit           UARTStatus;
  u08           UserInput    = 0;
  unsigned int  DigitCounter = 0;
  int           DigitValue;
  char          InputString[ ASMN_MENUCOM_BUFLEN ];

  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_HDR1, 
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_HDR2,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN0,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#ifdef ASMN_MENULINE_MEN1
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN1,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN2
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN2,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_CMD1,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );

  while( DigitCounter < ( ASMN_MENUCOM_BUFLEN-1 ) ) {

    do {  /* wait for one char to be received */
      
      UARTStatus = ASMN_UARTRECEIVEBYTE( MenuCom, &UserInput );
      
    } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
    UARTStatus = ASMN_UARTSENDBYTE( MenuCom, UserInput ); /* echo */
    
    if( ( UserInput == ASMN_MENUCOM_EXE1 ) || 
        ( UserInput == ASMN_MENUCOM_EXE2 ) ) { /* the "return" */
      
      InputString[ DigitCounter ] = 0;       /* close string */
      sscanf( InputString, "%d", &DigitValue );
      *MenuCommand = ( unsigned char )DigitValue;
      return( UARTStatus );
    }
    else {  /* store digit */
      
      if( UserInput >= ' ' ) {
        InputString[ DigitCounter++ ] = ( char )UserInput;
      }
      else if( UserInput == 0x08 ) {
        if( DigitCounter > 0 ) DigitCounter--;
      }
    }
  }

  *MenuCommand = -1;
  return( UARTStatus );
}

#ifdef ASMN_MENULINE_MEN1

bit
ApplRLIN2LINMasterTableStart( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN2_OK;
  int           UnitNumber     = 0;
  int           ChannelNumber  = 0;  
  int           Table          = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_UNIT,
				             &UnitNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_CHANNEL,
				             &ChannelNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_TABLE,
				             &Table,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == RLIN2_OK )
  {
    SuccessFlag =  RLIN2_LINM_SetTable( ( u08 )UnitNumber,
                                        ( u08 )ChannelNumber,
                                        ( u08 )Table );
    SuccessFlag &= RLIN2_LINM_RestartTable( ( u08 )UnitNumber,
                                            ( u08 )ChannelNumber );
  }
  
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == RLIN2_OK ) {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_OK,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  return( UARTStatus );
}

#endif

#ifdef ASMN_MENULINE_MEN2

bit
ApplRLIN2LINMasterTableNext( u08 MenuCom )
{
  u08           UserInput;
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN2_OK;
  u08           ErrorStatus;
  int           UnitNumber     = 0;
  int           ChannelNumber  = 0;  
  unsigned long Baudrate       = 9600L;
  unsigned long Masterdelay    = 0L;
  unsigned long MasterdelayCount;
  
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_UNIT,
				             &UnitNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_CHANNEL,
				             &ChannelNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
				              ASMN_MENUINPUT_BAUDRATE,
				              &Baudrate,
				              &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
				              ASMN_MENUINPUT_MASTERDELAY,
				              &Masterdelay,
				              &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  SuccessFlag = RLIN2_LIN_SetMode( ( u08 )UnitNumber,
                                   ( u08 )ChannelNumber,
                                   ( u32 )Baudrate,
                                   OSCILLATOR_FREQUENCY );

  do
  {
    SuccessFlag &=  RLIN2_LINM_SendWakeup( ( u08 )UnitNumber, 
                                           ( u08 )ChannelNumber );
    
  } while( ( RLIN2_LINM_GetStatus( ( u08 )UnitNumber, 
                                   ( u08 )ChannelNumber ) != RLIN2_A_LIN_STATE_IDLE ) &&
           ( RLIN2_LINM_GetStatus( ( u08 )UnitNumber, 
                                   ( u08 )ChannelNumber ) != RLIN2_A_LIN_STATE_WAKEUP ) );

  do {  /* repeat until one char to be received */

    SuccessFlag &= RLIN2_LINM_NextTableContent( ( u08 )UnitNumber, 
                                                ( u08 )ChannelNumber );
    do
    {
      ErrorStatus = RLIN2_LINM_GetStatus( ( u08 )UnitNumber, 
                                          ( u08 )ChannelNumber );
      
    } while( ErrorStatus != RLIN2_A_LIN_STATE_IDLE );
    
    for( MasterdelayCount = Masterdelay; 
         MasterdelayCount > 0L; 
         MasterdelayCount-- )
    {
      __nop();
    }

    UARTStatus = ASMN_UARTRECEIVEBYTE( ASMN_MENUCOM, &UserInput );    
    
  } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
  if( SuccessFlag == RLIN2_OK ) {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_OK,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  return( UARTStatus );
}

#endif

unsigned char ASMN_RLIN2Applications( unsigned int MenuCom )
{
  bit           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
    	 ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMainMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {

    case ASMN_MENUCODE_EXIT: 
      break;
#ifdef ASMN_MENULINE_MEN1
    case ASMN_MENUCODE_LINMSTART:
      UARTStatus = ApplRLIN2LINMasterTableStart( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN2
    case ASMN_MENUCODE_LINMNEXT:
      UARTStatus = ApplRLIN2LINMasterTableNext( MenuCom );
      break;
#endif

    default:
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_NOCMD,
                                        ASMN_UARTMODECRLF );
      break;
    }
  }
  return( UARTStatus );
}

#endif
