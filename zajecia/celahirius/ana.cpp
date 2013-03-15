#include <iostream>

using namespace std;

int main()
{
string tekst;
int tab[256];

cin>>tekst;

for(int i=0; i<256; i++)
{
	tab[i]=0;
}

for(int i=0; i<tekst.length(); i++)
{
			tab[tekst[i]]++;
}

/*for(int i=0; i<256; i++)
{
	if(tab[i]!=0)
	{		
		cout<<(char)i;
	}
}*/

for(int i=255; i>=0; i--)
{
	if(tab[i]!=0)
	{
		for(int j=0; j<tab[i]; j++)
		{
			cout<<(char)i;
		}
	}
}

cout<<endl;

return 0;
}
