
#include <iostream>
using namespace std;

int main() 
{

	int q;

	cin >> q;
	q = q - 1;

for (int i = q; i >= 0; i--) 
	{
		for (int u = 0; u <= i; u++)
		{
			cout << " ";
		}
	
		for (int y = 2 * (q - i); y >= 0; y--)
		{
			cout << "*";
		}
		cout << endl; 
	
	}

for (int i = q + 1; i >= 0; i--) 
	{
		for (int u = 1; u <= i; u++)
		{
			cout << " ";
		}	
		for (int y = 2 * (q + 1 - i); y >= 0; y--)
			{
			cout << "*";
			}	
		cout << endl; 
	
	}
}
