/*
 * Mapa.c
 *
 * Created: 2011-12-18 13:16:56
 *  Author: sMi
 */ 
#include "../Includes/Headers.h"

void UstawMape(int ind_x, int ind_y)
{
	if(ind_x > 0 && ind_x < 80 && ind_y >0 && ind_y < 80 )
	{
		int tym = ind_x>>2, tym2 = ind_y>>2;
		ind_x = ind_x - tym<<2;
		ind_y = ind_y - tym<<2;
		Mapa[tym][tym2] |= (1<< ( ind_y*4 + ind_x));
	}
}
int ReadMap(int ind_x, int ind_y)
{
	if(ind_x > 0 && ind_x < 80 && ind_y >0 && ind_y < 80 )
	{
		int tym = ind_x>>2, tym2 = ind_y>>2;
		ind_x = ind_x - tym<<2;
		ind_y = ind_y - tym<<2;
		return (Mapa[tym][tym2] &= (1<< ( ind_y*4 + ind_x)));
	}
	return -1;
}
int ReadRaster(int x, int y)
{
	if(x>=0 && x<20 && y>=0 && y<20)
	{
		return Mapa[x][y];		
	}
}
void MapaSendLineX(int y)
{
	int tym;
	for(int i=0;i<20;i++)
	{
		tym = ReadRaster(i,y);
		USART_SendInt(tym);
	}
}
void MapaSendLineY(int x)
{
	int tym;
	for(int i=0;i<20;i++)
	{
		tym = ReadRaster(x,i);
		USART_SendInt(tym);
	}	
}
void MapaSendRaster(int x, int y)
{
	USART_SendInt(ReadRaster(x,y));	
}
void MapaSendALL()
{
	for(int i=0;i<20;i++) MapaSendLineX(i);
}