// (C) Janek Bielecki
#include <iostream>

using namespace std;

int main()
{
	int tab[20];
	
	for(int i = 0; i < 20; i++)
	
	{

	cin >> tab[i];
	
	}

	for(int i = 0; i < 20; i++) 
	
	{

	if((tab[i] % 2) == 0)
		{
	
	cout << tab[i];
		}

	}
	for(int i = 0; i < 20; i++) 
	{

	if((tab[i] % 2) != 0)
		{
	
	cout << " " << tab[i];
		}

	}
}
