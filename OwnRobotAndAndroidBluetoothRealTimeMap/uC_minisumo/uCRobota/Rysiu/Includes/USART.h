/*
 * USART.h
 *
 * Created: 2011-12-12 23:47:24
 *  Author: sMi
 */ 


#ifndef USART_H_
#define USART_H_

void USART_init();
void USART_transmit(unsigned char ReceivedByte);
void USART_receive();
void USART_SendInt(int Data2Send);

#endif /* USART_H_ */