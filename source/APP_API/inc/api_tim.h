/**
  ******************************************************************************
  * @file    api_tim.h
  * @author  
  * @version V1.0
  * @date    2018.6.19
  * @brief   tim应用接口层
  ******************************************************************************
  */ 
#ifndef __API_TIM_H
#define __API_TIM_H

/* Define to prevent recursive inclusion -------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif 
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
// *** <<< Use Configuration Wizard in Context Menu >>> *** 
// <o>TIM_TO_TIME_ID <1-8>
// <i>The ID num of timer to time
#define  TIM_TO_TIME_ID        5
// *** <<< End of Configuration section             >>> ***  
/* Exported functions ------------------------------------------------------- */
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  初始化定时器定时操作(2到7和12到14定时器默认时钟是84M，其余的168M)
  * @param  load_value:计数装载值
  * @param  prescaler:预分频系数
  * @retval None
  */
void InitTimerToTimeApi(const u16 load_value, const u16 prescaler);
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
void InitTimToCapApi(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc);
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
void InitTimToPwmApi(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc);

/**
  * @brief  TIM定时中断处理函数 \n
  * 根据需求自己添加 请在本文件的向导中配置定时器号(仅需一个 如需要多个定时 请定义频率最高的 然后计数算出其他的) 
  * @retval None
  */
//void TIM5_IRQHandler(void)
//{
//    UBaseType_t uxSavedInterruptStatus; 
//    uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR(); 
//	if(TIM5->SR & 0x0001)//溢出中断
//	{
//		TIM5->SR &=~(1<<0);//清除中断标志位
//		{
//      }
//  }
//    portCLEAR_INTERRUPT_MASK_FROM_ISR(uxSavedInterruptStatus); 
//}

/**
  * @brief  TIM输入捕获中断处理函数 \n
  * 根据需求自己添加
  * @retval None
  */
//void TIM3_IRQHandler(void)
//{
//    u8 uRising_Falling_Flag = 0;  
//  //    UBaseType_t uxSavedInterruptStatus; 
//    uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();   
//	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET) //捕获边沿
//	{	 
//		if( uRising_Falling_Flag == 0) 	 
//		{				 
//			uRising_Falling_Flag = 1; 
//			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
//		}
//		else								 
//		{
//			uRising_Falling_Flag = 0;
//			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);	 //CC1P=1 设置为下降沿捕获
//		}
//	}
//	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1); //清除中断标志位
//}

/**
  * @brief  如定时器1的ch2是PWM模式 下面语句则是配置定时器1通道2的占空比 \n
  * 根据需求自己添加
  * @retval None
  */
//TIM1->CCR2 = 50;

#ifdef __cplusplus
}
#endif

#endif /* __API_TIM_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
