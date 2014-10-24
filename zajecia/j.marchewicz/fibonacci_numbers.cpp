#include <iostream>
using namespace std;
int main ()
{
	int pierwsza_liczba = 0;
	int druga_liczba = 1;
	int suma_dwoch_kolejnych;
	int suma_parzystych = 0;
	for (int i = druga_liczba; druga_liczba <= 4000000; i++)
	{
		suma_dwoch_kolejnych = pierwsza_liczba + druga_liczba;
		pierwsza_liczba = druga_liczba;
		druga_liczba = suma_dwoch_kolejnych;
		if ( druga_liczba % 2 == 0)
		{
			suma_parzystych += druga_liczba;
		}
	}
	cout << suma_parzystych << endl;

}
