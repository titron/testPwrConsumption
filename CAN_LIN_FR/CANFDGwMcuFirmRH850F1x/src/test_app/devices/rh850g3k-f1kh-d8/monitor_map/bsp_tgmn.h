//============================================================================
// PROJECT = TFT GRAPHICS DISPLAY APP BOARD SUPPORT CODE
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2016 by Renesas Electronics (Europe) GmbH. All rights reserved.
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

/* The following connections apply:

RH850 connections:

        2.8" TFT Display (ILI9341) and SD-Flash:
        ========================================

        Port          | NWB_F1K Board | PiggyBoard | Arduino  | I/O | used for
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        PWM9/P9_1     |    CN88_5     |   CN3_10   | D4       |  O  | SD_NCS
        PWM20/P9_2    |    CN88_6     |   CN3_34   | D5       |  O  | TFT_NCS (ILI9341: CSX, active low)
        PWM25/P11_0   |    CN88_7     |   CN3_26   | D6       |  O  | TFT_D/C (ILI9341: D/CX <low: control; high: data>)
        PWM38/P8_6    |    CN88_8     |   CN3_39   | D7       |  O  | TFT_LED (PCB jumper change on TFT required)
        PWM21/P9_3    |    CN98_1     |   CN3_22   | D8       | I/O | unused
        PWM25/P11_0   |    CN98_2     |   CN3_26   | D9       |  O  | TFT_D/C (ILI9341: D/CX <low: control; high: data>)
        PWM20/P9_2    |    CN98_3     |   CN3_34   | D10      |  O  | TFT_NCS (ILI9341: CSX, active low)
        PWM27/P11_2   |    CN98_4     |   CN3_28   | D11      |  O  | SD_MOSI, TFT_MOSI (ILI9341: SDI, sampled at rising edge of SCL)
        PWM29/P11_4   |    CN98_5     |   CN3_30   | D12      |  I  | SD_MISO, TFT_MISO (ILI9341: SDO, changed with falling edge of SCL)
        PWM28/P11_3   |    CN98_6     |   CN3_29   | D13      |  O  | SD_SCK, TFT_SCK (ILI9341: SCL)

        ADC2/AP0_2    |    CN100_1    |   CN1_109  | A0       | I/O | Y-
        ADC3/AP0_3    |    CN100_2    |   CN1_110  | A1       | I/O | X-
        ADC4/AP0_4    |    CN100_3    |   CN1_111  | A2       | I/O | Y+
        ADC5/AP0_5    |    CN100_4    |   CN1_112  | A3       | I/O | X+ (33k pull-up resistor to +3.3V must be added)
        IIC0SDA/P10_2 |    CN100_5    |   CN1_25   | A4       | I/O | unused
        IIC0SCL/P10_3 |    CN100_6    |   CN1_23   | A5       | I/O | unused

        P8_4          |    CN101_6    |   CN1_89   | SYS_05   |  O  | Reset

ILI9341 is configured for 4-wire 8-bit data serial interface II (IM[3:0]=1110, separate SDI/SDO)

Note that V0.1 board (only used Renesas internally) has the following differences:

        Port          | NWB_F1K Board | PiggyBoard | Arduino  | I/O | used for
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        PWM33/P9_4    |    CN88_6     |   CN3_34   | D5       |  O  | TFT_NCS (ILI9341: CSX, active low)
        PWM33/P9_4    |    CN98_3     |   CN3_34   | D10      |  O  | TFT_NCS (ILI9341: CSX, active low)
        P8_4          |    CN101_6    |   CN1_89   | SYS_05   |  O  | not connected


*/

#ifndef BSP_TGMN
#define BSP_TGMN

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       Includes                                                                                                        |
+-----------------------------------------------------------------------------------------------------------------------+
*/
#include <ree_types.h>
#include <map_device.h>
#include <iodefine.h>

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       Defines                                                                                                         |
+-----------------------------------------------------------------------------------------------------------------------+
*/
#define PIN0_bm  0x0001
#define PIN1_bm  0x0002
#define PIN2_bm  0x0004
#define PIN3_bm  0x0008
#define PIN4_bm  0x0010
#define PIN5_bm  0x0020
#define PIN6_bm  0x0040
#define PIN7_bm  0x0080
#define PIN8_bm  0x0100
#define PIN9_bm  0x0200
#define PIN10_bm 0x0400
#define PIN11_bm 0x0800
#define PIN12_bm 0x1000
#define PIN13_bm 0x2000
#define PIN14_bm 0x4000
#define PIN15_bm 0x8000
#define LOW_BYTE_bm 0x00ff
#define HIGH_BYTE_bm 0xff00
#define BOTH_BYTE_bm 0xffff

