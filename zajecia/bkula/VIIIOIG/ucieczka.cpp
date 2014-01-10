#include <iostream>
#include <algorithm>
using namespace std;

int partition(int *a, int l, int r)
{
    int i = l;
    int x = a[l];
    int j = r + 1;

    do
    {
        do
            i++;
        while (a[i] < x);
        do
            j--;
        while (a[j] > x);

        if (i < j)
            swap(a[i], a[j]);

    } while (j > i);

    swap(a[l], a[j]);
    return j;
}

void quicksort(int *a, int p, int r)
{
    if (p == r) return;

    int q = partition(a, p, r);
    if (q - p > 1) quicksort(a, p, q - 1);
    if (r - q > 1) quicksort(a, q + 1, r);
}

int main() {

    int n, t, d;
    cin >> n >> t >> d;

    int warty[n*2+1]; // początki i końce wart

    for (int i = 0; i < n*2; i++) {
        cin >> warty[i];
        warty[i] *= 2;
        if ((i % 2) == 1) warty[i]++;
    }

    warty[n*2] = 1000000001;
    quicksort(warty, 0, n*2 - 1);

    int momenty[n+1]; // ilości i-bezpiecznych momentów w bieżącej ucieczce
    int ucieczki[n+1]; // ilości i-bezpiecznych ucieczek

    for (int i = 0; i < n+1; i++) {
        momenty[i] = 0;
        ucieczki[i] = 0;
    }

    int moment = 1, i = 0;
    int b_ucieczki = n, b_momentu = 0;

    for (; moment <= t; moment++) {
        for (; warty[i] <= moment*2; i++) {
            if ((warty[i] % 2) == 0) {
                b_momentu++;
            } else {
                b_momentu--;
            }
        }
        if (b_momentu < b_ucieczki) b_ucieczki = b_momentu;
        momenty[b_momentu]++;
    }
    ucieczki[b_ucieczki]++;

    int moment2 = 1, i2 = 0;
    int b_momentu2 = 0;

    while (moment <= d) {

        for (; warty[i] <= moment*2; i++) {
            if ((warty[i] % 2) == 0) {
                b_momentu++;
            } else {
                b_momentu--;
            }
        }
        moment++;
        momenty[b_momentu]++;
        if (b_momentu < b_ucieczki) b_ucieczki = b_momentu;

        for (; warty[i2] <= moment2*2; i2++) {
            if ((warty[i2] % 2) == 0) {
                b_momentu2++;
            } else {
                b_momentu2--;
            }
        }
        moment2++;
        momenty[b_momentu2]--;
        if (b_momentu2 == b_ucieczki) {
            for (int j = b_momentu2; j < n+1; j++) {
                if (momenty[j] != 0) {
                    b_ucieczki = j;
                    break;
                }
            }
        }

        ucieczki[b_ucieczki]++;
    }

    for (int j = n-1; j >= 0; j--) ucieczki[j] += ucieczki[j+1];

    for (int j = 0; j < n+1; j++) {
        if (ucieczki[j] != 0) cout << j << " " << ucieczki[j] << endl;
        else return 0;
    }

    return 0;
}
