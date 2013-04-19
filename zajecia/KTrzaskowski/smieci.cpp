#include <iostream> /* Rodzeństwo Bajtuś i Bajtotka mają dyżur wynoszenia śmieci. Bajtuś - jako starszy brat - wynosi śmieci we wszystkie nieparzyste dni miesiąca, a Bajtotka - w parzyste. Wczytaj dzień miesiąca i napisz, które z dzieci tego dnia ma dyżur wynoszenia śmieci.*/
using namespace std;

int main()
{
	int a;

	cout<<"Podaj podaj numer dnia: \n";
	cin>> a;
	
	if  (a > 31 || a < 0)
	{
		cout<<"fatal error\nerror!\n48634 error\nNie ma takiego dnia miesiąca\n\n";
	}
	else if (a % 2 == 0)
	{
		cout<<"dzisiaj śmieci wynosi Bajtotka.\n";
	}
	else if (a % 2 != 0)
	{
		cout<<"dzisiaj śmieci wynosi Bajtuś.\n";
	}
	
}

