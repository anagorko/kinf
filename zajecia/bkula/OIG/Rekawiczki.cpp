#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    if (a <= b && a <= c) cout << b+c+2;
    else if (b <= c && b <= c) cout << a+c+2;
    else cout << a+b+2;

    return 0;
}
