/*===========================================================================*/
/* PROJECT = ASMN Test Monitor                                               */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2013 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG.Support                                                        */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: device_support.rl78-eu@lm.renesas.com                      */
/*        FAX:   +49 - (0)211 / 65 03 - 12 79                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/

#include <stddef.h>
#include <stdio.h>
#include <ree_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#if( defined( EE_RSCAN_MACROS ) || defined( RSCAN_MACROS ) )

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

/* RSCAN Driver Interface */
#ifdef DRIVER_LOCAL
#undef DRIVER_LOCAL
#endif
#include <map_rscan.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "RSCAN APPLICATION MENU\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 11/2011    \n\n"
#define ASMN_MENULINE_MEN0  " 0 -> Exit\n"

#if( EE_RSCAN_TYPE == RSCAN_3CH )
//#define ASMN_MENULINE_MEN1  " 1 -> Reset\n"
#define ASMN_MENULINE_MEN2  " 2 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN3  " 3 -> Basic AUTOSAR Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN4  " 4 -> RAM Test\n"
#endif

#if( EE_RSCAN_TYPE == RSCAN_UCIAPRCN )
//#define ASMN_MENULINE_MEN1  " 1 -> Reset\n"
#define ASMN_MENULINE_MEN3  " 3 -> Basic AUTOSAR Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN4  " 4 -> RAM Test\n"
#define ASMN_MENULINE_MEN9  " 9 -> Internal Self Test\n"
#ifndef EE_RSCAN_SINGLECHANNEL
#define ASMN_MENULINE_MEN2  " 2 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN7  " 7 -> Self Test\n"
#endif
#endif

#if( EE_RSCAN_TYPE == RSCANFD_UCIAPRCN )
//#define ASMN_MENULINE_MEN1  " 1 -> Reset\n"
#define ASMN_MENULINE_MEN4  " 4 -> RAM Test\n"
#ifndef EE_RSCAN_SINGLECHANNEL
#define ASMN_MENULINE_MEN2  " 2 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN7  " 7 -> Self Test\n"
#endif
#endif

#if( EE_RSCAN_TYPE == RSCAN_LITE_1CH )
//#define ASMN_MENULINE_MEN1  " 1 -> Reset\n"
#define ASMN_MENULINE_MEN4  " 4 -> RAM Test\n"
#define ASMN_MENULINE_MEN5  " 5 -> Basic Test: Sending\n"
#define ASMN_MENULINE_MEN6  " 6 -> Basic Test: Receiving\n"
#define ASMN_MENULINE_MEN8  " 8 -> Partial Networking Test\n"
#define ASMN_MENULINE_MEN9  " 9 -> Internal Self Test\n"
#endif

#if( EE_RSCAN_TYPE == RSCAN_LITE )
//#define ASMN_MENULINE_MEN1  " 1 -> Reset\n"
#define ASMN_MENULINE_MEN4  " 4 -> RAM Test\n"
#define ASMN_MENULINE_MEN5  " 5 -> Basic Test: Sending\n"
#define ASMN_MENULINE_MEN6  " 6 -> Basic Test: Receiving\n"
#define ASMN_MENULINE_MEN8  " 8 -> Partial Networking Test\n"
#define ASMN_MENULINE_MEN9  " 9 -> Internal Self Test\n"
#ifndef EE_RSCAN_SINGLECHANNEL
#define ASMN_MENULINE_MEN2  " 2 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN7  " 7 -> Self Test\n"
#endif
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
#define ASMN_MENUINPUT_UNITS     "\n Enter Sending Unit [0...] "
#define ASMN_MENUINPUT_UNITR     "\n Enter Receiving Unit [0...] "
#define ASMN_MENUINPUT_UNITM     "\n Enter Mirroring Unit [0...] "
#define ASMN_MENUINPUT_UNITH     "\n Enter Highload Generation Unit [0...] "
#define ASMN_MENUINPUT_UNITMR    "\n Enter Mirrored Receive Unit [0...] "
#define ASMN_MENUINPUT_MACHINE   "\n Enter Machine [0...]: "
#define ASMN_MENUINPUT_MACHIN1   "\n Enter First Machine [0...] "
#define ASMN_MENUINPUT_MACHIN2   "\n Enter Second Machine [0...] "
#define ASMN_MENUINPUT_MACHINS   "\n Enter Sending Machine [0...] "
#define ASMN_MENUINPUT_MACHINR   "\n Enter Receiving Machine [0...] "
#define ASMN_MENUINPUT_MACHINH   "\n Enter Highload Genration Machine [0...] "
#define ASMN_MENUINPUT_MACHINM   "\n Enter Mirroring Machine [0...] "
#define ASMN_MENUINPUT_MACHINMR  "\n Enter Mirrored Receive Machine [0...] "
#define ASMN_MENUINPUT_BUFR      "\n Enter Receiving Buffer [0...] "
#define ASMN_MENUINPUT_POWERSAVE "\n Enter Power Save Mode [0=ACTIVE,1=RESET,2=HALT,4=SLEEP] "
#define ASMN_MENUINPUT_REMOTEFLG "\n Enter Remote Frame Usage [0=DATA-FRAMES,1=REMOTE-FRAMES] "
#define ASMN_MENUINPUT_ERRORMASK "\n Enter Error Mask [1CH = all on] "

#define ASMN_MENUOUTPUT_RDCFG    "\n Config Values: Global: %04x H, Bitrate: %x H \n"

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK   1
#define ASMN_MENUCODE_NOCMD   -1
#define ASMN_MENUCODE_EXIT     0
#define ASMN_MENUCODE_BACK     0

#if( EE_RSCAN_TYPE == RSCAN_3CH )
//#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST2    2
#define ASMN_MENUCODE_TEST3    3
#define ASMN_MENUCODE_TEST4    4
#endif

