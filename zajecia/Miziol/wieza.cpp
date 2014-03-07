#include<iostream>
using namespace std;
int main()
{
int is,im,m,w;
cin>>is>>im;
int s[is];
for(int i=0;i<is;i++)
	{
	cin>>s[i];
	}
for(int i=0;i<im;i++)
	{
	w=0;
	cin>>m;
	for(int j=0;j<is;j++)
		{
		if(m>s[j]){w++;}
		else{break;}
		}
	cout<<w<<"\n";
	}

return 0;
}
