// jak to przyśpieszyć? O.o

#include <iostream>
using namespace std;

int nwd(int a, int b)
{
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return nwd(b, a % b);
}

int main()
{
    ios_base::sync_with_stdio(0);

    int z;
    cin >> z;
    for (int i = 0; i < z; i++) {
        int n, d;
        cin >> n >> d;
        cout << n / nwd(n,d) << endl;
    }
}
