#include<iostream>
using namespace std;
int main() {
int n = 0;
cin >> n;
int x[n];
for (int i = 0;i < n;i++){
	cin >> x[i];
}
for (int i = 0; i < n;i++){
	if (x[i] % 5 != 0){
		cout<< x[i];
	}
	if (i < n-1){
		cout << " ";
	}
}
cout << endl;



}
