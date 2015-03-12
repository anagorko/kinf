#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef long long LL;

int main()
{
    int n, m;
    cin >> n >> m;

    int last[m]; // ostatnie wystąpienie smakołyka
    for (int i = 0; i < m; i++) last[i] = -1;

    int granica = 0; // przed tym elementem już nie sprawdzamy
    LL wyn = 0;

    for (int i = 0; i < n; i++)
    {
        int c;
        cin >> c;
        c--;

        if (granica <= last[c]) {
            granica = last[c] + 1;
        }
        last[c] = i;

        wyn += (i+1) - granica;
    }
    cout << wyn << endl;
}

/*
typedef long long LL;

LL suma_do(LL x)
{
    return (x*(x+1L))/2L;
}

int main()
{
    int n, m;
    cin >> n >> m;

    int last[m]; // ostatnie wystąpienie
    for (int i = 0; i < m; i++) last[i] = -1;

    vector<pair<int,int> > v;

    int plecy = 0;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        c--;
        if (last[c] >= plecy) {
            pair<int,int> p;
            p.first = plecy;
            p.second = last[c] + 1;
            v.push_back(p);
            plecy = last[c] + 1;
        }
        last[c] = i;
    }
    v.push_back(pair<int,int>(plecy, n));

    bool czy_poczatek[n+1];
    bool czy_koniec[n+1];
    for (int i = 0; i < n+1; i++) {
        czy_poczatek[i] = 0;
        czy_koniec[i] = 0;
    }

    for (int i = 0; i < v.size(); i++) {
        cout << v[i].first << " " << v[i].second << endl;
        czy_poczatek[v[i].first] = 1;
        czy_koniec[v[i].second] = 1;
    }

    LL wyn = 0;

    int przod = -1;
    list<int> tyl;
    for (int i = 0; i < n+1; i++) {
        if (czy_poczatek[i]) {
            tyl.push_back(i);
        }
        if (czy_koniec[i]) {
            if (tyl.front() < przod) {
                int arg = i - tyl.front();
                if (i != 0) arg += 1;
                if (i != n) arg += 1;
                wyn += suma_do(arg);
            } else {
                wyn += suma_do()
            }
            tyl.pop_front();
        }
    }
}

int n;

long long kombinacje(int from, int to)
{
    long long x = to - from;
    int boki = 0;
    if (from != 0) boki++;
    if (to != n) boki++;
    if (boki > 0) x++;
    cout<<"k"<<from<<","<<to<<"="<<((x * (x+1L)) / 2L - x) * (boki > 1 ? 2L : 1L)<<endl;
    return ((x * (x+1L)) / 2L - x) * (boki > 1 ? 2L : 1L);
}

int main()
{
    int m;
    cin >> n >> m;
    long long wyn = n;
    int last[m]; //// ostatnie wystąpienie
    int plecy = 0; //// tyłek gąsiennicy
    int przed = -1;
    for (int i = 0; i < m; i++) last[i] = -1;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        c--;
        if (last[c] >= plecy) {
            cout<<i<<"->";
            wyn += kombinacje(plecy, last[c] + 1);
            plecy = last[c] + 1;
        }
        last[c] = i;
    }
    cout << wyn + kombinacje(plecy, n) << endl;
}
*/
