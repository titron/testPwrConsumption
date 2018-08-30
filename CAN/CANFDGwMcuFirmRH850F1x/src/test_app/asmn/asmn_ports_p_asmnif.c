//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 597 $
// DATE    = $Date: 2008-11-19 10:14:49 +0100 (Mi, 19 Nov 2008) $
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2002 by NEC Electronics (EUROPE) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
//============================================================================
// Purpose: Standard Ports Primitive Access Interface
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
// Revision 1.1  2004/02/09 14:30:32  liederr
// Initial creation.
//
//
//============================================================================


#include <ree_types.h>
#include <stdio.h>
#include <map_asmn_basic.h>
#include <map_device.h>

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

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* STANDARD PORTS Driver Interface */
#ifdef DRIVER_LOCAL
#undef DRIVER_LOCAL
#endif
#include <map_ports.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "PORTS TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 11/2002    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( PORTS_TYPE == PORTS_STANDARD )
#define ASMN_MENULINE_MEN1  "1 -> Port Enable\n"
#define ASMN_MENULINE_MEN2  "2 -> Port Disable\n"
#define ASMN_MENULINE_MEN3  "3 -> Write\n"
#define ASMN_MENULINE_MEN4  "4 -> Read\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT       "\n Enter Port Unit [0...=NUMERIC, 0x100...=DL,DH,AL,AH,CS,CT,CM,CD: "
#define ASMN_MENUINPUT_BIT        "\n Enter Bit Mask [16-bit]: "
#define ASMN_MENUINPUT_DIRECTION  "\n Enter Direction [0=OUT,1=IN,2=KEEP]: "
#define ASMN_MENUINPUT_PERIPHERAL "\n Enter Peripheral Mode [0=OFF,1=ON,2=KEEP]: "
#define ASMN_MENUINPUT_FUNCTION   "\n Enter Alternative Function Mode [0=OFF,1=ON,2=KEEP]: "
#define ASMN_MENUINPUT_DATA       "\n Enter Data Value: "
#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUOUTPUT_READ      "\n Read Value: %04XH\n"

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0
#define ASMN_MENUCODE_PORTE 1
#define ASMN_MENUCODE_PORTD 2
#define ASMN_MENUCODE_WRITE 3
#define ASMN_MENUCODE_READ  4

/* UART Replacement Functions for Monitor */

#define ASMN_A_TTYMODE_CR   0 /* application level constants */
#define ASMN_A_TTYMODE_CRLF 1
#define ASMN_A_HEXMODE      1
#define ASMN_A_DECMODE      0
#define ASMN_A_RECBUFLEN    80

/*
 * global variables
 */

/*
 * interrupt functions
 */

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
// FunctionName: TestPORTPortEnable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestPORTPortEnable( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag          = PORT_OK;
           int  UnitNumber_int       = -1; 
           int  BitSpecification_int = -1;
           int  PortDirection_int;
           int  PeripheralMode_int;
           int  AlternateFunction_int;         
           u08  PortDirection_u08;
           u08  PeripheralMode_u08;
           u08  AlternateFunction_u08;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_BIT,
                				    &BitSpecification_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  if( SuccessFlag == PORT_OK )
    {
      SuccessFlag = PORT_GetStatus( ( u16 )UnitNumber_int,  
                                    ( u16 )BitSpecification_int,
                                    &PortDirection_u08,  
                                    &PeripheralMode_u08,
                                    &AlternateFunction_u08 );
    }

  if( SuccessFlag == PORT_OK ) 
  {  
    PortDirection_int       = ( int )PortDirection_u08;
    PeripheralMode_int      = ( int )PeripheralMode_u08;
    AlternateFunction_int   = ( int )AlternateFunction_u08;
  }

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_DIRECTION,
                				    &PortDirection_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_PERIPHERAL,
                				    &PeripheralMode_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_FUNCTION,
                				    &AlternateFunction_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  if( SuccessFlag == PORT_OK )
  {
    SuccessFlag = PORT_Enable( ( u16 )UnitNumber_int,
                               ( u16 )BitSpecification_int,
                               ( u08 )PortDirection_int,  
                               ( u08 )PeripheralMode_int,
                               ( u08 )AlternateFunction_int );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == PORT_OK ) {
    
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
// FunctionName: TestPORTPortDisable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestPORTPortDisable( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag          = PORT_OK;
           int  UnitNumber_int       = -1; 
           int  BitSpecification_int = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_BIT,
                				    &BitSpecification_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  if( SuccessFlag == PORT_OK )
  {
    SuccessFlag = PORT_Disable( ( u16 )UnitNumber_int,
                                ( u16 )BitSpecification_int );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == PORT_OK ) {
    
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
// FunctionName: TestPORTWrite
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestPORTWrite( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag          = PORT_OK;
           int  UnitNumber_int       = -1; 
           int  PortData_int;
           u16  PortData_u16;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  if( SuccessFlag == PORT_OK )
    {
      SuccessFlag = PORT_Read( ( u16 )UnitNumber_int, &PortData_u16 );
    }

  if( SuccessFlag == PORT_OK ) 
  {
    PortData_int = ( int )PortData_u16;
  }

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_DIRECTION,
                				    &PortData_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  if( SuccessFlag == PORT_OK )
  {
    SuccessFlag = PORT_Write( ( u16 )UnitNumber_int,
                              ( u16 )PortData_int );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == PORT_OK ) {
    
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

//=============================================================================
// FunctionName: TestPORTRead
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
bit TestPORTRead( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag          = PORT_OK;
           int  UnitNumber_int       = -1; 
           u16  ReadData_u16;
           char PrintString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = PORT_ERROR;

  if( SuccessFlag == PORT_OK )
  {
    SuccessFlag = PORT_Read( ( u16 )UnitNumber_int, &ReadData_u16 );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == PORT_OK ) {
    
    sprintf( PrintString, ASMN_MENUOUTPUT_READ, ( unsigned int )ReadData_u16 );

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

//=============================================================================
// FunctionName: ASMN_PORTFunctions
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Decode and execute DCAN Primitive Menu Functions.
//=============================================================================
unsigned char ASMN_PORTFunctions( u08 MenuCom )
{
  bit           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
         ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;
#ifdef ASMN_MENULINE_MEN1      
    case ASMN_MENUCODE_PORTE:
      UARTStatus = TestPORTPortEnable( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN2
    case ASMN_MENUCODE_PORTD:
      UARTStatus = TestPORTPortDisable( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN3
    case ASMN_MENUCODE_WRITE:
      UARTStatus = TestPORTWrite( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN4
    case ASMN_MENUCODE_READ:
      UARTStatus = TestPORTRead( MenuCom );
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
