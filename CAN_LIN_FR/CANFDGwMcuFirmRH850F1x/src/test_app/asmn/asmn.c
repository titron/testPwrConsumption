/*===========================================================================*/
/* PROJECT = ASMN Test Monitor                                               */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2015 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG.Support                                                        */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: device_support.rl78-eu@lm.renesas.com                      */
/*        FAX:   +49 - (0)211 / 65 03 - 12 79                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/

#include <ree_types.h>
#include <ree_macros.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* MAP includes */
#include <map_device.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>
#include <map_asmn_basic.h>

#include "test_lin.h"

/* Direct start / concurrent app functionality hooks */
#ifdef ASMN_DIRECTSTART
extern void ASMN_DIRECTSTART( void );
#endif

/* ASMN Modules: Port Functions (always needed) */
#if( defined PORTS_TYPE )
#if( PORTS_TYPE == PORTS_STANDARD )
//#include <ports\standardports\standardports_p.h>
#include <standardports_p.h>
#else
#error "ASMN: Unknown Interface Defined"
#endif
#else
#error "ASMN: No Port Interface Defined"
#endif


/* ASMN Modules: Interrupt Functions */
#if( defined INTC_MACROS )
#include <map_intc.h>
#endif

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#if( defined UARTA_MACROS )
#include <map_uarta.h>
#else
#error "ASMN: UARTA Communication Interface Missing"
#endif

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#if( defined UARTC_MACROS )
#include <map_uartc.h>
#else
#error "ASMN: UARTC Communication Interface Missing"
#endif

#elif( ASMN_UARTINTERFACE == UARTD_STANDARD )
#if( defined UARTD_MACROS )
#include <map_uartd.h>
#else
#error "ASMN: UARTD Communication Interface Missing"
#endif

#elif( ASMN_UARTINTERFACE == UARTE_STANDARD )
#if( defined UARTE_MACROS )
#include <map_uarte.h>
#else
#error "ASMN: UARTE Communication Interface Missing"
#endif

#elif( ASMN_UARTINTERFACE == UARTF_STANDARD )
#if( defined UARTF_MACROS )
#include <map_uartf.h>
#else
#error "ASMN: UARTF Communication Interface Missing"
#endif

#elif( ASMN_UARTINTERFACE == RLIN3_STANDARD )
#if( defined RLIN3_MACROS )
#include <map_rlin3.h>
#else
#error "ASMN: RLIN3 Communication Interface Missing"
#endif

#elif( ASMN_UARTINTERFACE == DEBUG_INTERNAL )


#else
#error "ASMN: No Communication Interface Defined"
#endif

/* ASMN Modules: SML Primitive Test Access */

#include "asmn_ports_p_asmnif.h"

#ifdef   ADC_MACROS
#include "asmn_adc_p_asmnif.h"
#endif
#ifdef   BRG_MACROS
#include "asmn_brg_p_asmnif.h"
#endif
#ifdef   MEMC_MACROS
#include "asmn_memc_p_asmnif.h"
#endif
#ifdef   DMAC_MACROS
#include "asmn_dmac_p_asmnif.h"
#endif
#ifdef   DCAN_MACROS
#include "asmn_dcan_p_asmnif.h"
#endif
#ifdef   INTC_MACROS
#include "asmn_intc_p_asmnif.h"
#endif
#ifdef   TMC_MACROS
#include "asmn_timer_cp_asmnif.h"
#endif
#ifdef   TMD_MACROS
#include "asmn_timer_dp_asmnif.h"
#endif
#ifdef   TME_MACROS
#include "asmn_timer_ep_asmnif.h"
#endif
#ifdef   TMG_MACROS
#include "asmn_timer_gp_asmnif.h"
#endif
#ifdef   TMP_MACROS
#include "asmn_timerp_p_asmnif.h"
#endif
#ifdef   TMY_MACROS
#include "asmn_timery_p_asmnif.h"
#endif
#ifdef   TMZ_MACROS
#include "asmn_timerz_p_asmnif.h"
#endif
#ifdef   TM0_MACROS
#include "asmn_timer0_p_asmnif.h"
#endif
#ifdef   WTM_MACROS
#include "asmn_watch_p_asmnif.h"
#endif
#ifdef   WDT_MACROS
#include "asmn_watchdog_p_asmnif.h"
#endif
#ifdef   EE_ISM_MACROS
#include "asmn_ism_p_asmnif.h"
#endif
#ifdef   UARTA_MACROS
#include "asmn_uarta_p_asmnif.h"
#endif
#ifdef   UARTC_MACROS
#include "asmn_uartc_p_asmnif.h"
#endif
#ifdef   CSI_MACROS
#include "asmn_csi_p_asmnif.h"
#endif

/* ASMN Modules: SML Application Test Access */

