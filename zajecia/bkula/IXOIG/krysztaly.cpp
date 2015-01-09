#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    string tab[n];
    for (int i = 0; i < n; i++)
    {
        cin >> tab[i];
    }

    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < m-1; j++)
        {
            int wyn = 0;
            bool stop = 0;
            while (1)
            {
                char ch = NULL;

                #define GRID(x,y) \
                for (int k = 0; k < wyn + 1; k++) {\
                if (stop) break; \
                if (x < 0 || x >= n || y < 0 || y >= m) {stop = true; break;} \
                if (ch == NULL) ch = tab[x][y]; \
                else if (ch != tab[x][y]) stop = true; }

                GRID(i-wyn+k,j-k); // lewa gora
                GRID(i+1+wyn-k,j+1+k); // prawy dol
                GRID(i+1+wyn-k,j-k); // lewy dol
                GRID(i-wyn+k,j+1+k); // prawa gora

                if (stop) break;
                wyn++;
            }
            cout << wyn << " ";
        }
        cout << endl;
    }
}
