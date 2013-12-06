#include <iostream>
#include <string>
using namespace std;

int main() {

    string l, w;
    cin >> l;

    int s = 0, p[l.length()];

    for (int i = 0; i < l.length()-1; i++) {
        p[i] = (int) l[i] - 48;
    }

    int j = 7;

    for (int i = 1; i < l.length(); i++) {
        s += p[l.length()-i-1]*j;
        j *= 7;
    }

    s += (int) l[l.length()-1] - 48;

    int naj = 0;

    for (int i = 1; ; i*=3) {
        if (i > s) {
            naj = i/3;
            break;
        }
    }

    for (int i = naj; i > 0; i /= 3) {
        if (i*2 <= s) {
            cout << "2";
            s -= i*2;
        } else if (i <= s) {
            cout << "1";
            s -= i;
        } else {
            cout << "0";
        }
    }

    return 0;
}
