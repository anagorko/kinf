<<<<<<< HEAD
#include <iostream>
using namespace std;
int main ()
{
int n, b, c, a, d, i = 1;
cin >> n;
c = 2 * n - 1;
d = n;
a = n;
c = b;
  while (n > 0) {
		d = a;
		while (d > 1) {
			cout << " " ;
			d--;
		}
		while (b > 0) {
			while (i < c) {
				cout << "*" ;
				i = i + 2;
			}
			cout << "" << endl;
		}
		n --;
	}
}            // wyniki pracy po 2 godzinach (bez przesady)
=======

#include <iostream>
using namespace std;
int main() {
int n;
cout << "podaj liczbę wierszy" << endl;
cin >> n;
n = n - 1;
for (int a = n; a >= 0; a--) {
  for (int w = 0; w <= a; w++){
		cout << " ";
	}
	for (int i = 2 * (n - a); i >= 0; i--){
		cout << "*";
	}
		cout << endl;	
}
for (int a = n + 1; a >= 0; a--) {
	for (int w = 1; w <= a; w++){
		cout << " ";
	}	
	for (int i = 2 * (n + 1 - a); i >= 0; i--){
		cout << "*";
	}	
	cout << endl; 
	
}
}
>>>>>>> ee59d19067288742bdc7018e6f2aceb5a5b4c3da
