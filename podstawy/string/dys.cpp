#include<iostream>
#include<string>

using namespace std;

int main()
{
	string a, b;
	int n;

	cin >> n;
	cin >> a;
	cin >> b;

	int e = 0;

	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) { e++; }
	}

	cout << e << endl;

	return 0;
}

