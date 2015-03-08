#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct U
{
    string name;
    int l;

    U(string _name = "", int _l = 0)
    : name(_name)
    , l(_l)
    {
    }

    friend bool operator<(const U& a, const U& b)
    {
        return a.l < b.l;
    }
};

int main()
{
    int n, s;
    cin >> n >> s;
    vector<U> u(n);
    for (int i = 0; i < n; i++) cin >> u[i].name >> u[i].l;

    sort(u.begin(), u.end());

    for (int i = 0; i < n; i++) {
        vector<U>::iterator it = lower_bound(u.begin(), u.end(), U("", s - u[i].l));
        if (it->l == s - u[i].l) {
            cout << u[i].name << " " << it->name << endl;
            return 0;
        }
    }

    cout << "NIE\n";
}
