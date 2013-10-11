#include <iostream>
using namespace std;

int main() {

    int min;
    cin >> min;
    for (int i = 0; i < 2; i++) {
        int a;
        cin >> a;
        if (a < min) min = a;
    }
    cout << min;

    return 0;
}
