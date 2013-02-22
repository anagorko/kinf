#include<iostream>
using namespace std;
string reverse(string s)
{
	string s2 = s;
	char s3;
	for(int i = 0; i < s.length() / 2; i++){
		s3 = s2[s2.length() - 1 - i];
		s2[s2.length() - 1 - i] = s2[i];
		s2[i] = s3;
	}
	return s2;
}
int main()
{
	string s;
	cin >> s;
	cout << reverse(s) << "\n";
}
