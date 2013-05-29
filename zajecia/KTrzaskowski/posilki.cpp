#include <iostream> /*Bajtuś stara się zdrowo odżywiać i je posiłki o regularnych porach dnia: śniadanie o 6 rano, obiad w południe i kolację o 18. Wczytaj godzinę (0, 1, 2, ..., 22, 23) i napisz, czy Bajtuś wtedy je, czy nie.*/
using namespace std;

int main()
{
	int godzina;
	
	cout<<"Podaj godzinę, aby dowiedzieć się czy Bajtuś teraz je: \n";
	cin>> godzina;

	if (godzina == 6)
	{
		cout<<"Bajtuś teraz je śniadanie.\n";
	}
	else if (godzina == 12)
	{
		cout<<"Bajtuś je teraz obiad.\n";
	}
	else if (godzina == 18)
	{
		cout<<"Bajtuś je teraz kolację.\n";
	}
	else if (godzina == 1 - 5 || 7 - 11 || 13 - 17 || 19 - 24)
	{
		cout<<"Bajtuś nie je teraz posiłku, ponieważ je tylko o 6, 12 i 18\n";
	}
	else  
	{
		cout<<"error! error!\n 233289479374 fatal error\nNie ma takiej godziny!\n";
	}
}
