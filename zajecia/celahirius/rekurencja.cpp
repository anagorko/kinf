#include <iostream>

using namespace std;

int main()
{
	int n;
	float w;
	
	cin>>n;
	
	int a[n+1];
	
	for(int i=1; i<=n; i++)
	{
		if(i==1) a[i]=1;
		else if(i==2) a[i]=2;
		else a[i]=a[n-2]+(a[n-1]*a[n-1]);
	}
	
	w=a[n]%7;
	cout<<w;
	
	for(int j=1; j<=n; j++)
	{
		//cout<<a[j]<<endl;
	}
	
	return 0;
}
