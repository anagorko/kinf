#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int INF = 1000007;

int s;
vector<int> tree;

void update()
{
    int k, x;
    cin >> k >> x;
    k--;

    int node = s/2 + k;
    tree[node] = x;

    do {
        node = (node-1) / 2;
        tree[node] = max(tree[node*2 + 1], tree[node*2 + 2]);
    } while (node > 0);
}

vector<int> bases;

class Node
{
public:

    int index;
    int l, r;

    Node* son(bool num)
    {
        if (num == 0) {
            if (! s[0]) {
                s[0] = new Node(index*2 + 1, l, (l+r)/2);
            }
            return s[0];
        } else {
            if (! s[1]) {
                s[1] = new Node(index*2 + 2, (l+r)/2 + 1, r);
            }
            return s[1];
        }
    }

private:

    Node* s[2];

public:

    Node(int _index, int _l, int _r)
    : index(_index), l(_l), r(_r)
    {
        s[0] = NULL;
        s[1] = NULL;
    }

    explicit Node(Node* other)
    {
        *this = Node(other->index, other->l, other->r);
    }

    ~Node()
    {
        if (s[0]) delete s[0];
        if (s[1]) delete s[1];
    }
};

void find_bases(Node node, int p, int q)
{
    if (p == node.l && q == node.r) {
        bases.push_back(node.index);
        return;
    }

    if (q <= node.son(0)->r)
    {
        find_bases(Node(node.son(0)), p, q);
    }
    else if (node.son(1)->l <= p)
    {
        find_bases(Node(node.son(1)), p, q);
    }
    else
    {
        find_bases(Node(node.son(0)), p, node.son(0)->r);
        find_bases(Node(node.son(1)), node.son(1)->l, q);
    }
}

void maximal()
{
    int p, q;
    cin >> p >> q;
    p--, q--;

    bases.clear();
    find_bases(Node(0, 0, s/2), p, q);

    int maximum = -INF;
    for (int i = 0; i < bases.size(); i++) {
        maximum = max(maximum, tree[bases[i]]);
    }

    cout << maximum << "\n";
}

int make_tree(int node)
{
    if (node < s/2) {
        tree[node] = max(make_tree(node*2 + 1), make_tree(node*2 + 2));
    }

    return tree[node];
}

int main()
{
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    s = 1;
    while (s < n) {
        s *= 2;
    }
    s = s*2 - 1;

    tree.reserve(s);
    for (int i = s/2; i < s; i++) {
        if (i - s/2 < n) cin >> tree[i];
        else tree[i] = -INF;
    }

    make_tree(0);

    for (int t = 0; t < m; t++) {
        string str;
        cin >> str;
        if (str == "UPDATE") update();
        else maximal();
    }
}
