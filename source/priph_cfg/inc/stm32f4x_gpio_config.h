/**
  ******************************************************************************
  * @file    stm32f10x_gpio_config.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio����ģ��
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F40x_GPIO_CONFIG_H
#define  __STM32F40x_GPIO_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif
    
    
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  ϵͳLEDָʾ��IO������
  * @param  None
  * @retval None
  */
void pinMode(GPIO_TypeDef* GPIOx,
	uint16_t pin,
	GPIOMode_TypeDef mode,
	GPIOSpeed_TypeDef GPIO_Speed,
	GPIOOType_TypeDef GPIO_OType,
	GPIOPuPd_TypeDef GPIO_PuPd);

    
    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

