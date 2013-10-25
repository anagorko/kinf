#include <iostream> 
using namespace std;

int main()
{
	int t[10];
	
	for(int i=0; i<10; i++)
	{
		cin>> t[i];
	}
	
	for(int j=9; j>=0; j--)
	{
		cout<<t[j]<<" ";
	}
}
