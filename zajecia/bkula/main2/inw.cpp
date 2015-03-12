
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

long long inversions = 0;

void mergeSort(int* tab, int from, int to)
{
    if (to - from <= 1) return;

    int center = (from + to) / 2;
    mergeSort(tab, from, center);
    mergeSort(tab, center, to);

    int pom[to - from];

    // merge(tab + from, tab + center, tab + center, tab + to, pom);

    int a = from, b = center;
    for (int i = 0; i < to - from; i++) {
        if (b >= to || (a < center && tab[a] < tab[b])) {
            pom[i] = tab[a];
            a++;
        } else {
            pom[i] = tab[b];
            inversions += center - a;
            b++;
        }
    }

    for (int i = 0; i < to - from; i++) {
        tab[from + i] = pom[i];
    }
}

int main()
{
    int n;
    cin >> n;
    int tab[n];
    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    mergeSort(tab, 0, n);

    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;

    cout << inversions << endl;
}

// Poprzednie podejście
/*
struct Number
{
    int value;
    int index;
    friend bool operator<(const Number& a, const Number& b)
    {
        return a.value < b.value;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    Number tab[n];
    for (int i = 0; i < n; i++)
    {
        cin >> tab[i].value;
        tab[i].index = i;
    }

    sort(tab, tab + n);
    for (int i = 0; i < n; i++)
    {
        cout << tab[i].value << " ";
    }
    cout << endl;

    int result = 0;

    vector<int> lni; //lower_numbers_indexes;
    for (int i = 0; i < n; i++) {
        cout << "#" << i << "\n";
        for (int j = 0; j < lni.size(); j++) cout << lni[j] << " "; cout << endl;

        lni.push_back(tab[i].index);
        push_heap(lni.begin(), lni.end(), greater<int>());
        vector<int>::iterator it = lower_bound(lni.begin(), lni.end(), tab[i].index);
        //if (*it != tab[i].index) it = lni.end();
        result += it - lni.begin();

        for (int j = 0; j < lni.size(); j++) cout << lni[j] << " "; cout << endl;
        cout << it - lni.begin() << "\n";
    }

    cout << result << endl;
}
*/
