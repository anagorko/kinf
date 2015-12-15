#include<iostream>
using namespace std;

int main(){
	string s;
	int a, i=1;
	cin >> a;
	cin >> s;
	while(i<a && i!=a){
		cout << s[i];
		i++;	
		i++;
	}
	cout << endl;
	return 0;
}
