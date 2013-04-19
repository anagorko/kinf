#include <iostream>
using namespace std;

int main()
{
	char a;

	do
	{
		cout<<"napisz jakąś literę:\n";
		cin>> a;
		cout<<"napisałeś \"" << a <<"\""<<endl;
	}
	while (a != 't');
	
	cout<<"napisałeś \"t\" więc kończymy\n";
	
} 
	
	
	
