#include <iostream>
using namespace std;

int main() {

    int a, b, wyn = 0;

    cin >> a >> b;

    for (int i = 0; i < a*b; i++) {
        int n;
        cin >> n;
        wyn += n;
    }

    cout << wyn;

    return 0;
}

