#include <iostream> //Adaś, Bartek, i Cezary zastanawiają się, czy w sumie mają więcej niż 21 lat, czy mniej. Pomóż im odpowiedzieć na to pytanie.
using namespace std;

int main()
{
	int adas, bartek, cezary;
	
	cout<<"Podajcie wiek Adasia: \n";
	cin>> adas;

	cout<<"Podajcie wiek Bartka: \n";
	cin>> bartek;

	cout<<"Podajcie wiek Cezarego: \n";
	cin>> cezary;

	if (adas + bartek + cezary > 21)
   	{
		cout<<"Macie razem więcej niż 21 lat!\n";
   	}
	else 
   	{
		cout<<"Razem macie mniej niż 21 lat.\n";
   	}
}
