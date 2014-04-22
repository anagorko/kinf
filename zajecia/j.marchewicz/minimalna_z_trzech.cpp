#include <iostream>

using namespace std;

int main ()
{
	int g;
	int m;
	int s;
	int gms;
	cin>> g;
	cin>> m;
	cin>> s;
	gms = s + (m*60) + (g * 3600);
	cout<< gms << endl;
}
