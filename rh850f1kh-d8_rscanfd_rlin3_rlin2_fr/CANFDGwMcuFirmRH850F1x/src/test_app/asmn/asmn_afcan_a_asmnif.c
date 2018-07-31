//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 602 $
// DATE    = $Date: 2009-02-09 16:15:32 +0100 (Mo, 09 Feb 2009) $
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2002 by NEC Electronics (Europe) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: AFCAN Application Interface
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
//
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
// Revision 1.3  2006/01/31 12:58:51  liederr
// Added AFCAN Sleep Mode Test
//
// Revision 1.2  2004/02/09 14:29:48  liederr
// Additional aFCAN tests: Receiving, Power Saving, Buffer Reading.
//
// Revision 1.1  2003/12/11 13:58:45  liederr
// Initial creation.
//
//
//============================================================================

#include <stddef.h>
#include <stdio.h>
#include <ree_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#if( defined( EE_AFCAN_MACROS ) || defined( AFCAN_MACROS ) )

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

/* AFCAN Driver Interface */
#include <map_afcan.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "FCAN APPLICATION MENU\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 06/1999    \n\n"
#define ASMN_MENULINE_MEN0  " 0 -> Exit\n"
#if( EE_AFCAN_TYPE == QLNPUAFC0A10V1 )
#define ASMN_MENULINE_MEN1  " 1 -> Reset AFCAN\n"
#define ASMN_MENULINE_MEN3  " 3 -> Single Channel Operation Test\n"
#define ASMN_MENULINE_MEN4  " 4 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN5  " 5 -> Arbitration Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN6  " 6 -> ABT Mode Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN10 "10 -> Reception Test (Buffer Setup)\n"
#define ASMN_MENULINE_MEN11 "11 -> Reception Test (Buffer Read)\n"
#define ASMN_MENULINE_MEN20 "20 -> AFCAN Power Save Entry\n"
#define ASMN_MENULINE_MEN21 "21 -> AFCAN Sleep Mode Test\n"
#endif

#if( EE_AFCAN_TYPE == QLNPUAFC0A12V1 )
#define ASMN_MENULINE_MEN1  " 1 -> Reset AFCAN\n"
#define ASMN_MENULINE_MEN3  " 3 -> Single Channel Operation Test\n"
#define ASMN_MENULINE_MEN4  " 4 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN5  " 5 -> Arbitration Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN6  " 6 -> ABT Mode Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN7  " 7 -> DIAG Mirror Mode Test\n"
#define ASMN_MENULINE_MEN10 "10 -> Reception Test (Buffer Setup)\n"
#define ASMN_MENULINE_MEN11 "11 -> Reception Test (Buffer Read)\n"
#define ASMN_MENULINE_MEN20 "20 -> AFCAN Power Save Entry\n"
#define ASMN_MENULINE_MEN21 "21 -> AFCAN Sleep Mode Test\n"
#endif

