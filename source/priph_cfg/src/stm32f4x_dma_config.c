/**
  ******************************************************************************
  * @file    stm32f4x_dma_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio功能模块
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f4x_dma_config.h"
#include "stm32f4x_adc_config.h"
#include "api_adc.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ADC1的DMA配置
  * @param  None
  * @retval None
  */
void DMA_ADC1_Config(void)
{
#if      ADC1SAMPLE       
	DMA_InitTypeDef DMA_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);/*DMA2的时钟使能*/
    while(DMA_GetCmdStatus(DMA1_Stream0)!=DISABLE);/*等待DMA可以配置*/
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;/*DMA通道0*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //0x4001244C; //ADC1->DR; //DMA外设ADC地址(0x4001244C);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)g_vusAdc1ValueBuff;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = SAMPLE_CNT * g_vucAdc1ChannelNum; //DMA通道的缓存大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道X拥有高优先级
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;/*禁止FIFO*/
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;/*FIFO的值*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;/*单次传输*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;/*单次传输*/
    DMA_Init(DMA1_Stream0,&DMA_InitStructure);
    DMA_Cmd(DMA1_Stream0,ENABLE);//开启DMA传输
#endif
}
/**
  * @brief  ADC3的DMA配置
  * @param  None
  * @retval None
  */
void DMA_ADC3_Config(void)
{
#if      ADC3SAMPLE 
	DMA_InitTypeDef DMA_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);/*DMA2的时钟使能*/
    while(DMA_GetCmdStatus(DMA2_Stream0)!=DISABLE);/*等待DMA可以配置*/

    DMA_InitStructure.DMA_Channel = DMA_Channel_2;/*DMA通道2*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC3->DR; //DMA外设ADC地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)g_vusAdc3ValueBuff; //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; //内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = SAMPLE_CNT * g_vucAdc3ChannelNum; //DMA通道的缓存大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道X拥有高优先级
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;/*禁止FIFO*/
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;/*FIFO的值*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;/*单次传输*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;/*单次传输*/
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    
    DMA_Cmd(DMA2_Stream0, ENABLE);//开启DMA传输
#endif
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
