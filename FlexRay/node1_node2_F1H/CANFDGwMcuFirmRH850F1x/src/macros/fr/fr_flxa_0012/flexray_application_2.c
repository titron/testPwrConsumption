//============================================================================
// PROJECT  : REE FlexRay controller evalutation
// MODULE   : flexray_application_1.c
// VERSION  : 0.2
// DATE     : 21.05.2014
//============================================================================
//                           C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by REE Electronics (Europe) GmbH. All rights reserved.
// Arcadiastr. 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by REE, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. REE shall not have any obligation to maintain,
// service or provide bug fixes for the supplied Product(s) and/or the
// Application.
//
// Each User is solely responsible for determining the appropriateness of
// using the Product(s) and assumes all risks associated with its exercise
// of rights under this Agreement, including, but not limited to the risks
// and costs of program errors, compliance with applicable laws, damage to
// or loss of data, programs or equipment, and unavailability or
// interruption of operations.
//
// Limitation of Liability :
// In no event shall REE be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. REE shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by REE in connection with the Product(s) and/or the
// Application.
//
//============================================================================
// Enviroment : Devices    : RH850/P1x
//              Assembler  : GHS Multi              Version : 6.1.4
//              C-Compiler : GHS Multi              Version : 6.1.4
//              Linker     : GHS Multi              Version : 6.1.4
//              Debugger   : GHS Multi              Version : 6.1.4
//============================================================================
// Version    Author                       Description
// 0.1        P.Szczupak                   Initial Release
// 0.2        P.Szczupak                   Modified for P1x device
//============================================================================


//============================================================================
// Includes
//============================================================================

#include <map_fr.h>
#include "GlobalDefines.h"
#include "TypeDefines.h"
#include "FrDrv.h"

//============================================================================
// Prototypes
//============================================================================
void application_start_2 ( void );
void application_2 ( void );

// from flexray_application_common.c
extern void wait_ms ( u16 time_u16 );
extern void wait_us ( u16 time_u16 );
// from FrDrv_state.c
extern void FrDrv_unlock_seq_CONF ( void );
extern u08  FrDrv_send_command ( u08 command_u08 );
extern void FrDrv_Interrupt_clear ( void );
extern void FrDrv_Interrupt_Line0_enable ( void );
extern void FrDrv_Interrupt_Line1_enable ( void );
extern void FrDrv_Start_timer0 ( void );
extern void FrDrv_Start_timer1 ( void );
#ifdef RH850
  extern void FrDrv_Timer0_Interrupt_enable ( void );
  extern void FrDrv_Timer0_Status_clear     ( void );
#endif
// from FrDrv_error_status_signaling.c
extern Fr_ReturnType FrDrv_state_1 ( void );
// from FrDrv_data_transfer.c
extern Fr_ReturnType FrDrv_data_HOST_to_IB ( u32 *data_u32, u08 data_words_u08 );
extern Fr_ReturnType FrDrv_data_IB_to_TRAM ( u08 mb_u08 );
extern Fr_ReturnType FrDrv_data_MB_to_OBF ( u08 mb_u08 );
extern Fr_ReturnType FrDrv_data_OBF_to_HOST ( u32 *data_u32, u08 data_words_u08 );

//============================================================================
// Global variables
//============================================================================
extern const u16 BufferHeader_u16[128][10];

//============================================================================
// Functions
//============================================================================

void application_start_2 ( void ) {
//=============================================================================
// FunctionName:
// IN :
// OUT :
// Description :
// Version:
//=============================================================================

  wait_ms(5);

  //leave config mode
  FrDrv_unlock_seq_CONF ( );

  FrDrv_send_command ( READY );
  //wait until FrDrv is in READY
  while ( FrDrv_state_1 ( ) != (Fr_ReturnType) READY_STATE  ) {
  }

  FrDrv_send_command ( RUN );
  FrDrv_send_command ( ALLOW_COLDSTART );
//wait until FrDrv is in NORMAL_ACTIVE_STATE or NORMAL_PASSIVE_STATE
  while ( ( FrDrv_state_1 ( ) != (Fr_ReturnType) NORMAL_ACTIVE_STATE  ) ) {
  }

  FrDrv_Interrupt_clear ( );
#ifdef RH850
  FrDrv_Timer0_Status_clear ( );
#endif
  //=============================================================================
  FrDrv_Interrupt_Line0_enable ( );
  FrDrv_Interrupt_Line1_enable ( );
#ifdef RH850
  //FrDrv_Timer0_Interrupt_enable ( );
#endif
  //FrDrv_Start_timer0 ( );
  //FrDrv_Start_timer1 ( );

  application_2( );
}

