#include <iostream> //Napisz program, który oblicza sumę liczb parzystych od 2 do 100.
using namespace std;

int main()
{
	cout<<"suma liczb od 2 do 200 to:\n";
	long long int a=2;
	long long int wynik=0;
	for (a=2; a<200; a++)
	{
		wynik=wynik+a;
	}
	cout<<wynik<<endl;
}
