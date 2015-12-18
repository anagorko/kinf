#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n];
	for(int i=0;i<n;i++){
		cin>>t[i];
		if(i%2==0)cout<<t[i]<<" ";
	}
	cout<<"\n";
	for(int i=1;i<n;i+=2){
		cout<<t[i]<<" ";
	}
}
