#include <iostream>
using namespace std;

int main()
{
string s;
cout<<"Jak masz na imię ?"<<endl;
cin>>s;

if ( s[s.length()-1]=='a')
cout<< "Jesteś kobietom"<<endl;
else
cout<< "Jesteś menszczysna"<<endl;



return 0;
}
