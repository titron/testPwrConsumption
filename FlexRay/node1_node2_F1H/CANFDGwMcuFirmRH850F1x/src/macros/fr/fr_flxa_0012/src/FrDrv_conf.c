
//============================================================================
// PROJECT  : REE FlexRay driver
// MODULE   : FrDrv_conf.c
// VERSION  : 0.2
// DATE     : 02.10.2013, 10:55:09
//============================================================================
//                           C O P Y R I G H T
//============================================================================
// Copyright (c) 2013 by REE Electronics (Europe) GmbH. All rights reserved.
// Arcadiastr. 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by REE, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. REE shall not have any obligation to maintain,
// service or provide bug fixes for the supplied Product(s) and/or the
// Application.
//
// Each User is solely responsible for determining the appropriateness of
// using the Product(s) and assumes all risks associated with its exercise
// of rights under this Agreement, including, but not limited to the risks
// and costs of program errors, compliance with applicable laws, damage to
// or loss of data, programs or equipment, and unavailability or
// interruption of operations.
//
// Limitation of Liability :
// In no event shall REE be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. REE shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by REE in connection with the Product(s) and/or the
// Application.
//
//============================================================================
// Enviroment : Devices    : RH850/P1x-C
//              Assembler  : GHS Multi              Version : 6.1.4
//              C-Compiler : GHS Multi              Version : 6.1.4
//              Linker     : GHS Multi              Version : 6.1.4       
//              Debugger   : GHS Multi              Version : 6.1.4
//============================================================================
// Version    Author                       Description
// 0.1        H. Schmerling                Initial Release
// 0.2        p. Szczupak                  Adapted for P1x-C device
//============================================================================

//============================================================================
// Includes
//============================================================================

#include <map_ports.h>
//#include <ports\standardports\standardports_p.h>
#include <standardports_p.h>

#include "interrupt_reg.h"
#include "FrDrv.h"
#include "GlobalDefines.h"
#include "TypeDefines.h"

#include "cluster.h"        // "REE E-Ray Configurator" global file

#ifdef Application_1
#define FLEXRAY_CHI_INIT_VARS
#include "Node_1.h"         // "REE E-Ray Configurator" node file
#undef FLEXRAY_CHI_INIT_VARS
#endif

#ifdef Application_2
#define FLEXRAY_CHI_INIT_VARS
#include "Node_2.h"         // "REE E-Ray Configurator" node file
#undef FLEXRAY_CHI_INIT_VARS
#endif

#ifdef Application_3
#define FLEXRAY_CHI_INIT_VARS
#include "Node_3.h"         // "REE E-Ray Configurator" node file
#undef FLEXRAY_CHI_INIT_VARS
#endif

//============================================================================
// Prototypes
//============================================================================
void FrDrv_CC_init ( void );
Fr_ReturnType FrDrv_Config_LLParams ( void );
Fr_ReturnType FrDrv_Config_PhysicalBuffers ( void );

extern void FrDrv_EnterConfigMode ( void );
extern u32 FrDrv_read_32bit ( u32 addr_u32 );
extern void FrDrv_write_32bit ( u32 addr, u32 data_u32 );
extern u16 FrDrv_read_16bit ( u32 addr_u32 );
extern u32 FrDrv_crc ( u08 mb_u08 );
//============================================================================
// Global variables
//============================================================================
u32 eies_reg_u32;
u32 sies_reg_u32;
extern const u16 BufferHeader_u16[128][10];
/* start @titron */
s_busload_paras testModeParas[FLX_TEST_TOTAL_MODE_NUM]={
{
	/* INDEX_SFDL_1_BUSLOAD_100_PERCENT */
	15,
	6000,
	150,
	144,
	148,
	1284,
	1,
	1,
	0x00
},
{
	/* INDEX_SFDL_2_BUSLOAD_100_PERCENT */
	17,
	6800,
	170,
	164,
	168,
	1484,
	2,
	1,
	0x00
},
{
	/* INDEX_SFDL_127_BUSLOAD_100_PERCENT */
	//254bytes
	267,
	106800,
	2670,
	2600,
	2665,
	26000,
	127,
	64,
	0x00
}
};
/* end @titron */

