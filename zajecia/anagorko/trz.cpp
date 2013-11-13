/*
 * Rozwiązanie zadania "Podzielne przez trzy" z laboratorium OIG (gr. średniozaawansowana)
 */

#include<iostream>
using namespace std;

string l;
long long int ile[1000001][3];

int main()
{
    int n;
    cin >> n;
    cin >> l;    
    
    ile[0][0] = 0;
    ile[0][1] = 0;
    ile[0][2] = 0;
    
    int p = 1;
    
    for (int i = 1; i <= n; i++) {
        if (l[n - i] == '0') {
            ile[i][0] = ile[i-1][0] + 1;
            ile[i][1] = ile[i-1][1];
            ile[i][2] = ile[i-1][2];
        } else {
            if (p == 1) {
                ile[i][0] = ile[i-1][2];
                ile[i][1] = ile[i-1][0] + 1;
                ile[i][2] = ile[i-1][1];
            } else {
                ile[i][0] = ile[i-1][1];
                ile[i][1] = ile[i-1][2];
                ile[i][2] = ile[i-1][0] + 1;
            }
        }

        p = 3 - p;
    }
    
    long long int s = 0;
    for (int i = 1; i <= n; i++) {
        s += ile[i][0];
    }
    
    cout << s << endl;
    
    return 0;
}
