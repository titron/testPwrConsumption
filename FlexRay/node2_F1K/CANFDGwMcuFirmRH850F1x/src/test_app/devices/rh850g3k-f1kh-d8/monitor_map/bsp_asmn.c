//============================================================================
// PROJECT = ASMN BOARD SUPPORT CODE
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2018 by Renesas Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
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
//
//
//============================================================================
// Environment: Devices:          RH850/F1x Application Network Test Board
//              Assembler:        GHS MULTI 
//              C-Compiler:       GHS MULTI 
//              Linker:           GHS MULTI 
//              Debugger:         GHS MULTI 
//============================================================================

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       Includes                                                                                                        |
+-----------------------------------------------------------------------------------------------------------------------+
*/
#include <platform.h>
#include "../../../../devices/rh850g3k-f1kh-d8/bak-iodefine.h"
//#include <device.h>

/*
+=======================================================================================================================+
||      Interrupt Handlers                                                                                             ||
+=======================================================================================================================+
*/
#ifndef CSPLUS_PRJ_USED /* GHS project */
/* 1ms timer tick interrupt */
__interrupt void INTOSTM0(void)
{
}

__interrupt void INTWDTA0(void)
{
	WDTA0WDTE = 0xAC;
}
#else
/* 1ms timer tick interrupt */
#pragma section text"comint"
//#pragma interrupt INTOSTM0( enable=false , channel=24 , callt=false , fpu=false )
//void INTOSTM0(void)
//{
//}

#pragma interrupt INTWDTA0( enable=false , channel=40 , callt=false , fpu=false )
void INTWDTA0(void)
{
	WDTA0.WDTE = 0xAC;
}
#pragma section default
#endif
//End of file
