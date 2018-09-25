//============================================================================
// PROJECT = RSCFD Type RSCFDFD_UCIAPRCN_V3
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2002 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RSCFD Low Level Driver
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
// Environment: Devices:          All featuring RSCFDFD_UCIAPRCN_V3
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#define DRIVER_LOCAL

#include <ree_types.h>
#include <stddef.h>

#ifdef VLIB
#include <config_rscfd.h>
#include <standardports_p.h>
#include <ql85e70x_p.h>

#else
#include <map_rscfd.h>
#include <map_ports.h>
#include <map_asmn_basic.h>
//#include <ports\standardports\standardports_p.h>
#include <standardports_p.h>
#endif

#if( EE_RSCFD_MACROS > 2 )
#error "NUMBER OF UNITS NOT SUPPORTED"
#endif

#ifdef EE_RSCFD_INT_BUNDLINGHOOK
extern void EE_RSCFD_INT_BUNDLINGHOOK( u08, 
                                       u08 *, u08 *, u08 *, u08 *, u08 *, u08 *,
                                       u08 *, u08 *, u08 * );
#endif


u32* testsfrAddress;
u32 testsfrValue;
float testValue;

/*
 * CreateInterrupt() Jump Vector Table
 */
 

#if( EE_RSCFD_MACROS == 1 )

void EE_RSCFD_IRQDefault( );
void EE_RSCFD_CH0_RXF();
void EE_RSCFD_GetMessageRF( struct ee_rscfd_r_rfmsg *Buffer,
                            struct ee_rscfd_message *Message );

static void ( *EE_RSCFD_CIVector [ ( EE_RSCFD_MACROS * 
       			                       ( EE_RSCFD_INT_GLOBAL + 
            		                     EE_RSCFD_INT_CHANNEL * 
            		                     EE_RSCFD_MAXCHANNELS ) ) ] )( ) =
	{
		EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault
	};

#endif

#if( EE_RSCFD_MACROS == 2 )

static void ( *EE_RSCFD_CIVector [ ( EE_RSCFD_MACROS * 
       			                       ( EE_RSCFD_INT_GLOBAL + 
            		                     EE_RSCFD_INT_CHANNEL * 
            		                     EE_RSCFD_MAXCHANNELS ) ) ] )( ) =
	{
		EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault,
		EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault, EE_RSCFD_IRQDefault
	};

#endif

/*
 * Global Variables 
 */

/* Number of interrupt vector */

u08 EE_RSCFD_InterruptFlag_Unit_u08     = 0;

u08 EE_RSCFD_InterruptFlag_Global_u08   = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_InterruptFlag_Channel0_u08 = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_InterruptFlag_Channel1_u08 = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_InterruptFlag_Channel2_u08 = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_InterruptFlag_Channel3_u08 = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_InterruptFlag_Channel4_u08 = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_InterruptFlag_Channel5_u08 = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_InterruptFlag_Channel6_u08 = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_InterruptFlag_Channel7_u08 = EE_RSCFD_INT_NOINT;

u08 EE_RSCFD_LastErrorCode_Global_u08   = EE_RSCFD_GINT_NONE;
u08 EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_MAXCHANNELS ] =
	{ EE_RSCFD_INT_NOINT, EE_RSCFD_INT_NOINT, EE_RSCFD_INT_NOINT, EE_RSCFD_INT_NOINT,
	  EE_RSCFD_INT_NOINT, EE_RSCFD_INT_NOINT, EE_RSCFD_INT_NOINT, EE_RSCFD_INT_NOINT };
u16 EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_MAXCHANNELS ] = 
	{ EE_RSCFD_ERROR_CLEARALL, EE_RSCFD_ERROR_CLEARALL, EE_RSCFD_ERROR_CLEARALL, EE_RSCFD_ERROR_CLEARALL,
	  EE_RSCFD_ERROR_CLEARALL, EE_RSCFD_ERROR_CLEARALL, EE_RSCFD_ERROR_CLEARALL, EE_RSCFD_ERROR_CLEARALL };

u08 EE_RSCFD_LastTxObjectChannel0_u08   = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_LastTxObjectChannel1_u08   = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_LastTxObjectChannel2_u08   = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_LastTxObjectChannel3_u08   = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_LastTxObjectChannel4_u08   = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_LastTxObjectChannel5_u08   = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_LastTxObjectChannel6_u08   = EE_RSCFD_INT_NOINT;
u08 EE_RSCFD_LastTxObjectChannel7_u08   = EE_RSCFD_INT_NOINT;


/*
 * Internal Support Functions
 */
 
void EE_RSCFD_IRQDefault( )
{
}

/* rx fifo 0 interrupt routine@titron */
void EE_RSCFD_CH0_RXF()
{
	ee_rscfd_message tempMsg;
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	u08 SendStatus_u08;

    /* Read received message */
	EE_RSCFD_GetMessageRF( &ee_rscfd_rxfifo_p[ 0 ]->buf[ 0 ],
												  &tempMsg );

    /* Transmit the received message */
	tempMsg.path = EE_RSCFD_PATH_MSGBOX; /* Send via Message Box */
	tempMsg.pathdetail = EE_RSCFD_PATHDETAIL_ANY; /* use any box... */
	EE_RSCFD_Status_bit &= EE_RSCFD_SendMessage(0, 0,
				&SendStatus_u08, &tempMsg );
}
extern struct ee_rscfd_message SendMessage;
void EE_RSCFD_CH0_tx()
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	u08 SendStatus_u08;

	EE_RSCFD_Status_bit &= EE_RSCFD_SendMessage(0, 0,
				&SendStatus_u08, &SendMessage);
}
void EE_RSCFD_CH7_tx()
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	u08 SendStatus_u08;

	EE_RSCFD_Status_bit &= EE_RSCFD_SendMessage(0, 7,
				&SendStatus_u08, &SendMessage);
}

                                  
u08 EE_RSCFD_GetTxBuffer( u32 FlagRegister_u32 )
{
	u08 CurrentScan_u08;
	
	for( CurrentScan_u08 = 0; 
			 CurrentScan_u08 < EE_RSCFD_MAXTXBUFFERS;
			 CurrentScan_u08++ )
	{
		if( ( ( FlagRegister_u32 >> CurrentScan_u08 ) & 0x01 ) == 0x01 )
		{
			return( CurrentScan_u08 );
		}
	}
	return( EE_RSCFD_INT_NOINT );
}   

u08 EE_RSCFD_GetComFIFOIntStatus( u08 UnitNumber_u08,
                                  u08 ChannelNumber_u08,
                                  u08 InterruptType_u08 )
{
	u32 FlagSet_u32;
	u08 FlagFirst_u08;
	
	switch( InterruptType_u08 )
	{
		case EE_RSCFD_INT_RXCF:
			FlagSet_u32 = ( u32 )( ee_rscfd_common_p[ UnitNumber_u08 ]->cfrists );
    	for( FlagFirst_u08 = 0;
    			 FlagFirst_u08 < EE_RSCFD_MAXRXFIFOS;
    			 FlagFirst_u08++ )
    	{
    		if( FlagSet_u32 & ( 1 << FlagFirst_u08 ) )
    			return( FlagFirst_u08 );
    	}
			break;
		case EE_RSCFD_INT_TXCF:
			FlagSet_u32 = ( u32 )( ee_rscfd_common_p[ UnitNumber_u08 ]->cftists );
    	for( FlagFirst_u08 = ( EE_RSCFD_MAXCOMFIFOS * ChannelNumber_u08 );
    			 FlagFirst_u08 < ( EE_RSCFD_MAXCOMFIFOS * ( ChannelNumber_u08 + 1 ) );
    			 FlagFirst_u08++ )
    	{
    		if( FlagSet_u32 & ( 1 << FlagFirst_u08 ) )
    			return( FlagFirst_u08 );
    	}
			break;
	}
	
	return( EE_RSCFD_GLOBAL );
}

void EE_RSCFD_SetIDData( struct ee_rscfd_t_msg   *Buffer,
                         struct ee_rscfd_message *Message )
{
  u08 DataCount_u08;
  u08 DataCountMax_u08;
  
  if( Message->flag.dlc <= EE_RSCFD_DLC_CMAX )
  {
    DataCountMax_u08 = Message->flag.dlc;
  }
  else
  {
    switch( Message->flag.dlc )
    {
      case EE_RSCFD_DLC_FD_12: DataCountMax_u08 = 12; break;
      case EE_RSCFD_DLC_FD_16: DataCountMax_u08 = 16; break;
      case EE_RSCFD_DLC_FD_20: DataCountMax_u08 = 20; break;
      case EE_RSCFD_DLC_FD_24: DataCountMax_u08 = 24; break;
      case EE_RSCFD_DLC_FD_32: DataCountMax_u08 = 32; break;
      case EE_RSCFD_DLC_FD_48: DataCountMax_u08 = 48; break;
      case EE_RSCFD_DLC_FD_64: DataCountMax_u08 = 64; break;
      default:                 DataCountMax_u08 = 64; break;
    }
  }

  Buffer->id.id    = Message->hdr.id;
  Buffer->id.thlen = Message->hdr.thlen;
  Buffer->id.rtr   = Message->hdr.rtr;
  Buffer->id.ide   = Message->hdr.ide;

  for( DataCount_u08 = 0;
       DataCount_u08 < DataCountMax_u08;
       DataCount_u08++ )
  {
    if( ( DataCount_u08 % 4 ) == 0 )
    {
      Buffer->data[ DataCount_u08 / 4 ] = 0L;
    }
    Buffer->data[ DataCount_u08 / 4 ] += ( u32 )( Message->data[ DataCount_u08 ] 
                                             << ( 8 * ( DataCount_u08 % 4 ) ) );
  }
  
  Buffer->ptr.dlc   = Message->flag.dlc;
  Buffer->fdsts.esi = Message->fdsts.esi;
  Buffer->fdsts.brs = Message->fdsts.brs;
  Buffer->fdsts.fdf = Message->fdsts.fdf;
  Buffer->fdsts.ptr = Message->fdsts.ptr;
}

void EE_RSCFD_SetIDDataCFIFO( struct ee_rscfd_r_cmsg  *Buffer,
                              struct ee_rscfd_message *Message )
{
  u08 DataCount_u08;
  u08 DataCountMax_u08;
  
  if( Message->flag.dlc <= EE_RSCFD_DLC_CMAX )
  {
    DataCountMax_u08 = Message->flag.dlc;
  }
  else
  {
    switch( Message->flag.dlc )
    {
      case EE_RSCFD_DLC_FD_12: DataCountMax_u08 = 12; break;
      case EE_RSCFD_DLC_FD_16: DataCountMax_u08 = 16; break;
      case EE_RSCFD_DLC_FD_20: DataCountMax_u08 = 20; break;
      case EE_RSCFD_DLC_FD_24: DataCountMax_u08 = 24; break;
      case EE_RSCFD_DLC_FD_32: DataCountMax_u08 = 32; break;
      case EE_RSCFD_DLC_FD_48: DataCountMax_u08 = 48; break;
      case EE_RSCFD_DLC_FD_64: DataCountMax_u08 = 64; break;
      default:                 DataCountMax_u08 = 64; break;
    }
  }

  Buffer->id.id    = Message->hdr.id;
  Buffer->id.thlen = Message->hdr.thlen;
  Buffer->id.rtr   = Message->hdr.rtr;
  Buffer->id.ide   = Message->hdr.ide;

  for( DataCount_u08 = 0;
       DataCount_u08 < DataCountMax_u08;
       DataCount_u08++ )
  {
    if( ( DataCount_u08 % 4 ) == 0 )
    {
      Buffer->data[ DataCount_u08 / 4 ] = 0L;
    }
    Buffer->data[ DataCount_u08 / 4 ] += ( u32 )( Message->data[ DataCount_u08 ] 
                                             << ( 8 * ( DataCount_u08 % 4 ) ) );
  }
  
  Buffer->ptr.dlc   = Message->flag.dlc;
  Buffer->fdsts.esi = Message->fdsts.esi;
  Buffer->fdsts.brs = Message->fdsts.brs;
  Buffer->fdsts.fdf = Message->fdsts.fdf;
  Buffer->fdsts.ptr = Message->fdsts.ptr;
}

void EE_RSCFD_GetMessage( struct ee_rscfd_r_rmsg  *Buffer,
                          struct ee_rscfd_message *Message )
{
  u08 DataCount_u08;
  u08 DataCountMax_u08;
  
  Message->flag.ts  = Buffer->ptr.ts;
  Message->flag.dlc = Buffer->ptr.dlc;

  Message->hdr.id  = Buffer->id.id;
  Message->hdr.rtr = Buffer->id.rtr;
  Message->hdr.ide = Buffer->id.ide;

  Message->fdsts.esi = Buffer->fdsts.esi;
  Message->fdsts.brs = Buffer->fdsts.brs;
  Message->fdsts.fdf = Buffer->fdsts.fdf;
  Message->fdsts.ptr = Buffer->fdsts.ptr;
  
  if( Message->flag.dlc <= EE_RSCFD_DLC_CMAX )
  {
    DataCountMax_u08 = Message->flag.dlc;
  }
  else
  {
    switch( Message->flag.dlc )
    {
      case EE_RSCFD_DLC_FD_12: DataCountMax_u08 = 12; break;
      case EE_RSCFD_DLC_FD_16: DataCountMax_u08 = 16; break;
      case EE_RSCFD_DLC_FD_20: DataCountMax_u08 = 20; break;
      case EE_RSCFD_DLC_FD_24: DataCountMax_u08 = 24; break;
      case EE_RSCFD_DLC_FD_32: DataCountMax_u08 = 32; break;
      case EE_RSCFD_DLC_FD_48: DataCountMax_u08 = 48; break;
      case EE_RSCFD_DLC_FD_64: DataCountMax_u08 = 64; break;
      default:                 DataCountMax_u08 = 64; break;
    }
  }

  for( DataCount_u08 = 0;
       DataCount_u08 < DataCountMax_u08;
       DataCount_u08++ )
  {
    Message->data[ DataCount_u08 ] = ( u08 )( Buffer->data[ DataCount_u08 / 4 ] 
                                                     >> ( ( DataCount_u08 % 4 ) * 8 ) );
  }  
}

void EE_RSCFD_GetMessageRF( struct ee_rscfd_r_rfmsg *Buffer,
                            struct ee_rscfd_message *Message )
{
  u08 DataCount_u08;
  u08 DataCountMax_u08;
  
  Message->flag.ts  = Buffer->ptr.ts;
  Message->flag.dlc = Buffer->ptr.dlc;

  Message->hdr.id  = Buffer->id.id;
  Message->hdr.rtr = Buffer->id.rtr;
  Message->hdr.ide = Buffer->id.ide;

  Message->fdsts.esi = Buffer->fdsts.esi;
  Message->fdsts.brs = Buffer->fdsts.brs;
  Message->fdsts.fdf = Buffer->fdsts.fdf;
  Message->fdsts.ptr = Buffer->fdsts.ptr;
  
  if( Message->flag.dlc <= EE_RSCFD_DLC_CMAX )
  {
    DataCountMax_u08 = Message->flag.dlc;
  }
  else
  {
    switch( Message->flag.dlc )
    {
      case EE_RSCFD_DLC_FD_12: DataCountMax_u08 = 12; break;
      case EE_RSCFD_DLC_FD_16: DataCountMax_u08 = 16; break;
      case EE_RSCFD_DLC_FD_20: DataCountMax_u08 = 20; break;
      case EE_RSCFD_DLC_FD_24: DataCountMax_u08 = 24; break;
      case EE_RSCFD_DLC_FD_32: DataCountMax_u08 = 32; break;
      case EE_RSCFD_DLC_FD_48: DataCountMax_u08 = 48; break;
      case EE_RSCFD_DLC_FD_64: DataCountMax_u08 = 64; break;
      default:                 DataCountMax_u08 = 64; break;
    }
  }

  for( DataCount_u08 = 0;
       DataCount_u08 < DataCountMax_u08;
       DataCount_u08++ )
  {
    Message->data[ DataCount_u08 ] = ( u08 )( Buffer->data[ DataCount_u08 / 4 ] 
                                                     >> ( ( DataCount_u08 % 4 ) * 8 ) );
  }  
}

void EE_RSCFD_GetMessageCF( struct ee_rscfd_r_cmsg  *Buffer,
                            struct ee_rscfd_message *Message )
{
  u08 DataCount_u08;
  u08 DataCountMax_u08;
  
  Message->flag.ts  = Buffer->ptr.ts;
  Message->flag.dlc = Buffer->ptr.dlc;

  Message->hdr.id  = Buffer->id.id;
  Message->hdr.rtr = Buffer->id.rtr;
  Message->hdr.ide = Buffer->id.ide;

  Message->fdsts.esi = Buffer->fdsts.esi;
  Message->fdsts.brs = Buffer->fdsts.brs;
  Message->fdsts.fdf = Buffer->fdsts.fdf;
  Message->fdsts.ptr = Buffer->fdsts.ptr;
  
  if( Message->flag.dlc <= EE_RSCFD_DLC_CMAX )
  {
    DataCountMax_u08 = Message->flag.dlc;
  }
  else
  {
    switch( Message->flag.dlc )
    {
      case EE_RSCFD_DLC_FD_12: DataCountMax_u08 = 12; break;
      case EE_RSCFD_DLC_FD_16: DataCountMax_u08 = 16; break;
      case EE_RSCFD_DLC_FD_20: DataCountMax_u08 = 20; break;
      case EE_RSCFD_DLC_FD_24: DataCountMax_u08 = 24; break;
      case EE_RSCFD_DLC_FD_32: DataCountMax_u08 = 32; break;
      case EE_RSCFD_DLC_FD_48: DataCountMax_u08 = 48; break;
      case EE_RSCFD_DLC_FD_64: DataCountMax_u08 = 64; break;
      default:                 DataCountMax_u08 = 64; break;
    }
  }

  for( DataCount_u08 = 0;
       DataCount_u08 < DataCountMax_u08;
       DataCount_u08++ )
  {
    Message->data[ DataCount_u08 ] = ( u08 )( Buffer->data[ DataCount_u08 / 4 ] 
                                                     >> ( ( DataCount_u08 % 4 ) * 8 ) );
  }  
}

