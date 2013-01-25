/*
 * Silniki.h
 *
 * Created: 2011-12-12 22:47:13
 *  Author: sMi
 */ 


#ifndef SILNIKI_H_
#define SILNIKI_H_

// PORTC 6 AIN1 -> PORTD 5 (to do)
// PORTC 7 AIN2 -> PORTB 0 (to do)
#define DDR_SIL_1_1 DDRD
#define DDR_SIL_1_2 DDRB
#define PORT_SIL_1_1 PORTD
#define PORT_SIL_1_2 PORTB
#define AIN1 5
#define AIN2 0
// PORTB 2 PWMB

#define DDR_SIL_2 DDRD
#define PORT_SIL_2 PORTD
#define BIN1 6
#define BIN2 7
// PORTB 1 PWMA


// 1-do przodu, 0 do tylu
#define kierunek_lewe (PORT_SIL_1_2 & (1<<AIN2))
#define kierunek_prawe (PORT_SIL_2 & (1<<BIN2))

// Uzytkowe
void Silniki_Init();
void Silniki_Start();
void JazdaNaPrzod();
void SkretWPrawo();
void SkretWLewo();
void Silniki_Stop();
void ZmienKierunek();
void ZmienKierunekLewe();
void ZmienKierunekPrawe();

// Raczej systemowe
void SetWypelnieniePWM(int a, int b); // od 0 do 100



#endif /* SILNIKI_H_ */