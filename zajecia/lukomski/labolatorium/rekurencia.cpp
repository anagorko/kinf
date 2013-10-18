#include<iostream>
using namespace std;
int main(){
	long long int n;
	cin>>n;
	if(n==1 || n==2){cout<<n<<"\n";return 0;}
	int t[n+1];
	t[1]=1;
	t[2]=2;
	for(int i=3;i<=n;i++){
		t[i]=t[i-2]+t[i-1]*t[i-1];
		t[i]=t[i]%7;
	}
	cout<<t[n]<<"\n";
	return 0;
}
