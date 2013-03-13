#include <iostream>
using namespace std;
int main (){

int n;
int s = 0;
int g = 0;



cin>>n;

s = n;
g = 1;

for (int i = 0; i != n; i++){
	for (int j = 0; j != s; j++){
	cout<<" ";
	}

	for (int k = 0; k != g; k++){
	cout<<"*";

	if (k == g - 1) cout<<endl;
	}

	s --;
	g += 2;
}

s = n;
g = 1;

for (int i = 0; i != n + 1; i++){
        for (int j = 0; j != s; j++){
        cout<<" ";
        }

        for (int k = 0; k != g; k++){
        cout<<"*";

        if (k == g - 1) cout<<endl;
        }

        s --;
        g += 2;
}


return 0;
}
