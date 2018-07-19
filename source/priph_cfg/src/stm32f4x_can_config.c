/**
  ******************************************************************************
  * @file    stm32f4x_can_config.c
  * @author  
  * @version V1.0
  * @date    2018.6.8
  * @brief   can功能模块
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4x_can_config.h"
#include "api_can.h"
#include "common.h"
#include "portable.h"
  
static xQueueHandle s_xCanTxQueue = {0}, s_xCanRxQueue = {0};
static xSemaphoreHandle s_xCanTxMutex = {0};               ///<CAN数据发送互斥
static can_msg Tx_Msg_Buff = {0}, Rx_Msg_Buff = {0};/*!< 中断中发送和接收消息用此变量 减少中断申请内存失败的风险  */
xSemaphoreHandle g_xCanTxRxMutex = {0};                   ///<CAN数据接收和发送互斥
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  can除了过波器以外的配置
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该can口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @retval None
  */
void CanInitNoFilter(const u8 can_id, const u8 remap_par)
{
    u16 GPIO_Pin_Tx = 0;
	u16 GPIO_Pin_Rx = 0;
    u16 can_id_remap = (can_id << 4) | remap_par;
	GPIO_TypeDef *GPIOx_Rx = {0}, *GPIOx_Tx = {0};
    GPIO_InitTypeDef        GPIO_InitStructure;
    CAN_InitTypeDef         CAN_InitStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;
    
    switch (can_id_remap)
    {
        case 0x10:
        {
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource11, GPIO_AF_CAN1); //GPIOA11复用为CAN1
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource12, GPIO_AF_CAN1); //GPIOA12复用为CAN1
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能CAN1时钟	
            GPIO_Pin_Tx = GPIO_Pin_12;
            GPIOx_Tx    = GPIOA;
            GPIO_Pin_Rx = GPIO_Pin_11;
            GPIOx_Rx    = GPIOA;
        }
            break;
        case 0x11:
        {
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1); //GPIOA11复用为CAN1
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1); //GPIOA12复用为CAN1
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能CAN1时钟	
            GPIO_Pin_Tx = GPIO_Pin_9;
            GPIOx_Tx    = GPIOB;
            GPIO_Pin_Rx = GPIO_Pin_8;
            GPIOx_Rx    = GPIOB;
        }
            break;
        case 0x12:
        {
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1); //GPIOA11复用为CAN1
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1); //GPIOA12复用为CAN1
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能CAN1时钟	
            GPIO_Pin_Tx = GPIO_Pin_1;
            GPIOx_Tx    = GPIOD;
            GPIO_Pin_Rx = GPIO_Pin_0;
            GPIOx_Rx    = GPIOD;
        }
            break;
        case 0x13:
        {
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE );
            GPIO_PinAFConfig(GPIOH, GPIO_PinSource13, GPIO_AF_CAN1); //GPIOA11复用为CAN1
            GPIO_PinAFConfig(GPIOI, GPIO_PinSource9, GPIO_AF_CAN1); //GPIOA12复用为CAN1
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能CAN1时钟	
            GPIO_Pin_Tx = GPIO_Pin_13;
            GPIOx_Tx    = GPIOH;
            GPIO_Pin_Rx = GPIO_Pin_9;
            GPIOx_Rx    = GPIOI;
        }
            break;
        case 0x20:
        {
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2); //GPIOA11复用为CAN1
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2); //GPIOA12复用为CAN1
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);//使能CAN1时钟	
            GPIO_Pin_Tx = GPIO_Pin_5;
            GPIOx_Tx    = GPIOB;
            GPIO_Pin_Rx = GPIO_Pin_6;
            GPIOx_Rx    = GPIOB;
        }
            break;
        case 0x21:
        {
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2); //GPIOA11复用为CAN1
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2); //GPIOA12复用为CAN1
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);//使能CAN1时钟	
            GPIO_Pin_Tx = GPIO_Pin_13;
            GPIOx_Tx    = GPIOB;
            GPIO_Pin_Rx = GPIO_Pin_12;
            GPIOx_Rx    = GPIOB;
        }
            break;
        default :
            break;
    }        
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;///<复用功能 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;///<推挽输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;///<上拉
    GPIO_Init(GPIOx_Tx, &GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
    GPIO_Init(GPIOx_Rx, &GPIO_InitStructure);

    CAN_InitStructure.CAN_TTCM=DISABLE;         ///<enable or disable 时间触发通讯模式
    CAN_InitStructure.CAN_ABOM=DISABLE;         ///<enable or disable 软件自动离线管理
    CAN_InitStructure.CAN_AWUM=DISABLE;         ///<enable or disable 自动唤醒模式
    CAN_InitStructure.CAN_NART=ENABLE;          ///<enable or disable 非自动重传 ENABLE:禁止报文自动传送
    CAN_InitStructure.CAN_RFLM=DISABLE;         ///<enable or disable 发送FIFO锁定模式 DISABLE:报文不锁定 新的覆盖旧的
    CAN_InitStructure.CAN_TXFP=DISABLE;         ///<enable or disable 发送FIFO优先级 DISABLE:优先级由报文标识符决定
    CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; /*!<CAN_Mode_Normal 正常模式 CAN_Mode_LoopBack 回环模式 CAN_Mode_silent 静默模式 CAN_Mode_Silent_LoopBack 静默回环模式*/
    CAN_InitStructure.CAN_SJW =CAN_SJW_1tq;     /*!<重新同步跳跃宽度(Tsjw),每位中可以延长或缩短多少个时间单位的上限为tsjw+1个时间单位 CAN_SJW_1tq:跳跃宽度为1 */
    CAN_InitStructure.CAN_BS1 =CAN_BS1_9tq;     /*!<时间段1的时间单位数目 为1--16个时间单位 Tbs1=tbs1+1个时间单位CAN_BS1_1tq~CAN_BS1_16tq */
    CAN_InitStructure.CAN_BS2 =CAN_BS2_4tq;     /*!<时间段2的时间单位数目 为1--8个时间单位 Tbs2=tbs2+1个时间单位CAN_BS2_1tq~CAN_BS2_8tq */
    CAN_InitStructure.CAN_Prescaler=3;          ///<分频系数 ((CAN_BS1+1)+(CAN_BS2+1)+1)*CAN_Prescaler/42M=1/baud
    CAN_Init(CAN1, &CAN_InitStructure);         ///<CiA=(CAN_BS1+1)/(CAN_BS2+CAN_BS1+1).buad>800K时,CiA=75%.>500K,CiA=80%.<=500K时,CiA=87.5%.
    
    CAN_ITConfig(CAN1, CAN_IT_FMP0 | CAN_IT_TME, ENABLE);/*!< 接收中断和发送中断使能 | CAN_IT_TME */
    
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CAN1_TX_ISR_PRIO;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CAN1_RX_ISR_PRIO;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  
}   

