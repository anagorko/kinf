#include<iostream>
using namespace std;
int main(){
	int m;
	cin>>m;
	string s[m];
	char max;
	for(int i=0;i<m;i++){
		cin>>s[i];
	}
	if(s[0][1]=='>'){
		max=s[0][0];
	}
	if(s[0][1]=='<'){
		max=s[0][2];
	}
	for(int a=1;a<m;a++){
		if(s[a][0]==max && s[a][1]=='<'){
			max=s[a][2];
			a=1;
			break;
		}
		if(s[a][2]==max && s[a][1]=='>'){
			max=s[a][0];
			a=1;
			break;
		}
	}
	cout<<max<<endl;
return 0;
}