/*
 * The interrupt Functions
 */


//=============================================================================
// FunctionName: RSCFD_Interrupt
// IN  :         -
// OUT :         -
// Description : Central Interrupt Entry, clears pending bits and stores status
// 
//=============================================================================
void EE_RSCFD_Interrupt( )
{     
	u08 FIFONumber_u08;
	u08 UnitNumber_u08;
	
	UnitNumber_u08 = EE_RSCFD_InterruptFlag_Unit_u08;
	
#ifdef EE_RSCFD_INT_BUNDLINGHOOK

    EE_RSCFD_INT_BUNDLINGHOOK( UnitNumber_u08,
                               &EE_RSCFD_InterruptFlag_Global_u08,
                               &EE_RSCFD_InterruptFlag_Channel0_u08,
                               &EE_RSCFD_InterruptFlag_Channel1_u08,
                               &EE_RSCFD_InterruptFlag_Channel2_u08,
							                 &EE_RSCFD_InterruptFlag_Channel3_u08,
              							   &EE_RSCFD_InterruptFlag_Channel4_u08,
              							   &EE_RSCFD_InterruptFlag_Channel5_u08,
              							   &EE_RSCFD_InterruptFlag_Channel6_u08,
              							   &EE_RSCFD_InterruptFlag_Channel7_u08 );

#endif
	
  /* Handling of Unit 0 */

  if( EE_RSCFD_InterruptFlag_Global_u08 != EE_RSCFD_INT_NOINT )
    {
      switch( EE_RSCFD_InterruptFlag_Global_u08 )
        {
        	case EE_RSCFD_INT_GERR:
          	EE_RSCFD_LastErrorCode_Global_u08 = ee_rscfd_common_p[ UnitNumber_u08 ]->gerfl.err;
          	ee_rscfd_common_p[ UnitNumber_u08 ]->gerfl.err  = EE_RSCFD_GINT_NONE;
            for( FIFONumber_u08 = 0;
                 FIFONumber_u08 < EE_RSCFD_MAXRXFIFOS;
                 FIFONumber_u08++ )
            {
  	        	if( ee_rscfd_common_p[ UnitNumber_u08 ]->rfsts[ FIFONumber_u08 ].rfmlt )
  	          {
  	        		EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GINT_MSGLOST;
  	        		ee_rscfd_common_p[ UnitNumber_u08 ]->rfsts[ FIFONumber_u08 ].rfmlt = 0;
  	        	}
  	        }
            for( FIFONumber_u08 = 0;
                 FIFONumber_u08 < ( EE_RSCFD_MAXCOMFIFOS * EE_RSCFD_MAXCHANNELS );
                 FIFONumber_u08++ )
            {
    	      	if( ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfmlt )
  	      		{
  	      			EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GINT_MSGLOST;
  	      			ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfmlt = 0;
  	      		}
  	      	}
          	EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
          	break;
        	case EE_RSCFD_INT_RXF0:
        	case EE_RSCFD_INT_RXF1:
        	case EE_RSCFD_INT_RXF2:
        	case EE_RSCFD_INT_RXF3:
        	case EE_RSCFD_INT_RXF4:
	        case EE_RSCFD_INT_RXF5:
	        case EE_RSCFD_INT_RXF6:
	        case EE_RSCFD_INT_RXF7:
	        	FIFONumber_u08 = EE_RSCFD_InterruptFlag_Global_u08 - EE_RSCFD_INT_RXF0;
	        		ee_rscfd_common_p[ UnitNumber_u08 ]->rfsts[ FIFONumber_u08 ].rfif = 0;
	        		EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_RXF0 + FIFONumber_u08 ]( );
	          break;
	        default:
	        	break;
        }
      EE_RSCFD_InterruptFlag_Global_u08 = EE_RSCFD_INT_NOINT;
    }
  else if( EE_RSCFD_InterruptFlag_Channel0_u08 != EE_RSCFD_INT_NOINT )
    {
    	EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_CHANNEL0 ] =
    		EE_RSCFD_InterruptFlag_Channel0_u08;
    		
    	switch( EE_RSCFD_InterruptFlag_Channel0_u08 )
    	{
    		case EE_RSCFD_INT_TX:
    			EE_RSCFD_LastTxObjectChannel0_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtcsts[ EE_RSCFD_CHANNEL0 ]);
    			if( EE_RSCFD_LastTxObjectChannel0_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel0_u08 ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TX + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL0 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXA:
    			EE_RSCFD_LastTxObjectChannel0_u08 =
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtasts[ EE_RSCFD_CHANNEL0 ]);
    			if( EE_RSCFD_LastTxObjectChannel0_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel0_u08 ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXA + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL0 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXQ0:
    			EE_RSCFD_LastTxObjectChannel0_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL0 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL0 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ0 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL0 ) ]( );
					break;
    		case EE_RSCFD_INT_TXQ1:
    			EE_RSCFD_LastTxObjectChannel0_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL0 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL0 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ1 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL0 ) ]( );
					break;
				case EE_RSCFD_INT_CERR:
					EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_CHANNEL0 ] = 
						( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL0 ].erfl.err );
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_CERR + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL0 ) ]( );
					ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL0 ].erfl.err = EE_RSCFD_ERROR_CLEARALL;
					break;
				case EE_RSCFD_INT_TXHL:
					ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL0 ].irq = 0;
					if( ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL0 ].elt )
					{
						ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL0 ].elt = 0;
						EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GERROR_THLLOST;
						EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
					}
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXHL + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL0 ) ]( );
					break;
				case EE_RSCFD_INT_RXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL0, EE_RSCFD_INT_RXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_RXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL0 ) ]( );
					break;
				case EE_RSCFD_INT_TXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL0, EE_RSCFD_INT_TXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL0 ) ]( );
					break;
    	}
        EE_RSCFD_InterruptFlag_Channel0_u08 = EE_RSCFD_INT_NOINT;
    }
  else if( EE_RSCFD_InterruptFlag_Channel1_u08 != EE_RSCFD_INT_NOINT )
    {
    	EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_CHANNEL1 ] =
    		EE_RSCFD_InterruptFlag_Channel1_u08;

    	switch( EE_RSCFD_InterruptFlag_Channel1_u08 )
    	{
    		case EE_RSCFD_INT_TX:
    			EE_RSCFD_LastTxObjectChannel1_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtcsts[ EE_RSCFD_CHANNEL1 ] );
    			if( EE_RSCFD_LastTxObjectChannel1_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel1_u08 
	    			                              + EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TX + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL1 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXA:
    			EE_RSCFD_LastTxObjectChannel1_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtasts[ EE_RSCFD_CHANNEL1 ] );
    			if( EE_RSCFD_LastTxObjectChannel1_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel1_u08
	    			                              + EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXA + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL1 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXQ0:
    			EE_RSCFD_LastTxObjectChannel1_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL1 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL1 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ0 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL1 ) ]( );
					break;
    		case EE_RSCFD_INT_TXQ1:
    			EE_RSCFD_LastTxObjectChannel1_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL1 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL1 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ1 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL1 ) ]( );
					break;
				case EE_RSCFD_INT_CERR:
					EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_CHANNEL1 ] = 
						( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL1 ].erfl.err );
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_CERR + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL1 ) ]( );
					ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL1 ].erfl.err = EE_RSCFD_ERROR_CLEARALL;
					break;
				case EE_RSCFD_INT_TXHL:
					ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL1 ].irq = 0;
					if( ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL1 ].elt )
					{
						ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL1 ].elt = 0;
						EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GERROR_THLLOST;
						EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
					}
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXHL + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL1 ) ]( );
					break;
				case EE_RSCFD_INT_RXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL1, EE_RSCFD_INT_RXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_RXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL1 ) ]( );
					break;
				case EE_RSCFD_INT_TXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL1, EE_RSCFD_INT_TXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL1 ) ]( );
					break;
    	}
        EE_RSCFD_InterruptFlag_Channel1_u08 = EE_RSCFD_INT_NOINT;
    }
  else if( EE_RSCFD_InterruptFlag_Channel2_u08 != EE_RSCFD_INT_NOINT )
    {
    	EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_CHANNEL2 ] =
    		EE_RSCFD_InterruptFlag_Channel2_u08;

    	switch( EE_RSCFD_InterruptFlag_Channel2_u08 )
    	{
    		case EE_RSCFD_INT_TX:
    			EE_RSCFD_LastTxObjectChannel2_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtcsts[ EE_RSCFD_CHANNEL2 ]);
    			if( EE_RSCFD_LastTxObjectChannel2_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel2_u08
	    			                              + 2 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TX + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL2 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXA:
    			EE_RSCFD_LastTxObjectChannel2_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtasts[ EE_RSCFD_CHANNEL2 ]);
    			if( EE_RSCFD_LastTxObjectChannel2_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel2_u08
	    			                              + 2 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXA + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL2 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXQ0:
    			EE_RSCFD_LastTxObjectChannel2_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL2 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL2 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ0 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL2 ) ]( );
					break;
    		case EE_RSCFD_INT_TXQ1:
    			EE_RSCFD_LastTxObjectChannel2_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL2 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL2 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ1 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL2 ) ]( );
					break;
				case EE_RSCFD_INT_CERR:
					EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_CHANNEL2 ] = 
						( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL2 ].erfl.err );
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_CERR + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL2 ) ]( );
					ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL2 ].erfl.err = EE_RSCFD_ERROR_CLEARALL;
					break;
				case EE_RSCFD_INT_TXHL:
					ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL2 ].irq = 0;
					if( ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL2 ].elt )
					{
						ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL2 ].elt = 0;
						EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GERROR_THLLOST;
						EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
					}
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXHL + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL2 ) ]( );
					break;
				case EE_RSCFD_INT_RXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL2, EE_RSCFD_INT_RXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_RXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL2 ) ]( );
					break;
				case EE_RSCFD_INT_TXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL2, EE_RSCFD_INT_TXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL2 ) ]( );
					break;
    	}
        EE_RSCFD_InterruptFlag_Channel2_u08 = EE_RSCFD_INT_NOINT;
    }
  else if( EE_RSCFD_InterruptFlag_Channel3_u08 != EE_RSCFD_INT_NOINT )
    {
    	EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_CHANNEL3 ] =
    		EE_RSCFD_InterruptFlag_Channel3_u08;
    		
    	switch( EE_RSCFD_InterruptFlag_Channel3_u08 )
    	{
    		case EE_RSCFD_INT_TX:
    			EE_RSCFD_LastTxObjectChannel3_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtcsts[ EE_RSCFD_CHANNEL3 ] );
    			if( EE_RSCFD_LastTxObjectChannel3_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel3_u08 
	    			                                          + 3 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TX + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL3 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXA:
    			EE_RSCFD_LastTxObjectChannel3_u08 =
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtasts[ EE_RSCFD_CHANNEL3 ] );
    			if( EE_RSCFD_LastTxObjectChannel3_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel3_u08 
	    			                                          + 3 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXA + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL3 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXQ0:
    			EE_RSCFD_LastTxObjectChannel3_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL3 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL3 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ0 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL3 ) ]( );
					break;
    		case EE_RSCFD_INT_TXQ1:
    			EE_RSCFD_LastTxObjectChannel3_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL3 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL3 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ1 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL3 ) ]( );
					break;
				case EE_RSCFD_INT_CERR:
					EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_CHANNEL3 ] = 
						( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL3 ].erfl.err );
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_CERR + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL3 ) ]( );
					ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL3 ].erfl.err = EE_RSCFD_ERROR_CLEARALL;
					break;
				case EE_RSCFD_INT_TXHL:
					ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL3 ].irq = 0;
					if( ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL3 ].elt )
					{
						ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL3 ].elt = 0;
						EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GERROR_THLLOST;
						EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
					}
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXHL + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL3 ) ]( );
					break;
				case EE_RSCFD_INT_RXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL3, EE_RSCFD_INT_RXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_RXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL3 ) ]( );
					break;
				case EE_RSCFD_INT_TXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL3, EE_RSCFD_INT_TXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL3 ) ]( );
					break;
    	}
        EE_RSCFD_InterruptFlag_Channel3_u08 = EE_RSCFD_INT_NOINT;
    }
    
  else if( EE_RSCFD_InterruptFlag_Channel4_u08 != EE_RSCFD_INT_NOINT )
    {
    	EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_CHANNEL4 ] =
    		EE_RSCFD_InterruptFlag_Channel4_u08;
    		
    	switch( EE_RSCFD_InterruptFlag_Channel4_u08 )
    	{
    		case EE_RSCFD_INT_TX:
    			EE_RSCFD_LastTxObjectChannel4_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtcsts[ EE_RSCFD_CHANNEL4 ]);
    			if( EE_RSCFD_LastTxObjectChannel4_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel4_u08 
	    			                                      + 4 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TX + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL4 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXA:
    			EE_RSCFD_LastTxObjectChannel4_u08 =
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtasts[ EE_RSCFD_CHANNEL4 ]);
    			if( EE_RSCFD_LastTxObjectChannel4_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel4_u08 
	    			                                      + 4 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXA + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL4 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXQ0:
    			EE_RSCFD_LastTxObjectChannel4_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL4 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL4 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ0 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL4 ) ]( );
					break;
    		case EE_RSCFD_INT_TXQ1:
    			EE_RSCFD_LastTxObjectChannel4_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL4 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL4 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ1 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL4 ) ]( );
					break;
				case EE_RSCFD_INT_CERR:
					EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_CHANNEL4 ] = 
						( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL4 ].erfl.err );
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_CERR + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL4 ) ]( );
					ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL4 ].erfl.err = EE_RSCFD_ERROR_CLEARALL;
					break;
				case EE_RSCFD_INT_TXHL:
					ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL4 ].irq = 0;
					if( ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL4 ].elt )
					{
						ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL4 ].elt = 0;
						EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GERROR_THLLOST;
						EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
					}
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXHL + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL4 ) ]( );
					break;
				case EE_RSCFD_INT_RXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL4, EE_RSCFD_INT_RXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_RXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL4 ) ]( );
					break;
				case EE_RSCFD_INT_TXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL4, EE_RSCFD_INT_TXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL4 ) ]( );
					break;
    	}
        EE_RSCFD_InterruptFlag_Channel4_u08 = EE_RSCFD_INT_NOINT;
    }
  else if( EE_RSCFD_InterruptFlag_Channel5_u08 != EE_RSCFD_INT_NOINT )
    {
    	EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_CHANNEL5 ] =
    		EE_RSCFD_InterruptFlag_Channel5_u08;

    	switch( EE_RSCFD_InterruptFlag_Channel5_u08 )
    	{
    		case EE_RSCFD_INT_TX:
    			EE_RSCFD_LastTxObjectChannel5_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtcsts[ EE_RSCFD_CHANNEL5 ] );
    			if( EE_RSCFD_LastTxObjectChannel5_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel5_u08 
	    			                              + 5 * EE_RSCFD_MAXTXBUFFERS  ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TX + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL5 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXA:
    			EE_RSCFD_LastTxObjectChannel5_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtasts[ EE_RSCFD_CHANNEL5 ] );
    			if( EE_RSCFD_LastTxObjectChannel1_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel5_u08
	    			                              + 5 * EE_RSCFD_MAXTXBUFFERS  ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXA + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL5 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXQ0:
    			EE_RSCFD_LastTxObjectChannel5_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL5 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL5 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ0 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL5 ) ]( );
					break;
    		case EE_RSCFD_INT_TXQ1:
    			EE_RSCFD_LastTxObjectChannel5_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL5 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL5 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ1 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL5 ) ]( );
					break;
				case EE_RSCFD_INT_CERR:
					EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_CHANNEL5 ] = 
						( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL5 ].erfl.err );
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_CERR + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL5 ) ]( );
					ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL5 ].erfl.err = EE_RSCFD_ERROR_CLEARALL;
					break;
				case EE_RSCFD_INT_TXHL:
					ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL5 ].irq = 0;
					if( ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL5 ].elt )
					{
						ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL5 ].elt = 0;
						EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GERROR_THLLOST;
						EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
					}
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXHL + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL5 ) ]( );
					break;
				case EE_RSCFD_INT_RXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL5, EE_RSCFD_INT_RXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_RXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL5 ) ]( );
					break;
				case EE_RSCFD_INT_TXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL5, EE_RSCFD_INT_TXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL5 ) ]( );
					break;
    	}
        EE_RSCFD_InterruptFlag_Channel5_u08 = EE_RSCFD_INT_NOINT;
    }
  else if( EE_RSCFD_InterruptFlag_Channel6_u08 != EE_RSCFD_INT_NOINT )
    {
    	EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_CHANNEL6 ] =
    		EE_RSCFD_InterruptFlag_Channel6_u08;

    	switch( EE_RSCFD_InterruptFlag_Channel6_u08 )
    	{
    		case EE_RSCFD_INT_TX:
    			EE_RSCFD_LastTxObjectChannel6_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtcsts[ EE_RSCFD_CHANNEL6 ] );
    			if( EE_RSCFD_LastTxObjectChannel6_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel6_u08
	    			                              + 6 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TX + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL6 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXA:
    			EE_RSCFD_LastTxObjectChannel6_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtasts[ EE_RSCFD_CHANNEL6 ] );
    			if( EE_RSCFD_LastTxObjectChannel6_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel6_u08
	    			                              + 6 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXA + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL6 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXQ0:
    			EE_RSCFD_LastTxObjectChannel6_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL6 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL6 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ0 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL6 ) ]( );
					break;
    		case EE_RSCFD_INT_TXQ1:
    			EE_RSCFD_LastTxObjectChannel6_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL6 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL6 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ1 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL6 ) ]( );
					break;
				case EE_RSCFD_INT_CERR:
					EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_CHANNEL6 ] = 
						( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL6 ].erfl.err );
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_CERR + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL6 ) ]( );
					ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL6 ].erfl.err = EE_RSCFD_ERROR_CLEARALL;
					break;
				case EE_RSCFD_INT_TXHL:
					ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL6 ].irq = 0;
					if( ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL2 ].elt )
					{
						ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL6 ].elt = 0;
						EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GERROR_THLLOST;
						EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
					}
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXHL + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL6 ) ]( );
					break;
				case EE_RSCFD_INT_RXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL6, EE_RSCFD_INT_RXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_RXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL6 ) ]( );
					break;
				case EE_RSCFD_INT_TXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL6, EE_RSCFD_INT_TXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL6 ) ]( );
					break;
    	}
        EE_RSCFD_InterruptFlag_Channel6_u08 = EE_RSCFD_INT_NOINT;
    }
  else if( EE_RSCFD_InterruptFlag_Channel7_u08 != EE_RSCFD_INT_NOINT )
    {
    	EE_RSCFD_InterruptFlag_Channel_u08[ EE_RSCFD_CHANNEL7 ] =
    		EE_RSCFD_InterruptFlag_Channel7_u08;
    		
    	switch( EE_RSCFD_InterruptFlag_Channel7_u08 )
    	{
    		case EE_RSCFD_INT_TX:
    			EE_RSCFD_LastTxObjectChannel7_u08 = 
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtcsts[ EE_RSCFD_CHANNEL7 ] );
    			if( EE_RSCFD_LastTxObjectChannel7_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel7_u08 
	    			                                      + 7 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TX + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL7 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXA:
    			EE_RSCFD_LastTxObjectChannel7_u08 =
    				EE_RSCFD_GetTxBuffer( ee_rscfd_common_p[ UnitNumber_u08 ]->tmtasts[ EE_RSCFD_CHANNEL7 ] );
    			if( EE_RSCFD_LastTxObjectChannel7_u08 != EE_RSCFD_INT_NOINT )
    			{
	    			ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts[ EE_RSCFD_LastTxObjectChannel7_u08 
	    			                                      + 7 * EE_RSCFD_MAXTXBUFFERS ]
	    			                      &= ( u08 )( ~( EE_RSCFD_TMSTS_RFMSK ) );
    				EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXA + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL7 ) ]( );
    			}
    			break;
    		case EE_RSCFD_INT_TXQ0:
    			EE_RSCFD_LastTxObjectChannel7_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL7 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ EE_RSCFD_CHANNEL7 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ0 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL7 ) ]( );
					break;
    		case EE_RSCFD_INT_TXQ1:
    			EE_RSCFD_LastTxObjectChannel7_u08 = ( u08 )
    				( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL7 ].mc );
    			ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ EE_RSCFD_CHANNEL7 ].irq = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXQ1 + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL7 ) ]( );
					break;
				case EE_RSCFD_INT_CERR:
					EE_RSCFD_LastErrorCode_Channel_u16[ EE_RSCFD_CHANNEL7 ] = 
						( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL7 ].erfl.err );
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_CERR + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL7 ) ]( );
					ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ EE_RSCFD_CHANNEL7 ].erfl.err = EE_RSCFD_ERROR_CLEARALL;
					break;
				case EE_RSCFD_INT_TXHL:
					ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL7 ].irq = 0;
					if( ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL7 ].elt )
					{
						ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ EE_RSCFD_CHANNEL7 ].elt = 0;
						EE_RSCFD_LastErrorCode_Global_u08 = EE_RSCFD_GERROR_THLLOST;
						EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GERR ]( );
					}
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXHL + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL7 ) ]( );
					break;
				case EE_RSCFD_INT_RXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL7, EE_RSCFD_INT_RXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfrxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_RXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL7 ) ]( );
					break;
				case EE_RSCFD_INT_TXCF:
	      	FIFONumber_u08 = EE_RSCFD_GetComFIFOIntStatus( 0, EE_RSCFD_CHANNEL7, EE_RSCFD_INT_TXCF );
	      	if( FIFONumber_u08 == EE_RSCFD_GLOBAL ) break;
      		ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cftxif = 0;
    			EE_RSCFD_CIVector[ ( EE_RSCFD_INT_MACRO * UnitNumber_u08 ) + EE_RSCFD_INT_GLOBAL + EE_RSCFD_INT_TXCF + 
    												 ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_CHANNEL7 ) ]( );
					break;
    	}
        EE_RSCFD_InterruptFlag_Channel7_u08 = EE_RSCFD_INT_NOINT;
    }
    __syncp();
}


