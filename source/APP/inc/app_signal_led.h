/**
  ******************************************************************************
  * @file    app_signal_led.h
  * @author  chen.g 
  * @version V1.0
  * @date    2018.7.17
  * @brief   指示灯灯业务层
  ******************************************************************************
  */
  
#ifndef  __APP_SIGNAL_LED_H
#define  __APP_SIGNAL_LED_H


#ifdef __cplusplus
extern "C" {
#endif


/* 指示灯信号状态 */	
typedef enum{
    SIG_LED_NOMAL = 1,
    SIG_LED_ALARM = 2,
    SIG_LED_ERROR = 3,
}SIGNAL_LED_STATUS;	

/* 指示灯编号 */	
typedef enum{
    SIG_LED_NUM_A = 1,
    SIG_LED_NUM_B = 2,
}SIGNAL_LED_NUM;

	
/* 指示灯控制句柄  */
typedef struct ST_SIGNAL_LED_HANDLE ST_SIGNAL_LED_HANDLE_T;

struct ST_SIGNAL_LED_HANDLE
{
    u8 (*Signal_Led_Nomal)  (ST_SIGNAL_LED_HANDLE_T *handle);   // 指示灯正常模式 
    u8 (*Signal_Led_Alarm)  (ST_SIGNAL_LED_HANDLE_T *handle);   // 指示灯灯繁忙模式 
    u8 (*Signal_Led_Err)    (ST_SIGNAL_LED_HANDLE_T *handle);   // 指示灯灯错误模式 
	  u8 (*Signal_Led_On)     (ST_SIGNAL_LED_HANDLE_T *handle);
	  u8 (*Signal_Led_Off)    (ST_SIGNAL_LED_HANDLE_T *handle);
    u8  signal_led_status;                                      // 指示灯控制状态 
	  SIGNAL_LED_NUM signal_led_num;                               // 指示灯编号        
};


/*
****************************************************************************************
                              对外函数申明
****************************************************************************************
*/
extern u8 SignalLedInit(ST_SIGNAL_LED_HANDLE_T *handle,SIGNAL_LED_NUM signal_led_num);

	
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif
