/**
  ******************************************************************************
  * @file    api_tim.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.19
  * @brief   tim应用接口层
  ******************************************************************************
  */
#include "api_tim.h"
#include "stm32f4x_tim_config.h"

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  初始化定时器定时操作
  * @param  load_value:计数装载值
  * @param  prescaler:预分频系数
  * @retval None
  */
void InitTimerToTimeApi(const u16 load_value, const u16 prescaler)
{
    InitTimerToTime(load_value, prescaler);
}
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
void InitTimToCapApi(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc)
{
    InitTimToCap(tim_id, channel, remap, arr, psc);
}
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
void InitTimToPwmApi(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc)
{
    InitTimToPwm(tim_id, channel, remap, arr, psc);
}
  
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
