#include <iostream>

using namespace std;

int main() {

    int wyn = 0;

    for (int i = 0; ; i++) {
        int n;
        cin >> n;
        if (n == 0) break;
        else if ((i % 2) == 0) wyn += n;
    }

    cout << wyn;

    return 0;
}
