/**
 * @file shell_port.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-02-22
 * 
 * @copyright (c) 2019 Letter
 * 
 */

#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "shell.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "elog.h"
#include "cmsis_os.h"
#include "stdbool.h"
#include "semphr.h"

#include "kfifo.h"

Shell shell;
char shellBuffer[512];
char shelldata=0;
struct kfifo shell_rxfifo;
//static SemaphoreHandle_t shellMutex;


/**
 * @brief 用户shell写
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际写入的数据长度
 */
short userShellWrite(char *data, unsigned short len)
{
	HAL_UART_Transmit(&huart6,(uint8_t*)data,len,0xffff);
//		while(huart6.gState != HAL_UART_STATE_READY)
//	{
//		osDelay(1);
//	}
//	HAL_UART_Transmit_IT(&huart6,(uint8_t*)data,len);

	return len;
}


/**
 * @brief 用户shell读
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际读取到
 */
short userShellRead(char *data, unsigned short len)
{
	
	uint32_t cnt=kfifo_out(&shell_rxfifo,(uint8_t*)data,len);
	if(!cnt)osDelay(5);
	return cnt;
}
/**
 * @brief 用户shell上锁
 * 
 * @param shell shell
 * 
 * @return int 0
 */
int userShellLock(Shell *shell)
{

	extern SemaphoreHandle_t xMutex_Usart1;
	BaseType_t xStatus;
	xStatus = xSemaphoreTakeRecursive(xMutex_Usart1, 10);
	//log_d("shell_get");

    return xStatus;
}

/**
 * @brief 用户shell解锁
 * 
 * @param shell shell
 * 
 * @return int 0       
 */
int userShellUnlock(Shell *shell)
{

	extern SemaphoreHandle_t xMutex_Usart1;
	BaseType_t xStatus;
	xStatus  = xSemaphoreGiveRecursive(xMutex_Usart1);
	//log_d("shell_give");

  return xStatus;
}



//void uartLogWrite(char *buffer, short len)
//{
//    if (uartLog.shell)
//    {
//        shellWriteEndLine(uartLog.shell, buffer, len);
//    }
//}


/**
 * @brief 用户shell初始化
 * 
 */
void userShellInit(void)
{

    shell.write = userShellWrite;
    shell.read = userShellRead;
    shell.lock = userShellLock;
    shell.unlock = userShellUnlock;
    shellInit(&shell, shellBuffer, 512);
		//logRegister(&uartLog, &shell);
		static uint8_t rxbuffer[128]={0};
		kfifo_init(&shell_rxfifo,rxbuffer,sizeof(rxbuffer));
		extern void var_init(void);
		var_init();


		HAL_UART_Receive_IT(&huart6,(uint8_t*)&shelldata,1);

    if (xTaskCreate(shellTask, "shell", 512, &shell, 15, NULL) != pdPASS)
    {
        //logError("shell task creat failed");
    }
}

/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static int cnt=0;
	if(huart==&huart6){
		//extern Shell shell;
		//extern uint8_t shelldata;	
		//extern struct kfifo shell_rxfifo;	
		uint8_t data=shelldata;//不要删
		HAL_UART_Receive_IT(&huart6,(uint8_t*)&shelldata,1);//
		cnt++;
		kfifo_in(&shell_rxfifo,&data,1);
	  //shellHandler(&shell, data);

	}

	
	
	
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	
   char a = huart->Instance->DR;
			__HAL_UART_CLEAR_NEFLAG(huart);  //读DR寄存器，就可以清除ORE错误标志位

			__HAL_UART_CLEAR_FEFLAG(huart);  //读DR寄存器，就可以清除ORE错误标志位

			__HAL_UART_CLEAR_OREFLAG(huart);  //读DR寄存器，就可以清除ORE错误标志位
		

	
}

//CEVENT_EXPORT(EVENT_INIT_STAGE2, userShellInit);


