/*
 * I2C.h
 *
 * Created: 2012-04-21 18:55:43
 *  Author: sMi
 */ 


#ifndef I2C_H_
#define I2C_H_

#define adres_slave 0x02
#define WRITE 0x00
#define READ 0x01

#define BUFFER_SIZE 6
#define I2C_INFO 4

unsigned char buffer[BUFFER_SIZE];
unsigned char buf_i;
unsigned char akt_indeks;

unsigned char I2C_received;

void I2C_init();
void I2C_RequestTransmision();

#endif /* I2C_H_ */