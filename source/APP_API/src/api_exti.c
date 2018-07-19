/**
  ******************************************************************************
  * @file    api_exti.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   exti应用接口层
  ******************************************************************************
  */
#include "api_exti.h" 
#include "stm32f4x_exti_config.h" 
 
/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
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
void ExtiInit(GPIO_TypeDef* exti_port,const u16 exti_pin,const u8 trigger)
{
    Exti_Init(exti_port, exti_pin, trigger);
}
  
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

