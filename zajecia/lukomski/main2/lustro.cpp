#include<iostream>
using namespace std;
int main(){
	int n,l=0;
	cin>>n;
	while(n>0){
		if(l==0 && n%10==0){
			n=n/10;
			continue;
		}
		l=10 * l + n%10;
		n=n/10;
	}
	cout<<l<<endl;
}
