/**
  ******************************************************************************
  * @file    stm32f4x_adc_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   ADC功能模块
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f4x_adc_config.h"
#include "stm32f4x_dma_config.h"
#include "api_adc.h"
#include "common.h"

/* Private variables ---------------------------------------------------------*/
volatile u8  g_vucAdc1ChannelNum = 0;
volatile u8  g_vucAdc2ChannelNum = 0;
volatile u8  g_vucAdc3ChannelNum = 0;

#if      ADC1SAMPLE
    volatile u16 g_vusAdc1ValueBuff[16 * SAMPLE_CNT] = {0};  ///<建立最大数据存储ADC采集的数据
#endif
#if      ADC2SAMPLE
    volatile u16 g_vusAdc2ValueBuff[16 * SAMPLE_CNT] = {0};  ///<建立最大数据存储ADC采集的数据
#endif
#if      ADC3SAMPLE
    volatile u16 g_vusAdc3ValueBuff[16 * SAMPLE_CNT] = {0};  ///<建立最大数据存储ADC采集的数据
#endif
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  初始化ADC1或ADC2的某一个
  * @param  gpio_par:通道号
  * @retval None
  */
static void InitAdc12Gpio(const u8 gpio_par)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;         ///<模拟输入
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;     ///<不带上下拉
    
    switch (gpio_par)
    {
        case 0: 
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 1:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 2:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 3:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 4: 
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 5:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 6:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 7:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 8:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        break;
        case 9:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        break;
        case 10:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 11:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 12:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 13:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
       case 14:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 15:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        default :
            break;
    }
}
/**
  * @brief  初始化ADC3
  * @param  gpio_par:通道号
  * @retval None
  */
static void InitAdc3Gpio(const u8 gpio_par)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;     ///<不带上下拉
    
    switch (gpio_par)
    {
        case 0:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 1:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 2:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 3:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 4: 
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 5:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 6:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 7:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 8:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 9:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        break;
        case 10:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 11:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 12:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 13:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
       case 14:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 15:
            RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        default :
            break;
    }
    
}
/**
  * @brief  ADC1配置通道
  * @param  gpio_par:通道号
  * @retval None
  */
static s8 InitAdc1(const u8 gpio_par)
{
    static u8 channel_num = 0;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef ADC_InitStrucutre;
    
    g_vucAdc1ChannelNum = channel_num + 1;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent; //ADC工作在独立模式
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
    ADC_CommonInit(&ADC_CommonInitStructure);//初始化
    
    ADC_InitStrucutre.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStrucutre.ADC_ScanConvMode = DISABLE; //模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_ContinuousConvMode = DISABLE; //模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStrucutre.ADC_DataAlign = ADC_DataAlign_Right; //ADC数据右对齐
	ADC_InitStrucutre.ADC_NbrOfConversion = g_vucAdc1ChannelNum; //顺序进行转换的工作模式
	ADC_Init(ADC1, &ADC_InitStrucutre);
    DMA_ADC1_Config();
    ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
    
    if ( ++channel_num > 16)
        return SIGNED_TYPE_ERR;
	/* 设定AD采集通道转换顺序 */
        switch (gpio_par)
    {
        case 0: 
            ADC_RegularChannelConfig(ADC1, ADC_Channel_0, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 1:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_1, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 2:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_2, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 3:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_3, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 4: 
            ADC_RegularChannelConfig(ADC1, ADC_Channel_4, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 5:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_5, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 6:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_6, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 7:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_7, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 8:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_8, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 9:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_9, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 10:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_10, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 11:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_11, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 12:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_12, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 13:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_13, channel_num, ADC_SampleTime_480Cycles); 
        break;
       case 14:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_14, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 15:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_15, channel_num, ADC_SampleTime_480Cycles); 
        break;
        default :
            break;
    }
	
    ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
    ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
    
    return channel_num;
}
/**
  * @brief  ADC2配置通道
  * @param  gpio_par:通道号
  * @retval None
  */
