#include<iostream>
#include<string>

using namespace std;

int main()
{
	string s;

	cout << "Podaj tekst do zaszyfrowania: ";
	getline(cin, s);

	cout << "Zaszyfrowany tekst: ";

	for (int i = 0; i < s.length(); i++) {
		char c = s[i];

		c = c + 3;
		if (c > 'z') { c = c - 26; }

		cout << c;
	}
	cout << endl;

	return 0;
}
