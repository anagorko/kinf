#include<iostream>
using namespace std;

int main(){
int n;
cin >> n;
for (int a; a<n; a++){
	for (int i=0; i<n; i++){
	cout << "#.";
}
cout << "\n";
	for (int b=0; b<n; b++){
	cout << ".#";
}
cout << "\n";
}
}
