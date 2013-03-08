#include<iostream>
#include<string.h>
using namespace std;
string rev(string &s)
	{
	char n;
	int l=s.length()/2;
	for(int i=0;i<l;i++)
		{
		n=s[(s.length()-i)-1];
		s[(s.length()-i)-1]=s[i];
		s[i]=n;
		}

	return s;
	}


int main()
{
string s;
getline(cin,s);
cout<<rev(s)<<"\n";
return 0;
}
