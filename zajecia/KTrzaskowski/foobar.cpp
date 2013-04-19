#include <iostream> /* Napisz program, który wyświetla liczby od 1 do 100, zamiast liczb podzielnych przez 3
wypisując „foo”, zamiast liczby podzielnych przez 3 ale nie podzielnych przez 5 wypisując
„bar” a zamiast liczb podzielnych przez 3 i przez 5 wypisując „foobar”.
*/
using namespace std;

int main()
{
	int n=1;
	for (n==1; n<=100 ; n++)
	{
		if (n % 3 == 0 & n % 5 == 0)
		{
			cout<<"foobar\n";
		}
		else if (n % 3 == 0)
		{
			cout<<"foo\n";
		}
		else if (n % 5 == 0)
		{
			cout<<"bar\n";
		}
		
		else
		{
			cout<< n <<endl;
		}
	}
}

