/*
 * SPI.c
 *
 * Created: 2012-04-21 19:24:31
 *  Author: sMi
 */ 
#include "../Includes/Headers.h"

void SPI_init()
{
	SPI_DDR = SPI_DDR | (1<<MOSI_BIT) | (1<<SCK_BIT) | (1<<SS_BIT);
	SPI_PORT = SPI_PORT | (1<<MOSI_BIT) | (1<<SCK_BIT) | (1<<SS_BIT);		// drive outputs to the SPI port
	
	//SPSR = (1<<SPI2X); // Double speed SPI
	SPCR = (1<<MSTR)|(1<<SPE)|(1<<SPR1); //setup SPI: Master mode, MSB first, SCK phase low, SCK idle low
}

void SPI_write(unsigned char data)
{
	// Start transmission
	SPDR = data;

	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
}