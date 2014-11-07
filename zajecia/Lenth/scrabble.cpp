#include<iostream>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int n;
    n = s.length();
    int a = 0, b = n-1;
    while (a <= b)
    {
        cout << s[a];
        if (b != a)
        {
            cout << s[b];
        }
        a = a+1;
        b = b-1;
    }
    cout << "\n";
    return 0;
}
