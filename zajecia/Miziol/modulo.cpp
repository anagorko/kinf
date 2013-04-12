#include<iostream>
using namespace std;
int main()
{
int n,w,t[37],w2=0, k=1;

for (int i = 0; i < 37;i++) {
	t[i]  = 0;
}

while(k<16)

{
	k++;
	cin>>n;
	w=n%37;
	for(int i=0;i<37;i++)
		{
		
		if(w==i)
			{
			t[i]++;
			}
		
		}
	
}

for(int j=0;j<37;j++)
{
if(t[j]>1)
{
t[j]=1;
}

w2=w2+t[j];

}
cout<<w2;
return 0;
}
