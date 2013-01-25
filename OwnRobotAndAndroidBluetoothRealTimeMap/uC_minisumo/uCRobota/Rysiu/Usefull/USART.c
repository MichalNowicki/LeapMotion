/*
 * USART.c
 *
 * Created: 2011-12-12 23:47:43
 *  Author: sMi
 */ 
#include "../Includes/Headers.h"

#define F_CPU 8000000L
#define USART_BAUDRATE 250000 // Error 0.02%
#define BAUD_PRESCALE (F_CPU / (8UL*USART_BAUDRATE) -1)

char receive;


void USART_init()	
{
	UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register 
	UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register 
    
	UCSRA &=0;
	UCSRB &=0;
	UCSRC &=0;
	UCSRA |= (1 << U2X); // Asynchroniczna x2
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE );   // Turn on the transmission and reception circuitry 
    UCSRC |= (1 << UCSZ0) | (1 << UCSZ1)| (1 << URSEL); // Use 8-bit character sizes 
}

void USART_transmit(unsigned char ReceivedByte)
{
	while ((UCSRA & (1 << UDRE)) == 0) {};
    UDR = ReceivedByte; 
}
void USART_receive()
{
	while ((UCSRA & (1 << RXC)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR 
    receive = UDR; 
}
void USART_SendInt(int Data2Send)
{
	char znak;
	for(int i=1;i>=0;i--)
	{
		// 04 00
		znak=(Data2Send>>(i*8)) & 0x00ff;
		USART_transmit(znak);
	}
}
SIGNAL(SIG_UART_RECV)
{
	 receive = UDR;
	 // Odkodowanie rozkazu
	 USART_transmit(receive);
}