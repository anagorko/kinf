#include<iostream>
using namespace std;
int main(){
int x[20];
int n;
 for (int y = 0; y < 19; y++) {
            cin >> x[y];
        }
cout << "\n";
for (int y = 0; y < 19; y++) {
            if( x[y] % 2 == 0 ){cout << x[y]<<" ";}
        }
cout << "\n";
for (int y = 0; y < 19; y++) {
            if( x[y] % 2 == 1 ){cout << x[y]<<" ";}
        }

return 0;
}
