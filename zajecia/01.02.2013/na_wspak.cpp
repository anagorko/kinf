#include <iostream>

using namespace std;

int main()
{

int n[20];

for(int i=0; i<20; i++) {cin >> n[i];}

for(int x=19; x>=0; x--) {cout << n[x]<<" ";}

return 0;
}
