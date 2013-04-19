#include <iostream> /*Napisz program, który wyświetla na ekranie najpierw liczby nieparzyste od 1 do 99, a
następnie liczby parzyste od 2 do 100.*/
using namespace std;

int main()
{
	for (int a=0; a<100; a++)
	{
	    	if (a%2 == 1)
		{
			cout<< a <<endl;
		}
	}
	
	for (int a=0; a<100; a++)
	{
	    	if (a%2 == 0)
		{
			cout<< a <<endl;
		}
	}
	
}
