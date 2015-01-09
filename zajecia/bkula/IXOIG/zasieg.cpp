
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

struct V
{
    float d;
    int p;
};

const int NIESK = 1000000007;

int sufit(float a, float b)
{
    if (a/b == float(int(a/b))) return a/b;
    if (a/b < 0) return int(a/b) - 1;
    return int(a/b) + 1;
}

float przekatna(int* a, int* b)
{
    return sqrt(
        pow(abs(a[0] - b[0]), 2.0) +
        pow(abs(a[1] - b[1]), 2.0)
    );
}

int main()
{
    int n;
    float z;
    cin >> z;
    z *= 2;
    int buf[4];
    for (int i = 0; i < 4; i++)
    {
        cin >> buf[i];
    }
    cin >> n;
    n += 2;
    int wieza[n][2];
    wieza[0][0] = buf[0];
    wieza[0][1] = buf[1];
    wieza[n-1][0] = buf[2];
    wieza[n-1][1] = buf[3];
    for (int i = 0; i < n - 2; i++)
    {
        cin >> wieza[i+1][0] >> wieza[i+1][1];
    }

    float edge[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            edge[i][j] = std::max(0, sufit(przekatna(wieza[i], wieza[j])-z, z));
        }
    }

    V vertex[n];
    vertex[0].d = 0;
    for (int i = 1; i < n; i++) vertex[i].d = NIESK;
    typedef pair<int,int> ii;
    priority_queue<ii, vector<ii>, greater<ii> > q;
    q.push(ii(0,0));
    while (! q.empty())
    {
        ii top = q.top();
        q.pop();
        int v = top.second, d = top.first;
        if(d <= vertex[v].d)
        {
              for (int i = 0; i < n; i++)
              {
                    if (i != v)
                    {
                        float waga = edge[v][i];
                        if(vertex[i].d > vertex[v].d + waga)
                        {
                              vertex[i].d = vertex[v].d + waga;
                              vertex[i].p = v;
                              q.push(ii(vertex[i].d, i));
                        }
                    }
              }
        }
    }

    cout << vertex[n-1].d;
}
