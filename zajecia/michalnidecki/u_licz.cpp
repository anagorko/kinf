#include<iostream>
using namespace std;
int main()
{
	int n, a, j, d, w = 0;
	cin >> n;
	char t[n];
	for(int i = 0; i < n; i++){
		cin >> t[i];
	}
	for(int i = 0; i < n; i++){
		if(t[i] >= 48 && t[i] <= 57){
			d = 1;
			for(a = 0; t[i + a] >= 48 && t[i + a] <= 57; a++);
			for(int j = 1; j < a; j++){d *= 10;}
			w += (t[i] - 48) * d;
		}
	}
	cout << w << "\n";
}
