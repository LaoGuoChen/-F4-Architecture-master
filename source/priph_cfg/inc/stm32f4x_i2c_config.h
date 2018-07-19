/**
  ******************************************************************************
  * @file    stm32f10x_i2c_config.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.15
  * @brief   i2c功能模块
  ******************************************************************************
  */
  
#ifndef  __STM32F10x_I2C_CONFIG_H
#define  __STM32F10x_I2C_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

/**
  * @brief  模拟IIC初始化
  * @param  None
  * @retval None
  */
void I2c_Init(GPIO_TypeDef* gpio_scl_port, u16 gpio_scl_pin, GPIO_TypeDef* gpio_sda_port, u16 gpio_sda_pin);
/**
  * @brief  模拟IIC根据地址读取多个字节
  * @param  None
  * @retval 非零:成功 0:失败
  */  
u8 I2cReadBytes(u8 SlaveAddress, u8 reg, u8 length, u8 *data);    
/**
  * @brief  模拟IIC根据地址写入多个字节
  * @param  None
  * @retval 1:成功 0:失败
  */  
u8 I2cWriteBytes(u8 SlaveAddress, u8 reg, u8 length, u8* data);
/**
  * @brief  硬件IIC配置初始化
  * @param  i2c_id:i2c的编号
  * @param  i2c_remap:
            -0:无重映射
            -1:重映射
  * @param  slave_addr:I2C设备的从地址
  * @retval 1:成功 0:失败
  */ 
void I2CConfig(const u8 i2c_id, const u8 i2c_remap, const u16 slave_addr);    
/**
  * @brief  硬件IIC发送数据
  * @param  addr:寄存器的地址
  * @param  data:待发送的数据
  * @retval 1:成功 0:失败
  */ 
u8 HardwareI2cSendData(u8 addr, u8 data);
/**
  * @brief  硬件IIC读取数据
  * @param  addr:寄存器的地址
  * @retval 非0:接收到的数据 0:失败
  */ 
u8 HardwareI2cReadData(u8 addr);
/**
  * @brief  硬件IIC读取多个数据
  * @param  register_addr:寄存器的地址
  * @param  data_out:接收到的数据地址
  * @param  length:待接收的数据长度
  * @retval 1:成功 0:失败
  */ 
u8 HardwareI2cReadDatas(u8 register_addr, u8 *data_out, u8 length);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

 
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

