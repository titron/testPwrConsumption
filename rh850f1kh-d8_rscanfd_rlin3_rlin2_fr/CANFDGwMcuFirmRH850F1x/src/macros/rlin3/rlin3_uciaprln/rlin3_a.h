//============================================================================
// PROJECT = RSCAN Type RLIN3_UCIAPRLN
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RLIN3 Application Level Function Include
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
// Environment: Devices:          All featuring RLIN3_UCIAPRLN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#ifndef _QLAPBRLIN3V1_A_H
#define _QLAPBRLIN3V1_A_H

#include <ree_types.h>

extern bit
RLIN3_SendString( u08   UnitNumber_u08,
                  char *SendString,
                  u08   TTYMode_u08 );

extern bit
RLIN3_SendChar( u08           UnitNumber_u08,
                unsigned char SendChar,
                u08           TTYMode_u08 );

extern bit
RLIN3_SendInt( u08          UnitNumber_u08,
               unsigned int SendInt,
               u08          TTYMode_u08 );

extern bit
RLIN3_ReceiveString( u08   UnitNumber_u08,
                     char *ReceiveString,
                     u16   ReceiveLength_u16,
                     u32   TimeOutCount_u32 );

extern bit
RLIN3_ReceiveUChar( u08            UnitNumber_u08,
                    u16            ReceiveLength_u16,
                    char          *RequestString,
                    unsigned char *Result,
                    pu08           ScanState_pu08 );

extern bit
RLIN3_ReceiveFloat( u08    UnitNumber_u08,
                    u16    ReceiveLength_u16,
                    char  *RequestString,
                    float *Result,
                    pu08   ScanState_pu08 );

extern bit
RLIN3_ReceiveInteger( u08    UnitNumber_u08,
                      u16    ReceiveLength_u16,
                      char  *RequestString,
                      int   *Result,
                      pu08   ScanState_pu08 );

extern bit
RLIN3_ReceiveULong( u08            UnitNumber_u08,
                    u16            ReceiveLength_u16,
                    char          *RequestString,
                    unsigned long *Result,
                    pu08           ScanState_pu08 );

extern
bit RLIN3_LIN_SetMode( u08 UnitNumber_u08,
                       u08 LINMode_u08,
                       u32 Baudrate_u32,
                       flt Oscillator_Frequency_flt );

extern
bit RLIN3_LINM_SetTable( u08 UnitNumber_u08,
                         u08 Table_u08 );

extern
bit RLIN3_LINM_RestartTable( u08 UnitNumber_u08 );

extern
bit RLIN3_LINM_SetTableContent( u08 UnitNumber_u08,
                                u08  TableIndex_u08,
                                pu08 DataArray_pu08 );

extern
bit RLIN3_LINM_NextTableContent( u08 UnitNumber_u08 );

extern
bit RLIN3_LINM_GetTableContent( u08 UnitNumber_u08,
                                u08  ReadTableIndex_u08,
                                pu08 DataArray_pu08 );

extern
u08 RLIN3_LINM_GetStatus( u08 UnitNumber_u08 );

extern
bit RLIN3_LINM_ResetFrame( u08 UnitNumber_u08 );

extern
bit RLIN3_LINM_SetSleepState( u08 UnitNumber_u08 );

extern
bit RLIN3_LINM_SendWakeup( u08 UnitNumber_u08 );

extern
bit RLIN3_LINS_SetTableContent( u08  TableIndex_u08,
                                pu08 DataArray_pu08 );

extern
bit RLIN3_LINS_GetTableContent( u08  ReadTableIndex_u08,
                                pu08 Type_pu08,
                                pu08 DataLength_pu08,
                                pu08 DataArray_pu08 );

extern
bit RLIN3_LINS_SetTablePID( u08 TableIndex_u08,
                            u08 NewPID_u08 );

extern
u08 RLIN3_LINS_GetStatus( u08  UnitNumber_u08,
                          pu08 TableIndex_pu08 );

extern
void RLIN3_LINS_ActivateResponses( u08 UnitNumber_u08,
                                   bit Activation_bit );

extern
bit RLIN3_LINS_SetSleepState( u08 UnitNumber_u08 );

extern
bit RLIN3_LINS_SendWakeup( u08 UnitNumber_u08 );

extern
bit RLIN3_UARTSendString( u08  UnitNumber_u08,
                          u32  Baudrate_u32,
                          pu08 String_pu08 );

extern
bit RLIN3_LINMasterExecution( u08 UnitNumber_u08,
                              u08 TableNumber_u08,
                              u32 Baudrate_u32 );

extern
bit RLIN3_LINSlaveActivation( u08 UnitNumber_u08,
                              u32 Baudrate_u32 );

extern
bit RLIN3_ResetAll( u08 UnitNumber_u08 );

#endif
