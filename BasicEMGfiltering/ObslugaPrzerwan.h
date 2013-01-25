#ifndef _ObsPrze
#define _ObsPrze

//
// Obsluga przerwania od skonczonej konwersji ADC po DMA
//
void DMA1_Channel1_IRQHandler(void);

//
// Obsluga przerwania od skonczonej transmisji po USARTcie
//
void DMA1_Channel4_IRQHandler(void);

#endif
