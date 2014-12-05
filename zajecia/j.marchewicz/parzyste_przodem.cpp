#include <iostream>
using namespace std;
int main ()
{
	int n[20];
	for (int i = 0; i < 20; i++)
	{
		cin >> n[i];
	}
	for (int l = 19; l>=0; l--)
	{
		if (l % 2 == 0)
		cout << n[l] << " ";
	}
	for (int l = 19; l>=0; l--)
	{
		if (l % 2 !=0)
		cout << n[l] << " ";
	}
	return 0;
}
