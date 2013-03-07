#include<iostream>
using namespace std;
int main () {
int n;
int y = n;
int r;
int rx;
int x = 3;
int nx = n*2+1;
	cin >> n;
	while (x > 0){
		r = 1;
		while (n > 0){
			y = n;
			rx = r;
			while (y > 0 ){
				cout << " ";
				y -= 1;
			}
			while (rx > 0){
				cout << "*";
				rx -= 1;
			}
			cout << "\n";		
			n -= 1;
			r += 2; 
		}
		x -=1;
	}

	

return 0;
}
