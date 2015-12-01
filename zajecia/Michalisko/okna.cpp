#include<iostream>
using namespace std;

int main(){
	int wys, pole, il, ob;

	cin >> wys >> pole >> il;

	ob= pole/wys;
	ob= (wys*2)+(ob*2);
	ob= ob*il;

	cout << ob;
}
