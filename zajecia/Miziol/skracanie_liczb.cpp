#include<iostream>
#include<string>
using namespace std;
int main()
{
int n=0,i;
string s,s2;
cin>>s;
for(i=s.length()-1; i>0 ; i--)
	{
	if(s[i]=='0')
		{
		n++;
		}
	else
		{
		break;
		}
	}
i++;
for(int j=0 ; j<i ; j++)
	{
	cout<<s[j];
	}
cout<<"E"<<n<<"\n";

return 0;
}
