#include<iostream>
using namespace std;
int main()
{
int n,t,a,b,c,x,y,k[1000000000],o[10000];
//zerowanie
for(int i=0;i<1000000;i++){k[i]=0;}
for(int i=0;i<10000;i++){o[i]=0;}
//program właściwy
cin>>n;
for(int i=0;i<n;i++)
	{
	cin>>a;
	for(int ia=0;ia<1000000;ia+a){k[ia]++;}
	cin>>b;
	for(int ib=0;ib<1000000;ib+b){k[ib]++;}
	cin>>c;
	for(int ic=0;ic<1000000;ic+c){k[ic]++;}
	cin>>x;
	cin>>y;
	
	}

return 0;
}
