#include <iostream>
using namespace std;
main()
{
int ktory,i,n,l;
   cout<<"\nIle podzespołów sprawdzić?\n";
   cin>>n;
   l=n;
for(i=0;i<n;i=i+1)
{
   cout<<"\nKtóry podzespół sprawdzić?\n"
       <<"nr 1 - działo jonowe.\n"
       <<"nr 2 - hipernapend.\n"
       <<"nr 3 - osłonę.\n"
       <<"nr 4 - zasilanie.\n"
       <<"nr 5 - działo protonowe.\n" 
       <<"nr 6 - system samozniszczenia.\n" 
       <<"Podaj numer: \n";
   cin>>ktory;
switch(ktory)
{
  case 1 :
   cout<<"\nSprawdzam działo jonowe.\n\n";
   l=l-1;
   cout<<"Pozostało podzespołów do sprawdzenia: "<< l <<"\n\n";
  break;
case 2 :
   cout<<"Sprawdzam nadprzestrzeń.\n\n";
   l=l-1;
   cout<<"Pozostało podzespołów do sprawdzenia: "<< l <<"\n\n";
  break;
case 3 :
   cout<<"Sprawdzam osłonę.\n\n";
   l=l-1;
   cout<<"Pozostało podzespołów do sprawdzenia: "<< l <<"\n\n";
  break;
case 4 :
   cout<<"Sprawdzam zasilanie.\n\n";
   l=l-1;
   cout<<"Pozostało podzespołów do sprawdzenia: "<< l <<"\n\n";
  break;
case 5 :
   cout<<"Sprawdzam działo protonowe.\n\n";
   l=l-1;
   cout<<"Pozostało podzespołów do sprawdzenia: "<< l <<"\n\n";
  break;
case 6 :
   cout<<"\nSprawdzam system samozniszczenia.\n\n";
   l=l-1;
   cout<<"Pozostało podzespołów do sprawdzenia: "<< l <<"\n\n";
  break;
default :
   cout<<"Nie znam takiego numeru.\n\n";
   n=n+1;
   cout<<"Pozostało podzespołów do sprawdzenia: "<< l <<"\n\n";
  break;
}
}
}
 
