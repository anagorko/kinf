#include<iostream>
#include<math.h>
#include<string.h>
#include "kalkulator.h"
using namespace std;
int main()
{
cout<<"Witaj w programie kalkulator. Program tan dysponuje dwoma możliwościami obliczeń.\n1. Klasyczny kalkulator\n2. Obliczanie pól\n3.Zakończ\n";
int kalpo=0;
bool korzystanie=false;
while(1)
	{
	cout<<"Którą opcję wybierasz?";
	cin>>kalpo;
	if(kalpo==1)
		{
		korzystanie=true;
		kalkulator();
		}
	if(kalpo==2)
		{
		korzystanie=true;
		
		}
	if(kalpo==3)
		{
		if(korzystanie==false)
			{
			cout<<"Dziękuję za uruchomienie mojego programu. Do zobaczenia.\n";
			}
		if(korzystanie==true)
			{
			cout<<"Dziękuję za skorzystanie z mojego programu. Do zobaczenia. ;)\n";
			}
		break;
		}
	}

return 0;
}