/*
 * The peripheral Support Functions
 */

//=============================================================================
// FunctionName: RSCFD_PortEnable
// IN  : UnitNumber: Selected Macro
//       ChannelNumber: Selected Channel
// OUT : Error Flag
// Description : 
// Enable AFCAN I/O ports
//=============================================================================
bit EE_RSCFD_PortEnable( u08 UnitNumber_u08,
                         u08 ChannelNumber_u08 )
{
  u08 ChannelCount_u08;

    if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
    if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
      return( EE_RSCFD_ERROR );

    switch( UnitNumber_u08 ) 
      {
      case EE_RSCFD_0:
        switch( ChannelNumber_u08 )
          {

#ifdef EE_RSCFD_PORT_M0RX0
          case EE_RSCFD_CHANNEL0:
            PORT_Enable( EE_RSCFD_PORT_M0RX0, EE_RSCFD_PORT_BIT_M0RX0,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0RX0 );
            PORT_Enable( EE_RSCFD_PORT_M0TX0, EE_RSCFD_PORT_BIT_M0TX0,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0TX0 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX1
          case EE_RSCFD_CHANNEL1:
            PORT_Enable( EE_RSCFD_PORT_M0RX1, EE_RSCFD_PORT_BIT_M0RX1,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0RX1 );
            PORT_Enable( EE_RSCFD_PORT_M0TX1, EE_RSCFD_PORT_BIT_M0TX1,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0TX1 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX2
          case EE_RSCFD_CHANNEL2:
            PORT_Enable( EE_RSCFD_PORT_M0RX2, EE_RSCFD_PORT_BIT_M0RX2,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0RX2 );
            PORT_Enable( EE_RSCFD_PORT_M0TX2, EE_RSCFD_PORT_BIT_M0TX2,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0TX2 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX3
          case EE_RSCFD_CHANNEL3:
            PORT_Enable( EE_RSCFD_PORT_M0RX3, EE_RSCFD_PORT_BIT_M0RX3,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0RX3 );
            PORT_Enable( EE_RSCFD_PORT_M0TX3, EE_RSCFD_PORT_BIT_M0TX3,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0TX3 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX4
          case EE_RSCFD_CHANNEL4:
            PORT_Enable( EE_RSCFD_PORT_M0RX4, EE_RSCFD_PORT_BIT_M0RX4,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0RX4 );
            PORT_Enable( EE_RSCFD_PORT_M0TX4, EE_RSCFD_PORT_BIT_M0TX4,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0TX4 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX5
          case EE_RSCFD_CHANNEL5:
            PORT_Enable( EE_RSCFD_PORT_M0RX5, EE_RSCFD_PORT_BIT_M0RX5,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0RX5 );
            PORT_Enable( EE_RSCFD_PORT_M0TX5, EE_RSCFD_PORT_BIT_M0TX5,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0TX5 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX6
          case EE_RSCFD_CHANNEL6:
            PORT_Enable( EE_RSCFD_PORT_M0RX6, EE_RSCFD_PORT_BIT_M0RX6,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0RX6 );
            PORT_Enable( EE_RSCFD_PORT_M0TX6, EE_RSCFD_PORT_BIT_M0TX6,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0TX6 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX7
          case EE_RSCFD_CHANNEL7:
            PORT_Enable( EE_RSCFD_PORT_M0RX7, EE_RSCFD_PORT_BIT_M0RX7,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0RX7 );
            PORT_Enable( EE_RSCFD_PORT_M0TX7, EE_RSCFD_PORT_BIT_M0TX7,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M0TX7 );
            break;
#endif

          case EE_RSCFD_GLOBAL:
            for( ChannelCount_u08 = 0; 
                 ChannelCount_u08 < ee_rscfd_channels[ UnitNumber_u08 ];
                 ChannelCount_u08++ )
              {
                EE_RSCFD_PortEnable( UnitNumber_u08, ChannelCount_u08 );
              }
            break;
              
          default:
            return( EE_RSCFD_ERROR );
          } // switch ChannelNumber_u08
        break;
        
      case EE_RSCFD_1:
        switch( ChannelNumber_u08 )
          {

#ifdef EE_RSCFD_PORT_M1RX0
          case EE_RSCFD_CHANNEL0:
            PORT_Enable( EE_RSCFD_PORT_M1RX0, EE_RSCFD_PORT_BIT_M1RX0,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M1RX0 );
            PORT_Enable( EE_RSCFD_PORT_M1TX0, EE_RSCFD_PORT_BIT_M1TX0,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M1TX0 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M1RX1
          case EE_RSCFD_CHANNEL1:
            PORT_Enable( EE_RSCFD_PORT_M1RX1, EE_RSCFD_PORT_BIT_M1RX1,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M1RX1 );
            PORT_Enable( EE_RSCFD_PORT_M1TX1, EE_RSCFD_PORT_BIT_M1TX1,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M1TX1 );
            break;
#endif
#ifdef EE_RSCFD_PORT_M1RX2
          case EE_RSCFD_CHANNEL2:
            PORT_Enable( EE_RSCFD_PORT_M1RX2, EE_RSCFD_PORT_BIT_M1RX2,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M1RX2 );
            PORT_Enable( EE_RSCFD_PORT_M1TX2, EE_RSCFD_PORT_BIT_M1TX2,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M1TX2 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M1RX3
          case EE_RSCFD_CHANNEL3:
            PORT_Enable( EE_RSCFD_PORT_M1RX3, EE_RSCFD_PORT_BIT_M1RX3,
                         PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M1RX3 );
            PORT_Enable( EE_RSCFD_PORT_M1TX3, EE_RSCFD_PORT_BIT_M1TX3,
                         PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                         EE_RSCFD_PORT_FUNC_M1TX3 );
            break;
#endif

          case EE_RSCFD_GLOBAL:
            for( ChannelCount_u08 = 0; 
                 ChannelCount_u08 < ee_rscfd_channels[ UnitNumber_u08 ];
                 ChannelCount_u08++ )
              {
                EE_RSCFD_PortEnable( UnitNumber_u08, ChannelCount_u08 );
              }
            break;

          default:
            return( EE_RSCFD_ERROR );
          } // switch ChannelNumber_u08
        break;
        
      default: 
        return( EE_RSCFD_ERROR );

    } // switch( UnitNumber )

    return( EE_RSCFD_OK );
}
    
//=============================================================================
// FunctionName: EE_RSCFD_PortDisable
// IN  : UnitNumber: Selected Macro
//       ChannelNumber: Selected Channel
// OUT : Error Flag
// Description : 
// Release AFCAN I/O ports to normal port function
//=============================================================================
bit EE_RSCFD_PortDisable( u08 UnitNumber_u08,
                          u08 ChannelNumber_u08 )
{
  u08 ChannelCount_u08;

    if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
    if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
      return( EE_RSCFD_ERROR );

    switch( UnitNumber_u08 ) 
      {
      case EE_RSCFD_0:
        switch( ChannelNumber_u08 )
          {
            
#ifdef EE_RSCFD_PORT_M0RX0
          case EE_RSCFD_CHANNEL0:
            PORT_Disable( EE_RSCFD_PORT_M0RX0, EE_RSCFD_PORT_BIT_M0RX0 );
            PORT_Disable( EE_RSCFD_PORT_M0TX0, EE_RSCFD_PORT_BIT_M0TX0 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX1
          case EE_RSCFD_CHANNEL1:
            PORT_Disable( EE_RSCFD_PORT_M0RX1, EE_RSCFD_PORT_BIT_M0RX1 );
            PORT_Disable( EE_RSCFD_PORT_M0TX1, EE_RSCFD_PORT_BIT_M0TX1 );
            break;
#endif
            
#ifdef EE_RSCFD_PORT_M0RX2
          case EE_RSCFD_CHANNEL2:
            PORT_Disable( EE_RSCFD_PORT_M0RX2, EE_RSCFD_PORT_BIT_M0RX2 );
            PORT_Disable( EE_RSCFD_PORT_M0TX2, EE_RSCFD_PORT_BIT_M0TX2 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX3
          case EE_RSCFD_CHANNEL3:
            PORT_Disable( EE_RSCFD_PORT_M0RX3, EE_RSCFD_PORT_BIT_M0RX3 );
            PORT_Disable( EE_RSCFD_PORT_M0TX3, EE_RSCFD_PORT_BIT_M0TX3 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX4
          case EE_RSCFD_CHANNEL4:
            PORT_Disable( EE_RSCFD_PORT_M0RX4, EE_RSCFD_PORT_BIT_M0RX4 );
            PORT_Disable( EE_RSCFD_PORT_M0TX4, EE_RSCFD_PORT_BIT_M0TX4 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX5
          case EE_RSCFD_CHANNEL5:
            PORT_Disable( EE_RSCFD_PORT_M0RX5, EE_RSCFD_PORT_BIT_M0RX5 );
            PORT_Disable( EE_RSCFD_PORT_M0TX5, EE_RSCFD_PORT_BIT_M0TX5 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX6
          case EE_RSCFD_CHANNEL6:
            PORT_Disable( EE_RSCFD_PORT_M0RX6, EE_RSCFD_PORT_BIT_M0RX6 );
            PORT_Disable( EE_RSCFD_PORT_M0TX6, EE_RSCFD_PORT_BIT_M0TX6 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M0RX7
          case EE_RSCFD_CHANNEL7:
            PORT_Disable( EE_RSCFD_PORT_M0RX7, EE_RSCFD_PORT_BIT_M0RX7 );
            PORT_Disable( EE_RSCFD_PORT_M0TX7, EE_RSCFD_PORT_BIT_M0TX7 );
            break;
#endif

          case EE_RSCFD_GLOBAL:
            for( ChannelCount_u08 = 0; 
                 ChannelCount_u08 < ee_rscfd_channels[ UnitNumber_u08 ];
                 ChannelCount_u08++ )
              {
                EE_RSCFD_PortDisable( UnitNumber_u08, ChannelCount_u08 );
              }
            break;

          default:
            return( EE_RSCFD_ERROR );
          } // switch ChannelNumber_u08
        break;

      case EE_RSCFD_1:
        switch( ChannelNumber_u08 )
          {
            
#ifdef EE_RSCFD_PORT_M1RX0
          case EE_RSCFD_CHANNEL0:
            PORT_Disable( EE_RSCFD_PORT_M1RX0, EE_RSCFD_PORT_BIT_M1RX0 );
            PORT_Disable( EE_RSCFD_PORT_M1TX0, EE_RSCFD_PORT_BIT_M1TX0 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M1RX1
          case EE_RSCFD_CHANNEL1:
            PORT_Disable( EE_RSCFD_PORT_M1RX1, EE_RSCFD_PORT_BIT_M1RX1 );
            PORT_Disable( EE_RSCFD_PORT_M1TX1, EE_RSCFD_PORT_BIT_M1TX1 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M1RX2
          case EE_RSCFD_CHANNEL2:
            PORT_Disable( EE_RSCFD_PORT_M1RX2, EE_RSCFD_PORT_BIT_M1RX2 );
            PORT_Disable( EE_RSCFD_PORT_M1TX2, EE_RSCFD_PORT_BIT_M1TX2 );
            break;
#endif

#ifdef EE_RSCFD_PORT_M1RX3
          case EE_RSCFD_CHANNEL3:
            PORT_Disable( EE_RSCFD_PORT_M1RX3, EE_RSCFD_PORT_BIT_M1RX3 );
            PORT_Disable( EE_RSCFD_PORT_M1TX3, EE_RSCFD_PORT_BIT_M1TX3 );
            break;
#endif

          case EE_RSCFD_GLOBAL:
            for( ChannelCount_u08 = 0; 
                 ChannelCount_u08 < ee_rscfd_channels[ UnitNumber_u08 ];
                 ChannelCount_u08++ )
              {
                EE_RSCFD_PortDisable( UnitNumber_u08, ChannelCount_u08 );
              }
            break;

          default:
            return( EE_RSCFD_ERROR );
          } // switch ChannelNumber_u08
        break;

      default: 
        return( EE_RSCFD_ERROR );

      } // switch( UnitNumber )
    
    return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_CreateInterrupt
// IN  :         Unit Number, Channel Number, Int Number, Int Level, 
//               Int Function Vector
// OUT :         Success Status
// Description : Enables and Sets Interrupt Vector to given Function
// 
//=============================================================================
bit EE_RSCFD_CreateInterrupt( u08  UnitNumber_u08,
                              u08  ChannelNumber_u08,
                              u08  IntNumber_u08,
                              u16  SetIntLevel_u16,
                              void ( *FunctionVector )( ) )
{
  u16 IntLevel_u16 = SetIntLevel_u16;

  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( FunctionVector == NULL ) 
  {
    IntLevel_u16 = EE_RSCFD_INTCLEAR;
    FunctionVector = EE_RSCFD_IRQDefault;
  }

  if( ChannelNumber_u08 == EE_RSCFD_GLOBAL )
	{
      EE_RSCFD_CIVector[ UnitNumber_u08 * ( EE_RSCFD_MAXCHANNELS * EE_RSCFD_INT_CHANNEL + 
                                            EE_RSCFD_INT_GLOBAL )
                                          + IntNumber_u08 ] = FunctionVector;
      
	  switch( UnitNumber_u08 )
        {
	  	case EE_RSCFD_0:
	    	switch( IntNumber_u08 ) 
	    	{
#if( defined( EE_RSCFD_INT_M0GERR ) )
            case EE_RSCFD_INT_GERR:
              EE_RSCFD_INT_M0GERR = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M0RXF0 ) )
            case EE_RSCFD_INT_RXF0:
              EE_RSCFD_INT_M0RXF0 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M0RXF1 ) )
            case EE_RSCFD_INT_RXF1:
              EE_RSCFD_INT_M0RXF1 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M0RXF2 ) )
            case EE_RSCFD_INT_RXF2:
              EE_RSCFD_INT_M0RXF2 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M0RXF3 ) )
            case EE_RSCFD_INT_RXF3:
              EE_RSCFD_INT_M0RXF3 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M0RXF4 ) )
            case EE_RSCFD_INT_RXF4:
              EE_RSCFD_INT_M0RXF4 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M0RXF5 ) )
            case EE_RSCFD_INT_RXF5:
              EE_RSCFD_INT_M0RXF5 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M0RXF6 ) )
            case EE_RSCFD_INT_RXF6:
              EE_RSCFD_INT_M0RXF6 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M0RXF7 ) )
            case EE_RSCFD_INT_RXF7:
              EE_RSCFD_INT_M0RXF7 = IntLevel_u16;
              break;
#endif
	    	}
				break;

	  	case EE_RSCFD_1:
	    	switch( IntNumber_u08 ) 
	    	{
#if( defined( EE_RSCFD_INT_M1GERR ) )
            case EE_RSCFD_INT_GERR:
              EE_RSCFD_INT_M1GERR = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M1RXF0 ) )
            case EE_RSCFD_INT_RXF0:
              EE_RSCFD_INT_M1RXF0 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M1RXF1 ) )
            case EE_RSCFD_INT_RXF1:
              EE_RSCFD_INT_M1RXF1 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M1RXF2 ) )
            case EE_RSCFD_INT_RXF2:
              EE_RSCFD_INT_M1RXF2 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M1RXF3 ) )
            case EE_RSCFD_INT_RXF3:
              EE_RSCFD_INT_M1RXF3 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M1RXF4 ) )
            case EE_RSCFD_INT_RXF4:
              EE_RSCFD_INT_M1RXF4 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M1RXF5 ) )
            case EE_RSCFD_INT_RXF5:
              EE_RSCFD_INT_M1RXF5 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M1RXF6 ) )
            case EE_RSCFD_INT_RXF6:
              EE_RSCFD_INT_M1RXF6 = IntLevel_u16;
              break;
