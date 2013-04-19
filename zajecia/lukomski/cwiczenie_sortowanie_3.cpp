#include<iostream>
using namespace std;
int main(){
	long long int n;
	cin>>n;
	long long int t[n];
	for(int i=0;i<n;i++){
		cin>>t[i];
	}
	if(n%2!=0){
		cout<<t[n/2];
	}else{
		cout<<(t[n/2-1]+t[n/2])/2;
	}
return 0;
}