#define TFT_SDI PIN2_bm /* port 11_2 (out) */
#define TFT_SCK PIN3_bm /* port 11_3 (out) */
#define TFT_SDO PIN4_bm /* port 11_4 (in) */
#define TFT_DNC PIN0_bm /* port 11_0 (out) */
#define TFT_RES PIN4_bm /* port 8_4 (out) */
#define TFT_LED PIN6_bm /* port 8_6 (out) */
#ifdef NWB_V01
#define TFT_NCS PIN4_bm /* port 9_4 (out) */
#define BITBANG /* only bit-bang mode supported, CSIH is not connected */
#else
#define TFT_NCS PIN2_bm /* port 9_2 (out) */
#endif
#define SD_NCS  PIN1_bm /* port 9_1 (out) */

#define TP_YM PIN2_bm   /* YM: AP0_2 */
#define TP_XM PIN3_bm   /* XM: AP0_3 */
#define TP_YP PIN4_bm   /* YP: AP0_4 */
#define TP_XP PIN5_bm   /* XP: AP0_5 */

#define TP_ALL (TP_YM | TP_XM | TP_YP | TP_XP)

#define AP_TP PORTAP0
#define APSR_TP PORTAPSR0
#define APPR_TP PORTAPPR0
#define APM_TP PORTAPM0
#define APNOT_TP PORTAPNOT0
#define APMSR_TP PORTAPMSR0
#define APIBC_TP PORTAPIBC0
#define APBDC_TP PORTAPBDC0

/* In simulation, a syncm follows any port operation. It simplifies debugging as it waits for the write data to arrive at the peripheral.
   For running on the real device, the syncm should be removed, as it slows the operation unnecessarily. */
//#ifdef SIMULATION
//#define SYNC do {__asm("syncm") ;} while(0) ;
//#else
#define SYNC
//#endif

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       structs and enums                                                                                               |
+-----------------------------------------------------------------------------------------------------------------------+
*/
typedef struct timerstruct {
        struct timerstruct *next ; /* pointer to next timer */
        volatile uint32_t timer ;  /* timer */
        volatile bool expired ;    /* set by interrupt handler if timer has just expired */
        } TIMER_TYPE ;

typedef struct current_monitor {
        bool valid ;       /* true if this block is valid */
        int32_t shunt ;    /* shunt voltage in 礦 */
        int32_t bus ;      /* bus voltage in mV */
        int32_t current ;  /* shunt current in 礎 */
        int32_t power ;    /* power in mW */
        } CM_TYPE ;

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       Function prototypes                                                                                             |
+-----------------------------------------------------------------------------------------------------------------------+
*/
void hw_init(void) ;
void hw_init_pe2(void) ;
void get_ui33(CM_TYPE *cm) ;
void get_ui125(CM_TYPE *cm) ;
uint8_t i2c_read8(uint8_t addr) ;
uint16_t i2c_read16(uint8_t addr) ;
bool i2c_write8(uint8_t addr, uint8_t pointer, uint8_t data) ;
bool i2c_write16(uint8_t addr, uint8_t pointer, uint16_t data) ;
bool i2c_setptr(uint8_t addr, uint8_t pointer) ;
void check_rotenc(void) ;
void buzzer_time(int freq, int volume, int duration) ;
void buzzer_init(void) ;
unsigned long get_freerun_timer_clocks(void);

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       external variables                                                                                              |
+-----------------------------------------------------------------------------------------------------------------------+
*/
#ifdef DECLARE_VARS
unsigned int adresult ;
uint32_t ostm_timer ;
#else
extern unsigned int adresult ;
extern uint32_t ostm_timer ;
#endif

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       global variables                                                                                                |
+-----------------------------------------------------------------------------------------------------------------------+
*/
volatile uint16_t resXM, resXP, resYM, resYP ;

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       inline functions                                                                                                |
+-----------------------------------------------------------------------------------------------------------------------+
*/
/* OSTM1 is configured as free running counter, which is clocked by 60 MHz PCLK (=CPUCLK2=CPUCLK/2=60MHz)).
   Therefore one clock tick is 16.667 ns, 6 ticks take 100 ns. */
#pragma inline stimer,gtimer
void stimer(void) {
	/* save OSTM1 counter */
	ostm_timer = OSTM1.CNT ;
}

uint32_t gtimer(void) {
	/* get number of OSTM1 clocks since last call to stimer() */
	return(OSTM1.CNT - ostm_timer) ;
}

#pragma inline active_wait_ns,active_wait_us,active_wait_ms
void active_wait_ns(uint32_t delay){
	/* active wait for <delay> ns. */
#ifndef SIMULATION
	uint32_t target_count ;
	uint32_t current_count ;
	uint32_t start_count ;
	bool wait_for_overflow ;
	start_count = OSTM1.CNT ;
	target_count = start_count + (delay * 6) / 100 ; /* OSTM1.CNT clocks (60 MHz, 16.7ns) */
	if (target_count >= start_count)
	   wait_for_overflow = false ; /* target_count is higher than start_count */
	else
	   wait_for_overflow = true ; /* target_count is lower than start_count -> must wait for counter overflow */
	do {current_count = OSTM1.CNT ;}
	while ( ((!wait_for_overflow) &&  (current_count < target_count) && (current_count >= start_count))
		 || (( wait_for_overflow) && ((current_count < target_count) || (current_count >= start_count))) ) ;
#endif
}

