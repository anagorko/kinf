#include <iostream>
using namespace std;

const int limit = 10000;

int potega(int a, int b)
{
    if (b == 0) return 1;

    if ((b % 2) == 0) {

        int p = potega(a, b/2);
        p %= limit;
        p *= p;
        p %= limit;
        return p;

    } else {

        int p = potega(a, b-1);
        p %= limit;
        p *= a % limit;
        p %= limit;
        return p;
    }
}

int main()
{
    int p;
    cin >> p;
    for (int i = 0; i < p; i++) {
        int a, b;
        cin >> a >> b;
        cout << potega(a+1, b) << "\n";
    }
}
