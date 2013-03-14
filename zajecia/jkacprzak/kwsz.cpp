#include<iostream>
#include <math.h>
using namespace std;
int main (){
int n;
long long int x [n];

	cin >> n;


	for (long long int i = 1; i <= n; i++){
		
		cin >> x [i];
		
	}

	for (long long int i = 1; i <= n; i++){
		
		cout << pow(x[i],2) << "  ";
		
	}

	cout << "\n";

	for (long long int i = 1; i <= n; i++){
		
		cout << pow(x[i],3) << "  ";
		
	}

	cout << "\n";
	
return 0;
}
