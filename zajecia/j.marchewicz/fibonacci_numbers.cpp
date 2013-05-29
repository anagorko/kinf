// (C) Marchewa

#include <iostream>
using  namespace std;

int main()
{
	int x = 0;
	int y = 1;
	int z;
	int suma = 0;
	
	for(int i = y; y <= 4000000; i++)
	{
	    z = x + y;
	    x = y;
	    y = z;
	    if (y % 2 == 0) sum += y;
	}
	cout << suma << endl;
}
