#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
int main(){
	srandom(time(NULL)+getpid());
	string g[11];
	g[0]="my";
	g[1]="our common";
	g[2]="the party's";
	g[3]="my family's";
	g[4]="our children's";
	g[5]="my fellow Europeans'";
	g[6]="the government's";
	g[7]="the industry's";
	g[8]="the consumers'";
	g[9]="the immigrants'";
	g[10]="the only truly";
	string a[15];
	a[0]="improved";
	a[1]="responsible";
	a[2]="peacekeeping";
	a[3]="free";
	a[4]="pro-life";
	a[5]="politically correct";
	a[6]="integrated";
	a[7]="federal";
	a[8]="progressive";
	a[9]="anti-crime";
	a[10]="drug-addicted";
	a[11]="gradual";
	a[12]="democratic";
	a[13]="genetically engineered";
	a[14]="racial";
	string s[17];
	s[0]="freedom";
	s[1]="national security";
	s[2]="abuse";
	s[3]="opportunity";
	s[4]="tax cut";
	s[5]="congress";
	s[6]="task force";
	s[7]="Europe";
	s[8]="decision";
	s[9]="dialogue";
	s[10]="future";
	s[11]="community";
	s[12]="answer";
	s[13]="environment";
	s[14]="set of family-values";
	s[15]="legislation";
	s[16]="discrimination";
	string v[10];
	v[0]="benefits";
	v[1]="improves";
	v[2]="decreases";
	v[3]="supports";
	v[4]="is built on";
	v[5]="is the best guarantee for";
	v[6]="creates an opportunity for";
	v[7]="forms";
	v[8]="is necessary for";
	v[9]="will be established to combat";


	cout<<g[random()%11]<<" ";
	cout<<a[random()%11]<<" ";
	cout<<s[random()%17]<<" ";
	cout<<v[random()%10]<<" ";
	cout<<g[random()%11]<<" ";
	cout<<a[random()%11]<<" ";
	cout<<s[random()%17]<<endl;
	return 0;
}
