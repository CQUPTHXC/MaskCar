#include "cmsis_os.h"
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
#include "bsp_sbus.h"
		extern PID_T pid1;
		extern PID_T pid2;
		extern float p,i,d;
		extern rc_info_t rc;
void test_task(void const * argument)
{


	while(1)
	{
		if(rc.ch5==1){
		DJ_Set_Motor_Speed(8,0);
		
		DJ_Set_Motor_Speed(9,0);
		
		DJ_Set_Motor_Speed(10,0);
		}
		else if(rc.ch5==3){
		DJ_Set_Motor_Speed(8,1500);
		
		DJ_Set_Motor_Speed(9,-1500);
		
		DJ_Set_Motor_Speed(10,2500);
		}
		else if(rc.ch5==2){
		DJ_Set_Motor_Speed(8,2500);
		
		DJ_Set_Motor_Speed(9,-2500);
		
		DJ_Set_Motor_Speed(10,2500);
		}
		

		dj_motor_handler(5,2);

	}
}






