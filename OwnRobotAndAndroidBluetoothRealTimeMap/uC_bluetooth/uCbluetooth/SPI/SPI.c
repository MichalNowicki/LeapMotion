/*
 * SPI.c
 *
 * Created: 2012-04-21 19:24:31
 *  Author: sMi
 */ 
#include "../Headers.h"

void SPI_init()
{
	//SPI_PORT = SPI_PORT | (1<<MISO_BIT);		// drive outputs to the SPI port
	SPI_DDR |= (1<<MISO_BIT);
			
	SPCR = (1<<SPE) | (1<<SPIE);	// enable SPI 
}

SIGNAL (SIG_SPI) 
{
	char znaczek;
	znaczek = SPDR;
	if(znaczek == 'q') LCD_Home();
	else	LCD_WriteData(znaczek);
}
