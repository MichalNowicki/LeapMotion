/*
 * Rysiu.c
 *
 * Created: 2011-12-12 19:40:56
 *  Author: sMi
 */ 
#include "Includes/Headers.h"

void Init()
{
	I2C_init();
	USART_init();
	Enkoders_Init();
	Sharp_Init();
	Silniki_Init();
}


int main(void)
{
	
	Init();
	
	_delay_ms(10000);
	
	sei();
	
	
	
    while(1)
    {
    }
}