#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main()
{
    int x,y,kx,ky,kroki=0;
    bool end=true;
    cin >> x >> y;
    char qwer[x][y];
    int tab[x][y];
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<x; j++)
        {
            cin >> qwer[i][j];
            switch(qwer[i][j])
            {
                case '#':
                tab[i][j]=-1;
                break;
                
                case '.':
                tab[i][j]=0;
                break;
                
                case 'P':
                tab[i][j]=1;
                break;
                
                case 'K':
                tab[i][j]=0;
                kx=i;
                ky=j;
                break;
            }
        }
    }
    while(end)
    {
        kroki++;
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            if(tab[i][j]==kroki)
            {
                if(tab[i+1][j]==0)
                {
                    tab[i+1][j]=kroki+1;
                }
                if(tab[i-1][j]==0)
                {
                    tab[i-1][j]=kroki+1;
                }
                if(tab[i][j+1]==0)
                {
                    tab[i][j+1]=kroki+1;
                }
                if(tab[i][j-1]==0)
                {
                    tab[i][j-1]=kroki+1;
                }
            }
            if(tab[kx][ky]!=0)
            {
                end=false;
            }
        }
    }
    }
    cout << kroki;
}