#endif
#if( defined( EE_RSCFD_INT_M1RXF7 ) )
            case EE_RSCFD_INT_RXF7:
              EE_RSCFD_INT_M1RXF7 = IntLevel_u16;
              break;
#endif
	    	}

	    default:
		    return( EE_RSCFD_ERROR );
		}
	}
	else
	{
	  if( ChannelNumber_u08 >= EE_RSCFD_CHANNELS ) return( EE_RSCFD_ERROR );
	  
      EE_RSCFD_CIVector[ UnitNumber_u08 * ( EE_RSCFD_MAXCHANNELS * EE_RSCFD_INT_CHANNEL + 
                                            EE_RSCFD_INT_GLOBAL )
                                        + ChannelNumber_u08 * EE_RSCFD_INT_CHANNEL
                                        + EE_RSCFD_INT_GLOBAL
										                    + IntNumber_u08 ] = FunctionVector;
	  switch( UnitNumber_u08 )
      {
	  	case EE_RSCFD_0:
        switch( ChannelNumber_u08 )
	  		{
            case EE_RSCFD_CHANNEL0:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M0TX0 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M0TX0 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXA0 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M0TXA0 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ00 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M0TXQ00 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ10 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M0TXQ10 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0THL0 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M0THL0 = IntLevel_u16;
				 break;
#endif
#if( defined( EE_RSCFD_INT_M0RXCF0 ) )
                 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M0RXCF0 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXCF0 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M0TXCF0 = IntLevel_u16;
                 break;
#endif
              }
              break;
              
            case EE_RSCFD_CHANNEL1:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M0TX1 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M0TX1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXA1 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M0TXA1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ01 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M0TXQ01 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ11 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M0TXQ11 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0ERR1 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M0ERR1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0THL1 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M0THL1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0RXCF1 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M0RXCF1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXCF1 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M0TXCF1 = IntLevel_u16;
                 break;
#endif
              }
              break;
  
            case EE_RSCFD_CHANNEL2:
              switch( IntNumber_u08 ) 
                {
#if( defined( EE_RSCFD_INT_M0TX2 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M0TX2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXA2 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M0TXA2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ02 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M0TXQ02 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ12 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M0TXQ12 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0ERR2 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M0ERR2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0THL2 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M0THL2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0RXCF2 ) )
                 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M0RXCF2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXCF2 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M0TXCF2 = IntLevel_u16;
                 break;
#endif
             }
             break;

			case EE_RSCFD_CHANNEL3:
              switch( IntNumber_u08 ) 
                {
#if( defined( EE_RSCFD_INT_M0TX3 ) )
                 case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M0TX3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXA3 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M0TXA3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ03 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M0TXQ03 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ13 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M0TXQ13 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0ERR3 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M0ERR3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0THL3 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M0THL3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0RXCF3 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M0RXCF3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXCF3 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M0TXCF3 = IntLevel_u16;
                 break;
#endif
              }
              break;

			case EE_RSCFD_CHANNEL4:
              switch( IntNumber_u08 ) 
                {
#if( defined( EE_RSCFD_INT_M0TX4 ) )
                 case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M0TX4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXA4 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M0TXA4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ04 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M0TXQ04 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ14 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M0TXQ14 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0ERR4 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M0ERR4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0THL4 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M0THL4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0RXCF4 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M0RXCF4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXCF4 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M0TXCF4 = IntLevel_u16;
                 break;
#endif
             }
             break;

			case EE_RSCFD_CHANNEL5:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M0TX5 ) )
                 case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M0TX5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXA5 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M0TXA5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ05 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M0TXQ05 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXQ15 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M0TXQ15 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0ERR5 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M0ERR5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0THL5 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M0THL5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0RXCF5 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M0RXCF5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M0TXCF5 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M0TXCF5 = IntLevel_u16;
                 break;
#endif
             }
             break;

			case EE_RSCFD_CHANNEL6:
              switch( IntNumber_u08 ) 
              {
#ifdef EE_RSCFD_INT_M0TX6
                 case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M0TX6 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0TXA6
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M0TXA6 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0TXQ06
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M0TXQ06 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0TXQ16
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M0TXQ16 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0ERR6
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M0ERR6 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0THL6
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M0THL6 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0RXCF6
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M0RXCF6 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0TXCF6
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M0TXCF6 = IntLevel_u16;
                 break;
#endif
             }
             break;

			case EE_RSCFD_CHANNEL7:
              switch( IntNumber_u08 ) 
              {
#ifdef EE_RSCFD_INT_M0TX7
                 case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M0TX7 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0TXA7
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M0TXA7 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0TXQ07
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M0TXQ07 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0TXQ17
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M0TXQ17 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0ERR7
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M0ERR7 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0THL7
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M0THL7 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0RXCF7
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M0RXCF7 = IntLevel_u16;
                 break;
#endif
#ifdef EE_RSCFD_INT_M0TXCF7
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M0TXCF7 = IntLevel_u16;
                 break;
#endif
             }
             break;

	    default:
		    return( EE_RSCFD_ERROR );
		  }
		  break;
		
	  	case EE_RSCFD_1:
        switch( ChannelNumber_u08 )
	  		{
            case EE_RSCFD_CHANNEL0:
              switch( IntNumber_u08 ) 
                {
#if( defined( EE_RSCFD_INT_M1TX0 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M1TX0 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXA0 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M1TXA0 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ00 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M1TXQ00 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ10 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M1TXQ10 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1ERR0 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M1ERR0 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1THL0 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M1THL0 = IntLevel_u16;
				         break;
#endif
#if( defined( EE_RSCFD_INT_M1RXCF0 ) )
                 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M1RXCF0 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXCF0 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M1TXCF0 = IntLevel_u16;
                 break;
#endif
              }
              break;

            case EE_RSCFD_CHANNEL1:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M1TX1 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M1TX1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXA1 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M1TXA1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ01 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M1TXQ01 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ11 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M1TXQ11 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1ERR1 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M1ERR1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1THL1 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M1THL1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1RXCF1 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M1RXCF1 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXCF1 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M1TXCF1 = IntLevel_u16;
                 break;
#endif
              }
              break;
	    
            case EE_RSCFD_CHANNEL2:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M1TX2 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M1TX2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXA2 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M1TXA2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ02 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M1TXQ02 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ12 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M1TXQ12 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1ERR2 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M1ERR2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1THL2 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M1THL2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1RXCF2 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M1RXCF2 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXCF2 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M1TXCF2 = IntLevel_u16;
                 break;
#endif
              }
              break;

            case EE_RSCFD_CHANNEL3:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M1TX3 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M1TX3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXA3 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M1TXA3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ03 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M1TXQ03 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ13 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M1TXQ13 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1ERR3 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M1ERR3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1THL3 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M1THL3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1RXCF3 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M1RXCF3 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXCF3 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M1TXCF3 = IntLevel_u16;
                 break;
#endif
              }
              break;

            case EE_RSCFD_CHANNEL4:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M1TX4 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M1TX4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXA4 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M1TXA4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ04 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M1TXQ04 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ14 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M1TXQ14 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1ERR4 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M1ERR4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1THL4 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M1THL4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1RXCF4 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M1RXCF4 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXCF4 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M1TXCF4 = IntLevel_u16;
                 break;
#endif
              }
              break;

            case EE_RSCFD_CHANNEL5:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M1TX5 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M1TX5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXA5 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M1TXA5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ05 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M1TXQ05 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ15 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M1TXQ15 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1ERR5 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M1ERR5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1THL5 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M1THL5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1RXCF5 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M1RXCF5 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXCF5 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M1TXCF5 = IntLevel_u16;
                 break;
#endif
              }
              break;

            case EE_RSCFD_CHANNEL6:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M1TX6 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M1TX6 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXA6 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M1TXA6 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ06 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M1TXQ06 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ16 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M1TXQ16 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1ERR6 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M1ERR6 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1THL6 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M1THL6 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1RXCF6 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M1RXCF6 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXCF6 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M1TXCF6 = IntLevel_u16;
                 break;
#endif
              }
              break;

            case EE_RSCFD_CHANNEL7:
              switch( IntNumber_u08 ) 
              {
#if( defined( EE_RSCFD_INT_M1TX7 ) )
                case EE_RSCFD_INT_TX:
                  EE_RSCFD_INT_M1TX7 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXA7 ) )
                 case EE_RSCFD_INT_TXA:
                  EE_RSCFD_INT_M1TXA7 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ07 ) )
                 case EE_RSCFD_INT_TXQ0:
                  EE_RSCFD_INT_M1TXQ07 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXQ17 ) )
                 case EE_RSCFD_INT_TXQ1:
                  EE_RSCFD_INT_M1TXQ17 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1ERR7 ) )
                 case EE_RSCFD_INT_CERR:
                  EE_RSCFD_INT_M1ERR7 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1THL7 ) )
                 case EE_RSCFD_INT_TXHL:
                  EE_RSCFD_INT_M1THL7 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1RXCF7 ) )
				 case EE_RSCFD_INT_RXCF:
                  EE_RSCFD_INT_M1RXCF7 = IntLevel_u16;
                 break;
#endif
#if( defined( EE_RSCFD_INT_M1TXCF7 ) )
                 case EE_RSCFD_INT_TXCF:
                  EE_RSCFD_INT_M1TXCF7 = IntLevel_u16;
                 break;
#endif
              }
              break;

	    default:
		    return( EE_RSCFD_ERROR );
  	  }
  	  break;
  	}
  }
  return( EE_RSCFD_OK );
}


//=============================================================================
// FunctionName: EE_RSCFD_SetInterrupt
// IN  :         UnitNumber, Channel Number, Int Mask
// OUT :         Success Status
// Description : Enables or disables dedicated Interrupts
// 
//=============================================================================
bit EE_RSCFD_SetInterrupt( u08 UnitNumber_u08,
                           u08 ChannelNumber_u08,
                           u08 InterruptSelection_u08,
                           u16 InterruptSubSelection_u08 )
{
  u08 RegIndex_u08;
  u08 RegPos_u08;
  u32 RegBits_u32;
	
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  	
  if( ChannelNumber_u08 == EE_RSCFD_GLOBAL )
  {
  	switch( InterruptSelection_u08 )
      {
      case EE_RSCFD_INT_GERR:
        ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.ie = 
          ( u32 )InterruptSubSelection_u08;
        break;
      default:   /* RX FIFO Interrupt selected */
        if( InterruptSelection_u08 > EE_RSCFD_MAXRXFIFOS )
          return( EE_RSCFD_ERROR );
        ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc
                         [ InterruptSelection_u08 - EE_RSCFD_INT_RXF0 ].rfie = 
                         InterruptSubSelection_u08;
        break;
  	}
  }
  else
  {
    if( ChannelNumber_u08 >= EE_RSCFD_CHANNELS ) return( EE_RSCFD_ERROR );
    RegIndex_u08 = ChannelNumber_u08 * EE_RSCFD_MAXTXBUFFERS / EE_RSCFD_COMREGSBITS;
    RegPos_u08   = ChannelNumber_u08 * EE_RSCFD_MAXTXBUFFERS - 
                   RegIndex_u08      * EE_RSCFD_COMREGSBITS;
		
    switch( InterruptSelection_u08 )
      {
      case EE_RSCFD_INT_TX:
      case EE_RSCFD_INT_TXA:
        if( InterruptSubSelection_u08 == EE_RSCFD_INT_NOINT )  /* clears all */
          {
            RegBits_u32 = ( u32 )( EE_RSCFD_MAXTXBUFFERS - 1 ) << RegPos_u08;
            ee_rscfd_common_p[ UnitNumber_u08 ]->tmiec[ RegIndex_u08 ] &= ~RegBits_u32;
          }
        else  /* Sub selection defines the Tx Buffer IRQ to be enabled */
          {
            if( InterruptSubSelection_u08 >= EE_RSCFD_MAXTXBUFFERS ) 
              return( EE_RSCFD_ERROR );
            RegBits_u32 = ( u32 )( 1 << ( InterruptSubSelection_u08 + RegPos_u08 ) );
            ee_rscfd_common_p[ UnitNumber_u08 ]->tmiec[ RegIndex_u08 ] |= RegBits_u32;
          }
        break;
      case EE_RSCFD_INT_TXQ0:
        ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].cc[ ChannelNumber_u08 ].ie =
          InterruptSubSelection_u08;
        break;
      case EE_RSCFD_INT_TXQ1:
        ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].cc[ ChannelNumber_u08 ].ie =
          InterruptSubSelection_u08;
        break;
      case EE_RSCFD_INT_CERR:
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.ie =
          InterruptSubSelection_u08;
        break;
      case EE_RSCFD_INT_TXHL:
        ee_rscfd_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].ie =
          InterruptSubSelection_u08;
        break;
      case EE_RSCFD_INT_RXCF:
        if( InterruptSubSelection_u08 == EE_RSCFD_INT_NOINT )  /* clears all */
          {
            for( RegIndex_u08 = ( ChannelNumber_u08 * EE_RSCFD_CHANNELS );
                 RegIndex_u08 < ( ( ChannelNumber_u08 + 1 ) * EE_RSCFD_CHANNELS );
                 RegIndex_u08++ )
              {
                ee_rscfd_common_p[ UnitNumber_u08 ]->cfcc[ RegIndex_u08 ].cfrxie = 
                  EE_RSCFD_INT_DISABLE;
              }
          }
        else  /* Sub Index selects the COM FIFO number per channel */
          {
            RegIndex_u08 = ( ChannelNumber_u08 * EE_RSCFD_CHANNELS ) + 
              InterruptSubSelection_u08;
            ee_rscfd_common_p[ UnitNumber_u08 ]->cfcc[ RegIndex_u08 ].cfrxie = 
              EE_RSCFD_INT_ENABLE;
          }
        break;
      case EE_RSCFD_INT_TXCF:
        if( InterruptSubSelection_u08 == EE_RSCFD_INT_NOINT )  /* clears all */
          {
            for( RegIndex_u08 = ( ChannelNumber_u08 * EE_RSCFD_CHANNELS );
                 RegIndex_u08 < ( ( ChannelNumber_u08 + 1 ) * EE_RSCFD_CHANNELS );
                 RegIndex_u08++ )
              {
                ee_rscfd_common_p[ UnitNumber_u08 ]->cfcc[ RegIndex_u08 ].cftxie = 
                  EE_RSCFD_INT_DISABLE;
              }
          }
        else  /* Sub Index selects the COM FIFO number per channel */
          {
            RegIndex_u08 = ( ChannelNumber_u08 * EE_RSCFD_CHANNELS ) + 
              InterruptSubSelection_u08;
            ee_rscfd_common_p[ UnitNumber_u08 ]->cfcc[ RegIndex_u08 ].cftxie = 
              EE_RSCFD_INT_ENABLE;
          }
        break;
      }
  }
  
  return( EE_RSCFD_OK );
}    

