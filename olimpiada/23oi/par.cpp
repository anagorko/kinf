#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    
    int d[n][n]; // d - "d"ane; 0 - alejka, 1 = basenik;  d[nr wiersza][nr kolumny]
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            
            cin >> c;
            
            if (c == 'A') {
                d[i][j] = 0;
            } else if (c == 'B') {
                d[i][j] = 1;
            } else {
                cout << "Nie rozumiem znaku " << c << endl;
            }
        }
    }
    
    int b[n][n]; // numery basenów
    int nr = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] == 0) {
                b[i][j] = -1;
                continue;
            }
            
            int numer_obok = -1;
            
            if (i > 0 && d[i-1][j] == 1) {
                numer_obok = b[i-1][j];
            }
            if (j > 0 && d[i][j-1] == 1) {
                numer_obok = b[i][j-1];
            }
            
            if (numer_obok == -1) {
                b[i][j] = nr;
                nr++;
            } else {
                b[i][j] = numer_obok;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] == -1) {
                    cout << " ";
            } else {
                cout << b[i][j];
            }
        }
        cout << endl;
    }
    
    cout << "Liczba basenow: " << nr << endl;
}

