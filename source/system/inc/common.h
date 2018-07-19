/**
  ******************************************************************************
  * @file    common.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   定义通用的宏、结构体、变量等
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef  __COMMON_H
#define	 __COMMON_H

#ifdef __cplusplus
extern "C" {
#endif
   
    
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "stdio.h"
	
/* Exported types ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define             TURN_OFF                    (0)
#define             TURN_ON                     (1)

#define             SIGNED_TYPE_ERR             (-1)
#define             SIGNED_TYPE_SUCCESS         (0)

#define             SYSTEM_ERR                  (0x000)
    #define         CAN_MEM_ERR                 (0x010)

#define             HAL_INIT_ERR                (0x100)
    #define         HAL_INIT_ME_ERR             (0x010)

#define             TASK_SIGNAL_LED_ERR          (0x200)
    #define         TASK_SIGNAL_LED_CREATE_ERR   (0x001)
        
#define             TASK_MOTOR_CTL_ERR          (0x300)
    #define         TASK_MOTOR_CTL_CREATE_ERR   (0x010)

#define             TASK_CAN_RECEIVE_ERR        (0x400)
    #define         TASK_CAN_RECEIVE_CREATE_ERR (0x010)

#define             TASK_TEST_ERR               (0x500)
    #define         TASK_TEST_CREATE_ERR        (0x010)    
		
/* Exported functions ------------------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
extern EventGroupHandle_t g_xCreatedEventGroup;



  
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/******************* (C) COPYRIGHT 2016 HWJ *****END OF FILE****/

