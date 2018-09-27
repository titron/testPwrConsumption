//============================================================================
// PROJECT = RH850/F1KH-D8
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2017 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RSCFD Hardware Interrupt Bundling Decoder
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
// Environment: Devices:          RH850/F1KH-D8
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#include <ree_types.h>
#include <stddef.h>
#include <map_rscfd.h>

void RSCFD_IntBundlingDecode( u08 UnitNumber_u08,
                              u08 *GlobalInterruptFlag_pu08,
                              u08 *MachineInterruptFlag0_pu08,
                              u08 *MachineInterruptFlag1_pu08,
                              u08 *MachineInterruptFlag2_pu08, 
                              u08 *MachineInterruptFlag3_pu08, 
                              u08 *MachineInterruptFlag4_pu08,
                              u08 *MachineInterruptFlag5_pu08,
                              u08 *MachineInterruptFlag6_pu08,
                              u08 *MachineInterruptFlag7_pu08 )
{
  u08 FIFONumber_u08;
  u08 TXIRQBundling_u08;

  if( *GlobalInterruptFlag_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *GlobalInterruptFlag_pu08 )
        {
        case EE_RSCFD_INT_GERR:
          break;
          
        case EE_RSCFD_INT_RXF0:
        case EE_RSCFD_INT_RXF1:
        case EE_RSCFD_INT_RXF2:
        case EE_RSCFD_INT_RXF3:
        case EE_RSCFD_INT_RXF4:
        case EE_RSCFD_INT_RXF5:
        case EE_RSCFD_INT_RXF6:
        case EE_RSCFD_INT_RXF7:
          for( FIFONumber_u08 = 0;
               FIFONumber_u08 < EE_RSCFD_MAXRXFIFOS;
               FIFONumber_u08++ )
            {
              if( ee_rscfd_common_p[ UnitNumber_u08 ]->rfsts[ FIFONumber_u08 ].rfif )
                {
                  *GlobalInterruptFlag_pu08 = EE_RSCFD_INT_RXF0 + 
                    FIFONumber_u08;
                }
            }
          break;

        default:
          break;
        }
    }

  if( *MachineInterruptFlag0_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *MachineInterruptFlag0_pu08 )
        {
        case EE_RSCFD_INT_CERR:
        case EE_RSCFD_INT_RXCF:
          break;

        case EE_RSCFD_INT_TX:
          TXIRQBundling_u08 = ( u08 )( ee_rscfd_common_p[ UnitNumber_u08 ]->gtintsts[ 0 ] & 0x000000FF );
          if( TXIRQBundling_u08 & 0x01 ) *MachineInterruptFlag0_pu08 = EE_RSCFD_INT_TX;
          if( TXIRQBundling_u08 & 0x02 ) *MachineInterruptFlag0_pu08 = EE_RSCFD_INT_TXA;
          if( TXIRQBundling_u08 & 0x04 )
          {
#ifdef RH850_F1H_RSCFD20
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[0].irq != 0 )
              *MachineInterruptFlag0_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[0].irq != 0 )
              *MachineInterruptFlag0_pu08 = EE_RSCFD_INT_TXQ1;
#else
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ 0 ].irq != 0 )
              *MachineInterruptFlag0_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ 0 ].irq != 0 )
              *MachineInterruptFlag0_pu08 = EE_RSCFD_INT_TXQ1;
#endif
          }
          if( TXIRQBundling_u08 & 0x08 ) *MachineInterruptFlag0_pu08 = EE_RSCFD_INT_TXCF;
          if( TXIRQBundling_u08 & 0x10 ) *MachineInterruptFlag0_pu08 = EE_RSCFD_INT_TXHL;
          break;

        default:
          break;
        }
    }

  if( *MachineInterruptFlag1_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *MachineInterruptFlag1_pu08 )
        {
        case EE_RSCFD_INT_CERR:
        case EE_RSCFD_INT_RXCF:
          break;

        case EE_RSCFD_INT_TX:
          TXIRQBundling_u08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gtintsts[ 0 ] & 0x0000FF00 ) >> 8 );
          if( TXIRQBundling_u08 & 0x01 ) *MachineInterruptFlag1_pu08 = EE_RSCFD_INT_TX;
          if( TXIRQBundling_u08 & 0x02 ) *MachineInterruptFlag1_pu08 = EE_RSCFD_INT_TXA;
          if( TXIRQBundling_u08 & 0x04 )
          {
#ifdef RH850_F1H_RSCFD20
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[1].irq != 0 )
              *MachineInterruptFlag1_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[1].irq != 0 )
              *MachineInterruptFlag1_pu08 = EE_RSCFD_INT_TXQ1;
#else
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[1].irq != 0 )
              *MachineInterruptFlag1_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[1].irq != 0 )
              *MachineInterruptFlag1_pu08 = EE_RSCFD_INT_TXQ1;
