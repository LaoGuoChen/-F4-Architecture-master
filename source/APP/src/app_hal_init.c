/**
  ******************************************************************************
  * @file    app_hal_init.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   �ӿڲ��ʼ��
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "app_hal_init.h"

/*
 *******************************************************************************
                                  ȫ�ֱ���
 *******************************************************************************
 */
drive_usart_desc_t      g_stUsartDebug            = {0};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ģ��Ӳ����ʼ��
  * @param  None
  * @retval None
  */
void ModulesHalInit(void)
{    
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	  /* ���� printf������debug��ʼ�� */
   #if USART1_EN
      Api_Init_Usart(&g_stUsartDebug, 1, 0, 115200);
      g_stUsartDebug.set_usart_print(g_stUsartDebug.usart_id);
   #endif
	
	/* Ledָʾ�Ƴ�ʼ�� */

}


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
