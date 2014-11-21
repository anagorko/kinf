#include <iostream>
using namespace std;
int main ()
{
	int n;
	cout << "Podaj N" << endl;
	cin >> n;
	for (int i = 0; i < n ; i++)
		{
			for ( int j = 0; j < (4 * n); j++)
			{
				cout << ".";
			}
			cout << endl;
		}

	for (int i = 0; i < n ; i++)
		{
			for ( int j = 0; j < (4 * n); j++)
			{
				cout << "#";
			}
			cout << endl;
		}

}
