#include<iostream>
using namespace std;
int main(){
	long long int n,l=1;
	cin>>n;
	do{
		cout<<l<<"\n";
		l*=2;
	}while(l <= n);
	return 0;
}