#ifdef   EE_RSCAN_MACROS
#include "asmn_rscan_a_asmnif.h"
#endif
#ifdef   EE_RSCFD_MACROS
#include "asmn_rscfd_a_asmnif.h"
#endif
#ifdef   MCAN_MACROS
#include "asmn_mcan_a_asmnif.h"
#endif
#ifdef   MTTCAN_MACROS
#include "asmn_mttcan_a_asmnif.h"
#endif
#ifdef   EE_AFCAN_MACROS
#include "asmn_afcan_a_asmnif.h"
#endif
#ifdef   AFCAN_MACROS
#include "asmn_afcan_a_asmnif.h"
#endif
#ifdef   FVAN_MACROS
#include "asmn_fvan_a_asmnif.h"
#endif
#ifdef   SWC_MACROS
#include "asmn_swc_a_asmnif.h"
#endif
#ifdef   TMC_MACROS
#include "asmn_timer_ca_asmnif.h"
#endif
#ifdef   TME_MACROS
#include "asmn_timer_ea_asmnif.h"
#endif
#ifdef   TMG_MACROS
#include "asmn_timer_ga_asmnif.h"
#endif
#ifdef   TMP_MACROS
#include "asmn_timerp_a_asmnif.h"
#endif
#ifdef   TMY_MACROS
#include "asmn_timery_a_asmnif.h"
#endif
#ifdef   TMZ_MACROS
#include "asmn_timerz_a_asmnif.h"
#endif
#ifdef   EE_ISM_MACROS
#include "asmn_ism_a_asmnif.h"
#endif
#ifdef   UARTA_MACROS
#include "asmn_uarta_a_asmnif.h"
#endif
#ifdef   UARTC_MACROS
#include "asmn_uartc_a_asmnif.h"
#endif
#ifdef   UARTF_MACROS
#include "asmn_uartf_a_asmnif.h"
#endif
#ifdef   RLIN3_MACROS
#include "asmn_rlin3_a_asmnif.h"
#endif
#ifdef   RLIN2_MACROS
#include "asmn_rlin2_a_asmnif.h"
#endif
#ifdef   FR_MACROS
#include "asmn_fr_a_asmnif.h"
#endif
#ifdef   ETH_MACROS
#include "asmn_eth_a_asmnif.h"
#endif
#ifdef RIIC_MACROS
#include "riic_application.h"
#endif

/* SDST includes */
#ifdef   SDST_EMIEMS
#include <sdst\emi_ems\sdst_emi_p.h>
#endif

/* ATIF includes */
#ifdef   ATIF_INJCUR
#include <atif\injcur\atif_injcur_asmnif.h>
#endif
#ifdef   ATIF_POWER
#include <atif\power\atif_power.h>
#include <atif\power\atif_power_p.h>
#include <atif\power\atif_power_asmnif.h>
#endif
#ifdef   ATIF_BUSIF
#include <atif\busif\atif_busif.h>
#include <atif\busif\atif_busif_p.h>
#include <atif\busif\atif_busif_p_asmnif.h>
#endif

/* STFN includes */
#ifdef   STFN_SELFTEST
#include <stfn\stfn.h>
#include <stfn\stfn_p.h>
#include <map_stfn.h>
#endif

/* Global Settings */

#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0
#define ASMN_MENUCODE_COM   1
#define ASMN_MENUCODE_PORTS 2
#ifdef  ADC_MACROS
#define ASMN_MENUCODE_ADP   3
#endif
#ifdef  ATIF_INJCUR
#define ASMN_MENUCODE_ADA   4
#endif
#ifdef  BRG_MACROS
#define ASMN_MENUCODE_BRGP  5
#endif
#ifdef  TMC_MACROS
#define ASMN_MENUCODE_TMCP  6
#define ASMN_MENUCODE_TMCA  7
#endif
#ifdef  TMD_MACROS
#define ASMN_MENUCODE_TMD   8
#endif
#ifdef  TME_MACROS
#define ASMN_MENUCODE_TMEP  9
#define ASMN_MENUCODE_TMEA  10 
#endif
#ifdef  TMG_MACROS
#define ASMN_MENUCODE_TMGP  11
#define ASMN_MENUCODE_TMGA  12
#endif
#ifdef  TMP_MACROS
#define ASMN_MENUCODE_TMPP  13
#define ASMN_MENUCODE_TMPA  14
#endif
#ifdef  TMY_MACROS
#define ASMN_MENUCODE_TMYP  15
#define ASMN_MENUCODE_TMYA  16
#endif
#ifdef  TMZ_MACROS
#define ASMN_MENUCODE_TMZP  17
#define ASMN_MENUCODE_TMZA  18
#endif
#ifdef  TM0_MACROS
#define ASMN_MENUCODE_TM0P  19
#endif
#ifdef  WTM_MACROS
#define ASMN_MENUCODE_WTM   20
#endif
#ifdef  WDT_MACROS
#define ASMN_MENUCODE_WDT   21
#endif
#ifdef  DCAN_MACROS
#define ASMN_MENUCODE_DCANP 22
#endif
#ifdef  FCAN_MACROS
#define ASMN_MENUCODE_FCANA 23
#endif
#ifdef  AFCAN_MACROS
#define ASMN_MENUCODE_AFCANA 24
#endif
#ifdef  EE_AFCAN_MACROS
#define ASMN_MENUCODE_AFCANA 25
#endif
#ifdef  FVAN_MACROS
#define ASMN_MENUCODE_FVANA 26
#endif
#ifdef  EE_RSCAN_MACROS
#define ASMN_MENUCODE_RSCANA 27
#endif
#ifdef  EE_RSCFD_MACROS
#define ASMN_MENUCODE_RSCFDA 28
#endif
#ifdef  MCAN_MACROS
#define ASMN_MENUCODE_MCANA 29
#endif
#ifdef  MTTCAN_MACROS
#define ASMN_MENUCODE_MTTCANA 30
#endif
#ifdef  UARTA_MACROS
#define ASMN_MENUCODE_UARTAP 31
#define ASMN_MENUCODE_UARTAA 32
#endif
#ifdef  UARTC_MACROS
#define ASMN_MENUCODE_UARTCP 33
#define ASMN_MENUCODE_UARTCA 34
#endif
#ifdef  UARTF_MACROS
#define ASMN_MENUCODE_UARTFA 35
#endif
#ifdef  CSI_MACROS
#define ASMN_MENUCODE_CSIP   36
#endif
#ifdef  INTC_MACROS
#define ASMN_MENUCODE_INTC   37
#endif
#ifdef  DMAC_MACROS
#define ASMN_MENUCODE_DMACP  38
#endif
#ifdef  SWC_MACROS
#define ASMN_MENUCODE_SWC  39
#endif
#ifdef  ATIF_BUSIF
#define ASMN_MENUCODE_BUSIF  40
#endif
#ifdef  ATIF_POWER
#define ASMN_MENUCODE_PWR   41
#endif
#ifdef  EE_ISM_MACROS
#define ASMN_MENUCODE_ISM    42
#define ASMN_MENUCODE_ISMA   43
#endif
#ifdef  RLIN3_MACROS
#define ASMN_MENUCODE_RLIN3  44
#endif
#ifdef  RLIN2_MACROS
#define ASMN_MENUCODE_RLIN2  45
#endif
#ifdef  FR_MACROS
#define ASMN_MENUCODE_FR    46
#endif
#ifdef  ETH_MACROS
#define ASMN_MENUCODE_ETH   47
#endif
#ifdef  STFN_SELFTEST
#define ASMN_MENUCODE_SELF  99
#endif

