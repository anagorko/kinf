#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[n];
	int najmniej,max=0,zmienna,kom;
	for(int i=0;i<n;i++){
		cin>>t[i];
		if(t[i]>max){max=t[i];}
	}
	for(int i=0;i<n;i++){
		najmniej=max+1;
        	for(int a=i;a<n;a++){
                	if(t[a]<najmniej){
                        	najmniej=t[a];
                        	kom=a;
               		 }
        	}
		zmienna=t[i];
		t[i]=najmniej;
		t[kom]=zmienna;
	}
	for(int i=0;i<n;i++){
		cout<<t[i]<<" ";
	}
	cout<<"\n";
return 0;
}

