//============================================================================
// PROJECT = RLIN3 Type RLIN3_UCIAPRLN
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2014 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: AUTOSAR RSCAN Driver Hardware Configuration Types
//
//Warranty Disclaimer
//
//Because the Product(s) is licensed free of charge, there is no warranty 
//of any kind whatsoever and expressly disclaimed and excluded by RENESAS, 
//either expressed or implied, including but not limited to those for 
//non-infringement of intellectual property, merchantability and/or 
//fitness for the particular purpose. 
//RENESAS shall not have any obligation to maintain, service or provide bug 
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
//In no event shall RENESAS be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. RENESAS shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by RENESAS in connection with the Product(s) and/or the 
//Application.
//
//
//
//============================================================================
// Environment: Devices:          All featuring RLIN3_UCIAPRLN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#ifndef _RLIN3_AS_H
#define _RLIN3_AS_H
#define _RLIN2_AS_H

#include <stddef.h>
#include <ree_types.h>

#include <map_rlin3.h>


/* Interrupt priorities of CAN driver */

#define RLIN3_AS_IRQPRIO_RX  ( RLIN3_INTENABLEDEFAULT )
#define RLIN3_AS_IRQPRIO_TX  ( RLIN3_INTENABLEDEFAULT )
#define RLIN3_AS_IRQPRIO_ERR ( RLIN3_INTENABLEDEFAULT )
#define RLIN3_AS_IRQPRIO_COM ( RLIN3_INTCLEAR )

/* Common LIN AUTOSAR driver types */

typedef u08 uint8;

typedef struct Lin_UnitConfigType
{
  u08 UnitNumber_u08;
  u08 LINMode_u08;
  u08 LINStandard_u08;
  u32 Baudrate_u32;
  u08 SamplesPerBit_u08;
  u08 ClockSelection_u08;
  u08 WakeupLength_u08;
  u08 BreakDetectionLength_u08;
  u08 BreakLength_u08;
  u08 BreakDelimiter_u08;
  u08 HeaderSpace_u08;
  u08 InterByteSpace_u08;
  u08 FilterMode_u08;
  u08 InterruptMode_u08;
  u08 ErrorBit_u08;
  u08 ErrorPhyBus_u08;
  u08 ErrorTimeout_u08;
  u08 ErrorFrame_u08;
  u08 ErrorSync_u08;
  u08 ErrorIDParity_u08;
  u08 TimeoutSel_u08;
  u08 TableNumber_u08;
  
} Lin_UnitConfigType;

typedef struct Lin_ConfigType
{
  const struct Lin_UnitConfigType  *Unit[ RLIN3_MAXMACROS ];
  
}Lin_ConfigType;

typedef u08 Lin_FramePidType;
typedef u08 Lin_FrameDlType;

typedef enum
{
  LIN_ENHANCED_CS = RLIN3_CHECKSUM_ENHANCED,
  LIN_CLASSIC_CS  = RLIN3_CHECKSUM_CLASSIC
  
} Lin_FrameCsModelType;

typedef enum
{
  LIN_MASTER_RESPONSE = RLIN3_RESPONSE_TRANSMIT,
  LIN_SLAVE_RESPONSE  = RLIN3_RESPONSE_RECEIVE,
  LIN_SLAVE_TO_SLAVE  = RLIN3_INVALID              /* S2S is not yet supported */
  
} Lin_FrameResponseType;

typedef struct Lin_PduType
{
  Lin_FramePidType       Pid;
  Lin_FrameCsModelType   Cs;
  Lin_FrameResponseType  Drc;
  Lin_FrameDlType        Dl;
  uint8                 *SduPtr;
  
} Lin_PduType;

typedef enum
{
  LIN_NOT_OK,
  LIN_TX_OK,
  LIN_TX_BUSY,
  LIN_TX_HEADER_ERROR,
  LIN_TX_ERROR,
  LIN_RX_OK,
  LIN_RX_BUSY,
  LIN_RX_ERROR,
  LIN_RX_NO_RESPONSE,
  LIN_OPERATIONAL,
  LIN_CH_SLEEP
  
} Lin_StatusType;

typedef enum
{
  E_OK     = RLIN3_OK,
  E_NOT_OK = RLIN3_ERROR
  
} Std_ReturnType;

typedef struct LinSlaveTable
{
  uint8        Semaphore;
  Lin_PduType *PDU;

} LinSlaveTable;


/* Function prototypes */

void           Lin_Init( const Lin_ConfigType *Config );
Std_ReturnType Lin_CheckWakeup( uint8 Channel );
Std_ReturnType Lin_SendFrame( uint8 Channel, Lin_PduType *PduInfoPtr );
Std_ReturnType Lin_GoToSleep( uint8 Channel );
Std_ReturnType Lin_Wakeup( uint8 Channel );
Lin_StatusType Lin_GetStatus( uint8 Channel, uint8 *LinSduPtr );
Std_ReturnType Lin_GetFrame( uint8                Channel, 
                             Lin_FrameDlType      Length, 
                             Lin_FrameCsModelType ChecksumType );
Std_ReturnType Lin_SkipFrame( uint8 Channel );

#endif
