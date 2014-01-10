#include <iostream>
#include <vector>

using namespace std;

const int MAX = 4000001;

struct pole {
    bool dziura;
    int grupa;
};

int main() {

    int n, m;
    cin >> n >> m;

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    pole tab[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char t;
            cin >> t;
            if (t == '.') tab[i][j].dziura = false;
            else tab[i][j].dziura = true;
        }
    }

    vector < int > grupy;

    if (tab[0][0].dziura == false) {
        tab[0][0].grupa = 0;
        grupy.push_back(0);
    }

    for (int i = 1; i < n; i++) {
        if (tab[i][0].dziura == false) {
            if (tab[i-1][0].dziura) {
                tab[i][0].grupa = grupy.size();
                grupy.push_back(grupy.size());
            } else {
                tab[i][0].grupa = tab[i-1][0].grupa;
            }
        }
    }

    for (int j = 1; j < m; j++) {
        if (tab[0][j].dziura == false) {
            if (tab[0][j-1].dziura) {
                tab[0][j].grupa = grupy.size();
                grupy.push_back(grupy.size());
            } else {
                tab[0][j].grupa = tab[0][j-1].grupa;
            }
        }
    }

    for (int i = 1; i < n; i++){
        for (int j = 1; j < m; j++){
            if (tab[i][j].dziura == false) {
                if (tab[i-1][j].dziura == false) {
                    if (tab[i][j-1].dziura == false && grupy[tab[i-1][j].grupa] != grupy[tab[i][j-1].grupa]) {
                        if (grupy[tab[i-1][j].grupa] > grupy[tab[i][j-1].grupa]) {
                            grupy[tab[i-1][j].grupa] = grupy[tab[i][j-1].grupa];
                        } else {
                            grupy[tab[i][j-1].grupa] = grupy[tab[i-1][j].grupa];
                        }
                    }
                    tab[i][j].grupa = tab[i-1][j].grupa;
                } else if (tab[i][j-1].dziura == false) {
                    tab[i][j].grupa = tab[i][j-1].grupa;
                } else {
                    tab[i][j].grupa = grupy.size();
                    grupy.push_back(grupy.size());
                }
            }
        }
    }

    int start, meta;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (tab[i][j].dziura == false) {
                tab[i][j].grupa = grupy[tab[i][j].grupa];
            }
            if (i == x1-1 && j == y1-1) start = tab[i][j].grupa;
            else if (i == x2-1 && j == y2-1) meta = tab[i][j].grupa;
        }
    }

    int w = grupy.size(); //liczba wierzchołków

    bool graf[w][w];

    vector < int > Q;

    int cecha[w];

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            graf[i][j] = false;
        }
        Q.push_back(i);
        cecha[i] = MAX;
    }

    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-1; j++) {
            if (tab[i][j].dziura) {
                if (tab[i-1][j].dziura == false && tab[i+1][j].dziura == false && tab[i-1][j].grupa != tab[i+1][j].grupa) {
                    graf[tab[i-1][j].grupa][tab[i+1][j].grupa] = true;
                    graf[tab[i+1][j].grupa][tab[i-1][j].grupa] = true;
                } else if (tab[i][j+1].dziura == false && tab[i][j-1].dziura == false && tab[i][j+1].grupa != tab[i][j-1].grupa) {
                    graf[tab[i][j+1].grupa][tab[i][j-1].grupa] = true;
                    graf[tab[i][j-1].grupa][tab[i][j+1].grupa] = true;
                }
            }
        }
    }
    for (int i = 1; i < n-1; i++) {
        if (tab[i][0].dziura) {
            if (tab[i-1][0].dziura == false && tab[i+1][0].dziura == false && tab[i-1][0].grupa != tab[i+1][0].grupa) {
                graf[tab[i-1][0].grupa][tab[i+1][0].grupa] = true;
                graf[tab[i+1][0].grupa][tab[i-1][0].grupa] = true;
            }
        }
    }
    for (int i = 1; i < n-1; i++) {
        if (tab[i][m-1].dziura) {
            if (tab[i-1][m-1].dziura == false && tab[i+1][m-1].dziura == false && tab[i-1][m-1].grupa != tab[i+1][m-1].grupa) {
                graf[tab[i-1][m-1].grupa][tab[i+1][m-1].grupa] = true;
                graf[tab[i+1][m-1].grupa][tab[i-1][m-1].grupa] = true;
            }
        }
    }
    for (int j = 1; j < m-1; j++) {
        if (tab[0][j].dziura) {
            if (tab[0][j+1].dziura == false && tab[0][j-1].dziura == false && tab[0][j+1].grupa != tab[0][j-1].grupa) {
                graf[tab[0][j+1].grupa][tab[0][j-1].grupa] = true;
                graf[tab[0][j-1].grupa][tab[0][j+1].grupa] = true;
            }
        }
    }
    for (int j = 1; j < m-1; j++) {
        if (tab[n-1][j].dziura) {
            if (tab[n-1][j+1].dziura == false && tab[n-1][j-1].dziura == false && tab[n-1][j+1].grupa != tab[n-1][j-1].grupa) {
                graf[tab[n-1][j+1].grupa][tab[n-1][j-1].grupa] = true;
                graf[tab[n-1][j-1].grupa][tab[n-1][j+1].grupa] = true;
            }
        }
    }

    ///*************************************///

    cecha[start] = 0;

    while (1) {

        int min = MAX, index, v;
        for (int i = 0; i < Q.size(); i++) {
            if (cecha[Q[i]] < min) {
                v = Q[i];
                min = cecha[v];
                index = i;
            }
        }


        if (min == MAX) {
            cout << "-1";
            return 0;
        } else if (v == meta) {
            cout << cecha[v];
            return 0;
        }

        Q.erase(Q.begin()+index);

        for (int i = 0; i < Q.size(); i++) {
            if (graf[v][Q[i]]) {
                if (cecha[v]+1 < cecha[Q[i]]) {
                    cecha[Q[i]] = cecha[v]+1;
                }
            }
        }
    }

    return 0;
}
