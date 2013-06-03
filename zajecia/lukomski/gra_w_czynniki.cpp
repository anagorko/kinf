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
	ta[0]=0;
	ta[1]=0;
	for(int i=2;i<max;i++){
		ta[i]=0;
		for(int a=2;a<=(i+1)/2;a++){
			if((i+1)%a==0 && ta[i-a]==0){ta[i]=1;break;}
		}
	}
	for(int i=0;i<n;i++){
		if(ta[t[i]-1]==1){cout<<"MAGDA\n";
		}else{
			cout<<"BARTEK\n";
		}
	}
	return 0;
}
