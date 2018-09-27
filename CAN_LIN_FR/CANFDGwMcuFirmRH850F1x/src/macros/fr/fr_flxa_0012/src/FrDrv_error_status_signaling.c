//============================================================================
// PROJECT  : REE FlexRay driver
// MODULE   : FrDrv_error_status_interrupt.c
// VERSION  : 0.2
// DATE     : 02.10.2013
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
// 0.1        H.Schmerling                 Initial Release
// 0.2        P.Szczupak                   Modified for P1x-C device
//============================================================================


//============================================================================
// Includes                                                                  
//============================================================================
#include "FrDrv.h"
#include "GlobalDefines.h"
#include "TypeDefines.h"

//============================================================================
// Prototypes
//============================================================================
const char *FrDrvReturnString ( Fr_ReturnType eCode );
Fr_ReturnType FrDrv_error_interrupt ( void );
Fr_ReturnType FrDrv_status_interrupt ( void );
Fr_ReturnType FrDrv_state_1 ( void );
Fr_ReturnType FrDrv_wakeup_state ( void );
Fr_ReturnType FrDrv_startup_state ( void );
Fr_ReturnType FrDrv_state_2 ( void );
Fr_ReturnType FrDrv_wakeup_status ( void );
Fr_ReturnType FrDrv_error_status ( void );
Fr_ReturnType FrDrv_clock_correction_status ( void );
Fr_ReturnType FrDrv_symbol_window_and_NIT_status ( void );
Fr_ReturnType FrDrv_aggregated_channel_status ( void );
Fr_ReturnType FrDrv_message_handler_status ( void );
Fr_ReturnType FrDrv_message_buffer_status ( void );
void FrDrv_network_management_vector ( u32 *nmv1_u32,  u32 *nmv2_u32, u32 *nmv3_u32);

extern u32 FrDrv_read_32bit ( u32 addr_u32 );
extern void FrDrv_write_32bit ( u32 addr, u32 data_u32 );
extern u16 FrDrv_read_16bit ( u32 addr_u32 );
//============================================================================
// Global variables
//============================================================================


