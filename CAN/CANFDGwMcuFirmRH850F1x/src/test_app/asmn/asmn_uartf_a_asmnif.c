//============================================================================
// PROJECT = ASMN Test Monitor
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2002 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
// Purpose: UART F Application Access Interface
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

#ifdef UARTF_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTF_STANDARD )
/* #include <map_uartf.h> - This is the module itself */

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

/* UARTF Driver Interface */
#include <map_uartf.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "UARTF APPLICATION MENU\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 04/2012    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( ( UARTF_TYPE == QLAPBUARTFV1 ) ||\
     ( UARTF_TYPE == UARTF_STANDARD ) )
#define ASMN_MENULINE_MEN1  "1 -> Send String\n"
#define ASMN_MENULINE_MEN2  "2 -> Set LIN Master Mode\n"
#define ASMN_MENULINE_MEN3  "3 -> Set LIN Master Table\n"
#define ASMN_MENULINE_MEN4  "4 -> Send LIN Master Table Entry\n"
#define ASMN_MENULINE_MEN5  "5 -> Set LIN Slave Mode\n"
#define ASMN_MENULINE_MEN6  "6 -> Monitor LIN Slave Activity\n"
#define ASMN_MENULINE_MEN7  "7 -> Monitor LIN Slave Auto Addressing\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT       "\n Enter Unit: "
#define ASMN_MENUINPUT_LENGTH     "\n Enter Length [0=Send 1 Char Forever, given is MAX]: "
#define ASMN_MENUINPUT_STRING     "\n Enter String: "
#define ASMN_MENUINPUT_BAUDRATE   "\n Enter Baudrate: "
#define ASMN_MENUINPUT_TABLE      "\n Enter Table: "

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
#define ASMN_MENUCODE_LINSAADR  7

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
ApplUARTFSendString( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = UARTF_OK;
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

  if( SuccessFlag == UARTF_OK )

    SuccessFlag = UARTF_SendString( ( u08 )UnitNumber, 
                                    SendString, 
                                    ASMN_UARTMODECR );
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTF_OK ) {
    
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
ApplUARTFLINSetMasterMode( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = UARTF_OK;
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

  if( SuccessFlag == UARTF_OK )

    SuccessFlag = UARTF_LIN_SetMode( ( u08 )UnitNumber, 
                                     UARTF_A_MASTER, 
                                     ( u32 )Baudrate,
                                     OSCILLATOR_FREQUENCY );
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTF_OK ) {
    
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
ApplUARTFLINMasterTableStart( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = UARTF_OK;
  int           Table          = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				             ASMN_MENUINPUT_TABLE,
				             &Table,
				             &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == UARTF_OK )
  {
    SuccessFlag =  UARTF_LINM_SetTable( ( u08 )Table );
    SuccessFlag &= UARTF_LINM_RestartTable( );
  }
  
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTF_OK ) {
    
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
ApplUARTFLINMasterTableNext( u08 MenuCom )
{
  bit           UARTStatus;
  bit           SuccessFlag    = UARTF_OK;

  SuccessFlag =  UARTF_LINM_SendWakeup( );
  while( UARTF_LINM_GetStatus( ) != EE_UARTF_A_LIN_STATE_IDLE );
  SuccessFlag &= UARTF_LINM_NextTableContent( );
  while( UARTF_LINM_GetStatus( ) != EE_UARTF_A_LIN_STATE_IDLE );
  
  if( SuccessFlag == UARTF_OK ) {
    
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
ApplUARTFLINSetSlaveMode( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = UARTF_OK;
  int           UnitNumber     = 0;
  unsigned long Baudrate       = 9600;

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

  if( SuccessFlag == UARTF_OK )

    SuccessFlag = UARTF_LIN_SetMode( ( u08 )UnitNumber, 
                                     UARTF_A_SLAVE, 
                                     ( u32 )Baudrate,
                                     OSCILLATOR_FREQUENCY );
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTF_OK ) {
    
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
ApplUARTFLINSlaveMonitor( u08 MenuCom )
{
  bit           UARTStatus;
  bit           SuccessFlag    = UARTF_OK;
  u08           CurrentStatus;
  u08           PreviousStatus;
  
  char          StatusString[ 4 ];
  char          StatusLine[ 12 ];
  
  PreviousStatus = EE_UARTF_A_LIN_STATE_IDLE;
  CurrentStatus  = PreviousStatus;

  StatusLine[ 0 ] = 0;
  
  UARTF_LINS_ActivateResponses( true );

  while( CurrentStatus != EE_UARTF_A_LIN_STATE_SLEEP )
  {
    CurrentStatus = UARTF_LINS_GetSleepState( );
    if( CurrentStatus != PreviousStatus )
    {
      sprintf( StatusString, "%02X", ( int )CurrentStatus );
      strcat( StatusLine, StatusString );
      if( ( CurrentStatus == EE_UARTF_A_LIN_STATE_IDLE ) ||
          ( CurrentStatus & EE_UARTF_A_LIN_STATE_ERROR ) )
      {
        strcat( StatusLine, "\n" );
        UARTStatus = ASMN_UARTSENDSTRING( MenuCom, StatusLine,
                                          ASMN_UARTMODECRLF );
        StatusLine[ 0 ] = 0;
        
        if( CurrentStatus & EE_UARTF_A_LIN_STATE_ERROR )
        {
          UARTF_LINS_GetClearErrorState( );  /* restart slave on errors */
        }
      }
      PreviousStatus = CurrentStatus;
    }
  }

  while( UARTF_LINS_GetSleepState( ) != EE_UARTF_A_LIN_STATE_IDLE ); /* wake */
    
  if( SuccessFlag == UARTF_OK ) {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_OK,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  return( UARTF_OK );
}

#endif

#ifdef ASMN_MENULINE_MEN7

bit
ApplUARTFLINAutoAddressing( u08 MenuCom )
{
  bit           UARTStatus         = ASMN_UARTTRANSFEROK;
  u08           AutoAddrStatus_u08 = EE_UARTF_A_AAEND;
  u08           AutoAddress_u08    = EE_UARTF_A_LIN_INITIALNAD;
  u08           AutoAddrOldStatus_u08;
  u08           AutoAddressOld_u08;
  
  char          AddressString[ 80 ];
  
  do
  {
    AutoAddrOldStatus_u08 = AutoAddrStatus_u08;
    AutoAddressOld_u08    = AutoAddress_u08;
    
    AutoAddrStatus_u08 = UARTF_LINS_GetAAdrNAD( &AutoAddress_u08 );

    switch( AutoAddrStatus_u08 )
    {
      case EE_UARTF_A_AANONE:
        if( AutoAddrStatus_u08 != AutoAddrOldStatus_u08 )
        {
          UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENUOUTPUT_AAWAITING,
                                            ASMN_UARTMODECRLF );
        }
        break;
        
      case EE_UARTF_A_AASTART:
        if( AutoAddrStatus_u08 != AutoAddrOldStatus_u08 )
        {
          UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENUOUTPUT_AAMEASURE,
                                            ASMN_UARTMODECRLF );
        }
        break;
        
      case EE_UARTF_A_AAMEASURE:
        sprintf( AddressString, ASMN_MENUOUTPUT_AANADRCV, 
                ( int )AutoAddress_u08 );
        if( AutoAddressOld_u08 != AutoAddress_u08 )
        {
          UARTStatus = ASMN_UARTSENDSTRING( MenuCom, AddressString,
                                            ASMN_UARTMODECRLF );
        }
        break;
        
      case EE_UARTF_A_AAEND:
        if( AutoAddrStatus_u08 != AutoAddrOldStatus_u08 )
        {
          UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENUOUTPUT_AACOMPL,
                                            ASMN_UARTMODECRLF );
          UARTStatus = ASMN_UARTERROR;
        }
        break;
        
      default:
        break;
    }
  } while( UARTStatus == ASMN_UARTTRANSFEROK );
    
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_OK,
                                    ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );

  return( UARTStatus );
}

#endif

unsigned char ASMN_UARTFApplications( unsigned int MenuCom )
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
      UARTStatus = ApplUARTFSendString( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN2
    case ASMN_MENUCODE_LINMMODE:
      UARTStatus = ApplUARTFLINSetMasterMode( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN3
    case ASMN_MENUCODE_LINMSTART:
      UARTStatus = ApplUARTFLINMasterTableStart( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN4
    case ASMN_MENUCODE_LINMNEXT:
      UARTStatus = ApplUARTFLINMasterTableNext( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN5
    case ASMN_MENUCODE_LINSMODE:
      UARTStatus = ApplUARTFLINSetSlaveMode( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN6
    case ASMN_MENUCODE_LINSMON:
      UARTStatus = ApplUARTFLINSlaveMonitor( MenuCom );
      break;
#endif 
#ifdef ASMN_MENULINE_MEN7
    case ASMN_MENUCODE_LINSAADR:
      UARTStatus = ApplUARTFLINAutoAddressing( MenuCom );
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
