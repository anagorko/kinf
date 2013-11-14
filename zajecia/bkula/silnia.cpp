#include <iostream>
using namespace std;

int silnia(int n) {
    if (n == 0) return 1;
    return n*silnia(n-1);
}

int main () {

    int n;
    cin >> n;

    cout << silnia(n);

    return 0;
}
