#include <iostream> //Wczytaj dwie liczby i wypisz najpierw mniejszą, a potem większą z nich.
using namespace std;

int main()
{
	cout<<"za chwilę podasz dwie liczby, a program wypisze je od mniajszej do większej\n";
	
	float a,b;

	cout<<"podaj pierwszą liczbę: \n";
	cin>> a;

	cout<<"podaj drugą liczbę: \n";
	cin>> b;

	if (a>b)
   	{
		cout<< a <<","<< b << endl;
   	}
	else 
   	{
		cout<< b <<","<< a << endl;
   	}
}
