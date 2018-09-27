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

//#include <device.h>
//#include "../../../../devices/rh850g3k-f1kh-d8/bak-iodefine.h"
#include "iodefine.h"

//--------------------------------------------------------------------------
// defines
//--------------------------------------------------------------------------
//#define WR_PROT_REG(cmd, reg, value)                \
//    do {                                            \
//        cmd = 0xA5U;                                \
//        reg = value;                                \
//        reg = ~value;                               \
//        reg = value;                                \
//    } while (0)
#define WR_PROT_REG(preg,pstatus,reg,value)   do{\
                                                  (preg)=0xa5u;\
                                                  (reg)=(value);\
                                                  (reg)=~(value);\
                                                  (reg)=(value);\
                                                  }while((pstatus)==1u)
//--------------------------------------------------------------------------
// variables
//--------------------------------------------------------------------------

extern long __ghsbegin_bss[];
extern long __ghsend_bss[];
extern long __ghsbegin_slbss[];
extern long __ghsend_slbss[];
extern long __ghsbegin_sldata[];
extern long __ghsend_sldata[];
extern long __ghsbegin_slsync[];
extern long __ghsend_slsync[];
extern long __ghsbegin_stack[];
extern long __ghsend_stack[];

#pragma ghs startdata			// locate to GRAM
#pragma ghs section bss=".slsync"	// to section ".slsync"
extern volatile unsigned int	ThreadLocked;		// for mutual exclusion
extern volatile unsigned int	PE_Started;		// for mutual exclusion
#pragma ghs section			//
#pragma ghs enddata			// locate default	

#ifdef GHS
/*
 * This section is basically defined in GHS startup and system library
 * and contains exactly 1 variable. Since the RH850 offers the 32 MEV registers.
 * One (MEV31) is taken as the synchronization flag. With each RESET, it
 * is automatically cleared and must be set to 1 if the initialization of the
 * shared components is done by core1 (PE1).
 */
#pragma ghs section data=".multicore_init"
int __ghs_multicore_init_flag = 0;
#pragma ghs section data=default


void __spinLockRW( PVOID pMEVREG);
void __spinUnlockRW( PVOID pMEVREG);

int swreset0( int try)
{
	if( GetPEID() == PE1) 
    {
        do
        {
            __SNOOZE();
        } while( try--);
    }

    return -1;
}
#endif
/*
 * Called first, directly after RESET and before _start() is called
 * Be aware of following restrictions:
 *   1. Use ONLY variables of 32-bit size (int, long)
 *   2. Do not read from any memory, before it has been written to by 32-bit 
 *   3. Minimize usage of local variables
 *   4. Initialized memory is NOT available at this point
 */