// Return of Code
static const char *FrDrvReturnCode[] = {
    
/*  1*/  "FLEXRAY_STATUS_OK                          "  ,   // General status code 
/*  2*/  "FLEXRAY_STATUS_CHI_INCOMPATIBLE            "  ,   
/*  3*/  "FLEXRAY_STATE_CHANGE_FAILED                "  ,   
/*  4*/  "FLEXRAY_STATUS_BUSY_TIME_OUT               "  ,        
/*  5*/  "FLEXRAY_NO_ERROR_INTERRUPT           "  ,   // FRCC error interrupt 
/*  6*/  "POC_ERROR_MODE_CHANGED             "  ,  
/*  7*/  "COMMAND_NOT_ACCEPTED               "  ,  
/*  8*/  "SYNC_FRAMES_BELOW_MINIMUM            "  ,  
/*  9*/  "SYNC_FRAME_OVERFLOW              "  ,          
/* 10*/  "CLOCK_CORRECTION_FAILURE             "  ,  
/* 11*/  "CHI_COMMAND_LOCKED               "  ,
/* 12*/  "PARITY_ERROR                   "  ,   
/* 13*/  "RECEIVE_FIFO_OVERRUN               "  ,  
/* 14*/  "EMPTY_FIFO_ACCESS                "  ,
/* 15*/  "ILLEGAL_INPUT_BUFFER               "  ,
/* 16*/  "ILLEGAL_OUTPUT_BUFFER_ACCESS           "  ,
/* 17*/  "MESSAGE_HANDLER_CONSTRANTS_FLAG        "  ,
/* 18*/  "ERROR_DETECTED_CHA               "  ,  
/* 19*/  "LATEST_TRANSMIT_VIOLATION_CHA          "  ,  
/* 20*/  "TRANSMISSION_ACROSS_BOUNDARY_CHA         "  ,  
/* 21*/  "ERROR_DETECTED_CHB               "  ,   
/* 22*/  "LATEST_TRANSMIT_VIOLATION_CHB          "  ,  
/* 23*/  "TRANSMISSION_ACROSS_BOUNDARY_CHB         "  ,  
/* 24*/  "FLEXRAY_NO_STATUS_INTERRUPT          "  ,   // FRCC status interrupt 
/* 25*/  "WAKEUP_STATUS                  "  ,  
/* 26*/  "COLLISION_AVOIDANCE_SYMBOL           "  ,   
/* 27*/  "CYCLE_START_INTERRUPT              "  ,   
/* 28*/  "TRANSMIT_INTERRUPT               "  ,   
/* 29*/  "RECEIVE_INTERRUPT                "  ,   
/* 30*/  "RECEIVE_FIFO_NOT_EMPTY             "  ,  
/* 31*/  "RECEIVE_CRITICAL_LEVEL             "  ,   
/* 32*/  "NETWORK_MANAGEMENT_VECTOR_CHANGED        "  ,  
/* 33*/  "TIMER_INTERRUPT_0                "  ,   
/* 34*/  "TIMER_INTERRUPT_1                "  ,  
/* 35*/  "TRANSFER_INPUT_BUFFER_COMPLETED        "  ,   
/* 36*/  "TRANSFER_OUTPUT_BUFFER_COMPLETED         "  ,   
/* 37*/  "STOP_WATCH_EVENT                 "  ,  
/* 38*/  "STARTUP_COMPLETED_SUCCESSFULLY         "  ,   
/* 39*/  "MESSAGE_BUFFER_STATUS_INTERRUPT        "  ,
/* 40*/  "START_OF_DYNAMIC_SEGMENT             "  ,
/* 41*/  "WAKEUP_PATTERN_CHA               "  ,
/* 42*/  "MTS_RECEIVED_CHA                 "  ,
/* 43*/  "WAKEUP_PATTERN_CHB               "  ,
/* 44*/  "MTS_RECEIVED_CHB                 "  ,
/* 45*/  "NO_STATE                     "  ,   // FRCC state 1
/* 46*/  "DEFAULT_CONFIG_STATE               "  ,     
/* 54*/  "READY_STATE                  "  ,     
/* 55*/  "NORMAL_ACTIVE_STATE                "  ,     
/* 56*/  "NORMAL_PASSIVE_STATE               "  ,           
/* 57*/  "HALT_STATE                   "  ,                       
/* 58*/  "MONITOR_MODE_STATE               "  ,                                                   
/* 59*/  "CONFIG_STATE                   "    ,
/* 60*/  "WAKEUP_STANDBY_STATE               "  ,   // FRCC wakeup state
/* 61*/  "WAKEUP_LISTEN_STATE              "  ,       
/* 62*/  "WAKEUP_SEND_STATE                "  ,              
/* 63*/  "WAKEUP_DETECT_STATE              "  ,                       
/* 64*/  "STARTUP_PREPARE_STATE              "  ,   // FRCC startup state       
/* 65*/  "COLDSTART_LISTEN_STATE             "  ,        
/* 66*/  "COLDSTART_COLLISTION_RESOLUTION_STATE      "  ,     
/* 67*/  "COLDSTART_CONSISTENCY_CHECK_STATE        "  ,              
/* 68*/  "COLDSTART_GAP_STATE              "  ,         
/* 69*/  "COLDSTART_JOIN_STATE                     "  ,           
/* 70*/  "INTEGRATION_COLDSTART_CHECK_STATE        "  ,  
/* 71*/  "INTEGRATION_LISTEN_STATE             "  ,                  
/* 72*/  "INTEGRATION_CONSISTENCY_CHECK_STATE      "  ,                       
/* 73*/  "INITIALIZE_SCHEDULE_STATE            "  ,                     
/* 74*/  "ABORT_STARTUP_STATE              "  ,
/* 75*/  "FREEZE_STATUS_INDICATOR            "  ,   // FRCC state 2 
/* 76*/  "HALT_REQUEST                   "  ,    
/* 77*/  "SLOT_MODE_SINGLE                 "  ,         
/* 78*/  "SLOT_MODE_ALL_PENDING              "  ,    
/* 79*/  "SLOT_MODE_ALL                  "  ,
/* 80*/  "COLDSTART_NOISE_INDICATOR            "  ,
/* 81*/  "COLDSTART_ABORT_INDICATOR            "  ,
/* 82*/  "COLDSTART_ABORT_INHIBIT            "  ,
/* 83*/  "DEFAULT_CONFIG_REQUEST             "  ,
/* 84*/  "NO_WAKEUP_ATTEMPT                "  ,   // FRCC wakeup status
/* 85*/  "WAKEUP_RECEIVED_HEADER             "  ,    
/* 86*/  "WAKEUP_RECEIVED_WUP              "  ,      
/* 87*/  "WAKEUP_COLLISION_HEADER            "  ,      
/* 88*/  "WAKEUP_COLLISION_WUP               "  ,                
/* 89*/  "WAKEUP_COLLISION_UNKNOWN             "  ,         
/* 90*/  "WAKEUP_TRANSMITTED               "  ,                 
/* 91*/  "ERROR_MODE_ACTIVE                "  ,   // CC Error Vector          
/* 92*/  "ERROR_MODE_PASSIVE               "  ,           
/* 93*/  "ERROR_MODE_COMM_HALT               "  ,     
/* 94*/  "CLOCK_CORRECTION_OK              "  ,   // Clock Correction Status 1    
/* 95*/  "MISSING_OFFSET_CORRECTION_SIGNAL         "  ,                       
/* 96*/  "OFFSET_CORRECTION_LIMIT_REACHED          "  ,                       
/* 97*/  "MISSING_RATE_CORRECTION_SIGNAL         "  ,                       
/* 98*/  "RATE_CORRECTION_LIMIT_REACHED          "  ,
/* 99*/  "SYMBOL_WINDOW_NIT_OK               "  ,   // Symbol window and NIT Status   
/*100*/  "SYNTAX_ERROR_IN_SYMBOL_WINDOW_CHA        "  ,             
/*101*/  "SLOT_BOUNDARY_VIOLATION_IN_SYMBOL_WINDOW_CHA "  ,           
/*102*/  "TRANSMISSION_CONFLICT_IN_SYMBOL_WINDOW_CHA   "  ,           
/*103*/  "SYNTAX_ERROR_IN_SYMBOL_WINDOW_CHB        "  ,            
/*104*/  "SLOT_BOUNDARY_VIOLATION_IN_SYMBOL_WINDOW_CHB "  ,   
/*105*/  "TRANSMISSION_CONFLICT_IN_SYMBOL_WINDOW_CHB   "  ,            
/*106*/  "SYNTAX_ERROR_DURING_NIT_CHA          "  ,                 
/*107*/  "SLOT_BOUNDARY_VIOLATION_DURING_NIT_CHA     "  ,                   
/*108*/  "SYNTAX_ERROR_DURING_NIT_CHB          "  ,          
/*109*/  "SLOT_BOUNDARY_VIOLATION_DURING_NIT_CHB     "  ,                          
/*110*/  "AGGREGATED_CHANNEL_STATUS_OK           "  ,   // Aggregated Channel Status  
/*111*/  "VALID_FRAME_RECEIVED_ON_CHA          "  ,                
/*112*/  "SYNTAX_ERROR_DETECTED_0N_CHA           "  ,                       
/*113*/  "CONTENT_ERROR_DETECTED_ON_CHA          "  ,   
/*114*/  "COMMUNICATION_INDICATOR_CHA          "  ,  
/*115*/  "SLOT_BOUNDARY_VIOLATION_ON_CHA         "  ,     
/*116*/  "VALID_FRAME_RECEIVED_ON_CHB          "  ,  
/*117*/  "SYNTAX_ERROR_DETECTED_0N_CHB           "  ,       
/*118*/  "CONTENT_ERROR_DETECTED_ON_CHB          "  ,  
/*119*/  "COMMUNICATION_INDICATOR_CHB          "  ,   
/*120*/  "SLOT_BOUNDARY_VIOLATION_ON_CHB         "  ,     
/*121*/  "MESSAGE_HANDLER_STATUS_OK            "  ,   // FRCC Message Handler Status
/*122*/  "PARITY_ERROR_INPUT_BUFFER            "  ,    
/*123*/  "PARITY_ERROR_OUTPUT_BUFFER           "  ,         
/*124*/  "PARITY_ERROR_MESSAGE_RAM             "  ,     
/*125*/  "PARITY_ERROR_TRANSIENT_BUFFER_A        "  ,                       
/*126*/  "PARITY_ERROR_TRANSIENT_BUFFER_B        "  ,
/*127*/  "FAULTY_MESSAGE_BUFFER_DETECTED         "  ,
/*128*/  "MULTIPLE_FAULTY_MESSAGE_BUFFER_DETECTED    "  ,
/*129*/  "CLEAR_ALL_INTERNAL_RAMS            "  ,                       
/*130*/  "MESSAGE_BUFFER_OK                "  ,   // General Messages Buffer Status   
/*131*/  "MESSAGE_BUFFER_FULL              "  ,            
/*132*/  "MESSAGE_BUFFER_NO_DATA             "  ,                       
/*133*/  "VALID_FRAME_RECEIVED_CHA             "  , // Transmit & Receive Buffer
/*134*/  "VALID_FRAME_RECEIVED_CHB             "  , 
/*135*/  "SYNTAX_ERROR_OBSERVED_CHA            "  ,   
/*136*/  "SYNTAX_ERROR_OBSERVED_CHB            "  ,   
/*137*/  "CONTENT_ERROR_OBSERVED_CHA           "  ,          
/*138*/  "CONTENT_ERROR_OBSERVED_CHB           "  ,                     
/*139*/  "SLOT_BOUNDARY_VIOLATION_OBSERVED_CHA       "  ,  
/*140*/  "SLOT_BOUNDARY_VIOLATION_OBSERVED_CHB       "  ,   
/*141*/  "TRANSMIT_CONFLICT_INDICATION_CHA         "  ,   
/*142*/  "TRANSMIT_CONFLICT_INDICATION_CHB         "  ,   
/*143*/  "EMPTY_SLOT_CHA                 "  ,   
/*144*/  "EMPTY_SLOT_CHB                 "  ,   
/*145*/  "MESSAGE_LOST                   "                             
     
};     
     
     
const char *FrDrvReturnString ( Fr_ReturnType eCode ) {  
//=============================================================================
// FunctionName: FrDrvReturnString
// IN: REE FlexRay return value number
// OUT: REE FlexRay return value character
// Description: convention return value num -> char
//=============================================================================  
  return FrDrvReturnCode [ eCode ];
}

