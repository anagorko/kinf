#include <iostream>
#include <string>
using namespace std;
int modul(int a)
 {
	if(a<0){return -1*a;}
	else {return a;}
 }
main()
{
string krok;
int liczba_wpisow,liczba_powt,i,j,k,z;
int xb=0;
int yb=0;
int xmax=0;
int ymax=0;
int xmin=0;
int ymin=0;
int ywynik=0;
int xwynik=0;
int x=0;
int y=0;

cin>>liczba_wpisow;

for(i=0;i<=liczba_wpisow;i=i+1)
{
	cin>>liczba_powt;

	for(j=0;j<=liczba_powt;j=j+1)
	{
		cin>>krok;
		
		for(k=0;k<=krok.length();k=k+1)
		{
			if(krok[k]=='N')
			{
				yb=yb+1;
				
				if(yb>ymax)
				{
					ymax=ymax+yb;
				}
			}
			
			if(krok[k]=='S')
			{
				yb=yb-1;
				
				if(yb<ymin)
				{
					ymin=ymin+yb;
				}
			}
			
			if(krok[k]=='E')
			{
				xb=xb+1;
				
				if(xb>xmax)
				{
					xmax=xmax+xb;
				}
			}

			if(krok[k]=='W')
			{
				xb=xb-1;
				
				if(xb<xmin)
				{
					xmin=xmin+xb;
				}
			}			
		}
	}
}
cout<<modul(ymin)<<" ";
cout<<modul(xmin)<<"\n";
//ywynik=y+ymax;
//xwynik=x+xmax;
//cout<<ywynik<<" "<<xwynik<<"\n";
return 0;
}

