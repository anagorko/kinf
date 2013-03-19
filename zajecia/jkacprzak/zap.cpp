#include <iostream>
#include <cmath>         
using namespace std;
int main(){
int n, szer, wys;

	cin >> n;

int zap[n];

	cin >> wys;
	cin >> szer;



	for(int i = 0; i < n; i++){

	cin >> zap[i];

	}

	for(int i = 0; i < n; i++){

		if(zap[i] <= szer || zap[i] <= wys || zap[i] <= sqrt((szer * szer) + (wys * wys) )){

			cout << "TAK" << endl;

	}else{
		cout << "NIE" << endl;
	}
	}

}
