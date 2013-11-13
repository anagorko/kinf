#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	bool n1[n+1];
	int licz=0;
	for(int i=0;i<=n;i++){n1[i]=true;}
	for(int i=1;i<=n;i++){
		if(!n1[i]){continue;}
		if(n%i!=0){
			for(int a=i;a<n;a+=i){
				n1[a]=false;
			}
		}
		if(n%i==0){
			licz++;
		}
	}
	cout<<licz<<"\n";
	return 0;
	}
