
#include <iostream>
#include <math.h>

using namespace std;

int main() {

    int n, w, h;

    cin >> n >> w >> h;

    int z[n];

    float x = sqrt(w*w+h*h);

    for (int i = 0; i < n; i++) {
        cin >> z[i];
    }
    for (int i = 0; i < n; i++) {
        if (z[i] > x) cout << "NIE" << endl;
        else cout << "TAK" << endl;
    }

    return 0;
}

