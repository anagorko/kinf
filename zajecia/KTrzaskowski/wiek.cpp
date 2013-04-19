#include <iostream>	
using namespace std;

int main()
{
	int wiek;
	
	cout<<"podaj swój wiek: \n";
	cin>> wiek;

	if (wiek < 18)
	{
		cout<<"jesteś niepełnoletni\n";
  	}
	else
  	{
		cout<<"jesteś pełnoletni/a\n";
  	}
}
