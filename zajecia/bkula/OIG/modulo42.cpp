#include <iostream>

using namespace std;

int main() {

    int l[10], wyn = 0;

    for (int i = 0; i < 10; i++) {
        cin >> l[i];
        l[i] = l[i] % 42;
    }

    for (int i = 0; i < 42; i++) {
        for (int j = 0; j < 10; j++) {
            if (l[j] == i) {
                wyn++;
                break;
            }
        }
    }

    cout << wyn;

    return 0;
}
