#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

const int SIZE = 8;

struct Point
{
    int x, y;

    Point(int _x, int _y)
    : x(_x)
    , y(_y)
    {
    }
};

bool pusta(char plansza[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (plansza[i][j] != '.') return false;
        }
    }

    return true;
}

// false - brak zmian
bool grawitacja(char plansza[SIZE][SIZE])
{
    stack<Point> to_clear;

    // w poziomie
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 2; j++)
        {
            if (plansza[i][j] != '.' && plansza[i][j] == plansza[i][j+1] && plansza[i][j+1] == plansza[i][j+2])
            {
                for (int k = 0; k < 3; k++) {
                    to_clear.push(Point(i,j+k));
                }
            }
        }
    }

    // w pionie
    for (int i = 0; i < SIZE - 2; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (plansza[i][j] != '.' && plansza[i][j] == plansza[i+1][j] && plansza[i+1][j] == plansza[i+2][j])
            {
                for (int k = 0; k < 3; k++) {
                    to_clear.push(Point(i+k,j));
                }
            }
        }
    }

    // czyszczenie
    bool result = ! to_clear.empty();
    while (! to_clear.empty()) {
        Point p = to_clear.top();
        to_clear.pop();
        plansza[p.x][p.y] = '.';
    }

    // opadanie
    for (int kol = 0; kol < SIZE; kol++)
    {
        int puste = 0;
        for (int w = SIZE - 1; w >= 0; w--)
        {
            if (plansza[w][kol] == '.') puste++;
            else if (puste > 0) {

                plansza[w + puste][kol] = plansza[w][kol];
                plansza[w][kol] = '.';

                result = true;
            }
        }
    }

    if (! result) return false;

    grawitacja(plansza);

    return true;
}

void f(int x1, int y1, int x2, int y2, int ruch, string output, char p[SIZE][SIZE])
{
    if (p[x1][y1] == p[x2][y2]) return;
    if (p[x1][y1] == '.' || p[x2][y2] == '.') return;

    // kopiowanie planszy
    char plansza[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            plansza[i][j] = p[i][j];
        }
    }

    // zamiana
    char pom = plansza[x1][y1];
    plansza[x1][y1] = plansza[x2][y2];
    plansza[x2][y2] = pom;

    if (grawitacja(plansza)) // jedziemy głębiej
    {
        cout << "ruch: " << ruch << endl;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                cout << plansza[i][j];
            }
            cout << endl;
        }
        cout << endl;

        stringstream ss;
        ss << output << x1 + 1 << " " << y1 + 1 << " " << x2 + 1 << " " << y2 + 1 << "\n";

        if (pusta(plansza)) {

                cout << ruch + 1 << "\n" << ss.str();
                exit(0);

        } else if (ruch == SIZE - 1) {

            return;

        } else {

            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE - 1; j++)
                {
                    f(i, j, i, j+1, ruch + 1, ss.str(), plansza);
                }
            }
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    f(i, j, i+1, j, ruch + 1, ss.str(), plansza);
                }
            }
        }
    }
}

int main()
{
    char plansza[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> plansza[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 1; j++)
        {
            f(i, j, i, j+1, 0, "", plansza);
        }
    }
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            f(i, j, i+1, j, 0, "", plansza);
        }
    }
}
