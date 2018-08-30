//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 115 $
// DATE    = $Date: 2003-12-11 14:58:45 +0100 (Do, 11 Dez 2003) $
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2002 by NEC Electronics (EUROPE) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
//============================================================================
// Purpose: UART C Primitive Access Interface
//
//Warranty Disclaimer
//
//Because the Product(s) is licensed free of charge, there is no warranty 
//of any kind whatsoever and expressly disclaimed and excluded by NEC, 
//either expressed or implied, including but not limited to those for 
//non-infringement of intellectual property, merchantability and/or 
//fitness for the particular purpose. 
//NEC shall not have any obligation to maintain, service or provide bug 
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
//In no event shall NEC be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. NEC shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by NEC in connection with the Product(s) and/or the 
//Application.
//
//============================================================================
// Environment: Devices:          All featuring ASMN Monitor (min. 128k ROM)
//              Assembler:        GHS MULTI 2000
//              C-Compiler:       GHS MULTI 2000
//              Linker:           GHS MULTI 2000
//              Debugger:         GHS MULTI 2000
//============================================================================
//
// $Log$
// Revision 1.1  2003/12/11 13:58:45  liederr
// Initial creation.
//
//
//============================================================================


//#include <nec_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef UARTC_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
/* #include <map_uartc.h> - This is the module itself */

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* UARTC Driver Interface */
#include <map_uartc.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "UART TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 04/2002    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( ( UARTC_TYPE == QLNPUUARTCV1 ) ||\
     ( UARTC_TYPE == UARTC_STANDARD ) )
#define ASMN_MENULINE_MEN1  "1 -> Port Enable\n"
#define ASMN_MENULINE_MEN2  "2 -> Port Disable\n"
#define ASMN_MENULINE_MEN3  "3 -> Configuration\n"
#define ASMN_MENULINE_MEN4  "4 -> Status\n"
#define ASMN_MENULINE_MEN5  "5 -> Reset UART\n"
#define ASMN_MENULINE_MEN6  "6 -> Send Byte\n"
#define ASMN_MENULINE_MEN7  "7 -> Receive Byte\n"
#define ASMN_MENULINE_MEN8  "8 -> LIN Configuration\n"
#define ASMN_MENULINE_MEN9  "9 -> LIN Break Send\n"
#define ASMN_MENULINE_MEN10 "10-> LIN Break Receive\n"
#define ASMN_MENULINE_MEN11 "11-> LIN Break Read (Status)\n"
#define ASMN_MENULINE_MEN12 "12-> Generate Interrupts\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT       "\n Enter Unit: "
#define ASMN_MENUINPUT_BAUDRATE   "\n Enter Baud Rate: "
#define ASMN_MENUINPUT_PARITY     "\n Enter Parity [0=OFF,1=ZERO,2=ODD,3=EVEN]: "
#define ASMN_MENUINPUT_CHARLEN    "\n Enter Character Length [0=7BITS,1=8BITS]: "
#define ASMN_MENUINPUT_STOPBITS   "\n Enter Stop Bits [0=ONE,1=TWO]: "
#define ASMN_MENUINPUT_BYTE       "\n Enter Byte: "
#define ASMN_MENUINPUT_INTLEVEL   "\n Enter Interrupt Level: "
#define ASMN_MENUINPUT_IRQEVERY   "\n Enter Indicator Count Threshold: "
#define ASMN_MENUINPUT_IRQSOURCE  "\n Enter Interrupt Source [0=RECEIVE,1=TRANSMIT,2=ERROR]: "
#define ASMN_MENUINPUT_DATADIR    "\n Enter Data Direction [0=MSB FIRST,1=LSB FIRST]: "
#define ASMN_MENUINPUT_SIGLEVEL   "\n Enter Signal Level [0=RS232,1=INVERTED]: "
#define ASMN_MENUINPUT_SBLENGTH   "\n Enter Sync Break Length [0-7]: "
#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUOUTPUT_READ      "\n Read Value: %02XH\n"
#define ASMN_MENUOUTPUT_STATUS    "\n PE:%d, FE:%d, OVF:%d\n TXSF:%d\n"
#define ASMN_MENUOUTPUT_BREAK     "\n TX:%d, RX:%d, RXLINE:%d\n"

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0
#define ASMN_MENUCODE_PORTE 1
#define ASMN_MENUCODE_PORTD 2
#define ASMN_MENUCODE_CNF   3
#define ASMN_MENUCODE_STATE 4
#define ASMN_MENUCODE_RESET 5
#define ASMN_MENUCODE_SEND  6
#define ASMN_MENUCODE_RECV  7
#define ASMN_MENUCODE_LINC  8
#define ASMN_MENUCODE_LINBS 9
#define ASMN_MENUCODE_LINBR 10
#define ASMN_MENUCODE_LINST 11
#define ASMN_MENUCODE_IRQ   12

/*
 * global variables
 */

