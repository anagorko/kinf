#include <iostream>
using namespace std;

int main () {

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w = (i+1)*(j+1);
            if (w < 100) cout << " ";
            if (w < 10) cout << " ";
            cout << " " << w;
        }
        cout << endl;
    }

    return 0;
}
