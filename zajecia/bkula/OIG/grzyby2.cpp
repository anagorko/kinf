#include <iostream>
using namespace std;

int main() {

    int wyn = 0;
    for (int i = 0; i < 5; i++) {
        int a;
        cin >> a;
        wyn += a;
    }
    cout << wyn/3;

    return 0;
}

