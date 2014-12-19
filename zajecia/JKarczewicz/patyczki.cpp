#include<iostream>
using namespace std;

int main () {
int a, b, c;
cout << "Podaj długość pierwszego patyka: ";
cin >> a;
cout << "Podaj długość drugiego patyka: ";
cin >> b;
cout << "Podaj długość trzeciego patyka: ";
cin >> c;
if (a+b<c)
{
cout << "Trójkąt może zostać stworzony\n";

}else{ if (b+c<a)
{
cout << "Trójkąt może zostać stworzony\n";

}else{ if (a+c<b)
{
cout << "Trójkąt może zostać stworzony\n";
}

}
