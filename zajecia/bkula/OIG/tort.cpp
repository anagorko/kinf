#include <iostream>
using namespace std;

int mniejsza(int a, int b) {
    if (a < b) return a;
    else return b;
}

int main() {

    int n;

    cin >> n;

    int a[n], b[n], max = 1, s = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        max *= b[i];
    }

    for (int i = 0; i < n; i++) {
        s += a[i] * max/b[i];
    }

    if (s > max) {
        int w = 0;
        for (int i = max; i < s; i += max) {
            w++;
        }
        s -= w * max;
    }

    if (s == max) {
        cout << "1";
    } else {
        s = max - s;
        for (int j = mniejsza(s, max); j > 2; j--) {
            if ((s % j) == 0 && (max % j) == 0) {
                s /= j;
                max /= j;
                break;
            }
        }
        cout << s << "/" << max;
    }

    return 0;
}

