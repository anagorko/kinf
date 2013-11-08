/*
 * Rozwiązanie zadania Hasło z 2 treningu Zawodów Drużynowych VIII OIG
 */

#include<iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    
    int w[n][n];
    int maks = 0;
    int maks_dl = 0;
    
    for (int i = 0; i < n; i++) {
        w[i][i] = 0;
        
        for (int j = i+1; j < n; j++) {
            w[i][j] = w[i][j-1] + abs(s[j] - s[j-1]);
            if (w[i][j] >= maks && w[i][j] <= m && maks_dl <= j - i + 1) {
                maks = w[i][j];
                maks_dl = j - i + 1;
            }
        }
    }
    
    cout << maks_dl << endl;
    
    return 0;
}
