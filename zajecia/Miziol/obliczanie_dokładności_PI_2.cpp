#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std;
int main()
{
srandom(time(NULL)+getpid());
float r=0,x=0,y=0,n=0;
int w=0;
cin>>n;
for( int i=0;i<n;i++)
	{
	x=(random()%10000001)/10000000.0;
	y=(random()%10000001)/10000000.0;
	r=sqrt(((x-0.5)*(x-0.5))+(y-0.5)*(y-0.5));
	if(r<0.5){w++;}
	}
cout<<w/n<<"\n";

return 0;
}
