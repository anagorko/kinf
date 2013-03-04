#include <iostream>
using namespace std;
int main()
{
	int tab[20];

	for(int i = 0; i < 20; i++)
	{
	
	cin >> tab[i];
	
	}
	
	for(int i = 19; i >= 0; i--) 
	{
	cout << tab[i] << " ";
	}
	cout << endl;
}
