#include <iostream>
#include <string>
using namespace std;
int main(){
string s;
cin >> s;
int ss[200];
int rr[200];

	for(int i = s.length(); i > 0; i--){
	ss[i]=s[i];
	if(i == s.length()){ss[i] = 0;}
	}
	for(int j = 0; j < s.length(); j++){
	rr[j] = ss[j] * 2;
	if(ss[j] * 2 > 9){rr[j + 1] = rr[j + 1] + 1;}	
	}

	
		

}
