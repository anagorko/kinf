#include<iostream>

using namespace std;

int main()
{

int n;

cin>>n;

int wyraz[n];

for(int i=0;i<n;i++)
{
	cin>>wyraz[i];
}

int znak;

bool bylem;

while(true)
{
	bylem=false;
		for(int i=1;i<n;i++)
		{
			if(wyraz[i-1]>wyraz[i])
			{
				znak=wyraz[i-1];
				wyraz[i-1]=wyraz[i];
				wyraz[i]=znak;
				bylem=true;
			}
		}
	if(!bylem)
	{
		for(int i=0;i<n;i++)
		{
			cout<<wyraz[i]<<" ";
		}
		return 0;
	}
}
cout<<endl;
}
