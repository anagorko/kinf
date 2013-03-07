
//
// Przyjmuje się, że pierwszym i drugim wyrazem ciągu Fibnoacciego jest 1, 1
// Po poprawieniu usterek usuń ten komentarz.
//
#include<iostream>
using namespace std;
int fibonacci(int n)
{
	int a = 0, b = 1, c;
	for(int i = 0; i < n; i++){
		c = a + b;
		a = b;
		b = c;
	}
	return a;
}
int main()
{
	int n;
	cin >> n;
	cout << fibonacci(n) << "\n";
}
