/**
  ******************************************************************************
  * @file    stm32f4x_usart_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   usart功能模块
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4x_usart_config.h"
#include "common.h"
#include "stdio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Private variables ---------------------------------------------------------*/
typedef void (*proc_on_rx_fun)(u8 id, u8 data);

static void Usart_Recv_Process(u8 id, u8 data);

static USART_TypeDef* s_stPrint_Usart = {0};

/*!< 串口队列数组 */  
static QueueHandle_t  s_stUsartQueueHandleTable[
    0
    #if USART1_EN
        +1       
    #endif
    #if USART2_EN
        +1
    #endif
    #if  USART3_EN
        +1
    #endif
    #if USART4_EN
        +1
    #endif
    #if  USART5_EN
        +1
    #endif
    #if  USART6_EN
        +1
    #endif
] = {0};

/*!< 定义串口数据单元缓冲数组 */
#if USART1_EN
    static u8 s_ucUsart1DateIndex = 0;
     u8 s_ucUsart1DataBuffTable[USART1_QUEUE_TYPE_L] = {0};      
#endif
#if USART2_EN
    static u8 s_ucUsart2DateIndex = 0;
    static u8 s_ucUsart2DataBuffTable[USART2_QUEUE_TYPE_L] = {0};  
#endif
#if  USART3_EN
    static u8 s_ucUsart3DateIndex = 0;
    static u8 s_ucUsart3DataBuffTable[USART3_QUEUE_TYPE_L] = {0};  
#endif
#if USART4_EN
    static u8 s_ucUsart4DateIndex = 0;
    static u8 s_ucUsart4DataBuffTable[USART4_QUEUE_TYPE_L] = {0};  
#endif
#if  USART5_EN
    static u8 s_ucUsart5DateIndex = 0;
    static u8 s_ucUsart5DataBuffTable[USART5_QUEUE_TYPE_L] = {0};  
#endif 
#if  USART6_EN
    static u8 s_ucUsart6DateIndex = 0;
    static u8 s_ucUsart6DataBuffTable[USART6_QUEUE_TYPE_L] = {0};  
#endif 
/**
  * @brief  串口配置
  * @param  usart_id:串口号
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该串口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @param  baud_par:波特率
  * @retval None
  */
