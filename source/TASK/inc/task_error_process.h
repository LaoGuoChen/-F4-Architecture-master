/**
  ******************************************************************************
  * @file    task_error_process.h
  * @author  
  * @version V1.0
  * @date    2018.6.2
  * @brief   错误处理线程业务
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_ERROR_PROCESS_H
#define __TASK_ERROR_PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

    
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
/* Exported types ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported Variable ---------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void vErrorProcessTask ( void * pvParameters );


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
