//============================================================================
// PROJECT  : REE FlexRay driver 
// MODULE   : flexray_test_mode.c
// VERSION  : 0.2
// DATE     : 02.10.2013
//============================================================================
//                           C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2013 by REE Electronics (Europe) GmbH. All rights reserved.
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
// Enviroment : Devices    : RH850/P1x-C
//              Assembler  : GHS Multi              Version : 6.1.4
//              C-Compiler : GHS Multi              Version : 6.1.4
//              Linker     : GHS Multi              Version : 6.1.4       
//              Debugger   : GHS Multi              Version : 6.1.4
//============================================================================
// Version    Author                       Description
// 0.1        H.Schmerling                 Initial Release
// 0.2        P.Szczupak                   Modified for P1x-C device
//============================================================================
// Includes                                                                  
//============================================================================
#include "FrDrv.h"
#include "GlobalDefines.h"
#include "TypeDefines.h"

//============================================================================
// Prototypes
//============================================================================
 void FrDrv_write_GIO ( u16 data_u08 ); 
void FrDrv_test_unlock_seq ( void );
void FrDrv_test_register_enable ( void );
u08 FrDrv_normal_operation_test_mode ( void );
u08 FrDrv_ram_test_mode ( void );
u08 FrDrv_asynron_transmit_test_mode ( void );
u08 FrDrv_loop_back_test_mode ( void );
u08 FrDrv_IO_test_mode ( void );

//============================================================================
// Functions
//============================================================================


void FrDrv_write_GIO ( u16 data_u16 ) { 
//=============================================================================
// FunctionName: FrDrv_write_GIO
// IN: data
// OUT: - 
// Description: Special function for the E-Ray with FPGA, turns the LEDs on
//============================================================================= 
 
  //FrDrv_write_16bit ( CR4_REG, data_u16 );
  FrDrv_write_32bit ( CR4_REG, 0x00000000 + data_u16 );
}


void FrDrv_test_unlock_seq ( void ) { 
//=============================================================================
// FunctionName: FrDrv_test_unlock_seq
// IN: -
// OUT: -
// Description: Unlock sequence for the test mode
//=============================================================================

//FrDrv_write_16bit ( LCK_REG, 0x7500 );
//FrDrv_write_16bit ( LCK_REG, 0x8A00 );
FrDrv_write_32bit ( LCK_REG, 0x00007500 );
FrDrv_write_32bit ( LCK_REG, 0x00008A00 );

}

void FrDrv_test_register_enable ( void ) {
//=============================================================================
// FunctionName: FrDrv_test_register_enable
// IN: -
// OUT: -
// Description: Enables test mode
//=============================================================================
  u32 value_u32;

   FrDrv_test_unlock_seq ( );

  value_u32 = FrDrv_read_32bit ( TEST1_REG ) | 0x1;
  FrDrv_write_32bit ( TEST1_REG, value_u32 );
}

u08 FrDrv_normal_operation_test_mode ( void ) {
//=============================================================================
// FunctionName: FrDrv_normal_operation_test_mode
// IN: -
// OUT: REE FlexRay return value
// Description: Normal operation test mode
//=============================================================================
  u32 value_u32;

  FrDrv_test_register_enable ( );

  value_u32 = FrDrv_read_32bit ( TEST1_REG ) & ~0x00000070;
  FrDrv_write_32bit ( TEST1_REG, value_u32 );
   
  return FrDrv_state_1 ( );   
}

u08 FrDrv_ram_test_mode ( void ) {
//=============================================================================
// FunctionName: FrDrv_ram_test_mode
// IN: -
// OUT: REE FlexRay return value
// Description: RAM test mode
//============================================================================= 
  u32 value_u32;

  FrDrv_test_register_enable ( );

  value_u32 = FrDrv_read_32bit ( TEST1_REG ) & ~0x00000070;
  value_u32 |= 0x00000010;
  FrDrv_write_32bit ( TEST1_REG, value_u32 );

  return FrDrv_state_1 ( );
}

u08 FrDrv_loop_back_test_mode ( void ) {
//=============================================================================
// FunctionName: FrDrv_loop_back__test_mode
// IN: -
// OUT: REE FlexRay return value
// Description: Loop bakc mode
//============================================================================= 
  
  FrDrv_test_register_enable ( );
  FrDrv_unlock_seq_CONF ( );
  FrDrv_send_command ( LOOP_BACK_MODE );

  return FrDrv_state_1 ( );
}

u08 FrDrv_IO_test_mode ( void ) {
//=============================================================================
// FunctionName: FrDrv_IO_test_mode
// IN: -
// OUT: REE FlexRay return value
// Description: IO_test_mode
//============================================================================= 
  u32 value_u32;

  FrDrv_test_register_enable ( );

  value_u32 = FrDrv_read_32bit ( TEST1_REG ) & ~0x00000070;
  value_u32 |= 0x00000030;
  FrDrv_write_32bit ( TEST1_REG, value_u32 );

  return FrDrv_state_1 ( );   
}

// end of file
