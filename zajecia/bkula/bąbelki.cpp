#include <iostream>
using namespace std;
int main(){

int n;
int z;
bool k = false;

cin>>n;

int l[n];

for (int i = 0; i != n; i++){
	cin>>l[i];
}

for (; k != true;){
	k = true;
	for (int i = 0; i != n - 1; i++){
		if (l[i] > l[i + 1]){
			z = l[i];
			l[i] = l[i + 1];
			l[i + 1] = z;
			k = false;
		}
	}
}

for (int i = 0; i != n; i++){
	cout<<l[i];
}

return 0;
}