#define ASMN_MENULINE_HDR1    "ASMN APPLICATION TEST MONITOR\n"
#define ASMN_MENULINE_HDR2    "     (C) RL 01/2001            \n\n"
#define ASMN_MENULINE_MEN0    "0 -> Exit\n"
#define ASMN_MENULINE_MEN1    "1 -> Change COM Port Number\n"
#define ASMN_MENULINE_MEN2    "2 -> Ports Low Level Access\n"
#ifdef  ADC_MACROS
#define ASMN_MENULINE_MEN3    "3 -> A/D Converter Low Level Access\n"
#endif
#ifdef  ATIF_INJCUR
#define ASMN_MENULINE_MEN4    "4 -> A/D Converter Applications\n"
#endif
#ifdef  BRG_MACROS
#define ASMN_MENULINE_MEN5    "5 -> Baud Rate Generator Low Level Access\n"
#endif
#ifdef  TMC_MACROS
#define ASMN_MENULINE_MEN6    "6 -> Timer C Low Level Access\n"
#define ASMN_MENULINE_MEN7    "7 -> Timer C Applications\n"
#endif
#ifdef  TMD_MACROS
#define ASMN_MENULINE_MEN8    "8 -> Timer D\n"
#endif
#ifdef  TME_MACROS
#define ASMN_MENULINE_MEN9    "9 -> Timer E Low Level Access\n"
#define ASMN_MENULINE_MEN10   "10-> Timer E Applications\n"
#endif
#ifdef  TMG_MACROS
#define ASMN_MENULINE_MEN11   "11-> Timer G Low Level Access\n"
#define ASMN_MENULINE_MEN12   "12-> Timer G Applications\n"
#endif
#ifdef  TMP_MACROS
#define ASMN_MENULINE_MEN13   "13-> Timer P Low Level Access\n"
#define ASMN_MENULINE_MEN14   "14-> Timer P Applications\n"
#endif
#ifdef  TMY_MACROS
#define ASMN_MENULINE_MEN15   "15-> Timer Y Low Level Access\n"
#define ASMN_MENULINE_MEN16   "16-> Timer Y Applications\n"
#endif
#ifdef  TMZ_MACROS
#define ASMN_MENULINE_MEN17   "17-> Timer Z Low Level Access\n"
#define ASMN_MENULINE_MEN18   "18-> Timer Z Applications\n"
#endif
#ifdef  TM0_MACROS
#define ASMN_MENULINE_MEN19   "19-> Timer 0 Low Level Access\n"
#endif
#ifdef  WTM_MACROS
#define ASMN_MENULINE_MEN20   "20-> Watch Timer Low Level Access\n"
#endif
#ifdef  WDT_MACROS
#define ASMN_MENULINE_MEN21   "21-> WatchDog Timer Low Level Access\n"
#endif
#ifdef  DCAN_MACROS
#define ASMN_MENULINE_MEN22   "22-> DCAN Low Level Access\n"
#endif
#ifdef  FCAN_MACROS
#define ASMN_MENULINE_MEN23   "23-> FCAN Applications\n"
#endif
#ifdef  AFCAN_MACROS
#define ASMN_MENULINE_MEN24   "24-> AFCAN Applications\n"
#endif
#ifdef  EE_AFCAN_MACROS
#define ASMN_MENULINE_MEN25   "25-> AFCAN Applications\n"
#endif
#ifdef  FVAN_MACROS
#define ASMN_MENULINE_MEN26   "26-> FVAN Applications\n"
#endif
#ifdef  EE_RSCAN_MACROS
#define ASMN_MENULINE_MEN27   "27-> RSCAN Applications\n"
#endif
#ifdef  EE_RSCFD_MACROS
#define ASMN_MENULINE_MEN28   "28-> RSCAN-FD Applications\n"
#endif
#ifdef  MCAN_MACROS
#define ASMN_MENULINE_MEN29   "29-> MCAN Applications\n"
#endif
#ifdef  MTTCAN_MACROS
#define ASMN_MENULINE_MEN30   "30-> MTTCAN Applications\n"
#endif
#ifdef  UARTA_MACROS
#define ASMN_MENULINE_MEN31   "31-> UART A Low Level Access\n"
#define ASMN_MENULINE_MEN32   "32-> UART A Applications\n"
#endif
#ifdef  UARTC_MACROS
#define ASMN_MENULINE_MEN33   "33-> UART C Low Level Access\n"
#define ASMN_MENULINE_MEN34   "34-> UART C Applications\n"
#endif
#ifdef  UARTF_MACROS
#define ASMN_MENULINE_MEN35   "35-> UART F Applications\n"
#endif
#ifdef  CSI_MACROS
#define ASMN_MENULINE_MEN36   "36-> CSI Low Level Access\n"
#endif
#ifdef  INTC_MACROS
#define ASMN_MENULINE_MEN37   "37-> NMI / External Interrupts\n"
#endif
#ifdef  DMAC_MACROS
#define ASMN_MENULINE_MEN38   "38-> DMA Low Level Access\n"
#endif
#ifdef  SWC_MACROS
#define ASMN_MENULINE_MEN39   "39-> SWC Applications\n"
#endif
#ifdef  ATIF_BUSIF
#define ASMN_MENULINE_MEN40   "40-> Bus Interface\n"
#endif
#ifdef  ATIF_POWER
#define ASMN_MENULINE_MEN41   "41-> Power Saving\n"
#endif
#ifdef  EE_ISM_MACROS
#define ASMN_MENULINE_MEN42   "42-> ISM Low Level Access\n"
#define ASMN_MENULINE_MEN43   "43-> ISM Applications\n"
#endif
#ifdef  RLIN3_MACROS
#define ASMN_MENULINE_MEN44   "44-> RLIN3 Applications\n"
#endif
#ifdef  RLIN2_MACROS
#define ASMN_MENULINE_MEN45   "45-> RLIN2 Applications\n"
#endif
#ifdef  FR_MACROS
#define ASMN_MENULINE_MEN46   "46-> FR Applications\n"
#endif
#ifdef  ETH_MACROS
#define ASMN_MENULINE_MEN47   "47-> ETH Applications\n"
#endif
#ifdef  STFN_SELFTEST
#define ASMN_MENULINE_MEN99   "99-> SelfTest\n"
#endif

