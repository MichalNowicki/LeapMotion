/*
 * Sharp.c
 *
 * Created: 2011-12-12 23:55:07
 *  Author: sMi
 */ 
#include "../Includes/Headers.h"

void Sharp_Init()
{
	// Sharpy wywolywane timerem, bo ADC ma za du¿¹ czêstotliwoœæ :D. Nie potrzebuje 20kHz
	
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading 
		
	ADC_Timer_Init();
	
	
	// Zerowanie zmiennych usredniajacych
	ADC0 = 0;
	ADC1 = 0;
	ADC2 = 0;
	ADC3 = 0;
}
void ADC_Timer_Init() 
{
	Sharp_Timer_Value = 0;
	TCCR0 |= _BV(CS02); // 256 prescale
	TCNT0 = 0;
	TIMSK |= _BV(TOIE0);
}
int Zrob_Pomiar(int nr)
{
	// Wylacz ADC by zmienic ustawienia
	ADCSRA 	&= ~(1<<ADEN);
		
	// Zrobienie pomiaru dla ADC
	ADMUX &= 0x00;
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading 
	
	if(nr == 0)			; 
	else if(nr == 1)	ADMUX 	|= (1<<MUX0); 
	else if(nr == 2)	ADMUX 	|= (1<<MUX1); 
	else if(nr == 3)	ADMUX 	|= (1<<MUX1) | (1<<MUX0); 
	
	
	// Zezwolenie na ADC
	ADCSRA 	|= (1<<ADEN); 
		
	// START
	ADCSRA  |= (1 << ADSC); 
	while(ADCSRA & (1 << ADSC)) {}; // Oczekiwanie na pomiar
		
	//	Pobranie wyniku z ADC
	nr = ADCL>>6;
	nr = nr + (ADCH<<2); 
	return nr;
}
uint16_t Pomiar2Indeks(uint16_t val)
{
	val = (((val*50)/1024)-4);
	if ( val > 26 || val < 4) val = 27;
	return  val;
	
}

SIGNAL(SIG_OVERFLOW0) // 8Mhz/ 256/ 256 = 122.07 Hz 
{
	
	Sharp_Timer_Value++;
	
	// Sharp ADC0
	ADC0 +=	Zrob_Pomiar(0);
	// Sharp ADC1
	ADC1 +=	Zrob_Pomiar(1);
	// Sharp ADC2
	ADC2 +=	Zrob_Pomiar(2);
	// Sharp ADC3
	ADC3 +=	Zrob_Pomiar(3);
		
	if(Sharp_Timer_Value == 50) // By³o 30
	{	
		// Przeliczanie wynikow z Voltow na mm z tabeli przyblizonych charakterystyk
		ADC0 = SharpValue[Pomiar2Indeks(ADC0 / 50)];
		ADC1 = SharpValue[Pomiar2Indeks(ADC1 / 50)];
		ADC2 = SharpValue[Pomiar2Indeks(ADC2 / 50)];
		ADC3 = SharpValue[Pomiar2Indeks(ADC3 / 50)];
		
		// Zrob cos z wynikami Sharpa
		// 
		// Robie ...
		
		akt_indeks = 0;
		buffer[akt_indeks++] = '#';
		buffer[akt_indeks++] = ADC0;
		buffer[akt_indeks++] = ADC1;
		buffer[akt_indeks++] = ADC2;
		buffer[akt_indeks++] = ADC3;
		buffer[akt_indeks++] = '%';
		I2C_RequestTransmision();
		
		ADC0 = 0;
		ADC1 = 0;
		ADC2 = 0;
		ADC3 = 0;
		Sharp_Timer_Value = 0;
	}		
}
