#include <iostream>
#include <string>
using namespace std;
int main (){

int n = 0, b = 0;
string t1, t2;

cin>>n;
cin>>t1;
cin>>t2;

//_______________

for (; n != 0; n--){

	if (t1[n] != t2[n]) b++;
}

//_______________

cout<<b;

return 0;
}
