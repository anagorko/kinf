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

typedef long long LL;

LL NWD(LL a, LL b)
{
    return (b == 0) ? a : NWD(b, a % b);
}

int main()
{
    LL n, k;
    cin >> n >> k;
    if (NWD(n, k) == 1)
    {
        cout << "TAK" << " ";
        cout << ((k <= (n-1) / 2) ? "P" : "L") << endl;
    }
    else
    {
        cout << "NIE" << endl;
    }
}