static void InitUsart(const u8 usart_id, const u8 remap_par, const u32 baud_par)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
    
    u16 GPIO_Pin_Tx = 0;
	u16 GPIO_Pin_Rx = 0;
	GPIO_TypeDef *GPIOx_Rx = {0}, *GPIOx_Tx = {0};
    USART_TypeDef* USARTx = {0};
    volatile u8 USARTx_IRQChannel = 0;
    u8 usart_id_remap_par = (usart_id << 4) | remap_par;
    
    switch (usart_id_remap_par)
    {
        case 0x10:
        {
          	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
            GPIO_Pin_Tx = GPIO_Pin_9;
            GPIOx_Tx    = GPIOA;
            GPIO_Pin_Rx = GPIO_Pin_10;
            GPIOx_Rx    = GPIOA; 
            USARTx_IRQChannel = USART1_IRQn;
            USARTx      = USART1;
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
        }
        break;
        case 0x11:
        {
          	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_6;
            GPIOx_Tx    = GPIOB;
            GPIO_Pin_Rx = GPIO_Pin_7;
            GPIOx_Rx    = GPIOB; 
            USARTx_IRQChannel = USART1_IRQn;
            USARTx      = USART1;
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
        }
        break;
        case 0x20:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_2;
            GPIOx_Tx    = GPIOA;
            GPIO_Pin_Rx = GPIO_Pin_3;
            GPIOx_Rx    = GPIOA;    
            USARTx_IRQChannel = USART2_IRQn;
            USARTx      = USART2;
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
        }
        break;
        case 0x21:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

            GPIO_Pin_Tx = GPIO_Pin_5;
            GPIOx_Tx    = GPIOD;
            GPIO_Pin_Rx = GPIO_Pin_6;
            GPIOx_Rx    = GPIOD; 
            USARTx_IRQChannel = USART2_IRQn;     
            USARTx      = USART2;
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
        }
        break;
        case 0x30:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_10;
            GPIOx_Tx    = GPIOB;
            GPIO_Pin_Rx = GPIO_Pin_11;
            GPIOx_Rx    = GPIOB;    
            USARTx_IRQChannel = USART3_IRQn;
            USARTx      = USART3;
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
        }
        break;
        case 0x31:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_10;
            GPIOx_Tx    = GPIOC;
            GPIO_Pin_Rx = GPIO_Pin_11;
            GPIOx_Rx    = GPIOC;
            USARTx_IRQChannel = USART3_IRQn;
            USARTx      = USART3;
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
        }
        break;
        case 0x32:
        {
          	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_10;
            GPIOx_Tx    = GPIOD;
            GPIO_Pin_Rx = GPIO_Pin_11;
            GPIOx_Rx    = GPIOD;  
            USARTx_IRQChannel = USART3_IRQn;
            USARTx      = USART3;
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_USART3);
        }
        break;
        case 0x40:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_0;
            GPIOx_Tx    = GPIOC;
            GPIO_Pin_Rx = GPIO_Pin_1;
            GPIOx_Rx    = GPIOC;
            USARTx_IRQChannel = UART4_IRQn;
            USARTx      = UART4;
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
        }
        break;
        case 0x41:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_10;
            GPIOx_Tx    = GPIOC;
            GPIO_Pin_Rx = GPIO_Pin_11;
            GPIOx_Rx    = GPIOC;
            USARTx_IRQChannel = UART4_IRQn;
            USARTx      = UART4;
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);
        }
        break;
        case 0x50:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_12;
            GPIOx_Tx    = GPIOC;
            GPIO_Pin_Rx = GPIO_Pin_2;
            GPIOx_Rx    = GPIOD;  
            USARTx_IRQChannel = UART5_IRQn;
            USARTx      = UART5;
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
        }
        break;
        case 0x60:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_6;
            GPIOx_Tx    = GPIOC;
            GPIO_Pin_Rx = GPIO_Pin_7;
            GPIOx_Rx    = GPIOC;  
            USARTx_IRQChannel = USART6_IRQn;
            USARTx      = USART6;
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
        }
        break;
        case 0x61:
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
            
            GPIO_Pin_Tx = GPIO_Pin_14;
            GPIOx_Tx    = GPIOG;
            GPIO_Pin_Rx = GPIO_Pin_9;
            GPIOx_Rx    = GPIOG;  
            USARTx_IRQChannel = USART6_IRQn;
            USARTx      = USART6;
            GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
            GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
        }
        break;
        default:
        break;
    }
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOx_Tx, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOx_Rx, &GPIO_InitStructure);  
    
	  USART_InitStructure.USART_BaudRate = baud_par;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No ;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USARTx, &USART_InitStructure);
   
	  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQChannel;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = USART1_PREEMPTION_PRIORITY;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = USART1_SUB_PRIORITY;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
    
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
    USART_ClearFlag(USARTx, USART_FLAG_TC);
    USART_Cmd(USARTx, ENABLE);
}

/**
  * @brief  串口中断设置
  * @param  usart_id:串口号
  * @param  enable:中断使能 0关闭 1开启 
  * @retval None
  */
void UsartItConfig(const u8 usart_id, FunctionalState NewState)
{
	switch(usart_id)
	{
		case 1:
			if(ENABLE == NewState)
			{
    			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			}else
			{
					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
			}
			break;
		case 2:
			if(ENABLE == NewState)
			{
    			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
			}else
			{
					USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
			}
			break;
		case 3:
			if(ENABLE == NewState)
			{
    			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			}else
			{
					USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
			}
			break;
		case 4:
			if(ENABLE == NewState)
			{
    			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
			}else
			{
					USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);
			}
			break;
		case 5:
			if(ENABLE == NewState)
			{
    			USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
			}else
			{
					USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);
			}
			break;
		case 6:
			if(ENABLE == NewState)
			{
    			USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
			}else
			{
					USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);
			}
			break;
			
		default:
			break;
	}
	
}
  

