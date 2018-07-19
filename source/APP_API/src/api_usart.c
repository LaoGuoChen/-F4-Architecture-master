/**
  ******************************************************************************
  * @file    api_usart.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   usart接口层
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "api_usart.h"
#include "stm32f4x_usart_config.h"
#include "common.h"


/**
  * @brief  串口发送函数.
  * @param  usart_id:串口号
  * @param  usart_data_par:需要发送的地址
  * @param  usart_data_len：发送数据长度
  * @retval -1:设置失败(对应串口未开启或者已经开启其他串口).0：成功
  */
u8 usart_send_data_index = 0;
static s8 Usart_Send(u8 usart_id, u8 *usart_data_par, u8 usart_data_len)
{
//    u8 usart_send_data_index = 0;
    u16 timeout = 0;
    
    if (usart_id > 5 || NULL == usart_data_par)
        return SIGNED_TYPE_ERR;
    
    switch (usart_id)
    {   
        #if USART1_EN
        case 1:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {
                timeout = 200;
                while ((USART1->SR & USART_FLAG_TXE) && (--timeout))
                {							
                    USART_SendData(USART1, *(usart_data_par + usart_send_data_index));
                }
                timeout = 2000;
                while ((!(USART1->SR & USART_FLAG_TC)) && (--timeout));
            }
            break;
        #endif
        #if USART2_EN
        case 2:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {
                timeout = 250;
                while ((USART1->SR & USART_FLAG_TXE) && (--timeout))
                {							
                    USART_SendData(USART2, *(usart_data_par + usart_send_data_index));
                }while ((!(USART1->SR & USART_FLAG_TC)) && (--timeout));    
            }
            break;
        #endif
        #if USART3_EN
        case 3:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {               
                timeout = 250;
                while ((USART1->SR & USART_FLAG_TXE) && (--timeout))
                {							
                    USART_SendData(USART3, *(usart_data_par + usart_send_data_index));
                }while ((!(USART1->SR & USART_FLAG_TC)) && (--timeout));                 
            }
            break;
        #endif
        #if USART4_EN
        case 4:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {           
                timeout = 250;
                while ((USART1->SR & USART_FLAG_TXE) && (--timeout))
                {							
                    USART_SendData(UART4, *(usart_data_par + usart_send_data_index));
                }while ((!(USART1->SR & USART_FLAG_TC)) && (--timeout));                
            }
            break;
        #endif
        #if USART5_EN
        case 5:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {  
                timeout = 250;
                while ((USART1->SR & USART_FLAG_TXE) && (--timeout))
                {							
                    USART_SendData(UART5, *(usart_data_par + usart_send_data_index));
                }while ((!(USART1->SR & USART_FLAG_TC)) && (--timeout)); 
            }
            break;
        #endif
        default:
            break;
    }
    
    return SIGNED_TYPE_SUCCESS;
}
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
void Api_Init_Usart(drive_usart_desc_t *handle, const u8 usart_id, const u8 remap_par, const u32 baud_par)
{
    handle->usart_init      = InitUsartShell;
    handle->usart_send      = Usart_Send;
    handle->set_usart_print = SetUsartPrintFun;
    handle->usart_id        = usart_id;
    handle->usart_init(handle, usart_id, remap_par, baud_par);
    handle->usart_it_config = UsartItConfig;
	  
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
