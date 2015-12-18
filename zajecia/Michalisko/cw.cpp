#include<iostream>
using namespace std;

int main(){
	int x, y;
	cin >> x >> y;
	if (x > 0 & y > 0){
		cout << "Punkt znajduje się w kwadracie 'B'" << endl;
	}
	else if (x > 0 & y < 0){
		cout << "Punkt znajduje się w kwadracie 'C'" << endl;
	}
	else if (x < 0 & y < 0){
		cout << "Punkt znajduje się w kwadracie 'D'" << endl;
	}
	else if (x < 0 & y > 0){
		cout << "Punkt znajduje się w kwadracie 'A'" << endl;
	}
}