//=============================================================================
// FunctionName: EE_RSCFD_GetError
// IN  :         UnitNumber, Channel Number
// OUT :         Success Status, Error States
// Description : Returns global or channel local error states
// 
//=============================================================================
bit EE_RSCFD_GetError( u08  UnitNumber_u08,
                       u08  ChannelNumber_u08,
                       pu16 InterruptErrorFlag_pu16,
                       pu16 LastErrorFlag_pu16 )
{
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );

  if( ChannelNumber_u08 == EE_RSCFD_GLOBAL )
    {
      *InterruptErrorFlag_pu16 = ( u16 )EE_RSCFD_LastErrorCode_Global_u08;
      *LastErrorFlag_pu16      = ( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->gerfl.err );  	
	}
  else
	{
      if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) return( EE_RSCFD_ERROR );
      
      *InterruptErrorFlag_pu16 = EE_RSCFD_LastErrorCode_Channel_u16[ ChannelNumber_u08 ];
      *LastErrorFlag_pu16      = ( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                                          [ ChannelNumber_u08 ].erfl.err );  	
	}  
  
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_GetStatus
// IN  :         UnitNumber, Channel Number
// OUT :         Success Status, Channel Status Values
// Description : Returns channel local status information flags
// 
//=============================================================================
bit EE_RSCFD_GetStatus( u08  UnitNumber_u08,
                     	  u08  ChannelNumber_u08,
                     		u08  StatusNumber_u08,
                     		pu16 StatusValue_pu16 )
{
  static u16 LocalStatusValue_THL_u16;

  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) &&
  		( ChannelNumber_u08 != EE_RSCFD_GLOBAL ) )return( EE_RSCFD_ERROR );

  switch( StatusNumber_u08 )
  {
    case EE_RSCFD_STATUS_OPMODE:              /* Operation mode of channel */
      ( ( ChannelNumber_u08 == EE_RSCFD_GLOBAL ) ?
        ( *StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds ) :
        ( *StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
          [ ChannelNumber_u08 ].sts.mds ) );
      break;  

    case EE_RSCFD_STATUS_PSMODE:              /* Operation mode of channel */
      ( ( ChannelNumber_u08 == EE_RSCFD_GLOBAL  ) ?
  	  	( *StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.slps ) :
  	  	( *StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
          [ ChannelNumber_u08 ].sts.slps ) );
      break;  
            
    case EE_RSCFD_STATUS_RECEIVE:        /* indicates channel is receiving */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
  	  	                                             [ ChannelNumber_u08 ].sts.recs;
      break;
            
    case EE_RSCFD_STATUS_TRANSMIT:        /* indicates channel is sending */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
  	  	                                             [ ChannelNumber_u08 ].sts.trxs;
      break;
            
    case EE_RSCFD_STATUS_BUSOFF:         /* indicates channel is bus off */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
  	  	                                             [ ChannelNumber_u08 ].sts.boffs;
      break;

    case EE_RSCFD_STATUS_ERRCNTLEV:                       /* error level */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 )( ee_rscfd_common_p[ UnitNumber_u08 ]->ch
  	  	                                              [ ChannelNumber_u08 ].erfl.err &
  	  	                                              ( EE_RSCFD_ERROR_WARNING |
  	  	                                                EE_RSCFD_ERROR_PASSIVE |
  	  	                                                EE_RSCFD_ERROR_BUSOFF ) );
      break;
            
    case EE_RSCFD_STATUS_TOVF:               /* send history overrun flag */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts
  	  	                                             [ ChannelNumber_u08 ].elt;
	    if( *StatusValue_pu16 )
	    {
				ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ ChannelNumber_u08 ].elt = 0;
	    }
	    break;

    case EE_RSCFD_STATUS_THPM:                 /* send history empty flag */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts
  	  	                                             [ ChannelNumber_u08 ].emp;
      break;

    case EE_RSCFD_STATUS_TXTS:                       /* send Tx timestamp */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
    	if( !ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ ChannelNumber_u08 ].emp )
    	{
    	  *StatusValue_pu16 = ( u16 )ee_rscfd_thl_p[ UnitNumber_u08 ]
    		                                         [ ChannelNumber_u08 ]->l.tmts;
    	}
    	else
    	{
    	  *StatusValue_pu16 = 0;
    	  return( EE_RSCFD_ERROR );
    	}
      break;

    case EE_RSCFD_STATUS_TGPT:                    /* send history pointer */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
    	if( !ee_rscfd_common_p[ UnitNumber_u08 ]->thlsts[ ChannelNumber_u08 ].emp )
    	{
    		LocalStatusValue_THL_u16 = ( u16 )ee_rscfd_thl_p[ UnitNumber_u08 ]
    		                                            [ ChannelNumber_u08 ]->h.tid;
    		if( LocalStatusValue_THL_u16 == EE_RSCFD_TID_NOTUSED )
    		{
    			LocalStatusValue_THL_u16 = ( u16 )( ee_rscfd_thl_p[ UnitNumber_u08 ]
                                                            [ ChannelNumber_u08 ]->l.bt +
                                            ( ee_rscfd_thl_p[ UnitNumber_u08 ]
                                                            [ ChannelNumber_u08 ]->l.bn 
    		                                                    << EE_RSCFD_THL_BN_P ) );
    		}
    		*StatusValue_pu16 = LocalStatusValue_THL_u16;
    	}
    	else
    	{
    	  *StatusValue_pu16 = EE_RSCFD_TID_NOTUSED;
    	}
      break;
            
    case EE_RSCFD_STATUS_NEWTXHISTORY:               /* get next THL entry */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
		  ee_rscfd_common_p[ UnitNumber_u08 ]->thlpctr[ ChannelNumber_u08 ] = 
		  	EE_RSCFD_THL_NEXTELEMENT;
      break;

    case EE_RSCFD_STATUS_VALID:      /* channel has integrated sucessfully */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
  	  	                                             [ ChannelNumber_u08 ].sts.coms;
      break;
            
    case EE_RSCFD_STATUS_TRERRCOUNT:       /* transmit error counter value */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
  	  	                                             [ ChannelNumber_u08 ].sts.tec;
      break;

    case EE_RSCFD_STATUS_RXERRCOUNT:       /* receive error counter value */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
  	  	                                             [ ChannelNumber_u08 ].sts.rec;
      break;
            
    case EE_RSCFD_STATUS_ERRPLEV:                /* error counter passive */
		  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
		    return( EE_RSCFD_ERROR );
  	  	*StatusValue_pu16 = ( u16 ) ee_rscfd_common_p[ UnitNumber_u08 ]->ch
  	  	                                             [ ChannelNumber_u08 ].sts.eps;
      break;

    case EE_RSCFD_STATUS_INT_RXFIFO:
    	*StatusValue_pu16 = ( u16 )ee_rscfd_common_p[ UnitNumber_u08 ]->rfists;
      break;

    case EE_RSCFD_STATUS_MLT_RXFIFO:
        *StatusValue_pu16 = ( u16 )ee_rscfd_common_p[ UnitNumber_u08 ]->fmsts.rf;
        break;

    case EE_RSCFD_STATUS_MLT_COMFIFO:
        *StatusValue_pu16 = ( u16 )ee_rscfd_common_p[ UnitNumber_u08 ]->fmsts.cf;
        break;

    case EE_RSCFD_STATUS_INTERRUPT:
    	if( ChannelNumber_u08 == EE_RSCFD_GLOBAL )
    	{
    		*StatusValue_pu16 = ( u16 )EE_RSCFD_InterruptFlag_Global_u08;
    		EE_RSCFD_InterruptFlag_Global_u08 = EE_RSCFD_INT_NOINT;
    	}
    	else
    	{
			  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
			    return( EE_RSCFD_ERROR );
    		*StatusValue_pu16 = ( u16 )EE_RSCFD_InterruptFlag_Channel_u08[ ChannelNumber_u08 ];
    		EE_RSCFD_InterruptFlag_Channel_u08[ ChannelNumber_u08 ] = EE_RSCFD_INT_NOINT;
    	}
	    break;

    default: return( EE_RSCFD_ERROR );

  } // end switch( StatusNumber_u08 )
    
  __syncp();
  return( EE_RSCFD_OK );
}    

//=============================================================================
// FunctionName: EE_RSCFD_Start
// IN  :         UnitNumber, Channel Number, Operation Mode
// OUT :         Success Status
// Description : Activates CAN Unit from any stop/sleep mode
// 
//=============================================================================
bit EE_RSCFD_Start( u08 UnitNumber_u08,
                    u08 ChannelNumber_u08,
                    u08 OperationMode_u08,
                    u08 ClearErrorCounter_u08,
                    u16 TimeStampSetting_u16 )
{
  u32 AccessTimeout_u32 = EE_RSCFD_SHUTDOWNTIMEOUT; 
  u08 ChannelIndex_u08;

  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
    
  while( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.rsts );
    
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.slps )  /* activate the unit */
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.gslpr = EE_RSCFD_SLEEP_DISABLE;
  }

  /* go globally to OPERATION */

  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCFD_RSTATUS_OPERATION )
  {                                               
  	ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.gmdc = EE_RSCFD_OPMODE_OPER;
    __syncp();
    while( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCFD_RSTATUS_OPERATION )
             && ( --AccessTimeout_u32 > 0 ) );
    if( AccessTimeout_u32 == 0L ) return( EE_RSCFD_ERROR );
  }
   
  if( TimeStampSetting_u16 )
  {
  	ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.tsrst = EE_RSCFD_SET;
  }
  
  if( ChannelNumber_u08 == EE_RSCFD_GLOBAL )
  {
    for( ChannelIndex_u08 = 0;
         ChannelIndex_u08 < ee_rscfd_channels[ UnitNumber_u08 ];
         ChannelIndex_u08++ )
    {
      EE_RSCFD_Start( UnitNumber_u08,
                      ChannelIndex_u08,
                      OperationMode_u08,
                      ClearErrorCounter_u08,
                      TimeStampSetting_u16 );
    }
  }
  else
  {  
    if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
      return( EE_RSCFD_ERROR );
      
    /* channels: cancel any sleep states */
    
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                     [ ChannelNumber_u08 ].ctr.cslpr = EE_RSCFD_CLEAR;
    AccessTimeout_u32 = EE_RSCFD_SHUTDOWNTIMEOUT;
    __syncp();
    while( ( ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                              [ ChannelNumber_u08 ].sts.slps != EE_RSCFD_CLEAR )
             && ( --AccessTimeout_u32 > 0 ) );
    if( AccessTimeout_u32 == 0L ) return( EE_RSCFD_ERROR );
      
    if( ClearErrorCounter_u08 )
    {
      EE_RSCFD_Start( UnitNumber_u08,
                      ChannelNumber_u08,
                      EE_RSCFD_OPMODE_RESET,
                      0,
                      0 );
    }

    switch( OperationMode_u08 )
    {
      case EE_RSCFD_OPMODE_RESET:
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.chmdc = EE_RSCFD_OPMODE_RESET;
        break;
        
      case EE_RSCFD_OPMODE_HALT:
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.chmdc = EE_RSCFD_OPMODE_HALT;
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.ctme = EE_RSCFD_CLEAR;
        break;
  
      case EE_RSCFD_OPMODE_OPER:
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.chmdc = EE_RSCFD_OPMODE_OPER;
        break;
  
      case EE_RSCFD_OPMODE_RECONLY:
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.ctms = EE_RSCFD_TEST_RXONLY;
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.ctme = EE_RSCFD_SET;
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.chmdc = EE_RSCFD_OPMODE_OPER;
        OperationMode_u08 = EE_RSCFD_OPMODE_OPER;
        break;
  
      case EE_RSCFD_OPMODE_STEST:
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.ctms = EE_RSCFD_TEST_INTLOOP;
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.ctme = EE_RSCFD_SET;
        ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                         [ ChannelNumber_u08 ].ctr.chmdc = EE_RSCFD_OPMODE_OPER;
        OperationMode_u08 = EE_RSCFD_OPMODE_OPER;
        break;
        
      default: return( EE_RSCFD_ERROR );
  
    } // switch( OperationMode_u08 )
  
    __syncp();
    AccessTimeout_u32 = EE_RSCFD_SHUTDOWNTIMEOUT;
    while( ( ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                              [ ChannelNumber_u08 ].sts.mds != ( u32 )OperationMode_u08 )
           && ( --AccessTimeout_u32 > 0 ) );
    if( AccessTimeout_u32 == 0L ) return( EE_RSCFD_ERROR );
      
    if( OperationMode_u08 == EE_RSCFD_OPMODE_OPER )    /* verify communication ready state */
    {
      AccessTimeout_u32 = EE_RSCFD_SHUTDOWNTIMEOUT;
      while( ( ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                                [ ChannelNumber_u08 ].sts.coms != EE_RSCFD_SET )
             && ( --AccessTimeout_u32 > 0 ) );
      if( AccessTimeout_u32 == 0L ) return( EE_RSCFD_ERROR );      
    }
  }
  return( EE_RSCFD_OK );    
}

//=============================================================================
// FunctionName: EE_RSCFD_Stop
// IN  :         UnitNumber, Channel Number, Stop Mode
// OUT :         Success Status
// Description : Sets CAN Channel into any init/stop/sleep mode
// 
//=============================================================================
bit EE_RSCFD_Stop( u08 UnitNumber_u08,
                   u08 ChannelNumber_u08,
                   u08 StopMode_u08 )
{
  u32 AccessTimeout_u32 = EE_RSCFD_SHUTDOWNTIMEOUT; 

  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) &&
      ( ChannelNumber_u08 != EE_RSCFD_GLOBAL ) ) return( EE_RSCFD_ERROR );

  if( ChannelNumber_u08 == EE_RSCFD_GLOBAL )
    {
      switch( StopMode_u08 )
        {
        case EE_RSCFD_OPMODE_SLEEP:
          if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCFD_OPMODE_RESET )
            return( EE_RSCFD_ERROR );
          ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.gslpr = EE_RSCFD_SET;
          __syncp();
          while( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.slps != EE_RSCFD_SET )
                 && ( --AccessTimeout_u32 > 0 ) );
          break;
          
        default:
          ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.gmdc = ( u32 )StopMode_u08;
          __syncp();
          while( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != ( u32 )StopMode_u08 )
                 && ( --AccessTimeout_u32 > 0 ) );
          break;
        }
    }
  else
    {
      switch( StopMode_u08 )
        {
        case EE_RSCFD_OPMODE_SLEEP:
          if( ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                               [ ChannelNumber_u08 ].sts.mds != EE_RSCFD_OPMODE_RESET )
            return( EE_RSCFD_ERROR );
          ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                           [ ChannelNumber_u08 ].ctr.cslpr = EE_RSCFD_SET;
          __syncp();
          while( ( ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                                    [ ChannelNumber_u08 ].sts.slps != EE_RSCFD_SET )
                 && ( --AccessTimeout_u32 > 0 ) );
          break;

        default:
          ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                           [ ChannelNumber_u08 ].ctr.chmdc = ( u32 )StopMode_u08;
          ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                           [ ChannelNumber_u08 ].ctr.ctme = EE_RSCFD_CLEAR;
          __syncp();
          while( ( ee_rscfd_common_p[ UnitNumber_u08 ]->ch
                                    [ ChannelNumber_u08 ].sts.mds != ( u32 )StopMode_u08 )
                 && ( --AccessTimeout_u32 > 0 ) );
          break;
        }
    }

  if( AccessTimeout_u32 == 0L ) return( EE_RSCFD_ERROR );
  else return( EE_RSCFD_OK );
}    

//=============================================================================
// FunctionName: EE_RSCFD_SetGlobalConfiguration
// IN  :         UnitNumber, Global configuration set
// Description : Performs Global Configurations
// 
//=============================================================================