#define ASMN_MENULINE_CMD1    "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD   "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_GOODBYE "\n\nTHANK YOU - GOODBYE!\n\n"
#define ASMN_MENULINE_OK      "\nOK.\n"
#define ASMN_MENULINE_FAIL    "\nFAILED!!\n"
#define ASMN_MENULINE_IERR    "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_COM    "\nEnter COM Unit Number: [0...] "
#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

/* UART Replacement Functions for Monitor */

#define ASMN_A_TTYMODE_CR   0 /* application level constants */
#define ASMN_A_TTYMODE_CRLF 1
#define ASMN_A_HEXMODE      1
#define ASMN_A_DECMODE      0
#define ASMN_A_RECBUFLEN    80

bit ASMN_SendString( u08   UnitNumber_u08,
                     char *SendString,
                     u08   TTYMode_u08 )
{
  printf( SendString );
#ifdef ASMN_UARTMODEFORCELF
  if( SendString[ strlen( SendString ) - 1 ] != '\n' )
    printf( "\n" );
#endif
  return( ASMN_UARTTRANSFEROK );
}

bit ASMN_SendByte( u08 UnitNumber_u08,
                   u08 SendByte_u08 )
{
  putchar( SendByte_u08 );
  return( ASMN_UARTTRANSFEROK );
}

bit ASMN_ReceiveByte( u08  UnitNumber_u08,
                      pu08 ReceiveByte_pu08 )
{
  *ReceiveByte_pu08 = getchar( );
  return( ASMN_UARTTRANSFEROK );
}

bit ASMN_ReceiveString( u08   UnitNumber_u08,
                        char *ReceiveString,
                        u16   ReceiveLength_u16,
                        u32   TimeOutCount_u32 )
{
  bit ReceiveStatus_bit;
  u16 ActualReceived_u16 = 0;
  
  do {

    ReceiveStatus_bit = ASMN_ReceiveByte( UnitNumber_u08,
                                        ( pu08 )( &ReceiveString[ ActualReceived_u16 ] ) );

    if( ReceiveStatus_bit == ASMN_UARTTRANSFEROK ) {
      ActualReceived_u16++;
    }
  } while( ( ActualReceived_u16 < ReceiveLength_u16 ) &&
           ( ReceiveStatus_bit == ASMN_UARTTRANSFEROK ) );
  
  if( ActualReceived_u16 == ReceiveLength_u16 ) return( ASMN_UARTTRANSFEROK );
  else
  {
    return( ASMN_UARTERROR );
  }
}

bit ASMN_ReceiveInteger( u08    UnitNumber_u08,
                         u16    ReceiveLength_u16,
                         char  *RequestString,
                         int   *Result,
                         pu08   ScanState_pu08 )
{
  bit  UARTStatus_bit;
  bit  ReceiveStatus_bit;
  u08  ReceiveMode_u08    = ASMN_A_DECMODE;
  s16  ActualReceived_s16 = 0;
  char InputBuffer[ ASMN_A_RECBUFLEN ];
  char ActualDisplayBuffer[ 20 ];

  if( ReceiveLength_u16 >= ASMN_A_RECBUFLEN ) return( ASMN_UARTERROR );

  UARTStatus_bit = ASMN_SendString( UnitNumber_u08, RequestString,
                                    ASMN_UARTMODECRLF );
  if( UARTStatus_bit != ASMN_UARTTRANSFEROK ) return( UARTStatus_bit );

  if( *Result >= 0 ) {

    sprintf( ActualDisplayBuffer, "(%d [%XH]) ", *Result, *Result );
    UARTStatus_bit = ASMN_SendString( UnitNumber_u08, ActualDisplayBuffer,
                                      ASMN_A_TTYMODE_CR );
    if( UARTStatus_bit != ASMN_UARTTRANSFEROK ) return( UARTStatus_bit );
  }

  do {

    ReceiveStatus_bit = ASMN_ReceiveByte( UnitNumber_u08,
                                          ( pu08 )( &InputBuffer[ ActualReceived_s16 ] ) );

    if( ReceiveStatus_bit == ASMN_UARTTRANSFEROK ) {

      ASMN_SendByte( UnitNumber_u08, ( u08 )InputBuffer[ ActualReceived_s16 ] );

      if( ( InputBuffer[ ActualReceived_s16 ] == 'H' ) || 
          ( InputBuffer[ ActualReceived_s16 ] == 'h' ) ) {
        ReceiveMode_u08 = ASMN_A_HEXMODE;
      }
      else {
        ActualReceived_s16++;
        if( InputBuffer[ ActualReceived_s16 - 1 ] < ' ' ) {
          if( InputBuffer[ ActualReceived_s16 - 1 ] == 0x08 ) {
            InputBuffer[ ActualReceived_s16 - 1 ] = 0x00;
            ActualReceived_s16 -= 2;
            if( ActualReceived_s16 < 0 ) ActualReceived_s16 = 0;
          }
          continue;
        }
      }
    }
  } while( ( ActualReceived_s16 < ReceiveLength_u16 ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0D ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0A ) );

  if( ActualReceived_s16 > 1 ) {
    
    InputBuffer[ ActualReceived_s16 ] = 0;
    
    switch( ReceiveMode_u08 ) {
      
    case ASMN_A_DECMODE:
      *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%d", Result );
      break;

    case ASMN_A_HEXMODE:
      *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%x", Result );
      break;

    default:
      return( ASMN_UARTERROR );
    }
  }
  return( UARTStatus_bit );
}