void active_wait_us(uint32_t delay){
	/* active wait for <delay> 祍. */
#ifndef SIMULATION
	uint32_t i ;
	for (i=0;i<delay;i++) active_wait_ns(1000) ;
#endif
 }

void active_wait_ms(uint32_t delay){
	/* active wait for <delay> ms. */
#ifndef SIMULATION
	extern volatile uint32_t timer_1ms ; /* will be incremented once per ms */
	if (delay != 0)
	{ /* skip if no delay required */
	   timer_1ms = 0 ;
	   while (timer_1ms < delay) ;
	}
#endif
}

#pragma inline TFT_PORTCONFIG
void TFT_PORTCONFIG(void)
{
	/* Configure ports for TFT panel */
	PORTPMSR8   = ((TFT_RES | TFT_LED) << 16) | (0) ; /* set to input/output */
	PORTPSR8    = ((TFT_RES | TFT_LED) << 16) | (0) ; /* both are initially low */
	PORTPMCSR8  = ((TFT_RES | TFT_LED) << 16) | (0) ; /* use port mode */

	PORTPMSR9   = ((TFT_NCS | SD_NCS) << 16) | (0) ; /* set to input/output */
	PORTPSR9    = ((TFT_NCS | SD_NCS) << 16) | (TFT_NCS | SD_NCS) ; /* both initially high */
	PORTPMCSR9  = ((TFT_NCS | SD_NCS) << 16) | (0) ; /* use port mode */

	#ifdef BITBANG
	PORTPMSR11  = ((TFT_SDI | TFT_SCK | TFT_SDO | TFT_DNC) << 16) | (TFT_SDO) ; /* set to input/output */
	PORTPSR11   = ((TFT_SDI | TFT_SCK | TFT_SDO | TFT_DNC) << 16) | (0) ; /* all initially low */
	PORTPMCSR11 = ((TFT_SDI | TFT_SCK | TFT_SDO | TFT_DNC) << 16) | (0) ; /* use port mode */
	#else
	PORTPFCAE11 &= ~(TFT_SDI | TFT_SCK | TFT_SDO) ; /* set alternative mode 1 */
	PORTPFCE11  &= ~(TFT_SDI | TFT_SCK | TFT_SDO) ; /* set alternative mode 1 */
	PORTPFC11   &= ~(TFT_SDI | TFT_SCK | TFT_SDO) ; /* set alternative mode 1 */
	PORTPM11    &= ~(TFT_SDI | TFT_SCK          ) ; /* set output mode */
	PORTPM11    |=  (                    TFT_SDO) ; /* set input mode */
	PORTPMC11   |=  (TFT_SDI | TFT_SCK | TFT_SDO) ; /* set alternative mode */
	PORTPIPC11  |=  (          TFT_SCK          ) ; /* I/O mode is selected by the peripheral function (direct I/O control) */

	PORTPM11   &= ~(TFT_DNC) ;  /* TFT_DNC is output */
	PORTP11    |=  (TFT_DNC) ;  /* TFT_DNC is initially high */
	PORTPMC11  &= ~(TFT_DNC) ;  /* use port mode */

	/* Initialize CSIH */
	CSIH2CTL0   =  ((1 <<  7)    /* Bit7  - 0: Stop Clock, 1: Supply operation clock */
				   |(1 <<  6)    /* Bit6  - 0: Transmission disabled, 1: Transmission enabled */
				   |(0 <<  5)    /* Bit5  - 0: Reception disabled, 1: Reception enabled */
				   |(0 <<  1)    /* Bit1  - 0: Communication stop is not requested, 1: Stops communication */
				   |(0 <<  0)) ; /* Bit0  - 0: Memory mode, 1: direct access mode */

	CSIH2CTL1   =  ((1 << 24)    /* Bit24 - 0: internal synchronization timing for receive data input is rising edge of PCLK */
				   |(0 << 18)    /* Bit18 - 0: The CPU-controlled high-priority communication function is disabled */
				   |(0 << 17)    /* Bit17 - 0: The default level of CSIHTSCK is high */
				   |(0 << 16)    /* Bit16 - 0: Normal interrupt timing (interrupt is generated after the transfer) */
				   |(0 << 15)    /* Bit15 - 0: Chip select is active low. */
				   |(0 << 14)    /* Bit14 - 0: Chip select is active low. */
				   |(0 << 13)    /* Bit13 - 0: Chip select is active low. */
				   |(0 << 12)    /* Bit12 - 0: Chip select is active low. */
				   |(0 << 11)    /* Bit11 - 0: Chip select is active low. */
				   |(0 << 10)    /* Bit10 - 0: Chip select is active low. */
				   |(0 <<  9)    /* Bit9  - 0: Chip select is active low. */
				   |(0 <<  8)    /* Bit8  - 0: Chip select is active low. */
				   |(0 <<  7)    /* Bit7  - 0: Disables extended data length mode */
				   |(0 <<  6)    /* Bit6  - 0: Disables job mode. */
				   |(0 <<  5)    /* Bit5  - 0: Disables data consistency check. */
				   |(1 <<  4)    /* Bit4  - 1: Chip select signal returns to the inactive level after last data transfer */
				   |(0 <<  3)    /* Bit3  - 0: Deactivates loop-back mode (LBM) */
				   |(0 <<  2)    /* Bit2  - 0: No interrupt delay mode */
				   |(0 <<  1)    /* Bit1  - 0: Disables the handshake function. */
				   |(0 <<  0)) ; /* Bit0  - 0: disables the slave select function. */
	CSIH2CTL2   = (0x1<<13) ;    /* Clock selection: PCLK / 2 */
	CSIH2STCR0  = ((1 << 15)     /* Bit15 - 1: Clears the time-out error flag */
				  |(1 << 14)     /* Bit14 - 1: Clears the overflow error flag */
				  |(1 <<  8)     /* Bit8  - 1: Clears the FIFO buffer pointers */
				  |(1 <<  3)     /* Bit3  - 1: Clears the data consistency error flag */
				  |(1 <<  1)     /* Bit1  - 1: Clears the parity error flag */
				  |(1 <<  0)) ;  /* Bit0  - 1: Clears the overrun error flag */
	CSIH2MCTL0  = ((0x0 <<8)     /* Bit[9:8] - 00: FIFO mode, 01: Dual buffer mode, 10: Transmit only buffer mode, 11: prohibited */
				  |(0x00<<0)) ;  /* Bit[4:0] - 00000: no timeout, 00001: Time-out is (1 � 8 � BRG output clocks), ... 11111: Time-out is (31 � 8 � BRG output clocks) */
	CSIH2MRWP0  = 0x00000000 ;   /* reset read and write pointers */
	CSIH2BRS0   = 0x0004 ;       /* PCLK / (2^a � 2 � 2) = PCLK/16 = 2.5MHz */
	CSIH2CFG0   = ((0x0<<30)     /* The transfer clock frequency is set according to the CSIHnBRS0 setting. */
				  |(0x0<<28)     /* Does not transmit any parity bit. */
				  |(0x8<<24)     /* 8 bit data length */
				  |(  0<<19)     /* Dominant (higher priority) */
				  |(  0<<18)     /* MSB first */
				  |(0x3<<16)     /* set clock/data phase */
				  |(  0<<15)     /* Selects the idle enforcement configuration for chip select signal */
				  |(0x0<<12)     /* Selects the idle time for chip select signal */
				  |(0x0<< 8)     /* Specifies the hold time for chip select signal x in transmission clock cycles. */
				  |(0x0<< 4)     /* Specifies the inter-data time for chip select signal x in transmission clock cycles. */
				  |(0x0<< 0)) ;  /* Specifies the setup time for chip select signal x in transmission clock cycles. */
	#endif
	SYNC ;
}

