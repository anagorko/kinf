#include <iostream>
#include <sstream>
using namespace std;

#define int long long

int p, q;

const int MAX = 1000000000000000007;

inline int wynik(int x)
{
    //if (x > 1000000) return -1;
    return x*x*x + p*x;
}

struct BSR // Binary Search Result
{
    bool b;
    int from;
    int to;
};

int lowerBound(int l, int from, int to, bool ret = false)
{
    //if (wynik(to) == -1) return 0;
    //if (! ret && l > wynik(to)) return lowerBound(l, to, to*2, 0);

    int center = (from + to - 1) / 2;

    if (to - from <= 2) {
        if (wynik(from) == l) return from;
        else return from + 1;
    }

    if (l > wynik(center)) return lowerBound(l, center, to, 1);
    else return lowerBound(l, from, center+1, 1);
}

BSR binarySearch(int l, int from, int to)
{
    BSR result;

    result.from = lowerBound(l, from, to);
    result.b = wynik(result.from) == l;

    return result;
}

#undef int

int main()
{
    ios_base::sync_with_stdio(0);

    int z;
    cin >> z;
    for (int i = 0; i < z; i++) {
        cin >> p >> q;
        BSR bsr = binarySearch(q, 0, 1000000);
        if (bsr.b) cout << bsr.from << "\n";
        else cout << "NIE\n";
    }

}
