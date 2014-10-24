#include<iostream>
using namespace std;

int main()
{
int a, b, c, d;
cout << "Podaj liczbę czekoladek w wierszu z pierwszej czekolady: ";
cin >> a;
cout << "Podaj liczbę czekoladek w kolumnie z pierwszej czekolady: ";
cin >> b;
cout << "Podaj liczbę czekoladek w wierszu z drugiej czekolady: ";
cin >> c;
cout << "Podaj liczbę czekoladek w kolumine z drugiej czekolady: ";
cin >> d;
cout << "Liczba wszystkich czekoladek z obu czekolad to: " << ((a*b)+(c*d));
}
