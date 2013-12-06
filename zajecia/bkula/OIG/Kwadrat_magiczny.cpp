#include <iostream>
using namespace std;

void f (int &a, int n) {

    if (a < n) a = n;
}

int main () {

int wyn = 0;

int k[3][3];

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        cin >> k[i][j];
    }
}

for (int i = 0; i < 3; i++) {
    f(wyn,k[0][i]+k[1][i]+k[2][i]);
    f(wyn,k[i][0]+k[i][1]+k[i][2]);
}

f(wyn,k[0][0]+k[1][1]+k[2][2]);
f(wyn,k[0][2]+k[1][1]+k[2][0]);


for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (k[i][j] == 0) {
            cout << wyn-(k[i][0]+k[i][1]+k[i][2]);
        } else {
            cout << k[i][j];
        }
        cout << " ";
    }
    cout << endl;
}

}

