/**
  ******************************************************************************
  * @file   stm32f10x_flash_config.h
  * @author  
  * @version V1.0
  * @date    2018.6.13
  * @brief   flash功能模块
  ******************************************************************************
  */
  
#ifndef  __STM32F40x_FLASH_CONFIG_H
#define  __STM32F40x_FLASH_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
#include "stm32f4x_spi_config.h" 
   
#if STM32_FLASH_WRITE_EN	///<如果使能了写   
/**
  * @brief  从指定地址开始读出指定长度的数据
  * @param  ReadAddr:起始地址
  * @param  pBuffer:数据指针
  * @param  NumToWrite:半字(16位)数
  * @retval None
  */ 
void Stm_Flash_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);
/**
  * @brief  从指定地址开始写入指定长度的数据
  * @param  WriteAddr:起始地址(此地址必须为2的倍数!!)
  * @param  pBuffer:数据指针
  * @param  NumToWrite:半字(16位)数 (就是要写入的16位数据的个数.) 
  * @retval None
  */ 		 
void Stm_flash_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);
/**
  * @brief  写数据进flash
  * @param  pBuffer:写入数据的地址
  * @param  WriteAddr:写入的flash地址
  * @param  NumByteToWrite:写入数据的长度
  * @retval None
  */
#endif  

void Spi_Flash_Buffer_Write(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
/**
  * @brief  从flash指定地址读取数据
  * @param  pBuffer:读取数据后存放的地址
  * @param  ReadAddr:读取的flash地址
  * @param  NumByteToWrite:写入数据的长度
  * @retval None
  */
void Spi_Flash_Buffer_Read(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
/**
  * @brief  擦出flash的区域
  * @param  SectorAddr:区域的地址
  * @retval None
  */
void Spi_Flash_Sector_Erase(u32 SectorAddr);
/**
  * @brief  flash进入掉电模式
  * @param  None
  * @retval None
  */
void Spi_Flash_Power_Down(void);
	
#ifdef __cplusplus
}
#endif/* extern "C" */

#endif


/******************* (C) COPYRIGHT 2016 HWJ *****END OF FILE****/

