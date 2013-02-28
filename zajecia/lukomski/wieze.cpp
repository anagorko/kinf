//
// Bez komentarzy trudno odgadnąć Twoje intencje w tym programie.
// Nazwy tablic t i ta są zbyt generyczne i nic nie znaczą.
// Jakie jest znaczenie ta[i][0] i ta[i][1]? Czy uzasadnione jest użycie jednej tablicy?
// Być może sensowne jest oddzielenie czytania danych od obliczeń.
// Co to jest least i most i do czego służą?
// Itd.
//
#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	int t[1000001],ta[n][2];
	int kon=0,least=1000001,most=0;
	//czyszczenie tablic
	for(int i=0;i<1000001;i++){
		t[i]=0;
		if(i<n){
		ta[i][0]=0;
		ta[i][1]=0;
		}
	}
	//end of czyszczenie tablic
	for(int i=0;i<n;i++){
		cin>>ta[i][0];
		ta[i][1]=kon;
		if(least>ta[i][0]){least=ta[i][0];}//cout<<"least="<<least<<"\n";}
		if(most<ta[i][0]){most=ta[i][0];}//cout<<"most="<<most<<"\n";}
		for(int a=0;a<ta[i][0];a++){
		cin>>t[kon];
		kon++;
		}
	}ta[n][1]=kon;
	cout<<"rozwiazywanie..."<<endl;
	//rozwiazywanie
	int suma=0;
	int max=0;
	for(int a=0;a<most-least;a++){
		for(int i=0;i<n;i++){
			if(a<=ta[i][0]){
				if(t[ta[i+1][1]-a]>max){max=t[ta[i+1][1]-a];cout<<"max =  "<<max<<endl;}
			}
		}
		suma=suma+max;
		cout<<"suma = "<<suma<<endl;
		max=0;
	}
	cout<<suma<<endl;
	int suma1=0;
	for(int i=0;i<n;i++){
		for(int a=0;a<least;a++){
			suma1=suma1+t[ta[i][1]+a];
		}
		if(suma1>max){max=suma1;}
	}
	suma=suma+suma1;
	cout<<suma<<endl;
	//i tu reszta kodu, ale nie wiem czemu nie działa to co do tej pory.
return 0;
}