/**
  * @brief  can配置过波器
  * @param  id:过滤器的id
  * @param  mask:过滤器的mask 如id:0x00550000 mask:0x00ff0000表示接收0x00550000、0x00550001等的数据，不接收0x00560000的数据
  * @param  format:过滤器是标准帧还是拓展帧
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 SetCanFilter(u32 id, u32 mask, u8 format)  
{
    static s16 can_filter_count = 0;
    u32 can_msg_Id              = 0;
    u32 can_msg_mask            = 0;
    CAN_FilterInitTypeDef       CAN_FilterInitStructure;
  
    /*!< check if Filter Memory is full                                          */
    if (can_filter_count > 13) {
        return SIGNED_TYPE_ERR;	      /*!< no more filter number available 普通增强F1只有一个CAN 14个滤波器组 互联型F105 107两个CAN 28个*/
    }
    /*!< Setup the identifier information                                        */
    if (format == STANDARD_FORMAT)  {       /*!< Standard ID                     */
        can_msg_mask  |= (u32)(mask << 21) | CAN_ID_STD;
    }  else  {                              /*!< Extended ID 只接收数据帧        */
        can_msg_mask  |= (u32)(mask <<  3) | CAN_ID_EXT;
    }

    if (format == STANDARD_FORMAT)  {       /*!< Standard ID                     */
        can_msg_Id  |= (u32)(id << 21) | CAN_ID_STD;
    }  else  {                               /*!< Extended ID                     */
        can_msg_Id  |= (u32)(id <<  3) | CAN_ID_EXT;
    }
  
    CAN_FilterInitStructure.CAN_FilterNumber         = can_filter_count;	 
    CAN_FilterInitStructure.CAN_FilterMode           = CAN_FilterMode_IdMask; 
    CAN_FilterInitStructure.CAN_FilterScale          = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh         = (can_msg_Id & 0xFFFF0000) >> 16;
    CAN_FilterInitStructure.CAN_FilterIdLow          = (can_msg_Id & 0x0000FFFF);
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = (can_msg_mask & 0xFFFF0000) >> 16;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow      = (can_msg_mask & 0x0000FFFF);

    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation     = ENABLE; 

    CAN_FilterInit(&CAN_FilterInitStructure);
    
    can_filter_count += 1;                              /*!< increase filter number */
  
    return SIGNED_TYPE_SUCCESS; 
}
/**
  * @brief  can配置
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该can口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 CanInit(const u8 remap_par)
{
    static u8 first_run_flag = 0;
	
	if (first_run_flag == 0)  
	{
		first_run_flag = 1;
        s_xCanTxQueue = xQueueCreate( CAN_SEND_OBJECTS, sizeof( can_msg ) );
        if (NULL == s_xCanTxQueue)
        {
            xEventGroupSetBits(g_xCreatedEventGroup, (SYSTEM_ERR | CAN_MEM_ERR));
            return CAN_MEM_ERR;
        }
        s_xCanRxQueue = xQueueCreate( CAN_RECE_OBJECTS, sizeof( can_msg ) );
        if (NULL == s_xCanRxQueue)
        {
            xEventGroupSetBits(g_xCreatedEventGroup, (SYSTEM_ERR | CAN_MEM_ERR));
            return CAN_MEM_ERR;
        }
        
        s_xCanTxMutex   = xSemaphoreCreateMutex();
        g_xCanTxRxMutex = xSemaphoreCreateMutex();
        xSemaphoreGive(g_xCanTxRxMutex);
        
	}
    CanInitNoFilter(1, remap_par);
    
    return SIGNED_TYPE_SUCCESS;
}
/**
  * @brief  can接收数据处理函数
  * @param  msg:用于返回CAN读取后的数据，和库函数类似
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 RevDataProcess(can_msg *msg)
{
    if(NULL == msg)
        return SIGNED_TYPE_ERR;
    
    /*!< Read identifier information                                             */
    if ((CAN1->sFIFOMailBox[0].RIR & CAN_ID_EXT) == 0) 
    {       /*!< Standard ID   */
        msg->format = STANDARD_FORMAT;
        msg->id     = (u32)0x000007FF & (CAN1->sFIFOMailBox[0].RIR >> 21);
    }  else  {                                                /*!< Extended ID   */
        msg->format = EXTENDED_FORMAT;
        msg->id     = (u32)0x1FFFFFFF & (CAN1->sFIFOMailBox[0].RIR >> 3);
    }

    /*!< Read type information                                                   */
    if ((CAN1->sFIFOMailBox[0].RIR & CAN_RTR_REMOTE) == 0) 
    {
        msg->type =   DATA_FRAME;                               /*!< DATA   FRAME  */
        /*!< Read length (number of received bytes)                                  */
        msg->len = (u32)0x0000000F & CAN1->sFIFOMailBox[0].RDTR;

        /*!< Read data bytes                                                         */
        msg->data[0] = (u32)0x000000FF & (CAN1->sFIFOMailBox[0].RDLR);
        msg->data[1] = (u32)0x000000FF & (CAN1->sFIFOMailBox[0].RDLR >> 8);
        msg->data[2] = (u32)0x000000FF & (CAN1->sFIFOMailBox[0].RDLR >> 16);
        msg->data[3] = (u32)0x000000FF & (CAN1->sFIFOMailBox[0].RDLR >> 24);

        msg->data[4] = (u32)0x000000FF & (CAN1->sFIFOMailBox[0].RDHR);
        msg->data[5] = (u32)0x000000FF & (CAN1->sFIFOMailBox[0].RDHR >> 8);
        msg->data[6] = (u32)0x000000FF & (CAN1->sFIFOMailBox[0].RDHR >> 16);
        msg->data[7] = (u32)0x000000FF & (CAN1->sFIFOMailBox[0].RDHR >> 24);
    }  
    else  
    {
        msg->type = REMOTE_FRAME;                               /*!< REMOTE FRAME  */
    }
    
    return SIGNED_TYPE_SUCCESS;
}
/**
  * @brief  can发送数据处理函数
  * @param  msg:发送的数据，和库函数类似
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 SendDataProcess(can_msg *msg)
{
    if(NULL == msg)
        return SIGNED_TYPE_ERR;
    
    /*!< Reset TIR register                                                      */
    CAN1->sTxMailBox[0].TIR  = (u32)0;                        /*!< reset TXRQ bit*/

    /* Setup the identifier information                                        */
    if (msg->format == STANDARD_FORMAT)  {                   /*!<    Standard ID */
        CAN1->sTxMailBox[0].TIR |= (u32)(msg->id << 21) | CAN_ID_STD;
    }  else  {                                               /*!< Extended ID    */
        CAN1->sTxMailBox[0].TIR |= (u32)(msg->id <<  3) | CAN_ID_EXT;
    }

    /*!< Setup type information                                                  */
    if (msg->type == DATA_FRAME)  
    {                          /*!< DATA FRAME     */
        CAN1->sTxMailBox[0].TIR |= CAN_RTR_DATA;

        /*!< Setup data bytes                                                     */
        CAN1->sTxMailBox[0].TDLR = (((u32)msg->data[3] << 24) | 
                                 ((u32)msg->data[2] << 16) |
                                 ((u32)msg->data[1] <<  8) | 
                                 ((u32)msg->data[0])        );
        CAN1->sTxMailBox[0].TDHR = (((u32)msg->data[7] << 24) | 
                                 ((u32)msg->data[6] << 16) |
                                 ((u32)msg->data[5] <<  8) |
                                 ((u32)msg->data[4])        );

        /*!< Setup length                                                            */
        CAN1->sTxMailBox[0].TDTR &= ~((unsigned long)0x0000000F);
        CAN1->sTxMailBox[0].TDTR |=  (msg->len & ((unsigned long)0x0000000F));
    }
    else 
    {
        CAN1->sTxMailBox[0].TIR |= CAN_RTR_REMOTE;
    }

    CAN1->IER |= CAN_IER_TMEIE;                       /*!<  enable  TME interrupt */ 

    /*<  transmit message                                                       */
    CAN1->sTxMailBox[0].TIR |=  ((unsigned long)0x00000001);///<CAN_TIxR_TXRQ;                /*<   set TXRQ bit */

    return SIGNED_TYPE_SUCCESS;
}
/**
  * @brief  can发送数据函数
  * @param  msg:发送的数据
  * @param  timeout:发送超时函数
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 Can_Push(can_msg *msg, u16 timeout)  
{
	u8 ret_status = 0; 
//    CanTxMsg txMsg = {0};
    if(NULL == msg)
        return SIGNED_TYPE_ERR;
    
//    msg->format = EXTENDED_FORMAT;
//    txMsg.ExtId = msg->id;
//    txMsg.DLC   = msg->len;
//    txMsg.Data[0]  = msg->data[0];
//    txMsg.Data[1]  = msg->data[1];
//    txMsg.Data[2]  = msg->data[2];
//    txMsg.Data[3]  = msg->data[3];
//    CAN_Transmit(CAN1, &txMsg);
    
    
    if ((CAN1->TSR & CAN_TSR_TME0) != 0) /* Transmit mailbox 0 is empty         */
	{ /* Transmit hardware free for send */
		SendDataProcess(msg);            /* Send message                        */
	}
	else 
	{ /*!< If hardware for sending is busy     */
        Tx_Msg_Buff = *msg;
        /* If message hasn't been sent but timeout expired, deallocate memory  */
        
        ret_status = xQueueSend(s_xCanTxQueue, &Tx_Msg_Buff, timeout); 
            
        if (ret_status == pdPASS)
        {
            if ((CAN1->TSR & CAN_TSR_TME0) != 0) /* Transmit mailbox 0 is empty         */
            { /* Transmit hw free for send */
                ret_status = xQueueReceive(s_xCanTxQueue, &Tx_Msg_Buff, timeout); 
                if (ret_status != pdPASS)
                {
                    return CAN_MEM_ERR;
                }  
                SendDataProcess(&Tx_Msg_Buff);      /* Send message                        */
            }
        }
        else
        {		//邮箱满
            ret_status = xSemaphoreTake( s_xCanTxMutex, timeout);

            if(ret_status != pdTRUE )
            {
                ret_status = xQueueReceive(s_xCanTxQueue, &Tx_Msg_Buff, timeout); 
                if(ret_status != pdPASS)
                {
                    return CAN_MEM_ERR;
                }
                else
                {
                    SendDataProcess(&Tx_Msg_Buff);      /* Send message                        */
                }
            }
            else
            {
                SendDataProcess(msg);      /* Send message                        */
            }
        }
	}
    
	return SIGNED_TYPE_SUCCESS;
}
/**
  * @brief  can接收数据函数
  * @param  msg:发送的数据
  * @param  timeout:发送超时函数
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 Can_Pull(can_msg *msg, u16 timeout)  
{
	u8 ret_status = 0;
	
	/* Wait for received message in mailbox                                     */
	ret_status = xQueueReceive(s_xCanRxQueue, &Rx_Msg_Buff, timeout); 
	if (ret_status != pdPASS)
	{
		return SIGNED_TYPE_ERR;
	}  
	
	if(&Rx_Msg_Buff != 0)
	{
		/* Copy received message from mailbox to address given in function parameter msg */
		*msg = Rx_Msg_Buff;
	}
    
    return SIGNED_TYPE_SUCCESS;
}
/**
  * @brief  can1发送完成中断
  * @param  None
  * @retval None
  */
