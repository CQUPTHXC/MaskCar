#include "cmsis_os.h"
//#include "test_task.h"
//#include "bsp_as5048.h"
//#include "vofa_lower.h"
//#include "bldc_interface.h"
//#include "bsp_sbus.h"
//#include "bsp_vesc.h"
#include "can.h"
#include "dj_m2006_3508_driver.h"
#include "stdio.h"
#include "pid.h"
//#include "vofa_lower.h"
#include "shell.h"
#include "commend.h"
#include <stdarg.h>
#include <stdlib.h>
#include "elog.h"

		extern PID_T pid1;
		extern PID_T pid2;
		extern float p,i,d;

void test_task(void const * argument)
{
//	const rc_info_t* _rc = get_remote_control_point();
//	Init_test_AS5048();
			//log_d(" t:%.0f,%.0f,%.0f",pid1.parameter.present,pid1.parameter.target,pid1.parameter.out);

	while(1)
	{

		//Test_AS5048();
			//elog_raw_output(" t:%.0f,%.0f,%.0f\r\n",pid2.parameter.present,pid2.parameter.target,pid2.parameter.out);

			//log_d(" t:%.0f,%.0f,%.0f",pid1.parameter.present,pid1.parameter.target,pid1.parameter.out);


		osDelay(40);

	}
}






