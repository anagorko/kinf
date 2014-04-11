#include <iostream>
using namespace std;

int main ()
{

	int i;
	cin >> i;
	for (int n=0; n<i; n++)
	{
		if ( i== i/2)
		{
			for (int j=0; j<i; j++)
			{
				cout<< "H";
			}
			
		}
		else
		{
			cout<< "H";
			for (int l=0; l<i-2; l++)
			{
				cout<< " ";
			}
			cout<< "H";
		}
		cout << "\n";
	}
}
		 

