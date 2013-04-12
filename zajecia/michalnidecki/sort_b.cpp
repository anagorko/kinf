#include<iostream>
using namespace std;
int main()
{
	int n, w, z;
	cin >> n;
	int t[n];
	for(int i = 0; i < n; i++){
		cin >> t[i];
	}
	while(true){
		w = 0;
		for(int i = 0; i < n - 1; i++){
			if(t[i] > t[i + 1]){
				z = t[i + 1];
				t[i + 1] = t[i];
				t[i] = z;
				w++;
			}
		}
		if(w == 0){break;}
	}
	for(int i = 0; i < n; i++){
		cout << t[i] << " ";
	}
	cout << "\n";
}
