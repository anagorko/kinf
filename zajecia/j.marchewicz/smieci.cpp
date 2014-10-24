#include <iostream>
using namespace std;
int main ()
{
	int i;
	cout << "Podaj dzień miesiąca: " << endl;
	cin >> i;
	if ( i % 2 == 1)
	{
		cout << "Dzisiaj śmieci wynosi Bajtek." << endl;
	}
	else
	{
		cout << "Dzisiaj śmieci wynosi Bajtotka." << endl;
	}
}