#pragma inline TFT_RST_low.TFT_RST_high
void TFT_RST_low(void)  {PORTPSR8    = ((TFT_RES) << 16) | (0)       ; SYNC ;}  /* RST low */
void TFT_RST_high(void) {PORTPSR8    = ((TFT_RES) << 16) | (TFT_RES) ; SYNC ;}  /* RST high */

#pragma inline TFTSET_CS,TFTSET_NCS,TFTSET_CMD,TFTSET_DATA,TFT_DAT_set,TFT_DAT_get
void TFTSET_CS(void)    {PORTPSR9    = ((TFT_NCS) << 16) | (0)       ; SYNC ;}  /* CS active */
void TFTSET_NCS(void)   {PORTPSR9    = ((TFT_NCS) << 16) | (TFT_NCS) ; SYNC ;}  /* CS inactive */
void TFTSET_CMD(void)   {PORTPSR11   = ((TFT_DNC) << 16) | (0)       ; SYNC ;}  /* DAT low (control) */
void TFTSET_DATA(void)  {PORTPSR11   = ((TFT_DNC) << 16) | (TFT_DNC) ; SYNC ;}  /* DAT high (data) */
void TFT_DAT_set(uint16_t data) {PORTPSR11   = ((TFT_SDI) << 16) | (data) ; SYNC ;}  /* set DAT */
uint_least8_t TFT_DAT_get(void) {return((PORTPPR11&TFT_SDO)==0?0:1) ; SYNC ;}  /* get bit from TFT */

