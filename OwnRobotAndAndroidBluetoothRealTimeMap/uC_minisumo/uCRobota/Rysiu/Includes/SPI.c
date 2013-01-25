/*
 * SPI.c
 *
 * Created: 2012-04-21 19:24:31
 *  Author: sMi
 */ 
#include "../Headers.h"

void SPI_init()
{
	//SPI_PORT = SPI_PORT | ((1<<MOSI_BIT) | (1<<SCK_BIT) | (1<<SS_BIT));		// drive outputs to the SPI port
	//SPI_DDR = SPI_DDR | ((1<<MOSI_BIT) | (1<<SCK_BIT) | (1<<SS_BIT));
	//SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1);	// enable SPI as master, /64 prescaler
	//	SPSR = (1<<SPI2X);// double SPI clock speed
		// SPI na fclk/2 = 4MHz
	//SPCR = (1<<4)|(1<<6); //setup SPI: Master mode, MSB first, SCK phase low, SCK idle low
	//SPSR = (1<<0); // Double speed SPI
	//SPCR = (1<<SPE) ;	// enable SPI as master, /64 prescaler
	
	//SPI_PORT = SPI_PORT | (1<<MISO_BIT);		// drive outputs to the SPI port
	SPI_DDR = SPI_DDR | (1<<MISO_BIT);
			
	SPCR = (1<<SPE) | (1<<SPIE);	// enable SPI 
}

/*unsigned char SPI_write(unsigned char data)
{
	// Start transmission
	SPDR = data;

	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
	  data = SPDR;
	  
	return  SPDR;
}*/

/*unsigned char SPI_receive()
{
	unsigned char data;
	// Wait for reception complete

	SPDR = 0xff;
	while(!(SPSR & (1<<SPIF)));
	  data = SPDR;

	// Return data register
	return data;
}*/

SIGNAL (SIG_SPI) 
{
	char znaczek;
	znaczek = SPDR;
	if(znaczek == 'q') LCD_Home();
	else	LCD_WriteData(znaczek);
}