Fr_ReturnType FrDrv_error_interrupt ( void ) {
//=============================================================================
// FunctionName: FrDrv_error_interrupt
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the E-Ray error interrupt status
//=============================================================================  
    u32 value_u32;

    value_u32 = FrDrv_read_32bit ( EIR_REG );
    value_u32 &= FrDrv_read_32bit ( EIES_REG );
    
   // Error Interrupt Register (EIR) 0x0020
   if ( value_u32 & 0x00000001 ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000001 );
     return POC_ERROR_MODE_CHANGED;
   } // end of if                    
   if ( value_u32 & 0x00000002 ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000002 );
     return COMMAND_NOT_ACCEPTED;
   } // end of if                   
   if ( value_u32 & 0x00000004 ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000004 );
     return SYNC_FRAMES_BELOW_MINIMUM;
   } // end of if                   
   if ( value_u32 & 0x00000008  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000008 );
     return SYNC_FRAME_OVERFLOW;
   } // end of if  
                    
   if ( value_u32 & 0x00000010  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000010 );
     return CLOCK_CORRECTION_FAILURE;
   } // end of if 
   if ( value_u32 & 0x00000020  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000020 );
     return CHI_COMMAND_LOCKED;
   } // end of if                                                       
   if ( value_u32 & 0x00000040  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000040 );
     return PARITY_ERROR;
   } // end of if                    
   if ( value_u32 & 0x00000080  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000080 );
     return RECEIVE_FIFO_OVERRUN;
   } // end of if
     
   if ( value_u32 & 0x00000100  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000100 );
     return EMPTY_FIFO_ACCESS;
   } // end of if  
   if ( value_u32 & 0x00000200  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000200 );
     return ILLEGAL_INPUT_BUFFER;
   } // end of if  
   if ( value_u32 & 0x00000400  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000400 );
     return ILLEGAL_OUTPUT_BUFFER_ACCESS;
   } // end of if
   if ( value_u32 & 0x00000800  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00000800 );
     return MESSAGE_HANDLER_CONSTRANTS_FLAG;
   } // end of if
                                                 
   if ( value_u32 & 0x00010000  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00010000 );
     return ERROR_DETECTED_CHA;
   } // end of if                   
   if ( value_u32 & 0x00020000  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00020000 );
     return LATEST_TRANSMIT_VIOLATION_CHA;
   } // end of if                    
   if ( value_u32 & 0x00040000  ) {
     FrDrv_write_32bit ( EIR_REG, 0x00040000 );
     return TRANSMISSION_ACROSS_BOUNDARY_CHA;
   } // end of if
                                        
   if ( value_u32 & 0x01000000  ) {
     FrDrv_write_32bit ( EIR_REG, 0x01000000 );
     return ERROR_DETECTED_CHB;
   } // end of if                   
   if ( value_u32 & 0x02000000  ) {
     FrDrv_write_32bit ( EIR_REG, 0x02000000 );
     return LATEST_TRANSMIT_VIOLATION_CHB;
   } // end of if                    
   if ( value_u32 & 0x04000000  ) {
     FrDrv_write_32bit ( EIR_REG, 0x04000000 );
     return TRANSMISSION_ACROSS_BOUNDARY_CHB;
   } // end of if 

   return FLEXRAY_NO_ERROR_INTERRUPT;
}

