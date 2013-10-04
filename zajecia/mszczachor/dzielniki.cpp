//Dzielniki Marcin Szcząchor
#include <iostream>
using namespace std;
int main() {
int i;
int n = 1;
int a = 0;
cout << "Wpisz liczbę:" << endl;
cin >> i;
for(;n <= i;n++)
{
	if(i%n == 0) a++;
}
cout << "Liczba dzielników liczby " << i << " wynosi "<< a << "." << endl; 
return 0;
}
