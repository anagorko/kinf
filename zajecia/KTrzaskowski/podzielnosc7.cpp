#include <iostream> /*Wczytaj liczbę i wypisz, czy jest podzielna przez 7 czy nie. Czy znasz cechę podzielności przez 7?*/
using namespace std;

int main()
{
	int liczba;
	
	cout<<"Podaj liczbę, aby dowiedzieć się czy dzieli się przez 7: \n";
	cin>> liczba;

	if (liczba % 7 == 0)
	{
		cout<<"Podana liczba dzieli się przez 7\n";
	}
	else 
	{
		cout<<"Podana liczba nie dzieli się przez 7\n";
	}
} 
	
