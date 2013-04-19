#include <iostream>
using namespace std;
int main()
{
	int n; //jaki bedzie rozmiara tablicy
	cin >> n;
    int tab[n];
	for (int i = 0; i < n; i++ ) cin >> tab[i]; //wczytywanie danych do tablicy
    for (int i = 0; i < n; ++
        for (int j=0; j < n; j ++)
            if (tab[j]>tab[j + 1]){
				int x = tab[j];
                tab[j] = tab[j + 1];
				tab[j + 1] = x;
			}   
	for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
	cout << endl;
	   return 0;
}
