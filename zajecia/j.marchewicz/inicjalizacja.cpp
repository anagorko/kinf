#include <iostream>
using namespace std;
int main ()
{
	int n;
	cin >> n;
	int t[n-1];
	for (int i = 0; i < n ; i++)
	{
		t[i] = i;

	}
		for (int i = 0; i < n; i++)
		{
			cout << t[i] << " ";
		}
		cout << endl;
	for (int i = 0; i < n ; i++)
	{
		t[i] = i+7;

	}
		for (int i = 0; i < n; i++)
		{
			cout << t[i] << " ";
		}
		cout << endl;
	for (int i = 0; i < n ; i+4)
		{
			t[i] = i+4;

		}
		for (int i = 0; i < n; i++)
			{
				cout << t[i] << " ";
			}
		cout << endl;
	for (int i = 1; i < n ; i*2)
			{
				t[i] = i+1;

			}
			for (int i = 0; i < n; i++)
				{
					cout << t[i] << " ";
				}
		cout << endl;
		return 0;


}
