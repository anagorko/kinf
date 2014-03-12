#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

	srandom (getpid());

	const int n = 10;

	vector <int> v;

	for (int i = 0; i < n; i++)
	{
		v.push_back(random() % 100);
	}

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}

	sort (v.begin(), v.end());

	cout << endl;

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}

	cout << endl;
	int x;
	cin >> x;

	int a = 0, b = v.size()-1;

	while (b>a)
	{
		int l = (b-a)/2;

		if (v[l] > x) b = l;
		else a = l;
	}

	cout << v[a] << endl;

	return 0;
}
