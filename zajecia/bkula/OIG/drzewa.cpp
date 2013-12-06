#include <iostream>
using namespace std;

int max (int a1, int a2) {
    if (a1 > a2) return a1;
    return a2;
}

int main () {

    int a, b, c;
    cin >> a >> b >> c;

    int t1[a+b+c];

    for (int i = 0; i < a+b+c; i++) t1[i] = i+1;

    int t2[a+b+c];

    for (int i = 0; i < a; i++) {
        t2[i] = i+1;
    }
    for (int i = a; i < a+b; i++) {
        t2[i] = i+1-a;
    }
    for (int i = a+b; i < a+b+c; i++) {
        t2[i] = i+1-a-b;
    }

    for (int i = 0; i < a+b+c; i++) {
        while (t2[i] != 1) {
            for (int j = 0; j < a+b+c; j++) {
                if (t1[j]>=t2[i]&&(t1[j]%t2[i])==0) {
                    t1[j] /= t2[i];
                    t2[i] = 1;
                }
                for (int d = 2; d < max(t1[j],t2[i]); d++) {
                    if ((t1[j]%d)==0&&(t2[i]%d)==0) {
                        t1[j] /= d;
                        t2[i] /= d;
                        if (t2[i]==1)break;
                    }
                }
                if (t2[i]==1)break;
            }
        }
    }

    const int m = 1000000007;

    long long wyn = t1[0]%m;

    for (int i = 1; i < a+b+c; i++) {
        wyn *= t1[i]%m;
    }

    cout << wyn;

    return 0;
}
