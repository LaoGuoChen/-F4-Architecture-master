/**
  ******************************************************************************
  * @file		can_macro.h
  * @author		Nobita Yan
  * @version	V0.1
  * @date    
  * @brief   	can macro protocal
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_MACRO_H
#define __CAN_MACRO_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f4xx_conf.h"
	 
/* Exported types ------------------------------------------------------------*/
    
/*!< CAN message object structure                                              */
typedef struct  {
  u32 id;                 /*!< 29 bit identifier                            */
  u8  data[8];            /*!< Data field                                   */
  u8  len;                /*!< Length of data field in bytes                */
  u8  ch;                 /*!< Object channel                               */
  u8  format;             /*!< 0 - STANDARD, 1- EXTENDED IDENTIFIER         */
  u8  type;               /*!< 0 - DATA FRAME, 1 - REMOTE FRAME             */
} can_msg;

/*!< Symbolic names for formats of CAN message                                 */
typedef enum {STANDARD_FORMAT = 0, EXTENDED_FORMAT} CAN_FORMAT;
/*!< Symbolic names for type of CAN message                                    */
typedef enum {DATA_FRAME = 0, REMOTE_FRAME}         CAN_FRAME;

/* Exported define -----------------------------------------------------------*/

#define ID_CHASSIS			0x2
	#define CHASSIS_SYSTEM_CH		1

	#define CHASSIS_MOTOR_CTL_CH		1
  		#define CHASSIS_SET_SCRAM_STOP		1
		#define CHASSIS_SET_NORMAL_STOP		2
		#define CHASSIS_SET_MOTOR_MODE      3
		#define CHASSIS_GET_MOTOR_MODE      4
		#define CHASSIS_GET_MOTOR_SPEED     5
		#define CHASSIS_SET_MOTOR_SPEED     6

	

#define OWN_DEVICE_ID   ID_CHASSIS

#define SRC_ID_MASK	    0x0F000000
#define DEST_ID_MASK	0x00F00000
#define CH_MASK			0x000FF000
#define PRO_MASK		0x00000FF0
#define BUILD_ID(src_id,dest_id,channel,property)	(0x10000000|(src_id<<24)|(deviceid<<20)|((channel)<<12)|(property<<4))
#define BUILD_ID_ERR(src_id,dest_id,channel,property)	((src_id<<24)|(deviceid<<20)|((channel)<<12)|(property<<4))


#ifdef __cplusplus
}
#endif

#endif /* __CAN_MACRO_H */


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