#endif
          }
          if( TXIRQBundling_u08 & 0x08 ) *MachineInterruptFlag1_pu08 = EE_RSCFD_INT_TXCF;
          if( TXIRQBundling_u08 & 0x10 ) *MachineInterruptFlag1_pu08 = EE_RSCFD_INT_TXHL;
          break;

        default:
          break;
        }
    }

  if( *MachineInterruptFlag2_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *MachineInterruptFlag2_pu08 )
        {
        case EE_RSCFD_INT_CERR:
        case EE_RSCFD_INT_RXCF:
          break;

        case EE_RSCFD_INT_TX:
          TXIRQBundling_u08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gtintsts[ 0 ] & 0x00FF0000 ) >> 16 );
          if( TXIRQBundling_u08 & 0x01 ) *MachineInterruptFlag2_pu08 = EE_RSCFD_INT_TX;
          if( TXIRQBundling_u08 & 0x02 ) *MachineInterruptFlag2_pu08 = EE_RSCFD_INT_TXA;
          if( TXIRQBundling_u08 & 0x04 )
          {
#ifdef RH850_F1H_RSCFD20
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[2].irq != 0 )
              *MachineInterruptFlag2_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[2].irq != 0 )
              *MachineInterruptFlag2_pu08 = EE_RSCFD_INT_TXQ1;
#else
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ 2 ].irq != 0 )
              *MachineInterruptFlag2_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ 2 ].irq != 0 )
              *MachineInterruptFlag2_pu08 = EE_RSCFD_INT_TXQ1;
#endif
          }
          if( TXIRQBundling_u08 & 0x08 ) *MachineInterruptFlag2_pu08 = EE_RSCFD_INT_TXCF;
          if( TXIRQBundling_u08 & 0x10 ) *MachineInterruptFlag2_pu08 = EE_RSCFD_INT_TXHL;
          break;

        default:
          break;
        }
    }
	
	if( *MachineInterruptFlag3_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *MachineInterruptFlag3_pu08 )
        {
        case EE_RSCFD_INT_CERR:
        case EE_RSCFD_INT_RXCF:
          break;

        case EE_RSCFD_INT_TX:
          TXIRQBundling_u08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gtintsts[ 0 ] & 0xFF000000 ) >> 24 );
          if( TXIRQBundling_u08 & 0x01 ) *MachineInterruptFlag3_pu08 = EE_RSCFD_INT_TX;
          if( TXIRQBundling_u08 & 0x02 ) *MachineInterruptFlag3_pu08 = EE_RSCFD_INT_TXA;
          if( TXIRQBundling_u08 & 0x04 )
          {
#ifdef RH850_F1H_RSCFD20
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[3].irq != 0 )
              *MachineInterruptFlag3_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[3].irq != 0 )
              *MachineInterruptFlag3_pu08 = EE_RSCFD_INT_TXQ1;
#else
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ 3 ].irq != 0 )
              *MachineInterruptFlag3_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ 3 ].irq != 0 )
              *MachineInterruptFlag3_pu08 = EE_RSCFD_INT_TXQ1;
#endif
          }
          if( TXIRQBundling_u08 & 0x08 ) *MachineInterruptFlag3_pu08 = EE_RSCFD_INT_TXCF;
          if( TXIRQBundling_u08 & 0x10 ) *MachineInterruptFlag3_pu08 = EE_RSCFD_INT_TXHL;
          break;

        default:
          break;
        }
    }
	
	if( *MachineInterruptFlag4_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *MachineInterruptFlag4_pu08 )
        {
        case EE_RSCFD_INT_CERR:
        case EE_RSCFD_INT_RXCF:
          break;

        case EE_RSCFD_INT_TX:
          TXIRQBundling_u08 = ( u08 )( ee_rscfd_common_p[ UnitNumber_u08 ]->gtintsts[ 1 ] & 0x000000FF );
          if( TXIRQBundling_u08 & 0x01 ) *MachineInterruptFlag4_pu08 = EE_RSCFD_INT_TX;
          if( TXIRQBundling_u08 & 0x02 ) *MachineInterruptFlag4_pu08 = EE_RSCFD_INT_TXA;
          if( TXIRQBundling_u08 & 0x04 )
          {
#ifdef RH850_F1H_RSCFD20
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[4].irq != 0 )
              *MachineInterruptFlag4_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[4].irq != 0 )
              *MachineInterruptFlag4_pu08 = EE_RSCFD_INT_TXQ1;
#else
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ 4 ].irq != 0 )
              *MachineInterruptFlag4_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ 4 ].irq != 0 )
              *MachineInterruptFlag4_pu08 = EE_RSCFD_INT_TXQ1;
