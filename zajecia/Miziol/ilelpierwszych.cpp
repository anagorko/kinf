#include<iostream>
using namespace std;
int main()
{
int d,w=0;
long long int n;
cin>>n;
for(long long int i=2;i<n;i++)
	{
	d=2;
	while(d*d<=i)
		{
		if(i%d==0){break;}
		d++;
		}
	if(d*d<=i){;}
	else{w++;cout<<i<<"\n";}
	}
cout<<"jest ich "<<w<<"\n";
return 0;
}
