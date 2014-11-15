#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> txt;
    while(1) {
        string t;
        cin >> t;
        if (t == "0") break;
        txt.push_back(t);
    }
    string out;
    bool b = false;
    for (int i = 0; i < txt.size(); i++) {
        b = false;
        for (int j = 0; j < txt[i].size(); j++) {
            if (txt[i][j] == '<') b = true;
            else if (txt[i][j] == '>') {b = false;out += ", ";}
            if (b && txt[i][j] != '<') {
                out += txt[i][j];
            }
        }
    }
    out -= ", ";
    cout << out << endl;
}
