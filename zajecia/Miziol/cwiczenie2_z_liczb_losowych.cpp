#include<iostream>
#include<stdlib.h>
using namespace std;
int main()
{
int n=0;
srandom(time(NULL)+getpid());
cout << "\nWyniki dziesięciokrotnego rzutu monetą: ";
	for (int i = 0; i < 10; i++)
		{
		n=random()%2;
		if(n==0)cout<<"R ";
		if(n==1)cout<<"O ";
		}
cout << "\n\n";
}
