#include<iostream>
using namespace std;
int main()
{	
float a, b, h;
cout <<"Podaj długość: ";
cin >>a;
cout <<"Podaj szerokość: ";
cin >>b;
cout <<"Podaj wysokość: ";
cin >>h;
cout <<"Objętość tego prostopadłościanu to: " <<(a*b*h);
cout <<"Pole powieszchni tego prostopadłościanu to: " <<((a*b)+(a*h)+(a*b)+(a*h)+(h*b)+(h*b));
}
