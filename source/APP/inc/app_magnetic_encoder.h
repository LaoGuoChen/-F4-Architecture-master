/**
  ******************************************************************************
  * @file    app_magnetic_encoder.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.4
  * @brief   磁编码应用接口层
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_MAGNETIC_ENCODER_H
#define __APP_MAGNETIC_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
#include "api_adc.h"

/* Exported types ------------------------------------------------------------*/

/** 
  * read_magnetic_encoder_data:心跳灯正常模式 返回值：磁编码均值滤波后的数值 参数：磁编码在ADC中的数据存储下标 \n
  * rec_data_index:磁编码在ADC中的数据存储下标 \n
  */
    
typedef struct magnetic_encoder_desc magnetic_encoder_desc_t;

struct magnetic_encoder_desc{
    u16  (*read_magnetic_encoder_data) (u8 adc_index); /*!< 心跳灯正常模式 返回值：磁编码均值滤波后的数值 参数：磁编码在ADC中的数据存储下标 */
    u8   rec_data_index;                               /*!< 磁编码在ADC中的数据存储下标 */
};
/* Exported define -----------------------------------------------------------*/
#define   MAGNETIC_ENCODER_EN            (TURN_ON)
#define   MAGNETIC_ENCODER_ADC_ID        (3)
#define   MAGNETIC_ENCODER_ADC_CHANNEL   (0x20)
#define   MAGNETIC_ENCODER_CHANNEL_ID    (5)

/**
  * @brief  获取磁编码应用数据
  * @param  adc_data_index:ADC下的某通道对应的存储数据下标
  * @retval 经过均值滤波的adc采集值
  */
s8 Magnetic_Encoder_Init( magnetic_encoder_desc_t *handle);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/

