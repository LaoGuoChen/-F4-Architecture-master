/**
  ******************************************************************************
  * @file    api_usart.h
  * @author  
  * @version V1.0
  * @date    2018.6.2
  * @brief   usart接口层
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __HWJ_USART_API_H
#define  __HWJ_USART_API_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* Exported types ------------------------------------------------------------*/
    
/** 
  * usart_init:usart初始化 \n
  * set_usart_print:设置该串口为打印输出 \n
  * usart_send:发送消息函数 \n
  * usart_id:该驱动设备的串口号,如USBAT1则串口号为1 \n
  * xQueue:串口中断后接收数据的消息队列 使用前用判断是否为空 \n
  */
typedef struct drive_usart_desc drive_usart_desc_t;
    
struct drive_usart_desc{
    s8   (*usart_init)       (drive_usart_desc_t *handle, u8 usart_id, u8 remap_par, u32 baud_par); /*!< usart初始化 */
    s8   (*set_usart_print)  (u8 usart_id);                                                         /*!< 设置该串口为打印输出 */                                                                             /* 消息队列 使用前需判断是否为空 */
    s8   (*usart_send)       (u8 usart_id, u8 *usart_data_par, u8 usart_data_len);                  /*!< 发送消息函数 */
    void (*usart_it_config)  (u8 usart_id, FunctionalState NewState);
	  u8   usart_id;                                                                                  /*!< 该驱动设备的串口号 如USBAT1则串口号为1 */ 
    QueueHandle_t xQueue;                                                                          /*!< 串口中断后接收数据的消息队列 使用前用判断是否为空 */
	
};


/* Exported Defines ----------------------------------------------------------*/
/*
 * @brief 串口API配置说明
 *        1、开启串口
 *        2、配置中断优先级
 *        3、如需消息队列,请在下面配置消息队列存储的数据单元数量和单个单元的字节长度
 *        4、声明结构体并初始化后即可使用
 */
// *** <<< Use Configuration Wizard in Context Menu >>> *** 
/*
// <q>USART1 Enable
*/
#define USART1_EN     1
// <h>USART1 priority & Queue
// <o>USART1_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART1 Tx
    #define  USART1_PREEMPTION_PRIORITY  (1)
// <o>USART1_SUB_PRIORITY <1-16>
// <i>Start priority of USART1 Sub Tx
    #define  USART1_SUB_PRIORITY         (2)
// <o>USART1_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART1 
    #define  USART1_QUEUE_LENGTH         (20)
// <o>USART1_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART1     
    #define  USART1_QUEUE_TYPE_L         (5)
// </h>
/*
// <q>USART2 Enable
*/
#define USART2_EN     0
// <h>USART2 priority & Queue
// <o>USART2_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART2 Tx
    #define  USART2_PREEMPTION_PRIORITY  (1)
// <o>USART2_SUB_PRIORITY <1-16>
// <i>Start priority of USART2 Sub Tx
    #define  USART2_SUB_PRIORITY         (2)
// <o>USART2_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART2 
    #define  USART2_QUEUE_LENGTH         (20)
// <o>USART2_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART2     
    #define  USART2_QUEUE_TYPE_L         (1)

// </h>
/*
// <q>USART3 Enable
*/
#define USART3_EN     0
// <h>USART3 priority & Queue
// <o>USART3_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART2 Tx
    #define  USART3_PREEMPTION_PRIORITY  (0)
// <o>USART3_SUB_PRIORITY <1-16>
// <i>Start priority of USART3 Sub Tx
    #define  USART3_SUB_PRIORITY         (0)
// <o>USART3_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART2 
    #define  USART3_QUEUE_LENGTH         (0)
// <o>USART3_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART3     
    #define  USART3_QUEUE_TYPE_L         (0)
				

// </h>
/*
// <q>USART4 Enable
*/
#define USART4_EN     0
// <h>USART4 priority & Queue
// <o>USART4_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART4 Tx
    #define  USART3_PREEMPTION_PRIORITY  (0)
// <o>USART4_SUB_PRIORITY <1-16>
// <i>Start priority of USART4 Sub Tx
    #define  USART4_SUB_PRIORITY         (0)
// <o>USART4_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART4 
    #define  USART4_QUEUE_LENGTH         (0)
// <o>USART4_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART4     
    #define  USART4_QUEUE_TYPE_L         (0)

// </h>
/*
// <q>USART5 Enable
*/
#define USART5_EN     1
// <h>USART5 priority & Queue
// <o>USART5_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART5 Tx
    #define  USART5_PREEMPTION_PRIORITY  (1)
// <o>USART5_SUB_PRIORITY <1-16>
// <i>Start priority of USART5 Sub Tx
    #define  USART5_SUB_PRIORITY         (1)
// <o>USART5_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART5 
    #define  USART5_QUEUE_LENGTH         (4)
// <o>USART5_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART5     
    #define  USART5_QUEUE_TYPE_L         (22)
	
// </h>
/*
// <q>USART5 Enable
*/
#define USART6_EN     0
// <h>USART6 priority & Queue
// <o>USART6_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART6 Tx
    #define  USART6_PREEMPTION_PRIORITY  (1)
// <o>USART6_SUB_PRIORITY <1-16>
// <i>Start priority of USART6 Sub Tx
    #define  USART6_SUB_PRIORITY         (1)
// <o>USART6_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART6 
    #define  USART6_QUEUE_LENGTH         (4)
// <o>USART6_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART6     
    #define  USART6_QUEUE_TYPE_L         (4)
				
// </h>
// *** <<< End of Configuration section             >>> ***  
    
/**
  * @brief  串口接口层初始化
  * @param  handle:返回的句柄
  * @param  usart_id:初始化的串口号
  * @param  remap_par:重映射参数
  *         -0:无重映射                                    
  *         -1:该串口有部分重映射则部分重映射，无则全重映射     
  *         -2:全重映射 
  * @param  baud_par:波特率
  * @retval None
  */
void Api_Init_Usart(drive_usart_desc_t *handle, const u8 usart_id, const u8 remap_par, const u32 baud_par);




#ifdef __cplusplus
}
#endif/* extern "C" */

#endif


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/

