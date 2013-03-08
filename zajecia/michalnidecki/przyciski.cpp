#include<iostream>
using namespace std;
int main()
{
	int n, m, p, max;
	cin >> n >> m;
	int t[n];
	for(int i = 0; i < n; i++){t[i] = 0;}
	for(int i = 0; i < m; i++){
		cin >> p;
		if(p > n){
			max = 0;
			for(int j = 0; j < n; j++){
				if(t[j] > max){max = t[j];}
			}
			for(int j = 0; j < n; j++){
				t[j] = max;
			}
		}
		else{
			t[p - 1]++;
		}
	}
	for(int i = 0; i < n; i++)cout << t[i] << " ";
	cout << "\n";
}
