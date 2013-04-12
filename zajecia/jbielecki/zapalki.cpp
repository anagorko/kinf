#include <iostream>
#include <cmath>         //podobno powinno się jej uzywać zamiast math.h
using namespace std;
int main(){
int n, w, h;
cin >> n;
cin >> w;
cin >> h;
int dlugosc[n];
for(int i = 0; i < n; i++){

cin >> dlugosc[i];

}

for(int i = 0; i < n; i++){

if(dlugosc[i] <= w || dlugosc[i] <= h || dlugosc[i] <= sqrt((w * w) + (h * h) )){
cout << "TAK" << endl;
}
else{
cout << "NIE" << endl;
}
}

}
