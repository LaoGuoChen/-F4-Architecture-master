/**
  ******************************************************************************
  * @file    app_signal_led.h
  * @author  chen.g 
  * @version V1.0
  * @date    2018.7.17
  * @brief   ָʾ�Ƶ�ҵ���
  ******************************************************************************
  */
  
#ifndef  __APP_SIGNAL_LED_H
#define  __APP_SIGNAL_LED_H


#ifdef __cplusplus
extern "C" {
#endif


/* ָʾ���ź�״̬ */	
typedef enum{
    SIG_LED_NOMAL = 1,
    SIG_LED_ALARM = 2,
    SIG_LED_ERROR = 3,
}SIGNAL_LED_STATUS;	

/* ָʾ�Ʊ�� */	
typedef enum{
    SIG_LED_NUM_A = 1,
    SIG_LED_NUM_B = 2,
}SIGNAL_LED_NUM;

	
/* ָʾ�ƿ��ƾ��  */
typedef struct ST_SIGNAL_LED_HANDLE ST_SIGNAL_LED_HANDLE_T;

struct ST_SIGNAL_LED_HANDLE
{
    u8 (*Signal_Led_Nomal)  (ST_SIGNAL_LED_HANDLE_T *handle);   // ָʾ������ģʽ 
    u8 (*Signal_Led_Alarm)  (ST_SIGNAL_LED_HANDLE_T *handle);   // ָʾ�ƵƷ�æģʽ 
    u8 (*Signal_Led_Err)    (ST_SIGNAL_LED_HANDLE_T *handle);   // ָʾ�Ƶƴ���ģʽ 
	  u8 (*Signal_Led_On)     (ST_SIGNAL_LED_HANDLE_T *handle);
	  u8 (*Signal_Led_Off)    (ST_SIGNAL_LED_HANDLE_T *handle);
    u8  signal_led_status;                                      // ָʾ�ƿ���״̬ 
	  SIGNAL_LED_NUM signal_led_num;                               // ָʾ�Ʊ��        
};


/*
****************************************************************************************
                              ���⺯������
****************************************************************************************
*/
extern u8 SignalLedInit(ST_SIGNAL_LED_HANDLE_T *handle,SIGNAL_LED_NUM signal_led_num);

	
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif
