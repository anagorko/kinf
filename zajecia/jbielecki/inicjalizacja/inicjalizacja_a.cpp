// (C) Janek Bielecki
#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int tab[n];
	
	for(int i = 0; i < n; i++)
	
	{
	
	tab[i] = i;
	
	}

	for(int i = 0; i < n; i++)
	
	{
	
	cout << "tab[" << i << "] = " << tab[i] << endl;
	
	}

}
