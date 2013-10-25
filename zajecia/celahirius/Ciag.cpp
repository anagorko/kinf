#include <iostream>

using namespace std;

int main() 
{
	int n;
	
	cin>>n;
	int l[n];
	int p=0 ,z=0, s=0;
	
	for(int i=0; i<n; i++)
	{
		cin>>l[i];
	}
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<=p; j++)
		{
			if(l[j]>=0)
			{
				z++;
			}
		}
		
		for(int k=p+1; k<n; k++)
		{
			if(l[k]<=0)
			{
				z++;
			}
		}
		
		if(i==0)
		{
			s=z;
		}
		else if(z<s)
		{
			s=z;
		}
		p++;
		z=0;
	}
	
	cout<<s;
	
	return 0;
}
