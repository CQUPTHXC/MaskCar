
#include "chassis_task.h"
#include "math.h"
//#include "bsp_sbus.h"
#include "cmsis_os.h"
#include "stdio.h"
//#include "bsp_as5048.h"
#include "dj_m2006_3508_driver.h"
#include "pid.h"
#include "elog.h"





#define CHASSIS_CAN hcan1
#define DECE_RATIO_ER_TR  12
//extern rc_info_t rc;
//全

static void chassis_init(void);
PID_T pid1;
PID_T pid2;
float p=78.9f,i=0.000009f,d=45.f,target=3600;




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

    while(1)
    {       
	
//const motor_measure_t* motor1 = get_chassis_motor_measure_point(0);

		//PID_Sst_Target(&pid1,target);
//		PID_Sst_Target(&pid2,target*0.88824);
//				//printf(" rpm %i\r\n",motor1->speed_rpm);

//		PID_Sst_Present(&pid1,motor1->speed_rpm);
//		PID_Sst_Present(&pid2,((float)motor1->total_angle/819.2f));
//		pid2.parameter.kp=p;
//		pid2.parameter.ki=i;
//		pid2.parameter.kd=d;
//		PID_Hander(&pid2,10);
//		PID_Sst_Target(&pid1,pid2.parameter.out);
//		PID_Hander(&pid1,10);
//		
		//DJ_Set_Motor_Speed(0,360);
		DJ_Set_Motor_Position(0,3600);
		dj_motor_handler(5,2);
		//dj_set_motor_Group_A(&hcan1,pid1.parameter.out,pid1.parameter.out, pid1.parameter.out,pid1.parameter.out);

        osDelay(5);

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




















