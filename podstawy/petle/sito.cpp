#include<iostream>
using namespace std;

int main()
{
  int n;
  
  cin >> n;
  
  bool p[n+1];
  
  for (int i = 0; i <= n; i++) {
    p[i] = true;
  }

  p[0] = false; p[1] = false;
    
  int d = 2;
  
  while (d * d <= n) {
    for (int k = 2; d * k <= n; k++) {
      p[d * k] = false;
    }
    
    do {
      d++;
    } while (d * d <= n && p[d] == false);
  }

  int ile = 0;
    
  for (int i = 0; i <= n; i++) {
    if (p[i]) {
      ile++;
    }
  }
  cout << ile << endl;
  
  return 0;
}
