#include<iostream>
using namespace std;
int main (){
long long int suma = 0;
	for (int i = 0; int  i < 1000; i++ ){

		if ((i % 3 == 0) || (i % 5 == 0)){
			suma += i;
		}
	}

	cout << suma << endl;
return 0;
}
