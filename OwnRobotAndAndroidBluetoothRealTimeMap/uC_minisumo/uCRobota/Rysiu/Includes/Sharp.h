/*
 * Sharp.h
 *
 * Created: 2011-12-12 23:54:54
 *  Author: sMi
 */ 


#ifndef SHARP_H_
#define SHARP_H_

// PORTC 0 Sharp1
// PORTC 1 Sharp2
// PORTC 2 Sharp3
// PORTC 3 Sharp4

int Sharp_Timer_Value;

// Potrzeba tablicy przeliczaj¹cej wyniki sharpa (powód: nieliniowa charakterystyka)
// Tabela sharpa w mm, indeksy 0[0.4V], 1[0.5V], ..., 26[3V], 27[bledny pomiar]
static const int SharpValue[28]= { 425, 350, 290, 242, 203, 174, 150, 132, 117, 106, 97, 89, 83,
									77, 71, 67, 62, 57, 53, 49, 46, 42, 39, 36, 32, 28, 23, 0 };
									
// Wyniki usredniane sa w tych zmiennych 
uint16_t ADC0, ADC1, ADC2, ADC3;
	
// Programowe
void Sharp_Init();

// Systemowe
int Zrob_Pomiar(int nr);
uint16_t Pomiar2Indeks(uint16_t val);
void ADC_Timer_Init();






#endif /* SHARP_H_ */