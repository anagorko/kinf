#include <iostream>
using namespace std;
int main ()
{
long long int a2, w2 = 0;
float a, b, d, l, w = 0;
cout << "ile działań chcesz wykonać?" << endl;
cin >> d;
while (d > 0) {
  cout << "1 - dodaj; 2 - odejmij; 3 - pomnóz; 4 - podziel, 5 - potęga" << endl;
	cin >> b;
	w = 0;
	w2 = 0;
	a = 0;
	a2 = 0;
		if (b <= 5) {
			if (b == 1) {
				cout << "podaj liczbę liczb" << endl;
				cin >> l;
				cout << "podaj liczby" << endl;
				while (l > 0) {
					cin >> a;
			        	w = w + a;
					l--;
				}
				cout << "wynik to " << w << endl;
			}
			if (b == 2) {
				cout << "podaj liczbę liczb" << endl;
				cin >> l;
				cout << "podaj liczby" << endl;
				cin >> a;
				w = w + a;
				l--;
				while (l > 0) {
					cin >> a;
					w = w - a;
					l--;
				}
				cout << "wynik to " << w << endl;
			}
			if (b == 3) {
				w = w + 1;
				cout << "podaj liczbę liczb" << endl;
				cin >> l;
				cout << "podaj liczby" << endl;
				while (l > 0) {
					cin >> a;
					w = w * a;
					l--;
				}
				cout << "wynik to " << w << endl;
			}
			if (b == 4) {
				cout << "podaj liczbę liczb" << endl;
				cin >> l;
				cout << "podaj liczby" << endl;
				cin >> a;
				w = w + a;
				l--;
				while (l > 0) {
					cin >> a;
					w = w / a;
					l--;
				}
				cout << "wynik to " << w << endl;
			}
			if (b == 5) {
				w2 = w2 + 1;
				cout << "do której potęgi chcesz podnieść?" << endl;
				cin >> l;
				cout << "podaj liczbę" << endl;
				cin >> a2;
				while (l > 0) {
					w2 = w2 * a2;
					l--;
				}
				cout << "wynik to " << w2 << endl;
			}
		}else{
			cout << "nie ten level" << endl;
		}
		d--;
	}
}
