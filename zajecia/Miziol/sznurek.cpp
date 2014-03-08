#include<iostream>
using namespace std;
int main()
{
int n,j,w=0,a,b=0;
cin>>n>>j;
for(int i=0;i<n;i++)
	{
	cin>>a;
	b=b+a;
	if(b>=j)
		{
		b=0;
		w++;
		}
	}
cout<<w<<"\n";

return 0;
}
