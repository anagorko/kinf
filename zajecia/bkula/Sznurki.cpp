#include <iostream>
using namespace std;

int main()
{
    int n, w, wyn = 0, m = 0;
    cin >> n >> w;

    for (int i = 0; i < n; i++)
    {
        int a; cin >> a;
        m += a;
        if (m >= w)
        {
            m = 0;
            wyn++;
        }
    }

    cout << wyn;

    return 0;
}
