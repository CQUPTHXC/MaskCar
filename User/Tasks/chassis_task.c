
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


#define CHASSIS_CAN hcan1
#define DECE_RATIO_ER_TR  12
extern rc_info_t rc;
//ȫ

static void chassis_init(void);
PID_T pid1;
PID_T pid2;
float p=78.9f,i=0.000009f,d=45.f,target=3600;




///**
//  * @brief          �������񣬼�� CHASSIS_CONTROL_TIME_MS 2ms
//  * @param[in]      pvParameters: ��
//* @retval         none 1:
//  */
void chassis_task(void const * argument)
{
/* ��ʼ��elog */
	elog_init();
	/* ����ÿ���������־�����*/
	elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
	//�����־������Ϣ����־TAG
	elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG);
	elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG);
	elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG);
	elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_LVL | ELOG_FMT_TAG);
	//����ʱ�䡢������Ϣ�߳���Ϣ֮�⣬����ȫ�����
	//elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_TIME | ELOG_FMT_P_INFO | ELOG_FMT_T_INFO));
	
	elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL);
	elog_set_text_color_enabled(true);
	/* ����elog */
	elog_start();
	
		
    chassis_init();
		dbus_uart_init();
    while(1)
    {       
//
		static float r=34.9;
		static float angle=0;

		if(rc.ch1<0)
		{
			r=34.9 + 1.f/(float)(rc.ch1);
		}else
		{
			r=-34.9 - 1.f/(float)(rc.ch1);
		}
		angle=asin(20/r) * 180.0/3.1416;
		
		
		DJ_Set_Motor_Speed(0,rc.ch2*4);
		//DJ_Set_Motor_Position(1,rc.ch1/67*3);
		DJ_Set_Motor_Position(1,angle);
			
		DJ_Set_Motor_Speed(2,rc.ch2*4);
		DJ_Set_Motor_Position(3,0);
		//DJ_Set_Motor_Position(1,rc.ch1/67*3);
		
		DJ_Set_Motor_Speed(4,rc.ch2*4);
		DJ_Set_Motor_Position(5,angle);
		



		DJ_Set_Motor_Speed(8,-rc.ch2*4);
		DJ_Set_Motor_Position(9,angle);
		
		DJ_Set_Motor_Speed(10,-rc.ch2*4);
		DJ_Set_Motor_Position(11,0);
		
		DJ_Set_Motor_Speed(12,-rc.ch2*4);
		DJ_Set_Motor_Position(13,angle);
		
		dj_motor_handler(5,2);
		
		elog_raw_output(":%f,%f,%f,%f\n",rc.ch1,rc.ch2,rc.ch3,rc.ch4);        
		osDelay(5);

    }
}



///**
//  * @brief          ��ʼ��"chassis_move"����������pid��ʼ���� ң����ָ���ʼ����3508���̵��ָ���ʼ������̨�����ʼ���������ǽǶ�ָ���ʼ��
//  * @param[out]     Chassis_Move_Init:"chassis_move_t"����ָ��.
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




















