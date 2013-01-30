#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

class para {
public:
  string syg, sl;

  const bool operator<(const para p2) const {
    return syg < p2.syg;
  }
};

int main()
{
  int n; cin >> n;
  
  vector<para> t;
  
  while (n--) {
    para p;
    cin >> p.sl;
    p.syg = p.sl;
    sort(p.syg.begin(), p.syg.end());
    t.push_back(p);
  }
  
  sort(t.begin(), t.end());
  
  string s = "", sl = "";
  int c = 0;
  for (int i = 0; i < t.size(); i++) {
    if (t[i].syg != s) {
      if (sl != "") {
        cout << (c+1) << " " << sl << "\n";
      }
      sl = t[i].sl; s = t[i].syg; c = 0;
    } else {
      if (sl == "") {
        sl = t[i].sl;
      } else {
        sl = sl + ", " + t[i].sl;
      }
      c++;
    }
  }
  cout << (c+1) << " " << sl << "\n";
  
  return 0;
}
