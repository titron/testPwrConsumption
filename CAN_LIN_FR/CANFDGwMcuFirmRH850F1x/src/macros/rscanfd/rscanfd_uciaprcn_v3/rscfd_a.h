//============================================================================
// PROJECT = RSCFD Type RSCFD_UCIAPRCN
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2002 by Renesas Electronics (Europe) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RSCFD Application Functions Include
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

#ifndef _RSCFD_A_H
#define _RSCFD_A_H

#include <ree_types.h>

extern bit EE_RSCFD_Reset( u08 Unit_u08 );

extern bit EE_RSCFD_BasicTest( u08 Unit1_u08,
                               u08 Unit2_u08,
                               u08 Channel1_u08,
                               u08 Channel2_u08 );

extern bit EE_RSCFD_RAMTestApp( u08 Unit_u08 );

extern bit EE_RSCFD_BasicSelfTest( u08 Unit1_u08, 
                                   u08 Channel1_u08,
                                   u08 Channel2_u08 );

extern bit EE_RSCFD_BasicIntSelfTest( u08 Unit_u08,
                                      u08 Channel_u08 );

extern bit EE_RSCFD_SW_Gateway( u08 Unit_u08,
                                u08 ChannelCount_u08 );

#endif
