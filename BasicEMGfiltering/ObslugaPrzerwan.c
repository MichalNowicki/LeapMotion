#include "Init.h"
#include "ObslugaPrzerwan.h"
#include "Filtry.h"

void DMA1_Channel1_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC1))
  {
	  val = ADC1ConvertedValue * 3.3 / 4096;

	  if(flaga == 1)
	  {
		  int i;
	  	  for(i=0;i<100000;i++) asm("nop");
	  }
	  flaga = 1;
	  DMA_ClearITPendingBit(DMA1_IT_TC1);
  }
}

void DMA1_Channel4_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC4))
  {
	  DMA_ClearITPendingBit(DMA1_IT_TC4);

	  DMA_InitTypeDef DMA_InitStructure;

	  /* USARTy_Tx_DMA_Channel (triggered by USARTy Tx event) Config */
	  DMA_DeInit(DMA1_Channel4);
	  DMA_InitStructure.DMA_PeripheralBaseAddr = ((uint32_t)0x40013804);
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	  DMA_InitStructure.DMA_BufferSize = TxBufferSize;
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  }
}

