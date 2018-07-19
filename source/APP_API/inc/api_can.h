/**
  ******************************************************************************
  * @file    api_can.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.8
  * @brief   can应用接口层
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __CAN_API_H
#define  __CAN_API_H

#ifdef __cplusplus
extern "C" {
#endif

    
/* Includes ------------------------------------------------------------------*/
#include "stm32f4x_can_config.h"
#include  "can_macro.h"
    
/* Exported types ------------------------------------------------------------*/
/** 
  * can_init:can初始化 \n
  * can_send_data_frame:can发送数据帧 \n
  * can_send_remote_frame:can发送远程帧 \n
  * can_receive_data:can接收数据 \n
  * can_tx_recv_data:can先发送再接收数据 \n
  */
typedef struct drive_can_desc drive_can_desc_t;

struct drive_can_desc{
    s8  (*can_init)              (u8 remap_par);                  /*!< can初始化   */
    s8  (*can_send_data_frame)   (u32 id, void *buf, u8 bufsize); /*!< can发送数据帧 */   
    s8  (*can_send_remote_frame) (u32 id);                        /*!< can发送远程帧 */ 
    s8  (*can_receive_data)      (can_msg *msg, u16 timeout);     /*!< can接收数据 */  
    s8  (*can_tx_recv_data)      (u32 id, void *inbuf, u8 insize, void *outbuf, u8 outsize , u16 timeout); /*!< can先发送再接收数据 */      
};

typedef struct
{
    u32 id;
    u32 mask;
    u8  format;
}can_set_filter_t;
/** 
  * can设置过滤器数组 \n
  * 第一步：用户在此添加过滤器的配置 \n
  */
static can_set_filter_t can_set_filter_table[] = {
{0x00200000, 0x00f00000, EXTENDED_FORMAT},
{0x00400000, 0x00f00000, EXTENDED_FORMAT}
};

/* Exported Defines ----------------------------------------------------------*/
/*!< 第二步：通过配置向导配置发送、接收的优先级和消息队列长度 */
// *** <<< Use Configuration Wizard in Context Menu >>> *** 
// <h>Can priority
// <o>CAN1_TX_ISR_PRIO <1-16>
// <i>Start priority of CAN1 Tx
#define  CAN1_TX_ISR_PRIO		(4)
// <o>CAN1_RX_ISR_PRIO <1-16>
// <i>Start priority of CAN1 Rx
#define  CAN1_RX_ISR_PRIO		(5)
// <o>CAN1_TX_ISR_PRIO <1-40>
// <i>Start priority of CAN1 Tx
#define  CAN_SEND_OBJECTS       (20)
// <o>CAN1_TX_ISR_PRIO <1-40>
// <i>Start priority of CAN1 Tx
#define  CAN_RECE_OBJECTS       (20)
// </h>
// *** <<< End of Configuration section             >>> *** 

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  第三步：HAL注册CAN并初始化，用户调用句柄操作
  * @param  handle:用于返回控制点的句柄
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该can口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 drive_can_init(drive_can_desc_t *handle, const u8 remap_par);

    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