//============================================================================
// Functions
//============================================================================
void FrDrv_CC_Port_init(void){
  /* Transceiver pin init */
#ifdef EE_FR_PORT_ENA
  PORT_Enable( EE_FR_PORT_ENA, EE_FR_PORT_BIT_ENA,
               PORT_DIR_OUTPUT, PORT_MODE_IO, 
               PORT_FUNCTION_NORMAL );
  PORT_WriteBit( EE_FR_PORT_ENA, EE_FR_PORT_BIT_ENA, 1 );
#endif

#ifdef EE_FR_PORT_WAKEA
  PORT_Enable( EE_FR_PORT_WAKEA, EE_FR_PORT_BIT_WAKEA,
               PORT_DIR_OUTPUT, PORT_MODE_IO, 
               PORT_FUNCTION_NORMAL );
  PORT_WriteBit( EE_FR_PORT_WAKEA, EE_FR_PORT_BIT_WAKEA, 1 );
#endif

#ifdef EE_FR_PORT_BGEA
  PORT_Enable( EE_FR_PORT_BGEA, EE_FR_PORT_BIT_BGEA,
               PORT_DIR_OUTPUT, PORT_MODE_IO, 
               PORT_FUNCTION_NORMAL );
  PORT_WriteBit( EE_FR_PORT_BGEA, EE_FR_PORT_BIT_BGEA, 1 );
#endif

#ifdef EE_FR_PORT_STBNA
  PORT_Enable( EE_FR_PORT_STBNA, EE_FR_PORT_BIT_STBNA,
               PORT_DIR_OUTPUT, PORT_MODE_IO, 
               PORT_FUNCTION_NORMAL );
  PORT_WriteBit( EE_FR_PORT_STBNA, EE_FR_PORT_BIT_STBNA, 1 );
#endif

#ifdef EE_FR_PORT_ENB
  PORT_Enable( EE_FR_PORT_ENB, EE_FR_PORT_BIT_ENB,
               PORT_DIR_OUTPUT, PORT_MODE_IO, 
               PORT_FUNCTION_NORMAL );
  PORT_WriteBit( EE_FR_PORT_ENB, EE_FR_PORT_BIT_ENB, 1 );
#endif

#ifdef EE_FR_PORT_WAKEB
  PORT_Enable( EE_FR_PORT_WAKEB, EE_FR_PORT_BIT_WAKEB,
               PORT_DIR_OUTPUT, PORT_MODE_IO, 
               PORT_FUNCTION_NORMAL );
  PORT_WriteBit( EE_FR_PORT_WAKEB, EE_FR_PORT_BIT_WAKEB, 1 );
#endif

#ifdef EE_FR_PORT_BGEB
  PORT_Enable( EE_FR_PORT_BGEB, EE_FR_PORT_BIT_BGEB,
               PORT_DIR_OUTPUT, PORT_MODE_IO, 
               PORT_FUNCTION_NORMAL );
  PORT_WriteBit( EE_FR_PORT_BGEB, EE_FR_PORT_BIT_BGEB, 1 );
#endif

#ifdef EE_FR_PORT_STBNB
  PORT_Enable( EE_FR_PORT_STBNB, EE_FR_PORT_BIT_STBNB,
               PORT_DIR_OUTPUT, PORT_MODE_IO, 
               PORT_FUNCTION_NORMAL );
  PORT_WriteBit( EE_FR_PORT_STBNB, EE_FR_PORT_BIT_STBNB, 1 );
#endif

  /* FlexRay pins */
  PORT_Enable( EE_FR_PORT_TXA, EE_FR_PORT_BIT_TXA,
               PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
               EE_FR_PORT_FUNC_TXA );
  PORT_Enable( EE_FR_PORT_TXENA, EE_FR_PORT_BIT_TXENA,
               PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
               EE_FR_PORT_FUNC_TXENA );
  PORT_Enable( EE_FR_PORT_RXA, EE_FR_PORT_BIT_RXA,
               PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
               EE_FR_PORT_FUNC_RXA );

  PORT_Enable( EE_FR_PORT_TXB, EE_FR_PORT_BIT_TXB,
               PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
               EE_FR_PORT_FUNC_TXB );
  PORT_Enable( EE_FR_PORT_TXENB, EE_FR_PORT_BIT_TXENB,
               PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
               EE_FR_PORT_FUNC_TXENB );
  PORT_Enable( EE_FR_PORT_RXB, EE_FR_PORT_BIT_RXB,
               PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
               EE_FR_PORT_FUNC_RXB );
}

void FrDrv_CC_init ( void ) {
//=============================================================================
// FunctionName: FrDrv_CC_init
// IN: -
// OUT: -
// Description: Initialization of the FlexRay macro
//=============================================================================

  /* Interrupt activation */
  REG_ICFLX0LINE0   = EE_FR_INTLEV_INT0;
  REG_ICFLX0LINE1   = EE_FR_INTLEV_INT1;
  REG_ICFLX0TIM0 = EE_FR_INTLEV_TIMER0;
  REG_ICFLX0TIM1 = EE_FR_INTLEV_TIMER1;
  REG_ICFLX0TIM2 = EE_FR_INTLEV_TIMER2;

  /* Port activation */
  FrDrv_CC_Port_init();

  /*** DEFAULT_CONFIG -> CONFIG @Titron ***/
  FrDrv_EnterConfigMode ( );
  FrDrv_Config_LLParams ( );
  FrDrv_Config_PhysicalBuffers ( );

  eies_reg_u32 = FrDrv_read_32bit ( EIES_REG );
  sies_reg_u32 = FrDrv_read_32bit ( SIES_REG );
} 