#pragma inline TFT_SCK_low,TFT_SCK_high,TFT_LED_on,TFT_LED_off
void TFT_SCK_low(void)  {PORTPSR11   = ((TFT_SCK) << 16) | (0)       ; SYNC ;}  /* SCK low */
void TFT_SCK_high(void) {PORTPSR11   = ((TFT_SCK) << 16) | (TFT_SCK) ; SYNC ;}  /* SCK high */
void TFT_LED_on(void)   {PORTPSR8    = ((TFT_LED) << 16) | (TFT_LED) ; SYNC ;}  /* LED on */
void TFT_LED_off(void)  {PORTPSR8    = ((TFT_LED) << 16) | (0)       ; SYNC ;}  /* LED off */

/* The following functions send one byte to the TFT panel.
   ILI9341 is configured for 4-wire 8-bit data serial interface (IM[3:0]=1110).
   Control signals (NCS and DNC) are not handled here and must be set or cleared before the send byte function is called */
#pragma inline TFT_SENDBYTE
void TFT_SENDBYTE(uint8_t data)
                             { /* Send one byte to the TFT panel. */
#ifdef BITBANG
                                uint8_t mask ;
                                TFT_SCK_low() ;
                                for (mask=0x80; mask!=0; mask>>=1)
                                {
                                   TFT_DAT_set(((data&mask)!=0)?0xffff:0) ;
                                   TFT_SCK_high() ;
                                   TFT_SCK_low() ;
                                }
#else
                                while ((CSIH2STR0 & (1 << 5)) != 0) ; /* Wait while FIFO is full (CSIHnFLF flag) */
                                CSIH2TX0W  = 0x00FE0000 | data ; /* CSIH2 Transmission Data Register
                                                                    Bit 16 : 0 activates chip select signal S0
                                                                    Bit 0-15   Transmission Data */
#endif
                             }

#ifdef BITBANG
#pragma inline WAIT_SENDCOMPLETE
__inline void WAIT_SENDCOMPLETE(void) { /* do nothing */ }
#else
#pragma inline WAIT_SENDCOMPLETE
void WAIT_SENDCOMPLETE(void) { while (CSIH2STR0 & (1 << 7)) ; /* wait until transmission completed (CSIHnTSF flag) */ }
#endif

#pragma inline TFT_SENDCMD,TFT_SENDDATA,TFT_RECEIVEBYTE
void TFT_SENDCMD(uint8_t cmd)
                             { /* send a command to the TFT display */
                                TFTSET_CMD() ;  /* prepare sending a command */
                                TFTSET_CS() ;   /* CS active */
                                TFT_SENDBYTE(cmd) ;   /* Send command */
                                WAIT_SENDCOMPLETE() ; /* wait for completion */
                                TFTSET_NCS() ;  /* CS inactive */
                             }

void TFT_SENDDATA(uint8_t data)
                             { /* send data to the TFT display */
                                TFTSET_DATA() ; /* prepare sending data */
                                TFTSET_CS() ;   /* CS active */
                                TFT_SENDBYTE(data) ;  /* Send data */
                                WAIT_SENDCOMPLETE() ; /* wait for completion */
                                TFTSET_NCS() ;  /* CS inactive */
                             }

uint8_t TFT_RECEIVEBYTE(void)
                             { /* Receive one byte from the TFT panel, ILI9341 is configured for 4-wire 8-bit data serial interface (IM[3:0]=1110)*/
                                uint8_t mask, result ;
                                result = 0 ;
                                for (mask=0x80; mask!=0; mask>>=1)
                                {
                                   TFT_SCK_high() ;
                                   if (TFT_DAT_get() != 0) result |= mask ;
                                   TFT_SCK_low() ;
                                }
                                return(result) ;
                             }

/* Buzzer interface functions (no buzzer available on this board) */
#pragma inline buzzer_intc_off,buzzer_off,buzz_untouch,get_timer1ms
void buzzer_intc_off(void) {} /* Disable PWGA interrupt used for buzzer */
void buzzer_off(void) {} /* disable buzzer output */
void buzz_untouch(void) {} /* freq[Hz], vol[%], duration[ms] */
uint32_t get_timer1ms(void) {extern volatile uint32_t clock_1ms ; return(clock_1ms) ;} /* read 1ms clock timer value */