/**
  * @brief  获取串口号
  * @param  usart_id:串口号
  * @param  usart_id_par:串口号 
  * @retval -1:错误 >=0:对应的串口号-1
  */
static s8 GetPortID(const u8 usart_id_par)
{
    volatile s8 port_id = -1;

#if USART1_EN
    port_id++;
    if (usart_id_par == 1) 
    {
        goto __go_teturn;
    }
#endif
#if USART2_EN
    port_id++;
    if (usart_id_par == 2) 
    {
        goto __go_teturn;
    }
#endif
#if  USART3_EN
    port_id++;
    if (usart_id_par == 3) 
    {
        goto __go_teturn;
    }
#endif
#if  USART4_EN
    port_id++;
    if (usart_id_par == 4) 
    {
        goto __go_teturn;
    }
#endif
#if  USART5_EN
    port_id++;
    if (usart_id_par == 5) 
    {
        goto __go_teturn;
    }
#endif
#if  USART6_EN
    port_id++;
    if (usart_id_par == 6)
    {        
        goto __go_teturn;
    }
#endif

    __go_teturn:
    
    if(port_id < 0)
        port_id = 0;
    
    return port_id;
}
/**
  * @brief  串口初始化总入口
  * @param  handle:注册后返回的句柄
  * @param  usart_id:串口号
  * @param  remap_par:重映射参数
  *         -0:无重映射                                    
  *         -1:该串口有部分重映射则部分重映射，无则全重映射     
  *         -2:全重映射  
  * @param  baud_par:波特率
  * @retval -1:错误 0:成功
  */
s8 InitUsartShell(drive_usart_desc_t *handle, const u8 usart_id, const u8 remap_par, const u32 baud_par)
{
    if(usart_id > 6)
        return SIGNED_TYPE_ERR;
    

    InitUsart(usart_id, remap_par, baud_par);
#if USART1_EN
    if (usart_id == 1)
    {        
        s_stUsartQueueHandleTable[GetPortID(usart_id)] = xQueueCreate(USART1_QUEUE_LENGTH, USART1_QUEUE_TYPE_L);  
    }        
#endif
#if USART2_EN
    if (usart_id == 2) 
    {
        s_stUsartQueueHandleTable[GetPortID(usart_id)] = xQueueCreate(USART2_QUEUE_LENGTH, USART2_QUEUE_TYPE_L);  
    }
#endif
#if  USART3_EN
    if (usart_id == 3) 
    {
        s_stUsartQueueHandleTable[GetPortID(usart_id)] = xQueueCreate(USART3_QUEUE_LENGTH, USART3_QUEUE_TYPE_L); 
    }        
#endif
#if USART4_EN
    if (usart_id == 4)
    {        
        s_stUsartQueueHandleTable[GetPortID(usart_id)] = xQueueCreate(USART4_QUEUE_LENGTH, USART4_QUEUE_TYPE_L);  
    }
#endif
#if  USART5_EN
    if (usart_id == 5)
    {        
        s_stUsartQueueHandleTable[GetPortID(usart_id)] = xQueueCreate(USART5_QUEUE_LENGTH, USART5_QUEUE_TYPE_L); 
    }        
#endif 
#if  USART6_EN
    if (usart_id == 6) 
    {
        s_stUsartQueueHandleTable[GetPortID(usart_id)] = xQueueCreate(USART6_QUEUE_LENGTH, USART6_QUEUE_TYPE_L);  
    }
#endif 
    
    if (NULL == s_stUsartQueueHandleTable[GetPortID(usart_id)])
    {
        return SIGNED_TYPE_ERR;
    }
    else
    {
        handle->xQueue = s_stUsartQueueHandleTable[GetPortID(usart_id)];
    }
    
    return SIGNED_TYPE_SUCCESS;     
}

#if 1
/**
  * @brief  重定向c库函数printf到指定串口
  * @param  不明
  * @retval 不明
  */
int fputc(int ch, FILE* f)
{
    /*!< 发送一个字节数据到USART1 */
    USART_SendData(s_stPrint_Usart, (uint8_t) ch);
    /*!< 等待发送完毕 */
    while(USART_GetFlagStatus(s_stPrint_Usart, USART_FLAG_TC) == RESET);
    return (ch);
}


