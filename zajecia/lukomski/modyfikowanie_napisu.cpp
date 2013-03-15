#include<iostream>
using namespace std;
int main(){
	string s;
	char s1,a,b;
	int n;
	getline(cin, s);
	int kon=s.length();
	for(int i=0;;i=i+2){
		cin>>s1;
		if(s1=='Z'){
			cin>>a>>b;
			for(int q=0;q<kon;q++){
				if(s[q]==a){s[q]=b;}
			}
		}
		if(s1=='D'){
			cin>>a;
			s[kon]=a;
			kon++;
		}
		if(s1=='U'){
			cin>>n;
			kon=kon-n;
		}
		if(s1=='N'){break;}
	}
	for(int i=0;i<kon;i++){
		cout<<s[i];
	}
return 0;
}
