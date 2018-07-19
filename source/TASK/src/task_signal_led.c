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


/*
 ****************************************************************************************
                              句柄申明
 ****************************************************************************************
 */
ST_SIGNAL_LED_HANDLE_T g_StSignalLedHandle_Power = {0};
ST_SIGNAL_LED_HANDLE_T g_StSignalLedHandle_Work = {0};


/*
 ***************************************************************************************
                              任务函数
 ***************************************************************************************
 */
/**
  * @brief  心跳灯任务函数
  * @param  None
  * @retval None
  */
void vSignalLedTask( void * pvParameters )
{ 
 u16 led_timer=0;  
	
	 /* 初始化LED句柄 */
	SignalLedInit(&g_StSignalLedHandle_Power,SIG_LED_NUM_A);
	SignalLedInit(&g_StSignalLedHandle_Work,SIG_LED_NUM_B);
	

	//g_StSignalLedHandle_Power.Signal_Led_Alarm( &g_StSignalLedHandle_Power );
	
	g_StSignalLedHandle_Work.Signal_Led_Err( &g_StSignalLedHandle_Work );
	
  //printf("time= %d \n ",led_timer);
	
  while(1)
	{
		led_timer++;
		

		if(0 == led_timer%10)         // 0.1s
		{
	
			
			/* 开启LED，报警模式 亮0.9秒灭0.1秒 */
			if(SIG_LED_ALARM == g_StSignalLedHandle_Power.signal_led_status)
			{
				g_StSignalLedHandle_Power.Signal_Led_On( &g_StSignalLedHandle_Power );
			}
			
			if(SIG_LED_ALARM == g_StSignalLedHandle_Work.signal_led_status)
			{
				g_StSignalLedHandle_Work.Signal_Led_On( &g_StSignalLedHandle_Work );
			}
			
			/* 开启LED 报错模式 5Hz */
			if(SIG_LED_ERROR == g_StSignalLedHandle_Power.signal_led_status)
			{
				g_StSignalLedHandle_Power.Signal_Led_On( &g_StSignalLedHandle_Power );
			}
			
			if(SIG_LED_ERROR == g_StSignalLedHandle_Work.signal_led_status)
			{
				g_StSignalLedHandle_Work.Signal_Led_On( &g_StSignalLedHandle_Work );
			}
			
		}
		
		if(0 == led_timer%20)   // 0.2s
    {
				/* 关闭LED 报错模式 5Hz */
			if(SIG_LED_ERROR == g_StSignalLedHandle_Power.signal_led_status)
			{
				g_StSignalLedHandle_Power.Signal_Led_Off( &g_StSignalLedHandle_Power );
			}
			
			if(SIG_LED_ERROR == g_StSignalLedHandle_Work.signal_led_status)
			{
				g_StSignalLedHandle_Work.Signal_Led_Off( &g_StSignalLedHandle_Work );
			}
			
		}
		
		if(0 == led_timer%40)   // 0.4s
    {
		
			
		}
		
		if(0 == led_timer%50)   // 0.5s
    {
			/* 开启LED 2Hz*/
			if(SIG_LED_NOMAL == g_StSignalLedHandle_Power.signal_led_status)
			{
				g_StSignalLedHandle_Power.Signal_Led_On( &g_StSignalLedHandle_Power );
			}
			
			if(SIG_LED_NOMAL == g_StSignalLedHandle_Work.signal_led_status)
			{
				g_StSignalLedHandle_Work.Signal_Led_On( &g_StSignalLedHandle_Work );
			}
		}
		
		if(0 == led_timer%100)  // 1s
    {
			/* 关闭LED，报警模式 亮0.9秒灭0.1秒  正常模式2Hz*/
			if(SIG_LED_NOMAL == g_StSignalLedHandle_Power.signal_led_status || 
				 SIG_LED_ALARM == g_StSignalLedHandle_Power.signal_led_status)
			{
				g_StSignalLedHandle_Power.Signal_Led_Off( &g_StSignalLedHandle_Power );
			}
			
			if(SIG_LED_NOMAL == g_StSignalLedHandle_Work.signal_led_status || 
				 SIG_LED_ALARM == g_StSignalLedHandle_Work.signal_led_status)
			{
				g_StSignalLedHandle_Work.Signal_Led_Off( &g_StSignalLedHandle_Work );
			}
		}
		
		if(0 == led_timer%1000) // 10s
    {
			led_timer = 0;
		}else{}
		
		vTaskDelay(10 / portTICK_RATE_MS);

	}
	
}
