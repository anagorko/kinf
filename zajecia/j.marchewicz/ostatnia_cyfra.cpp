#include <iostream>
using namespace std;
int main ()
{
	int i;
	int a = 3;
	int b = 9;
	int c = 7;
	int d = 1;

	cout << "Podaj wykładnik N do działania 3^N: " << endl;
	cin >> i;
	if ( i % 4 == 1)
	{
		
		cout << " Ostatnia cyfrą wyniku jest " << a << endl;
	}
	else if ( i % 4 == 2)
	{
		
		cout << " Ostatnia cyfrą wyniku jest " << b << endl;
	}
	else if ( i % 4 == 3)
	{
	
		cout << " Ostatnia cyfrą wyniku jest " << c << endl;
	}
	else if ( i % 4 == 0)
	{
		
		cout << " Ostatnia cyfrą wyniku jest " << d << endl;
	}
}
