#include <iostream>
using namespace std;
int main ()
{
	int wynik;
	for (int i = 0; i < 1000; i++)
	{
		if ( (i % 3 == 0) || (i % 5 == 0) )
		{
			wynik += i;
		}
	}
	cout << wynik << endl;
}