#if( EE_AFCAN_TYPE == QLAPBAFC0C1xV1 )
#define ASMN_MENULINE_MEN1  " 1 -> Reset AFCAN\n"
#define ASMN_MENULINE_MEN2  " 2 -> Read Configuration\n"
#define ASMN_MENULINE_MEN3  " 3 -> Single Channel Operation Test\n"
#define ASMN_MENULINE_MEN4  " 4 -> Basic Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN5  " 5 -> Arbitration Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN6  " 6 -> ABT Mode Test: Sending and Receiving\n"
#define ASMN_MENULINE_MEN7  " 7 -> DIAG Mirror Mode Test\n"
#define ASMN_MENULINE_MEN8  " 8 -> Mask Test\n"
#define ASMN_MENULINE_MEN9  " 9 -> Transmit Abort Test\n"
#define ASMN_MENULINE_MEN10 "10 -> Reception Test (Buffer Setup)\n"
#define ASMN_MENULINE_MEN11 "11 -> Reception Test (Buffer Read)\n"
#define ASMN_MENULINE_MEN20 "20 -> AFCAN Power Save Entry\n"
#define ASMN_MENULINE_MEN21 "21 -> AFCAN Sleep Mode Test\n"
#define ASMN_MENULINE_MEN30 "30 -> Error Level Test\n"
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
#define ASMN_MENUINPUT_FREQSEL   "\n Enter MCS+MCP Value [0-15]: "
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
#define ASMN_MENUINPUT_DIAGBUS   "\n Enter Diag Bus Input [0-7] "
#define ASMN_MENUINPUT_BUFR      "\n Enter Receiving Buffer [0...] "
#define ASMN_MENUINPUT_POWERSAVE "\n Enter Power Save Mode [0=ACTIVE,1=SLEEP,3=STOP] "
#define ASMN_MENUINPUT_REMOTEFLG "\n Enter Remote Frame Usage [0=DATA-FRAMES,1=REMOTE-FRAMES] "
#define ASMN_MENUINPUT_ERRORMASK "\n Enter Error Mask [1CH = all on] "

#define ASMN_MENUOUTPUT_RDCFG    "\n Config Values: Global: %04x H, Bitrate: %x H \n"

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK   1
#define ASMN_MENUCODE_NOCMD   -1
#define ASMN_MENUCODE_EXIT     0
#define ASMN_MENUCODE_BACK     0

#if( EE_AFCAN_TYPE == QLNPUAFC0A10V1 )
#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST3    3
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST5    5
#define ASMN_MENUCODE_TEST6    6
#define ASMN_MENUCODE_TEST10   10
#define ASMN_MENUCODE_TEST11   11
#define ASMN_MENUCODE_TEST20   20
#define ASMN_MENUCODE_TEST21   21
#endif

#if( EE_AFCAN_TYPE == QLNPUAFC0A12V1 )
#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST3    3
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST5    5
#define ASMN_MENUCODE_TEST6    6
#define ASMN_MENUCODE_TEST7    7
#define ASMN_MENUCODE_TEST10   10
#define ASMN_MENUCODE_TEST11   11
#define ASMN_MENUCODE_TEST20   20
#define ASMN_MENUCODE_TEST21   21
#endif

