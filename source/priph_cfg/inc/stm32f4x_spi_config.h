/**
  ******************************************************************************
  * @file    stm32f10x_spi_config.h
  * @author  
  * @version V1.0
  * @date    2018.6.2
  * @brief   spi功能模块
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F40x_SPI_CONFIG_H
#define  __STM32F40x_SPI_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

/* Private functions ---------------------------------------------------------*/
    
/**
  * @brief  初始化spi
  * @param  spi_id:spi编号
  * @param  remap_par:重映射参数
  * @retval None
  */
void InitSpi(const u8 spi_id, const u8 remap_par);
/**
  * @brief  设置spi flash的片选信号电平
  * @param  spi_id:spi编号
  * @retval None
  */
void Set_Spi_Flash_Cs(u8 cs_level);

#ifdef __cplusplus
}
#endif/* extern "C" */

#endif


/******************* (C) COPYRIGHT 2016 HWJ *****END OF FILE****/

