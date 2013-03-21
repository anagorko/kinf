#include<iostream>
using namespace std;
int main()
{
int n,w;
cin>>n;
for(int j=n-1;j>0;j--)
	{
	int x,m;
	cin>>x;
	cin>>m;
	for(int i=m;i>0;i--)
		{
		int y;
		cin>>y;
		if(y==x)
			{
			w++;
			}
		}
		cout<<w;
	}
return 0;
}
