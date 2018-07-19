/**
  ******************************************************************************
  * @file    stm32f10x_exti_config.h
  * @author  
  * @version V1.0
  * @date    2018.6.15
  * @brief   exti功能模块
  ******************************************************************************
  */
  
#ifndef  __STM32F40x_EXTI_CONFIG_H
#define  __STM32F40x_EXTI_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

/**
  * @brief  外部中断初始化
  * @param  exti_port:外部端口
  * @param  exti_pin:外部引脚
  * @param  trigger:触发方式
            -0:上升沿
            -1:下降沿
            -2:上升下降沿
  * @retval None
  */
void Exti_Init(GPIO_TypeDef* exti_port, const u16 exti_pin, const u8 trigger);
    

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

