#include<iostream>
using namespace std;
int main()
{
int n1,n2,n3,w1,w2;
cin>>n1;
cin>>n2;
cin>>n3;

if(n1<n2)
{w1=n1;}
if(n1>n2)
{w1=n2;}
if(w1>n3)
{w2=n3;}
if(w1<n3)
{w2=w1;}
cout<<w2;

return 0;
}
