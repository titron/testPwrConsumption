#ifndef _lint
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * (MISRA C:2012 Violation - Rule 3.1
 * Justification - C comment contains C++ comment can't avoid here.)
 * http:/ /www.renesas.com/disclaimer
 *
 * Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : main_pe1.c
 * Version      : 1.0
 * Device(s)	   : R7F7015273,WS1.0
 * Tool-Chain   : 1. IDE and Compiler
 *              : GHS MULTI Launcher - MULTI v6.1.6
 *              : Compiler: Compiler V2013.5.5
 *              :
 *              : 2. Renesas CAN Gateway Designer - Version 1.0.1
 *              :
 *              : 3. Renesas CANvisualizer Version 1.1
 *              :
 * OS		   : none.
 * H/W Platform : R0K5CANFDE000BR, RH850/F1x FPGA BOARD
 *              : R0K5F1GCPE000BR, RH850/F1x CPU BOARD
 * Description  : This file implements main function and ISR.
 * Operation	   : 1. Run Renesas CAN Gateway Designer.
 *              :   Design CAN network.
 *              :   Then Rule Check.
 *              :   Generate code if no error.
 *              :
 *              : 2. Build project on MULTI IDE.
 *              :   Compile and download the sample code.
 *              :
 *              : 3. Run Renesas CANvisualizer.
 *              :   Configure CAN frame.
 *              :   - Baudrate, frames etc..
 *              :   then Start.
 *              :
 *              : 4. Run core PE1 and core PE2 on MULTI IDE.
 *              :
 *              : 5. Check CAN frame Tx/Rx on Renesas CANvisualizer.
 *              :
 * Limitations  : none.
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 25.09.2014 1.00     First Release
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "iodefine.h"
#ifdef TEST_ENV
#include <test_tmr.h>
#include <test_port.h>
#endif
/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/
extern void __lowinit_hw( void);
void main(void);


/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: main
 * Description  : The main loop
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void main(void)
{
	__DI();
	__lowinit_hw();
#ifdef TEST_ENV
	tmr0_init();
	port_init();
#endif
	 /* Tell PE2 that clock init is done */
	MEV.G0MEV0.UINT32=1u;
	__EI();

#ifdef TEST_ENV
	while(1);
	port_test();
#endif

	main_loop();
} /* End of main() */

/* End of file */
#endif
