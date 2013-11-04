#include<iostream>
using namespace std;
int main ()
{
	float wzrost;
	float waga;
	float bmi;
	
	cout << "Podaj swoj wzrost w centymetrach: ";
	cin >> wzrost;
	cout << "Podaj swoja wage w kilogramach: ";
	cin >> waga;
	
	bmi = waga / ((wzrost/100) * (wzrost/100));
	
	cout << "Twoje BMI wynosi " << bmi << ", co oznacza ";
	
	if(bmi < 16)cout << "wyglodzenie." << endl;
	if((bmi >= 16) && (bmi < 17))cout << "wychudzenie." << endl;
	if((bmi >= 17) && (bmi < 18.5))cout << "niedowage." << endl;
	if((bmi >= 18.5) && (bmi < 25))cout << "wartosc prawidlowa." << endl;
	if((bmi >= 25) && (bmi < 30))cout << "nadwage." << endl;
	if((bmi >= 30) && (bmi < 35))cout << "otylosc." << endl;
	if((bmi >= 35) && (bmi < 40))cout << "otylosc kliniczna." << endl;
	if(bmi >= 40)cout << "skrajna otylosc." << endl;

	return 0;

}
