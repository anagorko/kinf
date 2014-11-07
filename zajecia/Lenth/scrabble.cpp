#include<iostream>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int n;
    n = s.length() + 1;
    int a = 1, b = n;
    while (a <= b)
    {
        cout << s[a];
        if (b != a)
        {
            cout << s[b];
        }
        a = a-1;
        b = b-1;
    }
    return 0;
}