bit EE_RSCFD_SetGlobalConfiguration( u08 UnitNumber_u08,
                                     const struct ee_rscfd_cfg_global *Config )
{    
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );

  /* Must be in global reset to set the global configuration! */
  
  while( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.rsts );

  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCFD_OPMODE_RESET )
    return( EE_RSCFD_ERROR );

  ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.gslpr   = Config->gctr.gslpr;
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.tpri     = Config->gcfg.tpri;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.dce      = Config->gcfg.dce;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.dre      = Config->gcfg.dre;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.mme      = Config->gcfg.mme;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.dcs      = Config->gcfg.dcs;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.cmpoc    = Config->gcfg.cmpoc;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.tsp      = Config->gcfg.tsp;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.tsss     = Config->gcfg.tsss;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.tsbtcs   = Config->gcfg.tsbtcs;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.itrcp    = Config->gcfg.itrcp;

  ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.gmdc     = Config->gctr.gmdc;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.ie       = Config->gctr.ie;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.tsrst    = Config->gctr.tsrst;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.tswr     = Config->gctr.tswr;

  ee_rscfd_common_p[ UnitNumber_u08 ]->gfdcfg.rped   = Config->gfdcfg.rped;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gfdcfg.tsccfg = Config->gfdcfg.tsccfg;
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->gcrccfg.nie   = Config->gcrccfg.nie;

  ee_rscfd_common_p[ UnitNumber_u08 ]->rmnb.nrxmb    = Config->rmnb.nrxmb;
  ee_rscfd_common_p[ UnitNumber_u08 ]->rmnb.rmpls    = Config->rmnb.rmpls;

	ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc0.rnc0   = Config->rnc[ 0 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc0.rnc1   = Config->rnc[ 1 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc0.rnc2   = Config->rnc[ 2 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc0.rnc3   = Config->rnc[ 3 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc1.rnc4   = Config->rnc[ 4 ];	
	ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc1.rnc5   = Config->rnc[ 5 ];		
	ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc1.rnc6   = Config->rnc[ 6 ];		
	ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc1.rnc7   = Config->rnc[ 7 ];				

	// added by @titron
	ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc[0]   = Config->rfcc[ 0 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc[1]   = Config->rfcc[ 1 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc[2]   = Config->rfcc[ 2 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc[3]   = Config->rfcc[ 3 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc[4]   = Config->rfcc[ 4 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc[5]   = Config->rfcc[ 5 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc[6]   = Config->rfcc[ 6 ];
	ee_rscfd_common_p[ UnitNumber_u08 ]->rfcc[7]   = Config->rfcc[ 7 ];

  return( EE_RSCFD_OK );
}    

//=============================================================================
// FunctionName: EE_RSCFD_EnableCOMFIFO
// IN  :         Unit, Channel, FIFO Number, Enable Flag
// OUT :         Success Status
// Description : Enable and Disable COMMON FIFO
// 
//=============================================================================

bit EE_RSCFD_EnableCOMFIFO( u08 UnitNumber_u08,
                            u08 ChannelNumber_u08,
                            u08 FIFONumber_u08,
                            u08 EnableFlag_u08 )
{
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].sts.mds == EE_RSCFD_OPMODE_RESET )
    return( EE_RSCFD_ERROR );
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->
    cfcc[ FIFONumber_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfe =
    ( u32 )EnableFlag_u08;
  
  __syncp();
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_EnableRXFIFO
// IN  :         Unit, FIFO Number, Enable Flag
// OUT :         Success Status
// Description : Enable and Disable RX FIFO
// 
//=============================================================================

bit EE_RSCFD_EnableRXFIFO( u08 UnitNumber_u08,
                           u08 FIFONumber_u08,
                           u08 EnableFlag_u08 )
{
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds == EE_RSCFD_OPMODE_RESET )
    return( EE_RSCFD_ERROR );
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->
    rfcc[ FIFONumber_u08 ].rfe = ( u32 )EnableFlag_u08;
  ee_rscfd_common_p[ UnitNumber_u08 ]->
    rfsts[ FIFONumber_u08 ].rfmlt = 0;
    
  __syncp();
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_SetBittiming
// IN  :         InputFrequency, Bitrate, TQ per Bit, Sampling Point, SJW
// OUT :         Main Prescaler Setting, Bit Rate Prescaler Setting, Bit Timing
// Description : Calculates Settings from Clock Supply and Parameters
// 
//=============================================================================

bit EE_RSCFD_SetBittiming( u08  UnitNumber_u08,
                           u32  InputFrequency_u32,
                           u32  Bitrate_u32,
                           bit  Timingspec_bit,
                           pu16 BRPSetting_pu16,
                           pu08 TSEG1Setting_pu08,
                           pu08 TSEG2Setting_pu08,
                           pu08 SJWSetting_pu08,
                           flt  SamplingPointPos_flt ) // optional Parameter, can be 0.0
{
  u16 TQPerBitUsed_u16;
  u16 TQPerBitMinDeviation_u16;
  u16 BRPSettingUsed_u16;
  u08 TSEG1SettingUsed_u16;
  u08 TSEG2SettingUsed_u16;
  flt SamplingPointPosUsed_flt = SamplingPointPos_flt;
  u32 BitrateAchieved_u32;
  s32 MinBitrateDeviation_s32;
  s32 BitrateDeviation_s32;

  /* Automatic settings generation */

  TQPerBitUsed_u16 = ( u16 )( InputFrequency_u32 / 
                            ( Bitrate_u32 * EE_RSCFD_TRLAYERFACTOR ) );

  if( Timingspec_bit == EE_RSCFD_BT_SPEC )
  {
    if( TQPerBitUsed_u16 > EE_RSCFD_BT_MAXTQ ) TQPerBitUsed_u16 = EE_RSCFD_BT_MAXTQ;
    if( TQPerBitUsed_u16 < EE_RSCFD_BT_MINTQ ) return( EE_RSCFD_ERROR );

    /* Minimum Bitrate check */
  
    if( ( InputFrequency_u32 / 
          ( ( u32 )TQPerBitUsed_u16 * EE_RSCFD_TRLAYERFACTOR * Bitrate_u32 ) ) >
          EE_RSCFD_BT_MAXBRP )
      return( EE_RSCFD_ERROR );
  }
  else
  {
    if( TQPerBitUsed_u16 > EE_RSCFD_BTD_MAXTQ ) TQPerBitUsed_u16 = EE_RSCFD_BTD_MAXTQ;
    if( TQPerBitUsed_u16 < EE_RSCFD_BTD_MINTQ ) return( EE_RSCFD_ERROR );

    /* Minimum Bitrate check */
  
    if( ( InputFrequency_u32 / 
          ( ( u32 )TQPerBitUsed_u16 * EE_RSCFD_TRLAYERFACTOR * Bitrate_u32 ) ) >
          EE_RSCFD_BTD_MAXBRP )
      return( EE_RSCFD_ERROR );
  }

  if( SamplingPointPos_flt == 0.0 ) SamplingPointPosUsed_flt = EE_RSCFD_BT_SPTOPTIMUM;

  /* Other plausibility checks */
  
  if( ( InputFrequency_u32 / Bitrate_u32 ) < EE_RSCFD_CLKMINFACTOR )
    return( EE_RSCFD_ERROR );
  
  /* Maximum Bitrate check */

  if( ( InputFrequency_u32 / 
        ( ( u32 )TQPerBitUsed_u16 * EE_RSCFD_TRLAYERFACTOR ) ) < Bitrate_u32 )
    return( EE_RSCFD_ERROR );

  /* Maximum Prescaler check */

  BRPSettingUsed_u16 = ( u16 )( InputFrequency_u32 / 
                              ( Bitrate_u32 *
                              ( u32 )TQPerBitUsed_u16 * 
                                EE_RSCFD_TRLAYERFACTOR ) );

  /* Frequency rounding optimization */
  
  BitrateAchieved_u32 = ( u32 )InputFrequency_u32 / 
    ( ( u32 ) ( ( u32 )BRPSettingUsed_u16 *
                ( u32 )TQPerBitUsed_u16 *
                ( u32 )EE_RSCFD_TRLAYERFACTOR ) );

  MinBitrateDeviation_s32 = ( s32 )( BitrateAchieved_u32 - Bitrate_u32 );
  if( MinBitrateDeviation_s32 < 0L ) 
    MinBitrateDeviation_s32 = -MinBitrateDeviation_s32;
  BitrateDeviation_s32    = MinBitrateDeviation_s32;

  while( BitrateAchieved_u32 != Bitrate_u32 )
    {
      TQPerBitUsed_u16--;
      if( Timingspec_bit == EE_RSCFD_BT_SPEC )
      {
        if( TQPerBitUsed_u16 < EE_RSCFD_BT_MINTQ ) break;
      }
      else
      {
        if( TQPerBitUsed_u16 < EE_RSCFD_BTD_MINTQ ) break;
      }
       
      BRPSettingUsed_u16 = ( u16 )( InputFrequency_u32 / 
                                  ( Bitrate_u32 *
                                  ( u32 )TQPerBitUsed_u16 * 
                                    EE_RSCFD_TRLAYERFACTOR ) );

      if( Timingspec_bit == EE_RSCFD_BT_SPEC )
      {
        if( BRPSettingUsed_u16 > EE_RSCFD_BT_MAXBRP )
          return( EE_RSCFD_ERROR );
      }          
      else
      {
        if( BRPSettingUsed_u16 > EE_RSCFD_BTD_MAXBRP )
          return( EE_RSCFD_ERROR );
      }
      
      BitrateAchieved_u32 = ( u32 )InputFrequency_u32 / 
                ( ( u32 ) ( ( u32 )BRPSettingUsed_u16 *
                            ( u32 )TQPerBitUsed_u16 *
                            ( u32 )EE_RSCFD_TRLAYERFACTOR ) );

      BitrateDeviation_s32 = ( s32 )( BitrateAchieved_u32 - Bitrate_u32 );
      if( BitrateDeviation_s32 < 0L ) BitrateDeviation_s32 = -BitrateDeviation_s32;
      if( BitrateDeviation_s32 < MinBitrateDeviation_s32 )
        {
          MinBitrateDeviation_s32  = BitrateDeviation_s32;
          TQPerBitMinDeviation_u16 = TQPerBitUsed_u16;
        }
    }

  if( BitrateAchieved_u32 != Bitrate_u32 )  /* Optimum Bitrate was not found */
    {
      TQPerBitUsed_u16 = TQPerBitMinDeviation_u16;   /* use the best value instead */
      BRPSettingUsed_u16 = ( u16 )( InputFrequency_u32 / 
                                  ( Bitrate_u32 *
                           ( u32 )TQPerBitUsed_u16 * 
                                  EE_RSCFD_TRLAYERFACTOR ) );
    }

  /* Sampling Point setting and segment splitting */
  /* Synchronisation Jump Width setting */
  
  if( Timingspec_bit == EE_RSCFD_BT_SPEC )
  {
    TSEG1SettingUsed_u16 = ( u16 )( ( flt )( TQPerBitUsed_u16 - EE_RSCFD_BT_SYNCSEGLEN ) 
                                    * SamplingPointPosUsed_flt );
    if( TSEG1SettingUsed_u16 < EE_RSCFD_BT_MINTSEG1 ) TSEG1SettingUsed_u16 = EE_RSCFD_BT_MINTSEG1;
    if( TSEG1SettingUsed_u16 > EE_RSCFD_BT_MAXTSEG1 ) TSEG1SettingUsed_u16 = EE_RSCFD_BT_MAXTSEG1;
  
    TSEG2SettingUsed_u16 = TQPerBitUsed_u16 - TSEG1SettingUsed_u16 - EE_RSCFD_BT_SYNCSEGLEN;
    if( TSEG2SettingUsed_u16 > EE_RSCFD_BT_MAXTSEG2 ) TSEG2SettingUsed_u16 = EE_RSCFD_BT_MAXTSEG2;
    if( TSEG2SettingUsed_u16 < EE_RSCFD_BT_MINTSEG2 ) TSEG2SettingUsed_u16 = EE_RSCFD_BT_MINTSEG2;
  
    TSEG1SettingUsed_u16 = TQPerBitUsed_u16 - TSEG2SettingUsed_u16 - EE_RSCFD_BT_SYNCSEGLEN;
    if( ( TSEG1SettingUsed_u16 < EE_RSCFD_BT_MINTSEG1 ) ||
        ( TSEG1SettingUsed_u16 > EE_RSCFD_BT_MAXTSEG1 ) ) return( EE_RSCFD_ERROR );
    
    *SJWSetting_pu08 = ( u08 )TSEG2SettingUsed_u16 - 1;
    if( *SJWSetting_pu08 >= EE_RSCFD_BT_MAXSJW )
  		*SJWSetting_pu08 = EE_RSCFD_BT_MAXSJW - 1;
  }
  else
  {
    TSEG1SettingUsed_u16 = ( u16 )( ( flt )( TQPerBitUsed_u16 - EE_RSCFD_BTD_SYNCSEGLEN ) 
                                    * SamplingPointPosUsed_flt );
    if( TSEG1SettingUsed_u16 < EE_RSCFD_BTD_MINTSEG1 ) TSEG1SettingUsed_u16 = EE_RSCFD_BTD_MINTSEG1;
    if( TSEG1SettingUsed_u16 > EE_RSCFD_BTD_MAXTSEG1 ) TSEG1SettingUsed_u16 = EE_RSCFD_BTD_MAXTSEG1;
  
    TSEG2SettingUsed_u16 = TQPerBitUsed_u16 - TSEG1SettingUsed_u16 - EE_RSCFD_BTD_SYNCSEGLEN;
    if( TSEG2SettingUsed_u16 > EE_RSCFD_BTD_MAXTSEG2 ) TSEG2SettingUsed_u16 = EE_RSCFD_BTD_MAXTSEG2;
    if( TSEG2SettingUsed_u16 < EE_RSCFD_BTD_MINTSEG2 ) TSEG2SettingUsed_u16 = EE_RSCFD_BTD_MINTSEG2;
  
    TSEG1SettingUsed_u16 = TQPerBitUsed_u16 - TSEG2SettingUsed_u16 - EE_RSCFD_BTD_SYNCSEGLEN;
    if( ( TSEG1SettingUsed_u16 < EE_RSCFD_BTD_MINTSEG1 ) ||
        ( TSEG1SettingUsed_u16 > EE_RSCFD_BTD_MAXTSEG1 ) ) return( EE_RSCFD_ERROR );
  
    *SJWSetting_pu08 = ( u08 )TSEG2SettingUsed_u16 - 1;
    if( *SJWSetting_pu08 >= EE_RSCFD_BTD_MAXSJW )
  		*SJWSetting_pu08 = EE_RSCFD_BTD_MAXSJW - 1;
  }
  
  /* Definition of Register Values */

  *BRPSetting_pu16   = ( u16 )( BRPSettingUsed_u16 - 1 );
  *TSEG1Setting_pu08 = ( u08 )( TSEG1SettingUsed_u16 - 1 );
  *TSEG2Setting_pu08 = ( u08 )( TSEG2SettingUsed_u16 - 1 );

  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_SetChannelConfiguration
// IN  :         UnitNumber, Channel Number, Config Set
// OUT :         Success Status
// Description : Performs Channel Configurations
// 
//=============================================================================

bit EE_RSCFD_SetChannelConfiguration( u08 UnitNumber_u08,
                                      u08 ChannelNumber_u08,
                                      const struct ee_rscfd_cfg_channel *Config )
{  
  u32 ClockFrequency_u32;
  u16 BRPSetting_u16;
  u08 TSEG1Setting_u08;
  u08 TSEG2Setting_u08;
  u08 SJWSetting_u08;
  u08 TXCounter_u08;
  bit Status_bit;
    
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].sts.mds != EE_RSCFD_OPMODE_RESET )
    return( EE_RSCFD_ERROR );

  /* first, clear any sleep mode */
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.cslpr = Config->ctr.cslpr;

  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gcfg.dcs == EE_RSCFD_CLOCK_SYS )
  {
    ClockFrequency_u32 = ( u32 )( OSCILLATOR_FREQUENCY * EE_RSCFD_FREQFACTOR );
    if( Config->arb_bitrate > EE_RSCFD_MAXBAUDRATE ) return( EE_RSCFD_ERROR );
    if( Config->data_bitrate > EE_RSCFD_MAXBAUDRATE ) return( EE_RSCFD_ERROR );
  }
  else
  {
    ClockFrequency_u32 = ( u32 )( OSCILLATOR_FREQUENCY * EE_RSCFD_FREQFACTORPLLBP );
    if( Config->arb_bitrate > EE_RSCFD_MAXBAUDRATEPLLBP ) return( EE_RSCFD_ERROR );
    if( Config->data_bitrate > EE_RSCFD_MAXBAUDRATEPLLBP ) return( EE_RSCFD_ERROR );
  }
  
  if( Config->arb_bitrate != 0L )
  {
    Status_bit = EE_RSCFD_SetBittiming( UnitNumber_u08,
                                        ClockFrequency_u32,
                                        Config->arb_bitrate,
                                        EE_RSCFD_BT_SPEC,
                                        &BRPSetting_u16,
                                        &TSEG1Setting_u08,
                                        &TSEG2Setting_u08,
                                        &SJWSetting_u08,
                                        Config->arb_samplingpointpos );
    if( Status_bit != EE_RSCFD_OK ) return( EE_RSCFD_ERROR );
      
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ncfg.nbrp = 
      ( u32 )BRPSetting_u16;
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ncfg.ntseg1 = 
      ( u32 )TSEG1Setting_u08;
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ncfg.ntseg2 = 
      ( u32 )TSEG2Setting_u08;
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ncfg.nsjw = 
      ( u32 )SJWSetting_u08;
  }
  else
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ncfg.nbrp = 
      Config->ncfg.nbrp;
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ncfg.ntseg1 = 
      Config->ncfg.ntseg1;
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ncfg.ntseg2 = 
      Config->ncfg.ntseg2;
    ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ncfg.nsjw = 
      Config->ncfg.nsjw;
  }
    
  if( Config->data_bitrate != 0L )
  {
    Status_bit = EE_RSCFD_SetBittiming( UnitNumber_u08,
                                        ClockFrequency_u32,
                                        Config->data_bitrate,
                                        EE_RSCFD_BTD_SPEC,
                                        &BRPSetting_u16,
                                        &TSEG1Setting_u08,
                                        &TSEG2Setting_u08,
                                        &SJWSetting_u08,
                                        Config->data_samplingpointpos );
    if( Status_bit != EE_RSCFD_OK ) return( EE_RSCFD_ERROR );
      
    ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].dcfg.dbrp = 
      ( u32 )BRPSetting_u16;
    ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].dcfg.dtseg1 = 
      ( u32 )TSEG1Setting_u08;
    ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].dcfg.dtseg2 = 
      ( u32 )TSEG2Setting_u08;
    ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].dcfg.dsjw = 
      ( u32 )SJWSetting_u08;
  }
  else
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].dcfg.dbrp = 
      Config->dcfg.dbrp;
    ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].dcfg.dtseg1 = 
      Config->dcfg.dtseg1;
    ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].dcfg.dtseg2 = 
      Config->dcfg.dtseg2;
    ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].dcfg.dsjw = 
      Config->dcfg.dsjw;
  }

  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.chmdc = Config->ctr.chmdc;
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.rtbo = Config->ctr.rtbo;
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.ie = Config->ctr.ie;
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.bom = Config->ctr.bom;
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.errd = Config->ctr.errd;
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.ctme = Config->ctr.ctme;
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.ctms = Config->ctr.ctms;
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.crct = Config->ctr.crct;
  ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.rom = Config->ctr.rom;
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdctr.eocclr = Config->fdctr.eocclr;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdctr.socclr = Config->fdctr.socclr;
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.eoccfg = Config->fdcfg.eoccfg;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.tdcoc  = Config->fdcfg.tdcoc;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.tdce   = Config->fdcfg.tdce;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.esic   = Config->fdcfg.esic;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.tdco   = Config->fdcfg.tdco;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.gwen   = Config->fdcfg.gwen;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.gwfdf  = Config->fdcfg.gwfdf;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.gwbrs  = Config->fdcfg.gwbrs;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.fdoe   = Config->fdcfg.fdoe;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.refe   = Config->fdcfg.refe;
  ee_rscfd_common_p[ UnitNumber_u08 ]->fdch[ ChannelNumber_u08 ].fdcfg.cloe   = Config->fdcfg.cloe;
  
  for( TXCounter_u08 = 0;
       TXCounter_u08 < EE_RSCFD_MAXTXBUFFERS;
       TXCounter_u08++ )
  {
    if( ( Config->tmiec >> TXCounter_u08 ) & 0x01 )
    {
      ee_rscfd_common_p[ UnitNumber_u08 ]->
        tmiec[ EE_RSCFD_COMTXREG( ChannelNumber_u08 ) ] |= 
        ( 1 << ( TXCounter_u08 + ( ChannelNumber_u08 * EE_RSCFD_MAXTXBUFFERS ) -
        EE_RSCFD_COMREGSBITS * EE_RSCFD_COMTXREG( ChannelNumber_u08 ) ) );
    }
    else
    {
      ee_rscfd_common_p[ UnitNumber_u08 ]->
        tmiec[ EE_RSCFD_COMTXREG( ChannelNumber_u08 ) ] &= 
        ~( 1 << ( TXCounter_u08 + ( ChannelNumber_u08 * EE_RSCFD_MAXTXBUFFERS ) -
        EE_RSCFD_COMREGSBITS * EE_RSCFD_COMTXREG( ChannelNumber_u08 ) ) );
    }
  }

  for( TXCounter_u08 = 0;
       TXCounter_u08 < EE_RSCFD_MAXTXQUEUES;
       TXCounter_u08++ )
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      txq[ TXCounter_u08 ].cc[ ChannelNumber_u08 ].dc = 
      Config->txq[ TXCounter_u08 ].dc;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      txq[ TXCounter_u08 ].cc[ ChannelNumber_u08 ].im = 
      Config->txq[ TXCounter_u08 ].im;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      txq[ TXCounter_u08 ].cc[ ChannelNumber_u08 ].ie = 
      Config->txq[ TXCounter_u08 ].ie;
  }
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].dte  = Config->thlcc.dte;
  ee_rscfd_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].im   = Config->thlcc.im;
  ee_rscfd_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].ie   = Config->thlcc.ie;

	/* Set Channel to HALT mode, in order to activate queues and lists */

	ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ctr.chmdc =
		EE_RSCFD_OPMODE_HALT;
  __syncp();
	while( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].sts.mds
			   != EE_RSCFD_OPMODE_HALT );
	
  for( TXCounter_u08 = 0;
       TXCounter_u08 < EE_RSCFD_MAXTXQUEUES;
       TXCounter_u08++ )
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      txq[ TXCounter_u08 ].cc[ ChannelNumber_u08 ].qe = 
      Config->txq[ TXCounter_u08 ].qe;
  }

  ee_rscfd_common_p[ UnitNumber_u08 ]->thlcc[ ChannelNumber_u08 ].thle = Config->thlcc.thle;

	return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_SetGlobalFIFOConfiguration