#if( EE_RSCAN_TYPE == RSCAN_UCIAPRCN )
//#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST3    3
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST9    9
#ifndef EE_RSCAN_SINGLECHANNEL
#define ASMN_MENUCODE_TEST2    2
#define ASMN_MENUCODE_TEST7    7
#endif
#endif

#if( EE_RSCAN_TYPE == RSCANFD_UCIAPRCN )
#define ASMN_MENUCODE_TEST4    4
#ifndef EE_RSCAN_SINGLECHANNEL
#define ASMN_MENUCODE_TEST2    2
#define ASMN_MENUCODE_TEST7    7
#endif
#endif

#if( EE_RSCAN_TYPE == RSCAN_LITE_1CH )
//#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST5    5
#define ASMN_MENUCODE_TEST6    6
#define ASMN_MENUCODE_TEST8    8
#define ASMN_MENUCODE_TEST9    9
#endif

#if( EE_RSCAN_TYPE == RSCAN_LITE )
//#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST5    5
#define ASMN_MENUCODE_TEST6    6
#define ASMN_MENUCODE_TEST8    8
#define ASMN_MENUCODE_TEST9    9
#ifndef EE_RSCAN_SINGLECHANNEL
#define ASMN_MENUCODE_TEST2    2
#define ASMN_MENUCODE_TEST7    7
#endif
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
#ifdef ASMN_MENULINE_MEN20
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN20,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN21
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN21,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN30
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN30,
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

bit
ApplRSCANReset( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCAN_OK;
  int           Unit            = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;

  if( SuccessFlag == EE_RSCAN_OK ) {
    
//    SuccessFlag = EE_RSCAN_Reset( ( u08 )Unit );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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
ApplRSCANBasicTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCAN_OK;
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
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN2,
				    &Machine_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;

  if( SuccessFlag == EE_RSCAN_OK ) {

    SuccessFlag = EE_RSCAN_BasicTest( ( u08 )Unit_1, 
                                      ( u08 )Unit_2,
                                      ( u08 )Machine_1, 
                                      ( u08 )Machine_2 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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

bit
ApplRSCANASBasicTest( u08 MenuCom )
{
  bit           UARTStatus;
  bit           SuccessFlag     = EE_RSCAN_OK;

  SuccessFlag = EE_AS_RSCAN_BasicTest( );

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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

bit ApplRSCANRAMTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCAN_OK;
  int           Unit            = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;

  if( SuccessFlag == EE_RSCAN_OK ) {
    
    SuccessFlag = EE_RSCAN_RAMTestApp( ( u08 )Unit );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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
ApplRSCANBasicTestTx( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCAN_OK;
  int           Unit_1          = 0;
  int           Machine_1       = 0;


  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT,
				    &Unit_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINE,
				    &Machine_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;

  if( SuccessFlag == EE_RSCAN_OK ) {

    SuccessFlag = EE_RSCAN_BasicTest_Tx( ( u08 )Unit_1, 
                                         ( u08 )Machine_1 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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
ApplRSCANBasicTestRx( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCAN_OK;
  int           Unit_1          = 0;
  int           Machine_1       = 0;


  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT,
				    &Unit_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINE,
				    &Machine_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;

  if( SuccessFlag == EE_RSCAN_OK ) {

    SuccessFlag = EE_RSCAN_BasicTest_Rx( ( u08 )Unit_1, 
                                         ( u08 )Machine_1 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST7

bit
ApplRSCANSelfTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCAN_OK;
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
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN2,
				    &Machine_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;

  if( SuccessFlag == EE_RSCAN_OK ) {

    SuccessFlag = EE_RSCAN_BasicSelfTest( ( u08 )Unit_1, 
                                          ( u08 )Machine_1, 
                                          ( u08 )Machine_2 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST8

bit
ApplRSCANPartialNWTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCAN_OK;
  int           Unit_1          = 0;
  int           Machine_1       = 0;


  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT,
				    &Unit_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINE,
				    &Machine_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;

  if( SuccessFlag == EE_RSCAN_OK ) {

    SuccessFlag = EE_RSCAN_CANFD_PNW_Test( ( u08 )Unit_1, 
                                           ( u08 )Machine_1 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST9

bit
ApplRSCANIntSelfTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_RSCAN_OK;
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
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_RSCAN_ERROR;

  if( SuccessFlag == EE_RSCAN_OK ) {

    SuccessFlag = EE_RSCAN_BasicIntSelfTest( ( u08 )Unit_1, 
                                             ( u08 )Machine_1 );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_RSCAN_OK ) {
    
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

bit ASMN_RSCANApplications( u08 MenuCom )
{
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
      UARTStatus = ApplRSCANReset( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST2
    case ASMN_MENUCODE_TEST2:
      UARTStatus = ApplRSCANBasicTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST3
    case ASMN_MENUCODE_TEST3:
      UARTStatus = ApplRSCANASBasicTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST4
    case ASMN_MENUCODE_TEST4:
      UARTStatus = ApplRSCANRAMTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST5
    case ASMN_MENUCODE_TEST5:
      UARTStatus = ApplRSCANBasicTestTx( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST6
    case ASMN_MENUCODE_TEST6:
      UARTStatus = ApplRSCANBasicTestRx( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST7
    case ASMN_MENUCODE_TEST7:
      UARTStatus = ApplRSCANSelfTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST8
    case ASMN_MENUCODE_TEST8:
      UARTStatus = ApplRSCANPartialNWTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST9
    case ASMN_MENUCODE_TEST9:
      UARTStatus = ApplRSCANIntSelfTest( MenuCom );
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
