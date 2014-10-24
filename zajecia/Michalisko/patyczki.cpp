#include<iostream>
using namespace std;

int main() {
int a, b, c;
cin >> a >> b >> c;
if (a+b>c && c+b>b && b+c>a){
cout << "Morzesz ułorzyć trójkąt:";

}
if (a==b && a==c){
cout << "rónoboczny, ";
}
if (a==b){
cout << "równoramienny, ";
}
else if (a==c){
cout << "równoramienny, ";
}
else if (b==c){
cout << "równoramienny, ";
}
if ((a*a)+(b*b)==(c*c)){
cout << "prostokątny, ";
}
else if ((a*a)+(c*c)==(b*b)){
cout << "prostokątny, ";
}
if ((c*c)+(b*b)==(a*a)){
cout << "prostokątny, ";
}
}



