/**
  ******************************************************************************
  * @file    stm32f10x_gpio_config.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio功能模块
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
  * @brief  系统LED指示灯IO口配置
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

