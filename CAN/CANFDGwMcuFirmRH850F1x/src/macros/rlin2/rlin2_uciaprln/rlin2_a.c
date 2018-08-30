//============================================================================
// PROJECT = RLIN2 Type RLIN2_UCIAPRLN
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RLIN2 Application Level
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

#include <ree_types.h>

#include <map_rlin2.h>
#include <map_asmn.h>
#include <map_asmn_basic.h>

#include <string.h>
#include <stdio.h>

/*****************************************************************************/
/*                                                                           */
/*              LIN IMPLEMENTATION FOR RLIN2                                 */
/*                                                                           */
/*****************************************************************************/

/* LIN State Machine flags */

static u08 RLIN2_LINSF_State_u08[ RLIN2_MAXMACROS ][ RLIN2_MAXCHANNELS ] = 
           { { RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE,
               RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE },
             { RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE,
               RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE },
             { RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE,
               RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE },
             { RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE,
               RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE },
             { RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE,
               RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE },
             { RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE,
               RLIN2_A_LIN_STATE_IDLE, RLIN2_A_LIN_STATE_IDLE } }  ;

/* LIN Buffer Handling flags */

static u08  RLIN2_LINMF_TableIndex_u08[ RLIN2_MAXMACROS ][ RLIN2_MAXCHANNELS ] = 
            { { RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH,
                RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH },
              { RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH,
                RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH },
              { RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH,
                RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH },
              { RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH,
                RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH },
              { RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH,
                RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH },
              { RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH,
                RLIN2_A_LIN_MAXTABLELENGTH, RLIN2_A_LIN_MAXTABLELENGTH } }  ;
              
static u08  RLIN2_LINMF_CurTable_u08[ RLIN2_MAXMACROS ][ RLIN2_MAXCHANNELS ] = 
            { { 0, 0, 0, 0 },
              { 0, 0, 0, 0 },
              { 0, 0, 0, 0 },
              { 0, 0, 0, 0 },
              { 0, 0, 0, 0 },
              { 0, 0, 0, 0 } };
            
static u08  RLIN2_LINMF_TableStart_u08[ RLIN2_MAXMACROS ][ RLIN2_MAXCHANNELS ] = 
            { { 1, 1, 1, 1 },
              { 1, 1, 1, 1 },
              { 1, 1, 1, 1 },
              { 1, 1, 1, 1 },
              { 1, 1, 1, 1 },
              { 1, 1, 1, 1 } };

static struct rlin2_a_lintable_entry RLIN2_LINM_Buffer;


/*****************************************************************************/
/*                                                                           */
/*              LIN IMPLEMENTATION FOR RLIN2 (MASTER ONLY)                   */
/*                                                                           */
/*****************************************************************************/

/* LIN Interrupt vectors */

