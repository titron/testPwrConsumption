//============================================================================
// PROJECT = RSCFD Type RSCFD_UCIAPRCN
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2015 by Renesas Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RSCFD Driver Functions Include
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
// Environment: Devices:          All featuring RSCFD_UCIAPRCN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#ifndef _RSCFD_P_H
#define _RSCFD_P_H

#include <ree_types.h>

extern bit EE_RSCFD_PortEnable( u08 UnitNumber_u08,
                                u08 ChannelNumber_u08 );
extern bit EE_RSCFD_PortDisable( u08 UnitNumber_u08,
                                 u08 ChannelNumber_u08 );

extern bit EE_RSCFD_CreateInterrupt( u08  UnitNumber_u08,
                                     u08  ChannelNumber_u08,
                                     u08  IntNumber_u08,
                                     u16  SetIntLevel_u16,
                                     void ( *FunctionVector )( ) );
extern bit EE_RSCFD_SetInterrupt( u08 UnitNumber_u08,
                                  u08 ChannelNumber_u08,
                                  u08 InterruptSelection_u08,
                                  u16 InterruptSubSelection_u08 );
                                  
extern bit EE_RSCFD_GetError( u08  UnitNumber_u08,
                              u08  ChannelNumber_u08,
                              pu16 InterruptErrorFlag_pu16,
                              pu16 LastErrorFlag_pu16 );
                             
extern bit EE_RSCFD_GetStatus( u08  UnitNumber_u08,
                           	   u08  ChannelNumber_u08,
                     		       u08  StatusNumber_u08,
                     		       pu16 StatusValue_pu16 );
                     		       
extern bit EE_RSCFD_GetFIFOStatus( u08  UnitNumber_u08,
                                   u08  ChannelNumber_u08,
                                   u08  FIFONumber_u08,
                                   u08  StatusType_u08,
                                   pu08 StatusValue_pu08 );

extern bit EE_RSCFD_Start( u08 UnitNumber_u08,
                           u08 ChannelNumber_u08,
                           u08 OperationMode_u08,
                           u08 ClearErrorCounter_u08,
                           u16 TimeStampSetting_u16 );
                           
extern bit EE_RSCFD_Stop( u08 UnitNumber_u08,
                          u08 ChannelNumber_u08,
                          u08 StopMode_u08 );

extern bit EE_RSCFD_SetGlobalConfiguration( u08 UnitNumber_u08,
                                            const struct ee_rscfd_cfg_global *Config );

extern bit EE_RSCFD_SetChannelConfiguration( u08 UnitNumber_u08,
                                             u08 ChannelNumber_u08,
                                             const struct ee_rscfd_cfg_channel *Config );

extern bit EE_RSCFD_SetGlobalFIFOConfiguration( u08 Unit_u08, 
                                                const struct ee_rscfd_cfg_global *Config );

extern bit EE_RSCFD_SetCOMFIFOConfiguration( u08 UnitNumber_u08,
                                             u08 ChannelNumber_u08,
                                             const struct ee_rscfd_cfg_channel *Config );

extern bit EE_RSCFD_EnableCOMFIFO( u08 UnitNumber_u08,
                                   u08 ChannelNumber_u08,
                                   u08 FIFONumber_u08,
                                   u08 EnableFlag_u08 );

extern bit EE_RSCFD_EnableRXFIFO( u08 UnitNumber_u08,
                                  u08 FIFONumber_u08,
                                  u08 EnableFlag_u08 );

extern bit EE_RSCFD_SendMessage( u08  UnitNumber_u08,
                                 u08  ChannelNumber_u08,
                                 pu08 Status_pu08,
                                 struct ee_rscfd_message *Message );

extern bit EE_RSCFD_TxAbort( u08  UnitNumber_u08,
                             u08  ChannelNumber_u08,
                             struct ee_rscfd_message *Message );
  
extern bit EE_RSCFD_ReceiveMessage( u08  UnitNumber_u08,
                                    pu08 Status_pu08,
                                    struct ee_rscfd_message *Message );

extern bit EE_RSCFD_GetTimeStampCounter( u08  UnitNumber_u08,
                                         pu32 TimeStampValue_pu32 );

extern bit EE_RSCFD_SetAFLEntry( u08  UnitNumber_u08,
                                 u08  ChannelNumber_u08,
																 u16  RuleNumber_u16,																 
                                 struct ee_rscfd_a_afl *AFLEntry );

extern bit EE_RSCFD_RAMTest( u08 UnitNumber_u08 );

extern bit EE_RSCFD_IntCANBusActivate( u08 UnitNumber_u08 );

#endif
