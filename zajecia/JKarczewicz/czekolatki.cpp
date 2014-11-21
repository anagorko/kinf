#include <iostream>
using namespace std;
int main()
{
int a, b, c, d;
cout << "Podaj ilość czekoladek w pionie w pierwszej czekoladzie: ";
cin >> a;
cout << "Podaj ilość czekoladek w poziomie w pierwszej czekoladzie: ";
cin >> b;
cout << "Podaj ilość czekoladek w pionie w drugiej czekoladzie: ";
cin >> c;
cout << "Podaj ilość czekoladek w poziomie w drugiej czekoladzie: ";
cin >> d;
cout << "Suma wszystkich kostek czekolady wynosi " << (a*b)+(c*d) << "\n" ;
return 0;
}
