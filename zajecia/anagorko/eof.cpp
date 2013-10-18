#include<iostream>
using namespace std;

int main()
{
	int x;
	int s = 0;
	while (!cin.eof()) {
		cin >> x;

		if (cin.eof()) break;

		s += x;
	}

	cout << s << endl;

	return 0;
}

