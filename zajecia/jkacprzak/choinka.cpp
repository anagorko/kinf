// (c) copyright by Jan Kacprzak


#include<iostream>
using namespace std;
int main () {
int n;
int y = n;
int r;
int rx;
int z;
int x = 3;
int nx = n*2+1;
	cin >> n;
	while (x > 0){
		r = 1;
		while (n > 0){
			y = n;
			rx = r;
			while (y > 1 ){
				cout << ".";
				y -= 1;
			}
			while (rx > 0){
				cout << "A";
				rx -= 1;
			}
			cout << "\n";		
			n -= 1;
			r += 2; 
		}
		x -=1;
	}
	z = (n*2+1)/2;
	for (int i = 0; i <= z ;i++){
		cout << ".";
	}
	cout << "HHH\n";
return 0;
}
