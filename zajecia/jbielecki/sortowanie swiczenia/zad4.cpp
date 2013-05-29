// Wyszukiwanie dominanty
// (C)2010 I LO w tabarnowie
//------------------------

#include <iostream>

using namespace std;

int main()
{
    int n,i,j,ile_razy,najczestszy;
	cin >> n;

	int tab[n];
    for(i = 0; i < n; i++) cin >> tab[i];

    // szukamy najczęstszego elementu

    ile_razy = 0;

    for(i = 0; i < n; i++)
    {
        int w = tab[i];
        int c = 0;

        for(j = 0; j < n; j++) if(w == tab[j]) c++;

        if(c > ile_razy)
        {
            ile_razy = c;
            najczestszy = w;
        }
    }
   	cout << najczestszy << " wystepuje ";
	cout << ile_razy << " razy";
	cout << endl;
    return 0;
} 
