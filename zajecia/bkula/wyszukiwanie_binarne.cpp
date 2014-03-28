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

	cout << "Wygenerowany zbiór: ";

	for (int i = 0; i < n; i++)
	{
		v.push_back(random() % 100);
	}

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}

	sort (v.begin(), v.end());

	cout << endl << "Posortowany zbiór: ";

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}

	cout << endl << "Szukaj w zbiorze: ";
	int x;
	cin >> x;

	int a = 0, b = v.size()-1;

	while ((b-a) > 1)
	{
		int l = a + (b-a)/2;

		if (v[l] == x)
		{
		    cout << "Podany element występuje w zbiorze\n";
		    return 0;
		}

		if (v[l] > x) b = l;
		else a = l;
	}

	int wyn;
	if (abs(x-v[a]) <= abs(x-v[b])) wyn = v[a];
	else wyn = v[b];

	cout << "Podany element nie występuje w zbiorze. Najbardziej zbliżonym elementem jest " << wyn << endl;

	return 0;
}
