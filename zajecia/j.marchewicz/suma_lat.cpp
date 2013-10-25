#include <iostream>
using namespace std;

int main ()
{
int a,s,d;

cout << "Podaj 3 wieki ";
cin>> a;
cin>> s;
cin>> d;
if (a+s+d <= 21)
	{cout<< "Mają mniej niż 21 lat" <<endl;
	}

else 
	{ cout<< "Mają więcej niż 21 lat" <<endl;
	}

return 0;
}
