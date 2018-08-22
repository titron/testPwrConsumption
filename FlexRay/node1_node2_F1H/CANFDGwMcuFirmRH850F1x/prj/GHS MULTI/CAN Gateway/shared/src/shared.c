
#pragma ghs startdata										// locate to Global RAM
#pragma ghs section bss=".slbss"				// in SLBSS Section	
 volatile unsigned int global_var;
#pragma ghs section									
#pragma ghs enddata		
