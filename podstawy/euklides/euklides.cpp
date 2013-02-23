#include<iostream>
using namespace std;

int NWD(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;

    if (a > b) {
        return NWD(a - b, b);
    } else {
        return NWD(a, b - a);
    }
}

int NWD2(int a, int b)
{
    while (a > 0 && b > 0) {
      if (a > b) {
          a = a - b;
      } else {
          b = b - a;
      }
    }
    if (a != 0) return a;
    if (b != 0) return b;
}

int NWD3(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;

    if (a > b) {
        return NWD(a % b, b);
    } else {
        return NWD(a, b % a);
    }
}

int main()
{
	int a, b;
	cin >> a >> b;

	cout << NWD(a,b) << " " << NWD2(a,b) << " " << NWD3(a,b) << endl;

	return 0;
}
