#include <iostream>
using namespace std;
int main ()
{
	int n [20];
	for (int a = 0; a < 20; a++)
	{
		cout << "Wpisz liczbe nr " << a + 1 << ":";
		cin >> n [a];
	}
	for (int a = 19; a >= 0; a--)
	{
		cout << n [a];
	}
	return 0;
}
