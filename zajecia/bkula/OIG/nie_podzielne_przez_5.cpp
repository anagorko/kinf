
#include <iostream>

using namespace std;

int main() {


    int n;
    cin >> n;
    int tab[n];

    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    for (int i = 0; i < n; i++) {
        if ((tab[i] % 5) != 0) cout << tab[i] << " ";
    }

    return 0;
}

