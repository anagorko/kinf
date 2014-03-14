#include <iostream>
#include <algorithm>
using namespace std;

struct people
{
    int lp;
    int wys;
    int wyn;
};

bool kolejnosc (people a, people b)
{
    return a.lp < b.lp;
}

bool wysokosc (people a, people b)
{
    return a.wys < b.wys;
}

int main()
{
    int n, m;
    cin >> n >> m;

    int s[n];
    people p[m];

    for (int i = 0; i < n; i++) cin >> s[i];

    for (int i = 0; i < m; i++)
    {
        int in; cin >> in;
        p[i] = {i,in,-1};
    }

    sort (p, p + m, wysokosc);

    int stopien = 0;

    for (int i = 0; i < m; i++)
    {
        for (; stopien < n; stopien++)
        {
            if (s[stopien] >= p[i].wys)
            {
                p[i].wyn = stopien;
                break;
            }
        }
        if (p[i].wyn == -1) p[i].wyn = n;
    }

    sort (p, p + m, kolejnosc);

    for (int i = 0; i < m; i++) cout << p[i].wyn << " ";

    return 0;
}
