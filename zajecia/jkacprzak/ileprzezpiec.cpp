#include<iostream>
using namespace std;
int main() {
int n = 0;
cin >> n;
int x[n], wynik = 0;
for (int i = 0;i < n;i++){
	cin >> x[i];
}
for (int i = 0; i < n;i++){
	if (x[i] % 5 == 0){
		wynik += 1;
	}
	
}
cout << wynik <<endl;



}
