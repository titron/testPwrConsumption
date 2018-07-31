//============================================================================
// PROJECT = RSCAN Type RLIN3_UCIAPRLN
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RLIN3 AUTOSAR interface
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

#include <ree_types.h>

#include <map_rlin3.h>
#include <rlin3_as.h>
#include <rlin3_as_cfg.h>

/* External functions (callbacks) */

extern void LinIf_RxHeaderIndication( Lin_FramePidType );
extern void LinIf_RxFrameIndication( Lin_FramePidType, uint8* );

/* Local Static Flags */

static u08 WakeupLength[ RLIN3_MAXMACROS ] = { RLIN3_WUPTL_8BITS, RLIN3_WUPTL_8BITS,
                                               RLIN3_WUPTL_8BITS, RLIN3_WUPTL_8BITS,
                                               RLIN3_WUPTL_8BITS, RLIN3_WUPTL_8BITS };

static Lin_FrameDlType CurrentDl[ RLIN3_MAXMACROS ] = { 0, 0, 0, 0, 0, 0 };

static Lin_StatusType CurrentState[ RLIN3_MAXMACROS ] = { LIN_NOT_OK, LIN_NOT_OK,
                                                          LIN_NOT_OK, LIN_NOT_OK,
                                                          LIN_NOT_OK, LIN_NOT_OK };

static uint8 DataBuffer[ RLIN3_LINDATALEN_MAX ];

/* Interrupt routines */

void RLIN3_LINS_AS_IRQSend( void )
{
  u08 ActiveUnit_u08;
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 PID_u08;
  
  for( ActiveUnit_u08 = 0;
       ActiveUnit_u08 < RLIN3_MAXMACROS;
       ActiveUnit_u08++ )
  {
    if( CurrentState[ ActiveUnit_u08 ] != LIN_NOT_OK )
    {
      RLIN3_LINGetStatus( ActiveUnit_u08,
                          &HeaderReceived_u08,
                          &DataReceived_u08,
                          &DataTransmitted_u08,
                          &PID_u08 );
                        
      switch( CurrentState[ ActiveUnit_u08 ] )
      {
        case LIN_TX_BUSY:
          if( DataTransmitted_u08 )
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_TX_OK;
          }
          else
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_TX_ERROR;
          }
        break;

      default:
        break;
      }
    }

    RLIN3_LINSReceiveAction( ActiveUnit_u08,
                             RLIN3_A_GETHEADER,
                             0,
                             RLIN3_AS_CSMODEL_DEFAULT );
    CurrentState[ ActiveUnit_u08 ] = LIN_RX_BUSY;
  }
}

void RLIN3_LINS_AS_IRQReceive( void )
{
  u08 ActiveUnit_u08;
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 PID_u08;
  
  for( ActiveUnit_u08 = 0;
       ActiveUnit_u08 < RLIN3_MAXMACROS;
       ActiveUnit_u08++ )
  {
    if( CurrentState[ ActiveUnit_u08 ] != LIN_NOT_OK )
    {
      RLIN3_LINGetStatus( ActiveUnit_u08,
                          &HeaderReceived_u08,
                          &DataReceived_u08,
                          &DataTransmitted_u08,
                          &PID_u08 );
                        
      switch( CurrentState[ ActiveUnit_u08 ] )
      {
        case LIN_RX_BUSY:
          if( HeaderReceived_u08 )
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_RX_OK;
            LinIf_RxHeaderIndication( ( Lin_FramePidType )PID_u08 );
          }
          else if( DataReceived_u08 )
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_RX_OK;
            RLIN3_LINReceiveMessage( ActiveUnit_u08,
                                     RLIN3_LINDATALEN_MAX,
                                     &DataBuffer[ 0 ] );
            LinIf_RxFrameIndication( ( Lin_FramePidType )PID_u08, 
                                     &DataBuffer[ 0 ] );
            RLIN3_LINSReceiveAction( ActiveUnit_u08,
                                     RLIN3_A_GETHEADER,
                                     0,
                                     RLIN3_AS_CSMODEL_DEFAULT );
            CurrentState[ ActiveUnit_u08 ] = LIN_RX_BUSY;
          }
          else
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_RX_ERROR;
          }
        break;

      default:
        break;
      }
    }
  }  
}

