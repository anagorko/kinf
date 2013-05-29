#include <iostream> //Napisz program obliczający sumę liczb nieparzystych mniejszych od miliarda.
using namespace std;

int main()
{
	cout<<"suma liczb od 1 do 1000000000 to:\n";
	long long int wynik=0;
	for (long long int a=1; a<1000000000; a++)
	{
		wynik=wynik+a;
	}
	cout<<wynik<<endl;
}