Fr_ReturnType FrDrv_status_interrupt ( void ) {
//=============================================================================
// FunctionName: FrDrv_status_interrupt
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the E-Ray status interrupt status
//=============================================================================  
    u32 value_u32;

    value_u32 = FrDrv_read_32bit ( SIR_REG );
    value_u32 &= FrDrv_read_32bit ( SIES_REG );
    
   // Status Interrupt Register (SIR_REG) 0x0024
   if ( value_u32 & 0x00000001  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000001 );
     return WAKEUP_STATUS;
   } // end of if                    
   if ( value_u32 & 0x00000002  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000002 );
     return COLLISION_AVOIDANCE_SYMBOL;
   } // end of if                    
   if ( value_u32 & 0x00000004  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000004 );
     return CYCLE_START_INTERRUPT;
   } // end of if                    
   if ( value_u32 & 0x00000008  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000008 );
     return TRANSMIT_INTERRUPT;
   } // end of if
                       
   if ( value_u32 & 0x00000010  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000010 );
     return RECEIVE_INTERRUPT;
   } // end of if                    
   if ( value_u32 & 0x00000020  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000020 );
     return RECEIVE_FIFO_NOT_EMPTY;
   } // end of if                    
   if ( value_u32 & 0x00000040  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000040 );
     return RECEIVE_CRITICAL_LEVEL;
   } // end of if                    
   if ( value_u32 & 0x00000080  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000080 );
     return NETWORK_MANAGEMENT_VECTOR_CHANGED;
   } // end of if
                       
   if ( value_u32 & 0x00000100  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000100 );
     return TIMER_INTERRUPT_0;
    } // end of if                   
   if ( value_u32 & 0x00000200  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000200 );
     return TIMER_INTERRUPT_1;
   } // end of if                    
   if ( value_u32 & 0x00000400  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000400 );
     return TRANSFER_INPUT_BUFFER_COMPLETED;
   } // end of if                    
   if ( value_u32 & 0x00000800  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00000800 );
     return TRANSFER_OUTPUT_BUFFER_COMPLETED;
   } // end of if 
                      
   if ( value_u32 & 0x00001000  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00001000 );
     return STOP_WATCH_EVENT;
   } // end of if 
   if ( value_u32 & 0x00002000  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00002000 );
     return STARTUP_COMPLETED_SUCCESSFULLY;
   } // end of if
   if ( value_u32 & 0x00004000  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00004000 );
     return MESSAGE_BUFFER_STATUS_INTERRUPT;
   } // end of if 
   if ( value_u32 & 0x00008000  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00008000 );
     return START_OF_DYNAMIC_SEGMENT;
   } // end of if
         
   if ( value_u32 & 0x00010000  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00010000 );
     return WAKEUP_PATTERN_CHA;
   } // end of if                    
   if ( value_u32 & 0x00020000  ) {
     FrDrv_write_32bit ( SIR_REG, 0x00020000 );
     return MTS_RECEIVED_CHA;
   } // end of if
                       
   if ( value_u32 & 0x01000000  ) {
     FrDrv_write_32bit ( SIR_REG, 0x01000000 );
     return WAKEUP_PATTERN_CHB;
   } // end of if
   if ( value_u32 & 0x02000000  ) {
     FrDrv_write_32bit ( SIR_REG, 0x02000000 );
     return MTS_RECEIVED_CHB;
   } // end of if
   
   return FLEXRAY_NO_STATUS_INTERRUPT;
}

