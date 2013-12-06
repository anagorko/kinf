/*
 * Rozwiązanie zadania "Tabliczka mnożenia" z laboratorium OIG
 */

#include<iostream>
using namespace std;

void wypisz_4(int n)
{
    int c = 1, m = n;
    while (m >= 10) {
        m = m / 10; c++;
    }
    for (int i = 0; i < 4 - c; i++) {
        cout << " ";
    }
    cout << n;
}

int main()
{
    int k;
    cin >> k;
    
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            wypisz_4(i*j);
        }
        cout << endl;
    }
    
    return 0;
}
