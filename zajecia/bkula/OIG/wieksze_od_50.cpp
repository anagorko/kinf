#include <iostream>

using namespace std;

int main() {

    int wyn = 0;

    for (int i = 0; i < 10; i++) {
        int a;
        cin >> a;
        if (a > 50) wyn += a;
    }

    cout << wyn;

    return 0;
}