Fr_ReturnType FrDrv_state_1 ( void ) {
//=============================================================================
// FunctionName: FrDrv_state_1
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the E-Ray state status
//=============================================================================  

   // CCSR" CCSEV" Communication Controller Status Vector 0x0100
   switch ( FrDrv_read_16bit ( CCSV_REG )  & 0x3f ) {
   
    case ( 0 ):
                    return DEFAULT_CONFIG_STATE;
  case ( 1 ):
                    return READY_STATE;
  case ( 2 ):
                    return NORMAL_ACTIVE_STATE;
  case ( 3 ):
                    return NORMAL_PASSIVE_STATE;
  case ( 4 ):
                    return HALT_STATE;
  case ( 5 ):
                    return MONITOR_MODE_STATE;
  case ( 15 ):
                    return CONFIG_STATE;

  default:
        break;
   } // end of switch

   return NO_STATE;
}          

Fr_ReturnType FrDrv_wakeup_state ( void ) {
//=============================================================================
// FunctionName: FrDrv_wakeup_state
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the E-Ray wakeup state
//=============================================================================  

    // CCSR" CCSEV" Communication Controller Status Vector 0x0100
   switch ( FrDrv_read_16bit ( CCSV_REG )  & 0x1F ) {
   
        case ( 16 ):
                    return WAKEUP_STANDBY_STATE;
        case ( 17 ):
                    return WAKEUP_LISTEN_STATE;
        case ( 18 ):
                    return WAKEUP_SEND_STATE;
        case ( 19 ):
                    return WAKEUP_DETECT_STATE;
        default:
                    break;
   } // end of switch

   return NO_STATE;
}        

