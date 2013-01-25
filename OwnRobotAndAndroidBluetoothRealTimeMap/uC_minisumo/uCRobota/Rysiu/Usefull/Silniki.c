/*
 * Silniki.c
 *
 * Created: 2011-12-12 22:47:26
 *  Author: sMi
 */ 
#include "../Includes/Headers.h"

void Silniki_Init()
{
	// AIN1 i AIN2 Silnika1 jak wyjscia
	DDR_SIL_1_1 |= (1<<AIN1);
	DDR_SIL_1_2 |= (1<<AIN2);
	
	// BIN1 i BIN2 Silnika2 jako wyjscia
	DDR_SIL_2 |= (1<<BIN1) | (1<<BIN2);
	
	// timer 1 fast PWM 8 bit 
	TCCR1A = _BV(COM1A1)| _BV(COM1B1) |_BV(WGM10 ); // |_BV(COM1A0)|_BV(COM1B0)  
	//no prescaling
	TCCR1B = _BV(CS10)|_BV(WGM12);  
	
	// PWM1 i PWM2 as outputs
	DDRB |= (1<<1) |(1<<2);
	
	OCR1A = 0;
	OCR1B = 0;
	
	Silniki_Start();
}
void Silniki_Start()
{
	// AIN1 i AIN2 Silnika1 -> kierunki poczatkowe
	PORT_SIL_1_1 &= ~(1<<AIN1);
	PORT_SIL_1_2 |= (1<<AIN2);
	
	// BIN1 i BIN2 Silnika2 -> kierunki poczatkowe
	PORT_SIL_2 &= ~(1<<BIN1);
	PORT_SIL_2 |= (1<<BIN2);
}
void SetWypelnieniePWM(int b, int a)
{
	OCR1A = (a*256)/100;
	OCR1B = (b*256)/100;
}
void JazdaNaPrzod()
{
	SetWypelnieniePWM(56,75);
}
void SkretWLewo()
{
	SetWypelnieniePWM(25,92);
}
void SkretWPrawo()
{
	SetWypelnieniePWM(70,35);
}
void Silniki_Stop()
{
	SetWypelnieniePWM(0,0);
}
void ZmienKierunek()
{
	ZmienKierunekLewe();
	ZmienKierunekPrawe();
}
void ZmienKierunekLewe()
{
	if(kierunek_lewe == 1)
	{
		PORT_SIL_2 &= ~(1<<BIN1);
		PORT_SIL_2 |= (1<<BIN2);
	}
	else
	{
		PORT_SIL_2 |= (1<<BIN2);
		PORT_SIL_2 &= ~(1<<BIN1);		
	}
}
void ZmienKierunekPrawe()
{
	if(kierunek_prawe == 1)
	{
		PORT_SIL_1_1 |= (1<<AIN1);
		PORT_SIL_1_2 &= ~(1<<AIN2);
	}
	else
	{
		PORT_SIL_1_1 &= ~(1<<AIN1);
		PORT_SIL_1_2 |= (1<<AIN2);		
	}
}	