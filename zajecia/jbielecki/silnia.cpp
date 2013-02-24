#include <iostream>

using namespace std;
 
int main()
{
	int x;
	cin >> x;
	
	long long int silnia=1;
	
	for (int i=  1; i<=x; i++) 
	silnia *= i; 
	cout << silnia;
 return 0;
}
