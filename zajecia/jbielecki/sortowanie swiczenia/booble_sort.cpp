#include <iostream>
using namespace std;
int main()
{
	int n; //jaki bedzie rozmiar tablicy
	cin >> n;
    int tab[n];
	for (int i = 0; i < n; i++ ) cin >> tab[i]; //wczytywanie danych do tablicy
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
	for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
	cout << endl;
	   return 0;
}
