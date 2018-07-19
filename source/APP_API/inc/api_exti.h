/**
  ******************************************************************************
  * @file    api_exti.h
  * @author  
  * @version V1.0
  * @date    2018.6.2
  * @brief   exti应用接口层
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_EXTI_H
#define __API_EXTI_H


#ifdef __cplusplus
 extern "C" {
#endif 
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Private functions ---------------------------------------------------------*/
     
/**
  * @brief  外部中断初始化
  * @param  exti_port:外部端口
  * @param  exti_pin:外部引脚
  * @param  trigger:触发方式
            -0:上升沿
            -1:下降沿
            -2:上升下降沿
  * @retval None
  */
void ExtiInit(GPIO_TypeDef* exti_port, const u16 exti_pin, const u8 trigger);

/**
  * @brief  外部触发中断 \n
  * 根据自己需求定义实现。
  * @retval None
  */

//void EXTI0_IRQHandler(void)
//{
//	EXTI_ClearFlag(EXTI_Line0);
//}

#ifdef __cplusplus
}
#endif

#endif /* __API_EXTI_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
