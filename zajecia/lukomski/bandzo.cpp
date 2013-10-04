#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n][2];
	for(int i=0;i<n;i++){
		cin>>t[i][0];
		cin>>t[i][1];
	}
	int ta[n*2];
	int as,is;
	int kon=0;
	for(int q=0;q<n*2;q++){
		int mini=1000000000;
		for(int i=1;i>=0;i--){
			for(int a=0;a<n;a++){
				if(t[a][i]!=1000000001 && t[a][i]<mini){mini=t[a][i];as=a;is=i;}
			}
		}
		if(is==0){
			ta[kon]=t[as][is];
		}else{
			ta[kon]=t[as][is]-t[as][is]*2;
		}
		t[as][is]=1000000001;
		kon++;
	}
	int w=0;
	int max=0;
	for(int i=0;i<2*n;i++){
		if(ta[i]>0){w++;
		}else{w--;}
		if(w>max){max=w;}
	}
	cout<<max<<endl;
return 0;
}