void RLIN3_LINS_AS_IRQError( void )
{
  u08 ActiveUnit_u08;  
  u08 AnyError_u08;
  u08 BitError_u08;
  u08 DataConsistencyError_u08;
  u08 TimeoutError_u08;
  u08 FrameError_u08;
  u08 SyncFieldError_u08;
  u08 CheckSumError_u08;
  u08 IdentParityError_u08;
  u08 ResponsePreparationError_u08;
  
  for( ActiveUnit_u08 = 0;
       ActiveUnit_u08 < RLIN3_MAXMACROS;
       ActiveUnit_u08++ )
  {
    if( CurrentState[ ActiveUnit_u08 ] != LIN_NOT_OK )
    {
      RLIN3_LINGetError( ActiveUnit_u08,
                         &AnyError_u08,
                         &BitError_u08,
                         &DataConsistencyError_u08,
                         &TimeoutError_u08,
                         &FrameError_u08,
                         &SyncFieldError_u08,
                         &CheckSumError_u08,
                         &IdentParityError_u08,
                         &ResponsePreparationError_u08 );

      if( AnyError_u08 )
      {
        if( DataConsistencyError_u08 ) CurrentState[ ActiveUnit_u08 ] = LIN_TX_HEADER_ERROR;
        if( CheckSumError_u08 )        CurrentState[ ActiveUnit_u08 ] = LIN_RX_ERROR;
        if( TimeoutError_u08 )         CurrentState[ ActiveUnit_u08 ] = LIN_RX_NO_RESPONSE;
        if( BitError_u08 )             CurrentState[ ActiveUnit_u08 ] = LIN_TX_ERROR;
      }

      RLIN3_LINSReceiveAction( ActiveUnit_u08,
                               RLIN3_A_GETHEADER,
                               0,
                               RLIN3_AS_CSMODEL_DEFAULT );
      CurrentState[ ActiveUnit_u08 ] = LIN_RX_BUSY;
    }
  }
}

void RLIN3_LINM_AS_IRQSend( void )
{
  u08 ActiveUnit_u08;
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 PID_u08;
  
  for( ActiveUnit_u08 = 0;
       ActiveUnit_u08 < RLIN3_MAXMACROS;
       ActiveUnit_u08++ )
  {
    if( CurrentState[ ActiveUnit_u08 ] != LIN_NOT_OK )
    {
      RLIN3_LINGetStatus( ActiveUnit_u08,
                          &HeaderReceived_u08,
                          &DataReceived_u08,
                          &DataTransmitted_u08,
                          &PID_u08 );
                        
      switch( CurrentState[ ActiveUnit_u08 ] )
      {
        case LIN_TX_BUSY:
          if( DataTransmitted_u08 )
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_TX_OK;
          }
          else
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_TX_ERROR;
          }
        break;

      default:
        break;
      }
    }
  }
}

void RLIN3_LINM_AS_IRQReceive( void )
{
  u08 ActiveUnit_u08;
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 PID_u08;
  
  for( ActiveUnit_u08 = 0;
       ActiveUnit_u08 < RLIN3_MAXMACROS;
       ActiveUnit_u08++ )
  {
    if( CurrentState[ ActiveUnit_u08 ] != LIN_NOT_OK )
    {
      RLIN3_LINGetStatus( ActiveUnit_u08,
                          &HeaderReceived_u08,
                          &DataReceived_u08,
                          &DataTransmitted_u08,
                          &PID_u08 );
                        
      switch( CurrentState[ ActiveUnit_u08 ] )
      {
        case LIN_RX_BUSY:
          if( DataReceived_u08 )
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_RX_OK;
          }
          else
          {
            CurrentState[ ActiveUnit_u08 ] = LIN_RX_ERROR;
          }
        break;

      default:
        break;
      }
    }
  }
}

