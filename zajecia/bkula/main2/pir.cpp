#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> wyn;
string str;

int f(int i)
{
    if (i < 0) return 0;
    if (wyn[i] != -1) return wyn[i];

    wyn[i] = 0;

    if (str[i] == '1') {
        for (int j = 0; j < 6; j++) {
            wyn[i] += f(i - j - 1);
            wyn[i] %= k;
        }
    }

    return wyn[i];
}

int main()
{
    cin >> n >> k >> str;
    for (int i = 0; i < n; i++) wyn.push_back(-1);
    wyn[0] = 1;
    cout << f(n-1) << endl;
}
