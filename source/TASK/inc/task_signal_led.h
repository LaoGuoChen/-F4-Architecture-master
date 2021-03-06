/**
  ******************************************************************************
  * @file    task_signal_led.h
  * @author  chen.g  
  * @version V1.0
  * @date    2018.7.17
  * @brief   指示灯任务
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __TASK_SIGNAL_LED_H
#define __TASK_SIGNAL_LED_H

#ifdef __cplusplus
extern "C" {
#endif

/*
****************************************************************************************
                              头文件
****************************************************************************************
*/
#include "stm32f4xx_conf.h"
#include "app_signal_led.h"
	

/*
 ****************************************************************************************
                            任务函数申明
 ****************************************************************************************
 */
void vSignalLedTask( void * pvParameters );

	
	
/*
 ****************************************************************************************
                            全局变量
 ****************************************************************************************
 */
 

extern ST_SIGNAL_LED_HANDLE_T g_StSignalLedHandle_Power;
extern ST_SIGNAL_LED_HANDLE_T g_StSignalLedHandle_Work;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
