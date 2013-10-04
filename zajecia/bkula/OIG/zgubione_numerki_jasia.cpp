#include <iostream>

using namespace std;

int main() {

    int P, K;
    cin >> P >> K;
    bool n[P];
        for (int i = 0; i < P; i++) n[i] = false;
    for (int i = 0; i < K; i++) {
        int pom;
        cin >> pom;
        n[pom-1] = true;
    }

    for (int i = 0; i < P; i++) {
        if (n[i] == false) cout << i+1 << endl;
    }

    return 0;
}
