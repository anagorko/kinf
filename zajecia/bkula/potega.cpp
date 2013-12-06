#include <iostream>
using namespace std;

int potega(int n, int m) {
    if (m == 1) return n;
    return n*potega(n,m-1);
}

int main () {

    int n, m;
    cin >> n >> m;

    cout << potega(n,m);

    return 0;
}
