/*
 * Mapa.h
 *
 * Created: 2011-12-18 03:26:41
 *  Author: sMi
 */ 


#ifndef MAPA_H_
#define MAPA_H_


// Rozmiar mapy terenu
// 20 * 4 = 80 pol w linii
// 80 * 80 = 6400 pol
//
// Kazdy raster ma 1cm x 1 cm
// Stad 80 pol jest rowne 80 cm
// 
// Szerokosc robota to 12.5cm, a wiêc robota ma mapê (80-12.5)/2 = 33.75 cm w bok (sensory widz¹ do 30cm, wiêc jest znaczny zapas)
//
unsigned int Mapa[20][20];

void UstawMape(int ind_x, int ind_y);
int ReadMap(int ind_x, int ind_y);
int ReadRaster(int x, int y);

void MapaSendRaster(int x, int y);
void MapaSendLineX(int y);
void MapaSendLineY(int x);
void MapaSendALL();



#endif /* MAPA_H_ */