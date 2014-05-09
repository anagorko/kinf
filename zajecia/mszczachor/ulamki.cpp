#include<iostream>
#include<sstream>
using namespace std;
int nwd (int a, int b) 
{
	for(;;)
	{
		if(a == 0 || b == 0)return 0;
		if(a == b)
		{
			return a;
		}
		if(a > b)
		{
			a = a - b;	
		}
		else
		{
			b = b - a;
		}
	}
}
int main () {

string okres;
int len;
int okr;
int a = 1;
int b;
cin >> okres;
stringstream ss;
ss << okres;
ss >> okr;
len = okres.length();
for(int i = 0; i < len; i++)
{
	a = a*10;
}
a = a - 1;
b = nwd(okr,a);
okr = okr/b;
a = a/b;
cout << okr << "/" << a << endl;

return 0;
}
