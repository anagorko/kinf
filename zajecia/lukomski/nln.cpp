#include<iostream>
using namespace std;
int main(){
	int a,max=0,nr=0;
	for(int i=1;i<=10;i++){
		cin>>a;
		if(a>max){max=a;nr=i;}
	}
	cout<<nr<<endl;
return 0;
}