static s8 InitAdc2(const u8 gpio_par)
{
    static u8 channel_num = 0;
	ADC_InitTypeDef ADC_InitStrucutre;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;

    g_vucAdc2ChannelNum = channel_num + 1;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
    ADC_CommonInit(&ADC_CommonInitStructure);//初始化
    
    ADC_InitStrucutre.ADC_Resolution = ADC_Resolution_12b;//12位模式
    ADC_InitStrucutre.ADC_ScanConvMode = DISABLE;//非扫描模式	
    ADC_InitStrucutre.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
    ADC_InitStrucutre.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
    ADC_InitStrucutre.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
    ADC_InitStrucutre.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
    ADC_Init(ADC2, &ADC_InitStrucutre);//ADC初始化
    
    ADC_Cmd(ADC2, ENABLE);//开启AD转换器	
    
    if ( ++channel_num > 16)
        return SIGNED_TYPE_ERR;
	/* 设定AD采集通道转换顺序 */
    switch (gpio_par)
    {
        case 0: 
            ADC_RegularChannelConfig(ADC2, ADC_Channel_0, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 1:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_1, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 2:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_2, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 3:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_3, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 4: 
            ADC_RegularChannelConfig(ADC2, ADC_Channel_4, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 5:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_5, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 6:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_6, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 7:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_7, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 8:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_8, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 9:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_9, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 10:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_10, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 11:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_11, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 12:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_12, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 13:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_13, channel_num, ADC_SampleTime_480Cycles); 
        break;
       case 14:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_14, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 15:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_15, channel_num, ADC_SampleTime_480Cycles); 
        break;
        default :
            break;
    }
	
	ADC_SoftwareStartConv(ADC2);		//使能指定的ADC1的软件转换启动功能	
    ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
    
    return channel_num;
}
/**
  * @brief  ADC3配置通道
  * @param  gpio_par:通道号
  * @retval None
  */
static s8 InitAdc3(const u8 gpio_par)
{
    static u8 channel_num = 0;
	ADC_InitTypeDef ADC_InitStrucutre;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;

    g_vucAdc3ChannelNum = channel_num + 1;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);	  //ADC3复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);	//复位结束	 
    
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;//两个采样阶段之间的延迟5个时钟
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
    ADC_CommonInit(&ADC_CommonInitStructure);//初始化
    
    ADC_InitStrucutre.ADC_Resolution = ADC_Resolution_12b;//12位模式
    ADC_InitStrucutre.ADC_ScanConvMode = DISABLE;//非扫描模式	
    ADC_InitStrucutre.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
    ADC_InitStrucutre.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
    ADC_InitStrucutre.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
    ADC_InitStrucutre.ADC_NbrOfConversion = g_vucAdc3ChannelNum;//1个转换在规则序列中 也就是只转换规则序列1 
    ADC_Init(ADC3, &ADC_InitStrucutre);//ADC初始化
    
    DMA_ADC3_Config();
    
    if ( ++channel_num > 13)
        return SIGNED_TYPE_ERR;
    
    ADC_Cmd(ADC3, ENABLE);//开启AD转换器
	/* 设定AD采集通道转换顺序 */
    switch (gpio_par)
    {
        case 0: 
            ADC_RegularChannelConfig(ADC3, ADC_Channel_0, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 1:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_1, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 2:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_2, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 3:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_3, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 4: 
            ADC_RegularChannelConfig(ADC3, ADC_Channel_4, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 5:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_5, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 6:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_6, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 7:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_7, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 8:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_8, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 10:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_10, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 11:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_11, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 12:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_12, channel_num, ADC_SampleTime_480Cycles); 
        break;
        case 13:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_13, channel_num, ADC_SampleTime_480Cycles); 
        break;
        default :
            break;
    }
	
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC3的软件转换启动功能	
    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);//源数据发生变化时开启DMA传输
    ADC_DMACmd(ADC3, ENABLE);  //使能ADC_DMA

    return channel_num;
}
/**
  * @brief  初始化ADC
  * @param  adc_num:adc数 如1即为ADC1
  * @param  adc_channel_sum:该ADC下的所有adc通道,每二进制位数的高低代表对应通道的开启状态，如101=0x0065=0B0000000001100101代表通道0、2、5、6采集
  * @retval -1：传入参数错误,>0:adc对应通道的存储数据下标
  */
