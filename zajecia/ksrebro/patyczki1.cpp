#include <iostream>
using namespace std;
int main ()
{
cout << "Podaj trzy liczby a ja ci powiem czy da sie z nich zrobic trojkat";
int a, b, c;
cin >> a>> b>> c;
if(a+b>c&&a+c>b&&c+b>a){
cout << "Z tych liczb trojkat da sie zrobic";
}else{
cout<< "No te liczby raczej bokami trojkata byc nie moga";
}
}
