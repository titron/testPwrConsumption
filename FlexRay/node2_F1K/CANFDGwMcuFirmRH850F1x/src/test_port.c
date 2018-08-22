#include <test_port.h>

void port_test_delay(void)
{
	int delay_small = 1000;
	int delay_big = 1000;

	do{
		do{
			delay_small--;
		}while(delay_small > 0);

		delay_big--;
	}while(delay_big > 0);
}

void port_init(void)
{
	PORT_Enable( EE_FR_PORT_TEST, EE_FR_PORT_BIT_TEST,
	               PORT_DIR_OUTPUT, PORT_MODE_IO,
	               PORT_FUNCTION_NORMAL );
    PORT_WriteBit( EE_FR_PORT_TEST, EE_FR_PORT_BIT_TEST, 1 );
}

void port_test(void)
{
	PORT_Enable( EE_FR_PORT_TEST, EE_FR_PORT_BIT_TEST,
	               PORT_DIR_OUTPUT, PORT_MODE_IO,
	               PORT_FUNCTION_NORMAL );
    PORT_WriteBit( EE_FR_PORT_TEST, EE_FR_PORT_BIT_TEST, 1 );

    while(1)
    {
    	PORT_WriteBit( EE_FR_PORT_TEST, EE_FR_PORT_BIT_TEST, 1 );
    	port_test_delay();
    	PORT_WriteBit( EE_FR_PORT_TEST, EE_FR_PORT_BIT_TEST, 0 );
    	port_test_delay();
    }
//	PORT_Enable( EE_FR_PORT_ENA, EE_FR_PORT_BIT_ENA,
//	               PORT_DIR_OUTPUT, PORT_MODE_IO,
//	               PORT_FUNCTION_NORMAL );
//	  PORT_WriteBit( EE_FR_PORT_ENA, EE_FR_PORT_BIT_ENA, 1 );
}

// End of file
