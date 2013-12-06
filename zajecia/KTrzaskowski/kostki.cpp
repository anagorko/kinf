#include <iostream> 
using namespace std;

int main()
{
	int licznik [6];
	licznik [0]=0;
	licznik [1]=0;
	licznik [2]=0;
	licznik [3]=0;
	licznik [4]=0;
	licznik [5]=0;

	int z;
	cin>>z;
	cout<<"\n";
	int k[z];
	for(int i=0; i<z; i++)
	{	
		cin>>k[i];
	}	
	for(int i=0; i<z; i++)
	{ 
		if (k[i]==1) { licznik [0]++; }
		if (k[i]==2) { licznik [1]++; }
		if (k[i]==3) { licznik [2]++; } 
		if (k[i]==4) { licznik [3]++; } 
		if (k[i]==5) { licznik [4]++; } 
		if (k[i]==6) { licznik [5]++; }
	
	}
	
	cout<<"jedynek było "<< licznik [0]<<"\n";
	cout<<"dwójek było "<< licznik [1]<<"\n";
	cout<<"trójek było "<< licznik [2]<<"\n";
	cout<<"czwórek było "<< licznik [3]<<"\n";
	cout<<"piatek było "<< licznik [4]<<"\n";
	cout<<"szóstek było "<< licznik [5]<<"\n";
}
