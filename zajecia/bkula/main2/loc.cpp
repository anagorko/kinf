#include <iostream>
#include <queue>
using namespace std;

struct P
{
    int x, y;
    int d;
    P(int _x, int _y, int _d)
    : x(_x), y(_y), d(_d)
    {
    }
};

void f()
{
    int n, m;
    cin >> n >> m;
    char tab[n][m];
    int bx, by;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> tab[i][j];
            if (tab[i][j] == '@') {
                bx = i, by = j;
            }
        }
    }

    queue<P> q;
    q.push(P(bx, by, 0));
    tab[bx][by] = '#';

    while (! q.empty())
    {
        P p = q.front();
        q.pop();

        #define GO(x, y) \
        if (x >= 0 && x < n && y >= 0 && y < m && tab[x][y] != '#') { \
            if (tab[x][y] == '>') { \
                cout << p.d + 1 << "\n"; \
                return; \
            } \
            q.push(P(x, y, p.d + 1)); \
            tab[x][y] = '#'; \
        }

        GO(p.x + 1, p.y);
        GO(p.x, p.y + 1);
        GO(p.x - 1, p.y);
        GO(p.x, p.y - 1);
    }

    cout << "NIE\n";
}

int main()
{
    int z;
    cin >> z;

    while (z-- > 0)
    {
        f();
    }
}
