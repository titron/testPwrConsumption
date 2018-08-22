//============================================================================
// PROJECT  : NEC FlexRay driver 
// MODULE   : flexray_error_status_interrupt.h
// VERSION  : 0.1
// DATE     : 10.11.2003
//============================================================================
//                           C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2002 by NEC Electronics (Europe) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by NEC, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. NEC shall not have any obligation to maintain,
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
// In no event shall NEC be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. NEC shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by NEC in connection with the Product(s) and/or the
// Application.
//
//============================================================================
// Enviroment : Devices    : V850E/IA1  
//              Assembler  : GHS AS-V850 1.8.9             Version : 3.0
//              C-Compiler : GHS CCV850, Multi 2000, V800  Version : 3.5.1
//              Linker     : GHS lx, Multi 2000, V800      Version : 3.5.1       
//              Debugger   : GHS Multi 2000, V800          Version : 3.5.1
//============================================================================
// Version                    Author            Description
// 0.1              H.Schmerling        Initial Release
//============================================================================

#ifndef FLEXRAY_SERVICE_PARAMETER_H
#define FLEXRAY_SERVICE_PARAMETER_H

#ifdef FLEXRAY_SERVICE_PARAMETER_VARS
   #define _EXTERN_
#else
   #define _EXTERN_ extern
#endif


