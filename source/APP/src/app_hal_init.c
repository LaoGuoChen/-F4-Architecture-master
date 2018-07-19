/**
  ******************************************************************************
  * @file    app_hal_init.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   接口层初始化
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "app_hal_init.h"

/*
 *******************************************************************************
                                  全局变量
 *******************************************************************************
 */
drive_usart_desc_t      g_stUsartDebug            = {0};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  模块硬件初始化
  * @param  None
  * @retval None
  */
void ModulesHalInit(void)
{    
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	  /* 调试 printf，串口debug初始化 */
   #if USART1_EN
      Api_Init_Usart(&g_stUsartDebug, 1, 0, 115200);
      g_stUsartDebug.set_usart_print(g_stUsartDebug.usart_id);
   #endif
	
	/* Led指示灯初始化 */

}


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
