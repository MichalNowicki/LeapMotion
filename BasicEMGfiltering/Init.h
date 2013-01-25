#ifndef _Inits
#define _Inits

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_usart.h"
#include "math.h"

extern uint32_t TxBufferSize;
extern uint8_t TxBuffer[30];
extern uint16_t ADC1ConvertedValue;
extern float RMS, LicznikProbek, val;
extern uint8_t flaga;

///
/// Inicjalizacja pinow uC
///
void GPIO_init(void);

///
/// Inicjalizacja transmisji szeregowej
///
void USART_init(void);

///
/// Inicjalizacja timera uzywanego do wyzwalania ADC
///
void Timer_init(void);

///
/// Inicjalizacja DMA dla USART i ADC
///
void DMA_init(void);

///
/// Inicjalizacja ADC
///
void ADC_init(void);

///
/// Inicjalizacja zegarow systemowych
///
void RCC_On(void);

#endif
