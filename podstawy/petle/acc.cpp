#include<iostream>
using namespace std;

int main()
{
    int a = 0;
    int b, c;

    cin >> b >> c;

    while (true)
    {
        if (b == 0) break;
            if (b % 2 == 1) {  a += c; }
            b /= 2;
            c *= 2;
    }

    cout << a << endl;

    return 0;
}
