#include <iostream>
#include <queue>
#include <iomanip>
#include <sstream>
using namespace std;

class F
{
public:

    static const int MAX = 3000;

protected:

    long long tab[MAX];
    F * next;

public:

    int d;

    virtual void licz_tab(int n)
    {
        //cout << "f(" << d << "," << n << ")\n";

        long long wyn = 0;
        if (((n*10) % d) == 0) wyn++;

        for (int i = n*10; i > 0; i -= d) {
            wyn += next->get(i/10);
            //cout << "+" << next->get(i/10) << endl;
        }

        tab[n] = wyn;
    }

    long long get(int i)
    {
        if (tab[i] == -1) licz_tab(i);
        return tab[i];
    }

    F()
    {
        for (int i = 0; i < MAX; i++) {
            tab[i] = -1;
        }
    }

    F(int arg_d, F * arg_next)
    {
        d = arg_d;
        next = arg_next;
        for (int i = 0; i < MAX; i++) {
            tab[i] = -1;
        }
    }
};

class DYCHA: public F
{
public:

    void licz_tab(int n)
    {
        tab[n] = n+1;
        //cout<<"@"<<n<<"="<<tab[n]<<"\n";
    }
};

class wynik
{
public:
    double a;
    long long b;
    void wypisz()
    {
        stringstream ss;
        ss << fixed << setprecision(2) << a << " " << b;
        string t1,t2;
        ss >> t1 >> t2;

	for (int i = 5 - t1.size(); i >= 0; i--) {
            cout << " ";
        }

        cout << t1;

        for (int i = 16 - t2.size(); i >= 0; i--) {
            cout << " ";
        }

        cout << t2 << endl;
    }
};

int main()
{
    cin.sync_with_stdio();
    cout.sync_with_stdio();

    int monety[] = {10,20,50,100,200,500,1000,2000,5000,10000};

    int n = sizeof(monety) / sizeof(int);

    F * f[n];
    f[0] = new DYCHA;
    for (int i = 1; i < n; i++) {
        f[i] = new F(monety[i],f[i-1]);
    }

    queue <wynik> wyn;

    while(1) {
        double x;
        cin >> x;
        if (x == 0.00) break;
        wynik nowy;
        nowy.a = x;
        nowy.b = f[n-1]->get(x*10);
        wyn.push(nowy);
    }

    while(!wyn.empty()) {
        wyn.front().wypisz();
        wyn.pop();
    }
}
