#include<iostream>
#include<math.h>
using namespace std;
int main(){
	float n,m;
	cin>>n>>m;
	float w= sqrt((n*n+m*m)/4);
	cout.setf(ios::fixed);
	cout.precision(2);
	cout<<w<<"\n";
	return 0;
}
