/*
 * Rozwiązanie zadania "Imieninowy zbiór" z laboratorium OIG (gr. średniozaawansowana)
 */

#include<iostream>
using namespace std;

int n;
int l[18];

int dfs(int mask, int cnt, int dep)
{
    if (dep >= n) {
        return cnt;
    }
    
    int t1, t2;
    
    if ((mask & l[dep]) == 0) {
        t1 = dfs(mask | l[dep], cnt + 1, dep + 1);
    } else {
        t1 = 0;
    }
    t2 = dfs(mask, cnt, dep + 1);
    
    return (t1 > t2) ? t1 : t2;
}

int main()
{
    int p[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };

    cin >> n;
    
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        
        l[i] = 0;
        int m = 1;
        for (int j = 0; j < sizeof(p)/sizeof(int); j++) {
            if (x % p[j] == 0) {
                l[i] |= m;
            }
            m *= 2;
        }
    }
    
    cout << dfs(0, 0, 0) << endl;
        
    return 0;
}
