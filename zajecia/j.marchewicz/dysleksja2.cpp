#include <iostream>
#include <string>

using namespace std;
int main()
{
	int n;	
	string r;
	string t;

	cin >> n;
	cin >> r;
	cin >> t;

	int wynik = 0;
	for(int i= 0; i < n; i++){

	if(t[i] != r[i]){ wynik++; }}


	cout << wynik;
}

