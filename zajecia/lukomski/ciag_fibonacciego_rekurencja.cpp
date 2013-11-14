#include<iostream>
using namespace std;
long long int w=0;
int fibonacci(int n){
	w=w+n;
	n--;
	if(n>0){
		fibonacci(n);
	}
	return w;
}
int main(){
	cout<<"do jakiej liczby obliczyc ciag fibonacciego?";
	long long int n;
	cin>>n;
	cout<<fibonacci(n)<<"\n";
	return 0;
}
