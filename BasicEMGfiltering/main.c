#include "Init.h"
#include "ObslugaPrzerwan.h"
#include "NVIC.h"
#include "Delay.h"

#include "Filtry.h"

///
/// Wielkosc bufora danych dla transmisji po USARTcie
///
uint32_t TxBufferSize = 4;

///
/// Bufor danych dla transmisji po USARTcie
///
uint8_t TxBuffer[30];

///
/// Bufor do zapisania przekonwertowanej wartosci z ADC
///
uint16_t ADC1ConvertedValue = 0;

///
/// Zmienna pomocnicza
///
float RMS;

///
/// Zmienna pomocnicza
///
float LicznikProbek;

///
/// Zmienna pomocnicza
///
float val;

///
/// Flaga, czy nastapila konwersja ADC
///
uint8_t flaga = 0;

///
/// Funkcja inicjalizujaca peryferia oraz wykonujaca glowna petle programu,
/// w ktorej przeliczane sa wartosci filtrow cyfrowych
///
int main()
{
	RCC_On();
	NVIC_Configuration();
	GPIO_init();

	ADC_init();
	USART_init();
	DMA_init();

	Timer_init();


	RMS = 0;
	LicznikProbek = 0;


	/* Enable USART */
	USART_Cmd(USART1, ENABLE);

	/* Enable USART1 DMA TX request */
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

	//DMA_Cmd(DMA1_Channel4, ENABLE);

    // Enable DMA1 channel1
    DMA_Cmd(DMA1_Channel1, ENABLE);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);


	ADC_ExternalTrigConvCmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));

	TIM_Cmd(TIM1, ENABLE);

	/* TIM1 main Output Enable */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);


	while (1)
	{
		if(flaga)
		{
			val = Notching(val);
			val = HighPass(val);

			// Liczenie RMS
			RMS = RMS + val*val;
			LicznikProbek = LicznikProbek + 1;

			if(LicznikProbek == 5000)
			{
				RMS = RMS / 5000;
				RMS = sqrt(RMS);

				// Przepisanie wartoœci do tymczasowej i wys³anie
				uint32_t tymczasowa,i;
				tymczasowa = (uint32_t) RMS;

				for(i=0;i<4;i++)
				{
					TxBuffer[i] = (tymczasowa>>(8*i)) & 0x000000FF;
				}
				DMA_Cmd(DMA1_Channel4, ENABLE);

				LicznikProbek = 0;
				RMS = 0;
			}
			flaga = 0;
		}
	}
}

