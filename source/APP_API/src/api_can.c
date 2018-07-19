/**
  ******************************************************************************
  * @file    api_can.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   can应用接口层
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "api_can.h"
#include "stm32f4x_can_config.h"
#include "common.h"
#include "queue.h"
#include "semphr.h"
#include "portable.h"
#include "string.h"

/* Private variables ---------------------------------------------------------*/
static can_msg Tx_Msg_Buff = {0}, Rx_Msg_Buff = {0};/*!< 中断中发送和接收消息用此变量 减少申请内存失败的风险  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  can发送数据帧函数
  * @param  id:发送的id
  * @param  buf:发送的数据地址
  * @param  bufsize:发送数据长度
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
static s8 CanSendData(u32 id, void *buf, u8 bufsize)
{
	can_msg msg;
	s8 ret;
	
	msg.id = id;
	msg.format = EXTENDED_FORMAT;
	msg.type = DATA_FRAME;
	msg.len = bufsize;		

	memcpy(msg.data, buf, bufsize);
	    
	CAN_TX_RX_LOCK();          
	ret = Can_Push(&msg, 10 / portTICK_RATE_MS);       
	CAN_TX_RX_UNLOCK(); 	

	return (ret);  
}
/**
  * @brief  can发送远程帧函数
  * @param  id:发送的id
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
static s8 CanSendRemote(u32 id)
{
	can_msg msg;
	s8 ret;
    
	msg.format = EXTENDED_FORMAT;
	msg.type = REMOTE_FRAME;
	msg.id = id;
	    
	CAN_TX_RX_LOCK(); 
	ret = Can_Push(&msg, 10 / portTICK_RATE_MS);       
	CAN_TX_RX_UNLOCK();

	return (ret);
}
/**
  * @brief  can接收数据函数
  * @param  msg:发送的数据
  * @param  timeout:发送超时函数
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
static s8 CanReceive(can_msg *msg, u16 timeout)
{
    return Can_Pull(msg, timeout);
}
/**
  * @brief  can接收扩展，先发送后接收函数
  * @param  id:发送的id
  * @param  inbuf:发送的数据地址
  * @param  insize:发送数据的长度
  * @param  outbuf:接收的数据地址
  * @param  outsize:接收数据的长度
  * @param  timeout:发送超时函数
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
static s8 CANRecvBufferEx(u32 id, void *inbuf, u8 insize, void *outbuf, u8 outsize , u16 timeout)
{
	can_msg msg;
	s8 err_rt;
    u32 convert_get_id = 0;
	u8 rx_len = 0;

	CanSendData(id, inbuf, insize);
	
	CAN_TX_RX_LOCK(); 
	while (1) 
    {
		do
        {
			err_rt = CanReceive(&msg, timeout);
			if(err_rt != SIGNED_TYPE_SUCCESS)
            {
				CAN_TX_RX_UNLOCK();
				return SIGNED_TYPE_ERR;
			}
            
            convert_get_id = (msg.id & 0x100FFFFF) & ((msg.id & 0x00F00000) << 4) & ((msg.id & 0x0F000000) >> 4);
		} while(convert_get_id != id);

		if((rx_len + msg.len) < outsize) 
        {
			rx_len += msg.len;
			memcpy((u8 *)((u32)outbuf + rx_len), msg.data, msg.len);
		} 
        else 
        {
			memcpy((u8 *)((u32)outbuf + rx_len), msg.data, (outsize - rx_len));
            
			CAN_TX_RX_UNLOCK();
            
			return SIGNED_TYPE_SUCCESS;
		}	
	}
}
/**
  * @brief  HAL注册CAN.
  * @param  handle:用于返回控制点的句柄
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该can口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @retval SIGNED_TYPE_ERR：配置出现错误 SIGNED_TYPE_SUCCESS：配置成功
  */
s8 drive_can_init(drive_can_desc_t *handle, const u8 remap_par)
{
    u8 set_can_filter_index = 0;
    
    if (NULL == handle)
        return SIGNED_TYPE_ERR;
    handle->can_init = CanInit;
    handle->can_send_data_frame = CanSendData;
    handle->can_send_remote_frame = CanSendRemote;
    handle->can_receive_data = CanReceive;
    handle->can_tx_recv_data = CANRecvBufferEx;
    
    if (SIGNED_TYPE_SUCCESS != handle->can_init(remap_par))
        return SIGNED_TYPE_ERR;
    
    for (set_can_filter_index = 0; set_can_filter_index < (sizeof(can_set_filter_table) / sizeof(can_set_filter_table[0])); set_can_filter_index++)
    {
        if(SIGNED_TYPE_SUCCESS != SetCanFilter(can_set_filter_table[set_can_filter_index].id, can_set_filter_table[set_can_filter_index].mask, can_set_filter_table[set_can_filter_index].format))
            return SIGNED_TYPE_ERR;
    }
    
    
    return SIGNED_TYPE_SUCCESS;
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
