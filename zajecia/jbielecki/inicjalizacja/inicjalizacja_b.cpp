#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int tab[n];
	
	for(int i = 7; i < n + 7; i++)
	
	{
	
	tab[i] = i;
	
	}

	for(int i = 7; i < n + 7; i++)
	
	{


	cout << "tab[" << i - 7 << "] = " << tab[i] << endl;
	
	}

}
