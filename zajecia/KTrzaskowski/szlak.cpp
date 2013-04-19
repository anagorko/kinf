#include <iostream> /*Bajtuś z tatą wybrali się na całodniową wyprawę górskim szlakiem. O godzinie 12 wysłali sms-a do mamy, na jakiej wysokości nad poziomem morza się znajdują. Podobnie zrobili o godzinie 18. Napisz, czy wieczorem weszli pod górkę, czy zeszli w dół w stosunku do wysokości z południa.*/
using namespace std;

int main()
{
	int a, b;
	
	cout<<"Podaj wysokość na jakiej znajdowali się tata z Bajtusiem o godzinie 12: \n";
	cin>> a;

	cout<<"Podaj wysokość na jakiej znajdowali się tata z Bajtusiem o godzinie 18: \n";
	cin>> b;

	if (a > b)
	{
		cout<<"Tata z Bajtusiem zeszli w dół w stosunku do wysokości z południa.\n";
	}
	else if (a == b)
	{
		cout<<"Tata z Bajtusiem wieczorem zostali na takiej samej wysokości jak w południe.\n";
	}
	else
	{
		cout<<"Bajtuś z tatą podeszli wieczorem wyżej niż w południe.\n";
	}
} 
