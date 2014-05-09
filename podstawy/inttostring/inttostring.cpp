#include<sstream>
#include<iostream>
using namespace std;

int main()
{
  stringstream ss;
  int i = 17;
  
  ss << i;
  string s = ss.str();
  
  cout << s;
  
  return 0;
}
