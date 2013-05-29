#include<iostream>
using namespace std;
int main(){
	long long int n;
	cin>>n;
	long long int t[n],zmienna;
	for(int i=0;i<n;i++){
		cin>>t[i];
	}
	for(int i=0;i<n-1;i++){
		for(int a=i+1;a<n;a++){
			if(t[i]>t[a]){
				zmienna=t[a];
				t[a]=t[i];
				t[i]=zmienna;
			}
		}
	}
/////////////////////////////
	if(n%2!=0){
		cout<<t[n/2];
	}else{
		cout<<(t[n/2-1]+t[n/2])/2;
	}
return 0;
}
