/*
 * SPI.h
 *
 * Created: 2012-04-21 19:24:40
 *  Author: sMi
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../Headers.h"

#define  MOSI_BIT		3
#define  MISO_BIT		4
#define  SCK_BIT		5
#define  SS_BIT			2

#define  SPI_PORT		PORTB
#define  SPI_DDR		DDRB

void SPI_init();

#endif /* SPI_H_ */