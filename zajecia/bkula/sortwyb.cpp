#include <iostream>
using namespace std;
int main (){

int n, x = 1000000001;

cin>>n;

int z[n];
int b[n];

for (int i = 0; i != n; i++){
	cin>>z[i];
}

for (int i = 0; i != n; i++){
	for (int j = 0; j != n; i++){
		if (z[i] > z[j] && x > z[j]) x = z[j];
	}
	if (x != 1000000001) b[i] = x;
	x = 1000000001;
}

for (int i = 0; i != n; i++){
	cin>>z[i];
}

for (int i = 0; i != n; i++){
	cout<<b[i]<<endl;
}

return 0;
}
