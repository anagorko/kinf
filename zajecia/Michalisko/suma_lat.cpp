#include<iostream>
using namespace std;

int main() {
int a, b, c, d;
cout << "Podaj wiek pierwszej osoby: ";
cin >> a;
cout << "Podaj wiek drugiej osoby: ";
cin >> b;
cout << "Podaj wiek trzeciej osoby: "; 
cin >> c;
d=a+b+c;
if (d>=21){
cout << "Więcej\n";

}
else {
cout << "Mniej\n";
}

}
