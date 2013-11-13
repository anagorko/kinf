#include<iostream>
using namespace std;

int main()
{
  int n;
  cin >> n;
  
  int kopiec[n+1];
  int o = 1;
  
  for (int i = 0; i < n; i++) {
    int l;
    cin >> l;
    
    int x = o; 
    o++;
    
    kopiec[x] = l;
    while (kopiec[x] < kopiec[x/2]) {
      int tmp = kopiec[x];
      kopiec[x] = kopiec[x/2];
      kopiec[x/2] = tmp;
      x = x / 2;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << kopiec[1] << " ";
    
    int x = 1; 
    o--;
    kopiec[1] = kopiec[o];
    
    while (true) {
      int y = -1;
    
      if (2*x+1 < o) {
        if (kopiec[2*x] < kopiec[2*x+1]) {
          y = 2 * x;
        } else {
          y = 2 * x + 1;
        }
      } else if (2*x < o) {
        y = 2 * x;
      }
    
      if (y > 0 && kopiec[y] < kopiec[x]) {
        int tmp = kopiec[y];
        kopiec[y] = kopiec[x];
        kopiec[x] = tmp;
        x = y;
      } else {
        break;
      }
    }
  }
  
  return 0;
}