Fr_ReturnType FrDrv_startup_state ( void ) {
//=============================================================================
// FunctionName: FrDrv_startup_state
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the E-Ray startup state
//=============================================================================          

    // CCSR" CCSEV" Communication Controller Status Vector 0x0100
   switch ( FrDrv_read_16bit ( CCSV_REG )  & 0x3F ) {
   
        case ( 32 ):
                    return STARTUP_PREPARE_STATE;
        case ( 33 ):
                    return COLDSTART_LISTEN_STATE;
        case ( 34 ):
                    return COLDSTART_COLLISTION_RESOLUTION_STATE;
        case ( 35 ):
                    return COLDSTART_CONSISTENCY_CHECK_STATE;
        case ( 36 ):
                    return COLDSTART_GAP_STATE;
        case ( 37 ):
                    return COLDSTART_JOIN_STATE;
        case ( 38 ):
                    return INTEGRATION_COLDSTART_CHECK_STATE;
        case ( 39 ):
                    return INTEGRATION_LISTEN_STATE;
        case ( 40 ):
                    return INTEGRATION_CONSISTENCY_CHECK_STATE;
        case ( 41 ):
                    return INITIALIZE_SCHEDULE_STATE;
        case ( 42 ):
                    return ABORT_STARTUP_STATE;    
        default:
                    break;
   } // end of switch

   return NO_STATE;
}        

Fr_ReturnType FrDrv_state_2 ( void ) {
//=============================================================================
// FunctionName: FrDrv_state_2
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the E-Ray state status
//=============================================================================    

   switch ( ( FrDrv_read_16bit ( CCSV_REG ) >> 6 ) & 0x3FF ) {

    case ( 1 ):
    return FREEZE_STATUS_INDICATOR;
    case ( 2 ):
    return HALT_REQUEST;
    case ( 8 ):
    return SLOT_MODE_ALL_PENDING;
    case ( 12 ):
    return SLOT_MODE_ALL;
  case ( 64 ):
    return COLDSTART_NOISE_INDICATOR;
    case ( 128 ):
    return COLDSTART_ABORT_INDICATOR;
    case ( 256 ):
    return COLDSTART_ABORT_INHIBIT;
    case ( 512 ):
    return DEFAULT_CONFIG_REQUEST;
    default:
        return SLOT_MODE_SINGLE;  // break;
   } // end of switch

}
          
Fr_ReturnType FrDrv_wakeup_status ( void ) {
//=============================================================================
// FunctionName: FrDrv_wakeup_status
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the wakeup status
//=============================================================================  

    // CCSR" CCSEV" Wakeup Status Vector 
   switch ( FrDrv_read_16bit ( CCSV_REG + 2 )  & 0x7) {
  
          case ( 0 ):
                    return NO_WAKEUP_ATTEMPT;
          case ( 1 ):
                    return WAKEUP_RECEIVED_HEADER;
          case ( 2 ):
                    return WAKEUP_RECEIVED_WUP;
          case ( 3 ):
                    return WAKEUP_COLLISION_HEADER;
          case ( 4 ):
                    return WAKEUP_COLLISION_WUP;
          case ( 5 ):
                    return WAKEUP_COLLISION_UNKNOWN;
          case ( 6 ):
                    return WAKEUP_TRANSMITTED;
          default:
                    break;
   } // end of switch

   return NO_STATE; 
}