extern void test_port(void);
extern void test_delay(void);
void __lowinit_hw( void)
{
    /* PE2 stops from continuation, if PE1 did not finish the
     * initialization of shared memory area.
     */
//	if( GetPEID() == PE2)
//    {
//        while( __ghs_multicore_init_flag == 0)  __SNOOZE();
//    }

    /* If MainOSC needs to be started */
    if((CLKCTL.MOSCS&0x04u) != 0x04u)
    {
        CLKCTL.MOSCC = 0x06;                                                /* Set MainOSC gain for 16MHz */
        WR_PROT_REG(WPROTR.PROTCMD0,WPROTR.PROTS0,CLKCTL.MOSCE,0x01);   /* Trigger MainOsc start */
        while ((CLKCTL.MOSCS&0x04u) != 0x04u);                              /* Wait for active MainOSC */
		}
    
    /* Prepare PLL0*/
    if((CLKCTL.PLL0S&0x04u) != 0x04u)
    {

        /* 16 MHz MainOSC setting (VCOOUT=480MHz; 5% modulation range; Mr=2; Nr=60;--> MFD=40)*/
//        PLL0C = 0x6A10683B;
        CLKCTL.PLL0C = 0x6A00483B; 
        
        /* Set stabilization time to recommended value */
        CLKCTL.PLL0ST = 0x1B80;
        
        WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.PLL0E,0x01);   /* Enable PLL0 */
        while((CLKCTL.PLL0S&0x04u) != 0x04u);                               /* Wait for active PLL0 */
    }
    
    /* Prepare PLL1*/
    if((CLKCTL.PLL1S&0x04u) != 0x04u)
    {

        /* 16 MHz MainOSC setting (VCOOUT=480MHz; Mr=2; Nr=60; PPLLOUT=80MHz)*/
        CLKCTL.PLL1C=0x10B3B;
        
        WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.PLL1E,0x01);   /* Enable PLL1 */
        while((CLKCTL.PLL1S&0x04u) != 0x04u);                               /* Wait for active PLL1 */

    }
      
    /* CPU Clock divider = 1, CPLL Divider = 2 -> CPLL0OUT = 240MHz */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_CPUCLKD_CTL,0x29u);
    while(CLKCTL.CKSC_CPUCLKD_ACT!=0x29u);

    /* CPLL0OUT -> CPU Clock */ 
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_CPUCLKS_CTL,0x00u);
    while(CLKCTL.CKSC_CPUCLKS_ACT!=0x00u);

    /* Set PPLLCLK to PPLLOUT = 80MHz */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_PPLLCLKS_CTL,0x03u);
    while(CLKCTL.CKSC_PPLLCLKS_ACT!=0x03u);
    
    /* Set Peripheral CLK1 to PPLLCLK = 80MHz */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_IPERI1S_CTL,0x01u);
    while(CLKCTL.CKSC_IPERI1S_ACT!=0x01u);
    
    /* Set Peripheral CLK2 to PPLLCLK/2 = 40 MHZ */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_IPERI2S_CTL,0x01u);
    while(CLKCTL.CKSC_IPERI2S_ACT!=0x01u);

    /* PLL -> RSCAN-FD Clock: PPLLCLK (PLL1, 80 MHz) */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_ICANS_CTL,0x03);
    while((CLKCTL.CKSC_ICANS_ACT & 0x03) != 0x03);
  
    /* MainOSC/1 -> RSCAN-FD direct Clock: 16 MHz */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_ICANOSCD_CTL,0x01);
    while((CLKCTL.CKSC_ICANOSCD_ACT & 0x03) != 0x01);
  
    /* PLL -> RLIN3 Clock: PPLLCLK2 (PLL1, 40 MHz) */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_ILINS_CTL,0x03);
    while((CLKCTL.CKSC_ICANS_ACT & 0x03) != 0x03);
    
    /* PLL -> RIIC Clock: PPLLCLK2 (PLL1, 40 MHz) */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_IIICS_CTL,0x02);
    while((CLKCTL.CKSC_IIICS_ACT & 0x02) != 0x02);

    /* PLL -> CSI Clock: PPLLCLK (PLL1, 80 MHz) */
    WR_PROT_REG(WPROTR.PROTCMD1,WPROTR.PROTS1,CLKCTL.CKSC_ICSIS_CTL,0x01);
    while((CLKCTL.CKSC_ICSIS_ACT & 0x03) != 0x01);
}


#if 0
/*
 * This function is called directly after _start(), before runtime 
 * initialization takes place.
 */
void __ghs_board_memory_init( void)
{
	int		i;
	
	/*
	 * Delay PE2
	 * and make sure PE2 is waiting for some time
	 */

	if( GetPEID() == PE2) 
	{
		for( i=0; i<10000; i++) {
			__SNOOZE();			/* wait a while */
		}
	}

	/*
	 * Only core PE1 clears global, shared memory.No data initialization 
     * takes place in shared section, ie. initialized data is NOT 
     * allowed. All shared variables are located in global memory.
	 */
	if( GetPEID() == PE1) 
    {
        long *__p= __ghsbegin_bss;

        /* Clear shared bss section */
        while( __p <= __ghsend_bss)
            *__p++= 0UL;

        /* Clear shared slbss (secondary, large bss) section */
        __p= __ghsbegin_slbss;
        while( __p <= __ghsend_slbss)
            *__p++= 0UL;

        /* Clear shared synchronization section */
        __p= __ghsbegin_slsync;
        while( __p <= __ghsend_slsync)
            *__p++= 0UL;

        /* Clear shared data section, if exists */
        __p= __ghsbegin_sldata;
        while( __p <= __ghsend_sldata)
            *__p++= 0UL;
    }
	if( GetPEID() == PE2) 
		__SNOOZE();
}

/* 
 * Once PE1 finished its initialization part, PE2 may continue to
 * initialize the workspeace.
 */
void __ghs_board_devices_init(void)
{
	/* 
	 * If both cores are finished with the runtime initialization,
     * the MEV32 register contains PE1|PE2 (3)
	 */
    __ghs_multicore_init_flag |=  GetPEID();
}
#endif
/* End of file */
