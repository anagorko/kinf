#include <iostream>
using namespace std;
int main ()
{
	int n[20];
	for (int j = 0; j < 20; j++)
	{
		cin >> n[j];
	}
	for (int j = 19; j>=0; j--)
	{
		cout << n[j] << " ";
	}
	cout << endl;
	return 0;
}
