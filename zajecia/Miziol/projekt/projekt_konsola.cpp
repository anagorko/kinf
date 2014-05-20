#include<iostream>
#include<math.h>
#include<string.h>
#include"kalkulator.h"
#include"pola.h"
#include"ulamki.h"
using namespace std;
int main()
{
cout<<"Witaj w programie kalkulator. Program ten dysponuje dwoma możliwościami obliczeń.\n1. Klasyczny kalkulator\n2. Obliczanie pól\n3. Kalkulator działający na ułamkach zwykłych\n4. Przypomnij możliwości\n5. Zakończ\n";
int kalpo=0;
bool korzystanie=false;
cout<<"Którą opcję wybierasz?\n";
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
		pola();
		}
	if(kalpo==3)
		{
		korzystanie=true;
		ulamki();
		}
	if(kalpo==4)
		{
		cout<<"Witaj w programie kalkulator. Program tan dysponuje dwoma możliwościami obliczeń.\n1. Klasyczny kalkulator\n2. Obliczanie pól\n3. Kalkulator działający na ułamkach zwykłych\n4. Przypomnij możliwości\n5. Zakończ\n";
		}
	if(kalpo==5)
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
	cout<<"4.Przypomnij możliwości\nKtórą opcję wybierasz?";
	}

return 0;
}
