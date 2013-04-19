#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n][2];
	for(int i=0;i<n;i++){
		cin>>t[i][0];
		cin>>t[i][1];
		t[i][1]=t[i][1]-t[i][0];
	}
	for(int i=0;i<n;i++){
		if(t[i][1]>0){
			if(t[(i+1)%n][1]<0){
				if(t[(i+1)%n][1]+t[i][1]==0){
					t[i][1]=0;
					t[(i+1)%n][1]=0;
					licz++;
					continue;
				}
				if(t[(i+1)%n][1]+t[i][1]<0){
					t[(i+1)%n][1]=t[(i+1)%n][1]+t[i][1];
					t[i][1]=0;
					licz
				}
			
