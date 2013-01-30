#include<iostream>
using namespace std;

struct wymierna {
  int l;
  int m;
};

wymierna s(wymierna w)
{
  w.l = w.l + w.m;
  
  return w;
}

wymierna r(wymierna w)
{
  int l = -w.m;
  w.m = w.l;
  w.l = l;

  if (w.m < 0) {
    w.l = -w.l;
    w.m = -w.m;
  }
  
  return w;
}

int main()
{
  int n;
  cin >> n;

  wymierna w;
  
  w.l = 0;
  w.m = 1;
  
  while (n--) {
    char c;
    cin >> c;
    
    if (c == 'R') {
      w = r(w);
    } else if (c == 'S') {
      w = s(w);
    }
  }
  

  while (w.l != 0) {
    cout << w.l << "/" << w.m << "  ";

    if (w.l > 0 || w.m == 0) {
      cout << "R";
      w = r(w);
    } else {
      cout << "S";
      w = s(w);
    }

    cout << "\n";
  }

  cout << "\n";
  
  return 0;
}
