
/**
  ******************************************************************************
  * @file    app_signal_led.c
  * @author  chen.g 
  * @version V1.0
  * @date    2018.7.17
  * @brief   ָʾ�Ƶ�ҵ���
  ******************************************************************************
  */
 
/*
****************************************************************************************
                              ͷ�ļ�
****************************************************************************************
*/
#include "stm32f4x_gpio_config.h"
#include "app_signal_led.h"

/*
****************************************************************************************
                              �ֲ�����
****************************************************************************************
*/
 
 /**
   * ����   ָʾ�ƿ���IO��ʼ��
	 * ����   ��
	 * ����   ��
   */
 static void Signal_Led_Init(SIGNAL_LED_NUM signal_led_num)
 {
	 
	 switch(signal_led_num)
	 {
		 case SIG_LED_NUM_A:
			  pinMode(GPIOF,GPIO_Pin_9,GPIO_Mode_OUT,GPIO_Speed_50MHz,GPIO_OType_PP,GPIO_PuPd_DOWN);
			 break;
		 case SIG_LED_NUM_B:
			  pinMode(GPIOF,GPIO_Pin_10,GPIO_Mode_OUT,GPIO_Speed_50MHz,GPIO_OType_PP,GPIO_PuPd_DOWN);
			 break;
	 }

 }
 
 /**
   * ����   ָʾ�ƿ��ƽ�������ģʽ
	 * ����   ���ض�����
	 * ����   0 ���� 1 ���� ���δ��ʼ��
   */
 static u8 Signal_Led_Nomal(ST_SIGNAL_LED_HANDLE_T *handle)
 {
	 if( SIG_LED_NUM_A == handle->signal_led_num ||  SIG_LED_NUM_B == handle->signal_led_num)
	 {
		 handle->signal_led_status = SIG_LED_NOMAL;
	 }else
   {
		 return 1;
	 }
	 return 0;
	 
 }
 
  
 /**
   * ����   ָʾ�ƿ��ƽ��뱨��ģʽ
	 * ����   ��
	 * ����   0 ���� 1 ���� ���δ��ʼ��
   */
 static u8 Signal_Led_Alarm(ST_SIGNAL_LED_HANDLE_T *handle)
 {
	 if( SIG_LED_NUM_A == handle->signal_led_num ||  SIG_LED_NUM_B == handle->signal_led_num)
	 {
		 handle->signal_led_status = SIG_LED_ALARM;
	 }else
   {
		 return 1;
	 }
	 return 0;
	 
 }
 
  
 /**
   * ����   ָʾ�ƿ��ƽ��뱨��ģʽ
	 * ����   ��
	 * ����   0 ���� 1 ���� ���δ��ʼ��
   */
 static u8 Signal_Led_Err(ST_SIGNAL_LED_HANDLE_T *handle)
 {
	 
	 if( SIG_LED_NUM_A == handle->signal_led_num ||  SIG_LED_NUM_B == handle->signal_led_num)
	 {
		 handle->signal_led_status = SIG_LED_ERROR;
	 }else
   {
		 return 1;
	 }
	 return 0;
	 
 }
 
  /**
   * ����   ָʾ�ƹ�
	 * ����   ��
	 * ����   0 ���� 1 ���� δ��ʼ��
   */
 static u8 Signal_Led_Off(ST_SIGNAL_LED_HANDLE_T *handle)
 {
	  switch(handle->signal_led_num)
	  {
		  case SIG_LED_NUM_A:
		  	 GPIO_SetBits(GPIOF, GPIO_Pin_9);
		  	 break;
			
		  case SIG_LED_NUM_B:
			   GPIO_SetBits(GPIOF, GPIO_Pin_10);
		     break;
			 
			default:
				 return 1;
			// break;
	  }
		
		return 0;
 }
 
 
  /**
   * ����   ָʾ����
	 * ����   ��
	 * ����   0 ���� 1 ���� δ��ʼ��
   */
 static u8 Signal_Led_On(ST_SIGNAL_LED_HANDLE_T *handle)
 {

	   switch(handle->signal_led_num)
	   {
		   case SIG_LED_NUM_A:
		  	  GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		  	  break;
			 
		   case SIG_LED_NUM_B:
			    GPIO_ResetBits(GPIOF, GPIO_Pin_10);
			   break;
			 
			 default:
				 return 1;
			// break;
	   }
 
	 return 0;

 }
 
 
  /**
   * ����   ָʾ�ƿ��ƽ��뱨��ģʽ
	 * ����   ��
	 * ����   0 ���� 1 LED���δ��ʼ�� 
   */
u8 SignalLedInit(ST_SIGNAL_LED_HANDLE_T *handle,SIGNAL_LED_NUM signal_led_num)
 {
	 if( SIG_LED_NUM_A == signal_led_num ||  SIG_LED_NUM_B == signal_led_num)
	 {
	   handle->signal_led_status = SIG_LED_NOMAL;
	   handle->Signal_Led_Alarm = Signal_Led_Alarm;
	   handle->Signal_Led_Nomal = Signal_Led_Nomal;
	   handle->Signal_Led_Err = Signal_Led_Err;
	   handle->signal_led_num = signal_led_num;
	   handle->Signal_Led_On = Signal_Led_On;
	   handle->Signal_Led_Off = Signal_Led_Off;
	
	   /* ��ʼ�� */
	   Signal_Led_Init( handle->signal_led_num);
		
	 }else
	 {
		 return 1;
	 }
	  return 0;
}
