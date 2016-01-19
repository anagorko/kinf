#include <iostream>
#include <vector>
using namespace std;

class basen
{
public:
    int x, y;
    int width, height;
    int siz;
    void calc_size ()
    {
        siz = height * width;
    }
    basen(int nx, int ny)
    {
        x=nx;
        y=ny;
        width = 1;
        height = 1;
        calc_size();
    }
    void miw()
    {
        width++;
        calc_size();
    }
    void mih()
    {
        height++;
        calc_size();
    }
    void add_one(int nx, int ny)
    {
        if(x + width - 1 < nx)miw();
        if(y + height - 1 < ny)mih();
    }


};
int main()
{
    int n;
    cin >> n;

    int d[n][n]; // d - "d"ane; 0 - alejka, 1 = basenik;  d[nr wiersza][nr kolumny]
    int b[n][n]; // numery basenów
    int w1[n][n]; // rozmiar basenu po przekształceniu alejki w basen (0 - basen - nie da się zamienić w alejkę)

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char c;
            cin >> c;
            if (c == 'A')
            {
                d[i][j] = 0;
            }
            else if (c == 'B')
            {
                d[i][j] = 1;
            }
            else
            {
                cout << "Nie rozumiem znaku " << c << endl;
            }
        }
    }

    vector <basen> baseny;
    int nr = 0;

    for (int i = 0; i < n; i++) // wypełnianie tablicy b i Baseny
    {
        for (int j = 0; j < n; j++)
        {
            if (d[i][j] == 0)
            {
                b[i][j] = -1;
                continue;
            }


            int numer_obok = -1;

            if (i > 0 && d[i-1][j] == 1)
            {
                //baseny[b[i-1][j]].miw();
                baseny[b[i-1][j]].add_one(i, j);
                numer_obok = b[i-1][j];
            }
            if (j > 0 && d[i][j-1] == 1)
            {
                //baseny[b[i][j-1]].mih();
                baseny[b[i][j-1]].add_one(i, j);
                numer_obok = b[i][j-1];
            }

            if (numer_obok == -1)
            {
                b[i][j] = nr;
                basen tmp (i, j);
                baseny.push_back(tmp);
                nr++;
            }
            else
            {
                b[i][j] = numer_obok;
            }
        }
    }

    /*for (int i = 0; i < n; i++) //rysowanie b
    {
        for (int j = 0; j < n; j++)
        {
            if (b[i][j] == -1)
            {
                cout << " ";
            }
            else
            {
                cout << b[i][j];
            }
        }
        cout << endl;
    }*/

    /*int h[nr];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(b[i][j] != 0)h[b[i][j]]++;
        }
    }*/

    //cout << "Liczba basenow: " << nr << endl;
    for (int i = 0; i < nr; i++)
    {
        //cout << "Powierzchnia basenu nr " << i << " wynosi " << baseny[i].siz << endl;
    }


    /*int total_size (int x1, int y1, int x2, int y2){
        int baseny_laczone[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
        int nr = 0;

                if(x1 > 0 && d[x1 - 1][y1] == 1)
                {
                    baseny_laczone[nr] = b[x1-1][y1];
                    nr++;
                }
                if(x1 < (n- 1) && d[x1 + 1][j] == 1)
                {
                    baseny_laczone[nr] = b[x1+1][y1];
                    nr++;
                }
                if(y1 > 0 && d[x1][y1 - 1] == 1)
                {
                    baseny_laczone[nr] = b[x1][y1 - 1];
                    nr++;
                }
                if(y1 < (n- 1) && d[x1][y1 + 1] == 1)
                {
                    baseny_laczone[nr] = b[x1][y1 + 1];
                    nr++;
                }

                cout << endl;
            }
            else
            {
                w1[i][j] = 0;
            }
        }



    };*/


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (d[i][j] == 0)
            {
                int s = 0;
                vector <int> xs;
                vector <int> ys;


                if(i > 0 && d[i - 1][j] == 1)
                {
                    /*for(int z = baseny[b[i-1][j]].x - 1; z < (baseny[b[i-1][j]].width + baseny[b[i-1][j]].x); z++){
                        for(int p = baseny[b[i-1][j]].y - 1; p < (baseny[b[i-1][j]].height + baseny[b[i-1][j]].y); p++){

                        }
                    }*/
                    s += baseny[b[i-1][j]].siz;
                }
                if(i < (n- 1) && d[i + 1][j] == 1)
                {
                    s += baseny[b[i+1][j]].siz;
                }
                if(j > 0 && d[i][j - 1] == 1)
                {
                    s += baseny[b[i][j - 1]].siz;
                }
                if(j < (n- 1) && d[i][j + 1] == 1)
                {
                    s += baseny[b[i][j + 1]].siz;
                }
                w1[i][j] = s + 1;
                //cout << endl;
            }
            else
            {
                w1[i][j] = 0;
            }
        }

}

int m = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            //cout << "#"<< w1[i][j] << " ";
            if(w1[i][j] > m) m = w1[i][j];

        }
        //cout << endl;
    }
    cout << m << endl;
}


