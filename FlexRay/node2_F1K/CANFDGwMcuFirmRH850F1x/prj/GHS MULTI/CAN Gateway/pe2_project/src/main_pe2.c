/*===============================================================================================

    Copyright (c) 2013 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics 
    Corporation. All rights reserved.

  ===============================================================================================

    Warranty Disclaimer                                                       
                                                                             
    Because the Product(s) is licensed free of charge, there is no warranty of any kind
    whatsoever and expressly disclaimed and excluded by Renesas, either expressed or implied, 
    including but not limited to those for non-infringement of intellectual property,
    merchantability and/or fitness for the particular purpose.
    Renesas shall not have any obligation to maintain, service or provide bug fixes for the
    supplied Product(s) and/or the Application.

    Each User is solely responsible for determining the appropriateness of using the Product(s)
    and assumes all risks associated with its exercise of rights under this Agreement, including,
    but not limited to the risks and costs of program errors, compliance with applicable laws,
    damage to or loss of data, programs or equipment, and unavailability or interruption of
    operations.

    Limitation of Liability

    In no event shall Renesas be liable to the User for any incidental, consequential, indirect,
    or punitive damage (including but not limited to lost profits) regardless of whether such
    liability is based on breach of contract, tort, strict liability, breach of warranties, 
    failure of essential purpose or otherwise and even if advised of the possibility of such
    damages. Renesas shall not be liable for any services or products provided by third party
    vendors, developers or consultants identified or referred to the User by Renesas in 
    connection with the Product(s) and/or the Application.

  ===============================================================================================*/

//--------------------------------------------------------------------------
// includes
//--------------------------------------------------------------------------

#include <device.h>

//--------------------------------------------------------------------------
// defines
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// prototypes
//--------------------------------------------------------------------------
__interrupt void INTOSTM5_1(void)
{  

}


void init_OSTM5 (void) {

   /*Set Count stop trigger reg*/

	OSTM5TT= 0x01;
	
	/*Select Interval Timer mode and start interrupt disabled*/
	OSTM5CTL = 0x00;

	/* Set start value of down counter in interval timer mode */
	OSTM5CMP = 0x3D0900;		// OSTM runs on CPUCLK2 = 40MHz / (39999+1) = 1000Hz
 
 
  /* enable interrupt for OSTM5 (interrupt channel 314) */
  EIBD314=0x00000002; /* assign interrupt to PE2 */
  PFSSTBOSTM5=1;      /* activate table mode */
  PFSSRFOSTM5=0;      /* clear request flag */
  PFSSMKOSTM5=0;      /* unmask interrupt */
 
  /* Start timer */
  OSTM5TS = 0x01;
}

//--------------------------------------------------------------------------
//
//	Common MAIN function
//
//--------------------------------------------------------------------------

void main()
{
  /* wait until clock init is done by PE1 */
  while(PFSSG0MEV0!=1u);
init_OSTM5();

 EI();
 
 while(1);
  
}

