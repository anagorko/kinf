#include<iostream>
using namespace std;

int main()
{
  int n;
  cin >> n;
  
  int c[n];
  for (int i = 0; i < n; i++) { cin >> c[i]; }
  
  int min = c[n-1];
  int p = 0;
  int i = n-2;
  int cena = 0;
  
  while (i >= 0) {
    if (min < c[i]) {
      p++;
    } else {
      cena = cena + (p+1) * min;
      min = c[i];
      p = 0;
    }
    i--;
  }
  
  cena = cena + (p+1) * min;
  
  cout << cena;
  
  return 0;
}
