#include<iostream>
using namespace std;
int main()
{
int i,ob,naj=0;
cin>>i;
int p[i],w[i];
//zerowanie
for(int j=0;j<i;j++){p[j]=0;w[j]=0;}
//program właściwy

for(int j=0;j<i;j++)
	{
	cin>>ob;
	i++;
	for(int g=1;g<i;g++)
		{
		if(ob>g){w[g]++;}
		}
	i--;
	}

//wynik
for (int m=0;m<i;m++)
	{
	if (w[m]<=naj){}
	if (w[m]>naj){naj=w[m];}
	}
cout<<naj<<"\n";
return 0;
}
