#include<iostream>
using namespace std;
int main(){
	long long int n;
	cin>>n;
	long long int licznik=0;
	bool pierwszyd=false;
	long long int id=0;
	string t;
	cin>>t;
	if(t[0]=='D'){pierwszyd=true;id++;}
	for(long long int i=1;i<n;i++){
		if(pierwszyd && t[i]!='D'){pierwszyd=false;}
		if(pierwszyd && t[i]=='D'){id++;}
		if(t[i]=='D' && t[i-1]=='C'){
			t[id]='D';
			t[i]='C';
			licznik=licznik+2*(i-id);
			id++;
		}
	}
	cout<<licznik<<"\n";
	return 0;
}
