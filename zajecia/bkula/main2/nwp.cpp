#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string str[2];
    cin >> str[0] >> str[1];

    int f[str[0].size()+1][str[1].size()+1];

    for (int i = 0; i < str[0].size() + 1; i++)
    {
        for (int j = 0; j < str[1].size() + 1; j++)
        {
            if (i == 0 || j == 0) f[i][j] = 0;
            else f[i][j] = max(
                (str[0][i+1] == str[1][j+1]) ? f[i-1][j-1]+1 : 0,
                max(f[i][j-1], f[i-1][j])
            );

        }
    }

    /*
    for (int i = 0; i < str[0].size() +1; i++) {
        for (int j = 0; j < str[1].size() +1; j++) {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }
    */

    cout << f[str[0].size()][str[1].size()] << endl;
}