s8 Adc_Init(const u8 adc_num, const u16 adc_channel_sum)
{
    u8 get_par_channel_index = 0;
    s8 adc_rec_data_index = 0;
    
    if (adc_num == 0 || adc_num > 3 || adc_channel_sum == 0) /* 传入参数错误 */
        return SIGNED_TYPE_ERR;
    
    switch (adc_num)
    {
        case 1:
        {
            for (get_par_channel_index = 0; get_par_channel_index < 16; get_par_channel_index++)
            {
                if ( ( adc_channel_sum >> get_par_channel_index ) & 0x01)
                {
                    InitAdc12Gpio(get_par_channel_index);
                    adc_rec_data_index = InitAdc1(get_par_channel_index);
                }
            }
             
        }
        break;
        case 2:
        {
            for (get_par_channel_index = 0; get_par_channel_index < 16; get_par_channel_index++)
            {
                if ( ( adc_channel_sum >> get_par_channel_index ) & 0x01)
                {
                    InitAdc12Gpio(get_par_channel_index);
                    adc_rec_data_index = InitAdc2(get_par_channel_index);
                }
            }
            
        }
        break;
        
        case 3:
        {
            for (get_par_channel_index = 0; get_par_channel_index < 16; get_par_channel_index++)
            {
                if ( ( adc_channel_sum >> get_par_channel_index ) & 0x01)
                {
                    InitAdc3Gpio(get_par_channel_index);
                    adc_rec_data_index = InitAdc3(get_par_channel_index);
                }
            }
        }
        break;
    }
    
    return adc_rec_data_index;
}
/**
  * @brief  获取ADC的采集值
  * @param  rec_data_index:ADC下的某通道对应的存储数据下标
  * @param  adc_num:adc数,如1即为ADC1
  * @retval 0:传入参数错误 
  * @retval >0:经过均值滤波的adc采集值
  */
u16 Achieve_Adc_Data(const u8 rec_data_index, const u8 adc_num)
{
    u32 calc_sum          = 0;
    u8  calc_index        = 0;
    u8  adc_channel_index = 0;
    u16 return_voltage_ma = 0;
    
    if (rec_data_index > 18 || adc_num == 0 || adc_num > 3) /* 传入参数错误 */
        return 0;
    
    #if ADC1SAMPLE
    if (adc_num == 1)
    {
        for (calc_index = 0; calc_index < SAMPLE_CNT; calc_index++)
        {
            adc_channel_index = (rec_data_index - 1) + g_vucAdc3ChannelNum * calc_index;
            calc_sum += g_vusAdc1ValueBuff[adc_channel_index];
        }
        
        return_voltage_ma = calc_sum * 3300 / SAMPLE_CNT / 4096;
        
        return return_voltage_ma;
    }
    #endif
    
    #if ADC2SAMPLE
    if (adc_num == 2)
    {
        for (calc_index = 0; calc_index < SAMPLE_CNT; calc_index++)
        {
            adc_channel_index = (rec_data_index - 1) + g_vucAdc3ChannelNum * calc_index;
            calc_sum += g_vusAdc2ValueBuff[adc_channel_index];
        }
        
        return_voltage_ma = calc_sum * 3300 / SAMPLE_CNT / 4096;
        
        return return_voltage_ma;
    }
    #endif
    
    #if ADC3SAMPLE
    if (adc_num == 3)
    {
        for (calc_index = 0; calc_index < SAMPLE_CNT; calc_index++)
        {
            adc_channel_index = (rec_data_index - 1) + g_vucAdc3ChannelNum * calc_index;
            calc_sum += g_vusAdc3ValueBuff[adc_channel_index];
        }
        
        return_voltage_ma = calc_sum * 3300 / SAMPLE_CNT / 4096;
        
        return return_voltage_ma;
    }
    #endif
    
    return 0;
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

