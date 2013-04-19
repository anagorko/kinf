#include <iostream> /*Napisz program obliczający sumę 10 liczb podanych przez użytkownika. Przetestuj program Następnie zmień go tak, by obliczał sumę 20 liczb podanych przez użytkownika.*/
using namespace std;
int main()
{
	int suma = 0;
	for (int a=0; a < 10; a++)
	{
		int b;
		cout<<"podaj  liczbę:\n";
		cin>> b;
		suma = b + suma;
	}
	cout<<suma<<endl;
	
	cout<<"zmodyfikowana wersja:\n";
	
	int suma2 = 0;
	for (int c=0; c < 20; c++)
	{
		int d;
		cout<<"podaj  liczbę:\n";
		cin>> d;
		suma = d + suma2;
	}
	cout<<suma2<<endl;
}
