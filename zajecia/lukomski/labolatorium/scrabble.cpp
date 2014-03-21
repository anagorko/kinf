#include <iostream>
using namespace std;
int main(){
		string s;
		cin>>s;
		//getline(cin, s);
		char is[s.length()+1];
			for(int i=0;i<s.length()+1;i++){
				is[i]='0';
			}
		int pocz=0;
		int ls=0;	
		int kon=s.length()-1;
		while(ls<=s.length()){
				is[ls]=s[pocz];
				pocz++;
				ls++;
				is[ls]=s[kon];
				ls++;
				kon--;
		}
		for(int i=0;i<s.length();i++){
			cout<<is[i];
		}
		cout<<"\n";
	return 0;
	}