void RLIN3_LINM_AS_IRQError( void )
{
  u08 ActiveUnit_u08;  
  u08 AnyError_u08;
  u08 BitError_u08;
  u08 DataConsistencyError_u08;
  u08 TimeoutError_u08;
  u08 FrameError_u08;
  u08 SyncFieldError_u08;
  u08 CheckSumError_u08;
  u08 IdentParityError_u08;
  u08 ResponsePreparationError_u08;
  
  for( ActiveUnit_u08 = 0;
       ActiveUnit_u08 < RLIN3_MAXMACROS;
       ActiveUnit_u08++ )
  {
    if( CurrentState[ ActiveUnit_u08 ] != LIN_NOT_OK )
    {
      RLIN3_LINGetError( ActiveUnit_u08,
                         &AnyError_u08,
                         &BitError_u08,
                         &DataConsistencyError_u08,
                         &TimeoutError_u08,
                         &FrameError_u08,
                         &SyncFieldError_u08,
                         &CheckSumError_u08,
                         &IdentParityError_u08,
                         &ResponsePreparationError_u08 );

      if( AnyError_u08 )
      {
        if( DataConsistencyError_u08 ) CurrentState[ ActiveUnit_u08 ] = LIN_TX_HEADER_ERROR;
        if( CheckSumError_u08 )        CurrentState[ ActiveUnit_u08 ] = LIN_RX_ERROR;
        if( TimeoutError_u08 )         CurrentState[ ActiveUnit_u08 ] = LIN_RX_NO_RESPONSE;
        if( BitError_u08 )             CurrentState[ ActiveUnit_u08 ] = LIN_TX_ERROR;
      }
    }
  }
}

/* API Functions */

//=============================================================================
// FunctionName: Lin_Init
// IN  : Configuration set
// OUT : -
// Description : 
// Initialize AUTOSAR interface driver
//=============================================================================

