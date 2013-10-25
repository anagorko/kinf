#include <iostream> 
using namespace std;

int main()
{
	int t[20];
	
	for(int i=0; i<20; i++)
	{
		cin>> t[i];
	}
	
	for(int j=0; j<20; j++)
	{		
		if (t[j]%2 == 0)
		{
			cout<< t[j] <<" ";
		}
	}

	cout<<endl;
	cout<<endl;
	
	for(int j=0; j<20; j++)
	{		
		if (t[j]%2 == 1)
		{
			cout<< t[j] <<" ";
		}
	}
	
}
	
