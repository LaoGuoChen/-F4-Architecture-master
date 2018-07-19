/**
  ******************************************************************************
  * @file    project_main.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   ����������
  ******************************************************************************
  */

/*
**********************************************************************************
                               ͷ�ļ�
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
                                ���������� 
**********************************************************************************
*/

/* �ں˶����� */
EventGroupHandle_t g_xCreatedEventGroup = NULL;

/* �������ȼ� */
#define vSTARTTask_PRIORITY							( ( unsigned portBASE_TYPE ) 2U )	//2
#define vSignalLedTask_PRIORITY					( ( unsigned portBASE_TYPE ) 3U )	//3
#define vUartDebugTask_PRIORITY         ( ( unsigned portBASE_TYPE ) 9U)	//10
#define vErrorProcessTask_PRIORITY      ( ( unsigned portBASE_TYPE ) 10U)	//10


#if 0
/*   printf ��ӳ��  */
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
                                ���������� 
**********************************************************************************
*/
static void vStartTask   ( void * pvParameters );

/**
  * ����  ������
  * ����  ��
  * ����  ��
  */
int main ( void )
{	    
	/* ������ʼ���� */
	xTaskCreate( vStartTask, 
	             "Task Start", 
	             configMINIMAL_STACK_SIZE, 
	             NULL,
               vSTARTTask_PRIORITY,
	             NULL);

	/* �������������������FreeRTOSϵͳ */
  vTaskStartScheduler();
	
}

/**
  * @brief  ������ʼ������
  * @param  None
  * @retval None
  */
static void vStartTask( void * pvParameters )                   
{	
     /* ģ���ʼ�� */
    ModulesHalInit();
	
	  printf("start... \n ");
	
    BaseType_t ret_status = 0;
    
    /* ���������ź��� */
  	g_xCreatedEventGroup = xEventGroupCreate();
	
	  /* ���������� */
    xTaskCreate( vErrorProcessTask, 
	               "Error Process Task",    
	               512, 
	               NULL, 
	               vErrorProcessTask_PRIORITY, 
	               NULL);
     
   
    
	
    /* ָʾ������ */
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
    
     /*  ��������  */		
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
		
    vTaskDelete(NULL);		// ���Լ�ɾ��

}

