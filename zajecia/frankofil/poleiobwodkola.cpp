#include <iostream>
#include <iomanip>
using namespace std;

int main (){
float r, p, o;
cin >>r;
p= 3.14;
o= 2*(p*r);

cout << fixed << setprecision(3) << o << endl;

float c;

c= p*(r*r);

cout << fixed << setprecision(3) << c << endl;

}
