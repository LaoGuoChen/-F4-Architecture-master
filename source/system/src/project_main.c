/**
  ******************************************************************************
  * @file    project_main.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   工程主函数
  ******************************************************************************
  */

/*
**********************************************************************************
                               头文件
**********************************************************************************
*/


#include "stm32f4xx_conf.h"

#include "app_hal_init.h"

#include "task_signal_led.h"
#include "task_error_process.h"
#include "task_uart_debug.h"


#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "common.h"




/*
**********************************************************************************
                                任务函数声明 
**********************************************************************************
*/

/* 内核对象句柄 */
EventGroupHandle_t g_xCreatedEventGroup = NULL;

/* 任务优先级 */
#define vSTARTTask_PRIORITY							( ( unsigned portBASE_TYPE ) 2U )	//2
#define vSignalLedTask_PRIORITY					( ( unsigned portBASE_TYPE ) 3U )	//3
#define vUartDebugTask_PRIORITY         ( ( unsigned portBASE_TYPE ) 9U)	//10
#define vErrorProcessTask_PRIORITY      ( ( unsigned portBASE_TYPE ) 10U)	//10


#if 0
/*   printf 重映射  */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch) 1
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
PUTCHAR_PROTOTYPE
{
  ITM_SendChar(ch);
  return ch;
}
#endif
/*
**********************************************************************************
                                任务函数声明 
**********************************************************************************
*/
static void vStartTask   ( void * pvParameters );

/**
  * 描述  主函数
  * 参数  无
  * 返回  无
  */
int main ( void )
{	    
	/* 创建起始任务 */
	xTaskCreate( vStartTask, 
	             "Task Start", 
	             configMINIMAL_STACK_SIZE, 
	             NULL,
               vSTARTTask_PRIORITY,
	             NULL);

	/* 启动任务调度器，运行FreeRTOS系统 */
  vTaskStartScheduler();
	
}

/**
  * @brief  定义起始任务函数
  * @param  None
  * @retval None
  */
static void vStartTask( void * pvParameters )                   
{	
     /* 模块初始化 */
    ModulesHalInit();
	
	  printf("start... \n ");
	
    BaseType_t ret_status = 0;
    
    /* 创建互斥信号量 */
  	g_xCreatedEventGroup = xEventGroupCreate();
	
	  /* 错误处理任务 */
    xTaskCreate( vErrorProcessTask, 
	               "Error Process Task",    
	               512, 
	               NULL, 
	               vErrorProcessTask_PRIORITY, 
	               NULL);
     
   
    
	
    /* 指示灯任务 */
	  ret_status = xTaskCreate( vSignalLedTask, 
                              "The Task Of Signal Led",  
		                          512, 
		                          NULL,
                          	  vSignalLedTask_PRIORITY	,     
		                          NULL);

    if (pdPASS != ret_status)
    {
        xEventGroupSetBits(g_xCreatedEventGroup, (TASK_SIGNAL_LED_ERR | TASK_SIGNAL_LED_CREATE_ERR));
    }
    
     /*  调试任务  */		
		ret_status = xTaskCreate( vUartDebugTask, 
                              "The Task Of Debug",  
		                          512, 
		                          NULL,
                          	  vUartDebugTask_PRIORITY	,     
		                          NULL);

    if (pdPASS != ret_status)
    {
        xEventGroupSetBits(g_xCreatedEventGroup, (TASK_SIGNAL_LED_ERR | TASK_SIGNAL_LED_CREATE_ERR));
    }
		
    vTaskDelete(NULL);		// 把自己删除

}

