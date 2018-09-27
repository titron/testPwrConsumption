//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $RCSfile$
// VERSION = $Revision: 227 $
// DATE    = $Date: 2004-02-19 16:15:48 +0100 (Do, 19 Feb 2004) $
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2004 by NEC Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
// Purpose: AFCAN Application Interface
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
// Environment:     Devices:      all featuring ASMN Monitor (min. 128k ROM)
//                  Assembler:    N/A
//                  C-Compiler:   GHS MULTI 2000
//                  Linker:       GHS MULTI 2000
//                  Debugger:     GHS MULTI 2000
//============================================================================
// Version Author Description
// $Log$
// Revision 1.1  2004/02/19 15:15:02  liederr
// Initial creation.
//
//
//============================================================================

#include <stddef.h>
//#include <nec_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef CSI_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* BRG Driver Interface */
#include <map_csi.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "CSI TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 02/2004    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( CSI_TYPE == QLNPUCSI3V1 )
#define ASMN_MENULINE_MEN1  "1 -> Configuration\n"
#define ASMN_MENULINE_MEN2  "2 -> Stop\n"
#define ASMN_MENULINE_MEN3  "3 -> Send     8 Bit Data\n"
#define ASMN_MENULINE_MEN4  "4 -> Send    16 Bit Data\n"
#define ASMN_MENULINE_MEN5  "5 -> Receive  8 Bit Data\n"
#define ASMN_MENULINE_MEN6  "6 -> Receive 16 Bit Data\n"
#define ASMN_MENULINE_MEN7  "7 -> Generate Interrupts\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT       "\n Enter Unit: "
#define ASMN_MENUINPUT_TXRXMODE   "\n Enter Mode [0=RX,1=TX,3=TX/RX]: "
#define ASMN_MENUINPUT_CHARLEN    "\n Enter Data Size [0=16Bit,1..15=Bit]: "
#define ASMN_MENUINPUT_DIRECTION  "\n Enter Direction [0=MSBFirst,1=LSBFirst]: "
#define ASMN_MENUINPUT_IRQDELAY   "\n Enter INT Delay [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_TXMODE     "\n Enter TX Mode [0=SINGLE,1=CONT]: "
#define ASMN_MENUINPUT_CLOCKPHASE "\n Enter Clock Phase on Data Change [0=FALL,1=RISE]: "
#define ASMN_MENUINPUT_DATAPHASE  "\n Enter Data Capture Phase on Clock [0=RISE,1=FALL]: "
#define ASMN_MENUINPUT_CLOCKSEL   "\n Enter Clock Selection [0..6,7=SLAVE]: "
#define ASMN_MENUINPUT_BRGSEL     "\n Enter BRG Factor [0=OFF,1..7=2*DIV]: "
#define ASMN_MENUINPUT_VALUE      "\n Enter Value [0..]: "
#define ASMN_MENUINPUT_COUNT      "\n Enter Count: "
#define ASMN_MENUINPUT_INTLEVEL   "\n Enter Interrupt Level: "
#define ASMN_MENUINPUT_IRQEVERY   "\n Enter Indicator Count Threshold: "
#define ASMN_MENUINPUT_IRQSOURCE  "\n Enter Interrupt Source [0=TX/RX,1=OVF]: "
#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUOUTPUT_DATA8     "Read Data Value: %02X\n"
#define ASMN_MENUOUTPUT_DATA16    "Read Data Value: %04X\n"

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0

#if( CSI_TYPE == QLNPUCSI3V1 )
#define ASMN_MENUCODE_CFG   1
#define ASMN_MENUCODE_STOP  2
#define ASMN_MENUCODE_TX8   3
#define ASMN_MENUCODE_TX16  4
#define ASMN_MENUCODE_RX8   5
#define ASMN_MENUCODE_RX16  6
#define ASMN_MENUCODE_IRQ   7
#endif

/*
 * global variables
 */

static u16 CSI_InterruptCount_u16 = 0;

/*
 * interrupt functions
 */

void TestCSIIRQNotifier( )
{
  CSI_InterruptCount_u16++;
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
static u08                          /* local submenu: invisible from outside */
DisplayMenu( u08   MenuCom,
    	     char *MenuCommand )
{
  u08           UARTStatus;
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
	InputString[ DigitCounter++ ] = UserInput;
      }
      else if( UserInput == 0x08 ) {
	if( DigitCounter > 0 ) DigitCounter--;
      }
    }
  }

  *MenuCommand = -1;
  return( UARTStatus );
}

