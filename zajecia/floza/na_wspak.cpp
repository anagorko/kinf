#include <iostream>
using namespace std;
int main(){

int m[20];

for (int i = 0; i != 20; i++){
	cin>>m[i];
}

for (int i = 19; i >= 0; i--){
	cout<<m[i]<<" ";
}
return 0;
}
