//============================================================================
// PROJECT = ASMN Test Monitor
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
// Purpose: RLIN3 Application Access Interface
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

#ifdef RLIN3_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == RLIN3_STANDARD )

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
extern bit ASMN_ReceiveString( u08   UnitNumber_u08,
                               char *ReceiveString,
                               u16   ReceiveLength_u16,
                               u32   TimeOutCount_u32 );
                              

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* RLIN3 Driver Interface */
#include <map_rlin3.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "RLIN3 APPLICATION MENU\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 07/2014    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( ( RLIN3_TYPE == RLIN3_UCIAPRLN ) ||\
     ( RLIN3_TYPE == RLIN3_STANDARD ) )
#define ASMN_MENULINE_MEN1  "1 -> Send String\n"
#define ASMN_MENULINE_MEN2  "2 -> Set LIN Master Mode\n"
#define ASMN_MENULINE_MEN3  "3 -> Set LIN Master Table\n"
#define ASMN_MENULINE_MEN4  "4 -> Send Next LIN Master Table Entry\n"
#define ASMN_MENULINE_MEN5  "5 -> Set LIN Slave Mode\n"
#define ASMN_MENULINE_MEN6  "6 -> Monitor LIN Slave Activity\n"
#define ASMN_MENULINE_MEN7  "7 -> LIN Master/Slave Test\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT       "\n Enter Unit: "
#define ASMN_MENUINPUT_SLAVEUNIT  "\n Enter Slave Unit: "
#define ASMN_MENUINPUT_MSTRUNIT   "\n Enter Master Unit: "
#define ASMN_MENUINPUT_LENGTH     "\n Enter Length [0=Send 1 Char Forever, given is MAX]: "
#define ASMN_MENUINPUT_STRING     "\n Enter String: "
#define ASMN_MENUINPUT_BAUDRATE   "\n Enter Baudrate: "
#define ASMN_MENUINPUT_TABLE      "\n Enter Table: "
#define ASMN_MENUINPUT_SLAVEMODE  "\n Enter Slave Mode [0=AUTO; 1=FIX Baudrate]: "
#define ASMN_MENUINPUT_ENDLESS    "\n Enter Loop Condition [0=EXIT CHECK; 1=ENDLESS: "

#define ASMN_MENUOUTPUT_AAWAITING "WAITING ON TRIGGER\n"
#define ASMN_MENUOUTPUT_AAMEASURE "MEASUREMENT START TRIGGER RECEIVED\n"
#define ASMN_MENUOUTPUT_AANADRCV  "AUTO ADDRESSING NAD RECEIVED: %02x\n"
#define ASMN_MENUOUTPUT_AACOMPL   "AUTO ADDRESSING COMPLETED\n"

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1
#define ASMN_MENUINPUT_TIMEOUT    MAX_CPU_FREQUENCY

#define ASMN_MENUCODE_SCANOK    1
#define ASMN_MENUCODE_NOCMD    -1
#define ASMN_MENUCODE_EXIT      0
#define ASMN_MENUCODE_BACK      0
#define ASMN_MENUCODE_SEND      1
#define ASMN_MENUCODE_LINMMODE  2
#define ASMN_MENUCODE_LINMSTART 3
#define ASMN_MENUCODE_LINMNEXT  4
#define ASMN_MENUCODE_LINSMODE  5
#define ASMN_MENUCODE_LINSMON   6
#define ASMN_MENUCODE_LINMST    7

/*
 * external functions
 */

extern bit ASMN_UARTSENDSTRING( u08, char*, u08 );
extern bit ASMN_UARTSENDBYTE( u08, u08 );
extern bit ASMN_UARTRECEIVEBYTE( u08, pu08 );
extern bit ASMN_UARTRECEIVEINT( u08, u16, char*, int*, pu08 );
extern bit ASMN_UARTRECEIVELONG( u08, u16, char*, unsigned long*, pu08 );
extern bit ASMN_UARTRECEIVEFLOAT( u08, u16, char*, float*, pu08 );

/* UART Replacement Functions for Monitor */

#define ASMN_A_TTYMODE_CR   0 /* application level constants */
#define ASMN_A_TTYMODE_CRLF 1
#define ASMN_A_HEXMODE      1
#define ASMN_A_DECMODE      0
#define ASMN_A_RECBUFLEN    80

/*
 * functions
 */

void LinIf_RxHeaderIndication( Lin_FramePidType PID )
{
}

