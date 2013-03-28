#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n][2];
	int ta[n];
	for(int i=0;i<n;i++){
		cin>>t[i][0];
		cin>>t[i][1];
	}
	int licz=0;
	for(int i=0;i<n;i++){
		if(t[i][0]==0){continue;}
		for(int a=0;a<n;a++){
			if(t[a][0]==0){continue;}
			if(t[a][0]>t[i][0] && t[a][1]<t[i][1]){
				licz++;
				ta[licz-1]=a+1;
				t[a][0]=0;
			}
		}
	}
	cout<<licz<<"\n";
	    for(int i=0;i<licz;i++){
			cout<<ta[i]<<" ";
	    }
}
