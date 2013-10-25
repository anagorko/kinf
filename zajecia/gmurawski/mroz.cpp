#include<iostream>
using namespace std;
 
int main ()
{ 
int i;
cout << "Podaj temperaturę: ";
cin >> i;
if ( i<=0)
   { cout << " Jest mróz"<< endl;
   } 
else
     { cout << "Mrozu nie ma"<<endl;
   }

return 0 ;
}
