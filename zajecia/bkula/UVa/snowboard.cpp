#include <iostream>
using namespace std;

struct WYN
{
    string name;
    long long naj;
    void print()
    {
        cout << name << ": " << naj << endl;
    }
};

int n, m;
int h[101][101];
int naj[101][101];

long long run(int x, int y)
{
    if (naj[x][y] != -1) return naj[x][y];

    long long result = 1;

    if (x != n && h[x][y] > h[x+1][y]) {
        int pom = run(x+1,y) + 1;
        if (pom > result) result = pom;
    }
    if (y != m && h[x][y] > h[x][y+1]) {
        int pom = run(x,y+1) + 1;
        if (pom > result) result = pom;
    }
    if (x != 0 && h[x][y] > h[x-1][y]) {
        int pom = run(x-1,y) + 1;
        if (pom > result) result = pom;
    }
    if (y != 0 && h[x][y] > h[x][y-1]) {
        int pom = run(x,y-1) + 1;
        if (pom > result) result = pom;
    }

    return result;
}

WYN test()
{
    WYN wyn;
    cin >> wyn.name;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> h[i][j];
            naj[i][j] = -1;
        }
    }
    wyn.naj = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            naj[i][j] = run(i,j);
            if (naj[i][j] > wyn.naj) {
                wyn.naj = naj[i][j];
            }
        }
    }
    return wyn;
}

int main()
{
    cin.sync_with_stdio(0);
    cin.sync_with_stdio(0);

    int T;
    cin >> T;

    WYN wyn[T];

    for (int i = 0; i < T; i++) wyn[i] = test();

    for (int i = 0; i < T; i++) wyn[i].print();
}
