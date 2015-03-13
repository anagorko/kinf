#include <iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);

    int t;
    cin >> t;

    for (int q = 0; q < t; q++)
    {
        int w, h;
        cin >> w >> h;

        int tab[h][w];
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> tab[i][j];
                tab[i][j] += max(
                    i == 0 ? 0 : tab[i-1][j],
                    j == 0 ? 0 : tab[i][j-1]
                );
            }
        }

        cout << tab[h-1][w-1] << "\n";
    }
}
