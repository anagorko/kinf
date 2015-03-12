#include<iostream>
using namespace std;
int main(){
	int n,x;
	cin>>n>>x;
	int p=-1,o=-1;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		if(a!=x)continue;
		if(p==-1){
			p=i;
			o=i;
		}else{
			o=i;
		}
	}
	cout<<p<<" "<<o<<endl;
}
