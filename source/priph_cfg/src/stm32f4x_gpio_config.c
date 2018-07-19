/**
  ******************************************************************************
  * @file    stm32f4x_gpio_config.c
  * @author   
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio功能模块
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4x_gpio_config.h"

/**
  * @brief  初始化GPIO
  * @param  None
  * @retval None
  */
void pinMode(GPIO_TypeDef* GPIOx,
	uint16_t pin,
	GPIOMode_TypeDef mode,
	GPIOSpeed_TypeDef GPIO_Speed,
	GPIOOType_TypeDef GPIO_OType,
	GPIOPuPd_TypeDef GPIO_PuPd)
{
    GPIO_InitTypeDef init;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF  | RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);
	
	init.GPIO_Pin = pin;
	init.GPIO_Mode = mode;
	init.GPIO_Speed = GPIO_Speed;
	init.GPIO_OType = GPIO_OType;
	init.GPIO_PuPd = GPIO_PuPd;
	GPIO_Init(GPIOx, &init);
}


/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
