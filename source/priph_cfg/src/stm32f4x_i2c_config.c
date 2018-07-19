/**
  ******************************************************************************
  * @file    stm32f4x_i2c_config.c
  * @author  
  * @version V1.0
  * @date    2018.6.15
  * @brief   i2c����ģ��
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4x_i2c_config.h"
#include "api_i2c.h"

typedef enum {
	IIC_NACK = 0,
	IIC_ACK
}IIC_REPLAY;

typedef enum {
	IIC_BUS_READY = 0,
	IIC_BUS_BUSY,
	IIC_BUS_ERROR
}IIC_BUS_STATE;

static GPIO_TypeDef *s_pGpioSclPort = {0}, *s_pGpioSdaPort = {0};
static u16 s_usGpioSclPin = 0, s_usGpioSdaPin = 0, s_usI2sSoftwareInitFlg = 0;
static u16 s_usSlaveAddress = 0;
static I2C_TypeDef* s_pHardwareI2c = {0};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ģ��IIC��ʼ��
  * @param  gpio_scl_port
  * @retval None
  */
void I2c_Init(GPIO_TypeDef* gpio_scl_port, u16 gpio_scl_pin, GPIO_TypeDef* gpio_sda_port, u16 gpio_sda_pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD \
    | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);			     
    
 	GPIO_InitStructure.GPIO_Pin = gpio_scl_pin;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(gpio_scl_port, &GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Pin = gpio_sda_pin;
    GPIO_Init(gpio_sda_port, &GPIO_InitStructure);
    s_pGpioSclPort = gpio_scl_port;
    s_usGpioSclPin = gpio_scl_pin;
    s_pGpioSdaPort = gpio_sda_port;
    s_usGpioSdaPin = gpio_sda_pin;
    GPIO_SetBits(s_pGpioSdaPort, s_usGpioSdaPin);
    GPIO_SetBits(s_pGpioSclPort, s_usGpioSclPin);
    s_usI2sSoftwareInitFlg = 1;
}
/**
  * @brief  ģ��IIC��ʱ���� f0ʱһ���ռ��ɡ���ͬ����Ҫ��һ�� һ����1us����
  * @param  None
  * @retval None
  */
static void I2c_Delay(void)    
{ 
    u8 timeout = 50;
    while(--timeout)
    {
        __NOP();
    }
}
/**
  * @brief  ����sda�ߵ�ƽ
  * @param  level����Ӧ�ĵ�ƽ 1���ߵ�ƽ 0���͵�ƽ
  * @retval None
  */
static void Set_Sda_Bit(u8 level)
{
    if(level == 1)
    {
        GPIO_SetBits(s_pGpioSdaPort, s_usGpioSdaPin);
    }
    else if(level == 0)
    {
        GPIO_ResetBits(s_pGpioSdaPort, s_usGpioSdaPin);
    }
}
/**
  * @brief  ����scl�ߵ�ƽ
  * @param  level����Ӧ�ĵ�ƽ 1���ߵ�ƽ 0���͵�ƽ
  * @retval None
  */
static void Set_Scl_Bit(u8 level)
{
    if(level == 1)
    {
        GPIO_SetBits(s_pGpioSclPort, s_usGpioSclPin);
    }
    else if(level == 0)
    {
        GPIO_ResetBits(s_pGpioSclPort, s_usGpioSclPin);
    }
}
/**
  * @brief  ����sda�������������
  * @param  level����Ӧ�ķ��� 1����� 0������
  * @retval None
  */
static void Set_Sda_Direct(u8 direct)
{
    u16 gpio_sda_pin_tmp = (s_usGpioSdaPin >> 1);
    u8  index = 0;
    
    while(gpio_sda_pin_tmp)
    {
        gpio_sda_pin_tmp = (gpio_sda_pin_tmp >> 1);
        index ++;
    }

    s_pGpioSdaPort->MODER &= (~(0x3 << index * 2));
    if(direct == 1)
    {

        s_pGpioSdaPort->MODER |= (0x1 << index * 2);
    }
    else if(direct == 0)
    {
        s_pGpioSdaPort->MODER |= (0x0 << index * 2);
    }
}    
/**
  * @brief  ģ��IIC��ʼʱ��
  * @param  None
  * @retval IIC���ߵ�״̬
  */
