#include <iostream>
using namespace std;

const int MAX = 1000001;

bool bl (bool a) { return a == 0; }

int main()
{
    int n;
    cin >> n;

    bool tab[MAX];

    for (int i = 0; i < MAX; i++) tab[i] = 0;

    for (int i = 0; i < n; i++)
    {
	int a, b;
	cin >> a >> b;
	tab[a] = bl(tab[a]); tab[b] = bl(tab[b]);
    }

    bool wyn = 0;
    int a;

    for (int i = 0; i < MAX; i++)
    {
	if (tab[i])
	{
	    if (wyn == 0)
	    {
		wyn = 1;
		a = i;
	    }
	    else
	    {
		cout << min(a,i) << " " << max(a,i);
		return 0;
	    }
	}
    }

    return -1;
}
