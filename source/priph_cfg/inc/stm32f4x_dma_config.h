/**
  ******************************************************************************
  * @file    stm32f10x_dma_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio功能模块
  ******************************************************************************
  */
  
#ifndef  __STM32F40x_DMA_CONFIG_H
#define  __STM32F40x_DMA_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

/**
  * @brief  ADC1的DMA配置
  * @param  None
  * @retval None
  */
void DMA_ADC1_Config(void);
/**
  * @brief  ADC3的DMA配置
  * @param  None
  * @retval None
  */
void DMA_ADC3_Config(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
