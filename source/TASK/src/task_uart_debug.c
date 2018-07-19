/**
  ******************************************************************************
  * @file    task_heart_led.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   心跳灯任务
  ******************************************************************************
  */

/*
 ***************************************************************************************
                              头文件
 ***************************************************************************************
 */

#include "stdio.h"
#include  "app_hal_init.h"
#include  "FreeRTOS.h"
#include  "task.h"

#include "app_signal_led.h"
#include "api_usart.h"
#include "stm32f4x_usart_config.h"


/*
 ****************************************************************************************
                              句柄申明
 ****************************************************************************************
 */

/*
 ****************************************************************************************
                              局部变量
 ****************************************************************************************
 */
 BaseType_t s_Ret_Status = 0;
/*
 ***************************************************************************************
                              任务函数
 ***************************************************************************************
 */
 
 u8 s_Read_Uart_Data_Buf[10];
 
/**
  * @brief  心跳灯任务函数
  * @param  None
  * @retval None
  */
void vUartDebugTask( void * pvParameters )
{ 
 //printf("time= %d \n ",led_timer);

  while(1)
	{
	
   s_Ret_Status = xQueueReceive( g_stUsartDebug.xQueue, &s_Read_Uart_Data_Buf[0], 10 / portTICK_RATE_MS);

 //  printf("buf0 = %x %x %x %x %x \n",s_Read_Uart_Data_Buf[0],s_Read_Uart_Data_Buf[1],s_Read_Uart_Data_Buf[2],
 //		 		                               s_Read_Uart_Data_Buf[3],s_Read_Uart_Data_Buf[4]);
		
	 if(s_Ret_Status == pdPASS)
	 {
		 
		 if(0x55 == s_Read_Uart_Data_Buf[0] && 0xFE == s_Read_Uart_Data_Buf[4])
		 {
         g_stUsartDebug.usart_it_config(1,ENABLE);
		 		 printf("buf1 = %x %x %x %x %x \n",s_Read_Uart_Data_Buf[0],s_Read_Uart_Data_Buf[1],s_Read_Uart_Data_Buf[2],
		 		                                  s_Read_Uart_Data_Buf[3],s_Read_Uart_Data_Buf[4]);
		 }else
     {
         /* 数据校验错误可能是数据被截断，延时一段时间,错开数据 ，实际时钟节拍也会起到延时作用,但是也有可能切换任务时刚好时钟节拍到了，那么延时就没有啦*/
	       vTaskDelay(5 / portTICK_RATE_MS);
         /* 清除寄存器,若不清除会遗留一个字节 */
			   USART1->DR;
		  	 g_stUsartDebug.usart_it_config(1,ENABLE);
		
			 
		 	 printf("buf2 = %x %x %x %x %x \n",s_Read_Uart_Data_Buf[0],s_Read_Uart_Data_Buf[1],s_Read_Uart_Data_Buf[2],
		 		                               s_Read_Uart_Data_Buf[3],s_Read_Uart_Data_Buf[4]);
		//	 printf("buf3 = %x %x %x %x %x \n",s_ucUsart1DataBuffTable[0],s_ucUsart1DataBuffTable[1],s_ucUsart1DataBuffTable[2],
		// 		                               s_ucUsart1DataBuffTable[3],s_ucUsart1DataBuffTable[4]);
			 
		 }  
	 }
	}
	
}
