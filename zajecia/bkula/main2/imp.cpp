
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;

const int MAX_N = 18;

int zbanowany[MAX_N]; // 0 - niezbanowany

bool nielubi[MAX_N][MAX_N];

stringstream out;
int naj = 0;

int n;

void f(int pos, int num)
{
    //cout << "f(" << pos << "," << num+1 << ")\n";

    zbanowany[num]--;

    if (pos > naj) {
        naj = pos;
        out.str("");
        out.clear();
        for (int i = 0; i < n; i++) {
            if (! zbanowany[i]) {
                out << i+1 << " ";
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (nielubi[num][i]) {
            zbanowany[i]++;
        }
    }

    for (int i = num + 1; i < n; i++) {
        if (zbanowany[i] <= 1) {
            f(pos + 1, i);
        }
    }

    for (int i = 0; i < n; i++) {
        if (nielubi[num][i]) {
            zbanowany[i]--;
        }
    }

    zbanowany[num]++;
}

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char in;
            cin >> in;
            nielubi[i][j] = in == '1' ? 1 : 0;
        }
        zbanowany[i] = 1;
    }

    for (int i = 0; i < n; i++) f(1, i);

    cout << naj << endl << out.str() << endl;
}
