//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision$
// DATE    = $Date$
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2002 by Renesas Electronics (Europe) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RSCFD Application Interface
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
//
//
//============================================================================
// Environment: Devices:          All featuring ASMN Monitor (min. 128k ROM)
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#include <stddef.h>
#include <stdio.h>
#include <ree_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#if( defined( EE_RSCFD_MACROS ) || defined( RSCFD_MACROS ) )

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

/* RSCFD Driver Interface */
#ifdef DRIVER_LOCAL
#undef DRIVER_LOCAL
#endif
#include <map_rscfd.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "RSCAN-FD APPLICATION MENU\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 03/2015    \n\n"
#define ASMN_MENULINE_MEN0  " 0 -> Exit\n"

#if( EE_RSCFD_TYPE == RSCFD_UCIAPRCN )
//#define ASMN_MENULINE_MEN1  " 1 -> Reset\n"
#define ASMN_MENULINE_MEN2  " 2 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN3  " 3 -> RAM Test\n"
#define ASMN_MENULINE_MEN4  " 4 -> Self Test\n"
#define ASMN_MENULINE_MEN5  " 5 -> Internal Self Test\n"
#endif

#if( EE_RSCFD_TYPE == RSCANFD_UCIAPRCN_V3 )
#define ASMN_MENULINE_MEN1  " 1 -> Reset\n"
#define ASMN_MENULINE_MEN2  " 2 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN3  " 3 -> RAM Test\n"
#define ASMN_MENULINE_MEN4  " 4 -> Self Test\n"
#define ASMN_MENULINE_MEN5  " 5 -> Internal Self Test\n"
#define ASMN_MENULINE_MEN6  " 6 -> Software Gateway\n"
#endif


#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_CYCLES    "\n Enter Number of Cycles: "
#define ASMN_MENUINPUT_ECYCLES   "\n Enter Number of Cycles [0=Forever]: "
#define ASMN_MENUINPUT_ID        "\n Enter Message ID: "
#define ASMN_MENUINPUT_BAUDSEL   "\n Enter Baud Rate [bit/s, 0=MAX]: "
#define ASMN_MENUINPUT_UNIT      "\n Enter Unit [0...] "
#define ASMN_MENUINPUT_UNIT1     "\n Enter First Unit [0...] "
#define ASMN_MENUINPUT_UNIT2     "\n Enter Second Unit [0...] "
#define ASMN_MENUINPUT_MACHINE   "\n Enter Channel [0...]: "
#define ASMN_MENUINPUT_MACHIN1   "\n Enter First Channel [0...] "
#define ASMN_MENUINPUT_MACHIN2   "\n Enter Second Channel [0...] "
#define ASMN_MENUINPUT_MACHINES  "\n Enter Channels [2...]: "

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK   1
#define ASMN_MENUCODE_NOCMD   -1
#define ASMN_MENUCODE_EXIT     0
#define ASMN_MENUCODE_BACK     0

#if( EE_RSCFD_TYPE == RSCFD_UCIAPRCN )
//#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST2    2
#define ASMN_MENUCODE_TEST3    3
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST5    5
#endif

#if( EE_RSCFD_TYPE == RSCFD_UCIAPRCN_V3 )
#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST2    2
#define ASMN_MENUCODE_TEST3    3
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST5    5
#define ASMN_MENUCODE_TEST6    6
#endif

/* UART Replacement Functions for Monitor */

#define ASMN_A_TTYMODE_CR   0 /* application level constants */
#define ASMN_A_TTYMODE_CRLF 1
#define ASMN_A_HEXMODE      1
#define ASMN_A_DECMODE      0
#define ASMN_A_RECBUFLEN    80

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
      	InputString[ DigitCounter++ ] = UserInput;
      }
      else if( UserInput == 0x09 ) {
      	if( DigitCounter > 0 ) DigitCounter--;
      }
    }
  }

  *MenuCommand = -1;
  return( UARTStatus );
}

#ifdef ASMN_MENUCODE_TEST1

