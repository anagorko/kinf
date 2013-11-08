/*
 * Rozwiązanie zadania "Pole" z laboratorium OIG
 */

#include<iostream>
using namespace std;

void rozwiaz(int n)
{
    if (n == 0) { cout << "0"; return; }
    
    int cyfry[10];
    for (int i = 0; i < 10; i++) { cyfry[i] = 0; }
    
    int dziel[] = { 2, 3, 5, 7 };
    int m = n;
    for (int i = 0; i < sizeof(dziel) / sizeof(int); i++) {
        while (m % dziel[i] == 0) {
            cyfry[dziel[i]]++; m /= dziel[i];
        }
    }
    
    if (m > 1) { cout << "0" << endl; return; }
    
    while (cyfry[2] >= 3) {
        cyfry[2] -= 3;
        cyfry[8]++;
    }
    if (cyfry[2] == 2) {
        cyfry[2] = 0;
        cyfry[4] = 1;
    }
    
    while (cyfry[3] >= 2) {
        cyfry[3] -= 2;
        cyfry[9]++;
    }
    
    int ilec = 0;
    for (int i = 0; i < 10; i++) {
        ilec += cyfry[i];
    }
    if (ilec == 1) {
        cout << "1";
    }
    
    for (int i = 0; i < 10; i++) {
        while (cyfry[i] > 0) {
            cout << i;
            cyfry[i]--;
        }
    }
    cout << endl;
}

int main()
{
    int d;
    cin >> d;
    
    for (int i = 0; i < d; i++) {
        int n;
        cin >> n;
        
        rozwiaz(n);
    }
    
    return 0;
}
