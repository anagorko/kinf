#include<iostream>
using namespace std;
int main() {
string n;
cin >> n;
for (int i = 1;i < n.length() ;i++ ){
	if (i % 2 == 0){
		cout << n[i];
	}
}
cout << endl;
}
