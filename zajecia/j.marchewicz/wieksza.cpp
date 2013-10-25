#include <iostream>
using namespace std;

int main ()
{
int i;
int s;
cout << "Podaj dwie liczby ";
cin>> i;
cin>> s;
if (i < s)
	{cout<< "Ułożone liczby to: "<< i << " " << s <<endl;
	}

else 
	{ cout<< "Ułożone liczby to: "<< s << " " << i <<endl;
	}

return 0;
}
