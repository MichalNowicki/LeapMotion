#include "Init.h"

void RCC_On()
{
	ErrorStatus HSEStartUpStatus;

	RCC_DeInit();                                           // Reset ustawien RCC
	RCC_HSEConfig(RCC_HSE_ON);                              // Wlacz HSE
	HSEStartUpStatus = RCC_WaitForHSEStartUp();             // Czekaj az HSE bedzie gotowy
	if(HSEStartUpStatus == SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);                  // zwloka dla pamieci Flash
		RCC_HCLKConfig(RCC_SYSCLK_Div1);                    // HCLK = SYSCLK 1
		RCC_PCLK2Config(RCC_HCLK_Div1);                     // PCLK2 = HCLK
		RCC_PCLK1Config(RCC_HCLK_Div2);                     // PCLK1 = HCLK/2
		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_7);// PLLCLK = 10MHz * 7 = 70 MHz
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); // Czekaj az PLL poprawnie sie uruchomi
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);          // PLL bedzie zrodlem sygnalu zegarowego
		while(RCC_GetSYSCLKSource() != 0x08);               // Czekaj az PLL bedzie sygnalem zegarowym systemu
	}

	/* DMA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);

	/* Enable UART clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* ADCCLK = PCLK2/4 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	/* Enable ADC1, ADC2, ADC3 and GPIOC clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
}

void GPIO_init()
{
	GPIO_InitTypeDef GPIO_InitDiody;
	GPIO_InitDiody.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitDiody.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_6|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitDiody.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitDiody);
	GPIO_ResetBits(GPIOE, GPIO_Pin_14);
	GPIO_ResetBits(GPIOE, GPIO_Pin_15);


	GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure PC.04 (ADC Channel14) as analog inputs */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void USART_init()
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* USART configuration */
	USART_Init(USART1, &USART_InitStructure);
}

void Timer_init()
{
	TIM_TimeBaseInitTypeDef TIMER1;
	TIMER1.TIM_ClockDivision = 0;
	TIMER1.TIM_CounterMode = TIM_CounterMode_Up;
	TIMER1.TIM_Prescaler = 70; // 100 000 Hz
	TIMER1.TIM_Period = 200; // 5 000 Hz
	//TIMER1.TIM_Prescaler = 7000; // 1000 Hz
	//TIMER1.TIM_Period = 50000; // 1/5 Hz
	TIM_TimeBaseInit(TIM1, &TIMER1);


	TIM_OCInitTypeDef         TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0x7F;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
}
void DMA_init()
{
	DMA_InitTypeDef DMA_InitStructure, DMA_InitStructure2;

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

	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC ,ENABLE);
	DMA_ClearFlag(DMA1_FLAG_TC4);

  /* DMA1 channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure2.DMA_PeripheralBaseAddr = ((uint32_t)0x4001244C);
    DMA_InitStructure2.DMA_MemoryBaseAddr = (uint32_t)&ADC1ConvertedValue;
    DMA_InitStructure2.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure2.DMA_BufferSize = 1;
    DMA_InitStructure2.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure2.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure2.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure2.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure2.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure2.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure2.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure2);

    DMA_ITConfig(DMA1_Channel1,DMA1_IT_TC1 ,ENABLE);
}
void ADC_init()
{
	ADC_InitTypeDef ADC_InitStructure;

	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADC1 regular channels configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_28Cycles5);

	/* Enable ADC2 EOC interrupt */
	//ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	//ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);

}
