#include<iostream>
#include<math.h>
using namespace std;
int main(){
	float a,b,c;
	cin>>a>>b>>c;
	float x=sqrt(a*a+b*b);
	float cost0=(a+b)*c;
	float cost1=x*c;
	cout.setf(ios::fixed);
        cout.precision(2);
	cout<<cost0-cost1<<"\n";
	return 0;
	}
