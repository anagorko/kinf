#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;


int main()
{
    int n;
    cin >> n;
    int l[n];
    int naj = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> l[i];
        naj = max(naj, l[i]);
    }

    int sito_s = sqrt(naj) + 5;
    bool sito[sito_s];
    for (int i = 0; i < sito_s; i++) sito[i] = 1;
    for (int i = 2; i < sito_s; i++)
    {
        if (sito[i])
        {
            for (int j = 2 * i; j < sito_s; j += i)
            {
                sito[j] = 0;
            }
        }
    }

    vector<int> p;
    for (int i = 2; i < sito_s; i++)
    {
        if (sito[i]) p.push_back(i);
    }

    for (int i = 0; i < n; i++)
    {
        cout << l[i] << " = ";
        bool first = 1;
        for (int j = 0; j < p.size(); j++)
        {
            int x = 0;
            while (1)
            {
                if ((l[i] % p[j]) == 0) l[i] /= p[j];
                else break;
                x++;
            }
            if (x > 0) {
                if (first) first = 0;
                else cout << "*";
                cout << p[j];
            }
            if (x > 1) cout << "^" << x;

            if (l[i] == 1) break;
        }
        if (l[i] != 1) {
            if (first) first = 0;
            else cout << "*";
            cout << l[i];
        }
        cout << endl;
    }
}
