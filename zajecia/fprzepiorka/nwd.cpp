#include <iostream>
using namespace std;

int nwd (int a, int b)
{
if (a > b) {
	int r = b;
	b = a;
	a = r;
}

int c = 0;
	while (b != 0) {
		c = (b % a);
		a = b;
		b = c;
	}
return a;
}

int main ()
{
int n = 0, w = 1;
cin >> n;
int t[n];

	for (int i = 0; i < n; i++) {
		cin >> t[i];
	}
	
w = nwd(t[0], t[1]);

	for (int i = 2; i < n; i++) {
		w = nwd(w, t[i]);
	}
	
cout << w << endl;
}
