#include <iostream>
using namespace std;
int main()
{
	int n; //jaki bedzie rozmiar tablicy
	cin >> n;
    int tab[n];
	for (int i = 0; i < n; i++ ) cin >> tab[i]; //wczytywanie danych do tablicy
for(int i=0;i<n;i++)
	{
	for(int j=i+1;j<n;j++)
		{
		if(tab[i]>tab[j])
			{
			int x = tab[i];
			tab[i] = tab[j];
			tab[j] = x;
			}
		}
	}	   
	for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
	cout << endl;
	   return 0;
}
/*
#include <iostream>
using namespace std;
int main(){
	int n;
	cin >> n;
	int data[n];
	for(int i = 0; i < n; i++) cin >> data[i];
	int SubArrayEnd = n -1;  

	while (SubArrayEnd > 0)
	{
	int nextEnd = 0;
    
	for (int j = 0; j < (SubArrayEnd); j++)
	{
    if (data[j] > data[j+1])
	{
	int temp=data[j]; 
       data[j]=data[j+1];      
       data[j+1]=temp;   


       nextEnd = j;
	}
	else  
	++j;
	}

	SubArrayEnd = nextEnd;
	}
	for(int i = 0; i < n; i++) cout << data[i] << " ";
	cout << endl
}*/
