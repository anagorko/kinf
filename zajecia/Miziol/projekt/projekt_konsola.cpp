#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;

//zmienne globalne
int kalpo=0;
bool korzystanie=false;
//zmienne globalne

#include"napisy.h"
#include"kalkulator.h"
#include"odwrocona_notacja_polska.h"
#include"ulamki.h"
#include"pola.h"

int main()
{
powitanie();
mozliwosci();
ktora();

while(1)
	{
	cin>>kalpo;
	if(kalpo==1)
		{
		korzystanie=true;
		kalkulator();
		}
	if(kalpo==2)
		{
		korzystanie=true;
		odwrotna_notacja_polska();
		}
	if(kalpo==3)
		{
		korzystanie=true;
		ulamki();
		}
	if(kalpo==4)
		{
		korzystanie=true;
		pola();
		}
	if(kalpo==5)
		{
		mozliwosci();
		}
	if(kalpo==6)
		{
		koniec();
		break;
		}
	cout<<"5.Przypomnij możliwości\n";
	ktora();
	}

return 0;
}
