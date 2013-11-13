/*
 * Rozwiązanie zadania Miliard z 2 treningu Zawodów Drużynowych VIII OIG
 */
 
#include<iostream>
using namespace std;

int n;
int p[50];

int ile(long long int x, int d)
{
    if (x > 1000000000) return 0;
    
    int wyn = 1;
    
    for (int i = d; i < n; i++) {
        wyn += ile(x * p[i], i);
    }

    return wyn;
}

int main()
{
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    cout << (ile(1, 0) - 1) << endl;
    
    return 0;
}
