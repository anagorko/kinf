#include <iostream>
using namespace std;

int main()
{
	int i,j,x;
	int n;
	cin >> n;
	int tab[n];
	for(i = 0; i < n; i++) cin >> tab[i];
	for(j = n - 2; j >= 0; j--)
	{
	 x = tab[j];
	 i = j + 1;
	 while((i < n) && (x > tab[i]))
	 {
		tab[i - 1] = tab[i];
		i++;
	 }
	 tab[i - 1] = x;
	}

	for(i = 0; i < n; i++) cout << tab[i] << " ";
	cout << endl;
	return 0;
}
