#include <iostream>
using namespace std;
int main(){

int n;
int z;

bool k = false;
bool p = false;

cin>>n;

int l[n];

for (int i = 0; i != n; i++){
	cin>>l[i];
}

int w[n];

for (int i = 0; i != n; i++){
	w[i] = 1000000001;
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

	for (int i = 0; i != n - 1; i++){
		if (l[i] = l[i + 1]){
			for (int j = 0; j != n; j++){
				if (l[i] = w[j]){
					p = true;
					break;
				}
			}
			if (p == false){
				w[i] = l[i];
			}
		}
	}

for (int i = 0; i != n; i++){
	if (w[i] != 1000000001) cout<<w[i]<<" ";
}

return 0;
}
