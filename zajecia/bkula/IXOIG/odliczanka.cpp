#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

// jeżeli N jest podzielne przez
// dowolny dzielnik pierwszy K
// odpowiedź brzmi NIE

// innymi słowy
// jeśli jakaś liczba pierwsza
// dzieli zarówno N i K
// odpowiedź brzmi NIE

// wynika z tego, że
// odpowiedź brzmi TAK
// tylko wtedy gdy
// liczby N i K
// są względnie pierwsze

bool pierwsza(int x)
{
    for (int i = 2; i <= sqrt(x); i++)
    {
        if ((x % i) == 0) return 0;
    }
    return 1;
}

bool f(int n, int k)
{
    int l = min(n,k);

    for (int i = 2; i <= l; i++)
    {
        if (pierwsza(i) &&
                ((n % (i)) == 0) &&
                ((k % (i)) == 0))
        {
                cout<<i<<" ";
                return 0;
        }
    }

    return 1;
}

int main()
{
    int n, k;
    cin >> n >> k;
    cout << (f(n, k) ? "TAK" : "NIE") << endl;
}
