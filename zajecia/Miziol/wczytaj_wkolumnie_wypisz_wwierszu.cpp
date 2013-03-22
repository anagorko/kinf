#include<iostream>
using namespace std;
int main()
{
int t[1000000],r=1;
int i=0;
for (i=0 ; r!=0 ; i++)
	{
	cin>>r;
	t[i]=r;
	}
i--;
for (int j=0 ; j!=i ; j++)
	{
	cout<<t[j]<<" ";
	}

return 0;
}
