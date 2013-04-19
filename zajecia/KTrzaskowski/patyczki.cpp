#include <iostream> /*Bajtuś bawi się trzema patyczkami w ten sposób, że chce ułożyć z nich
a) trójkąt,
b) trójkąt równoboczny,
c) trójkąt równoramienny,
d) trójkąt prostokątny.
Sprawdź, czy mu się to uda. Wczytaj trzy liczby, odpowiadające długościom patyczków, i wypisz, czy można zbudować z nich a) trójkąt, b) trójkąt równoboczny, c) trójkąt równoramienny, d) trójkąt prostokątny.*/
using namespace std;

int main()
{
	double a, b, c;

	cout<<"Podaj długość pierwszego patyczka którym bawi się Bajtuś: \n";
	cin>> a;

	cout<<"Podaj długość drugiego patyczka którym bawi się Bajtus: \n";
	cin>> b;

	cout<<"Podaj długość trzeciego patyczka którym bawi się Bajtuś: \n";
	cin>> c;

	if (a >= b + c || b >= a + c || c >= a + b)
	{ 
		cout<<"Niestety nie da się z tych patyczków ułożyć żadnego trójkąta,\n";
		//chciałem zamknąć program, ale nie wiem jak
	}
	else
	{
		cout<<"Z patyczków którymi bawi się Bajtuś da się ułożyć trójkąt,\n";
		cout<<"więc próbujemy dalej!\n";
	}

	if (a==b || b==c || c==a) //Zamieniłem kolejnośc żeby było logiczniej
	{
		cout<<"Z patyczków którymi bawi się Bajtuś da się ułożyć trójkąt równoramienny,\n";
	}
	else
	{
		cout<<"Patyczki Bajtusia są niestety nieodpowiednie aby ułożyć trójkąt równoramienny,\n";
	}

	if (a==c && a==b && b==c)
	{
		cout<<"Bajtuś może ułożyć trójkąt równoboczny,\n";
	}
	else
	{
		cout<<"Z tych patyczków nie da się ułożyć trójkąta równobocznego,\n";
	}

	if  ((a * a + b * b == c * c) && (a * a + c * c == b * b) && (c * c + b * b == a * a)) 
	{
		cout<<"Z patyczków którymi bawi się Bajtuś da się także ułożyć trójkąt prostokątny!\n";
	}
	else
	{
		cout<<"Bajtuś ze swoich patyczków nie będzie mógł ułożyć trójkąta prostokątnego.\n";
	}
}  								