#endif
          }
          if( TXIRQBundling_u08 & 0x08 ) *MachineInterruptFlag4_pu08 = EE_RSCFD_INT_TXCF;
          if( TXIRQBundling_u08 & 0x10 ) *MachineInterruptFlag4_pu08 = EE_RSCFD_INT_TXHL;
          break;

        default:
          break;
        }
    }

	if( *MachineInterruptFlag5_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *MachineInterruptFlag5_pu08 )
        {
        case EE_RSCFD_INT_CERR:
        case EE_RSCFD_INT_RXCF:
          break;

        case EE_RSCFD_INT_TX:
          TXIRQBundling_u08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gtintsts[ 1 ] & 0x0000FF00 ) >> 8 );
          if( TXIRQBundling_u08 & 0x01 ) *MachineInterruptFlag5_pu08 = EE_RSCFD_INT_TX;
          if( TXIRQBundling_u08 & 0x02 ) *MachineInterruptFlag5_pu08 = EE_RSCFD_INT_TXA;
          if( TXIRQBundling_u08 & 0x04 )
          {
#ifdef RH850_F1H_RSCFD20
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[5].irq != 0 )
              *MachineInterruptFlag5_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[5].irq != 0 )
              *MachineInterruptFlag5_pu08 = EE_RSCFD_INT_TXQ1;
#else
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ 5 ].irq != 0 )
              *MachineInterruptFlag5_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ 5 ].irq != 0 )
              *MachineInterruptFlag5_pu08 = EE_RSCFD_INT_TXQ1;
#endif
          }
          if( TXIRQBundling_u08 & 0x08 ) *MachineInterruptFlag5_pu08 = EE_RSCFD_INT_TXCF;
          if( TXIRQBundling_u08 & 0x10 ) *MachineInterruptFlag5_pu08 = EE_RSCFD_INT_TXHL;
          break;

        default:
          break;
        }
    }
	if( *MachineInterruptFlag6_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *MachineInterruptFlag6_pu08 )
        {
        case EE_RSCFD_INT_CERR:
        case EE_RSCFD_INT_RXCF:
          break;

        case EE_RSCFD_INT_TX:
          TXIRQBundling_u08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gtintsts[ 1 ] & 0x00FF0000 ) >> 16 );
          if( TXIRQBundling_u08 & 0x01 ) *MachineInterruptFlag6_pu08 = EE_RSCFD_INT_TX;
          if( TXIRQBundling_u08 & 0x02 ) *MachineInterruptFlag6_pu08 = EE_RSCFD_INT_TXA;
          if( TXIRQBundling_u08 & 0x04 )
          {
#ifdef RH850_F1H_RSCFD20
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[6].irq != 0 )
              *MachineInterruptFlag6_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[6].irq != 0 )
              *MachineInterruptFlag6_pu08 = EE_RSCFD_INT_TXQ1;
#else
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ 6 ].irq != 0 )
              *MachineInterruptFlag6_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ 6 ].irq != 0 )
              *MachineInterruptFlag6_pu08 = EE_RSCFD_INT_TXQ1;
#endif
          }
          if( TXIRQBundling_u08 & 0x08 ) *MachineInterruptFlag6_pu08 = EE_RSCFD_INT_TXCF;
          if( TXIRQBundling_u08 & 0x10 ) *MachineInterruptFlag6_pu08 = EE_RSCFD_INT_TXHL;
          break;

        default:
          break;
        }
    }

	if( *MachineInterruptFlag7_pu08 != EE_RSCFD_INT_NOINT )
    {
      switch( *MachineInterruptFlag7_pu08 )
        {
        case EE_RSCFD_INT_CERR:
        case EE_RSCFD_INT_RXCF:
          break;

        case EE_RSCFD_INT_TX:
          TXIRQBundling_u08 = ( u08 )( ( ee_rscfd_common_p[ UnitNumber_u08 ]->gtintsts[ 1 ] & 0xFF000000 ) >> 24 );
          if( TXIRQBundling_u08 & 0x01 ) *MachineInterruptFlag7_pu08 = EE_RSCFD_INT_TX;
          if( TXIRQBundling_u08 & 0x02 ) *MachineInterruptFlag7_pu08 = EE_RSCFD_INT_TXA;
          if( TXIRQBundling_u08 & 0x04 )
          {
#ifdef RH850_F1H_RSCFD20
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[7].irq != 0 )
              *MachineInterruptFlag7_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq.sts[7].irq != 0 )
              *MachineInterruptFlag7_pu08 = EE_RSCFD_INT_TXQ1;
#else
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 0 ].sts[ 7 ].irq != 0 )
              *MachineInterruptFlag7_pu08 = EE_RSCFD_INT_TXQ0;
            if( ee_rscfd_common_p[ UnitNumber_u08 ]->txq[ 1 ].sts[ 7 ].irq != 0 )
              *MachineInterruptFlag7_pu08 = EE_RSCFD_INT_TXQ1;
#endif
          }
          if( TXIRQBundling_u08 & 0x08 ) *MachineInterruptFlag7_pu08 = EE_RSCFD_INT_TXCF;
          if( TXIRQBundling_u08 & 0x10 ) *MachineInterruptFlag7_pu08 = EE_RSCFD_INT_TXHL;
          break;

        default:
          break;
        }
    }
}
