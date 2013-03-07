// (C) Janek Bielecki
#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int tab[n];
	long  z = 4;
	
	for(long i = 0; i < n; i++)
	
	{
	
	
	tab[i] = z;
	
	z ++;
	}

	for(long i = 0; i < n; i++)
	
	{
	
	cout << "tab[" << i << "] = " << tab[i] << endl;
	
	}

}
