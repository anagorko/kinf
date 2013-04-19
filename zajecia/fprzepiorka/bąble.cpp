#include <iostream>
using namespace std;
int main()
{
int n;
cin >> n;
int tablica_frania[n];
	for (int i = n; i > 0; i--) {
		cin >> tablica_frania[i];
	}
	for (long long int a = n; a > 0; a--) {
		for (int i = n; i > 0; i--) {
			if (tablica_frania[n] != n - 1) {
				if (tablica_frania[i] > tablica_frania[i + 1]) {
					int x = tablica_frania[i];
					tablica_frania[i] = tablica_frania[i + 1];
					tablica_frania[i + 1] = x;
				}
			}
		}
	}
	for (int i = n; i > 0; i--) {
		cout << tablica_frania[i] << " ";
	}
	cout << endl;
}
