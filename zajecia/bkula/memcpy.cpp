#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class C
{
public:
	int x, y;
	float f;
	string t;
	C() {}
	C(string in)
	{
		//
	}
} foo;

int main()
{
	foo.x = 1;
	foo.y = 200;
	foo.f = 1.5;
	foo.t = "XXXXXX";
	
	int n = sizeof(foo) / sizeof(char) + 2;
	char c[n];
	for (int i = 0; i < n; i++) c[i] = 0; 
	memcpy(&c, &foo, sizeof(foo));
	for (int i = 0; i < n; i++) cout << c[i];
	cout<<endl;
	
	string* str = new string(c, n);
	cout << *str << endl;
	
	C* bar = new C();
	cout << sizeof(*bar) << " " << sizeof(foo) << endl;
	memcpy(bar, c, sizeof(char) * n);
	cout << bar->x << " " << bar->y << " " << bar->f << " " << bar->t << endl;
}
