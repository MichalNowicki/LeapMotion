/*
 * I2c.c
 *
 * Created: 2012-04-21 18:56:03
 *  Author: sMi
 */ 

#include "../Includes/Headers.h"


void I2C_init()
{	
	buf_i = 0;
	akt_indeks = 0;
	
	TWAR = (adres_slave<<1);
	TWCR = 0x00;
	TWCR |= (1<<TWEN) | (1<<TWEA) | (1<<TWIE);
	
	// Ustawienie portu sygnalizuj¹cego jak wyjœcia
	DDRD |= (1<<I2C_INFO);
}

void I2C_RequestTransmision()
{
	if(PORTD & (1<<I2C_INFO))
		PORTD &= ~(1<<I2C_INFO);	
	else 
		PORTD |= (1<<I2C_INFO);	
};

SIGNAL (SIG_2WIRE_SERIAL) 
{ 
	switch (TW_STATUS) 
	{ 
		// case TW_ST_SLA_NACK:	
		// case TW_SR_SLA_NACK:	
		case TW_SR_SLA_ACK:
			I2C_received = TWDR; 
			TWCR |= (1<<TWEA);
			break;
		case TW_ST_SLA_ACK:
			TWDR = buffer[buf_i++];
			TWCR |= (1<<TWEA);
			break;
			
		// case TW_SR_DATA_NACK:
		case TW_SR_DATA_ACK:
			I2C_received = TWDR;
			USART_transmit(I2C_received);
			if(I2C_received == 's')
				Silniki_Stop();
			// Lewo
			else if(I2C_received == 'a')
				SkretWLewo();
			// Przod
			else if(I2C_received == 'w')
				JazdaNaPrzod();
			// Prawo
			else if(I2C_received == 'd')
				SkretWPrawo();
		
			TWCR |= (1<<TWEA);
			break;
			
		// case TW_ST_DATA_NACK:
		case TW_ST_DATA_ACK:
			//USART_transmit(buffer[1]);
			//TWCR = buffer[buf_i++]; // DATA 	
			//if(buf_i==BUFFER_SIZE) buf_i = 0;
			TWDR = buffer[buf_i++];
			TWCR |= (1<<TWEA);	
			
			break;
		default:
			buf_i = 0;
			break;
	} 
	TWCR |= _BV(TWINT);
	 
} 