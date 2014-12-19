#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	long long int a,i;
	cin >> a ;
	for(i = sqrt(2 * a); (i * (i+1))/2 >= a; i--);
	cout << i+1;
	return 0;
}

