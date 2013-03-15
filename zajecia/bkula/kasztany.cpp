#include <iostream>
using namespace std;
int main (){

int d;
int n[2000];
int a[1000];
int w[2000];

cin>>d;

for (int i = 0; i != d; i++){
	cin>>n[i];
	w[i] =0;
	for (int j = 0; j != n[i]; j++){
		cin>>a[j];
		w[i] += a[j]; 
	}
}

for (int k = 0; k != d; k++){
	cout<<w[k]<<endl;
}

return 0;
}
