#include <iostream>
#include <string>
using namespace std;

int main () {

    string txt, wyn = "0";
    cin >> txt;

    int l[250];

    for (int i = 0; i < 250; i++) {
        l[i] = 0;
    }

    char z[250];

    l[0]++; z[0] = txt[0];

    int j = 0;

    for (int i = 1; i < txt.length(); i++) {
        if (txt[i] == txt[i-1]) l[j]++;
        else
        {
            j++;
            z[j] = txt[i];
            l[j]++;
        }
    }

    for (int i = 0; i < j+1; i++) {
        cout << l[i] << z[i];
    }

    return 0;
}