static u16 UARTC_InterruptCount_u16 = 0;

/*
 * interrupt functions
 */

void TestUARTIRQNotifier( )
{
  UARTC_InterruptCount_u16++;
}

/*
 * functions
 */

//=============================================================================
// FunctionName: DisplayMenu
// IN  : MenuCom:       Communication Port ID
// OUT : MenuCommand:   Selected command number by user
//       Return:        Communication status
// Description : 
// Present submenu on the TTY and wait for user input. Return user's coice.
//=============================================================================
static bit                /* local submenu: invisible from outside */
DisplayMenu( u08   MenuCom,
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
#ifdef ASMN_MENULINE_MEN0
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN0,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
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
#ifdef ASMN_MENULINE_MEN8
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN8,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN9
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN9,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN10
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN10,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN11
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN11,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN12
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN12,
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
      sscanf( InputString, "%u", &DigitValue );
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

//=============================================================================
// FunctionName: TestUARTCPortEnable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCPortEnable( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
  {
    SuccessFlag = UARTC_PortEnable( ( u08 )UnitNumber );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
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

//=============================================================================
// FunctionName: TestUARTCPortDisable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCPortDisable( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
  {
    SuccessFlag = UARTC_PortDisable( ( u08 )UnitNumber );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN8

//=============================================================================
// FunctionName: TestUARTCLINConfiguration
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCLINConfiguration( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  u08           PDataDirection;
  u08           PSignalLevel;
  u08           PSyncBreakLength;
           int  UnitNumber  = -1;
           int  DataDirection   = -1;
           int  SignalLevel     = -1;
           int  SyncBreakLength = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_UNIT,
                                    &UnitNumber,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
    {
      SuccessFlag = UARTC_LINGetConfig( ( u08 )UnitNumber,
                                        &PDataDirection,
                                        &PSignalLevel,
                                        &PSyncBreakLength );  
    }

  if( SuccessFlag == UARTC_OK ) 
  {
    DataDirection   = ( int )PDataDirection;
    SignalLevel     = ( int )PSignalLevel;
    SyncBreakLength = ( int )PSyncBreakLength;
  }

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_DATADIR,
                				    &DataDirection,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_SIGLEVEL,
                				    &SignalLevel,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_SBLENGTH,
                				    &SyncBreakLength,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
  {
    SuccessFlag = UARTC_LINSetConfig( ( u08 )UnitNumber,
                                      ( u08 )DataDirection,
                                      ( u08 )SignalLevel,
                                      ( u08 )SyncBreakLength );
                                    
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
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

//=============================================================================
// FunctionName: TestUARTCConfiguration
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCConfiguration( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag   = UARTC_OK;
  int           UnitNumber    = -1;
  int           Parity        = -1;
  int           CharLength    = -1;
  int           StopBits      = -1;
  int           DataDirection = -1;
  unsigned long BaudRate      = 9600L;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_UNIT,
                                    &UnitNumber,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                     ASMN_MENUINPUT_BAUDRATE,
                                     &BaudRate,
                                     &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_PARITY,
                                    &Parity,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_CHARLEN,
                                    &CharLength,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_STOPBITS,
                                    &StopBits,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_DATADIR,
                				    &DataDirection,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
  {
    SuccessFlag = UARTC_Configuration( ( u08 )UnitNumber,
                                       ( flt )OSCILLATOR_FREQUENCY,
                                       ( u32 )BaudRate,
                                       ( u08 )Parity,
                                       ( u08 )CharLength,
                                       ( u08 )StopBits,
                                       ( u08 )DataDirection );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN9

//=============================================================================
// FunctionName: TestUARTCLINSendBreak
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCLINSendBreak( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
  {
    SuccessFlag = UARTC_LINSendBreak( ( u08 )UnitNumber );        
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN10

//=============================================================================
// FunctionName: TestUARTCLINReceiveBreak
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCLINReceiveBreak( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
  {
    SuccessFlag = UARTC_LINReceiveBreak( ( u08 )UnitNumber );        
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN11

//=============================================================================
// FunctionName: TestUARTCLINReadBreak
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCLINReadBreak( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  int           UnitNumber  = -1;
  u08           ReceiveBreakPending;
  u08           ReceiveBreakActive;
  u08           SendBreakActive;
           char PrintString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
  {
    SuccessFlag = UARTC_LINReadBreak( ( u08 )UnitNumber,
                                      &ReceiveBreakPending,
                                      &ReceiveBreakActive,
                                      &SendBreakActive );        
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
    sprintf( PrintString, ASMN_MENUOUTPUT_BREAK, 
             ( unsigned int )SendBreakActive,
             ( unsigned int )ReceiveBreakPending,
             ( unsigned int )ReceiveBreakActive );

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, PrintString,
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

//=============================================================================
// FunctionName: TestUARTCReset
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCReset( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
  {
    SuccessFlag = UARTC_Reset( ( u08 )UnitNumber );        
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
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

//=============================================================================
// FunctionName: TestUARTCSendByte
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCSendByte( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag   = UARTC_OK;
  int           UnitNumber    = -1;
  int           SendCharacter = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_BYTE,
                                    &SendCharacter,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTERROR )
    SuccessFlag = UARTC_SendByte( ( u08 )UnitNumber, ( u08 )SendCharacter );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
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

//=============================================================================
// FunctionName: TestUARTCReadByte
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCReadByte( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  int           UnitNumber  = -1;
  u08           ReadValue;
  char          ReadString[ 20 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
    SuccessFlag = UARTC_ReceiveByte( ( u08 )UnitNumber, &ReadValue );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				                  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
    sprintf( ReadString, ASMN_MENUOUTPUT_READ, ( unsigned int )ReadValue );
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ReadString,
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

//=============================================================================
// FunctionName: TestUARTCGetStatus
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestUARTCGetStatus( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  int           UnitNumber  = -1;
  u08           ParityError;
  u08           FrameError;
  u08           OverrunError;
  u08           SendFlag;
  char          ResultString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK )
    SuccessFlag = UARTC_GetStatus( ( u08 )UnitNumber, 
                                   &ParityError,
                                   &FrameError,
                                   &OverrunError,
                                   &SendFlag );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				                  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {
    
    sprintf( ResultString, ASMN_MENUOUTPUT_STATUS, 
             ( unsigned int )ParityError,  ( unsigned int )FrameError,
             ( unsigned int )OverrunError, ( unsigned int )SendFlag );
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ResultString,
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

#ifdef ASMN_MENULINE_MEN12

//=============================================================================
// FunctionName: TestUARTCInterrupt
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Insert interrupt handler to show a dot on every x-th interrupt occurrance
//=============================================================================
bit TestUARTCInterrupt( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = UARTC_OK;
  u08           DummyByte;
  int           UnitNumber  = -1;
  int           EveryCount  = -1;
  int           IRQSource   = -1;
  int           IRQLevel    = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQEVERY,
                				    &EveryCount,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQSOURCE,
                				    &IRQSource,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_INTLEVEL,
                				    &IRQLevel,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK ) {

    UARTC_InterruptCount_u16 = 0;

    SuccessFlag = UARTC_CreateInterrupt( ( u08 )UnitNumber,
                                         ( u08 )IRQSource,
                                         ( u08 )IRQLevel,
                                         TestUARTIRQNotifier );
  }

  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == UARTC_OK ) {

    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

    do {

      if( UARTC_InterruptCount_u16 >= EveryCount ) {

	    UARTC_InterruptCount_u16 = 0;
	    ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
      }

      UARTStatus = ASMN_UARTRECEIVEBYTE( MenuCom, &DummyByte );

    } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  return( UARTStatus );
}

#endif

//=============================================================================
// FunctionName: ASMN_UARTCFunctions
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Decode and execute UART Primitive Menu Functions.
//=============================================================================
unsigned char ASMN_UARTCFunctions( u08 MenuCom )
{
  bit  UARTStatus   = ASMN_UARTTRANSFEROK;
  char MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
         ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;
      
#ifdef ASMN_MENULINE_MEN1
    case ASMN_MENUCODE_PORTE:
      UARTStatus = TestUARTCPortEnable( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN2
    case ASMN_MENUCODE_PORTD:
      UARTStatus = TestUARTCPortDisable( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN3
    case ASMN_MENUCODE_CNF:
      UARTStatus = TestUARTCConfiguration( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN8
    case ASMN_MENUCODE_LINC:
      UARTStatus = TestUARTCLINConfiguration( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN4
    case ASMN_MENUCODE_STATE:
      UARTStatus = TestUARTCGetStatus( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN5
    case ASMN_MENUCODE_RESET:
      UARTStatus = TestUARTCReset( MenuCom );
      break;
#endif      
#ifdef ASMN_MENULINE_MEN6
    case ASMN_MENUCODE_SEND:
      UARTStatus = TestUARTCSendByte( MenuCom );
      break;
#endif      
#ifdef ASMN_MENULINE_MEN7
    case ASMN_MENUCODE_RECV:
      UARTStatus = TestUARTCReadByte( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN9
    case ASMN_MENUCODE_LINBS:
      UARTStatus = TestUARTCLINSendBreak( MenuCom );
      break;
#endif      
#ifdef ASMN_MENULINE_MEN10
    case ASMN_MENUCODE_LINBR:
      UARTStatus = TestUARTCLINReceiveBreak( MenuCom );
      break;
#endif      
#ifdef ASMN_MENULINE_MEN11
    case ASMN_MENUCODE_LINST:
      UARTStatus = TestUARTCLINReadBreak( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN12
    case ASMN_MENUCODE_IRQ:
      UARTStatus = TestUARTCInterrupt( MenuCom );
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
