/**
  ******************************************************************************
  * @file    stm32f10x_can_config.h
  * @author  êÌÖÇÐÛ  
  * @version V1.0
  * @date    2018.6.8
  * @brief   can¹¦ÄÜÄ£¿é
  ******************************************************************************
  */

#ifndef  __STM32F40x_CAN_CONFIG_H
#define  __STM32F40x_CAN_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif

    #include "stm32f4xx_conf.h"
    #include "common.h"
    #include "queue.h"
    #include "semphr.h"
    #include "api_can.h"
    #include  "can_macro.h"
    
    s8 CanInit(const u8 remap_par);
    s8 Can_Push(can_msg *msg, u16 timeout);
    s8 Can_Pull(can_msg *msg, u16 timeout);
    s8 SetCanFilter(u32 id, u32 mask, u8 format); 
    
    extern xSemaphoreHandle   g_xCanTxRxMutex;
    
    #define CAN_TX_RX_LOCK()    xSemaphoreTake( g_xCanTxRxMutex, 10 / portTICK_RATE_MS)
    #define CAN_TX_RX_UNLOCK()  xSemaphoreGive(g_xCanTxRxMutex)

#ifdef __cplusplus
}
#endif/* extern "C" */

#endif


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/

