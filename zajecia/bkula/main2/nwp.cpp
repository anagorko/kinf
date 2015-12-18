#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int max3 (int a, int b, int c)
{
    return max(a, max(b,c));
}

string a, b;
int** tab;

int nwp(int i, int j)
{
    if (i < 0 || j < 0) return 0;

    if (tab[i][j] != -1) return tab[i][j];

    tab[i][j] =  max3(
        nwp(i-1, j),
        nwp(i, j-1),
        a[i] == b[j] ? nwp(i-1, j-1) + 1 : 0
    );

    return tab[i][j];
}

int main()
{
    cin >> a >> b;

    tab = new int*[a.size()];
    for (int i = 0; i < a.size(); i++) {
        tab[i] = new int[b.size()];
        for (int j = 0; j < b.size(); j++) {
            tab[i][j] = -1;
        }
    }

    cout << nwp(a.size()-1, b.size()-1) << endl;

    for (int i = 0; i < a.size(); i++) {
        delete[] tab[i];
    }
    delete[] tab;
}