Fr_ReturnType FrDrv_Config_LLParams ( void ) {
//=============================================================================
// FunctionName: FrDrv_Config_LLParams
// IN : -
// OUT : REE FlexRay return value
// Description : Basic parameter configuration
//=============================================================================
  u32 value_u32;

  // IR, EILS - Error Interrupt Line Select  0x0028
  value_u32 = 0;
  value_u32 |= ( PEMCL & 0x1 )  ;       // POC Error Mode Changed Interrupt Line            
  value_u32 |= ( CNAL  & 0x1 )  << 1;   // Command Not Accepted Interrupt Line        
  value_u32 |= ( SFBML & 0x1 )  << 2;   // Sync Frames Below Minimum Interrupt Line  
  value_u32 |= ( SFOL  & 0x1 )  << 3;   // Sync Frame Overflow Interrupt Line                 
  value_u32 |= ( CCFL  & 0x1 )  << 4;   // Clock Correction Failure Interrupt Line      
  value_u32 |= ( CCLL  & 0x1 )  << 5;   // CHI Command Locked Interrupt Line
  value_u32 |= ( PERRL & 0x1 )  << 6;   // Parity Error Interrupt Line
  value_u32 |= ( RFOL  & 0x1 )  << 7;   // Receive FIFO Overrun Interrupt Line            
  value_u32 |= ( EFAL  & 0x1 )  << 8;   // Empty FIFO Access Interrupt Line
  value_u32 |= ( IIBAL & 0x1 )  << 9;   // Illegal Input Buffer Access Interrupt Line
  value_u32 |= ( IOBAL & 0x1 )  << 10;  // Illegal Output Buffer Access Interrupt Line
  value_u32 |= ( MHFL  & 0x1 )  << 11;  // Message Handler Constraints Flag Interrupt Line
  value_u32 |= ( EDAL  & 0x1 )  << 16;  // Error Detected on CHA Interrupt Line   
  value_u32 |= ( LTVAL & 0x1 )  << 17;  // Latest Transmit Violation CHA Interrupt Line             
  value_u32 |= ( TABAL & 0x1 )  << 18;  // Transmission Across Boundary Channel A Interrupt Line
  value_u32 |= ( EDBL  & 0x1 )  << 24;  // Error Detected on CHB Interrupt Line       
  value_u32 |= ( LTVBL & 0x1 )  << 25;  // Latest Transmit Violation CHB Interrupt Line           
  value_u32 |= ( TABBL & 0x1 )  << 26;  // Transmission Across Boundary Channel B Interrupt Line
  FrDrv_write_32bit ( EILS_REG, value_u32 );

  // IR, SILS - Status Interrupt Line Select 0x002C
  value_u32 = 0;
  value_u32 |= ( WSTL   & 0x1 ) ;       // Wakeup Status Interrupt Line               
  value_u32 |= ( CASL   & 0x1 ) << 1;   // Collision Avoidance Symbol Interrupt Line                        
  value_u32 |= ( CYCSL  & 0x1 ) << 2;   // Cycle Start Interrupt Line               
  value_u32 |= ( TXIL   & 0x1 ) << 3;   // Transmit Interrupt Line              
  value_u32 |= ( RXIL   & 0x1 ) << 4;   // Receive Interrupt Line             
  value_u32 |= ( RFNEL  & 0x1 ) << 5;   // Receive FIFO Not Empty Interrupt Line                      
  value_u32 |= ( RFCLL  & 0x1 ) << 6;   // Receive FIFO Critical Level Interrupt Line                   
  value_u32 |= ( NMVCL  & 0x1 ) << 7;   // Network Management Vector Changed Interrupt Line                         
  value_u32 |= ( TI0L   & 0x1 ) << 8;   // Timer Interrupt 0 Line             
  value_u32 |= ( TI1L   & 0x1 ) << 9;   // Timer Interrupt 1 Line             
  value_u32 |= ( TIBCL  & 0x1 ) << 10;  // Transfer Input Buffer Completed Line                         
  value_u32 |= ( TOBCL  & 0x1 ) << 11;  // Transfer Output Buffer Completed Line                          
  value_u32 |= ( SWEL   & 0x1 ) << 12;  // Stop Watch Event Interrupt Line                      
  value_u32 |= ( SUCSL  & 0x1 ) << 13;  // Startup Completed Successfully Interrupt Line
  value_u32 |= ( MBSIL  & 0x1 ) << 14;  // Message Buffer Status Interrupt Line   
  value_u32 |= ( SDSL   & 0x1 ) << 15;  // Start of Dynamic Segment Interrupt Line
  value_u32 |= ( WUPAL  & 0x1 ) << 16;  // Wakeup Pattern Channel A  Interrupt Line                           
  value_u32 |= ( MTSAL  & 0x1 ) << 17;  // Media Access Test Symbol Channel A Interrupt Line                      
  value_u32 |= ( WUPBL  & 0x1 ) << 24;  // Wakeup Pattern Channel B Interrupt Line                                          
  value_u32 |= ( MTSBL  & 0x1 ) << 25;  // Media Access Test Symbol Channel B Interrupt Line
  FrDrv_write_32bit ( SILS_REG, value_u32 );

  // IR, EIES - Error Interrupt Enable Set Register 0x0030   
  value_u32 = 0;
  value_u32 |= ( PEMCE & 0x1 )  ;       // POC Error Mode Changed Interrupt Enable            
  value_u32 |= ( CNAE  & 0x1 )  << 1;   // Command Not Accepted Interrupt Enable        
  value_u32 |= ( SFBME & 0x1 )  << 2;   // Sync Frames Below Minimum Interrupt Enable  
  value_u32 |= ( SFOE  & 0x1 )  << 3;   // Sync Frame Overflow Interrupt Enable                 
  value_u32 |= ( CCFE  & 0x1 )  << 4;   // Clock Correction Failure Interrupt Enable      
  value_u32 |= ( CCLE  & 0x1 )  << 5;   // CHI Command Locked Interrupt Enable
  value_u32 |= ( PERRE & 0x1 )  << 6;   // Parity Error Interrupt Enable
  value_u32 |= ( RFOE  & 0x1 )  << 7;   // Receive FIFO Overrun Interrupt Enable            
  value_u32 |= ( EFAE  & 0x1 )  << 8;   // Empty FIFO Access Interrupt Enable
  value_u32 |= ( IIBAE & 0x1 )  << 9;   // Illegal Input Buffer Access Interrupt Enable
  value_u32 |= ( IOBAE & 0x1 )  << 10;  // Illegal Output Buffer Access Interrupt Enable
  value_u32 |= ( MHFE  & 0x1 )  << 11;  // Message Handler Constraints Flag Interrupt Enable
  value_u32 |= ( EDAE  & 0x1 )  << 16;  // Error Detected on CHA Interrupt Enable   
  value_u32 |= ( LTVAE & 0x1 )  << 17;  // Latest Transmit Violation CHA Interrupt Enable             
  value_u32 |= ( TABAE & 0x1 )  << 18;  // Transmission Across Boundary Channel A Interrupt Enable
  value_u32 |= ( EDBE  & 0x1 )  << 24;  // Error Detected on CHB Interrupt Enable       
  value_u32 |= ( LTVBE & 0x1 )  << 25;  // Latest Transmit Violation CHB Interrupt Enable           
  value_u32 |= ( TABBE & 0x1 )  << 26;  // Transmission Across Boundary Channel B Interrupt Enable
          
  FrDrv_write_32bit ( EIES_REG, value_u32 );
                                        
  // IR, SIES - Status Interrupt Enable Set Register 0x0038           
  value_u32 = 0;
  value_u32 |= ( WSTE   & 0x1 ) ;       // Wakeup Status Interrupt Enable               
  value_u32 |= ( CASE   & 0x1 ) << 1;   // Collision Avoidance Symbol Interrupt Enable                        
  value_u32 |= ( CYCSE  & 0x1 ) << 2;   // Cycle Start Interrupt Enable               
  value_u32 |= ( TXIE   & 0x1 ) << 3;   // Transmit Interrupt Enable              
  value_u32 |= ( RXIE   & 0x1 ) << 4;   // Receive Interrupt Enable             
  value_u32 |= ( RFNEE  & 0x1 ) << 5;   // Receive FIFO Not Empty Interrupt Enable                      
  value_u32 |= ( RFCLE  & 0x1 ) << 6;   // Receive FIFO Critical Level Interrupt Enable                   
  value_u32 |= ( NMVCE  & 0x1 ) << 7;   // Network Management Vector Changed Interrupt Enable                         
  value_u32 |= ( TI0E   & 0x1 ) << 8;   // Timer Interrupt 0 Enable             
  value_u32 |= ( TI1E   & 0x1 ) << 9;   // Timer Interrupt 1 Enable             
  value_u32 |= ( TIBCE  & 0x1 ) << 10;  // Transfer Input Buffer Completed Enable                         
  value_u32 |= ( TOBCE  & 0x1 ) << 11;  // Transfer Output Buffer Completed Enable                          
  value_u32 |= ( SWEE   & 0x1 ) << 12;  // Stop Watch Event Interrupt Enable                      
  value_u32 |= ( SUCSE  & 0x1 ) << 13;  // Startup Completed Successfully Interrupt Enable
  value_u32 |= ( MBSIE  & 0x1 ) << 14;  // Message Buffer Status Interrupt Enable   
  value_u32 |= ( SDSE   & 0x1 ) << 15;  // Start of Dynamic Segment Interrupt Enable
  value_u32 |= ( WUPAE  & 0x1 ) << 16;  // Wakeup Pattern Channel A  Interrupt Enable                           
  value_u32 |= ( MTSAE  & 0x1 ) << 17;  // Media Access Test Symbol Channel A Interrupt Enable                      
  value_u32 |= ( WUPBE  & 0x1 ) << 24;  // Wakeup Pattern Channel B Interrupt Enable                                          
  value_u32 |= ( MTSBE  & 0x1 ) << 25;  // Media Access Test Symbol Channel B Interrupt Enable
  FrDrv_write_32bit ( SIES_REG, value_u32 );

  // IR, ILE - Interrupt Line Enable Configuration Register 0x0040  
  value_u32 = 0;
  value_u32 |= ( EINT0  & 0x1 ) ;       // Enable Interrupt Line 0
  value_u32 |= ( EINT1  & 0x1 ) << 1;   // Enable Interrupt Line 1
  FrDrv_write_32bit ( ILE_REG, value_u32 );
                                       
  // IR, T0C - Timer Interrupt 0 Configuration Register 0x0044       
  value_u32 = 0;   
  value_u32 |= ( T0MS   & 0x1 )   << 1; // Timer 0 Mode Select     
  value_u32 |= ( T0CC   & 0x7F )  << 8; // Timer 0 Cycle Code [6:0]  
  value_u32 |= ( T0MO   & 0x3FFF )<< 16;// Timer 0 Macrotick Offset [13:0]     
  FrDrv_write_32bit ( T0C_REG, value_u32 );

  value_u32 = 0;             
  value_u32 |= ( T1MS   & 0x1 )   << 1; // Timer 1 Mode Select           
  value_u32 |= ( T1MC   & 0x3FFF )<< 16;// Timer 1 Macrotick Count  [13:0]       
  FrDrv_write_32bit ( T1C_REG, value_u32 );

  // IR, STPW1 - Stop Watch Register 1 0x004C                
  value_u32 = 0;
  value_u32 |= ( ESWT   & 0x1 );        // Enable Stop
  value_u32 |= ( SWMS   & 0x1 )   << 1; // Stop Watch Mode Select
  value_u32 |= ( EDGE   & 0x1 )   << 2; // Stop Watch Trigger Edge Select
  value_u32 |= ( SSWT   & 0x1 )   << 3; // Software Stop Watch Trigger  
  value_u32 |= ( EETP   & 0x1 )   << 4; // Enable External Trigger Pin
  value_u32 |= ( EINT0_S & 0x1 )  << 5; // Enalbe Interrupt 0 Trigger
  value_u32 |= ( EINT1_S & 0x1 )  << 6; // Enalbe Interrupt 1 Trigger
  FrDrv_write_32bit ( STPW1_REG, value_u32 );

                                       
  //CCCR, SUCC1 - SUC Configuration Register 1 (0x0080)                
  value_u32 = 0;
  value_u32 |= ( TXST & 0x1 ) << 8;   //Transmit Startup Frami in Key Slot
  value_u32 |= ( TXSY & 0x1 ) << 9;   //Transmit Sync Frame in Key Slot 
  value_u32 |= ( CSA  & 0x1F )<< 11;  //Cold Start Attempts [4:0]
  value_u32 |= ( PTA  & 0x1F )<< 16;  //Passive to Active [4:0]
  value_u32 |= ( WUCS & 0x1 ) << 21;  //Wakeup Channel Select
  value_u32 |= ( TSM  & 0x1 ) << 22;  //Transmission Slot Mode
  value_u32 |= ( HCSE & 0x1 ) << 23;  //Halt due to Clock Sync Error 
  value_u32 |= ( MTSA & 0x1 ) << 24;  //Select Channel A  for MTSymbol Transmission      
  value_u32 |= ( MTSB & 0x1 ) << 25;  //Select Channel B  for MTSymbol Transmission
  value_u32 |= ( CCHA & 0x1 ) << 26;  //Connected to Channel A
  value_u32 |= ( CCHB & 0x1 ) << 27;  //Connected to Channel B
  FrDrv_write_32bit ( SUCC1_REG, value_u32 );
                                                       
  //CCCR, SUCC2 - SUC Configuration Register 2 (0x0084)   
  value_u32 = 0;
  value_u32 |= ( testModeParas[FLX_CURRENT_TEST_MODE].reg_SUCC2_LT   & 0x1FFFFF );   // Listen Timeout [20:0]
  value_u32 |= ( LTN  & 0xF ) << 24;  // Listen Timeout [3:0]              
  FrDrv_write_32bit ( SUCC2_REG, value_u32 );

  //CCCR, SUCC3 - SUC Configuration Register 3 (0x0088)   
  value_u32 = 0;
  value_u32 |= ( WCP  & 0xF );    // Maximum Without Clock Correction Passive [3:0]                            
  value_u32 |= ( WCF  & 0xF ) << 4; // Maximum Without Clock Correction Fatal [3:0]              
  FrDrv_write_32bit ( SUCC3_REG, value_u32 );

  //CCCR, NEMC -  Configuration Register (0x008C)              
  value_u32 = 0;
  value_u32 |= ( NML  & 0xF );      // Network Management Vector Length [3:0]    
  FrDrv_write_32bit (  NEMC_REG, value_u32 );
                                 
  //CCCR, PRTC1 -  Configuration Register  (0x0090) 
  value_u32 = 0;
  value_u32 |= ( TSST & 0xF ) ; // Transmission Start Sequence Transmitter [3:0]             
  value_u32 |= ( CASM & 0x3F ) << 4;  // Collision Avoidance Symbol Max [6:0]
  value_u32 |= ( SPP  & 0x3 )  << 12; // 
  value_u32 |= ( BRP  & 0x3 )  << 14; // Baud Rate Prescaler [1:0]            
  value_u32 |= ( RXW  & 0x1FF )<< 16; // Wakeup Symbol Receiver Window Length [8:0]   
  value_u32 |= ( RWP  & 0x3F ) << 26; // Repetitions of Tx Wakeup Pattern [5:0]     
  FrDrv_write_32bit ( PRTC1_REG, value_u32 );
                                     
  //CCCR, PRTC2 -  Configuration Register  (0x0094)         
  value_u32 = 0;
  value_u32 |= ( RXI  & 0x3F ) ;    // Wakeup Symbol Receive Idle [5:0]                    
  value_u32 |= ( RXL  & 0x3F ) << 8;   // Wakeup Symbol Receive Low [5:0]   
  value_u32 |= ( TXI  & 0xFF ) << 16;  // Wakeup Symbol Transmit Idle [7:0]
  value_u32 |= ( TXL  & 0x3F ) << 24;  // Wakeup Symbol Transmit Low [5:0]  
  FrDrv_write_32bit ( PRTC2_REG, value_u32 );
                           
  //CCCR, MHDC -  Configuration Register  (0x0098)       
  value_u32 = 0;
//  value_u32 |= ( SFDL & 0x7F );     // Static Frame Data Length [6:0], comment @Titron
  value_u32 |= ( testModeParas[FLX_CURRENT_TEST_MODE].reg_MHDC_SFDL & 0x7F );     // Static Frame Data Length [6:0]
  value_u32 |= ( SLT  & 0x1FFF )  << 16;  // Start of Latest Transmit [12:0]                             
  FrDrv_write_32bit ( MHDC_REG, value_u32 );
                                                                                                                   
  //CCCR, GTUC1 - GTU Configuration Register 1 (0x00A0)            
  value_u32 = 0;
//  value_u32 |= ( UT   & 0xFFFFF );    // Microtick per Cycle [19:0], comment @Titron
  value_u32 |= ( testModeParas[FLX_CURRENT_TEST_MODE].reg_GTUC1_UT   & 0xFFFFF );    // Microtick per Cycle [19:0]
  FrDrv_write_32bit ( GTUC1_REG, value_u32 );
                                   
  //CCCR, GTUC2 - GTU Configuration Register 2 (0x00A4)
  value_u32 = 0;
//  value_u32 |= ( MPC  & 0x3FFF );   // Macrotick Per Cycle [13:0], comment @Titron
  value_u32 |= ( testModeParas[FLX_CURRENT_TEST_MODE].reg_GTUC2_MPC  & 0x3FFF );   // Macrotick Per Cycle [13:0]
  value_u32 |= ( SNM  & 0xF ) << 16;  // Sync Node Max [3:0]                             
  FrDrv_write_32bit ( GTUC2_REG, value_u32 );
                                   
  //CCCR, GTUC3 - GTU Configuration Register 3 (0x00AC)  
  value_u32 = 0;
  value_u32 |= ( UIOA & 0xFF ); // Microtick Initial Offset channel A [7:0]        
  value_u32 |= ( UIOB & 0xFF )<< 8; // Microtick Initial Offset channel B [7:0]         
  value_u32 |= ( MIOA & 0x3F )<< 16;  // Macrotick Initial Offset channel A [6:0]             
  value_u32 |= ( MIOB & 0x3F )<< 24;  // Macrotick Initial Offset channel B [6:0]
  FrDrv_write_32bit ( GTUC3_REG, value_u32 );

  //CCCR, GTUC4 - GTU Configuration Register 4 (0x00AC)        
  value_u32 = 0;
//  value_u32 |= ( NIT  & 0x3FFF );   // Network Idle Time Start [13:0], comment @Titron
  value_u32 |= ( testModeParas[FLX_CURRENT_TEST_MODE].reg_GTUC4_NIT  & 0x3FFF );   // Network Idle Time Start [13:0]
//  value_u32 |= ( OCS  & 0x3FFF )  << 16;  // Offset Correction Start [13:0], comment @Titron
  value_u32 |= ( testModeParas[FLX_CURRENT_TEST_MODE].reg_GTUC4_OCS  & 0x3FFF )  << 16;  // Offset Correction Start [13:0]
  FrDrv_write_32bit ( GTUC4_REG, value_u32 );
                         
  //CCCR, GTUC5 - GTU Configuration Register 5 (0x00B0)         
  value_u32 = 0;
  value_u32 |= ( DCA  & 0xFF );   // Delay Compensation Channel A [7:0]                        
  value_u32 |= ( DCB  & 0xFF )<< 8; // Delay Compensation Channel B [7:0]            
  value_u32 |= ( CDD  & 0x1F )<< 16;  // Cluster Drift Damping [4:0]
  value_u32 |= ( DEC  & 0x7F )<< 24;  // Decoding Correction [6:0]
  FrDrv_write_32bit ( GTUC5_REG, value_u32 );
                
  //CCCR, GTUC6 - GTU Configuration Register 6 (0x00B4)      
  value_u32 = 0;
  value_u32 |= ( ASR  & 0x7FF );      // Accepted Startup Range [10:0]             
  value_u32 |= ( MOD  & 0x7FF ) << 16;  // Maximum Oscillator Drift [10:0]             
  FrDrv_write_32bit ( GTUC6_REG, value_u32 );          
                                       
  //CCCR, GTUC7 - GTU Configuration Register 7 (0x00B8)          
  value_u32 = 0;
//  value_u32 |= ( SSL  & 0x7FF );      // Static Slot Length [10:0], comment @Titron
  value_u32 |= ( testModeParas[FLX_CURRENT_TEST_MODE].reg_GTUC7_SSl  & 0x7FF );      // Static Slot Length [10:0]
  value_u32 |= ( NSS  & 0x3FF ) << 16;  // Number of Static Slots [9:0]                          
  FrDrv_write_32bit ( GTUC7_REG, value_u32 );
                                           
  //CCCR, GTUC8 - GTU Configuration Register 8 (0x00BC) MSL_;                
  value_u32 = 0;
  value_u32 |= ( MSL  & 0x3F );     // Minislot Length [5:0]                            
  value_u32 |= ( NMS  & 0x1FFF )  << 16;  // Number of Minislots [12:0]                              
  FrDrv_write_32bit ( GTUC8_REG, value_u32 );
                                     
  //CCCR, GTUC9 - GTU Configuration Register 9 (0x00C0) 
  value_u32 = 0;
  value_u32 |= ( APO  & 0x1F );     // Action Point Offset[4:0]                               
  value_u32 |= ( MAPO & 0x1F )  << 8; // Minislot Action Point Offset [4:0]                           
  value_u32 |= ( DSI  & 0x3 ) << 16;    // Dynamic Slot Idle Phase [1:0]    
  FrDrv_write_32bit ( GTUC9_REG, value_u32 );
                                       
  //CCCR, GTUC10 - GTU Configuration Register 10 (0x00C4)                
  value_u32 = 0;
  value_u32 |= ( MOC  & 0x3FFF ) ;      // Maximum Offset Correction [13:0]     
  value_u32 |= ( MRC  & 0x7FF ) << 16;  // Maximum Rate Correction [10:0]      
  FrDrv_write_32bit ( GTUC10_REG, value_u32 );
                                       
  //CCCR, GTUC11 - GTU Configuration Register 11 (0x00C8)                
  value_u32 = 0;
  value_u32 |= ( EOCC & 0x3 ) ;       // External Offset Correction Control [1:0]              
  value_u32 |= ( ERCC & 0x3 ) ;       // External Offset Correction Control [1:0]
  value_u32 |= ( EOC  & 0x7 ) << 16;  // External Offset Correction [2:0]          
  value_u32 |= ( ERC  & 0x7 ) << 24;  // External Rate Correction [2:0]      
  FrDrv_write_32bit ( GTUC11_REG, value_u32 );

                                                                                                                     
  //MBCR, MRC - Message RAM Configuration 0x0300           
  value_u32 = 0;                        
  value_u32 |= ( FDB  & 0xFF ) ;      // First Dynamic Buffer [7:0] 
  value_u32 |= ( FFB  & 0xFF ) << 8;  // First FIFO Buffer [7:0]
  value_u32 |= ( LCB  & 0xFF ) << 16; // Last Configured Buffer [7:0]                                            
  value_u32 |= ( SEC  & 0x3 )  << 24; // Secure Buffers [1:0]
  value_u32 |= ( SPLM & 0x1 )  << 25; // Sync Frame Payload Multiplex     
  FrDrv_write_32bit ( MRC_REG, value_u32 );
                                     
  //MBCR, FRF - FIFO Rejection Filter 0x0304          
  value_u32 = 0;
  value_u32 |= ( CHA  & 0x1 )  ;      // Channel Filter A                   
  value_u32 |= ( CHB  & 0x1 )  << 1;  // Channel Filter B                   
  value_u32 |= ( FID  & 0x7FF )<< 2;  // Frame ID Filter [10:0]                   
  value_u32 |= ( CYF  & 0x7F ) << 16; // Cycle Code Filter [6:0]                    
  value_u32 |= ( RSS  & 0x1 )  << 23; // Reject Static Segment
  value_u32 |= ( RNF  & 0x1 )  << 24; // Reject Null Frames
  FrDrv_write_32bit ( FRF_REG, value_u32 );                    
                              
  //MBCR, FRFM - FIFO Rejection Filter Mask 0x0308
  value_u32 = 0;
  value_u32 |= ( MFID   & 0x7FF ) << 2; // FIFO Rejection Filter Mask Bits [10:0]
  FrDrv_write_32bit ( FRFM_REG, value_u32 );

  //MBCR, FCL - FIFO Critical Level 0x030C
  value_u32 = 0;
  value_u32 |= ( CL   & 0xFF ) ; // Critical Level [7:0]
  FrDrv_write_32bit ( FCL_REG, value_u32 );
  
  //

  return FLEXRAY_STATUS_OK;
}

