#include<iostream>
using namespace std;
string reverse(string &s){
	char s1;
	for(int i=0;i<s.length()/2;i++){
		s1=s[i];
		s[i]=s[s.length()-i-1];
		s[s.length()-i-1]=s1;
	}
return s;
}
int main(){
	string s;
	cin>>s;
	cout<<reverse(s)<<"\n";
return 0;
}
