#include<iostream>
using namespace std;

int main()
{
    string s = "ą";
    
    cout << s << " " << s.length() << endl;

    wstring ws = L"ą";
    
    wcout << ws << " " << ws.length() << endl;
    
    s = "ɐ";

    cout << s << " " << s.length() << endl;
    
    s = "\u0250";

    cout << s << " " << s.length() << endl;
}
