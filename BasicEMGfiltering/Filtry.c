#include "Filtry.h"
#include "Notching.h"
#include "HighPass20pass40dB.h"


float x_notch[3],y_notch[3];
float x_pass[9][3], y_pass[9][3];


void Filtr_init()
{
	int i,j;
	for(i=0;i<3;i++) x_notch[i] = y_notch[i] = 0;
	for(i=0;i<MWSPT_NSEC;i++) for(j=0;j<3;j++) x_pass[i][j] = y_pass[i][j] = 0;
}

inline float Notching(float value)
{
	float w = 0;

	x_notch[2] = x_notch[1];
	x_notch[1] = x_notch[0];
	x_notch[0] = value;

	y_notch[2] = y_notch[1];
	y_notch[1] = y_notch[0];

	int i;
	for(i=0;i<NL2;i++) w+= (NUM2[i]*x_notch[i]);
	for(i=1;i<DL2;i++) w-= (DEN2[i]*y_notch[i]);
	w/= DEN2[0];

	y_notch[0] = w;

	return w;
}

inline float HighPass(float value)
{
	float w;

	int i,j;
	for(i=0;i<MWSPT_NSEC;i++)
	{
		w = 0;

		// i oznacza, który filtr w kaskadzie
		// drugi indeks to ile probek wstecz od obecnej chwili czasowej
		x_pass[i][2] = x_pass[i][1];
		x_pass[i][1] = x_pass[i][0];
		x_pass[i][0] = value;

		y_pass[i][2] = y_pass[i][1];
		y_pass[i][1] = y_pass[i][0];

		for(j=0;j<NL[i];j++)	w+= (NUM[i][j]*x_pass[i][j]);
		for(j=1;j<DL[i];j++)	w-= (DEN[i][j]*y_pass[i][j]);
		w/=DEN[i][0];

		y_pass[i][0] = w;
	}
	return y_pass[MWSPT_NSEC-1][0];
}
