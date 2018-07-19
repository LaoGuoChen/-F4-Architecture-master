/**
  ******************************************************************************
  * @file    stm32f40x_usart_config.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   usart功能模块
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F40x_USART_CONFIG_H
#define  __STM32F40x_USART_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"	
#include "api_usart.h"
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
  
/**
  * @brief  串口初始化总入口
  * @param  handle:注册后返回的句柄
  * @param  usart_id:串口号
  * @param  remap_par:重映射参数
  *         -0:无重映射                                    
  *         -1:该串口有部分重映射则部分重映射，无则全重映射     
  *         -2:全重映射  
  * @param  baud_par:波特率
  * @retval -1:错误 0:成功
  */
s8 InitUsartShell(drive_usart_desc_t *handle, const u8 usart_id, const u8 remap_par, const u32 baud_par);

/**
  * @brief  串口中断设置
  * @param  usart_id:串口号
  * @param  enable:中断使能 0关闭 1开启 
  * @retval None
  */
void UsartItConfig(const u8 usart_id, FunctionalState NewState);

/**
  * @brief  设置串口为打印串口
  * @param  usart_id:串口号
  * @retval -1:错误 0:成功
  */
s8 SetUsartPrintFun(const u8 usart_id);
    
extern u8 s_ucUsart1DataBuffTable[USART1_QUEUE_TYPE_L];  

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