// FlexRay return values
typedef enum
{
  	
/*  1*/  FLEXRAY_STATUS_OK           	           	,  	// General status code 
/*  2*/  FLEXRAY_STATUS_CHI_INCOMPATIBLE	       	,   
/*  3*/  FLEXRAY_STATE_CHANGE_FAILED       	   	   	,   
/*  4*/  FLEXRAY_STATUS_BUSY_TIME_OUT         	   	,   		 
/*  5*/  FLEXRAY_NO_ERROR_INTERRUPT				   	,   // FRCC error interrupt 
/*  6*/  POC_ERROR_MODE_CHANGED					   	,  
/*  7*/  COMMAND_NOT_ACCEPTED				 	   	,  
/*  8*/  SYNC_FRAMES_BELOW_MINIMUM				   	,  
/*  9*/  SYNC_FRAME_OVERFLOW					   	,  				 
/* 10*/  CLOCK_CORRECTION_FAILURE				   	,  
/* 11*/  CHI_COMMAND_LOCKED						   	,
/* 12*/  PARITY_ERROR							   	,   
/* 13*/  RECEIVE_FIFO_OVERRUN					   	,  
/* 14*/  EMPTY_FIFO_ACCESS						   	,
/* 15*/  ILLEGAL_INPUT_BUFFER					   	,
/* 16*/  ILLEGAL_OUTPUT_BUFFER_ACCESS			   	,
/* 17*/  MESSAGE_HANDLER_CONSTRANTS_FLAG		   	,
/* 18*/  ERROR_DETECTED_CHA						   	,  
/* 19*/  LATEST_TRANSMIT_VIOLATION_CHA  		   	,  
/* 20*/  TRANSMISSION_ACROSS_BOUNDARY_CHA		   	,  
/* 21*/  ERROR_DETECTED_CHB						   	,   
/* 22*/  LATEST_TRANSMIT_VIOLATION_CHB  		   	,  
/* 23*/  TRANSMISSION_ACROSS_BOUNDARY_CHB		   	,  
/* 24*/  FLEXRAY_NO_STATUS_INTERRUPT			   	,   // FRCC status interrupt 
/* 25*/  WAKEUP_STATUS							   	,  
/* 26*/  COLLISION_AVOIDANCE_SYMBOL				    ,  	
/* 27*/  CYCLE_START_INTERRUPT					   	,  	
/* 28*/  TRANSMIT_INTERRUPT						    ,  	
/* 29*/  RECEIVE_INTERRUPT						   	,  	
/* 30*/  RECEIVE_FIFO_NOT_EMPTY					    ,  
/* 31*/  RECEIVE_CRITICAL_LEVEL					    ,  	
/* 32*/  NETWORK_MANAGEMENT_VECTOR_CHANGED		   	,  
/* 33*/  TIMER_INTERRUPT_0						   	,  	
/* 34*/  TIMER_INTERRUPT_1						   	,  
/* 35*/  TRANSFER_INPUT_BUFFER_COMPLETED		   	,  	
/* 36*/  TRANSFER_OUTPUT_BUFFER_COMPLETED		   	,  	
/* 37*/  STOP_WATCH_EVENT						   	,  
/* 38*/  STARTUP_COMPLETED_SUCCESSFULLY			    ,  	
/* 39*/  MESSAGE_BUFFER_STATUS_INTERRUPT		   	,
/* 40*/  START_OF_DYNAMIC_SEGMENT				   	,
/* 41*/  WAKEUP_PATTERN_CHA						    ,
/* 42*/  MTS_RECEIVED_CHA						   	,
/* 43*/  WAKEUP_PATTERN_CHB						    ,
/* 44*/	 MTS_RECEIVED_CHB						   	,
/* 45*/  NO_STATE								   	,   // FRCC state 1
/* 46*/  DEFAULT_CONFIG_STATE					   	,     
/* 54*/  READY_STATE							   	,     
/* 55*/  NORMAL_ACTIVE_STATE  					   	,     
/* 56*/  NORMAL_PASSIVE_STATE 					   	,     	 		
/* 57*/  HALT_STATE								    ,			  							 	
/* 58*/  MONITOR_MODE_STATE						    ,    				  	 													 				  
/* 59*/  CONFIG_STATE							    ,
/* 60*/  WAKEUP_STANDBY_STATE					   	,   // FRCC wakeup state
/* 61*/  WAKEUP_LISTEN_STATE					   	,       
/* 62*/  WAKEUP_SEND_STATE						   	,       		   
/* 63*/  WAKEUP_DETECT_STATE					   	,       								
/* 64*/  STARTUP_PREPARE_STATE					   	,   // FRCC startup state				
/* 65*/  COLDSTART_LISTEN_STATE					    ,     	 
/* 66*/  COLDSTART_COLLISTION_RESOLUTION_STATE	   	,     
/* 67*/  COLDSTART_CONSISTENCY_CHECK_STATE		   	,              
/* 68*/  COLDSTART_GAP_STATE					   	,    			
/* 69*/  COLDSTART_JOIN_STATE            		   	,    		 		
/* 70*/  INTEGRATION_COLDSTART_CHECK_STATE		   	,  
/* 71*/  INTEGRATION_LISTEN_STATE				   	,    						   
/* 72*/  INTEGRATION_CONSISTENCY_CHECK_STATE	   	,    		   							
/* 73*/  INITIALIZE_SCHEDULE_STATE 				    ,						   				
/* 74*/  ABORT_STARTUP_STATE					   	,
/* 75*/  FREEZE_STATUS_INDICATOR				   	,   // FRCC state 2	
/* 76*/  HALT_REQUEST							   	,  	 
/* 77*/  SLOT_MODE_SINGLE						   	,  	 			
/* 78*/  SLOT_MODE_ALL_PENDING					   	,  	 
/* 79*/  SLOT_MODE_ALL							   	,
/* 80*/  COLDSTART_NOISE_INDICATOR				   	,
/* 81*/  COLDSTART_ABORT_INDICATOR				   	,
/* 82*/  COLDSTART_ABORT_INHIBIT				   	,
/* 83*/  DEFAULT_CONFIG_REQUEST					    ,
/* 84*/  NO_WAKEUP_ATTEMPT						   	,   // FRCC wakeup status
/* 85*/  WAKEUP_RECEIVED_HEADER			 		    ,  	 
/* 86*/  WAKEUP_RECEIVED_WUP		 			   	,  	   
/* 87*/	 WAKEUP_COLLISION_HEADER	 			   	,  	   
/* 88*/	 WAKEUP_COLLISION_WUP					   	,  			   			 
/* 89*/	 WAKEUP_COLLISION_UNKNOWN	 			   	,  	   	  
/* 90*/	 WAKEUP_TRANSMITTED				 		    ,     						
/* 91*/	 ERROR_MODE_ACTIVE						   	,   // CC Error Vector    		  
/* 92*/  ERROR_MODE_PASSIVE						    ,       	  
/* 93*/	 ERROR_MODE_COMM_HALT					   	,     
/* 94*/	 CLOCK_CORRECTION_OK					   	,   // Clock Correction Status 1		
/* 95*/	 MISSING_OFFSET_CORRECTION_SIGNAL 		   	,  		     			  	    
/* 96*/	 OFFSET_CORRECTION_LIMIT_REACHED 		   	,  	   									
/* 97*/	 MISSING_RATE_CORRECTION_SIGNAL			    ,     									
/* 98*/	 RATE_CORRECTION_LIMIT_REACHED			   	,
/* 99*/  SYMBOL_WINDOW_NIT_OK					   	,   // Symbol window and NIT Status		
/*100*/  SYNTAX_ERROR_IN_SYMBOL_WINDOW_CHA		   	,  	   			  
/*101*/  SLOT_BOUNDARY_VIOLATION_IN_SYMBOL_WINDOW_CHA,  		  	  
/*102*/  TRANSMISSION_CONFLICT_IN_SYMBOL_WINDOW_CHA  ,      		  
/*103*/  SYNTAX_ERROR_IN_SYMBOL_WINDOW_CHB			 ,  		       
/*104*/  SLOT_BOUNDARY_VIOLATION_IN_SYMBOL_WINDOW_CHB,  	
/*105*/  TRANSMISSION_CONFLICT_IN_SYMBOL_WINDOW_CHB  ,      		   
/*106*/  SYNTAX_ERROR_DURING_NIT_CHA				 ,  								
/*107*/  SLOT_BOUNDARY_VIOLATION_DURING_NIT_CHA	    ,  									
/*108*/  SYNTAX_ERROR_DURING_NIT_CHB			    ,  	       
/*109*/  SLOT_BOUNDARY_VIOLATION_DURING_NIT_CHB	    ,  	  						   		   
/*110*/  AGGREGATED_CHANNEL_STATUS_OK			   	,   // Aggregated Channel Status 	
/*111*/  VALID_FRAME_RECEIVED_ON_CHA			   	,  		    		   
/*112*/  SYNTAX_ERROR_DETECTED_0N_CHA			   	,     									
/*113*/  CONTENT_ERROR_DETECTED_ON_CHA			   	,  	
/*114*/  COMMUNICATION_INDICATOR_CHA			   	,  
/*115*/  SLOT_BOUNDARY_VIOLATION_ON_CHA			    ,  	  
/*116*/  VALID_FRAME_RECEIVED_ON_CHB			   	,  
/*117*/  SYNTAX_ERROR_DETECTED_0N_CHB			   	,  			
/*118*/  CONTENT_ERROR_DETECTED_ON_CHB			   	,  
/*119*/  COMMUNICATION_INDICATOR_CHB			   	,   
/*120*/  SLOT_BOUNDARY_VIOLATION_ON_CHB 		   	,     
/*121*/  MESSAGE_HANDLER_STATUS_OK				   	,   // FRCC Message Handler Status
/*122*/	 PARITY_ERROR_INPUT_BUFFER				   	,  	 
/*123*/	 PARITY_ERROR_OUTPUT_BUFFER				    ,  	  		
/*124*/	 PARITY_ERROR_MESSAGE_RAM				   	,     
/*125*/  PARITY_ERROR_TRANSIENT_BUFFER_A		   	,     		 	 	    			
/*126*/  PARITY_ERROR_TRANSIENT_BUFFER_B		   	,
/*127*/  FAULTY_MESSAGE_BUFFER_DETECTED			    ,
/*128*/	 MULTIPLE_FAULTY_MESSAGE_BUFFER_DETECTED   	,
/*129*/	 CLEAR_ALL_INTERNAL_RAMS				   	,         							
/*130*/  MESSAGE_BUFFER_OK						   	,   // General Messages Buffer Status 	
/*131*/  MESSAGE_BUFFER_FULL					   	,   			   
/*132*/  MESSAGE_BUFFER_NO_DATA					    ,  				      				
/*133*/  VALID_FRAME_RECEIVED_CHA				   	,	// Transmit & Receive Buffer
/*134*/  VALID_FRAME_RECEIVED_CHB				   	,	
/*135*/  SYNTAX_ERROR_OBSERVED_CHA				   	,  	
/*136*/  SYNTAX_ERROR_OBSERVED_CHB				   	,   
/*137*/  CONTENT_ERROR_OBSERVED_CHA				    ,  		     
/*138*/  CONTENT_ERROR_OBSERVED_CHB				    ,  	   						 		
/*139*/  SLOT_BOUNDARY_VIOLATION_OBSERVED_CHA	   	,  
/*140*/  SLOT_BOUNDARY_VIOLATION_OBSERVED_CHB	   	,  	
/*141*/  TRANSMIT_CONFLICT_INDICATION_CHA		   	,   
/*142*/  TRANSMIT_CONFLICT_INDICATION_CHB		   	,   
/*143*/  EMPTY_SLOT_CHA							    ,   
/*144*/  EMPTY_SLOT_CHB							    ,   
/*145*/  MESSAGE_LOST		 					   													   

} Fr_ReturnType;									   	

#endif
											   	
#ifdef _EXTERN_								   	
#undef _EXTERN_								   	
#endif										   
											   
/* end of file*/ 							   
											   
