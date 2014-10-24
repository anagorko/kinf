//#define DEBUG

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int n, m;

void debug(const string& str) {
    #ifdef DEBUG
    cout << str << endl;
    #endif // DEBUG
}

template<class T> string to_string(T x)
{
    stringstream ss;
    ss << x;
    return ss.str();
}

struct Path
{
    Path(const int& _to, const int& _d) : to(_to), d(_d) {}
    int to;
    int d;
};

struct Vertex
{
    vector<Path> p;
    bool zaliczony;
};

vector<Vertex> v;

struct Score
{
    long long score;
    vector<int> way;
    stringstream naj;
};

Score high;

void go(int i, int score)
{
    v[i].zaliczony = 1;
    high.way.push_back(i);

    if (i == 0) {
        if ((score < high.score || high.score == -1) && (high.way.size() == n+1)) {
            high.score = score;
            high.naj.clear(); high.naj.str("");
            for (int j = 0; j < high.way.size(); j++) {
                high.naj << high.way[j]+1 << " ";
            }
        }
        if (high.way.size() != 1) {
            v[i].zaliczony = 0;
            high.way.pop_back();
            return;
        }
    }

    #ifdef DEBUG
    cout << "###"<<i+1<<"\n";
    cout << score << endl;
    for (int j = 0; j < high.way.size(); j++) {
        cout << high.way[j]+1 << " ";
    }
    cout << endl;
    #endif // DEBUG

    for (int j = 0; j < v[i].p.size(); j++) {
        if (! v[v[i].p[j].to].zaliczony || v[i].p[j].to == 0) go(v[i].p[j].to, score + v[i].p[j].d);
    }

    v[i].zaliczony = 0;
    high.way.pop_back();
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    v.reserve(n);
    for (int i = 0; i < m; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        v[a-1].p.push_back(Path(b-1, d));
    }
    for (int i = 0; i < n; i++) {
        v[i].zaliczony = false;
    }

    high.score = -1;
    go(0, 0);

    cout << high.score << endl;
    cout << high.naj.str() << endl;

    debug(to_string(high.way.size()));
}
