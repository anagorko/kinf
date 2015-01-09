#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct V
{
    int c;
    V* syn[26];
    V()
    {
        for (int i = 0; i < 26; i++) {
            syn[i] = NULL;
        }
        c = 0;
    }
};

int best = 1;

void dfs(V* v, int wyn)
{
    wyn += v->c;

    best = max(best, wyn);

    for (int i = 0; i < 26; i++) {
        if (v->syn[i]) {
            dfs(v->syn[i], wyn);
        }
    }
}

int main()
{
    int n;
    cin >> n;

    V* r = new V();

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        V* v = r;

        for (int j = 0; j < s.size(); j++)
        {
            if (v->syn[s[j]-'a']) {
                v = v->syn[s[j]-'a'];
            } else {
                v = v->syn[s[j]-'a'] = new V();
            }
        }

        v->c++;
    }

    dfs(r, 0);

    cout << best << endl;
}
