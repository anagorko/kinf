#include <iostream> // ulepszony kwadrat01 z pierwszych zajęć
using namespace std;

int main()
{
	int a;
	
	cout<<"Podaj liczbę, którą odejmie się od 100 rzędów gwiazdek:\n";
	cin>> a;

	while (a < 100)
	{
		cout<<"**************\n";
		a++;
	}
	
	if (a > 100)
	{
		cout<<"Niestety twoja liczba jest za duża.\n";
	}
}