static IIC_BUS_STATE I2c_Start(void)
{
	Set_Sda_Direct(1);
	Set_Sda_Bit(1);
	Set_Scl_Bit(1);
    I2c_Delay();
	if((s_pGpioSdaPort->IDR & s_usGpioSdaPin) == RESET)
		return IIC_BUS_BUSY;
	Set_Sda_Bit(0);
	I2c_Delay();
	Set_Scl_Bit(0);
	I2c_Delay();
	if((s_pGpioSdaPort->IDR & s_usGpioSdaPin) == SET)
		return IIC_BUS_ERROR;

	return IIC_BUS_READY;
}

/**
  * @brief  ģ��IICֹͣʱ��
  * @param  None
  * @retval None
  */
static void I2c_Stop(void)
{
	Set_Sda_Direct(1);
	Set_Sda_Bit(0);
	I2c_Delay();
	Set_Scl_Bit(1);
	I2c_Delay();
	Set_Sda_Bit(1);
	I2c_Delay();	
}
/**
  * @brief  ģ��IIC�ȴ�Ӧ��
  * @param  None
  * @retval 1:�ɹ� 0:ʧ��
  */
static u8 I2c_Wait_Ack(void)
{
	u8 ucErrTime=250;
	
	Set_Sda_Direct(0);
	Set_Sda_Bit(1);
    I2c_Delay();	   
	Set_Scl_Bit(1);
    I2c_Delay(); 
	while((s_pGpioSdaPort->IDR & s_usGpioSdaPin) == SET) 
    {
		if(!--ucErrTime) 
        {
			I2c_Stop();
			return 0;
		}
		I2c_Delay();
	}
	Set_Scl_Bit(0);
	
	return 1;  
} 
/**
  * @brief  ģ��IICӦ��
  * @param  None
  * @retval None
  */
static void I2c_Ack(void)
{
	Set_Scl_Bit(0);
	Set_Sda_Direct(1);
	Set_Sda_Bit(0);
	I2c_Delay();
	Set_Scl_Bit(1);
	I2c_Delay();
	Set_Scl_Bit(0);
}
/**
  * @brief  ģ��IIC��Ӧ��
  * @param  None
  * @retval None
  */    
static void I2c_NAck(void)
{
	Set_Scl_Bit(0);
	Set_Sda_Direct(1);
	Set_Sda_Bit(1);
	I2c_Delay();
	Set_Scl_Bit(1);
	I2c_Delay();
	Set_Scl_Bit(0);
}					 				     

/**
  * @brief  ģ��IIC����һ���ֽ�
  * @param  None
  * @retval None
  */ 		  
static void I2c_Send_Byte(u8 txd)
{                        
	u8 t;   
    
	Set_Sda_Direct(1);
	Set_Scl_Bit(0);
	for(t = 0; t < 8; t++) {            
		if(txd & 0x80)
			Set_Sda_Bit(1);
		else
			Set_Sda_Bit(0);
		txd <<= 1; 	  
		I2c_Delay();
		Set_Scl_Bit(1);
		I2c_Delay();
		Set_Scl_Bit(0);
        I2c_Delay();
	}	 
} 	 
   
/**
  * @brief  ģ��IIC��ȡһ���ֽ�
  * @param  None
  * @retval ���յ�������
  */  
static u8 I2c_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;

	Set_Sda_Direct(0);
	for(i = 0; i < 8; i++ ) {
		Set_Scl_Bit(0);
		I2c_Delay();
		Set_Scl_Bit(1);
		receive <<= 1;
		if(s_pGpioSdaPort->IDR & s_usGpioSdaPin)
			receive++;   
		I2c_Delay();
	}
	if(ack)
		I2c_Ack(); 
	else
		I2c_NAck();
	
	return receive;
}
/**
  * @brief  ģ��IIC���ݵ�ַ��ȡ����ֽ�
  * @param  None
  * @retval ����:�ɹ� 0:ʧ��
  */  
u8 I2cReadBytes(u8 SlaveAddress, u8 reg, u8 length, u8 *data)
{
    if (s_usI2sSoftwareInitFlg == 1)
    {
        u8 count = 0;
        
        I2c_Start();
        I2c_Send_Byte(SlaveAddress);	
        if(!I2c_Wait_Ack())
            return 0;
        I2c_Send_Byte(reg);		
        if(!I2c_Wait_Ack())
            return 0;	  
        I2c_Start();
        I2c_Send_Byte(SlaveAddress + 1);  
        if(!I2c_Wait_Ack())
            return 0;
        
        for(count = 0; count < length; count++) {
            if(count != length-1)
                data[count] = I2c_Read_Byte(1); 
            else
                data[count]=I2c_Read_Byte(0);	
        }
        I2c_Stop();
        
        return count;
    }

    return 0;
}
/**
  * @brief  ģ��IIC���ݵ�ַд�����ֽ�
  * @param  None
  * @retval 1:�ɹ� 0:ʧ��
  */  
