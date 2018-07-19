/**
  ******************************************************************************
  * @file    app_hal_init.h
  * @author  
  * @version V1.0
  * @date    2018.6.2
  * @brief   �ӿڲ��ʼ��
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __HWJ_HALINIT_H
#define  __HWJ_HALINIT_H

#ifdef __cplusplus
extern "C" {
#endif
	
    
/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "api_usart.h"
#include "app_magnetic_encoder.h"
#include "api_can.h"
#include "api_spi.h"
#include "api_exti.h"
#include "api_flash.h"
#include "stm32f4x_can_config.h"


/*
 *******************************************************************************
	                                ���⺯������
 *******************************************************************************
 */
void ModulesHalInit(void);

/*
 *******************************************************************************
	                                ȫ�ֱ���
 *******************************************************************************
 */
extern  drive_usart_desc_t  g_stUsartDebug;  


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
