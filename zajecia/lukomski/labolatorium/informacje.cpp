#include<iostream>
using namespace std;
int main(){
	int n,a;
	cin>>n>>a;
	int t[n];
	for(int i=n-1;i>=0;i--){
		cin>>t[i];
	}
	for(int i=0;i<n;i++){
		cout<<t[i]+a<<" ";
	}
	cout<<"\n";
	return 0;
}
