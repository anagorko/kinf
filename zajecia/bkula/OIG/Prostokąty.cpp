#include <iostream>

using namespace std;

int main() {

    int n;
    cin >> n;

    struct punkt {
        int x;
        int y;
    };

    punkt p[n];

    cin >> p[0].x >> p[0].y;

    int l = p[0].x, r = p[0].x, u = p[0].y, d = p[0].y;

    for (int i = 1; i < n; i++) {
        cin >> p[i].x >> p[i].y;

        if (l > p[i].x) {
            l = p[i].x;
        }
        if (r < p[i].x) {
            r = p[i].x;
        }
        if (u > p[i].y) {
            u = p[i].y;
        }
        if (d < p[i].y) {
            d = p[i].y;
        }
    }

    int a = r-l, b = d-u;

    if (a == 0) a++;
    if (b == 0) b++;

    cout << a * b;

    return 0;
}
