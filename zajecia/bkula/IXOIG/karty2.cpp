
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int t, n;
    cin >> t >> n;
    int k[t], m[t];
    int rozmiar = 1;
    for (int i = 0; i < t; i++)
    {
        cin >> k[i] >> m[i];
        rozmiar = max(rozmiar, m[i]);
    }
    int tab[rozmiar+1][t];
    for (int i = 0; i < t; i++)
    {
        tab[0][i] = k[i];
    }
    for (int i = 0; i < rozmiar; i++)
    {
    ///f(x) = {2*x when x <= n/2,
    ///2*(x-n/2)-1 when x > n/2}, (n == 0) % 2
        for (int j = 0; j < t; j++)
        {
            int x = tab[i][j];
            //cout << ((x <= n/2) ? 2*x : 2*(x-n/2)-1) << " ";
            tab[i+1][j] = ((x <= n/2) ? 2*x : 2*(x-n/2)-1);
            //tab[i+1][((j <= n/2) ? 2*j : 2*(j-n/2)-1) - 1] = tab[i][j-1];
        }//cout<<endl;
    }

    for (int i = 0; i < t; i++)
    {
        cout << tab[m[i]][i] << endl;
    }
}
