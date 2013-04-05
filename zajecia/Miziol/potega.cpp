#include<iostream>
using namespace std;
int main()
{
int n,w=1;
cin>>n;
for(int i=0;i<n;i++)
	{
	w=w*2;
	w=w%10;
	}
cout<<w<<"\n";

return 0;
}