void Lin_Init( const Lin_ConfigType *Config )
{
  u08 CurrentUnit_u08;
  bit UARTStatus_bit   = RLIN3_OK;
  
  for( CurrentUnit_u08 = RLIN3_0;
       CurrentUnit_u08 < RLIN3_MAXMACROS;
       CurrentUnit_u08++ )
  {
    if( Config->Unit[ CurrentUnit_u08 ] != NULL )
    {
      UARTStatus_bit &= RLIN3_Reset( Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08 );
      UARTStatus_bit &= RLIN3_PortEnable( Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08 );

      UARTStatus_bit &= RLIN3_LINEnableInterrupt( 
                          Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                          RLIN3_SET,       /* TX */
                          RLIN3_SET,       /* RX */
                          RLIN3_SET,       /* ERR */
                          Config->Unit[ CurrentUnit_u08 ]->ErrorBit_u08,      /* Bit error */
                          Config->Unit[ CurrentUnit_u08 ]->ErrorPhyBus_u08,   /* Phys. Bus error */
                          Config->Unit[ CurrentUnit_u08 ]->ErrorTimeout_u08,  /* Timeout error */
                          Config->Unit[ CurrentUnit_u08 ]->ErrorFrame_u08,    /* Frame error */
                          Config->Unit[ CurrentUnit_u08 ]->ErrorSync_u08,     /* Sync error */
                          Config->Unit[ CurrentUnit_u08 ]->ErrorIDParity_u08, /* ID Parity error */
                          Config->Unit[ CurrentUnit_u08 ]->TimeoutSel_u08,    /* Frame Timeout */
                          ( Config->Unit[ CurrentUnit_u08 ]->LINMode_u08
                           == RLIN3_MODE_LINMASTER ) ? RLIN3_CLEAR : RLIN3_SET );   /* HEADER */

      UARTStatus_bit &= RLIN3_LINSetConfig( 
                          Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                          OSCILLATOR_FREQUENCY,
                          Config->Unit[ CurrentUnit_u08 ]->LINMode_u08,
                          Config->Unit[ CurrentUnit_u08 ]->LINStandard_u08,
                          Config->Unit[ CurrentUnit_u08 ]->Baudrate_u32,
                          Config->Unit[ CurrentUnit_u08 ]->SamplesPerBit_u08,
                          Config->Unit[ CurrentUnit_u08 ]->ClockSelection_u08,
                          Config->Unit[ CurrentUnit_u08 ]->BreakDetectionLength_u08,
                          Config->Unit[ CurrentUnit_u08 ]->BreakLength_u08,
                          Config->Unit[ CurrentUnit_u08 ]->BreakDelimiter_u08,
                          Config->Unit[ CurrentUnit_u08 ]->HeaderSpace_u08,
                          Config->Unit[ CurrentUnit_u08 ]->InterByteSpace_u08,
                          Config->Unit[ CurrentUnit_u08 ]->FilterMode_u08,
                          Config->Unit[ CurrentUnit_u08 ]->InterruptMode_u08 );

      switch( Config->Unit[ CurrentUnit_u08 ]->LINMode_u08 )
      {
        case RLIN3_MODE_LINMASTER:

          if( RLIN3_AS_IRQPRIO_COM != RLIN3_INTCLEAR )
            UARTStatus_bit &= RLIN3_CreateInterrupt( 
                                Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                                RLIN3_IRQ_COMMON,
                                RLIN3_AS_IRQPRIO_COM,
                                RLIN3_LINM_AS_IRQError );
          if( RLIN3_AS_IRQPRIO_TX != RLIN3_INTCLEAR )
            UARTStatus_bit &= RLIN3_CreateInterrupt( 
                                Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                                RLIN3_IRQ_SEND,
                                RLIN3_AS_IRQPRIO_TX,
                                RLIN3_LINM_AS_IRQSend );
          if( RLIN3_AS_IRQPRIO_RX != RLIN3_INTCLEAR )
            UARTStatus_bit &= RLIN3_CreateInterrupt( 
                                Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                                RLIN3_IRQ_RECEIVE,
                                RLIN3_AS_IRQPRIO_RX,
                                RLIN3_LINM_AS_IRQReceive );
          if( RLIN3_AS_IRQPRIO_ERR != RLIN3_INTCLEAR )
            UARTStatus_bit &= RLIN3_CreateInterrupt( 
                                Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                                RLIN3_IRQ_ERROR,
                                RLIN3_AS_IRQPRIO_ERR,
                                RLIN3_LINM_AS_IRQError );
          break;
          
        case RLIN3_MODE_LINSLAVE_FIX:
        case RLIN3_MODE_LINSLAVE_AUTO:  
          
          if( RLIN3_AS_IRQPRIO_COM != RLIN3_INTCLEAR )
            UARTStatus_bit &= RLIN3_CreateInterrupt( 
                                Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                                RLIN3_IRQ_COMMON,
                                RLIN3_AS_IRQPRIO_COM,
                                RLIN3_LINS_AS_IRQError );
          if( RLIN3_AS_IRQPRIO_TX != RLIN3_INTCLEAR )
            UARTStatus_bit &= RLIN3_CreateInterrupt( 
                                Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                                RLIN3_IRQ_SEND,
                                RLIN3_AS_IRQPRIO_TX,
                                RLIN3_LINS_AS_IRQSend );
          if( RLIN3_AS_IRQPRIO_RX != RLIN3_INTCLEAR )
            UARTStatus_bit &= RLIN3_CreateInterrupt( 
                                Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                                RLIN3_IRQ_RECEIVE,
                                RLIN3_AS_IRQPRIO_RX,
                                RLIN3_LINS_AS_IRQReceive );
          if( RLIN3_AS_IRQPRIO_ERR != RLIN3_INTCLEAR )
            UARTStatus_bit &= RLIN3_CreateInterrupt( 
                                Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                                RLIN3_IRQ_ERROR,
                                RLIN3_AS_IRQPRIO_ERR,
                                RLIN3_LINS_AS_IRQError );

          UARTStatus_bit &= RLIN3_LINSReceiveAction( 
                              Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08,
                              RLIN3_A_GETHEADER,
                              0,
                              RLIN3_AS_CSMODEL_DEFAULT );
          break;
        }
    
      if( UARTStatus_bit == RLIN3_OK ) 
      {
        WakeupLength[ Config->Unit[ CurrentUnit_u08 ]
                                    ->UnitNumber_u08 ] = 
                                    Config->Unit[ CurrentUnit_u08 ]
                                    ->WakeupLength_u08;

        switch( Config->Unit[ CurrentUnit_u08 ]->LINMode_u08 )
        {
          case RLIN3_MODE_LINMASTER:
            CurrentState[ Config->Unit[ CurrentUnit_u08 ]
                                        ->UnitNumber_u08 ] = LIN_OPERATIONAL;
            break;
            
          case RLIN3_MODE_LINSLAVE_FIX:
          case RLIN3_MODE_LINSLAVE_AUTO:
            CurrentState[ Config->Unit[ CurrentUnit_u08 ]
                                        ->UnitNumber_u08 ] = LIN_RX_BUSY;
            break;
        }
      }
    }
  }
}