bit ApplRSCFDReset( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCFD_OK;
  int           Unit            = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCFD_ERROR;

  if( SuccessFlag == EE_RSCFD_OK ) {
    
    SuccessFlag = EE_RSCFD_Reset( ( u08 )Unit );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCFD_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST2

bit
ApplRSCFDBasicTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCFD_OK;
  int           Unit_1          = 0;
  int           Unit_2          = 0;
  int           Machine_1       = 0;
  int           Machine_2       = 1;


  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT1,
				    &Unit_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT2,
				    &Unit_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN1,
				    &Machine_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCFD_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN2,
				    &Machine_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCFD_ERROR;

  if( SuccessFlag == EE_RSCFD_OK ) {

    SuccessFlag = EE_RSCFD_BasicTest( ( u08 )Unit_1, 
                                      ( u08 )Unit_2,
                                      ( u08 )Machine_1, 
                                      ( u08 )Machine_2 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCFD_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST3

bit ApplRSCFDRAMTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCFD_OK;
  int           Unit            = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCFD_ERROR;

  if( SuccessFlag == EE_RSCFD_OK ) {
    
    SuccessFlag = EE_RSCFD_RAMTestApp( ( u08 )Unit );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCFD_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST4

bit
ApplRSCFDSelfTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCFD_OK;
  int           Unit_1          = 0;
  int           Machine_1       = 0;
  int           Machine_2       = 1;


  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT1,
				    &Unit_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN1,
				    &Machine_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCFD_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN2,
				    &Machine_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCFD_ERROR;

  if( SuccessFlag == EE_RSCFD_OK ) {

    SuccessFlag = EE_RSCFD_BasicSelfTest( ( u08 )Unit_1, 
                                          ( u08 )Machine_1, 
                                          ( u08 )Machine_2 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCFD_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST5

bit
ApplRSCFDIntSelfTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCFD_OK;
  int           Unit_1          = 0;
  int           Machine_1       = 0;


  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT1,
				    &Unit_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN1,
				    &Machine_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCFD_ERROR;

  if( SuccessFlag == EE_RSCFD_OK ) {

    SuccessFlag = EE_RSCFD_BasicIntSelfTest( ( u08 )Unit_1, 
                                             ( u08 )Machine_1 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCFD_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST6

bit
ApplRSCFDSWGateway( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCFD_OK;
  int           Unit            = 0;
  int           Channels        = -1;


  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT,
				    &Unit,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINES,
				    &Channels,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCFD_ERROR;

  if( SuccessFlag == EE_RSCFD_OK ) {

    SuccessFlag = EE_RSCFD_SW_Gateway( ( u08 )Unit, 
                                       ( u08 )Channels );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCFD_OK ) {
    
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

bit ASMN_RSCFDApplications( u08 MenuCom )
{
#if 0
  bit           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
         ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMainMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {

    case ASMN_MENUCODE_EXIT: 
      break;
      
#ifdef ASMN_MENUCODE_TEST1
    case ASMN_MENUCODE_TEST1:
      UARTStatus = ApplRSCFDReset( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST2
    case ASMN_MENUCODE_TEST2:
      UARTStatus = ApplRSCFDBasicTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST3
    case ASMN_MENUCODE_TEST3:
      UARTStatus = ApplRSCFDRAMTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST4
    case ASMN_MENUCODE_TEST4:
      UARTStatus = ApplRSCFDSelfTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST5
    case ASMN_MENUCODE_TEST5:
      UARTStatus = ApplRSCFDIntSelfTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST6
    case ASMN_MENUCODE_TEST6:
      UARTStatus = ApplRSCFDSWGateway( MenuCom );
      break;
#endif
    default:
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_NOCMD,
				    ASMN_UARTMODECRLF );
      break;
    }
  }
  return( UARTStatus );
#endif
  EE_RSCFD_Reset( 0 );
  EE_RSCFD_BasicTest( 0, 1, 0, 0 );
}

#endif
