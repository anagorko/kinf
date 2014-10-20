#include<iostream>
using namespace std;

int main(){
int a, b;
cout << "Podaj wysokość o 12:00";
cin >> a;
cout << "Podaj wysokość o 18:00";
cin >> b;
if (a>b){
cout << "Schodzisz w dół";
}
else if (b>a){
cout << "Idziesz po górę";
}
else if (b==a){
cout << "Jesteś na tej samej wysokości";
}
}
