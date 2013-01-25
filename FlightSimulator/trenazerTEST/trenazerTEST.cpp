// trenazerTEST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>

using namespace std;

// typedef funkcji
typedef int (*funkcja)();
typedef int (*funkcja2)(int x);
typedef bool (*funkcjaBOOL)();
typedef DWORD (*funkcja3)();
typedef float (*funkcjaFLOAT)();

// deklaracje funkcji
funkcja synchronizuj;
funkcja2 razy2;
funkcja3 stan,stan2;
funkcjaBOOL polaczenie;
funkcjaFLOAT polozenieX,polozenieY,polozenieZ;

bool term;

DWORD WINAPI Sync(LPVOID lpdwParam)
{
	while(!term)
	{
		synchronizuj();
		Sleep(10);
	}
	return 0;
}
void TEST(int x)
{
	int y;
	y = razy2(x);
	cout<<y<<endl;
	cout<<x<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE DLL;
	term= false;
	// Ladowanie biblioteki
	DLL = LoadLibrary (L"TrenazerSterownik.dll"); 

   if (DLL) 
   { 
	  cout<<"Zalaczono biblioteke"<<endl;
	  // Ladowanie funkcji 
	  synchronizuj = (funkcja) GetProcAddress (DLL, "Synchronizuj");
	  razy2 = (funkcja2) GetProcAddress (DLL, "Test"); 
	  stan = (funkcja3) GetProcAddress (DLL, "Stan");
	  stan2 = (funkcja3) GetProcAddress (DLL, "Stan2");
	  polaczenie = (funkcjaBOOL) GetProcAddress (DLL, "JestPolaczenie");

	  polozenieX = (funkcjaFLOAT) GetProcAddress (DLL, "PolozenieOsX");
	  polozenieY = (funkcjaFLOAT) GetProcAddress (DLL, "PolozenieOsY");
	  polozenieZ = (funkcjaFLOAT) GetProcAddress (DLL, "PolozenieOsZ");

	  

	  // Synchronizacja 
	  HANDLE uchwyt;
	  uchwyt=CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE) Sync, (LPVOID) 0,0,0);

      // Wywolania funkcji z biblioteki
		Sleep(1000);
	for(int w=0;w<5;w++)
	{
	   cout<<"Polaczenie  == "<<polaczenie()<<endl;
	    Sleep(10);
	}
	   /*int te = 2;
	   TEST(te);
	   cout<<"te : 2*2 = " <<te<<endl;
	   TEST(te);
	   cout<<"te : 4*2 = " <<te<<endl;
	    cout<<"Polaczenie  == "<<polaczenie()<<endl;*/

	   cout<<"Stan trenazera"<<endl;
	   cout<<stan()<<" ";
	   Sleep(10);
	   cout<<stan2()<<endl;

	   cout<<"Polozenie: "<<endl;
	    Sleep(10);
	   cout<<"X = "<<polozenieX();
	    Sleep(10);
		cout<<"\tY = "<<polozenieY();
		 Sleep(10);
		 cout<<"\tZ = "<<polozenieZ()<<endl;

	  Sleep(1500);
	  term=false;

	  // czekania na koniec watku
	  WaitForSingleObject(uchwyt,INFINITE);

	  //Zwolnienie biblioteki
      FreeLibrary (DLL); 
   } 
   else 
   {
      cout << "Nie udalo sie znalezc biblioteki dll!" << endl;
   }
   //(*fu)();
	return 0;
}

