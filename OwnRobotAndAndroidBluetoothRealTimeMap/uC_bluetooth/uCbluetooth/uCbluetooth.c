/*
 * uCbluetooth.c
 *
 * Created: 2012-03-16 18:05:51
 *  Author: sMi
 */ 
#include "Headers.h"

void init()
{
	USART_init();
	LCD_Initalize();
	I2C_init();
}

int main(void)
{
	init();
	

	_delay_ms(1); // czekaj 1ms 
	LCD_Home();
	
	_delay_ms(1000);
	LCD_WriteText("Start");
	_delay_ms(1000);
	
	sei();
	LCD_Home();
	
    while(1)
    {
		// Czyste przekazywanie
	}
}