#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		int n;
		cin>>n;
		string s;
		cin>>s;
		if(n%2!=0){cout<<"NIEMOZLIWE\n";continue;}
		int o=0,z=0;
		int l;
		for(int i=0;i<n;i++){
			if(s[i]=='(')o++;
			if(s[i]==')'){
				z++;
				if(o-z<0){l++;z=0;}
			}
		}
	

	}
	return 0;
}