/* Touch Panel Control by built-in ADC */
/* Functions for built-in ADC */
#pragma inline TPIF_PORTCONFIG
void TPIF_PORTCONFIG(void)
                             { /* Configure ports and ADC for touch panel */
                                APMSR_TP  = (TP_ALL<<16) | TP_ALL ; /* all used analog ports are input for now */
                                APIBC_TP &= ~TP_ALL ;               /* all input buffers disabled for now */

                                ADCA0VCR00 = 0x000000002 ;   /* Bits[5..0]=0 -> Select AP0_2 (YM) as Physical Channel
                                                                Bits[7,6]=00b -> No Upper Limit/Lower Limit  check
                                                                Bit[8]=0 -> disable A/D Conversion End Interrupt Enable
                                                                Bit[9]=0 -> A/D conversion of the hold value is performed during a self-diagnostic
                                                                Bit[14..12]=0 -> do not set the MPX value to be transferred to an external analog multiplexer.
                                                                Bit[15]=0 -> do not enable MPX
                                                             */

                                ADCA0VCR01 = 0x000000003 ;   /* Bits[5..0]=1 -> Select AP0_3 (XM) as Physical Channel
                                                                Bits[7,6]=00b -> No Upper Limit/Lower Limit  check
                                                                Bit[8]=0 -> disable A/D Conversion End Interrupt Enable
                                                                Bit[9]=0 -> A/D conversion of the hold value is performed during a self-diagnostic
                                                                Bit[14..12]=0 -> do not set the MPX value to be transferred to an external analog multiplexer.
                                                                Bit[15]=0 -> do not enable MPX
                                                             */

                                ADCA0VCR02 = 0x000000004 ;   /* Bits[5..0]=0 -> Select AP0_4 (YP) as Physical Channel
                                                                Bits[7,6]=00b -> No Upper Limit/Lower Limit  check
                                                                Bit[8]=0 -> disable A/D Conversion End Interrupt Enable
                                                                Bit[9]=0 -> A/D conversion of the hold value is performed during a self-diagnostic
                                                                Bit[14..12]=0 -> do not set the MPX value to be transferred to an external analog multiplexer.
                                                                Bit[15]=0 -> do not enable MPX
                                                             */

                                ADCA0VCR03 = 0x000000005 ;   /* Bits[5..0]=1 -> Select AP0_5 (XP) as Physical Channel
                                                                Bits[7,6]=00b -> No Upper Limit/Lower Limit  check
                                                                Bit[8]=0 -> disable A/D Conversion End Interrupt Enable
                                                                Bit[9]=0 -> A/D conversion of the hold value is performed during a self-diagnostic
                                                                Bit[14..12]=0 -> do not set the MPX value to be transferred to an external analog multiplexer.
                                                                Bit[15]=0 -> do not enable MPX
                                                             */

                                ADCA0ADCR = 0x00000002 ;     /* Bits[1,0]=10b -> Asynchronous suspend
                                                                Bit[4]=0 -> CTYP: 12-bit mode
                                                                Bit[5]=0 -> CRAC: PWDDR and ADCAnDRj are set to right align
                                                                Bit[7]=0 -> The self-diagnostic voltage circuit is turned off
                                                             */

                                ADCA0SMPCR = 0x00000018 ;    /* Bits[7..0]=00010010b   Set sampling time to 24cycles/40MHz */

                                ADCA0SFTCR = 0x00000010 ;    /* Bit[2]=0 -> Overwrite Error Interrupt disabled
                                                                Bit[3]=0 -> Upper Limit/Lower Limit Error Interrupt disabled
                                                                Bit[4]=1 -> When the A/D conversion result is read, the A/D conversion result is cleared by hardware.
                                                             */

                                ADCA0DGCTL0 = 0x00000000 ;   /* No setting for Self-Diagnostic voltage level */
                                ADCA0DGCTL1 = 0x00000000 ;   /* No channels selected for Self-Diagnostic */

                                ADCA0PDCTL1 = 0x00000000 ;   /* Bits[15..0]=0 -> ANIn[00:15] Pull-down enable is off */
                                ADCA0PDCTL2 = 0x00000000 ;   /* Bits[19..0]=0 -> ANI0[16:35], ANI1[16:23] Pull-down enable is off*/

                                ADCA0SGTSEL1 = 0x00000000 ;  /* Bits[8..0]=0 ->External input HW trigger is disabled */
                                ADCA0SGTSEL2 = 0x00000000 ;  /* Bits[8..0]=0 ->External input HW trigger is disabled */
                                ADCA0SGTSEL3 = 0x00000000 ;  /* Bits[8..0]=0 ->External input HW trigger is disabled */

                                ADCA0SGVCSP1 = 0x00000000 ;  /* Bits[5..0]=0 -> select the virtual channel 0 from which the scan is to be started */
                                ADCA0SGVCEP1 = 0x00000003 ;  /* Bits[5..0]=1 -> select the virtual channel 1 at which the scan is to be ended */
                                ADCA0SGMCYCR1 = 0x00000000 ; /* Bits[1,0]=0 -> specify the number  of times for scanning in multicycle scan mode */

                                ADCA0SGCR1 = 0x00000000 ;    /* Bit[0]=0 -> SGx_TRG trigger is disabled
                                                                Bits[3,2]=0 -> Channel repeat times is one
                                                                Bit[4]=1 -> INT_SGx is output when the scan for SGx ends
                                                                Bit[5]=0 -> Multicycle scan mode
                                                             */
                             }
