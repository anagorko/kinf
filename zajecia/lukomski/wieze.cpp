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
	int t[1000000],ta[n][2];
	int kon=0,least=1000001,most=0;
	//czyszczenie tablic
	for(int i=0;i<1000000;i++){
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
	}
	//cout<<least<<" "<<most<<endl;
	int suma=0;
	int sumamax=0;
	int w=0;//wynik
	for(int i=0;i<n;i++){
		for(int a=0;a<least;a++){
			suma=suma+t[ta[i][1]+a];
		}
		if(suma>sumamax){sumamax=suma;}
		suma=0;
	}
	w=sumamax;
	sumamax=0;
	cout<<w<<endl<<endl;
	for(int i=least;i<most;i++){
		for(int a=0;a<n;a++){
			if(i<ta[a][0] && t[ta[a][1]+i]>sumamax){sumamax=t[ta[a][1]+i];cout<<"sumamax="<<sumamax<<endl;}
		}
		w=w+sumamax;
		sumamax=0;
		cout<<w<<endl;
	}
	cout<<w<<endl;
	//i tu reszta kodu, ale nie wiem czemu nie działa to co do tej pory.
return 0;
}
