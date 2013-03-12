
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
