/**

Czemu to nie przeszło? :(

Test	Wynik	Czas	Wynik
1	Błąd wykonania	0.00s/1.00s	0/16
2	Błąd wykonania	0.00s/1.00s	0/16
3	Błąd wykonania	0.00s/1.00s	0/17
4	Błąd wykonania	0.20s/6.00s	0/17
5	Zła odpowiedź	3.73s/15.00s	0/17
6	Zła odpowiedź	0.89s/4.00s	0/17

1 process exited due to signal 11
2 process exited due to signal 11
3 process exited due to signal 11
4 process exited due to signal 11
5 wiersz 293204: wczytano '4', a oczekiwano '5'
6 wiersz 200003: wczytano '11', a oczekiwano '10532'

Debugowałem chyba ze 2h, poddaję się :D

Dla tego testu moj komputer zwraca dobry wynik,
a serwer main2 jakiś "signal 11".
Mają inny kompilator czy co? O.o

4

5 10
1 5
2 5
3 5
4 5
1 4
2 4
3 4
1 3
2 3
1 2
2

5 0
3

6 6
1 2
2 3
3 4
4 5
5 6
6 1
5

5 4
1 2
2 3
3 4
4 5
1

*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct V
{
    vector<int> e;
    int dist;
};
vector<V> v;

void bfs(int first)
{
    queue<int> q;
    v[first].dist = 0;
    q.push(first);

    while (! q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < v[x].e.size(); i++) {
            if (v[v[x].e[i]].dist == -1) {
                v[v[x].e[i]].dist = v[x].dist + 1;
                q.push(v[x].e[i]);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);

    int t;
    cin >> t;

    while (t-- > 0)
    {
        int n, m;
        cin >> n >> m;

        v.clear();
        v.reserve(n);
        for (int i = 0; i < n; i++) {
            v[i].dist = -1;
        }

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--, b--;

            v[a].e.push_back(b);
            v[b].e.push_back(a);
        }

        int me;
        cin >> me;
        me--;

        bfs(me);

        queue<int> to_bfs;

        cout << "Znajomi numeru " << me+1 << ":\n";
        for (int i = 0; i < n; i++) {
            if (v[i].dist == -1) to_bfs.push(i);
            else if (v[i].dist != 0) cout << i+1 << ": " << v[i].dist << "\n";
        }

        int groups = 1;

        while (! to_bfs.empty()) {
            int x = to_bfs.front();
            to_bfs.pop();
            if (v[x].dist == -1) {
                groups++;
                bfs(x);
            }
        }

        cout << "Grup znajomych jest " << groups << ".\n";
    }
}
