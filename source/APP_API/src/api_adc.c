/**
  ******************************************************************************
  * @file    api_adc.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   adc应用接口层
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "api_adc.h"
#include "stm32f4x_adc_config.h"

/* Private variables ---------------------------------------------------------*/
static drive_adc_desc_t s_stHandle;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  HAL注册ADC.
  * @param  handle:用于返回控制点的句柄
  * @retval None
  */
void drive_adc_init(drive_adc_desc_t * handle)
{    
    s_stHandle.adc_init         = Adc_Init;
    s_stHandle.achieve_adc_data = Achieve_Adc_Data;
    
    *handle = s_stHandle;
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
