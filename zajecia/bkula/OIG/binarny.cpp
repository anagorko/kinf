#include <iostream>

using namespace std;

int main() {

    int d, w;
    cin >> d;

    for (int i = 1; i <= d; i *= 2)
        w = i;

    for (int i = w; i != 0; i /= 2) {
        if (i <= d) {
            cout << "1";
            d -= i;
        } else
            cout << "0";
    }

    return 0;
}
