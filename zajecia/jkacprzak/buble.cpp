#include<iostream>
using namespace std;
int main (){
int n;
cin >> n;
int x[n];
int o;
int prawda;
for (int i = 0; i < n; i++){
	cin >> x[i];
}
bool koniec = false;
while (!koniec) {
  koniec = true;
  for (int k = 0; k < n; k++){
	if (x[k] > x[k+1]) {
		prawda = x[k];
		x[k] = x[k+1];
		x[k+1] = prawda;
		koniec = false;
		
		
	}}
}
for (int i = 0; i < n; i++){
	cout << x[i]<< "  ";
}	
cout << endl;

return 0;
}
