#include <iostream>
#include <string>
using namespace std;
int main (){

string t;
int d, i;

cin>>t;

d = t.length();

i = 1;

for (; i != d; i++){
	if ((i % 4) == 1) cout<<t[i];
	else cout<<".";
}

cout<<endl;

i = 1;

for (; i != d; i++){
	if ((i % 2) == 0) cout<<t[i];
        else cout<<".";
}

cout<<endl;

i = 1;

for (; i != d; i++){
	if ((i % 4) == 3) cout<<t[i];
       	else cout<<".";
}

cout<<endl;

return 0;
}
