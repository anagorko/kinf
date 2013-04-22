#include <iostream>
using namespace std;
int main()
{
	int n; //jaki bedzie rozmiar tablicy
	cin >> n;
    float tab[n];
	float wynik;
	for (int i = 0; i < n; i++ ) cin >> tab[i];
for(int i=0;i<n;i++)
	{
	for(int j=i+1;j<n;j++)
		{
		if(tab[i]>tab[j])
			{
			int x = tab[i];
			tab[i] = tab[j];
			tab[j] = x;
			}
		}
	}	   

if(n % 2 == 0) wynik = (tab[n/2]+tab[(n/2)-1])/2;
if(n % 2 == 1) wynik = tab[n/2];
cout << wynik << endl;
return 0;
}
