#include <iostream>

using namespace std;

int main() {

    int a, w = 0;
    cin >> a;
    for (int i = 10; i < a; i *= 10) w++;
    cout << w + 1;
}

