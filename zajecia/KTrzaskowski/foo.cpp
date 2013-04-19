#include <iostream> /* Napisz program, który wyświetla liczby od 1 do 100, ale każdą liczbę podzielną przez
3 zastępując tekstem „foo”.*/
using namespace std;

int main()
{
	int n=1;
	for (n==1; n<=100 ; n++)
	{
		if (n % 3 == 0)
		{
			cout<<"foo\n";
		}
		else
		{
			cout<< n <<endl;
		}
	}
}
