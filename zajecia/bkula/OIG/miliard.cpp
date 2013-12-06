#include <iostream>
using namespace std;
int main () {

    short n;
    cin >> n;

    int d[n];
    for (short i = 0; i < n; i++) {
        cin >> d[i];
    }

    int j, pom;
    for (short i = 1; i < n; i++) {
        j = 0;
        while (d[j] < d[i])
            j++;
        pom = d[i];
        for(int k = i-1; k >= j; k--)
            d[k+1] = d[k];
        d[j] = pom;
    }

    int wyn = 0;

    for (int i = 2; i < 1000000000; i++) {

        cout << i << " ";

        int m = i;

        bool wyjdz = false;
        while (m != 1 && wyjdz != true) {
            for (int k = 0; ; k++) {
                if ((m % d[k]) == 0) {
                    m /= d[k];
                    break;
                }
                else if (k == n-1) {
                    wyjdz = true;
                    break;
                }
            }
        }

        if (wyjdz != true) {
            wyn++;
        }
    }

    cout << endl << wyn;

    return 0;
}
