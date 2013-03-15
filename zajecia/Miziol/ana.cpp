#include<iostream>
using namespace std;
int main()
{
int n=0,w=0,t2[25],t[25];
for (int i=0;i<25;i++){t[i]=0;t2[i]=0;}
string s,s2,a="abcdefghijklmnopqrstuwxyz";
cin>>s;
//getline (cin, s);
for (int i=0;i<s.size();i++)
	{
	if(s[i]='a'){t[0]++;}
	if(s[i]='b'){t[1]++;}
	if(s[i]='c'){t[2]++;}
	if(s[i]='d'){t[3]++;}
	if(s[i]='e'){t[4]++;}
	if(s[i]='f'){t[5]++;}
	if(s[i]='g'){t[6]++;}
	if(s[i]='h'){t[7]++;}
	if(s[i]='i'){t[8]++;}
	if(s[i]='j'){t[9]++;}
	if(s[i]='k'){t[10]++;}
	if(s[i]='l'){t[11]++;}
	if(s[i]='m'){t[12]++;}
	if(s[i]='n'){t[13]++;}
	if(s[i]='o'){t[14]++;}
	if(s[i]='p'){t[15]++;}
	if(s[i]='q'){t[16]++;}
	if(s[i]='r'){t[17]++;}
	if(s[i]='s'){t[18]++;}
	if(s[i]='t'){t[19]++;}
	if(s[i]='u'){t[20]++;}
	if(s[i]='w'){t[21]++;}
	if(s[i]='x'){t[22]++;}
	if(s[i]='y'){t[23]++;}
	if(s[i]='z'){t[24]++;}
	}
cin>>n;
for (int i=0;i<n;i++)
	{
	for (int k=0;k<25;k++){t[k]=0;t2[k]=0;}
	cin>>s2;
	//getline(cin, s2);
	for (int j=0;j<s2.size();j++)
		{
		if(s2[i]='a'){t2[0]++;}
		if(s2[i]='b'){t2[1]++;}
		if(s2[i]='c'){t2[2]++;}
		if(s2[i]='d'){t2[3]++;}
		if(s2[i]='e'){t2[4]++;}
		if(s2[i]='f'){t2[5]++;}
		if(s2[i]='g'){t2[6]++;}
		if(s2[i]='h'){t2[7]++;}
		if(s2[i]='i'){t2[8]++;}
		if(s2[i]='j'){t2[9]++;}
		if(s2[i]='k'){t2[10]++;}
		if(s2[i]='l'){t2[11]++;}
		if(s2[i]='m'){t2[12]++;}
		if(s2[i]='n'){t2[13]++;}
		if(s2[i]='o'){t2[14]++;}
		if(s2[i]='p'){t2[15]++;}
		if(s2[i]='q'){t2[16]++;}
		if(s2[i]='r'){t2[17]++;}
		if(s2[i]='s'){t2[18]++;}
		if(s2[i]='t'){t2[19]++;}
		if(s2[i]='u'){t2[20]++;}
		if(s2[i]='w'){t2[21]++;}
		if(s2[i]='x'){t2[22]++;}
		if(s2[i]='y'){t2[23]++;}
		if(s2[i]='z'){t2[24]++;}
		}
	if(t[0]==t2[0]&&t[1]==t2[1]&&t[2]==t2[2]&&t[3]==t2[3]&&t[4]==t2[4]&&t[5]==t2[5]&&t[6]==t2[6]&&t[7]==t2[7]&&t[8]==t2[8]&&t[9]==t2[9]&&t[10]==t2[10]&&t[11]==t2[11]&&t[12]==t2[12]&&t[13]==t2[13]&&t[14]==t2[14]&&t[15]==t2[15]&&t[16]==t2[16]&&t[17]==t2[17]&&t[18]==t2[18]&&t[19]==t2[19]&&t[20]==t2[20]&&t[21]==t2[21]&&t[22]==t2[22]&&t[23]==t2[23]&&t[24]==t2[24]){cout<<"0\n";}
	else
		{
		for(int j=0;j<25;j++)
			{
			w=t[j]-t2[j];
			if(w<0&&w!=-1){cout<<w<<a[j];}
			if(w>0&&w!=1){cout<<w<<a[j];}
			if(w<0&&w==-1){cout<<a[j];}
			if(w>0&&w==1){cout<<a[j];}
			else{}
			w=0;
			}
		}
	}
cout<<"\n";

return 0;
}
