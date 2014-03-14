#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main()
{
  const int n = 20;
 
  srandom(getpid());

  vector<int> v;
  
  for (int i = 0; i < n; i++) {
    v.push_back((random() % 900) + 100);
  }

  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
  
  for (const int &i: v) {
    cout << i << " ";
  }
  cout << endl;
  
  for (vector<int>::iterator i = v.begin(); i < v.end(); i++) {
    cout << *i << " ";
  }
  cout << endl;
    
  sort(v.begin(), v.end());

  for (const int &i: v) {
    cout << i << " ";
  }
  cout << endl;
  
  int x;
  
  cout << "Podaj liczbe: ";
  cin >> x;
}
