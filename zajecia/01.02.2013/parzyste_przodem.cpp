#include <iostream>

using namespace std;

int main()
{

int n[20];

for(int i=0; i<20; i++) {
		
		cin >> n[i];
}

for(int x=19; x>=0; x--) {
	if(n[x] % 2 == 0){	
	cout << n[x]<<" ";}
}

for(int x=19; x>=0; x--) {
	if(n[x] % 2 != 0){	
	cout << n[x]<<" ";}
}
return 0;
}
