#include <iostream>
using namespace std;
int main ()
{
	int long long suma = 0;
	for (int i = 1; i<1000000000; i +=2 )
	{
		suma += i;
	}
	
	
	cout << "Suma liczba równa jest" << suma << endl;
}