#pragma inline SET_TOUCHP_XI_YREF,SET_TOUCHP_YI_XREF,SET_TOUCHP_XI_Y0,START_TOUCHP_ADC
void SET_TOUCHP_XI_YREF(void)
                             { /* set XM/XP input, YM/YP reference voltage */
                                APMSR_TP  = (TP_ALL<<16) | TP_XM | TP_XP ;  /* XM/XP are input, YM/YP output */
                                APIBC_TP &= ~(TP_XM | TP_XP) ;              /* disable XM/XP input buffers (we measure an analogue input voltage with the ADC) */
                                APSR_TP   = ((TP_YM | TP_YP)<<16) | TP_YM ; /* set YM = high, YP = low */
                                SYNC ;
                             }

void SET_TOUCHP_YI_XREF(void)
                             { /* set YM/YP input, XM/XP reference voltage */
                                APMSR_TP  = (TP_ALL<<16) | TP_YM | TP_YP ;  /* YM/YP are input, XM/XP output */
                                APIBC_TP &= ~(TP_YM | TP_YP) ;              /* disable YM/YP input buffers (we measure an analogue input voltage with the ADC) */
                                APSR_TP   = ((TP_XM | TP_XP)<<16) | TP_XP ; /* set XM = low, XP = high */
                                SYNC ;
                             }

void SET_TOUCHP_XI_Y0(void)
                             { /* set XM/XP input, YM/YP to ground */
                                APMSR_TP  = (TP_ALL<<16) | TP_XM | TP_XP ;  /* XM/XP are input, YM/YP output */
                                APIBC_TP |= (TP_XM | TP_XP) ;               /* enable XM/XP input buffers (used in digital mode to detect touching) */
                                APSR_TP   = ((TP_YM | TP_YP)<<16) ;         /* set YM/YP = low */
                                SYNC ;
                             }

void START_TOUCHP_ADC(void)
                             { /* Start Touch Panel ADC for XP and YP measurement */
                                ADCA0SGSEFCR1 = 1 ; /* clear SG1 End Flag */
                                ADCA0SGSTCR1 = 1 ;  /* Start Conversion of SG1 */
                                SYNC ;
                             }
#pragma inline GET_TOUCHP_ADC_X,GET_TOUCHP_ADC_Y,TOUCHP_CONVERTING
uint16_t GET_TOUCHP_ADC_X(void)
                             { /* Read Touch Panel ADC X result (measured on YM/YP) */
                                return((ADCA0DIR00+ADCA0DIR02)/2) ;
                             }

uint16_t GET_TOUCHP_ADC_Y(void)
                             { /* Read Touch Panel ADC Y result (measured on XM/XP) */
                                return((ADCA0DIR01+ADCA0DIR03)/2) ;
                             }

bool TOUCHP_CONVERTING(void)
                             { /* Check if conversion has finished. Return true otherwise. */
                                return((ADCA0SGSTR & 0x200) != 0) ; /* check SGACT flag for SG1 */
                             }

#pragma inline READ_TP_XP,READ_TP_XM,READ_TP_YP,READ_TP_YM
uint8_t READ_TP_XP(void) {return (((APPR_TP & TP_XP) == 0) ? 1 : 0) ;} /* binary read XP */
uint8_t READ_TP_XM(void) {return (((APPR_TP & TP_XM) == 0) ? 1 : 0) ;} /* binary read XM */
uint8_t READ_TP_YP(void) {return (((APPR_TP & TP_YP) == 0) ? 1 : 0) ;} /* binary read YP */
uint8_t READ_TP_YM(void) {return (((APPR_TP & TP_YM) == 0) ? 1 : 0) ;} /* binary read YM */

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       Defines                                                                                                         |
+-----------------------------------------------------------------------------------------------------------------------+
*/
#ifdef WIN32 /* Visual C */
#define GET_CONST_BYTE(addr) ((unsigned char) *(addr))          /* get byte from constant memory (flash) */
#define GET_CONST_SHORT(addr) ((unsigned short) *(addr))        /* get two bytes from constant memory (flash) */
#define CONST_MEM const         /* data in program memory */
#define CONST_MEMP const*       /* pointer to data in program memory */
/* critical section management is not required for Windows. Events are serialized by "SetEvent" and "WaitForSingleObject" */
__inline int8_t atomic_rw_bool(volatile int8_t *src, int8_t newval) {int8_t tmp ; tmp = *src ; *src = newval ; return tmp ;}
__inline int8_t atomic_rw_int8(volatile int8_t *src, int8_t newval) {int8_t tmp ; tmp = *src ; *src = newval ; return tmp ;}
__inline uint16_t atomic_rw_uint16(volatile uint16_t *src, uint16_t newval) {uint16_t tmp ; tmp = *src ; *src = newval ; return tmp ;}
__inline int    atomic_rw_int (volatile int    *src, int newval)    {int tmp    ; tmp = *src ; *src = newval ; return tmp ;}
__inline unsigned int SCS() {return (0) ;} /* start critical section (do nothing, critical section management is not required for Windows) */
__inline void ECS(unsigned int istat) {return ;} /* end critical section (do nothing) */
typedef int32_t winprocparm_t ; /* parameter type of windows procedures */
typedef int32_t winprocret_t ;  /* return type of windows procedures */
typedef int32_t displayprocparm_t ; /* parameter type of display procedures */
typedef int32_t displayprocret_t ;  /* return type of display procedures */
#endif

