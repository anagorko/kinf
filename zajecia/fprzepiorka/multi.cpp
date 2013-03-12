#include <iostream>
using namespace std;
int main ()
{
long long int a, w = 0;
cin >> a;
  for (int b = a - 1; b > 0; b--) {
		if (b % 3 == 0 && b % 5 == 0) {
			w = w + b;
		}else{
			if (b % 3 == 0) {
				w = w + b;
			}
			if (b % 5 == 0) {
				w = w + b;
			}
		}
	}
cout << w << endl;
}