/**
  * @brief  重定向c库函数scanf到指定串口
  * @param  不明
  * @retval 不明
  */
int fgetc(FILE* f)
{
    /*!< 等待串口1输入数据 */
    while(USART_GetFlagStatus(s_stPrint_Usart, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(s_stPrint_Usart);
}

/**
  * @brief  重定向c库函数put_char到指定串口
  * @param  不明
  * @retval 不明
  */
void put_char(unsigned char ch, USART_TypeDef* uart)
{	
    /*!< 发送一个字节数据到USART1 */
    USART_SendData(uart, (unsigned char) ch);
}

#endif
/**
  * @brief  设置串口为打印串口
  * @param  usart_id:串口号
  * @retval -1:错误 0:成功
  */
s8 SetUsartPrintFun(const u8 usart_id)
{
    if(s_stPrint_Usart != 0)
        return SIGNED_TYPE_ERR; /* 已经设置了串口打印 */
    
#if USART1_EN
    if ( usart_id == 1)
    {
        s_stPrint_Usart = USART1;
    }
#endif
#if USART2_EN
    if ( usart_id == 2)
    {
        s_stPrint_Usart = USART2;
    }
#endif
#if USART3_EN
    if ( usart_id == 3)
    {
        s_stPrint_Usart = USART3;
    }
#endif
#if USART4_EN
    if ( usart_id == 4)
    {
        s_stPrint_Usart = UART4;
    }
#endif
#if USART5_EN
    if ( usart_id == 5)
    {
        s_stPrint_Usart = UART5;
    }
#endif   
#if USART6_EN
    if ( usart_id == 6)
    {
        s_stPrint_Usart = USART6;
    }
#endif  

    return SIGNED_TYPE_SUCCESS;
}

/**
  * @brief  串口中断接收回调函数
  * @param  usart_id:串口号
  * @param  usart_data:接收到的单个数据
  * @retval None
  */
static void Usart_Recv_Process(const u8 usart_id, const u8 usart_data)
{
    BaseType_t higher_priority_task_woken_par = pdTRUE;
    
    switch (usart_id)
    {   
        #if USART1_EN
        case 1:
            s_ucUsart1DataBuffTable[s_ucUsart1DateIndex++] = usart_data; 
				   
            if (s_ucUsart1DateIndex >= USART1_QUEUE_TYPE_L) 
            {    
                s_ucUsart1DateIndex = 0; 
							  UsartItConfig(usart_id, DISABLE);
                xQueueSendFromISR(s_stUsartQueueHandleTable[GetPortID(usart_id)], &s_ucUsart1DataBuffTable, &higher_priority_task_woken_par);
							   
            }
            break;
     
        #endif
        #if USART2_EN
        case 2:
            s_ucUsart2DataBuffTable[s_ucUsart2DateIndex++] = usart_data; 
            if (s_ucUsart2DateIndex >= USART2_QUEUE_TYPE_L) 
            { 
                s_ucUsart2DateIndex = 0; 
		            UsartItConfig(usart_id, DISABLE);
                xQueueSendFromISR(s_stUsartQueueHandleTable[GetPortID(usart_id)], &s_ucUsart2DataBuffTable, &higher_priority_task_woken_par);
            } 
            break;
        #endif
        #if  USART3_EN
        case 3:
            s_ucUsart1DataBuffTable[s_ucUsart3DateIndex++] = usart_data; 
            if (s_ucUsart3DateIndex >= USART3_QUEUE_TYPE_L) 
            { 
                s_ucUsart3DateIndex = 0; 
							  UsartItConfig(usart_id, DISABLE);
                xQueueSendFromISR(s_stUsartQueueHandleTable[GetPortID(usart_id)], &s_ucUsart3DataBuffTable, &higher_priority_task_woken_par);
            } 
            break;
        #endif
        #if USART4_EN
        case 4:
            s_ucUsart4DataBuffTable[s_ucUsart4DateIndex++] = usart_data; 
            if (s_ucUsart4DateIndex >= USART4_QUEUE_TYPE_L) 
            { 
                s_ucUsart4DateIndex = 0; 
							  UsartItConfig(usart_id, DISABLE);
                xQueueSendFromISR(s_stUsartQueueHandleTable[GetPortID(usart_id)], &s_ucUsart4DataBuffTable, &higher_priority_task_woken_par);
            } 
            break;
        #endif
        #if  USART5_EN
        case 5:
            s_ucUsart5DataBuffTable[s_ucUsart5DateIndex++] = usart_data; 
            if (s_ucUsart5DateIndex >= USART5_QUEUE_TYPE_L) 
            { 
                s_ucUsart5DateIndex = 0; 
							  UsartItConfig(usart_id, DISABLE);
                xQueueSendFromISR(s_stUsartQueueHandleTable[GetPortID(usart_id)], &s_ucUsart5DataBuffTable, &higher_priority_task_woken_par);
            } 
            break;
        #endif
        #if  USART6_EN
        case 6:
            s_ucUsart6DataBuffTable[s_ucUsart6DateIndex++] = usart_data; 
            if (s_ucUsart6DateIndex >= USART6_QUEUE_TYPE_L) 
            { 
                s_ucUsart6DateIndex = 0; 
							  UsartItConfig(usart_id, DISABLE);
                xQueueSendFromISR(s_stUsartQueueHandleTable[GetPortID(usart_id)], &s_ucUsart6DataBuffTable, &higher_priority_task_woken_par);
            } 
            break;
        #endif             
        default:
            break;
    }
}

#define DEF_RX1236_HANDLER_FOR_ID(id) \
void USART##id##_IRQHandler(void)  \
{   \
    int tmp = 0; \
    UBaseType_t uxUsartSavedInterruptStatus; \
    uxUsartSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR(); \
    if(USART_GetITStatus(USART##id, USART_IT_RXNE) != RESET)  \
    { \
        /*!< Read one byte from the receive data register */  \
        tmp = USART##id->DR & 0xFF; \
        Usart_Recv_Process(id, tmp); \
    } \
    if(USART_GetFlagStatus(USART##id,USART_FLAG_ORE)==SET) \
    /*!< Overflow? */ \
    { \
        USART##id->SR = (uint16_t)~USART_FLAG_ORE; \
        tmp = USART##id->DR; \
    } \
    taskEXIT_CRITICAL_FROM_ISR( uxUsartSavedInterruptStatus ); \
}

#define DEF_RX45_HANDLER_FOR_ID(id) \
void UART##id##_IRQHandler(void)  \
{   \
    int tmp = 0; \
    UBaseType_t uxUsartSavedInterruptStatus; \
    uxUsartSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR(); \
    if(USART_GetITStatus(UART##id, USART_IT_RXNE) != RESET)  \
    { \
        /*!< Read one byte from the receive data register */  \
        tmp = UART##id->DR & 0xFF; \
        Usart_Recv_Process(id, tmp); \
    } \
    if(USART_GetFlagStatus(UART##id, USART_FLAG_ORE) == SET) \
    /*!< Overflow? */ \
    { \
        UART##id->SR = (uint16_t)~USART_FLAG_ORE; \
        tmp = UART##id->DR; \
    } \
    taskEXIT_CRITICAL_FROM_ISR( uxUsartSavedInterruptStatus ); \
}

#if USART1_EN
    // USART1 Int handler
    DEF_RX1236_HANDLER_FOR_ID(1)
#endif
#if USART2_EN
    // USART2 Int handler
    DEF_RX1236_HANDLER_FOR_ID(2)
#endif
#if USART3_EN
    // USART3 Int handler
    DEF_RX1236_HANDLER_FOR_ID(3)
#endif
#if USART4_EN
    // USART4 Int handler
    DEF_RX45_HANDLER_FOR_ID(4)
#endif
#if USART5_EN
    // USART5 Int handler
    DEF_RX45_HANDLER_FOR_ID(5)
#endif
#if USART6_EN
    // USART1 Int handler
    DEF_RX1236_HANDLER_FOR_ID(6)
#endif
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