Fr_ReturnType FrDrv_error_status ( void ) {
//=============================================================================
// FunctionName: FrDrv_error_status
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the error status
//=============================================================================  

    // CCSR" CCSEV" Wakeup Status Vector 
   switch ( ( FrDrv_read_16bit ( CCEV_REG ) >> 6 )  & 0x3) {
  
          case ( 0 ):
                    return ERROR_MODE_ACTIVE;
          case ( 1 ):
                    return ERROR_MODE_PASSIVE;
          case ( 2 ):
                    return ERROR_MODE_COMM_HALT;
          default:
                    break;
   } // end of switch

   return NO_STATE; 
}

Fr_ReturnType FrDrv_clock_correction_status ( void ) {
//=============================================================================
// FunctionName: FrDrv_clock_correction_status
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the status of the clock correction
//=============================================================================  

    switch ( FrDrv_read_16bit ( SFS_REG + 2 ) & 0xF) {
     case ( 1 ):
    return MISSING_OFFSET_CORRECTION_SIGNAL;
     case ( 2 ):
    return OFFSET_CORRECTION_LIMIT_REACHED;
     case ( 4 ):
    return MISSING_RATE_CORRECTION_SIGNAL;
     case ( 8 ):
    return RATE_CORRECTION_LIMIT_REACHED;
     default:
        break;
   } // end of switch

   return CLOCK_CORRECTION_OK; 
}
 
Fr_ReturnType FrDrv_symbol_window_and_NIT_status ( void ) {
//=============================================================================
// FunctionName: FrDrv_symbol_window_and_NIT_status
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the value of the Symbol window and NIT
//=============================================================================  

    // CCSR" CCSEV" Wakeup Status Vector 
   switch ( FrDrv_read_16bit ( SWNIT_REG ) ) {
  
          case ( 0x0001 ):
                    return SYNTAX_ERROR_IN_SYMBOL_WINDOW_CHA;
          case ( 0x0002 ):
                    return SLOT_BOUNDARY_VIOLATION_IN_SYMBOL_WINDOW_CHA;
          case ( 0x0004 ):
                    return TRANSMISSION_CONFLICT_IN_SYMBOL_WINDOW_CHA;
          case ( 0x0008 ):
                    return SYNTAX_ERROR_IN_SYMBOL_WINDOW_CHB;
          case ( 0x0010 ):
                    return SLOT_BOUNDARY_VIOLATION_IN_SYMBOL_WINDOW_CHB;
          case ( 0x0020 ):
                    return TRANSMISSION_CONFLICT_IN_SYMBOL_WINDOW_CHB;
          case ( 0x0100 ):
                    return SYNTAX_ERROR_DURING_NIT_CHA;
          case ( 0x0200 ):
                    return SLOT_BOUNDARY_VIOLATION_DURING_NIT_CHA;
          case ( 0x0400 ):
                    return SYNTAX_ERROR_DURING_NIT_CHB;
          case ( 0x0800 ):
                    return SLOT_BOUNDARY_VIOLATION_DURING_NIT_CHB;
          default:
                    break;
   } // end of switch

   return SYMBOL_WINDOW_NIT_OK; 
}

Fr_ReturnType FrDrv_aggregated_channel_status ( void ) {
//=============================================================================
// FunctionName: FrDrv_aggregated_channel_status
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the frame status (ACS register)
//=============================================================================  

   switch ( FrDrv_read_16bit ( ACS_REG ) ) {
  
          case ( 0x0001 ):
                    return VALID_FRAME_RECEIVED_ON_CHA;
          case ( 0x0002 ):
                    return SYNTAX_ERROR_DETECTED_0N_CHA;
          case ( 0x0004 ):
                    return CONTENT_ERROR_DETECTED_ON_CHA;
          case ( 0x0008 ):
                    return COMMUNICATION_INDICATOR_CHA;
          case ( 0x0010 ):
                    return SLOT_BOUNDARY_VIOLATION_ON_CHA;
          case ( 0x0100 ):
                    return VALID_FRAME_RECEIVED_ON_CHB;
          case ( 0x0200 ):
                    return SYNTAX_ERROR_DETECTED_0N_CHB;
          case ( 0x0400 ):
                    return CONTENT_ERROR_DETECTED_ON_CHB;
          case ( 0x0800 ):
                    return COMMUNICATION_INDICATOR_CHB;
          case ( 0x1000 ):
                    return SLOT_BOUNDARY_VIOLATION_ON_CHB;
          default:
                    break;
   } // end of switch

   return AGGREGATED_CHANNEL_STATUS_OK; 
}
           
