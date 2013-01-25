/*
 * USART.h
 *
 * Created: 2012-03-16 20:19:44
 *  Author: sMi
 */ 


#ifndef USART_H_
#define USART_H_

void USART_init();
void USART_transmit(unsigned char ReceivedByte);
void USART_send(char* data);
void USART_receive();
void USART_SendInt(int Data2Send);

#endif /* USART_H_ */