#include <iostream>
#include <string>

using namespace std;
int main()
{
	int n;	
	string a;
	string b;

	cin >> n;
	cin >> a;
	cin >> b;

	int wynik = 0;
	for(int i= 0; i < n; i++){

	if(b[i] != a[i]){ wynik++; }}


	cout << wynik;
}

