/**
  ******************************************************************************
  * @file    stm32f10x_adc_config.h
  * @author  
  * @version V1.0
  * @date    2018.6.2
  * @brief   ADC功能模块
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F40x_ADC_CONFIG_H
#define  __STM32F40x_ADC_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif

    
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
#include "api_adc.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
    
#define  SAMPLE_CNT    (10)    /*!< 采集次数 */
/* Private functions ---------------------------------------------------------*/
    
/**
  * @brief  初始化ADC
  * @param  adc_num:adc数 如1即为ADC1
  * @param  adc_channel_sum:该ADC下的所有adc通道,每二进制位数的高低代表对应通道的开启状态，如101=0x0065=0B0000000001100101代表通道0、2、5、6采集
  * @retval -1:传入参数错误,>0:adc对应通道的存储数据下标
  */
s8 Adc_Init(const u8 adc_num, const u16 adc_channel_sum);

/**
  * @brief  获取ADC的采集值
  * @param  rec_data_index:ADC下的某通道对应的存储数据下标
  * @param  adc_num:adc数,如1即为ADC1
  * @retval 0:传入参数错误,>0:经过均值滤波的adc采集值
  */
u16 Achieve_Adc_Data(const u8 rec_data_index, const u8 adc_num);

/* Exported Variable ----------------------------------------------*/        
extern volatile u8 g_vucAdc1ChannelNum;
extern volatile u8 g_vucAdc2ChannelNum;
extern volatile u8 g_vucAdc3ChannelNum;
  
#if      ADC1SAMPLE
    extern volatile u16 g_vusAdc1ValueBuff[16 * SAMPLE_CNT];  ///<建立最大数据存储ADC采集的数据
#endif
#if      ADC2SAMPLE
    extern volatile u16 g_vusAdc2ValueBuff[16 * SAMPLE_CNT];  ///<建立最大数据存储ADC采集的数据
#endif
#if      ADC3SAMPLE
    extern volatile u16 g_vusAdc3ValueBuff[16 * SAMPLE_CNT];  ///<建立最大数据存储ADC采集的数据
#endif


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

