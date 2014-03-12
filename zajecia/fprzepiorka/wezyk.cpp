#include <iostream>
using namespace std;
int main() {
int n;
cin >> n;
int tab[n][n];
	for (int i = 0; i < n; i++){
		if ((i + 1) % 2 == 1) {
			for(int e = 1; e <= n; e++) {
				tab [e - 1][i] = (i + 1) * n - n + e;
			}
		}
		if ((i + 1) % 2 == 0) {
			for (int o = 0, r = ((i + 1) * n); o < n; o++) {
				tab [o][i] = (i + 1) * n - n + r;
			}
		}
	}
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < n; b++) {
			cout << tab [b][a]<< " ";
		}
		cout << "" << endl;
	}
}
