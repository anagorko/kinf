#include <iostream>
using namespace std;
main()
{
int p,l;
float k,c,i;  
   
   cout<<"Ile litrów chcesz zatankować?\n";
   cin>>l;
   cout<<"Jak jest obecnie cena paliwa?\n";
   cin>>c;
   i=c*l;
   cout<<"To będzie kosztowało "<<i<<" złotych.\n";
   cout<<"\nIle masz pieniędzy?\n";
   cin>>p;
   if(p<i) 
   {
      cout<<"\nNie masz wystarczająco pieniędzy.\n";
   }
   else 
   {
      cout<<"\nZapłaciłeś "<<i<<" złotych\n";
      k=p-i;
      cout<<"Zostało ci "<<k<<" złotych\n";
   }
}
 
