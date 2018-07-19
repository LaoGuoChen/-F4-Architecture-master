/**
  ******************************************************************************
  * @file   stm32f10x_tim_config.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.15
  * @brief   spi功能模块
  ******************************************************************************
  */
  
#ifndef  __STM32F40x_TIM_CONFIG_H
#define  __STM32F40x_TIM_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  初始化定时器定时操作
  * @param  load_value:计数装载值
  * @param  prescaler:预分频系数
  * @retval None
  */
void InitTimerToTime(const u16 load_value, const u16 prescaler);
/**
  * @brief  初始化定时器输入捕获操作
  * @param  tim_id:定时器的编号
  * @param  channel:通道数和，后四位每位的高低状态表示CH1-4的选择状态。如0x06表示选择了CH2和CH4.
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该串口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @param  arr:重载计数
  * @param  psc:预分频系数
  * @retval None
  */
void InitTimToCap(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc);
/**
  * @brief  初始化定时器PWM操作
  * @param  tim_id:定时器的编号
  * @param  channel:通道数和，后四位每位的高低状态表示CH1-4的选择状态。如0x06表示选择了CH2和CH4.
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该串口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @param  arr:重载计数
  * @param  psc:预分频系数
  * @retval None
  */
void InitTimToPwm(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
