#include <iostream>
using namespace std;
int main(){
int n = 6;
int dobre[6] = { 1, 1, 2, 2, 2, 8 };
int zle[6];
	for(int i = 0; i < n; i++){
	cin >> zle[i];
	}
	for(int i = 0; i < n; i++){
		cout << dobre[i] - zle[i] << " ";
	}
}
