// (C) Janek Bielecki
#include <iostream>
using namespace std;
int main()
{
   int a,liczba,max,min;

   cin >> a;
   for(int i=0;i<a;i++)
   {
       cin>>liczba;
       if(i==0)
       {
           max=liczba;
           min=liczba;
       }
       if(liczba>max)
           max=liczba;
       if(liczba<min)
           min=liczba;
   }
   cout << max - min;
   return 0;
 }