void RLIN2_LINM_IRQSend( void )
{
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 NoAction_u08;
  u08 PID_u08;
  
  RLIN2_LINGetStatus( RLIN2_InterruptFlagUnit_u08,
                      RLIN2_InterruptFlagChannel_u08,
                      &NoAction_u08,
                      &HeaderReceived_u08,
                      &DataReceived_u08,
                      &DataTransmitted_u08,
                      &PID_u08 );
                        
  switch( RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ]
                               [ RLIN2_InterruptFlagChannel_u08 ] )
  {
    case RLIN2_A_LIN_STATE_TXBREAK:
      if( DataTransmitted_u08 )
      {
        if( RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08
                                   [ RLIN2_InterruptFlagUnit_u08 ]
                                   [ RLIN2_InterruptFlagChannel_u08 ] ]
                                   [ RLIN2_LINMF_TableIndex_u08
                                   [ RLIN2_InterruptFlagUnit_u08 ]
                                   [ RLIN2_InterruptFlagChannel_u08 ] ].Type_u08 ==
                                     RLIN2_A_NO )
        {
          RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                               [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_SLEEP;
        }
        else
        {
          RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                               [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_IDLE;
        }
      }
      else
      {
        RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                             [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_FSMERROR;
      }
      break;

    case RLIN2_A_LIN_STATE_WAKEUP:
      RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                           [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_IDLE;
      break;
      
    default:
      if( !(RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                                 [ RLIN2_InterruptFlagChannel_u08 ] & RLIN2_A_LIN_STATE_ERROR ) )
        RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                             [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_FSMERROR;
      break;
  }
}

void RLIN2_LINM_IRQReceive( void )
{
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 NoAction_u08;
  u08 DataIndex_u08;
  u08 PID_u08;
  
  RLIN2_LINGetStatus( RLIN2_InterruptFlagUnit_u08,
                      RLIN2_InterruptFlagChannel_u08,
                      &NoAction_u08,
                      &HeaderReceived_u08,
                      &DataReceived_u08,
                      &DataTransmitted_u08,
                      &PID_u08 );

  switch( RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                               [ RLIN2_InterruptFlagChannel_u08 ] )
  {
    case RLIN2_A_LIN_STATE_TXBREAK:
      if( DataReceived_u08 )
      {
        RLIN2_LINReceiveMessage( RLIN2_InterruptFlagUnit_u08,
                                 RLIN2_InterruptFlagChannel_u08,
                                 RLIN2_A_TAB_MASTER_BASE
                                      [ RLIN2_LINMF_CurTable_u08
                                      [ RLIN2_InterruptFlagUnit_u08 ] 
                                      [ RLIN2_InterruptFlagChannel_u08 ] ]
                                      [ RLIN2_LINMF_TableIndex_u08
                                      [ RLIN2_InterruptFlagUnit_u08 ] 
                                      [ RLIN2_InterruptFlagChannel_u08 ] ]
                                        .DataLength_u08,
                                &RLIN2_LINM_Buffer.Data[ 0 ] );

        for( DataIndex_u08 = 0;
             DataIndex_u08 < RLIN2_A_TAB_MASTER_BASE
                             [ RLIN2_LINMF_CurTable_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                                                       [ RLIN2_InterruptFlagChannel_u08 ] ]
                             [ RLIN2_LINMF_TableIndex_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                                                         [ RLIN2_InterruptFlagChannel_u08 ] ]
                             .DataLength_u08;
             DataIndex_u08++ )
        {
          RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                                                           [ RLIN2_InterruptFlagChannel_u08 ] ]
                                 [ RLIN2_LINMF_TableIndex_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                                                             [ RLIN2_InterruptFlagChannel_u08 ] ]
                                 .Data[ DataIndex_u08 ] =
                                 RLIN2_LINM_Buffer.Data[ DataIndex_u08 ];
        }

        RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                             [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_IDLE;
      }
      else
      {
        RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                             [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_UNEXRECV;
      }
      break;

    case RLIN2_A_LIN_STATE_WAKEUP:
      RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                           [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_IDLE;
      break;
      
    default:
      if( !( RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                                  [ RLIN2_InterruptFlagChannel_u08 ] & RLIN2_A_LIN_STATE_ERROR ) )
        RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                             [ RLIN2_InterruptFlagChannel_u08 ] = RLIN2_A_LIN_STATE_UNEXRECV;
      break;
  }
}

void RLIN2_LINM_IRQError( void )
{
  u08 AnyError_u08;
  u08 BitError_u08;
  u08 DataConsistencyError_u08;
  u08 TimeoutError_u08;
  u08 FrameError_u08;
  u08 CheckSumError_u08;
  
  RLIN2_LINGetError( RLIN2_InterruptFlagUnit_u08,
                     RLIN2_InterruptFlagChannel_u08,
                     &AnyError_u08,
                     &BitError_u08,
                     &DataConsistencyError_u08,
                     &TimeoutError_u08,
                     &FrameError_u08,
                     &CheckSumError_u08 );

  if( AnyError_u08 )
  {
    if( DataConsistencyError_u08 ) RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                                                        [ RLIN2_InterruptFlagChannel_u08 ] = 
                                   RLIN2_A_LIN_STATE_DCCERROR;
    if( CheckSumError_u08 )        RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                                                        [ RLIN2_InterruptFlagChannel_u08 ] =
                                   RLIN2_A_LIN_STATE_CHSERROR;
      
    if( ( RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                               [ RLIN2_InterruptFlagChannel_u08 ] & RLIN2_A_LIN_STATE_ERROR ) !=
                                 RLIN2_A_LIN_STATE_ERROR )
    {
      RLIN2_LINSF_State_u08[ RLIN2_InterruptFlagUnit_u08 ] 
                           [ RLIN2_InterruptFlagChannel_u08 ] = 
                             RLIN2_A_LIN_STATE_DLLERROR; /* default error */
    }
  }
}

/* Global configuration of LIN mode */

bit RLIN2_LIN_SetMode( u08 UnitNumber_u08,
                       u08 ChannelNumber_u08,
                       u32 Baudrate_u32,
                       flt Oscillator_Frequency_flt )
{
  bit LINStatus_bit;
  
  LINStatus_bit =  RLIN2_Reset( UnitNumber_u08 );
  LINStatus_bit &= RLIN2_PortEnable( UnitNumber_u08, ChannelNumber_u08 );
  
  LINStatus_bit &= RLIN2_LINEnableInterrupt( UnitNumber_u08,
                                             ChannelNumber_u08,
                                             RLIN2_SET,       /* TX */
                                             RLIN2_SET,       /* RX */
                                             RLIN2_SET,       /* ERR */
                                             RLIN2_SET,       /* Bit error */
                                             RLIN2_SET,       /* Phys. Bus error */
                                             RLIN2_SET,       /* Timeout error */
                                             RLIN2_SET );     /* Frame error */   
  LINStatus_bit &= RLIN2_LINSetConfig( UnitNumber_u08,
                                       ChannelNumber_u08,
                                       Oscillator_Frequency_flt,
                                       RLIN2_LINSTANDARD_V2,
                                       Baudrate_u32,
                                       RLIN2_CLOCK_FA,
                                       RLIN2_SBF15BITS,
                                       RLIN2_BDT1BITS,
                                       RLIN2_SPACE_HDRRESP_1BITS,
                                       RLIN2_SPACE_RESBYTE_1BITS );
  LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                          ChannelNumber_u08,
                                          RLIN2_IRQ_SEND,
                                          RLIN2_INTENABLEDEFAULT,
                                          RLIN2_LINM_IRQSend );
  LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                          ChannelNumber_u08,
                                          RLIN2_IRQ_RECEIVE,
                                          RLIN2_INTENABLEDEFAULT,
                                          RLIN2_LINM_IRQReceive );
  LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                          ChannelNumber_u08,
                                          RLIN2_IRQ_ERROR,
                                          RLIN2_INTENABLEDEFAULT,
                                          RLIN2_LINM_IRQError );
  
  RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                       [ ChannelNumber_u08 ] = RLIN2_A_LIN_STATE_IDLE;

  return( LINStatus_bit );
}

/*************************************************/
/* LIN Master Support Functions for upper layers */
/*************************************************/

bit RLIN2_LINM_SetTable( u08 UnitNumber_u08,
                         u08 ChannelNumber_u08,
                         u08 Table_u08 )
{
  if( Table_u08 >= RLIN2_A_LIN_MASTERTABLES ) return( RLIN2_ERROR );
  
  RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 0;
  RLIN2_LINMF_TableStart_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 1;
  RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ]   = Table_u08;
  
  return( RLIN2_OK );
}

bit RLIN2_LINM_RestartTable( u08 UnitNumber_u08, 
                             u08 ChannelNumber_u08 )
{
  RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 0;
  RLIN2_LINMF_TableStart_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 1;
  
  return( RLIN2_OK );
}

bit RLIN2_LINM_SetTableContent( u08  UnitNumber_u08,
                                u08  ChannelNumber_u08,
                                u08  TableIndex_u08,
                                pu08 DataArray_pu08 )
{
  u08 DataIndex_u08;
  u08 DataLength_u08;
  
  if( TableIndex_u08 >= RLIN2_A_LIN_MAXTABLELENGTH ) return( RLIN2_ERROR );
  
  DataLength_u08 = RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08
                                          [ UnitNumber_u08 ]
                                          [ ChannelNumber_u08 ] ]
                                          [ TableIndex_u08 ]
                                             .DataLength_u08;

  ASMN_DICOMMAND;

  for( DataIndex_u08 = 0;
       DataIndex_u08 < DataLength_u08;
       DataIndex_u08++ )
  {
    RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08
                           [ UnitNumber_u08 ]
                           [ ChannelNumber_u08 ] ]
                           [ TableIndex_u08 ].Data
                           [ DataIndex_u08 ] = *DataArray_pu08;
    DataArray_pu08++;
  }

  ASMN_EICOMMAND;

  return( RLIN2_OK );
}

