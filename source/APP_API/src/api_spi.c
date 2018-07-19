/**
  ******************************************************************************
  * @file    api_spi.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   spi接口层
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "api_spi.h"
#include "stm32f4x_spi_config.h"
#include "common.h"
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  初始化spi
  * @param  spi_id:spi编号
  * @param  remap_par:重映射参数
  * @retval None
  */
static void InitSpiShell(const u8 spi_id, const u8 remap_par)
{
    InitSpi(spi_id, remap_par);
}
/**
  * @brief  发送消息函数
  * @param  spi_id:初始化的spi号
  * @param  spi_data_par:发送数据的地址
  * @param  spi_data_len:发送数据的长度
  * @param  txData:先发送的值
  * @retval None
  */
static u16 Spi_Send(const u8 spi_id, u8 *spi_data_par)
{
    u8 send_index = 0;
    SPI_TypeDef* SPIx = NULL;
    u16 timeout = 0x1000;
    
    if(spi_id == 1)
    {
        SPIx = SPI1;
    }
    else if(spi_id == 2)
    {
        SPIx = SPI2;
    }
    else if(spi_id == 3)
    {
        SPIx = SPI3;
    }
    
    timeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) 
    {
        if(!(--timeout))
        {
            return 0x0;
        }
    }

    /* Send byte through the SPI2 peripheral */
    SPI_I2S_SendData(SPIx, *spi_data_par);

    /* Wait to receive a byte */
    timeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if(!(--timeout))
        {
            return 0x0;
        }
    }
    
    return SPI_I2S_ReceiveData(SPIx);
}
/**
  * @brief  接收消息函数
  * @param  spi_id:初始化的spi号
  * @retval 返回的数值
  */
static u8  Spi_Receive(const u8 spi_id)
{
    SPI_TypeDef* SPIx = NULL;
    
    if(spi_id == 1)
        SPIx = SPI1;
    else if(spi_id == 2)
        SPIx = SPI2;
    else if(spi_id == 3)
        SPIx = SPI3;
    
    return SPI_I2S_ReceiveData(SPIx);
}
/**
  * @brief  先发送消息后接收消息函数
  * @param  spi_id:初始化的spi号
  * @param  txData:先发送的值
  * @retval 0：读取超时错误 >0 返回的数值
  */
static u8 Spi_TxRx(const u8 spi_id, const u8 txData)
{	
	u8 rxData = 0; 
	u16 timeout = 0x1000;
    SPI_TypeDef* SPIx = NULL;
    
    if(spi_id == 1)
        SPIx = SPI1;
    else if(spi_id == 2)
        SPIx = SPI2;
    else if(spi_id == 3)
        SPIx = SPI3;
    
    
	/* Wait until the transmit buffer is empty */
	timeout = 0x1000;
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) {
		if(!(--timeout))
			return 0x0;
	}
	SPI_I2S_SendData(SPIx, txData);
	
	/* Wait until a data is received */
	timeout = 0x1000;
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET){
		if(!(--timeout))
			return 0x0;
	}
	rxData = SPI_I2S_ReceiveData(SPIx);
	
	return (u8)rxData;
}
/**
  * @brief  spi接口层初始化
  * @param  handle:返回的句柄
  * @param  spi_id:初始化的spi号
  * @param  remap_par:重映射参数
  *         -0:无重映射                                     
  *         -1:全重映射 
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 Api_Init_Spi(drive_spi_desc_t *handle, const u8 spi_id, const u8 remap_par)    
{
    if (NULL == handle)
        return SIGNED_TYPE_ERR;

    InitSpiShell(spi_id, remap_par);
    handle->spi_send    = Spi_Send;
    handle->spi_receive = Spi_Receive;
    handle->spi_tx_rx   = Spi_TxRx;
    handle->spi_id      = spi_id;
    handle->spi_set_cs  = Set_Spi_Flash_Cs;
    
    return SIGNED_TYPE_SUCCESS;
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