u8 I2cWriteBytes(u8 SlaveAddress, u8 reg, u8 length, u8* data)
{
    if (s_usI2sSoftwareInitFlg == 1)
    {
        u8 count = 0;
        
        I2c_Start();
        I2c_Send_Byte(SlaveAddress);	  
        if(!I2c_Wait_Ack())
            return 0;
        I2c_Send_Byte(reg); 
        if(!I2c_Wait_Ack())
            return 0;	  
        for(count = 0; count < length; count++) {
            I2c_Send_Byte(data[count]); 
            I2c_Wait_Ack(); 
        }
        I2c_Stop();
        I2c_Delay();
        I2c_Delay();
        I2c_Delay();
        I2c_Delay();
        I2c_Delay();
        return 1;
    }
    
    return 0;
}
/**
  * @brief  Ӳ��IIC���ó�ʼ��
  * @param  i2c_id:i2c�ı��
  * @param  i2c_remap:
            -0:����ӳ��
            -1:��ӳ��
  * @retval 1:�ɹ� 0:ʧ��
  */ 
void I2CConfig(const u8 i2c_id, const u8 i2c_remap, const u16 slave_addr)
{

	GPIO_InitTypeDef	GPIO_InitStructure;
	I2C_InitTypeDef		I2C_InitStructure;
	u8 i2c_id_remap = (i2c_id << 4) | i2c_remap;
    s_usSlaveAddress = slave_addr;
    
    switch (i2c_id_remap)
    {
        case 0x10:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //���츴�����
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
            /*!< I2C configuration */
            I2C_DeInit(I2C1);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C1, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C1;
            I2C_Cmd(I2C1, ENABLE);
        }
            break;
        case 0x11:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //���츴�����
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
            /*!< I2C configuration */
            I2C_DeInit(I2C1);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C1, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C1;
            I2C_Cmd(I2C1, ENABLE);
        }     
            break;
        case 0x20:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //���츴�����
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);
            /*!< I2C configuration */
            I2C_DeInit(I2C2);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C2, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C2;
            I2C_Cmd(I2C2, ENABLE);
        }  
            break;
        case 0x21:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
            
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //���츴�����
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
            GPIO_Init(GPIOF, &GPIO_InitStructure);
            GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_I2C2);
            GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_I2C2);
            /*!< I2C configuration */
            I2C_DeInit(I2C2);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C2, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C2;
            I2C_Cmd(I2C2, ENABLE);
        }   
            break;
        case 0x22:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
            
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //���츴�����
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
            GPIO_Init(GPIOH, &GPIO_InitStructure);
            GPIO_PinAFConfig(GPIOH, GPIO_PinSource4, GPIO_AF_I2C2);
            GPIO_PinAFConfig(GPIOH, GPIO_PinSource5, GPIO_AF_I2C2);
            /*!< I2C configuration */
            I2C_DeInit(I2C2);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C2, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C2;
            I2C_Cmd(I2C2, ENABLE);
        }  
            break;
        case 0x30:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);
            
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //���츴�����
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_I2C3);
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_I2C3);
            /*!< I2C configuration */
            I2C_DeInit(I2C3);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C3, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C3;
            I2C_Cmd(I2C3, ENABLE);
        }  
            break;
        case 0x31:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
            
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //���츴�����
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
            GPIO_Init(GPIOH, &GPIO_InitStructure);
            GPIO_PinAFConfig(GPIOH, GPIO_PinSource7, GPIO_AF_I2C3);
            GPIO_PinAFConfig(GPIOH, GPIO_PinSource8, GPIO_AF_I2C3);
            /*!< I2C configuration */
            I2C_DeInit(I2C3);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C3, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C3;
            I2C_Cmd(I2C3, ENABLE);
        }  
            break;
        default:
            break;
    }
}
/**
  * @brief  Ӳ��IIC��������
  * @param  addr:�Ĵ����ĵ�ַ
  * @param  data:�����͵�����
  * @retval 1:�ɹ� 0:ʧ��
  */ 
