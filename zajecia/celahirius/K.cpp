#include <iostream>
using namespace std;
main()
{
char litera;

do
{
cout<<"Napisz jakąś literę. Jeśli wpiszesz wielkie K to zakończysz program : ";
cin>>litera;

cout<<"\nNapisałeś : "<<litera<<"\n";
}
while(litera != 'K');
cout<<"\nSkoro napisałeś K to kończymy\n";

}