#ifdef __ghs__ /* Green Hills */
#define GET_CONST_BYTE(addr) ((unsigned char) *(addr))          /* get byte from constant memory (flash) */
#define GET_CONST_SHORT(addr) ((unsigned short) *(addr))        /* get two bytes from constant memory (flash) */
#define CONST_MEM const         /* data in program memory */
#define CONST_MEMP const*       /* pointer to data in program memory */
typedef int32_t winprocparm_t ; /* parameter type of windows procedures */
typedef int32_t winprocret_t ;  /* return type of windows procedures */
typedef int32_t displayprocparm_t ; /* parameter type of display procedures */
typedef int32_t displayprocret_t ;  /* return type of display procedures */
#ifdef NWB_F1K_V2 /* __RIR() does not work in User Mode on this device */
__inline bool atomic_rw_bool(volatile bool *src, bool newval) {bool tmp ; __DI() ; tmp = *src ; *src = newval ; __EI() ; return tmp ;}
__inline unsigned int SCS() {__DI() ; return(0) ;} /* start critical section (disable interrupts) */
__inline void ECS(unsigned int istat) {__EI() ; return ;} /* end critical section (enable interrupts unconditionally!) */
#else
__inline bool atomic_rw_bool(volatile bool *src, bool newval) {bool tmp ; unsigned int istat ; istat = __DIR() ; tmp = *src ; *src = newval ; __RIR(istat) ; return tmp ;}
__inline unsigned int SCS() {return __DIR() ;} /* start critical section (disable interrupts) */
__inline void ECS(unsigned int istat) {__RIR(istat) ; return ;} /* end critical section (restore interrupts) */
#endif /* NWB_F1K_V2 */
#endif

#ifdef AVR /* Atmel Studio */
#define GET_CONST_BYTE(addr) (pgm_read_byte(addr))              /* get byte from constant memory (flash) */
#define GET_CONST_SHORT(addr) (pgm_read_word(addr))             /* get word (two bytes) from constant memory (flash) */
#define CONST_MEM const PROGMEM         /* data in program memory */
#define CONST_MEMP const* PROGMEM      /* pointer to data in program memory */
typedef int8_t winprocparm_t ;  /* parameter type of windows procedures */
typedef int8_t winprocret_t ;  /* return type of windows procedures */
typedef int8_t displayprocparm_t ; /* parameter type of display procedures */
typedef int8_t displayprocret_t ;  /* return type of display procedures */
__inline bool   atomic_rw_bool(volatile bool   *src, bool   newval) {bool   tmp ; __asm("cli") ; tmp = *src ; *src = newval ; __asm("sei") ; return tmp ;}
__inline int8_t atomic_rw_int8(volatile int8_t *src, int8_t newval) {int8_t tmp ; __asm("cli") ; tmp = *src ; *src = newval ; __asm("sei") ; return tmp ;}
__inline uint16_t atomic_rw_uint16(volatile uint16_t *src, uint16_t newval) {uint16_t tmp ; __asm("cli") ; tmp = *src ; *src = newval ; __asm("sei") ; return tmp ;}
__inline int    atomic_rw_int (volatile int    *src, int    newval) {int    tmp ; __asm("cli") ; tmp = *src ; *src = newval ; __asm("sei") ; return tmp ;}

/* SCS/ECS to be fixed later. ECS should restore the previous interrupt status! */
__inline unsigned int SCS() {__asm("cli") ; return (0) ;} /* start critical section (disable interrupts) */
__inline void ECS(unsigned int istat) {__asm("sei") ; return ;} /* end critical section (restore interrupts) */
#endif


/*
+-----------------------------------------------------------------------------------------------------------------------+
|       structs and enums                                                                                               |
+-----------------------------------------------------------------------------------------------------------------------+
*/

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       Function prototypes                                                                                             |
+-----------------------------------------------------------------------------------------------------------------------+
*/

/*
+-----------------------------------------------------------------------------------------------------------------------+
|       global variables                                                                                                |
+-----------------------------------------------------------------------------------------------------------------------+
*/

#endif

