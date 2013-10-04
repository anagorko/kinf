#include <iostream>
using namespace std;
int main () {
int a[10];
int wyniki1 [10];
int wyniki2 [42];
int b = 0;
for(int z = 0; z < 10; z++)
{
	cin >> a[z];
}
for(int z = 0; z < 10; z++)
{
	wyniki1[z] = a[z]%42;
}
for(int z = 0; z < 42; z++)
{
	wyniki2[z] = 0;
}

for(int z = 0; z < 42; z++)
{
	for(int x = 0; x < 10; x++)
	{
		if((wyniki1[x] == z) && (wyniki2[z] == 0))wyniki2[z]=1;
	
	}

}
for(int z = 0; z < 42; z++)
{
	if(wyniki2[z]==1)b++;
}
cout << b << endl;

return 0;

}
