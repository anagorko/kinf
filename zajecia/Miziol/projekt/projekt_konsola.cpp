#include<iostream>
#include<math.h>
#include<string.h>
#include"kalkulator.h"
#include"pola.h"
using namespace std;
int main()
{
cout<<"Witaj w programie kalkulator. Program ten dysponuje dwoma możliwościami obliczeń.\n1. Klasyczny kalkulator\n2. Obliczanie pól\n3.Przypomnij możliwości\n4.Zakończ\n";
int kalpo=0;
bool korzystanie=false;
cout<<"Którą opcję wybierasz?\n";
while(1)
	{
	cout<<"Witaj w programie kalkulator. Program tan dysponuje dwoma możliwościami obliczeń.\n1. Klasyczny kalkulator\n2. Obliczanie pól\n3.Zakończ\n";
	cin>>kalpo;
	if(kalpo==1)
		{
		korzystanie=true;
		kalkulator();
		}
	if(kalpo==2)
		{
		korzystanie=true;
		pola();
		}
	if(kalpo==3)
		{

		}
	if(kalpo==4)
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
	cout<<"3.Przypomnij możliwości\nKtórą opcję wybierasz?";
	}

return 0;
}