#if( EE_AFCAN_TYPE == QLAPBAFC0C1xV1 )
#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST2    2
#define ASMN_MENUCODE_TEST3    3
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST5    5
#define ASMN_MENUCODE_TEST6    6
#define ASMN_MENUCODE_TEST7    7
#define ASMN_MENUCODE_TEST8    8
#define ASMN_MENUCODE_TEST9    9
#define ASMN_MENUCODE_TEST10   10
#define ASMN_MENUCODE_TEST11   11
#define ASMN_MENUCODE_TEST20   20
#define ASMN_MENUCODE_TEST21   21
#define ASMN_MENUCODE_TEST30   30
#endif

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
ApplAFCANReset( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Unit            = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {
    
    SuccessFlag = EE_AFCAN_Reset( ( u08 )Unit );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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
ApplAFCANReadConfig( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Unit            = 0;
  int           Machine         = 0;
  int           GlobalConfig    = 0;
  int           BitRateConfig   = 0;
  char          PrintString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_MACHINE,
				                    &Machine,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {
    
    SuccessFlag = EE_AFCAN_ReadConfig( ( u08 )Unit,
                                    ( u08 )Machine,
                                    ( pu16 )( &GlobalConfig ),
                                    ( pu16 )( &BitRateConfig ) );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  sprintf( PrintString, ASMN_MENUOUTPUT_RDCFG, ( unsigned int )GlobalConfig,
                                               ( unsigned int )BitRateConfig );

  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, PrintString,
                                    ASMN_UARTMODECRLF );

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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
ApplAFCANOperationTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Unit            = 0;
  int           Machine         = 0;
  unsigned long CANFrequency    = 0L;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT1,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_MACHINE,
				                    &Machine,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                     ASMN_MENUINPUT_BAUDSEL,
                                     &CANFrequency,
                                     &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {
    
    SuccessFlag = EE_AFCAN_OperateTest( ( u08 )Unit,
                                     ( u08 )Machine,
                                     ( u32 )( CANFrequency ) );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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
ApplAFCANBasicTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Cycles          = -1;
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
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN2,
				    &Machine_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_ECYCLES,
				    &Cycles,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_BasicTest( ( u08 )Unit_1, 
                                   ( u08 )Unit_2,
                                   ( u08 )Machine_1, 
                                   ( u08 )Machine_2,
                                   Cycles );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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
ApplAFCANArbitrateTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Cycles          = -1;
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
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN2,
				    &Machine_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_ECYCLES,
				    &Cycles,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_ArbitrateTest( ( u08 )Unit_1,    ( u08 )Unit_2, 
                                       ( u08 )Machine_1, ( u08 )Machine_2, 
                                       Cycles );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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
ApplAFCANABTModeTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Cycles          = -1;
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
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN2,
				    &Machine_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_ECYCLES,
				    &Cycles,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_ABTModeTest( ( u08 )Unit_1,    ( u08 )Unit_2, 
                                     ( u08 )Machine_1, ( u08 )Machine_2, 
                                     Cycles );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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
ApplAFCANMirrorModeTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState        = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag      = EE_AFCAN_OK;
  int           FrequencySelect  = -1;
  int           FrequencySelectM = -1;
  int           Unit_s           = 0;
  int           Unit_r           = 1;
  int           Unit_m           = 4;
  int           Unit_mr          = 3;
  int           Machine_s        = 0;
  int           Machine_r        = 0;
  int           Machine_m        = 0;
  int           Machine_mr       = 0;
  int           Diagbus          = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITS,
				    &Unit_s,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITR,
				    &Unit_r,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITM,
				    &Unit_m,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITMR,
				    &Unit_mr,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINS,
				    &Machine_s,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINR,
				    &Machine_r,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINM,
				    &Machine_m,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINMR,
				    &Machine_mr,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_DIAGBUS,
				    &Diagbus,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_DiagMirrorTest( ( u08 )Unit_s,    ( u08 )Machine_s, 
                                        ( u08 )Unit_r,    ( u08 )Machine_r, 
                                        ( u08 )Unit_m,    ( u08 )Machine_m, 
                                        ( u08 )Unit_mr,   ( u08 )Machine_mr, 
                                        ( u08 )Diagbus );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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

bit ApplAFCANMaskTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           RemoteMsgFlag   = 0;
  int           Unit_1          = 0;
  int           Unit_2          = 1;
  int           Machine_1       = 0;
  int           Machine_2       = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITS,
				    &Unit_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITR,
				    &Unit_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINS,
				    &Machine_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINR,
				    &Machine_2,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_REMOTEFLG,
				    &RemoteMsgFlag,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_MaskTest( ( u08 )Unit_1,    ( u08 )Unit_2, 
                                  ( u08 )Machine_1, ( u08 )Machine_2, 
                                  ( u08 )RemoteMsgFlag );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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
ApplAFCANTxAbortTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Unit            = 0;
  int           Machine         = 0;
  int           HUnit           = 1;
  int           HMachine        = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINE,
				    &Machine,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNITH,
				                    &HUnit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINH,
				    &HMachine,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {
    
    SuccessFlag = EE_AFCAN_TxAbortTest( ( u08 )Unit, ( u08 )Machine,
                                     ( u08 )HUnit, ( u08 )HMachine );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST10

bit
ApplAFCANReceiveTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Unit            = 0;
  int           Machine         = 0;
  int           Buffer          = 0;
  unsigned long StandardID      = 0L;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITR,
				    &Unit,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINR,
				    &Machine,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_BUFR,
				    &Buffer,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                     ASMN_MENUINPUT_ID,
                                     &StandardID,
                                     &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  
  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_ReceiveTest( ( u08 )Unit,
                                     ( u08 )Machine,
                                     ( u08 )Buffer,
                                     ( u32 )StandardID );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST11

bit
ApplAFCANReadBufferTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Unit            = 0;
  int           Machine         = 0;
  int           Buffer          = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITR,
				    &Unit,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINR,
				    &Machine,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_BUFR,
				    &Buffer,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  
  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_ReadBufferTest( ( u08 )Unit,
                                        ( u08 )Machine,
                                        ( u08 )Buffer );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST20

bit
ApplAFCANPowerSaveTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Unit            = 0;
  int           Machine         = 0;
  int           PowerSaveMode   = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNITR,
				    &Unit,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINR,
				    &Machine,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_POWERSAVE,
				    &PowerSaveMode,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  
  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_PowerSaveTest( ( u08 )Unit,
                                       ( u08 )Machine,
                                       ( u08 )PowerSaveMode );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST21

bit
ApplAFCANWakeupTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Unit            = 0;
  int           Machine         = 0;
  int           RunCount        = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT,
				    &Unit,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHINE,
				    &Machine,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_CYCLES,
				    &RunCount,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  
  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_WakeupTest( ( u08 )Unit,
                                    ( u08 )Machine,
                                    RunCount );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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

#ifdef ASMN_MENUCODE_TEST21

bit
ApplAFCANErrorLevelTest( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = EE_AFCAN_OK;
  int           Cycles          = -1;
  int           Unit_1          = 0;
  int           Machine_1       = 0;
  int           ErrorMask       = 0x1C;


  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_UNIT1,
				    &Unit_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_MACHIN1,
				    &Machine_1,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_ERRORMASK,
				    &ErrorMask,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_ECYCLES,
				    &Cycles,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_AFCAN_ERROR;

  if( SuccessFlag == EE_AFCAN_OK ) {

    SuccessFlag = EE_AFCAN_ErrorLevelTest( ( u08 )Unit_1, 
                                        ( u08 )Machine_1,
                                        ( u08 )ErrorMask,
                                        Cycles );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_AFCAN_OK ) {
    
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

bit ASMN_AFCANApplications( u08 MenuCom )
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
      UARTStatus = ApplAFCANReset( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST2
    case ASMN_MENUCODE_TEST2:
      UARTStatus = ApplAFCANReadConfig( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST3
    case ASMN_MENUCODE_TEST3:
      UARTStatus = ApplAFCANOperationTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST4
    case ASMN_MENUCODE_TEST4:
      UARTStatus = ApplAFCANBasicTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST5
    case ASMN_MENUCODE_TEST5:
      UARTStatus = ApplAFCANArbitrateTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST6
    case ASMN_MENUCODE_TEST6:
      UARTStatus = ApplAFCANABTModeTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST7
    case ASMN_MENUCODE_TEST7:
      UARTStatus = ApplAFCANMirrorModeTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST8
    case ASMN_MENUCODE_TEST8:
      UARTStatus = ApplAFCANMaskTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST9
    case ASMN_MENUCODE_TEST9:
      UARTStatus = ApplAFCANTxAbortTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST10
    case ASMN_MENUCODE_TEST10:
      UARTStatus = ApplAFCANReceiveTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST11
    case ASMN_MENUCODE_TEST11:
      UARTStatus = ApplAFCANReadBufferTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST20
    case ASMN_MENUCODE_TEST20:
      UARTStatus = ApplAFCANPowerSaveTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST21
    case ASMN_MENUCODE_TEST21:
      UARTStatus = ApplAFCANWakeupTest( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_TEST30
    case ASMN_MENUCODE_TEST30:
      UARTStatus = ApplAFCANErrorLevelTest( MenuCom );
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
