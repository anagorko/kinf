#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int alfabet['z'-'a'+1];
	string alf="abcdefghijklmnopqrstuvwxyz";
	for(int i=0;i<'z'-'a'+1;i++){
		alfabet[i]=0;
	}
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		for(int a=0;a<s.length();a++){
			alfabet[s[a]-'a']++;
		}
	}
	for(int i=0;i<'z'-'a'+1;i++){
		if(alfabet[i]!=0){
			cout<<alf[i]<<" "<<alfabet[i]<<"\n";
		}
	}
	return 0;
}
