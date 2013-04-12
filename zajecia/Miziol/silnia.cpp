#include<iostream>
using namespace std;
int main()
{
int n,w=1;
cin>>n;
for(int i=1;i<n+1;i++)
	{
	w=w*i;
	}
w=w%10;
cout<<w<<"\n";

return 0;
}
