#include<iostream>
using namespace std;
int main(){
	int liczb=0;
	int ile;
	cin>>ile;
	string slowo;
	cin>>slowo;
	int odp=0;
	int cyfra;
	for(int r=0;r<ile;r++){
		if(slowo[r]<'0' || slowo[r]>'9'){
			odp=odp+liczb;
			liczb=0;
		}
		else{
			cyfra=(int)slowo[r]-48;
			liczb=liczb*10+cyfra;
		}
	}
	odp=odp+liczb;
	cout<<odp;
return 0;
}
