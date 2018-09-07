//============================================================================
// PROJECT = RH850/F1KH-D8
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2017 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastr. 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: Header File for RCAN2NEXT SCIT SFR includes
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
//
// $Log$
//
//============================================================================

#ifndef _MAP_DEVICE_H
#define _MAP_DEVICE_H

/* Define registers for F1KH-D8 */
/* Select the device specific include here */

#ifdef __ghs__
#include <DR7F701709_0.h>

#endif

#include <ree_macros.h>

/* List of all included macros, to be supported */

/* ...MACROS: Number or macro units
 * ...TYPE:   Unique type identifier from nec_macros.h
 */

#define PORTS_TYPE     PORTS_STANDARD

#define EE_RSCFD_MACROS   1
#define EE_RSCFD_TYPE     RSCFD_UCIAPRCN_V3

#define RLIN3_MACROS      8
#define RLIN3_TYPE        RLIN3_UCIAPRLN

#define RLIN2_MACROS      3
#define RLIN2_TYPE        RLIN2_UCIAPRLN

#define FR_MACROS         1
#define FR_TYPE           FR_FLXA_0012

#define RIIC_MACROS         1
#endif


