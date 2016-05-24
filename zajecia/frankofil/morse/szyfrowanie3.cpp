#include<iostream>
#include<string>
#include <stdio.h>

using namespace std;

int main() 
{
	string a;
	string morstab[256];
	    morstab['a']=".-";
    	morstab['b']="-...";
		morstab['c']="-.-.";
		morstab['d']="-..";
		morstab['e']=".";
		morstab['f']="..-.";
		morstab['g']="--.";
		morstab['h']="....";
		morstab['i']="..";
		morstab['j']=".---";
		morstab['k']="-.-";
		morstab['l']=".-..";
		morstab['m']="--";
		morstab['n']="-.";
		morstab['o']="---";
		morstab['p']=".--.";
		morstab['q']="--.-";
		morstab['r']=".-.";
		morstab['s']="...";
		morstab['t']="-";
		morstab['u']="..-";
		morstab['w']=".--";
		morstab['v']="...-";
		morstab['x']="-..-";
		morstab['y']="-.--";
		morstab['z']="--..";
		morstab['1']=".----";
		morstab['2']="..---";
		morstab['3']="...--";
		morstab['4']="....-";
		morstab['5']=".....";
		morstab['6']="-....";
		morstab['7']="--...";
		morstab['8']="---..";
		morstab['9']="----.";
		morstab[' ']="";

	cout<<"Podaj tekst do zaszyfrowania."<<endl;
	getline(cin,a);
	
	cout<<"Zaszyfrowany tekst:"<<endl;
	int dl;
	dl = a.length();
	for (int i = 0; i < dl; i++){
        char znak=a[i];   
        //if(znak==-60) cout<<" ";
        cout<<znak;
        if(znak>=0 && znak<256) {
            string znakMorsea=morstab[znak];
            for(int j =0; j<znakMorsea.length(); j++)
                cout<<" ";
        } 
	}
    cout<<endl;
	for (int i = 0; i < dl; i++){
        char znak=a[i];
        //cout<<(int)znak<<" ";
        if(znak>=0 && znak<256) {
            string znakMorsea=morstab[znak];
    		cout<<znakMorsea<<"/";
        }
        else if (znak<-61 || znak>-59) cout<<"/";
	}
    cout<<endl;
}
