#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	long long int oldn=n;
	long long int  w=1,p=2;
	while(p*p<=n){
		if(n%p!=0){
			p++;
			continue;
		}else{
			if(n%(p*p)!=0){
				w=w*p;
				n=n/p;
				continue;
			}
			if(n%(p*p)==0){
				n=n/(p*p);
			}
		}
	}
	if(n>0){w=w*n;}
	cout<<w*oldn<<endl;
	return 0;
}