bit RLIN2_LINM_NextTableContent( u08 UnitNumber_u08,
                                 u08 ChannelNumber_u08 )
{
  bit LINStatus_bit;
  u08 DataIndex_u08;
  u08 PID_u08;
  
  /* wait on LIN idle state */
  
  if( ( RLIN2_LINSF_State_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] != RLIN2_A_LIN_STATE_IDLE ) &&
      ( RLIN2_LINSF_State_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] != RLIN2_A_LIN_STATE_WAKEUP ) )
  {
    return( RLIN2_ERROR );
  }
  
  /* move to the next master table entry to be executed */
  
  if( !RLIN2_LINMF_TableStart_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] )
  {
    RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ]++;
    if( RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] 
        > RLIN2_A_LIN_MAXTABLELENGTH )
      RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 0;
    if( RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                                         [ ChannelNumber_u08 ] ]
                               [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                           [ ChannelNumber_u08 ] ]
                                                           .Type_u08 ==
                                 RLIN2_A_NO )
      RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 0;
  }
  else
  {
    RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 0;
    RLIN2_LINMF_TableStart_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 0;
  }
  
  /* copy current table entry into buffer */
  
  RLIN2_LINM_Buffer.Type_u08 = RLIN2_A_TAB_MASTER_BASE
                     [ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                               [ ChannelNumber_u08 ] ]
                     [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                 [ ChannelNumber_u08 ] ].Type_u08;
  RLIN2_LINM_Buffer.PID_u08 = RLIN2_A_TAB_MASTER_BASE
                     [ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                               [ ChannelNumber_u08 ] ]
                     [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                 [ ChannelNumber_u08 ] ].PID_u08;
  RLIN2_LINM_Buffer.DataLength_u08 = RLIN2_A_TAB_MASTER_BASE
                     [ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                               [ ChannelNumber_u08 ] ]
                     [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                 [ ChannelNumber_u08 ] ].DataLength_u08;

  for( DataIndex_u08 = 0;
       DataIndex_u08 < RLIN2_A_TAB_MASTER_BASE
                       [ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                                 [ ChannelNumber_u08 ] ]
                       [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                   [ ChannelNumber_u08 ] ]
                       .DataLength_u08;
       DataIndex_u08++ )
  {
    RLIN2_LINM_Buffer.Data[ DataIndex_u08 ] = RLIN2_A_TAB_MASTER_BASE
                       [ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                                 [ ChannelNumber_u08 ] ]
                       [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                   [ ChannelNumber_u08 ] ]
                       .Data[ DataIndex_u08 ];
                       
  }

  /* initiate a master frame cycle */
  
  RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                       [ ChannelNumber_u08 ] = RLIN2_A_LIN_STATE_TXBREAK;
  
  PID_u08 = RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                                             [ ChannelNumber_u08 ] ]
                                   [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                               [ ChannelNumber_u08 ] ]
                                                               .PID_u08;
  
  LINStatus_bit = RLIN2_LINSendMessage( UnitNumber_u08,
                                        ChannelNumber_u08,
                                        PID_u08,
                                        RLIN2_A_TAB_MASTER_BASE
                                         [ RLIN2_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         [ RLIN2_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         .DataLength_u08,
                                        ( ( PID_u08 >= RLIN2_A_LIN_CLASSCHKSUMLIM ) ?
                                         RLIN2_CHECKSUM_CLASSIC : RLIN2_CHECKSUM_ENHANCED ),
                                        RLIN2_A_TAB_MASTER_BASE
                                         [ RLIN2_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         [ RLIN2_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         .Type_u08,
                                         RLIN2_LINM_Buffer.Data );

  return( LINStatus_bit );
}

bit RLIN2_LINM_GetTableContent( u08  UnitNumber_u08,
                                u08  ChannelNumber_u08,
                                u08  ReadTableIndex_u08,
                                pu08 DataArray_pu08 )
{
  u08 DataIndex_u08;
  
  if( ReadTableIndex_u08 >= RLIN2_A_LIN_MAXTABLELENGTH ) 
    return( RLIN2_ERROR );

  /* get the appropriate content from the master table */
  
  ASMN_DICOMMAND;

  for( DataIndex_u08 = 0;
       DataIndex_u08 < RLIN2_A_TAB_MASTER_BASE
                       [ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                       [ ChannelNumber_u08 ] ]
                       [ ReadTableIndex_u08 ].DataLength_u08;
       DataIndex_u08++ )
  {
    *DataArray_pu08 = RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08
                                             [ UnitNumber_u08 ]
                                             [ ChannelNumber_u08 ] ]
                                             [ ReadTableIndex_u08 ].Data
                                             [ DataIndex_u08 ];
    DataArray_pu08++;
  }
  
  ASMN_EICOMMAND;

  return( RLIN2_OK );
}

u08 RLIN2_LINM_GetStatus( u08 UnitNumber_u08,
                          u08 ChannelNumber_u08 )
{
  u08 ErrorCode_u08;
  
  ErrorCode_u08 = RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                                       [ ChannelNumber_u08 ] 
                                       & RLIN2_A_LIN_STATE_APIMASK;
  
  if( ErrorCode_u08 & RLIN2_A_LIN_STATE_ERROR )
  {
    ErrorCode_u08 = RLIN2_LINSF_State_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ];
    RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                         [ ChannelNumber_u08 ] = RLIN2_A_LIN_STATE_IDLE;
  }
  
  return( ErrorCode_u08 );
}

bit RLIN2_LINM_ResetFrame( u08 UnitNumber_u08,
                           u08 ChannelNumber_u08 )
{
  u08 ErrorCode_u08;
  
  ErrorCode_u08 = RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                                       [ ChannelNumber_u08 ] 
                                       & RLIN2_A_LIN_STATE_APIMASK;
  
  if( !( ErrorCode_u08 & RLIN2_A_LIN_STATE_ERROR ) )
  {
    RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                         [ ChannelNumber_u08 ] = RLIN2_A_LIN_STATE_IDLE;
    return( RLIN2_OK );
  }
  else
  {
    return( RLIN2_ERROR );
  }
}

bit RLIN2_LINM_SetSleepState( u08 UnitNumber_u08,
                              u08 ChannelNumber_u08 )
{
  bit LINStatus_bit;
  u08 TableIndex_u08 = 0;
  u08 PID_u08;
    
  /* search sleep instruction in current master table */
  
  while( RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                [ ChannelNumber_u08 ] ]
                                [ TableIndex_u08 ].Type_u08 != RLIN2_A_NO )
  {
    TableIndex_u08++;
  }
  
  /* use sleep instruction and initiate a restart of the table */
  
  RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                            [ ChannelNumber_u08 ] = TableIndex_u08;
  RLIN2_LINMF_TableStart_u08[ UnitNumber_u08 ][ ChannelNumber_u08 ] = 1;
  
  /* initiate a master frame cycle */
  
  RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                       [ ChannelNumber_u08 ] = RLIN2_A_LIN_STATE_TXBREAK;
   
  PID_u08 = RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                                             [ ChannelNumber_u08 ] ]
                                   [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                               [ ChannelNumber_u08 ] ]
                                    .PID_u08;

  LINStatus_bit = RLIN2_LINSendMessage( UnitNumber_u08,
                                        ChannelNumber_u08,
                                        PID_u08,
                                        RLIN2_A_TAB_MASTER_BASE
                                         [ RLIN2_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         [ RLIN2_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         .DataLength_u08,
                                        ( ( PID_u08 >= RLIN2_A_LIN_CLASSCHKSUMLIM ) ?
                                         RLIN2_CHECKSUM_CLASSIC : RLIN2_CHECKSUM_ENHANCED ),
                                        RLIN2_A_TAB_MASTER_BASE
                                         [ RLIN2_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         [ RLIN2_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         .Type_u08,
                                         RLIN2_A_TAB_MASTER_BASE
                                         [ RLIN2_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         [ RLIN2_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ] ]
                                         .Data );
  
  while( ( RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                                [ ChannelNumber_u08 ] != 
                                RLIN2_A_LIN_STATE_SLEEP ) &&
         ( ( RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                                  [ ChannelNumber_u08 ] 
                                  & RLIN2_A_LIN_STATE_ERROR ) !=
                                  RLIN2_A_LIN_STATE_ERROR ) );
  
  if( RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                           [ ChannelNumber_u08 ] == RLIN2_A_LIN_STATE_SLEEP )
  {
    LINStatus_bit &= RLIN2_LINReceiveWakeup( UnitNumber_u08,
                                             ChannelNumber_u08 );
  }
  
  return( LINStatus_bit );
}

bit RLIN2_LINM_SendWakeup( u08 UnitNumber_u08,
                           u08 ChannelNumber_u08 )
{
  bit LINStatus_bit;
  
  /* any error does not allow to wake up */
  
  if( ( RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                             [ ChannelNumber_u08 ] != RLIN2_A_LIN_STATE_IDLE ) &&
      ( RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                             [ ChannelNumber_u08 ] != RLIN2_A_LIN_STATE_SLEEP ) )
  {
    return( RLIN2_ERROR );
  }
  
  /* initiate the sending of the wake up pattern */
  
  RLIN2_LINSF_State_u08[ UnitNumber_u08 ]
                       [ ChannelNumber_u08 ] = RLIN2_A_LIN_STATE_WAKEUP;
  
  LINStatus_bit = RLIN2_LINSendWakeup( UnitNumber_u08,
                                       ChannelNumber_u08,
                                       RLIN2_WUPTL_8BITS );
  return( LINStatus_bit );
}

/* Activate LIN Master with selectable table,
   generates a WUP and then executes the table
 */
 
bit RLIN2_LINMasterExecution( u08 UnitNumber_u08,
                              u08 ChannelNumber_u08,
                              u08 TableNumber_u08,
                              u32 Baudrate_u32 )
{
  bit LINStatus_bit = RLIN2_OK;
  u08 ErrorStatus;

  LINStatus_bit =  RLIN2_LIN_SetMode( UnitNumber_u08, 
                                      ChannelNumber_u08,
                                      Baudrate_u32,
                                      OSCILLATOR_FREQUENCY );
  LINStatus_bit &= RLIN2_LINM_SetTable( UnitNumber_u08,
                                        ChannelNumber_u08,
                                        TableNumber_u08 );
  LINStatus_bit &= RLIN2_LINM_RestartTable( UnitNumber_u08,
                                            ChannelNumber_u08 );

  do
  {
    LINStatus_bit &= RLIN2_LINM_SendWakeup( UnitNumber_u08, ChannelNumber_u08 );
    
  } while( ( RLIN2_LINM_GetStatus( UnitNumber_u08, 
                                   ChannelNumber_u08 ) != RLIN2_A_LIN_STATE_IDLE ) &&
           ( RLIN2_LINM_GetStatus( UnitNumber_u08, 
                                   ChannelNumber_u08 ) != RLIN2_A_LIN_STATE_WAKEUP ) );


  while( RLIN2_A_TAB_MASTER_BASE[ RLIN2_LINMF_CurTable_u08[ UnitNumber_u08 ]
                                                          [ ChannelNumber_u08 ] ]
                                [ RLIN2_LINMF_TableIndex_u08[ UnitNumber_u08 ]
                                                            [ ChannelNumber_u08 ] + 1 ].Type_u08 !=
                                  RLIN2_A_NO )
  {
    LINStatus_bit &= RLIN2_LINM_NextTableContent( UnitNumber_u08, ChannelNumber_u08 );

    do
    {
      ErrorStatus = RLIN2_LINM_GetStatus( UnitNumber_u08, ChannelNumber_u08 );
      
    } while( ErrorStatus != RLIN2_A_LIN_STATE_IDLE );
  }

  LINStatus_bit &= RLIN2_Reset( UnitNumber_u08 );
  LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                          ChannelNumber_u08,
                                          RLIN2_IRQ_SEND,
                                          RLIN2_INTCLEAR,
                                          NULL );
  LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                          ChannelNumber_u08,
                                          RLIN2_IRQ_RECEIVE,
                                          RLIN2_INTCLEAR,
                                          NULL );
  LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                          ChannelNumber_u08,
                                          RLIN2_IRQ_ERROR,
                                          RLIN2_INTCLEAR,
                                          NULL );
  LINStatus_bit &= RLIN2_PortDisable( UnitNumber_u08, ChannelNumber_u08 );

  return( LINStatus_bit );
}

/* Reset Unit */

bit RLIN2_ResetAll( u08 UnitNumber_u08 )
{
  bit LINStatus_bit = RLIN2_OK;
  u08 ChannelNumber_u08;

  LINStatus_bit &= RLIN2_Reset( UnitNumber_u08 );

  for( ChannelNumber_u08 = 0;
       ChannelNumber_u08 < ee_rlin2_channels[ UnitNumber_u08 ];
       ChannelNumber_u08++ )
  {
    LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                            ChannelNumber_u08,
                                            RLIN2_IRQ_SEND,
                                            RLIN2_INTCLEAR,
                                            NULL );
    LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                            ChannelNumber_u08,
                                            RLIN2_IRQ_RECEIVE,
                                            RLIN2_INTCLEAR,
                                            NULL );
    LINStatus_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                            ChannelNumber_u08,
                                            RLIN2_IRQ_ERROR,
                                            RLIN2_INTCLEAR,
                                            NULL );
    RLIN2_PortDisable( UnitNumber_u08, ChannelNumber_u08 );
  }
  return( LINStatus_bit );
}
