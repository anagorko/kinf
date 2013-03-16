#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	string w,k;
	for(int i=0;i<n;i++){
		cin>>w;
		cin>>k;
		
		if((((int)w[w.length()-1]-48)%2==0 && ((int)k[k.length()-1]-48)%2==0) || (((int)w[w.length()-1]-48)%2==1 && (((int)k[k.length()-1]-48)%2==1))){cout<<"C"<<endl;continue;}
		if((((int)w[w.length()-1]-48)%2==0 && ((int)k[k.length()-1]-48)%2==1) || (((int)w[w.length()-1]-48)%2==1 && (((int)k[k.length()-1]-48)%2==0))){cout<<"B"<<endl;continue;}
	}
return 0;
}

