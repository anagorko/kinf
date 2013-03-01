//
// Funkcja min jest błędna: co się dzieje, gdy a == b?
// Proszę też, byś zrobił odpowiednie wcięcia.
// Po wprowadzeniu poprawek usuń ten komentarz.
//
#include<iostream>
using namespace std;
int min(int a, int b){
if(a>b){return b;}
if(b>a){return a;}
}
int main(){
int a,b;
cin>>a>>b;
cout<<min(a,b);
}
