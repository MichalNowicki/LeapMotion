/*
 * Enkoders.c
 *
 * Created: 2011-12-12 22:36:22
 *  Author: sMi
 */ 
#include "../Includes/Headers.h"

void Enkoders_Init()
{
	// Piny od enkoderów PD2 i PD3
	DDRD &= ~(1<<2);
	DDRD &= ~(1<<3);
	
	// Ustawienie przerwania INT1 i INT0
	// ISC11 = 0, ISC10 = 1 -> Any logical change generates interrupt
	MCUCR |=(1<<ISC10);
	MCUCR |=(1<<ISC00);
	
	// Wlaczenie przerwan
	GICR |= (1<<INT1) | (1<<INT0);
}
SIGNAL(SIG_INTERRUPT0)
{
	// Enkoder lewego ko³a
	akt_indeks = 0;
	buffer[akt_indeks++] = '#';
	buffer[akt_indeks++] = 'L';
	buffer[akt_indeks++] = kierunek_lewe;
	buffer[akt_indeks++] = 'L';
	buffer[akt_indeks++] = kierunek_lewe;
	buffer[akt_indeks++] = '%';
	I2C_RequestTransmision();
}
SIGNAL(SIG_INTERRUPT1)
{
	akt_indeks = 0;
	buffer[akt_indeks++] = '#';
	buffer[akt_indeks++] = 'P';
	buffer[akt_indeks++] = kierunek_prawe;
	buffer[akt_indeks++] = 'P';
	buffer[akt_indeks++] = kierunek_prawe;
	buffer[akt_indeks++] = '%';
	I2C_RequestTransmision();
}
