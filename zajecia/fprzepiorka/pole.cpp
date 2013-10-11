#include <iostream>
using namespace std;
int main ()
{
int t[10], w = 0;
	for (int i = 0; i < 10; i++) {
		cin >> t[i];
		if (t[i] >= 1000) {
			t[i] = 0;
		}
	}
	for (int a = 0; a < 10; a++) {
		t[a] = t[a] % 42;
	}
	for (int w = 0; w < 43; w++) {
		for (int e = 0; e < 10; e++) {
			if (t[e] == w) {
				w = w + 1;
			} 
		}
	}
cout << w << endl;
}