u8 HardwareI2cSendData(u8 addr, u8 data)
{
	u8 timeout = 0xFF;
	
    if(0 == s_pHardwareI2c)
    {
        return 0;
    }
    
	while(I2C_GetFlagStatus(s_pHardwareI2c, I2C_FLAG_BUSY))
    {
		if(!(--timeout))
        {
			return 0;
		}
	}

	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
		if(!(--timeout))
        {
			return 0;
		}
	}
	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Transmitter);	///<AD+W
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {	///<ACK
		if(!(--timeout))
        {
			return 0;
		}
	}
	I2C_SendData(s_pHardwareI2c, addr);							///<RREGISTER ADDRESS
	timeout = 0xFF;
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {			///<ACK
		if(!(--timeout))
        {
			return 0;
		}
	}
	I2C_SendData(s_pHardwareI2c, data);							///<DATA
	timeout = 0xFF;
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {			///<ACK
		if(!(--timeout))
        {
			return 0;
		}
	}
	I2C_GenerateSTOP(s_pHardwareI2c, ENABLE);							///<STOP
	
    I2c_Delay();
    I2c_Delay();
    I2c_Delay();
    I2c_Delay();
    I2c_Delay();
    
	return 1;
}
/**
  * @brief  Ӳ��IIC��ȡ����
  * @param  addr:�Ĵ����ĵ�ַ
  * @retval ��0:���յ������� 0:ʧ��
  */ 
u8 HardwareI2cReadData(u8 addr)
{
	u8 data = 0;
	u8 timeout = 0xFF;
	
	while(I2C_GetFlagStatus(s_pHardwareI2c, I2C_FLAG_BUSY))
    {
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Transmitter);	///<AD+W
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {	///<ACK
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_Cmd(s_pHardwareI2c, ENABLE);
	I2C_SendData(s_pHardwareI2c, addr); 							///<REGISTER ADDRESS	
	timeout = 0xFF;
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {			///<ACK
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	timeout = 0xFF;
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Receiver); 		///<AD+R
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {		///<ACK
		if(!(--timeout))
        {
			return 0x0;
		}
	}					
	I2C_AcknowledgeConfig(s_pHardwareI2c, DISABLE);						///<NACK
	I2C_GenerateSTOP(s_pHardwareI2c, ENABLE);							///<STOP
	while(!(I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_BYTE_RECEIVED)))
    {		
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	data = I2C_ReceiveData(s_pHardwareI2c); 							///<DATA
	I2C_AcknowledgeConfig(s_pHardwareI2c, ENABLE);
	
	return data;
}
/**
  * @brief  Ӳ��IIC��ȡ�������
  * @param  register_addr:�Ĵ����ĵ�ַ
  * @param  data_out:���յ������ݵ�ַ
  * @param  length:�����յ����ݳ���
  * @retval 1:�ɹ� 0:ʧ��
  */ 
u8 HardwareI2cReadDatas(u8 register_addr, u8 *data_out, u8 length)
{
	u16 timeout = 0xF000, i = 14, j = 0;
    
	while(I2C_GetFlagStatus(s_pHardwareI2c, I2C_FLAG_BUSY))
    {
		if(!(--timeout))
        {
			return 0;
		}
	}
		
	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	
	while (!I2C_GetFlagStatus(s_pHardwareI2c,I2C_FLAG_SB)) 
    {
		if(!(--timeout)) 
        {
			return 0;
		}
	}

	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Transmitter);	///<AD+W
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {	///<ACK
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	I2C_SendData(s_pHardwareI2c, register_addr); 					///<REGISTER ADDRESS	
	while ((!I2C_GetFlagStatus(s_pHardwareI2c,I2C_FLAG_BTF)))
    {
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	while (!I2C_GetFlagStatus(s_pHardwareI2c,I2C_FLAG_SB)) 
    {
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Receiver); 		///<AD+R
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {		///<ACK
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	while(length)
    {

		if(i == 1)
        {
			I2C_AcknowledgeConfig(s_pHardwareI2c, DISABLE);
			I2C_GenerateSTOP(s_pHardwareI2c, ENABLE);					///<STOP
		}
		while((!I2C_GetFlagStatus(s_pHardwareI2c,I2C_FLAG_BTF)))
        {		///<ACK
			if(!(--timeout)) 
            {
				return 0;
			}
		}
		*(data_out+j) = I2C_ReceiveData(s_pHardwareI2c); 				///<DATA
        j++;
		i--;
	}

	I2C_AcknowledgeConfig(s_pHardwareI2c, ENABLE);

	return 1;
}
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

