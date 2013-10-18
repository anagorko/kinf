#include <iostream>
using namespace std; 

int main()
{
	int a;
	int j;
	
	cout<< "podaj wysokość trójkąta, który ma byc wyswietlony: \n";
	cin>> a;

	for (int i=0; i < a; i++)
	{
		for (j=0; j < i+1; j++)
		{
		cout<< "T";
		}
	cout<< "\n";	 
	}
 
}	
	
