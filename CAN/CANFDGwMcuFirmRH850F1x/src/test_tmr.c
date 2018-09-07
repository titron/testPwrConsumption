#include <test_port.h>
#include "devices/rh850g3k-f1kh-d8/bak-iodefine.h"

void tmr0_init (void) {

   /*Set Count stop trigger reg*/
	OSTM0.TT= 0x01;

	/* Set start value of down counter in interval timer mode */
//	OSTM0.CMP = 0x3D0900;		// OSTM runs on 10Hz
	OSTM0.CMP = 0x9c40;		// OSTM runs on 1000Hz

	/*Select Interval Timer mode and start interrupt disabled*/
	OSTM0.CTL = 0x00;

  /* enable interrupt for OSTM0  (interrupt channel 84) */
	IBDOSTM0 = 0x00000001; /* assign interrupt to PE1 */
	ICOSTM0=0x41;

	/* Start timer */
	OSTM0.TS = 0x01;
}

/* interrupt routine */
#pragma section text"comint"
#pragma interrupt Isr_OsTimer0( enable=false , channel=84 , callt=false , fpu=false )
char portlevel = 0;
void Isr_OsTimer0(void)
{
	if(portlevel)
	{
		PORT_SET_LEVEL(1);
		portlevel = 0;
	}
	else
	{
		PORT_SET_LEVEL(0);
		portlevel = 1;
	}
} /* End of Isr_OsTimer0() */
#pragma section default
// End of file
