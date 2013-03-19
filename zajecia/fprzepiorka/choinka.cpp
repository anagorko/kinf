
#include <iostream>
using namespace std;
int main() {
int n;
cin >> n;
for (int a = n; a > 0; a--) {
	for (int w = 1; w < a; w++){
		cout << ".";
	}
	for (int i = 2 * (n - a); i >= 0; i--){
		cout << "A";
	}
		cout << endl;	
}
for (int w = 0; w < n - 2; w++){
		cout << ".";
	}
cout << "HHH" << endl;
}
