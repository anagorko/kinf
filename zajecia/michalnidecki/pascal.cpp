#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int t[n][n];
	t[0][0] = 1;
	for(int i = 1; i < n; i++){
		t[i][0] = 1; t[i][i] = 1;
		for(int j = 1; j <= i - 1; j++){
			t[i][j] = t[i - 1][j - 1] + t[i-1][j];
		}
	}
	for(int i = 0; i < n; i++){
	for(int j = 0; j <= i; j++){
		cout << t[i][j] << " ";
	}
		cout << "\n";
	}
}
