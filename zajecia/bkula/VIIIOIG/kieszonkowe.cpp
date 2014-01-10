#include <iostream>
using namespace std;

const int MAX = 1000001;

void swap_int (int &a, int &b) {
    int pom = a;
    a = b;
    b = pom;
}

void swap_double (double &a, double &b) {
    double pom = a;
    a = b;
    b = pom;
}

struct tablica {
    int index;
    double wedlug;
};

int partition (tablica *a, int l, int r)
{
    int i = l;
    int x = a[l].wedlug;
    int j = r + 1;

    do
    {
        do
            i++;
        while (a[i].wedlug < x);
        do
            j--;
        while (a[j].wedlug > x);

        if (i < j) {
            swap_int(a[i].index, a[j].index);
            swap_double(a[i].wedlug, a[j].wedlug);
        }

    } while (j > i);

    swap_double(a[l].wedlug, a[j].wedlug);
    swap_int(a[l].index, a[j].index);
    return j;
}

void quicksort (tablica *a, int p, int r)
{
    if (p == r) return;

    int q = partition(a, p, r);
    if (q - p > 1) quicksort(a, p, q - 1);
    if (r - q > 1) quicksort(a, q + 1, r);
}

int main()
{
    int n, k;
    cin >> n >> k;

    int wartosc[n][2];
    short ilosc[n];

    tablica tab[2*n+1];
    tab[2*n].wedlug = MAX;

    for (int i = 0; i < n; i++)
    {
        ilosc[i] = 2;
        cin >> wartosc[i][1];
        tab[i].index = i;
    }

    for (int i = 0; i < n; i++)
    {
        cin >> wartosc[i][0];
        tab[i+n].index = i+n;
        tab[i*2+1].wedlug = wartosc[i][0];
        if (wartosc[i][1] > wartosc[i][0]) tab[i*2].wedlug = wartosc[i][1];
        else tab[i*2].wedlug = (double)(wartosc[i][1] + wartosc[i][0]) / 2;
    }

    quicksort (tab, 0, n*2 -1);

    long long wyn = 0;

    for (int i = n*2-1; i >= 0; i--) {

        int indeks = tab[i].index / 2;

        if (ilosc[indeks] == 2 && (tab[i].index % 2) == 0) {

            wyn += wartosc[indeks][1];
            ilosc[indeks]--;
            k--;

            if (wartosc[indeks][0] >= tab[i-1].wedlug) {
                wyn += wartosc[indeks][0];
                ilosc[indeks]--;
                k--;
            }

        } else if (ilosc[indeks] == 1 && (tab[i].index % 2) != 0) {

            wyn += wartosc[indeks][0];
            ilosc[indeks]--;
            k--;
        }

        if (k <= 1) {
            if (k == 1) {
                int naj = 0;
                for (int j = i-2; j >= 0; j--) {
                    if (wartosc[tab[j].index / 2][ilosc[tab[j].index / 2]-1] > naj) {
                        naj = wartosc[tab[j].index / 2][ilosc[tab[j].index / 2]-1];
                    }
                }
                wyn += naj;
            }
            break;
        }
    }

    cout << wyn;

    return 0;
}
