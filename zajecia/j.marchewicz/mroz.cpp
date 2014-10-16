// (C) Jan Marchewicz
#include <iostream>
using namespace std;

int main ()
{
	int i;
	cout << "Podaj temperaturę na zewnątrz: ";
	cin>> i;
	if (i<=0)
	{
		cout<< "Mróz jest"<<endl;
	}
else 
	{ 
		cout << "Nie ma mrozu."<<endl;
	}


}
