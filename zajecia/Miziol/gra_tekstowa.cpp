#include<iostream>
using namespace std;

int pokoj=0;
string komenda;

void lozko()
	{
	cout<<"Budzisz się. Leżysz w łóżku. Przed sobą widzisz otynkowany sufit.\n>";
	getline(cin,komenda);
	while(true)
		{
		if(komenda=="u"||komenda=="up"){pokoj=1;return;}
		else{cout<<"Komenda nie znana";}
		}
	pokoj=100;
	}
void dom()
	{
	cout<<"Jestes w pokoju";
	pokoj=100;
	}

int main()
{
while(true)
	{
	if(pokoj==0)
		{
		lozko();
		}	
	if(pokoj==1)
		{
		dom();
		}
	if(pokoj==100)
		{
		return 0;
		}
	}

return 0;
}
