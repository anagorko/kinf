#include <iostream>

using namespace std;

int main() {

    int G, M, S;
    cin >> G >> M >> S;

    cout << S + M*60 + G*60*60;

    return 0;
}
