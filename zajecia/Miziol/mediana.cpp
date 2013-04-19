#include<iostream>
using namespace std;
int main()
{
int n,r,ru;
float w;
cin>>n;
float t[n];
for(int i=0;i<n;i++){cin>>t[i];}

for(int i=0;i<n;i++)
	{
	for(int j=i+1;j<n;j++)
		{
		if(t[i]>t[j])
			{
			r=t[i];
			t[i]=t[j];
			t[j]=r;
			}
		}
	}
if(n%2==0){w=(t[n/2]+t[(n/2)-1])/2;}
if(n%2==1){w=t[n/2];}
cout<<w<<"\n";

return 0;
}