bit ASMN_ReceiveULong( u08            UnitNumber_u08,
                        u16            ReceiveLength_u16,
                        char          *RequestString,
                        unsigned long *Result,
                        pu08           ScanState_pu08 )
{
  bit  UARTStatus_bit;
  bit  ReceiveStatus_bit;
  u08  ReceiveMode_u08    = ASMN_A_DECMODE;
  s16  ActualReceived_s16 = 0;
  char InputBuffer[ ASMN_A_RECBUFLEN ];
  char ActualDisplayBuffer[ 20 ];

  if( ReceiveLength_u16 >= ASMN_A_RECBUFLEN ) return( ASMN_UARTERROR );

  UARTStatus_bit = ASMN_SendString( UnitNumber_u08, RequestString,
                                    ASMN_A_TTYMODE_CR );
  if( UARTStatus_bit != ASMN_UARTTRANSFEROK ) return( UARTStatus_bit );

  sprintf( ActualDisplayBuffer, "(%ld [%lXH]) ", *Result, *Result );
  UARTStatus_bit = ASMN_SendString( UnitNumber_u08, ActualDisplayBuffer,
                                     ASMN_A_TTYMODE_CR );
  if( UARTStatus_bit != ASMN_UARTTRANSFEROK ) return( UARTStatus_bit );

  do {

    ReceiveStatus_bit = ASMN_ReceiveByte( UnitNumber_u08,
                                           ( pu08 )( &InputBuffer[ ActualReceived_s16 ] ) );

    if( ReceiveStatus_bit == ASMN_UARTTRANSFEROK ) {

      ASMN_SendByte( UnitNumber_u08, ( u08 )InputBuffer[ ActualReceived_s16 ] );

      if( ( InputBuffer[ ActualReceived_s16 ] == 'H' ) || 
          ( InputBuffer[ ActualReceived_s16 ] == 'h' ) ) {
        ReceiveMode_u08 = ASMN_A_HEXMODE;
      }
      else {
        ActualReceived_s16++;
        if( InputBuffer[ ActualReceived_s16 - 1 ] < ' ' ) {
          if( InputBuffer[ ActualReceived_s16 - 1 ] == 0x08 ) {
            InputBuffer[ ActualReceived_s16 - 1 ] = 0x00;
            ActualReceived_s16 -= 2;
            if( ActualReceived_s16 < 0 ) ActualReceived_s16 = 0;
          }
          continue;
        }
      }
    }
  } while( ( ActualReceived_s16 < ReceiveLength_u16 ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0D ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0A ) );

  if( ActualReceived_s16 > 1 ) {
    
    InputBuffer[ ActualReceived_s16 ] = 0;
    
    switch( ReceiveMode_u08 ) {
      
    case ASMN_A_DECMODE:
      *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%ld", Result );
      break;

    case ASMN_A_HEXMODE:
      *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%lx", Result );
      break;

    default:
      return( ASMN_UARTERROR );
    }
  }
  return( UARTStatus_bit );
}

bit ASMN_ReceiveFloat( u08    UnitNumber_u08,
                       u16    ReceiveLength_u16,
                       char  *RequestString,
                       float *Result,
                       pu08   ScanState_pu08 )
{
  bit  UARTStatus_bit;
  bit  ReceiveStatus_bit;
  s16  ActualReceived_s16 = 0;
  char InputBuffer[ ASMN_A_RECBUFLEN ];

  if( ReceiveLength_u16 >= ASMN_A_RECBUFLEN ) return( ASMN_UARTERROR );

  UARTStatus_bit = ASMN_SendString( UnitNumber_u08, RequestString,
                                    ASMN_A_TTYMODE_CR );
  if( UARTStatus_bit != ASMN_UARTTRANSFEROK ) return( UARTStatus_bit );

  do {

    ReceiveStatus_bit = ASMN_ReceiveByte( UnitNumber_u08,
                                          ( pu08 )( &InputBuffer[ ActualReceived_s16 ] ) );

    if( ReceiveStatus_bit == ASMN_UARTTRANSFEROK ) {

      ASMN_SendByte( UnitNumber_u08, ( u08 )InputBuffer[ ActualReceived_s16 ] );
      ActualReceived_s16++;

      if( InputBuffer[ ActualReceived_s16 - 1 ] < ' ' ) {
        if( InputBuffer[ ActualReceived_s16 - 1 ] == 0x08 ) {
          InputBuffer[ ActualReceived_s16 - 1 ] = 0x00;
          ActualReceived_s16 -= 2;
          if( ActualReceived_s16 < 0 ) ActualReceived_s16 = 0;
        }
        continue;
      }
    }
  } while( ( ActualReceived_s16 < ReceiveLength_u16) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0D ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0A ) );
  
  *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%f", Result );

  return( UARTStatus_bit );
}

