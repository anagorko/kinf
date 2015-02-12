#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const int SIZE = 8;

#define FOREACH \
for (int i = 0; i < SIZE; i++) \
    for (int j = 0; j < SIZE; j++)

struct P
{
    int w, k;
    char from, to;
};

char plansza[SIZE][SIZE];
long long calls=0;
// false - brak zmian
bool grawitacja(vector<P>& zmiany)
{if((++calls%10)==0)cout<<calls<<endl;
    int z_size = zmiany.size();
if((calls%10)==0)cout<<"A"<<endl;
    // usuwanie

    // w poziomie
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 2; j++)
        {
            if (plansza[i][j] == plansza[i][j+1] == plansza[i][j+2])
            {
                for (int k = 0; k < 3; k++) {
                    P z;
                    z.w = i;
                    z.k = j+k;
                    z.from = plansza[z.w][z.k];
                    z.to = '.';
                    zmiany.push_back(z);
                }
            }
        }
    }
    // w pionie
    for (int i = 0; i < SIZE - 2; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (plansza[i][j] == plansza[i+1][j] && plansza[i+1][j] == plansza[i+2][j])
            {
                for (int k = 0; k < 3; k++) {
                    P z;
                    z.w = i+k;
                    z.k = j;
                    z.from = plansza[z.w][z.k];
                    z.to = '.';
                    zmiany.push_back(z);
                }
            }
        }
    }

    // opadanie
    for (int kol = 0; kol < SIZE; kol++)
    {
        int puste = 0;
        for (int w = SIZE - 1; w >= 0; w--)
        {
            if (plansza[w][kol] == '.') puste++;
            else if (puste > 0) {

                P z1;
                z1.w = w;
                z1.k = kol + puste;
                z1.from = plansza[w][kol + puste];
                z1.to = plansza[w][kol];
                zmiany.push_back(z1);

                P z2;
                z2.w = w;
                z2.k = kol;
                z2.from = plansza[w][kol];
                z2.to = '.';
                zmiany.push_back(z2);
            }
        }
    }
if((calls%10)==0)cout<<"B"<<endl;
    if (z_size == zmiany.size()) return false;
if((calls%10)==0)cout <<"E"<<endl;
    grawitacja(zmiany);
if((calls%10)==0)cout << "grav: true\n";
if((calls%10)==0)cout<<"D"<<endl;
    return true;
}

void f(int x1, int y1, int x2, int y2, int ruch, string output)
{if((calls%10)==0)cout<<"C"<<endl;
    if (plansza[x1][y1] == plansza[x2][y2]) return;
    if (plansza[x1][y1] == '.' || plansza[x2][y2] == '.') return;

    vector<P> zmiany;

    // swap

    P z1;
    z1.w = x1;
    z1.k = y1;
    z1.from = plansza[x1][y1];
    z1.to = plansza[x2][y2];
    zmiany.push_back(z1);

    P z2;
    z2.w = x2;
    z2.k = y2;
    z2.from = plansza[x2][y2];
    z2.to = plansza[x1][y1];
    zmiany.push_back(z2);

    for (int i = 0; i < zmiany.size(); i++)
    {
        //cout << "["<<zmiany[i].w<<"]["<<zmiany[i].k <<"] from " << plansza[zmiany[i].w][zmiany[i].k] << " ";
        plansza[zmiany[i].w][zmiany[i].k] = zmiany[i].to;
        //if (zmiany[i].to != '.') cout << "to " << plansza[zmiany[i].w][zmiany[i].k] << "\n";
    }

    /*for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) cout << plansza[i][j] << " ";
        cout << endl;
    }
    cout << endl;*/

    if (grawitacja(zmiany)) // jedziemy głębiej
    {if((calls%10)==0)cout<<"OK!\n";
        stringstream ss;
        ss << output << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";

        // zastosuj zmiany
        for (int i = 0; i < zmiany.size(); i++)
        {
            plansza[zmiany[i].w][zmiany[i].k] = zmiany[i].to;
        }

        if (ruch == SIZE - 1) {

            cout << ss.str();
            exit(0);

        } else {

            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE - 1; j++)
                {
                    f(i, j, i, j+1, ruch + 1, ss.str());
                }
            }
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    f(i, j, i+1, j, ruch + 1, ss.str());
                }
            }
        }
    }

    // odwróc zmiany
    for (int i = zmiany.size() - 1; i >= 0; i--)
    {
        plansza[zmiany[i].w][zmiany[i].k] = zmiany[i].from;
    }if((calls%10)==0)cout<<"D"<<endl;
}

int main()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> plansza[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 1; j++)
        {
            f(i, j, i, j+1, 0, "");
        }
    }
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            f(i, j, i+1, j, 0, "");
        }
    }
}
