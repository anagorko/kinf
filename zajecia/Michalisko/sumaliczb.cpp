#include<iostream>
using namespace std;

int main(){
	long long int b;
	for (long long int a=0; a<1000000000; a++)
	{
		if (a%2==0){
		} else {
			b=a+b;
		}
	}
	cout << b <<endl;
}