// IN  :         UnitNumber, Global configuration set
// Description : Performs Global Configurations
//
//=============================================================================

bit EE_RSCFD_SetGlobalFIFOConfiguration( u08 Unit_u08, 
                                         const struct ee_rscfd_cfg_global *Config ) 
{
  u08 CurrentFIFO_u08;

  if( Unit_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );

  /* Must be in global reset to set the global configuration! */

  if( ee_rscfd_common_p[ Unit_u08 ]->gsts.mds != EE_RSCFD_OPMODE_RESET ) return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ Unit_u08 ]->gsts.slps != 0 ) return( EE_RSCFD_ERROR );

  for( CurrentFIFO_u08 = 0; CurrentFIFO_u08 < EE_RSCFD_MAXRXFIFOS; CurrentFIFO_u08++ ) 
  {
    ee_rscfd_common_p[ Unit_u08 ]->rfcc[ CurrentFIFO_u08 ].rfie =   Config->rfcc[ CurrentFIFO_u08 ].rfie;
    ee_rscfd_common_p[ Unit_u08 ]->rfcc[ CurrentFIFO_u08 ].rfpls =  Config->rfcc[ CurrentFIFO_u08 ].rfpls;
    ee_rscfd_common_p[ Unit_u08 ]->rfcc[ CurrentFIFO_u08 ].rfdc =   Config->rfcc[ CurrentFIFO_u08 ].rfdc;
    ee_rscfd_common_p[ Unit_u08 ]->rfcc[ CurrentFIFO_u08 ].rfim =   Config->rfcc[ CurrentFIFO_u08 ].rfim;
    ee_rscfd_common_p[ Unit_u08 ]->rfcc[ CurrentFIFO_u08 ].rfigcv = Config->rfcc[ CurrentFIFO_u08 ].rfigcv;
  }
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_SetCOMFIFOConfiguration
// IN  :         UnitNumber, Channel Number, Config Set
// OUT :         Success Status
// Description : Performs Channel COM FIFO Configurations
//
//=============================================================================

bit EE_RSCFD_SetCOMFIFOConfiguration( u08 UnitNumber_u08,
                                      u08 ChannelNumber_u08,
                                      const struct ee_rscfd_cfg_channel *Config )
{  
  u08 TXCounter_u08;
  
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );

  /* Must be in global reset to set the global configuration! */
  
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCFD_OPMODE_RESET )
    return( EE_RSCFD_ERROR );

  for( TXCounter_u08 = 0;
       TXCounter_u08 < EE_RSCFD_MAXCOMFIFOS;
       TXCounter_u08++ )
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfrxie =
      Config->cfcc[ TXCounter_u08 ].cfrxie;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cftxie =
      Config->cfcc[ TXCounter_u08 ].cftxie;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfpls =
      Config->cfcc[ TXCounter_u08 ].cfpls;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfdc =
      Config->cfcc[ TXCounter_u08 ].cfdc;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfim =
      Config->cfcc[ TXCounter_u08 ].cfim;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfigcv =
      Config->cfcc[ TXCounter_u08 ].cfigcv;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfm =
      Config->cfcc[ TXCounter_u08 ].cfm;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfitss =
      Config->cfcc[ TXCounter_u08 ].cfitss;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfitr =
      Config->cfcc[ TXCounter_u08 ].cfitr;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cftml =
      Config->cfcc[ TXCounter_u08 ].cftml;
    ee_rscfd_common_p[ UnitNumber_u08 ]->
      cfcc[ TXCounter_u08 + ChannelNumber_u08 * EE_RSCFD_MAXCOMFIFOS ].cfitt =
      Config->cfcc[ TXCounter_u08 ].cfitt;
  }
	return( EE_RSCFD_OK ); 
}

//=============================================================================
// FunctionName: EE_RSCFD_TxAbort
// IN  :         UnitNumber, Channel Number, Message
// OUT :         Success Status
// Description : Performs Message Sending
//=============================================================================
bit EE_RSCFD_TxAbort( u08  UnitNumber_u08,
                      u08  ChannelNumber_u08,
                      struct ee_rscfd_message *Message )
{
  u08 SendBox_u08;
  u08 FirstBox_u08;
  u08 LastBox_u08;

  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].sts.mds != EE_RSCFD_OPMODE_OPER )
    return( EE_RSCFD_ERROR );

  switch( Message->path )
  {
    case EE_RSCFD_PATH_MSGBOX:         /* direct abortion of message box */
      if( Message->pathdetail == EE_RSCFD_PATHDETAIL_ANY )  /* abort all */
      {
        FirstBox_u08 = 0;
        LastBox_u08  = EE_RSCFD_MAXTXBUFFERS - 1;
      }
      else
      {
        FirstBox_u08 = Message->pathdetail;
        LastBox_u08  = FirstBox_u08;
      }
      break;

    case EE_RSCFD_PATH_COMFIFO:        /* only one FIFO abort at a time */
      if( Message->pathdetail == EE_RSCFD_PATHDETAIL_ANY )
      {
        return( EE_RSCFD_ERROR );
      }
      else
      {
        SendBox_u08 = Message->pathdetail;
        if( SendBox_u08 >= EE_RSCFD_MAXCOMFIFOS )
        {
          return( EE_RSCFD_ERROR );
        }
        else
        {
          SendBox_u08 = ( EE_RSCFD_MAXCOMFIFOS * ChannelNumber_u08 ) + 
                        Message->pathdetail;
          if( ee_rscfd_common_p[ UnitNumber_u08 ]->cfcc[ SendBox_u08 ].cfe )
          {
            FirstBox_u08 = ee_rscfd_common_p[ UnitNumber_u08 ]->
                                        cfcc[ SendBox_u08 ].cftml;
            LastBox_u08 = FirstBox_u08;
          }
          else return( EE_RSCFD_ERROR );
        }
      }
      break;

    case EE_RSCFD_PATH_TXQUEUE:   /* only one TX Queue abort at a time */
      if( Message->pathdetail == EE_RSCFD_PATHDETAIL_ANY )
      {
        return( EE_RSCFD_ERROR );
      }
      else
      {
        SendBox_u08 = Message->pathdetail;
        if( SendBox_u08 >= EE_RSCFD_MAXTXQUEUES )
        {
          return( EE_RSCFD_ERROR );
        }
        else
        {
          if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ SendBox_u08 ].cc
                               [ ChannelNumber_u08 ].qe )
          {
            FirstBox_u08 = ee_rscfd_txqentries[ UnitNumber_u08 ]
                                              [ ChannelNumber_u08 ]
                                              [ SendBox_u08 ];
            LastBox_u08 = FirstBox_u08;
          }
          else return( EE_RSCFD_ERROR );
        }
      }
      break;

    default:
      return( EE_RSCFD_ERROR );
  }
  
  for( SendBox_u08 =  FirstBox_u08;
       SendBox_u08 <= LastBox_u08;
       SendBox_u08++ )
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->tmc
                     [( EE_RSCFD_MAXTXBUFFERS * ChannelNumber_u08 + 
                        SendBox_u08 ) ] |= ( u08 )
                      ( EE_RSCFD_TMC_SET_AR );
  }

  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_SendMessage
// IN  :         UnitNumber, Channel Number, Message
// OUT :         Success Status
// Description : Performs Message Sending
//=============================================================================
bit EE_RSCFD_SendMessage( u08  UnitNumber_u08,
                          u08  ChannelNumber_u08,
                          pu08 Status_pu08,
                          struct ee_rscfd_message *Message )
{
  u08 SendBox_u08;
  u08 FirstBox_u08;
  u08 LastBox_u08;
  u08 SendBoxOccupied_u08 = EE_RSCFD_CLEAR;
  u08 FIFONumber_u08;
  
  *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
  
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].sts.mds != EE_RSCFD_OPMODE_OPER )
    return( EE_RSCFD_ERROR );
    
  *Status_pu08 = EE_RSCFD_FAULT_NONE;

  switch( Message->path )
  {
    case EE_RSCFD_PATH_MSGBOX:      /* search a free SendBox, if required */
    {
      if( Message->pathdetail != EE_RSCFD_PATHDETAIL_ANY )
      {
        FirstBox_u08 = Message->pathdetail;
        LastBox_u08  = FirstBox_u08;
        if( FirstBox_u08 >= EE_RSCFD_MAXTXBUFFERS )
        {
          *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
          return( EE_RSCFD_ERROR );
        }
      }
      else
      {
        FirstBox_u08 = 0;
        LastBox_u08  = ( EE_RSCFD_MAXTXBUFFERS - 1 );
      }
      
      for( SendBox_u08 =  FirstBox_u08;
           SendBox_u08 <= LastBox_u08; )
      {
        if( ( ( ( ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts
                  [ ( EE_RSCFD_MAXTXBUFFERS * ChannelNumber_u08 + 
                      SendBox_u08 ) ] ) )
                & EE_RSCFD_TMSTS_STSMSK ) == 
                EE_RSCFD_TMSTS_CLEAR )    /* check pending TRQ */
        {
          for( FIFONumber_u08 = 0;
               FIFONumber_u08 < EE_RSCFD_MAXCOMFIFOS;
               FIFONumber_u08++ )   /* check any COM FIFO assignment */
          
          {
            if( ( ( u08 )( ee_rscfd_common_p[ UnitNumber_u08 ]->cfcc
                                            [ EE_RSCFD_MAXCOMFIFOS * 
                                            ChannelNumber_u08 ].cftml ) 
                                            == SendBox_u08 ) &&
                         ( ee_rscfd_common_p[ UnitNumber_u08 ]->cfcc
                                            [ EE_RSCFD_MAXCOMFIFOS * 
                                            ChannelNumber_u08 ].cfe ) )
            {
              SendBoxOccupied_u08 = EE_RSCFD_SET;
              break;
            }
          }
          for( FIFONumber_u08 = 0;
               FIFONumber_u08 < EE_RSCFD_MAXTXQUEUES;
               FIFONumber_u08++ )   /* check any TX Queue assignment */
          {
            if( ( ( u08 )( ee_rscfd_txqentries[ UnitNumber_u08 ]
                                              [ ChannelNumber_u08 ]
                                              [ FIFONumber_u08 ] -
                           ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ FIFONumber_u08 ].cc
                                            [ ChannelNumber_u08 ].dc <= SendBox_u08 ) ) &&
                ( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ FIFONumber_u08 ].cc
                                   [ ChannelNumber_u08 ].qe != EE_RSCFD_TXQ_OFF ) && 
                ( ee_rscfd_txqentries[ UnitNumber_u08 ]
                                     [ ChannelNumber_u08 ]
                                     [ FIFONumber_u08 ] >= SendBox_u08 ) )
            {
              SendBoxOccupied_u08 = EE_RSCFD_SET;            
            }
          }
        }
        else
        {
          SendBoxOccupied_u08 = EE_RSCFD_SET;
        }

        if( SendBoxOccupied_u08 == EE_RSCFD_CLEAR )
        {
          /* Initiate Sending with this box and exit the box searching */
          
          EE_RSCFD_SetIDData( &ee_rscfd_txmsg_p[ UnitNumber_u08 ]
                                               [ ChannelNumber_u08 ]->
                                            buf[ SendBox_u08 ],
                              Message );                           
          
          ee_rscfd_common_p[ UnitNumber_u08 ]->tmsts
                           [ ( EE_RSCFD_MAXTXBUFFERS * ChannelNumber_u08 + 
                             SendBox_u08 ) ] &= ( u08 )
                             ( ~( EE_RSCFD_TMSTS_RFMSK ) );

          ee_rscfd_common_p[ UnitNumber_u08 ]->tmc
                           [ ( EE_RSCFD_MAXTXBUFFERS * ChannelNumber_u08 + 
                             SendBox_u08 ) ] |= ( u08 )
                             ( EE_RSCFD_TMC_SET_TR );
          break;
        }
        else
        {
          SendBoxOccupied_u08 = EE_RSCFD_CLEAR;   /* test next SendBox */
        }
        
        SendBox_u08++;
      }
      
      if( SendBox_u08 >= EE_RSCFD_MAXTXBUFFERS )
      {
        *Status_pu08 = EE_RSCFD_FAULT_BUSY;
        return( EE_RSCFD_OK );
      }
      break;
    }
    
    case EE_RSCFD_PATH_COMFIFO:                    /* use dedicated FIFO */
    {
      if( Message->pathdetail != EE_RSCFD_PATHDETAIL_ANY )
      {
        SendBox_u08 = Message->pathdetail;
        if( SendBox_u08 >= EE_RSCFD_MAXCOMFIFOS )
        {
          *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
          return( EE_RSCFD_ERROR );
        }
        else
        {
          SendBox_u08 = ( EE_RSCFD_MAXCOMFIFOS * ChannelNumber_u08 ) + 
                        Message->pathdetail;
          if( ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ SendBox_u08 ].cffll )
          {
            *Status_pu08 = EE_RSCFD_FAULT_BUSY;
            return( EE_RSCFD_OK );                    
          }
        }
      }
      else                                  /* search enabled, non-full FIFO */
      {
        SendBox_u08 = EE_RSCFD_FIFO_NEXTELEMENT;
        
        for( FIFONumber_u08 = ( EE_RSCFD_MAXCOMFIFOS * ChannelNumber_u08 );
             FIFONumber_u08 < ( EE_RSCFD_MAXCOMFIFOS * ( ChannelNumber_u08 + 1 ) );
             FIFONumber_u08++ )
        {
          if( ee_rscfd_common_p[ UnitNumber_u08 ]->cfcc[ FIFONumber_u08 ].cfe )
          {
            if( !ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cffll )
            {
              SendBox_u08 = FIFONumber_u08;
              if( ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ FIFONumber_u08 ].cfemp )
              {
                break;             /* an empty FIFO can be used immediately */
              }
            }
          }
        }
      }
      
      if( SendBox_u08 != EE_RSCFD_FIFO_NEXTELEMENT ) /* feed message into FIFO */
      {
        SendBox_u08 %= EE_RSCFD_MAXCOMFIFOS;
        
        EE_RSCFD_SetIDDataCFIFO( &ee_rscfd_comfifo_p[ UnitNumber_u08 ]
                                                    [ ChannelNumber_u08 ]->
                                                 buf[ SendBox_u08 ],
                                 Message );
                                 
        ee_rscfd_common_p[ UnitNumber_u08 ]->cfpctr
                         [ EE_RSCFD_MAXCOMFIFOS * ChannelNumber_u08 + 
                           SendBox_u08 ].fpc = EE_RSCFD_FIFO_NEXTELEMENT;      
      }
      else                  /* free and enabled FIFO was not found */
      {
        *Status_pu08 = EE_RSCFD_FAULT_BUSY;
        return( EE_RSCFD_OK );        
      }
      break;
    }
      
    case EE_RSCFD_PATH_TXQUEUE:                /* use dedicated TX Queue */
    {
      if( Message->pathdetail != EE_RSCFD_PATHDETAIL_ANY )
      {
        SendBox_u08 = Message->pathdetail;
        if( SendBox_u08 >= EE_RSCFD_MAXTXQUEUES )
        {
          *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
          return( EE_RSCFD_ERROR );
        }
      }
      else                               
      {
        SendBoxOccupied_u08 = EE_RSCFD_SET;
        
        for( SendBox_u08 = 0;            /* search enabled, non-full queue */
             SendBox_u08 < EE_RSCFD_MAXTXQUEUES;
             SendBox_u08++ )
        {
          if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ SendBox_u08 ].cc
                               [ ChannelNumber_u08 ].qe )
          {
            if( !ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ SendBox_u08 ].sts
                                  [ ChannelNumber_u08 ].fll )
            {
              SendBoxOccupied_u08 = EE_RSCFD_CLEAR;
              if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ SendBox_u08 ].sts
                                   [ ChannelNumber_u08 ].emp )
              {
                break;    /* empty queue can be used immediately */
              }
            }
          }
        }
      }
      
      if( SendBoxOccupied_u08 == EE_RSCFD_CLEAR )  /* feed message into queue */
      {
        LastBox_u08 = ee_rscfd_txqentries[ UnitNumber_u08 ]
                                         [ ChannelNumber_u08 ]
                                         [ SendBox_u08 ];
                                         
        EE_RSCFD_SetIDData( &ee_rscfd_txmsg_p[ UnitNumber_u08 ]
                                             [ ChannelNumber_u08 ]->
                                          buf[ LastBox_u08 ],
                            Message );
                       
        ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ SendBox_u08 ].pctr
                         [ ChannelNumber_u08 ] = EE_RSCFD_TXQ_NEXTELEMENT;
      }
      else           /* free and enabled queue was not found */
      {
        *Status_pu08 = EE_RSCFD_FAULT_BUSY;
        return( EE_RSCFD_OK );        
      }
      break;
    }
    
    default:
      *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
      return( EE_RSCFD_ERROR );
  }
     
  __syncm();
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_ReceiveMessage
// IN  :         UnitNumber, (preferred) Reception path within message
// OUT :         Success Status
//               Message with content and information
// Description : Performs Message Reception
// 
//=============================================================================
bit EE_RSCFD_ReceiveMessage( u08  UnitNumber_u08,
                             pu08 Status_pu08,
                             struct ee_rscfd_message *Message )
{
  u08 ReceiveBox_u08;
  u08 SearchBegin_u08;
  u08 SearchEnd_u08;
  
