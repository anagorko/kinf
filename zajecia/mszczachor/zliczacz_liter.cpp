#include <iostream>
using namespace std;
int main () {

int i;
cin >> i;
string a[i];
string alfabet = "abcdefghijklmnopqrstuvwxyz";
int wyniki[alfabet.length()];
for (int z = 0; z < alfabet.length(); z++)
{
	 wyniki[z] = 0;
}
for (int z = 0; z < i; z++)
{
	 cin >>  a[z];
}
for (int z = 0; z < alfabet.length(); z++)
{
	for (int x = 0; x < i; x++)
	{
		for (int y = 0; y < a[x].length(); y++)
		{
			if(alfabet[z] == a[x][y])wyniki[z]++;
		}

	}
}
for (int z = 0; z < alfabet.length(); z++)
{
	if(wyniki[z] > 0)cout << alfabet[z] << " " << wyniki[z] << endl;
}

return 0;

}
