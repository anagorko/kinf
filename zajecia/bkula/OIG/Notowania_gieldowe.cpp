#include <iostream>
#include <sstream>

using namespace std;

int main() {

    int X[30000], naj = 0,  n;

    for (int i = 0; ; i++) {
        string t;
        cin >> t;
        if (cin.eof()) {
            n = i;
            break;
        }
        stringstream ss;
        ss << t;
        ss >> X[i];
    }

    for (int k = 0; k < n + 1; k++) {
        for (int j = 0; j < n + 1; j++) {
            int s = 0;
            for (int i = k; i < j; i++) {
                s += X[i];
            }
            if (s > naj) {
                naj = s;
            }
        }
    }

    cout << naj;

    return 0;
}
