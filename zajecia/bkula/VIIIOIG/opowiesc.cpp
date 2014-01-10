#include <iostream>
#include <string>
using namespace std;

int main() {

    int n;
    cin >> n;

    int a[26];

    for (int i = 0; i < 26; i++) {
        a[i] = 0;
    }


    string t;
    cin >> t;

    int wyn = 0;

    for (int i = 0; i < n; i++) {
        if (t[i] > 96) {
            if (a[t[i]-97] == 0) {
                a[t[i]-97] = 1;
            } else if (a[t[i]-97] == 2) {
                a[t[i]-97] = 3;
                wyn++;
            } else if (a[t[i]-97] == 3) {
                wyn++;
            }
        } else {
            if (a[t[i]-65] == 0) {
                a[t[i]-65] = 2;
            } else if (a[t[i]-65] == 1) {
                a[t[i]-65] = 3;
                wyn++;
            } else if (a[t[i]-65] == 3) {
                wyn++;
            }
        }
    }

    cout << wyn;

    return 0;
}