void LinIf_RxFrameIndication( Lin_FramePidType PID, uint8* DataArray )
{
}

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
#ifdef ASMN_MENULINE_MEN3
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN3,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN4
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN4,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN5
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN5,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN6
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN6,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN7
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN7,
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
ApplRLIN3SendString( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN3_OK;
  int           UnitNumber     = -1;
  int           StringLength   = ASMN_MENUINPUT_BUFLEN;
  char          SendString[ ASMN_MENUINPUT_BUFLEN + 1 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_LENGTH,
				                    &StringLength,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENUINPUT_STRING,
                                    ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVESTRG( MenuCom, 
                                     &SendString[ 0 ],
                                     ( u16 )StringLength,
                                     ASMN_MENUINPUT_TIMEOUT );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == RLIN3_OK )
  {
    SuccessFlag  = RLIN3_Reset( ( u08 )UnitNumber );
    SuccessFlag &= RLIN3_PortEnable( ( u08 )UnitNumber );
    SuccessFlag &= RLIN3_LegacyConfig( ( u08 )UnitNumber,
                                       OSCILLATOR_FREQUENCY,
                                       ASMN_MENUCOM_BAUD,
                                       ASMN_MENUCOM_PARITY,
                                       ASMN_MENUCOM_CHLEN,
                                       ASMN_MENUCOM_STOP,
                                       ASMN_MENUCOM_DIR );

    SuccessFlag &= RLIN3_SendString( ( u08 )UnitNumber, 
                                     SendString, 
                                     ASMN_UARTMODECR );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == RLIN3_OK ) {
    
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
ApplRLIN3LINSetMasterMode( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN3_OK;
  int           UnitNumber     = 0;
  unsigned long Baudrate       = 9600L;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_UNIT,
				             &UnitNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
				              ASMN_MENUINPUT_BAUDRATE,
				              &Baudrate,
				              &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == RLIN3_OK )

    SuccessFlag = RLIN3_LIN_SetMode( ( u08 )UnitNumber, 
                                     RLIN3_MODE_LINMASTER, 
                                     ( u32 )Baudrate,
                                     OSCILLATOR_FREQUENCY );
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == RLIN3_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN3

bit
ApplRLIN3LINMasterTableStart( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN3_OK;
  int           UnitNumber     = 0;
  int           Table          = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_UNIT,
				             &UnitNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_TABLE,
				             &Table,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == RLIN3_OK )
  {
    SuccessFlag =  RLIN3_LINM_SetTable( ( u08 )UnitNumber,
                                        ( u08 )Table );
    SuccessFlag &= RLIN3_LINM_RestartTable( ( u08 )UnitNumber );
  }
  
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == RLIN3_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN4

bit
ApplRLIN3LINMasterTableNext( u08 MenuCom )
{
  u08           UserInput;
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN3_OK;
  u08           ErrorStatus;
  int           UnitNumber     = 0;
  int           EndlessMode    = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_UNIT,
				             &UnitNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_ENDLESS,
				             &EndlessMode,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  do
  {
    SuccessFlag =  RLIN3_LINM_SendWakeup( ( u08 )UnitNumber );
    
  } while( ( RLIN3_LINM_GetStatus( ( u08 )UnitNumber ) != RLIN3_A_LIN_STATE_IDLE ) &&
           ( RLIN3_LINM_GetStatus( ( u08 )UnitNumber ) != RLIN3_A_LIN_STATE_WAKEUP ) );

  UARTStatus = ASMN_UARTERROR;

  do {  /* repeat until one char to be received */
    
    SuccessFlag &= RLIN3_LINM_NextTableContent( ( u08 )UnitNumber );
    do
    {
      ErrorStatus = RLIN3_LINM_GetStatus( ( u08 )UnitNumber );
      
    } while( ErrorStatus != RLIN3_A_LIN_STATE_IDLE );

    if( !EndlessMode )
    {
      UARTStatus = ASMN_UARTRECEIVEBYTE( ASMN_MENUCOM, &UserInput );    
    }
    
  } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
  if( SuccessFlag == RLIN3_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN5

bit
ApplRLIN3LINSetSlaveMode( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN3_OK;
  int           UnitNumber     = 0;
  int           SlaveMode      = -1;
  unsigned long Baudrate       = 9600;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_UNIT,
				             &UnitNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_SLAVEMODE,
				             &SlaveMode,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
				              ASMN_MENUINPUT_BAUDRATE,
				              &Baudrate,
				              &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == RLIN3_OK )
  {
    switch( SlaveMode )
    {
      case 0:
        SuccessFlag = RLIN3_LIN_SetMode( ( u08 )UnitNumber, 
                                         RLIN3_MODE_LINSLAVE_AUTO, 
                                         ( u32 )Baudrate,
                                         OSCILLATOR_FREQUENCY );
        break;
        
      case 1:
        SuccessFlag = RLIN3_LIN_SetMode( ( u08 )UnitNumber, 
                                         RLIN3_MODE_LINSLAVE_FIX, 
                                         ( u32 )Baudrate,
                                         OSCILLATOR_FREQUENCY );
        break;
        
      default:
        SuccessFlag = RLIN3_ERROR;
        break;
    }
    RLIN3_LINS_ActivateResponses( ( u08 )UnitNumber, true );
  }  
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == RLIN3_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN6

bit
ApplRLIN3LINSlaveMonitor( u08 MenuCom )
{
  u08           UserInput;
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN3_OK;
  u08           ErrorStatus;
  u08           LastErrorStatus;
  int           UnitNumber     = 0;
  u08           LINData[ 8 ];
  u08           TableIndex;
  u08           DataIndex;
  u08           DataLength;
  u08           FrameType;
  char          PrintString[ 80 ];
  char          DataString[ 4 ];
  
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_UNIT,
				             &UnitNumber,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;
    
  LastErrorStatus = RLIN3_A_LIN_STATE_IDLE;

  do {  /* repeat until one char to be received */

    ErrorStatus = RLIN3_LINS_GetStatus( ( u08 )UnitNumber, &TableIndex );
    
    PrintString[ 0 ] = 0;

    if( ErrorStatus == RLIN3_A_LIN_STATE_NEWSDATA )
    {
      SuccessFlag = RLIN3_LINS_GetTableContent( TableIndex, &FrameType, 
                                                &DataLength, LINData );
      if( FrameType == RLIN3_A_NO ) break;
      if( FrameType == RLIN3_A_RX )
      {
        for( DataIndex = 0;
             DataIndex < DataLength;
             DataIndex++ )
        {
          sprintf( DataString, "%02X ", LINData[ DataIndex ] );
          strcat( PrintString, DataString );
        }
        strcat( PrintString, "\n" );
        UARTStatus = ASMN_UARTSENDSTRING( MenuCom, PrintString,
                                          ASMN_UARTMODECRLF );
      }
      LastErrorStatus = ErrorStatus;
    }
    
    if( ErrorStatus & RLIN3_A_LIN_STATE_ERROR )
    {
      strcat( PrintString, "E\n" );
      LastErrorStatus = ErrorStatus;
    }

    if( ( ErrorStatus == RLIN3_A_LIN_STATE_SLEEP ) &&
        ( LastErrorStatus != ErrorStatus ) )
    {
      strcat( PrintString, "S\n" );
      LastErrorStatus = ErrorStatus;
    }
    
    if( ErrorStatus == RLIN3_A_LIN_STATE_WAKEUP )
    {
      strcat( PrintString, "W\n" );
      LastErrorStatus = ErrorStatus;
    }

    UARTStatus = ASMN_UARTRECEIVEBYTE( ASMN_MENUCOM, &UserInput );    
        
  } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
  if( SuccessFlag == RLIN3_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN7

bit
ApplRLIN3LINMasterSlaveTest( u08 MenuCom )
{
  u08           UserInput;
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = RLIN3_OK;
  u08           ErrorStatus;
  u08           LastErrorStatus;
  u08           TableIndex;
  u08           DataIndex;
  u08           DataLength;
  u08           FrameType;
  u08           LINData[ 8 ];
  char          PrintString[ 80 ];
  char          DataString[ 4 ];
  int           UnitNumberM    = 0;
  int           UnitNumberS    = 0;
  int           SlaveMode      = -1;
  int           EndlessMode    = 0;
  int           Table          = 0;
  unsigned long Baudrate       = 9600L;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_MSTRUNIT,
				             &UnitNumberM,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_TABLE,
				             &Table,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_SLAVEUNIT,
				             &UnitNumberS,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_SLAVEMODE,
				             &SlaveMode,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
				              ASMN_MENUINPUT_BAUDRATE,
				              &Baudrate,
				              &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_ENDLESS,
				             &EndlessMode,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == RLIN3_OK )
  {
    SuccessFlag = RLIN3_LIN_SetMode( ( u08 )UnitNumberM, 
                                     RLIN3_MODE_LINMASTER, 
                                     ( u32 )Baudrate,
                                     OSCILLATOR_FREQUENCY );
    switch( SlaveMode )
    {
      case 0:
        SuccessFlag &= RLIN3_LIN_SetMode( ( u08 )UnitNumberS, 
                                          RLIN3_MODE_LINSLAVE_AUTO, 
                                          ( u32 )Baudrate,
                                          OSCILLATOR_FREQUENCY );
        break;
        
      case 1:
        SuccessFlag &= RLIN3_LIN_SetMode( ( u08 )UnitNumberS, 
                                          RLIN3_MODE_LINSLAVE_FIX, 
                                          ( u32 )Baudrate,
                                          OSCILLATOR_FREQUENCY );
        break;
        
      default:
        SuccessFlag = RLIN3_ERROR;
        break;
    }
    RLIN3_LINS_ActivateResponses( ( u08 )UnitNumberS, true );

    SuccessFlag &= RLIN3_LINM_SetTable( ( u08 )UnitNumberM,
                                        ( u08 )Table );
    SuccessFlag &= RLIN3_LINM_RestartTable( ( u08 )UnitNumberM );

    do
    {
      SuccessFlag =  RLIN3_LINM_SendWakeup( ( u08 )UnitNumberM );
      
    } while( ( RLIN3_LINM_GetStatus( ( u08 )UnitNumberM ) != RLIN3_A_LIN_STATE_IDLE ) &&
             ( RLIN3_LINM_GetStatus( ( u08 )UnitNumberM ) != RLIN3_A_LIN_STATE_WAKEUP ) );

    UARTStatus = ASMN_UARTERROR;

    do {  /* repeat until one char to be received */
      
      do
      {
        ErrorStatus = RLIN3_LINS_GetStatus( ( u08 )UnitNumberS, &TableIndex );
        
        PrintString[ 0 ] = 0;
    
        if( ErrorStatus == RLIN3_A_LIN_STATE_NEWSDATA )
        {
          SuccessFlag = RLIN3_LINS_GetTableContent( TableIndex, &FrameType, 
                                                    &DataLength, LINData );
          if( FrameType == RLIN3_A_NO ) break;
          if( FrameType == RLIN3_A_RX )
          {
            for( DataIndex = 0;
                 DataIndex < DataLength;
                 DataIndex++ )
            {
              sprintf( DataString, "%02X ", LINData[ DataIndex ] );
              strcat( PrintString, DataString );
            }
            strcat( PrintString, "\n" );
            UARTStatus = ASMN_UARTSENDSTRING( MenuCom, PrintString,
                                              ASMN_UARTMODECRLF );
          }
          LastErrorStatus = ErrorStatus;
        }
        
        if( ErrorStatus & RLIN3_A_LIN_STATE_ERROR )
        {
          strcat( PrintString, "E\n" );
          LastErrorStatus = ErrorStatus;
        }
    
        if( ( ErrorStatus == RLIN3_A_LIN_STATE_SLEEP ) &&
            ( LastErrorStatus != ErrorStatus ) )
        {
          strcat( PrintString, "S\n" );
          LastErrorStatus = ErrorStatus;
        }
        
        if( ErrorStatus == RLIN3_A_LIN_STATE_WAKEUP )
        {
          strcat( PrintString, "W\n" );
          LastErrorStatus = ErrorStatus;
        }

      } while( ErrorStatus != RLIN3_A_LIN_STATE_IDLE );
      
      SuccessFlag &= RLIN3_LINM_NextTableContent( ( u08 )UnitNumberM );
      do
      {
        ErrorStatus = RLIN3_LINM_GetStatus( ( u08 )UnitNumberM );
        
      } while( ErrorStatus != RLIN3_A_LIN_STATE_IDLE );
  
      if( !EndlessMode )
      {
        UARTStatus = ASMN_UARTRECEIVEBYTE( ASMN_MENUCOM, &UserInput );    
      }
      
    } while( UARTStatus != ASMN_UARTTRANSFEROK );
  }

  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }
    
  if( SuccessFlag == RLIN3_OK ) {
    
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

unsigned char ASMN_RLIN3Applications( unsigned int MenuCom )
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
    case ASMN_MENUCODE_SEND:
      UARTStatus = ApplRLIN3SendString( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN2
    case ASMN_MENUCODE_LINMMODE:
      UARTStatus = ApplRLIN3LINSetMasterMode( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN3
    case ASMN_MENUCODE_LINMSTART:
      UARTStatus = ApplRLIN3LINMasterTableStart( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN4
    case ASMN_MENUCODE_LINMNEXT:
      UARTStatus = ApplRLIN3LINMasterTableNext( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN5
    case ASMN_MENUCODE_LINSMODE:
      UARTStatus = ApplRLIN3LINSetSlaveMode( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN6
    case ASMN_MENUCODE_LINSMON:
      UARTStatus = ApplRLIN3LINSlaveMonitor( MenuCom );
      break;
#endif 
#ifdef ASMN_MENULINE_MEN7
    case ASMN_MENUCODE_LINMST:
      UARTStatus = ApplRLIN3LINMasterSlaveTest( MenuCom );
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
