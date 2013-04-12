#include <iostream>
#include <string>
using namespace std;
int main()
{
	string w;
	getline (cin,w);
	char t[3][w.length()];
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<w.length(); j++)
		{
			t[i][j]='.';
		}
	}
	
	for (int k=0; k<w.length(); k++)
	{
		switch (k % 4)
		{
			case 0: t[0][k]= w[k];
			break;
			
			case 1:
			case 3: t[3][k]= w[k];
			break;

			case 2: t[2][k]= w[k];
			break;
		}
	}    		
	for (int n=0; n<w.length() n++)
	{
		cout<<w<<endl;
	}
}