//=============================================================================
// FunctionName: TestCSIConfiguration
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestCSIConfiguration( u08 MenuCom )
{
  u08           UARTStatus;
  unsigned char ScanState;
  u08           SuccessFlag          = CSI_OK;
           int  UnitNumber_int       = -1; 
           int  TxRxMode_int         = -1;
           int  CharLength_int       = -1;
           int  TxDirection_int      = -1;
           int  IntDelay_int         = -1;
           int  TxMode_int           = -1;
           int  ClockPhase_int       = -1;
           int  DataPhase_int        = -1;
           int  ClockSelect_int      = -1;
           int  BRGSelect_int        = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CLOCKSEL,
                				    &ClockSelect_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_BRGSEL,
                				    &BRGSelect_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TXRXMODE,
                				    &TxRxMode_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHARLEN,
                				    &CharLength_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_DIRECTION,
                				    &TxDirection_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQDELAY,
                				    &IntDelay_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TXMODE,
                				    &TxMode_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CLOCKPHASE,
                				    &ClockPhase_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_DATAPHASE,
                				    &DataPhase_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  if( SuccessFlag == CSI_OK )
  {
    SuccessFlag = CSI_configure_csi( ( unsigned char )UnitNumber_int,
                                     CSI_ENABLE_CSI,
                                     ( unsigned char )TxRxMode_int,
                                     ( unsigned char )CharLength_int,
                                     ( unsigned char )TxDirection_int,
                                     ( unsigned char )IntDelay_int,
                                     ( unsigned char )TxMode_int,
                                     ( unsigned char )ClockPhase_int,
                                     ( unsigned char )DataPhase_int,
                                     ( ( unsigned char )ClockSelect_int ) +
                                     ( ( ( unsigned char )BRGSelect_int ) << 
                                       CSI_BRG_P ) );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == CSI_OK ) {
    
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

//=============================================================================
// FunctionName: TestCSIStop
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestCSIStop( u08 MenuCom )
{
  u08           UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag          = CSI_OK;
           int  UnitNumber_int       = -1; 

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  if( SuccessFlag == CSI_OK )
  {
    SuccessFlag = CSI_stop_csi( ( unsigned char )UnitNumber_int );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == CSI_OK ) {
    
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

//=============================================================================
// FunctionName: TestCSISend8Bit
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestCSISend8Bit( u08 MenuCom )
{
  u08           UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag          = CSI_OK;
           int  UnitNumber_int       = -1; 
           int  Data_int             = -1;
           int  Count_int            = 1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_VALUE,
                				    &Data_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_COUNT,
                				    &Count_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  if( SuccessFlag == CSI_OK )
  {
    while( --Count_int >= 0 )
      {
        SuccessFlag = CSI_transmit_8_bit_csi( ( ( unsigned char )UnitNumber_int ) |
                                              ( CSI_TP ),
                                              ( unsigned char )Data_int );
      }
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == CSI_OK ) {
    
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

//=============================================================================
// FunctionName: TestCSISend16Bit
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestCSISend16Bit( u08 MenuCom )
{
  u08           UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag          = CSI_OK;
           int  UnitNumber_int       = -1; 
           int  Data_int             = -1;
           int  Count_int            = 1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_VALUE,
                				    &Data_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_COUNT,
                				    &Count_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  if( SuccessFlag == CSI_OK )
  {
    while( --Count_int >= 0 )
      {
        SuccessFlag = CSI_transmit_16_bit_csi( ( ( unsigned char )UnitNumber_int ) |
                                               ( CSI_TP ),
                                               ( unsigned short )Data_int );
      }
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == CSI_OK ) {
    
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

//=============================================================================
// FunctionName: TestCSIReceive8Bit
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestCSIReceive8Bit( u08 MenuCom )
{
  u08           UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag          = CSI_OK;
           int  UnitNumber_int       = -1; 
  unsigned char Data_uc              = 0;
  char          ReadString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  if( SuccessFlag == CSI_OK )
  {
    SuccessFlag = CSI_receive_8_bit_csi( ( unsigned char )UnitNumber_int,
                                         &Data_uc );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == CSI_OK ) {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, "\n",
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    sprintf( ReadString, ASMN_MENUOUTPUT_DATA8, ( unsigned int )Data_uc );
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

//=============================================================================
// FunctionName: TestCSIReceive16Bit
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestCSIReceive16Bit( u08 MenuCom )
{
  u08            UARTStatus;
  unsigned char  ScanState;
  unsigned char  SuccessFlag          = CSI_OK;
           int   UnitNumber_int       = -1; 
  unsigned short Data_us              = 0;
  char           ReadString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  if( SuccessFlag == CSI_OK )
  {
    SuccessFlag = CSI_receive_16_bit_csi( ( unsigned char )UnitNumber_int,
                                          &Data_us );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == CSI_OK ) {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, "\n",
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    sprintf( ReadString, ASMN_MENUOUTPUT_DATA16, ( unsigned int )Data_us );
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

//=============================================================================
// FunctionName: TestCSIInterrupt
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Insert interrupt handler to show a dot on every x-th interrupt occurrance
//=============================================================================
u08 TestCSIInterrupt( u08 MenuCom )
{
  u08           UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag = CSI_OK;
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
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQEVERY,
                				    &EveryCount,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQSOURCE,
                				    &IRQSource,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_INTLEVEL,
                				    &IRQLevel,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = CSI_ERROR;

  if( SuccessFlag == CSI_OK ) {

    SuccessFlag = CSI_CreateInterrupt( ( unsigned int )UnitNumber,
                                       ( unsigned int )IRQSource,
                                       ( unsigned char )IRQLevel,
                                       TestCSIIRQNotifier );
  }

  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == CSI_OK ) {

    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

    do {

      if( CSI_InterruptCount_u16 >= EveryCount ) {

	    CSI_InterruptCount_u16 = 0;
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

//=============================================================================
// FunctionName: ASMN_CSIFunctions
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Decode and execute CSI Primitive Menu Functions.
//=============================================================================
unsigned char ASMN_CSIFunctions( u08 MenuCom )
{
  u08           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
         ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;

#ifdef ASMN_MENUCODE_CFG      
    case ASMN_MENUCODE_CFG:
      UARTStatus = TestCSIConfiguration( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_STOP
    case ASMN_MENUCODE_STOP:
      UARTStatus = TestCSIStop( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TX8
    case ASMN_MENUCODE_TX8:
      UARTStatus = TestCSISend8Bit( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TX16
    case ASMN_MENUCODE_TX16:
      UARTStatus = TestCSISend16Bit( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_RX8
    case ASMN_MENUCODE_RX8:
      UARTStatus = TestCSIReceive8Bit( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_RX16
    case ASMN_MENUCODE_RX16:
      UARTStatus = TestCSIReceive16Bit( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_IRQ
    case ASMN_MENUCODE_IRQ:
      UARTStatus = TestCSIInterrupt( MenuCom );
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
