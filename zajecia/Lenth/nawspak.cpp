#include <iostream>
#include <string>
using namespace std;
int main()
{
	string a;
	cin >> a;
	string b( a.rbegin(), a.rend() );
	cout << b << "\n";
}
