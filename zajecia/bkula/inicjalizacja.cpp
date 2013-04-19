#include <iostream>
using namespace std;
int main (){

int n;

cin>>n;

int z[n];

for (int i = 0; i != n; i++){
	z[i] = i;
}

for (int i = 0; i != n; i++){
	z[i] = i + 6;
}

for (int i = 0; i != n; i++){
	z[i] = (i + 1) * 4;
}

for (int i = 0; i != n; i++){
	z[i] = i * i;
}

for (int i = 0; i != n; i++){
	z[i] = i + 3;
}

return 0;
}
