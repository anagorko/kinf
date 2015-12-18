#define DEBUG 0

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node
{
    int l, r, val;
};

int s;
int levels_count;
vector<Node> tree;

void update_node(int node, int divisor, bool go_down)
{

    if (go_down && node >= s/2) return;

    int son[2];
    son[0] = node*2 + 1;
    son[1] = node*2 + 2;

    if (go_down) {
        update_node(son[0], divisor*2, true);
        update_node(son[1], divisor*2, true);
    }

    tree[node].l = tree[son[0]].l
        + (tree[son[0]].l == ((s+1)/2) / (divisor*2) ? tree[son[1]].l : 0);
    tree[node].r = tree[son[1]].r
        + (tree[son[1]].r == ((s+1)/2) / (divisor*2) ? tree[son[0]].r : 0);
    tree[node].val = max(
        max(tree[son[0]].val, tree[son[1]].val),
        tree[son[0]].r + tree[son[1]].l
    );

    if (! go_down) {
        if (node == 0) return;
        update_node((node-1) / 2, divisor/2, false);
    }
}

void change(int node)
{
    node += s/2;

    tree[node].val = ! tree[node].val;
    tree[node].l = ! tree[node].l;
    tree[node].r = ! tree[node].r;

    update_node((node-1) / 2, ((s+1)/2) / 2, false);

    cout << tree[0].val << "\n";
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
        char val;
        if (i - s/2 < n) cin >> val;
        else val = 1;
        tree[i].val = val == '0';
        tree[i].l = val == '0';
        tree[i].r = val == '0';
    }

    update_node(0, 1, true);

    for (int t = 0; t < m; t++) {

        #if DEBUG
        for (int i = 0; i < s; i++) cout << i % 10 << " "; cout << endl;
        for (int i = 0; i < s; i++) cout << tree[i].val << " "; cout << endl;
        for (int i = 0; i < s; i++) cout << tree[i].l << " "; cout << endl;
        for (int i = 0; i < s; i++) cout << tree[i].r << " "; cout << endl;
        #endif // DEBUG

        int pos;
        cin >> pos;
        change(pos - 1);
    }
}
