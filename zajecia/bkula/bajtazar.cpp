#include <iostream>
using namespace std;
int main()
{

int liczba_ludzi;
int liczba_minut;

int widownia = 0;

int minuta = 0;
int naj_minuta = 0;
int naj_widownia = 0;

int pom;

cin>>liczba_ludzi;

  int n; //jaki bedzie rozmiar tablicy
  n = liczba_ludzi * 2;
    int tab[n];

    //-----------------

    for (int i = 0; i != liczba_ludzi * 2; i++){
        cin>>pom;
        if (i == 1) liczba_minut = pom;
        if ((i % 2) == 0) tab[i] = pom * 2 + 1;
        else {
            tab[i] = pom * 2;
            if (pom > liczba_minut) liczba_minut = pom;
        }
    }

    //-----------------

for(int i=0;i<n;i++)
  {
  for(int j=i+1;j<n;j++)
    {
    if(tab[i]>tab[j])
      {
      int x = tab[i];
      tab[i] = tab[j];
      tab[j] = x;
      }
    }
  }

  //------------------------
  //------------------------
  //------------------------

  for (int i = 0; i != liczba_ludzi * 2; i++){
    if ((tab[i] % 2) != 0) {
        minuta = tab[i] / 2 - 1;
        widownia++;
    } else {
        minuta = tab[i] / 2;
        widownia--;
    }
    if (widownia > naj_widownia) {naj_widownia = widownia; naj_minuta = minuta;}
  }

  cout<<"Bajtazar powinien zagrać pomiędzy "<<naj_minuta + 1 <<" a "<<naj_minuta + 2<<" minutą.";

  cout << endl;


     return 0;
}
