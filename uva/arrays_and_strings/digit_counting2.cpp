#include <iostream>
#include <string>
using namespace std;

void count_digits(int l, int d[])
{
    while (l != 0) {
        d[l % 10]++;
        l = l / 10;
    }
}

void single_test(int n)
{
    int d[10];

    for (int i = 0; i < 10; i++) {
        d[i] = 0;
    }

    for (int j = 1; j <= n; j++) {
        count_digits(j, d);
    }
    
    for (int i = 0; i < 10; i++) {
        cout << d[i] << (i < 9 ? " " : "");
    }
    cout << endl;

}

int main()
{
    int t;    
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        int n; cin >> n;
        
        single_test(n);
    }    
}

