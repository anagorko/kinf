#include <iostream>
using namespace std;
int main (){

int w = 0;

for (int i = 0; i != 1000; i++){
	if ((i % 3) == 0 || (i % 5) == 0) w += i;
}

cout<<w;

return 0;
}