void CAN1_TX_IRQHandler (void) 
{
    UBaseType_t uxCanTxSavedInterruptStatus; 
    portBASE_TYPE ret_status = 0;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
	if (CAN1->TSR & CAN_TSR_RQCP0) /*!< request completed mbx 0 */
    {      			
		CAN1->TSR |= CAN_TSR_RQCP0;      		/*!< reset request complete mbx 0 */
		uxCanTxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();
		
		/*!< If there is a message in the mailbox ready for send, read the \n
		message from the mailbox and send it                                  */
        
    ret_status = xQueueReceiveFromISR(s_xCanTxQueue, &Tx_Msg_Buff, &xHigherPriorityTaskWoken); 
		
		if (errQUEUE_EMPTY == ret_status) 
		{
			CAN1->IER &= ~CAN_IER_TMEIE;       	/*!< disable  TME interrupt */ 
		} 
		else if(&Tx_Msg_Buff != NULL)
		{
			SendDataProcess(&Tx_Msg_Buff);		   		
		}
		
    xSemaphoreGiveFromISR( s_xCanTxMutex, &xHigherPriorityTaskWoken );
        
    taskEXIT_CRITICAL_FROM_ISR( uxCanTxSavedInterruptStatus );
	}
}
/**
  * @brief  can1接收完成中断
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler (void) 
{
    UBaseType_t uxCanRxSavedInterruptStatus; 
    portBASE_TYPE ret_status = pdPASS;
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;

	if (CAN1->RF0R & CAN_RF0R_FMP0) 
	{	 
		uxCanRxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();

        RevDataProcess(&Rx_Msg_Buff);        		///< Read received message   

        ret_status = xQueueSendToBackFromISR(s_xCanRxQueue, &Rx_Msg_Buff, &xHigherPriorityTaskWoken);
        if (pdPASS != ret_status)			///<队列满，放入队列失败
        {
            xEventGroupSetBits(g_xCreatedEventGroup, (SYSTEM_ERR | CAN_MEM_ERR));			
        }
 
		CAN1->RF0R |= CAN_RF0R_RFOM0; ///< Release FIFO 0 output mailbox 
        
        taskEXIT_CRITICAL_FROM_ISR( uxCanRxSavedInterruptStatus );  
	}
}



/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

