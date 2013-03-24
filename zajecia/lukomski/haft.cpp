#include<iostream>
using namespace std;
int main(){
	string s;
	cin>>s;
	int w;
	cin>>w;
	char t[s.length()*w*2][s.length()*w*2];
	for(int i=0;i<s.length()*w*2;i++){
		for(int a=i;a<s.length()*w*2-i;a++){
			for(int q=i;q<s.length()*w*2-i;q++){
				t[a][q]=s[i%s.length()];
			}
		}
	}
	for(int i=0;i<s.length()*w*2;i++){
		for(int a=0;a<s.length()*w*2;a++){
			cout<<t[i][a];
		}
		cout<<"\n";
	}
return 0;
}
