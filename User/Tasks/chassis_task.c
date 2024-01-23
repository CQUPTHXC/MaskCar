
#include "chassis_task.h"
#include "math.h"
//#include "bsp_sbus.h"
#include "cmsis_os.h"
#include "stdio.h"
//#include "bsp_as5048.h"
#include "dj_m2006_3508_driver.h"
#include "pid.h"
#include "elog.h"

#include "bsp_sbus.h"
#include "tim.h"

#define CHASSIS_CAN hcan1
#define DECE_RATIO_ER_TR  12
#define cos45 0.70711
extern rc_info_t rc;
//全
extern int cnt;
static void chassis_init(void);
PID_T pid1;
PID_T pid2;
float p=78.9f,i=0.000009f,d=45.f,target=3600;

float wheel_speed1;
float wheel_speed2;
float wheel_speed3;
float wheel_speed4;

///**
//  * @brief          底盘任务，间隔 CHASSIS_CONTROL_TIME_MS 2ms
//  * @param[in]      pvParameters: 空
//* @retval         none 1:
//  */
void chassis_task(void const * argument)
{
/* 初始化elog */
	elog_init();
	/* 设置每个级别的日志输出格*/
	elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
	//输出日志级别信息和日志TAG
	elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG);
	elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG);
	elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG);
	elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_LVL | ELOG_FMT_TAG);
	//除了时间、进程信息线程信息之外，其余全部输出
	//elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_TIME | ELOG_FMT_P_INFO | ELOG_FMT_T_INFO));
	
	elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL);
	elog_set_text_color_enabled(true);
	/* 启动elog */
	elog_start();
	
		
    chassis_init();
		dbus_uart_init();
    while(1)
    {       
//
//		static float r=34.9;
//		static float angle=0;

//		if(rc.ch1<0)
//		{
//			r=34.9 + 1.f/(float)(rc.ch1);
//		}else
//		{
//			r=-34.9 - 1.f/(float)(rc.ch1);
//		}
//		angle=asin(20/r) * 180.0/3.1416;
			
			
		 wheel_speed1 = (float)rc.ch3*cos45 + (float)rc.ch4*cos45+(float)rc.ch2;
		 wheel_speed1 =  wheel_speed1/10*19;
     wheel_speed2 = (float)rc.ch3*cos45 - (float)rc.ch4*cos45+(float)rc.ch2;
		 wheel_speed2 =  wheel_speed2/10*19;
     wheel_speed3 = -(float)rc.ch3*cos45 - (float)rc.ch4*cos45+(float)rc.ch2;
		 wheel_speed3 =  wheel_speed3/10*19;
     wheel_speed4 = -(float)rc.ch3*cos45 + (float)rc.ch4*cos45+(float)rc.ch2;
		 wheel_speed4 =  wheel_speed4/10*19;
		
		
		 DJ_Set_Motor_Speed(0,wheel_speed1);
		 DJ_Set_Motor_Speed(1,wheel_speed2);    
		 DJ_Set_Motor_Speed(2,wheel_speed3);
		 DJ_Set_Motor_Speed(3,wheel_speed4);
		
	
		dj_motor_handler(5,2);
		//__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,1080);
		//elog_raw_output("%.2f,%.2f,%.2f,%.2f\n",wheel_speed1,wheel_speed2,wheel_speed3,wheel_speed4);  

    }
}



///**
//  * @brief          初始化"chassis_move"变量，包括pid初始化， 遥控器指针初始化，3508底盘电机指针初始化，云台电机初始化，陀螺仪角度指针初始化
//  * @param[out]     Chassis_Move_Init:"chassis_move_t"变量指针.
//  * @retval         none
//  */
static void chassis_init(void)
{

PID_Init(&pid1,PID_POSITION_NULL,5.f,0.03f,1.0f);
PID_Sst_Out_Limit(&pid1,30000);
PID_Sst_Integral_Limit(&pid1,2000);
PID_Sst_Bias_Dead_Zone(&pid1,10);

PID_Init(&pid2,PID_POSITION_NULL,0.001f,0.01f,0.0f);
PID_Sst_Out_Limit(&pid1,20000);
PID_Sst_Integral_Limit(&pid1,9);
//PID_Sst_Bias_Dead_Zone(&pid1,10);


}




















