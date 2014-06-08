#include"iostream"
using namespace std;

void jakie()
{
cout<<"\nPodaj swoje działanie\n";

return;
}

void powitanie()
{
if(kalpo=='0')
	{
	cout<<"Witaj w programie SUPER KALKULATOR. Program ten dysponuje kilkoma możliwościami obliczeń.";
	}
else
	{
	if(kalpo=='1')
		{
		cout<<"Witaj w kalkulatorze klasycznym.";
		jakie();
		}
	if(kalpo=='2')
		{
		cout<<"Witaj w kalkulatorze liczącym w odwrotnej notacji polskiej.";
		jakie();
		}
	if(kalpo=='3')
		{
		cout<<"Witaj w kalkulatorze operującym na ułamkach zwykłych.";
		jakie();
		}
	if(kalpo=='4')
		{
		cout<<"Witaj w programie liczącym pola figur.\n1. Pole kwadratu\n2. Pole prostokąta\n3. Pole trókata\n4. Pole trapez\n5. Pole równoległoboku\n6. Pole koła\n";
		}
	}

return;
}

void mozliwosci()
{
cout<<"\n1. Klasyczny kalkulator\n2. Kalkulator liczący w odwrotnej notacji polskiej\n3. Kalkulator działający na ułamkach zwykłych\n4. Obliczanie pól\n5. Przypomnij możliwości\n6. Zakończ\n";

return;
}

void ktora()
{
cout<<"Którą opcję wybierasz?\n";

return;
}

void koniec()
{
if(korzystanie==false)
	{
	cout<<"Dziękuję za uruchomienie mojego programu. Do zobaczenia.\n";
	}
if(korzystanie==true)
	{
	cout<<"Dziękuję za skorzystanie z mojego programu. Do zobaczenia. ;)\n";
	}

return;
}

void wynik(string s,float w)
{
cout<<"Wynikiem działania "<<s<<" jest "<<w<<"\n"<<s<<" = "<<w<<"\n";

return;
}

