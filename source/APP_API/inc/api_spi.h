/**
  ******************************************************************************
  * @file    api_spi.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.13
  * @brief   spi接口层
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __API_SPI_H
#define  __API_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
/* Exported types ------------------------------------------------------------*/
/** 
  * spi_init:spi初始化 \n
  * spi_send:发送消息函数 \n
  * spi_receive:接收消息函数 \n
  * spi_tx_rx:先发送消息后接收消息函数 \n
  * spi_id:该驱动设备的串口号,如spi1则编号为1 \n
  */
typedef struct drive_spi_desc drive_spi_desc_t;
    
struct drive_spi_desc{                                                                  
    u16  (*spi_send)       (u8 spi_id, u8 *spi_data_par);                       /*!< 发送消息函数 */
    u8   (*spi_receive)    (u8 spi_id);                                         /*!< 接收消息函数 */
    u8   (*spi_tx_rx)      (u8 spi_id, u8 txData);                              /*!< 先发送消息后接收消息函数 */
    void (*spi_set_cs)     (u8 cs_status);                                      /*!< 设置SPI片选高低状态 */
    u8    spi_id;                                                               /*!< 该驱动设备的spi号 如spi1则为1 */
};
    
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  spi接口层初始化
  * @param  handle:返回的句柄
  * @param  spi_id:初始化的spi号
  * @param  remap_par:重映射参数
  *         -0:无重映射                                     
  *         -1:全重映射 
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 Api_Init_Spi(drive_spi_desc_t *handle, const u8 spi_id, const u8 remap_par);    


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/