void application_2 ( void ) {
//=============================================================================
// FunctionName:
// IN :
// OUT :
// Description :
// Version:
//=============================================================================
  static u16 result_u16 = 0;
  static u16 result_old_u16 = 0;
  u32 data_u32[64];
  u08 data_words_u08 = 1;

#ifndef __TEST_FLX_COM//original settings@Titron
  data_u32[0] = 0x3333;
#else
  data_u32[0] = 0x0;
#endif
  FrDrv_data_HOST_to_IB ( &data_u32[0], data_words_u08 );
  FrDrv_data_IB_to_TRAM ( MB0 );

#ifndef __TEST_FLX_COM//original settings@Titron
  data_u32[1] = 0x7777;
#else
  data_u32[1] = 0x0;
#endif
  FrDrv_data_HOST_to_IB ( &data_u32[1], data_words_u08 );
  FrDrv_data_IB_to_TRAM ( MB3 );

#ifndef __TEST_FLX_COM//original settings@Titron
  data_u32[2] = 0xBBBB;
#else
  data_u32[2] = 0x0;
#endif
  FrDrv_data_HOST_to_IB ( &data_u32[2], data_words_u08 );
  FrDrv_data_IB_to_TRAM ( MB5 );

#ifndef __TEST_FLX_COM//original settings@Titron
  data_u32[3] = 0xF1F1;
#else
  data_u32[3] = 0x0;
#endif
  FrDrv_data_HOST_to_IB ( &data_u32[3], data_words_u08 );
  FrDrv_data_IB_to_TRAM ( MB7 );
  
  // Receive frame from node1
  if ( FrDrv_data_MB_to_OBF ( MB1 ) != MESSAGE_BUFFER_NO_DATA ) {
    result_old_u16 = result_u16;

    FrDrv_data_OBF_to_HOST ( &data_u32[4], data_words_u08 );

  // compare received data of frame 1 in output buffer
  data_u32[4] &= 0x0000FFFF;
#ifndef __TEST_FLX_COM//original settings@Titron
  if ( data_u32[4] != 0x1111)
#else
  if ( data_u32[4] != 0x0)
#endif
    { result_u16++;
    }
  }
   // Receive frame from node1
  if ( FrDrv_data_MB_to_OBF ( MB2 ) != MESSAGE_BUFFER_NO_DATA ) {
    result_old_u16 = result_u16;

    FrDrv_data_OBF_to_HOST ( &data_u32[5], data_words_u08 );
// compare received data of frame 5 in output buffer
  data_u32[5] &= 0x0000FFFF;
#ifndef __TEST_FLX_COM//original settings@Titron
  if ( data_u32[5] != 0x5555)
#else
  if ( data_u32[5] != 0x0)
#endif
    { result_u16++;
    }
  }

   // Receive frame from node1
  if ( FrDrv_data_MB_to_OBF ( MB4 ) != MESSAGE_BUFFER_NO_DATA ) {
    result_old_u16 = result_u16;

    FrDrv_data_OBF_to_HOST ( &data_u32[6], data_words_u08 );
// compare received data of frame 9 in output buffer
  data_u32[6] &= 0x0000FFFF;
#ifndef __TEST_FLX_COM//original settings@Titron
  if ( data_u32[6] != 0x9999)
#else
  if ( data_u32[6] != 0x0)
#endif
    { result_u16++;
    }
  }

   // Receive frame from node1
  if ( FrDrv_data_MB_to_OBF ( MB6 ) != MESSAGE_BUFFER_NO_DATA ) {
    result_old_u16 = result_u16;

    FrDrv_data_OBF_to_HOST ( &data_u32[7], data_words_u08 );
// compare received data of frame 13 in output buffer
  data_u32[7] &= 0x0000FFFF;
#ifndef __TEST_FLX_COM//original settings@Titron
  if ( data_u32[7] != 0xDDDD)
#else
  if ( data_u32[7] != 0x0)
#endif
    { result_u16++;
    }
  }

   // Receive frame from node1
  if ( FrDrv_data_MB_to_OBF ( MB8 ) != MESSAGE_BUFFER_NO_DATA ) {
    result_old_u16 = result_u16;

    FrDrv_data_OBF_to_HOST ( &data_u32[8], data_words_u08 );
// compare received data of frame 17 in output buffer
  data_u32[8] &= 0x0000FFFF;
#ifndef __TEST_FLX_COM//original settings@Titron
  if ( data_u32[8] != 0xF2F2)
#else
  if ( data_u32[8] != 0x0)
#endif
    { result_u16++;
    }
  }

  wait_us (400);                    //***RLI: removed as it is blocking in interrupt context

}

// end of file


