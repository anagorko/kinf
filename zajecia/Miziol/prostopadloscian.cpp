#include<iostream>
using namespace std;
int main()
{
int a,b,c,w;
cin>>a;
cin>>b;
cin>>c;
w=a*b*c;
cout<<w<<"\n";
w=2*(a*b)+2*(a*c)+2*(b*c);
cout<<w<<"\n";
return 0;
}
