/**
  ******************************************************************************
  * @file    app_magnetic_encoder.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.4
  * @brief   磁编码应用接口层
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "app_magnetic_encoder.h"

/* Private variables ---------------------------------------------------------*/
static drive_adc_desc_t s_stDrive_Adc_Handle = {0};
/* Private functions ---------------------------------------------------------*/

static u16 Read_Magnetic_Encoder_Data(const u8 adc_data_index);

/**
  * @brief  磁编码应用接口初始化
  * @param  用于操作的编码器设备句柄
  * @retval None
  */	
s8 Magnetic_Encoder_Init(magnetic_encoder_desc_t *handle)
{
    drive_adc_init(&s_stDrive_Adc_Handle);
    
    s_stDrive_Adc_Handle.rec_data_index = s_stDrive_Adc_Handle.adc_init(MAGNETIC_ENCODER_ADC_ID, MAGNETIC_ENCODER_ADC_CHANNEL);
    
    if (SIGNED_TYPE_ERR == s_stDrive_Adc_Handle.rec_data_index)
    {
       return SIGNED_TYPE_ERR;
    }
    handle->read_magnetic_encoder_data = Read_Magnetic_Encoder_Data;
    handle->rec_data_index =  s_stDrive_Adc_Handle.rec_data_index;
    
    return SIGNED_TYPE_SUCCESS;
}

/**
  * @brief  获取磁编码应用数据
  * @param  adc_data_index:ADC下的某通道对应的存储数据下标
  * @retval 经过均值滤波的adc采集值
  */
u16 Read_Magnetic_Encoder_Data(const u8 adc_data_index)
{
    return s_stDrive_Adc_Handle.achieve_adc_data(adc_data_index, MAGNETIC_ENCODER_ADC_ID);
}
