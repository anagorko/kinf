#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    float suma = 0;
    int n;

    cin >> n;

    struct punkt {
        int x;
        int y;
    };

    punkt p[n+1];

    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    p[n].x = p[0].x;
    p[n].y = p[0].y;

    bool odejmowanie = false;

    for (int i = 0; i < n; i++) {

        if (!odejmowanie && p[i].x > p[i+1].x) odejmowanie = true;

        if (!odejmowanie) suma += (p[i+1].x - p[i].x) * ((p[i].y + p[i+1].y) / 2);
        else suma -= (p[i].x - p[i+1].x) * ((p[i].y + p[i+1].y) / 2);
    }

    cout << fixed << setprecision(2) << suma;

    return 0;
}
