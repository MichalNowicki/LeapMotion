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

#define I2C_MAPA 0x0F
#define I2C_POZYCJA 0x0A

void I2C_init();
void I2C_read(unsigned char znak); 
void I2C_write(unsigned char znak); 

#define DANE_SIZE 6
unsigned char dane[DANE_SIZE];
unsigned char dane_indeks;

#endif /* I2C_H_ */