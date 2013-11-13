/*
 * Rozwiązanie zadania "Nawiasowanie" z laboratorium OIG (gr. średniozaawansowana)
 */
 
#include<iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--) {
        int l;
        cin >> l;
        string s;
        cin >> s;
        
        int z = 0, o = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                z++;
            } else {
                z--;
                if (z < 0) {
                    o++;
                    z += 2;
                }
            }
        }
        
        if (z % 2 == 1) {
            cout << "NIEMOZLIWE\n";
        } else {
            cout << (o + z / 2) << "\n";
        }
    }
    
    return 0;
}
