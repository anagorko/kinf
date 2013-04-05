#include <iostream>
#include <string>
using namespace std;
int main (){

string t;
int n, w = 0;

cin>>n;
cin>>t;

for (int i = 0; n >= i; i++){
	if (t[i+1] != t[i]) i++;
	w++;
}

cout<<w;

return 0;
}
