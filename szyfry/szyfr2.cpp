#include<iostream>
#include<string>

using namespace std;

int main()
{
	string s;

	cout << "Podaj tekst do zaszyfrowania: ";
	getline(cin, s);

	cout << "Zaszyfrowany tekst: ";

	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	string doidehw = "defghijklmnopqrstuvwxyzabc";

	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		char f = '*';

		for (int j = 0; j < alfabet.length(); j++) {
			if (alfabet[j] == c) {
				f = doidehw[j];
			}
		}

		cout << f;
	}
	cout << endl;

	return 0;
}
