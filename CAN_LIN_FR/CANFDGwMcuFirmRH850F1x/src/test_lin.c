#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ree_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#include "riic_application.h"

#include <rlin2.h>
#include <rlin2_a.h>
#include <rlin2_s.h>

#include <rlin3.h>
#include <rlin3_a.h>
#include <rlin3_s.h>

u08	RLIN2Master[MAX_LIN_BUS_NUM][2] =
{
	{0 , 1},	/* RLIN21 */
	{0 , 2},	/* RLIN22 */
	{1 , 3},	/* RLIN27 */
	{2 , 0},	/* RLIN28 */
	{2 , 1}		/* RLIN29 */
};

u08	RLIN3Slave[MAX_LIN_BUS_NUM] =
{
	0,	/* RLIN30 */
	1,	/* RLIN31 */
	2,	/* RLIN32 */
	3,	/* RLIN33 */
	4	/* RLIN34 */
};

void powertest_lin_rlin2_m_rlin3_s (void)
{
	u08 i;

//    Cetic_CAN_LIN_TRA_turn_Off();
#if ACTIVATE_LIN_BUS_NUM == 1
    	//Cetic_CAN_LIN_TRA_turn_On(Transceiver_RLIN30_RLIN20);
    	//Cetic_CAN_LIN_TRA_turn_On(Transceiver_RLIN34_RLIN24);
#elif ACTIVATE_LIN_BUS_NUM == 5
//    	Cetic_CAN_LIN_TRA_turn_On(Transceiver_ALL_RLIN);
#else
		#error "LIN bus number isn't defined"
#endif

    for(i = (u08)0; i < ACTIVATE_LIN_BUS_NUM; i ++)
    //for(i = (u08)4; i < 5; i ++)
    {
		RLIN3_LINSlaveActivation(RLIN3Slave[i], LIN_BAUDRATE);
    }

	while(1)
	{
	    for(i = (u08)0; i < ACTIVATE_LIN_BUS_NUM; i ++)
		//for(i = (u08)4; i < 5; i ++)
	    {
	    	RLIN2_LINMasterExecution_StateManage(RLIN2Master[i][0], RLIN2Master[i][1], i, LIN_BAUDRATE);
	    }
	}
}
