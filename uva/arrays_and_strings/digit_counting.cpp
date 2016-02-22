#include <iostream>
#include <string>
using namespace std;

int main()
{
    int t;    
    cin >> t;

    int d[10];
    
    for (int i = 0; i < t; i++) {
        for (int i = 0; i < 10; i++) {
            d[i] = 0;
        }

        int n; cin >> n;
        
        for (int j = 1; j <= n; j++) {
            int k = j;
            while (k != 0) {
                d[k % 10]++;
                k = k / 10;
            }
        }
        for (int i = 0; i < 10; i++) {
            cout << d[i] << (i < 9 ? " " : "");
        }
        cout << endl;
    }    
}

