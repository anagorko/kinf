#include <iostream>
using namespace std;
main()
{
int i,n;
char o;
cout<<"Ile chcesz mieć pytań? Odpowiedzi do pytań to T-tak i N-nie.\n" 
    <<"Nie można odpowiedzieć pełnym słowem. \n";
cin>>n;
for(i=0;i<n;i=i+1)
{
cout<<"Lubisz kiełbasę?\n";
cin>>o;
cout<<"\n";
}
}
 