/* Dummy Interrupt function for Communication Interface (UART) */

static void ASMN_COMInterrupt( void )
{
}

static unsigned char                /* local submenu: invisible from outside */
DisplayMenu( u08  ComPortUnit_u08,
            char *MenuCommand )
{
  unsigned char UARTStatus;
  u08           UserInput    = 0;
  unsigned int  DigitCounter = 0;
  int           DigitValue;        
  char          InputString[ ASMN_MENUCOM_BUFLEN ];

  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_HDR1, 
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_HDR2,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN0,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#ifdef ASMN_MENULINE_MEN1
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN1,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN2
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN2,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN3
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN3,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN4
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN4,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN5
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN5,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN6
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN6,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN7
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN7,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN8
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN8,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN9
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN9,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN10
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN10,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN11
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN11,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN12
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN12,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN13
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN13,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN14
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN14,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN15
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN15,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN16
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN16,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN17
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN17,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN18
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN18,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN19
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN19,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN20
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN20,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN21
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN21,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN22
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN22,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN23
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN23,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN24
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN24,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN25
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN25,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN26
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN26,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN27
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN27,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN28
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN28,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN29
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN29,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN30
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN30,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN31
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN31,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN32
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN32,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN33
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN33,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN34
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN34,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN35
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN35,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN36
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN36,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN37
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN37,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN38
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN38,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN39
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN39,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN40
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN40,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN41
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN41,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN42
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN42,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN43
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN43,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN44
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN44,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN45
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN45,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN46
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN46,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN47
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN47,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN99
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_MEN99,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
  UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_CMD1,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );

  while( DigitCounter < ( ASMN_MENUCOM_BUFLEN-1 ) ) {

    do {  /* wait for one char to be received */
      
      UARTStatus = ASMN_UARTRECEIVEBYTE( ComPortUnit_u08, &UserInput );
      
    } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
    UARTStatus = ASMN_UARTSENDBYTE( ComPortUnit_u08, UserInput ); /* echo */
    
    if( ( UserInput == ASMN_MENUCOM_EXE1 ) || 
      	( UserInput == ASMN_MENUCOM_EXE2 ) ) { /* the "return" */
      
      InputString[ DigitCounter ] = 0;       /* close string */
      if( DigitCounter > 0 )
      {
        sscanf( InputString, "%d", &DigitValue );
        *MenuCommand = ( unsigned char )DigitValue;
      }
      else
      {
        *MenuCommand = -1;
      }
      return( UARTStatus );
    }
    else {  /* store digit */
      
      if( ( UserInput >= '0' ) && ( UserInput <= '9' ) ) {
      	  InputString[ DigitCounter++ ] = UserInput;
      }
      else if( UserInput == 0x08 ) {
        	if( DigitCounter > 0 ) DigitCounter--;
      }
    }
  }

  *MenuCommand = -1;
  return( UARTStatus );
}

#ifdef  STFN_SELFTEST

unsigned char
ASMN_SelfTest( u08 MenuCom )
{
    unsigned char UARTStatus;
    unsigned char SuccessFlag  = STFN_SELFTEST_OK;
    int           TestCom      = STFN_SELFTEST_TESTCOM;
    unsigned long TestBaudrate = STFN_SELFTEST_TESTCOM_BAUD;

#if( !STFN_SELFTEST_ONECOM )

    unsigned char ScanState;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                        		      ASMN_MENUINPUT_TIMERUNIT,
                    			      &TestCom,
				                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SELFTEST_ERROR;

    UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                       ASMN_MENUINPUT_TICKPERIOD,
                                       &TestBaudRate,
                                       &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SELFTEST_ERROR;

#endif

    if( SuccessFlag == STFN_SELFTEST_OK )
    {
        SuccessFlag = STFN_SelfTest( MenuCom, TestCom, TestBaudrate );
    }
    else 
    {
        UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
	                    		      ASMN_UARTMODECRLF );
        if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }

    if( SuccessFlag == STFN_SELFTEST_OK ) {
        UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_OK,
	                    		      ASMN_UARTMODECRLF );
        if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    else 
    {
        UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
	                       		      ASMN_UARTMODECRLF );
        if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }

    return( UARTStatus );
}

#endif

unsigned char
ASMN_SetNewCom( pu08 MenuCom_pu08 )
{
    unsigned char UARTStatus;
    unsigned char SuccessFlag  = ASMN_UARTTRANSFEROK;
    int           NewComUnit   = ( int )( *MenuCom_pu08 );
    unsigned char ScanState;

    UARTStatus = ASMN_UARTRECEIVEINT( *MenuCom_pu08, ASMN_MENUINPUT_BUFLEN,
                        		          ASMN_MENUINPUT_COM,
                    			           &NewComUnit,
				                             &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUINPUT_SCANOK ) SuccessFlag = ASMN_UARTERROR;


    if( SuccessFlag == ASMN_UARTTRANSFEROK )
    {
        UARTStatus = ASMN_UARTSENDSTRING( *MenuCom_pu08, ASMN_MENULINE_OK,
	                    		                ASMN_UARTMODECRLF );
        if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
        *MenuCom_pu08 = ( u08 )NewComUnit;
    }
    else 
    {
        UARTStatus = ASMN_UARTSENDSTRING( *MenuCom_pu08, ASMN_MENULINE_IERR,
	                    		                ASMN_UARTMODECRLF );
        if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }

    return( UARTStatus );
}
#define TEST_RSCFD_RLIN_FR
#define TEST_RSCFD
//#define TEST_RLIN3
//#define TEST_RLIN2
#define TEST_FR
//#define TEST_RIIC

