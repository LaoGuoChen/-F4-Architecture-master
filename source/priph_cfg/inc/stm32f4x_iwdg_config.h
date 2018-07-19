/**
  ******************************************************************************
  * @file   stm32f10x_iwdg_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.15
  * @brief   iwdg功能模块
  ******************************************************************************
  */
#ifndef  __STM32F40x_IWDG_CONFIG_H
#define  __STM32F40x_IWDG_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

/**
  * @brief  初始化看门狗分频 喂狗时间函数
  * @param  prer：预分频  
  * @param  rlr：看门狗计数器重装载值  
  * @note   复位时间ms：Tout=((4*2^prer)*rlr)/40 :有个4是因为看门狗分频寄存器(IWDG_PR)的值 \n
			并不是2^prer就对应的分频还要乘4才是分频，具体看手册。看门狗时钟40KHZ  
  * @retval None
*/
void Iwdg_Init(const u8 prer, const u16 rlr);
/**
  * @brief  喂狗函数；超过喂狗时间不喂狗就复位
  * @param  None
  * @retval None
*/
void Iwdg_Feed(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/

