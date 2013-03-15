#include<iostream>
using namespace std;
int main()
{
	string s1, s2;
	int n = 1, k = 1, d, sg[2], w = 0;
	bool tak;
	cin >> n >> k;
	cin.ignore();
	for(int i = 0; i < n; i++){
		//cin >> s1;
		//cin >> s2;
		getline(cin,s1);
		getline(cin,s2);
		sg[0] = 0;
		sg[1] = 0;
		for(int j = 0; j < s1.length(); j++){
			if(s1[j] == 'a' || s1[j] == 'e' || s1[j] == 'y' || s1[j] == 'u' || s1[j] == 'i' || s1[j] == 'o'){sg[0]++;}
		}
		for(int j = 0; j < s2.length(); j++){
			if(s2[j] == 'a' || s2[j] == 'e' || s2[j] == 'y' || s2[j] == 'u' || s2[j] == 'i' || s2[j] == 'o'){sg[1]++;}
		}
		tak = false;
		if(sg[0] == sg[1]){
			for(int j = 1; j <= k; j++){
				if(s1[s1.length() - j] == s2[s2.length() - j]){tak = true;}
				else{tak = false; break;}
			}
		}
		if(tak){w++;}
	}
	cout << w << "\n";
}
