/**
  ******************************************************************************
  * @file    api_flash.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.15
  * @brief   flash应用接口层
  ******************************************************************************
  */
  
#ifndef  __API_FLASH_H
#define  __API_FLASH_H

/* Define to prevent recursive inclusion -------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif 
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
/* Exported types ------------------------------------------------------------*/
// *** <<< Use Configuration Wizard in Context Menu >>> *** 
/*
// <q>STM32_FLASH_WRITE_EN
*/
#define STM32_FLASH_WRITE_EN  1
// <o>FLASH_SPI_ID <1-3>
// <i>The ID Bum of Spi to Flash
#define  FLASH_SPI_ID  2
// *** <<< End of Configuration section             >>> ***  

#define EXPAND_WRAPPER( __NEXTLEVEL__, ...)  __NEXTLEVEL__( __VA_ARGS__ )
#define  _GET_SPI(x)   SPI##x
#define  GET_SPI(x)    EXPAND_WRAPPER(_GET_SPI, x)
    
#define FLASH_CHIP_WRITE_ENABLE             0x06 
#define FLASH_CHIP_READ_STATAUS_REG         0x05 
#define FLASH_CHIP_WIP_FLAG                 0x01  /* Write In Progress (WIP) flag */
#define FLASH_CHIP_POWER_DOWN_ADDR          0xB9
#define FLASH_CHIP_SECTOR_ERASE             0x20
#define FLASH_CHIP_PAGE_PROGRAM	            0x02 
#define FLASH_CHIP_PER_WRITE_PAGE_SIZE      256
#define FLASH_CHIP_PAGE_SIZE                256
#define FLASH_CHIP_READ_DATA                0x03   
    
/** 
  * stm_flash_read:从内部flash指定地址开始读出指定长度的数据 \n
  * stm_flash_write:从内部flash指定地址开始写入指定长度的数据 \n
  * spi_flash_write:写数据进外部flash \n
  * spi_flash_read:该驱动设备的串口号,如USBAT1则串口号为1 \n
  * Spi_Flash_Sector_Erase: 擦出flash的区域 \n
  * Spi_Flash_Power_Down: flash进入掉电模式 \n
  */
typedef struct drive_flash_desc drive_flash_desc_t;
    
struct drive_flash_desc{
#if STM32_FLASH_WRITE_EN	///<如果使能了写 
    void (*stm_flash_read)        (u32 ReadAddr,u16 *pBuffer,u16 NumToRead);
    void (*stm_flash_write)       (u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);
#endif
    void (*spi_flash_write)       (u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);                                                                                
    void (*spi_flash_read)        (u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);                 
    void (*spi_flash_erase)       (u32 SectorAddr);
    void (*spi_flash_power_down)  (void);                                                                                  
};
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  初始化spi_flash
  * @param  spi_id:spi编号
  * @param  remap_par:重映射参数
  * @retval None
  */
void Spi_Flash_Init (drive_flash_desc_t *handle, const u8 spi_id, const u8 remap_par);

#ifdef __cplusplus
}
#endif

#endif /* __API_FLASH_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
