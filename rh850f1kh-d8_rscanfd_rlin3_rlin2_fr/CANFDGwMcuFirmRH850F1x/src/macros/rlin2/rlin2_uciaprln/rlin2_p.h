//============================================================================
// PROJECT = RSCAN Type RLIN2_UCIAPRLN
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RLIN2 Low Level Driver Function Include
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
//referred to the User by Renesas in connection with the Product(s) and/or the 
//Application.
//
//============================================================================
// Environment: Devices:          All featuring RLIN2_UCIAPRLN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#ifndef _RLIN2_UCIAPRLN_P_H
#define _RLIN2_UCIAPRLN_P_H
                   
#include <ree_types.h>

/*
 * Global Variables Sharing
 */

extern u08 RLIN2_InterruptFlagType_u08;    /* interrupt resolution */
extern u08 RLIN2_InterruptFlagChannel_u08;
extern u08 RLIN2_InterruptFlagUnit_u08;

extern bit
RLIN2_PortEnable( u08 UnitNumber_u08,
                  u08 ChannelNumber_u08 );

extern bit
RLIN2_PortDisable( u08 UnitNumber_u08,
                   u08 ChannelNumber_u08 );

extern bit
RLIN2_Reset( u08 UnitNumber_u08 );

extern bit
RLIN2_CreateInterrupt( u08 UnitNumber_u08,
                       u08 ChannelNumber_u08,
                       u08 InterruptSource_u08,
                       u08 InterruptLevel_u08,
                       void ( *FunctionVector )( ) );

extern 
bit RLIN2_LINSetConfig( u08 UnitNumber_u08,
                        u08 ChannelNumber_u08,
                        flt Oscillator_Frequency_flt,
                        u08 LINStandard_u08,
                        u32 Baudrate_u32,
                        u08 ClockSelection_u08,
                        u08 BreakLength_u08,
                        u08 BreakDelimiter_u08,
                        u08 HeaderSpace_u08,
                        u08 InterByteSpace_u08 );

extern
bit RLIN2_LINSendMessage( u08  UnitNumber_u08,
                          u08  ChannelNumber_u08,
                          u08  PID_u08,
                          u08  MessageLength_u08,
                          u08  EnhancedCheckSum_u08,
                          u08  Direction_u08,
                          pu08 Data_pu08 );

extern
bit RLIN2_LINEnableInterrupt( u08 UnitNumber_u08,
                              u08 ChannelNumber_u08,
                              u08 Transmit_u08,
                              u08 Receive_u08,
                              u08 ErrorGlobal_u08,
                              u08 ErrorBit_u08,
                              u08 ErrorPhyBus_u08,
                              u08 ErrorTimeout_u08,
                              u08 ErrorFrame_u08 );

extern
bit RLIN2_LINGetStatus( u08  UnitNumber_u08,
                        u08  ChannelNumber_u08,
                        pu08 NoAction_pu08,
                        pu08 HeaderComplete_pu08,
                        pu08 DataReceived_pu08,
                        pu08 DataTransmitted_pu08,
                        pu08 PID_pu08 );

extern
bit RLIN2_LINGetError( u08  UnitNumber_u08,
                       u08  ChannelNumber_u08,
                       pu08 AnyError_pu08,
                       pu08 BitError_pu08,
                       pu08 DataConsistencyError_pu08,
                       pu08 TimeoutError_pu08,
                       pu08 FrameError_pu08,
                       pu08 CheckSumError_pu08 );

extern
bit RLIN2_LINReceiveMessage( u08  UnitNumber_u08,
                             u08  ChannelNumber_u08,
                             u08  MessageLength_u08,
                             pu08 Data_pu08 );

extern
bit RLIN2_LINSendWakeup( u08 UnitNumber_u08,
                         u08 ChannelNumber_u08,
                         u08 WakeupLength_u08 );
                         
extern
bit RLIN2_LINReceiveWakeup( u08 UnitNumber_u08,
                            u08 ChannelNumber_u08 );

extern
bit RLIN2_LINRestart( u08 UnitNumber_u08,
                      u08 ChannelNumber_u08 );

#endif
