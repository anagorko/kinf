#include<iostream>
using namespace std;
int main()
{
	string tekst;
	cin >>tekst;
	for(int i = 0;i <= tekst.length(); i++)
	{
		if(tekst[i] >= 65 && tekst[i] <= 90 - 13) tekst[i]=int(tekst[i]) + 13;
		else if(tekst[i] >= 91 - 13 && tekst[i] <= 90) tekst[i]=int(tekst[i]) - 26 + 13;
		else if(tekst[i] >= 97 && tekst[i] <= 122 - 13) tekst[i]=int(tekst[i]) + 13;
		else if(tekst[i] >= 123 - 13 && tekst[i] <= 122) tekst[i]=int(tekst[i]) - 26 + 13;
	}
	cout << tekst<<endl;
	return 0;
}