int main_loop(void)
{
#if 0
  unsigned char UARTStatus;
  char          MenuCommand        = ASMN_MENUCODE_NOCMD;
  u08           ComPortUnit_u08    = ASMN_MENUCOM;
  u08           NewComPortUnit_u08 = ASMN_MENUCOM;

#ifdef INTC_MACROS
  INTC_EnableInterrupts( );
#else
  ASMN_EICOMMAND;
#endif

#ifdef ASMN_DIRECTSTART
  ASMN_DIRECTSTART( );
#endif

#ifdef ATIF_POWER
  ATIF_Pwrtest_Entry( );
#endif
#ifdef SDST_EMIEMS
  SDST_EMI_Entry( );
#endif

#ifdef OSC_PORT
  if( PORT_Oscillator_Switch_Setup( OSC_PORT ) != PORT_OK )
    {
      exit( 0 );
    }  
#endif

#if( ASMN_UARTINTERFACE == DEBUG_INTERNAL )

  UARTStatus  = ASMN_UARTTRANSFEROK;

#else

  UARTStatus  = ASMN_UARTRESET( ComPortUnit_u08 );
  UARTStatus *= ASMN_UARTPORTENABLE( ComPortUnit_u08 );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) {
    ASMN_UARTPORTDISABLE( ComPortUnit_u08 );
    exit( 0 );
  }
  UARTStatus = ASMN_UARTCONFIG( ComPortUnit_u08,
                                OSCILLATOR_FREQUENCY,
                                ASMN_MENUCOM_BAUD,
                                ASMN_MENUCOM_PARITY,
                                ASMN_MENUCOM_CHLEN,
                                ASMN_MENUCOM_STOP,
                                ASMN_MENUCOM_DIR );
                   
  UARTStatus *= ASMN_UARTCREATEINT( ComPortUnit_u08,
                                    ASMN_UARTIRQTX,
                                    ASMN_UARTIRQLEV,
                                    ASMN_COMInterrupt );

  UARTStatus *= ASMN_UARTCREATEINT( ComPortUnit_u08,
                                    ASMN_UARTIRQRX,
                                    ASMN_UARTIRQLEV,
                                    ASMN_COMInterrupt );

  if( UARTStatus != ASMN_UARTTRANSFEROK ) {
    ASMN_UARTRESET( ComPortUnit_u08 );
    ASMN_UARTPORTDISABLE( ComPortUnit_u08 );
    exit( 0 );
  }
  
