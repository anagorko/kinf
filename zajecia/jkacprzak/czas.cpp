// (c) by Jan Kacprzak

#include<iostream>
using namespace std;
int main () {
double droga, predkosc, czas, sec = 0, min = 0, gdz = 0 ;
cin >> droga >> predkosc;
czas = droga / predkosc;
sec = czas;
	for (; sec >= 59; ){
	
		sec -= 60;
		min  += 1;
	}	
	for (; min >= 59; ){
	
		min -= 60;
		gdz  += 1;
	}

	if (gdz <= 9)cout << 0;

	cout << gdz << ":"; 

	if (min <= 9)cout << 0;
	cout<< min << ":";

	if (sec <= 9)cout << 0;

	cout << sec << endl;

}

