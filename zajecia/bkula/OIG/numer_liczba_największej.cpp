
#include <iostream>

using namespace std;

int main() {

    int naj = 0, wyn;

    for (int i = 0; i < 10; i++) {
        int a;
        cin >> a;
        if (naj < a) {
            naj = a;
            wyn = i + 1;
        }
    }

    cout << wyn;

    return 0;
}
