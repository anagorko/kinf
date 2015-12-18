#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    cin >> t;
    int a[t], b[t];
    int naj = 0;
    for (int i = 0; i < t; i++)
    {
        cin >> a[i] >> b[i];
        naj = max(naj, b[i]);
    }

    naj += 5;
    long long tab[naj];

    // sito
    for (int i = 0; i < naj; i++) tab[i] = 1;
    for (int i = 2; i < naj; i++)
    {
        if (tab[i])
        {
            for (int j = i*2; j < naj; j += i)
            {
                tab[j] = 0;
            }
        }
    }

    // sumowanie
    for (int i = 2; i < naj; i++)
    {
        tab[i] = tab[i-1] + (tab[i] ? i : 0);
    }

    for (int i = 0; i < t; i++)
    {
        cout << tab[b[i]] - tab[a[i]-1] << endl;
    }
}
