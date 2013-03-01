#include<iostream>
using namespace std;
void reverse(string &s)
{
	char s3;
	for(int i = 0; i < s.length() / 2; i++){
		s3 = s[s.length() - 1 - i];
		s[s.length() - 1 - i] = s[i];
		s[i] = s3;
	}
}
int main()
{
	string s;
	getline(cin, s);
	reverse(s);
	cout << s << "\n";
}
