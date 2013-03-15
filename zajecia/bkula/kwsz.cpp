#include <iostream>
using namespace std;
int main (){

int n;
int l[100];
int kw[100];
int sz[100];

cout<<"wpisz wartość n =< 100";

cin>>n;

cout<<"wpisz "<<n<<" liczb/y";

for (int i = 0; i != n; i++){
	cin>>l[i];
}

cout<<"Liczby które wpisałeś :";

for (int i = 0; i != n; i++){
        cout<<l[i]<<" ";
}

cout<<"ich kwadraty :";

for (int i = 0; i != n; i++){
	kw[i] = l[i] * l[i];
	cout<<kw[i]<<" ";
}

cout<<"ich sześciany :";

for (int i = 0; i != n; i++){
        sz[i] = l[i] * l[i] * l[i];
        cout<<sz[i]<<" ";
}


return 0;
}