//=============================================================================
// FunctionName: Lin_SendFrame
// IN  : Channel, PDU
// OUT : -
// Description : 
// Send PDU on channel
//=============================================================================

Std_ReturnType Lin_SendFrame( uint8 Channel, Lin_PduType *PduInfoPtr )
{
  bit UARTStatus_bit;
  u08 OperationMode_u08;
  
  if( ( CurrentState[ Channel ] == LIN_TX_BUSY ) ||
      ( CurrentState[ Channel ] == LIN_RX_BUSY ) ||
      ( CurrentState[ Channel ] == LIN_NOT_OK )  ||
      ( CurrentState[ Channel ] == LIN_CH_SLEEP ) )
  {
    return( E_NOT_OK );
  }
  
  UARTStatus_bit = RLIN3_LINSendMessage( ( u08 )Channel,
                                         ( u08 )PduInfoPtr->Pid,
                                         ( u08 )PduInfoPtr->Dl,
                                         ( u08 )PduInfoPtr->Cs,
                                         ( u08 )PduInfoPtr->Drc,
                                         ( pu08 )PduInfoPtr->SduPtr,
                                         &OperationMode_u08 );

  CurrentDl[ Channel ] = PduInfoPtr->Dl;

  switch( PduInfoPtr->Drc )
  {
     case LIN_MASTER_RESPONSE:
      if( OperationMode_u08 == RLIN3_MODE_LINMASTER )
      {
        CurrentState[ Channel ] = LIN_TX_BUSY;
      }
      else
      {
        CurrentState[ Channel ] = LIN_NOT_OK;
      }
      break;
      
     case LIN_SLAVE_RESPONSE:
     case LIN_SLAVE_TO_SLAVE:
      if( OperationMode_u08 == RLIN3_MODE_LINMASTER )
      {
        CurrentState[ Channel ] = LIN_RX_BUSY;
      }
      else
      {
        CurrentState[ Channel ] = LIN_TX_BUSY;
      }
      break;
  }

  if( UARTStatus_bit == RLIN3_OK ) return( E_OK );
  else return( E_NOT_OK );
}

//=============================================================================
// FunctionName: Lin_GetFrame
// IN  : Channel
// OUT : -
// Description : 
// Receive next response on channel
//=============================================================================

Std_ReturnType Lin_GetFrame( uint8                Channel, 
                             Lin_FrameDlType      Length, 
                             Lin_FrameCsModelType ChecksumType )
{
  bit UARTStatus_bit;

  UARTStatus_bit = RLIN3_LINSReceiveAction( Channel,
                                            RLIN3_A_GETMESSAGE,
                                            ( u08 )Length,
                                            ( u08 )( ( ChecksumType == LIN_ENHANCED_CS ) ? 
                                            RLIN3_CHECKSUM_ENHANCED : 
                                            RLIN3_CHECKSUM_CLASSIC ) );
  if( UARTStatus_bit == RLIN3_OK )
  {
    CurrentState[ Channel ] = LIN_RX_BUSY;
    return( E_OK );
  }
  else
  {
    CurrentState[ Channel ] = LIN_NOT_OK;
    return( E_NOT_OK );
  }
}

//=============================================================================
// FunctionName: Lin_SkipFrame
// IN  : Channel
// OUT : -
// Description : 
// Skip next response on channel
//=============================================================================

