#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// DZIAŁA TYLKO DLA A,B < 11 !!!

string f(string l, int a, int b);

int main() {

    string t;
    int a, b;
    cin >> a >> b >> t;
    cout << f(t,a,b);

    return 0;
}

string f(string l, int a, int b) {

    string w;

    int s = 0, p[l.length()];

    for (int i = 0; i < l.length()-1; i++) {
        p[i] = (int) l[i] - 48;
    }

    int j = a;

    for (int i = 1; i < l.length(); i++) {
        s += p[l.length()-i-1]*j;
        j *= a;
    }

    s += (int) l[l.length()-1] - 48;

    int naj = 0;

    for (int i = 1; ; i*=b) {
        if (i > s) {
            naj = i/b;
            break;
        }
    }

    stringstream ss;

    for (int i = naj; i > 0; i /= b) {
        for (int k = b; k > 0; k--) {
            if (i*(k-1) <= s) {
                ss << (k-1);
                s -= i*(k-1);
                break;
            }
        }
    }

    return ss.str();
}