//Fr_ReturnType FrDrv_Config_PhysicalBuffers ( u16 BufferHeader_u16[64][10] ) {
Fr_ReturnType FrDrv_Config_PhysicalBuffers ( void ) {    
//=============================================================================
// FunctionName: FrDrv_Config_PhysicalBuffers
// IN : - 
// OUT : -
// Description:  REE FlexRay return value
//=============================================================================
  u32 value_u32;
  u08 i_u08;
  u08 mb_u08;

  i_u08 = 0;
  
  for ( mb_u08 = 0; mb_u08 < 128; mb_u08++ ) {
      
    value_u32 = 0;
    value_u32 |= ( BufferHeader_u16[mb_u08][0]        & 0x7FF );      // Frame ID [10:0]
    value_u32 |= ( BufferHeader_u16[mb_u08][1]        & 0x7F )  << 16;  // Base Cycle [5:0]
    value_u32 |= ( BufferHeader_u16[mb_u08][2]        & 0x1 )   << 24;  // Channel A Filter Control
    value_u32 |= ( BufferHeader_u16[mb_u08][3]        & 0x1 )   << 25;  // Channel B Filter Control
    value_u32 |= ( BufferHeader_u16[mb_u08][4]        & 0x1 )   << 26;  // Message Buffer Direction Conf Bit
    value_u32 |= ( BufferHeader_u16[mb_u08][5]        & 0x1 )   << 27;  // Payload Preamble Indicator Transmit
    value_u32 |= ( BufferHeader_u16[mb_u08][6]        & 0x1 )   << 28;  // Transmission Mode
    value_u32 |= ( BufferHeader_u16[mb_u08][7]        & 0x1 )   << 29;  // Message Buffer Interrupt
    FrDrv_write_32bit ( WRHS1_REG, value_u32 );

    // IB, WRHS3 - Write Header Section 2
    value_u32 = 0;
//    value_u32 |= (BufferHeader_u16[mb_u08][8]         & 0x7F )  << 16;  // Payload [10:0], comment @titron
    value_u32 |= (testModeParas[FLX_CURRENT_TEST_MODE].reg_MHDC_SFDL & 0x7F )  << 16;  // Payload [10:0]
    FrDrv_write_32bit ( WRHS2_REG, value_u32 );

    // IB, WRHS3 - Write Header Section 3
    value_u32 = 0;
    value_u32 |= (BufferHeader_u16[mb_u08][9]        & 0x7FF );  // Data Pointer [10:0]
    FrDrv_write_32bit ( WRHS3_REG, value_u32 );

    // IB, WRHS2 - Write Header Section 2
    value_u32 = 0;
    value_u32 |= ( FrDrv_crc ( mb_u08 ) & 0x7FF );  // Header CRC [10:0]
    value_u32 |= ( BufferHeader_u16[mb_u08][8]        & 0x7F )  << 16;  // Payload
    FrDrv_write_32bit ( WRHS2_REG, value_u32 );

    // check if input buffer busy by the message handler
    while ( ( FrDrv_read_16bit ( IBCR_REG ) & 0x8000 ) != 0 ) {
              i_u08++;
              if ( i_u08 == 0x80 ) {
              return FLEXRAY_STATUS_BUSY_TIME_OUT;
              } // end of if
    } // end of while                    
             
    // IB, IBCM - Input Buffer Command Mask Register
    value_u32 = 0;
    value_u32 |= 0x1;     //Load Header Section    
    FrDrv_write_32bit ( IBCM_REG, value_u32 );
    
    // IB, IBCM - Input Buffer Command Request
    value_u32 = 0;
    value_u32 |= ( mb_u08 & 0x7F ); 
    FrDrv_write_32bit ( IBCR_REG, value_u32 );
  } // end of for

  // check if input buffer busy by the message handler
  while ( ( ( FrDrv_read_16bit ( IBCR_REG ) & 0x8000 ) != 0 ) ||
          ( ( FrDrv_read_32bit ( IBCR_REG ) & 0x80000000 ) != 0 ) ) {
     i_u08++;
     if ( i_u08 == 0x80 ) {
        return FLEXRAY_STATUS_BUSY_TIME_OUT;
     } // end of if
  } // end of while

  return FLEXRAY_STATUS_OK;
}


// end of file

