#include<iostream>
using namespace std;

int main(){
	int dl, a, ns=0, sa=0;
	cin >> dl;
	for(int i=dl; i>0; i--){
		cin >> a;
		sa=sa+a;
		if (sa<0)
			sa=0;
		if (ns<sa)
			ns=sa;
	}
	cout << ns;
}
