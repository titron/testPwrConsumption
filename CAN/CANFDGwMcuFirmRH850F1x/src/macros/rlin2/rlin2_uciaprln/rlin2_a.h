//============================================================================
// PROJECT = RSCAN Type RLIN2_UCIAPRLN
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RLIN2 Application Level Function Include
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

#ifndef _QLAPBRLIN2V1_A_H
#define _QLAPBRLIN2V1_A_H

#include <ree_types.h>

extern
bit RLIN2_LIN_SetMode( u08 UnitNumber_u08,
                       u08 ChannelNumber_u08,
                       u32 Baudrate_u32,
                       flt Oscillator_Frequency_flt );

extern
bit RLIN2_LINM_SetTable( u08 UnitNumber_u08,
                         u08 ChannelNumber_u08,
                         u08 Table_u08 );

extern
bit RLIN2_LINM_RestartTable( u08 UnitNumber_u08, 
                             u08 ChannelNumber_u08 );

extern
bit RLIN2_LINM_SetTableContent( u08  UnitNumber_u08,
                                u08  ChannelNumber_u08,
                                u08  TableIndex_u08,
                                pu08 DataArray_pu08 );

extern
bit RLIN2_LINM_NextTableContent( u08 UnitNumber_u08,
                                 u08 ChannelNumber_u08 );

extern
bit RLIN2_LINM_GetTableContent( u08  UnitNumber_u08,
                                u08  ChannelNumber_u08,
                                u08  ReadTableIndex_u08,
                                pu08 DataArray_pu08 );

extern
u08 RLIN2_LINM_GetStatus( u08 UnitNumber_u08,
                          u08 ChannelNumber_u08 );

extern
bit RLIN2_LINM_ResetFrame( u08 UnitNumber_u08,
                           u08 ChannelNumber_u08 );

extern
bit RLIN2_LINM_SetSleepState( u08 UnitNumber_u08,
                              u08 ChannelNumber_u08 );

extern
bit RLIN2_LINM_SendWakeup( u08 UnitNumber_u08,
                           u08 ChannelNumber_u08 );

extern
bit RLIN2_LINMasterExecution( u08 UnitNumber_u08,
                              u08 ChannelNumber_u08,
                              u08 TableNumber_u08,
                              u32 Baudrate_u32 );

extern
bit RLIN2_ResetAll( u08 UnitNumber_u08 );

#endif
