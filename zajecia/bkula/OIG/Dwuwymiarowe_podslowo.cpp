#include <iostream>
using namespace std;

short n, m, k;
char s[101], p[101][101];
long long wyn = 0;

void f (short a, short b, int c) {

    for (int i = a; i < n; i++) {
        for (int j = b; j < m; j++) {
            if (p[i][j] == s[c]) {
                if (k == c + 1) {
                    wyn++;
                } else {
                    f(i,j,c+1);
                }
            }
        }
    }

    return;
}

int main() {

    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) cin >> s[i];

    for (short i = 0; i < n; i++)
        for (short j = 0; j < m; j++)
            cin >> p[i][j];

    short i[k], j[k];

    f(0,0,0);

    cout << wyn % (1000000000 + 33);

    return 0;
}

