#include <iostream>
using namespace std;
int main ()
{
	int l;	//liczba ludzi wchodzacych na rynek
	cin>>l;
	int tab [1000000]; //tablica przedstawiajaca ...
	for (int i = 0; i < 2*l; i++)
	{
		int x;
	   	cin >> x;
		tab[i] = 2 * x;
		i++;

	   	cin >> x;
		tab[i] = 2 * x + 1;
		i++;
	}
}