#endif

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
         ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( ComPortUnit_u08, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;
      
    case ASMN_MENUCODE_COM:
#if( ASMN_UARTINTERFACE != DEBUG_INTERNAL )
      UARTStatus = ASMN_SetNewCom( &NewComPortUnit_u08 );
      if( ( NewComPortUnit_u08 != ComPortUnit_u08 ) &&
          ( UARTStatus == ASMN_UARTTRANSFEROK ) )
      {
        ASMN_UARTRESET( ComPortUnit_u08 );
        ASMN_UARTPORTDISABLE( ComPortUnit_u08 );
        ComPortUnit_u08 = NewComPortUnit_u08;
        ASMN_UARTRESET( ComPortUnit_u08 );
        UARTStatus = ASMN_UARTPORTENABLE( ComPortUnit_u08 );
        UARTStatus *= ASMN_UARTCONFIG( ComPortUnit_u08,
                                       OSCILLATOR_FREQUENCY,
                                       ASMN_MENUCOM_BAUD,
                                       ASMN_MENUCOM_PARITY,
                                       ASMN_MENUCOM_CHLEN,
                                       ASMN_MENUCOM_STOP,
                                       ASMN_MENUCOM_DIR );
                         
        UARTStatus *= ASMN_UARTCREATEINT( ComPortUnit_u08,
                                          ASMN_UARTIRQTX,
                                          ASMN_UARTIRQLEV,
                                          ASMN_COMInterrupt );
      
        UARTStatus *= ASMN_UARTCREATEINT( ComPortUnit_u08,
                                          ASMN_UARTIRQRX,
                                          ASMN_UARTIRQLEV,
                                          ASMN_COMInterrupt );
      }
#endif
      break;

#ifdef ASMN_MENUCODE_PORTS
    case ASMN_MENUCODE_PORTS:
      UARTStatus = ASMN_PORTFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_ADP
    case ASMN_MENUCODE_ADP:
      UARTStatus = ASMN_ADConverterFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_ADA
    case ASMN_MENUCODE_ADA:
      UARTStatus  = ATIF_ADConverterApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_BRGP
    case ASMN_MENUCODE_BRGP:
      UARTStatus = ASMN_BRGFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMCP
    case ASMN_MENUCODE_TMCP:
      UARTStatus = ASMN_TimerCFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMCA
    case ASMN_MENUCODE_TMCA:
      UARTStatus = ASMN_TimerCApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMD
    case ASMN_MENUCODE_TMD:
      UARTStatus = ASMN_TimerDFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMEP
    case ASMN_MENUCODE_TMEP:
      UARTStatus = ASMN_TimerEFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMEA
    case ASMN_MENUCODE_TMEA:
      UARTStatus = ASMN_TimerEApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMGP
    case ASMN_MENUCODE_TMGP:
      UARTStatus = ASMN_TimerGFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMGA
    case ASMN_MENUCODE_TMGA:
      UARTStatus = ASMN_TimerGApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMPP
    case ASMN_MENUCODE_TMPP:
      UARTStatus = ASMN_TimerPFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMPA
    case ASMN_MENUCODE_TMPA:
      UARTStatus = ASMN_TimerPApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMYP
    case ASMN_MENUCODE_TMYP:
      UARTStatus = ASMN_TimerYFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMYA
    case ASMN_MENUCODE_TMYA:
      UARTStatus = ASMN_TimerYApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMZP
    case ASMN_MENUCODE_TMZP:
      UARTStatus = ASMN_TimerZFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TMZA
    case ASMN_MENUCODE_TMZA:
      UARTStatus = ASMN_TimerZApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_TM0P
    case ASMN_MENUCODE_TM0P:
      UARTStatus = ASMN_Timer0Functions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_WTM
    case ASMN_MENUCODE_WTM:
      UARTStatus = ASMN_WatchFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_WDT
    case ASMN_MENUCODE_WDT:
      UARTStatus = ASMN_WatchdogFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_DCANP
    case ASMN_MENUCODE_DCANP:
      UARTStatus = ASMN_DCANFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_FCANA
    case ASMN_MENUCODE_FCANA:
      UARTStatus = ASMN_FCANApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_AFCANA
    case ASMN_MENUCODE_AFCANA:
      UARTStatus = ASMN_AFCANApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_FVANA
    case ASMN_MENUCODE_FVANA:
      UARTStatus = ASMN_FVANApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_RSCANA
    case ASMN_MENUCODE_RSCANA:
      UARTStatus = ASMN_RSCANApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_RSCFDA
    case ASMN_MENUCODE_RSCFDA:
      UARTStatus = ASMN_RSCFDApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_MCANA
    case ASMN_MENUCODE_MCANA:
      UARTStatus = ASMN_MCANApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_MTTCANA
    case ASMN_MENUCODE_MTTCANA:
      UARTStatus = ASMN_MTTCANApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_SWC
    case ASMN_MENUCODE_SWC:
      UARTStatus = ASMN_SWCApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_UARTAP
    case ASMN_MENUCODE_UARTAP:
      UARTStatus = ASMN_UARTAFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_UARTAA
    case ASMN_MENUCODE_UARTAA:
      UARTStatus = ASMN_UARTAApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_UARTCP
    case ASMN_MENUCODE_UARTCP:
      UARTStatus = ASMN_UARTCFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_UARTCA
    case ASMN_MENUCODE_UARTCA:
      UARTStatus = ASMN_UARTCApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_UARTFA
    case ASMN_MENUCODE_UARTFA:
      UARTStatus = ASMN_UARTFApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_CSIP
    case ASMN_MENUCODE_CSIP:
      UARTStatus = ASMN_CSIFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_INTC
    case ASMN_MENUCODE_INTC:
      UARTStatus = ASMN_INTCFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_DMACP
    case ASMN_MENUCODE_DMACP:
      UARTStatus = ASMN_DMACFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_BUSIFM
    case ASMN_MENUCODE_BUSIF:
      UARTStatus = ATIF_BusInterfaceFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_PWR
    case ASMN_MENUCODE_PWR:
      UARTStatus = ATIF_PowerSaveFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_ISM
    case ASMN_MENUCODE_ISM:
      UARTStatus = ASMN_ISMFunctions( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_ISMA
    case ASMN_MENUCODE_ISMA:
      UARTStatus = ASMN_ISMApplications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_RLIN3
    case ASMN_MENUCODE_RLIN3:
      UARTStatus = ASMN_RLIN3Applications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_RLIN2
    case ASMN_MENUCODE_RLIN2:
      UARTStatus = ASMN_RLIN2Applications( ComPortUnit_u08 );
      break;
#endif

#ifdef ASMN_MENUCODE_FR
    case ASMN_MENUCODE_FR:
      UARTStatus = ASMN_FRApplications( ComPortUnit_u08 );
#endif

#ifdef ASMN_MENUCODE_ETH
    case ASMN_MENUCODE_ETH:
      UARTStatus = ASMN_ETHApplications( ComPortUnit_u08 );
#endif

#ifdef ASMN_MENUCODE_SELF
    case ASMN_MENUCODE_SELF:
      UARTStatus = ASMN_SelfTest( ComPortUnit_u08 );
      break;
#endif

    default:
      UARTStatus = ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_NOCMD,
                                        ASMN_UARTMODECRLF );
      break;
    }
  }

  ASMN_UARTSENDSTRING( ComPortUnit_u08, ASMN_MENULINE_GOODBYE,
				    ASMN_UARTMODECRLF );

#if( ASMN_UARTINTERFACE != DEBUG_INTERNAL )
  ASMN_UARTRESET( ComPortUnit_u08 );
  ASMN_UARTPORTDISABLE( ComPortUnit_u08 );
#endif

#ifdef REXIT
  REXIT( );
#else
  exit( 0 );
#endif

#endif
#ifdef TEST_RSCFD_RLIN_FR
	/* 1st. FR test */
	ApplFRStart_2( 0 );
	/* 2nd. RSCFD test */
	ASMN_RSCFDApplications( 1 );
	/* 3rd. RLIN2/3 */
	powertest_lin_rlin2_m_rlin3_s();
	/* 3rd. while(1) loop */
	while(1);
#endif

#ifdef TEST_RIIC
  riic_app();
#endif
#ifdef TEST_RSCFD
	ASMN_RSCFDApplications( 1 );
#endif
#ifdef TEST_RLIN3
	ASMN_RLIN3Applications( 1 );
#endif
#ifdef TEST_RLIN2
	ASMN_RLIN2Applications( 1 );
#endif
#ifdef TEST_FR
	ASMN_FRApplications( 1 );
#endif
#ifdef POWER_TEST_RLIN_1_BUS
	powertest_lin_1bus_rlin21m_rlin30s();
#endif
#ifdef POWER_TEST_RLIN
	powertest_lin_rlin2_m_rlin3_s();
#endif
}
