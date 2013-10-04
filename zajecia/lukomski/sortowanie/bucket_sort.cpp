#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n];
	int max=0;
	for(int i=0;i<n;i++){
		cin>>t[i];
		if(t[i]>max){max=t[i];}
	}
	int ta[max];
	for(int i=0;i<n;i++){
		ta[i]=0;
	}
	for(int i=0;i<n;i++){
		ta[t[i]]++;
	}
	for(int i=0;i<=max;i++){
		for(int a=0;a<ta[i];a++){
			cout<<i<<" ";
		}
	}
	return 0;
}
