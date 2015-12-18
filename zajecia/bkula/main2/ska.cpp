/*
Mają złą sprawdzarkę na mainie!

przykład:

fragment wejścia:
2 30
17 50
16 40

komunikat: wiersz 5: wczytano '50', a oczekiwano '40'
*/


#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n, p;
        cin >> n >> p;
        if (i == 3) cout << n << " " << p << endl;

        int a[p+1];
        for (int j = 0; j < p+1; j++) a[j] = 0;

        for (int j = 0; j < n; j++)
        {
            int s, v;
            cin >> s >> v;
            if (i == 3) cout << s << " " << v << endl;

            for (int k = 0; k < p+1; k++) {
                if (s <= k) {
                    a[k] = max(a[k], a[k-s] + v);
                }
            }
        }

        cout << a[p] << "\n";
    }
}
