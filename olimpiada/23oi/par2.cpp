#include <iostream>
#include <vector>
using namespace std;

class basen
{
public:
int x, y;
int width, height;
int size;
void calc_size (){
size = height * width;
}
basen(int nx, int ny){
x=nx;
y=ny;
width = 1;
height = 1;
calc_size();
}
void miw(){
width++;
calc_size();
}
void mih(){
height++;
calc_size();
}


};
int main()
{
    int n;
    cin >> n;
    
    int d[n][n]; // d - "d"ane; 0 - alejka, 1 = basenik;  d[nr wiersza][nr kolumny]
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            
            cin >> c;
            
            if (c == 'A') {
                d[i][j] = 0;
            } else if (c == 'B') {
                d[i][j] = 1;
            } else {
                cout << "Nie rozumiem znaku " << c << endl;
            }
        }
    }
    
    int b[n][n]; // numery basenów
vector <basen> baseny;
    int nr = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] == 0) {
                b[i][j] = -1;
                continue;
            }
            
            int numer_obok = -1;
            
            if (i > 0 && d[i-1][j] == 1) {
                baseny[b[i-1][j]].miw();
numer_obok = b[i-1][j];
            }
            if (j > 0 && d[i][j-1] == 1) {
                baseny[b[i][j-1]].mih();
numer_obok = b[i][j-1];
            }
            
            if (numer_obok == -1) {
                b[i][j] = nr;
basen tmp (i, j);
baseny.push_back(tmp);
                nr++;
            } else {
                b[i][j] = numer_obok;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] == -1) {
                    cout << " ";
            } else {
                cout << b[i][j];
            }
        }
        cout << endl;
    }

int h[nr];
for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
if(b[i][j] != 0)h[b[i][j]]++; 
}
}
    
    cout << "Liczba basenow: " << nr << endl;
for (int i = 0; i < nr; i++) {
        cout << "Powierzchnia basenu nr " << i << " wynosi " << baseny[i].size << endl;
}
}



