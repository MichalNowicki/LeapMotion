/*
 * I2c.c
 *
 * Created: 2012-04-21 18:56:03
 *  Author: sMi
 */ 

#include "../Headers.h"

void I2C_init()
{
	// 100kHz I2C
	TWSR = 0x00;
	TWBR = 0x20;
	
	// Przerwanie wykazuj¹ce dane do pobrania
	DDRD &= ~(1<<2);
	
	// Any change generates an interrupt
	MCUCR |=(1<<ISC00);
	
	// Wlaczenie przerwania
	GICR |= (1<<INT0);
	
	// Wyzerowanie indeksu buforu odbioru
	dane_indeks = 0;
}



void I2C_read(unsigned char znak) 
{ 
	//uint16_t read;      
	
	// START
	TWCR =(1 << TWINT) | (1 << TWSTA) | ( 1 << TWEN ); 
	while(!(TWCR & (1 << TWINT))); 
	
	// SLA+W
	TWDR = (adres_slave << 1) | WRITE; 
	TWCR =(1 << TWINT) | (1 << TWEN); 
	while(!(TWCR & (1 << TWINT))); 
	
	// Przeslanie komendy
	TWDR = znak; 
	TWCR =(1 << TWINT) | (1 << TWEN); 
	while(!(TWCR & (1 << TWINT))); 
	
	// START
	TWCR =(1 << TWINT) | (1 << TWSTA) | ( 1 << TWEN ); 
	while(!(TWCR & (1 << TWINT))); 
  
	// SLA+R
	TWDR = (adres_slave << 1) | READ ; 
	TWCR =(1 << TWINT) | (1 << TWEN); 
	while(!(TWCR & (1 << TWINT))); 
  
	// READ the 6-byte message
	dane_indeks = 0;
	while (dane_indeks <6)
	{
		// Read byte
		TWCR =(1 << TWINT) | (1 << TWEN); 
		
		// Generate ACK if not the last byte
		if(dane_indeks!= 5) TWCR |= (1<<TWEA);
		
		while(!(TWCR & (1 << TWINT))); 
		
		dane[dane_indeks] = TWDR; 
		USART_transmit(dane[dane_indeks]);
		dane_indeks++;
	}
	
	// STOP    
	TWCR =(1 << TWINT) | (1<<TWEN) | (1<<TWSTO);
} 

void I2C_write( unsigned char znak) 
{ 
	// START
	TWCR =(1 << TWINT) | (1 << TWSTA) | ( 1 << TWEN ); 
	while(!(TWCR & (1 << TWINT))); 
	
	// SLA+W
	TWDR = (adres_slave << 1) | WRITE; 
	TWCR =(1 << TWINT) | (1 << TWEN); 
	while(!(TWCR & (1 << TWINT))); 
	
	// Przeslanie znaku
	TWDR = znak; 
	TWCR =(1 << TWINT) | (1 << TWEN); 
	while(!(TWCR & (1 << TWINT))); 
	
	// STOP
	TWCR =(1 << TWINT) | (1<<TWEN) | (1<<TWSTO); 
} 

SIGNAL(SIG_INTERRUPT0)
{
	I2C_read(I2C_POZYCJA);
}