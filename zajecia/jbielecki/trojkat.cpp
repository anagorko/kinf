#include <iostream>
using namespace std;
int main(){

int n;
cin>>n;
int tab[n][n];

	for(int i = 0; i < n; i++){
		for(int c = 0;c <= i; c++){
			tab[i][c]=1;
			if(c >= 1 && i >= 2 && c !=i){
			tab[i][c]=tab[i-1][c-1]+tab[i-1][c];
			}
		}
	}

cout<<endl;

	for(int i = 0; i < n; i++){
		for(int c = 0;c <= i;c++){
		cout<<tab[i][c]<< " ";
		}
	cout<<endl;
	}
return 0;
}