  *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
  
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCFD_OPMODE_OPER )
    return( EE_RSCFD_ERROR );
    
  *Status_pu08 = EE_RSCFD_FAULT_NODATA;
  
  if( ( Message->path == EE_RSCFD_PATH_MSGBOX ) ||
      ( Message->path == EE_RSCFD_PATH_ANY ) ) /* check within message boxes */
  {
    if( Message->pathdetail == EE_RSCFD_GLOBAL )    /* read first filled box */
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCFD_MAXRXBUFFERS - 1;
    }
    else                             /* read dedicated box (typical polling) */
    {
      SearchBegin_u08 = Message->pathdetail;
      SearchEnd_u08   = Message->pathdetail;
      
      if( SearchBegin_u08 >= EE_RSCFD_MAXRXBUFFERS )
      {
        *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
        return( EE_RSCFD_ERROR );
      }
    }
    
    for( ReceiveBox_u08 =  SearchBegin_u08;
         ReceiveBox_u08 <= SearchEnd_u08;
         ReceiveBox_u08++ )
    {
      while( ee_rscfd_common_p[ UnitNumber_u08 ]->rmnd
                              [ EE_RSCFD_COMRXREG( ReceiveBox_u08 ) ] >> 
                                EE_RSCFD_COMRXBIT( ReceiveBox_u08 ) & 
                                EE_RSCFD_SET )
      {
        *Status_pu08 = EE_RSCFD_FAULT_NONE;
                                                      /* Clear new data flag */
        ee_rscfd_common_p[ UnitNumber_u08 ]->rmnd
                         [ EE_RSCFD_COMRXREG( ReceiveBox_u08 ) ] = ( u32 )
                         ( ~( 1 << EE_RSCFD_COMRXBIT( ReceiveBox_u08 ) ) );
        
        EE_RSCFD_GetMessage( &ee_rscfd_rxmsg_p[ UnitNumber_u08 ]->
                                           buf[ ReceiveBox_u08 ],
                             Message );
      }
      if( *Status_pu08 != EE_RSCFD_FAULT_NODATA ) break;
    }
  }

  if( ( Message->path == EE_RSCFD_PATH_RXFIFO ) ||
      ( ( Message->path == EE_RSCFD_PATH_ANY ) &&
        ( *Status_pu08 == EE_RSCFD_FAULT_NODATA ) ) ) /* check within RX FIFO */
  {
    if( Message->pathdetail == EE_RSCFD_GLOBAL )    /* read first filled FIFO */
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCFD_MAXRXFIFOS - 1;
    }
    else                                               /* read dedicated FIFO */
    {
      SearchBegin_u08 = Message->pathdetail;
      SearchEnd_u08   = Message->pathdetail;
 
      if( SearchBegin_u08 >= EE_RSCFD_MAXRXFIFOS )
      {
        *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
        return( EE_RSCFD_ERROR );
      }
    }
    
    for( ReceiveBox_u08 =  SearchBegin_u08;
         ReceiveBox_u08 <= SearchEnd_u08;
         ReceiveBox_u08++ )
    {
      if( !ee_rscfd_common_p[ UnitNumber_u08 ]->rfsts[ ReceiveBox_u08 ].rfemp )
      {
        *Status_pu08 = EE_RSCFD_FAULT_NONE;
        
        EE_RSCFD_GetMessageRF( &ee_rscfd_rxfifo_p[ UnitNumber_u08 ]->
                                              buf[ ReceiveBox_u08 ],
                               Message );
        
        ee_rscfd_common_p[ UnitNumber_u08 ]->rfpctr[ ReceiveBox_u08 ].fpc = 
          EE_RSCFD_FIFO_NEXTELEMENT;
        
        break;
      }
    }    
  }

  if( ( Message->path == EE_RSCFD_PATH_COMFIFO ) ||
      ( ( Message->path == EE_RSCFD_PATH_ANY ) &&
        ( *Status_pu08 == EE_RSCFD_FAULT_NODATA ) ) ) /* check within COMFIFO */
  {
    if( Message->pathdetail == EE_RSCFD_GLOBAL )    /* read first filled FIFO */
    {
      SearchBegin_u08 = 0;
      SearchEnd_u08   = EE_RSCFD_MAXCOMFIFOS * ee_rscfd_channels[ UnitNumber_u08 ] - 1;
    }
    else                                               /* read dedicated FIFO */
    {
      SearchBegin_u08 = Message->pathdetail;
      SearchEnd_u08   = Message->pathdetail;
 
      if( SearchBegin_u08 >= ( EE_RSCFD_MAXCOMFIFOS * ee_rscfd_channels[ UnitNumber_u08 ] ) )
      {
        *Status_pu08 = EE_RSCFD_FAULT_PARAMETER;
        return( EE_RSCFD_ERROR );
      }
    }
    
    for( ReceiveBox_u08 =  SearchBegin_u08;
         ReceiveBox_u08 <= SearchEnd_u08;
         ReceiveBox_u08++ )
    {
      if( !ee_rscfd_common_p[ UnitNumber_u08 ]->cfsts[ ReceiveBox_u08 ].cfemp )
      {
        *Status_pu08 = EE_RSCFD_FAULT_NONE;
        
        EE_RSCFD_GetMessageCF( &ee_rscfd_comfifo_p[ UnitNumber_u08 ]
		                                              [ ReceiveBox_u08 /
					                                     EE_RSCFD_MAXCOMFIFOS ]->
                                               buf[ ReceiveBox_u08 ],
                               Message );
        
        ee_rscfd_common_p[ UnitNumber_u08 ]->cfpctr[ ReceiveBox_u08 ].fpc = 
          EE_RSCFD_FIFO_NEXTELEMENT;
        
        break;
      }
    }    
  }

  __syncm();
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_SetAFLEntry
// IN  :         UnitNumber, Channel Number, AFL Entry object
// OUT :         Success Status
// Description : Enters a new entry into the AFL
//               Limitations for routing are not verified!
//=============================================================================
bit EE_RSCFD_SetAFLEntry( u08  UnitNumber_u08,
                          u08  ChannelNumber_u08,
													u16  RuleNumber_u16,
                          struct ee_rscfd_a_afl *AFLEntry )
{
  u08 AFLPage_u08;
  u16 AFLElement_u16 = RuleNumber_u16;
  u08 AFLIndex_u08;
  u08 AFLChannelEntry[ EE_RSCFD_MAXCHANNELS ];
  
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
    return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].sts.mds ==
			EE_RSCFD_OPMODE_OPER )
    return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.gslpr == EE_RSCFD_SET )
    return( EE_RSCFD_ERROR );
    
  for( AFLIndex_u08 = 0;
       AFLIndex_u08 <= ChannelNumber_u08;
       AFLIndex_u08++ )
  {
    switch( AFLIndex_u08 )
    {
      case EE_RSCFD_CHANNEL0:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( u08 )ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc0.rnc0;
        break;
      case EE_RSCFD_CHANNEL1:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( u08 )ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc0.rnc1;
        AFLElement_u16 += ( u16 )AFLChannelEntry[ EE_RSCFD_CHANNEL0 ];
        break;
      case EE_RSCFD_CHANNEL2:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( u08 ) ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc0.rnc2;
        AFLElement_u16 += (u16) AFLChannelEntry[ EE_RSCFD_CHANNEL1 ];
        break;
	    case EE_RSCFD_CHANNEL3:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( u08 ) ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc0.rnc3;
        AFLElement_u16 += (u16) AFLChannelEntry[ EE_RSCFD_CHANNEL2 ];
        break;
	    case EE_RSCFD_CHANNEL4:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( u08 ) ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc1.rnc4;
        AFLElement_u16 += (u16) AFLChannelEntry[ EE_RSCFD_CHANNEL3 ];
        break;
	    case EE_RSCFD_CHANNEL5:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( u08 ) ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc1.rnc5;
        AFLElement_u16 += (u16) AFLChannelEntry[ EE_RSCFD_CHANNEL4 ];
        break;
	    case EE_RSCFD_CHANNEL6:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( u08 ) ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc1.rnc6;
        AFLElement_u16 += (u16) AFLChannelEntry[ EE_RSCFD_CHANNEL5 ];
        break;
	    case EE_RSCFD_CHANNEL7:
        AFLChannelEntry[ AFLIndex_u08 ] = 
          ( u08 ) ee_rscfd_common_p[ UnitNumber_u08 ]->gaflc1.rnc7;
        AFLElement_u16 += (u16) AFLChannelEntry[ EE_RSCFD_CHANNEL6 ];
        break;
      default: 
        return( EE_RSCFD_ERROR );
    }
  }
  
  if( AFLElement_u16 >= EE_RSCFD_MAXAFLENTRIES ) 
    return( EE_RSCFD_ERROR );

//	if( RuleNumber_u16 >= AFLChannelEntry[ ChannelNumber_u08 ] )
//		return( EE_RSCFD_ERROR );
	if( RuleNumber_u16 > AFLChannelEntry[ ChannelNumber_u08 ] )
		return( EE_RSCFD_ERROR );

  if( AFLChannelEntry[ ChannelNumber_u08 ] > EE_RSCFD_MAXAFLCHANSET )
    return( EE_RSCFD_ERROR );
    
  AFLPage_u08    = ( u08 )( AFLElement_u16 / EE_RSCFD_AFLPAGESIZE );
	AFLElement_u16 = AFLElement_u16 % EE_RSCFD_AFLPAGESIZE;

  ee_rscfd_common_p[ UnitNumber_u08 ]->gafle.afldae = EE_RSCFD_SET;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gafle.aflpn  = ( u32 )AFLPage_u08;
  
  __syncp();

  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].id.id =
    AFLEntry->id.id;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].id.lb =
    AFLEntry->id.lb;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].id.rtr =
    AFLEntry->id.rtr;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].id.ide =
    AFLEntry->id.ide;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].mask.id =
    AFLEntry->mask.id;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].mask.rtr =
    AFLEntry->mask.rtr;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].mask.ide =
    AFLEntry->mask.ide;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptr0.rmdp =
    AFLEntry->ptr0.rmdp;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptr0.rmv =
    AFLEntry->ptr0.rmv;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptr0.ptr =
    AFLEntry->ptr0.ptr;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptr0.dlc =
    AFLEntry->ptr0.dlc;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptr1.rxfifomask =
    AFLEntry->ptr1.rxfifomask;
  ee_rscfd_aflpage_p[ UnitNumber_u08 ]->af[ AFLElement_u16 ].ptr1.comfifomask =
    AFLEntry->ptr1.comfifomask;

  ee_rscfd_common_p[ UnitNumber_u08 ]->gafle.afldae = EE_RSCFD_CLEAR;
  
  __syncp();
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_GetTimeStampCounter
// IN  :         Unit Number
// OUT :         Success Status
// Description : Returns current value of Time Stamp Counter
// 
//=============================================================================
bit EE_RSCFD_GetTimeStampCounter( u08  UnitNumber_u08,
                                  pu32 TimeStampValue_pu32 )
{
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  
  *TimeStampValue_pu32 = ee_rscfd_common_p[ UnitNumber_u08 ]->gtsc;
  
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_RAMTest
// IN  :         Unit Number
// OUT :         Success Status
// Description : Executes RAM Test
// 
//=============================================================================
bit EE_RSCFD_RAMTest( u08 UnitNumber_u08 )
{
  u16 RAMPage_u16;
  u16 RAMElement_u16;
  u32 RAMData_u32 = 0x00000001;

  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCFD_OPMODE_HALT )
    return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gctr.gslpr == EE_RSCFD_SET )
    return( EE_RSCFD_ERROR );

  /* Unlock the test mode */
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->glockk     = EE_RSCFD_RAMTEST_KEY1;
  ee_rscfd_common_p[ UnitNumber_u08 ]->glockk     = EE_RSCFD_RAMTEST_KEY2;
  ee_rscfd_common_p[ UnitNumber_u08 ]->gtctr      = EE_RSCFD_RAMTEST_MODE;
  
  // Reading back zero value from cleared RAM
  for( RAMPage_u16 = 0; RAMPage_u16 < EE_RSCFD_RAMTEST_PAGES; RAMPage_u16++ )
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->gtcfg.rtmps = RAMPage_u16;
	
    for( RAMElement_u16 = 0; RAMElement_u16 < EE_RSCFD_RAMTEST_ENTRIES; RAMElement_u16++ )
    {
      
#ifdef EE_RSCFD_RAMTEST_LASTPGENTRIES
     if( ( RAMPage_u16 == ( EE_RSCFD_RAMTEST_PAGES-1 ) ) &
         ( RAMElement_u16 > EE_RSCFD_RAMTEST_LASTPGENTRIES ) ) break;
#endif
     
     ee_rscfd_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] = 0x00000000;
     if( ee_rscfd_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] != 0x00000000 )
     {
      return( EE_RSCFD_ERROR );
     }
	}
  }
  
  // Write walking-1 to all RAM pages
  for( RAMPage_u16 = 0; RAMPage_u16 < EE_RSCFD_RAMTEST_PAGES; RAMPage_u16++ )
  {
	ee_rscfd_common_p[ UnitNumber_u08 ]->gtcfg.rtmps = RAMPage_u16;
	
    for( RAMElement_u16 = 0; RAMElement_u16 < EE_RSCFD_RAMTEST_ENTRIES; RAMElement_u16++ )
    {
      
#ifdef EE_RSCFD_RAMTEST_LASTPGENTRIES
     if( ( RAMPage_u16 == ( EE_RSCFD_RAMTEST_PAGES-1 ) ) &
         ( RAMElement_u16 > EE_RSCFD_RAMTEST_LASTPGENTRIES ) ) break;
#endif
     
    ee_rscfd_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] = RAMData_u32;
	  if( RAMData_u32 >= 0x80000000)
	  {
       RAMData_u32 = 0x00000001;
	  }
	  else
	  {
	   RAMData_u32 = RAMData_u32 * 2;
	  }
	}
  }

  
  // Checking Walking-1 through all pages
  for( RAMPage_u16 = 0; RAMPage_u16 < EE_RSCFD_RAMTEST_PAGES; RAMPage_u16++ )
  {
    ee_rscfd_common_p[ UnitNumber_u08 ]->gtcfg.rtmps = RAMPage_u16;
	
    for( RAMElement_u16 = 0; RAMElement_u16 < EE_RSCFD_RAMTEST_ENTRIES; RAMElement_u16++ )
    {
      
#ifdef EE_RSCFD_RAMTEST_LASTPGENTRIES
     if( ( RAMPage_u16 == ( EE_RSCFD_RAMTEST_PAGES-1 ) ) &
         ( RAMElement_u16 > EE_RSCFD_RAMTEST_LASTPGENTRIES ) ) break;
#endif
     
  	  if ( RAMPage_u16 == 0 && RAMElement_u16 == 0 )
  	  {
  	    RAMData_u32 = 0x00000001;
  	  }
  	  else if( RAMData_u32 >= 0x80000000)
  	  {
         RAMData_u32 = 0x00000001;
  	  }
  	  else
  	  {
  	   RAMData_u32 = RAMData_u32 * 2;
  	  }
	  
      if( ee_rscfd_ram_p[ UnitNumber_u08 ]->cell[ RAMElement_u16 ] != RAMData_u32 )
      {
       return( EE_RSCFD_ERROR );
      }
	  }
  }
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_IntCANBusActivate
// IN  :         Unit Number
// OUT :         Success Status
// Description : Activates internal CAN bus communication for testing
// 
//=============================================================================
bit EE_RSCFD_IntCANBusActivate( u08 UnitNumber_u08 )
{
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );
  if( ee_rscfd_common_p[ UnitNumber_u08 ]->gsts.mds != EE_RSCFD_OPMODE_HALT )
    return( EE_RSCFD_ERROR );
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->gtcfg.icbce = EE_RSCFD_COMTEST_ALLON;
  
  ee_rscfd_common_p[ UnitNumber_u08 ]->gtctr = EE_RSCFD_COMTEST_MODE;
  while( ee_rscfd_common_p[ UnitNumber_u08 ]->gtctr != EE_RSCFD_COMTEST_MODE );
  
  return( EE_RSCFD_OK );
}

//=============================================================================
// FunctionName: EE_RSCFD_GetFIFOStatus
// IN  :         Unit Number, Channel Number, FIFO Number, Status Type
// OUT :         Success Status, Status Value
// Description : Reads FIFO Status registers
// 
//=============================================================================

bit EE_RSCFD_GetFIFOStatus( u08  UnitNumber_u08,
                            u08  ChannelNumber_u08,
                            u08  FIFONumber_u08,
                            u08  StatusType_u08,
                            pu08 StatusValue_pu08 )
{
  if( UnitNumber_u08 >= EE_RSCFD_MACROS ) return( EE_RSCFD_ERROR );

  if( ChannelNumber_u08 == EE_RSCFD_GLOBAL )
  {
    switch( StatusType_u08 )
    {
      case EE_RSCFD_FIFO_STATUS_FULL:
        *StatusValue_pu08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->
                                       ffsts.rf >> FIFONumber_u08 ) & 0x01L );
        break;
        
      case EE_RSCFD_FIFO_STATUS_EMPTY:
        *StatusValue_pu08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->
                                       fests.rf >> FIFONumber_u08 ) & 0x01L );
        break;
        
      case EE_RSCFD_FIFO_STATUS_LOST:
        *StatusValue_pu08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->
                                       fmsts.rf >> FIFONumber_u08 ) & 0x01L );
        break;
    }
  }
  else
  {
    if( ChannelNumber_u08 >= ee_rscfd_channels[ UnitNumber_u08 ] ) 
      return( EE_RSCFD_ERROR );

    FIFONumber_u08 = EE_RSCFD_MAXCOMFIFOS * ChannelNumber_u08 + FIFONumber_u08;

    switch( StatusType_u08 )
    {
      case EE_RSCFD_FIFO_STATUS_FULL:
        *StatusValue_pu08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->
                                       ffsts.cf >> FIFONumber_u08 ) & 0x01L );
        break;
        
      case EE_RSCFD_FIFO_STATUS_EMPTY:
        *StatusValue_pu08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->
                                       fests.cf >> FIFONumber_u08 ) & 0x01L );
        break;
        
      case EE_RSCFD_FIFO_STATUS_LOST:
        *StatusValue_pu08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->
                                       fmsts.cf >> FIFONumber_u08 ) & 0x01L );
        break;
    }
  }
  return( EE_RSCFD_OK );
}



// End of file
