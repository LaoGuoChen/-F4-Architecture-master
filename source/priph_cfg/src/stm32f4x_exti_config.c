/**
  ******************************************************************************
  * @file    stm32f4x_exti_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.15
  * @brief   exti功能模块
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4x_exti_config.h"


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
void Exti_Init(GPIO_TypeDef* exti_port,const u16 exti_pin,const u8 trigger)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    u8  port_source = 0, pin_source = 0;
    u32 exti_Line = 0;
    static u8 exti_irq_cnt = 0;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD \
    | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);
	GPIO_InitStructure.GPIO_Pin = exti_pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
    if (trigger == 0)
    {    
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    }
    else if (trigger == 1)
    {
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    }
    else if (trigger == 2)
    {
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    }
	GPIO_Init(exti_port, &GPIO_InitStructure);
    
    if (exti_port == GPIOA)
    {
        port_source = EXTI_PortSourceGPIOA;
    }
    else if (exti_port == GPIOB)
    {
        port_source = EXTI_PortSourceGPIOB;
    }
    else if (exti_port == GPIOC)
    {
        port_source = EXTI_PortSourceGPIOC;
    }
    else if (exti_port == GPIOD)
    {
        port_source = EXTI_PortSourceGPIOD;
    }
    else if (exti_port == GPIOE)
    {
        port_source = EXTI_PortSourceGPIOE;
    }    
    else if (exti_port == GPIOF)
    {
        port_source = EXTI_PortSourceGPIOF;
    }
    else if (exti_port == GPIOG)
    {
        port_source = EXTI_PortSourceGPIOG;
    }
    else if (exti_port == GPIOH)
    {
        port_source = EXTI_PortSourceGPIOH;
    }
    else if (exti_port == GPIOI)
    {
        port_source = EXTI_PortSourceGPIOI;
    }
    
    switch (exti_pin)
    {
        case GPIO_Pin_0:
            pin_source = GPIO_PinSource0;
            exti_Line  = EXTI_Line0;
            break;
        case GPIO_Pin_1:
            pin_source = GPIO_PinSource1;
            exti_Line  = EXTI_Line1;
            break;
        case GPIO_Pin_2:
            pin_source = GPIO_PinSource2;
            exti_Line  = EXTI_Line2;
            break;
        case GPIO_Pin_3:
            pin_source = GPIO_PinSource3;
            exti_Line  = EXTI_Line3;
            break;
        case GPIO_Pin_4:
            pin_source = GPIO_PinSource4;
            exti_Line  = EXTI_Line4;
            break;
        case GPIO_Pin_5:
            pin_source = GPIO_PinSource5;
            exti_Line  = EXTI_Line5;
            break;
        case GPIO_Pin_6:
            pin_source = GPIO_PinSource6;
            exti_Line  = EXTI_Line6;
            break;
        case GPIO_Pin_7:
            pin_source = GPIO_PinSource7;
            exti_Line  = EXTI_Line7;
            break;
        case GPIO_Pin_8:
            pin_source = GPIO_PinSource8;
            exti_Line  = EXTI_Line8;
            break;
        case GPIO_Pin_9:
            pin_source = GPIO_PinSource9;
            exti_Line  = EXTI_Line9;
            break;
        case GPIO_Pin_10:
            pin_source = GPIO_PinSource10;
            exti_Line  = EXTI_Line10;
            break;
        case GPIO_Pin_11:
            pin_source = GPIO_PinSource11;
            exti_Line  = EXTI_Line11;
            break;
        case GPIO_Pin_12:
            pin_source = GPIO_PinSource12;
            exti_Line  = EXTI_Line12;
            break;
        case GPIO_Pin_13:
            pin_source = GPIO_PinSource13;
            exti_Line  = EXTI_Line13;
            break;
        case GPIO_Pin_14:
            pin_source = GPIO_PinSource14;
            exti_Line  = EXTI_Line14;
            break;
        case GPIO_Pin_15:
            pin_source = GPIO_PinSource15;
            exti_Line  = EXTI_Line15;
            break;               
    }
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
    
    SYSCFG_EXTILineConfig(port_source, pin_source);//PE2 连接到中断线2
    
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    
    if (trigger == 0)
    {
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    }
    else if (trigger == 1)
    {
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    }
    else if (trigger == 2)
    {
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    }
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	EXTI_InitStructure.EXTI_Line = exti_Line;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    switch (exti_pin)
    {
        case GPIO_Pin_0:
            NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
            break;
        case GPIO_Pin_1:
            NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
            break;
        case GPIO_Pin_2:
            NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
            break;
        case GPIO_Pin_3:
            NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
            break;
        case GPIO_Pin_4:
            NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
            break;
        case GPIO_Pin_5:
        case GPIO_Pin_6:
        case GPIO_Pin_7:
        case GPIO_Pin_8:
        case GPIO_Pin_9:
            NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
            break;
        case GPIO_Pin_10:
        case GPIO_Pin_11:
        case GPIO_Pin_12:
        case GPIO_Pin_13:
        case GPIO_Pin_14:
        case GPIO_Pin_15:
            NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; 
            break;
    }    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = exti_irq_cnt++;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

