#include <iostream>
using namespace std;


int main()
{
int  a, b, c;
cout << "Jaki jest bok podstawy prostopadłościanu: ";
cin >> a;
cout << "Jaki jest bok podstawy prostopadłościanu: ";
cin >> b;
cout << "Jaka jest wysokość prostopadłościanu: ";
cin >> c;
cout << " Pole prostopadłościanu jest równe: " << ((b*c)*4)+((a*b)*2) << endl;
cout << "Objętość prostopałościanu jest równa: " << (a*b*c) << endl;
 
return 0;


}
