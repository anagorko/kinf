// (C) Janek Bielecki
#include <iostream>
using namespace std;

int main() {

int n;

cin >> n;
n = n - 1;

for (int i = n; i >= 0; i--) {

	for (int j = 0; j <= i; j++)

	cout << " ";

	for (int a = 2 * (n - i); a >= 0; a--)

	cout << "*";
	cout << endl; 
}
for (int i = n + 1; i >= 0; i--) {

	for (int j = 1; j <= i; j++)
	cout << " ";
	for (int a = 2 * (n + 1 - i); a >= 0; a--)
	cout << "*";
	cout << endl; 
}
}