Fr_ReturnType FrDrv_message_handler_status ( void ) {
//=============================================================================
// FunctionName: FrDrv_message_handler_status
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the value of a parity error (MHDS register)
//=============================================================================  

   // MHSR - Message Handler Status Register
   switch ( FrDrv_read_16bit ( MHDS_REG ) ) {
   
  case ( 0x0001 ):
                    return PARITY_ERROR_INPUT_BUFFER;
  case ( 0x0002 ):
                    return PARITY_ERROR_OUTPUT_BUFFER;         
  case ( 0x0004 ):
                    return PARITY_ERROR_MESSAGE_RAM;          
  case ( 0x0008 ):
                    return PARITY_ERROR_TRANSIENT_BUFFER_A;          
  case ( 0x0010 ):
                    return PARITY_ERROR_TRANSIENT_BUFFER_B;
  case ( 0x0020 ):
                    return FAULTY_MESSAGE_BUFFER_DETECTED;          
  case ( 0x0040 ):
                    return MULTIPLE_FAULTY_MESSAGE_BUFFER_DETECTED;          
  case ( 0x0080 ):
                    return CLEAR_ALL_INTERNAL_RAMS;                                
  default:
        break;
   } // end of switch

   return MESSAGE_HANDLER_STATUS_OK;
}

Fr_ReturnType FrDrv_message_buffer_status ( void ) {
//=============================================================================
// FunctionName: FrDrv_message_buffer_status
// IN: -
// OUT: REE FlexRay return value
// Description: Returns the status of the message buffer status
//=============================================================================  

   // MBS - Message Buffer Status
   switch ( FrDrv_read_16bit ( MBS_REG ) ) {

  case ( 0x0001 ):                  
                    return VALID_FRAME_RECEIVED_CHA;     
  case ( 0x0002 ):                  
                    return VALID_FRAME_RECEIVED_CHB;  
  case ( 0x0004 ):                             
                    return SYNTAX_ERROR_OBSERVED_CHA;            
  case ( 0x0008 ):                             
                    return SYNTAX_ERROR_OBSERVED_CHB;            
  case ( 0x0010 ):                             
                    return CONTENT_ERROR_OBSERVED_CHA;               
  case ( 0x0020 ):                             
                    return CONTENT_ERROR_OBSERVED_CHB;                 
  case ( 0x0040 ):                             
                    return SLOT_BOUNDARY_VIOLATION_OBSERVED_CHA;          
  case ( 0x0080 ):                             
                    return SLOT_BOUNDARY_VIOLATION_OBSERVED_CHB;       
  case ( 0x0100 ):                             
                    return TRANSMIT_CONFLICT_INDICATION_CHA;                              
  case ( 0x0200 ):                             
                  return TRANSMIT_CONFLICT_INDICATION_CHB;         
  case ( 0x0400 ):                             
                  return EMPTY_SLOT_CHA;                                     
  case ( 0x0800 ):                             
                  return EMPTY_SLOT_CHB;               
  case ( 0x1000 ):                             
                    return MESSAGE_LOST;                  
  default:
        break;
   } // end of switch

   return MESSAGE_BUFFER_OK;
}

void FrDrv_network_management_vector ( u32 *nmv1_u32,  u32 *nmv2_u32, u32 *nmv3_u32) {
//=============================================================================
// FunctionName: FrDrv_network_management_vector
// IN: Pointer to RAM
// OUT: -
// Description: Stores the value of the Network managment vector to the pointed 
//              area in the RAM
//=============================================================================  

   *nmv1_u32 = FrDrv_read_32bit ( NMV1_REG ) ;
   *nmv2_u32 = FrDrv_read_32bit ( NMV2_REG ) ;
   *nmv3_u32 = FrDrv_read_32bit ( NMV3_REG ) ;
}

// end of file
