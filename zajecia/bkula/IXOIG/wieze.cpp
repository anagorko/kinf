#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string in[2];
int n, m;
int zle[2], granica[2];

bool w(int x, int y)
{
    return in[x][y] == 'B';
}

void f()
{
    #define FOR(x)\
    granica[x] = x == 0 ? n : m; \
    zle[x] = 0; \
    for (int i = 0; i < (x == 0 ? n : m); i++) {\
        if (x == 0 ? ! w(x,i) : w(x,i)) { \
            if (granica[x] == (x == 0 ? n : m)) { \
                granica[x] = i; \
                zle[x] = 1; \
            } else { \
                zle[x]++; \
            }\
        } \
    };

    FOR(0);
    FOR(1);

    cout << 2 * (n - granica[0]) + 2 * (m - granica[1]) - max(zle[0],zle[1]) << " ";
}

int main()
{
    ios_base::sync_with_stdio(0);

    cin >> n >> m;
    cin >> in[0] >> in[1];

    f();
    swap(in[0], in[1]);
    swap(n, m);
    f();
}
