/*
 * Rozwiązanie zadania "Pole" z laboratorium OIG
 */

#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int n;
    cin >> n;
    
    long double x[n+1], y[n+1];
    
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    x[n] = x[0]; y[n] = y[0];
    
    long double pole = 0;
    
    for (int i = 1; i <= n; i++) {
        pole += (x[i] - x[i-1]) * ((y[i] + y[i-1])/2.0);
    }
    
    cout << fixed << setprecision(2) << (pole < 0 ? -pole : pole) << endl;
    
    return 0;
}
