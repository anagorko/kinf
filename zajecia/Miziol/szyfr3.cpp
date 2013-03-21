#include<iostream>
#include<string>

using namespace std;

int main()
{
	string s,k;

	cout << "Podaj tekst do zaszyfrowania: "; getline(cin, s);
	cout << "Podaj klucz (hasło): "; getline(cin, k);

	cout << "Zaszyfrowany tekst: ";

	for (int i = 0; i < s.length(); i++) {
		unsigned char c = s[i];
		unsigned char p = k[i % k.length()] - 'a';

		c = c + p;
		if (c > 'z') { c = c - 26; }

		cout << c;
	}
	cout << endl;

	return 0;
}
