#include <iostream>

using namespace std;


int main() {

    int n, k, m1 = 0, m2 = 0, m3 = 0;
    cin >> n >> k;

    int t[n];
        for (int i = 0; i < n; i++) t[i] = 0;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            int l;
            cin >> l;
            t[j] += l;
        }
    }

    for (int j = 0; j < n; j++) {
        if (t[j] > m1) {
            m3 = m2;
            m2 = m1;
            m1 = j;
        } else if (t[j] > m2) {
            m3 = m2;
            m2 = j;
        } else if (t[j] > m3) {
            m3 = j;
        }
    }

    cout << m1 + 1 << " " << m2 + 1 << " " << m3 + 1;

    return 0;
}
