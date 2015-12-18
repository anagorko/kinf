#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    long long wyn = 0;
    int ile_zer = 0;
    for (int i = 0; i < n; i++)
    {
        bool s;
        cin >> s;
        if (s) wyn += ile_zer;
        else ile_zer++;
    }

    cout << wyn << endl;
}