Std_ReturnType Lin_SkipFrame( uint8 Channel )
{
  bit UARTStatus_bit;

  UARTStatus_bit = RLIN3_LINSReceiveAction( Channel,
                                            RLIN3_A_SKIPMESSAGE,
                                            0,
                                            RLIN3_AS_CSMODEL_DEFAULT );
  if( UARTStatus_bit == RLIN3_OK )
  {
    CurrentState[ Channel ] = LIN_RX_BUSY;
    return( E_OK );
  }
  else
  {
    CurrentState[ Channel ] = LIN_NOT_OK;
    return( E_NOT_OK );
  }
}

//=============================================================================
// FunctionName: Lin_GetStatus
// IN  : Channel, SDU pointer
// OUT : -
// Description : 
// Get LIN status and receive SDU from channel
//=============================================================================

Lin_StatusType Lin_GetStatus( uint8 Channel, uint8 *LinSduPtr )
{
  bit UARTStatus_bit;
  u08 ByteCounter_u08;
  u08 LINBuffer[ RLIN3_LINDATALEN_MAX ];
  
  Lin_StatusType CurrentStateFlag;
  
  CurrentStateFlag = CurrentState[ Channel ];
  
  if( ( CurrentStateFlag == LIN_TX_HEADER_ERROR ) ||
      ( CurrentStateFlag == LIN_TX_ERROR )        ||
      ( CurrentStateFlag == LIN_RX_ERROR )        ||
      ( CurrentStateFlag == LIN_RX_NO_RESPONSE ) )
  {
    CurrentState[ Channel ] = LIN_OPERATIONAL;
  }
  
  if( CurrentStateFlag == LIN_RX_OK )
  {
    UARTStatus_bit = RLIN3_LINReceiveMessage( Channel,
                                              CurrentDl[ Channel ],
                                              &LINBuffer[ 0 ] );
    if( UARTStatus_bit == RLIN3_OK )
    {
      for( ByteCounter_u08 = 0;
           ByteCounter_u08 < CurrentDl[ Channel ];
           ByteCounter_u08++ )
      {
        *LinSduPtr = LINBuffer[ ByteCounter_u08 ];
        LinSduPtr++;
      }
      return( CurrentStateFlag );
    }
    else
    {
      return( LIN_NOT_OK );
    }
  }
  else
  {
    return( CurrentStateFlag );
  }
}

//=============================================================================
// FunctionName: Lin_CheckWakeup
// IN  : Channel
// OUT : -
// Description : 
// Get LIN wakeup status
//=============================================================================

Std_ReturnType Lin_CheckWakeup( uint8 Channel )
{
  if( CurrentState[ Channel ] == LIN_CH_SLEEP ) return( E_NOT_OK );
  else return( E_OK );
}

//=============================================================================
// FunctionName: Lin_GoToSleep
// IN  : Channel
// OUT : -
// Description : 
// Set LIN channel in sleep mode
//=============================================================================

Std_ReturnType Lin_GoToSleep( uint8 Channel )
{
  bit UARTStatus_bit;  
  
  UARTStatus_bit = RLIN3_LINReceiveWakeup( ( u08 )Channel );
  
  if( UARTStatus_bit == RLIN3_OK )
  {
    CurrentState[ Channel ] = LIN_CH_SLEEP;
    return( E_OK );
  }
  else
  {
    CurrentState[ Channel ] = LIN_NOT_OK;
    return( E_NOT_OK );
  }
}

//=============================================================================
// FunctionName: Lin_Wakeup
// IN  : Channel
// OUT : -
// Description : 
// Set LIN channel in active mode, send wake up frame
//=============================================================================

Std_ReturnType Lin_Wakeup( uint8 Channel )
{
  bit UARTStatus_bit;  
  
  UARTStatus_bit = RLIN3_LINSendWakeup( ( u08 )Channel,
                                        WakeupLength[ Channel ] );
                                        
  if( UARTStatus_bit == RLIN3_OK )
  {
    CurrentState[ Channel ] = LIN_OPERATIONAL;
    return( E_OK );
  }
  else
  {
    CurrentState[ Channel ] = LIN_NOT_OK;
    return( E_NOT_OK );
  }
}
