#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n];
	max=0;
	for(int i=0;i<n;i++){
		cin>>t[i];
		if(t[i]>max){max=t[i];}
	}
	int ta[max];
	for(int i=0;i<n;i++){
		
