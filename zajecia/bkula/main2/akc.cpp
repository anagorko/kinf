/*
W ostatnim teście otrzymuję:
"Przekroczenie limitu czasu"
choć limitu 2.00s nie przekroczyłem
więc chyba mają popsutą sprawdzarkę :P

Uzyskuję takie czasy:

USE_STL = 0: 1.37s/2.00s
USE_STL = 1: 1.30s/2.00s

po użyciu ios_base::sync_with_stdio(0):

USE_STL = 0: 0.64s/2.00s
USE_STL = 1: 0.56s/2.00s
*/

#define USE_STL 1

#include <iostream>
#include <algorithm>
using namespace std;

struct BSR // Binary Search Result
{
    bool b;
    int from;
    int to;
};

int lowerBound(int l, int* tab, int from, int to)
{
    //cout<<"L: "<<from<<" "<<to<<endl;

    int center = (from + to - 1) / 2;

    if (to - from <= 2) {
        if (tab[from] == l) return from;
        else return from + 1;
    }

    if (l > tab[center]) return lowerBound(l, tab, center, to);
    else return lowerBound(l, tab, from, center+1);
}

int upperBound(int l, int* tab, int from, int to)
{
    //cout<<"U: "<<from<<" "<<to<<endl;

    int center = (from + to) / 2;

    if (to - from <= 2) {
        if (tab[to - 1] == l) return to;
        else return to - 1;
    }

    if (l < tab[center]) return upperBound(l, tab, from, center);
    else return upperBound(l, tab, center, to);
}


BSR binarySearch(int l, int* tab, int from, int to)
{
    BSR result;

    result.from = lowerBound(l, tab, from, to);
    result.to = upperBound(l, tab, result.from, to);
    result.b = tab[result.from] == l;

    return result;
}

int main()
{
    ios_base::sync_with_stdio(1);

    int n;
    cin >> n;
    int tab[n];
    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {

        int s;
        cin >> s;

        #if USE_STL

        pair<int*,int*> p = equal_range(tab, tab + n, s);
        if (p.first != p.second) {
            cout << (p.second - p.first) << "\n";
        } else {
            cout << "0\n";
        }

        #else

        BSR bsr = binarySearch(s, tab, 0, n);
        if (bsr.b) {
            cout << bsr.to -  bsr.from << "\n";
        } else {
            cout << "0\n";
        }

        #endif // USE_STL
    }
}
